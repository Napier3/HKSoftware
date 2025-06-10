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

// IecConfigView.cpp : CIecConfigView ���ʵ��
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

// CIecConfigView ����/����

CIecConfigView::CIecConfigView()
	: CFormView(CIecConfigView::IDD)
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

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


// CIecConfigView ���

#ifdef _DEBUG
void CIecConfigView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIecConfigView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CIecConfigDoc* CIecConfigView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIecConfigDoc)));
	return (CIecConfigDoc*)m_pDocument;
}
#endif //_DEBUG


// CIecConfigView ��Ϣ�������

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

	//��ô��ڵĴ�����Ϣָ��
	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;

	m_tabPara.Create(CMFCTabCtrl::STYLE_3D_ROUNDED ,CRect(0, 0, 0, 0), this, 1000, CMFCTabCtrl::LOCATION_TOP);

	m_pViewSmvMain = new CIecCfgSmvViewMain();
	if (m_pViewSmvMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST, pContext))
	{
		m_tabPara.AddTab(m_pViewSmvMain, CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecSMVCfg/*_T("SMV����")*/);
	}

	m_pViewGinMain = new CIecCfgGinViewMain();
	if (m_pViewGinMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+1, pContext))
	{
		m_tabPara.AddTab(m_pViewGinMain, CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecGoSubCfg/*_T("GOOSE��������")*/);
	}

	m_pViewGoutMain = new CIecCfgGoutViewMain();
	if (m_pViewGoutMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+2, pContext))
	{
		m_tabPara.AddTab(m_pViewGoutMain, CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecGoPubCfg/*_T("GOOSE��������")*/);
	}

	m_pSysParasView = new CIecCfgSysParasView();//CIecCfgSmvViewMain    CIecCfgSysParasView

	if (m_pSysParasView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+3, pContext))
	{
		m_tabPara.AddTab(m_pSysParasView, _T("ϵͳ��������"));
	}


#ifdef _use_CXscdViewMain
	m_pXscdViewMain = new CXscdViewCfgMain();
	if (m_pXscdViewMain->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST, pContext))
	{
		m_tabPara.AddTab(m_pXscdViewMain, _T("ͼ����ͼ"));
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

