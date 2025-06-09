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

// AutoTestBaseLogicView.cpp : CAutoTestBaseLogicView ���ʵ��
//

#include "stdafx.h"
#include "AutoTestBaseFrame.h"
#include "AutoTestBaseLogicView.h"
#include "../TCtrlCntrDefine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoTestBaseLogicView

IMPLEMENT_DYNCREATE(CAutoTestBaseLogicView, CScrollView)

BEGIN_MESSAGE_MAP(CAutoTestBaseLogicView, CScrollView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

// CAutoTestBaseLogicView ����/����
void CAutoTestBaseLogicView::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
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

CAutoTestBaseLogicView::CAutoTestBaseLogicView()
{
	m_pTestControl = NULL;
	m_pVisioRptFill = NULL;
	m_pParentWnd = NULL;
}

CAutoTestBaseLogicView::~CAutoTestBaseLogicView()
{
	if (m_pVisioRptFill != NULL)
	{
		delete m_pVisioRptFill;
		m_pVisioRptFill = NULL;
	}
}

BOOL CAutoTestBaseLogicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CAutoTestBaseLogicView ����

void CAutoTestBaseLogicView::OnDraw(CDC* pDC)
{
	CAutoTestBaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

// CAutoTestBaseLogicView ���

#ifdef _DEBUG
void CAutoTestBaseLogicView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAutoTestBaseLogicView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CAutoTestBaseDoc* CAutoTestBaseLogicView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoTestBaseDoc)));
	return (CAutoTestBaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CAutoTestBaseLogicView ��Ϣ�������

void CAutoTestBaseLogicView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal(100, 100);
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_pVisioRptFill = new CVisioLogicRptFill();
}

void CAutoTestBaseLogicView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	if(m_pVisioRptFill != NULL)
	{
		m_pVisioRptFill->AdjustReportWindowOnSize();
	}
}

void CAutoTestBaseLogicView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}

void CAutoTestBaseLogicView::CreateTestControlView(CTestControl *pTestControl)
{
// 	//�����ĵ�����
// 	CAutoTestBaseDoc* pDoc = (CAutoTestBaseDoc*)GetDocument();
// 	CString strTitle = pDoc->GetTitle();
// 	strTitle = _T("�߼�ͼ��ͼ��") + strTitle;
// 	pDoc->SetTitle(strTitle);
	CString strFile;

	//�˴����߼�ͼ�ļ�
	if (m_pVisioRptFill != NULL)
	{
		m_pVisioRptFill->SetParentWnd(this);
		strFile = m_pVisioRptFill->GetVisioFilePath();

		if (strFile.GetLength() > 5)
		{
			m_pVisioRptFill->InitVisioRptFill();
			m_pVisioRptFill->OpenVisioFile();
			m_pVisioRptFill->AdjustVisioWindow();
		}
		else
		{
			CMFCTabCtrl *pTab = (CMFCTabCtrl *)m_pParentWnd;
			pTab->ShowTab(1, FALSE);
		}
	}
}

void CAutoTestBaseLogicView::CloseTestControl()
{
	if (m_pVisioRptFill != NULL)
	{
		m_pVisioRptFill->CloseFile();
		m_pVisioRptFill->CloseApplication();
	}
}

void CAutoTestBaseLogicView::LocateVisio(CExBaseObject *pItem)
{
	if (m_pVisioRptFill == NULL)
	{
		return;
	}

	m_pVisioRptFill->LocateVisio(pItem);
}

void CAutoTestBaseLogicView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pTestControl = (CTestControl*)lHint;

	if (m_pTestControl == NULL)
	{
		return;
	}

	if (m_pVisioRptFill != NULL)
	{
		m_pVisioRptFill->m_pTestControl = m_pTestControl;
	}

	CreateTestControlView(m_pTestControl);
}

BOOL CAutoTestBaseLogicView::OnEraseBkgnd(CDC* pDC)
{
	if (m_pTestControl == NULL)
	{
		return CScrollView::OnEraseBkgnd(pDC);;
	}

	if (m_pVisioRptFill == NULL)
	{
		return CScrollView::OnEraseBkgnd(pDC);
	}

	return TRUE;
}

long CAutoTestBaseLogicView::OnCurrItemStateChanged(CGbItemBase* pItem)
{
	if (m_pVisioRptFill == NULL)
	{
		return 0;
	}

	if (pItem == NULL)
	{
		return 0;
	}

	long nState = pItem->GetState();

	//ͨ����Ŀ״̬���ж���Ŀ�Ƿ���Խ���
	if (nState == TEST_STATE_NORMAL || nState == TEST_STATE_TESTING || nState == TEST_STATE_COUNT
		|| nState == TEST_STATE_SKIP)
	{
		return 0;
	}

	//��ȡ�����CItems��m_strActLogic��Ϣ������Ϣ���߼�ͼ�ļ��е�ĳһҳ���Ӧ��
	CString strActLogic = pItem->GetActLogic_String();

	if (strActLogic.GetLength() <= 0)
	{
		return 0;
	}

	m_pVisioRptFill->OnItemTestFinished(pItem, strActLogic);

	return 0;
}