#ifndef GSP_LIBDLT860_DEFINE
#define GSP_LIBDLT860_DEFINE

#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef NOT_USE_IN_C11
#ifndef nullptr
#define nullptr NULL
#endif
#endif

#ifdef _MSC_VER 
//not #if defined(_WIN32) || defined(_WIN64) because we have strncasecmp in mingw
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

#ifdef __GNUC__
#define ATTRIBUTE_PACKED __attribute__ ((__packed__))
#else
#define ATTRIBUTE_PACKED
#endif

#ifndef DEPRECATED
#if defined(__GNUC__) || defined(__clang__)
  #define DEPRECATED __attribute__((deprecated))
#else
  #define DEPRECATED
#endif
#endif

#if defined _WIN32 || defined __CYGWIN__
    #ifdef EXPORT_FUNCTIONS_FOR_DLL
        #define LIB860_API __declspec(dllexport)
    #else
        #define LIB860_API
    #endif

    #define LIB860_INTERNAL
#else
    #if __GNUC__ >= 4
        #define LIB860_API __attribute__ ((visibility ("default")))
        #define LIB860_INTERNAL  __attribute__ ((visibility ("default")))
    #else
        #define LIB860_API
        #define LIB860_INTERNAL
    #endif
#endif

#endif
