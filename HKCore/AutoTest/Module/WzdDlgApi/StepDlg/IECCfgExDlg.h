#pragma once
#include "../StepCtrl/WzdDlgStyleGrid.h"
#include "../StepCtrl/WzdDlgButton.h"
#include "../../../../61850/Module/UI/SmvRateGrid.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSMVDatas.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSmvRates.h"
#include "../../../iSmartTestWzd/Resource.h"

#define IECCFG_COL_ID_SMVRATE_NAME     1
#define IECCFG_COL_ID_SMVRATE_RATE     2
#define IECCFG_COLS_SMVRATE            3

class CIECCfgSmvRateGrid : public CWzdDlgStyleGrid
{
public:
	CIECCfgSmvRateGrid();
	virtual ~CIECCfgSmvRateGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	static void EndEditCell_Value_Precision(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

class CIECCfgExDlg : public CDialog
{
	DECLARE_DYNAMIC(CIECCfgExDlg)

private:
	CWzdDlgNormalBtn m_btnOK;
	CWzdDlgNormalBtn m_btnCancel;
	CComboBox m_cbbASDU;
	CEdit m_editRate;
	CIECCfgSmvRateGrid m_gridEx;

	CIecCfgDatasSMV* m_pIecSMV;
	CIecCfgSmvRates* m_pIecCfgSmvRates;//取克隆数据
	CIecCfgDataSmvCommon* m_pCommon;//取原始数据

public:
	CIECCfgExDlg(CWnd* pParent = NULL); 
	virtual ~CIECCfgExDlg();

	enum { IDD = IDD_IECCFG_EX_DIALOG };

public:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	void SetIecCfg(CIecCfgDatasSMV* pIecCfg);
	CIecCfgSmvRates* GetIecCfg() { return m_pIecCfgSmvRates; }
	virtual void OnOK();
	void ClearClone();
	DECLARE_MESSAGE_MAP()
};
