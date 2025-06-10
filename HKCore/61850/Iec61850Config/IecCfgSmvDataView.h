#pragma once

#include "resource.h"
#include "..\Module\IecCfgTool\IecCfgFile.h"
#include "IecCfgDataViewBase.h"

#include "..\Module\UI\IecCfgSmvData92Grid.h"
#include "..\Module\UI\IecCfgSmvData91Grid.h"
#include "..\Module\UI\IecCfgSmvData6044Grid.h"
#include "..\Module\UI\IecCfgSmvData6044CommonGrid.h"

#include "..\module\ui\ieccfgsmvtypecombobox.h"
#include "..\..\module\mfcctrlex\numbercombobox.h"

#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"//2016.10.13
#include "..\..\Module\XLanguage\XLanguageButton.h" //2016.10.13
#include "afxwin.h"

// class CIecCfgSmvDataChsView;
// CIecCfgSmvDataView 窗体视图

class CIecCfgSmvDataView : public CIecCfgDataViewBase
{
	DECLARE_DYNCREATE(CIecCfgSmvDataView)

public:
	virtual void ShowIecCfgData();
	virtual CIecCfgDatasBase* GetIecCfgDatas();
	virtual void CreateIecCfgDataGrid();

	void xlang_InitAndAdjust();//2016.10.13

protected:
	CIecCfgSmvDataView();           // 动态创建所使用的受保护的构造函数
	virtual ~CIecCfgSmvDataView();

	CIecCfgDataSmvCommon* GetIecCfgDataSmvCommon();

public:
	enum { IDD = IDD_IECCFG_SMVCTRL_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	void UpdateSMV_UI(long nSmvType);
	void SetSmpRateFT3_UI();
	void GetSmpRateFT3_UI();
	void SetBautRateFT3_UI();
	void GetBautRateFT3_UI();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CIecCfgSmvTypeComboBox m_cmbIecCfgSmvType;//002 20161013
	CString m_strSmpRate;
	afx_msg void OnCbnSelchangeComboSmvType();
	CNumberComboBox m_cmbAsdu; //006 20161013
	afx_msg void OnEnKillfocusEditSmapRate();
	afx_msg void OnCbnSelchangeComboAsdu();
	afx_msg void OnBnClickedSmvRate();
	BOOL m_bNoQuality;
	BOOL m_bSelDataset;
	BOOL m_bSelSecurity;
	BOOL m_bSelSmpRate;
	BOOL m_bSelRefrTm;
	afx_msg void OnBnClickedCheckQuality();
	afx_msg void OnBnClickedCheckDataset();
	afx_msg void OnBnClickedCheckSecurity();
	afx_msg void OnBnClickedCheckSmpRate();
	afx_msg void OnBnClickedCheckRefrTm();
//	CStatic m_STATIC_MesType;

/*	CXLanguageTextWnd m_wndTitleTask;//2016.10.13
	CXLanguageButton m_btnCancel;//2016.10.13
	CXLanguageTextWnd m_wndTestInf;//2016.10.13
	CXLanguageTextWnd m_wndTaskName;//2016.10.13
	CXLanguageTextWnd m_wndTestType;//2016.10.13
	CXLanguageTextWnd m_wndProSet;//2016.10.13
	CEdit m_edtName;//2016.10.13
	CXLanguageButton m_btnBrowse;//2016.10.13
	CXLanguageTextWnd m_wndPoFile;//2016.10.13
	CXLanguageTextWnd m_wndChoTest;//2016.10.13 */
	CXLanguageTextWnd m_staIecMesType; //001 20161013
	CStatic m_staIecSampleRate; //003 20161013
	CEdit m_ediIecSmapRate;  //004 20161013
	CXLanguageTextWnd m_staIecASDU;  //005 20161013
	CXLanguageButton m_cheIecQuality;  //007 20161013
	CXLanguageButton m_butIecSMVRate;  //008 20161013
	afx_msg void OnStnClickedStaticSamplerate();
	afx_msg void OnStnClickedStaticMestype();
	afx_msg void OnEnChangeEditSmapRate();
	afx_msg void OnStnClickedStaticAsdu();

private:
	void UpdateOptionalDatas();//zhouhj 20210320 更新可选项参数值
public:
	CButton m_btnDataset;
	CStatic m_stcSmpRateFT3;
	CComboBox m_cmbSmpRateFT3;
	CStatic m_stcBaudRateFT3;
	CComboBox m_cmbBaudRateFT3;
	afx_msg void OnCbnSelchangeComboSmpRateFt3();
	afx_msg void OnCbnSelchangeComboBaudRateFt3();

protected:
	CRect m_rcSmpRateFT3_Stc;
	CRect m_rcSmpRateFT3_Cmb;
	CRect m_rcBaudRateFT3_Stc;
	CRect m_rcBaudRateFT3_Cmb;
};


