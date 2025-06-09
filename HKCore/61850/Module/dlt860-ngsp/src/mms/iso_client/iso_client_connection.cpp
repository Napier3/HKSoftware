#include "libdlt860_platform_includes.h"
#include "stack_config.h"
#include "gsp_hal_socket.h"
#include "gsp_hal_thread.h"
#include "cotp.h"
#include "iso_session.h"
#include "iso_client_connection.h"
#include "gsp_tls_config.h"
#include "gsp_hal_time.h"


#ifndef DEBUG_ISO_CLIENT
#ifdef DEBUG
#define DEBUG_ISO_CLIENT 1
#else
#define DEBUG_ISO_CLIENT 0
#endif
#endif

#define GSP_STATE_IDLE 0
#define GSP_STATE_CONNECTED 1
#define GSP_STATE_ERROR 2
#define GSP_STATE_CONNECTING 3
#define GSP_TPKT_RFC1006_HEADER_SIZE 4

// 最大100帧数据缓存
#define GSP_ISO_CLIENT_BUFFER_SIZE CONFIG_MMS_MAXIMUM_APDU_SIZE * 100 + 100

// iso 链接客户端的状态
typedef enum {
    // 空闲状态
    GSP_INT_STATE_IDLE,
    // tcp 正在链接的状态
    GSP_INT_STATE_TCP_CONNECTING,
    // 等待数据状态
    GSP_INT_STATE_WAIT_FOR_DATA_MSG,
    // 关闭链接错误状态
    GSP_INT_STATE_CLOSE_ON_ERROR,
    // 错误的状态
    GSP_INT_STATE_ERROR
} eGspIsoClientInternalState;

// iso 链接信息
struct sGspIsoClientConnection
{
    // 链接参数
    GspIsoConnectionParameters parameters;

    // 链接的回调函数
    GspIsoIndicationCallback callback;
    void* callbackParameter;

    // 链接状态
    volatile eGspIsoClientInternalState intState;
    volatile int state;
    GspSemaphore stateMutex;

    // 链接读超时的参数
    uint32_t readTimeoutInMs;
    // 链接下一次的超时时间
    uint64_t nextReadTimeout;

    // socket 链接
    GspSocket socket;

    // tls 链接
#if (CONFIG_MMS_SUPPORT_TLS == 1)
    TLSSocket tlsSocket;
#endif

    // 传输层链接封装
    GspCotpConnection* cotpConnection;

    // 发送数据缓存
    GspByteBuffer* transmitPayloadBuffer;
    GspSemaphore transmitBufferMutex;

    // 这些链接封装将会被抛弃
    GspIsoSession* session;

    // mms 发送缓存(待发送的原始数据)
    uint8_t* sendBuffer;
    // mms 接收缓存(接受到的原始数据)
    uint8_t* receiveBuf;
    // 接受的数据缓存
    GspByteBuffer* receiveBuffer;

    // 链接的定时器信号量
    GspSemaphore tickMutex;

    // cotp 传输层读缓存
    uint8_t* cotpReadBuf;

    // cotp 传输层写缓存
    uint8_t* cotpWriteBuf;

    // 传输层读缓存
    GspByteBuffer* cotpReadBuffer;

    // 传输层写缓存
    GspByteBuffer* cotpWriteBuffer;
};

static void setState(GspIsoClientConnection self, int newState)
{
    GspSemaphore_wait(self->stateMutex);
    self->state = newState;
    GspSemaphore_post(self->stateMutex);
}

static int getState(GspIsoClientConnection self)
{
    int stateVal;

    GspSemaphore_wait(self->stateMutex);
    stateVal = self->state;
    GspSemaphore_post(self->stateMutex);

    return stateVal;
}

static void setIntState(GspIsoClientConnection self, eGspIsoClientInternalState newState)
{
    self->intState = newState;
}

static eGspIsoClientInternalState getIntState(GspIsoClientConnection self)
{
    return self->intState;
}

GspIsoClientConnection GspIsoClientConnection_create(GspIsoConnectionParameters parameters, GspIsoIndicationCallback callback, void* callbackParameter)
{
    GspIsoClientConnection self = (GspIsoClientConnection) GLOBAL_CALLOC(1, sizeof(struct sGspIsoClientConnection));

    if (self) {
        self->parameters = parameters;
        self->callback = callback;
        self->callbackParameter = callbackParameter;
        self->intState = GSP_INT_STATE_IDLE;
        self->state = GSP_STATE_IDLE;
        self->stateMutex = GspSemaphore_create(1);

        self->sendBuffer = (uint8_t*) GLOBAL_MALLOC(GSP_ISO_CLIENT_BUFFER_SIZE);
        self->transmitPayloadBuffer = (GspByteBuffer*) GLOBAL_CALLOC(1, sizeof(GspByteBuffer));
        self->transmitPayloadBuffer->buffer = self->sendBuffer;
        self->transmitPayloadBuffer->maxSize = GSP_ISO_CLIENT_BUFFER_SIZE;

        self->transmitBufferMutex = GspSemaphore_create(1);
        self->tickMutex = GspSemaphore_create(1);

        self->receiveBuf = (uint8_t*) GLOBAL_MALLOC(GSP_ISO_CLIENT_BUFFER_SIZE);
        self->receiveBuffer = (GspByteBuffer*) GLOBAL_CALLOC(1, sizeof(GspByteBuffer));
        GspByteBuffer_wrap(self->receiveBuffer, self->receiveBuf, 0, GSP_ISO_CLIENT_BUFFER_SIZE);

        self->session = (GspIsoSession*) GLOBAL_CALLOC(1, sizeof(GspIsoSession));

        self->cotpReadBuf = (uint8_t*) GLOBAL_MALLOC(CONFIG_COTP_MAX_TPDU_SIZE + GSP_TPKT_RFC1006_HEADER_SIZE);
        self->cotpReadBuffer = (GspByteBuffer*) GLOBAL_CALLOC(1, sizeof(GspByteBuffer));
        GspByteBuffer_wrap(self->cotpReadBuffer, self->cotpReadBuf, 0, CONFIG_COTP_MAX_TPDU_SIZE + GSP_TPKT_RFC1006_HEADER_SIZE);

        self->cotpWriteBuf = (uint8_t*) GLOBAL_MALLOC(CONFIG_COTP_MAX_TPDU_SIZE + GSP_TPKT_RFC1006_HEADER_SIZE);
        self->cotpWriteBuffer = (GspByteBuffer*) GLOBAL_CALLOC(1, sizeof(GspByteBuffer));
        GspByteBuffer_wrap(self->cotpWriteBuffer, self->cotpWriteBuf, 0, CONFIG_COTP_MAX_TPDU_SIZE + GSP_TPKT_RFC1006_HEADER_SIZE);

        self->cotpConnection = (GspCotpConnection*) GLOBAL_CALLOC(1, sizeof(GspCotpConnection));
    }

    return self;
}

static bool sendConnectionRequestMessage(GspIsoClientConnection self)
{
    /* COTP (ISO transport) handshake */
    GspCotpConnection_init(self->cotpConnection, self->socket, self->receiveBuffer, self->cotpReadBuffer, self->cotpWriteBuffer);

#if (CONFIG_MMS_SUPPORT_TLS == 1)
    if (self->parameters->tlsConfiguration) {

        TLSConfiguration_setClientMode(self->parameters->tlsConfiguration);

        /* create TLSSocket and start TLS authentication */
        TLSSocket tlsSocket = TLSSocket_create(self->socket, self->parameters->tlsConfiguration, false);

        if (tlsSocket)
            self->cotpConnection->tlsSocket = tlsSocket;
        else {

            if (g_nLogGspDebugString)
                Global_LogString("TLS handshake failed!\n");

            return false;
        }
    }
#endif

    GspCotpIndication cotpIndication = GspCotpConnection_sendGspMessage(self->cotpConnection, self->transmitPayloadBuffer);

    if (cotpIndication != COTP_OK)
        return false;
    else
        return true;
}

static void releaseSocket(GspIsoClientConnection self)
{
    if (self->socket) {

#if (CONFIG_MMS_SUPPORT_TLS == 1)
        if (self->cotpConnection->tlsSocket)
            TLSSocket_close(self->cotpConnection->tlsSocket);
#endif

        GspSocket_destroy(self->socket);
        self->socket = nullptr;
    }
}

bool GspIsoClientConnection_handleConnection(GspIsoClientConnection self)
{
    // 信号量等待
    GspSemaphore_wait(self->tickMutex);
    bool waits = false;

    // 获取当前的链接状态
    eGspIsoClientInternalState currentState = getIntState(self);

    // 理论上的下一个状态
    eGspIsoClientInternalState nextState = currentState;

    // 状态处理
    switch (currentState) {

    // 空闲状态
    case GSP_INT_STATE_IDLE:
    case GSP_INT_STATE_ERROR: {
        waits = true;
    } break;

    case GSP_INT_STATE_TCP_CONNECTING:
    {
        // 检查 socket 链接状态
        GspSocketState socketState = GspSocket_checkAsyncConnectState(self->socket);
        // tcp 链接成功
        if (socketState == GSP_SOCKET_STATE_CONNECTED) {
            // 发送关联协商帧
            if (sendConnectionRequestMessage(self)) {
                self->nextReadTimeout = GSP_Hal_getTimeInMs() + self->readTimeoutInMs;
                GspIsoClientConnection_releaseTransmitBuffer(self);
                nextState = GSP_INT_STATE_WAIT_FOR_DATA_MSG;
            } else {
                GspIsoClientConnection_releaseTransmitBuffer(self);
                self->callback(GSP_ISO_IND_ASSOCIATION_FAILED, self->callbackParameter, nullptr, 0);
                nextState = GSP_INT_STATE_CLOSE_ON_ERROR;
            }
        } else if (socketState == GSP_SOCKET_STATE_FAILED) {
            GspIsoClientConnection_releaseTransmitBuffer(self);
            self->callback(GSP_ISO_IND_ASSOCIATION_FAILED, self->callbackParameter, nullptr, 0);
            nextState = GSP_INT_STATE_CLOSE_ON_ERROR;
        } else {
            // 查询超时状态
            uint64_t currentTime = GSP_Hal_getTimeInMs();
            if (currentTime > self->nextReadTimeout) {
                GspIsoClientConnection_releaseTransmitBuffer(self);
                self->callback(GSP_ISO_IND_ASSOCIATION_FAILED, self->callbackParameter, nullptr, 0);
                nextState = GSP_INT_STATE_CLOSE_ON_ERROR;
            } else {
                waits = true;
            }
        }
    } break;

    case GSP_INT_STATE_WAIT_FOR_DATA_MSG:
    {
        // 读取报文并解析报文头
        GspTpktState packetState = GspCotpConnection_readApch(self->cotpConnection);
        if (packetState == TPKT_ERROR) {
            // 包头解析错误终止链接
            if(DEBUG_COTP){
                Global_LogString("出现错误的包，马上终止socket链接, 为了兼容性这里不在断连接\n");
            }
//            nextState = GSP_INT_STATE_CLOSE_ON_ERROR;
			// 重置链接状态
			nextState = GSP_INT_STATE_WAIT_FOR_DATA_MSG;
			// 重置负载信息
			GspCotpConnection_resetPayload(self->cotpConnection);
			self->cotpConnection->lastFrameTime = 0;
			self->cotpConnection->ccUnion.data = 0;

        } else if (packetState == TPKT_PACKET_COMPLETE) {

            // 有数据回应就认为链接成功了(这里后期可能会优化)
            setState(self, GSP_STATE_CONNECTED);

            // 报文解析处理
            GspCotpIndication cotpIndication = GspCotpConnection_parseGspIncomingMessage(self->cotpConnection);

            switch (cotpIndication) {
            case COTP_MORE_FRAGMENTS_FOLLOW:
            {
                // 调试信息
                if (g_nLogGspDebugString)
                    Global_LogString("ISO_CLIENT_CONNECTION: 等待后续数据帧\n");

                // 记录等待帧的时间
                self->cotpConnection->lastFrameTime = GSP_Hal_getTimeInMs();
            } break;
            case COTP_DATA_INDICATION:
            {
                // 调试信息
                if (g_nLogGspDebugString)
                    Global_LogString("ISO_CLIENT_CONNECTION: 收到完整的数据包，进行数据处理\n");

                // 报文处理
                self->callback(GSP_ISO_IND_DATA, self->callbackParameter, GspCotpConnection_getPayload(self->cotpConnection), self->cotpConnection->invokeID);

                // 重置负载信息
                GspCotpConnection_resetPayload(self->cotpConnection);
            } break;
            case COTP_REST_PAYLOAD:
                // 重置负载信息
                GspCotpConnection_resetPayload(self->cotpConnection);
                break;
            case COTP_ERROR:
                goto exit_function;
            default:
                break;
            }
        } else {
            // 当有下一帧时的超时处理
            if(self->cotpConnection->ccUnion.cc.next){
                uint64_t currentTimeMs = GSP_Hal_getTimeInMs();
                if((currentTimeMs - self->cotpConnection->lastFrameTime) > 1000 && self->cotpConnection->lastFrameTime > 0){
                    // 调试信息
                    if (g_nLogGspDebugString) {
                        Global_LogString("ISO_CLIENT_CONNECTION: 报文标记有下一帧数据，但是对方没给，超时处理，进行数据处理\n");
                    }

                    // 报文处理
                    self->callback(GSP_ISO_IND_DATA, self->callbackParameter, GspCotpConnection_getPayload(self->cotpConnection), self->cotpConnection->invokeID);

                    // 重置负载信息
                    GspCotpConnection_resetPayload(self->cotpConnection);
                    self->cotpConnection->lastFrameTime = 0;
                    self->cotpConnection->ccUnion.data = 0;
                }
            }

            // 等待后续数据
            waits = true;
        }

    } break;
    case GSP_INT_STATE_CLOSE_ON_ERROR:
    {
        // 链接关闭状态
        setState(self, GSP_STATE_ERROR);
        self->callback(GSP_ISO_IND_CLOSED, self->callbackParameter, nullptr, 0);
        releaseSocket(self);
        nextState = GSP_INT_STATE_ERROR;

    } break;
    default:{
        if (g_nLogGspDebugString)
            Global_LogString("ISO_CLIENT_CONNECTION: Illegal state\n");
    }
    }

exit_function:
    self->callback(GSP_ISO_IND_TICK, self->callbackParameter, nullptr, 0);
    setIntState(self, nextState);
    GspSemaphore_post(self->tickMutex);
    return waits;
}

bool GspIsoClientConnection_associateAsync(GspIsoClientConnection self, uint32_t connectTimeoutInMs, uint32_t readTimeoutInMs,const char* local_address)
{
    GspSemaphore_wait(self->tickMutex);

    // 创建TCP链接
    self->socket = GspTcpSocket_create();

    if (self->socket == nullptr) {
        GspSemaphore_post(self->tickMutex);
        return false;
    }

    bool success = true;

    // 设置链接状态
    setState(self, GSP_STATE_CONNECTING);
    setIntState(self, GSP_INT_STATE_TCP_CONNECTING);

    // keep alive
#if (CONFIG_ACTIVATE_TCP_KEEPALIVE == 1)
    GspSocket_activateTcpKeepAlive(self->socket,
                                   CONFIG_TCP_KEEPALIVE_IDLE,
                                   CONFIG_TCP_KEEPALIVE_INTERVAL,
                                   CONFIG_TCP_KEEPALIVE_CNT);
#endif

    // 设置读超时时间
    self->readTimeoutInMs = readTimeoutInMs;

    // 设置下一次操作的理论时间
    self->nextReadTimeout = GSP_Hal_getTimeInMs() + connectTimeoutInMs;

    // socket 建立链接
    if (!GspSocket_connectAsync(self->socket, self->parameters->hostname, self->parameters->tcpPort,local_address)) {
        GspSocket_destroy(self->socket);
        self->socket = nullptr;
        setIntState(self, GSP_INT_STATE_ERROR);
        setState(self, GSP_STATE_ERROR);
        GspIsoClientConnection_releaseTransmitBuffer(self);
        success = false;
    }

    GspSemaphore_post(self->tickMutex);

    return success;
}

uint8_t GspIsoClientConnection_getGspRequestSc(GspIsoClientConnection self)
{
    return self->cotpConnection->requestSC;
}

uint8_t GspIsoClientConnection_getGspResponseSc(GspIsoClientConnection self){
    return self->cotpConnection->responseSC;
}

int IsoClientConnection_getConnectionId(GspIsoClientConnection self) {
    return GspSocket_getId(self->cotpConnection->socket);
}

int GspIsoClientConnection_getGspNext(GspIsoClientConnection self)
{
    return self->cotpConnection->ccUnion.cc.next;
}

int GspIsoClientConnection_getGspResp(GspIsoClientConnection self)
{
    return self->cotpConnection->ccUnion.cc.resp;
}

int GspIsoClientConnection_getGspError(GspIsoClientConnection self)
{
    return self->cotpConnection->ccUnion.cc.err;
}

uint16_t GspIsoClientConnection_getGspInvokID(GspIsoClientConnection self)
{
    if(self->cotpConnection){
        return self->cotpConnection->invokeID;
    }
    return 0;
}

void* GspIsoClientConnection_getCallBackparam(GspIsoClientConnection self){
    return self->callbackParameter;
}

void GspIsoClientConnection_setCc(GspIsoClientConnection self, uint8_t next, uint8_t resp, uint8_t error, uint8_t pi) {
    self->cotpConnection->ccUnion.cc.next = next;
    self->cotpConnection->ccUnion.cc.resp = resp;
    self->cotpConnection->ccUnion.cc.err = error;
    self->cotpConnection->ccUnion.cc.pi = pi;
}

void GspIsoClientConnection_sendMessage(GspIsoClientConnection self, GspByteBuffer* payloadBuffer)
{
    if (getState(self) == GSP_STATE_CONNECTED) {
        GspCotpConnection_sendGspMessage(self->cotpConnection, payloadBuffer);
    } else {
        if (g_nLogGspDebugString)
            Global_LogString("ISO_CLIENT: Not connected --> cannot send message\n");
    }

    /* release transmit buffer for use by API client */
    GspSemaphore_post(self->transmitBufferMutex);
}

void GspIsoClientConnection_close(GspIsoClientConnection self)
{
    if (g_nLogGspDebugString)
        Global_LogString("ISO_CLIENT: IsoClientConnection_close\n");

    GspSemaphore_wait(self->tickMutex);

    eGspIsoClientInternalState intState = getIntState(self);
    if ((intState != GSP_INT_STATE_IDLE) && (intState != GSP_INT_STATE_ERROR) && (intState != GSP_INT_STATE_CLOSE_ON_ERROR)) {
        setIntState(self, GSP_INT_STATE_CLOSE_ON_ERROR);
        GspSemaphore_post(self->tickMutex);
        GspIsoClientConnection_handleConnection(self);
        setState(self, GSP_STATE_IDLE);
    } else {
        GspSemaphore_post(self->tickMutex);
    }
}

void GspIsoClientConnection_destroy(GspIsoClientConnection self)
{
    if (g_nLogGspDebugString)
        Global_LogString("ISO_CLIENT: IsoClientConnection_destroy\n");

    int state = getState(self);

    if (state == GSP_STATE_CONNECTED) {

        if (g_nLogGspDebugString)
            Global_LogString("ISO_CLIENT: call IsoClientConnection_close\n");

        GspIsoClientConnection_close(self);
    }

    releaseSocket(self);

    if (self->receiveBuf != nullptr)
        GLOBAL_FREEMEM(self->receiveBuf);

    if (self->receiveBuffer != nullptr)
        GLOBAL_FREEMEM(self->receiveBuffer);

    if (self->cotpConnection != nullptr)
        GLOBAL_FREEMEM(self->cotpConnection);

    if (self->cotpReadBuffer != nullptr)
        GLOBAL_FREEMEM(self->cotpReadBuffer);

    if (self->cotpReadBuf != nullptr)
        GLOBAL_FREEMEM(self->cotpReadBuf);

    if (self->cotpWriteBuffer != nullptr)
        GLOBAL_FREEMEM(self->cotpWriteBuffer);

    if (self->cotpWriteBuf != nullptr)
        GLOBAL_FREEMEM(self->cotpWriteBuf);

    if (self->session != nullptr)
        GLOBAL_FREEMEM(self->session);

    GLOBAL_FREEMEM(self->transmitPayloadBuffer);

    GspSemaphore_destroy(self->transmitBufferMutex);
    GspSemaphore_destroy(self->stateMutex);
    GspSemaphore_destroy(self->tickMutex);

    GLOBAL_FREEMEM(self->sendBuffer);
    GLOBAL_FREEMEM(self);
}

void GspIsoClientConnection_abortAsync(GspIsoClientConnection self)
{
    GspCotpConnection_sendGspMessage(self->cotpConnection, self->transmitPayloadBuffer);
    GspSemaphore_post(self->transmitBufferMutex);
}

GspByteBuffer* GspIsoClientConnection_allocateTransmitBuffer(GspIsoClientConnection self)
{
    GspSemaphore_wait(self->transmitBufferMutex);
    self->transmitPayloadBuffer->size = 0;
    self->transmitPayloadBuffer->maxSize = GSP_ISO_CLIENT_BUFFER_SIZE;
    return self->transmitPayloadBuffer;
}

void GspIsoClientConnection_releaseTransmitBuffer(GspIsoClientConnection self)
{
    GspSemaphore_post(self->transmitBufferMutex);
}

void GspIsoClientConnection_setResponseSc(GspIsoClientConnection self, uint8_t paramSC)
{
    self->cotpConnection->responseSC = paramSC;
}

void GspIsoClientConnection_setRequestSc(GspIsoClientConnection self, uint8_t paramSC){
    self->cotpConnection->requestSC = paramSC;
}
