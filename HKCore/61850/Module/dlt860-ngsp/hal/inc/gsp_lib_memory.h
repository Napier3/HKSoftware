/*
 * gsp_lib_memory.h
 * 内存操作封装
 */

#ifndef GSP_MEMORY_H_
#define GSP_MEMORY_H_

#include "gsp_hal_base.h"

// 获取初始化的内存
#define GLOBAL_CALLOC(nmemb, size) GspMemory_calloc(nmemb, size)

// 获取内存
#define GLOBAL_MALLOC(size)        GspMemory_malloc(size)

// 扩展内存
#define GLOBAL_REALLOC(oldptr, size)   GspMemory_realloc(oldptr, size)

// 释放内存
#define GLOBAL_FREEMEM(ptr)        GspMemory_free(ptr)

#ifdef __cplusplus
extern "C" {
#endif

// 内存异常处理函数
typedef void (*GspMemoryExceptionHandler) (void* parameter);

// 内存异常处理安装处理
PAL_API void GspMemory_installExceptionHandler(GspMemoryExceptionHandler handler, void* parameter);

// 获取内存(不对内存进行初始化)
PAL_API void* GspMemory_malloc(size_t size);

// 获取内存(默认初始化为0)
PAL_API void* GspMemory_calloc(size_t nmemb, size_t size);

// 修改内存尺寸
PAL_API void * GspMemory_realloc(void *ptr, size_t size);

// 释放内存
PAL_API void GspMemory_free(void* memb);

#ifdef __cplusplus
}
#endif

extern void Global_LogString( const char *strFormat, ...);//zhouhj 20220107 增加用于打印日志信息

#endif /* GSP_MEMORY_H_ */
