// RecordTestCalThread.cpp : implementation file
//

#include "stdafx.h"
#include "RecordTestCalThread.h"
#include "../RecordGlobalDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordTestCalThread

#ifndef _PSX_IDE_QT_
IMPLEMENT_DYNCREATE(CRecordTestCalThread, CWinThread)
#endif

long CRecordTestCalThread::g_nRecordTestCalThreadRefCount = 0;

CRecordTestCalThread::CRecordTestCalThread()
{
	m_pRecordTest = NULL;
	m_bIsInCalState = FALSE;
}

CRecordTestCalThread::~CRecordTestCalThread()
{
}

BOOL CRecordTestCalThread::InitInstance()
{
	g_nRecordTestCalThreadRefCount++;
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CRecordTestCalThread::ExitInstance()
{
	int nRet = CWinThread::ExitInstance();
	g_nRecordTestCalThreadRefCount--;
	return nRet;
}
// 
// void CRecordTestCalThread::WaitExit()
// {
// 	DWORD dwBegin = ::GetTickCount();
// 
// 	while(g_nRecordTestCalThreadRefCount > 0)
// 	{
// 		DWORD dwEnd = ::GetTickCount();
// 
// 		if (dwEnd - dwBegin > 3000)
// 		{
// 			break;
// 		}
// 	}
// }

#ifndef _PSX_IDE_QT_
BEGIN_MESSAGE_MAP(CRecordTestCalThread, CWinThread)
	//{{AFX_MSG_MAP(CRecordTestCalThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP

	ON_THREAD_MESSAGE(WM_BEGIN_CALVALUES, OnCalValues)

END_MESSAGE_MAP()
#endif

//���غ���OnWndMsg��ʵ����Ϣ����
void CRecordTestCalThread::OnThreadMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
	if (WM_BEGIN_CALVALUES == nMsgID)
	{
		if (g_nRecordTestCalState == 0)//20220618 zhouhj ���δ�������,���ٵ���
		{
			OnCalValues(wParam, lParam);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRecordTestCalThread message handlers
void CRecordTestCalThread::OnReceiveData()
{
	if (m_bIsInCalState || g_nRecordTestCalState == 1)
	{
		return;
	}
	
	PostThreadMessage(WM_BEGIN_CALVALUES, 0, 0);
}

long g_nRecordTestCalState = 0;
long g_nRecordTestCalCount = 0;

#ifdef _PSX_IDE_QT_
extern BOOL g_bSmartCap_RecordNow; 
#endif

void CRecordTestCalThread::OnCalValues(WPARAM wParam, LPARAM lParam)
{
#ifdef _PSX_IDE_QT_
	//zhouhj 2023.9.20 �˳�¼�������,���ٽ���¼��
	if (!g_bSmartCap_RecordNow)
	{
		return;
	}
#endif

	g_nRecordTestCalState = 1;
	m_bIsInCalState = TRUE;

	if (m_pRecordTest != NULL)
	{
		//lijunqing  2020-6-18
		if (lParam == 0)
		{//¼�������㣬ÿ��ͨ�������ݸ���һ��
			m_pRecordTest->CalValues();
		}
		else
		{//61850���ļ��㣬ÿ��ͨ�������ݸ�����һ��
			m_pRecordTest->CalValuesEx();
		}
	}
	
	m_bIsInCalState = FALSE;
	g_nRecordTestCalState = 0;

//	return 0;
}

void CRecordTestCalThread::SetRecordTest(CRecordTest *pRecordTest)
{
	m_pRecordTest = pRecordTest;
}
