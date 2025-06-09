// SmDbWriteThread.cpp : implementation file
//

#include "stdafx.h"
#include "SmDbWriteThread.h"

#include "..\SmartCap\61850Cap\CapSmDbFile\CapFrameDbFileQueryTool.h"

#define SMDB_WRITE_TIMER_LONG  1000

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCapFrameDbFileQueryTool g_oCapFrameDbFileQueryTool;

/////////////////////////////////////////////////////////////////////////////
// CSmDbWriteThread

IMPLEMENT_DYNCREATE(CSmDbWriteThread, CWinThread)


long CSmDbWriteThread::g_nSmDbWriteThreadRefCount = 0;

CSmDbWriteThread::CSmDbWriteThread()
{
	m_bIsNowWritting = FALSE;
	m_bIsInWrittingLastData = FALSE;
	m_pCapSmDbFile = NULL;
	m_pXSmMemBufferMngr = NULL;
	m_nExitState = 0;
	m_nWriteTimerID = 0;
}

CSmDbWriteThread::~CSmDbWriteThread()
{
	
}

void CSmDbWriteThread::FreeThread()
{
	
}

BOOL CSmDbWriteThread::InitInstance()
{
	//初始化COM环境
	::CoInitialize(NULL);

	g_nSmDbWriteThreadRefCount++;
	m_nWriteTimerID = ::SetTimer(NULL, 1, SMDB_WRITE_TIMER_LONG, NULL);

	return TRUE;
}

int CSmDbWriteThread::ExitInstance()
{
	::CoUninitialize();
	int iRet = CWinThread::ExitInstance();
	
	g_nSmDbWriteThreadRefCount--;
	return iRet;
}

BEGIN_MESSAGE_MAP(CSmDbWriteThread, CWinThread)
	//{{AFX_MSG_MAP(CSmDbWriteThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP

	ON_THREAD_MESSAGE(WM_CAP_WRITE_SMDB, CSmDbWriteThread::OnWriteSmDb)
	ON_THREAD_MESSAGE(WM_TIMER, OnTimer)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmDbWriteThread message handlers

BOOL CSmDbWriteThread::CanWriteNow()
{
	if (m_bIsNowWritting)
	{
		return FALSE;
	}
	
	return TRUE;
}

void CSmDbWriteThread::Post_WriteSmDB_Msg()
{
// 	BOOL bCanWrite = CanWriteNow();
// 	
// 	if (bCanWrite)
// 	{		
// 	}
// 	else
// 	{
// 	}

//	m_bIsNowWritting = TRUE;
	PostThreadMessage(WM_CAP_WRITE_SMDB, 0, 0);
}

BOOL CSmDbWriteThread::Post_WriteSmDBEx_Msg()
{
	PostThreadMessage(WM_CAP_WRITE_SMDB, 1, 1);
	return TRUE;
}

void CSmDbWriteThread::OnWriteSmDb(WPARAM wParam, LPARAM lParam)
{
	OnWriteSmDb();
}

void CSmDbWriteThread::OnWriteSmDb()
{
	DWORD dwBeginTick = ::GetTickCount();
	// 	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("写数据库开始>>>>>>"));

	if (m_pXSmMemBufferMngr == NULL || m_pCapSmDbFile == NULL)
	{
		return;
	}

	if (m_bIsNowWritting)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("错误，正在写数据库......"));
		return;
	}

	try
	{
		m_bIsNowWritting = TRUE;

		if (m_pCapSmDbFile != NULL && m_pXSmMemBufferMngr  !=  NULL)
		{
			if (m_pCapSmDbFile->Write(m_pXSmMemBufferMngr) > 0)
			{
				m_pXSmMemBufferMngr->FreeBuffer();
			}
		}
	

		//m_pCapSmDbFile->Free(m_pXSmMemBufferMngr);

		//数据

		//索引

		//一级索引
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("写数据库错误"));
	}

	m_bIsNowWritting = FALSE;
}


void CSmDbWriteThread::OnTimer(WPARAM wParam, LPARAM lParam)
{
	OnWriteSmDb(0, 0);
}
