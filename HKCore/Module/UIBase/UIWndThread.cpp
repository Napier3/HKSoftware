// UIWndThread.cpp : implementation file
//

#include "stdafx.h"
#include "UIWndThread.h"
#include "UILuaScript.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUIWndThread
long CUIWndThread::g_nCUIWndThreadRefCount = 0;
CUIWndThread* CUIWndThread::g_pUIWndThread = NULL;
CWnd* CUIWndThread::g_pWnd_WM_COMMAND = NULL;

CUIWndPage* CUIWndThread::FindPage(const char *pszPage)
{
	CString strPage;
	strPage = pszPage;

	return FindPage(strPage);
}

BOOL CUIWndThread::ShowPage(LPCTSTR pszPageID, long nShow)
{
	CString strPage;
	strPage = pszPageID;
	return ShowPage(strPage, nShow);
}

BOOL CUIWndThread::ClosePage(LPCTSTR pszPageID)
{
	CString strPage;
	strPage = pszPageID;
	return ClosePage(strPage);
}

CUIWndPage* CUIWndThread::FindPage(const CString &strPage)
{
	ASSERT (CUIWndThread::g_pUIWndThread != NULL);

	if (CUIWndThread::g_pUIWndThread == NULL)
	{
		return NULL;
	}

	CUIWndPage *pPage = (CUIWndPage*)CUIWndThread::g_pUIWndThread->m_pUIWndPages->FindByID(strPage);

	return pPage;
}

BOOL CUIWndThread::ShowPage(const CString &strPageID, long nShow)
{
	return CUIWndThread::g_pUIWndThread->m_pUIWndPages->ShowPage(strPageID, nShow);
}

BOOL CUIWndThread::ClosePage(const CString &strPageID)
{
	return CUIWndThread::g_pUIWndThread->m_pUIWndPages->ClosePage(strPageID);
}

void CUIWndThread::PostProcMainWndMsg(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT (g_pUIWndThread != NULL);

	if (g_pUIWndThread == NULL)
	{
		return;
	}

	ASSERT(g_pUIWndThread->m_pProcMainWnd != NULL);

	if(g_pUIWndThread->m_pProcMainWnd == NULL)
	{
		return;
	}
	
	g_pUIWndThread->m_pProcMainWnd->PostMessage(nMsg, wParam, lParam);
}

IMPLEMENT_DYNCREATE(CUIWndThread, CWinThread)

CUIWndPage* UIS_GetUIPage(const char* pszPageID)
{
	return CUIWndThread::FindPage(pszPageID);
}

CUIWndThread::CUIWndThread()
{
	m_pUIWndPages = NULL;
// 	m_pSystemMessageMngr = NULL;
	m_nCanDeletePageRef = 0;
	m_pProcMainWnd = NULL;

	CUIBaseXmlRWKeys::Create();
}

CUIWndThread::~CUIWndThread()
{
	CUIBaseXmlRWKeys::Release();
}

BOOL CUIWndThread::InitInstance()
{
	//初始化COM环境,因为m_pUIWndPages读取xml,这里不初始化会出错
	::CoInitialize(NULL);
	g_nCUIWndThreadRefCount++;

	//初始化脚本
	UILuaScript::UI_InitLua();

	
	//初始化系统消息集合
// 	m_pSystemMessageMngr = CSystemMessageMngr::CreateSystemMessageMngr();	
// 	m_pSystemMessageMngr->ReadSystemMessageXmlFile();
	
	//初始化页面集合
	m_pUIWndPages = new CUIWndMain();
	m_pUIWndPages->Load(_T("Main.xml"));	
	
	return TRUE;
}

int CUIWndThread::ExitInstance()
{
	if (m_pUIWndPages != NULL)
	{
		delete m_pUIWndPages;
		m_pUIWndPages = NULL;
	}
	
// 	if (m_pSystemMessageMngr != NULL)
// 	{
// 		m_pSystemMessageMngr->Release();
// 		m_pSystemMessageMngr = NULL;
// 	}

	UILuaScript::UI_CloseLua();

	::CoUninitialize();
	
	int iRet = CWinThread::ExitInstance();
	g_nCUIWndThreadRefCount--;

	return iRet;
}

BEGIN_MESSAGE_MAP(CUIWndThread, CWinThread)
	//{{AFX_MSG_MAP(CUIWndThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
// 	ON_MESSAGE(WM_DELETE_PAGE, OnDeletePage)
// 	ON_MESSAGE(WM_RECORD, OnRecord)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUIWndThread message handlers

void CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
// 	CMR1200BaseApp *pApp = (CMR1200BaseApp*)AfxGetApp();
// 	KillTimer(NULL, idEvent);
// 
// 	if (idEvent == pApp->m_pUIWndThread->m_nDeletePageTimerID)
// 	{
// 		if (pApp->m_pUIWndThread->m_pDeletePage != NULL)
// {
// 			pApp->m_pUIWndThread->m_pDeletePage->Destroy();
// 			pApp->m_pUIWndThread->m_pDeletePage = NULL;
// 		}
// 	}
// 	else
// 	{
// 	}
// 
// 	pApp->m_pUIWndThread->FireAdStartButtonMsg();
// 	pApp->SetCanFireSysMessage(TRUE);
}
		
void CUIWndThread::FireAdStartButtonMsg()
{
// 		CMR1200BaseApp *pApp = (CMR1200BaseApp*)AfxGetApp();
// 
// 		if (pApp->IsRecordDataModeOscillograph())
// 		{
// 			if (pApp->m_strAdStartButtonID.GetLength() > 1)
// 			{
// 			//if (pApp->CanFireSysMessage())
// 				{
// 					CUIWindowBase *pUIWnd = m_pUIWndPages->m_pActivePage->FindWindowByID(pApp->m_strAdStartButtonID);
// 					
// 					if (pUIWnd != NULL)
// 					{
// 						CMessageImp *pClick = pUIWnd->FindByMsgImpID(CUIWndButton::g_pszKeySysMsgClick);
// 						
// 						if (pClick != NULL)
// 						{
// 							pClick->Run();
// 							
// 						}
// 					}
// 				}
// 				
// 				pApp->m_strAdStartButtonID = "";
// 			}
// 		}
// 
// 	pApp->SetCanFireSysMessage(TRUE);
}

LRESULT CUIWndThread::OnDeletePage(WPARAM wParam, LPARAM lParam)
{
// 	CMR1200BaseApp *pApp = (CMR1200BaseApp*)AfxGetApp();
// 	pApp->SetCanFireSysMessage(FALSE);
// 
// 	CUIWndPage *pPage = (CUIWndPage*)wParam;
// 	if ( (stricmp(pPage->m_strID, "PageWaveAnalyse") == 0) || (pApp->m_strAdStartButtonID.GetLength() > 1))
// 	{
// 		if (::GetTickCount() - m_dwAnalyseWndCreate < 3000)
// 		{
// 			m_pDeletePage = pPage;
// 			m_nDeletePageTimerID = SetTimer(NULL, 1001, 2000, TimerProc);	
// 		}
// 		else
// 		{
// 			pPage->Destroy();
// 			FireAdStartButtonMsg();
// 		}
// 	}
// 	else
// 	{
// 		pPage->Destroy();
// 		pApp->SetCanFireSysMessage(TRUE);
// 	}
	
	return 0;	
}

LRESULT CUIWndThread::OnRecord(WPARAM wParam, LPARAM lParam)
{
// 	if (wParam == 0 && lParam == 0)
// 	{
// 		m_pUIWndPages->OnRecordBegin();
// 	}
// 
// 	if (wParam == 1 && lParam == 1)
// 	{
// 		m_pUIWndPages->OnRecordFinish();
// 	}
	
	return 0;	
}

// void CUIWndThread::WaitForExit()
// {
// 	DWORD dwBegin = ::GetTickCount();
// 
// 	while (g_nCUIWndThreadRefCount > 0)
// 	{
// 		DWORD dwEnd = ::GetTickCount();
// 
// 		if (dwEnd - dwBegin > 3000) 
// 		{
// 			break;
// 		}
// 	}
// }

LRESULT CUIWndThread::OnPageSysMessagees(WPARAM wParam, LPARAM lParam)
{
	long nImpCount = 0;
	long nRunCount = 0;
//	m_pUIWndPages->OnSystemMessage(m_pSystemMessageMngr->GetSystemMessages(), nImpCount, nRunCount);		
	return 0;
}

BOOL CUIWndThread::PreTranslateMessage(MSG* pMsg) 
{
//	CMR1200BaseApp *pApp = (CMR1200BaseApp *)AfxGetApp();
	BOOL bUse = FALSE;

	if (pMsg->message == WM_COMMAND)
	{
// 		if (g_pWnd_WM_COMMAND != NULL)
// 		{
// 			if (g_pWnd_WM_COMMAND->m_hWnd == pMsg->hwnd)
// 			{
// 				AfxCallWndProc(g_pWnd_WM_COMMAND, pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam);
// 				//g_pWnd_WM_COMMAND->WindowProc(pMsg->message, pMsg->wParam, pMsg->lParam);
// 			}
// 			else
// 			{
// 				CWnd *pWnd = CWnd::FromHandle(pMsg->hwnd);
// 				AfxCallWndProc(g_pWnd_WM_COMMAND, pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam);
// 			}
// 		}
// 		else
// 		{
// 			CWnd *pWnd = CWnd::FromHandle(pMsg->hwnd);
// 			AfxCallWndProc(pWnd, pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam);
// 		}
	}
	
// 	if (::GetTickCount() - pMsg->time > 50)
// 	{
// 		return CWinThread::PreTranslateMessage(pMsg);
// 	}
// 
// 	//如果是远程控制状态，则不响应任何消息
// 	if (pApp->GetRemoteCtrlState())
// 	{
// 		return FALSE;
// 	}
// 
// 	if ( (pMsg->message == WM_KEYDOWN) || (pMsg->message == WM_KEYUP) 
// 		|| (pMsg->message == WM_SYSKEYDOWN) || (pMsg->message == WM_SYSKEYUP))
// 	{
// 		if (pMsg->wParam == VK_END)
// 		{
// 			SHORT nState = GetKeyState(VK_CONTROL);
// 			
// 			if ( (nState & 0x8000) > 0)
// 			{
// 				///////////////////////////////fdp add 2010.5.5,在发送WM_QUIT消息前释放资源能有效避免内存泄漏
// 				/////////////////////////////////////////////
// 
// 				//AfxGetApp()->PostThreadMessage(WM_QUIT, 0, 0);
// 				AfxGetMainWnd()->PostMessage(WM_EXITINSTANCE, 0, 0);
// 
// 				return TRUE;
// 			}
// 			else
// 			{
// 				bUse = TranslateMessage(pMsg);
// 			}
// 		}
// 		else
// 		{
// 			bUse = TranslateMessage(pMsg);
// 		}
// 	}
// 	
// 	switch(pMsg->message) 
// 	{ 
// 	case   WM_GETDLGCODE: 
// 		{
// 			return  DLGC_WANTARROWS; 
// 		}
// 		break;
// 	case   WM_KEYDOWN: 
// 		{
// 			switch(pMsg->wParam) 
// 			{ 
// 			case   VK_UP: 
// 			case   VK_DOWN: 
// 			case   VK_LEFT: 
// 			case   VK_RIGHT: 
// 				MessageBeep(0); 
// 				return 0; 
// 			} 
// 		}
// 		break; 	
// 		default:
// 			break;
// 	}
// 
	if(!bUse)
	{
		return CWinThread::PreTranslateMessage(pMsg);		
	}
	else
	{
		return TRUE;
	}
}

BOOL CUIWndThread::TranslateMessage(MSG* pMsg)
{
//	CMR1200BaseApp *pApp = (CMR1200BaseApp *)AfxGetApp();
	long nImpCount = 0;
	long nRunCount = 0;

// 	if (pApp->CanFireSysMessage())
// 	{//是否可以处理消息
// 		m_pSystemMessageMngr->TranslateMessage(pMsg);//将按键消息翻译成程序定义的案件消息，并添加入消息队列
// 		
// 		if (m_pUIWndPages != NULL && m_pSystemMessageMngr->HasSysMsgNeedPost())
// 		{				
// 			m_pUIWndPages->OnSystemMessage(m_pSystemMessageMngr->GetSystemMessages(), nImpCount, nRunCount);//响应消息			
// 		}
// 	}
// 	else
// 	{
// 		nRunCount = 1;
// 	}
// 
	return (nRunCount > 0);
}
