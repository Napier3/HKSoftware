// ShareMemServer.cpp: implementation of the CShareMemServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShareMemServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShareMemServer::~CShareMemServer()
{
	_Destory();
}

CShareMemServer::CShareMemServer(const char *szFileName, const char *szMapName, DWORD dwSize)
{
	_Init();
	Create(szFileName, szMapName, dwSize);
}

void CShareMemServer::_Init()
{
	m_hFile = NULL;
	m_hFileMap = NULL;
	m_lpFileMapBuffer = NULL;
	m_pFileName = NULL;
	m_pMapName = NULL;
	m_dwSize = 0;
	m_bCreateFlag = 0;
}

void CShareMemServer::_Destory()
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

	if (m_pFileName)
	{
		free(m_pFileName);
		m_pFileName = NULL;
	}

	if (m_pMapName)
	{
		free(m_pMapName);
		m_pMapName = NULL;
	}

	_Init();
}

void CShareMemServer::Create(const char *szFileName, const char *szMapName, DWORD dwSize)
{
	if (m_bCreateFlag)
		_Destory();

	m_bCreateFlag = FALSE;

	if (szFileName)
		m_pFileName = _strdup(szFileName);

	ASSERT (szMapName != NULL && dwSize > 0);
	if (szMapName == NULL || dwSize <= 0)
	{
		return;

	}
	m_pMapName = _strdup(szMapName);
	m_dwSize = dwSize;

	if (m_pFileName)
	{
		// file
		m_hFile = CreateFile(
			_bstr_t(m_pFileName),
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
			0,
			m_dwSize,
			_bstr_t(m_pMapName)
			);
	}

	if (m_hFileMap)
	{
		m_lpFileMapBuffer = MapViewOfFile(
			m_hFileMap,
			FILE_MAP_ALL_ACCESS,//FILE_MAP_WRITE|FILE_MAP_READ,
			0,
			0,
			m_dwSize
			);
	}

	m_bCreateFlag = TRUE;
}

LPVOID CShareMemServer::GetBuffer()
{
	return m_lpFileMapBuffer;
}

DWORD CShareMemServer::GetSize()
{
	return m_dwSize;
}

void CShareMemServer::ResetBuffer(unsigned char ucData,DWORD nLen)
{
	if (nLen == 0)
	{
		nLen = m_dwSize;
	}
	if (nLen > m_dwSize)
	{
		nLen = m_dwSize;
	}

	if (m_lpFileMapBuffer != NULL)	
	{
		memset(m_lpFileMapBuffer,ucData,nLen);
	}
}
