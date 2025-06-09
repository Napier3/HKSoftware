#pragma once
#include "WzdDlgBase.h"
#include "IECSysDlg.h"
#include "../StepCtrl/WzdDlgTabCtrl.h"
#include "../StepCtrl/WzdDlgButton.h"
#include "../StepCtrl/61850/IecCfgDataGridBase.h"
#include "../StepCtrl/61850/IecCfgDataChsGridBase.h"
#include "../../../../61850/Module/IecCfgTool/IecCfgFile.h"
#include "../../../../61850/Module/UI/IecCfgSmvTypeComboBox.h"
#include "../../../iSmartTestWzd/Resource.h"

class CIeccfgDeviceConfigDlg : public CWzdDlgBase, public CExBaseListGridOptrInterface
{
	DECLARE_DYNAMIC(CIeccfgDeviceConfigDlg)
private:
	CStatic m_txtSmv;
	CIecCfgSmvTypeComboBox m_cbbSmv;
	CWzdDlgNormalBtn m_btnExSetting;
	CWzdDlgNormalBtn m_btnIECAdd;
	CWzdDlgNormalBtn m_btnIECDel;
	CWzdDlgNormalBtn m_btnReturn;
	CComboBox m_cbbSettingCfg;
	CWzdDlgTabCtrl m_tabCfg;
	CWzdDlgTabCtrl m_tabSetting;
	CIECCfgDataGridBase* m_pIecCfgDataGrid;
	CIECCfgDataChsGridBase* m_pIecCfgDataChsGrid;
	CIECSysDlg m_dlgIECSys;
	CButton m_btnAll;
	CButton m_btnVolt;
	CButton m_btnCur;

	CIecCfgFile* m_pIecCfgFile;
	CIecCfgDataBase* m_pLastSelIecCfgData;
	CIecCfgDataBase* m_pIecCfgData;    //关联显示的控制块数据对象
	CSclStation* m_pSclStation;//从IED选择中获取的IED信息

public:
	CIeccfgDeviceConfigDlg(CWnd* pParent = NULL);
	virtual ~CIeccfgDeviceConfigDlg();

	enum { IDD = IDD_IECCFG_CHILD_DIALOG };

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CIecCfgDatasBase* GetIecCfgDatas(long nIndex);
	CRect GetDataGridRect();
	CRect GetChsGridRect();
	CRect GetSysRect();
	void ClearDataGrid();
	void ClearChsGrid();
	void ShowCtrls(BOOL bShow = TRUE);

	void ShowIECCfgData();
	void ShowIECCfgChs();
	void CreateSMVDataGrid();
	void CreateSMVChsGrid();
	void UpdateSMVDatas(BOOL bInit);
	void CreateGOOSEINDataGrid();
	void CreateGOOSEINChsGrid();
	void UpdateGOOSEINDatas(BOOL bInit);
	void CreateGOOSEOUTDataGrid();
	void CreateGOOSEOUTChsGrid();
	void UpdateGOOSEOUTDatas(BOOL bInit);

	BOOL CheckAppIDExisted(CSclCtrlBase* pScl);
	void DeleteCtrlByAPPID(CIecCfgDatasBase* pDatas, long dwAppID);

public:
	void SetTableCfg(int iIndex){ m_tabCfg.SetCurSel(iIndex); }
	virtual void OnInitialUpdate();
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	virtual void OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	void SetIECCfgFile(CIecCfgFile* pIecCfg);
	void UpdateDatas(BOOL bInit = FALSE);
	void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);
	void ShowOtherSetting();
	void SetSclStation(CSclStation* pSclStation);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnTcnSelchangeTabCfg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabSetting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCbbSettingcfg();
	afx_msg void OnBnClickedBtnExsetting();
	afx_msg void OnBnClickedBtnIecadd();
	afx_msg void OnBnClickedBtnIecdel();
	afx_msg LRESULT OnGinChAppIDChanged(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnReturn();
	afx_msg void OnBnClickedCbAll();
};