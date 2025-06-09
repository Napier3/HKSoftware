#include "StdAfx.h"
#include "GbScriptFunctions.h"
#include "GbScript_System.h"
#include "GbScript_Engine.h"
#include "GbScript_GuideBook.h"

//Lua
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luabind.hpp"
#include "..\XLanguageResourceAts.h"

lua_State* g_pGuideBookLua = NULL;
char g_pLuaReturnString[MAX_PATH];

void Gb_RegisterFunctions()
{
	luabind::module( g_pGuideBookLua ) 
		[ 
			luabind::def("SetShow", &GBS_SetItemShow ),
			luabind::def("GetShow", &GBS_GetItemShow ), 
			luabind::def("SetEnable", &GBS_SetItemEnable),
			luabind::def("GetEnable", &GBS_GetItemEnable),
			luabind::def("SetSelect", &GBS_SetItemSelect),
			luabind::def("GetSelect", &GBS_GetItemSelect),
			luabind::def("SetName", &GBS_SetItemName),
			luabind::def("GetName", &GBS_GetItemName),
			luabind::def("SetRsltJdg", &GBS_SetItemResultJudge),
			luabind::def("GetRsltJdg", &GBS_GetItemResultJudge),
			luabind::def("SetPara", &GBS_SetItemParaValue),
			luabind::def("SetParaStr", &GBS_SetItemParaValueStr),
			luabind::def("GetPara", &GBS_GetItemParaValue),
			luabind::def("GetParaStr", &GBS_GetItemParaString),
			luabind::def("AddRptMapData", &GBS_AddRptMapData),
			luabind::def("SetReportValue", &GBS_SetItemReportValue),
			luabind::def("SetReportValStr", &GBS_SetItemReportValueString),
			luabind::def("GetReportValue", &GBS_GetItemReportValue),
			luabind::def("GetRptValL", &GBS_GetItemReportValueLong),
			luabind::def("GetRptValStr", &GBS_GetItemReportValueString),
			luabind::def("GotoItem", &GBS_GotoItem ),
			luabind::def("GotoItemEx", &GBS_GotoItemEx ),
			luabind::def("MtExcuteCmd", &GBS_MtExcuteCmd),
			luabind::def("MtRegistPpDataMsg", &GBS_MtRegistPpDataMsg),
			luabind::def("MtUnRegistPpDataMsg", &GBS_MtUnRegistPpDataMsg),
			luabind::def("MtRegistCmdMsg", &GBS_MtRegistCmdMsg),
			luabind::def("MtUnRegistCmdMsg", &GBS_MtUnRegistCmdMsg),
			luabind::def("BreakLoop", &GBS_BreakLoop ),
			luabind::def("BreakItems", &GBS_BreakItems ),

			luabind::def("GetReportValueEx", &GBS_GetItemReportValueEx),
			luabind::def("GetRptValLEx", &GBS_GetItemReportValueLongEx),
			luabind::def("GetRptValStrEx", &GBS_GetItemReportValueStringEx),
			luabind::def("GetRptCount", &GBS_GetItemReportCount),
			luabind::def("ClearReports", &GBS_ClearReports),

			luabind::def("SetUploadRptFile", &GBS_SetUploadRptFile ),
			luabind::def("GetDsDataValue", &GBS_GetDsDataValue ), 
			luabind::def("SetDsDataValue", &GBS_SetDsDataValue),
			luabind::def("GetDsDataStr", &GBS_GetDsDataValueStr ), 
			luabind::def("SetDsDataStr", &GBS_SetDsDataValueStr),
			luabind::def("GetDsDataValueEx", &GBS_GetDsDataValueEx ), 
			luabind::def("GetDsDataAttr", &GBS_GetDsDataAttr ), 
			luabind::def("SetDsDataValueEx", &GBS_SetDsDataValueEx),
			luabind::def("GetDsDataStrEx", &GBS_GetDsDataValueStrEx ), 
			luabind::def("SetDsDataStrEx", &GBS_SetDsDataValueStrEx),
			luabind::def("CalAinError", &GBS_CalAinError),
			luabind::def("CalAinErrorNom", &GBS_CalAinErrorNom),
			luabind::def("CalAinErrorEx", &GBS_CalAinErrorEx),
			luabind::def("CalAinError2", &GBS_CalAinError2),
			luabind::def("CalAinStdError", &GBS_CalAinStdError),
			luabind::def("CalAinStdError2", &GBS_CalAinStdError2),
			luabind::def("CalVariation", &GBS_CalVariation),
			luabind::def("CalVariationErr", &GBS_CalVariationErr),
			luabind::def("CalVariationErrEx", &GBS_CalVariationErrEx),
			luabind::def("FltCalErrMax", &GBS_FlterCalErrorMax),
			luabind::def("FltCalErrMin", &GBS_FlterCalErrorMin),
// 			luabind::def("GetSetValue", &GBS_GetSetValue ), 
// 			luabind::def("SetSetValue", &GBS_SetSetValue),
// 			luabind::def("GetSysPara", &GBS_GetSysParaValue),
// 			luabind::def("GetSftValue", &GBS_GetSoftswitchValue ), 
// 			luabind::def("SetSftValue", &GBS_SetSoftswitchValue),
// 			luabind::def("SetSysPara", &GBS_SetSysParaValue),
			luabind::def("GetTestPara", &GBS_GetTestParaValue),
			luabind::def("GetTestParaStr", &GBS_GetTestParaStr),
			luabind::def("SetTestPara", &GBS_SetTestParaValue),
			luabind::def("SetTestParaStr", &GBS_SetTestParaStr),
			luabind::def("ShowMsg", &GBS_ShowMessage),
			//luabind::def("PlayMusicFile", &GBS_PlayMusicFile),
			luabind::def("GetTime", &GBS_GetTime),
			luabind::def("GetRptExVal", &GBS_GetItemReportExValue),
			luabind::def("GetRptExValD", &GBS_GetItemReportExValue_D),
			luabind::def("GetRptExValL", &GBS_GetItemReportExValue_L),
			luabind::def("GetRptExValS", &GBS_GetItemReportExValue_S),
			luabind::def("GetRptExCount", &GBS_GetItemReportExCount),
			luabind::def("GetRptExCountByID", &GBS_GetItemReportExDataCountByID),
			luabind::def("GetRptExIndexByIDIndex", &GBS_GetItemReportDataIndexByIDIndex),
			luabind::def("GetFileInReportEx", &GBS_GetFileInReportEx),
			luabind::def("GetFileNumInReportEx", &GBS_GetFileNumInReportEx),
			luabind::def("CalTmGapStr", &GBS_CalTimeGapStr),
			luabind::def("CalTmGapStr_us", &GBS_CalTimeGapStr_us),
			luabind::def("CalTmGap", &GBS_CalItemReportTimeGap),
			luabind::def("CalTmGapEx", &GBS_CalItemReportTimeGapEx),
			luabind::def("CalTmGapEx2", &GBS_CalItemReportTimeGapEx2),
			luabind::def("GetTestIndex", &GBS_GetTestIndex),

			luabind::def("CalRptValMax", &GBS_CalRptValMax),
			luabind::def("CalRptValMin", &GBS_CalRptValMin),
			luabind::def("CalRptValAvg", &GBS_CalRptValAvg),

			luabind::def("FilterRptInit", &GBS_FilterInit),
			luabind::def("FilterRptExEqL", &GBS_FilterReportExEqualValueL),
			luabind::def("FilterRptExEqStr", &GBS_FilterReportExEqualValueStr),
			luabind::def("FilterRptExHasStr", &GBS_FilterReportExHasValueStr),
			luabind::def("FilterRptExNoStr", &GBS_FilterReportExHasNoValueStr),
			luabind::def("FilterCombine", &GBS_FilterCombineReportEx),
		
			luabind::def("FltRptExQuery", &GBS_FilterRptExQuery),
			luabind::def("FltRptExGetCount", &GBS_FilterRptExGetCount),
			luabind::def("FltRptExGetLong", &GBS_FilterRptExGetLong),
			luabind::def("FltRptExGetStr", &GBS_FilterRptExGetString),
			luabind::def("FltRptExGetDouble", &GBS_FilterRptExGetDouble),
			luabind::def("FltRptExGetValCount", &GBS_FilterRptExGetValCount),
			luabind::def("FltRptExGetValLong", &GBS_FilterRptExGetValLong),
			luabind::def("FltRptExGetValStr", &GBS_FilterRptExGetValString),
			luabind::def("FltRptExGetValDouble", &GBS_FilterRptExGetValDouble),
			luabind::def("FltRptExCalValError", &GBS_FilterRptExCalValError),
			luabind::def("FltRptExCalValErrEx", &GBS_FilterRptExCalValErrorEx),

			luabind::def("CreateDevice", &GBS_PpCreateDevice),
			luabind::def("ReleaseDevice", &GBS_PpReleaseDevice),

			luabind::def("GetDeviceAttr", &GBS_PpGetDeviceAttr),
			luabind::def("GetDeviceAttrL", &GBS_PpGetDeviceAttrL),
			luabind::def("GetDeviceAttrStr", &GBS_PpGetDeviceAttrStr),
			luabind::def("SetDeviceAttrL", &GBS_PpSetDeviceAttrL),
			luabind::def("SetDeviceAttrStr", &GBS_PpSetDeviceAttrStr),
			luabind::def("RptGetDevieNodeDatas", &GBS_PpRptGetDevieNodeDatas),
			luabind::def("RptGetDeviceAttrs", &GBS_PpRptGetDeviceAttrs),
			luabind::def("GetDevieNodeDataAttr", &GBS_PpGetDevieNodeDataAttr),
			luabind::def("SetDevieNodeDataAttr", &GBS_PpSetDevieNodeDataAttr),
			luabind::def("DeleteAllNodeData", &GBS_PpDeleteAllNodeData),
			luabind::def("IsProtocol", &GBS_IsProtocol),

// 			luabind::def("RecordPkg", &GBS_RecordPackage),
// 			luabind::def("UnRecordPkg", &GBS_UnRecordPackage),
// 			luabind::def("GetPckgPcTm", &GBS_GetPackagePcTime),
// 			luabind::def("GetGpsPcTmMap", &GBS_GetGpsPcTimeMap),
// 			luabind::def("GetOutGpsTm", &GBS_GetOutGpsTime),
// 			luabind::def("CalGpsPcTmGap", &GBS_CalGpsPcTimeGap),
// 			luabind::def("RdMacroTest", &GBS_ReadMacroTestResult),
// 			luabind::def("CrtGpsDtTm", &GBS_CreateGpsDateTime),
// 			luabind::def("CrtGpsTm", &GBS_CreateGpsTime),
// 			luabind::def("LGetRptDatas", &GBS_LGetItemReportDataCount),
// 			luabind::def("DownMacroPara", &GBS_DownloadMacroTestPara),

			luabind::def("SelectItem", &GBS_SSelectItem),
			luabind::def("GtItmRptCnt", &GBS_SGetItemReportCount),
			luabind::def("SelItemRpt", &GBS_SSelectItemReport),
			luabind::def("GtItmRptVal", &GBS_SGetItemReportValue),
			luabind::def("GtItmRptValL", &GBS_SGetItemReportValueLong),
			luabind::def("GtItmRptValS", &GBS_SGetItemReportValueString),
			luabind::def("GtItmRptVCnt", &GBS_SGetItemReportValueCount),
			luabind::def("GtItmRptVal2", &GBS_SGetItemReportValue2),
			luabind::def("GtItmRptValL2", &GBS_SGetItemReportValueLong2),
			luabind::def("GtItmRptValS2", &GBS_SGetItemReportValueString2),
			luabind::def("GtItmRptDCnt", &GBS_SGetItemReportExDataCount),
			luabind::def("GtItmRptDVal", &GBS_SGetItemReportExDataValue),
			luabind::def("GtItmRptDValL", &GBS_SGetItemReportExDataValueLong),
			luabind::def("GtItmRptDValS", &GBS_SGetItemReportExDataValueString),
			luabind::def("CmpDouble", &GBS_CmpDouble),
			luabind::def("CalRelErr", &GBS_CalRelError),
			luabind::def("CalIEC", &GBS_IEC),
			luabind::def("CalIEEE", &GBS_IEEE),
			luabind::def("CalIAC", &GBS_IAC),
			luabind::def("CalI2T", &GBS_I2T),
			luabind::def("RunExe", &GBS_RunExe),
			luabind::def("ExitExe", &GBS_ExitExe),
			luabind::def("CalTimeGap", &GBS_CalTimeGap),
			luabind::def("CalTimeGapCurr", &GBS_CalTimeGapCurr),
			luabind::def("AddLocalTime", &GBS_AddLocalTime),
			luabind::def("SubLocalTime", &GBS_SubLocalTime),

			luabind::def("RandLong", &GBS_RandLong),
			luabind::def("RandFloat", &GBS_RandFloat),
			luabind::def("RandDouble", &GBS_RandDouble),
			luabind::def("RandSeed", &GBS_RandSeed),

			luabind::def("RptExDsGetCount", &GBS_RptExDsGetCount),
			luabind::def("RptExDsGetValueD", &GBS_RptExDsGetValueD),
			luabind::def("RptExDsGetValueL", &GBS_RptExDsGetValueL),
			luabind::def("RptExDsGetValueStr", &GBS_RptExDsGetValueStr),

			luabind::def("DsvClear", &GBS_RptExDsValidClear),
			luabind::def("DsvAddElement", &GBS_RptExDsValidAddElement),
			luabind::def("DsvAddEChoice", &GBS_RptExDsValidAddElementChoice),
			luabind::def("DsvValid", &GBS_RptExDsValid),
			luabind::def("RecordCmd", &GBS_RecordCmd),
			luabind::def("AdjustWord", &GBS_AdjustWord),
			luabind::def("CalSoeTime", &GBS_CalSoeTime),
			luabind::def("CalSoeTimeEx", &GBS_CalSoeTimeEx),
			luabind::def("CalSoeTripDesc", &GBS_SetSoeTripDesc),
			luabind::def("GetItemTestTime", &GBS_GetItemTestTime),
			luabind::def("GetItemTestBeginTime", &GBS_GetItemTestBeginTime),
			luabind::def("GetItemTestEndTime", &GBS_GetItemTestEndTime),
			luabind::def("CalSoeError", &GBS_CalSoeError),
			luabind::def("CalSoeError2", &GBS_CalSoeError2),

			luabind::def("ClearCommCmdParas", &GBS_ClearCommCmdParas),
			luabind::def("AddCommCmdPara", &GBS_AddCommCmdParaValue),
			luabind::def("AddCommCmdParaLong", &GBS_AddCommCmdParaValue_Long),
			luabind::def("AddCommCmdParaStr", &GBS_AddCommCmdParaValue_String),

			luabind::def("RcdSetProgID", &GBS_RcdSetProgID),
			luabind::def("RcdExit", &GBS_RcdExit),
			luabind::def("RcdConfig", &GBS_RcdConfig),
			luabind::def("RcdSelect", &GBS_RcdSelect),
			luabind::def("RcdValidate", &GBS_RcdValidate),
			luabind::def("RcdCmpClear", &GBS_RcdCmpClear),
			luabind::def("RcdCmp", &GBS_RcdCmp),
			luabind::def("RcdCmpInit", &GBS_RcdCmpInit),
			luabind::def("RcdCopyFile", &GBS_RcdCopyFile),
			luabind::def("RcdSetPath", &GBS_RcdSetPath),

			luabind::def("GetRepeatTimes", &GBS_GetRepeatTimes),
			luabind::def("GetRepeatSuccTimes", &GBS_GetRepeatSuccTimes),
			luabind::def("SetCmdZoneIndex", &GBS_SetCmdZoneIndex),
			luabind::def("ValidBeginEndValRange", &Gbs_ValidBeginEndValRange),

			luabind::def("TmTrgSetSecond", &Gbs_SetTmTriggerSecond),
			luabind::def("TmTrgSetCntMinute", &Gbs_SetTmTriggerCountMinute),
			luabind::def("TmTrgEnter", &Gbs_EnterTmTrigger),
			luabind::def("TmTrgStart", &Gbs_StartTimerTigger),
			luabind::def("TmTrgStop", &Gbs_StopTimerTrigger),

			luabind::def("FltRptExQryUseErr", &Gbs_FilterRptExQueryUseErr),
			luabind::def("FltRptExQryUseErrEx", &Gbs_FilterRptExQueryUseErrEx),
			luabind::def("FltRptExQryUseAvg", &Gbs_FilterRptExQueryUseAvg),
			luabind::def("FltRptExQryUseAvgEx", &Gbs_FilterRptExQueryUseAvgEx),
			luabind::def("FltRptExQryClrNoUse", &Gbs_FilterRptExQueryClearNotUse),
			luabind::def("ValueRevised", &Gbs_ValueRevised),

			luabind::def("LogQueryClear", &Gbs_log_query_clear),
			luabind::def("LogQueryTime", &Gbs_log_query_time),
			luabind::def("LogQueryEntryID", &Gbs_log_query_entryid),
			luabind::def("LogQueryLogctrl", &Gbs_log_query_logctrl),
			luabind::def("LogQueryDataset", &Gbs_log_query_dataset),
			luabind::def("LogQueryData", &Gbs_log_query_data),
			luabind::def("LogQueryDataClear", &Gbs_log_query_data_clear),
			luabind::def("LogQueryDataGetCount", &Gbs_log_query_data_get_count),
			luabind::def("LogQueryDataAddRpt", &Gbs_log_query_data_add_to_rpt),
			luabind::def("LogQuery", &Gbs_log_query),
			luabind::def("LogGetCount", &Gbs_log_get_count),
			luabind::def("LogGetAttr", &Gbs_log_get_attr),
			luabind::def("LogGetDataCount", &Gbs_log_get_data_count),
			luabind::def("LogGetDataAtr", &Gbs_log_get_data_attr),
			luabind::def("LogGetDataAttr2)", &Gbs_log_get_data_attr2),
			luabind::def("StrTokInit", &GBS_InitStrTok),
			luabind::def("StrTokCount", &GBS_StrTokCount),
			luabind::def("StrTokIndex", &GBS_StrTokIndex),
			luabind::def("StrTokNext", &GBS_StrTokNext),
			luabind::def("ParseFileNameEx", &GBS_GetFileNameFromPath),
			luabind::def("ParseFilePostfix", &GBS_ParseFilePostfix),
			luabind::def("ParseFileName", &GBS_ParseFileName),
			luabind::def("SubStrToLong", &GBS_SubStrToLong),
			luabind::def("SubStrToStr", &GBS_SubStrToStr)	,
			luabind::def("SetGlobal_Str", &GBS_SetGlobal_Str),
			luabind::def("SetGlobal_Long", &GBS_SetGlobal_Long),
			luabind::def("SetGlobal_Float", &GBS_SetGlobal_Float),
			luabind::def("GetGlobal_Str", &GBS_GetGlobal_Str),
			luabind::def("GetGlobal_Long", &GBS_GetGlobal_Long),
			luabind::def("GetGlobal_Float", &GBS_GetGlobal_Float),

			luabind::def("SetTestError", &GBS_Set_TestError),
			luabind::def("GetSecondsFromMidnight", &GBS_GetSecondsFromMidnight),
			luabind::def("BinRslt", &GBS_BinRslt),
			luabind::def("BinChngCntRslt", &GBS_BinChngCntRslt),
			luabind::def("BinStateRslt", &GBS_BinStateRslt),
			luabind::def("SetAddErrValToRpt", &GBS_Set_AddDataErrorValueToRpt),
			luabind::def("AddDataErrToRpt", &GBS_AddDataErrorToRpt),
			luabind::def("GetTemplateFile", &GBS_GetTemplateFile),
			luabind::def("GetGbrptFile", &GBS_GetGbrptFile),
			luabind::def("SetGbrptFileName", &GBS_SetGbrptFileName),
			luabind::def("OffsetDataByDvIndex", &GBS_OffsetTestDataByGbrptIndex),
			luabind::def("VersionInfoCompare", &GBS_VersionInfoCompare),
			luabind::def("SetComtradeDrawLineMode", &GBS_SetComtradeDrawLineMode)
		]; 
}

BOOL Gb_InitLua()
{
	if( g_pGuideBookLua == NULL)  // 确保只会初始化一次 
	{ 
		g_pGuideBookLua = luaL_newstate(); // 创建Lua状态 

		if( g_pGuideBookLua == NULL) 
		{
			return false; 
		}

		luaL_openlibs( g_pGuideBookLua ); // 为该Lua状态打开所有Lua库 
		luabind::open( g_pGuideBookLua ); // 为该Lua状态打开luabind库 
	
		Gb_RegisterFunctions();		//绑定全局脚本函数
	} 

	lua_set_dofile_lib_path(_P_GetLibraryPath());

	return TRUE;
}

void Gb_CloseLua()
{
	if (g_pGuideBookLua != NULL)
	{
		lua_settop(g_pGuideBookLua,0);
		lua_close(g_pGuideBookLua);
		g_pGuideBookLua = NULL;
	}
}
// 
// void Gb_GetLuaGolbalVariables()
// {
// 	lua_getglobal(g_pGuideBookLua, "dAngPS");
// 	lua_getglobal(g_pGuideBookLua, "dGdDisZ");
// 	lua_getglobal(g_pGuideBookLua, "dGdDisT");
// 	lua_getglobal(g_pGuideBookLua, "dK0Zx");
// 	lua_getglobal(g_pGuideBookLua, "dK0Zr");
// 	lua_getglobal(g_pGuideBookLua, "PreFaultTime");
// 
// 	//遍历LUA堆栈，获取变量的值
// 	int top = lua_gettop(g_pGuideBookLua);
// 	int i = 0;
// 
// 	for (i = 1; i <= top; i++) 
// 	{ 
// 		int t = lua_type(g_pGuideBookLua, i);
// 
// 		switch (t) 
// 		{
// 		case LUA_TSTRING:  /* strings */
// 			CLogPrint::LogFormatString(NULL, XLOGLEVEL_INFOR, L"[%d] = %s", i, CString(lua_tostring(g_pGuideBookLua, i)) );
// 			break;
// 
// 		case LUA_TBOOLEAN:  /* booleans */
// 			break;
// 
// 		case LUA_TNUMBER:  /* numbers */
// 			CLogPrint::LogFormatString(NULL, XLOGLEVEL_INFOR, L"[%d] = %f", i, lua_tonumber(g_pGuideBookLua, i));
// 			break;
// 
// 		default:  /* other values */
// 			break;
// 
// 		}
// 	}
// }

long Gb_RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	//ASSERT (pScript != NULL && g_pGuideBookLua != NULL);
	long nErr = 0;

	CAutoSimpleLock oLock(&(_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oAutoCriticSection));

	if (pScript == NULL || g_pGuideBookLua == NULL)
	{
		return 0;
	}

	if (pScript->m_strScriptText.GetLength() == 0 && (!pScript->m_nIsRef) )
	{
		return 0;
	}

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SetScriptText( pScript );

	if (bInitFilter)
	{
		GBS_FilterInit();
	}

	long nLen = 0;
	char *pszScript = NULL;

	if (pScript->m_nIsRef)
	{
		CScriptText *pRef = pScript->GetRefScriptText();

		if(pRef != NULL)
		{
			nLen = pRef->m_strScriptText.GetLength();
			CString_to_char(pRef->m_strScriptText, &pszScript);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_FileNewest/*_T("引用脚本【%s】不存在，请检查脚本库文件是否为最新版本")*/, pScript->m_strID);
			nLen = 0;//pScript->m_strScriptText.GetLength();
			//CString_to_char(pScript->m_strScriptText, &pszScript);
			nErr = 1;
		}
	}
	else
	{
		nLen = pScript->m_strScriptText.GetLength();
		CString_to_char(pScript->m_strScriptText, &pszScript);
	}

	if (nErr > 0)
	{
		if (pszScript != NULL)
		{
			delete pszScript;
		}

		return nErr;
	}

	ASSERT (pszScript != NULL);
	nErr = luaL_loadstring(g_pGuideBookLua, pszScript);

	if (nErr)
	{
		strSyntaxError = lua_tostring(g_pGuideBookLua, -1);
		lua_pop(g_pGuideBookLua, -1);
		CLogPrint::LogString(XLOGLEVEL_ERROR, strSyntaxError);
	}
	else
	{
		nErr = lua_pcall(g_pGuideBookLua, 0, LUA_MULTRET, 0);

		if (nErr)
		{
			strSyntaxError = lua_tostring(g_pGuideBookLua, -1);
			lua_pop(g_pGuideBookLua, -1);
			CLogPrint::LogString(XLOGLEVEL_ERROR, strSyntaxError);
		}
	}

// 	Gb_GetLuaGolbalVariables();
	delete pszScript;
	lua_settop(g_pGuideBookLua, 0);

	return nErr;
}

long Gb_CompileScript(CScriptText *pScript, CString &strSyntaxError)
{
	return Gb_RunScript(pScript, strSyntaxError);
}

