#include "StdAfx.h"
#include "SerialMonitorMngr.h"

CSerialMonitorMngr::CSerialMonitorMngr(void)
{
	m_pDataProcessThread = NULL;
	m_bOnProcess = FALSE;
}

CSerialMonitorMngr::~CSerialMonitorMngr(void)
{
	StopCapture();
}

int CSerialMonitorMngr::StartCapture()
{
	POS pos = GetHeadPosition();
	CSerialMonitor *p = NULL;
	
	while (pos != NULL)
	{
		p = (CSerialMonitor*)GetNext(pos);
		p->StartCapture();
	}
	
	if (m_pDataProcessThread == NULL)
	{
		m_pDataProcessThread = AfxBeginThread(DataProcessThread,this);
		m_pDataProcessThread->m_bAutoDelete = TRUE;
	}

	return S_OK;
}

void CSerialMonitorMngr::StopCapture()
{
	DWORD dwBegin = GetTickCount();
	m_bOnProcess = FALSE;
	
	POS pos = GetHeadPosition();
	CSerialMonitor *p = NULL;
	
	while (pos != NULL)
	{
		p = (CSerialMonitor*)GetNext(pos);
		p->StopCapture();
	}
	
	if (m_pDataProcessThread != NULL)
	{
		m_pDataProcessThread = NULL;
	}

	DWORD dwEnd = GetTickCount();
	TRACE("Cost Time %u ms\n", dwEnd-dwBegin);
	CLogPrint::LogString((LPVOID)g_pLogTracePrint, LOGLEVEL_TRACE, "串口监视已停止...");
}

UINT CSerialMonitorMngr::DataProcessThread(LPVOID pParam)
{
	CSerialMonitorMngr* pThis = (CSerialMonitorMngr*)pParam;
	int iLen, iDel;
	CString strContent;
	BOOL bProcess = FALSE;
	BOOL bProcessEx = FALSE;
	BOOL bHasDealOneFrame;
	int iState;
	u_char *pbyContentOfMaster;
	
	while (pThis->m_bOnProcess)
	{
		POS pos = pThis->GetHeadPosition();
		CSerialMonitor *p = NULL;

		while (pos != NULL)
		{
			p = (CSerialMonitor*)pThis->GetNext(pos);
			iLen = p->GetData(&pbyContentOfMaster);
			
			if (iLen > 0)
			{			
				// 如果有数据，处理
				//iDel = pThis->ProcessData(pbyContentOfMaster, iLen, FRAME101_CONTROL_1To1, bHasDealOneFrame, iState);
				//p->OffsetProcessPos(iDel);
			}
		}

		Sleep(10);
	}
	
	TRACE("************************DataProcessThread Exit************************\n");
	return S_OK;
}

int CSerialMonitorMngr::ProcessData(const BYTE *byData, int iLen, int iType, BOOL &bHasDealOneFrame, int &iState)
{
	int iDel;

//	g_pNetMonitorData->InsertCaptureData(byData, iLen, iType, iDel, bHasDealOneFrame, iState);

	return iDel;
}

void CSerialMonitorMngr::ResetAllData()
{
//	g_pNetMonitorData->m_iCurrentFrame_101 = -1;
//	g_pNetMonitorData->m_pWndWatch_101_SerialSlaveEx->DeleteAllItems();
}