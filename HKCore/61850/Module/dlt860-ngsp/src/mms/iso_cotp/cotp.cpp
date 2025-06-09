/*
 *  cotp.c
 */

#include "libdlt860_platform_includes.h"
#include "stack_config.h"
#include "cotp.h"
#include "byte_buffer.h"
#include "buffer_chain.h"

#define TPKT_RFC1006_HEADER_SIZE 4

#define COTP_DATA_HEADER_SIZE 3
#ifdef CONFIG_COTP_MAX_TPDU_SIZE
#define COTP_MAX_TPDU_SIZE CONFIG_COTP_MAX_TPDU_SIZE
#else
#define COTP_MAX_TPDU_SIZE 65535
#endif

#ifndef DEBUG_COTP
#define DEBUG_COTP 1
#endif

/**
 * @brief addPayloadToBuffer 拷贝负载数据到负载指针中
 * @param self 链接信息
 * @param buffer 负载缓存
 * @param payloadLength 负载长度
 * @return
 */
static bool addPayloadToBuffer(GspCotpConnection* self, uint8_t* buffer, int payloadLength);

static int writeToSocket(GspCotpConnection* self, uint8_t* buf, int size)
{
#if (CONFIG_MMS_SUPPORT_TLS == 1)
    if (self->tlsSocket)
        return TLSSocket_write(self->tlsSocket, buf, size);
    else
        return Socket_write(self->socket, buf, size);
#else
    return GspSocket_write(self->socket, buf, size);
#endif
}

GspCotpIndication GspCotpConnection_sendGspMessage(GspCotpConnection* self, GspByteBuffer* payload)
{
    // 调试信息
    if(self->responseSC == 0x5a){
        Global_LogString("！！！！！！！！！！！！！！！！出现了不该出现的报文！！！！！！！！！！！！！！！！！！！！！\n");
    }

    // 修改发送缓存
    uint8_t *writeDataPayload = new uint8_t[4 + payload->maxSize];

    // 设置帧头
    writeDataPayload[0] = self->ccUnion.data;
    writeDataPayload[1] = self->responseSC;

    // 设置数据单元数值
    uint16_t fl = (uint16_t)payload->size;
    memcpy(writeDataPayload + 2, &fl, sizeof(fl));

    // 设置数据单元内容
    if(payload->size > 0){
        memcpy(writeDataPayload + 4, payload->buffer, (unsigned long)payload->size);
    }

    // 发送数据
    GspCotpIndication retValue = COTP_OK;
    int sentBytes = writeToSocket(self, writeDataPayload, 4 + payload->size);

    // 释放内存
    delete[] writeDataPayload;

    // 发送结果
    if (sentBytes == -1) {
        return COTP_ERROR;
    }
    return retValue;
}

int GspCotpConnection_sendGspData(GspCotpConnection *self, uint8_t sc, uint8_t error, uint8_t respFlag, uint8_t next, GspByteBuffer *data) {
    GspCcUnion cc;
    cc.data = 0;
    cc.cc.err = error;
    cc.cc.resp = respFlag;
    cc.cc.next = next;
    cc.cc.pi = 1;
    uint8_t apch[6];
    apch[0] = cc.data;
    apch[1] = sc;
    uint16_t dataSize = data->size - 4;
    memcpy(apch + 2, &dataSize, 2);

    if(dataSize == 0)
    {
        memcpy(data->buffer, apch, 4);
    } else {
        if(sc != 90){
            memcpy(apch + 4, &self->invokeID, 2);
        } else {
            memset(apch + 4, 0, 2);
        }
        memcpy(data->buffer, apch, 6);
    }

    int byteWritten = 0;
    if(data->size > 0) {
        byteWritten = writeToSocket(self, data->buffer, data->size);
    }
    return byteWritten;
}

void GspCotpConnection_init(GspCotpConnection* self, GspSocket socket, GspByteBuffer* payloadBuffer, GspByteBuffer* readBuffer, GspByteBuffer* writeBuffer)
{
    self->state = 0;
    self->socket = socket;
#if (CONFIG_MMS_SUPPORT_TLS == 1)
    self->tlsSocket = NULL;
#endif
    self->remoteRef = -1;
    self->localRef = 1;
    self->protocolClass = -1;
    self->options.tpduSize = 0;

    GspTSelector tsel;
    tsel.size = 2;
    tsel.value[0] = 0;
    tsel.value[1] = 1;

    self->options.tSelSrc = tsel;
    self->options.tSelDst = tsel;
    self->payload = payloadBuffer;

    GspCotpConnection_resetPayload(self);
    GspCotpConnection_setTpduSize(self, COTP_MAX_TPDU_SIZE);

    self->writeBuffer = writeBuffer;
    self->readBuffer = readBuffer;
    self->packetSize = 0;
}

int GspCotpConnection_getTpduSize(GspCotpConnection* self)
{
    return (1 << self->options.tpduSize);
}

void GspCotpConnection_setTpduSize(GspCotpConnection* self, int tpduSize /* in byte */)
{
    int newTpduSize = 1;

    if (tpduSize > COTP_MAX_TPDU_SIZE)
        tpduSize = COTP_MAX_TPDU_SIZE;

    while ((1 << newTpduSize) < tpduSize)
        newTpduSize++;

    if ((1 << newTpduSize) > tpduSize)
        newTpduSize--;

    self->options.tpduSize = newTpduSize;
}

GspByteBuffer* GspCotpConnection_getPayload(GspCotpConnection* self)
{
    return self->payload;
}

int GspCotpConnection_getRemoteRef(GspCotpConnection* self)
{
    return self->remoteRef;
}

int GspCotpConnection_getLocalRef(GspCotpConnection* self)
{
    return self->localRef;
}

static bool addPayloadToBuffer(GspCotpConnection* self, uint8_t* buffer, int payloadLength)
{
    if (payloadLength < 0) {
        if (DEBUG_COTP)
            Global_LogString("GSP: missing payload\n");
        return false;
    }

    if (DEBUG_COTP)
        Global_LogString("GSP: add to payload buffer (cur size: %i, len: %i)\n", self->payload->size, payloadLength);

    if ((self->payload->size + payloadLength) > self->payload->maxSize){
        if (DEBUG_COTP)
            Global_LogString("GSP: self->payload->maxSize: %d \n", self->payload->maxSize);
        return false;
    }

    memcpy(self->payload->buffer + self->payload->size, buffer, payloadLength);
    self->payload->size += payloadLength;
    return true;
}

static GspCotpIndication parseGspCotpMessage(GspCotpConnection* self)
{
    // 数据
    uint8_t* buffer = self->readBuffer->buffer;

    // 仅有报文头
    if(self->readBuffer->size == 4) {
        self->invokeID = 0;
        return COTP_DATA_INDICATION;
    }

    // invokid 部分
    buffer += 4;
    self->invokeID = (buffer[1] << 8) + buffer[0];

    // data 部分
    buffer += 2;
    int tpduLength = self->readBuffer->size - 6;
    if (!addPayloadToBuffer(self, buffer, tpduLength)){
        if (DEBUG_COTP) {

            // 错误信息打印
            Global_LogString("GSP: addPayloadToBuffer error\n");

            // return COTP_ERROR;
            // 无论什么情况都不要断开连接
            return COTP_REST_PAYLOAD;
        }
    }

    // 还有后续帧
    if(self->ccUnion.cc.next)
    {
        return COTP_MORE_FRAGMENTS_FOLLOW;
    }
    return COTP_DATA_INDICATION;
}

GspCotpIndication GspCotpConnection_parseGspIncomingMessage(GspCotpConnection* self)
{
    // 解析数据
    GspCotpIndication indication = parseGspCotpMessage(self);

    // 重置标记数据
    self->readBuffer->size = 0;
    self->packetSize = 0;

    return indication;
}

void GspCotpConnection_resetPayload(GspCotpConnection* self)
{
    self->payload->size = 0;
}

static int readFromSocket(GspCotpConnection* self, uint8_t* buf, int size)
{
#if (CONFIG_MMS_SUPPORT_TLS == 1)
    if (self->tlsSocket)
        return TLSSocket_read(self->tlsSocket, buf, size);
    else
        return Socket_read(self->socket, buf, size);
#else
    return GspSocket_read(self->socket, buf, size);
#endif
}

GspTpktState GspCotpConnection_readApch(GspCotpConnection *self)
{
    // 获取接受到的缓存数据
    uint8_t* buffer = self->readBuffer->buffer;

    // 最大缓存尺寸
    int bufferSize = self->readBuffer->maxSize;

    // 当前数据尺寸
    int bufPos = self->readBuffer->size;

	// 仅有报文头
	if(self->readBuffer->size == 4) {
		self->invokeID = 0;
		return TPKT_PACKET_COMPLETE;
	}

    // 数据最大尺寸断言
    assert (bufferSize > 4);

    int readBytes;
    // 前四个字节是报文头
    if (bufPos < 4) {
        readBytes = readFromSocket(self, buffer + bufPos, 4 - bufPos);
        if (readBytes < 0)
            goto exit_closed;

        if (DEBUG_COTP) {
            if (readBytes > 0)
                Global_LogString("TPKT: read %i bytes from socket\n", readBytes);
        }

        // 解析报文头
        bufPos += readBytes;
        if (bufPos == 4) {
            self->ccUnion.data = buffer[0];
            self->requestSC = buffer[1];
            if(self->ccUnion.cc.pi <= 1) {
                self->packetSize = (buffer[3] << 8) + buffer[2];
                if (DEBUG_COTP)
                    Global_LogString("GSP: header complete (msg size = %i)\n", self->packetSize);

                if (self->packetSize > bufferSize) {
                    if (DEBUG_COTP) Global_LogString("GSP: packet too large\n");
                    goto exit_error;
                }
            } else {
                if (DEBUG_COTP)
                    Global_LogString("GSP: failed to decode APCH header.\n");
                goto exit_error;
            }
        } else {
            goto exit_waiting;
        }
    }

    // 读报文体
    readBytes = readFromSocket(self, buffer + bufPos, self->packetSize - (bufPos - 4));
    if (readBytes < 0)
        goto exit_closed;
    bufPos += readBytes;
    if (bufPos < self->packetSize)
        goto exit_waiting;
    if (DEBUG_COTP) {
        Global_LogString("GSP: message complete (size = %i)\n", self->packetSize);
    }
    self->readBuffer->size = bufPos;
    return TPKT_PACKET_COMPLETE;

exit_closed:
    if (DEBUG_COTP)
        Global_LogString("GSP: socket closed or socket error\n");
    return TPKT_ERROR;

exit_error:
    if (DEBUG_COTP)
        Global_LogString("GSP: Error parsing message\n");
    return TPKT_ERROR;

exit_waiting:
    if (DEBUG_COTP)
        if (bufPos != 0)
            Global_LogString("GSP: waiting (read %i of %i)\n", bufPos, self->packetSize);

    self->readBuffer->size = bufPos;
    return TPKT_WAITING;
}
