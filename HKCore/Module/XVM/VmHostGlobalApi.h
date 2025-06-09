#ifndef _VmHostGlobalApi_H__
#define _VmHostGlobalApi_H__


#include <stddef.h>
#include <stdio.h>


#define XVM_BUFFERSIZE		BUFSIZ

#define bufflen(B)	((B)->p - (B)->buffer)
#define bufffree(B)	((size_t)(XVM_BUFFERSIZE - bufflen(B)))

typedef struct xvm_Buffer 
{
	char *p;			/* current position in buffer */
	int lvl;  /* number of strings in the stack (level) */
	LPVOID pXvm;
	char buffer[XVM_BUFFERSIZE];
	char *pEnd;
} xvm_Buffer;


#if defined(XVM_USELONGLONG)

#define XVM_INTFRMLEN		"ll"
#define XVM_INTFRM_T		long long

#else

#define XVM_INTFRMLEN		"l"
#define XVM_INTFRM_T		long

#endif

#define XVM_L_ESC		'%'
#define XVM_SPECIALS	"^$*+?.([%-"

void xvm_str_format (LPVOID pXvm) ;
void xvm_logprint (LPVOID pXvm) ;
void xvm_tostring (LPVOID pXvm) ;
void xvm_strlength (LPVOID pXvm) ;
void xvm_str_to_utf8 (LPVOID pXvm) ; //2022-1-7

//2022-1-7  lijunqing
void xvm_str_to_utf8 (LPVOID pXvm) ;
// void xvm_abs (LPVOID pXvm) ;

#endif


