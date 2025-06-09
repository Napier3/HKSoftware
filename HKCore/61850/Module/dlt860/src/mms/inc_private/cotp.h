/*
 *  cotp.h
 */

#ifndef GSP_COTP_H_
#define GSP_COTP_H_

#include "libdlt860_platform_includes.h"
#include "byte_buffer.h"
#include "buffer_chain.h"
#include "gsp_hal_socket.h"
#include "gsp_iso_connection_parameters.h"
#include "gsp_tls_socket.h"

typedef struct {
    GspTSelector tSelSrc;
    GspTSelector tSelDst;
    uint8_t tpduSize;
} GspCotpOptions;

typedef union {
    struct CC {
        uint8_t pi:4;
        uint8_t bak:1;
        uint8_t err:1;
        uint8_t resp:1;
        uint8_t next:1;
    } cc;
    uint8_t data;
} GspCcUnion;

typedef struct {
    // 链接状态
    int state;

    // ref
    int remoteRef;
    int localRef;

    // 协议类型
    int protocolClass;

    // 底层socket链接
    GspSocket socket;

    // tls socket 链接
#if (CONFIG_MMS_SUPPORT_TLS == 1)
    TLSSocket tlsSocket;
#endif

    // 链接选项
    GspCotpOptions options;

    // 是否是最后一帧数据
    bool isLastDataUnit;

    // 数据缓存
    GspByteBuffer* payload;

    // 发送帧内存
    GspByteBuffer* writeBuffer;
    
    // 接受帧内存
    GspByteBuffer* readBuffer;

    // 当前接受的包的长度
    uint16_t packetSize;

    // 请求消息的服务码
    uint8_t requestSC;

    // 回应消息的服务码
    uint8_t responseSC;

    // CC码
    GspCcUnion ccUnion;

    // invokid
    uint16_t invokeID;

    // 分帧时上一帧的接收时间
    uint64_t lastFrameTime;

} GspCotpConnection;

typedef enum {
    COTP_OK,
    COTP_ERROR,
    COTP_CONNECT_INDICATION,
    COTP_DATA_INDICATION,
    COTP_DISCONNECT_INDICATION,
    COTP_MORE_FRAGMENTS_FOLLOW,
    COTP_REST_PAYLOAD
} GspCotpIndication;

typedef enum {
    TPKT_PACKET_COMPLETE = 0,
    TPKT_WAITING = 1,
    TPKT_ERROR = 2
} GspTpktState;

LIB860_INTERNAL int GspCotpConnection_getTpduSize(GspCotpConnection* self);

LIB860_INTERNAL void GspCotpConnection_setTpduSize(GspCotpConnection* self, int tpduSize);

LIB860_INTERNAL void GspCotpConnection_init(GspCotpConnection* self, GspSocket socket, GspByteBuffer* payloadBuffer, GspByteBuffer* readBuffer, GspByteBuffer* writeBuffer);

// 处理tcp 接受到的数据
LIB860_INTERNAL GspCotpIndication GspCotpConnection_parseGspIncomingMessage(GspCotpConnection* self);

// 重置负载数据大小为0(并不释放内存)
LIB860_INTERNAL void GspCotpConnection_resetPayload(GspCotpConnection* self);

// 读取 860 协议的 APCH 头部信息
LIB860_INTERNAL GspTpktState GspCotpConnection_readApch(GspCotpConnection* self);

// 发送 gsp 消息(服务端用)
LIB860_INTERNAL int GspCotpConnection_sendGspData(GspCotpConnection *self, uint8_t sc, uint8_t error, uint8_t respFlag, uint8_t next, GspByteBuffer *data);

// 发送 gsp 消息(客户端用)
LIB860_INTERNAL GspCotpIndication GspCotpConnection_sendGspMessage(GspCotpConnection* self, GspByteBuffer* payload);

// 获取链接中的负载数据
LIB860_INTERNAL GspByteBuffer* GspCotpConnection_getPayload(GspCotpConnection* self);

LIB860_INTERNAL int GspCotpConnection_getRemoteRef(GspCotpConnection* self);

LIB860_INTERNAL int GspCotpConnection_getLocalRef(GspCotpConnection* self);

#endif /* COTP_H_ */
