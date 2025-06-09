#include "StdAfx.h"
#include "..\Protocol\EpProtocolFactory.h"
#include "EpCapThreadMngr.h"

CEpCapThreadMngr::CEpCapThreadMngr(void)
{
	m_pEpCapConfig = new CMonitorCapConfig();
	m_strName = _T("监视线程管理");
	m_strID = _T("EpCapThreadMngr");
}

CEpCapThreadMngr::~CEpCapThreadMngr(void)
{
	delete m_pEpCapConfig;
	m_pEpCapConfig = NULL;
	DeleteAll();
}

void CEpCapThreadMngr::InitCapConfig()
{
// 	CString strFile;
// 	strFile = _P_GetConfigPath();
// 	strFile += _T("EpCapConfig.xml");
// 
// 	m_pEpCapConfig->m_strFile = strFile;
// 	m_pEpCapConfig->OpenXmlFile(strFile, CMonitorCapConfigXmlRWKeys::CMonitorCapConfigKey(), CMonitorCapConfigXmlRWKeys::g_pXmlKeys);
	m_pEpCapConfig->InitConfig();
	g_DEBUG_MONITOR_STATE = m_pEpCapConfig->m_nUseGenerator;
}

void CEpCapThreadMngr::CreateCapture()
{
	CreateCapture(m_pEpCapConfig);
	long nCount = GetCount();

	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThread = NULL;

	while (pos != NULL)
	{
		pThread = (CEpCapThreadBase *)GetNext(pos);
// 		pThread->SetCapThreadCount(nCount);
	}
}

void CEpCapThreadMngr::CreateCapture(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EMCCLASSID_CEMCNETDEVICE)
		{
			CreateCapThread((CEmcNetDevice*)p);
		}
		else if (nClassID == EMCCLASSID_CEMCSERIALCONFIG)
		{
			CreateCapThread((CEmcSerialConfig*)p);
		}
		else if (p->IsBaseList())
		{
			CreateCapture((CExBaseList*)p);
		}
	}
}

void CEpCapThreadMngr::ReleaseCapture()
{
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);

		pThreadBase->ReleaseCapture();
	}

	g_nExitCaptrueState = 1;
}


void CEpCapThreadMngr::RestartNetCap(long nNetCardIndex)
{
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);

		if (pThreadBase->GetClassID() == CAPTHREAD_ETHERNET)
		{
			if (((CEpEthernetCapThread*)pThreadBase)->GetNetCardIndex() == nNetCardIndex)
			{
				((CEpEthernetCapThread*)pThreadBase)->SetRestartWinCap();
			}
		}
	}
}

void CEpCapThreadMngr::ViewThreadRunInfor()
{
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);
		pThreadBase->m_bViewThreadRunInfor = TRUE;
	}
}

BOOL CEpCapThreadMngr::CanRestartNetCap(long &nCardIndex, BOOL bReset)
{
	BOOL bCan = FALSE;
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);

		if (pThreadBase->GetClassID() == CAPTHREAD_ETHERNET)
		{
			if (((CEpEthernetCapThread*)pThreadBase)->CanRestartNetCap(bReset))
			{
				nCardIndex = ((CEpEthernetCapThread*)pThreadBase)->GetNetCardIndex();
				bCan = TRUE;
				break;
			}
		}
	}

	return bCan;
}

void CEpCapThreadMngr::StopCapture()
{
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);

		pThreadBase->StopCapture();
	}
}

void CEpCapThreadMngr::StartCapture()
{
	g_nExitCaptrueState = 0;
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);

		pThreadBase->CreateCapture();
	}
}

void CEpCapThreadMngr::ResumeCapture()
{
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);

		pThreadBase->ResumeCapture();
	}
}

void CEpCapThreadMngr::ExitCapture()
{
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);

		pThreadBase->ReleaseCapture();
	}
}

BOOL CEpCapThreadMngr::HasAllCapThreadExit()
{
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);

		bTrue = pThreadBase->HasAllCapThreadExit();

		if (!bTrue)
		{
			break;
		}
	}

	return bTrue;
}

BOOL CEpCapThreadMngr::IsCaptureStarted()
{
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);

		bTrue = pThreadBase->IsCaptureStarted();

		if (bTrue)
		{
			break;
		}
	}

	return bTrue;
}

void CEpCapThreadMngr::SetCanFreeAllCapDatas()
{
	POS pos = GetHeadPosition();
	CEpCapThreadBase *pThreadBase = NULL;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pThreadBase = (CEpCapThreadBase *)GetNext(pos);
		pThreadBase->SetCanFreeAllCapDatas();
	}
}

CEpEthernetCapThread* CEpCapThreadMngr::CreateCapThread(CEmcNetDevice *pNetDevice)
{
	CProtocolBase *pProtocol = CEpProtocolFactory::CreateProtocolByID(pNetDevice->m_strProtocol);	
	ASSERT(pProtocol != NULL);
	CEpEthernetCapThread *pThread = NULL;

	if (pProtocol != NULL)
	{
		pThread = CEpEthernetCapThread::CreateCapThread();
		pThread->SetCapConfig(pNetDevice);
//		EP_ETHER_CAP_CONFIG *pCapConfig = pThread->GetCapConfig();
//		pCapConfig->nNetCardIndex = CString_To_long(pNetDevice->m_strID);
		pThread->m_strName.Format(_T("Net:%s"), pNetDevice->m_strID);

//		pCapConfig->filters.count_filter = pNetDevice->m_nUDP + pNetDevice->m_nTCP;
		long nIndex = 0;
		
// 		if (pNetDevice->m_nUDP)
// 		{
// 			ep_ether_cap_filter *pFilter = &(pCapConfig->filters.filters[nIndex]);
// 			memset(pFilter, 0, sizeof(ep_ether_cap_filter));
// 			pFilter->type = EFT_UDP;
// 			nIndex++;
// 		}
// 
// 		if (pNetDevice->m_nUDP)
// 		{
// 			ep_ether_cap_filter *pFilter = &(pCapConfig->filters.filters[nIndex]);
// 			memset(pFilter, 0, sizeof(ep_ether_cap_filter));
// 			pFilter->type = EFT_TCP;
// 			nIndex++;
// 		}

		pThread->SetProtocol(pProtocol);
		pThread->m_strName = pNetDevice->m_strName;
		pThread->m_strID = pNetDevice->m_strID;

		AddTail(pThread);
// 		g_nEpCapBufferMngrCount++;
	}
	else
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("create %s protocol \"%s\" failed! "), pNetDevice->m_strName, pNetDevice->m_strProtocol);
	}

	return pThread;
}

CEpSerialCapThread* CEpCapThreadMngr::CreateCapThread(CEmcSerialConfig *pSerialDevice)
{
	CProtocolBase *pProtocol = CEpProtocolFactory::CreateProtocolByID(pSerialDevice->m_strProtocol);	
	ASSERT(pProtocol != NULL);
	CEpSerialCapThread *pThread = NULL;

	if (pProtocol != NULL)
	{
		pThread = CEpSerialCapThread::CreateCapThread();
		pThread->SetCapConfig(pSerialDevice);
// 		EP_SERIAL_CAP_CONFIG* pCapConfig = pThread->GetCapConfig();
// 		pCapConfig->iBaudRate = pSerialDevice->m_nBaudRate;
// 		pCapConfig->iByteSize = pSerialDevice->m_nByteSize;
// 		pCapConfig->iParity = pSerialDevice->m_nParity;
// 		pCapConfig->iPort = pSerialDevice->m_nPort;
// 		pCapConfig->iStopBits = pSerialDevice->m_nStopBits;

		pThread->SetProtocol(pProtocol);
		//pThread->m_strName = pSerialDevice->m_strName;
		pThread->m_strID.Format(_T("COM%d"), pSerialDevice->m_nPort);
		pThread->m_strName.Format(_T("%s (COM:%d)"), pSerialDevice->m_strName, pSerialDevice->m_nPort);
		AddTail(pThread);
// 		g_nEpCapBufferMngrCount++;
	}
	else
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("create %s protocol \"%s\" failed! "), pSerialDevice->m_strName, pSerialDevice->m_strProtocol);
	}

	return pThread;
}
