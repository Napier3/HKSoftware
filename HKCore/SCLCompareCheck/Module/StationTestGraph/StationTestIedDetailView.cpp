
// StationTestMainView.cpp : CStationTestMainView 类的实现
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"

#include "StationTestGraphDoc.h"
#include "StationTestIedDetailView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStationTestMainView
IMPLEMENT_DYNCREATE(CStationTestIedDetailView, CXscdViewIedDetailMain)

BEGIN_MESSAGE_MAP(CStationTestIedDetailView, CXscdViewIedDetailMain)
	ON_COMMAND(ID_STATIONTEST_IEC61850CONFIG, &CStationTestIedDetailView::OnStationTest_Iec61850Config)
	ON_COMMAND(ID_STATIONTEST_DVMTEST, &CStationTestIedDetailView::OnStationTest_DvmTest)
	ON_COMMAND(ID_STATIONTEST_VTERMTEST, &CStationTestIedDetailView::OnStationTest_VTermTest)
	ON_COMMAND(ID_STATIONTEST_PROTTEST, &CStationTestIedDetailView::OnStationTest_ProtTest)
	ON_COMMAND(ID_STATIONTEST_LINKTEST, &CStationTestIedDetailView::OnStationTest_LinkTest)
	ON_COMMAND(ID_STATIONTEST_EXPORTRPT, &CStationTestIedDetailView::OnStationTest_ExportRpt)
	ON_COMMAND(ID_STATIONTEST_UPLOADRPT, &CStationTestIedDetailView::OnStationTest_UploadRpt)
END_MESSAGE_MAP()

// CStationTestMainView 构造/析构

CStationTestIedDetailView::CStationTestIedDetailView()
{
	//m_pXScdDrawIedDetail = NULL;
}

CStationTestIedDetailView::~CStationTestIedDetailView()
{

}

BOOL CStationTestIedDetailView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CStationTestMainView 绘制

void CStationTestIedDetailView::OnDraw(CDC* pDC)
{
	CXscdViewIedDetailMain::OnDraw(pDC);
}

void CStationTestIedDetailView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CStationTestIedDetailView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CStationTestMainView 诊断

#ifdef _DEBUG
void CStationTestIedDetailView::AssertValid() const
{
	CView::AssertValid();
}

void CStationTestIedDetailView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStationTestGraphDoc* CStationTestIedDetailView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStationTestGraphDoc)));
	return (CStationTestGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CStationTestMainView 消息处理程序

void CStationTestIedDetailView::OnInitialUpdate()
{
	CXscdViewIedDetailMain::OnInitialUpdate();


	CSize sizeTotal;
	sizeTotal.cx=m_oXScdDrawViewIedDetail.m_nWidth;
	sizeTotal.cy=m_oXScdDrawViewIedDetail.m_nHeight;
	SetScrollSizes(MM_TEXT, sizeTotal); 
	m_oMemDC->SetSizeChanged();
	m_pXScdDrawViewRef = m_pXScdDrawView;
}


void CStationTestIedDetailView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pXScdDrawLine_Ctrls = (CXScdDrawLine_Ctrls*)lHint;

	if (m_pXScdDrawLine_Ctrls == NULL)
	{
		return;
	}

	CreateXscdViewIedDetailMain(m_pXScdDrawLine_Ctrls);

	CSize sizeTotal;

	sizeTotal.cx=m_oXScdDrawViewIedDetail.m_nWidth;
	sizeTotal.cy=m_oXScdDrawViewIedDetail.m_nHeight;

	SetScrollSizes(MM_TEXT, sizeTotal); 
	m_oMemDC->SetSizeChanged();
	m_pXScdDrawViewRef = m_pXScdDrawView;
}


void CStationTestIedDetailView::UpdateIedTestState()
{
	
}

void CStationTestIedDetailView::OnXScdElementLDblClk(CXDrawElement *pElement)
{
	
}


BOOL  CStationTestIedDetailView::OnXScdElementRButtonDown(UINT nFlags, CPoint point)
{
// 	CPoint pt = GetScrollPosition();
// 	pt += point;
// 
// 	CXDrawElement *pActiveElement = m_pXScdDrawView->UI_GetActiveXDrawElement(pt);
// 
// 	if ((pActiveElement == m_pXScdDrawView->m_pActiveElement) && (m_pXScdDrawView->m_pActiveElement != NULL))
// 	{
// 		CStationTest *pStationTest = theApp.GetCurrStationTest();
// 
// 		ASSERT( pStationTest != NULL );
// 		ClientToScreen(&point);
// 		pStationTest->OnInitStatioTestIedMenu(this, point, m_pXScdDrawView->m_pActiveElement->m_strID);
// 
// 		return TRUE;
// 	}

	return FALSE;
}



void CStationTestIedDetailView::OnStationTest_Iec61850Config()
{
	Optr_OnStationTest_Iec61850Config();
}

void CStationTestIedDetailView::OnStationTest_DvmTest()
{
	Optr_OnStationTest_DvmTest();
}

void CStationTestIedDetailView::OnStationTest_VTermTest()
{
	Optr_OnStationTest_VTermTest();
}

void CStationTestIedDetailView::OnStationTest_ProtTest()
{
	Optr_OnStationTest_ProtTest();
}

void CStationTestIedDetailView::OnStationTest_LinkTest()
{
	Optr_OnStationTest_LinkTest();
}

void CStationTestIedDetailView::OnStationTest_ExportRpt()
{
	Optr_OnStationTest_ExportRpt();
}

void CStationTestIedDetailView::OnStationTest_UploadRpt()
{
	Optr_OnStationTest_UploadRpt();
}

