#pragma once
#include "afxcmn.h"

#include "..\DialogBase\DynDialogEx.h"
#include "..\BaseClass\ExBaseListComboBox.h"
#include "..\DataMngr\DvmDataset.h"
// CDlgXFileNameGen 对话框


#define XIDC_COMBO_DATA	         7100
#define XIDC_COMBO_TITLE         7200
#define XIDC_COMBO_CONNFLAG      7300
#define XIDC_COMBO_MAX           20
#define XIDC_COMBO_DATAMAX	     (XIDC_COMBO_DATA+XIDC_COMBO_MAX)

#define XON_CBN_SELCHANGE_RANGE(id, idLast, memberFxn) \
	ON_CONTROL_RANGE(CBN_SELCHANGE, id, idLast, memberFxn)
#define XON_CBN_EDITCHANGE_RANGE(id, idLast, memberFxn) \
	ON_CONTROL_RANGE(CBN_EDITCHANGE, id, idLast, memberFxn)

class CDlgXFileNameGen : public CDynDialogEx
{
	DECLARE_DYNAMIC(CDlgXFileNameGen)

public:
	CDlgXFileNameGen(const CString &strNameGenConfigFile,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgXFileNameGen();

	CString m_strFileName;

protected:
	BOOL SaveXmlFile();
	BOOL OpenXmlFile();
	void CreateControls();

	CDvmDataset m_oFngDataset;
	CString m_strNameGenConfigFile;
	long m_nDlgWidth, m_nDlgHeight;
	CDvmData m_oDataFlag;

public:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CStatic   m_stcTitle[XIDC_COMBO_MAX];
	CExBaseListComboBox m_cmbDataType[XIDC_COMBO_MAX];
	CExBaseListComboBox m_cmbConnFlag[XIDC_COMBO_MAX];

	CButton m_btnOK;
	CButton m_btnCancel;

	virtual int DoModal(); 
public:
	afx_msg void OnBnClickedOk();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeDataType(UINT nID);
	afx_msg void OnCbnEditchangeDataType(UINT nID);
};
