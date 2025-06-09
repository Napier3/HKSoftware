#ifndef _XGlobalDefine_QT_h__
#define _XGlobalDefine_QT_h__

#include "XGlobalDataTypes_QT.h"



void ThrowInvalidArgException();

//QT+LINUX 需要的全局函数
#ifdef _PSX_QT_LINUX_

inline int MulDiv(int nNumber,int nNumerator,int nDenominator)
{
    long long nRet = nNumber * nNumerator;
    nRet /= nDenominator;
    return (int)nRet;
}


#include "CWinThread_QT.h"
class CWnd;
bool IsWindow(CWnd* hWnd);
CWinThread* AfxBeginThread(CWinThread *pThread, unsigned int nPRIORITY, unsigned int nParam=0, unsigned int nCREATE=0);
CWinThread* AfxBeginThread(WIN_THREAD_PROC *pfnThreadProc, LPVOID pData);

template<class _Ty>
inline _Ty _Pow_int(_Ty _X, int _Y)
{
    unsigned int _N;
    if (_Y >= 0)
        _N = (unsigned int)_Y;
    else
        _N = (unsigned int)(-_Y);

    for (_Ty _Z = _Ty(1); ; _X *= _X)
    {
        if ((_N & 1) != 0)
            _Z *= _X;
        if ((_N >>= 1) == 0)
            return (_Y < 0 ? _Ty(1) / _Z : _Z);
    }
}


#ifdef __cplusplus
extern "C" {
#endif

char* itoa(int val, char* buf, unsigned int radix=10);

long GetTickCount();
void Sleep(long nmSecond);

#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#define CopyMemory(Destination,Source,Length) memcpy((Destination),(Source),(Length))
#define stricmp strcasecmp
#define _stricmp stricmp

#define wcsicmp wcscasecmp

//2020-6-1  lijunqing
#define strtok_s strtok_r


bool IsWindow(HWND hWnd);
unsigned long PostMessage(HWND hWnd, unsigned long nMsg, unsigned long wPara, unsigned long lPara);
unsigned long PostThreadMessage(unsigned long hThreadID, unsigned long nMsg, unsigned long wPara, unsigned long lPara);

#ifdef __cplusplus
}
#endif


#endif //#ifndef _PSX_QT_LINUX_

#ifdef _PSX_QT_USE_MIN_MAX_
template <typename T>//typename == class
inline T max(T a,T b)
{
    return a>b?a:b;
}
template <typename T>//typename == class
inline T min(T a,T b)
{
    return a<b?a:b;
}
#endif

#ifdef _PSX_QT_LINUX_
using namespace std;
#endif

#endif   //_XGlobalDefine_QT_h__
