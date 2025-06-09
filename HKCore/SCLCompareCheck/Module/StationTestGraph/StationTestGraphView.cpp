
// StationTestMainView.cpp : CStationTestMainView 类的实现
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"

#include "StationTestGraphDoc.h"
#include "StationTestGraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStationTestMainView
IMPLEMENT_DYNCREATE(CStationTestGraphView, CXscdViewStationThumbMain)

//IMPLEMENT_DYNCREATE(CStationTestGraphView, CView)

BEGIN_MESSAGE_MAP(CStationTestGraphView, CXscdViewStationThumbMain)
	ON_COMMAND(ID_STATIONTEST_IEC61850CONFIG, &CStationTestGraphView::OnStationTest_Iec61850Config)
	ON_COMMAND(ID_STATIONTEST_DVMTEST, &CStationTestGraphView::OnStationTest_DvmTest)
	ON_COMMAND(ID_STATIONTEST_VTERMTEST, &CStationTestGraphView::OnStationTest_VTermTest)
	ON_COMMAND(ID_STATIONTEST_PROTTEST, &CStationTestGraphView::OnStationTest_ProtTest)
	ON_COMMAND(ID_STATIONTEST_LINKTEST, &CStationTestGraphView::OnStationTest_LinkTest)
	ON_COMMAND(ID_STATIONTEST_EXPORTRPT, &CStationTestGraphView::OnStationTest_ExportRpt)
	ON_COMMAND(ID_STATIONTEST_UPLOADRPT, &CStationTestGraphView::OnStationTest_UploadRpt)
END_MESSAGE_MAP()

// CStationTestMainView 构造/析构

CStationTestGraphView::CStationTestGraphView()
{
	// TODO: 在此处添加构造代码

}

CStationTestGraphView::~CStationTestGraphView()
{

}

BOOL CStationTestGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CStationTestMainView 绘制

void CStationTestGraphView::OnDraw(CDC* pDC)
{
// 	CStationTestGraphDoc* pDoc = GetDocument();
// 	ASSERT_VALID(pDoc);
// 	if (!pDoc)
// 		return;
// 

	CXscdViewStationThumbMain::OnDraw(pDC);
}

void CStationTestGraphView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CStationTestGraphView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CStationTestMainView 诊断

#ifdef _DEBUG
void CStationTestGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CStationTestGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStationTestGraphDoc* CStationTestGraphView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStationTestGraphDoc)));
	return (CStationTestGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CStationTestMainView 消息处理程序

void CStationTestGraphView::OnInitialUpdate()
{
	CXscdViewStationThumbMain::OnInitialUpdate();

	CSclStation *pSclStation = theApp.GetCurrentSclStation();

	CreateXscdViewThumbMain(pSclStation);

	CSize sizeTotal;
	sizeTotal.cx=m_oXScdDrawViewThumbnail.m_nWidth;
	sizeTotal.cy=m_oXScdDrawViewThumbnail.m_nHeight;
	SetScrollSizes(MM_TEXT, sizeTotal); 
	m_oMemDC->SetSizeChanged();
	m_pXScdDrawViewRef = m_pXScdDrawView;
}

void CStationTestGraphView::UpdateIedTestState()
{
	
}

void CStationTestGraphView::OnXScdElementLDblClk(CXDrawElement *pElement)
{
	if (pElement == NULL)
	{
		return ;
	}

	if (pElement->GetClassID() != XSCDDRAW_IED_THUMBNAIL)
	{
		return;
	}

	CXScdDrawIedThumbnail *pXScdDrawIedThumb = (CXScdDrawIedThumbnail*)pElement;

	CSclIed *pCurSclIed = pXScdDrawIedThumb->GetRefIed();

	theApp.m_pSclVisualTreeView->m_treeSclIecDetail.UpdateTabForm(pCurSclIed);//更新表格类视图
	theApp.UpdateScdDrawIedByID(pCurSclIed->m_strID);//更新单IED的可视化视图

}

CXScdDrawIedThumbnail * CStationTestGraphView::GetScdDrawIedByID(CString strID)
{
	return (CXScdDrawIedThumbnail*)m_pXScdDrawView->FindByID(strID);
}

BOOL  CStationTestGraphView::OnXScdElementRButtonDown(UINT nFlags, CPoint point)
{
	CPoint pt = GetScrollPosition();
	pt += point;

	if (m_pXScdDrawView->UI_OnLButtonDown(nFlags, pt))
	{
		Invalidate(FALSE);
	}

	if (m_pXScdDrawView->m_pActiveElement != NULL)
	{
		CStationTest *pStationTest = theApp.GetCurrStationTest();

		ASSERT( pStationTest != NULL );
		ClientToScreen(&point);
		pStationTest->OnInitStatioTestIedMenu(this, point, m_pXScdDrawView->m_pActiveElement->m_strID);

		return TRUE;
	}

	return FALSE;
}
// 
// BOOL CStationTestGraphView::IsIedNeedTest(CString &strIedId)
// {
// 	if (m_pXScdDrawView->m_pActiveElement == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	CStationTest *pStationTest = theApp.GetCurrStationTest();
// 
// 	ASSERT( pStationTest != NULL );
// 
// 	if (pStationTest == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	strIedId = m_pXScdDrawView->m_pActiveElement->m_strID;
// 
// 	return pStationTest->IsIedNeedTest(strIedId);
// }
// 
// CStationIedTest* CStationTestGraphView::GetCurrIedTest()
// {
// 	CString strIedID;
// 
// 	if (! IsIedNeedTest(strIedID))
// 	{
// 		return NULL;
// 	}
// 
// 	CStationTest *pStationTest = theApp.GetCurrStationTest();
// 	CStationIedTest *pIedTest = pStationTest->SetCurrIedTest(strIedID);
// 
// 	ASSERT(pIedTest != NULL);
// 
// 	return pIedTest;
// }

void CStationTestGraphView::OnStationTest_Iec61850Config()
{
	Optr_OnStationTest_Iec61850Config();
// 	CStationIedTest *pIedTest = GetCurrIedTest();
// 
// 	if (pIedTest == NULL)
// 	{
// 		return;
// 	}
// 
// 	pIedTest->Iec61850Config();
}

void CStationTestGraphView::OnStationTest_DvmTest()
{
	Optr_OnStationTest_DvmTest();
// 	CStationIedTest *pIedTest = GetCurrIedTest();
// 
// 	if (pIedTest == NULL)
// 	{
// 		return;
// 	}
// 
// 	pIedTest->DvmTest();

}

void CStationTestGraphView::OnStationTest_VTermTest()
{
	Optr_OnStationTest_VTermTest();
// 	CStationIedTest *pIedTest = GetCurrIedTest();
// 
// 	if (pIedTest == NULL)
// 	{
// 		return;
// 	}
// 
// 	pIedTest->VTerminalTest();
}

void CStationTestGraphView::OnStationTest_ProtTest()
{
	Optr_OnStationTest_ProtTest();
// 	CStationIedTest *pIedTest = GetCurrIedTest();
// 
// 	if (pIedTest == NULL)
// 	{
// 		return;
// 	}
// 
// 	pIedTest->ProtTest();
}

void CStationTestGraphView::OnStationTest_LinkTest()
{
	Optr_OnStationTest_LinkTest();
// 	CStationIedTest *pIedTest = GetCurrIedTest();
// 
// 	if (pIedTest == NULL)
// 	{
// 		return;
// 	}
// 
// 	pIedTest->LockTest();
}

void CStationTestGraphView::OnStationTest_ExportRpt()
{
	Optr_OnStationTest_ExportRpt();
}

void CStationTestGraphView::OnStationTest_UploadRpt()
{
	Optr_OnStationTest_UploadRpt();
}

