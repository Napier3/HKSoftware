/*
 *  lib_memory.c
 *  内存操作封装
 */

#include <stdlib.h>
#include "gsp_lib_memory.h"

#ifdef NOT_USE_IN_C11
#ifndef nullptr
#define nullptr NULL
#endif
#endif

// 内存异常处理函数
static GspMemoryExceptionHandler exceptionHandler = nullptr;

// 内存异常处理参数
static void* exceptionHandlerParameter = nullptr;

// 内存不足处理处理
static void noMemoryAvailableHandler(void)
{
    if (exceptionHandler != nullptr)
        exceptionHandler(exceptionHandlerParameter);
}

// 安装内存处理函数
void GspMemory_installExceptionHandler(GspMemoryExceptionHandler handler, void* parameter)
{
    exceptionHandler = handler;
    exceptionHandlerParameter = parameter;
}

// 获取内存(不对内存进行初始化)
void* GspMemory_malloc(size_t size)
{
    void* memory = malloc(size);
    if (memory == nullptr)
        noMemoryAvailableHandler();
    return memory;
}


// 获取内存(默认初始化为0)
void* GspMemory_calloc(size_t nmemb, size_t size)
{
    void* memory = calloc(nmemb, size);

    if (memory == nullptr)
        noMemoryAvailableHandler();

    return memory;
}

// 修改内存尺寸
void* GspMemory_realloc(void *ptr, size_t size)
{
    void* memory = realloc(ptr, size);

    if (memory == nullptr)
        noMemoryAvailableHandler();

    return memory;
}

// 释放内存
void GspMemory_free(void* memb)
{
    free(memb);
    memb = nullptr;
}

