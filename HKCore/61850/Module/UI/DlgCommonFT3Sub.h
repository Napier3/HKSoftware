#pragma once
#include "DlgCommonFT3Pub.h"
#include "../CfgDataMngr/IecCfg6044CommonChIn.h"

class CDlgCommonFT3Sub : public CDlgCommonFT3Pub
{
public:
	CDlgCommonFT3Sub(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCommonFT3Sub();
	virtual void InitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboxBit0();
	afx_msg void OnCbnSelchangeComboxBit1();
	afx_msg void OnCbnSelchangeComboxBit2();
	afx_msg void OnCbnSelchangeComboxBit3();
	afx_msg void OnCbnSelchangeComboxBit4();
	afx_msg void OnCbnSelchangeComboxBit5();
	afx_msg void OnCbnSelchangeComboxBit6();
	afx_msg void OnCbnSelchangeComboxBit7();
	afx_msg void OnCbnSelchangeComboxBit8();
	afx_msg void OnCbnSelchangeComboxBit9();
	afx_msg void OnCbnSelchangeComboxBit10();
	afx_msg void OnCbnSelchangeComboxBit11();
	afx_msg void OnCbnSelchangeComboxBit12();
	afx_msg void OnCbnSelchangeComboxBit13();
	afx_msg void OnCbnSelchangeComboxBit14();
	afx_msg void OnCbnSelchangeComboxBit15();
protected:
	BOOL IsBinMapRepeat(int nBitIndex);
	void InitChMapCombox();
	void SaveChMapCombox();
	virtual void OnOK();
	virtual void OnCancel();
	void OnCbnSelchangeComboxBit(int nIndex);

public:
	CIecCfg6044CommonCh *m_pCfg6044CommonCh;
	int m_nBitSelIndex[IECCFG_COMMON_FT3_BIT_NUM];

};
