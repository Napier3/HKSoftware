
#include "stdafx.h"
#include "AtsUiOutputWnd.h"
#include "..\..\Module\EpotoInterface\EpotoInterface.h"
#include "..\XLanguageResourceAts_AutoTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

CAtsUiOutputWnd::CAtsUiOutputWnd()
{
}

CAtsUiOutputWnd::~CAtsUiOutputWnd()
{
}

void CAtsUiOutputWnd::AdjustLog(HWND hLogParent)
{
	CMFCTabCtrl *pTabs = (CMFCTabCtrl*)CWnd::FromHandle(hLogParent);
	m_wndTabs.AutoDestroyWindow(FALSE);
	m_wndTabs.RemoveTab(0);
	m_wndTabs.RemoveTab(0);
	m_wndTabs.RemoveTab(0);
	m_wndTabs.RemoveTab(0);

	pTabs->AddTab(m_wndTabs.m_pWndInfo,g_sLangTxt_PromptMessage/*_T("提示信息")*/,(UINT)1);
	pTabs->AddTab(&m_wndTabs.m_gridInlegibleTestItem,g_sLangTxt_UnquaItem/*_T("不合格项目")*/,(UINT)1);
	pTabs->AddTab(m_wndTabs.m_pPpEngineLog,_T("通讯后台提示信息"),(UINT)1);
	pTabs->AddTab(m_wndTabs.m_pMacroTestLog,_T("测试仪提示信息"),(UINT)1);
}

BEGIN_MESSAGE_MAP(CAtsUiOutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_CLOSE()
//	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

void CAtsUiOutputWnd::OutPutString(const CString& str)
{
	m_wndTabs.SetActiveTab(1);
}

void CAtsUiOutputWnd::AddOutPutString(const CString &str)
{
	m_wndTabs.SetActiveTab(1);
}

int CAtsUiOutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font.CreateStockObject(DEFAULT_GUI_FONT);

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建选项卡窗口:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("未能创建输出选项卡窗口\n");
		return -1;      // 未能创建
	}

	// 创建输出窗格:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	CString strTabName;

	// 使用一些虚拟文本填写输出选项卡(无需复杂数据)
	FillBuildWindow();
	FillDebugWindow();
	FillFindWindow();

	return 0;
}

void CAtsUiOutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// 选项卡控件应覆盖整个工作区:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CAtsUiOutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&m_Font);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

void CAtsUiOutputWnd::FillBuildWindow()
{
// #ifndef AUTOTEST_DEMO
// 	char pString[MAX_PATH];
// 	long nStringLen = 0;
// 
// 	if (Encrypt_IsEncrypt(FETUREID_AUTOTEST))
// 	{
// 		Pp_GetEpotoString(0X00F00002, pString, nStringLen);
// 		CLogPrint::LogString(XLOGLEVEL_INFOR, CString(pString));
// 
// 		Pp_GetEpotoString(0X00F00003, pString, nStringLen);
// 		CLogPrint::LogString(XLOGLEVEL_INFOR, CString(pString));
// 	}
// 	else
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("你使用的系统没有授权"));
// 	}
// #endif

}

void CAtsUiOutputWnd::FillDebugWindow()
{
}

void CAtsUiOutputWnd::FillFindWindow()
{
}

void CAtsUiOutputWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDockablePane::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
}

void CAtsUiOutputWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CDockablePane::OnLButtonDblClk(nFlags, point);
}

void CAtsUiOutputWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDockablePane::OnMouseMove(nFlags, point);
}

void CAtsUiOutputWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDockablePane::OnRButtonDown(nFlags, point);
}

void CAtsUiOutputWnd::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDockablePane::OnClose();
}
