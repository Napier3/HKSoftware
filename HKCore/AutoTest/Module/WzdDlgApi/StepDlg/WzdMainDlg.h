#pragma once
#include "WzdDlgMngr.h"
#include "../StepCtrl/WzdDlgButton.h"
#include "../StepCtrl/WzdDlgList.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/GuideBook/GuideBook.h"
#include "../../../Module/XSmartTestClientInterface.h"
#include "../../../../SttStudio/Module/SmartTestInterface/XSmartTestEventInterface.h"
#include "../../../../61850/Module/IecCfgTool/IecCfgFile.h"
#include "../../../../BlueTooth/Module/TestTool/OrderInfo0x92.h"

#include "ThreadPrgsDlg.h"
#include "../WzdDlgSendState.h"
#include "WzdDlg_AutoTest.h"

//2023-4-16  lijunqing  关闭
#define TIMER_ID_CLOSE_WZD   1144

//模板中相关的项目、数据用固定ID的，需要软件特殊处理
#define ID_CONSTANT_ITEM_RPTVIEW        _T("UIRpt")    //用于汇总存储项目结果的安全措施项目的ID
#define ID_CONSTANT_DATA_ERRANALYSE     _T("Unqualified_Analysis")    //上述安全措施中，若不合格，用于存储不合格分析建议的报告数据ID
#define ID_CONSTANT_DATA_PREFIX_SHORT   _T("S_")  //安全措施中，对于短数据，一行展示两个数据，数据ID用固定前缀
#define ID_CONSTANT_ITEM_PREFIX_CONFIRM _T("Confirm_")  //安全措施，必须要人工确认的项目。项目ID的固定前缀

//网络状态
enum tagNetState
{
	NetState_BlueTooth = 0,
	NetState_Ethernet
};

class CWzdMainDlg : public CWzdDlgBase, public CXSmartTestEventInterface 
{
	DECLARE_DYNAMIC(CWzdMainDlg)
private:
	CWzdDlgButton m_txtTitle;
	CWzdDlgButton m_btnIcon;
	CWzdDlgButton m_btnBottom;
	CWzdDlgNormalBtn m_btnPrev;
	CWzdDlgNormalBtn m_btnNext;
	CButton m_grpBorder;
	CDialog m_listStep;
	CDialog m_dlgStep;
	CFont m_font;
	CWzdDlgMngr m_oStepsMngr;//DVM界面链
	CWzdDlgList* m_pStepList;
	
	CString m_strIecfgFile;
	CString m_strGbXmlFile;
	CString m_strGbRptFile;
	CString m_strReportFile;
	CString m_strExRptFile;

	CString m_strFileCfg;
	CString m_strFileVolt;
	CString m_strFileType;
	CString m_strFileTest;
	CString m_strComm;

	CXSmartTestClientInterface *m_pSmartTestClient;

private:
	//自动测试用文件
	CString m_strParameterMd5;
	CString m_strSettingMd5;
	CString m_strEnaMd5;
	CString m_strIP;
	CString m_strFactory;

	//拼接路径使用
	CString m_strUser;
	CString m_strSCDFile;

	//拼接名称使用
	CString m_strIedName;   //装置名称。用作“保护套别”
	CString m_strIedModel;   //装置型号
	CString m_strStationName;   //变电站名称
	CString m_strIedDesc;  //装置描述。用作“间隔/主变名称”

public:
	CIecCfgFile* m_pCurIecCfgFile;
	CSclStation m_oSclStation;
	CGuideBook m_oGuideBook;
	CString m_strGuideBookIecfgFile;
	CDvmDataset m_Recv0x92Data;
	CDataTypes m_oDataTypes;
	//最后一步测试界面
	CWzdDlg_AutoTest* m_pAutoTest;


public:
	CWzdMainDlg(CWnd* pParent = NULL);
	virtual ~CWzdMainDlg();

	enum { IDD = IDD_WZDMAIN_DIALOG };

	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, 
		long nItemIndex, const CString& strItemID, const CString& strState, long nSelect);
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex);
	virtual long OnExportRptEvent(CSttParas *pParas);	//20231026 huangliang 
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent);
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent);
	virtual long OnTestCreated(const CString& strDeviceID);
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID);
	virtual long OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, 
		long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState);
	virtual long OnTestProcess(CExBaseList* pSttParas);
	virtual long OnReTestFinished(CExBaseList* pSttParas);
	virtual long OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnUploadRptFile(const CString& strDeviceID, const CString &strFiles);
	virtual long OnInputData(const CString& strDatas, const CString& strMsgs);
	virtual long OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs);
	virtual long On_Ats_CreateTest(const CString &strGbrptFile){ return 0; }
	virtual long On_Ats_AdjustMainWnd(LONG nMainWnd) { return 0; }
	virtual long OnReport(CExBaseList* pSttParas);

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNext();
	afx_msg LRESULT OnSenSelChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSenSelTestChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSenSelUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSenSelCfg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSenSelComm(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSenSelFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOpenSclFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDvmMapDoNext(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStepListChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEnableNext(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEnablePrev(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEnableReturn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateConnect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImpSetUpdateMd5(WPARAM wParam, LPARAM lParam);
	CRect GetDlgRect();
	CRect GetListRect();
	void InitDlgs();
	void InitList();
	void InitBtns();
	CWzdDlgButton* InitListItem(const CString& strText, BOOL bImg, void* pItemData);
	void CreateNewTest();
	void GenerateFileName();
	void SaveWzdXmlFile();

public:
	void SetIEDInfo(const CString &strIedName, const CString &strIedModel
		, const CString &strStationName, const CString &strIedDesc);
	void SetIedInfoToGlobal();
	afx_msg LRESULT OnIEDSelText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnIEDSelSelect(WPARAM wParam, LPARAM lParam);
	void CmpDeviceFile_LoadIecFile(const CString &strFile, const CString &strIecfg);

	//20230619 huangliang 初始化IED文件的选择
	void InitIECFileChoose();

public:
	virtual void OnInitialUpdate();
	virtual void JumpToPrevDlg();
	virtual void JumpToNextDlg();
	virtual void SetActiveDlg(const CString& strID);
	virtual BOOL InitUI(CDataGroup* pDataGroup); //新建测试时的初始化UI
	virtual void LoadUI(); //加载测试时的初始化UI
	CDataGroup* IsLoadCfgXml() { return m_pDataCfg; }
	void ClearCfgXml();
	void OnWindowPosChanging();
	DECLARE_MESSAGE_MAP()


//2023-4-18  lijunqing
public:
	void CWzdDlg_IEDSel_DoNext(CWzdDlgBase *pDlg);

	void OpenGbRptForQue(const CString &strFilePath);
	void OpenGbRptFile(const CString &strFilePath);

	//20230609 huangliang 
	void SetDataInGlobal(CDvmDataset *dataG);
	void SetRecv0x92DataInGlobal();
	void ClearBlueData();
	void CloseTestClient();	

	//20231023 huangliang 添加获取厂家信息记录
	CString GetFactory(){ return m_strFactory; }

	//20231025 huangliang
	void TestClientExportRpt();
	void TestClientStartTest();
	void TestClientStopTest();
	void SetItemState(CString strMacroID, long nSelect);
	void SetTestParas(const CString &strDeviceID, CString &strTestParas);

	void SetNetState(long nState);
	void FinishInputData(CExBaseList* pDatas);

	void TestCurrentItem(CString strPath);
	void TestFromItem(CString strPath);

private:
	//CThreadPrgsDlg *m_pThreadPrgsDlg;
	CWzdDlgSendState *m_pThreadPrgsDlg;
};

extern CWzdMainDlg* g_pWzdMainDlg;