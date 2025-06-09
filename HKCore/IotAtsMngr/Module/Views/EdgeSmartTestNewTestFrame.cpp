
// iSmartTestNewTestFrame.cpp : CiSmartTestNewTestFrame 类的实现
//

#include "stdafx.h"

#include "EdgeSmartTestNewTestFrame.h"
#include "EdgeSmartTestNewTestView.h"
#include "../../EdgeEngineProtocolServer/MainFrm.h"
#include "../../EdgeEngineProtocolServer/EdgeSmartTestCtrlCntr.h"
#include "../Edge/EdgeEngineProtoSvrBaseApp.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

// CiSmartTestNewTestFrame

IMPLEMENT_DYNCREATE(CEdgeSmartTestNewTestFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CEdgeSmartTestNewTestFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CiSmartTestNewTestFrame 构造/析构

CEdgeSmartTestNewTestFrame::CEdgeSmartTestNewTestFrame()
{
	// TODO: 在此添加成员初始化代码
}

CEdgeSmartTestNewTestFrame::~CEdgeSmartTestNewTestFrame()
{
}


BOOL CEdgeSmartTestNewTestFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CiSmartTestNewTestFrame 诊断

#ifdef _DEBUG
void CEdgeSmartTestNewTestFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CEdgeSmartTestNewTestFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CiSmartTestNewTestFrame 消息处理程序
void CEdgeSmartTestNewTestFrame::OnClose()
{
	if (g_theSmartTestCtrlCntr->IsNowTesting())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("测试中，不能关闭......."));
		return;
	}

	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	//pMainFrame->m_wndOutput.m_wndSmartTest.SetWindowText(_T(""));
	pMainFrame->m_wndOutput.m_wndTabs.SetActiveTab(0);
	g_theSmartTestCtrlCntr->CloseTestCtrlCntr();
	g_pEdgeEngineProtoSvrBaseApp->m_nState = g_pEdgeEngineProtoSvrBaseApp->STATE_POWER;

 	CMDIChildWndEx::OnClose();
}

