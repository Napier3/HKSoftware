//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbFileBase.cpp  CSmDbFileBase


#include "stdafx.h"
#include "SmDbFileBase.h"
#include "SmDbConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CSmDbAreaBase::CSmDbAreaBase()
{
	m_pSmFileClient = NULL;
	m_bMapCycle = FALSE;
// 	m_nCurrWriteIndex = 0;
// 	m_nCurrFreeIndex = 0;
}

CSmDbAreaBase::~CSmDbAreaBase()
{
	FreeArea();
}

void CSmDbAreaBase::FreeArea()
{
	if (m_pSmFileClient != NULL)
	{
		m_pSmFileClient->UnMapView();
		delete m_pSmFileClient;
		m_pSmFileClient = NULL;
	}
}

BOOL CSmDbAreaBase::CreateArea(CEpCapDbFileArea *pCfgArea)
{
	FreeArea();
	CSmDbFileCfg *pFileCfg = (CSmDbFileCfg*)pCfgArea->GetParent();

	__int64 n64BeginPos = pCfgArea->m_nBeginPos * 1024 * 1024;
	__int64 n64Length = pCfgArea->m_nSize  * 1024 * 1024;
	int nMapSize = pCfgArea->m_nView   * 1024 * 1024;

	m_strID = pCfgArea->m_strID;
	m_strName = pCfgArea->m_strName;

	CreateArea(pFileCfg->m_strID, n64BeginPos, n64Length, nMapSize);

	return m_pSmFileClient->IsValid();
}

void CSmDbAreaBase::CreateArea(const CString &strID, volatile __int64 n64BeginPos, volatile __int64 n64Length, DWORD dwOnceMapSize)
{	
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

	if (m_pSmFileClient == NULL)
	{
		m_pSmFileClient = new CShareMemClientEx(FILE_MAP_READ|FILE_MAP_WRITE, strID);
	}

	MapView(m_n64AreaBeginPos, m_dwOnceMapSize);
}

void CSmDbAreaBase::MapArea(volatile __int64 n64BeginPos)
{
	ASSERT (m_pSmFileClient != NULL);

	if (m_pSmFileClient == NULL)
	{
		return;
	}

	MapView(n64BeginPos, m_dwOnceMapSize);
}

BOOL CSmDbAreaBase::IsAreaOpenSucc()
{
	if (m_pSmFileClient == NULL)
	{
		return FALSE;
	}

	if (m_pSmFileClient->GetBuffer() == NULL)
	{
		return FALSE;
	}

	return TRUE;
}

BYTE* CSmDbAreaBase::MapView(volatile __int64 n64BeginPos, DWORD dwLen, DWORD dwMinLen)//32M
{
	ASSERT (m_pSmFileClient != NULL);

	if (m_pSmFileClient == NULL)
	{
		return NULL;
	}

	//	volatile __int64 n64BackPos = n64BeginPos;
	volatile __int64 n64Left = m_n64AreaEndPos - n64BeginPos;

	if (n64BeginPos >= m_n64AreaEndPos || n64Left < dwMinLen)
	{//如果超出范围，或者剩下的空间不够最小空间，则从头开始映射
		n64BeginPos = m_n64AreaBeginPos;
		m_bMapCycle = TRUE;
	}

	volatile __int64 n64End = n64BeginPos + dwLen;

	if (n64End > m_n64AreaEndPos)
	{
		n64BeginPos = m_n64AreaEndPos - n64BeginPos;
	}

	DWORD dwOffset = n64BeginPos % 65536;
	volatile __int64 n64Pos = n64BeginPos;
	n64Pos = n64Pos - dwOffset;
	DWORD dwSize = dwLen + dwOffset;

	BYTE *pBuffer = (BYTE*)m_pSmFileClient->MapView(n64Pos, dwSize);
	ASSERT(pBuffer != NULL);

	if (pBuffer != NULL)
	{
		pBuffer = (BYTE*)m_pSmFileClient->LocatePos(dwOffset);
	}
	else
	{
	}

	return pBuffer;
}

volatile __int64 CSmDbAreaBase::GetCurrPos()
{
	return m_pSmFileClient->GetCurr64Pos();
}

LPVOID CSmDbAreaBase::LocateAreaPos(volatile __int64 n64CurrPos)
{
	m_pSmFileClient->UnMapView();
	LPVOID pBuffer = MapView(n64CurrPos, m_dwOnceMapSize, 0);

	if (pBuffer == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("数据库创建没有成功........"));
	}
	else
	{
		m_pSmFileClient->SetCurr64Pos(n64CurrPos);
	}

	return pBuffer;
}

volatile __int64 CSmDbAreaBase::SmWrite(LPVOID pData, long nLength)
{
	if (pData == NULL || nLength == 0)
	{//处理数据非法的情况
		return m_pSmFileClient->GetCurr64Pos();
	}

	if (!m_pSmFileClient->CanWriteLen(nLength))
	{
		volatile __int64 n64CurrPos = m_pSmFileClient->GetCurr64Pos();
		m_pSmFileClient->UnMapView();

		if (MapView(n64CurrPos, m_dwOnceMapSize, nLength) == NULL)
		{
			return -1;
		}
	}

	volatile __int64 n64Pos = m_pSmFileClient->GetCurr64Pos();
	m_pSmFileClient->WriteBuffer(pData, nLength);

	return n64Pos;
}

LPVOID CSmDbAreaBase::Read(__int64 n64BeginPos, DWORD dwLength)
{
	if (m_pSmFileClient == NULL)
	{
		return NULL;
	}

	LPVOID pBuffer = m_pSmFileClient->Read(n64BeginPos, dwLength);

	if (pBuffer == NULL)
	{
		pBuffer = MapView(n64BeginPos, m_dwOnceMapSize, dwLength);
	}

	return pBuffer;
}

//2020-06-12   lijunqing
BOOL CSmDbAreaBase::Read(LPVOID pBuffer, __int64 n64BeginPos, DWORD dwLength)
{
	LPVOID p = Read(n64BeginPos, dwLength);

	if (p == NULL)
	{
		return FALSE;
	}

	memcpy(pBuffer, p, dwLength);

	return TRUE;
}

long CSmDbAreaBase::GetWriteCount(CXSmMemBufferMngr *pBufferMngr)
{
	long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;
	pBufferMngr->GetWriteIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);
	long nCount = 0;

	if (nEnd1 > nBegin1)
	{
		nCount = nEnd1 - nBegin1 + 1;
	}

	if (nBegin2 >= 0)
	{
		nCount = nEnd2 - nBegin2 + 1;
	}

	return nCount;
}

long CSmDbAreaBase::Write(CXSmMemBufferMngr *pBufferMngr)
{
	long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;
	pBufferMngr->GetWriteIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);
	long nCount = 0;

	if (nEnd1 > nBegin1)
	{
		Write(pBufferMngr, nBegin1, nEnd1);
		nCount = nEnd1 - nBegin1 + 1;
	}

	if (nBegin2 >= 0)
	{
		Write(pBufferMngr, nBegin2, nEnd2);
		nCount += nEnd2 - nBegin2 + 1;
	}

	return nCount;
}
void CSmDbAreaBase::Write(CXSmMemBufferMngr *pBufferMngr,long nBeginIndex, long nEndIndex)
{
	if (nBeginIndex < 0 || nEndIndex < 0)
	{
		return;
	}

	long nIndex = 0;

	for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
	{
		CXSmMemBuffer *pCapBuffer = (CXSmMemBuffer*)pBufferMngr->GetFrameBuffer(nIndex);
		BYTE *pBuffer = pCapBuffer->GetBuffer();

		if (pBuffer != NULL)
		{
			pCapBuffer->m_n64Pos = SmWrite(pCapBuffer->GetBufferHead(), pCapBuffer->GetBufferHeadLength());
			pCapBuffer->m_n64Pos = SmWrite(pCapBuffer->GetBuffer(), pCapBuffer->GetBufferLength());
			pCapBuffer->Ebs_SetWrited();
		}

		//下一次的位置 = 当前位置的下一个位置
		pBufferMngr->SetCurrWriteIndex(nIndex+1);
	}
}

// 
// void CSmDbAreaBase::Free(CXSmMemBufferMngr *pBufferMngr)
// {
// 	long nMaxCount = pBufferMngr->GetMaxCount();
// 	long nCurrCount = pBufferMngr->GetCurrCount();
// 	long nCurrIndex = pBufferMngr->GetCurrIndex();
// 
// 	if (nCurrCount == nMaxCount)
// 	{
// 		if (m_nCurrFreeIndex < nCurrIndex)
// 		{
// 			Free(pBufferMngr, m_nCurrFreeIndex, nCurrIndex-1);
// 		}
// 		else
// 		{
// 			if (Free(pBufferMngr, m_nCurrFreeIndex, nCurrCount-1) )
// 			{
// 				Free(pBufferMngr, 0, nCurrIndex-1);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		Free(pBufferMngr, m_nCurrFreeIndex, nCurrIndex-1);
// 	}
// }
// 
// BOOL CSmDbAreaBase::Free(CXSmMemBufferMngr *pBufferMngr,long nBeginIndex, long nEndIndex)
// {
// 	long nIndex = 0;
// 
// 	for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
// 	{
// 		CXSmMemBuffer *pCapBuffer = (CXSmMemBuffer*)pBufferMngr->GetFrameBuffer(nIndex);
// 		
// 		if (pCapBuffer->CanFreeBuffer())
// 		{
// 			pCapBuffer->FreeBuffer();
// 			m_nCurrFreeIndex = nIndex;
// 		}
// 		else
// 		{
// 			return FALSE;
// 		}
// 	}
// 
// 	return TRUE;
// }

void CSmDbAreaBase::ReadBuffer(__int64 n64Pos, long nLen, CXMemBufferBse *pDestBuffer)
{
	BYTE *pFrmBuffer = (BYTE*)Read(n64Pos, nLen);

	if (pFrmBuffer != NULL)
	{
		pDestBuffer->SetBuffer(pFrmBuffer, nLen);
	}
}

void CSmDbAreaBase::ReadBuffer(CXSmMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer)
{
	ReadBuffer (pBuffer->m_n64Pos, pBuffer->GetBufferLength(), pDestBuffer);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CSmDbFileBase::CSmDbFileBase()
{
	//初始化属性
	m_pSmFileServer = NULL;
	m_n64SmDbSize = 0;
	m_pSmDbArea = NULL;

	//初始化成员变量
	m_n64BeginPos = 0;
}

CSmDbFileBase::~CSmDbFileBase()
{
	FreeDbFile();
}

__int64 CSmDbFileBase::GetFileSize()
{
	if (m_pSmFileServer == NULL)
	{
		return 0;
	}

	return m_pSmFileServer->GetFileSize();
}

void CSmDbFileBase::FreeDbFile()
{
	if (m_pSmFileServer != NULL)
	{
		delete m_pSmFileServer;
		m_pSmFileServer = NULL;
	}

	DeleteAll();
}

void CSmDbFileBase::CreateArea(CSmDbFileCfg *pCfg)
{
	ASSERT (pCfg->GetCount() > 0);
	POS pos = pCfg->GetHeadPosition();
	CEpCapDbFileArea *pCfgArea = NULL;
	CSmDbAreaBase *pSmDbArea = NULL;

	while (pos != NULL)
	{
		pCfgArea = (CEpCapDbFileArea *)pCfg->GetNext(pos);
		pSmDbArea = CreateNewArea(pCfgArea);
		AddNewChild(pSmDbArea);
	}

	m_pSmDbArea = (CSmDbAreaBase *)GetHead();
	ASSERT (m_pSmDbArea != NULL);
}

long CSmDbFileBase::CreateSmDb(CSmDbFileCfg *pCfg)
{
	CString strFile = pCfg->GetSmDBFilePath();
	__int64 nViewSize = pCfg->m_nView * 1024 * 1024;
	__int64 nDBSize = pCfg->m_nSize * 1024 * 1024;

	CreateSmDb(nDBSize, nViewSize, pCfg->m_strID, strFile);

	return m_pSmFileServer->IsValid();
}

long CSmDbFileBase::CreateSmDb(const CString &strFile, const CString &strSmDbName, __int64 n64FileSize)
{
	FreeDbFile();

	m_strFile = strFile;
	m_strID = strSmDbName;
	m_n64SmDbSize = n64FileSize;

	if (m_pSmFileServer == NULL)
	{
		m_pSmFileServer = new CShareMemServerEx(strFile, strSmDbName, n64FileSize);
	}

	return (m_pSmFileServer != NULL);
}


void CSmDbFileBase::CreateSmDb(volatile __int64 nDbSize, volatile __int64 nViewSize, const CString &strID, const CString &strPath)
{
	CString strFile;

	if (strPath.GetAt(1) == ':')//路径
	{
		strFile = strPath;
	}
	else
	{
		strFile = _P_GetDBPath();
		strFile += strPath;
	}

	CreateSmDb(strFile, strID, nDbSize);

	CSmDbAreaBase *pArea = CreateArea(0, nDbSize, nViewSize, TRUE);
	ASSERT (pArea != NULL);
	pArea->UnMap();
}

long CSmDbFileBase::OpenSmDb(CSmDbFileCfg *pCfg)
{
	CString strFile = pCfg->GetSmDBFilePath();
	__int64 nViewSize = pCfg->m_nView * 1024 * 1024;
	__int64 nDBSize = pCfg->m_nSize * 1024 * 1024;

	m_strFile = pCfg->GetSmDBFilePath();
	m_strID = pCfg->m_strID;
	m_n64SmDbSize = nDBSize;
	m_pSmFileServer = NULL;

	CreateArea(pCfg);

	return 0;
}

void CSmDbFileBase::OpenSmDb(volatile __int64 nDbSize, const CString &strID, const CString &strPath)
{
	m_strFile = strPath;
	m_strID = strID;
	m_n64SmDbSize = nDbSize;
	m_pSmFileServer = NULL;
}

CSmDbAreaBase* CSmDbFileBase::CreateArea(__int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize, BOOL bAddTail)
{
	CSmDbAreaBase *pArea = CreateNewArea();//new CSmDbAreaBase();
	pArea->CreateArea(m_strID, n64BeginPos, n64Length, dwOnceMapSize);

	if (bAddTail)
	{
		AddNewChild(pArea);
	}

	return pArea;
}


CSmDbAreaBase* CSmDbFileBase::CreateNewArea(CEpCapDbFileArea *pCfgArea)
{
	CSmDbAreaBase *pNew = new CSmDbAreaBase();
	pNew->CreateArea(pCfgArea);

	return pNew;
}

BOOL CSmDbFileBase::IsAreaOpenSucc()
{
	if (m_pSmDbArea == NULL)
	{
		return FALSE;
	}

	return m_pSmDbArea->IsAreaOpenSucc();
}

long CSmDbFileBase::Write(CXSmMemBufferMngr *pBufferMngr)
{
	LocatePos(m_n64BeginPos);
	long nCount = m_pSmDbArea->Write(pBufferMngr);
	m_n64BeginPos = m_pSmDbArea->GetCurrPos();
	m_pSmDbArea->UnMap();

	return nCount;
}
// 
// void CSmDbFileBase::Free(CXSmMemBufferMngr *pBufferMngr)
// {
// 	m_pSmDbArea->Free(pBufferMngr);
// }

void CSmDbFileBase::ReadBuffer(__int64 n64Pos, long nLen, CXMemBufferBse *pDestBuffer)
{
	m_pSmDbArea->ReadBuffer(n64Pos, nLen, pDestBuffer);
}

//////////////////////////////////////////////////////////////////////////
//
CSmDbFileMngrBase::CSmDbFileMngrBase()
{
	
}

CSmDbFileMngrBase::~CSmDbFileMngrBase()
{
	
}

BOOL CSmDbFileMngrBase::OpenCapDbConfigFile()
{
	CString strFile = GetCapDbConfigFile();
	
	return m_oSmDbConfig.OpenXmlFile(strFile, CSmDbConfigXmlRWKeys::g_pXmlKeys);;
}

CString CSmDbFileMngrBase::GetCapDbConfigFile()
{
	return EpCap_GetCapDbConfigFile();
}

BOOL CSmDbFileMngrBase::CreateServerByDbConfigFile()
{
	POS pos = m_oSmDbConfig.GetHeadPosition();
	CSmDbFileCfg *pCfg = NULL;
	CSmDbFileBase *pSmDB = NULL;

	while (pos != NULL)
	{
		pCfg = (CSmDbFileCfg *)GetNext(pos);
		pSmDB = CreateNewSmDB(pCfg);
		AddNewChild(pSmDB);
	}

	return TRUE;
}

BOOL CSmDbFileMngrBase::OpenByDbConfigFile()
{
	POS pos = m_oSmDbConfig.GetHeadPosition();
	CSmDbFileCfg *pCfg = NULL;
	CSmDbFileBase *pSmDB = NULL;

	while (pos != NULL)
	{
		pCfg = (CSmDbFileCfg *)GetNext(pos);
		pSmDB = OpenSmDB(pCfg);
		AddNewChild(pSmDB);
	}

	return TRUE;
}


CSmDbFileBase* CSmDbFileMngrBase::CreateNewSmDB(CSmDbFileCfg *pCfg)
{
	CSmDbFileBase *pNew = new CSmDbFileBase();

	pNew->CreateSmDb(pCfg);

	return pNew;
}

CSmDbFileBase* CSmDbFileMngrBase::OpenSmDB(CSmDbFileCfg *pCfg)
{
	CSmDbFileBase *pNew = new CSmDbFileBase();

	pNew->OpenSmDb(pCfg);

	return pNew;
}

//////////////////////////////////////////////////////////////////////////
//
CString EpCap_GetCapDbConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("ep-cap-db-config.xml");

	return strFile;
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

