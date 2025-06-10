#pragma once


#include "SclFileCtrlChsView.h"
#include "afxwin.h"

#include "..\..\Module\XLanguage\XLanguageButton.h" //2016.10.13

// CSclFileCtrlView 窗体视图

class CSclFileCtrlView : public CFormView
{
	DECLARE_DYNCREATE(CSclFileCtrlView)

public:
	CSclFileCtrlChsView *m_pChsView;
	CView *m_pSclFileTreeView;
	CSclFile *m_pSclFile;
	long m_cxMIn, m_cyMin;

	void UpdateIecCfgFilesComboBox();

	void xlang_InitAndAdjust();//2016.10.13

protected:
	CSclFileCtrlView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSclFileCtrlView();
	CSclIecCfgCtrlGrid m_oSclIecCfgCtrlGrid;
	CRect m_rcCtrlsOrigin[7];
	UINT m_nOldSclDatasClassID;

	CSclCtrls *m_pCurrSelSclCtrls;

	void ShowGridDatas(CExBaseList *pDatas);
	void InitComboBoxIecCfgType(CExBaseList *pDatas);
	CExBaseObject* GetDestIecCfgFile();
	UINT GetDestIecCfgDataClassID();

public:
	enum { IDD = IDD_SCLFILE_CTRL_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	LRESULT OnSclIecCfgCtrlSelected(WPARAM wParam, LPARAM lParam);
	LRESULT OnSclIecCfgCtrlsSelected(WPARAM wParam, LPARAM lParam);

public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	CXLanguageButton m_btnAddTo;  //002  20161013
	CComboBox m_cmbIecCfgFile;  //003  20161013
	CComboBox m_cmbIecCfgType;   //004  20161013
	afx_msg void OnBnClickedBtnAddto();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CXLanguageButton m_btnOverwrite;   //005  20161013
	CXLanguageButton m_btnCompare;     //006  20161013
	afx_msg void OnBnClickedBtnOverrite();
	afx_msg void OnBnClickedBtnCompare();
	afx_msg void OnBnClickedBtnExport();
	CXLanguageButton m_btnExport;   //007  20161013
//	afx_msg void OnBnClickedCheckAll();
//	CXLanguageButton m_btnAllSel;  //001  20161013
	afx_msg void OnCbnSelchangeComboIeccfgFile();
	afx_msg void OnCbnSelchangeComboIeccfgType();
	CButton m_btnOneKeyCfg;
	afx_msg void OnBnClickedBtnOneKeyCfg();
};


