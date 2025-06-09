// VirLoopSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SclCheckSetDlg.h"


// CSclCheckSetDlg 对话框

IMPLEMENT_DYNAMIC(CSclCheckSetDlg, CDialog)

CSclCheckSetDlg::CSclCheckSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSclCheckSetDlg::IDD, pParent)
{
	m_cxMIn =  m_cyMin = 0;
}

CSclCheckSetDlg::~CSclCheckSetDlg()
{
}

void CSclCheckSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSclCheckSetDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CSclCheckSetDlg 消息处理程序

BOOL CSclCheckSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(m_strTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSclCheckSetDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (!::IsWindow(m_tabPara.m_hWnd))
	{
		return;
	}

	CRect rcClient;
	GetClientRect(&rcClient);
	m_tabPara.MoveWindow(0, 0, rcClient.Width(), rcClient.Height()-50);
}

int CSclCheckSetDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;

	m_tabPara.Create(CMFCTabCtrl::STYLE_3D_ROUNDED ,CRect(0, 0, 0, 0), this, 1000, CMFCTabCtrl::LOCATION_TOP);

	if (m_schemaDlg.Create(IDD_CTRLDLG_SCLCHECK, &m_tabPara))
	{
		m_tabPara.AddTab(&m_schemaDlg, _T("Schema语法检查设置"));
	}

	if (m_DLT860ModelDlg.Create(IDD_CTRLDLG_SCLCHECK, &m_tabPara))
	{
		m_tabPara.AddTab(&m_DLT860ModelDlg, _T("DL/T860数据类型检查设置"));
	}

	if (m_ProjAppModelDlg.Create(IDD_CTRLDLG_SCLCHECK, &m_tabPara))
	{
		m_tabPara.AddTab(&m_ProjAppModelDlg, _T("工程应用模型规范性检查设置"));
	}
	
	if (m_virLoopDlg.Create(IDD_CTRLDLG_SCLCHECK, &m_tabPara))
	{
		m_tabPara.AddTab(&m_virLoopDlg, _T("虚回路相关检查设置"));
	}
	m_tabPara.EnableTabSwap(TRUE);//可以拖拽

	CArray<COLORREF,COLORREF> arColors;

	arColors.Add(RGB (121, 210, 231));
	arColors.Add(RGB (190, 218, 153));
	arColors.Add(RGB (255, 170, 100));
	arColors.Add(RGB (255, 255, 0));

	m_tabPara.EnableAutoColor(TRUE);
	m_tabPara.SetAutoColors(arColors);

	return 0;
}