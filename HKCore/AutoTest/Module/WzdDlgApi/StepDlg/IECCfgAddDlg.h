#pragma once
#include "../StepCtrl/WzdDlgButton.h"
#include "../StepCtrl/WzdDlgTabCtrl.h"
#include "../StepCtrl/WzdDlgStyleGrid.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../iSmartTestWzd/Resource.h"

class CIECCfgAddTypeGrid : public CWzdDlgStyleGrid
{
public:
	long m_nFilter;

public:
	void InitGrid();
	void InitGridTitle();
	
	void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow =TRUE);
	virtual CString GetGridClassID() { return "CIECCfgAddTypeGrid"; }
};

class CIECCfgAddAppGrid : public CWzdDlgStyleGrid
{
private:
	CExBaseList m_oList;

public:
	void InitGrid();
	void InitGridTitle();
	BOOL IsCtrlExisted(CSclCtrlBase* pData);
	void AddNewCtrl(CSclCtrlBase* pData);
	void DeleteCtrl(CSclCtrlBase* pData);
	void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow =TRUE);
	CExBaseList* GetAddCtrls();
	void RemoveAllCtrl();
	virtual CString GetGridClassID() { return "CIECCfgAddAppGrid"; }

	static void EndEditCell_AddCtrl(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
};

class CIECCfgAddChsGrid : public CWzdDlgStyleGrid
{
public:
	void InitGrid();
	void InitGridTitle();

	void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow =TRUE);
	virtual CString GetGridClassID() { return "CIECCfgAddChsGrid"; }

public:
	void ShowData_GooseInputChn(CSclChGsIn *pChn,int nRow);
	void ShowData_GooseOutputChn(CSclChGsOut *pChn,int nRow);
	void ShowData_SMVInputChn(CSclChSmvIn *pChn,int nRow);
	void ShowData_SMVOutputChn(CSclChSmvOut *pChn,int nRow);
};

class CIECCfgAddDlg : public CDialog, public CExBaseListGridOptrInterface
{
	DECLARE_DYNCREATE(CIECCfgAddDlg)

private:
	CWzdDlgButton m_txtListType;
	CWzdDlgButton m_btnBk;
	CIECCfgAddTypeGrid m_gridList;
	CIECCfgAddAppGrid m_gridApp;
	CIECCfgAddChsGrid m_gridChs;
	CWzdDlgTabCtrl m_tabAdd;
	CWzdDlgNormalBtn m_btnPro;//保护装置 IsIed_Prot();
	CWzdDlgNormalBtn m_btnTest;//测控 IsIed_Meas();
	CWzdDlgNormalBtn m_btnSmart;//智能 IsIed_RPIT();
	CWzdDlgNormalBtn m_btnUnion;//合并单元 IsIed_MU();
	CWzdDlgNormalBtn m_btnOther;
	CWzdDlgNormalBtn m_btnFind;
	CEdit m_editFind;

	CWzdDlgNormalBtn m_btnOK;
	CWzdDlgNormalBtn m_btnCancel;

	CSclStation* m_pSclStation;//从IED选择中获取的IED信息
	CExBaseList* m_pListApp;

public:
	enum { IDD = IDD_IECCFG_ADD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	void SetAllTypeBtnDefault();

public:
	CIECCfgAddDlg(CWnd* pParent = NULL);           // 动态创建所使用的受保护的构造函数
	virtual ~CIECCfgAddDlg();
	void Init(CSclStation* pSclStation);
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	void Attach(CExBaseList* pList);
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedAdddlgType1();
	afx_msg void OnBnClickedAdddlgType2();
	afx_msg void OnBnClickedAdddlgType3();
	afx_msg void OnBnClickedAdddlgType4();
	afx_msg void OnBnClickedAdddlgOther();
	afx_msg void OnTcnSelchangeAdddlgTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAdddlgFind();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};


