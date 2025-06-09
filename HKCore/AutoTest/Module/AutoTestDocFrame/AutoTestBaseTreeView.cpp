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

// AutoTestBaseTreeView.cpp : CAutoTestBaseTreeView ���ʵ��
//

#include "stdafx.h"

#include "AutoTestBaseFrame.h"

#include "AutoTestBaseTreeView.h"
#include "AutoTestBaseReportView.h"

#include "../TCtrlCntrDefine.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoTestBaseTreeView

IMPLEMENT_DYNCREATE(CAutoTestBaseTreeView, CView)

BEGIN_MESSAGE_MAP(CAutoTestBaseTreeView, CView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CAutoTestBaseTreeView ����/����

CAutoTestBaseTreeView::CAutoTestBaseTreeView()
{
	m_pTestControl = NULL;
	m_pReportView = NULL;
	m_pLogicView = NULL;
}

CAutoTestBaseTreeView::~CAutoTestBaseTreeView()
{
}

BOOL CAutoTestBaseTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CAutoTestBaseTreeView ����

void CAutoTestBaseTreeView::OnDraw(CDC* pDC)
{
	CAutoTestBaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//pDC->Rectangle(10, 10, 300, 300);
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CAutoTestBaseTreeView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAutoTestBaseTreeView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CAutoTestBaseTreeView ���

#ifdef _DEBUG
void CAutoTestBaseTreeView::AssertValid() const
{
	CView::AssertValid();
}

void CAutoTestBaseTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAutoTestBaseDoc* CAutoTestBaseTreeView::GetDocument() const // �ǵ��԰汾��������
{
	return (CAutoTestBaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CAutoTestBaseTreeView ��Ϣ�������

void CAutoTestBaseTreeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	ASSERT (g_theTCtrlCntrApp != NULL);

	CRect rectDummy;
	GetClientRect(&rectDummy);

	// ������ͼ:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;

	if (g_theTCtrlCntrApp->IsDebugWithoutGbTree())
	{

	}
	else
	{
		if (!m_treeGuideBook.Create(dwViewStyle, rectDummy, this, ID_GUIDEBOOK_TEST_TREECTRL))
		{
			TRACE0("δ�ܴ���XFile��ͼ\n");
		}

		m_treeGuideBook.SetFont(g_pGlobalFont12);
		m_treeGuideBook.SetParentWnd(this);
	}
	
	AdjustLayout(rectDummy.Width(), rectDummy.Height());
}

void CAutoTestBaseTreeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	AdjustLayout(cx, cy);
}

void CAutoTestBaseTreeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}

CRptFillInterface* CAutoTestBaseTreeView::GetRptFillInterface()
{
	return NULL;
}

void CAutoTestBaseTreeView::CloseTestControl()
{
	//m_treeGuideBook.CloseTestProject();
}

void CAutoTestBaseTreeView::AdjustLayout(int cx, int cy)
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	if (g_theTCtrlCntrApp->IsDebugWithoutGbTree())
	{

	}
	else
	{
		if (m_treeGuideBook.GetSafeHwnd() == NULL)
		{
			return;
		}

		m_treeGuideBook.SetWindowPos(NULL, 0, 0,cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void CAutoTestBaseTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pTestControl = (CTestControl*)lHint;

	if (m_pTestControl == NULL)
	{
		return;
	}

	m_treeGuideBook.InitShowTestControl(m_pTestControl);
}

long CAutoTestBaseTreeView::OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop)
{
	if(!::IsWindow(m_treeGuideBook.m_hWnd))
	{
		return 0;
	}

	m_treeGuideBook.Invalidate(FALSE);

	if(pItem != NULL /*&& pItem->GetState() == TEST_STATE_TESTING*/)
	{
		HTREEITEM hCurrSelTreeItem = (HTREEITEM)pItem->m_dwItemData;
		m_treeGuideBook.Expand(hCurrSelTreeItem, TVE_EXPAND);

		if (bBringToTop)
		{
			m_treeGuideBook.SelectTopItem(pItem);
		}
	}

	return 0;
}

void CAutoTestBaseTreeView::SelectTestItem(CExBaseObject *pItem)
{
	m_treeGuideBook.SelectTopItem((CGbItemBase*)pItem);
}

void CAutoTestBaseTreeView::LocateVisio(CExBaseObject *pItem)
{
	if (m_pLogicView != NULL)
	{
		m_pLogicView->LocateVisio(pItem);
	}
}

//shaolei 20220622 SV����ѹ��һ���Բ��ԣ���Ҫ��̬������Ŀ����Ҫɾ�������
void CAutoTestBaseTreeView::DeleteItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	if(!::IsWindow(m_treeGuideBook.m_hWnd))
	{
		return;
	}

	if (pParentItem == NULL || pSubItem == NULL)
	{
		return;
	}

	m_treeGuideBook.Invalidate(FALSE);

	HTREEITEM hParentTreeItem = (HTREEITEM)pParentItem->m_dwItemData;
	HTREEITEM hSubTreeItem = (HTREEITEM)pSubItem->m_dwItemData;
	m_treeGuideBook.DeleteItem(hSubTreeItem);
	m_treeGuideBook.Expand(hParentTreeItem, TVE_EXPAND);
}

void CAutoTestBaseTreeView::InsertItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	if(!::IsWindow(m_treeGuideBook.m_hWnd))
	{
		return;
	}

	if (pParentItem == NULL || pSubItem == NULL)
	{
		return;
	}

	m_treeGuideBook.Invalidate(FALSE);
	HTREEITEM hParentTreeItem = (HTREEITEM)pParentItem->m_dwItemData;
	DWORD dwItemData = 0;
	HTREEITEM hTreeItem = m_treeGuideBook.InsertItem(_T(""),0,0,hParentTreeItem);
	pSubItem->m_dwItemData = (DWORD)hTreeItem;
	m_treeGuideBook.SetItemData(hTreeItem, (DWORD)pSubItem);
	m_treeGuideBook.Expand(hParentTreeItem, TVE_EXPAND);
}

void CAutoTestBaseTreeView::InsertItemEx(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	InsertItem(pParentItem, pSubItem);

	POS pos = pSubItem->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pSubItem->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_ITEMS
			|| Gb_IsGbItemClassID(nClassID))
		{
			CGbItemBase *pItemBase = (CGbItemBase *)pObj;
			InsertItemEx(pSubItem, pItemBase);
		}
	}
}