#pragma once
#include "WzdDlgBase.h"
#include "IECCfgDlg.h"
#include "IECCfgAutoDlg.h"
#include "../StepCtrl/WzdDlgTabCtrl.h"
#include "../StepCtrl/IECSmvGrid.h"
#include "../StepCtrl/WzdDlgComboBox.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../../61850/Module/IecCfgTool/IecCfgFile.h"

class CWzdDlg_IECCfg : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzdDlg_IECCfg)
private:
	CSmvIecfgDataMngrSelDlg *m_pSelSmvIecfgDataMngrDlg;
	CIeccfgDeviceConfigDlg m_dlgIECCfg;
	CStatic m_txtSmv;
	CStatic m_txtSmvCh;
	CWzdDlgNormalBtn m_btnGsIn;
	CWzdDlgNormalBtn m_btnGsOut;
	CWzdDlgNormalBtn m_btnSmv;
	CWzdDlgNormalBtn m_btnSave;
	CWzdDlgNormalBtn m_btnIECSetting;
	CIECSmvGrid m_gridSmv;       //显示控制块信息的，只针对SMV，GOOSE配置时是隐藏的
	CIECSmvChGrid m_gridCh_Smv_Gs;   //SMV和GOOSE配置共用的
	
	CExBaseList m_oGsSmvChList;//SMV
	CExBaseList m_oGsinChList; //goose通道映射
	CExBaseList m_oIecCfgDatasMngrList;  //整装置全部配置对象链表，用于选择SMV配置时使用
	CString m_strType;
	CIecCfgFileDevice m_oIecCfgFileDevice;

	CExBaseList m_oGsoutChList; //goose通道映射

public:
	CWzdDlg_IECCfg(CWnd* pParent = NULL);
	virtual ~CWzdDlg_IECCfg();

	enum { IDD = IDD_IECCFG_DIALOG };

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ChangGooseFaceSize();

	void ShowOwnWindow(BOOL bShow);
	void ShowSelectDlg(BOOL bShow);
	void GsGridToSmvGrid();
	void SmvGridToGsGrid(bool bIn=true);
	CIecCfgGinCh* FindGsInChByID(const CString& strID);
	CIecCfgGoutCh* FindGsOutChByID(const CString& strID);
	void CollectAllGsCh(CExBaseList* pList);
	void CollectAllSmvCh(CExBaseList* pList);
	void CollectAllGsOutCh(CExBaseList* pList);
	void IecCfgDeviceCover();

	CString m_strIeccfgFile;
public:
	virtual BOOL InitUI(CDataGroup* pDataGroup);
	virtual void OnInitialUpdate();
	void LoadIecfgFile(const CString& strFile);
	void ShowIecfgFile();
	void SetSclStation(CSclStation* pSclStation);
	void SetIECCfgType(const CString& strType) { m_strType = strType; }
	virtual BOOL DoPrev();
	virtual BOOL DoNext();
	CIecCfgFileDevice* GetIecCfgFileDevice() { return &m_oIecCfgFileDevice; }
	virtual void OnWindowPosChanging();
	BOOL SaveXmlFile();

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnSettingReturn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAutoBtnClicked(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateGs(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnIecsetting();
	afx_msg void OnBnClickedBtnIecgsin();
	afx_msg void OnBnClickedBtnIecgsout();
	afx_msg void OnBnClickedBtnIecsmv();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

public:
	//20230619 huangliang 初始化IED文件的选择
	void InitIECFileChoose();

	//20230629 huangliang 
	void ReBindData();

	//20230630 huangliang 加载数据类型
	void ReLoadAllGsChDataType();
	void ReLoadAllGsOutChDataType();
};