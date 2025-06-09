// D:\WorkLiJQ\Source\AutoTest\Module\AudioTest\UI\ProtocolTypeDlg.cpp : 实现文件
#include "stdafx.h"
#include "ProtocolTypeDlg.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"
// CProtocolTypeDlg 对话框

IMPLEMENT_DYNAMIC(CProtocolTypeDlg, CDialog)

CProtocolTypeDlg::CProtocolTypeDlg(CWnd* pParent /*=NULL*/)
	: CAudioDlgBase(CProtocolTypeDlg::IDD, pParent)
{

}

CProtocolTypeDlg::~CProtocolTypeDlg()
{
}

void CProtocolTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LISTCTRL_PROTOCOLTYPE, m_ListCtrl_ProtocolType);
}

BEGIN_MESSAGE_MAP(CProtocolTypeDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL_PROTOCOLTYPE, &CProtocolTypeDlg::OnNMDblclkList)
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL_PROTOCOLTYPE, &CProtocolTypeDlg::OnNMClickList)
END_MESSAGE_MAP()
// CProtocolTypeDlg 消息处理程序

BOOL CProtocolTypeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_static.SubclassDlgItem(IDC_STATIC_PROTOCPL, this);
	m_font.CreatePointFont(130, _T("Microsoft Sans Serif"));
	m_static.SetFont(&m_font);

	// 为列表视图控件添加全行选中和栅格风格   
	m_ListCtrl_ProtocolType.SetExtendedStyle(m_ListCtrl_ProtocolType.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列   
	m_ListCtrl_ProtocolType.InsertColumn(1, _T("序号"), LVCFMT_CENTER, 50);
	m_ListCtrl_ProtocolType.InsertColumn(2, _T("规约类型"), LVCFMT_CENTER, 350);
	// 在列表视图控件中插入列表项，并设置列表子项文本   

	SetListCtrl(&m_ListCtrl_ProtocolType);
	SetListData(g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_pProtocolData);

	return true;
}

void CProtocolTypeDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(g_pAudioListener->m_bStartParse)
	{
		return;
	}

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem < 0)
	{
		return;
	}
	//int nLastSelRow = GetCurrentSelectRow();
	SetListSelectRow(pNMItemActivate->iItem);
	*pResult = 0;
}

void CProtocolTypeDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnNMDblclkList(pNMHDR,pResult);
	*pResult = 0;
}



