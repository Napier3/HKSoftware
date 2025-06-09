// D:\WorkLiJQ\Source\AutoTest\Module\AudioTest\UI\DviceTypeDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "DviceTypeDlg.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"



// CDviceTypeDlg 对话框

IMPLEMENT_DYNAMIC(CDviceTypeDlg, CDialog)

CDviceTypeDlg::CDviceTypeDlg(CWnd* pParent /*=NULL*/)
	: CAudioDlgBase(CDviceTypeDlg::IDD, pParent)
{
	
}

CDviceTypeDlg::~CDviceTypeDlg()
{
}

void CDviceTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LISTCTRL_DEVICETYPE, m_ListCtrl_DviceType);
}

BEGIN_MESSAGE_MAP(CDviceTypeDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL_DEVICETYPE, &CDviceTypeDlg::OnNMDblclkList)
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL_DEVICETYPE, &CDviceTypeDlg::OnNMClickList)
END_MESSAGE_MAP()

// CDviceTypeDlg 消息处理程序
BOOL CDviceTypeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_static.SubclassDlgItem(IDC_STATIC_DEVICETYPE, this);
	m_font.CreatePointFont(130, _T("Microsoft Sans Serif"));
	m_static.SetFont(&m_font);

	// 为列表视图控件添加全行选中和栅格风格   
	m_ListCtrl_DviceType.SetExtendedStyle(m_ListCtrl_DviceType.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列   
	m_ListCtrl_DviceType.InsertColumn(1, _T("序号"), LVCFMT_CENTER, 50);
	m_ListCtrl_DviceType.InsertColumn(2, _T("装置类型"), LVCFMT_CENTER, 350);

	SetListCtrl(&m_ListCtrl_DviceType);
	SetListData(g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_pDeviceData);

	return TRUE;
}

void CDviceTypeDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(g_pAudioListener->m_bStartParse)
	{
		return;
	}

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//int nLastSelRow = GetCurrentSelectRow();
	if(pNMItemActivate->iItem < 0)
	{
		return;
	}
	SetListSelectRow(pNMItemActivate->iItem);
	*pResult = 0;
}

void CDviceTypeDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnNMDblclkList(pNMHDR,pResult);
	*pResult = 0;
}

/*
CString CDviceTypeDlg::GetDevType()
{
	POSITION pos = m_ListCtrl_DviceType.GetFirstSelectedItemPosition();
	long nIndex = m_ListCtrl_DviceType.GetNextSelectedItem(pos);
	return m_ListCtrl_DviceType.GetItemText(nIndex, 1);
}*/

CString CDviceTypeDlg::GetDevID()
{
	CString strName = GetCurrentResult();
	for (int i = 0; i < g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_pDeviceData->GetCount(); i++)
	{
		CDvmValue* pValue = (CDvmValue*)(g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_pDeviceData->GetAt(i));
		if(pValue->m_strName == strName)
		{
			return pValue->m_strID;
		}
	}
	return "";
}