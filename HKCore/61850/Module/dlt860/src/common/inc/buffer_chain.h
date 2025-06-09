/*
 *  buffer_chain.h
 *  内存链表
 */

#ifndef GSP_BUFFER_CHAIN_H_
#define GSP_BUFFER_CHAIN_H_

#include "libdlt860_platform_includes.h"

// 内存块节点信息
typedef struct sBufferChain* BufferChain;
struct sBufferChain {
    int length;
    int partLength;
    int partMaxLength;
    uint8_t* buffer;
    BufferChain nextPart;
};

/**
 * @brief BufferChain_init 初始化内存链表
 * @param self 内存链表
 * @param length 内存总长度
 * @param partLength 本区块长度
 * @param nextPart 下一个区块地址
 * @param buffer 本区块的内容
 */
LIB860_INTERNAL void BufferChain_init(BufferChain self, int length, int partLength, BufferChain nextPart, uint8_t* buffer);

// 内存区域
typedef struct {
    uint8_t* memory;
    int currentPos;
    int size;
} MemoryArea;

/**
 * @brief MemoryArea_initialize 初始化内存域
 * @param self 内存域
 * @param memory 内存指针
 * @param size 内存大小
 */
LIB860_INTERNAL void MemoryArea_initialize(MemoryArea* self, uint8_t* memory, int size);

/**
 * @brief MemoryArea_getNextBlock 获取内存域中可用的下一块内存信息
 * @param self 内存域
 * @param size 大小尺寸
 * @return
 */
LIB860_INTERNAL uint8_t* MemoryArea_getNextBlock(MemoryArea* self, int size);

#if 0

typedef struct sMemoryPool* MemoryPool;

typedef struct sMemoryChunk MemoryChunk;

struct sMemoryPool {
    uint8_t* memory;
    int size;
    MemoryChunk firstChunk;
};

struct sMemoryChunk {
    MemoryChunk previous;
    MemoryChunk next;
    uint8_t* data;
    uint8_t free;
    int size;
};

MemoryPool MemoryPool_create(uint8_t* memoryAddress, int size);

void MemoryPool_destroy(MemoryPool self);

MemoryChunk MemoryPool_allocateChunk(MemoryPool self, int size);

MemoryPool_freeChunk(MemoryPool self, MemoryChunk chunk);

#endif

#endif /* GSP_BUFFER_CHAIN_H_ */
