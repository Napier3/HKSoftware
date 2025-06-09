
// XPing.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "SocketGlobal.h"

#ifndef _PSX_QT_LINUX_
#include < winsock2.h > 
#include < ws2tcpip.h >
#include <iphlpapi.h>
#pragma comment(lib,"iphlpapi.lib")
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString dwIP2csIP(DWORD dwIP)
{
	CString strIP = _T("");
	WORD add1,add2,add3,add4;

	add1=(WORD)(dwIP&255);
	add2=(WORD)((dwIP>>8)&255);
	add3=(WORD)((dwIP>>16)&255);
	add4=(WORD)((dwIP>>24)&255);
	strIP.Format(_T("%d.%d.%d.%d"),add4,add3,add2,add1);

	return strIP;	
}

DWORD csIP2dwIP(char *strIP)
{
	DWORD dwIP = 0;
	BYTE nVal = 0;
	long nIndex = 0;
	char *pString = strIP;

	while(*pString != 0)
	{
		if (*pString == '.')
		{
			dwIP |= (nVal << ((3-nIndex)*8));
			nVal = 0;
			nIndex++;

			if(nIndex > 3)
			{
				break;
			}
		}
		else
		{
			nVal = 10 * nVal;
			nVal += *pString - '0';
		}

		pString++;
	}

	if (nIndex == 3)
	{
		dwIP |= nVal;
	}

	return dwIP;
}

DWORD csIP2dwIP(wchar_t *strIP)
{
	DWORD dwIP = 0;
	BYTE nVal = 0;
	long nIndex = 0;
	wchar_t *pString = strIP;

	while(*pString != 0)
	{
		if (*pString == '.')
		{
			dwIP |= (nVal << ((3-nIndex)*8));
			nVal = 0;
			nIndex++;

			if(nIndex > 3)
			{
				break;
			}
		}
		else
		{
			nVal = 10 * nVal;
			nVal += *pString - '0';
		}

		pString++;
	}

	if (nIndex == 3)
	{
		dwIP |= nVal;
	}

	return dwIP;
}

DWORD csIP2dwIP(const CString &strIP)
{
#ifdef _UNICODE
	wchar_t *pszIP = (wchar_t *)strIP.GetString();
	return csIP2dwIP(pszIP);
#else
	char *pszIP = (char *)strIP.GetString();
	return csIP2dwIP(pszIP);
#endif
}
