// SclFileFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "MRptBaseFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSclFileFrame

IMPLEMENT_DYNCREATE(CMRptBaseFrame, CAutoTestBaseFrame)

CMRptBaseFrame::CMRptBaseFrame()
{
	
}

CMRptBaseFrame::~CMRptBaseFrame()
{
	
}


BEGIN_MESSAGE_MAP(CMRptBaseFrame, CAutoTestBaseFrame)
END_MESSAGE_MAP()


BOOL CMRptBaseFrame::OnCloseAtsFrame()
{
	if (!CanCloseAtsFrame())
	{
		return FALSE;
	}

	AfxGetMainWnd()->PostMessage(WM_CLOSE_TEST_PROJECT, (WPARAM)m_pTestControl, 1);
	
	return FALSE;
}

BOOL CMRptBaseFrame::CloseAtsFrameEx()
{
	CTestControlBase *pTestControl = m_pTestControl;
	BOOL bTestControlRef = m_bTestControlRef;

	//CAutoTestBaseFrame::CloseAtsFrameEx();
	CloseAtsFrame();
	CMDIChildWndEx::OnClose();

// 	if (!bTestControlRef)
// 	{
// 		delete pTestControl;
// 	}

	return TRUE;
}
