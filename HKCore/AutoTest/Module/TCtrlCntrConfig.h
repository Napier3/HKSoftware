#pragma once

/*
	功能描述：自动测试配置；设置自动测试过程中相关的配置
	关联文件：TCtrlCntr.xml/TCtrlCnr.ini
*/
#include "../../Module/BaseClass/ExBaseObject.h"
#include "AutoTestXMLRWKeys.h"
#include "../../Module/DataMngr/DvmDataset.h"

#define AUTOTEST_ERR_PROCESS_CONTINUE  0
#define AUTOTEST_ERR_PROCESS_STOP      1

#define  FACTORY_BATCH_TEST_FILE  _T("FactoryBatchTestMngr.xml")

#define  SMARTTEST_MODE_NORMAL_TEST               _T("Normal")
#define  SMARTTEST_MODE_SIMPLE_TEST                 _T("Simple")
#define  SMARTTEST_MODE_FACTORY_BATCH_TEST   _T("FactoryBatch")
//shaolei 20211101
#define  SMARTTEST_ITEM_COUNT_MODE_ITEMSTYPE  _T("ItemsType")  //根据测试分类的功能类节点属性计算项目数量
#define  SMARTTEST_ITEM_COUNT_MODE_ALLITEMS  _T("AllItems")  //根据所有的测试小项来计算项目数量

class CTCtrlCntrConfig : public CExBaseObject
{
private:
	CTCtrlCntrConfig();
	virtual ~CTCtrlCntrConfig();

public:
	static CTCtrlCntrConfig* g_pTCtrlCntrConfig;
	static long g_nTCtrlCntrConfigRef;

	static CTCtrlCntrConfig* Create();
	static void Release();

	static CString GetWorkSpacePath();

public:
	//Test
	long m_nAutoTestCtrlException;
	//CString m_strMacroTestEngineProgID;
	long m_nWriteTestTempFile;
	long m_nFillReport;
	CString m_strTestTasksViewMode;	
	//long m_nTestTasksViewMode;
	CString m_strProtocolPath;

	//WorkSpace
	//long m_nAutoLoadWorkspace;
	//CString m_strLastWorkSpaceFile;

	//Login
	//long m_nUserNetToLogin;
	//CString m_strCfgFile;

	//ItemStateColor
	COLORREF m_crNormal;
	COLORREF m_crTesting;
	COLORREF m_crEligible;
	COLORREF m_crStopped;
	COLORREF m_crInlegible;
	COLORREF m_crBackgroundInlegible;
	CString m_strBackgroundInlegible;
	COLORREF m_crNotStandard;
	COLORREF m_crProhibit;
	COLORREF m_crEligibleEx;

	//2021-2-25  lijunqing 不合格项目显示设置
	long m_nInlegibleFontBold; //
	//2021-11-01 shaolei  测试项目数量统计模式
	CString m_strItemsCountMode;   //ItemsType：测试分类的功能类节点；AllItems：统计所有测试小项
	//2021-11-16 shaolei  导出数据的导出路径
	CString m_strExportDatasSavePath;

	//Report
	long m_nHideAllCmdbars;
	CString m_strReplaceForEmptyCell;
	long m_nDebugWithoutReport;
	long m_nDebugWithoutGbTree;
	long m_nInsertDataLinkWhenEligible;
	long m_nSaveRptToDB;
	long m_nClearRptValues;
	long m_nClearRptSOE;
	long m_nFilterSoeQueryAll;

	//
// 	<error-process>stop</error-process>
// 	<error-sound></error-sound>
// 	<finish-sound></finish-sound>
	CString m_strErrorProcess;
	CString m_strErrorSoundFile;
	CString m_strFinishSoundFile;
	long m_nShowLevelOneItemsMsg;
	long m_nErrPlayMode;
	//long m_nUse_dsSetting_TimeTrans;

	//其他
	CString m_strFile;


	//召唤保护录波的配置
	CString m_strRecordProgID;
	long m_nRecordDelay;
	long m_nAddRecordReport;

	//测试报告存储的路径
	CString m_strWorkSpacePath;

	//自定义重复次数
	long m_nOwnDefRepeatTimes;

	//定义通讯命令失败后重试的次数
	long m_nCmmMaxRetrytimes;
	long m_nCmmRetryDelay;
	CString m_strSkipStxmlWhenWSetsError;
	//long m_nCanEditScript;

	CString m_strAutoSaveReportPath;   //测试完成，自动保存测试报告的位置

	//CString m_strSeparateChar;
	//CString m_strSeparateEndChar;
	//char m_chSeparateChar;
	//char m_chSeparateEndChar;

	//long m_nUseRegisterFile;

	CString m_strTestControlMode;
	CString m_strReportMode;
	long m_nMacroTestAppExceptionTDelay;

	long m_nAutoSaveGbDev;
	long m_nAutoSaveGbDevTimeLong;

	CString m_strTestWndMode;

	//long m_nScriptRunTimeLong;
	//long m_nEngineCalTimeLong;
	long m_nAdjustByTkIDMode;
	long m_nStopProtocolParseWhileReadSoe;
	long m_nSaveReportGap;
	long m_nXdvMgrpSelMode;
	CString m_strXdvMgrptExportUse;
	CString m_strXdvMgrptExportPath;
	CString m_strXdvMgrptExportPathWord;
	CString m_strXdvMgrptExportPathXml;
	CString m_strXdvMgrptExportPathGbrpt;
	long m_nXdvMgrptExportAuto;   //是否自动打开“导出报告”的对话框   shaolei 20210624
	long m_nTestSpyWndShow;

	//2017-12-09 记录导出报告的设置
	long m_nExport_ShowWordApp;
	long m_nExport_OriginalDatas;
	long m_nExport_CmbnReport;

	long m_nRWReportFileMode;
	//long m_nUsePowerTestTrans;   //是否使用PowerTest模板转换
	long m_nSysRptShowMaxCount;  //系统报告模式下显示的最大个数
	long m_nExportRptUseUpdateGuideBook;

	long m_nIsSingleApp;//2018-11-6  是否为唯一APP模式
	long m_nEngineUseCommTestMode;   //2018-11-6 通讯测试模式，如果联机失败，设置为装置通讯错误
	CString m_strFacBatchTestMngrFile;

	long m_nViewWordForMrptCount; //2019-10-30  在多装置多组报告的时候，如果测试记录小于这个数字，则显示Word报告
	long m_nEnableViewWordForMrpt; //2019-10-30  在多装置多组报告的时候，如果测试记录小于这个数字，则显示Word报告

	//2021-1-3  增加自动测试模式：normal、factory-batch、simple等，方便将来扩展
	CString m_strSmartTestMode;

	//2021-1-5  增加简化版本，测试仪和装置IP的设置
	CString m_strIP_TestApp, m_strIP_Device;
	long m_nUseSttAtsSvr;   // shaolei  20220324  是否使用自动测试服务，以协议控制自动测试
	CString m_strSttAtsSvrScene;  //shaolei  2023-10-08 启用自动测试服务时，自动测试服务场景
	CString m_strRptProgID;  //shaolei 20220523  上传报告的COM接口程序的ProgID
	long m_nDisableOptrWhenUseAtsSvr;   //shaolei 20220917   是否禁用操作按钮及菜单，当使用自动测试服务器模式时

	long m_nShowTestMsgWnd;  //是否显示测试消息窗口：异常、测试结束等  2023-7-10  lijunqing
public:
	long Save();
	long Open();

	CString GetRGBColorString(COLORREF crColor);

public:
// 	virtual long XmlRead(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWrite(CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTCtrlCntrKey;	}
	virtual void InitAfterRead();

	BOOL IsErrorProcessContinue();
	BOOL IsErrorProcessStop();
	long GetErrorProcessStop();
	void SetErrorProcess(long nProcess);
	BOOL HasRecorder();
	void SetRecorderProgID(const CString &strProgID);

	//CString GetMacroTestEngineProgID();

	BOOL IsTestControlModeSingle();
	BOOL IsTestControlModeSingleManyReport();
	BOOL IsReportControlWord();
	BOOL IsReportControlWPS();
	BOOL IsReportControlSystem();
	long GetReportControl();

	void SetTestControlModeSingle();
	void SetTestControlModeSingleManyReport();
	void SetReportControlWord();
	void SetReportControlWPS();
	void SetReportControlSystem();

	//TestWndMode
	void Set_TestWndMode_ShowAlways();
	void Set_TestWndMode_HideWhenMinize();
	BOOL Is_TestWndMode_ShowAlways();
	BOOL Is_TestWndMode_HideWhenMinize();
	CDataTypes* GetDvmTestKeyDataTypes();
	void SetSaveRptToDB(BOOL b)	{	m_nSaveRptToDB = b;	}

	static long GetClearRptValues();
	static long GetClearRptSOE();
	static long GetFilterSoeQueryAll();

	static void SetClearRptValues(long nVal);
	static void SetClearRptSOE(long nVal);
	static void SetFilterSoeQueryAll(long nVal);

	//static long GetScriptRunTimeLong();
	//static long GetEngineCalTimeLong();

	static BOOL IsAdjustByTkIDMode_Delete();
	static BOOL IsAdjustByTkIDMode_Select();
	static BOOL IsAdjustByTkIDMode_Show();
	static BOOL IsAdjustByTkIDMode_Enable();
	static BOOL IsStopProtocolParseWhileReadSoe();
	static long   GetSaveReportGap();
	static long   GetXdvMgrpSelMode();
	static void   SetSdvMgrpSelMode(long nMode);
	static long   GetTestSpyWndShow();
	static BOOL IsShowTestSpyWnd();
	static void   SetTestSpyWndShow(long nShow);

	static CString   GetXdvMgrptExportPath();
	static BOOL   GetXdvMgrptExportUse_XML();
	static BOOL   GetXdvMgrptExportUse_GBRPT();
	static CString   GetXdvMgrptExportPathWord();
	static CString   GetXdvMgrptExportPathXml();
	static CString   GetXdvMgrptExportPathGbrpt();
	static void   SetXdvMgrptExportPath(const CString &strPath);
	static void   SetXdvMgrptExportUse(const CString &strUse);
	static void   SetXdvMgrptExportPathWord(const CString &strPath);
	static void   SetXdvMgrptExportPathXml(const CString &strPath);
	static void   SetXdvMgrptExportPathGbrpt(const CString &strPath);

	static long Get_Export_ShowWordApp();
	static long Getm_Export_OriginalDatas();
	static long Get_Export_CmbnReport();
	static long Get_RWReportFileMode();
	static void Set_Export_ShowWordApp(long nVal);
	static void Setm_Export_OriginalDatas(long nVal);
	static void Set_Export_CmbnReport(long nVal);
	static void Set_RWReportFileMode(long nVal);

	//static BOOL Is_UsePowerTestTrans();
	static long GetSysRptShowMaxCount();
	static long Get_ExportRptUseUpdateGuideBook();
	static void Set_ExportRptUseUpdateGuideBook(long nVal);
	static long Get_IsSingleApp();
	static void Set_IsSingleApp(long nVal);
	static long Get_EngineUseCommTestMode();
	static void Set_EngineUseCommTestMode(long nVal);
	static COLORREF GetColor_Inlegible();
	static COLORREF GetColor_Inlegible_Background();
	static COLORREF GetColor_Eligible();
	static long Get_InlegibleFontBold();

	static CString GetReportMode(); 
	static void SetEnableViewWordForMrpt();
	static BOOL IsEnableViewWordForMrpt();
	static BOOL CanViewWordForMrpt(long nMrpt);
	static BOOL SetRptViewByMrpt(long nMrpt);

	//2021-1-3  lijunqing
	static BOOL IsFacBatchTestMode();
	static BOOL IsNormalTestMode();
	static BOOL IsSimpleTestMode();

	static void SetIP_TestApp(const CString &strIP);
	static void SetIP_Device(const CString &strIP);
	static void SetIP(const CString &strIP_TestApp, const CString &strIP_Device);
	static void GetIP_TestApp(CDvmDataset *pDataset);
	static void GetIP_Device(CDvmDataset *pDataset);
	static void GetIP_TestApp(CString &strXml);
	static void GetIP_Device(CString &strXml);

	static long GetShowTestMsgWnd();
	static void SetShowTestMsgWnd(long nVal);
public:
	static const CString g_strTestControlModeSingle;
	static const CString g_strTestControlModeSingleManyReport;

	CDataTypes *m_pDvmTestKeyDataTypes;

};

extern BOOL g_bShowTestWndTop;

