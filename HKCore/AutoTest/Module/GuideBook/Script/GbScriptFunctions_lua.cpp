#include "StdAfx.h"
#include "SmartTestHostApi_lua.h"
#include "GbScriptFunctions_lua.h"

#include "GbScript_GlobalDefine.h"

//Lua
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luabind.hpp"
#include "..\..\XLanguageResourceAts.h"

lua_State* g_pGuideBookLua = NULL;
extern char g_pLuaReturnString[MAX_PATH];

void Gb_RegisterFunctions()
{
	luabind::module( g_pGuideBookLua ) 
		[ 
			luabind::def("SetShow", &lua_GBS_SetItemShow ),
			luabind::def("GetShow", &lua_GBS_GetItemShow ), 
			luabind::def("SetEnable", &lua_GBS_SetItemEnable),
			luabind::def("GetEnable", &lua_GBS_GetItemEnable),
			luabind::def("SetSelect", &lua_GBS_SetItemSelect),
			luabind::def("GetSelect", &lua_GBS_GetItemSelect),
			luabind::def("SetName", &lua_GBS_SetItemName),
			luabind::def("GetName", &lua_GBS_GetItemName),
			luabind::def("SetRsltJdg", &lua_GBS_SetItemResultJudge),
			luabind::def("GetRsltJdg", &lua_GBS_GetItemResultJudge),
			luabind::def("SetPara", &lua_GBS_SetItemParaValue),
			luabind::def("SetParaStr", &lua_GBS_SetItemParaValueStr),
			luabind::def("GetPara", &lua_GBS_GetItemParaValue),
			luabind::def("GetParaStr", &lua_GBS_GetItemParaString),
			luabind::def("AddRptMapData", &lua_GBS_AddRptMapData),
			luabind::def("SetReportValue", &lua_GBS_SetItemReportValue),
			luabind::def("SetReportValStr", &lua_GBS_SetItemReportValueString),
			luabind::def("GetReportValue", &lua_GBS_GetItemReportValue),
			luabind::def("GetRptValL", &lua_GBS_GetItemReportValueLong),
			luabind::def("GetRptValStr", &lua_GBS_GetItemReportValueString),
			luabind::def("GotoItem", &lua_GBS_GotoItem ),
			luabind::def("GotoItemEx", &lua_GBS_GotoItemEx ),
			luabind::def("MtExcuteCmd", &lua_GBS_MtExcuteCmd),
			luabind::def("MtRegistPpDataMsg", &lua_GBS_MtRegistPpDataMsg),
			luabind::def("MtUnRegistPpDataMsg", &lua_GBS_MtUnRegistPpDataMsg),
			luabind::def("MtRegistCmdMsg", &lua_GBS_MtRegistCmdMsg),
			luabind::def("MtUnRegistCmdMsg", &lua_GBS_MtUnRegistCmdMsg),
			luabind::def("BreakLoop", &lua_GBS_BreakLoop ),
			luabind::def("BreakItems", &lua_GBS_BreakItems ),

			luabind::def("GetReportValueEx", &lua_GBS_GetItemReportValueEx),
			luabind::def("GetRptValLEx", &lua_GBS_GetItemReportValueLongEx),
			luabind::def("GetRptValStrEx", &lua_GBS_GetItemReportValueStringEx),
			luabind::def("GetRptCount", &lua_GBS_GetItemReportCount),
			luabind::def("ClearReports", &lua_GBS_ClearReports),

			luabind::def("SetUploadRptFile", &lua_GBS_SetUploadRptFile ),
			luabind::def("GetDsDataValue", &lua_GBS_GetDsDataValue ), 
			luabind::def("SetDsDataValue", &lua_GBS_SetDsDataValue),
			luabind::def("GetDsDataStr", &lua_GBS_GetDsDataValueStr ), 
			luabind::def("SetDsDataStr", &lua_GBS_SetDsDataValueStr),
			luabind::def("GetDsDataValueEx", &lua_GBS_GetDsDataValueEx ), 
			luabind::def("GetDsDataAttr", &lua_GBS_GetDsDataAttr ), 
			luabind::def("GetDsDataAttrStr", &lua_GBS_GetDsDataAttrStr ), //2024-2-26 shaolei
			luabind::def("SetDsDataValueEx", &lua_GBS_SetDsDataValueEx),
			luabind::def("GetDsDataStrEx", &lua_GBS_GetDsDataValueStrEx ), 
			luabind::def("SetDsDataStrEx", &lua_GBS_SetDsDataValueStrEx),
			luabind::def("CalAinError", &lua_GBS_CalAinError),
			luabind::def("CalAinErrorNom", &lua_GBS_CalAinErrorNom),
			luabind::def("CalAinErrorEx", &lua_GBS_CalAinErrorEx),
			luabind::def("CalAinError2", &lua_GBS_CalAinError2),
			luabind::def("CalAinStdError", &lua_GBS_CalAinStdError),
			luabind::def("CalAinStdError2", &lua_GBS_CalAinStdError2),
			luabind::def("CalVariation", &lua_GBS_CalVariation),
			luabind::def("CalVariationErr", &lua_GBS_CalVariationErr),
			luabind::def("CalVariationErrEx", &lua_GBS_CalVariationErrEx),
			luabind::def("FltCalErrMax", &lua_GBS_FlterCalErrorMax),
			luabind::def("FltCalErrMin", &lua_GBS_FlterCalErrorMin),
// 			luabind::def("GetSetValue", &lua_GBS_GetSetValue ), 
// 			luabind::def("SetSetValue", &lua_GBS_SetSetValue),
// 			luabind::def("GetSysPara", &lua_GBS_GetSysParaValue),
// 			luabind::def("GetSftValue", &lua_GBS_GetSoftswitchValue ), 
// 			luabind::def("SetSftValue", &lua_GBS_SetSoftswitchValue),
// 			luabind::def("SetSysPara", &lua_GBS_SetSysParaValue),
			luabind::def("GetTestPara", &lua_GBS_GetTestParaValue),
			luabind::def("GetTestParaStr", &lua_GBS_GetTestParaStr),
			luabind::def("SetTestPara", &lua_GBS_SetTestParaValue),
			luabind::def("SetTestParaStr", &lua_GBS_SetTestParaStr),
			luabind::def("ShowMsg", &lua_GBS_ShowMessage),
			//luabind::def("PlayMusicFile", &lua_GBS_PlayMusicFile),
			luabind::def("GetTime", &lua_GBS_GetTime),
			luabind::def("GetRptExVal", &lua_GBS_GetItemReportExValue),
			luabind::def("GetRptExValD", &lua_GBS_GetItemReportExValue_D),
			luabind::def("GetRptExValL", &lua_GBS_GetItemReportExValue_L),
			luabind::def("GetRptExValS", &lua_GBS_GetItemReportExValue_S),
			luabind::def("GetRptExCount", &lua_GBS_GetItemReportExCount),
			luabind::def("GetRptExCountByID", &lua_GBS_GetItemReportExDataCountByID),
			luabind::def("GetRptExIndexByIDIndex", &lua_GBS_GetItemReportDataIndexByIDIndex),
			luabind::def("GetFileInReportEx", &lua_GBS_GetFileInReportEx),
			luabind::def("GetFileNumInReportEx", &lua_GBS_GetFileNumInReportEx),
			luabind::def("CalTmGapStr", &lua_GBS_CalTimeGapStr),
			luabind::def("CalTmGapStr_us", &lua_GBS_CalTimeGapStr_us),
			luabind::def("CalTmGap", &lua_GBS_CalItemReportTimeGap),
			luabind::def("CalTmGapEx", &lua_GBS_CalItemReportTimeGapEx),
			luabind::def("CalTmGapEx2", &lua_GBS_CalItemReportTimeGapEx2),
			luabind::def("GetTestIndex", &lua_GBS_GetTestIndex),

			luabind::def("CalRptValMax", &lua_GBS_CalRptValMax),
			luabind::def("CalRptValMin", &lua_GBS_CalRptValMin),
			luabind::def("CalRptValAvg", &lua_GBS_CalRptValAvg),

			luabind::def("FilterRptInit", &lua_GBS_FilterInit),
			luabind::def("FilterRptExEqL", &lua_GBS_FilterReportExEqualValueL),
			luabind::def("FilterRptExEqStr", &lua_GBS_FilterReportExEqualValueStr),
			luabind::def("FilterRptExHasStr", &lua_GBS_FilterReportExHasValueStr),
			luabind::def("FilterRptExNoStr", &lua_GBS_FilterReportExHasNoValueStr),
			luabind::def("FilterCombine", &lua_GBS_FilterCombineReportEx),
		
			luabind::def("FltRptExQuery", &lua_GBS_FilterRptExQuery),
			luabind::def("FltRptExGetCount", &lua_GBS_FilterRptExGetCount),
			luabind::def("FltRptExGetLong", &lua_GBS_FilterRptExGetLong),
			luabind::def("FltRptExGetStr", &lua_GBS_FilterRptExGetString),
			luabind::def("FltRptExGetDouble", &lua_GBS_FilterRptExGetDouble),
			luabind::def("FltRptExGetValCount", &lua_GBS_FilterRptExGetValCount),
			luabind::def("FltRptExGetValLong", &lua_GBS_FilterRptExGetValLong),
			luabind::def("FltRptExGetValStr", &lua_GBS_FilterRptExGetValString),
			luabind::def("FltRptExGetValDouble", &lua_GBS_FilterRptExGetValDouble),
			luabind::def("FltRptExCalValError", &lua_GBS_FilterRptExCalValError),
			luabind::def("FltRptExCalValErrEx", &lua_GBS_FilterRptExCalValErrorEx),

			luabind::def("CreateDevice", &lua_GBS_PpCreateDevice),
			luabind::def("ReleaseDevice", &lua_GBS_PpReleaseDevice),

			luabind::def("GetDeviceAttr", &lua_GBS_PpGetDeviceAttr),
			luabind::def("GetDeviceAttrL", &lua_GBS_PpGetDeviceAttrL),
			luabind::def("GetDeviceAttrStr", &lua_GBS_PpGetDeviceAttrStr),
			luabind::def("SetDeviceAttrL", &lua_GBS_PpSetDeviceAttrL),
			luabind::def("SetDeviceAttrStr", &lua_GBS_PpSetDeviceAttrStr),
			luabind::def("RptGetDevieNodeDatas", &lua_GBS_PpRptGetDevieNodeDatas),
			luabind::def("RptGetDeviceAttrs", &lua_GBS_PpRptGetDeviceAttrs),
			luabind::def("GetDevieNodeDataAttr", &lua_GBS_PpGetDevieNodeDataAttr),
			luabind::def("SetDevieNodeDataAttr", &lua_GBS_PpSetDevieNodeDataAttr),
			luabind::def("DeleteAllNodeData", &lua_GBS_PpDeleteAllNodeData),
			luabind::def("IsProtocol", &lua_GBS_IsProtocol),

// 			luabind::def("RecordPkg", &lua_GBS_RecordPackage),
// 			luabind::def("UnRecordPkg", &lua_GBS_UnRecordPackage),
// 			luabind::def("GetPckgPcTm", &lua_GBS_GetPackagePcTime),
// 			luabind::def("GetGpsPcTmMap", &lua_GBS_GetGpsPcTimeMap),
// 			luabind::def("GetOutGpsTm", &lua_GBS_GetOutGpsTime),
// 			luabind::def("CalGpsPcTmGap", &lua_GBS_CalGpsPcTimeGap),
// 			luabind::def("RdMacroTest", &lua_GBS_ReadMacroTestResult),
// 			luabind::def("CrtGpsDtTm", &lua_GBS_CreateGpsDateTime),
// 			luabind::def("CrtGpsTm", &lua_GBS_CreateGpsTime),
// 			luabind::def("LGetRptDatas", &lua_GBS_LGetItemReportDataCount),
// 			luabind::def("DownMacroPara", &lua_GBS_DownloadMacroTestPara),

			luabind::def("SelectItem", &lua_GBS_SSelectItem),
			luabind::def("GtItmRptCnt", &lua_GBS_SGetItemReportCount),
			luabind::def("SelItemRpt", &lua_GBS_SSelectItemReport),
			luabind::def("GtItmRptVal", &lua_GBS_SGetItemReportValue),
			luabind::def("GtItmRptValL", &lua_GBS_SGetItemReportValueLong),
			luabind::def("GtItmRptValS", &lua_GBS_SGetItemReportValueString),
			luabind::def("GtItmRptVCnt", &lua_GBS_SGetItemReportValueCount),
			luabind::def("GtItmRptVal2", &lua_GBS_SGetItemReportValue2),
			luabind::def("GtItmRptValL2", &lua_GBS_SGetItemReportValueLong2),
			luabind::def("GtItmRptValS2", &lua_GBS_SGetItemReportValueString2),
			luabind::def("GtItmRptDCnt", &lua_GBS_SGetItemReportExDataCount),
			luabind::def("GtItmRptDVal", &lua_GBS_SGetItemReportExDataValue),
			luabind::def("GtItmRptDValL", &lua_GBS_SGetItemReportExDataValueLong),
			luabind::def("GtItmRptDValS", &lua_GBS_SGetItemReportExDataValueString),
			luabind::def("CmpDouble", &lua_GBS_CmpDouble),
			luabind::def("CalRelErr", &lua_GBS_CalRelError),
			luabind::def("CalIEC", &lua_GBS_IEC),
			luabind::def("CalIEEE", &lua_GBS_IEEE),
			luabind::def("CalIAC", &lua_GBS_IAC),
			luabind::def("CalI2T", &lua_GBS_I2T),
			luabind::def("RunExe", &lua_GBS_RunExe),
			luabind::def("ExitExe", &lua_GBS_ExitExe),
			luabind::def("CalTimeGap", &lua_GBS_CalTimeGap),
			luabind::def("CalTimeGapCurr", &lua_GBS_CalTimeGapCurr),
			luabind::def("AddLocalTime", &lua_GBS_AddLocalTime),
			luabind::def("SubLocalTime", &lua_GBS_SubLocalTime),

			luabind::def("RandLong", &lua_GBS_RandLong),
			luabind::def("RandFloat", &lua_GBS_RandFloat),
			luabind::def("RandDouble", &lua_GBS_RandDouble),
			luabind::def("RandSeed", &lua_GBS_RandSeed),

			luabind::def("RptExDsGetCount", &lua_GBS_RptExDsGetCount),
			luabind::def("RptExDsGetValueD", &lua_GBS_RptExDsGetValueD),
			luabind::def("RptExDsGetValueL", &lua_GBS_RptExDsGetValueL),
			luabind::def("RptExDsGetValueStr", &lua_GBS_RptExDsGetValueStr),

			luabind::def("DsvClear", &lua_GBS_RptExDsValidClear),
			luabind::def("DsvAddElement", &lua_GBS_RptExDsValidAddElement),
			luabind::def("DsvAddEChoice", &lua_GBS_RptExDsValidAddElementChoice),
			luabind::def("DsvValid", &lua_GBS_RptExDsValid),
			luabind::def("RecordCmd", &lua_GBS_RecordCmd),
			luabind::def("AdjustWord", &lua_GBS_AdjustWord),
			luabind::def("CalSoeTime", &lua_GBS_CalSoeTime),
			luabind::def("CalSoeTimeEx", &lua_GBS_CalSoeTimeEx),
			luabind::def("CalSoeTripDesc", &lua_GBS_SetSoeTripDesc),
			luabind::def("GetItemTestTime", &lua_GBS_GetItemTestTime),
			luabind::def("GetItemTestBeginTime", &lua_GBS_GetItemTestBeginTime),
			luabind::def("GetItemTestEndTime", &lua_GBS_GetItemTestEndTime),
			luabind::def("CalSoeError", &lua_GBS_CalSoeError),
			luabind::def("CalSoeError2", &lua_GBS_CalSoeError2),

			luabind::def("ClearCommCmdParas", &lua_GBS_ClearCommCmdParas),
			luabind::def("AddCommCmdPara", &lua_GBS_AddCommCmdParaValue),
			luabind::def("AddCommCmdParaLong", &lua_GBS_AddCommCmdParaValue_Long),
			luabind::def("AddCommCmdParaStr", &lua_GBS_AddCommCmdParaValue_String),

			luabind::def("RcdSetProgID", &lua_GBS_RcdSetProgID),
			luabind::def("RcdExit", &lua_GBS_RcdExit),
			luabind::def("RcdConfig", &lua_GBS_RcdConfig),
			luabind::def("RcdSelect", &lua_GBS_RcdSelect),
			luabind::def("RcdValidate", &lua_GBS_RcdValidate),
			luabind::def("RcdCmpClear", &lua_GBS_RcdCmpClear),
			luabind::def("RcdCmp", &lua_GBS_RcdCmp),
			luabind::def("RcdCmpInit", &lua_GBS_RcdCmpInit),
			luabind::def("RcdCopyFile", &lua_GBS_RcdCopyFile),
			luabind::def("RcdSetPath", &lua_GBS_RcdSetPath),

			luabind::def("GetRepeatTimes", &lua_GBS_GetRepeatTimes),
			luabind::def("GetRepeatSuccTimes", &lua_GBS_GetRepeatSuccTimes),
			luabind::def("SetCmdZoneIndex", &lua_GBS_SetCmdZoneIndex),
			luabind::def("ValidBeginEndValRange", &lua_Gbs_ValidBeginEndValRange),

			luabind::def("TmTrgSetSecond", &lua_Gbs_SetTmTriggerSecond),
			luabind::def("TmTrgSetCntMinute", &lua_Gbs_SetTmTriggerCountMinute),
			luabind::def("TmTrgEnter", &lua_Gbs_EnterTmTrigger),
			luabind::def("TmTrgStart", &lua_Gbs_StartTimerTigger),
			luabind::def("TmTrgStop", &lua_Gbs_StopTimerTrigger),

			luabind::def("FltRptExQryUseErr", &lua_Gbs_FilterRptExQueryUseErr),
			luabind::def("FltRptExQryUseErrEx", &lua_Gbs_FilterRptExQueryUseErrEx),
			luabind::def("FltRptExQryUseAvg", &lua_Gbs_FilterRptExQueryUseAvg),
			luabind::def("FltRptExQryUseAvgEx", &lua_Gbs_FilterRptExQueryUseAvgEx),
			luabind::def("FltRptExQryClrNoUse", &lua_Gbs_FilterRptExQueryClearNotUse),
			luabind::def("ValueRevised", &lua_Gbs_ValueRevised),

			luabind::def("LogQueryClear", &lua_Gbs_log_query_clear),
			luabind::def("LogQueryTime", &lua_Gbs_log_query_time),
			luabind::def("LogQueryEntryID", &lua_Gbs_log_query_entryid),
			luabind::def("LogQueryLogctrl", &lua_Gbs_log_query_logctrl),
			luabind::def("LogQueryDataset", &lua_Gbs_log_query_dataset),
			luabind::def("LogQueryData", &lua_Gbs_log_query_data),
			luabind::def("LogQueryDataClear", &lua_Gbs_log_query_data_clear),
			luabind::def("LogQueryDataGetCount", &lua_Gbs_log_query_data_get_count),
			luabind::def("LogQueryDataAddRpt", &lua_Gbs_log_query_data_add_to_rpt),
			luabind::def("LogQuery", &lua_Gbs_log_query),
			luabind::def("LogGetCount", &lua_Gbs_log_get_count),
			luabind::def("LogGetAttr", &lua_Gbs_log_get_attr),
			luabind::def("LogGetDataCount", &lua_Gbs_log_get_data_count),
			luabind::def("LogGetDataAtr", &lua_Gbs_log_get_data_attr),
			luabind::def("LogGetDataAttr2)", &lua_Gbs_log_get_data_attr2),
			luabind::def("StrTokInit", &lua_GBS_InitStrTok),
			luabind::def("StrTokCount", &lua_GBS_StrTokCount),
			luabind::def("StrTokIndex", &lua_GBS_StrTokIndex),
			luabind::def("StrTokNext", &lua_GBS_StrTokNext),
			luabind::def("ParseFileNameEx", &lua_GBS_GetFileNameFromPath),
			luabind::def("ParseFilePostfix", &lua_GBS_ParseFilePostfix),
			luabind::def("ParseFileName", &lua_GBS_ParseFileName),
			luabind::def("SubStrToLong", &lua_GBS_SubStrToLong),
			luabind::def("SubStrToStr", &lua_GBS_SubStrToStr)	,
			luabind::def("SetGlobal_Str", &lua_GBS_SetGlobal_Str),
			luabind::def("SetGlobal_Long", &lua_GBS_SetGlobal_Long),
			luabind::def("SetGlobal_Float", &lua_GBS_SetGlobal_Float),
			luabind::def("GetGlobal_Str", &lua_GBS_GetGlobal_Str),
			luabind::def("GetGlobal_Long", &lua_GBS_GetGlobal_Long),
			luabind::def("GetGlobal_Float", &lua_GBS_GetGlobal_Float),

			luabind::def("SetTestError", &lua_GBS_Set_TestError),
			luabind::def("GetSecondsFromMidnight", &lua_GBS_GetSecondsFromMidnight),
			luabind::def("BinRslt", &lua_GBS_BinRslt),
			luabind::def("BinChngCntRslt", &lua_GBS_BinChngCntRslt),
			luabind::def("BinStateRslt", &lua_GBS_BinStateRslt),
			luabind::def("SetAddErrValToRpt", &lua_GBS_Set_AddDataErrorValueToRpt),
			luabind::def("AddDataErrToRpt", &lua_GBS_AddDataErrorToRpt),
			luabind::def("GetTemplateFile", &lua_GBS_GetTemplateFile),
			luabind::def("GetGbrptFile", &lua_GBS_GetGbrptFile),
			luabind::def("SetGbrptFileName", &lua_GBS_SetGbrptFileName),
			luabind::def("OffsetDataByDvIndex", &lua_GBS_OffsetTestDataByGbrptIndex),
			luabind::def("VersionInfoCompare", &lua_GBS_VersionInfoCompare),
			luabind::def("SetComtradeDrawLineMode", &lua_GBS_SetComtradeDrawLineMode),
			luabind::def("RcdAnalysis", &lua_GBS_RcdAnalysis),
			luabind::def("CreateSafetyDatasByDataset", &lua_GBS_CreateSafetyDatasByDvmDataset),
			luabind::def("ImportSets", &lua_GBS_ImportSets),
			luabind::def("Sleep", &lua_GBS_Sleep),
			luabind::def("SaveExportDatas", &lua_GBS_SaveExportDatas),
			luabind::def("SetExportData", &lua_GBS_SetExportData),
			luabind::def("IsDsDataExist", &lua_GBS_IsDsDataExist),
			luabind::def("GenSvMatchItems", &lua_GBS_GenSvMatchItems),
			luabind::def("SaveDvmToLocal", &lua_GBS_SaveDvmToLocal),
			luabind::def("ReadDvmFromLocal", &lua_GBS_ReadDvmFromLocal),
			luabind::def("IecfgAddCnnInfoToSft", &lua_GBS_IecfgAddCnnInfoToSft),
			luabind::def("GenTransPlayItems", &lua_GBS_GenTransPlayItems)
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

long lua_RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter)
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
		GBS_FilterInit(NULL);
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_FileNewest/*_T("引用脚本【%s】不存在，请检查脚本库文件是否为最新版本")*/, pScript->m_strID);
			nLen = 0;//pScript->m_strScriptText.GetLength();
			//CString_to_char(pScript->m_strScriptText, &lua_pszScript);
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

long lua_CompileScript(CScriptText *pScript, CString &strSyntaxError)
{
	return lua_RunScript(pScript, strSyntaxError, TRUE);
}
