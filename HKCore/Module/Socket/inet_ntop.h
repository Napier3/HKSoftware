
// inet_ntop.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

/*
* ������: inet_ntop.h
* ˵��: 
* ��Ҫ������ͷ�ļ�
*/


const char* xinet_ntop_v4 (const void *src, char *dst, size_t size);
#ifdef HAVE_IPV6
const char* xinet_ntop_v6 (const void *src, char *dst, size_t size);
#endif
const char* xinet_ntop(int af, const void *src, char *dst, size_t size);
