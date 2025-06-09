#include "stdafx.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"

#include "../../AudioTest/UI/InspectTypeDlg.h"



// CInspectTypeDlg �Ի���

IMPLEMENT_DYNAMIC(CInspectTypeDlg, CDialog)

CInspectTypeDlg::CInspectTypeDlg(CWnd* pParent /*=NULL*/)
	: CAudioDlgBase(CInspectTypeDlg::IDD, pParent)
{

}

CInspectTypeDlg::~CInspectTypeDlg()
{
}

void CInspectTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LISTCTRL_INSPECTTYPE, m_ListCtrl_InspectType);
}


BEGIN_MESSAGE_MAP(CInspectTypeDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL_INSPECTTYPE, &CInspectTypeDlg::OnNMDblclkList)
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL_INSPECTTYPE, &CInspectTypeDlg::OnNMClickList)
END_MESSAGE_MAP()


// CInspectTypeDlg ��Ϣ�������

BOOL CInspectTypeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_static.SubclassDlgItem(IDC_STATIC_INSPECT, this);
	m_font.CreatePointFont(130, _T("Microsoft Sans Serif"));
	m_static.SetFont(&m_font);

	//LVS_EX_TRACKSELECT|LVS_EX_ONECLICKACTIVATE 
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_ListCtrl_InspectType.SetExtendedStyle(m_ListCtrl_InspectType.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������   
	m_ListCtrl_InspectType.InsertColumn(1, _T("���"), LVCFMT_CENTER, 50);
	m_ListCtrl_InspectType.InsertColumn(2, _T("��������"), LVCFMT_CENTER, 350);
	// ���б���ͼ�ؼ��в����б���������б������ı�   

	SetListCtrl(&m_ListCtrl_InspectType);
	SetListData(g_pAudioTestDlg->m_pAudioParser->m_oConfigMngr.m_pInspectData);
	return TRUE;
}

void CInspectTypeDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
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

void CInspectTypeDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnNMDblclkList(pNMHDR,pResult);
	*pResult = 0;
}
