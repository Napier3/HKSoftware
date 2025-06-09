// SclTextCCFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "..\..\SclFileTest\SCLCompareCheckDev.h"
#include "SclTextCCFrame.h"


/////////////////////////////////////////////////////////////////////////////
// CSclTextCCFrame

IMPLEMENT_DYNCREATE(CSclTextCCFrame, CMDIChildWndEx)
BEGIN_MESSAGE_MAP(CSclTextCCFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

CSclTextCCFrame::CSclTextCCFrame()
{
}

CSclTextCCFrame::~CSclTextCCFrame()
{
	theApp.ClearTextFrameAndView();
}

/////////////////////////////////////////////////////////////////////////////
BOOL CSclTextCCFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
        // TODO: Modify the Window class or styles here by modifying
        //  the CREATESTRUCT cs
        
        if (!CMDIChildWndEx::PreCreateWindow(cs))
        {
                return false;
        }
        
        cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW |
                WS_MAXIMIZE | FWS_ADDTOTITLE;
        return true;
}

BOOL CSclTextCCFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(&rect);

	m_wndSplitter.CreateStatic(this, //父窗口指针
		1, // 切分的行数
		2); // 切分的列数

	m_wndSplitter.CreateView(0,0, // 窗格的行、列序数
		RUNTIME_CLASS(CSclTreeStructView),//视图类
		CSize(rect.Width()/4,rect.Height()),//初始化大小
		pContext);//父窗口的创建参数

	CSclTreeStructView *pSclTreeStructView = (CSclTreeStructView *)m_wndSplitter.GetPane(0, 0);
	theApp.m_pSclTextTreeView = pSclTreeStructView;

	//为第二个窗格产生视图
	m_wndSplitter.CreateView(0,1,
		RUNTIME_CLASS(CSclTextCCView),
		CSize(rect.Width()*3/4,rect.Height()),
		pContext);

	CSclTextCCView *pSclTextCCView = (CSclTextCCView *)m_wndSplitter.GetPane(0, 1);
	theApp.m_pSclTextView = pSclTextCCView;
	pSclTreeStructView->m_treeSclIecDetail.AttachTreeMsgRcvWnd(pSclTextCCView);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSclTextCCFrame diagnostics

#ifdef _DEBUG
void CSclTextCCFrame::AssertValid() const
{
        CMDIChildWndEx::AssertValid();
}

void CSclTextCCFrame::Dump(CDumpContext& dc) const
{
        CMDIChildWndEx::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSclTextCCFrame 消息处理程序

void CSclTextCCFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CMDIChildWndEx::OnClose();
}
