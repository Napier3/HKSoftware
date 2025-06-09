/*
 *  iso_connection.c
 */

#include "fmt/color.h"
#include "libdlt860_platform_includes.h"

#include "mms_service_table.h"
#include "stack_config.h"
#include "buffer_chain.h"
#include "cotp.h"
#include "iso_session.h"
#include "iso_server.h"
#include "gsp_hal_socket.h"
#include "gsp_hal_thread.h"

#include "iso_server_private.h"
#include "nlogging.h"
#include "mms_service_table.h"
#include "xer_encoder.h"

#ifndef DEBUG_ISO_SERVER
#ifdef DEBUG
#define DEBUG_ISO_SERVER 1
#else
#define DEBUG_ISO_SERVER 0
#endif /*DEBUG */
#endif /* DEBUG_ISO_SERVER */

#define RECEIVE_BUF_SIZE CONFIG_MMS_MAXIMUM_APDU_SIZE + 100
#define SEND_BUF_SIZE (1024 * 1024 * 2)

#define TPKT_RFC1006_HEADER_SIZE 4

struct sGspIsoConnection
{
    uint8_t* receiveBuffer;
    GspByteBuffer rcvBuffer;
    uint8_t* sendBuffer;
    uint8_t* cotpReadBuf;
    uint8_t* cotpWriteBuf;
    GspByteBuffer cotpReadBuffer;
    GspByteBuffer cotpWriteBuffer;
    GspMessageReceivedHandler msgRcvdHandler;
    GspMessageReceivedHandler msgGspMmsHandler;
    GspMessageReceivedHandler msgGspHandler;
    GspUserLayerTickHandler tickHandler;
    void* handlerParameter; /* context parameter for msgRcvdHandler */
    GspIsoServer isoServer;
    GspSocket socket;

#if (CONFIG_MMS_SUPPORT_TLS == 1)
    TLSSocket tlsSocket;
#endif

    int state;
    GspIsoSession* session;
    GspCotpConnection* cotpConnection;
    char* clientAddress;
    char* localAddress;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspThread thread;
    GspSemaphore conMutex;
#endif

#if (CONFIG_MMS_SINGLE_THREADED != 1) || (CONFIG_MMS_THREADLESS_STACK == 1)
    HandleSet handleSet;
#endif
};

static void
finalizeIsoConnection(GspIsoConnection self)
{
    if (DEBUG_ISO_SERVER)
        printf("ISO_SERVER: finalizeIsoConnection (%p)--> close transport connection\n", self);

#if (CONFIG_MMS_SUPPORT_TLS == 1)
    if (self->tlsSocket)
        TLSSocket_close(self->tlsSocket);
#endif

#if (CONFIG_MMS_THREADLESS_STACK != 1)
#if (CONFIG_MMS_SINGLE_THREADED != 1)
    if (self->handleSet) {
        Handleset_destroy(self->handleSet);
        self->handleSet = NULL;
    }
#endif
#endif

    GLOBAL_FREEMEM(self->session);
    GLOBAL_FREEMEM(self->cotpReadBuf);
    GLOBAL_FREEMEM(self->cotpWriteBuf);
    GLOBAL_FREEMEM(self->cotpConnection);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_destroy(self->conMutex);
#endif

    GLOBAL_FREEMEM(self->receiveBuffer);
    GLOBAL_FREEMEM(self->sendBuffer);
    GLOBAL_FREEMEM(self->clientAddress);
    GLOBAL_FREEMEM(self->localAddress);
    GspIsoServer isoServer = self->isoServer;

    if (DEBUG_ISO_SERVER)
        printf("ISO_SERVER: connection %p closed\n", self);

    Private_IsoServer_decreaseConnectionCounter(isoServer);
}

void
IsoConnection_addToHandleSet(const GspIsoConnection self, GspHandleSet handles)
{
   GspHandleset_addSocket(handles, self->socket);
}

void
IsoConnection_removeFromHandleSet(const GspIsoConnection self, GspHandleSet handles)
{
    GspHandleset_removeSocket(handles, self->socket);
}

void IsoConnection_callTickHandler(GspIsoConnection self)
{
    if (self->tickHandler) {
        self->tickHandler(self->handlerParameter);
    }
}

uint8_t GspIsoConnection_getGspSc(GspIsoConnection self)
{
    return self->cotpConnection->requestSC;
}

int IsoConnection_getConnectionId(GspIsoConnection self) {
    return GspSocket_getId(self->cotpConnection->socket);
}

int GspIsoConnection_getGspNext(GspIsoConnection self)
{
    return self->cotpConnection->ccUnion.cc.next;
}

int GspIsoConnection_getGspResp(GspIsoConnection self)
{
    return self->cotpConnection->ccUnion.cc.resp;
}

int GspIsoConnection_getGspError(GspIsoConnection self)
{
    return self->cotpConnection->ccUnion.cc.err;
}

void GspIsoConnection_setCc(GspIsoConnection self, uint8_t next, uint8_t resp, uint8_t error) {
    self->cotpConnection->ccUnion.cc.next = next;
    self->cotpConnection->ccUnion.cc.resp = resp;
    self->cotpConnection->ccUnion.cc.err = error;
}

int IsoConnection_sendGspReport(GspIsoConnection self, GspByteBuffer *response)
{
    int ret = GspCotpConnection_sendGspData(self->cotpConnection, GSP_SC_Report, 0, 0, 0, response);
    return ret;
}

int
IsoConnection_sendGspData(GspIsoConnection self, uint8_t error, uint8_t respFlag, GspByteBuffer *response) {

    if(response->size == 0)
    {
        response->size = 4;
        int ret = GspCotpConnection_sendGspData(self->cotpConnection, self->cotpConnection->requestSC, error, respFlag, 0, response);
        if(ret != response->size)
        {
            NLOG_ERROR("服务端发送数据失败，应发送{}，实际发送{}", response->size, ret);
            response->size = 0;
            return 0;
        }
        response->size = 0;
        return 1;
    }

    GspByteBuffer currentResp;
    currentResp.maxSize = 30006;
    currentResp.buffer = response->buffer;
    currentResp.size = min(30006, response->size);
    response->size -= 6;
    NLOG_DEBUG("response size {}", response->size);
    uint8_t next = response->size > 30000;
    NLOG_DEBUG("服务端发送数据，共[{}]字节, 不包含帧头", response->size);
    while(true)
    {
        int ret = GspCotpConnection_sendGspData(self->cotpConnection, self->cotpConnection->requestSC, error, respFlag, next, &currentResp);
        if(ret != currentResp.size)
        {
            NLOG_ERROR("服务端发送数据失败，应发送{}，实际发送{}", currentResp.size, ret);
        }
        
        response->size -= (currentResp.size - 6);
        if(response->size == 0)
        {
            NLOG_DEBUG("服务端发送数据完成，最后一帧[{}]字节, 不包含帧头", currentResp.size - 6);
        }
        else
        {
            NLOG_DEBUG("服务端发送数据完成，发送[{}]字节, 不包含帧头", currentResp.size - 6);
        }
        if(!next)
        {
            break;
        }

        currentResp.buffer = response->buffer + currentResp.size - 6;
        currentResp.size = min(30006, response->size + 6);
        next = (response->size > 30006);
    }
    response->size = 0;
    return 1;
}

int IsoConnection_sendGspResp(GspIsoConnection self, GspByteBuffer *response) {
    return IsoConnection_sendGspData(self, 0, 1, response);
}

int IsoConnection_sendGspError(GspIsoConnection self, GspByteBuffer *response) {
    return IsoConnection_sendGspData(self, 1, 1, response);
}

void IsoConnection_handleGspTcpConnection(GspIsoConnection self, bool isSingleThread)
{
    GspTpktState tpktState = GspCotpConnection_readApch(self->cotpConnection);

    if (tpktState == TPKT_ERROR)
        self->state = GSP_ISO_CON_STATE_STOPPED;

    GspCotpIndication cotpIndication;
    if (tpktState != TPKT_PACKET_COMPLETE)
        goto exit_function;

    cotpIndication = GspCotpConnection_parseGspIncomingMessage(self->cotpConnection);

    switch (cotpIndication) {
    case COTP_MORE_FRAGMENTS_FOLLOW:
        goto exit_function;
    case COTP_DATA_INDICATION:
    {
        GspByteBuffer* mmsRequest = self->cotpConnection->payload;
        GspByteBuffer mmsResponseBuffer;

#if (CONFIG_MMS_THREADLESS_STACK != 1)
        IsoServer_userLock(self->isoServer);
        GspIsoConnection_lock(self);
#endif

        GspByteBuffer_wrap(&mmsResponseBuffer, self->sendBuffer, 0, SEND_BUF_SIZE);

        if(self->cotpConnection->ccUnion.cc.pi == 0)
        {
            if(self->msgGspHandler != NULL)
            {
                if (self->msgGspHandler != NULL) {
                    self->msgGspHandler(self->handlerParameter, mmsRequest, &mmsResponseBuffer);
                }
            }
        } else {
            if(self->msgGspMmsHandler != NULL)
            {
                if (self->msgGspMmsHandler != NULL) {
                    self->msgGspMmsHandler(self->handlerParameter, mmsRequest, &mmsResponseBuffer);
                }
            }
        }
        if (mmsResponseBuffer.size > 0) {
            GspCotpConnection_sendGspMessage(self->cotpConnection, &mmsResponseBuffer);
        }
#if (CONFIG_MMS_THREADLESS_STACK != 1)
        GspIsoConnection_unlock(self);
        IsoServer_userUnlock(self->isoServer);
#endif
        GspCotpConnection_resetPayload(self->cotpConnection);
    }
        break;
    case COTP_ERROR:
        if (DEBUG_ISO_SERVER)
            printf("ISO_SERVER: Connection closed\n");
        self->state = GSP_ISO_CON_STATE_STOPPED;
        break;
    default:
        if (DEBUG_ISO_SERVER)
            printf("ISO_SERVER: COTP unknown indication: %i\n", cotpIndication);
        self->state = GSP_ISO_CON_STATE_STOPPED;
        break;
    }
exit_function:
    return;
}

#if ((CONFIG_MMS_SINGLE_THREADED == 0) && (CONFIG_MMS_THREADLESS_STACK == 0))
/* only for multi-thread mode */
static void
handleTcpConnection(void* parameter)
{
    IsoConnection self = (IsoConnection) parameter;

    while(self->state == ISO_CON_STATE_RUNNING)
        IsoConnection_handleTcpConnection(self, false);

    IsoServer_closeConnection(self->isoServer, self);

    finalizeIsoConnection(self);

    self->state = ISO_CON_STATE_TERMINATED;
}
#endif

GspIsoConnection IsoConnection_create(GspSocket socket, GspIsoServer isoServer, bool isSingleThread)
{
    GspIsoConnection self = (GspIsoConnection) GLOBAL_CALLOC(1, sizeof(struct sGspIsoConnection));
    self->socket = socket;

#if (CONFIG_MMS_SUPPORT_TLS == 1)
    if (IsoServer_getTLSConfiguration(isoServer) != NULL) {
        self->tlsSocket = TLSSocket_create(socket, IsoServer_getTLSConfiguration(isoServer), true);

        if (self->tlsSocket == NULL) {
            if (DEBUG_ISO_SERVER)
                printf("ISO_SERVER: IsoConnection - TLS initialization failed\n");

            GLOBAL_FREEMEM(self);

            return NULL;
        }
    }
#endif /* (CONFIG_MMS_SUPPORT_TLS == 1) */


    self->receiveBuffer = (uint8_t*) GLOBAL_MALLOC(RECEIVE_BUF_SIZE);
    self->sendBuffer = (uint8_t*) GLOBAL_MALLOC(SEND_BUF_SIZE);
    self->msgRcvdHandler = NULL;
    self->msgGspMmsHandler = NULL;
    self->msgGspHandler = NULL;
    self->tickHandler = NULL;
    self->handlerParameter = NULL;
    self->isoServer = isoServer;
    self->state = GSP_ISO_CON_STATE_RUNNING;
    self->clientAddress = GspSocket_getPeerAddress(self->socket);
    self->localAddress = GspSocket_getLocalAddress(self->socket);

#if (CONFIG_MMS_THREADLESS_STACK != 1)
    self->conMutex = GspSemaphore_create(1);
#endif

    GspByteBuffer_wrap(&(self->rcvBuffer), self->receiveBuffer, 0, RECEIVE_BUF_SIZE);

    self->cotpReadBuf = (uint8_t*) GLOBAL_MALLOC(CONFIG_COTP_MAX_TPDU_SIZE + TPKT_RFC1006_HEADER_SIZE);
    self->cotpWriteBuf = (uint8_t*) GLOBAL_MALLOC(CONFIG_COTP_MAX_TPDU_SIZE + TPKT_RFC1006_HEADER_SIZE);

    GspByteBuffer_wrap(&(self->cotpReadBuffer), self->cotpReadBuf, 0, CONFIG_COTP_MAX_TPDU_SIZE + TPKT_RFC1006_HEADER_SIZE);
    GspByteBuffer_wrap(&(self->cotpWriteBuffer), self->cotpWriteBuf, 0, CONFIG_COTP_MAX_TPDU_SIZE + TPKT_RFC1006_HEADER_SIZE);

    self->cotpConnection = (GspCotpConnection*) GLOBAL_CALLOC(1, sizeof(GspCotpConnection));
    GspCotpConnection_init(self->cotpConnection, self->socket, &(self->rcvBuffer), &(self->cotpReadBuffer), &(self->cotpWriteBuffer));

#if (CONFIG_MMS_SUPPORT_TLS == 1)
    if (self->tlsSocket)
        self->cotpConnection->tlsSocket = self->tlsSocket;
#endif /* (CONFIG_MMS_SUPPORT_TLS == 1) */

    self->session = (GspIsoSession*) GLOBAL_CALLOC(1, sizeof(GspIsoSession));
    GspIsoSession_init(self->session);

    if (DEBUG_ISO_SERVER)
        printf("ISO_SERVER: IsoConnection: Start to handle connection for client %s\n", self->clientAddress);

#if (CONFIG_MMS_SINGLE_THREADED == 0)
#if (CONFIG_MMS_THREADLESS_STACK == 0)
    if (isSingleThread == false) {
        self->handleSet = Handleset_new();
        Handleset_addSocket(self->handleSet, self->socket);
        self->thread = Thread_create((ThreadExecutionFunction) handleTcpConnection, self, false);
    }
#endif
#endif

    return self;
}

int
IsoConnection_getState(GspIsoConnection self)
{
    return self->state;
}

void
IsoConnection_start(GspIsoConnection self)
{
#if (CONFIG_MMS_SINGLE_THREADED == 0)
#if (CONFIG_MMS_THREADLESS_STACK == 0)
    Thread_start(self->thread);
#endif
#endif
}

void
IsoConnection_destroy(GspIsoConnection self)
{
#if (CONFIG_MMS_THREADLESS_STACK == 0) && (CONFIG_MMS_SINGLE_THREADED == 0)
    if (self->thread)
        Thread_destroy(self->thread);
#endif

    if (self->socket != NULL)
        GspSocket_destroy(self->socket);

    GLOBAL_FREEMEM(self);
}

char*
GspIsoConnection_getPeerAddress(GspIsoConnection self)
{
    return self->clientAddress;
}

char*
GspIsoConnection_getLocalAddress(GspIsoConnection self)
{
    return self->localAddress;
}

void
GspIsoConnection_lock(GspIsoConnection self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_wait(self->conMutex);
#endif
}

void
GspIsoConnection_unlock(GspIsoConnection self)
{
#if (CONFIG_MMS_THREADLESS_STACK != 1)
    GspSemaphore_post(self->conMutex);
#endif
}

uint64_t GspIsoConnection_getConnectID(GspIsoConnection self)
{
    return GspIsoServer_getConnectionId(self->isoServer, self);
}

void
GspIsoConnection_close(GspIsoConnection self)
{
    if (self->state != GSP_ISO_CON_STATE_TERMINATED) {
        self->state = GSP_ISO_CON_STATE_STOPPED;

#if (CONFIG_MMS_THREADLESS_STACK != 1) && (CONFIG_MMS_SINGLE_THREADED != 1)
        /* wait for connection thread to terminate */
        if (self->thread) {
            Thread_destroy(self->thread);
            self->thread = NULL;
        }
        else {
            finalizeIsoConnection(self);
            self->state = ISO_CON_STATE_TERMINATED;
        }
#else
        finalizeIsoConnection(self);
        self->state = GSP_ISO_CON_STATE_TERMINATED;
#endif
    }
}

void
GspIsoConnection_installListener(GspIsoConnection self, GspMessageReceivedHandler rcvdHandler,
        GspUserLayerTickHandler tickHandler,
        void* parameter)
{
    self->msgRcvdHandler = rcvdHandler;
    self->tickHandler = tickHandler;
    self->handlerParameter = parameter;
}

void
GspIsoConnection_installGspListener(GspIsoConnection self,
                                 GspMessageReceivedHandler rcvdMmsHandler,
                                 GspMessageReceivedHandler rcvdGspHandler,
        GspUserLayerTickHandler tickHandler,
        void* parameter)
{
    self->msgGspMmsHandler = rcvdMmsHandler;
    self->msgGspHandler = rcvdGspHandler;
    self->tickHandler = tickHandler;
    self->handlerParameter = parameter;
}

void*
GspIsoConnection_getSecurityToken(GspIsoConnection self)
{
    // TODO 服务端暂时不支持
    return /*self->acseConnection->securityToken*/ nullptr;
}

bool
IsoConnection_isRunning(GspIsoConnection self)
{
    if (self->state == GSP_ISO_CON_STATE_RUNNING)
        return true;
    else
        return false;
}