// SclFileFrame.cpp : 实现文件
//

#include "stdafx.h"

#include "SclCheckFrame.h"
//#include "..\SCLCompareCheckDev.h"

// CSclCheckFrame

IMPLEMENT_DYNCREATE(CSclCheckFrame, CMDIChildWndEx)

CSclCheckFrame::CSclCheckFrame()
{
	m_pMsgRcvWnd = NULL;
}

CSclCheckFrame::~CSclCheckFrame()
{
//	theApp.ClearSclCheckFrameAndView();
	if (m_pMsgRcvWnd != NULL)
	{
		m_pMsgRcvWnd->SendMessage(WM_SCLCHECKCLASSID_CLOSEFRAME, 0, 0);
	}
}


BEGIN_MESSAGE_MAP(CSclCheckFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
	ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()


// CSclCheckFrame 消息处理程序

void CSclCheckFrame::OnClose()
{
	CString strMsg;


	strMsg.Format(_T("你确实要关闭SCL检查界面吗？"));

	UINT nRet = MessageBox(strMsg, _T("提示"), MB_YESNO | MB_ICONQUESTION);

	if (nRet == IDNO)
	{
		return;
	}

	CMDIChildWndEx::OnClose();
}


BOOL CSclCheckFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CMDIChildWndEx::PreCreateWindow(cs);
}

void CSclCheckFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// TODO: 在此处添加消息处理程序代码
}
