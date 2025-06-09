#include "stdafx.h"
#include "../../Module/api/GlobalConfigApi.h"
#include "../../Module/api/GloblaDrawFunctions.h"
#include "TCtrlCntrConfig.h"
#include "../../RelayTest/Module/SmartTestInterface/MacroTestInterface.h"

#ifdef _use_test_task
#include "TaskMngr/TestTask.h"
#endif

#ifndef _PSX_QT_LINUX_
#include "../../Module/UserDB/XUser.h"
#endif

#include "../../Module/Api/FileApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define g_strTCtrlCntrConfigFile  _T("autotestconfig.xml")
#define g_strErrProcessContinue  _T("continue")
#define g_strErrProcessStop    _T("stop")

const CString CTCtrlCntrConfig::g_strTestControlModeSingle           = _T("single");
const CString CTCtrlCntrConfig::g_strTestControlModeSingleManyReport = _T("single-many-report");

CTCtrlCntrConfig* CTCtrlCntrConfig::g_pTCtrlCntrConfig = NULL;
long CTCtrlCntrConfig::g_nTCtrlCntrConfigRef = 0;

BOOL g_bShowTestWndTop = TRUE;
extern CString g_strTCtrlCntrWorkspacePath;//				= _T("");
extern CString g_strReportFillProgID;

CTCtrlCntrConfig* CTCtrlCntrConfig::Create()
{
	g_nTCtrlCntrConfigRef++;

	if (g_nTCtrlCntrConfigRef == 1)
	{
		CAutoTestXMLRWKeys::Create();
		g_pTCtrlCntrConfig = new CTCtrlCntrConfig();
		g_pTCtrlCntrConfig->Open();
	}

	return g_pTCtrlCntrConfig;
}

void CTCtrlCntrConfig::Release()
{
	g_nTCtrlCntrConfigRef--;

	if (g_nTCtrlCntrConfigRef == 0)
	{
		CAutoTestXMLRWKeys::Release();
		delete g_pTCtrlCntrConfig;
		g_pTCtrlCntrConfig = NULL;
	}
}

CTCtrlCntrConfig::CTCtrlCntrConfig()
{
	//Test
	m_nAutoTestCtrlException = 1;
	m_nWriteTestTempFile = 1;
	m_nFillReport = 1;
	m_strTestTasksViewMode = L"AutoTest";
	//m_nTestTasksViewMode = 0;
	m_strProtocolPath = _T("e-Protocol");

	//WorkSpace
	//m_nAutoLoadWorkspace = 1;

	//Login
	//m_nUserNetToLogin = 0;
	//m_strCfgFile = L"Login.xml";

	//ItemStateColor
	m_crNormal = RGB(0, 0, 0);
	m_crTesting = RGB(0, 255, 0);
	m_crEligible = RGB(168, 168, 168);
	m_crStopped = RGB(255, 255, 0);
	m_crInlegible = RGB(255, 0, 0);
	m_crEligibleEx = RGB(136, 0, 21);
	m_crNotStandard = RGB(0,255, 255);
	m_crProhibit = RGB(192, 192, 192);
	m_crBackgroundInlegible = 7;   //默认纯黄色

	//Report
	m_nHideAllCmdbars = 1;
	m_strReplaceForEmptyCell = L"--";
	m_nDebugWithoutReport = 0;
	m_nDebugWithoutGbTree = 0;
	m_nInsertDataLinkWhenEligible = 1;
	m_nSaveRptToDB = 0;

	m_strErrorProcess = g_strErrProcessContinue;
	m_strErrorSoundFile = _T("");
	m_strFinishSoundFile = _T("");
	m_nShowLevelOneItemsMsg = 0;
	m_nErrPlayMode = 0;
	//m_nUse_dsSetting_TimeTrans = 1;
	m_nOwnDefRepeatTimes = 0;
	m_nCmmMaxRetrytimes = 3;
	m_nCmmRetryDelay = 3000;
	//m_nCanEditScript = 0;

	//m_chSeparateChar     = '=';
	//m_chSeparateEndChar  = ';';
	//m_strSeparateChar     = _T("=");
	//m_strSeparateEndChar  = _T(";");

	//m_nUseRegisterFile = 0;
	m_nMacroTestAppExceptionTDelay = 5;

	m_strTestControlMode = _T("single");
	m_strReportMode      = _T("word");

	m_nRecordDelay = 0;
	m_nAddRecordReport = 0;

	m_nAutoSaveGbDev = 0;
	m_nAutoSaveGbDevTimeLong = 0;

	Set_TestWndMode_ShowAlways();

	m_pDvmTestKeyDataTypes = NULL;

	//m_nScriptRunTimeLong = 0.5;
	//m_nEngineCalTimeLong = 0.2;

	m_nAdjustByTkIDMode = 0;
	m_nStopProtocolParseWhileReadSoe = 0;
	m_nSaveReportGap = 10;
	m_nXdvMgrpSelMode = 0;
	m_nTestSpyWndShow = 0;


	m_nExport_ShowWordApp = 1;
	m_nExport_OriginalDatas   = 0;
	m_nExport_CmbnReport    = 0;
	m_nRWReportFileMode    = 0;
	//m_nUsePowerTestTrans = 0;
	m_nSysRptShowMaxCount = 5;
	m_nExportRptUseUpdateGuideBook = 0;
	m_nIsSingleApp = 1;
	m_nEngineUseCommTestMode = 0;

	m_nViewWordForMrptCount = 4;
	m_nEnableViewWordForMrpt = 1;

	m_strIP_TestApp = _T("192.168.1.133");
	m_strIP_Device = _T("192.168.1.200");
	m_nInlegibleFontBold = 0;
	m_nXdvMgrptExportAuto = 0;

	m_strItemsCountMode = SMARTTEST_ITEM_COUNT_MODE_ALLITEMS;
	m_nUseSttAtsSvr = 0;
	m_nDisableOptrWhenUseAtsSvr = 0;
	m_nShowTestMsgWnd = 1;
}

CTCtrlCntrConfig::~CTCtrlCntrConfig()
{
	if (m_pDvmTestKeyDataTypes != NULL)
	{
		delete m_pDvmTestKeyDataTypes;
		m_pDvmTestKeyDataTypes = NULL;
	}
}

CDataTypes* CTCtrlCntrConfig::GetDvmTestKeyDataTypes()
{
	if (m_pDvmTestKeyDataTypes == NULL)
	{
		m_pDvmTestKeyDataTypes = new CDataTypes();
		CString strFile;
		strFile = _P_GetConfigPath();
		strFile += _T("DvmTestKeyDataTypes.xml");
		m_pDvmTestKeyDataTypes->OpenXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
	}

	return m_pDvmTestKeyDataTypes;
}

long CTCtrlCntrConfig::Open()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	//新疆保信测试系统，也需要用到该文件，此处修改打开、保存文件的路径  shaolei 20220707
	//m_strFile = (CString)_P_GetConfigPath();
	m_strFile = _P_GetInstallPath();
	m_strFile += _T("e-Report\\Config\\");
	m_strFile += g_strTCtrlCntrConfigFile;

	long nRet = OpenXmlFile(m_strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTCtrlCntrKey, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	if (m_strSmartTestMode.GetLength() == 0)
	{//兼容老版本工厂化批量测试
		if (0 < m_strFacBatchTestMngrFile.GetLength() && m_strFacBatchTestMngrFile.GetLength() <= 5)
		{
			m_strFacBatchTestMngrFile = FACTORY_BATCH_TEST_FILE;
			m_strSmartTestMode = SMARTTEST_MODE_FACTORY_BATCH_TEST;
			Save();
		}
	}

	return nRet;
}

long CTCtrlCntrConfig::Save()
{
#ifdef _PSX_QT_LINUX_
    return 1;
#endif

	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);

	//新疆保信测试系统，也需要用到该文件，此处修改打开、保存文件的路径  shaolei 20220707
	//CString strFile = (CString)_P_GetConfigPath();
	CString strFile = _P_GetInstallPath();
	strFile += _T("e-Report\\Config\\");
	strFile += g_strTCtrlCntrConfigFile;
	ClearFileReadOnlyAttr(strFile);
	SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return 1;
}

long CTCtrlCntrConfig::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
//long CTCtrlCntrConfig::XmlRead(CXmlRWNodeBase &oElement,CXmlRWKeys *pXmlRWKeys)
{
	CAutoTestXMLRWKeys* pXmlKeys = (CAutoTestXMLRWKeys*)pXmlRWKeys;
	CString strValue;

	xml_GetElementText(pXmlKeys->m_strAutoTestKey, oElement, m_nAutoTestCtrlException);
	//xml_GetElementText(pXmlKeys->m_strMacroTestEngineKey, oElement, m_strMacroTestEngineProgID);
	xml_GetElementText(pXmlKeys->m_strTestTempFileKey, oElement, m_nWriteTestTempFile);
	xml_GetElementText(pXmlKeys->m_strTestTasksViewMode, oElement, m_strTestTasksViewMode);
	xml_GetElementText(pXmlKeys->m_strProtocolPathKey, oElement, m_strProtocolPath);
	//xml_GetElementText(pXmlKeys->m_strAutoLoadWorkSpaceKey, oElement, m_nAutoLoadWorkspace);
	//xml_GetElementText(pXmlKeys->m_strLastWorkSpaceFile, oElement, m_strLastWorkSpaceFile);
	//xml_GetElementText(pXmlKeys->m_strUseNetToLoginKey, oElement, m_nUserNetToLogin);
	//xml_GetElementText(pXmlKeys->m_strCfgFileKey, oElement, m_strCfgFile);

#ifndef _PSX_IDE_QT_
	xml_GetElementText(pXmlKeys->m_strNormalKey, oElement, strValue);
	m_crNormal = ::GetRGBColor((char*)(_bstr_t)strValue);

	xml_GetElementText(pXmlKeys->m_strTestingKey, oElement, strValue);
	m_crTesting = ::GetRGBColor((char*)(_bstr_t)strValue);

	xml_GetElementText(pXmlKeys->m_strEligibleKey, oElement, strValue);
	m_crEligible = ::GetRGBColor((char*)(_bstr_t)strValue);

	xml_GetElementText(pXmlKeys->m_strStopedKey, oElement, strValue);
	m_crStopped = ::GetRGBColor((char*)(_bstr_t)strValue);

	xml_GetElementText(pXmlKeys->m_strInlegibleKey, oElement, strValue);
	m_crInlegible = ::GetRGBColor((char*)(_bstr_t)strValue);

	xml_GetElementText(pXmlKeys->m_strBackgroundInlegibleKey, oElement, m_strBackgroundInlegible);
	//m_crBackgroundInlegible = ::GetRGBColor((char*)(_bstr_t)strValue);

	xml_GetElementText(pXmlKeys->m_strEligibleExKey, oElement, strValue);
	m_crEligibleEx = ::GetRGBColor((char*)(_bstr_t)strValue);

	xml_GetElementText(pXmlKeys->m_strNotStandardKey, oElement, strValue);
	m_crNotStandard = ::GetRGBColor((char*)(_bstr_t)strValue);

	xml_GetElementText(pXmlKeys->m_strProhibitKey, oElement, strValue);
	m_crProhibit = ::GetRGBColor((char*)(_bstr_t)strValue);
#endif

	xml_GetElementText(pXmlKeys->m_strHideAllCmdbarsKey, oElement, m_nHideAllCmdbars);
	xml_GetElementText(pXmlKeys->m_strReplaceForEmptyCell, oElement, m_strReplaceForEmptyCell);
	xml_GetElementText(pXmlKeys->m_strDebugWithoutReport, oElement, m_nDebugWithoutReport);
	xml_GetElementText(pXmlKeys->m_strInsertDataLinkWhenEligible, oElement, m_nInsertDataLinkWhenEligible);
	xml_GetElementText(pXmlKeys->m_strSaveRptToDB, oElement, m_nSaveRptToDB);

	xml_GetElementText(pXmlKeys->m_strErrorProcessKey, oElement, m_strErrorProcess);
	xml_GetElementText(pXmlKeys->m_strErrorSoundFileKey, oElement, m_strErrorSoundFile);
	xml_GetElementText(pXmlKeys->m_strFinishSoundFileKey, oElement, m_strFinishSoundFile);
	xml_GetElementText(pXmlKeys->m_strShowLevelOneItemsMsgKey, oElement, m_nShowLevelOneItemsMsg);
	xml_GetElementText(pXmlKeys->m_strErrorPlayModeKey, oElement, m_nErrPlayMode);
	//xml_GetElementText(pXmlKeys->m_strUseSettingTimeTransKey, oElement, m_nUse_dsSetting_TimeTrans);
	xml_GetElementText(pXmlKeys->m_strUseOwnDefRepeatTimesKey, oElement, m_nOwnDefRepeatTimes);
	xml_GetElementText(pXmlKeys->m_strRecordProgIDKey, oElement, m_strRecordProgID);
	xml_GetElementText(pXmlKeys->m_strRecordDelayKey, oElement, m_nRecordDelay);
	xml_GetElementText(pXmlKeys->m_strWorkSpacePathKey, oElement, m_strWorkSpacePath);
	xml_GetElementText(pXmlKeys->m_strCmmMaxRetrytimesKey, oElement, m_nCmmMaxRetrytimes);
	xml_GetElementText(pXmlKeys->m_strCmmRetryDelayKey, oElement, m_nCmmRetryDelay);
	xml_GetElementText(pXmlKeys->m_strSkipStxmlWhenWSetsErrorKey, oElement, m_strSkipStxmlWhenWSetsError);
	//xml_GetElementText(pXmlKeys->m_strCanEditScriptKey, oElement, m_nCanEditScript);
	xml_GetElementText(pXmlKeys->m_strAutoSaveReportPathKey, oElement, m_strAutoSaveReportPath);
	//xml_GetElementText(pXmlKeys->m_strSeparateCharKey, oElement, m_strSeparateChar);
	//xml_GetElementText(pXmlKeys->m_strUseRegisterFileKey, oElement, m_nUseRegisterFile);
	xml_GetElementText(pXmlKeys->m_strAppExceptionTDelayKey, oElement, m_nMacroTestAppExceptionTDelay);
	xml_GetElementText(pXmlKeys->m_strAddRecordReportKey, oElement, m_nAddRecordReport);
	xml_GetElementText(pXmlKeys->m_strAutoSaveGbDevKey, oElement, m_nAutoSaveGbDev);
	xml_GetElementText(pXmlKeys->m_strAutoSaveGbDevTimeLongKey, oElement, m_nAutoSaveGbDevTimeLong);
	xml_GetElementText(pXmlKeys->m_strTestWndModeKey, oElement, m_strTestWndMode);

// 	//m_strSeparateChar.Trim();
// 	//m_strSeparateEndChar.Trim();
// 
// 	if (m_strSeparateChar.GetLength() > 0)
// 	{
// 		m_chSeparateChar     = m_strSeparateChar.GetAt(0);
// 	}
// 
// 	if (m_strSeparateEndChar.GetLength() > 0)
// 	{
// 		m_chSeparateEndChar     = m_strSeparateEndChar.GetAt(0);
// 	}

	xml_GetElementText(pXmlKeys->m_strDebugWithoutGbTree, oElement, m_nDebugWithoutGbTree);

	xml_GetElementText(pXmlKeys->m_strClearRptValues, oElement, m_nClearRptValues);
	xml_GetElementText(pXmlKeys->m_strClearRptSOE, oElement, m_nClearRptSOE);
	xml_GetElementText(pXmlKeys->m_strFilterSoeQueryAll, oElement, m_nFilterSoeQueryAll);

	//xml_GetElementText(pXmlKeys->m_strScriptRunTimeLongKey, oElement, m_nScriptRunTimeLong);
	//xml_GetElementText(pXmlKeys->m_strEngineCalTimeLongKey, oElement, m_nEngineCalTimeLong);
	xml_GetElementText(pXmlKeys->m_strAdjustByTkIDModeKey, oElement, m_nAdjustByTkIDMode);
	xml_GetElementText(pXmlKeys->m_strFillReportKey, oElement, m_nFillReport);
	xml_GetElementText(pXmlKeys->m_strStopProtocolParseWhileReadSoeKey, oElement, m_nStopProtocolParseWhileReadSoe);
	xml_GetElementText(pXmlKeys->m_strSaveReportGapKey, oElement, m_nSaveReportGap);
	xml_GetElementText(pXmlKeys->m_strSdvMgrpSelModeKey, oElement, m_nXdvMgrpSelMode);
	xml_GetElementText(pXmlKeys->m_strXdvMgrptExportPathKey, oElement, m_strXdvMgrptExportPath);
	xml_GetElementText(pXmlKeys->m_strXdvMgrptExportUseKey, oElement, m_strXdvMgrptExportUse);
	xml_GetElementText(pXmlKeys->m_strXdvMgrptExportPathWordKey, oElement, m_strXdvMgrptExportPathWord);
	xml_GetElementText(pXmlKeys->m_strXdvMgrptExportPathXmlKey, oElement, m_strXdvMgrptExportPathXml);
	xml_GetElementText(pXmlKeys->m_strXdvMgrptExportPathGbrptKey, oElement, m_strXdvMgrptExportPathGbrpt);
	xml_GetElementText(pXmlKeys->m_strXdvMgrptExportAutoKey, oElement, m_nXdvMgrptExportAuto);
	xml_GetElementText(pXmlKeys->m_strTestSpyWndShowKey, oElement, m_nTestSpyWndShow);

	xml_GetElementText(pXmlKeys->m_strExport_ShowWordApKey, oElement, m_nExport_ShowWordApp);
	xml_GetElementText(pXmlKeys->m_strnExport_OriginalDataKey, oElement, m_nExport_OriginalDatas);
	xml_GetElementText(pXmlKeys->m_strnExport_CmbnReportKey, oElement, m_nExport_CmbnReport);
	xml_GetElementText(pXmlKeys->m_strRWReportFileModeKey, oElement, m_nRWReportFileMode);
	//xml_GetElementText(pXmlKeys->m_strUsePowerTestTrans, oElement, m_nUsePowerTestTrans);
	xml_GetElementText(pXmlKeys->m_strSysRptShowMaxCount, oElement, m_nSysRptShowMaxCount);
	xml_GetElementText(pXmlKeys->m_strExportRptUseUpdateGuideBook, oElement, m_nExportRptUseUpdateGuideBook);
	xml_GetElementText(pXmlKeys->m_strIsSingleApp, oElement, m_nIsSingleApp);
	xml_GetElementText(pXmlKeys->m_strEngineUseCommTestMode, oElement, m_nEngineUseCommTestMode);
	xml_GetElementText(pXmlKeys->m_strFacBatchTestMngrFileKey, oElement, m_strFacBatchTestMngrFile);

	xml_GetElementText(pXmlKeys->m_strReportProgIDKey, oElement, strValue);
	strValue.MakeUpper();
	m_strReportMode = strValue;
	gb_SetReportFillProgID(strValue, m_strReportMode);
	g_strReportFillProgID = m_strReportMode;
        
	xml_GetElementText(pXmlKeys->m_strViewWordForMrptCountKey, oElement, m_nViewWordForMrptCount);
	xml_GetElementText(pXmlKeys->m_strEnableViewWordForMrptKey, oElement, m_nEnableViewWordForMrpt);

	m_strXdvMgrptExportUse.MakeLower();
	xml_GetElementText(pXmlKeys->m_strSmartTestModeKey, oElement, m_strSmartTestMode);

	xml_GetElementText(pXmlKeys->m_strIpTestAppKey, oElement, m_strIP_TestApp);
	xml_GetElementText(pXmlKeys->m_strIpDeviceKey, oElement, m_strIP_Device);

	xml_GetElementText(pXmlKeys->m_strInlegibleFontBoldKey, oElement, m_nInlegibleFontBold);
	xml_GetElementText(pXmlKeys->m_strItemsCountModeKey, oElement, m_strItemsCountMode);
	xml_GetElementText(pXmlKeys->m_strExportDatasSavePathKey, oElement, m_strExportDatasSavePath);
	xml_GetElementText(pXmlKeys->m_strUseSttAtsSvrKey, oElement, m_nUseSttAtsSvr);
	xml_GetElementText(pXmlKeys->m_strSttAtsSvrKey, oElement, m_strSttAtsSvrScene);
	xml_GetElementText(pXmlKeys->m_strRptProgIDKey, oElement, m_strRptProgID);
	xml_GetElementText(pXmlKeys->m_strDisableOptrWhenUseAtsSvrKey, oElement, m_nDisableOptrWhenUseAtsSvr);
	xml_GetElementText(pXmlKeys->m_strShowTestMsgWndKey, oElement, m_nShowTestMsgWnd);
	return 0;
}


CString CTCtrlCntrConfig::GetRGBColorString(COLORREF crColor)
{
	char pszColor[40];
	sprintf(pszColor,"RGB(%d,%d,%d)",crColor & 0x0ff,(crColor >> 8) & 0x0ff
		,(crColor >> 16) & 0x0ff);

	return CString(pszColor);
}

long CTCtrlCntrConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// long CTCtrlCntrConfig::XmlWrite(CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oElement,CXmlRWKeys *pXmlRWKeys)
{

	CAutoTestXMLRWKeys* pXmlKeys = (CAutoTestXMLRWKeys*)pXmlRWKeys;
	CString strValue;

	xml_SetElementText(pXmlKeys->m_strAutoTestKey, oXMLDoc, oElement, m_nAutoTestCtrlException);
	//xml_SetElementText(pXmlKeys->m_strMacroTestEngineKey, oXMLDoc, oElement, m_strMacroTestEngineProgID);
	xml_SetElementText(pXmlKeys->m_strTestTempFileKey, oXMLDoc, oElement, m_nWriteTestTempFile);
	xml_SetElementText(pXmlKeys->m_strFillReportKey, oXMLDoc, oElement, m_nFillReport);
	xml_SetElementText(pXmlKeys->m_strTestTasksViewMode, oXMLDoc, oElement, m_strTestTasksViewMode);
	xml_SetElementText(pXmlKeys->m_strProtocolPathKey, oXMLDoc, oElement, m_strProtocolPath);
	//xml_SetElementText(pXmlKeys->m_strAutoLoadWorkSpaceKey, oXMLDoc, oElement, m_nAutoLoadWorkspace);
	//xml_SetElementText(pXmlKeys->m_strLastWorkSpaceFile, oXMLDoc, oElement, m_strLastWorkSpaceFile);
	//xml_SetElementText(pXmlKeys->m_strUseNetToLoginKey, oXMLDoc, oElement, m_nUserNetToLogin);
	//xml_SetElementText(pXmlKeys->m_strCfgFileKey, oXMLDoc, oElement, m_strCfgFile);

	xml_SetElementText(pXmlKeys->m_strNormalKey, oXMLDoc, oElement, GetRGBColorString(m_crNormal));
	xml_SetElementText(pXmlKeys->m_strTestingKey, oXMLDoc, oElement, GetRGBColorString(m_crTesting));
	xml_SetElementText(pXmlKeys->m_strEligibleKey, oXMLDoc, oElement, GetRGBColorString(m_crEligible));
	xml_SetElementText(pXmlKeys->m_strStopedKey, oXMLDoc, oElement, GetRGBColorString(m_crStopped));
	xml_SetElementText(pXmlKeys->m_strInlegibleKey, oXMLDoc, oElement, GetRGBColorString(m_crInlegible));
	xml_SetElementText(pXmlKeys->m_strBackgroundInlegibleKey, oXMLDoc, oElement, m_strBackgroundInlegible);
	xml_SetElementText(pXmlKeys->m_strNotStandardKey, oXMLDoc, oElement, GetRGBColorString(m_crNotStandard));
	xml_SetElementText(pXmlKeys->m_strProhibitKey, oXMLDoc, oElement, GetRGBColorString(m_crProhibit));
	xml_SetElementText(pXmlKeys->m_strEligibleExKey, oXMLDoc, oElement, GetRGBColorString(m_crEligibleEx));

	xml_SetElementText(pXmlKeys->m_strHideAllCmdbarsKey, oXMLDoc, oElement, m_nHideAllCmdbars);
	xml_SetElementText(pXmlKeys->m_strReplaceForEmptyCell, oXMLDoc, oElement, m_strReplaceForEmptyCell);
	xml_SetElementText(pXmlKeys->m_strDebugWithoutReport, oXMLDoc, oElement, m_nDebugWithoutReport);
	xml_SetElementText(pXmlKeys->m_strDebugWithoutGbTree, oXMLDoc, oElement, m_nDebugWithoutGbTree);
	xml_SetElementText(pXmlKeys->m_strInsertDataLinkWhenEligible, oXMLDoc, oElement, m_nInsertDataLinkWhenEligible);
	xml_SetElementText(pXmlKeys->m_strSaveRptToDB, oXMLDoc, oElement, m_nSaveRptToDB);

	xml_SetElementText(pXmlKeys->m_strErrorProcessKey, oXMLDoc, oElement, m_strErrorProcess);
	xml_SetElementText(pXmlKeys->m_strErrorSoundFileKey, oXMLDoc, oElement, m_strErrorSoundFile);
	xml_SetElementText(pXmlKeys->m_strFinishSoundFileKey, oXMLDoc, oElement, m_strFinishSoundFile);
	xml_SetElementText(pXmlKeys->m_strShowLevelOneItemsMsgKey, oXMLDoc, oElement, m_nShowLevelOneItemsMsg);
	xml_SetElementText(pXmlKeys->m_strErrorPlayModeKey, oXMLDoc, oElement, m_nErrPlayMode);
	//xml_SetElementText(pXmlKeys->m_strUseSettingTimeTransKey, oXMLDoc, oElement, m_nUse_dsSetting_TimeTrans);
	xml_SetElementText(pXmlKeys->m_strUseOwnDefRepeatTimesKey, oXMLDoc, oElement, m_nOwnDefRepeatTimes);
	xml_SetElementText(pXmlKeys->m_strRecordProgIDKey, oXMLDoc, oElement, m_strRecordProgID);
	xml_SetElementText(pXmlKeys->m_strRecordDelayKey, oXMLDoc, oElement, m_nRecordDelay);
	xml_SetElementText(pXmlKeys->m_strWorkSpacePathKey, oXMLDoc, oElement, m_strWorkSpacePath);

	xml_SetElementText(pXmlKeys->m_strCmmMaxRetrytimesKey, oXMLDoc, oElement, m_nCmmMaxRetrytimes);
	xml_SetElementText(pXmlKeys->m_strCmmRetryDelayKey, oXMLDoc, oElement, m_nCmmRetryDelay);
	xml_SetElementText(pXmlKeys->m_strSkipStxmlWhenWSetsErrorKey, oXMLDoc, oElement, m_strSkipStxmlWhenWSetsError);
	//xml_SetElementText(pXmlKeys->m_strCanEditScriptKey, oXMLDoc, oElement, m_nCanEditScript);
	xml_SetElementText(pXmlKeys->m_strAutoSaveReportPathKey, oXMLDoc, oElement, m_strAutoSaveReportPath);
	//xml_SetElementText(pXmlKeys->m_strSeparateCharKey, oXMLDoc, oElement, m_strSeparateChar);
	//xml_SetElementText(pXmlKeys->m_strSeparateEndCharKey, oXMLDoc, oElement, m_strSeparateEndChar);
	//xml_SetElementText(pXmlKeys->m_strUseRegisterFileKey, oXMLDoc, oElement, m_nUseRegisterFile);
	xml_SetElementText(pXmlKeys->m_strAppExceptionTDelayKey, oXMLDoc, oElement, m_nMacroTestAppExceptionTDelay);
	xml_SetElementText(pXmlKeys->m_strAddRecordReportKey, oXMLDoc, oElement, m_nAddRecordReport);
	xml_SetElementText(pXmlKeys->m_strAutoSaveGbDevKey, oXMLDoc, oElement, m_nAutoSaveGbDev);
	xml_SetElementText(pXmlKeys->m_strAutoSaveGbDevTimeLongKey, oXMLDoc, oElement, m_nAutoSaveGbDevTimeLong);
	xml_SetElementText(pXmlKeys->m_strTestWndModeKey, oXMLDoc, oElement, m_strTestWndMode);

	if (m_nAutoSaveGbDevTimeLong < 6)
	{
		m_nAutoSaveGbDevTimeLong = 6;
	}

	//xml_SetElementText(pXmlKeys->m_strScriptRunTimeLongKey, oXMLDoc, oElement, m_nScriptRunTimeLong);
	//xml_SetElementText(pXmlKeys->m_strEngineCalTimeLongKey, oXMLDoc, oElement, m_nEngineCalTimeLong);
	xml_SetElementText(pXmlKeys->m_strAdjustByTkIDModeKey, oXMLDoc, oElement, m_nAdjustByTkIDMode);
	xml_SetElementText(pXmlKeys->m_strStopProtocolParseWhileReadSoeKey, oXMLDoc, oElement, m_nStopProtocolParseWhileReadSoe);
	xml_SetElementText(pXmlKeys->m_strSaveReportGapKey, oXMLDoc, oElement, m_nSaveReportGap);
	xml_SetElementText(pXmlKeys->m_strSdvMgrpSelModeKey, oXMLDoc, oElement, m_nXdvMgrpSelMode);
	xml_SetElementText(pXmlKeys->m_strXdvMgrptExportPathKey, oXMLDoc, oElement, m_strXdvMgrptExportPath);
	xml_SetElementText(pXmlKeys->m_strXdvMgrptExportUseKey, oXMLDoc, oElement, m_strXdvMgrptExportUse);
	xml_SetElementText(pXmlKeys->m_strXdvMgrptExportPathWordKey, oXMLDoc, oElement, m_strXdvMgrptExportPathWord);
	xml_SetElementText(pXmlKeys->m_strXdvMgrptExportPathXmlKey, oXMLDoc, oElement, m_strXdvMgrptExportPathXml);
	xml_SetElementText(pXmlKeys->m_strXdvMgrptExportAutoKey, oXMLDoc, oElement, m_nXdvMgrptExportAuto);
	xml_SetElementText(pXmlKeys->m_strXdvMgrptExportPathGbrptKey, oXMLDoc, oElement, m_strXdvMgrptExportPathGbrpt);
	xml_SetElementText(pXmlKeys->m_strTestSpyWndShowKey, oXMLDoc, oElement, m_nTestSpyWndShow);

	xml_SetElementText(pXmlKeys->m_strExport_ShowWordApKey, oXMLDoc, oElement, m_nExport_ShowWordApp);
	xml_SetElementText(pXmlKeys->m_strnExport_OriginalDataKey, oXMLDoc, oElement, m_nExport_OriginalDatas);
	xml_SetElementText(pXmlKeys->m_strnExport_CmbnReportKey, oXMLDoc, oElement, m_nExport_CmbnReport);
	xml_SetElementText(pXmlKeys->m_strRWReportFileModeKey, oXMLDoc, oElement, m_nRWReportFileMode);
	//xml_SetElementText(pXmlKeys->m_strUsePowerTestTrans, oXMLDoc, oElement, m_nUsePowerTestTrans);
	xml_SetElementText(pXmlKeys->m_strSysRptShowMaxCount, oXMLDoc, oElement, m_nSysRptShowMaxCount);
	xml_SetElementText(pXmlKeys->m_strExportRptUseUpdateGuideBook, oXMLDoc, oElement, m_nExportRptUseUpdateGuideBook);
	xml_SetElementText(pXmlKeys->m_strIsSingleApp, oXMLDoc, oElement, m_nIsSingleApp);
	xml_SetElementText(pXmlKeys->m_strEngineUseCommTestMode, oXMLDoc, oElement, m_nEngineUseCommTestMode);
	xml_SetElementText(pXmlKeys->m_strFacBatchTestMngrFileKey, oXMLDoc, oElement, m_strFacBatchTestMngrFile);
	xml_SetElementText(pXmlKeys->m_strReportProgIDKey, oXMLDoc, oElement, m_strReportMode);
	xml_SetElementText(pXmlKeys->m_strViewWordForMrptCountKey, oXMLDoc, oElement, m_nViewWordForMrptCount);
	xml_SetElementText(pXmlKeys->m_strEnableViewWordForMrptKey, oXMLDoc, oElement, m_nEnableViewWordForMrpt);
	xml_SetElementText(pXmlKeys->m_strSmartTestModeKey, oXMLDoc, oElement, m_strSmartTestMode);

	xml_SetElementText(pXmlKeys->m_strIpTestAppKey, oXMLDoc, oElement, m_strIP_TestApp);
	xml_SetElementText(pXmlKeys->m_strIpDeviceKey, oXMLDoc, oElement, m_strIP_Device);
	xml_SetElementText(pXmlKeys->m_strInlegibleFontBoldKey, oXMLDoc, oElement, m_nInlegibleFontBold);
	xml_SetElementText(pXmlKeys->m_strItemsCountModeKey, oXMLDoc, oElement, m_strItemsCountMode);
	xml_SetElementText(pXmlKeys->m_strExportDatasSavePathKey, oXMLDoc, oElement, m_strExportDatasSavePath);
	xml_SetElementText(pXmlKeys->m_strUseSttAtsSvrKey, oXMLDoc, oElement, m_nUseSttAtsSvr);
	xml_SetElementText(pXmlKeys->m_strSttAtsSvrKey, oXMLDoc, oElement, m_strSttAtsSvrScene);
	xml_SetElementText(pXmlKeys->m_strRptProgIDKey, oXMLDoc, oElement, m_strRptProgID);
	xml_SetElementText(pXmlKeys->m_strDisableOptrWhenUseAtsSvrKey, oXMLDoc, oElement, m_nDisableOptrWhenUseAtsSvr);
	xml_SetElementText(pXmlKeys->m_strShowTestMsgWndKey, oXMLDoc, oElement, m_nShowTestMsgWnd);

	return 0;
}

/*
enum WdColorIndex
{
	wdAuto = 0,
	wdBlack = 1,
	wdBlue = 2,
	wdTurquoise = 3,
	wdBrightGreen = 4,
	wdPink = 5,
	wdRed = 6,
	wdYellow = 7,
	wdWhite = 8,
	wdDarkBlue = 9,
	wdTeal = 10,
	wdGreen = 11,
	wdViolet = 12,
	wdDarkRed = 13,
	wdDarkYellow = 14,
	wdGray50 = 15,
	wdGray25 = 16,
	wdByAuthor = -1,
	wdNoHighlight = 0
};
*/

void CTCtrlCntrConfig::InitAfterRead()
{
	m_strBackgroundInlegible.MakeUpper();

	if (m_strBackgroundInlegible == _T("RGB(0,0,0)"))
	{
		m_crBackgroundInlegible = 1;  //纯黑
	}
	else  if (m_strBackgroundInlegible == _T("RGB(0,0,255)"))
	{
		m_crBackgroundInlegible = 2;  //纯蓝
	}
	else if (m_strBackgroundInlegible == _T("RGB(255,0,0)"))
	{
		m_crBackgroundInlegible = 6;  //纯红
	}
	else if (m_strBackgroundInlegible == _T("RGB(255,255,0)"))
	{
		m_crBackgroundInlegible = 7;  //纯黄
	}
	else if (m_strBackgroundInlegible == _T("RGB(255,255,255)"))
	{
		m_crBackgroundInlegible = 0;  //纯白
	}
	else
		m_crBackgroundInlegible = 0;
}

BOOL CTCtrlCntrConfig::IsErrorProcessContinue()
{
	if (m_strErrorProcess == g_strErrProcessContinue)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CTCtrlCntrConfig::IsErrorProcessStop()
{
	if (m_strErrorProcess == g_strErrProcessStop)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
long CTCtrlCntrConfig::GetErrorProcessStop()
{
	if (IsErrorProcessContinue())	
		return 0;
	else
		return 1;
}


void CTCtrlCntrConfig::SetErrorProcess(long nProcess)
{
	if (nProcess == AUTOTEST_ERR_PROCESS_CONTINUE)
	{
		m_strErrorProcess = g_strErrProcessContinue;
	}
	else
	{
		m_strErrorProcess = g_strErrProcessStop;
	}
}

BOOL CTCtrlCntrConfig::HasRecorder()
{
	return (m_strRecordProgID.GetLength() > 3);
}

void CTCtrlCntrConfig::SetRecorderProgID(const CString &strProgID)
{
	m_strRecordProgID = strProgID;
}

// CString CTCtrlCntrConfig::GetMacroTestEngineProgID()
// {
// 	if (m_strMacroTestEngineProgID.GetLength() < 3)
// 	{
// 		m_strMacroTestEngineProgID = _T("OnlyCtrl.DeviceCtrlApp");
// 	}
// 
// 	return m_strMacroTestEngineProgID;
// }


CString CTCtrlCntrConfig::GetWorkSpacePath()
{
	CString strWorkSpacePath;

#ifdef _use_UserDB
	ASSERT (g_pTCtrlCntrConfig != NULL);
	CXUser *pCurrUser = CUserDBConstGlobal::GetCurrUser();
	ASSERT (pCurrUser != NULL);

	CString strUser;

	if (!pCurrUser->IsAdmin())
	{
		strUser = pCurrUser->GetID();
	}
// 	if (g_pTCtrlCntrConfig == NULL)
// 	{
// 		CString strWorkspace;
// 		strWorkspace = _P_GetWorkspacePath();
// 		return strWorkspace;
// 	}

	strWorkSpacePath = g_pTCtrlCntrConfig->m_strWorkSpacePath;

	if (IsFileExist(strWorkSpacePath))
	{

	}
	else
	{
		strWorkSpacePath = _P_GetWorkspacePath(strUser);
	}

	//创建路径
	CreateAllDirectories(strWorkSpacePath);

#else
	strWorkSpacePath = g_pTCtrlCntrConfig->m_strWorkSpacePath;
#endif

	if (!IsFileExist(strWorkSpacePath))
	{
		strWorkSpacePath = g_strTCtrlCntrWorkspacePath;
	}

	return strWorkSpacePath;
}


BOOL CTCtrlCntrConfig::IsTestControlModeSingle()
{
	return (m_strTestControlMode == g_strTestControlModeSingle);
}

BOOL CTCtrlCntrConfig::IsTestControlModeSingleManyReport()
{
	return (m_strTestControlMode == g_strTestControlModeSingleManyReport);
}

BOOL CTCtrlCntrConfig::IsReportControlWord()
{
	return (m_strReportMode == REPORTFILL_PROGID_WORD);
}

BOOL CTCtrlCntrConfig::IsReportControlWPS()
{
	return (m_strReportMode == REPORTFILL_PROGID_WPS);
}

BOOL CTCtrlCntrConfig::IsReportControlSystem()
{
	return (m_strReportMode == REPORTFILL_PROGID_SYSTEM);
}
#define REPORTFILL_INDEX_SYSTEM		0
#define REPORTFILL_INDEX_WORD		1
#define REPORTFILL_INDEX_WPS		2
#define REPORTFILL_INDEX_NONE		3

long CTCtrlCntrConfig::GetReportControl()
{
	if (IsReportControlWord())
	{
		return REPORTFILL_INDEX_WORD;
	}

	if (IsReportControlWPS())
	{
		return REPORTFILL_INDEX_WPS;
	}

	if (IsReportControlSystem())
	{
		return REPORTFILL_INDEX_SYSTEM;
	}

	return REPORTFILL_INDEX_NONE;
}

void CTCtrlCntrConfig::SetTestControlModeSingle()
{
	m_strTestControlMode = g_strTestControlModeSingle;
}

void CTCtrlCntrConfig::SetTestControlModeSingleManyReport()
{
	m_strTestControlMode = g_strTestControlModeSingleManyReport;
}

void CTCtrlCntrConfig::SetReportControlWord()
{
	m_strReportMode = REPORTFILL_PROGID_WORD;
}

void CTCtrlCntrConfig::SetReportControlWPS()
{
	m_strReportMode = REPORTFILL_PROGID_WPS;
}

void CTCtrlCntrConfig::SetReportControlSystem()
{
	m_strReportMode = REPORTFILL_PROGID_SYSTEM;
}

//TestWndMode
#define TestWndMode_ShowAlways        _T("show-alwyas")
#define TestWndMode_HideWhenMinize   _T("hide-minimize")

void CTCtrlCntrConfig::Set_TestWndMode_ShowAlways()
{
	m_strTestWndMode = TestWndMode_ShowAlways;
}

void CTCtrlCntrConfig::Set_TestWndMode_HideWhenMinize()
{
	m_strTestWndMode = TestWndMode_HideWhenMinize;
}

BOOL CTCtrlCntrConfig::Is_TestWndMode_ShowAlways()
{
	return (m_strTestWndMode == TestWndMode_ShowAlways);
}

BOOL CTCtrlCntrConfig::Is_TestWndMode_HideWhenMinize()
{
	return (m_strTestWndMode == TestWndMode_HideWhenMinize);
}


long CTCtrlCntrConfig::GetClearRptValues()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nClearRptValues;
}

long CTCtrlCntrConfig::GetClearRptSOE()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nClearRptSOE;
}

long CTCtrlCntrConfig::GetFilterSoeQueryAll()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nFilterSoeQueryAll;
}

void CTCtrlCntrConfig::SetClearRptValues(long nVal)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nClearRptValues = nVal;
}

void CTCtrlCntrConfig::SetClearRptSOE(long nVal)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nClearRptSOE = nVal;
}

void CTCtrlCntrConfig::SetFilterSoeQueryAll(long nVal)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nFilterSoeQueryAll = nVal;
}

// long CTCtrlCntrConfig::GetScriptRunTimeLong()
// {
// 	ASSERT( g_pTCtrlCntrConfig != NULL);
// 	return g_pTCtrlCntrConfig->m_nScriptRunTimeLong;
// }
// 
// long CTCtrlCntrConfig::GetEngineCalTimeLong()
// {
// 	ASSERT( g_pTCtrlCntrConfig != NULL);
// 	return g_pTCtrlCntrConfig->m_nEngineCalTimeLong;
// }

BOOL CTCtrlCntrConfig::IsAdjustByTkIDMode_Select()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return (g_pTCtrlCntrConfig->m_nAdjustByTkIDMode == 1);
}

BOOL CTCtrlCntrConfig::IsAdjustByTkIDMode_Show()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return (g_pTCtrlCntrConfig->m_nAdjustByTkIDMode == 2);
}

BOOL CTCtrlCntrConfig::IsAdjustByTkIDMode_Enable()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return (g_pTCtrlCntrConfig->m_nAdjustByTkIDMode == 3);
}

BOOL CTCtrlCntrConfig::IsAdjustByTkIDMode_Delete()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return (g_pTCtrlCntrConfig->m_nAdjustByTkIDMode == 0);
}

BOOL CTCtrlCntrConfig::IsStopProtocolParseWhileReadSoe()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return (g_pTCtrlCntrConfig->m_nStopProtocolParseWhileReadSoe == 1);
}


long CTCtrlCntrConfig::GetSaveReportGap()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nSaveReportGap;
}

long CTCtrlCntrConfig::GetXdvMgrpSelMode()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nXdvMgrpSelMode;
}

void CTCtrlCntrConfig::SetSdvMgrpSelMode(long nSelMode)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nXdvMgrpSelMode = nSelMode;
	g_pTCtrlCntrConfig->Save();
}

long CTCtrlCntrConfig::GetTestSpyWndShow()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nTestSpyWndShow;
}

BOOL CTCtrlCntrConfig::IsShowTestSpyWnd()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return (g_pTCtrlCntrConfig->m_nTestSpyWndShow != 0);
}

void CTCtrlCntrConfig::SetTestSpyWndShow(long nShow)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nTestSpyWndShow = nShow;
	g_pTCtrlCntrConfig->Save();
}

CString CTCtrlCntrConfig::GetXdvMgrptExportPath()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_strXdvMgrptExportPath;
}

BOOL   CTCtrlCntrConfig::GetXdvMgrptExportUse_XML()
{
	return g_pTCtrlCntrConfig->m_strXdvMgrptExportUse.Find("xml") >= 0;
}

BOOL   CTCtrlCntrConfig::GetXdvMgrptExportUse_GBRPT()
{
	return g_pTCtrlCntrConfig->m_strXdvMgrptExportUse.Find("gbrpt") >= 0;
}

CString CTCtrlCntrConfig::GetXdvMgrptExportPathWord()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_strXdvMgrptExportPathWord;
}

CString CTCtrlCntrConfig::GetXdvMgrptExportPathXml()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_strXdvMgrptExportPathXml;
}

CString CTCtrlCntrConfig::GetXdvMgrptExportPathGbrpt()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_strXdvMgrptExportPathGbrpt;
}

void CTCtrlCntrConfig::SetXdvMgrptExportPath(const CString &strPath)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_strXdvMgrptExportPath = strPath;
	g_pTCtrlCntrConfig->Save();
}

void CTCtrlCntrConfig::SetXdvMgrptExportUse(const CString &strUse)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_strXdvMgrptExportUse = strUse;
	g_pTCtrlCntrConfig->Save();
}

void CTCtrlCntrConfig::SetXdvMgrptExportPathWord(const CString &strPath)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_strXdvMgrptExportPathWord = strPath;
	g_pTCtrlCntrConfig->Save();
}

void CTCtrlCntrConfig::SetXdvMgrptExportPathXml(const CString &strPath)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_strXdvMgrptExportPathXml = strPath;
	g_pTCtrlCntrConfig->Save();
}

void CTCtrlCntrConfig::SetXdvMgrptExportPathGbrpt(const CString &strPath)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_strXdvMgrptExportPathGbrpt = strPath;
	g_pTCtrlCntrConfig->Save();
}

long CTCtrlCntrConfig::Get_Export_ShowWordApp()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nExport_ShowWordApp;
}

long CTCtrlCntrConfig::Getm_Export_OriginalDatas()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nExport_OriginalDatas;
}

long CTCtrlCntrConfig::Get_Export_CmbnReport()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nExport_CmbnReport;
}

long CTCtrlCntrConfig::Get_RWReportFileMode()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nRWReportFileMode;
}

void CTCtrlCntrConfig::Set_Export_ShowWordApp(long nVal)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nExport_ShowWordApp = nVal;
	g_pTCtrlCntrConfig->Save();
}

void CTCtrlCntrConfig::Setm_Export_OriginalDatas(long nVal)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nExport_OriginalDatas = nVal;
	g_pTCtrlCntrConfig->Save();
}

void CTCtrlCntrConfig::Set_Export_CmbnReport(long nVal)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nExport_CmbnReport = nVal;
	g_pTCtrlCntrConfig->Save();
}


void CTCtrlCntrConfig::Set_RWReportFileMode(long nVal)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nRWReportFileMode = nVal;
	g_pTCtrlCntrConfig->Save();
}

// BOOL CTCtrlCntrConfig::Is_UsePowerTestTrans()
// {
// 	ASSERT( g_pTCtrlCntrConfig != NULL);
// 	return g_pTCtrlCntrConfig->m_nUse_dsSetting_TimeTrans;
// }

long CTCtrlCntrConfig::GetSysRptShowMaxCount()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nSysRptShowMaxCount;
}

long CTCtrlCntrConfig::Get_ExportRptUseUpdateGuideBook()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nExportRptUseUpdateGuideBook;
}

void CTCtrlCntrConfig::Set_ExportRptUseUpdateGuideBook(long nVal)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nExportRptUseUpdateGuideBook = nVal;
	g_pTCtrlCntrConfig->Save();
}

CString CTCtrlCntrConfig::GetReportMode()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_strReportMode;
}

void CTCtrlCntrConfig::SetEnableViewWordForMrpt()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	
	if (g_pTCtrlCntrConfig->m_nEnableViewWordForMrpt == 0)
	{
		g_pTCtrlCntrConfig->m_nEnableViewWordForMrpt = 1;
	}
	else
	{
		g_pTCtrlCntrConfig->m_nEnableViewWordForMrpt = 0;
	}

	g_pTCtrlCntrConfig->Save();
}

BOOL CTCtrlCntrConfig::IsEnableViewWordForMrpt()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);

	return (g_pTCtrlCntrConfig->m_nEnableViewWordForMrpt == 1);
}

BOOL CTCtrlCntrConfig::CanViewWordForMrpt(long nMrpt)
{
	if (g_pTCtrlCntrConfig->m_nEnableViewWordForMrpt == 0)
	{
		return FALSE;
	}

	if (nMrpt > g_pTCtrlCntrConfig->m_nViewWordForMrptCount)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTCtrlCntrConfig::SetRptViewByMrpt(long nMrpt)
{
	if (!CanViewWordForMrpt(nMrpt))
	{
		return FALSE;
	}

	g_strReportFillProgID = g_pTCtrlCntrConfig->m_strReportMode;

	return TRUE;
}

long CTCtrlCntrConfig::Get_IsSingleApp()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nIsSingleApp;
}

void CTCtrlCntrConfig::Set_IsSingleApp(long nVal)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nIsSingleApp = nVal;
	g_pTCtrlCntrConfig->Save();
}

long CTCtrlCntrConfig::Get_EngineUseCommTestMode()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nEngineUseCommTestMode;
}

void CTCtrlCntrConfig::Set_EngineUseCommTestMode(long nVal)
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	g_pTCtrlCntrConfig->m_nEngineUseCommTestMode = nVal;
	g_pTCtrlCntrConfig->Save();
}

COLORREF CTCtrlCntrConfig::GetColor_Inlegible()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_crInlegible;
}

COLORREF CTCtrlCntrConfig::GetColor_Inlegible_Background()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_crBackgroundInlegible;
}

COLORREF CTCtrlCntrConfig::GetColor_Eligible()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_crEligible;
}

long CTCtrlCntrConfig::Get_InlegibleFontBold()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);
	return g_pTCtrlCntrConfig->m_nInlegibleFontBold;
}


BOOL CTCtrlCntrConfig::IsFacBatchTestMode()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);

	if (g_pTCtrlCntrConfig == NULL)
	{
		return FALSE;
	}
// 	if (g_pTCtrlCntrConfig->m_strFacBatchTestMngrFile.GetLength() > 0)
// 	{
// 		return TRUE;
// 	}

	if (g_pTCtrlCntrConfig->m_strSmartTestMode.CompareNoCase(SMARTTEST_MODE_FACTORY_BATCH_TEST) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CTCtrlCntrConfig::IsNormalTestMode()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);

	if (g_pTCtrlCntrConfig->m_strSmartTestMode.CompareNoCase(SMARTTEST_MODE_NORMAL_TEST) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CTCtrlCntrConfig::IsSimpleTestMode()
{
	ASSERT( g_pTCtrlCntrConfig != NULL);

	if (g_pTCtrlCntrConfig->m_strSmartTestMode.CompareNoCase(SMARTTEST_MODE_SIMPLE_TEST) == 0)
	{
		return TRUE;
	}

	return FALSE;
}


void CTCtrlCntrConfig::SetIP_TestApp(const CString &strIP)
{
	g_pTCtrlCntrConfig->m_strIP_TestApp = strIP;

	g_pTCtrlCntrConfig->Save();
}

void CTCtrlCntrConfig::SetIP_Device(const CString &strIP)
{
	g_pTCtrlCntrConfig->m_strIP_Device = strIP;

	g_pTCtrlCntrConfig->Save();
}

void  CTCtrlCntrConfig::SetIP(const CString &strIP_TestApp, const CString &strIP_Device)
{
	g_pTCtrlCntrConfig->m_strIP_TestApp = strIP_TestApp;
	g_pTCtrlCntrConfig->m_strIP_Device = strIP_Device;

	g_pTCtrlCntrConfig->Save();
}


void CTCtrlCntrConfig::GetIP_TestApp(CDvmDataset *pDataset)
{
#ifndef GUIDEBOOK_DEV_MODE
	mt_GetIP_ConfigString(pDataset, g_pTCtrlCntrConfig->m_strIP_TestApp);
#endif
}

void CTCtrlCntrConfig::GetIP_Device(CDvmDataset *pDataset)
{
#ifndef GUIDEBOOK_DEV_MODE
	mt_GetIP_ConfigString(pDataset, g_pTCtrlCntrConfig->m_strIP_Device);
#endif
}

//2021-1-8  lijunqing
void CTCtrlCntrConfig::GetIP_TestApp(CString &strXml)
{
#ifndef GUIDEBOOK_DEV_MODE
	mt_GetIP_ConfigString(g_pTCtrlCntrConfig->m_strIP_TestApp, strXml);
#endif
}

void CTCtrlCntrConfig::GetIP_Device(CString &strXml)
{
#ifndef GUIDEBOOK_DEV_MODE
	mt_GetIP_ConfigString(g_pTCtrlCntrConfig->m_strIP_Device, strXml);
#endif
}

long CTCtrlCntrConfig::GetShowTestMsgWnd()
{
	return g_pTCtrlCntrConfig->m_nShowTestMsgWnd;
}

void CTCtrlCntrConfig::SetShowTestMsgWnd(long nVal)
{
	g_pTCtrlCntrConfig->m_nShowTestMsgWnd = nVal;
}


