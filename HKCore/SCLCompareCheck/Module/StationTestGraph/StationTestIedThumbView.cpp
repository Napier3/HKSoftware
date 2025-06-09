
// StationTestMainView.cpp : CStationTestMainView 类的实现
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"

#include "StationTestGraphDoc.h"
#include "StationTestIedThumbView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStationTestMainView
IMPLEMENT_DYNCREATE(CStationTestIedThumbView, CXscdViewIedThumbMain)

BEGIN_MESSAGE_MAP(CStationTestIedThumbView, CXscdViewIedThumbMain)
	ON_COMMAND(ID_STATIONTEST_IEC61850CONFIG, &CStationTestIedThumbView::OnStationTest_Iec61850Config)
	ON_COMMAND(ID_STATIONTEST_DVMTEST, &CStationTestIedThumbView::OnStationTest_DvmTest)
	ON_COMMAND(ID_STATIONTEST_VTERMTEST, &CStationTestIedThumbView::OnStationTest_VTermTest)
	ON_COMMAND(ID_STATIONTEST_PROTTEST, &CStationTestIedThumbView::OnStationTest_ProtTest)
	ON_COMMAND(ID_STATIONTEST_LINKTEST, &CStationTestIedThumbView::OnStationTest_LinkTest)
	ON_COMMAND(ID_STATIONTEST_EXPORTRPT, &CStationTestIedThumbView::OnStationTest_ExportRpt)
	ON_COMMAND(ID_STATIONTEST_UPLOADRPT, &CStationTestIedThumbView::OnStationTest_UploadRpt)
END_MESSAGE_MAP()

// CStationTestMainView 构造/析构

CStationTestIedThumbView::CStationTestIedThumbView()
{
	m_pXScdDrawIedThumb = NULL;
}

CStationTestIedThumbView::~CStationTestIedThumbView()
{

}

BOOL CStationTestIedThumbView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CStationTestMainView 绘制

void CStationTestIedThumbView::OnDraw(CDC* pDC)
{
// 	CStationTestGraphDoc* pDoc = GetDocument();
// 	ASSERT_VALID(pDoc);
// 	if (!pDoc)
// 		return;
// 

	CXscdViewIedThumbMain::OnDraw(pDC);
}

void CStationTestIedThumbView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CStationTestIedThumbView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CStationTestMainView 诊断

#ifdef _DEBUG
void CStationTestIedThumbView::AssertValid() const
{
	CView::AssertValid();
}

void CStationTestIedThumbView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStationTestGraphDoc* CStationTestIedThumbView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStationTestGraphDoc)));
	return (CStationTestGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CStationTestMainView 消息处理程序

void CStationTestIedThumbView::OnInitialUpdate()
{
	CXscdViewIedThumbMain::OnInitialUpdate();


	CSize sizeTotal;
	sizeTotal.cx=m_oXScdDrawViewThumbnail.m_nWidth;
	sizeTotal.cy=m_oXScdDrawViewThumbnail.m_nHeight;
	SetScrollSizes(MM_TEXT, sizeTotal); 
	m_oMemDC->SetSizeChanged();
	m_pXScdDrawViewRef = m_pXScdDrawView;
}


void CStationTestIedThumbView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	m_pXScdDrawIedThumb = (CXScdDrawIedThumbnail*)lHint;

	if (m_pXScdDrawIedThumb == NULL)
	{
		return;
	}

	if (m_pXScdDrawIedThumb->GetClassID() ==IFTCLASSID_CSCLFILE )//0x10002
	{
		return;
	}

	CreateXscdViewThumbMain(m_pXScdDrawIedThumb);

	CSize sizeTotal;

	sizeTotal.cx=m_oXScdDrawViewThumbnail.m_nWidth;
	sizeTotal.cy=m_oXScdDrawViewThumbnail.m_nHeight;

	SetScrollSizes(MM_TEXT, sizeTotal); 
	m_oMemDC->SetSizeChanged();
	m_pXScdDrawViewRef = m_pXScdDrawView;

	CScrollView::OnUpdate(pSender ,lHint ,pHint);
}


void CStationTestIedThumbView::UpdateIedTestState()
{
//	OnUpdate(NULL ,(LPARAM)m_pXScdDrawIedThumb ,NULL);
}

void CStationTestIedThumbView::OnXScdElementLDblClk(CXDrawElement *pElement)
{
	if (pElement == NULL)
	{
		return ;
	}

	if (pElement->GetClassID() != XSCDDRAW_LINE_CTRL)
	{
		return;
	}

	CXScdDrawLine_Ctrls *pLine_Ctrls = (CXScdDrawLine_Ctrls*)pElement;
	theApp.OpenIedDetailGraphView(pLine_Ctrls);
}


BOOL  CStationTestIedThumbView::OnXScdElementRButtonDown(UINT nFlags, CPoint point)
{
	CPoint pt = GetScrollPosition();
	pt += point;

	CXDrawElement *pActiveElement = m_pXScdDrawView->UI_GetActiveXDrawElement(pt);

	if ((pActiveElement == m_pXScdDrawView->m_pActiveElement) && (m_pXScdDrawView->m_pActiveElement != NULL))
	{
		CStationTest *pStationTest = theApp.GetCurrStationTest();

		ASSERT( pStationTest != NULL );
		ClientToScreen(&point);
		pStationTest->OnInitStatioTestIedMenu(this, point, m_pXScdDrawView->m_pActiveElement->m_strID);

		return TRUE;
	}

	return FALSE;
}



void CStationTestIedThumbView::OnStationTest_Iec61850Config()
{
	Optr_OnStationTest_Iec61850Config();
}

void CStationTestIedThumbView::OnStationTest_DvmTest()
{
	Optr_OnStationTest_DvmTest();
}

void CStationTestIedThumbView::OnStationTest_VTermTest()
{
	Optr_OnStationTest_VTermTest();
}

void CStationTestIedThumbView::OnStationTest_ProtTest()
{
	Optr_OnStationTest_ProtTest();
}

void CStationTestIedThumbView::OnStationTest_LinkTest()
{
	Optr_OnStationTest_LinkTest();
}

void CStationTestIedThumbView::OnStationTest_ExportRpt()
{
	Optr_OnStationTest_ExportRpt();
}

void CStationTestIedThumbView::OnStationTest_UploadRpt()
{
	Optr_OnStationTest_UploadRpt();
}

