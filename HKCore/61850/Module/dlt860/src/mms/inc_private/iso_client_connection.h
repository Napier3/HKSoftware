/*
 *  iso_client_connection.h
 */

#ifndef GSP_ISO_CLIENT_CONNECTION_H_
#define GSP_ISO_CLIENT_CONNECTION_H_

#include "byte_buffer.h"
#include "gsp_iso_connection_parameters.h"

// 回调函数索引
typedef enum
{
    GSP_ISO_IND_ASSOCIATION_SUCCESS,
    GSP_ISO_IND_ASSOCIATION_FAILED,
    GSP_ISO_IND_CLOSED,
    GSP_ISO_IND_DATA,
    GSP_ISO_IND_TICK
} GspIsoIndication;

typedef void* (*GspIsoIndicationCallback)(GspIsoIndication indication, void* param, GspByteBuffer* payload, uint16_t invokid);

/**
 * iso 链接
 */
typedef struct sGspIsoClientConnection* GspIsoClientConnection;

/**
 * @brief GspIsoClientConnection 创建iso链接
 * @param parameters 链接参数
 * @param callback 链接回调
 * @param callbackParameter 链接回调的参数
 * @return
 */
LIB860_INTERNAL GspIsoClientConnection GspIsoClientConnection_create(GspIsoConnectionParameters parameters,
                                                                     GspIsoIndicationCallback callback,
                                                                     void* callbackParameter);

/**
 * @brief GspIsoClientConnection_destroy 销毁iso链接并释放相关资源
 * @param self 链接回调
 */
LIB860_INTERNAL void GspIsoClientConnection_destroy(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_associateAsync 建立异步的iso链接
 * @param self 链接对象
 * @param connectTimeoutInMs 链接请求超时时间
 * @param readTimeoutInMs 链接读请求时的超时时间
 * @return 建立链接的结果
 */
LIB860_INTERNAL bool GspIsoClientConnection_associateAsync(GspIsoClientConnection self,
                                                           uint32_t connectTimeoutInMs,
                                                           uint32_t readTimeoutInMs,
														   const char* local_address = NULL);//zhouhj 20210929 增加客户端本地IP地址的绑定

/**
 * @brief GspIsoClientConnection_handleConnection 链接状态机处理函数
 * @param self 链接对象
 * @return 是否处于可调用状态
 */
LIB860_INTERNAL bool GspIsoClientConnection_handleConnection(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_sendMessage 把缓冲区里面的数据发送出去(底层调用gsp的发送)
 * @param self 链接信息
 * @param payload 负载数据
 */
LIB860_INTERNAL void GspIsoClientConnection_sendMessage(GspIsoClientConnection self, GspByteBuffer* payload);

/**
 * @brief GspIsoClientConnection_abortAsync 终止链接(服务端关闭，或者超时)
 * @param self 链接对象
 */
LIB860_INTERNAL void GspIsoClientConnection_abortAsync(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_close 链接关闭
 * @param self
 */
LIB860_INTERNAL void GspIsoClientConnection_close(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_allocateTransmitBuffer 获取一块发送缓冲区
 * 该缓冲区用来避免并发链接时发送缓冲区的冲突
 * @param self 链接对象
 * @return 发送缓存
 */
LIB860_INTERNAL GspByteBuffer* GspIsoClientConnection_allocateTransmitBuffer(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_releaseTransmitBuffer 释放传输缓存区
 * 避免数据被其他对象使用，同一时刻仅有一个对象使用
 * @param self
 */
LIB860_INTERNAL void GspIsoClientConnection_releaseTransmitBuffer(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_getGspRequestSc 获取请求头部的服务码
 * @param self 链接对象
 * @return 服务码
 */
LIB860_INTERNAL uint8_t GspIsoClientConnection_getGspRequestSc(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_getGspResponseSc 获取回应头部服务码
 * @param self 链接对象
 * @return 服务码
 */
LIB860_INTERNAL uint8_t GspIsoClientConnection_getGspResponseSc(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_getGspNext 获取头部的 next 位
 * @param self 链接对象
 * @return next 位
 */
LIB860_INTERNAL int GspIsoClientConnection_getGspNext(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_getGspResp 获取头部的 resp 位
 * @param self 链接对象
 * @return resp 位
 */
LIB860_INTERNAL int GspIsoClientConnection_getGspResp(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_getGspError 获取头部的 error 位
 * @param self 链接对象
 * @return error 位
 */
LIB860_INTERNAL int GspIsoClientConnection_getGspError(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_getGspInvokID 获取对方传递过来的 invokID
 * @param self 链接对象
 * @return invokID
 */
LIB860_INTERNAL uint16_t GspIsoClientConnection_getGspInvokID(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_getCallBackparam 获取mms链接
 *
 */
LIB860_INTERNAL void* GspIsoClientConnection_getCallBackparam(GspIsoClientConnection self);

/**
 * @brief GspIsoClientConnection_setCc 设置cc(8位)
 * @param self 链接对象
 * @param next next 位的值 (0--有下一帧， 1--没有下一帧)
 * @param resp resp 位的值 (0--请求， 1--回应)
 * @param error error 位的值 (0--没有错误，1--有错误)
 * @param pi 协议版本(占用4 bit的位段)
 */
LIB860_INTERNAL void GspIsoClientConnection_setCc(GspIsoClientConnection self,
                                                  uint8_t next,
                                                  uint8_t resp,
                                                  uint8_t error,
                                                  uint8_t pi);

/**
 * @brief GspIsoClientConnection_setResponseSc 设置回应的服务码
 * @param self 链接对象
 * @param paramSC 服务码
 */
LIB860_INTERNAL void GspIsoClientConnection_setResponseSc(GspIsoClientConnection self, uint8_t paramSC);

/**
 * @brief GspIsoClientConnection_setRequestSc 设置请求的服务码
 * @param self 链接对象
 * @param paramSC 服务码
 */
LIB860_INTERNAL void GspIsoClientConnection_setRequestSc(GspIsoClientConnection self, uint8_t paramSC);

#endif /* ISO_CLIENT_CONNECTION_H_ */
