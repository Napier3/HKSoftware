#pragma once

#include "../../Module/BaseClass/ExBaseObject.h"
#include "../../Module/DataMngr/DataMngrGlobal.h"

#include "GuideBook/GbXMLKeys.h"


class CAutoTestXMLRWKeys : public CGbXMLKeys
{
private:
	CAutoTestXMLRWKeys();
	virtual ~ CAutoTestXMLRWKeys()	{ }

public:
	static CAutoTestXMLRWKeys* g_pAutoTestRWKeys;
	static long g_nAutoTestRWKeysRef;
	static CAutoTestXMLRWKeys* Create();
	static void Release();

public:
	//systemconfig
	BSTR m_strSystemConfigKey;
	BSTR m_strDBNameKey;
	BSTR m_strTaskMngrFileKey;
	BSTR m_strWorkSpaceFileKey;
	BSTR m_strProtocolPathKey;

	//TCtrlCntrConfig
	BSTR m_strTCtrlCntrKey;

	BSTR m_strAutoTestKey;
	BSTR m_strMacroTestEngineKey;
	BSTR m_strTestTempFileKey;
	BSTR m_strFillReportKey;
	BSTR m_strTestTasksViewMode;
	BSTR m_strStopProtocolParseWhileReadSoeKey;
	BSTR m_strSaveReportGapKey;
	BSTR m_strSdvMgrpSelModeKey;
	BSTR m_strXdvMgrptExportPathKey;
	BSTR m_strXdvMgrptExportUseKey;
	BSTR m_strXdvMgrptExportPathWordKey;  //2021-1-2  lijunqing
	BSTR m_strXdvMgrptExportPathXmlKey;  //2021-1-2  lijunqing
	BSTR m_strXdvMgrptExportPathGbrptKey;  //2021-1-2  lijunqing
	BSTR m_strTestSpyWndShowKey;
	BSTR m_strXdvMgrptExportAutoKey; //20210624 SHAOLEI

	BSTR m_strExport_ShowWordApKey;
	BSTR m_strnExport_OriginalDataKey;
	BSTR m_strnExport_CmbnReportKey;
	BSTR m_strRWReportFileModeKey;
	
	BSTR m_strAutoLoadWorkSpaceKey;
	BSTR m_strLastWorkSpaceFile;

	BSTR m_strLoginKey;
	BSTR m_strUseNetToLoginKey;
	BSTR m_strCfgFileKey;

	BSTR m_strNormalKey;
	BSTR m_strTestingKey;
	BSTR m_strEligibleKey;
	BSTR m_strStopedKey;
	BSTR m_strInlegibleKey;
	BSTR m_strBackgroundInlegibleKey;
	BSTR m_strNotStandardKey;
	BSTR m_strProhibitKey;
	BSTR m_strEligibleExKey;

	BSTR m_strHideAllCmdbarsKey;
	BSTR m_strReplaceForEmptyCell;
	BSTR m_strDebugWithoutReport;
	BSTR m_strDebugWithoutGbTree;
	BSTR m_strInsertDataLinkWhenEligible;
	BSTR m_strSaveRptToDB;
	BSTR m_strSaveRptToDB_All;
	BSTR m_strClearRptValues;
	BSTR m_strClearRptSOE;
	BSTR m_strFilterSoeQueryAll;
	BSTR m_strUsePowerTestTrans;
	BSTR m_strSysRptShowMaxCount;
	BSTR m_strExportRptUseUpdateGuideBook;
	BSTR m_strIsSingleApp;
	BSTR m_strEngineUseCommTestMode;
	BSTR m_strFacBatchTestMngrFileKey;

	BSTR m_strErrorProcessKey;
	BSTR m_strErrorSoundFileKey;
	BSTR m_strFinishSoundFileKey;
	BSTR m_strShowLevelOneItemsMsgKey;
	BSTR m_strErrorPlayModeKey;
	BSTR m_strRecordProgIDKey;
	BSTR m_strRecordDelayKey;
	BSTR m_strAddRecordReportKey;
	BSTR m_strUseSettingTimeTransKey;
	BSTR m_strWorkSpacePathKey;
	BSTR m_strUseOwnDefRepeatTimesKey;
	BSTR m_strCmmMaxRetrytimesKey;
	BSTR m_strCmmRetryDelayKey;
	BSTR m_strSkipStxmlWhenWSetsErrorKey;
	BSTR m_strCanEditScriptKey;
	BSTR m_strAutoSaveReportPathKey;
	BSTR m_strSeparateCharKey;
	BSTR m_strSeparateEndCharKey;
	BSTR m_strUseRegisterFileKey;
	BSTR m_strAppExceptionTDelayKey;
	BSTR m_strAutoSaveGbDevKey;
	BSTR m_strAutoSaveGbDevTimeLongKey;
	BSTR m_strTestWndModeKey;

	//workspace.xml
	BSTR m_strWorkspaceKeyEx;
	BSTR m_strAppExitStateKey;
	BSTR m_strCurrTaskKey;
	BSTR m_strCurrTestKey;

	//tasks
	BSTR m_strTaskMngrKey;
	BSTR m_strTaskMngrsKey;
	BSTR m_strTaskMngrsGroupKey;
	BSTR m_strTaskMngrsDBKey;
	BSTR m_strCTestWzdDefineKey;
	BSTR m_strCTestWzdDefinesKey;
	BSTR m_strCStationTestMainConfigKey;
	BSTR m_strTasksMngrSrcFileKey;
	BSTR m_strXTestDbGroupPathKey;
	BSTR m_strShowWordRptKey;
	BSTR m_strEngineModeKey;   //shaolei 2023-11-3

	//task
	BSTR m_strTaskKey;
	BSTR m_strIDKeyEx;
	BSTR m_strLocalIDKey;
	BSTR m_strTestTypeKey;
	BSTR m_strLocationKey;
	BSTR m_strPlanBeginKey;
	BSTR m_strPlanFinishKey;
	BSTR m_strTestBeginKey;
	BSTR m_strTestFinishKey;
	BSTR m_strNameKeyEx;
	BSTR m_strTestStateKey;
	BSTR m_strTestTimeLongKey;
	BSTR m_strPpTemplateFileKey;
	BSTR m_strPpEngineProgIDKey;
	BSTR m_strReportSNKey;
	BSTR m_stDeviceModelFileKey;

	BSTR m_strReportSNGenKey;
	BSTR m_strReportSNGenDateKey;
	BSTR m_strReportSNGenIndexKey;

	//project
	BSTR m_strProjectKey;
	BSTR m_strProtocolTemplateKey;
	BSTR m_strCurrTestItemIndex;
	BSTR m_strPpDeviceFileKey;
	BSTR m_strTemplateFileKey;
	BSTR m_strReportMapFileKey;
	BSTR m_strDvmTestStateKey;
	BSTR m_strProtocolTestStateKey;
	BSTR m_strMaxMgrpIDKey;

	//测试项目引用
	BSTR m_strTestItemErrRefKey;

	BSTR m_strCPpDeviceRefsKey;
	BSTR m_strCPpDeviceRefKey;

	BSTR m_strTestControlModeKey;
	BSTR m_strReportModeKey;

	//mgbrpt
	BSTR m_strMgbrptKey;

	BSTR m_strWordPageOrientationKey;
	BSTR m_strReportFillClassIDKey;
	BSTR m_strSystemPathKey;

	BSTR m_strScriptRunTimeLongKey;
	BSTR m_strEngineCalTimeLongKey;

	BSTR m_strAdjustByTkIDModeKey;
	BSTR m_strReportProgIDKey;
	BSTR m_strViewWordForMrptCountKey;
	BSTR m_strEnableViewWordForMrptKey;

	BSTR m_strSmartTestModeKey;
	BSTR m_strIpTestAppKey;
	BSTR m_strIpDeviceKey;
	BSTR m_strInlegibleFontBoldKey;
	BSTR m_strItemsCountModeKey;
	BSTR m_strExportDatasSavePathKey;

	//GuideBookExportConfig
	BSTR m_strGuideBookExportConfigKey;
	BSTR m_strGuideBookExportGlobalDatasKey;
	BSTR m_strGuideBookExportJobGuideKey;
	BSTR m_strGuideBookExportExtendRptDefKey;
	BSTR m_strGuideBookExportAttrGbxmlKey;
	BSTR m_strGuideBookExportAttrDvmxmlKey;
	BSTR m_strGuideBookExportAttrPpxmlKey;
	BSTR m_strGuideBookExportDeviceModelKey;
	BSTR m_strGuideBookExportSysParasKey;
	BSTR m_strGuideBookExportRptMapKey;
	BSTR m_strGuideBookExportReportsKey;
	BSTR m_strGuideBookExportAttrSimplifyKey;
	BSTR m_strGuideBookExportSysParaEditKey;
	BSTR m_strGuideBookExportSafetyDatasKey;
	BSTR m_strGuideBookExportSafetyDllCallKey;
	BSTR m_strGuideBookExportSafetyMsgKey;
	BSTR m_strGuideBookExportCmdParaKey;
	BSTR m_strGuideBookExportCmdDatasKey;
	BSTR m_strGuideBookExportCmdDsvScriptKey;
	BSTR m_strGuideBookExportMacroTestParasKey;
	BSTR m_strGuideBookExportRptMapNotSaveNullKey;
	BSTR m_strGuideBookExportRptMapOnlySaveLastKey;
	BSTR m_strGuideBookExportReportOnlySaveBkmkKey;
	BSTR m_strGuideBookExportExprScriptKey;
	BSTR m_strGuideBookExportScriptNameKey;
	BSTR m_strGuideBookExportScriptInitKey;
	BSTR m_strGuideBookExportScriptRsltKey;

	//20210112-shaolei //是否保存模板结构描述文件
	BSTR m_strGbdevSaveStruDescFileKey;
	//2022-3-24-shaolei //是否启动自动测试服务，以STT协议控制自动测试
	BSTR m_strUseSttAtsSvrKey;
	//2023-10-08 shaolei  //启用自动测试服务时，创建的服务对象。目前仅区分PAL、其它
	BSTR m_strSttAtsSvrKey;
	//20220523 shaolei  //点击“上传报告”按钮时，是否通过COM接口调用对应的报告处理程序
	BSTR m_strRptProgIDKey;
	//shaolei 20220917   是否禁用操作按钮及菜单，当使用自动测试服务器模式时
	BSTR m_strDisableOptrWhenUseAtsSvrKey;
	BSTR m_strShowTestMsgWndKey;
public:
	BSTR CPpDeviceRefsKey()	{	return m_strCPpDeviceRefsKey;	}
	BSTR CPpDeviceRefKey()	{	return m_strCPpDeviceRefKey;	}

public:
	static BSTR CStationTestMainConfigKey()	{	return g_pAutoTestRWKeys->m_strCStationTestMainConfigKey;	}
};

