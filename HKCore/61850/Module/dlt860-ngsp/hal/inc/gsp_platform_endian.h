/*
 * gsp_platform_endian.h
 * 平台大小端判断
 */

#ifndef GSP_ENDIAN_H_
#define GSP_ENDIAN_H_

#ifndef PLATFORM_IS_BIGENDIAN
#ifdef __GNUC__
#ifdef __BYTE_ORDER__
#if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define PLATFORM_IS_BIGENDIAN 1
#endif

#else

/* older versions of GCC have __BYTE_ORDER__ not defined! */
#ifdef __PPC__
#define PLATFORM_IS_BIGENDIAN 1
#endif

#endif /* __BYTE_ORDER__ */
#endif /* __GNUC__ */
#endif

#if (PLATFORM_IS_BIGENDIAN == 1)
#  define ORDER_LITTLE_ENDIAN 0
#else
#  define ORDER_LITTLE_ENDIAN 1
#endif

#endif /* GSP_ENDIAN_H_ */
