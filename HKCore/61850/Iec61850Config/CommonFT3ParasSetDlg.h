#pragma once
#include "../Module/CfgDataMngr/IecCfgDataSmvCommon.h"


// CCommonFT3ParasSetDlg �Ի���

class CCommonFT3ParasSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CCommonFT3ParasSetDlg)

public:
	CCommonFT3ParasSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommonFT3ParasSetDlg();

// �Ի�������
	enum { IDD = IDD_IECCFG_FT3COMMON_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitParas(CIecCfgDataSmvCommon *pCommonData);
	void GetCommonDataValues(CIecCfgDataSmvCommon *pCommonData);

protected:
	long m_nDcVolCodeValue;
	long m_nDcCurCodeValue;
	long m_nDcNeutralVolCodeValue;
	float m_fDcVolPrimValue;
	float m_fDcCurPrimValue;
	float m_fDcNeutralVolPrimValue;
public:
	long m_nProtCurCodeValue;
	long m_nMeasCurCodeValue;
	long m_nAC_VolCodeValue;
	float m_fProtCurPrimValue;
	float m_fMeasCurPrimValue;
	float m_fAC_VolPrimValue;
};
