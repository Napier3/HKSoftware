// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// StateToolView.cpp : CStateToolView ���ʵ��
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

// CStateToolView ����/����

CStateToolView::CStateToolView()
	: CFormView(CStateToolView::IDD)
{
	// TODO: �ڴ˴���ӹ������
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ȱ�ٽ��涯̬���ӿ⣺%s"), strUiDLL);
	}
}

void CStateToolView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CStateToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

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


// CStateToolView ���

#ifdef _DEBUG
void CStateToolView::AssertValid() const
{
	CFormView::AssertValid();
}

void CStateToolView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CStateToolDoc* CStateToolView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStateToolDoc)));
	return (CStateToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CStateToolView ��Ϣ�������

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

// 	//��ô��ڵĴ�����Ϣָ��
// 	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;
// 
// 	m_tabPara.Create(CMFCTabCtrl::STYLE_3D_ROUNDED ,CRect(0, 0, 0, 0), this, 1000, CMFCTabCtrl::LOCATION_TOP);
// 
// 	m_pViewSmvMain = new CIecCfgSmvViewMain();
// 	if (m_pViewSmvMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
// 		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST, pContext))
// 	{
// 		m_tabPara.AddTab(m_pViewSmvMain, _T("SMV����"));
// 	}
// 
// 	m_pViewGinMain = new CIecCfgGinViewMain();
// 	if (m_pViewGinMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
// 		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+1, pContext))
// 	{
// 		m_tabPara.AddTab(m_pViewGinMain, _T("GOOSE��������"));
// 	}
// 
// 	m_pViewGoutMain = new CIecCfgGoutViewMain();
// 	if (m_pViewGoutMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
// 		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+2, pContext))
// 	{
// 		m_tabPara.AddTab(m_pViewGoutMain, _T("GOOSE��������"));
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

