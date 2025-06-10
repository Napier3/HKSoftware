#include "stdafx.h"
#include "XSmartCapMngr.h"

CAutoCriticSection g_oCapDeviceChRecordCriticSection;

long CXSmartCapMngr::g_nXSmartCapMngrRef = 0;
CXSmartCapMngr* CXSmartCapMngr::g_pXSmartCapMngr = NULL;

CXSmartCapMngr *g_theXSmartCapMngr = NULL;

CXSmartCapMngr::CXSmartCapMngr(void)
{
	g_theXSmartCapMngr = this;
#ifndef _PSX_IDE_QT_
	g_pXEthernetCap_61850 = NULL;
#endif
	g_pSttCap61850 = NULL;
	m_pX61850Cap = NULL;
	g_strSttRcdFilePath = _P_GetDBPath();
}

CXSmartCapMngr::~CXSmartCapMngr(void)
{
#ifndef _PSX_IDE_QT_
	if (g_pXEthernetCap_61850 != NULL)
	{
		delete g_pXEthernetCap_61850;
		g_pXEthernetCap_61850 = NULL;
	}
#endif

	if (g_pSttCap61850 != NULL)
	{
		delete g_pSttCap61850;
		g_pSttCap61850 = NULL;
	}

	g_theXSmartCapMngr = NULL;
	m_pX61850Cap = NULL;
}

void CXSmartCapMngr::Create()
{
	g_nXSmartCapMngrRef++;

	if (g_nXSmartCapMngrRef == 1)
	{
		g_pXSmartCapMngr = new CXSmartCapMngr();
	}
}

void CXSmartCapMngr::Release()
{
	g_nXSmartCapMngrRef--;

	if (g_nXSmartCapMngrRef == 0)
	{
		g_pXSmartCapMngr->ExitInstance();
		delete g_pXSmartCapMngr;
		g_pXSmartCapMngr = NULL;
	}
}

CXSttCap_61850* CXSmartCapMngr::GetSttCap61850_Global()
{
	if (g_theXSmartCapMngr == NULL)
	{
		return NULL;
	}

	return g_theXSmartCapMngr->GetSttCap_61850();
}

#ifndef _PSX_IDE_QT_
CXEthernetCap_61850* CXSmartCapMngr::CreateEthernetCap_61850(int nNetCardIndex)
{
	if (g_pXEthernetCap_61850 == NULL)
	{
		g_pXEthernetCap_61850 = new CXEthernetCap_61850();
	}

	m_pX61850Cap = g_pXEthernetCap_61850;
#ifdef _XSmartCap_use_SmDb_
	m_pX61850Cap->InitCapSmDb();
#endif

	PETHER_CAP_CONFIG pCapConfig = g_pXEthernetCap_61850->GetCapConfig();
	pCapConfig->nNetCardIndex = nNetCardIndex;

	return g_pXEthernetCap_61850;
}
#endif

//2022-4-7 lijunqing 创建纯粹的61850分析功能，不需要做报问提取，330报文监视模式
// CSttLocalRcdMemBufferMngrLinux *pSttLocalRcdMemBufferMngrLinux =new CSttLocalRcdMemBufferMngrLinux();
//CSttRcdMemBufferMngr *pSttRcdMemBufferMngr = new CSttRcdMemBufferMngr();
CXSttCap_61850* CXSmartCapMngr::CreateSttCap_61850(CSttTestAppCfg *pSttTestAppCfg
												   , CXCapPkgBufferMngrInterface *pSttXCapBufferMngr)
{
	if (g_pSttCap61850 == NULL)
	{
		CXSttCap_61850 *pNew = new CXSttCap_61850(pSttXCapBufferMngr);
		pNew->AttachSttTestAppCfg(pSttTestAppCfg);
		g_pSttCap61850 = pNew;
	}

	m_pX61850Cap = g_pSttCap61850;
#ifdef _XSmartCap_use_SmDb_
	m_pX61850Cap->InitCapSmDb();
#endif

	return g_pSttCap61850;
}


BOOL CXSmartCapMngr::IsCapExit()
{
	if (m_pX61850Cap == NULL)
	{
		return TRUE;
	}

	return m_pX61850Cap->IsCapExit();
}

BOOL CXSmartCapMngr::CanClose()
{
	if (m_pX61850Cap == NULL)
	{
		return TRUE;
	}

	return m_pX61850Cap->CanClose();
}

BOOL CXSmartCapMngr::IsInCapture()
{
	if (m_pX61850Cap == NULL)
	{
		return FALSE;
	}

	return m_pX61850Cap->IsInCapture();
}

BOOL CXSmartCapMngr::BeginCap(CIecCfgDatasMngr *pIecfgDataMngr, BOOL bClearDevices)
{
	ASSERT (m_pX61850Cap != NULL);
	return m_pX61850Cap->BeginCap(pIecfgDataMngr,bClearDevices);
}

BOOL CXSmartCapMngr::StopCap()
{
	ASSERT (m_pX61850Cap != NULL);
	return m_pX61850Cap->StopCap();
}

void CXSmartCapMngr::BeginRecord()
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->BeginRecord();
	}
}

void CXSmartCapMngr::StopRecord()
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->StopRecord();
	}
}

void CXSmartCapMngr::RecordDevice(CCapDeviceBase *pDevice)
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->RecordDevice(pDevice);
	}
}

//根据pCapDevice，初始化设备数据模型
void CXSmartCapMngr::InitDvmDevice(CCapDeviceBase *pCapDevice)
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->InitDvmDevice(pCapDevice);
	}
}

void CXSmartCapMngr::InitDvmDevices()
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->InitDvmDevices();
	}
}


CXSmMemBufferMngr* CXSmartCapMngr::GetCapMemBufferMngr()
{
	if (m_pX61850Cap == NULL)
	{
		return NULL;
	}

	return m_pX61850Cap->m_pFrameMemBufferMngr;
}

void CXSmartCapMngr::OnCloseMainFrame()
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->OnCloseMainFrame();
	}
}

CCapDeviceChRecordMngr* CXSmartCapMngr::GetCapDeviceChRecordMngr()
{
	if (m_pX61850Cap == NULL)
	{
		return NULL;
	}

	return &m_pX61850Cap->m_oCapDeviceChRecordMngr;
}

void CXSmartCapMngr::GetCapMemBufMngrIndex(CString &strCurrIndex, CString &strParseIndex, CString &strWriteIndex)
{
	CXSmMemBufferMngr* pMngr = GetCapMemBufferMngr();

	if (pMngr == NULL)
	{
		return;
	}

	strCurrIndex.Format(_T("%d"), pMngr->GetCurrIndex());
	strParseIndex.Format(_T("%d"), pMngr->GetCurrParseIndex());
	strWriteIndex.Format(_T("%d"), pMngr->GetCurrWriteIndex());
}

void CXSmartCapMngr::AdjustRecordChRange()
{
	CCapDeviceChRecordMngr *pRecordMngr = GetCapDeviceChRecordMngr();

	if (pRecordMngr != NULL)
	{
		pRecordMngr->AdjustRecordChRange();
	}
}

void CXSmartCapMngr::ExitInstance()
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->ExitInstance();
	}

	
}

void CXSmartCapMngr::ChangeChRecordState(CCapDeviceChBase *pCh, long nState)
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->ChangeChRecordState(pCh, nState);
	}

}

void CXSmartCapMngr::ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer)
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->ReadCapBuffer(pBuffer,pDestBuffer);
	}
}

void CXSmartCapMngr::SetIecCfgDevice(CIecCfgDevice* pCfgDevice)
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->SetIecCfgDevice(pCfgDevice);
	}
}

CRecordTest* CXSmartCapMngr::GetRecordTest()
{
	if (m_pX61850Cap != NULL)
	{
		return m_pX61850Cap->m_oCapDeviceChRecordMngr.m_pRecordTest;
	}

	return NULL;
}

void CXSmartCapMngr::GetSttCapParas(CDataGroup *pSttParas, BOOL bUseSmv, BOOL bUseGoose, BOOL bUseFT3)
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->GetSttCapParas(pSttParas, bUseSmv, bUseGoose,bUseFT3);
	}
}

//2022-5-2  lijunqing 
void CXSmartCapMngr::InitSmartCapCtrl()
{
	g_pSttCap61850->ClearCap();
}

//创建IEC分析相关的数据集
void CXSmartCapMngr::IecAnalysis_AddDatasets()
{
	if (m_pX61850Cap != NULL)
	{
		m_pX61850Cap->IecAnalysis_AddDatasets();
	}
}


