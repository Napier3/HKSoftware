// XFileMngrFrameEx.cpp : 实现文件
//

#include "stdafx.h"
// #include "StationTestMain.h"
#include "XFileMngrFrameEx.h"

#include "XFileMngrFolderView.h"
#include "XFileMngrListView.h"

#include "XFileMngrDoc.h"
#include "DocFrameMngr.h"

// CXFileMngrFrameEx

IMPLEMENT_DYNCREATE(CXFileMngrFrameEx, CMDIChildWndEx)

CXFileMngrFrameEx::CXFileMngrFrameEx()
{
	m_pXFileMngrListView   = NULL;
	m_pXFileMngrListView_Remote = NULL;
	m_pXFileMngrFolderView = NULL;
	m_pXFileMngrDoc = NULL;
}

CXFileMngrFrameEx::~CXFileMngrFrameEx()
{
}


CXFileMngrFrameEx* UI_GetCXFileMngrFrameEx(CView *pView)
{
	CWnd *pParent = pView->GetParent();
	CXFileMngrFrameEx *Find = NULL;

	while (pParent != NULL)
	{
		if (pParent->IsKindOf(RUNTIME_CLASS(CXFileMngrFrameEx)) )
		{
			Find = (CXFileMngrFrameEx*)pParent;
			break;
		}

	}

	return Find;
}


BOOL CXFileMngrFrameEx::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(&rect);

	m_wndSplitter.CreateStatic(this, //父窗口指针
		1, // 切分的行数
		2); // 切分的列数

	m_wndSplitter.CreateView(0,0, // 窗格的行、列序数
		RUNTIME_CLASS(CXFileMngrFolderView),//视图类
		CSize(rect.Width()/3,rect.Height()),//初始化大小
		pContext);//父窗口的创建参数

	//为第二个窗格产生视图
// 	m_wndSplitter.CreateView(0,1,
// 		RUNTIME_CLASS(CXFileMngrListView),
// 		CSize(rect.Width()*2/3,rect.Height()),
// 		pContext);

	//右边再分割上下两个视图
	if(m_wndSplitter_Right.CreateStatic(&m_wndSplitter,2,1,WS_CHILD|WS_VISIBLE,
		m_wndSplitter.IdFromRowCol(0, 1)) == NULL)
	{
		return FALSE; //将第1行0列再分开1行2列
	}
		
	m_wndSplitter_Right.CreateView(0,0
		,RUNTIME_CLASS(CXFileMngrListView)
		,CSize(rect.Width()*2/3,rect.Height()/2)
		,pContext);

	m_wndSplitter_Right.CreateView(1,0
		,RUNTIME_CLASS(CXFileMngrListView)
		,CSize(rect.Width()*2/3,rect.Height()/2)
		,pContext);

	m_pXFileMngrFolderView = (CXFileMngrFolderView*)m_wndSplitter.GetPane(0, 0);
	m_pXFileMngrListView_Remote = (CXFileMngrListView*)m_wndSplitter_Right.GetPane(0, 0);
	m_pXFileMngrListView   = (CXFileMngrListView*)m_wndSplitter_Right.GetPane(1, 0);

	CXFolderTreeCtrl *pXFolderTreeCtrl = m_pXFileMngrFolderView->GetXFolderTreeCtrl();
	CXFileListView   *pXFileListView    = m_pXFileMngrListView->GetXFileListView();
	CXFileListView   *pXFileListView_Remote = m_pXFileMngrListView_Remote->GetXFileListView();

	pXFileListView->SetType_XFileView(Type_XFileView_Local);
	pXFileListView_Remote->SetType_XFileView(Type_XFileView_Remote);
	m_pXFileMngrFolderView->AttachXFileListViewEx(pXFileListView,pXFileListView_Remote,this);
	m_pXFileMngrListView->AttatchXFolderTreeCtrl(pXFolderTreeCtrl, this);
	m_pXFileMngrListView_Remote->AttatchXFolderTreeCtrl(pXFolderTreeCtrl, this);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CXFileMngrFrameEx, CMDIChildWndEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CXFileMngrFrameEx 消息处理程序

void CXFileMngrFrameEx::OnClose()
{
	CDocFrameMngr::CloseDocFrame(m_strDocID);

	CMDIChildWndEx::OnClose();
}


void CXFileMngrFrameEx::ShowXFileMngr(CXFileMngr *pXFileMngr)
{
// 	m_pXFileMngrRef = pXFileMngr;
	CXFolderTreeCtrl *pXFolderTreeCtrl = m_pXFileMngrFolderView->GetXFolderTreeCtrl();
	CXFileListView   *pXFileListView    = m_pXFileMngrListView->GetXFileListView();
	CXFileListView   *pXFileListView_Remote = m_pXFileMngrListView_Remote->GetXFileListView();
	pXFolderTreeCtrl->SetXFileMsgRcvWnd((CXFileMngrDoc*)m_pXFileMngrDoc);

	m_pXFileMngrFolderView->ShowXFileMngr(pXFileMngr);
}

void CXFileMngrFrameEx::SetFramwWnd(CWnd *pFrameWnd)
{
	ASSERT (m_pXFileMngrListView != NULL);
	CXFileListView   *pXFileListView    = m_pXFileMngrListView->GetXFileListView();
	pXFileListView->SetFrameWnd(pFrameWnd);

	CXFileListView   *pXFileListView_Remote = m_pXFileMngrListView_Remote->GetXFileListView();
	pXFileListView_Remote->SetFrameWnd(pFrameWnd);
}

void CXFileMngrFrameEx::ExecXFile(CXFile *pFile)
{

}
