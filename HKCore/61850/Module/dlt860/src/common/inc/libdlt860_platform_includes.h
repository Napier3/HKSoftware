/*
 * libdlt860_platform_includes.h
 */

#ifndef GSP_LIBDLT860_PLATFORM_INCLUDES_H_
#define GSP_LIBDLT860_PLATFORM_INCLUDES_H_

#include "stack_config.h"
#include "libdlt860_common_api.h"
#include "string_utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "gsp_platform_endian.h"
#include <assert.h>
#include "gsp_lib_memory.h"

#ifdef NOT_USE_IN_C11
#define LIBDLT860_VERSION "1.0.36"
#else
#define LIBDLT860_VERSION LIB_VERSION
#endif

#ifndef CONFIG_DEFAULT_MMS_VENDOR_NAME
#define CONFIG_DEFAULT_MMS_VENDOR_NAME "sduept.com"
#endif

#ifndef CONFIG_DEFAULT_MMS_MODEL_NAME
#define CONFIG_DEFAULT_MMS_MODEL_NAME "LIBDLT860"
#endif

#ifndef CONFIG_DEFAULT_MMS_REVISION
#define CONFIG_DEFAULT_MMS_REVISION LIBDLT860_VERSION
#endif

#ifndef CONFIG_DLT860_SAMPLED_VALUES_SUPPORT
#define CONFIG_DLT860_SAMPLED_VALUES_SUPPORT 0
#endif

#if (DEBUG != 1)
#define NDEBUG 1
#endif

extern void Global_LogString( const char *strFormat, ...);//zhouhj 20220107 增加用于打印日志信息
extern int  g_nLogGspDebugString;

#endif /* GSP_LIBDLT860_PLATFORM_INCLUDES_H_ */
