/*
 *  simple_allocator.h
 *  内存操作封装(字节为单位)
 */

#ifndef GSP_SIMPLE_ALLOCATOR_H_
#define GSP_SIMPLE_ALLOCATOR_H_

#include "libdlt860_common_api.h"

// 内存块结构
typedef struct {
    char* memoryBlock;
    char* currentPtr;
    int size;
} GspMemoryAllocator;

/**
 * @brief GspMemoryAllocator_init 内存块初始化
 * @param self 内存快对象
 * @param memoryBlock 内存块地址(传入)
 * @param size 内存块尺寸(传入)
 */
LIB860_INTERNAL void GspMemoryAllocator_init(GspMemoryAllocator* self, char* memoryBlock, int size);

/**
 * @brief GspMemoryAllocator_getAlignedSize 获取字节对齐后的尺寸
 * @param size 尺寸
 * @return
 */
LIB860_INTERNAL int GspMemoryAllocator_getAlignedSize(int size);

/**
 * @brief GspMemoryAllocator_allocate 获取指定尺寸的内存
 * @param self 内存块对象
 * @param size 需要申请的内存大小
 * @return
 */
LIB860_INTERNAL char* GspMemoryAllocator_allocate(GspMemoryAllocator* self, int size);

#endif /* GSP_SIMPLE_ALLOCATOR_H_ */
