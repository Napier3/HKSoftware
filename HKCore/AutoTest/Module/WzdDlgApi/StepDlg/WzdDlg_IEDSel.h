#pragma once
#include "WzdDlgBase.h"
#include "../WzdDlgSclFileRead.h"
#include "../StepCtrl/IEDSelGrid.h"
#include "../../../../61850/Module/IecCfgTool/IecCfgTool.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDevice.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/SmartCap/61850Cap/EthernetCapGlobalDef.h"
#include "afxwin.h"
class CWzdDlg_IEDSel : public CWzdDlgBase, CExBaseListGridOptrInterface
{
	DECLARE_DYNAMIC(CWzdDlg_IEDSel)  
private:
	CIEDSelGrid m_girdIED;
	CString m_strSCDDvmFile;
	CWzdDlgSclFileRead m_oSclFileRead;

public:
	CWzdDlg_IEDSel(CWnd* pParent = NULL);
	virtual ~CWzdDlg_IEDSel();

	enum { IDD = IDD_IDESEL_DIALOG };

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	virtual void OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSclReadFinish(WPARAM, LPARAM);

	CSclIed* GetSelectedIED();
	void AutoGenIecCfgDevice(CSclIed *pSclIed);
	void OnFileNewDevice(CIecCfgDevice *pIecfgDevice,CSclIed *pSclIed);
	virtual BOOL DoNext();
	virtual BOOL DoNextForThead();
	virtual BOOL DoPrev();

	void CreateLocalIP_EngineIP(const CString &strDriverDesc,const CString &strIP,const CString &strDevName);//创建本机同一个网段IP地址,创建PpMMSEngine对应IP
	void ModifyIP_PpMmsEngine(const CString &strIP,const CString &strDevName);
	void ModifyIP_DltEngine(const CString &strIP,const CString &strDevName);
	void SaveFile();

public:
	virtual void OnInitialUpdate();
	void OpenSclFile(const CString& strFile);
	CSclStation* GetSclStation();
	BOOL IP_Find_OK(int nRow);

	DECLARE_MESSAGE_MAP()
	CComboBox m_cmb_ip;
	CComboBox m_cmb_card;
	CStNetCardInforList *Card;
	afx_msg void OnCbnSelchangeCmbCard();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};