//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttCmdDefineGlobal.cpp

#include "stdafx.h"
#include "SttCmdDefineGlobal.h"
#include "../../../Module/Expression/XExprGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CSttCmdDefineXmlRWKeys

CSttCmdDefineXmlRWKeys* CSttCmdDefineXmlRWKeys::g_pXmlKeys = NULL;
long CSttCmdDefineXmlRWKeys::g_nMngrRef = 0;


CSttCmdDefineXmlRWKeys::CSttCmdDefineXmlRWKeys()
{
	m_bOnlyGetItem = FALSE;
	m_nGuideBookUseItemKey = 0;

	m_strCSttIotTopoKey = L"topo";
	m_strCSttIotNodeKey = L"node";
	m_strCSttIotDevicesKey = L"devices";
	m_strCSttIotDeviceKey = L"device";
	m_strCSttMsgKey = L"msg";
	m_strCSttMsgsKey = L"msgs";
	m_strCSttRptMapDatasKey = L"rpt-map-datas";
	m_strCSttReportsKey = L"reports";
	m_strCSttReportKey = L"report";
	m_strCSttSysStateKey = L"sys-state";
	m_strCSttAssistCmdKey = L"assist-cmd";
	m_strCSttDebugCmdKey = L"dbg-cmd";
	m_strCSttRemoteCmdKey = L"remote-cmd";
	m_strCSttAtsCmdKey = L"ats-cmd";
	m_strCSttSystemCmdKey = L"sys-cmd";
	m_strCSttAdjustCmdKey = L"adj-cmd";
	m_strCSttTestCmdKey = L"test-cmd";
	m_strCSttIotCmdKey = L"iot-cmd";
	m_strCSttMacroKey = L"macro";
	m_strCSttParasKey = L"paras";
	m_strCSttResultsKey = L"results";
	m_strCSttSearchResultsKey = L"search-results";
	m_strCSttCmdBaseKey = L"SttCmdBase";
	m_strCSttCmdDataKey = L"SttCmdData";
	m_strTestorKey = L"testor";
	m_strMater_HostKey = L"mater-host";
	m_strRetTypeKey = L"ret-type";
	m_strRetCmdKey = L"id-cmd";
	m_strVersionKey = L"version";
	m_strTypeKey = L"type";
	m_strRemarkKey = L"remark";

	m_strBeginTimeKey = L"begintime";
	m_strEndTimeKey = L"endtime";

	m_strMidKey = L"mid";
	m_strTimeKey = L"time";
	m_strLevelKey = L"level";
	m_strContentKey = L"content";
	m_strDevCodeKey = L"devCode";
	m_strDevTypeKey = L"devType";
	m_strSNKey = L"SN";
	m_strCatKey = L"cat";
	m_strParentKey = L"parent";
	m_strStateKey = L"state";

	m_strCSttHdChKey = L"hd-ch";
	m_strCSttHdChsKey = L"hd-chs";
	m_strCSttChMapKey = L"ch-map";
	m_strCSttChMapsKey = L"ch-maps";
	m_strAliasKey = L"alias";
	m_strRsIndexKey = L"rs-index";

	//shaolei 20210724
	m_strCSttSysParaEditKey = L"sysparaedit";
	m_strCSttSafetyKey = L"safety";
	m_strCSttMacroTestKey = L"macrotest";
	m_strCSttCommCmdKey = L"commcmd";
	m_strCSttDataObjKey = L"data";
	m_strCSttSysParasKey = L"sys-paras";
	m_strCSttReportMapKey = L"rpt-map";
	m_strCSttRptDataKey = L"data";
	m_strCSttJobGuideKey = L"job-guide";
	m_strCSttDeviceKey = L"device";
	m_strCSttItemsKey = L"items";
	m_strCSttItemBaseKey = L"item";
	m_strCSttGuideBookKey = L"guidebook";
	m_strTestMacroFileIDKey = L"macro-file";
	m_strTestTypeFileKey = L"test-type-file";
	m_strDeviceIdKey = L"device-id";
	m_strDevByKey = L"dev-by";
	//m_strVersionKey = L"version";
	m_strCommCmdConfigFileKey = L"comm-cmd-config";
	m_strPpTemplateFileKey = L"PpTemplateFile";
	m_strScriptMngrFileKey = L"script-library";
	m_strPpEngineProgIDKey = L"PpEngineProgID";
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
	m_strTkidKey = L"tkid";
	m_strShowKey = L"show";
	m_strEnableKey = L"enable";
	m_strExectypeKey = L"exectype";
	m_strBatchItemKey = L"batch-item";
	m_strMdvTestEachKey = L"mdv-test-each";
	//m_strStateKey = L"state";
	m_strSelectKey = L"select";
	//m_strTypeKey = L"type";
	m_strCharacteristicIDKey = L"characteristic-id";
	m_strStxmlFileKey = L"stxml";
	m_strWzdMapFileKey = L"wzd-map";
	m_strActLogicKey = L"act-logic";
	m_strFactoryKey = L"factory";
	m_strDeviceTypeKey = L"type";
	m_strIsTimeSetsUnit_ms_Key = L"is-time-sets-unit-s";
	m_strDsvTextWithValueKey = L"dsv-text-with-value";
	m_strDsvTextWithUtcTimeKey = L"dsv-text-with-utctime";
	m_strSrcDeviceModelFileKey = L"src-device-model-file";
	m_strPrecisionKey = L"precision";
	m_strDataTypeKey = L"data-type";
	m_strRWAttrKey = L"rw-attr";
	m_strUnitKey = L"unit";
	m_strValueKey = L"value";
	m_strDefaultValueKey = L"default-value";
	m_strMinValKey = L"min";
	m_strMaxValKey = L"max";
	m_strStepKey = L"step";
	m_strDataIndexKey = L"data-index";
	m_strCmdRwKey = L"rw-optr";
	m_strSortSoeByTKey = L"sort-soe";
	m_strDsvRunAfterResultScriptKey = L"dsv-run-after-rst";
	m_strCmdExecModeForMgrptKey = L"mgbrpt-cmd-mode";
	m_strFillRptDatasetKey = L"fill-rpt-dataset";
	m_strRepeatTimesKey = L"repeat-timers";
	m_strCalModeKey = L"cal-mode";
	m_strReportFillUseNoRepeatKey = L"rpt-fill-no-repeat";
	m_strSoundFileKey = L"sound-file";
	m_strManyDeviceTestModeKey = L"many-rpt-test-mode";
	m_strMacroIDKey = L"macroid";
	m_strContentsKey = L"contents";
	m_strTestMacroUiParasKey = L"test-macro-ui-paras";
	m_strTestMacroCharParasKey = L"test-macro-char-paras";
	m_strCSttMacroCharItemsKey = L"macro-char-items";
	m_strTestModeKey = L"testmode";
	m_strParaKey = L"para";
	m_strCSttCharacteristicKey = L"characteristic";
	m_strAutoCloseKey = L"auto-close";
	m_strAxisKey = L"axis";
	m_strTestLineModeKey = L"test-line-mode";
	m_strXMinKey = L"x-min";
	m_strXMaxKey = L"x-max";
	m_strYMinKey = L"y-min";
	m_strYMaxKey = L"y-max";

	//2022-7-24  lijunqing
	m_strCMacroCharItemLineDefKey = L"char-item-line";
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

	//cmd-data
	m_strCSttCommCmdDataKey = L"cmd";
	m_strDataSetPathKey = L"dataset-path";
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
	m_strCSttItemRsltExprKey = L"rslt-expr";
;
#ifndef CLIENT_TEST_ENGINE_IN_LOCAL
	m_strCoefKey = L"coef";
#endif

	//shaolei 2023-6-20
	m_strRptTitleKey = L"rpt-title";
	m_strTitleLevelKey = L"title-level";

    //lijunqing 2024-10-25
    m_strCSttLicenseMngrKey = L"license-mngr";
    m_strCSttLicenseKey = L"license";
    m_strCSttLicenseModuleKey = L"module";
    m_strKeyKey = L"key";
    m_strYearKey = L"year";
    m_strMonthKey = L"month";
    m_strDayKey = L"day";
    m_strDaysKey = L"days";
    m_strTimesKey = L"times";
	m_strCurrTimesKey = L"currtimes";
	m_strTestGlobalDatasMngrKey = L"test-global-datas-mngr";  //shaolei 2024-12-11
}

CSttCmdDefineXmlRWKeys::~CSttCmdDefineXmlRWKeys()
{

}

CSttCmdDefineXmlRWKeys* CSttCmdDefineXmlRWKeys::Create()
{
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
	CXExprXmlRWKeys::Create();
#endif

	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CSttCmdDefineXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSttCmdDefineXmlRWKeys::Release()
{
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
	CXExprXmlRWKeys::Release();
#endif

	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}

//2022-3-24  lijunqing
void CSttCmdDefineXmlRWKeys::stt_Inc_GuideBookUseItemKey(CSttCmdDefineXmlRWKeys *pXmlKeys)
{
	if (pXmlKeys == NULL)
	{
		CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nGuideBookUseItemKey++;
	}
	else
	{
		pXmlKeys->m_nGuideBookUseItemKey++;
	}
}

void CSttCmdDefineXmlRWKeys::stt_Dec_GuideBookUseItemKey(CSttCmdDefineXmlRWKeys *pXmlKeys)
{
	if (pXmlKeys == NULL)
	{
		CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nGuideBookUseItemKey--;
	}
	else
	{
		pXmlKeys->m_nGuideBookUseItemKey--;
	}
}

long CSttCmdDefineXmlRWKeys::stt_Is_GuideBookUseItemKey(CSttCmdDefineXmlRWKeys *pXmlKeys)
{
	if (pXmlKeys == NULL)
	{
		return CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nGuideBookUseItemKey;
	}
	else
	{
		return pXmlKeys->m_nGuideBookUseItemKey--;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSttCmdDefineConstGlobal

long CSttCmdDefineConstGlobal::g_nGlobalRef = 0;
CSttCmdDefineConstGlobal* CSttCmdDefineConstGlobal::g_pGlobal = NULL;


CSttCmdDefineConstGlobal::CSttCmdDefineConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CSttCmdDefineConstGlobal::~CSttCmdDefineConstGlobal()
{
}

CSttCmdDefineConstGlobal* CSttCmdDefineConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSttCmdDefineConstGlobal();
	}

	return g_pGlobal;
}

void CSttCmdDefineConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

//CTestDataTypeMngrConstGlobal
long CTestDataTypeMngrConstGlobal::g_nDataTypeGlobal = 0;
CTestDataTypeMngrConstGlobal* CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal = NULL;
CTestDataTypeMngrConstGlobal::CTestDataTypeMngrConstGlobal()
{
	//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()
	InitGlobal();
}

CTestDataTypeMngrConstGlobal::~CTestDataTypeMngrConstGlobal()
{

}

CTestDataTypeMngrConstGlobal* CTestDataTypeMngrConstGlobal::Create()
{
	g_nDataTypeGlobal++;

	if (g_nDataTypeGlobal == 1)
	{
		g_pDataTypeGlobal = new CTestDataTypeMngrConstGlobal();
	}

	return g_pDataTypeGlobal;
}

void CTestDataTypeMngrConstGlobal::Release()
{
	g_nDataTypeGlobal--;

	if (g_nDataTypeGlobal == 0)
	{
		delete g_pDataTypeGlobal;
		g_pDataTypeGlobal = NULL;
	}
}

CDataTypes* CTestDataTypeMngrConstGlobal::GetTestDataTypes()
{
	ASSERT (g_pDataTypeGlobal != NULL);
	return &g_pDataTypeGlobal->m_oTestDataTypes;
}

CDataType* CTestDataTypeMngrConstGlobal::FindTestDataType( const CString &strDataTypeID )
{
	ASSERT (g_pDataTypeGlobal != NULL);
	CDataType *pDataType = NULL;

	pDataType = (CDataType*)g_pDataTypeGlobal->m_oTestDataTypes.FindByID(strDataTypeID);

	if (pDataType == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("datatype \"%s\"is not in file\"%s\""), strDataTypeID.GetString(), CFG_IECCFG_DATATYPES_FILE.GetString());
	}

	return pDataType;
}

void CTestDataTypeMngrConstGlobal::InitGlobal()
{
	Init_FaultTrigModeDataType();
	Init_K0ModeModeDataType(); 
	Init_PTPositionDataType();
	Init_CTPosDataType();
	Init_CBSimulationDataType();
	Init_IPlusDCDataType();
	Init_FaultAngModeDataType();
	Init_UxModeDataType();
	Init_CalcuMode();//mym 2021-6-28  add
	Init_RecloseMode();//mym 2021-7-5  add
	Init_TestProcess();//mym 2021-7-5  add
	Init_UzOutputDataType();//mym 2021-8-8  add
	Init_UzCKDataType();//mym 2021-8-8  add
	Init_K0CalModeDataType();//mym 2021-8-8  add
	Init_RXSelect();//mym 2021-8-8  add

	Init_USetMode();//sf 20210721 add
	Init_InputChannel();// mym 2021-8-11 add
	Init_IPoint();
	Init_InterMethod();

	Init_FaultType();//������ѡ��

	Init_DifferMarkType();	//yyj add 2021-08-25 ���ֵ������ʽ
	Init_BasicCurrSelect();//yyj add 2021-08-25 ���׼����ѡ��
	Init_ZDPointNum();		//yyj add 2021-08-25 ������ƶ����Թյ���
	Init_DiffHarmIndex();

	Init_FaultUType();
	Init_FaultDirection();
	Init_FaultDirection2();
	Init_FaultPermanent();
	Init_IFaultTrans();
	Init_FaultVolDef();

	Init_Uariable();
	Init_Iariable();
	Init_nFaultType();//��������
	Init_SearchMode();
	Init_TranSort();
	Init_CTPoint();//CT����
	Init_IrEquation();//�ƶ�����
	Init_SettingMode();//��ֵ������ʽ
	Init_HarmIndex();//г���ƶ�ϵ��
	Init_FaultPhase();//������
	Init_Conclusion();//����
	Init_FaultChannel();//����ͨ��
}

void CTestDataTypeMngrConstGlobal::Init_K0CalModeDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("K0CalMode"), _T("K0CalMode"));
	pDataType->AddNewValue(_T("S1=|K0|,,Phi(K0)"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("S2=RERL,,XEXL"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("S3=|Z0/Z1|,,Phi(Z0/Z1)"), _T(""), _T("2"));
}

void CTestDataTypeMngrConstGlobal::Init_UzCKDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("VzPhDefine"), _T("VzPhDefine"));
	pDataType->AddNewValue(_T("Va��λ"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("Vb��λ"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("Vc��λ"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("Vab��λ"), _T(""), _T("3"));
	pDataType->AddNewValue(_T("Vbc��λ"), _T(""), _T("4"));
	pDataType->AddNewValue(_T("Vca��λ"), _T(""), _T("5"));
}

void CTestDataTypeMngrConstGlobal::Init_UzOutputDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("PsuVzDefine"), _T("PsuVzDefine"));
	pDataType->AddNewValue(_T("0"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("Va"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("Vb"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("Vc"), _T(""), _T("3"));
	pDataType->AddNewValue(_T("��3��3Vo"), _T(""), _T("4"));
	pDataType->AddNewValue(_T("-��3��3Vo"), _T(""), _T("5"));
	pDataType->AddNewValue(_T("3Vo"), _T(""), _T("6"));
	pDataType->AddNewValue(_T("-3Vo"), _T(""), _T("7"));
}

void CTestDataTypeMngrConstGlobal::Init_FaultTrigModeDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("FaultTrigMode"), _T("FaultTrigMode"));
	pDataType->AddNewValue(_T("ʱ�䴥��"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("�ֶ�����"), _T(""), _T("3"));
	pDataType->AddNewValue(_T("����������"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("GPS����"), _T(""), _T("4"));
}

void CTestDataTypeMngrConstGlobal::Init_K0ModeModeDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("K0Mode"), _T("K0Mode"));
	pDataType->AddNewValue(_T("|K0|,Phi(K0)"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("RERL,XEXL"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("|Z0/Z1|,Phi(Z0/Z1)"), _T(""), _T("2"));
}

void CTestDataTypeMngrConstGlobal::Init_PTPositionDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("PTPosition"), _T("PTPosition"));
	pDataType->AddNewValue(_T("ĸ�߲�"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("��·��"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_CTPosDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("CTPos"), _T("CTPos"));
	pDataType->AddNewValue(_T("ָ��ĸ��"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("ָ����·"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_CBSimulationDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("CBSimulation"), _T("CBSimulation"));
	pDataType->AddNewValue(_T("��ģ��"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("ģ��"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_IPlusDCDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("FaultId"), _T("FaultId"));
	pDataType->AddNewValue(_T("��"), _T(""), _T("0"));//20230524 zhouhj ��Ϊ��0\��1
	pDataType->AddNewValue(_T("��"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_FaultAngModeDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("FaultAngMode"), _T("FaultAngMode"));
	pDataType->AddNewValue(_T("���"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("��ֵ"), _T(""), _T("1"));
}
void CTestDataTypeMngrConstGlobal::Init_UxModeDataType()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("UxMode"), _T("UxMode"));
	pDataType->AddNewValue(_T("+3U0"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("-3U0"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("+��3��3Vo"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("-��3��3Vo"), _T(""), _T("3"));
	pDataType->AddNewValue(_T("��ͬ��A"), _T(""), _T("4"));
	pDataType->AddNewValue(_T("��ͬ��B"), _T(""), _T("5"));
	pDataType->AddNewValue(_T("��ͬ��C"), _T(""), _T("6"));
	pDataType->AddNewValue(_T("��ͬ��AB"), _T(""), _T("7"));
	pDataType->AddNewValue(_T("��ͬ��BC"), _T(""), _T("8"));
	pDataType->AddNewValue(_T("��ͬ��CA"), _T(""), _T("9"));
	pDataType->AddNewValue(_T("������ѹĸ��ѹ"), _T(""), _T("10"));
	pDataType->AddNewValue(_T("������ѹĸ��ѹ"), _T(""), _T("11"));
	pDataType->AddNewValue(_T("������ѹĸ��ѹ"), _T(""), _T("12"));
	pDataType->AddNewValue(_T("������ѹĸ��ѹ"), _T(""), _T("13"));
	pDataType->AddNewValue(_T("�����"), _T(""), _T("14"));
}

void CTestDataTypeMngrConstGlobal::Init_CalcuMode()
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("CalcuMode"), _T("CalcuMode"));
	pDataType->AddNewValue(_T("��������"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("��ѹ����"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("ϵͳ�迹����"), _T(""), _T("2"));
}

void CTestDataTypeMngrConstGlobal::Init_TestProcess()
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("TestProcess"), _T("TestProcess"));
	pDataType->AddNewValue(_T("�����źſ���"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("ʱ�����"), _T(""), _T("1"));
}


void CTestDataTypeMngrConstGlobal::Init_RecloseMode()
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("RecloseMode"), _T("RecloseMode"));
	pDataType->AddNewValue(_T("���أ�����+���أ�"), _T(""), _T("0"));//0-���أ�����+���أ� 1-���� 2-���غ�
	pDataType->AddNewValue(_T("����"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("���غ�"), _T(""), _T("2"));
}

void CTestDataTypeMngrConstGlobal::Init_USetMode()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("������ѹѡ��"), _T("USetMode"));
	pDataType->AddNewValue(_T("���ѹ"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("�ߵ�ѹ"), _T(""), _T("1"));
}
void CTestDataTypeMngrConstGlobal::Init_IPoint()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("��������"), _T("IPoint"));
	pDataType->AddNewValue(_T("ָ���ѹ��"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("ָ��ĸ��"), _T(""), _T("1"));
}
void CTestDataTypeMngrConstGlobal::Init_InterMethod()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("��ֵ��"), _T("InterMethod"));
	pDataType->AddNewValue(_T("�������ղ�ֵ��"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("���Բ�ֵ��"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_RXSelect()//�迹�ο���ʽ
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("RXSelect"), _T("RXSelect"));
	pDataType->AddNewValue(_T("Z-��"), _T(""), _T("0"));	
	pDataType->AddNewValue(_T("R-X"), _T(""), _T("1"));//0-���أ�����+���أ� 1-���� 2-���غ�
}

void CTestDataTypeMngrConstGlobal::Init_InputChannel()//����������ͨ��
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("InputChannel"), _T("InputChannel"));
	pDataType->AddNewValue(_T("A"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("B"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("C"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("D"), _T(""), _T("3"));
	pDataType->AddNewValue(_T("E"), _T(""), _T("4"));
	pDataType->AddNewValue(_T("F"), _T(""), _T("5"));
	pDataType->AddNewValue(_T("G"), _T(""), _T("6"));
	pDataType->AddNewValue(_T("H"), _T(""), _T("7"));
	pDataType->AddNewValue(_T("I"), _T(""), _T("8"));
	pDataType->AddNewValue(_T("J"), _T(""), _T("9"));
}

void CTestDataTypeMngrConstGlobal::Init_FaultType()//������ѡ��
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("FaultType"), _T("FaultType"));
	pDataType->AddNewValue(_T("A-E"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("B-E"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("C-E"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("A-B"), _T(""), _T("3"));
	pDataType->AddNewValue(_T("B-C"), _T(""), _T("4"));
	pDataType->AddNewValue(_T("C-A"), _T(""), _T("5"));
	pDataType->AddNewValue(_T("A-B-C"), _T(""), _T("6"));
	pDataType->AddNewValue(_T("3Vo"), _T(""), _T("7"));
	pDataType->AddNewValue(_T("V2"), _T(""), _T("8"));
}

void CTestDataTypeMngrConstGlobal::Init_FaultUType()//���ϵ�ѹ����
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("���ϵ�ѹ����"), _T("FaultVolType"));
	pDataType->AddNewValue(_T("��·��ѹ"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("����(U2)"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("����(3U0)"), _T(""), _T("3"));
}

void CTestDataTypeMngrConstGlobal::Init_DifferMarkType()	//���ֵ������ʽ
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("���ֵ������ʽ"), _T("DifferMarkType"));
	pDataType->AddNewValue(_T("����ֵ"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("����ֵ"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_BasicCurrSelect() //���׼����ѡ��
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("���׼����ѡ��"), _T("BasicCurrSelect"));
	pDataType->AddNewValue(_T("�߲����ε���"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("�趨ֵ"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("������ζ����"), _T(""), _T("2"));
}

void CTestDataTypeMngrConstGlobal::Init_ZDPointNum()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("�����ƶ��յ���"), _T("ZDPointNum"));
	pDataType->AddNewValue(_T("һ���յ�"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("�����յ�"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("�����յ�"), _T(""), _T("2"));
}

void CTestDataTypeMngrConstGlobal::Init_DiffHarmIndex()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("г������ѡ��"), _T("DiffHarmIndex"));
	pDataType->AddNewValue(_T("2��г��"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("3��г��"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("5��г��"), _T(""), _T("2"));
}

void CTestDataTypeMngrConstGlobal::Init_FaultDirection()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("���Ϸ���"), _T("FaultDirection"));
	pDataType->AddNewValue(_T("����"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("����"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_FaultDirection2()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("ת�����Ϲ��Ϸ���"), _T("FaultDirection2"));
	pDataType->AddNewValue(_T("����"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("����"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_FaultPermanent()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("��������"), _T("FaultPermanent"));
	pDataType->AddNewValue(_T("˲ʱ"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("����"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_IFaultTrans()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("�Ƿ�ת���Թ���"), _T("_FaultTrans"));
	pDataType->AddNewValue(_T("��"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("��"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_FaultVolDef()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("���ϵ�ѹ����"), _T("FaultVolDef"));
	pDataType->AddNewValue(_T("���ѹ"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("�ߵ�ѹ"), _T(""), _T("1"));
}
void CTestDataTypeMngrConstGlobal::Init_Uariable()//��ѹ�仯��
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("��ѹ�仯��"), _T("UVariable"));
	pDataType->AddNewValue(_T("��ѹ"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("�����ѹ(U2)"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("�����ѹ(3U0)"), _T(""), _T("2"));
}

void CTestDataTypeMngrConstGlobal::Init_Iariable()//���������
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("���������"), _T("IVariable"));
	pDataType->AddNewValue(_T("Ia"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("Ib"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("lc"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("Iabc"), _T(""), _T("3"));
}
void CTestDataTypeMngrConstGlobal::Init_nFaultType()//��������ѡ��
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("��������"), _T("FaultType1"));
	pDataType->AddNewValue(_T("A��ӵ�"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("B��ӵ�"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("C��ӵ�"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("AB��·"), _T(""), _T("3"));
	pDataType->AddNewValue(_T("BC��·"), _T(""), _T("4"));
	pDataType->AddNewValue(_T("CA��·"), _T(""), _T("5"));
	pDataType->AddNewValue(_T("�����·"), _T(""), _T("6"));
}

void CTestDataTypeMngrConstGlobal::Init_SearchMode()//������ʽ
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("������ʽ"), _T("SearchMode"));
	pDataType->AddNewValue(_T("���ַ�"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("�����ƽ�"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_TranSort()//��ѹ��������ʽ
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("��ѹ��������ʽ"), _T("TranSort"));
	pDataType->AddNewValue(_T("Y/V����ƽ���ѹ��"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("Y/��-11����(��ת��)"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("�����ѹ��"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("Y/��/������"), _T(""), _T("3"));
	pDataType->AddNewValue(_T("Scott(1)"), _T(""), _T("4"));
	pDataType->AddNewValue(_T("V/V(1)"), _T(""), _T("5"));
	pDataType->AddNewValue(_T("V/X"), _T(""), _T("6"));
	pDataType->AddNewValue(_T("Y/A�����迹ƥ��ƽ���ѹ��"), _T(""), _T("7"));
	pDataType->AddNewValue(_T("����V/V���߱�ѹ��"), _T(""), _T("8"));
	pDataType->AddNewValue(_T("Scott(2)"), _T(""), _T("9"));
	pDataType->AddNewValue(_T("Scott(3)"), _T(""), _T("10"));
	pDataType->AddNewValue(_T("V/V(2)"), _T(""), _T("11"));
	pDataType->AddNewValue(_T("Scott(4)"), _T(""), _T("12"));
	pDataType->AddNewValue(_T("����V/V���߱�ѹ��2"), _T(""), _T("13"));
	pDataType->AddNewValue(_T("����V/V"), _T(""), _T("14"));
	pDataType->AddNewValue(_T("Y/V(2)"), _T(""), _T("15"));
	pDataType->AddNewValue(_T("Scott(5)"), _T(""), _T("16"));
	pDataType->AddNewValue(_T("Y/��-11����(Y��ת��)"), _T(""), _T("17"));
}

void CTestDataTypeMngrConstGlobal::Init_CTPoint()//������ʽ
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("CT����"), _T("CTPoint"));
	pDataType->AddNewValue(_T("����ָ���ѹ��"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("һ��ָ���ѹ��"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_IrEquation()//�ƶ�����
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("Ir�ƶ�����"), _T("IrEquation"));
	pDataType->AddNewValue(_T("Ir=(|I1-I2|)��(|I1+I2|)"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("Ir=(|I1-I2|)/2��(|I1+I2|)/2"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_SettingMode()	//��ֵ������ʽ
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("��ֵ������ʽ"), _T("MinAxis"));
	pDataType->AddNewValue(_T("����ֵ"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("����ֵ"), _T(""), _T("1"));
}

void CTestDataTypeMngrConstGlobal::Init_HarmIndex()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("г������"), _T("HarmIndex"));
	pDataType->AddNewValue(_T("2"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("3"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("5"), _T(""), _T("2"));
}

void CTestDataTypeMngrConstGlobal::Init_FaultPhase()
{
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("������"), _T("FaultPhase"));
	pDataType->AddNewValue(_T("A���·"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("B���·"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("C���·"), _T(""), _T("2"));
	pDataType->AddNewValue(_T("AB���·"), _T(""), _T("3"));
	pDataType->AddNewValue(_T("BC���·"), _T(""), _T("4"));
	pDataType->AddNewValue(_T("CA���·"), _T(""), _T("5"));
	pDataType->AddNewValue(_T("ABC���·"), _T(""), _T("6"));
	pDataType->AddNewValue(_T("����"), _T(""), _T("7"));
	pDataType->AddNewValue(_T("����"), _T(""), _T("8"));
}

void CTestDataTypeMngrConstGlobal::Init_Conclusion()//�Զ�-����
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("����"), _T("TestState"));
	pDataType->AddNewValue(_T("δ����"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("�ϸ�"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("���ϸ�"), _T(""), _T("2"));
}

void CTestDataTypeMngrConstGlobal::Init_FaultChannel()//��������(ֱ��)-����ͨ��
{	
	CDataType *pDataType = m_oTestDataTypes.AddNew2(_T("����ͨ��"), _T("FaultChannel"));
	pDataType->AddNewValue(_T("Ia1"), _T(""), _T("0"));
	pDataType->AddNewValue(_T("Ib1"), _T(""), _T("1"));
	pDataType->AddNewValue(_T("Ic1"), _T(""), _T("2"));
}
