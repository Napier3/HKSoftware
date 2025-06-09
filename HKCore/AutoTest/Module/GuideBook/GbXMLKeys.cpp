#include "stdafx.h"
#include "GbXMLKeys.h"
#include "../../../Module/Expression/XExprGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CGbXMLKeys* CGbXMLKeys::g_pGbXMLKeys = NULL;
long CGbXMLKeys::g_nGbXmlKeysRef = 0;

CGbXMLKeys* CGbXMLKeys::CreatetGbXMLkeys()
{
	CXExprXmlRWKeys::Create();
	g_nGbXmlKeysRef++;

	if(g_nGbXmlKeysRef == 1)
	{
		g_pGbXMLKeys = new CGbXMLKeys();

	}

	return g_pGbXMLKeys;
}

void CGbXMLKeys::Release()
{
	CXExprXmlRWKeys::Release();

	if (g_nGbXmlKeysRef == 0)
	{
		return;
	}

	g_nGbXmlKeysRef--;

	if (g_nGbXmlKeysRef == 0)
	{
		delete g_pGbXMLKeys;
		g_pGbXMLKeys = NULL;
	}
}

CGbXMLKeys::CGbXMLKeys()
{
	m_nSaveItemRpts = 1;   //默认保存报告

#ifdef ScriptText_NoGb
	CDataMngrXmlRWKeys::Create();
#else
	CCharacteristicXmlRWKeys::Create();
#endif

	m_strTestDefineKey = L"test-define";
	m_strCMacroCharItemLineDefKey = L"char-item-line";
	m_strCMacroCharItemsKey  = L"macro-char-items";

	m_strCAinExpandMngrKey = L"ain-expands";
	m_strCAinExpandKey = L"ain-expand";
	m_strAbsKey = L"abs";
	m_strRealKey = L"real";
	m_strRsltKey = L"rslt";
	m_strShowWordRptKey = L"show-wod-rpt";

	m_strAnalogsKey = L"analogs";
	m_strSetsKey = L"sets";
	m_strCtrlWordsKey = L"ctrl-words";
	m_strSoftSwitchsKey = L"soft-switchs";
	m_strBinaryInsKey = L"binary-ins";
	m_strBinaryOutsKey = L"binary-outs";
	m_strSoesKey = L"soes";
	m_strBinaryKey = L"binary";
	m_strCommCmdConfigKey = L"comm-cmd-config";
	m_strMacroFileKey = L"macro-file";
	m_strTestTypeFileKey = L"test-type-file";

	 m_strGuideBookKey = L"guidebook";
	 m_strDeviceIDKey =  L"device-id";
	 m_strDevByKey = L"dev-by";
	 m_strVersionKey = L"version";
	 m_strCommCmdConfigFileKey = L"comm-cmd-config";
	 m_strPpTemplateFileKey = L"pp-template";
	 m_strScriptMngrFileKey = L"script-library";
	 m_strPpEngineProgIDKey = L"ppengine-progid";
	 m_strDvmFileKey = L"dvm-file";
	 m_strStandNameFileKey = L"stand-file";
	 m_strDeviceModelFileKey = L"device-model-file";
	 m_strTestControlModeKey = L"test-control-mode";
	 m_strExpandConfigFileKey = L"expand-config-file";
	 m_strIecfgFileKey = L"iecfg-file";
	 m_strReadOnlyKey = L"read-only";
	 m_strSaveRptToDBKey = L"save-rpt-to-db";
	 m_strAuthoritySNKey = L"authority-sn";
	 m_strAuthorityCopKey = L"authority-cop";
	 m_strScriptTypeKey = L"script-type";

	 m_strJobGuideKey = L"job-guide";
	 m_strItemsKey = L"items";
	m_strSafetyKey = L"safety";
	m_strMdvTestEachKey = L"mdv-test-each";

	//items Attributes
	 m_strTypeKey = L"type";
	 m_strCmdRwKey = L"rw-optr";
	 m_strRepeatTimes = L"repeat-timers";
	 m_strReportFillUseNoRepeatKey = L"rpt-fill-no-repeat";
	 m_strTkIDKey = L"tkid";
	 m_strIndexKey = L"index";
	 m_strShowKey = L"show";
	 m_strEnableKey = L"enable";
	 m_strStateKey = L"state";
	 m_strSortSoeByTKey = L"sort-soe";
	 m_strDsvRunAfterResultScriptKey = L"dsv-run-after-rst";
	 m_strCmdExecModeForMgbrptKey = L"mgbrpt-cmd-mode";
	 m_strFillRptDatasetKey = L"fill-rpt-dataset";
	 m_strActLogicKey = L"act-logic";

	 //shaolei 2023-6-20
	 m_strRptTitleKey = L"rpt-title";
	 m_strTitleLevelKey = L"title-level";

	//Result Expression Script
	 m_strRsltExprKey = L"expr";
	 m_strRsltExprScriptKey = L"expr-script";
	 m_strRsltExprScriptMngrKey = L"expr-script-mngr";

	 m_strStandIDKey = L"stand-id"; //输出的标准值
	 m_strStandCalExprKey = L"std-expr"; //输出的标准值
	 m_strDvmDataCalExprKey = L"data-expr";  //数据计算公式
	 m_strAbsErrCalExprKey = L"abs-err-expr";
	 m_strRelErrCalExprKey = L"rel-err-expr"; 
	 m_strDvmDataIDKey = L"data-id";    //数据ID
	 m_strDvmDataAbsErrIDKey = L"data-abs-err-id";
	 m_strDvmDataRelErrIDKey = L"data-rel-err-id";
	 m_strVarAbsErrKey = L"var-abs-err";   //绝对误差限
	 m_strVarRelErrKey = L"var-rel-err";   //相对误差限
	 m_strRsltVarAbsErrKey = L"rslt-var-abs-err"; 
	 m_strRsltVarRelErrKey = L"rslt-var-rel-err";

	//safety Attributes
	 m_strExecTypeKey = L"exectype";
	 m_strBatchItemKey = L"batch-item";
	 m_strSoundFileKey = L"sound-file";
	 m_strManyDeviceTestModeKey = L"many-rpt-test-mode";

	 m_strStandardKey = L"standard";
	 m_strMsgKey = L"msg";
	 m_strDatasKey = L"datas";
	 m_strTableKey = L"table";
	 m_strScriptKey = L"script";
	 m_strScriptResultKey = L"script-result";
	 m_strScriptInitKey = L"script-init";
	 m_strScriptNameKey = L"script-name";
	 m_strScriptMngrKey = L"scriptmngr";
	 m_strScriptIsRefKey = L"is-ref";
	 m_strDllCallKey = L"dllcall";
	 m_strFuncNameKey = L"func-name";
	 m_strParaTypeKey = L"para-type";
	 m_strResultFileKey = L"result-file";

	//reports
	 m_strReportsKey = L"reports";
	 m_strReportKey = L"report";

	 m_strBeginTimeKey = L"begintime";
	 m_strEndTimeKey = L"endtime";
	 m_strReportValueElementKey = L"value";
	 m_strReportValAttrKey = L"value";
	 m_strBkmkDataAttrIDKey = L"attr-id";
	 m_strBkmkProcessKey = L"process";
	 m_strBkmkFillModeKey = L"fill-mode";
	m_strMgrpCmbnModeKey = L"mgrp-cmbn";

	//device Attributes
	 m_strDeviceKey = L"device";
	 m_strFactoryKey = L"factory";
	m_strDeviceTypeKey = L"type";
	m_strStandNameKey = L"stand-name";
	m_strIsTimeSetsUnit_ms_Key = L"is-time-sets-unit-s";
	m_strSrcDeviceModelFileKey = L"src-device-model-file";
	m_strDsvTextWithValueKey = L"dsv-text-with-value";
	m_strDsvTextWithUtcTimeKey = L"dsv-text-with-utctime";

	//cpus
	 m_strCpusKey = L"cpus";
	 m_strCpuKey = L"cpu";
	 m_strDeviceModelKey = L"device-model";
	 m_strLDeviceKey = L"ldevice";
	 m_strDataSetKey = L"dataset";
	 m_strDataSetGroupKey = L"dataset-group";
	 m_strLogKey = L"log";
	 m_strLogsKey = L"logs";
	 m_strLogCtrlKey = L"log-ctrl";
	 m_strLogCtrlsKey = L"log-ctrls";
	 m_strTestGlobalDatasMngrKey = L"test-global-datas-mngr";

	//analogs
	 //m_strAnalogsKey = L"analogs";
	 m_strAnalogKey = L"analog";
	 m_strUnitKey = L"unit";

	//sets
	 //m_strSetsKey = L"sets";
	 m_strSetKey = L"set";
	 m_strDataTypeKey = L"data-type";
	 m_strMinValKey = L"min";
	 m_strMaxValKey = L"max";
	 m_strRWAttrKey = L"rw-attr";
	 m_strDataIndexKey = L"data-index";

	//ctrl-words
	 //m_strCtrlWordsKey = L"ctrl-words";
	//soft-switchs
	 //m_strSoftSwitchsKey = L"soft-switchs";
	//binary-ins
	 //m_strBinaryInsKey = L"binary-ins";
	 //m_strBinaryKey = L"binary";
	//binary-outs
	 //m_strBinaryOutsKey = L"binary-outs";
	//soes
	 //m_strSoesKey = L"soes";
	 m_strSoeKey = L"soe";
	 m_strTimeKey = L"time";

	//sys-paras
	 m_strSysParasKey = L"sys-paras";
	 m_strDataKey = L"data";
	 m_strFormatKey = L"format";
	 m_strRemarkKey = L"remark";
	 m_strSelectKey = L"select";
	 m_strTestParaEditModeKey = L"test-para-edit-mode";
	 m_strProjectIDKey = L"project-id";

	//test-paras
	 m_strTestParasKey = L"test-paras";

	//macrotest
	 m_strMacroTestKey = L"macrotest";
	//para
	 m_strParaKey = L"para";
	 m_strMacroIDKey = L"macroid";
	 m_strTestModeKey = L"testmode";
	 m_strParaDatasKey = L"para-datas";

	 //fpara
	 m_strFaultParaKey = L"fparas";
	 m_strFaultParaUserKey = L"fparas-usr";
	 m_strParaSysVarKey = L"sys-var";
	 m_strSysVarTypeKey = L"type";
	 m_strSysVarPathKey = L"path";
	 m_strFaultParaTableParaKey = L"para";
	 m_strFaultParaTableParaUserKey = L"user";

	//commcmd
	 m_strCommCmdKey = L"commcmd";
	 m_strCpuIDKey = L"cpu";
	 m_strDataSetPathKey = L"dataset-path";

	//cmd
	 m_strCmdKey = L"cmd";
	 m_strDelayBeforeCmdKey = L"delaybeforecmd";
	 m_strDelayAfterCmdKey = L"delayaftercmd";
	 m_strCalModeKey = L"cal-mode";
	 m_strDelayBeforeTryKey = L"delaybefortry";
	 m_strMaxRetryTimesKey = L"maxretrytimes";
	 m_strRetryTimesKey = L"retrytimes";
	 m_strTimeLongKey = L"timelong";
	 m_strTimeGapKey = L"timegap";
	 m_strTimeIgnoreKey = L"time-ignore";
	 m_strUseCurrSetDataKey = L"usecurrsetdata";
	 m_strUseDeviceExKey = L"usedeviceex";
	 m_strBeginModeKey = L"begin-mode";
	 m_strCharacteristicIDKey = L"characteristic-id";
	m_strUseConnectKey = L"use-connect";
	m_strZoneIndexKey = L"zone-index";
	m_strStxmlFileKey = L"stxml";
	m_strWzdMapFileKey = L"wzd-map";

	//sysparaedit
	 m_strSysParaEditKey = L"sysparaedit";
	 m_strParasKey = L"paras";
	 m_strSysParaEditGroupKey = L"sysparaedit-group";
	 m_strSysParaEditGroupsKey = L"sysparaedit-groups";

	m_strValueKey = L"value";
	m_strDefaultValueKey = L"default-value";

	m_strPrecisionKey = L"precision";
	m_strBkmkKey = L"bkmk";
	m_strAreaKey = L"Area";
	m_strReportMapKey = L"rpt-map";	
	m_strMapRepeatKey = L"map-repeat";	
	m_strAreaTypeKey = L"type";

	//////////////////////////////////////////////////////////////////////////
	m_pReportValueKeys = CDataMngrXmlRWKeys::CreateNew();

	m_strCGbDataSetTypeKey = L"data-set-type";
	m_strCGbDataSetTypesKey = L"data-set-type";
	m_strDsParameterKey = L"dsParameter";
	m_strDsSettingKey = L"dsSetting";
	m_strDsEnaKey = L"dsEna";
	m_strDsAinKey = L"dsAin";
	m_strDsDinKey = L"dsDin";
	m_strDsRecKey = L"dsRec";
	m_strDsTripInfoKey = L"dsTripInfo";
	m_strDsAlarmKey = L"dsAlarm";
	m_strDsWarningKey = L"dsWarning";
	m_strDsSoeKey = L"dsSoe";
	m_strDsSVKey = L"dsSV";
	m_strDsGOOSEKey = L"dsGOOSE";
	m_strCanWriteKey = L"can-write";

	m_strGbtDataInterfacesKey = L"data-interfaces";
	m_strGbtDataInterfaceKey = L"data-interface";
	m_strGbtDataKey = L"data";
	m_strGbtDatasKey = L"datas";
	m_strGbtDataScriptKey = L"key-script";
	m_strGbtDataKeyKey = L"key";

	m_strGbtDataScptOptrAndKey = L"and";
	m_strGbtDataScptOptrOrKey = L"or";
	m_strGbtDataScptOptrNotKey = L"not";
	m_strGbtDataScptFuncMustHaveKey = L"must-have";
	m_strGbtDataScptFuncMustNotHaveKey = L"must-not-have";

	m_strAxisModeKey = L"axis-mode";   //Axis mode:x-y; r-angle
	m_strParaIdXbKey = L"x-b";
	m_strParaIdYbKey = L"y-b";
	m_strParaIdXeKey = L"x-e";
	m_strParaIdYeKey = L"y-e";
	m_strParaIdXsetKey = L"x-set";
	m_strParaIdYsetKey = L"y-set";
	m_strParaIdXactKey = L"x-act";
	m_strParaIdYactKey = L"y-act";
	m_strParaIdFlagActKey = L"flag-act";

	m_strParaIdSearchXbKey = L"search-x-b";
	m_strParaIdSearchYbKey = L"search-y-b";
	m_strParaIdSearchActbKey = L"search-actb";
	m_strParaIdSearchXeKey = L"search-x-e";
	m_strParaIdSearchYeKey = L"search-y-e";
	m_strParaIdSearchActeKey = L"search-acte";
	m_strParaIdSearchXcKey = L"search-x-c";
	m_strParaIdSearchYcKey = L"search-y-c";

	//2019-3-17  自动测试过程，与模板生成过程集成到一起
	m_strCGbWzdAutoTemplateKey = L"template";
	m_strCGbWzdAutoConfigKey = L"gb-wzd-auto";
	m_strDvm_FileKey = L"dvm-file";
	m_strGbxml_FileKey = L"gbxml-file";
	m_strRel_PathKey = L"rel-path";
	m_strBin_OffsetKey = L"bin-offset";
	m_strBout_OffsetKey = L"bout-offset";
	m_strDateKey = L"date";
	m_strCnt_BinKey = L"cnt-bin";
	m_strCnt_BoutKey = L"cnt-bout";
	m_strAutoKey = L"Auto";
	m_strDICountKey = L"DICount";
	m_strDOCountKey = L"DOCount";
	m_strEnaCountKey = L"EnaCount";
	m_strBmkDITestKey = L"Bmk_DITest";
	m_strBmkDOTestKey = L"Bmk_DOTest";

	m_strItemMngrKey = L"itemmngr";
	m_strwzdAutoItemsKey = L"items";
	m_strItemTypeKey = L"itemtype";
	m_strwzdAutoSafetyKey = L"safety";
	m_strItemParaMngrKey = L"itemparamngr";
	m_strItemParaKey = L"itempara";

	//2020-5-24
	m_strCSysGbRptUIKey = L"sys-rpt-ui";
	m_strCSysRptTableKey = L"table";
	m_strCSysRptTrKey = L"tr";
	m_strCSysRptTdKey = L"td";
	m_strCSysRptTextKey = L"text";
	m_strTextKey = L"text";
	m_strAlignKey = L"align";
	m_strFont_SizeKey = L"font-size";
	m_strFont_NameKey = L"font-name";
	m_strBkmkKey = L"bkmk";
	m_strRowspanKey = L"rowspan";
	m_strBorderKey = L"border";
	m_strWidthKey = L"width";
	m_strHeightKey = L"height";
	m_strBgColorKey = L"bgcolor";
	m_strCellPaddingKey = L"cellpadding";

	//2021-11-17  lijunqing
	m_strGbDevSaveStruDescFileKey = L"save-truct-file";
	m_strGbDevSaveStruDescDsvKey = L"truct-file-has-dsv";

	//shaolei 2022-01-05
	m_strTestMacroUiParasKey = L"test-macro-ui-paras";
	//shaolei 2023-3-22
	m_strTestMacroCharParasKey = L"test-macro-char-paras";

	//lijunqing 2022-9-24
	m_strCItemRsltExprRunKey = L"rslt-expr";  //reult-expr

	m_strHdResReqestKey = L"hd-res-req";  //HdResReq

	InitReportValueXMLRWKeys();
}

CGbXMLKeys::~CGbXMLKeys()
{
	CDataMngrXmlRWKeys::Release(m_pReportValueKeys);
	m_pReportValueKeys = NULL;

#ifdef ScriptText_NoGb
	CDataMngrXmlRWKeys::Release();
#else
	CCharacteristicXmlRWKeys::Release();
#endif

}

//shaolei  2023-3-19  保存模板时，是否保存测试项目的报告（reports节点）
void CGbXMLKeys::IncXml_SaveItemRpts(CGbXMLKeys *pXmlKeys, long nAdd)
{
	if (pXmlKeys == NULL)
	{
		g_pGbXMLKeys->m_nSaveItemRpts += nAdd;
	}
	else
	{
		pXmlKeys->m_nSaveItemRpts += nAdd;
	}
}

void CGbXMLKeys::DecXml_SaveItemRpts(CGbXMLKeys *pXmlKeys, long nDec)
{
	if (pXmlKeys == NULL)
	{
		g_pGbXMLKeys->m_nSaveItemRpts -= nDec;
	}
	else
	{
		pXmlKeys->m_nSaveItemRpts -= nDec;
	}
}

void CGbXMLKeys::InitReportValueXMLRWKeys()
{
	if (m_pReportValueKeys == NULL)
	{
		return ;
	}

// 	m_pReportValueKeys->put_IDKey(m_strIDKey);
// 	m_pReportValueKeys->put_ValueElementKey(m_strReportValueElementKey);
// 	m_pReportValueKeys->put_ValueKey(m_strReportValAttrKey);
// 	m_pReportValueKeys->put_IDKey(m_strIDKey);
// 	m_pReportValueKeys->put_IDKey(m_strIDKey);
// 	m_pReportValueKeys->put_IDKey(m_strIDKey);
}
