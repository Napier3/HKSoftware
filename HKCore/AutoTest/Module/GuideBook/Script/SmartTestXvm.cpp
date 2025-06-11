#include "stdafx.h"
#include "SmartTestXvm.h"

#include "SmartTestHostApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSmartTestXvm::CSmartTestXvm()
{

}

CSmartTestXvm::~CSmartTestXvm()
{

}

void CSmartTestXvm::RegisterHostAPIFuncs()
{
	CTScriptSingleVM::RegisterHostAPIFuncs();

	RegisterHostAPIFunc (-1, "SetShow", xvm_GBS_SetItemShow );
	RegisterHostAPIFunc (-1, "GetShow", xvm_GBS_GetItemShow ); 
	RegisterHostAPIFunc (-1, "SetEnable", xvm_GBS_SetItemEnable );
	RegisterHostAPIFunc (-1, "GetEnable", xvm_GBS_GetItemEnable ); 
	RegisterHostAPIFunc (-1, "SetSelect", xvm_GBS_SetItemSelect );
	RegisterHostAPIFunc (-1, "GetSelect", xvm_GBS_GetItemSelect );
	RegisterHostAPIFunc (-1, "SetName", xvm_GBS_SetItemName);
	RegisterHostAPIFunc (-1, "GetName", xvm_GBS_GetItemName);
	RegisterHostAPIFunc (-1, "SetRsltJdg", xvm_GBS_SetItemResultJudge);
	RegisterHostAPIFunc (-1, "GetRsltJdg", xvm_GBS_GetItemResultJudge);
	RegisterHostAPIFunc (-1, "SetPara", xvm_GBS_SetItemParaValue);
	RegisterHostAPIFunc (-1, "SetParaStr", xvm_GBS_SetItemParaValueStr);
	RegisterHostAPIFunc (-1, "GetPara", xvm_GBS_GetItemParaValue);
	RegisterHostAPIFunc (-1, "GetParaStr", xvm_GBS_GetItemParaString);
	RegisterHostAPIFunc (-1, "AddRptMapData", xvm_GBS_AddRptMapData);
	RegisterHostAPIFunc (-1, "SetReportValue", xvm_GBS_SetItemReportValue);
	RegisterHostAPIFunc (-1, "SetReportValStr", xvm_GBS_SetItemReportValueString);
	RegisterHostAPIFunc (-1, "GetReportValue", xvm_GBS_GetItemReportValue);
	RegisterHostAPIFunc (-1, "GetRptValL", xvm_GBS_GetItemReportValueLong);
	RegisterHostAPIFunc (-1, "GetRptValStr", xvm_GBS_GetItemReportValueString);
	RegisterHostAPIFunc (-1, "GotoItem", xvm_GBS_GotoItem );
	RegisterHostAPIFunc (-1, "GotoItemEx", xvm_GBS_GotoItemEx );
	RegisterHostAPIFunc (-1, "MtExcuteCmd", xvm_GBS_MtExcuteCmd);
	RegisterHostAPIFunc (-1, "MtRegistPpDataMsg", xvm_GBS_MtRegistPpDataMsg);
	RegisterHostAPIFunc (-1, "MtUnRegistPpDataMsg", xvm_GBS_MtUnRegistPpDataMsg);
	RegisterHostAPIFunc (-1, "MtRegistCmdMsg", xvm_GBS_MtRegistCmdMsg);
	RegisterHostAPIFunc (-1, "MtUnRegistCmdMsg", xvm_GBS_MtUnRegistCmdMsg);
	RegisterHostAPIFunc (-1, "BreakLoop", xvm_GBS_BreakLoop );
	RegisterHostAPIFunc (-1, "BreakItems", xvm_GBS_BreakItems );

	RegisterHostAPIFunc (-1, "GetReportValueEx", xvm_GBS_GetItemReportValueEx);
	RegisterHostAPIFunc (-1, "GetRptValLEx", xvm_GBS_GetItemReportValueLongEx);
	RegisterHostAPIFunc (-1, "GetRptValStrEx", xvm_GBS_GetItemReportValueStringEx);
	RegisterHostAPIFunc (-1, "GetRptCount", xvm_GBS_GetItemReportCount);
	RegisterHostAPIFunc (-1, "ClearReports", xvm_GBS_ClearReports);

	RegisterHostAPIFunc (-1, "SetUploadRptFile", xvm_GBS_SetUploadRptFile );
	RegisterHostAPIFunc (-1, "GetDsDataValue", xvm_GBS_GetDsDataValue ); 
	RegisterHostAPIFunc (-1, "SetDsDataValue", xvm_GBS_SetDsDataValue);
	RegisterHostAPIFunc (-1, "GetDsDataStr", xvm_GBS_GetDsDataValueStr );
	RegisterHostAPIFunc (-1, "SetDsDataStr", xvm_GBS_SetDsDataValueStr);
	RegisterHostAPIFunc (-1, "GetDsDataValueEx", xvm_GBS_GetDsDataValueEx ); 
	RegisterHostAPIFunc (-1, "GetDsDataAttr", xvm_GBS_GetDsDataAttr );
	RegisterHostAPIFunc (-1, "GetDsDataAttrStr", xvm_GBS_GetDsDataAttrStr );   // 2024-2-26 shaolei
	RegisterHostAPIFunc (-1, "SetDsDataValueEx", xvm_GBS_SetDsDataValueEx);
	RegisterHostAPIFunc (-1, "GetDsDataStrEx", xvm_GBS_GetDsDataValueStrEx ); 
	RegisterHostAPIFunc (-1, "SetDsDataStrEx", xvm_GBS_SetDsDataValueStrEx);
	RegisterHostAPIFunc (-1, "CalAinError", xvm_GBS_CalAinError);
	RegisterHostAPIFunc (-1, "CalAinErrorNom", xvm_GBS_CalAinErrorNom);
	RegisterHostAPIFunc (-1, "CalAinErrorEx", xvm_GBS_CalAinErrorEx);
	RegisterHostAPIFunc (-1, "CalAinError2", xvm_GBS_CalAinError2);
	RegisterHostAPIFunc (-1, "CalAinStdError", xvm_GBS_CalAinStdError);
	RegisterHostAPIFunc (-1, "CalAinStdError2", xvm_GBS_CalAinStdError2);
	RegisterHostAPIFunc (-1, "CalVariation", xvm_GBS_CalVariation);
	RegisterHostAPIFunc (-1, "CalVariationErr", xvm_GBS_CalVariationErr);
	RegisterHostAPIFunc (-1, "CalVariationErrEx", xvm_GBS_CalVariationErrEx);
	RegisterHostAPIFunc (-1, "FltCalErrMax", xvm_GBS_FlterCalErrorMax);
	RegisterHostAPIFunc (-1, "FltCalErrMin", xvm_GBS_FlterCalErrorMin);
// 	RegisterHostAPIFunc (-1, "GetSetValue", xvm_GBS_GetSetValue ); 
// 	RegisterHostAPIFunc (-1, "SetSetValue", xvm_GBS_SetSetValue);
// 	RegisterHostAPIFunc (-1, "GetSysPara", xvm_GBS_GetSysParaValue);
// 	RegisterHostAPIFunc (-1, "GetSftValue", xvm_GBS_GetSoftswitchValue ); 
// 	RegisterHostAPIFunc (-1, "SetSftValue", xvm_GBS_SetSoftswitchValue);
// 	RegisterHostAPIFunc (-1, "SetSysPara", xvm_GBS_SetSysParaValue);
	RegisterHostAPIFunc (-1, "GetTestPara", xvm_GBS_GetTestParaValue);
	RegisterHostAPIFunc (-1, "GetTestParaStr", xvm_GBS_GetTestParaStr);
	RegisterHostAPIFunc (-1, "SetTestPara", xvm_GBS_SetTestParaValue);
	RegisterHostAPIFunc (-1, "SetTestParaStr", xvm_GBS_SetTestParaStr);
	RegisterHostAPIFunc (-1, "ShowMsg", xvm_GBS_ShowMessage);
//	RegisterHostAPIFunc (-1, "PlayMusicFile", xvm_GBS_PlayMusicFile);
	RegisterHostAPIFunc (-1, "GetTime", xvm_GBS_GetTime);
	RegisterHostAPIFunc (-1, "GetRptExVal", xvm_GBS_GetItemReportExValue);
	RegisterHostAPIFunc (-1, "GetRptExValD", xvm_GBS_GetItemReportExValue_D);
	RegisterHostAPIFunc (-1, "GetRptExValL", xvm_GBS_GetItemReportExValue_L);
	RegisterHostAPIFunc (-1, "GetRptExValS", xvm_GBS_GetItemReportExValue_S);
	RegisterHostAPIFunc (-1, "GetRptExCount", xvm_GBS_GetItemReportExCount);
	RegisterHostAPIFunc (-1, "GetRptExCountByID", xvm_GBS_GetItemReportExDataCountByID);
	RegisterHostAPIFunc (-1, "GetRptExIndexByIDIndex", xvm_GBS_GetItemReportDataIndexByIDIndex);
	RegisterHostAPIFunc (-1, "GetFileInReportEx", xvm_GBS_GetFileInReportEx);
	RegisterHostAPIFunc (-1, "GetFileNumInReportEx", xvm_GBS_GetFileNumInReportEx);
	RegisterHostAPIFunc (-1, "CalTmGapStr", xvm_GBS_CalTimeGapStr);
	RegisterHostAPIFunc (-1, "CalTmGapStr_us", xvm_GBS_CalTimeGapStr_us);
	RegisterHostAPIFunc (-1, "CalTmGap", xvm_GBS_CalItemReportTimeGap);
	RegisterHostAPIFunc (-1, "CalTmGapEx", xvm_GBS_CalItemReportTimeGapEx);
	RegisterHostAPIFunc (-1, "CalTmGapEx2", xvm_GBS_CalItemReportTimeGapEx2);
	RegisterHostAPIFunc (-1, "GetTestIndex", xvm_GBS_GetTestIndex);

	RegisterHostAPIFunc (-1, "CalRptValMax", xvm_GBS_CalRptValMax);
	RegisterHostAPIFunc (-1, "CalRptValMin", xvm_GBS_CalRptValMin);
	RegisterHostAPIFunc (-1, "CalRptValAvg", xvm_GBS_CalRptValAvg);

	RegisterHostAPIFunc (-1, "FilterRptInit", xvm_GBS_FilterInit);
	RegisterHostAPIFunc (-1, "FilterRptExEqL", xvm_GBS_FilterReportExEqualValueL);
	RegisterHostAPIFunc (-1, "FilterRptExEqStr", xvm_GBS_FilterReportExEqualValueStr);
	RegisterHostAPIFunc (-1, "FilterRptExHasStr", xvm_GBS_FilterReportExHasValueStr);
	RegisterHostAPIFunc (-1, "FilterRptExNoStr", xvm_GBS_FilterReportExHasNoValueStr);
	RegisterHostAPIFunc (-1, "FilterCombine", xvm_GBS_FilterCombineReportEx);

	RegisterHostAPIFunc (-1, "FltRptExQuery", xvm_GBS_FilterRptExQuery);
	RegisterHostAPIFunc (-1, "FltRptExGetCount", xvm_GBS_FilterRptExGetCount);
	RegisterHostAPIFunc (-1, "FltRptExGetLong", xvm_GBS_FilterRptExGetLong);
	RegisterHostAPIFunc (-1, "FltRptExGetStr", xvm_GBS_FilterRptExGetString);
	RegisterHostAPIFunc (-1, "FltRptExGetDouble", xvm_GBS_FilterRptExGetDouble);
	RegisterHostAPIFunc (-1, "FltRptExGetValCount", xvm_GBS_FilterRptExGetValCount);
	RegisterHostAPIFunc (-1, "FltRptExGetValLong", xvm_GBS_FilterRptExGetValLong);
	RegisterHostAPIFunc (-1, "FltRptExGetValStr", xvm_GBS_FilterRptExGetValString);
	RegisterHostAPIFunc (-1, "FltRptExGetValDouble", xvm_GBS_FilterRptExGetValDouble);
	RegisterHostAPIFunc (-1, "FltRptExCalValError", xvm_GBS_FilterRptExCalValError);
	RegisterHostAPIFunc (-1, "FltRptExCalValErrEx", xvm_GBS_FilterRptExCalValErrorEx);

	RegisterHostAPIFunc (-1, "CreateDevice", xvm_GBS_PpCreateDevice);
	RegisterHostAPIFunc (-1, "ReleaseDevice", xvm_GBS_PpReleaseDevice);

	RegisterHostAPIFunc (-1, "GetDeviceAttr", xvm_GBS_PpGetDeviceAttr);
	RegisterHostAPIFunc (-1, "GetDeviceAttrL", xvm_GBS_PpGetDeviceAttrL);
	RegisterHostAPIFunc (-1, "GetDeviceAttrStr", xvm_GBS_PpGetDeviceAttrStr);
	RegisterHostAPIFunc (-1, "SetDeviceAttrL", xvm_GBS_PpSetDeviceAttrL);
	RegisterHostAPIFunc (-1, "SetDeviceAttrStr", xvm_GBS_PpSetDeviceAttrStr);
	RegisterHostAPIFunc (-1, "RptGetDevieNodeDatas", xvm_GBS_PpRptGetDevieNodeDatas);
	RegisterHostAPIFunc (-1, "RptGetDeviceAttrs", xvm_GBS_PpRptGetDeviceAttrs);
	RegisterHostAPIFunc (-1, "GetDevieNodeDataAttr", xvm_GBS_PpGetDevieNodeDataAttr);
	RegisterHostAPIFunc (-1, "SetDevieNodeDataAttr", xvm_GBS_PpSetDevieNodeDataAttr);
	RegisterHostAPIFunc (-1, "DeleteAllNodeData", xvm_GBS_PpDeleteAllNodeData);
	RegisterHostAPIFunc (-1, "IsProtocol", xvm_GBS_IsProtocol);

// 	RegisterHostAPIFunc (-1, "RecordPkg", xvm_GBS_RecordPackage);
// 	RegisterHostAPIFunc (-1, "UnRecordPkg", xvm_GBS_UnRecordPackage);
// 	RegisterHostAPIFunc (-1, "GetPckgPcTm", xvm_GBS_GetPackagePcTime);
// 	RegisterHostAPIFunc (-1, "GetGpsPcTmMap", xvm_GBS_GetGpsPcTimeMap);
// 	RegisterHostAPIFunc (-1, "GetOutGpsTm", xvm_GBS_GetOutGpsTime);
// 	RegisterHostAPIFunc (-1, "CalGpsPcTmGap", xvm_GBS_CalGpsPcTimeGap);
// 	RegisterHostAPIFunc (-1, "RdMacroTest", xvm_GBS_ReadMacroTestResult);
// 	RegisterHostAPIFunc (-1, "CrtGpsDtTm", xvm_GBS_CreateGpsDateTime);
// 	RegisterHostAPIFunc (-1, "CrtGpsTm", xvm_GBS_CreateGpsTime);
// 	RegisterHostAPIFunc (-1, "LGetRptDatas", xvm_GBS_LGetItemReportDataCount);
// 	RegisterHostAPIFunc (-1, "DownMacroPara", xvm_GBS_DownloadMacroTestPara);

	RegisterHostAPIFunc (-1, "SelectItem", xvm_GBS_SSelectItem);
	RegisterHostAPIFunc (-1, "GtItmRptCnt", xvm_GBS_SGetItemReportCount);
	RegisterHostAPIFunc (-1, "SelItemRpt", xvm_GBS_SSelectItemReport);
	RegisterHostAPIFunc (-1, "GtItmRptVal", xvm_GBS_SGetItemReportValue);
	RegisterHostAPIFunc (-1, "GtItmRptValL", xvm_GBS_SGetItemReportValueLong);
	RegisterHostAPIFunc (-1, "GtItmRptValS", xvm_GBS_SGetItemReportValueString);
	RegisterHostAPIFunc (-1, "GtItmRptVCnt", xvm_GBS_SGetItemReportValueCount);
	RegisterHostAPIFunc (-1, "GtItmRptVal2", xvm_GBS_SGetItemReportValue2);
	RegisterHostAPIFunc (-1, "GtItmRptValL2", xvm_GBS_SGetItemReportValueLong2);
	RegisterHostAPIFunc (-1, "GtItmRptValS2", xvm_GBS_SGetItemReportValueString2);
	RegisterHostAPIFunc (-1, "GtItmRptDCnt", xvm_GBS_SGetItemReportExDataCount);
	RegisterHostAPIFunc (-1, "GtItmRptDVal", xvm_GBS_SGetItemReportExDataValue);
	RegisterHostAPIFunc (-1, "GtItmRptDValL", xvm_GBS_SGetItemReportExDataValueLong);
	RegisterHostAPIFunc (-1, "GtItmRptDValS", xvm_GBS_SGetItemReportExDataValueString);
	RegisterHostAPIFunc (-1, "CmpDouble", xvm_GBS_CmpDouble);
	RegisterHostAPIFunc (-1, "CalRelErr", xvm_GBS_CalRelError);
	RegisterHostAPIFunc (-1, "CalIEC", xvm_GBS_IEC);
	RegisterHostAPIFunc (-1, "CalIEEE", xvm_GBS_IEEE);
	RegisterHostAPIFunc (-1, "CalIAC", xvm_GBS_IAC);
	RegisterHostAPIFunc (-1, "CalI2T", xvm_GBS_I2T);
	RegisterHostAPIFunc (-1, "RunExe", xvm_GBS_RunExe);
	RegisterHostAPIFunc (-1, "ExitExe", xvm_GBS_ExitExe);
	RegisterHostAPIFunc (-1, "CalTimeGap", xvm_GBS_CalTimeGap);
	RegisterHostAPIFunc (-1, "CalTimeGapCurr", xvm_GBS_CalTimeGapCurr);
	RegisterHostAPIFunc (-1, "AddLocalTime", xvm_GBS_AddLocalTime);
	RegisterHostAPIFunc (-1, "SubLocalTime", xvm_GBS_SubLocalTime);

	RegisterHostAPIFunc (-1, "RandLong", xvm_GBS_RandLong);
	RegisterHostAPIFunc (-1, "RandFloat", xvm_GBS_RandFloat);
	RegisterHostAPIFunc (-1, "RandDouble", xvm_GBS_RandDouble);
	RegisterHostAPIFunc (-1, "RandSeed", xvm_GBS_RandSeed);

	RegisterHostAPIFunc (-1, "RptExDsGetCount", xvm_GBS_RptExDsGetCount);
	RegisterHostAPIFunc (-1, "RptExDsGetValueD", xvm_GBS_RptExDsGetValueD);
	RegisterHostAPIFunc (-1, "RptExDsGetValueL", xvm_GBS_RptExDsGetValueL);
	RegisterHostAPIFunc (-1, "RptExDsGetValueStr", xvm_GBS_RptExDsGetValueStr);

	RegisterHostAPIFunc (-1, "DsvClear", xvm_GBS_RptExDsValidClear);
	RegisterHostAPIFunc (-1, "DsvAddElement", xvm_GBS_RptExDsValidAddElement);
	RegisterHostAPIFunc (-1, "DsvAddEChoice", xvm_GBS_RptExDsValidAddElementChoice);
	RegisterHostAPIFunc (-1, "DsvValid", xvm_GBS_RptExDsValid);
	RegisterHostAPIFunc (-1, "RecordCmd", xvm_GBS_RecordCmd);
	RegisterHostAPIFunc (-1, "AdjustWord", xvm_GBS_AdjustWord);
	RegisterHostAPIFunc (-1, "CalSoeTime", xvm_GBS_CalSoeTime);
	RegisterHostAPIFunc (-1, "CalSoeTimeEx", xvm_GBS_CalSoeTimeEx);
	RegisterHostAPIFunc (-1, "CalSoeTripDesc", xvm_GBS_SetSoeTripDesc);
	RegisterHostAPIFunc (-1, "GetItemTestTime", xvm_GBS_GetItemTestTime);
	RegisterHostAPIFunc (-1, "GetItemTestBeginTime", xvm_GBS_GetItemTestBeginTime);
	RegisterHostAPIFunc (-1, "GetItemTestEndTime", xvm_GBS_GetItemTestEndTime);
	RegisterHostAPIFunc (-1, "CalSoeError", xvm_GBS_CalSoeError);
	RegisterHostAPIFunc (-1, "CalSoeError2", xvm_GBS_CalSoeError2);

	RegisterHostAPIFunc (-1, "ClearCommCmdParas", xvm_GBS_ClearCommCmdParas);
	RegisterHostAPIFunc (-1, "AddCommCmdPara", xvm_GBS_AddCommCmdParaValue);
	RegisterHostAPIFunc (-1, "AddCommCmdParaLong", xvm_GBS_AddCommCmdParaValue_Long);
	RegisterHostAPIFunc (-1, "AddCommCmdParaStr", xvm_GBS_AddCommCmdParaValue_String);

	RegisterHostAPIFunc (-1, "RcdSetProgID", xvm_GBS_RcdSetProgID);
	RegisterHostAPIFunc (-1, "RcdExit", xvm_GBS_RcdExit);
	RegisterHostAPIFunc (-1, "RcdConfig", xvm_GBS_RcdConfig);
	RegisterHostAPIFunc (-1, "RcdSelect", xvm_GBS_RcdSelect);
	RegisterHostAPIFunc (-1, "RcdValidate", xvm_GBS_RcdValidate);
	RegisterHostAPIFunc (-1, "RcdCmpClear", xvm_GBS_RcdCmpClear);
	RegisterHostAPIFunc (-1, "RcdCmp", xvm_GBS_RcdCmp);
	RegisterHostAPIFunc (-1, "RcdCmpInit", xvm_GBS_RcdCmpInit);
	RegisterHostAPIFunc (-1, "RcdCopyFile", xvm_GBS_RcdCopyFile);
	RegisterHostAPIFunc (-1, "RcdSetPath", xvm_GBS_RcdSetPath);

	RegisterHostAPIFunc (-1, "GetRepeatTimes", xvm_GBS_GetRepeatTimes);
	RegisterHostAPIFunc (-1, "GetRepeatSuccTimes", xvm_GBS_GetRepeatSuccTimes);
	RegisterHostAPIFunc (-1, "SetCmdZoneIndex", xvm_GBS_SetCmdZoneIndex);
	RegisterHostAPIFunc (-1, "ValidBeginEndValRange", xvm_Gbs_ValidBeginEndValRange);

	RegisterHostAPIFunc (-1, "TmTrgSetSecond", xvm_Gbs_SetTmTriggerSecond);
	RegisterHostAPIFunc (-1, "TmTrgSetCntMinute", xvm_Gbs_SetTmTriggerCountMinute);
	RegisterHostAPIFunc (-1, "TmTrgEnter", xvm_Gbs_EnterTmTrigger);
	RegisterHostAPIFunc (-1, "TmTrgStart", xvm_Gbs_StartTimerTigger);
	RegisterHostAPIFunc (-1, "TmTrgStop", xvm_Gbs_StopTimerTrigger);

	RegisterHostAPIFunc (-1, "FltRptExQryUseErr", xvm_Gbs_FilterRptExQueryUseErr);
	RegisterHostAPIFunc (-1, "FltRptExQryUseErrEx", xvm_Gbs_FilterRptExQueryUseErrEx);
	RegisterHostAPIFunc (-1, "FltRptExQryUseAvg", xvm_Gbs_FilterRptExQueryUseAvg);
	RegisterHostAPIFunc (-1, "FltRptExQryUseAvgEx", xvm_Gbs_FilterRptExQueryUseAvgEx);
	RegisterHostAPIFunc (-1, "FltRptExQryClrNoUse", xvm_Gbs_FilterRptExQueryClearNotUse);
	RegisterHostAPIFunc (-1, "ValueRevised", xvm_Gbs_ValueRevised);

	RegisterHostAPIFunc (-1, "LogQueryClear", xvm_Gbs_log_query_clear);
	RegisterHostAPIFunc (-1, "LogQueryTime", xvm_Gbs_log_query_time);
	RegisterHostAPIFunc (-1, "LogQueryEntryID", xvm_Gbs_log_query_entryid);
	RegisterHostAPIFunc (-1, "LogQueryLogctrl", xvm_Gbs_log_query_logctrl);
	RegisterHostAPIFunc (-1, "LogQueryDataset", xvm_Gbs_log_query_dataset);
	RegisterHostAPIFunc (-1, "LogQueryData", xvm_Gbs_log_query_data);
	RegisterHostAPIFunc (-1, "LogQueryDataClear", xvm_Gbs_log_query_data_clear);
	RegisterHostAPIFunc (-1, "LogQueryDataGetCount", xvm_Gbs_log_query_data_get_count);
	RegisterHostAPIFunc (-1, "LogQueryDataAddRpt", xvm_Gbs_log_query_data_add_to_rpt);
	RegisterHostAPIFunc (-1, "LogQuery", xvm_Gbs_log_query);
	RegisterHostAPIFunc (-1, "LogGetCount", xvm_Gbs_log_get_count);
	RegisterHostAPIFunc (-1, "LogGetAttr", xvm_Gbs_log_get_attr);
	RegisterHostAPIFunc (-1, "LogGetDataCount", xvm_Gbs_log_get_data_count);
	RegisterHostAPIFunc (-1, "LogGetDataAtr", xvm_Gbs_log_get_data_attr);
	RegisterHostAPIFunc (-1, "LogGetDataAttr2", xvm_Gbs_log_get_data_attr2);
	RegisterHostAPIFunc (-1, "StrTokInit", xvm_GBS_InitStrTok);
	RegisterHostAPIFunc (-1, "StrTokCount", xvm_GBS_StrTokCount);
	RegisterHostAPIFunc (-1, "StrTokIndex", xvm_GBS_StrTokIndex);
	RegisterHostAPIFunc (-1, "StrTokNext", xvm_GBS_StrTokNext);
	RegisterHostAPIFunc (-1, "ParseFileNameEx", xvm_GBS_GetFileNameFromPath);
	RegisterHostAPIFunc (-1, "ParseFilePostfix", xvm_GBS_ParseFilePostfix);
	RegisterHostAPIFunc (-1, "ParseFileName", xvm_GBS_ParseFileName);
	RegisterHostAPIFunc (-1, "SubStrToLong", xvm_GBS_SubStrToLong);
	RegisterHostAPIFunc (-1, "SubStrToStr", xvm_GBS_SubStrToStr)	,
	RegisterHostAPIFunc (-1, "SetGlobal_Str", xvm_GBS_SetGlobal_Str);
	RegisterHostAPIFunc (-1, "SetGlobal_Long", xvm_GBS_SetGlobal_Long);
	RegisterHostAPIFunc (-1, "SetGlobal_Float", xvm_GBS_SetGlobal_Float);
	RegisterHostAPIFunc (-1, "GetGlobal_Str", xvm_GBS_GetGlobal_Str);
	RegisterHostAPIFunc (-1, "GetGlobal_Long", xvm_GBS_GetGlobal_Long);
	RegisterHostAPIFunc (-1, "GetGlobal_Float", xvm_GBS_GetGlobal_Float);

	RegisterHostAPIFunc (-1, "SetTestError", xvm_GBS_Set_TestError);
	RegisterHostAPIFunc (-1, "GetSecondsFromMidnight", xvm_GBS_GetSecondsFromMidnight);
	RegisterHostAPIFunc (-1, "BinRslt", xvm_GBS_BinRslt);
	RegisterHostAPIFunc (-1, "BinChngCntRslt", xvm_GBS_BinChngCntRslt);
	RegisterHostAPIFunc (-1, "BinStateRslt", xvm_GBS_BinStateRslt);
	RegisterHostAPIFunc (-1, "SetAddErrValToRpt", xvm_GBS_Set_AddDataErrorValueToRpt);
	RegisterHostAPIFunc (-1, "AddDataErrToRpt", xvm_GBS_AddDataErrorToRpt);
	RegisterHostAPIFunc (-1, "GetTemplateFile", xvm_GBS_GetTemplateFile);
	RegisterHostAPIFunc (-1, "GetGbrptFile", xvm_GBS_GetGbrptFile);
	RegisterHostAPIFunc (-1, "SetGbrptFileName", xvm_GBS_SetGbrptFileName);
	RegisterHostAPIFunc (-1, "OffsetDataByDvIndex", xvm_GBS_OffsetTestDataByGbrptIndex);
	RegisterHostAPIFunc (-1, "VersionInfoCompare", xvm_GBS_VersionInfoCompare);
	RegisterHostAPIFunc (-1, "SetComtradeDrawLineMode", xvm_GBS_SetComtradeDrawLineMode);

	//2021-2-21  lijunqing
	RegisterHostAPIFunc (-1, "RcdAnalysis", xvm_GBS_RcdAnalysis);

	//2021-3-28  lijunqing  根据数据集创建安全措施的数据对象
	RegisterHostAPIFunc (-1, "CreateSafetyDatasByDataset", xvm_GBS_CreateSafetyDatasByDvmDataset);

	//2021-5-23  lijunqing  
	RegisterHostAPIFunc (-1, "ImportSets", xvm_GBS_ImportSets);

	//2021-5-20 shaolei
	RegisterHostAPIFunc (-1, "Sleep", xvm_GBS_Sleep);
	//2021-11-12 shaolei
	RegisterHostAPIFunc (-1, "SaveExportDatas", xvm_GBS_SaveExportDatas);
	RegisterHostAPIFunc (-1, "SetExportData", xvm_GBS_SetExportData);
	//shaolei 20220330 
	RegisterHostAPIFunc (-1, "IsDsDataExist", xvm_GBS_IsDsDataExist);
	//shaolei 20220618 
	RegisterHostAPIFunc (-1, "GenSvMatchItems", xvm_GBS_GenSvMatchItems);
	RegisterHostAPIFunc (-1, "ReadDvmFromLocal", xvm_GBS_ReadDvmFromLocal);
	RegisterHostAPIFunc (-1, "SaveDvmToLocal", xvm_GBS_SaveDvmToLocal);

	//2023-4-17  lijunqing
	RegisterHostAPIFunc (-1, "IecfgAddCnnInfoToSft", xvm_GBS_IecfgAddCnnInfoToSft);
	//shaolei 20230614 
	RegisterHostAPIFunc (-1, "GenTransPlayItems", xvm_GBS_GenTransPlayItems);
}

