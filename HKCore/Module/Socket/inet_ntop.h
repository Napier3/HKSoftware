
// inet_ntop.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

/*
* 程序名: inet_ntop.h
* 说明: 
* 主要函数库头文件
*/


const char* xinet_ntop_v4 (const void *src, char *dst, size_t size);
#ifdef HAVE_IPV6
const char* xinet_ntop_v6 (const void *src, char *dst, size_t size);
#endif
const char* xinet_ntop(int af, const void *src, char *dst, size_t size);
