/*
 *  time.c
 *  时间封装
 */

#ifndef GSP_HAL_C_TIME_
#define GSP_HAL_C_TIME_

#include "gsp_hal_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取距离纪元时间的毫秒数
 * @return 毫秒数
 */
PAL_API uint64_t GSP_Hal_getTimeInMs();

#ifdef __cplusplus
}
#endif


#endif /* GSP_HAL_C_TIME_ */
