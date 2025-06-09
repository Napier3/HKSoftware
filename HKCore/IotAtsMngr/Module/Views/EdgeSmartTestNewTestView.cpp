#include "stdafx.h"
#include "EdgeSmartTestNewTestView.h"
#include "../../EdgeEngineProtocolServer/EdgeSmartTestCtrlCntr.h"
#include "../../EdgeEngineProtocolServer/MainFrm.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

IMPLEMENT_DYNCREATE(CEdgeSmartTestNewTestView, CFormView)

CEdgeSmartTestNewTestView::CEdgeSmartTestNewTestView()
	: CFormView(CEdgeSmartTestNewTestView::IDD)
{
	
}

CEdgeSmartTestNewTestView::~CEdgeSmartTestNewTestView()
{
	
}

void CEdgeSmartTestNewTestView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEdgeSmartTestNewTestView, CFormView)
	ON_WM_SIZE()
	ON_MESSAGE(WM_USER_ADJMAINWND, &CEdgeSmartTestNewTestView::OnAdjMainWnd)
END_MESSAGE_MAP()

void CEdgeSmartTestNewTestView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CExBaseObject *pObj = (CExBaseObject *)lHint;

	if (pObj == NULL)
	{
		return;
	}
	
	EnableBtns();
}

void CEdgeSmartTestNewTestView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	g_theSmartTestCtrlCntr->InitTestCtrlCntr(this, &pMainFrame->m_wndOutput.m_wndTabs);
}

void CEdgeSmartTestNewTestView::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	EnableBtns();
}

void CEdgeSmartTestNewTestView::EnableBtns()
{
	
}

void CEdgeSmartTestNewTestView::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if (g_theSmartTestCtrlCntr->m_hAtsMainWnd == NULL)
	{
		return;
	}

	::MoveWindow(g_theSmartTestCtrlCntr->m_hAtsMainWnd, 0, 0, cx, cy, TRUE);
}

LRESULT CEdgeSmartTestNewTestView::OnAdjMainWnd(WPARAM wParam, LPARAM lParam)
{

	g_theSmartTestCtrlCntr->AdjMainWnd();
	return 0;
}