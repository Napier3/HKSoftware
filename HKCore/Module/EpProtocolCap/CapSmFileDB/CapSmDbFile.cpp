//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapSmDbFile.cpp  CCapSmDbFile


#include "stdafx.h"
#include "CapSmDbFile.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CCapSmDbFileArea::CCapSmDbFileArea()
{
	m_pSmFile = NULL;
	m_bMapCycle = FALSE;
// 	m_dwCurrWriteLen = 0;
}

CCapSmDbFileArea::~CCapSmDbFileArea()
{
	FreeArea();
}

void CCapSmDbFileArea::FreeArea()
{
	if (m_pSmFile != NULL)
	{
		m_pSmFile->UnMapView();
		delete m_pSmFile;
		m_pSmFile = NULL;
	}
}

void CCapSmDbFileArea::CreateArea(const CString &strID, volatile __int64 n64BeginPos, volatile __int64 n64Length, DWORD dwOnceMapSize)
{	
	m_strID = strID;
	m_n64Length = n64Length;
	m_n64AreaBeginPos = n64BeginPos;
	m_dwOnceMapSize = dwOnceMapSize;	
	m_n64AreaEndPos = m_n64Length + n64BeginPos;

	if (dwOnceMapSize == 0)
	{
		m_dwOnceMapSize = (DWORD)m_n64Length;
	}

	if (m_n64Length < m_dwOnceMapSize)
	{
		m_dwOnceMapSize = (DWORD)m_n64Length;
	}

	if (m_pSmFile == NULL)
	{
		m_pSmFile = new CShareMemClientEx(FILE_MAP_READ|FILE_MAP_WRITE, strID);
	}

	MapView(m_n64AreaBeginPos, m_dwOnceMapSize);
}

void CCapSmDbFileArea::MapArea(volatile __int64 n64BeginPos)
{
	ASSERT (m_pSmFile != NULL);

	if (m_pSmFile == NULL)
	{
		return;
	}

	MapView(n64BeginPos, m_dwOnceMapSize);
}

BOOL CCapSmDbFileArea::IsAreaOpenSucc()
{
	if (m_pSmFile == NULL)
	{
		return FALSE;
	}

	if (m_pSmFile->GetBuffer() == NULL)
	{
		return FALSE;
	}

	return TRUE;
}

BYTE* CCapSmDbFileArea::MapView(volatile __int64 &n64BeginPos, DWORD dwLen, DWORD dwMinLen)//32M
{
	ASSERT (m_pSmFile != NULL);

	if (m_pSmFile == NULL)
	{
		return NULL;
	}

	if (CLogPrint::g_pLogPrint != NULL)
	{
		CLogPrint::LogFormatString(NULL, LOGLEVEL_TRACE, _T("64Begin=%I64d  Len = %08X"), n64BeginPos, dwLen);
	}

//	volatile __int64 n64BackPos = n64BeginPos;
	volatile __int64 n64Left = m_n64AreaEndPos - n64BeginPos;

	if (n64BeginPos >= m_n64AreaEndPos || n64Left < dwMinLen || n64Left < dwLen)
	{//如果超出范围，或者剩下的空间不够最小空间，则从头开始映射
		n64BeginPos = m_n64AreaBeginPos;
		m_bMapCycle = TRUE;
	}

	volatile __int64 n64End = n64BeginPos + dwLen;

	if (n64End >= m_n64AreaEndPos)
	{
		dwLen = m_n64AreaEndPos - n64BeginPos;
	}

	DWORD dwOffset = n64BeginPos % 65536;
	volatile __int64 n64Pos = n64BeginPos;
	n64Pos = n64Pos - dwOffset;
	DWORD dwSize = dwLen + dwOffset;

	BYTE *pBuffer = (BYTE*)m_pSmFile->MapView(n64Pos, dwSize);
	ASSERT(pBuffer != NULL);

	if (pBuffer != NULL)
	{
		pBuffer = (BYTE*)m_pSmFile->LocatePos(dwOffset);
	}
	else
	{
// 		CString strMsg;
// 		strMsg.Format(_T("n64BeginPos=%I64d  Len= %d ==>> n64Pos=%I64d  Len= %d"),n64BeginPos, dwLen,  n64Pos, dwSize);
// 		AfxMessageBox(strMsg);
// 		AfxMessageBox(m_strID);
// 		AfxMessageBox(m_strName);
	}

	return pBuffer;
}

volatile __int64 CCapSmDbFileArea::GetCurrPos()
{
	return m_pSmFile->GetCurr64Pos();
}

void CCapSmDbFileArea::LocateAreaPos(volatile __int64 n64BeginPos, volatile __int64 n64CurrPos)
{
	m_pSmFile->UnMapView();
	LPVOID pBuffer = MapView(n64CurrPos, m_dwOnceMapSize, 0);

	if (pBuffer == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("数据库创建没有成功........"));
	}
	else
	{
		m_pSmFile->SetCurr64Pos(n64CurrPos);
	}
}

volatile __int64 CCapSmDbFileArea::SmWrite(LPVOID pData, long nLength)
{
	if (!m_pSmFile->CanWriteLen(nLength))
	{
		volatile __int64 n64CurrPos = m_pSmFile->GetCurr64Pos();
		m_pSmFile->UnMapView();

		if (MapView(n64CurrPos, m_dwOnceMapSize, nLength) == NULL)
		{
			return -1;
		}
	}

	volatile __int64 n64Pos = m_pSmFile->GetCurr64Pos();
	m_pSmFile->WriteBuffer(pData, nLength);

	return n64Pos;
}

LPVOID CCapSmDbFileArea::Read(__int64 n64BeginPos, DWORD dwLength)
{
	if (m_pSmFile == NULL)
	{
		return NULL;
	}

	LPVOID pBuffer = m_pSmFile->Read(n64BeginPos, dwLength);

	if (pBuffer == NULL)
	{
		pBuffer = MapView(n64BeginPos, m_dwOnceMapSize, dwLength);
	}

	return pBuffer;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CCapSmDbFile::CCapSmDbFile()
{
	//初始化属性
	m_n64FileSize = 4 * 1024 * 1024;
	m_pSmFileServer = NULL;

	//初始化成员变量
}

CCapSmDbFile::~CCapSmDbFile()
{
	FreeDbFile();
}


void CCapSmDbFile::FreeDbFile()
{
	if (m_pSmFileServer != NULL)
	{
		delete m_pSmFileServer;
		m_pSmFileServer = NULL;
	}
}

long CCapSmDbFile::CreateCapSmDbFile(const CString &strFile, const CString &strCapSmDbName, volatile __int64 n64FileSize)
{
	FreeDbFile();

	m_strFile = strFile;
	m_strID = strCapSmDbName;

	if (m_pSmFileServer == NULL)
	{
		m_pSmFileServer = new CShareMemServerEx(strFile, strCapSmDbName, n64FileSize);
	}

	return (m_pSmFileServer != NULL);
}

CCapSmDbFileArea* CCapSmDbFile::CreateArea(volatile __int64 n64BeginPos, volatile __int64 n64Length, DWORD dwOnceMapSize)
{
	CCapSmDbFileArea *pArea = new CCapSmDbFileArea();
	pArea->CreateArea(m_strID, n64BeginPos, n64Length, dwOnceMapSize);
	AddNewChild(pArea);
	return pArea;
}

BOOL CCapSmDbFile::IsMapCycle()
{
	POS pos = GetHeadPosition();
	CCapSmDbFileArea *pArea = NULL;
	BOOL bCycle = FALSE;

	while (pos != NULL)
	{
		pArea = (CCapSmDbFileArea *)GetNext(pos);

		if (pArea->IsMapCycle())
		{
			bCycle = TRUE;
			break;
		}
	}

	return bCycle;
}

void EpCap_CalSmDbSize(double nDataSize, volatile __int64 &n64DataSize)
{
	if (nDataSize < 1)
	{
		double dK = nDataSize * 1000;
		n64DataSize = (__int64)dK;
		n64DataSize *= 1024;
	}
	else
	{
		n64DataSize = (DWORD)nDataSize;
		n64DataSize *= 1024;
		n64DataSize *= 1024;
	}
}

void EpCap_CalSmDbSize(long nDataSize, volatile __int64 &n64DataSize)
{
	n64DataSize = (DWORD)nDataSize;
	n64DataSize *= 1024;
	n64DataSize *= 1024;
}

void EpCap_CalSmDbSize(double nDataSize, double nDataView, volatile __int64 &n64DataSize, volatile __int64 &n64DataView)
{
	EpCap_CalSmDbSize(nDataSize, n64DataSize);
	EpCap_CalSmDbSize(nDataView, n64DataView);
}


void EpCap_CalSmDbSize(long nDataSize, long nDataView, volatile __int64 &n64DataSize, volatile __int64 &n64DataView)
{
	EpCap_CalSmDbSize(nDataSize, n64DataSize);
	EpCap_CalSmDbSize(nDataView, n64DataView);
}

