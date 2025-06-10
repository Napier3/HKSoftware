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

// IecConfigView.cpp : CIecConfigView 类的实现
//

#include "stdafx.h"
#include "Iec61850Config.h"

#include "IecConfigDoc.h"
#include "IecConfigView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIecConfigView

IMPLEMENT_DYNCREATE(CIecConfigView, CFormView)

BEGIN_MESSAGE_MAP(CIecConfigView, CFormView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CIecConfigView 构造/析构

CIecConfigView::CIecConfigView()
	: CFormView(CIecConfigView::IDD)
{
	// TODO: 在此处添加构造代码
	m_pSysParasView = NULL;
#ifdef _use_CXscdViewMain
	m_pXscdViewMain = NULL;
#endif
}

CIecConfigView::~CIecConfigView()
{
}

void CIecConfigView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CIecConfigView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CIecConfigView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//ResizeParentToFit();
}

void CIecConfigView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIecConfigView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CIecConfigView 诊断

#ifdef _DEBUG
void CIecConfigView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIecConfigView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CIecConfigDoc* CIecConfigView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIecConfigDoc)));
	return (CIecConfigDoc*)m_pDocument;
}
#endif //_DEBUG


// CIecConfigView 消息处理程序

void CIecConfigView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (!::IsWindow(m_tabPara.m_hWnd))
	{
		return;
	}

	CRect rcClient;
	GetClientRect(&rcClient);
	m_tabPara.MoveWindow(0, 0, rcClient.Width(), rcClient.Height());
}

int CIecConfigView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//获得窗口的创建信息指针
	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;

	m_tabPara.Create(CMFCTabCtrl::STYLE_3D_ROUNDED ,CRect(0, 0, 0, 0), this, 1000, CMFCTabCtrl::LOCATION_TOP);

	m_pViewSmvMain = new CIecCfgSmvViewMain();
	if (m_pViewSmvMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST, pContext))
	{
		m_tabPara.AddTab(m_pViewSmvMain, CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecSMVCfg/*_T("SMV配置")*/);
	}

	m_pViewGinMain = new CIecCfgGinViewMain();
	if (m_pViewGinMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+1, pContext))
	{
		m_tabPara.AddTab(m_pViewGinMain, CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecGoSubCfg/*_T("GOOSE订阅配置")*/);
	}

	m_pViewGoutMain = new CIecCfgGoutViewMain();
	if (m_pViewGoutMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+2, pContext))
	{
		m_tabPara.AddTab(m_pViewGoutMain, CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecGoPubCfg/*_T("GOOSE发布配置")*/);
	}

	m_pSysParasView = new CIecCfgSysParasView();//CIecCfgSmvViewMain    CIecCfgSysParasView

	if (m_pSysParasView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+3, pContext))
	{
		m_tabPara.AddTab(m_pSysParasView, _T("系统参数设置"));
	}


#ifdef _use_CXscdViewMain
	m_pXscdViewMain = new CXscdViewCfgMain();
	if (m_pXscdViewMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST, pContext))
	{
		m_tabPara.AddTab(m_pXscdViewMain, _T("图形视图"));
	}
#endif

	return 0;
}

void CIecConfigView::OnDestroy()
{
// 	m_tabPara.AutoDestroyWindow(FALSE);
// 	m_tabPara.RemoveAllTabs();

	CFormView::OnDestroy();
}


void CIecConfigView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CIecCfgFile *pIecfgFile = (CIecCfgFile*)lHint;

	if (pIecfgFile == NULL)
	{
		return;
	}

	CIecCfgFileDevice *pIecFileDevice = (CIecCfgFileDevice *)pIecfgFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);

	if (pIecFileDevice == NULL)
	{
		if (m_pSysParasView == NULL)
		{
			m_tabPara.ShowTab(3, FALSE);
		}
		else
		{
			m_tabPara.ShowTab(4, FALSE);
		}
	}


}

