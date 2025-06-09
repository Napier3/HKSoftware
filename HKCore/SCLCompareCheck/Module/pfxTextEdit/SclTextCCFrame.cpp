// SclTextCCFrame.cpp : ʵ���ļ�
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

	m_wndSplitter.CreateStatic(this, //������ָ��
		1, // �зֵ�����
		2); // �зֵ�����

	m_wndSplitter.CreateView(0,0, // ������С�������
		RUNTIME_CLASS(CSclTreeStructView),//��ͼ��
		CSize(rect.Width()/4,rect.Height()),//��ʼ����С
		pContext);//�����ڵĴ�������

	CSclTreeStructView *pSclTreeStructView = (CSclTreeStructView *)m_wndSplitter.GetPane(0, 0);
	theApp.m_pSclTextTreeView = pSclTreeStructView;

	//Ϊ�ڶ������������ͼ
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
// CSclTextCCFrame ��Ϣ�������

void CSclTextCCFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CMDIChildWndEx::OnClose();
}
