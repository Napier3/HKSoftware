#ifndef _XGlobalDataTypes_QT_h__
#define _XGlobalDataTypes_QT_h__

#ifdef _PSX_IDE_QT_

//////////////////////////////////////////////////////////////////////////
//_PSX_IDE_QT_
#define ASSERT(X)
#define TRACE(X)

#ifndef _T
#define _T(X)    (X)
#endif

#ifndef DEBUG_NEW
#define DEBUG_NEW new
#endif

//和系统相关的
//_PSX_QT_LINUX_ + _PSX_IDE_QT_
#ifdef _PSX_QT_LINUX_

#define PASCAL      __stdcall

#define BSTR   wchar_t*
#define LPCSTR   wchar_t*
#define INT int
#define UINT   unsigned int
#define UINT16   unsigned short
#define LONG   long
#define COLORREF  unsigned long
#define BYTE  unsigned char
#define WORD  unsigned short
#define DWORD unsigned long
#define LPARAM unsigned long
#define WPARAM unsigned long
#define CHAR   char
#define LPVOID  void*
#define LPCTSTR CString
#define LPSTR CString
#define LRESULT unsigned long
#define WCHAR wchar_t
#define SHORT short
#define ULONG unsigned long
#define FLOAT float
#define DOUBLE double
#define USHORT unsigned short

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

//#endif

#define _bstr_t   (wchar_t*)
#define BOOL   bool
#define FALSE  false
#define TRUE   true

#define TCHAR wchar_t
#define DWORD_PTR unsigned long
#define MAX_PATH  256

typedef void* HANDLE;

#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))

#define GetRValue(rgb)      (LOBYTE(rgb))
#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)      (LOBYTE((rgb)>>16))

/* Pen Styles */
#define PS_SOLID            0
#define PS_DASH             1       /* -------  */
#define PS_DOT              2       /* .......  */
#define PS_DASHDOT          3       /* _._._._  */
#define PS_DASHDOTDOT       4       /* _.._.._  */
#define PS_NULL             5
#define PS_INSIDEFRAME      6
#define PS_USERSTYLE        7
#define PS_ALTERNATE        8
#define PS_STYLE_MASK       0x0000000F

/* Brush Styles */
#define BS_SOLID            0
#define BS_NULL             1
#define BS_HOLLOW           BS_NULL
#define BS_HATCHED          2
#define BS_PATTERN          3
#define BS_INDEXED          4
#define BS_DIBPATTERN       5
#define BS_DIBPATTERNPT     6
#define BS_PATTERN8X8       7
#define BS_DIBPATTERN8X8    8
#define BS_MONOPATTERN      9

/* Stock Logical Objects */
#define WHITE_BRUSH         0
#define LTGRAY_BRUSH        1
#define GRAY_BRUSH          2
#define DKGRAY_BRUSH        3
#define BLACK_BRUSH         4
#define NULL_BRUSH          5
#define HOLLOW_BRUSH        NULL_BRUSH
#define WHITE_PEN           6
#define BLACK_PEN           7
#define NULL_PEN            8
#define OEM_FIXED_FONT      10
#define ANSI_FIXED_FONT     11
#define ANSI_VAR_FONT       12
#define SYSTEM_FONT         13
#define DEVICE_DEFAULT_FONT 14
#define DEFAULT_PALETTE     15
#define SYSTEM_FIXED_FONT   16

/*
 * DrawText() Format Flags
 */
#define DT_TOP                      0x00000000
#define DT_LEFT                     0x00000000
#define DT_CENTER                   0x00000001
#define DT_RIGHT                    0x00000002
#define DT_VCENTER                  0x00000004
#define DT_BOTTOM                   0x00000008
#define DT_WORDBREAK                0x00000010
#define DT_SINGLELINE               0x00000020
#define DT_EXPANDTABS               0x00000040
#define DT_TABSTOP                  0x00000080
#define DT_NOCLIP                   0x00000100
#define DT_EXTERNALLEADING          0x00000200
#define DT_CALCRECT                 0x00000400
#define DT_NOPREFIX                 0x00000800
#define DT_INTERNAL                 0x00001000

/* Background Modes */
#define TRANSPARENT         1
#define OPAQUE              2
#define BKMODE_LAST         2

#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2

#define LVS_EX_GRIDLINES        0x00000001
#define LVS_EX_SUBITEMIMAGES    0x00000002
#define LVS_EX_CHECKBOXES       0x00000004
#define LVS_EX_TRACKSELECT      0x00000008
#define LVS_EX_HEADERDRAGDROP   0x00000010
#define LVS_EX_FULLROWSELECT    0x00000020 // applies to report mode only
#define LVS_EX_ONECLICKACTIVATE 0x00000040
#define LVS_EX_TWOCLICKACTIVATE 0x00000080

/* Ternary raster operations */
#define SRCCOPY             (DWORD)0x00CC0020 /* dest = source                   */
#define SRCPAINT            (DWORD)0x00EE0086 /* dest = source OR dest           */
#define SRCAND              (DWORD)0x008800C6 /* dest = source AND dest          */
#define SRCINVERT           (DWORD)0x00660046 /* dest = source XOR dest          */
#define SRCERASE            (DWORD)0x00440328 /* dest = source AND (NOT dest )   */
#define NOTSRCCOPY          (DWORD)0x00330008 /* dest = (NOT source)             */
#define NOTSRCERASE         (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
#define MERGECOPY           (DWORD)0x00C000CA /* dest = (source AND pattern)     */
#define MERGEPAINT          (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     */
#define PATCOPY             (DWORD)0x00F00021 /* dest = pattern                  */
#define PATPAINT            (DWORD)0x00FB0A09 /* dest = DPSnoo                   */
#define PATINVERT           (DWORD)0x005A0049 /* dest = pattern XOR dest         */
#define DSTINVERT           (DWORD)0x00550009 /* dest = (NOT dest)               */
#define BLACKNESS           (DWORD)0x00000042 /* dest = BLACK                    */
#define WHITENESS           (DWORD)0x00FF0062 /* dest = WHITE                    */

/* Binary raster ops */
#define R2_BLACK            1   /*  0       */
#define R2_NOTMERGEPEN      2   /* DPon     */
#define R2_MASKNOTPEN       3   /* DPna     */
#define R2_NOTCOPYPEN       4   /* PN       */
#define R2_MASKPENNOT       5   /* PDna     */
#define R2_NOT              6   /* Dn       */
#define R2_XORPEN           7   /* DPx      */
#define R2_NOTMASKPEN       8   /* DPan     */
#define R2_MASKPEN          9   /* DPa      */
#define R2_NOTXORPEN        10  /* DPxn     */
#define R2_NOP              11  /* D        */
#define R2_MERGENOTPEN      12  /* DPno     */
#define R2_COPYPEN          13  /* P        */
#define R2_MERGEPENNOT      14  /* PDno     */
#define R2_MERGEPEN         15  /* DPo      */
#define R2_WHITE            16  /*  1       */
#define R2_LAST             16

#define __int64 qint64
#define __time64_t qint64
#define __uint64 quint64

#define VK_TAB Qt::Key_Tab
#define VK_SPACE Qt::Key_Space


#define SOCKET_ERROR   (-1)
#define INVALID_HANDLE_VALUE  (-1)
#define HWND unsigned long


//2020-5-7  lijq
#define DECLARE_DYNCREATE(x)   ()
#define DECLARE_MESSAGE_MAP
#define afx_msg
#define AFX_MSG_CALL
#define RUNTIME_CLASS(X)   (new X)


#define THREAD_PRIORITY_HIGHEST 0
#define CREATE_SUSPENDED 0

#define WM_QUIT    0X0012
#define WM_CLOSE 0X0010
#define WM_TIMER  0X0113

#define WM_USER  0X0400


#define FILETIME time_t

//2020-08-27 lijunqing
#define HCURSOR unsigned long

#define CALLBACK

//_PSX_QT_LINUX_  + _PSX_IDE_QT_
//////////////////////////////////////////////////////////////////////////
#else   ///////////////////////////////////////////////////////////_PSX_IDE_QT_
//////////////////////////////////////////////////////////////////////////
//Windows  + QT
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <wtypes.h>
#include <WinSock2.h>  //zhouhj 20210914 增加用于window下Qt程序使用组播功能
#include <ws2ipdef.h>

//#define WIN32_LEAN_AND_MEAN
//#include "wtypes.h"

//Windows
//////////////////////////////////////////////////////////////////////////
#endif  /////_PSX_QT_LINUX_

#endif /////_PSX_IDE_QT_

#endif   //_XGlobalDataTypes_QT_h__
