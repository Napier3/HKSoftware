// AT02D_CBsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "AT02D_CBsDlg.h"


// CAT02D_CBsDlg 对话框

IMPLEMENT_DYNAMIC(CAT02D_CBsDlg, CDialog)

CAT02D_CBsDlg::CAT02D_CBsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAT02D_CBsDlg::IDD, pParent)
{
	m_pCurDatasList = NULL;
	m_pDataViewOptrInterface = NULL;
}

CAT02D_CBsDlg::~CAT02D_CBsDlg()
{
}

void CAT02D_CBsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAT02D_CBsDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CAT02D_CBsDlg 消息处理程序

BOOL CAT02D_CBsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rcGrid;
	GetClientRect(&rcGrid);
	rcGrid.top = 5;
	rcGrid.left = 5;
	rcGrid.right -= 5;
	rcGrid.bottom -= 5;

	m_oSclIecCfgCtrlGrid.Create(rcGrid, this, IDC_GRID_SCLIECCFG_CTRL);
	m_oSclIecCfgCtrlGrid.SetFont(g_pGlobalFont11);
	m_oSclIecCfgCtrlGrid.InitGrid();
	m_oSclIecCfgCtrlGrid.AttachDataViewOptrInterface(m_pDataViewOptrInterface); 
	ShowGridDatas(m_pCurDatasList);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAT02D_CBsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (!::IsWindow(m_oSclIecCfgCtrlGrid.m_hWnd))
	{
		return;
	}

	CRect rcClient;
	GetClientRect(&rcClient);
	m_oSclIecCfgCtrlGrid.MoveWindow(0, 0, rcClient.Width(), rcClient.Height());
}

void CAT02D_CBsDlg::ShowGridDatas(CExBaseList *pDatas)
{
	if (pDatas == NULL)
	{
		m_oSclIecCfgCtrlGrid.SetRowCount(1);
		m_oSclIecCfgCtrlGrid.Invalidate(FALSE);
		return ;
	}

	//ASSERT (m_pSclFile != NULL);
	m_oSclIecCfgCtrlGrid.AttachDatas(pDatas);//&pSclFileFrame->m_oSclStation);
	m_oSclIecCfgCtrlGrid.InitGridTitle();
	CSclCtrls *pSclCtrls = (CSclCtrls*)pDatas;

// 	if (!pSclCtrls->IsRead())
// 	{
// 		m_oSclIecCfgCtrlGrid.SetRowCount(1);
// 		return ;
// 	}

	m_oSclIecCfgCtrlGrid.ShowDatas(pDatas);
	m_oSclIecCfgCtrlGrid.SelectRow(1);
}
