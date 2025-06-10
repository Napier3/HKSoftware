// CommonFT3ParasSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "CommonFT3ParasSetDlg.h"


// CCommonFT3ParasSetDlg 对话框

IMPLEMENT_DYNAMIC(CCommonFT3ParasSetDlg, CDialog)

CCommonFT3ParasSetDlg::CCommonFT3ParasSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommonFT3ParasSetDlg::IDD, pParent)
	, m_nDcVolCodeValue(1)
	, m_nDcCurCodeValue(1)
	, m_nDcNeutralVolCodeValue(1)
	, m_fDcVolPrimValue(100)
	, m_fDcCurPrimValue(1000)
	, m_fDcNeutralVolPrimValue(100)
	, m_nProtCurCodeValue(1)
	, m_nMeasCurCodeValue(1)
	, m_nAC_VolCodeValue(1)
	, m_fProtCurPrimValue(1000)
	, m_fMeasCurPrimValue(1000)
	, m_fAC_VolPrimValue(100)
{

}

CCommonFT3ParasSetDlg::~CCommonFT3ParasSetDlg()
{
}

void CCommonFT3ParasSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DC_VOL_CODE_VALUE, m_nDcVolCodeValue);
	DDV_MinMaxLong(pDX, m_nDcVolCodeValue, 1, 100000);
	DDX_Text(pDX, IDC_EDIT_DC_CUR_CODE_VALUE, m_nDcCurCodeValue);
	DDV_MinMaxLong(pDX, m_nDcCurCodeValue, 1, 100000);
	DDX_Text(pDX, IDC_EDIT_DC_NEUTRAL_VOL_CODE_VALUE, m_nDcNeutralVolCodeValue);
	DDV_MinMaxLong(pDX, m_nDcNeutralVolCodeValue, 1, 100000);
	DDX_Text(pDX, IDC_EDIT_DC_VOL_PRIM_VALUE, m_fDcVolPrimValue);
	DDV_MinMaxFloat(pDX, m_fDcVolPrimValue, 0.01, 10000);
	DDX_Text(pDX, IDC_EDIT_DC_CUR_PRIM_VALUE, m_fDcCurPrimValue);
	DDV_MinMaxFloat(pDX, m_fDcCurPrimValue, 0.01, 100000);
	DDX_Text(pDX, IDC_EDIT_DC_NEUTRAL_VOL_PRIM_VALUE, m_fDcNeutralVolPrimValue);
	DDV_MinMaxFloat(pDX, m_fDcNeutralVolPrimValue, 0.01, 10000);
	DDX_Text(pDX, IDC_EDIT_AC_PROT_CUR_CODE_VALUE, m_nProtCurCodeValue);
	DDV_MinMaxLong(pDX, m_nProtCurCodeValue, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_AC_MEAS_CUR_CODE_VALUE, m_nMeasCurCodeValue);
	DDV_MinMaxLong(pDX, m_nMeasCurCodeValue, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_AC__VOL_CODE_VALUE, m_nAC_VolCodeValue);
	DDV_MinMaxLong(pDX, m_nAC_VolCodeValue, 1, 65535);
	DDX_Text(pDX, IDC_EDIT_AC_PROT_CUR_PRIM_VALUE, m_fProtCurPrimValue);
	DDV_MinMaxFloat(pDX, m_fProtCurPrimValue, 0.01, 1000000);
	DDX_Text(pDX, IDC_EDIT_AC_MEAS_CUR_PRIM_VALUE, m_fMeasCurPrimValue);
	DDV_MinMaxFloat(pDX, m_fMeasCurPrimValue, 0.01, 100000);
	DDX_Text(pDX, IDC_EDIT_AC_VOL_PRIM_VALUE, m_fAC_VolPrimValue);
	DDV_MinMaxFloat(pDX, m_fAC_VolPrimValue, 0.01, 10000);
}


BEGIN_MESSAGE_MAP(CCommonFT3ParasSetDlg, CDialog)
END_MESSAGE_MAP()


// CCommonFT3ParasSetDlg 消息处理程序

BOOL CCommonFT3ParasSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCommonFT3ParasSetDlg::InitParas(CIecCfgDataSmvCommon *pCommonData)
{
	m_nDcVolCodeValue = pCommonData->m_nDcVol;
	m_nDcCurCodeValue = pCommonData->m_nDcCur;
	m_nDcNeutralVolCodeValue = pCommonData->m_nDcNeuatralVol;
	m_fDcVolPrimValue = pCommonData->m_dDcVolPrim;
	m_fDcCurPrimValue = pCommonData->m_dDcCurPrim;
	m_fDcNeutralVolPrimValue = pCommonData->m_dDcNeutralPrim;

	m_nProtCurCodeValue = pCommonData->m_nSCP;
	m_nMeasCurCodeValue = pCommonData->m_nSCM;
	m_nAC_VolCodeValue = pCommonData->m_nSV;
	m_fProtCurPrimValue = pCommonData->m_dInomProt;
	m_fMeasCurPrimValue = pCommonData->m_dInomMeas;
	m_fAC_VolPrimValue = pCommonData->m_fUNom;

}

void CCommonFT3ParasSetDlg::GetCommonDataValues(CIecCfgDataSmvCommon *pCommonData)
{
	pCommonData->m_nDcVol = m_nDcVolCodeValue;
	pCommonData->m_nDcCur = m_nDcCurCodeValue;
	pCommonData->m_nDcNeuatralVol = m_nDcNeutralVolCodeValue;
	pCommonData->m_dDcVolPrim = m_fDcVolPrimValue;
	pCommonData->m_dDcCurPrim = m_fDcCurPrimValue;
	pCommonData->m_dDcNeutralPrim = m_fDcNeutralVolPrimValue;

	pCommonData->m_nSCP = m_nProtCurCodeValue;
	pCommonData->m_nSCM = m_nMeasCurCodeValue;
	pCommonData->m_nSV = m_nAC_VolCodeValue;
	pCommonData->m_dInomProt = m_fProtCurPrimValue;
	pCommonData->m_dInomMeas = m_fMeasCurPrimValue;
	pCommonData->m_fUNom = m_fAC_VolPrimValue;
}