// D:\WorkPM\Source\PMTest\Module\ItemTestUI\MyMFCTabCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AtsUiTabCtrl.h"
#include "..\XLanguageResourceAts_AutoTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyMFCTabCtrl

IMPLEMENT_DYNAMIC(CAtsUiTabCtrl, CMFCTabCtrl)

CAtsUiTabCtrl::CAtsUiTabCtrl()
{
	m_pMainFrame = NULL;
	m_pWndInfo = NULL;

	//2020-12-23  lijunqing
	m_pMacroTestLog = NULL;
	m_pPpEngineLog = NULL;	

}

CAtsUiTabCtrl::~CAtsUiTabCtrl()
{
	if (m_pWndInfo != NULL)
	{
		delete m_pWndInfo;
		m_pWndInfo = NULL;
	}

	if (m_pMacroTestLog != NULL)
	{
		delete m_pMacroTestLog;
		m_pMacroTestLog = NULL;
	}

	if (m_pPpEngineLog != NULL)
	{
		delete m_pPpEngineLog;
		m_pPpEngineLog = NULL;
	}
}

void CAtsUiTabCtrl::EmptyGridInlegibleTestItem()
{
	m_gridInlegibleTestItem.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CAtsUiTabCtrl, CMFCTabCtrl)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMyMFCTabCtrl ��Ϣ�������

int CAtsUiTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
// 	m_btnTest.Create(_T(""),WS_CHILD|BS_OWNERDRAW|WS_VISIBLE, CRect(0,0,0,0), this, 1001);
// 	m_btnTest.CreateTitleTip();
// 	m_btnTest.SetOwner(this);
// 
// 	AddTab(&m_btnTest,_T("����״̬"),(UINT)0);
	m_Font.CreateStockObject(DEFAULT_GUI_FONT);

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_VSCROLL 
		| ES_AUTOVSCROLL | ES_READONLY | ES_MULTILINE;

	m_pWndInfo = new CAtsUiOutputLog(TRUE);
	m_pWndInfo->Create(dwStyle,rectDummy,this,1002);
	AddTab(m_pWndInfo,g_sLangTxt_PromptMessage/*_T("��ʾ��Ϣ")*/,(UINT)1);
	m_pWndInfo->SetFont(g_pGlobalFont12);
	
	m_gridInlegibleTestItem.CreateGrid(this, rectDummy, 1003, m_pMainFrame);
	AddTab(&m_gridInlegibleTestItem,g_sLangTxt_UnquaItem/*_T("���ϸ���Ŀ")*/,(UINT)1);
	m_gridInlegibleTestItem.SetFont(g_pGlobalFont12);

	//2020-12-23  lijunqing
	m_pMacroTestLog = new CAtsUiOutputLog(FALSE);
	m_pMacroTestLog->Create(dwStyle,rectDummy,this,1004);
	AddTab(m_pMacroTestLog,_T("��������ʾ��Ϣ"),(UINT)1);
	m_pMacroTestLog->SetFont(g_pGlobalFont12);
	
	m_pPpEngineLog = new CAtsUiOutputLog(FALSE);
	m_pPpEngineLog->Create(dwStyle,rectDummy,this,1005);
	AddTab(m_pPpEngineLog,_T("ͨѶ��̨��ʾ��Ϣ"),(UINT)1);
	m_pPpEngineLog->SetFont(g_pGlobalFont12);

	g_theSmartTestBaseApp->m_hMacroTestLogWnd = (unsigned long)m_pMacroTestLog->m_hWnd;
	g_theSmartTestBaseApp->m_hPpEngineLogWnd = (unsigned long)m_pPpEngineLog->m_hWnd;

	return 0;
}
// 
// void CAtsUiTabCtrl::UpdateTestProjectSpy()
// {
// 	m_btnTest.Invalidate(FALSE);
// 	m_btnTest._OnSize();
// }

void CAtsUiTabCtrl::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CMFCTabCtrl::OnClose();
}

