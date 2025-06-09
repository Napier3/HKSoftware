
// TestGridVs2008Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestGridVs2008.h"
#include "TestGridVs2008Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestGridVs2008Dlg 对话框




CTestGridVs2008Dlg::CTestGridVs2008Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestGridVs2008Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestGridVs2008Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestGridVs2008Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CTestGridVs2008Dlg 消息处理程序

BOOL CTestGridVs2008Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CreateGrid();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestGridVs2008Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestGridVs2008Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestGridVs2008Dlg::CreateGrid()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	rcClient.left = 5;
	rcClient.top = 5;
	rcClient.right -= 5;
	rcClient.bottom -= 50;
	m_gridex.Create(rcClient, this, IDC_CUSTOM1+1000);
	m_gridex.InitGrid(60);
	//m_gridex.CreateTitleTip();
	m_gridex.InitData();
	m_gridex.SelectRow(4);	
}