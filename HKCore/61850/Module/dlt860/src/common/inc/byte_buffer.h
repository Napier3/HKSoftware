/*
 *  byte_buffer.h
 *  字节缓存封装
 */

#ifndef GSP_BYTE_BUFFER_H_
#define GSP_BYTE_BUFFER_H_

#include "libdlt860_common_api.h"

// 字节缓存
typedef struct {
    // 缓存内容
    uint8_t* buffer;
    // 该缓存的大小
    int maxSize;
    // 其中有用数据的大小
    int size;
} GspByteBuffer;

/**
 * @brief ByteBuffer_create 创建一块字节缓存
 * @param self 字节缓存指针
 * @param maxSize 该字节缓存的大小
 * @return
 */
LIB860_INTERNAL GspByteBuffer* GspByteBuffer_create(GspByteBuffer* self, int maxSize);

/**
 * @brief ByteBuffer_destroy 销毁字节缓存
 * @param self 字节缓存指针
 */
LIB860_INTERNAL void GspByteBuffer_destroy(GspByteBuffer* self);

/**
 * @brief ByteBuffer_wrap 字节缓存覆盖
 * @param self 字节缓存指针
 * @param buf 待覆盖的数据
 * @param size 数据尺寸
 * @param maxSize 缓存尺寸
 */
LIB860_INTERNAL void GspByteBuffer_wrap(GspByteBuffer* self, uint8_t* buf, int size, int maxSize);

/**
 * @brief ByteBuffer_append 在当前字节缓存中增加一块缓存数据
 * @param self 字节缓存
 * @param data 待增加的数据
 * @param dataSize 待增加的数据尺寸
 * @return 增加后的数据尺寸, 错误时返回-1
 */
LIB860_INTERNAL int GspByteBuffer_append(GspByteBuffer* self, uint8_t* data, int dataSize);

/**
 * @brief ByteBuffer_appendByte 在当前字节缓存中增加一字节数据
 * @param self 字节缓存
 * @param byte 带增加的一字节数据
 * @return 成功 1 失败 0
 */
LIB860_INTERNAL int GspByteBuffer_appendByte(GspByteBuffer* self, uint8_t byte);

/**
 * @brief ByteBuffer_getBuffer 获取字节缓存中的数据
 * @param self 字节缓存
 * @return
 */
LIB860_INTERNAL uint8_t* GspByteBuffer_getBuffer(GspByteBuffer* self);

/**
 * @brief ByteBuffer_getSize 获取字节缓存中的数据的尺寸
 * @param self 字节缓存
 * @return
 */
LIB860_INTERNAL int GspByteBuffer_getSize(GspByteBuffer* self);

/**
 * @brief ByteBuffer_getMaxSize 获取字节缓存的尺寸
 * @param self 字节缓存
 * @return
 */
LIB860_INTERNAL int GspByteBuffer_getMaxSize(GspByteBuffer* self);

/**
 * @brief ByteBuffer_setSize 设置字节缓存中数据的尺寸
 * @param self 字节缓存
 * @param size 数据的尺寸
 * @return
 */
LIB860_INTERNAL int GspByteBuffer_setSize(GspByteBuffer* self, int size);

/**
 * @brief ByteBuffer_print 打印字节缓存的内容
 * @param self 字节缓存
 * @param message 原始内容
 */
LIB860_INTERNAL void GspByteBuffer_print(GspByteBuffer* self, char* message);

#endif /* GSP_BYTE_BUFFER_H_ */
