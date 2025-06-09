// XDocFileReadThread.cpp : 实现文件
//

#include "stdafx.h"
#include "XDocFileReadThread.h"

CXDocFileReadThread* CXDocFileReadThread::g_theDocFileReadThread = NULL;

void CXDocFileReadThread::AddFileRead(const char*strFile)
{
	CAutoSimpleLock oOlock(g_theDocFileReadThread->m_oCriticSection);

	XDOC_FILE_READ_MNGR *pFileMngr = &g_theDocFileReadThread->m_oXDocFileRead;
	strcpy(pFileMngr->m_pszFileArray[pFileMngr->nWriteIndex], strFile);

	long nWriteIndex = pFileMngr->nWriteIndex;
	pFileMngr->nWriteIndex++;

	if (pFileMngr->nWriteIndex >= XDOC_FILE_READ_MAX_FILE)
	{
		pFileMngr->nWriteIndex = 0;
		pFileMngr->nMngrCount = XDOC_FILE_READ_MAX_FILE;
	}
	else
	{
		pFileMngr->nMngrCount = pFileMngr->nWriteIndex;
	}

	PostXDocFilMsg(XDOC_FILE_OPTR_ADD, nWriteIndex);
}

void CXDocFileReadThread::AddFileRead(const CString &strFile)
{
	char *pszFile = NULL;
	CString_to_char(strFile, &pszFile);
	AddFileRead(pszFile);
	delete pszFile;
}

CXDocFileReadThread* CXDocFileReadThread::CreateXDocFileReadThread(CWnd *pMsgRcv, CThreadProgressInterface *pThreadProgressInterface)
{
	CXDocFileReadThread *pThread = (CXDocFileReadThread*)AfxBeginThread(RUNTIME_CLASS(CXDocFileReadThread)
		, THREAD_PRIORITY_HIGHEST, 0, CREATE_SUSPENDED);
	pThread->m_pMsgRcvWnd = pMsgRcv;
	pThread->m_pThreadProgressInterface = pThreadProgressInterface;
	pThread->ResumeThread();

	return pThread;
}

XDOC_FILE_READ_MNGR* CXDocFileReadThread::GetXDocFileMngr()
{
	XDOC_FILE_READ_MNGR *pFileMngr = &g_theDocFileReadThread->m_oXDocFileRead;
	return pFileMngr;
}

void CXDocFileReadThread::PostXDocFilMsg(WPARAM wPara,LPARAM lPara)
{
	if (g_theDocFileReadThread->m_pMsgRcvWnd != NULL)
	{
		g_theDocFileReadThread->m_pMsgRcvWnd->PostMessage(WM_XDOC_FILE_UPDATE, wPara, lPara);
	}
}

void CXDocFileReadThread::ShowWordApp(long nShow)
{
	g_theDocFileReadThread->m_nWordShow = nShow;
	g_theDocFileReadThread->m_nWordShowStateChanged = 1;
}

void CXDocFileReadThread::SetDocProg(const CString &strDocProg)
{
	g_theDocFileReadThread->m_strDocProg = strDocProg;
	g_theDocFileReadThread->m_strDocProg.MakeUpper();
	g_theDocFileReadThread->m_nDocProgChanged = 1;
}

// CXDocFileReadThread

IMPLEMENT_DYNCREATE(CXDocFileReadThread, CWinThread)

CXDocFileReadThread::CXDocFileReadThread()
{
	m_strDocProg = XDOC_PROG_ID_WPS;
	m_nDocProgChanged = 0;

	m_nWordShowStateChanged = 0;
	m_nWordShow = 1;

	m_pThreadProgressInterface = NULL;
	m_pMsgRcvWnd = NULL;
	m_pDocXRead_Prog = NULL;
	g_theDocFileReadThread = this;
	ZeroMemory(&m_oXDocFileRead, sizeof(m_oXDocFileRead));
}

CXDocFileReadThread::~CXDocFileReadThread()
{
}

void CXDocFileReadThread::CreateDocProg()
{
	m_strDocProg.MakeUpper();

	if (m_strDocProg == XDOC_PROG_ID_WORD)
	{
		m_pDocXRead_Prog = new CDocXRead_Word();
		m_pDocXRead_Prog->GetWordApp(m_nWordShow);
	}
	else if (m_strDocProg == XDOC_PROG_ID_WPS)
	{	
		m_pDocXRead_Prog = new CDocXRead_WPS();
		m_pDocXRead_Prog->GetWordApp(m_nWordShow);
	}
	else if (m_strDocProg == XDOC_PROG_ID_XML)
	{	
		g_nDocToXmlFormat = _PUGI_XML_TYPE_;
	}
	else
	{
		g_nDocToXmlFormat = _JSON_TYPE_;
	}

	m_nDocProgChanged = 0;
}

void CXDocFileReadThread::CloseDocProg()
{
	if ((m_strDocProg != XDOC_PROG_ID_WORD) && (m_strDocProg != XDOC_PROG_ID_WPS))
	{
		return;
	}

	if (m_pDocXRead_Prog != NULL)
	{
		m_pDocXRead_Prog->QuitApp();
		delete m_pDocXRead_Prog;
		m_pDocXRead_Prog = NULL;
	}
}

BOOL CXDocFileReadThread::InitInstance()
{
	::CoInitialize(NULL);

	CreateDocProg();

	return TRUE;
}

int CXDocFileReadThread::ExitInstance()
{
	m_pDocXRead_Prog->QuitApp();
	delete m_pDocXRead_Prog;
	::CoUninitialize();

	return CWinThread::ExitInstance();
}


BEGIN_MESSAGE_MAP(CXDocFileReadThread, CWinThread)
END_MESSAGE_MAP()


// CXDocFileReadThread 消息处理程序
int CXDocFileReadThread::Run()
{
	ASSERT_VALID(this);
	_AFX_THREAD_STATE* pState = AfxGetThreadState();

	// for tracking the idle time state
	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;

	// acquire and dispatch messages until a WM_QUIT message is received.
	for (;;)
	{
		Sleep(50);

		if (m_nWordShowStateChanged)
		{
			m_nWordShowStateChanged = 0;
			m_pDocXRead_Prog->ShowApp(m_nWordShow);

		}

		if (m_nDocProgChanged)
		{
			CloseDocProg();
			CreateDocProg();
		}

		ReadFile();		
	}
}

void CXDocFileReadThread::ReadFile()
{
	CAutoSimpleLock oLock(g_theDocFileReadThread->m_oCriticSection);

	XDOC_FILE_READ_MNGR *pFileMngr = &g_theDocFileReadThread->m_oXDocFileRead;

	if (pFileMngr->nReadIndex == pFileMngr->nWriteIndex)
	{
		oLock.Free();
		return;
	}

	CString strFile;
	long nReadIndex = pFileMngr->nReadIndex;
	strFile = pFileMngr->m_pszFileArray[pFileMngr->nReadIndex];

	pFileMngr->nReadIndex++;

	if (pFileMngr->nReadIndex >= XDOC_FILE_READ_MAX_FILE)
	{
		pFileMngr->nReadIndex = 0;
	}

	oLock.Free();

	PostXDocFilMsg(XDOC_FILE_OPTR_BEGIN_READ, nReadIndex);
	m_pDocXRead_Prog->SetProgressInterface(m_pThreadProgressInterface);
	m_pDocXRead_Prog->DocToXml(strFile);
	PostXDocFilMsg(XDOC_FILE_OPTR_FINISH_READ, nReadIndex);
}

