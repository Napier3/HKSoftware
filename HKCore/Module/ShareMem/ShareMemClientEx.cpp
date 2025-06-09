// ShareMemClientEx.cpp: implementation of the CSFMServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShareMemClientEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShareMemClientEx::~CShareMemClientEx()
{
	_Destory();
}

CShareMemClientEx::CShareMemClientEx(DWORD dwAccess, const CString &szMapName)
{
	m_strMapName= _T("");
	_Init();

	Open(dwAccess, szMapName);
}

void CShareMemClientEx::Open(DWORD dwAccess, const CString &szMapName)
{
	if (m_bOpen)
		_Destory();

// 	ASSERT (szMapName != NULL);
// 	if (szMapName == NULL)
// 	{
// 		return;
// 	}

	m_dwAccess = dwAccess;

	m_strMapName = szMapName;

	m_hFileMap = OpenFileMapping(
		dwAccess,
		TRUE,
		m_strMapName
		);

	m_bOpen = TRUE;
}

void CShareMemClientEx::_Init()
{
	m_hFileMap = NULL;
	m_pchData = NULL;
	m_dwSize    = 0;
	m_bOpen = 0;
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
	m_dwAccess = FILE_MAP_READ|FILE_MAP_WRITE;
}

void CShareMemClientEx::_Destory()
{
	if (m_pchData)
	{
		UnmapViewOfFile(m_pchData);
		m_pchData = NULL;
	}
	
	if (m_hFileMap)
	{
		CloseHandle(m_hFileMap);
		m_hFileMap = NULL;
	}

	_Init();
}

BOOL CShareMemClientEx::ReOpen()
{
	if (m_bOpen)
		_Destory();
	
	m_hFileMap = OpenFileMapping(
		m_dwAccess,
		TRUE,
		m_strMapName
		);
	
	m_bOpen = (m_hFileMap != NULL);
	return m_bOpen;
}

void CShareMemClientEx::Close()
{
	if (m_pchData)
	{
		UnmapViewOfFile(m_pchData);
		m_pchData = NULL;
	}
	
	if (m_hFileMap)
	{
		CloseHandle(m_hFileMap);
		m_hFileMap = NULL;
	}
	
	_Init();
}

void CShareMemClientEx::UnMapView()
{
	if (m_pchData)
	{
		UnmapViewOfFile(m_pchData);
		m_pchData = NULL;
		m_lpBufCur = NULL;
		m_lpBufMax = NULL;
//		m_dwSize = 0;
	}
}

LPVOID CShareMemClientEx::MapView(DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow,DWORD dwNumberOfBytesToMap)
{
	UnMapView();
	m_n64MapBeginPos = dwFileOffsetHigh;
	m_n64MapBeginPos = m_n64MapBeginPos << 32;
	m_n64MapBeginPos += dwFileOffsetLow;

	m_dwSize = dwNumberOfBytesToMap;
	ASSERT (m_hFileMap != NULL);
	
	if (m_hFileMap)
	{
		m_pchData = (char*)MapViewOfFile(
			m_hFileMap,
			FILE_MAP_ALL_ACCESS,
			dwFileOffsetHigh,
			dwFileOffsetLow,
			m_dwSize
			);

// #ifdef _DEBUG_ONLINE_TEST
// 		int n = GetLastError();
// 		if (n > 0)
// 		{
// 			LPVOID lpMsgBuf;
// 			FormatMessage(
// 				FORMAT_MESSAGE_ALLOCATE_BUFFER |
// 				FORMAT_MESSAGE_FROM_SYSTEM |
// 				FORMAT_MESSAGE_IGNORE_INSERTS,
// 				NULL,
// 				GetLastError(),
// 				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
// 				(LPTSTR) &lpMsgBuf,
// 				0,
// 				NULL
// 				);
// 			
// 			// Display the string.
// 			AfxMessageBox((LPCTSTR)lpMsgBuf);
// 			
// 			// Free the buffer.
// 			LocalFree( lpMsgBuf );
// 		}
// #endif
		DWORD dwError = 0;

		if (m_pchData == NULL)
		{
			dwError = GetLastError();
		}

		m_lpBufCur = m_pchData;
		m_lpBufMax = m_pchData + m_dwSize;
	}
	else
	{
		m_pchData = NULL;
		m_lpBufCur = NULL;
		m_lpBufMax = NULL;
	}
	
	return m_pchData;
}

LPVOID CShareMemClientEx::MapView(volatile __int64 n64Offset,DWORD dwNumberOfBytesToMap)
{
	DWORD dwFileOffsetHigh = 0;
	DWORD dwFileOffsetLow = 0;
	
	dwFileOffsetLow = (DWORD)(n64Offset & 0xFFFFFFFF);
	n64Offset = n64Offset >> 32;
	dwFileOffsetHigh = (DWORD)(n64Offset & 0xFFFFFFFF);
	
	return MapView(dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap);
}

LPVOID CShareMemClientEx::LocatePos(DWORD dwOffSet)
{
// 	ASSERT(m_pchData != NULL);

	if (m_pchData == NULL)
	{
		return NULL;
	}

	if (m_pchData + dwOffSet <= m_lpBufMax) 
	{
		m_lpBufCur = m_pchData + dwOffSet;
	}

	return m_lpBufCur;
}

volatile __int64 CShareMemClientEx::GetCurr64Pos()
{
	volatile __int64 n64Pos = m_lpBufCur - m_pchData;
	n64Pos += m_n64MapBeginPos;
	return n64Pos;
}

volatile __int64 CShareMemClientEx::SetCurr64Pos(volatile __int64 n64Pos)
{
	DWORD dwOffset = (DWORD)(n64Pos - m_n64MapBeginPos);
	m_lpBufCur = m_pchData + dwOffset;
	return n64Pos;
}

LPVOID CShareMemClientEx::Read(__int64 n64BeginPos, DWORD dwLength)
{
	__int64 n64EndPos = m_n64MapBeginPos + m_dwSize;
	__int64 n64ReadEnd = n64BeginPos + dwLength;

	if ( (m_n64MapBeginPos <= n64BeginPos && n64BeginPos <= n64EndPos)
		&& (m_n64MapBeginPos <= n64ReadEnd && n64ReadEnd <= n64EndPos) )
	{
		__int64 n64Offset = n64BeginPos - m_n64MapBeginPos;

		return LocatePos((DWORD)n64Offset);
	}
	else
	{
		return NULL;
	}
}

