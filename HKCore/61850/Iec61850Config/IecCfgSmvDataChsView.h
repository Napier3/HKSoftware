#pragma once

#include "resource.h"

#include "..\Module\IecCfgTool\IecCfgFile.h"
#include "IecCfgDataChsViewBase.h"
#include "..\Module\UI\IecCfgSmvData92ChsGrid.h"
#include "..\Module\UI\IecCfgSmvData91ChsGrid.h"
#include "..\Module\UI\IecCfgSmvData6044ChsGrid.h"
#include "..\Module\UI\IecCfgSmvData6044CommonChsGrid.h"
#include "afxwin.h"

#include "..\..\Module\XLanguage\XLanguageButton.h" //2016.10.13
// CIecCfgSmvDataChsView 窗体视图

class CIecCfgSmvDataChsView : public CIecCfgDataChsViewBase
{
	DECLARE_DYNCREATE(CIecCfgSmvDataChsView)

public:
	virtual void CreateChsGrid();
	void xlang_InitAndAdjust();//2016.10.13

protected:
	CIecCfgSmvDataChsView();           // 动态创建所使用的受保护的构造函数
	virtual ~CIecCfgSmvDataChsView();
	BOOL CanSetSelectChs(CExBaseList &oListDatas);
	virtual void ShowIecCfgDataChs(CIecCfgDataBase *pIecCfgData);

public:
	enum { IDD = IDD_IECCFG_SMVCTRL_CHS_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL m_bUseMapCur;
	BOOL m_bUseMapVol;
	afx_msg void OnBnClickedBtnSetAbc();
	afx_msg void OnBnClickedBtnSetPabc();
	afx_msg void OnBnClickedBtnSetSabc();
	afx_msg void OnBnClickedBtnSetTabc();
	afx_msg void OnBnClickedBtnSetabc5();
	afx_msg void OnBnClickedBtnSetabc6();
	afx_msg void OnBnClickedBtnSet0();
	afx_msg void OnBnClickedRadioUiselI();
	afx_msg void OnBnClickedRadioUiselU();
	afx_msg void OnBnClickedRadioUiselAll();
	afx_msg void OnBnClickedCheckUsename();
	int m_nUITypeSelIndex;
	BOOL m_bIntelligent;
	CXLanguageButton m_radIecUiselI;  //001 20161013
	CXLanguageButton m_radIecUiselU;  //002 20161013
	CXLanguageButton m_radIecUiselAll;  //003 20161013
	CXLanguageButton m_cheIecUseName;    //004 20161013
	CXLanguageButton m_butIecSetABC;     //005 20161013
	CXLanguageButton m_butIecSetPABC;     //006 20161013
	CXLanguageButton m_butIecSetSABC;      //007 20161013
	CXLanguageButton m_butIecSetTABC;      //008 20161013
	CXLanguageButton m_butIecSetABC5;      //zhouhj20210924
	CXLanguageButton m_butIecSetABC6;      //zhouhj20210924
	CXLanguageButton m_butIecSet0;         //009 20161013
	afx_msg void OnBnClickedBtnSetCheck();
	CButton m_btnSetCheck;
};


