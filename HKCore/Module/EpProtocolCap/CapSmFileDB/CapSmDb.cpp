//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapSmDb.cpp  CCapSmDb


#include "stdafx.h"
#include "CapSmDb.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define _use_index_0
#define _use_index

CCapSmDb::CCapSmDb()
{
	//初始化属性
// 	m_pCapFrameSmDbFile = NULL;
// 	m_pCapDeviceDataSmDbFile = NULL;
	m_pCapDbIndexSmDbFile = NULL;
	m_pCapDbIndex0SmDbFile = NULL;
	m_pCapFrmDvSmDbFile = NULL;
	m_pCapDataSmDbFile = NULL;

	m_nIndex0DbHeadSize = 0;
	m_nIndexDbSize = 0;
// 	m_nDeviceDataDbSize = 0;
	m_nCapFrameAndDeviceDbSize = 0;
	m_nCapDataDbSize = 0;

	m_nIndex0DbHeadView = 0;
	m_nIndexDbView = 0;
// 	m_nDeviceDataDbView = 0;
	m_nCapFrameAndDeviceDbView = 0;
	m_nCapDataDbView = 0;
	//初始化成员变量
}

CCapSmDb::~CCapSmDb()
{
	if (m_pCapDbIndexSmDbFile != NULL)
	{
		delete m_pCapDbIndexSmDbFile;
		m_pCapDbIndexSmDbFile = NULL;
	}

	if (m_pCapDbIndex0SmDbFile != NULL)
	{
		delete m_pCapDbIndex0SmDbFile;
		m_pCapDbIndex0SmDbFile = NULL;
	}

	if (m_pCapFrmDvSmDbFile != NULL)
	{
		delete m_pCapFrmDvSmDbFile;
		m_pCapFrmDvSmDbFile = NULL;
	}

	if (m_pCapDataSmDbFile != NULL)
	{
		delete m_pCapDataSmDbFile;
		m_pCapDataSmDbFile = NULL;
	}
}


void CCapSmDb::InitDbFiles()
{
#ifdef _use_index
	if (m_pCapDbIndexSmDbFile == NULL)
	{
		m_pCapDbIndexSmDbFile = new CCapDbIndexSmDbFile();
	}
#endif

#ifdef _use_index_0
	if (m_pCapDbIndex0SmDbFile == NULL)
	{
		m_pCapDbIndex0SmDbFile = new CCapDbIndex0SmDbFile();
	}
#endif

	if (m_pCapFrmDvSmDbFile == NULL)
	{
		m_pCapFrmDvSmDbFile = new CCapFrmDvSmDbFile();
	}

	if (m_pCapDataSmDbFile == NULL)
	{
		m_pCapDataSmDbFile = new CCapDataSmDbFile();
	}
}

void CCapSmDb::CreateSmDbServer()
{
	InitDbFiles();

#ifdef _use_index_0
	m_pCapDbIndex0SmDbFile->CreateCapDbIndex0SmDbServer(m_nIndex0DbHeadSize, m_nIndex0DbHeadView, m_strDbFilePath);
#else
	ZeroMemory(&m_oSmDbFilePos, sizeof(EPSMDBFILEPOS));
#endif

	if (IsCapDbVersionError())
	{
		return;
	}

	//根据Index0，初始化个数据库文件的位置
#ifdef _use_index
	m_pCapDbIndexSmDbFile->CreateCapDbIndexSmDbServer(m_nIndexDbSize, m_nIndexDbView, m_strCapIndexFilePath);
#endif

	m_pCapFrmDvSmDbFile->CreateCapFrmDvSmDbServer(m_nCapFrameAndDeviceDbSize, m_nCapFrameAndDeviceDbView, m_strCapDvFilePath);
	m_pCapDataSmDbFile->CreateCapDataSmDbServer(m_nCapDataDbSize, m_nCapDataDbView, m_strCapDvFilePath);

#ifdef _use_index_0
	if (m_pCapDbIndex0SmDbFile->IsNewCreate())
	{
		EPSMDBFILEPOS oSmDbFilePos;
		m_pCapDbIndex0SmDbFile->GetSmDbFilePos(oSmDbFilePos);
		oSmDbFilePos.n64DbIndexMax = m_pCapDbIndexSmDbFile->m_n64MaxIndexCount;
		m_pCapDbIndex0SmDbFile->SetSmDbFilePos(oSmDbFilePos);
	}
#endif

}

void CCapSmDb::CreateSmDbClient()
{
	InitDbFiles();
	m_pCapDbIndex0SmDbFile->CreateCapDbIndex0SmDbClient(m_nIndex0DbHeadSize, m_nIndex0DbHeadView, m_strDbFilePath);

	if (IsCapDbVersionError())
	{
		return;
	}

	//根据Index0，初始化个数据库文件的位置
	m_pCapDbIndexSmDbFile->CreateCapDbIndexSmDbClient(m_nIndexDbSize, m_nIndexDbView, m_strCapIndexFilePath);
 	m_pCapFrmDvSmDbFile->CreateCapFrmDvSmDbClient(m_nCapFrameAndDeviceDbSize, m_nCapFrameAndDeviceDbView, m_strCapDvFilePath);
	m_pCapDataSmDbFile->CreateCapDataSmDbClient(m_nCapDataDbSize, m_nCapDataDbView, m_strCapDataFilePath);
}

void CCapSmDb::ValidSmDb()
{
	if (m_pCapFrmDvSmDbFile == NULL)
	{
		return;
	}

	if (m_pCapDataSmDbFile == NULL)
	{
		return;
	}

	if (m_pCapFrmDvSmDbFile->m_pFrameSmDbArea == NULL)
	{
		return;
	}

	if (m_pCapDataSmDbFile->m_pFrameSmDbArea == NULL)
	{
		return;
	}

// 	if (m_pCapFrmDvSmDbFile->m_pFrameSmDbArea == NULL)
// 	{
// 		AfxMessageBox(_T("数据库创建没有成功"));
// 		return;
// 	}

}

void CCapSmDb::Write(CCapCycleMemBufferMngr *pBufferMngr)
{
	if (pBufferMngr->GetCount() == 0)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("没有需要写的数据........"));
		return;
	}

	if (m_pCapFrmDvSmDbFile->m_pFrameSmDbArea == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("数据库创建没有成功........"));
		return;
	}

	if (m_pCapDataSmDbFile->m_pFrameSmDbArea == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("数据库创建没有成功........"));
		return;
	}

	EPSMDBFILEPOS oSmDbFilePos;

#ifdef _use_index_0
	m_pCapDbIndex0SmDbFile->GetSmDbFilePos(oSmDbFilePos);
#else
	oSmDbFilePos = m_oSmDbFilePos;
#endif

	EPSMDBFILEPOS oSmDbFilePosBk = oSmDbFilePos;

 	m_pCapFrmDvSmDbFile->Write(pBufferMngr,  oSmDbFilePos);
	m_pCapDataSmDbFile->Write(pBufferMngr,  oSmDbFilePos);

#ifdef _use_index
	m_pCapDbIndexSmDbFile->Write(pBufferMngr,  m_pCapDbIndex0SmDbFile, oSmDbFilePos);
#endif

#ifdef _use_index_0
	m_pCapDbIndex0SmDbFile->SetSmDbFilePos(oSmDbFilePos);
	m_pCapDbIndex0SmDbFile->SaveIndexoMngr();;
#else
	m_oSmDbFilePos = oSmDbFilePos;
#endif

// 	CString strMsg;
// 	strMsg.Format(_T("报文库：%I64d ==>> %I64d"), oSmDbFilePosBk.n64CapFrmDvCurrPos, oSmDbFilePos.n64CapFrmDvCurrPos);
// 	CLogPrint::LogString(LOGLEVEL_TRACE, strMsg);
// 
// 	strMsg.Format(_T("索引库：%I64d ==>> %I64d"), oSmDbFilePosBk.n64DbIndexCurrPos, oSmDbFilePos.n64DbIndexCurrPos);
// 	CLogPrint::LogString(LOGLEVEL_TRACE, strMsg);

	SetWriteFlag(pBufferMngr);
}

void CCapSmDb::SetWriteFlag(CCapCycleMemBufferMngr *pBufferMngr)
{
	POS pos = pBufferMngr->GetHeadPosition();

	//设置数据标记
	while (pos != NULL)
	{
		CCapCycleMemBuffer *pBuffer = (CCapCycleMemBuffer*)pBufferMngr->GetAt(pos);

//		if (pBuffer->Ebs_BeParsed())
		{
			pBuffer->SetState(EBS_HASWRITE);
		}

		pBufferMngr->GetNext(pos);
	}
}

void CCapSmDb::ReadConfig()
{
// 	long dSize = 0;
// 	long dView = 0;
// 
// 	dSize = 2;
// 	dView = 1;
// 	EpCap_CalSmDbSize(dSize, dView, m_nIndex0DbHeadSize, m_nIndex0DbHeadView);
// 
// 	dSize = 4;
// 	dView = 1;
// 	EpCap_CalSmDbSize(dSize, dView, m_nIndexDbSize, m_nIndexDbView);
// 
// 	EpCap_CalSmDbSize(dSize, dView, m_nCapFrameAndDeviceDbSize, m_nCapFrameAndDeviceDbView);
// 
// 	m_strDbFilePath = _T("D:\\Program Files\\EPOTO\\e-Monitor\\DataBase\\");

	CString strFile;
	strFile = _P_GetConfigPath();

	strFile += _T("ep-cap-db-config.xml");
	OpenXmlFile(strFile, _bstr_t("epoto-cap-db"), NULL);
}

BOOL CCapSmDb::IsSmDbTrue()
{
	if (!m_pCapDbIndex0SmDbFile->m_pDbIndexHead->IsAreaOpenSucc())
	{
		return FALSE;
	}

	if (!m_pCapDbIndexSmDbFile->m_pDbIndex->IsAreaOpenSucc())
	{
		return FALSE;
	}

	if (!m_pCapFrmDvSmDbFile->m_pFrameSmDbArea->IsAreaOpenSucc())
	{
		return FALSE;
	}

	if (!m_pCapDataSmDbFile->m_pFrameSmDbArea->IsAreaOpenSucc())
	{
		return FALSE;
	}

// 	if (!m_pCapDeviceDataSmDbFile->m_pDeviceData->IsAreaOpenSucc())
// 	{
// 		return FALSE;
// 	}
// 
// 	if (!m_pCapFrameSmDbFile->m_pFrameSmDbArea->IsAreaOpenSucc())
// 	{
// 		return FALSE;
// 	}

	return TRUE;
}

long CCapSmDb::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	long dSize = 0;
	long dView = 0;

	xml_GetElementText(_bstr_t("db-index-head-size"), oNode, dSize);
	xml_GetElementText(_bstr_t("db-index-head-view"), oNode, dView);
	EpCap_CalSmDbSize(dSize, dView, m_nIndex0DbHeadSize, m_nIndex0DbHeadView);

	xml_GetElementText(_bstr_t("db-index-size"), oNode, dSize);
	xml_GetElementText(_bstr_t("db-index-view"), oNode, dView);
	EpCap_CalSmDbSize(dSize, dView, m_nIndexDbSize, m_nIndexDbView);

	xml_GetElementText(_bstr_t("db-cap-frame-size"), oNode, dSize);
	xml_GetElementText(_bstr_t("db-cap-frame-view"), oNode, dView);
	EpCap_CalSmDbSize(dSize, dView, m_nCapFrameAndDeviceDbSize, m_nCapFrameAndDeviceDbView);

	xml_GetElementText(_bstr_t("db-cap-data-size"), oNode, dSize);
	xml_GetElementText(_bstr_t("db-cap-data-view"), oNode, dView);
	EpCap_CalSmDbSize(dSize, dView, m_nCapDataDbSize, m_nCapDataDbView);

	xml_GetElementText(_bstr_t("db-file-path"), oNode, m_strDbFilePath);
	xml_GetElementText(_bstr_t("capdv-file-path"), oNode, m_strCapDvFilePath);
	xml_GetElementText(_bstr_t("capindex-file-path"), oNode, m_strCapIndexFilePath);
	xml_GetElementText(_bstr_t("capdata-file-path"), oNode, m_strCapDataFilePath);

	if (m_strCapDvFilePath.GetLength() == 0)
	{
		m_strCapDvFilePath = m_strDbFilePath;
	}

	if (m_strCapDataFilePath.GetLength() == 0)
	{
		m_strCapDataFilePath = m_strDbFilePath;
	}

	if (m_strCapIndexFilePath.GetLength() == 0)
	{
		m_strCapIndexFilePath = m_strDbFilePath;
	}

	if (m_strDbFilePath.Right(1) != _T("\\") )
	{
		m_strDbFilePath += _T("\\");
	}

	if (m_strCapDvFilePath.Right(1) != _T("\\") )
	{
		m_strCapDvFilePath += _T("\\");
	}

	if (m_strCapDataFilePath.Right(1) != _T("\\") )
	{
		m_strCapDataFilePath += _T("\\");
	}

	if (m_strCapIndexFilePath.Right(1) != _T("\\") )
	{
		m_strCapIndexFilePath += _T("\\");
	}

	return 0;
}

long CCapSmDb::Query(EPCAPSEARCHCONFIG &oSearchConfig, CEpQueryEpCapDbBufferIndex &oQuery, CEpDeviceDatasMngr &oDataMngr)
{
	if (m_pCapDbIndex0SmDbFile == NULL || m_pCapDbIndexSmDbFile == NULL)
	{
		return -1;
	}

	if (m_pCapDbIndex0SmDbFile->m_pDbIndexHead == NULL)
	{
		return -1;
	}

	if (m_pCapDbIndexSmDbFile->m_pDbIndex == NULL)
	{
		return -1;
	}

	CEpQueryIndex0Ranges oIndex0Ranges;
	m_pCapDbIndex0SmDbFile->m_pDbIndexHead->Query(oSearchConfig.tmBegin, oSearchConfig.tmEnd, oIndex0Ranges);

	if (oSearchConfig.dwSearchType == EP_SEARCH_TYPE_FRAME)
	{
		m_pCapDbIndexSmDbFile->m_pDbIndex->Query(oSearchConfig, oIndex0Ranges, oQuery);
	}
	else
	{
		m_pCapDataSmDbFile->m_pFrameSmDbArea->Query(oSearchConfig, oIndex0Ranges, oDataMngr);
	}

	return 0;
}

void CCapSmDb::ReadCapBuffer(EPCAPDBBUFFERINDEX *pIndex, CCycleMemBuffer *pBuffer)
{
	if (m_pCapFrmDvSmDbFile == NULL)
	{
		return;
	}

	m_pCapFrmDvSmDbFile->ReadCapBuffer(pIndex, pBuffer);
}

