
// iSmartTestNewTestFrame.cpp : CiSmartTestNewTestFrame ���ʵ��
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

// CiSmartTestNewTestFrame ����/����

CEdgeSmartTestNewTestFrame::CEdgeSmartTestNewTestFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CEdgeSmartTestNewTestFrame::~CEdgeSmartTestNewTestFrame()
{
}


BOOL CEdgeSmartTestNewTestFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CiSmartTestNewTestFrame ���

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

// CiSmartTestNewTestFrame ��Ϣ�������
void CEdgeSmartTestNewTestFrame::OnClose()
{
	if (g_theSmartTestCtrlCntr->IsNowTesting())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("�����У����ܹر�......."));
		return;
	}

	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	//pMainFrame->m_wndOutput.m_wndSmartTest.SetWindowText(_T(""));
	pMainFrame->m_wndOutput.m_wndTabs.SetActiveTab(0);
	g_theSmartTestCtrlCntr->CloseTestCtrlCntr();
	g_pEdgeEngineProtoSvrBaseApp->m_nState = g_pEdgeEngineProtoSvrBaseApp->STATE_POWER;

 	CMDIChildWndEx::OnClose();
}

