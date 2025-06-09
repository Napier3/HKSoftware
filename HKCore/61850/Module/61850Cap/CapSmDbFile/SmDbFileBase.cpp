//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapSmDb.cpp  CCapSmDb


#include "stdafx.h"
#include "SmDbFileBase.h"
#include "EpCapDbConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CSmDbAreaBase::CSmDbAreaBase()
{
	m_pSmFileClient = NULL;
	m_bMapCycle = FALSE;
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
	CEpCapDbFileCfg *pFileCfg = (CEpCapDbFileCfg*)pCfgArea->GetParent();

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

	if (n64End >= m_n64AreaEndPos)
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

void CSmDbAreaBase::LocateAreaPos(volatile __int64 n64BeginPos, volatile __int64 n64CurrPos)
{
	m_pSmFileClient->UnMapView();
	LPVOID pBuffer = MapView(n64CurrPos, m_dwOnceMapSize, 0);

	if (pBuffer == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("数据库创建没有成功........"));
	}
	else
	{
		m_pSmFileClient->SetCurr64Pos(n64CurrPos);
	}
}

volatile __int64 CSmDbAreaBase::SmWrite(LPVOID pData, long nLength)
{
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

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CSmDbFileBase::CSmDbFileBase()
{
	//初始化属性
	m_pSmFileServer = NULL;
	m_n64SmDbSize = 0;
	m_pSmDbArea = NULL;

	//初始化成员变量
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

void CSmDbFileBase::CreateArea(CEpCapDbFileCfg *pCfg)
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

long CSmDbFileBase::CreateSmDb(CEpCapDbFileCfg *pCfg)
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

long CSmDbFileBase::OpenSmDb(CEpCapDbFileCfg *pCfg)
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
	
	return m_oEpCapDbConfig.OpenXmlFile(strFile, CEpCapDbConfigXmlRWKeys::g_pXmlKeys);;
}

CString CSmDbFileMngrBase::GetCapDbConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("ep-cap-db-config.xml");

	return strFile;
}

BOOL CSmDbFileMngrBase::CreateServerByDbConfigFile()
{
	POS pos = m_oEpCapDbConfig.GetHeadPosition();
	CEpCapDbFileCfg *pCfg = NULL;
	CSmDbFileBase *pSmDB = NULL;

	while (pos != NULL)
	{
		pCfg = (CEpCapDbFileCfg *)GetNext(pos);
		pSmDB = CreateNewSmDB(pCfg);
		AddNewChild(pSmDB);
	}

	return TRUE;
}

BOOL CSmDbFileMngrBase::OpenByDbConfigFile()
{
	POS pos = m_oEpCapDbConfig.GetHeadPosition();
	CEpCapDbFileCfg *pCfg = NULL;
	CSmDbFileBase *pSmDB = NULL;

	while (pos != NULL)
	{
		pCfg = (CEpCapDbFileCfg *)GetNext(pos);
		pSmDB = OpenSmDB(pCfg);
		AddNewChild(pSmDB);
	}

	return TRUE;
}


CSmDbFileBase* CSmDbFileMngrBase::CreateNewSmDB(CEpCapDbFileCfg *pCfg)
{
	CSmDbFileBase *pNew = new CSmDbFileBase();

	pNew->CreateSmDb(pCfg);

	return pNew;
}

CSmDbFileBase* CSmDbFileMngrBase::OpenSmDB(CEpCapDbFileCfg *pCfg)
{
	CSmDbFileBase *pNew = new CSmDbFileBase();

	pNew->OpenSmDb(pCfg);

	return pNew;
}

