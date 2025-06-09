//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbFile.cpp  CSmDbFile


#include "stdafx.h"
#include "SmDbFile.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CSmDbFileArea::CSmDbFileArea()
{
	m_pSmFile = NULL;
}

CSmDbFileArea::~CSmDbFileArea()
{
	FreeArea();
}

void CSmDbFileArea::FreeArea()
{
	if (m_pSmFile != NULL)
	{
		m_pSmFile->UnMapView();
		delete m_pSmFile;
		m_pSmFile = NULL;
	}
}

void CSmDbFileArea::CreateArea(const CString &strID, __int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize)
{	
	m_strID = strID;
	m_n64Length = n64Length;
	m_n64BeginPos = n64BeginPos;
	m_dwOnceMapSize = dwOnceMapSize;	
	m_n64EndPos = n64Length + n64BeginPos;

	if (m_n64Length < m_dwOnceMapSize)
	{
		m_dwOnceMapSize = m_n64Length;
	}

	if (m_pSmFile == NULL)
	{
		m_pSmFile = new CShareMemClientEx(FILE_MAP_READ|FILE_MAP_WRITE, strID);
	}
}


BYTE* CSmDbFileArea::MapView(__int64 n64BeginPos, DWORD dwLen, DWORD dwMinLen)//32M
{
	ASSERT (m_pSmFile != NULL);

	if (m_pSmFile == NULL)
	{
		return NULL;
	}

	__int64 n64End = n64BeginPos + dwLen;

	if (n64End >= m_n64EndPos)
	{
		__int64 n64Temp = m_n64EndPos - n64BeginPos;

		if (n64Temp <= dwMinLen)
		{
			n64BeginPos = m_n64BeginPos;
		}
		else
		{
			n64BeginPos = n64Temp;
		}
	}

	DWORD dwOffset = n64BeginPos % 65536;
	__int64 n64Pos = n64BeginPos;
	n64Pos = n64Pos - dwOffset;
	DWORD dwSize = dwLen + dwOffset;


	BYTE *pBuffer = (BYTE*)m_pSmFile->MapView(n64Pos, dwSize);
	ASSERT(pBuffer != NULL);

	if (pBuffer != NULL)
	{
		m_pSmFile->LocatePos(dwOffset);
	}

	return pBuffer;
}

long CSmDbFileArea::SmWrite(CSmDbData *pData)
{
	long nDataLen = pData->GetLength();

	if (!m_pSmFile->CanWriteLen(nDataLen))
	{
		CalCurrPos();

		m_pSmFile->UnMapView();

		if (MapView(m_n64CurrPos, m_dwOnceMapSize) == NULL)
		{
			return FALSE;
		}
	}

	pData->SmWrite(*m_pSmFile);
	m_dwCurrWriteLen += nDataLen;

	return TRUE;
}

long CSmDbFileArea::SmWrite(CSmDbBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CSmDbData *p = NULL;

	while (pos != NULL)
	{
		p = (CSmDbData *)pList->GetNext(pos);
		SmWrite(p);
	}
	return 0;
}


long CSmDbFileArea::SmWrite(CSmDbTable *pTable)
{
	POS pos = pTable->GetHeadPosition();
	CSmDbData *p = NULL;

	while (pos != NULL)
	{
		p = (CSmDbData *)pTable->GetNext(pos);
		SmWrite(p);
	}

	return 0;
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CSmDbFile::CSmDbFile()
{
	//初始化属性
	m_n64FileSize = 4 * 1024 * 1024;
	m_pSmFileServer = NULL;

	//初始化成员变量
}

CSmDbFile::~CSmDbFile()
{
	FreeDbFile();
}


void CSmDbFile::FreeDbFile()
{
	if (m_pSmFileServer != NULL)
	{
		delete m_pSmFileServer;
		m_pSmFileServer = NULL;
	}
}

long CSmDbFile::CreateSmDbFile(const CString &strFile, const CString &strSmDbName, __int64 n64FileSize)
{
	FreeDbFile();

	m_strFile = strFile;
	m_strID = strSmDbName;

	if (m_pSmFileServer == NULL)
	{
		m_pSmFileServer = new CShareMemServerEx(strFile, strSmDbName, n64FileSize);
	}

	return (m_pSmFileServer != NULL);
}

CSmDbFileArea* CSmDbFile::CreateArea(__int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize)
{
	CSmDbFileArea *pArea = new CSmDbFileArea();
	pArea->CreateArea(m_strID, n64BeginPos, n64Length, dwOnceMapSize);
	return pArea;
}
