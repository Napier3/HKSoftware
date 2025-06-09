// ShareMemClient.cpp: implementation of the CSFMServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShareMemClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShareMemClient::~CShareMemClient()
{
	_Destory();
}

CShareMemClient::CShareMemClient(DWORD dwAccess, const char *szMapName)
{
	_Init();
	Open(dwAccess, szMapName);
}

void CShareMemClient::Open(DWORD dwAccess, const char *szMapName)
{
	if (m_iOpenFlag)
		_Destory();

	m_iOpenFlag = 0;	

	if (szMapName == NULL)
	{
		return;
	}

	m_pMapName = _strdup(szMapName);

	m_hFileMap = OpenFileMapping(
		dwAccess,
		TRUE,
		_bstr_t(m_pMapName)
		);

	if (m_hFileMap)
	{
		m_lpFileMapBuffer = MapViewOfFile(
			m_hFileMap,
			dwAccess,
			0,
			0,
			0
			);
	}

	m_iOpenFlag = 1;
}

void CShareMemClient::_Init()
{
	m_hFileMap = NULL;
	m_lpFileMapBuffer = NULL;
	m_pMapName = NULL;
	m_iOpenFlag = 0;
}

void CShareMemClient::_Destory()
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

	if (m_pMapName)
	{
		free(m_pMapName);
		m_pMapName = NULL;
	}

	_Init();
}

LPVOID CShareMemClient::GetBuffer()
{
	return (m_lpFileMapBuffer)?(m_lpFileMapBuffer):(NULL);
}

DWORD CShareMemClient::GetSize()
{
	return 0;
}
