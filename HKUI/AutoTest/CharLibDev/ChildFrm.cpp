// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "CharLibDev.h"

#include "ChildFrm.h"
#include "CharEditDlg.h"
#include "MainFrm.h"
#include "XLanguageResourceAts_CharLibDev.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
	ON_COMMAND(ID_CHAROPTR_EDIT, &CChildFrame::OnCharoptrEdit)
	ON_UPDATE_COMMAND_UI(ID_CHAROPTR_EDIT, &CChildFrame::OnUpdateCharoptrEdit)
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	m_pCurrCharTemp = NULL;
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序

void CChildFrame::OnClose()
{
	theApp.CloseCharTempFrame(this);

	CMDIChildWndEx::OnClose();
}

void CChildFrame::OnCharoptrEdit()
{
	CCharEditDlg dlg;
	dlg.m_strTitle = g_sLangTxt_NewCharCurve/*_T("新建特性曲线")*/;
	dlg.m_pCharTemp = m_pCurrCharTemp;
	dlg.m_pCurrFolder = (CCharacterFolder *)m_pCurrCharTemp->GetParent();

	if (dlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrame = (CMainFrame*)theApp.m_pMainWnd;
		m_pCurrCharTemp->m_strName = dlg.m_strName;
		m_pCurrCharTemp->m_strID   = dlg.m_strID;
		m_pCurrCharTemp->m_strAxis = dlg.m_strAxis;
		m_pCurrCharTemp->m_strTestLineMode = dlg.m_strTestLineMode;
		m_pCurrCharTemp->m_strXMin = dlg.m_strXMin;
		m_pCurrCharTemp->m_strXMax = dlg.m_strXMax;
		m_pCurrCharTemp->m_strYMin = dlg.m_strYMin;
		m_pCurrCharTemp->m_strYMax = dlg.m_strYMax;

		pMainFrame->UpdateCharTemp(m_pCurrCharTemp);
		CView *pView = GetActiveView();
		CDocument *pDoc = pView->GetDocument();
		pDoc->SetTitle(m_pCurrCharTemp->m_strName);
	}
	
}

void CChildFrame::OnUpdateCharoptrEdit(CCmdUI *pCmdUI)
{
	
}
