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

// AutoTestBaseReportView.cpp : CAutoTestBaseReportView ���ʵ��
//

#include "stdafx.h"

#include "AutoTestBaseFrame.h"

#include "AutoTestBaseReportView.h"
#include "AutoTestBaseTreeView.h"

#include "../TCtrlCntrDefine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoTestBaseReportView

IMPLEMENT_DYNCREATE(CAutoTestBaseReportView, CScrollView)

BEGIN_MESSAGE_MAP(CAutoTestBaseReportView, CScrollView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_CREATE_NEW_TEST_PROJECT,&CAutoTestBaseReportView::OnCreateNewTestProject)
	ON_MESSAGE(WM_ADJUSTVIEWSIZE,&CAutoTestBaseReportView::OnAdjustViewSize)
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

// CAutoTestBaseReportView ����/����
void CAutoTestBaseReportView::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	lpMMI->ptMaxSize.x = 2000;  // ���ô������ʱ�Ŀ��
	lpMMI->ptMaxSize.y = 0x00FFFFFF;  // ���ô������ʱ�ĸ߶�
// 	lpMMI->ptMaxPosition.x = 100; // ���ô������ʱx����
// 	lpMMI->ptMaxPosition.y = 100; // ���ô������ʱy����
// 	lpMMI->ptMinTrackSize.x = 400; // ���ô�����С���
// 	lpMMI->ptMinTrackSize.y = 400; // ���ô�����С�߶�
// 	lpMMI->ptMaxTrackSize.x = 600; // ���ô��������
// 	lpMMI->ptMaxTrackSize.y = 500; // ���ô������߶�

	CScrollView::OnGetMinMaxInfo(lpMMI);
}

CAutoTestBaseReportView::CAutoTestBaseReportView()
{
	m_nTestControlMode = TESTCONTROLMODE_NORMAL;
	m_pTestControl = NULL;
	m_pTreeView = NULL;
}

CAutoTestBaseReportView::~CAutoTestBaseReportView()
{
}

BOOL CAutoTestBaseReportView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CAutoTestBaseReportView ����

void CAutoTestBaseReportView::OnDraw(CDC* pDC)
{
	CAutoTestBaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CAutoTestBaseReportView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAutoTestBaseReportView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CAutoTestBaseReportView ���

#ifdef _DEBUG
void CAutoTestBaseReportView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAutoTestBaseReportView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CAutoTestBaseDoc* CAutoTestBaseReportView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoTestBaseDoc)));
	return (CAutoTestBaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CAutoTestBaseReportView ��Ϣ�������

void CAutoTestBaseReportView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal(100, 100);
	SetScrollSizes(MM_TEXT, sizeTotal); 
	//OpenReportView();
}

void CAutoTestBaseReportView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	CRptFillInterface *pRptFillInterface = GetRptFillInterface();

	if(pRptFillInterface != NULL)
	{
		pRptFillInterface->AdjustReportWindowOnSize();
	}
}

void CAutoTestBaseReportView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}

CRptFillInterface* CAutoTestBaseReportView::GetRptFillInterface()
{
	if (m_pTestControl != NULL)
	{
		return m_pTestControl->m_pReportFill;
	}
	else
	{
		return NULL;
	}
}

long CAutoTestBaseReportView::OpenReportView()
{
	if (m_pTestControl == NULL)
	{
		return 0;
	}

	if(!m_pTestControl->HasProject())
	{
		return 0;
	}

	//pFrame->m_bIsFirstFrame = TRUE;
	//pFrame->TraverseAllTestProjects();

	return 0;
}

LRESULT CAutoTestBaseReportView::OnCreateNewTestProject(WPARAM wParam,LPARAM lParam)
{
	CTestControl* pTestControl = (CTestControl*)wParam;

	if (pTestControl == NULL)
	{
		CloseTestControl();
		return 0;
	}
	
	m_nTestControlMode = pTestControl->GetTestControlMode();
	CreateTestControlView(pTestControl);

	return 0;
}

LRESULT CAutoTestBaseReportView::OnAdjustViewSize(WPARAM wParam,LPARAM lParam)
{
	CSystemRptFill *pSysRptFill = (CSystemRptFill*)wParam;
	CSize sizeTotal;
	sizeTotal.cx = pSysRptFill->GetWidth();
	sizeTotal.cy = pSysRptFill->GetHeight();

	if (lParam != 0)
	{
		SetScrollSizes(MM_TEXT, sizeTotal); 
		//SetScrollRange(SB_VERT, 0, sizeTotal.cx, TRUE);
		//SetScrollRange(SB_HORZ, 0, sizeTotal.cy, TRUE);
	}

	long nPos = pSysRptFill->GetCurrPos();
	CRect rcClient;
	GetClientRect(&rcClient);
	long nHeight = rcClient.Height();

	if (nHeight > sizeTotal.cy)
	{
		nPos = 0;
	}
	else
	{
		if (nPos + nHeight > sizeTotal.cy)
		{
			nPos = sizeTotal.cy - nHeight;
		}
	}

	ScrollToPosition(CPoint(0, nPos));

	return 0;
}

void CAutoTestBaseReportView::CreateTestControlView(CTestControl *pTestControl)
{
	//�����ĵ�����
	CAutoTestBaseDoc* pDoc = (CAutoTestBaseDoc*)GetDocument();

#if 0
	if(pDoc != NULL)
	{
		//ats_SetCocumentTitle(pTestControl->GetProjectName(), pDoc);//pDoc->SetTitle(pTestControl->GetProjectName());
	
		if (m_nTestControlMode == TESTCONTROLMODE_MDGBRPT
			|| m_nTestControlMode == TESTCONTROLMODE_SDVMPP)
		{
			CString strTitle = pDoc->GetTitle();
			strTitle = g_sLangTxt_MainView2/*_T("����ͼ:")*/ + strTitle;
			pDoc->SetTitle(strTitle);
		}
		else
		{

		}
	}
#endif

	CRptFillInterface *pRptFillInterface = GetRptFillInterface();

	if (pRptFillInterface != NULL)
	{
		pRptFillInterface->SetParentWnd(this);
	}

	pTestControl->OpenReportFile(this, TRUE);
	pTestControl->OpenAllBinaryTempFiles();
}


void CAutoTestBaseReportView::CloseTestControl()
{
	
}

void CAutoTestBaseReportView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pTestControl = (CTestControl*)lHint;

	if (m_pTestControl == NULL)
	{
		return;
	}

	CreateTestControlView(m_pTestControl);
}

BOOL CAutoTestBaseReportView::OnEraseBkgnd(CDC* pDC)
{
	if (m_pTestControl == NULL)
	{
		return CScrollView::OnEraseBkgnd(pDC);;
	}

	if (m_pTestControl->m_pReportFill == NULL)
	{
		return CScrollView::OnEraseBkgnd(pDC);
	}

	if (m_pTestControl->m_pReportFill->GetReportFillClassID() == REPORTFILL_PROGID_SYSTEM)
	{
		return CScrollView::OnEraseBkgnd(pDC);
	}

	return TRUE;//CScrollView::OnEraseBkgnd(pDC);
}
