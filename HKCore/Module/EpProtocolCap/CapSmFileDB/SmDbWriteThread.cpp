// SmDbWriteThread.cpp : implementation file
//

#include "stdafx.h"
#include "SmDbWriteThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmDbWriteThread

IMPLEMENT_DYNCREATE(CSmDbWriteThread, CWinThread)


long CSmDbWriteThread::g_nSmDbWriteThreadRefCount = 0;

CSmDbWriteThread::CSmDbWriteThread()
{
	m_bIsNowWritting = FALSE;
	m_bIsInWrittingLastData = FALSE;
	m_pCapSmDb = NULL;
	m_nExitState = 0;
}

CSmDbWriteThread::~CSmDbWriteThread()
{
	m_listBufferMngr.RemoveAll();
}

void CSmDbWriteThread::InitThread(CEpCapThreadMngr *pCapThreadMngr, CCapSmDb *pCapSmDb)
{
	m_listBufferMngr.RemoveAll();
	POS pos = pCapThreadMngr->GetHeadPosition();
	CEpCapThreadBase *pCapThread = NULL;
	m_pCapSmDb = pCapSmDb;

	while (pos != NULL)
	{
		pCapThread = (CEpCapThreadBase *)pCapThreadMngr->GetNext(pos);
		m_listBufferMngr.AddTail(pCapThread->GetCapCycleMemBufferMngr());
	}
}

void CSmDbWriteThread::FreeThread()
{
	CAutoSimpleLock oLock(g_oBufferCriticSection);
	m_listBufferMngr.RemoveAll();
}

BOOL CSmDbWriteThread::InitInstance()
{
	//初始化COM环境
	::CoInitialize(NULL);

	g_nSmDbWriteThreadRefCount++;
	
	return TRUE;
}

int CSmDbWriteThread::ExitInstance()
{
	::CoUninitialize();
	int iRet = CWinThread::ExitInstance();
	
	m_listBufferMngr.RemoveAll();
	g_nSmDbWriteThreadRefCount--;
	return iRet;
}

BEGIN_MESSAGE_MAP(CSmDbWriteThread, CWinThread)
	//{{AFX_MSG_MAP(CSmDbWriteThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP

	ON_THREAD_MESSAGE(WM_CAP_WRITE_SMDB, CSmDbWriteThread::OnWriteSmDb)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmDbWriteThread message handlers

BOOL CSmDbWriteThread::CanWriteNow()
{
	if (m_bIsNowWritting)
	{
		return FALSE;
	}
	
	BOOL bCanWrite = FALSE;

	CCapCycleMemBufferMngr *pBufferMngr = NULL;
	POS pos = m_listBufferMngr.GetHeadPosition();

	while (pos != NULL)
	{
		pBufferMngr = m_listBufferMngr.GetNext(pos);
		
		if (pBufferMngr->m_dwCurrBufferLength >= SMDB_WRITE_SIZE_MIN)
		{
			bCanWrite = TRUE;
			break;
		}
	}

	return bCanWrite;
}

void CSmDbWriteThread::WriteSmDB()
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

BOOL CSmDbWriteThread::WriteSmDBEx()
{
	CCapCycleMemBufferMngr *pBufferMngr = NULL;
	POS pos = m_listBufferMngr.GetHeadPosition();
	BOOL bHasNeedWrite;

	while (pos != NULL)
	{
		pBufferMngr = m_listBufferMngr.GetNext(pos);
		
		if (pBufferMngr->GetCount() > 0)
		{
			bHasNeedWrite = TRUE;
			break;
		}
	}

	if (bHasNeedWrite)
	{
		PostThreadMessage(WM_CAP_WRITE_SMDB, 1, 1);
	}

	return bHasNeedWrite;
}

void CSmDbWriteThread::OnWriteSmDb(WPARAM wParam, LPARAM lParam)
{
//	CAutoSimpleLock oLock(g_oBufferCriticSection);

	DWORD dwBeginTick = ::GetTickCount();
// 	CLogPrint::LogString(LOGLEVEL_TRACE, _T("写数据库开始>>>>>>"));

	g_nEpCapWriteCounter = 0;
	Ep_SetInWriteEpCapState();

	if (m_pCapSmDb == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("错误，SmDB错误......"));
		return;
	}

	if (m_bIsNowWritting)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("错误，正在写数据库......"));
		return;
	}

	try
	{
		m_bIsNowWritting = TRUE;
		ASSERT (m_pCapSmDb != NULL);

		CCapCycleMemBufferMngr *pBufferMngr = NULL;
		POS pos = m_listBufferMngr.GetHeadPosition();
		BOOL bWrite = FALSE;

		CCapCycleMemBufferMngr oMngr;

		while (pos != NULL)
		{
			pBufferMngr = m_listBufferMngr.GetNext(pos);
			oMngr.RemoveAll();
			InitCCapCycleMemBufferMngrForWrite(pBufferMngr, &oMngr);
			bWrite = TRUE;
			m_pCapSmDb->Write(&oMngr);
			pBufferMngr->SetWriteFinished(TRUE);
		}

		oMngr.RemoveAll();

// 		if (bWrite)
// 		{
// 			m_pCapSmDb->UpdateIndex0File();
// 		}

		pos = m_listBufferMngr.GetHeadPosition();

		while (pos != NULL)
		{
			pBufferMngr = m_listBufferMngr.GetNext(pos);
			pBufferMngr->SetWriteFinished(TRUE);
		}

		m_bIsNowWritting = FALSE;
		Ep_FinishInWriteEpCapState();
		DWORD dwEnd = ::GetTickCount();
		//CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("写数据库完成,用时%d毫秒"), dwEnd - dwBeginTick);	
	}
	catch (...)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("写数据库错误"));
	}
}


void CSmDbWriteThread::InitCCapCycleMemBufferMngrForWrite(CCapCycleMemBufferMngr *pSrc, CCapCycleMemBufferMngr*pDest)
{	
	POS posWriteBegin = NULL;
	POS posWriteEnd = NULL;
	posWriteBegin = pSrc->GetHeadPosition();
	posWriteEnd = pSrc->GetTailPosition();

	if (posWriteEnd != NULL)
	{
		pSrc->GetPrev(posWriteEnd);
	}

	if (posWriteBegin == NULL || posWriteEnd == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("1,InitCCapCycleMemBufferMngrForWrite：没有数据"));
		return;
	}

	CCapCycleMemBuffer *pBuffer = (CCapCycleMemBuffer*)pSrc->GetAt(posWriteEnd);

	while (TRUE)
	{
		if (posWriteEnd == NULL)
		{
			break;
		}

		if (pBuffer->Ebs_BeParsed())
		{
			break;
		}

		pSrc->GetPrev(posWriteEnd);
		pBuffer = (CCapCycleMemBuffer*)pSrc->GetAt(posWriteEnd);
	}

	POS pos = posWriteBegin;
	
	while (pos != posWriteEnd)
	{
		if (pos == NULL)
		{
			break;
		}

		pBuffer = (CCapCycleMemBuffer*)pSrc->GetAt(pos);

		if (pBuffer->Is_RECORD_HASRECORD())
		{
			pDest->AddTail(pBuffer);
		}
		else
		{
			pBuffer->SetState(EBS_HASWRITE);
		}

		pSrc->GetNext(pos);
	}

	if (pDest->GetCount() == 0)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("2,InitCCapCycleMemBufferMngrForWrite：没有数据"));
	}
}

