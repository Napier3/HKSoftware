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

// StateToolView.cpp : CStateToolView 类的实现
//

#include "stdafx.h"
#include "Iec61850Config.h"

#include "StateToolDoc.h"
#include "StateToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStateToolView

IMPLEMENT_DYNCREATE(CStateToolView, CFormView)

BEGIN_MESSAGE_MAP(CStateToolView, CFormView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CStateToolView 构造/析构

CStateToolView::CStateToolView()
	: CFormView(CStateToolView::IDD)
{
	// TODO: 在此处添加构造代码
	CGbMacroUILibMngr::Create();
	m_pGbMacroUI = NULL;
}

CStateToolView::~CStateToolView()
{
	CGbMacroUILibMngr::Release();
}

void CStateToolView::CreateGbUI()
{
	CString strUiDLL = _T("GbUIStateSmv.dll");

	CGbMacroUI *pGbMacroUI = CGbMacroUILibMngr::CreateGbMacroUI(strUiDLL, NULL);

	if (pGbMacroUI != NULL)
	{
		m_pGbMacroUI = pGbMacroUI;
		m_pGbMacroUI->GbUICreate(NULL, NULL, this, NULL);
		m_pGbMacroUI->GbUIShow(this);
	}
	else
	{
		m_pGbMacroUI = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("缺少界面动态链接库：%s"), strUiDLL);
	}
}

void CStateToolView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CStateToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CStateToolView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//ResizeParentToFit();
	CreateGbUI();
}

void CStateToolView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CStateToolView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CStateToolView 诊断

#ifdef _DEBUG
void CStateToolView::AssertValid() const
{
	CFormView::AssertValid();
}

void CStateToolView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CStateToolDoc* CStateToolView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStateToolDoc)));
	return (CStateToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CStateToolView 消息处理程序

void CStateToolView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (m_pGbMacroUI == NULL)
	{
		return;
	}

	CWnd *pWndGbUI = m_pGbMacroUI->GetWndGbUI();

	if (pWndGbUI != NULL)
	{
		pWndGbUI->MoveWindow(0, 0, cx, cy, TRUE);
	}
}

int CStateToolView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

// 	//获得窗口的创建信息指针
// 	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;
// 
// 	m_tabPara.Create(CMFCTabCtrl::STYLE_3D_ROUNDED ,CRect(0, 0, 0, 0), this, 1000, CMFCTabCtrl::LOCATION_TOP);
// 
// 	m_pViewSmvMain = new CIecCfgSmvViewMain();
// 	if (m_pViewSmvMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
// 		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST, pContext))
// 	{
// 		m_tabPara.AddTab(m_pViewSmvMain, _T("SMV配置"));
// 	}
// 
// 	m_pViewGinMain = new CIecCfgGinViewMain();
// 	if (m_pViewGinMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
// 		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+1, pContext))
// 	{
// 		m_tabPara.AddTab(m_pViewGinMain, _T("GOOSE订阅配置"));
// 	}
// 
// 	m_pViewGoutMain = new CIecCfgGoutViewMain();
// 	if (m_pViewGoutMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
// 		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+2, pContext))
// 	{
// 		m_tabPara.AddTab(m_pViewGoutMain, _T("GOOSE发布配置"));
// 	}

	return 0;
}

void CStateToolView::OnDestroy()
{
// 	m_tabPara.AutoDestroyWindow(FALSE);
// 	m_tabPara.RemoveAllTabs();

	CFormView::OnDestroy();
}


void CStateToolView::GetTestPara(CString &strParas)
{
	ASSERT (m_pGbMacroUI != NULL);

	if (m_pGbMacroUI == NULL)
	{
		strParas = _T("");
	}

	m_pGbMacroUI->GbUIGetParas(strParas);
}

