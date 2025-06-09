#include "StdAfx.h"
#include "XEthernetCap_61850.h"

CXEthernetCap_61850::CXEthernetCap_61850(void)
{
	m_pEthernetCapThread = NULL;
	m_pProtocol61850 = NULL;

#ifndef _PSX_IDE_QT_
	m_pSmDbWriteThread = NULL;
	m_pCapFrameDbFileServer = NULL;
	m_pCapFrameDbFileClient = NULL;

	m_pCapFrameDbFileServer = new CCapFrameDbFile();
	m_pProtocol61850 = new CProtocol61850();
	m_pCapFrameDbFileClient = new CCapFrameDbArea();
#endif
}

CXEthernetCap_61850::~CXEthernetCap_61850(void)
{

}


void CXEthernetCap_61850::CreateCapTrhead()
{
	FreeCapture();

	m_pEthernetCapThread = CEthernetCapThread::CreateNew();
	SetCapConfig(&m_oCapConfig);
	m_pEthernetCapThread->SetProtocol(m_pProtocol61850);
	m_pProtocol61850->SetCapDeviceMngr(&m_oCapDeviceAll);
	m_pFrameMemBufferMngr = m_pEthernetCapThread->GetCapMemBufferMngr();

#ifndef _PSX_IDE_QT_
	m_pCapFrameDbFileServer->Reset();

	if (m_pSmDbWriteThread == NULL)
	{
		m_pSmDbWriteThread = CSmDbWriteThread::CreateSmDbWriteThread();
	}

	m_pSmDbWriteThread->InitThread(m_pEthernetCapThread->GetCapMemBufferMngr(), m_pCapFrameDbFileServer);
#endif
}

BOOL CXEthernetCap_61850::BeginCap(CIecCfgDatasMngr *pIecfgDataMngr,BOOL bClearDevices)
{
	if (bClearDevices)
	{
		m_oCapDeviceAll.DeleteAll();
	}

	m_oCapDeviceChRecordMngr.BeginCap(bClearDevices);
	CreateCapTrhead();

	if (m_pEthernetCapThread != NULL)
	{
		m_pEthernetCapThread->CreateCapture();
	}

	return TRUE;
}

BOOL CXEthernetCap_61850::StopCap()
{
	if (m_pEthernetCapThread != NULL)
	{
		m_pEthernetCapThread->ReleaseCapture();
	}

	OnBeginSmDbWrite();

	return TRUE;
}

PETHER_CAP_CONFIG CXEthernetCap_61850::GetCapConfig()
{
	return &m_oCapConfig;
	// 	if (m_pEthernetCapThread != NULL)
	// 	{
	// 		return m_pEthernetCapThread->GetCapConfig();
	// 	}
	// 	else
	// 	{
	// 		return NULL;
	// 	}
}

void CXEthernetCap_61850::SetCapConfig(PETHER_CAP_CONFIG pCapConfig)
{
	if (m_pEthernetCapThread != NULL)
	{
		m_pEthernetCapThread->SetCapConfig(pCapConfig);
	}
}


BOOL CXEthernetCap_61850::IsCapExit()
{
	if (m_pEthernetCapThread != NULL)
	{
		if (!m_pEthernetCapThread->HasAllCapThreadExit())
		{
			return FALSE;
		}
	}

	// 	if (m_pSmDbWriteThread != NULL)
	// 	{
	// 		if (!m_pSmDbWriteThread->WaitForExit())
	// 		{
	// 			return FALSE;
	// 		}
	// 	}

	return TRUE;
}


BOOL CXEthernetCap_61850::CanClose()
{
	if (!IsCapExit())
	{
		return FALSE;
	}

	if (m_pSmDbWriteThread != NULL)
	{
		if (!m_pSmDbWriteThread->WaitForExit())
		{
			return FALSE;
		}
	}

	return TRUE;
}


BOOL CXEthernetCap_61850::IsInCapture()
{
	if (m_pEthernetCapThread == NULL)
	{
		return FALSE;
	}

	return m_pEthernetCapThread->IsCaptureStarted();
}

void CXEthernetCap_61850::FreeCapture()
{
	if (m_pEthernetCapThread != NULL)
	{
		delete m_pEthernetCapThread;
		m_pEthernetCapThread = NULL;
	}
}

void CXEthernetCap_61850::ExitInstance()
{
	FreeCapture();

	if (m_pProtocol61850 != NULL)
	{
		delete m_pProtocol61850;
		m_pProtocol61850 = NULL;
	}

#ifndef _PSX_IDE_QT_
	if (m_pCapFrameDbFileServer != NULL)
	{
		delete m_pCapFrameDbFileServer;
		m_pCapFrameDbFileServer = NULL;
	}

	if (m_pCapFrameDbFileClient != NULL)
	{
		delete m_pCapFrameDbFileClient;
		m_pCapFrameDbFileClient = NULL;
	}
#endif
}
