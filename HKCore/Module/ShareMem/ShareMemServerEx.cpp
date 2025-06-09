// ShareMemServerEx.cpp: implementation of the CShareMemServerEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShareMemServerEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShareMemServerEx::~CShareMemServerEx()
{
	_Destory();
}

CShareMemServerEx::CShareMemServerEx()
{
	_Init();
}

CShareMemServerEx::CShareMemServerEx(const CString &szFileName, const CString &szMapName, DWORD dwSizeHigh, DWORD dwSizeLow)
{
	_Init();
	CreateShareMem(szFileName, szMapName, dwSizeHigh, dwSizeLow);
}

CShareMemServerEx::CShareMemServerEx(const CString &szFileName, const CString &szMapName, volatile __int64 n64Size)
{
	_Init();
	
	CreateShareMem(szFileName, szMapName, n64Size);
}

void CShareMemServerEx::CreateShareMem(const CString &szFileName, const CString &szMapName, DWORD dwSizeHigh, DWORD dwSizeLow)
{
	Create(szFileName, szMapName, dwSizeHigh, dwSizeLow);
}

void CShareMemServerEx::CreateShareMem(const CString &szFileName, const CString &szMapName, volatile __int64 n64Size)
{
	DWORD dwSizeHigh = 0;
	DWORD dwSizeLow = 0;

	dwSizeLow = (DWORD)(n64Size & 0xFFFFFFFF);
	n64Size = n64Size >> 32;
	dwSizeHigh = (DWORD)(n64Size & 0xFFFFFFFF);

	Create(szFileName, szMapName, dwSizeHigh, dwSizeLow);
}

void CShareMemServerEx::FlushViewFile()
{
	FlushViewOfFile(m_lpFileMapBuffer, m_dwSize);
}

void CShareMemServerEx::_Init()
{
	m_hFile = NULL;
	m_hFileMap = NULL;
	m_lpFileMapBuffer = NULL;
	m_dwSize	= 0;
	m_strFileName = _T("---");
	m_strMapName = _T("---");
	m_n64Size = 0;
	m_bCreateFlag = 0;

	TRACE(m_strFileName);
	TRACE(m_strMapName);
}

void CShareMemServerEx::_Destory()
{
	if (m_lpFileMapBuffer)
	{
		UnmapViewOfFile(m_lpFileMapBuffer);
		m_lpFileMapBuffer = NULL;
	}
	
	if (m_hFileMap)
	{
		CloseHandle(m_hFileMap);
		m_hFileMap = NULL;
	}
	
	if (m_hFile && m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = NULL;
	}

	_Init();
}

void CShareMemServerEx::Create(const CString &szFileName, const CString &szMapName, DWORD dwSizeHigh, DWORD dwSizeLow)
{
	if (m_bCreateFlag)
		_Destory();

	m_bCreateFlag = FALSE;

	m_strFileName =szFileName;

	ASSERT (szMapName.GetLength() >= 3 && dwSizeHigh >= 0 && dwSizeLow >= 0);

	if (szMapName .GetLength() <= 3|| (dwSizeHigh == 0 && dwSizeLow == 0) )
	{
		return;

	}

	m_strMapName = szMapName;
	
	m_n64Size = dwSizeHigh;
	m_n64Size = m_n64Size << 32;
	m_n64Size += dwSizeLow;
	
	if (m_strFileName.GetLength() > 3)
	{
		// file
		m_hFile = CreateFile(
			m_strFileName,
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,//OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
	}
	else
	{
		// system
		m_hFile = (HANDLE)0xFFFFFFFF;
	}

	if (m_hFile)
	{
		m_hFileMap = CreateFileMapping(
			m_hFile,
			NULL,
			PAGE_READWRITE,
			dwSizeHigh,
			dwSizeLow,
			m_strMapName
			);
	}

	m_bCreateFlag = TRUE;
}

LPVOID CShareMemServerEx::MapView(DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow,DWORD dwNumberOfBytesToMap)
{
	m_dwSize = dwNumberOfBytesToMap;
	ASSERT (m_hFileMap != NULL);

	if (m_hFileMap)
	{
		m_lpFileMapBuffer = MapViewOfFile(
			m_hFileMap,
			FILE_MAP_ALL_ACCESS,
			dwFileOffsetHigh,
			dwFileOffsetLow,
			m_dwSize
			);
	}
	else
	{
		m_lpFileMapBuffer = NULL;
	}

	return m_lpFileMapBuffer;
}

LPVOID CShareMemServerEx::MapView(volatile __int64 n64Offset,DWORD dwNumberOfBytesToMap)
{
	DWORD dwFileOffsetHigh = 0;
	DWORD dwFileOffsetLow = 0;

	dwFileOffsetLow = (DWORD)(n64Offset & 0xFFFFFFFF);
	n64Offset = n64Offset >> 32;
	dwFileOffsetHigh = (DWORD)(n64Offset & 0xFFFFFFFF);

	return MapView(dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap);
}


void CShareMemServerEx::ResetBuffer(unsigned char ucData,long nLen)
{
	if (m_lpFileMapBuffer != NULL)	
	{
		memset(m_lpFileMapBuffer, ucData, nLen);
	}
}
