#pragma once

#include "AT02D_CBsDlg.h"

#include "../Module/SCL/SclIecCfgDatas.h"
#include "afxwin.h"


// CSelectAT02D_CBDlg 对话框

class CSelectAT02D_CBDlg : public CDialog,  public CExBaseListGridOptrInterface
{
	DECLARE_DYNAMIC(CSelectAT02D_CBDlg)

public:
	CSelectAT02D_CBDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSelectAT02D_CBDlg();

	CMFCTabCtrl m_tabPara;
	CAT02D_CBsDlg m_oSMV_AT02D_View;
	CAT02D_CBsDlg m_oGsSubAT02D_View;
	CAT02D_CBsDlg m_oGsPubAT02D_View;
	CSclStation *m_pCurSclStation;

	CSclCtrlsSmvIn m_oSMVList;
	CSclCtrlsGsIn m_oGinList;
	CSclCtrlsGsOut m_oGoutList;

	long m_nMaxFiberNum;
// 对话框数据
	enum { IDD = IDD_DLG_AT02D_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	void UpdateCurSelCB_Num();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
protected:
	virtual void OnOK();
public:
	CStatic m_stcLogMsg;
	CComboBox m_cmbMaxFiberNum;
};
