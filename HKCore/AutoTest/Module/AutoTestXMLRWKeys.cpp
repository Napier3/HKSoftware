#include "stdafx.h"
#include "AutoTestXMLRWKeys.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CAutoTestXMLRWKeys* CAutoTestXMLRWKeys::g_pAutoTestRWKeys = NULL;
long CAutoTestXMLRWKeys::g_nAutoTestRWKeysRef = 0;

CAutoTestXMLRWKeys* CAutoTestXMLRWKeys::Create()
{
	g_nAutoTestRWKeysRef ++;

	if(g_pAutoTestRWKeys == NULL)
	{
		g_pAutoTestRWKeys = new CAutoTestXMLRWKeys();
	}

	return g_pAutoTestRWKeys;
}

void CAutoTestXMLRWKeys::Release()
{
	g_nAutoTestRWKeysRef --;

	if(g_nAutoTestRWKeysRef == 0)
	{
		delete g_pAutoTestRWKeys;
		g_pAutoTestRWKeys = NULL;
	}
}

CAutoTestXMLRWKeys::CAutoTestXMLRWKeys()
{
// 	CGbXMLKeys::g_pXmlKeys = this;

	//systemconfig 
	m_strSystemConfigKey = L"system-config";
	m_strDBNameKey = L"db-name";
	m_strTaskMngrFileKey = L"task-mngr-file";
	m_strWorkSpaceFileKey = L"workspace-file";
	m_strProtocolPathKey = L"Protocol";

	//tctrlcntr config
	m_strTCtrlCntrKey = L"auto-test-config";

	m_strAutoTestKey = L"auto-test-ctrl-exception";
	m_strMacroTestEngineKey = L"macro-test-engine";
	m_strTestTempFileKey = L"write-test-temp-file";
	m_strFillReportKey = L"sys-fill-report";
	m_strTestTasksViewMode = L"TestTasksViewMode";
	m_strStopProtocolParseWhileReadSoeKey = L"stop-protocol-while-read-soe";
	m_strSaveReportGapKey = L"save-report-gap";
	m_strSdvMgrpSelModeKey = L"xdv-mgrp-mode";
	m_strXdvMgrptExportPathKey = L"xdv-mgrpt-path";
	m_strXdvMgrptExportUseKey = L"xdv-mgrpt-export";
	m_strXdvMgrptExportPathWordKey = L"xdv-mgrpt-path-word";
	m_strXdvMgrptExportPathXmlKey = L"xdv-mgrpt-path-xml";
	m_strXdvMgrptExportPathGbrptKey = L"xdv-mgrpt-path-gbrpt";
	m_strTestSpyWndShowKey = L"test-spy-wnd-show";
	m_strXdvMgrptExportAutoKey = L"xdv-mgrpt-auto";

	m_strExport_ShowWordApKey = L"export-rpt-show-app";
	m_strnExport_OriginalDataKey = L"export-rpt-original";
	m_strnExport_CmbnReportKey = L"export-rpt-cmbn";
	m_strRWReportFileModeKey = L"rw-rpt-file-mode";

	m_strAutoLoadWorkSpaceKey = L"auto-load-workspace";
	m_strLastWorkSpaceFile = L"LastWorkSpaceFile";

	m_strLoginKey = L"Login";
	m_strUseNetToLoginKey = L"use-login";
	m_strCfgFileKey = L"login-config-file";

	m_strNormalKey = L"item-color-normal";
	m_strTestingKey = L"item-color-testing";
	m_strEligibleKey = L"item-color-eligible";
	m_strStopedKey = L"item-color-stop";
	m_strInlegibleKey = L"item-color-inlegible";
	m_strBackgroundInlegibleKey = L"item-background-color-inlegible";   //±³¾°É«  shaolei  20210619
	m_strNotStandardKey = L"item-color-added";
	m_strProhibitKey = L"item-color-prohibit";
	m_strEligibleExKey = L"item-color-eligible-ex";

	m_strHideAllCmdbarsKey = L"report-hide-cmdbars";
	m_strReplaceForEmptyCell = L"report-replace-empty-cell";
	m_strDebugWithoutReport = L"report-debug-onlly-test";
	m_strDebugWithoutGbTree = L"debug-has-no-gbtree";
	m_strInsertDataLinkWhenEligible = L"add-data-link-when-eligible";
	m_strSaveRptToDB = L"save-rpt-to-db";
	m_strSaveRptToDB_All = L"save-rpt-to-db-all";
	m_strClearRptValues = L"clear-rpt-values";
	m_strClearRptSOE = L"clear-rpt-soe";
	m_strFilterSoeQueryAll = L"filter-soe-query-all";

	m_strErrorProcessKey = L"error-process";
	m_strErrorSoundFileKey = L"error-sound";
	m_strFinishSoundFileKey = L"finish-sound";
	m_strShowLevelOneItemsMsgKey = L"show-level1-msg";
	m_strErrorPlayModeKey = L"err-play-mode";
	m_strRecordProgIDKey = L"record-progid";
	m_strRecordDelayKey = L"record-delay";
	m_strAddRecordReportKey = L"add-record-report";
	m_strUseSettingTimeTransKey = L"setting-ms-s-trans";
	m_strWorkSpacePathKey = L"report-path";
	m_strUseOwnDefRepeatTimesKey = L"own-def-repeat-times";
	m_strCmmMaxRetrytimesKey = L"cmm-max-retry-times";
	m_strCmmRetryDelayKey = L"cmm-retry-delay";
	m_strSkipStxmlWhenWSetsErrorKey = L"skip-wsets-error";
	m_strCanEditScriptKey = L"can-edit-script";
	m_strAutoSaveReportPathKey = L"auto-save-path";
	m_strSeparateCharKey      = L"bar-code-separate";
	m_strSeparateEndCharKey   = L"bar-code-separate-end";
	m_strUseRegisterFileKey   = L"use-register-file";
	m_strAppExceptionTDelayKey   = L"app-exception-tdelay";
	m_strUsePowerTestTrans = L"use-powertest-trans";
	m_strSysRptShowMaxCount = L"sys-rpt-show-max-count";
	m_strExportRptUseUpdateGuideBook = L"export-rpt-use-update-gb";
	m_strIsSingleApp = L"is-single-app";
	m_strEngineUseCommTestMode = L"engine-comm-test-mode";
	m_strFacBatchTestMngrFileKey = L"factory-batch-test";

	//workspace.xml
	m_strWorkspaceKeyEx = L"Workspace";
	m_strAppExitStateKey = L"AppExitState";
	m_strCurrTaskKey = L"CurrTask";
	m_strCurrTestKey = L"CurrTest";

	//Tasks
	m_strTaskMngrKey = L"task-mngr";
	m_strTaskMngrsKey = L"task-mngrs";
	m_strTasksMngrSrcFileKey = L"task-mngrs-src-file";
	m_strTaskMngrsGroupKey = L"task-mngrs-group";
	m_strTaskMngrsDBKey = L"task-mngrs-DB";
	m_strCTestWzdDefineKey = L"test-wzd";
	m_strCTestWzdDefinesKey = L"test-wzd-defines";
	m_strCStationTestMainConfigKey = L"station-test-config";
	m_strXTestDbGroupPathKey = L"xtest-db-group-path";
	m_strShowWordRptKey = L"show-wod-rpt";
	m_strEngineModeKey = L"EngineMode";

	//Task
	m_strTaskKey = L"Task";
	m_strIDKeyEx = L"ID";
	m_strLocalIDKey = L"LocalID";
	m_strTestTypeKey = L"TestType";
	m_strLocationKey = L"Location";
	m_strPlanBeginKey = L"PlanBegin";
	m_strPlanFinishKey = L"PlanFinish";
	m_strTestBeginKey = L"TestBegin";
	m_strTestFinishKey = L"TestFinish";
	m_strNameKeyEx = L"Name";
	m_strTestStateKey = L"TestState";
	m_strDvmTestStateKey = L"DvmTestState";
	m_strProtocolTestStateKey = L"ProtocolTestState";
	m_strMaxMgrpIDKey = L"MaxMgrpID";
	m_strTestTimeLongKey = L"TestTimeLong";
	m_strPpTemplateFileKey = L"PpTemplateFile";
	m_strPpEngineProgIDKey = L"PpEngineProgID";
	m_strReportSNKey = L"ReportSN";
	m_stDeviceModelFileKey = L"DeviceModelFile";
	m_strReportSNGenKey = L"ReportSNGen";
	m_strReportSNGenDateKey = L"Date";
	m_strReportSNGenIndexKey = L"Index";

	//project
	m_strProjectKey = L"project";
	m_strProtocolTemplateKey = L"ProtocolTemplate";
	m_strCurrTestItemIndex = L"CurrTestItemIndex";
	m_strPpDeviceFileKey = L"PpDeviceFile";
	m_strTemplateFileKey = L"TemplateFile";
	m_strReportMapFileKey = L"ReportMapFile";
	m_strTestItemErrRefKey = L"TestItem";

	m_strCPpDeviceRefsKey  = L"CPpDeviceRefs";
	m_strCPpDeviceRefKey   = L"CPpDeviceRef";;

	m_strTestControlModeKey = L"test-control-mode";
	m_strReportModeKey      = L"report-mode";

	m_strMgbrptKey = L"mgbrpt";

	m_strAutoSaveGbDevKey      = L"auto-save-gbdev";
	m_strAutoSaveGbDevTimeLongKey      = L"auto-save-gbdev-time";
	m_strTestWndModeKey      = L"test-wnd-mode";

	m_strWordPageOrientationKey = L"page-orientation";
	m_strReportFillClassIDKey = L"rpt-class-id";
	m_strSystemPathKey = L"sys-path";

	m_strScriptRunTimeLongKey = L"cal-tm-long-script-run";
	m_strEngineCalTimeLongKey = L"cal-tm-long-engine-call";
	m_strAdjustByTkIDModeKey = L"adjust-by-tkid-mode";
	m_strReportProgIDKey = L"report-prog-id";
	m_strViewWordForMrptCountKey = L"view-word-rpts-min";
	m_strEnableViewWordForMrptKey = L"enable-view-word-rpts-min";
	m_strSmartTestModeKey = L"smart-test-mode";
	m_strIpTestAppKey = L"ip-test-app";
	m_strIpDeviceKey = L"ip-device";
	m_strInlegibleFontBoldKey = L"inlegible-font-bold";
	m_strItemsCountModeKey = L"items-count-mode";
	m_strExportDatasSavePathKey = L"export-datas-save-path";

	//GuideBookExportConfig
	m_strGuideBookExportConfigKey = L"guidebook-export-config";
	m_strGuideBookExportGlobalDatasKey = L"guidebook-export-globaldatas";
	m_strGuideBookExportJobGuideKey = L"guidebook-export-jobguide";
	m_strGuideBookExportExtendRptDefKey = L"guidebook-export-extendrptdef";
	m_strGuideBookExportAttrGbxmlKey = L"guidebook-export-attr-gbxml";
	m_strGuideBookExportAttrDvmxmlKey = L"guidebook-export-attr-dvmxml";
	m_strGuideBookExportAttrPpxmlKey = L"guidebook-export-attr-ppxml";
	m_strGuideBookExportDeviceModelKey = L"guidebook-export-devicemodel";
	m_strGuideBookExportSysParasKey = L"guidebook-export-sysparas";
	m_strGuideBookExportRptMapKey = L"guidebook-export-rptmap";
	m_strGuideBookExportReportsKey = L"guidebook-export-reports";
	m_strGuideBookExportAttrSimplifyKey = L"guidebook-export-attr-simplify";
	m_strGuideBookExportSysParaEditKey = L"guidebook-export-sysparaedit";
	m_strGuideBookExportSafetyDatasKey = L"guidebook-export-safetydatas";
	m_strGuideBookExportSafetyDllCallKey = L"guidebook-export-safetydllcall";
	m_strGuideBookExportSafetyMsgKey = L"guidebook-export-safetymsg";
	m_strGuideBookExportCmdParaKey = L"guidebook-export-cmdpara";
	m_strGuideBookExportCmdDatasKey = L"guidebook-export-cmddatas";
	m_strGuideBookExportCmdDsvScriptKey = L"guidebook-export-cmddsvscript";
	m_strGuideBookExportMacroTestParasKey = L"guidebook-export-macrotestparas";
	m_strGuideBookExportRptMapNotSaveNullKey = L"guidebook-export-rptmap-notsavenull";
	m_strGuideBookExportRptMapOnlySaveLastKey = L"guidebook-export-rpt-onlysavelast";
	m_strGuideBookExportReportOnlySaveBkmkKey = L"guidebook-export-report-onlysavebkmk";
	m_strGuideBookExportExprScriptKey = L"guidebook-export-expr-script";
	m_strGuideBookExportScriptNameKey = L"guidebook-export-script-name";
	m_strGuideBookExportScriptInitKey = L"guidebook-export-script-init";
	m_strGuideBookExportScriptRsltKey = L"guidebook-export-script-rslt";

	m_strGbdevSaveStruDescFileKey = L"gbdev-save-stru-desc-file";
	m_strUseSttAtsSvrKey = L"use-stt-ats-svr";
	m_strSttAtsSvrKey = L"stt-ats-svr-scene";
	m_strDisableOptrWhenUseAtsSvrKey = L"disable-optr-when-use-atssvr";
	m_strRptProgIDKey = L"rpt-progid";
	m_strShowTestMsgWndKey = L"show-test-msg-wnd";
}
