// SclFileFrame.cpp : ʵ���ļ�
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


// CSclCheckFrame ��Ϣ�������

void CSclCheckFrame::OnClose()
{
	CString strMsg;


	strMsg.Format(_T("��ȷʵҪ�ر�SCL��������"));

	UINT nRet = MessageBox(strMsg, _T("��ʾ"), MB_YESNO | MB_ICONQUESTION);

	if (nRet == IDNO)
	{
		return;
	}

	CMDIChildWndEx::OnClose();
}


BOOL CSclCheckFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CMDIChildWndEx::PreCreateWindow(cs);
}

void CSclCheckFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// TODO: �ڴ˴������Ϣ����������
}
