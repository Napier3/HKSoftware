// D:\WorkLiJQ\Source\AutoTest\Module\AudioTest\UI\ProtocolTypeDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "ProtocolTypeDlg.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../AudioTest/AudioTestDlg.h"
// CProtocolTypeDlg �Ի���

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
// CProtocolTypeDlg ��Ϣ�������

BOOL CProtocolTypeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_static.SubclassDlgItem(IDC_STATIC_PROTOCPL, this);
	m_font.CreatePointFont(130, _T("Microsoft Sans Serif"));
	m_static.SetFont(&m_font);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_ListCtrl_ProtocolType.SetExtendedStyle(m_ListCtrl_ProtocolType.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������   
	m_ListCtrl_ProtocolType.InsertColumn(1, _T("���"), LVCFMT_CENTER, 50);
	m_ListCtrl_ProtocolType.InsertColumn(2, _T("��Լ����"), LVCFMT_CENTER, 350);
	// ���б���ͼ�ؼ��в����б���������б������ı�   

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnNMDblclkList(pNMHDR,pResult);
	*pResult = 0;
}



