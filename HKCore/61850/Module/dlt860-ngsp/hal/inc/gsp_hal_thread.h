/*
 *  thread_hal.h
 *  线程封装
 */

#ifndef GSP_THREAD_HAL_H_
#define GSP_THREAD_HAL_H_

#include "gsp_hal_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 线程操作指针 */
typedef struct sThread* GspThread;

/** 信号量操作指针 */
typedef void* GspSemaphore;

/** 线程执行时的任务处理回调 */
typedef void* (*GspThreadExecutionFunction) (void*);

/**
 * \brief 创建线程
 *
 * \param 创建一个线程并赋予任务处理回调
 * \param parameter 线程 run 时的函数的参数数据
 * \param autodestroy 当线程任务函数处理完成时,自动销毁线程资源
 *
 * \return 创建的线程
 */
PAL_API GspThread GspThread_create(GspThreadExecutionFunction function, void* parameter, bool autodestroy);

/**
 * \brief 开启线程
 * 线程启动,线程启动时,会调用任务处理函数,任务处理函数执行完毕后,该函数就会停止
 *
 * \param thread 需要启动的线程指针
 */
PAL_API void GspThread_start(GspThread thread);

/**
 * \brief 销毁线程及其多有资源
 *
 * \param thread 需要销毁的线程指针
 */
PAL_API void GspThread_destroy(GspThread thread);

/**
 * \brief 挂起执行中的线程指定的毫秒数
 */
PAL_API void GspThread_sleep(int millies);

/**
 * \brief Semaphore_create 创建信号量
 */
PAL_API GspSemaphore GspSemaphore_create(int initialValue);

/**
 * 等待信号量大于零, 执行过去, 然后对其减去1,
 */
PAL_API void GspSemaphore_wait(GspSemaphore self);

/**
 * \brief Semaphore_post 信号两加1
 */
PAL_API void GspSemaphore_post(GspSemaphore self);

/**
 * \brief Semaphore_destroy 销毁信号量
 * \param self
 */
PAL_API void GspSemaphore_destroy(GspSemaphore self);


#ifdef __cplusplus
}
#endif


#endif /* GSP_THREAD_HAL_H_ */
