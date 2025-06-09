#pragma once
#include "afxwin.h"

#include "..\..\..\iSmartTestWzd\Resource.h"

#include "..\..\..\..\Module\BaseClass\ExBaseListTreeCtrl.h"

#include "../../../../Module/Acrobat/PdfXmlParseSets.h"
#include "../../../../Module/Acrobat/PdfDBInfo.h"

#include "../StepCtrl/WzdDlgStyleGrid.h"
#include "../StepCtrl/WzdDlgComboBox.h"
#include "../StepCtrl/DvmReadTreeCtrl.h"
#include "../StepCtrl/WzdDlgButton.h"
#include "../../../../Module/Acrobat/SetsFileManualConfirmInterface.h"
#include "../../../../Module/Acrobat/PdfXmlParseSets.h"


#include "afxcmn.h"
// SelTable 对话框

class CPdfXmlStringTable;


class SelTypeGrid : public CWzdDlgStyleGrid
{
public:
	int m_nCount;

public:
 	void InitGrid();
	void InitGridTitle();
	void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow =TRUE);
//	virtual CString GetGridClassID() { return "CIECCfgAddTypeGrid"; }
};

class SelTable : public CDialog, public CSetsFileManualConfirmInterface
{
	DECLARE_DYNAMIC(SelTable)

public:
	SelTable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SelTable();

	CPdfXmlStringTable *m_pSelectTable;

// 对话框数据
	enum { IDD = IDD_DIALOG_SELTABLE };

	void ShowManualConfirm();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void SetCMB(CComboBox *cmb,int count);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();

public:
	virtual BOOL OnInitDialog();

	CExBaseListTreeCtrl m_Tree;
	void LoadTreeData();

	afx_msg void OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	CWzdDlgComboBox m_CmbName;
	CWzdDlgComboBox m_CmbVal;
	CWzdDlgComboBox m_CmbDW;
	SelTypeGrid m_Gird;

	CString m_strTableName;
	void UpdateDlg_Grid();
	void UpdateDlg_CMB();

	void SetSelectTable(CExBaseObject* pSelectTable);
	
public:	
	BOOL CheckTableData();
	void SetTableNoUse();

	afx_msg void OnCbnSelchangeCmbName();
	afx_msg void OnCbnSelchangeCmbVal();
	afx_msg void OnCbnSelchangeCmbDw();
	void ChangeTableInfo();
	void SaveTableConfig();

	void Addtile();
	void Deltile();

	afx_msg void OnBnClickedRadioNouse();
	afx_msg void OnBnClickedRadioParameter();
	afx_msg void OnBnClickedRadioEna();
	afx_msg void OnBnClickedRadioSetting();
	afx_msg void OnBnClickedRadioMatrix();
	void SetClickedRadio(int iRadio);
	void ShowClickedRadio(CString strIdentify);
	
	CButton m_radioNoUse;
	CButton m_radioParameter;
	CButton m_radioEna;
	CButton m_radioSetting;
	CButton m_radioMatrix;

	CButton m_CheckHeadBtn;
	afx_msg void OnBnClickedCheckHead();
	afx_msg void OnClose();
};
