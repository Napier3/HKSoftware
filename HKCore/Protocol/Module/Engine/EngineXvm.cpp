#include "StdAfx.h"
#include "EngineXvm.h"

#include "EngineHostApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CEngineXvm::CEngineXvm()
{

}

CEngineXvm::~CEngineXvm()
{

}

void CEngineXvm::RegisterHostAPIFuncs()
{
	CTScriptSingleVM::RegisterHostAPIFuncs();

	RegisterHostAPIFunc (-1, "GetValDataType", xvm_script_GetCurrValueDataType );
	RegisterHostAPIFunc (-1, "GetValDataLen", xvm_script_GetCurrValueDataLength ); 
	RegisterHostAPIFunc (-1, "GetBbValLong", xvm_script_GetBbCurrValue);
	RegisterHostAPIFunc (-1, "GetBbValTmStr1970", xvm_script_GetBbCurrValueTimeStr1970);
	RegisterHostAPIFunc (-1, "GetBbValTmStr1970MS", xvm_script_GetBbCurrValueTimeStr1970_ms);
	RegisterHostAPIFunc (-1, "GetBbValLong1", xvm_script_GetBbCurrValue1);
	RegisterHostAPIFunc (-1, "GetBbValLong2", xvm_script_GetBbCurrValue2);
	RegisterHostAPIFunc (-1, "SetBbValLong", xvm_script_SetBbCurrValue);
	RegisterHostAPIFunc (-1, "SetBbValLong1", xvm_script_SetBbCurrValue1);
	RegisterHostAPIFunc (-1, "SetBbValLong2", xvm_script_SetBbCurrValue2);
	RegisterHostAPIFunc (-1, "SetBbValStr", xvm_script_SetBbCurrValueString);
	RegisterHostAPIFunc (-1, "SetBbValStrUtf8", xvm_script_SetBbCurrValueStringUtf8);
	RegisterHostAPIFunc (-1, "GetBbValStr", xvm_script_GetBbCurrValueString);
	RegisterHostAPIFunc (-1, "GetBbFdataStr", xvm_script_GetBbFormatDataString);
	RegisterHostAPIFunc (-1, "GetBbFdataFloat", xvm_script_GetBbFormatDataFloat);
	RegisterHostAPIFunc (-1, "GetBbFdataLong", xvm_script_GetBbFormatDataLong);
	RegisterHostAPIFunc (-1, "SetBbValFloat", xvm_script_SetBbCurrValueFloat);
	RegisterHostAPIFunc (-1, "GetBbValFloat", xvm_script_GetBbCurrValueFloat);
	RegisterHostAPIFunc (-1, "SetBbValByte", xvm_script_SetBbCurrValueByte);
	RegisterHostAPIFunc (-1, "GetBbValByte", xvm_script_GetBbCurrValueByte);
	RegisterHostAPIFunc (-1, "BbTranspos", xvm_script_BbTranspos);
	RegisterHostAPIFunc (-1, "LAnd", xvm_script_LAnd);
	RegisterHostAPIFunc (-1, "LOr", xvm_script_LOr);
	RegisterHostAPIFunc (-1, "LNot", xvm_script_LNot);
	RegisterHostAPIFunc (-1, "LComp", xvm_script_LComplement);
	RegisterHostAPIFunc (-1, "LComp2", xvm_script_LComplement2);
	RegisterHostAPIFunc (-1, "LComp1", xvm_script_LComplement1);
	RegisterHostAPIFunc (-1, "LInvs", xvm_script_LInverse);
	RegisterHostAPIFunc (-1, "LInvs2", xvm_script_LInverse2);
	RegisterHostAPIFunc (-1, "LInvs1", xvm_script_LInverse1);
	RegisterHostAPIFunc (-1, "LShift", xvm_script_LShift);
	RegisterHostAPIFunc (-1, "RShift", xvm_script_RShift );
	RegisterHostAPIFunc (-1, "MkWord", xvm_script_MkWord ); 

	RegisterHostAPIFunc (-1, "BcdToHex", xvm_script_BcdToHex );
	RegisterHostAPIFunc (-1, "HexToBcd", xvm_script_HexToBcd ); 

	RegisterHostAPIFunc (-1, "GetYear", xvm_script_GetYear );
	RegisterHostAPIFunc (-1, "GetMonth", xvm_script_GetMonth ); 
	RegisterHostAPIFunc (-1, "GetDay", xvm_script_GetDay );
	RegisterHostAPIFunc (-1, "GetHour", xvm_script_GetHour); 
	RegisterHostAPIFunc (-1, "GetMinute", xvm_script_GetMinute );
	RegisterHostAPIFunc (-1, "GetSecond", xvm_script_GetSecond ); 
	RegisterHostAPIFunc (-1, "GetMSecond", xvm_script_GetMillionSecond ); 
	RegisterHostAPIFunc (-1, "GetSystemTime", xvm_script_GetSystemTime); 

	RegisterHostAPIFunc (-1, "SetBbEnable", xvm_script_SetByteBlockEnable);
	RegisterHostAPIFunc (-1, "SetBbLen", xvm_script_SetByteBlockLength);
	RegisterHostAPIFunc (-1, "GetBbLen", xvm_script_GetByteBlockLength);
	RegisterHostAPIFunc (-1, "SetTimerLong", xvm_script_SetTimerLong);
	RegisterHostAPIFunc (-1, "GetValue", xvm_script_GetValue);
	RegisterHostAPIFunc (-1, "GetValueStr", xvm_script_GetValueString);
	RegisterHostAPIFunc (-1, "SetValueLong", xvm_script_SetValueLong);
	RegisterHostAPIFunc (-1, "SetValueDouble", xvm_script_SetValueDouble);
	RegisterHostAPIFunc (-1, "GetValueDouble", xvm_script_GetValueDouble);
	RegisterHostAPIFunc (-1, "SetValueStr", xvm_script_SetValueString);
	RegisterHostAPIFunc (-1, "SetPkgLen", xvm_script_SetPkgLen);
	RegisterHostAPIFunc (-1, "SetPkgValid", xvm_script_SetPkgValid);
	RegisterHostAPIFunc (-1, "GetPkgLen", xvm_script_GetPkgLen);
	RegisterHostAPIFunc (-1, "GetPkgParsePos", xvm_script_GetPkgParsePos);
	RegisterHostAPIFunc (-1, "GetPkgCurrBufVal", xvm_script_GetPkgCurrBufVal);
	RegisterHostAPIFunc (-1, "GetPkgNum", xvm_script_GetPkgNum);
	RegisterHostAPIFunc (-1, "SetBindDataL", xvm_script_SetBindDataL);
	RegisterHostAPIFunc (-1, "GetNextNdDataByAttr", xvm_script_GetNextDeviceNodeDataByAttrValue);
	RegisterHostAPIFunc (-1, "GetNdDataAttrL", xvm_script_GetDeviceNodeDataAttrValueL);
	RegisterHostAPIFunc (-1, "GetNdDataAttrD", xvm_script_GetDeviceNodeDataAttrValueD);
	RegisterHostAPIFunc (-1, "SetNdDatasAttr", xvm_script_SetDeviceNodeDataAttrs);
	RegisterHostAPIFunc (-1, "SetWBindDataL", xvm_script_SetWBindDataL);
	RegisterHostAPIFunc (-1, "InsertBindData", xvm_script_InsertBindData);
	RegisterHostAPIFunc (-1, "InsertBindDataset", xvm_script_InsertBindDataset);
	RegisterHostAPIFunc (-1, "InsertBindLogicDevice", xvm_script_InsertBindLogicDevice);
	RegisterHostAPIFunc (-1, "GetBindDataL", xvm_script_GetBindDataL);
	RegisterHostAPIFunc (-1, "GetWBindDataL", xvm_script_GetWBindDataL);
	RegisterHostAPIFunc (-1, "SetBindDataD", xvm_script_SetBindDataD);
	RegisterHostAPIFunc (-1, "SetWBindDataD", xvm_script_SetWBindDataD);
	RegisterHostAPIFunc (-1, "GetBindDataD", xvm_script_GetBindDataD);
	RegisterHostAPIFunc (-1, "GetWBindDataD", xvm_script_GetWBindDataD);
	RegisterHostAPIFunc (-1, "GetBindDataStr", xvm_script_GetBindDataStr);
	RegisterHostAPIFunc (-1, "GetWBindDataStr", xvm_script_GetWBindDataStr);
	RegisterHostAPIFunc (-1, "SetBindDataStr", xvm_script_SetBindDataStr);
	RegisterHostAPIFunc (-1, "SetBindDatasetStr", xvm_script_SetBindDatasetStr);
	RegisterHostAPIFunc (-1, "SetBindLogicDeviceStr", xvm_script_SetBindLogicDeviceStr);
	RegisterHostAPIFunc (-1, "GetPkgMaxLen", xvm_script_GetPkgMaxLen);
	RegisterHostAPIFunc (-1, "AdBindDataList", xvm_script_AdBindDataList);
	RegisterHostAPIFunc (-1, "GetMEA", xvm_script_GetMEA);
	RegisterHostAPIFunc (-1, "CalMEA", xvm_script_CalMEA);
	RegisterHostAPIFunc (-1, "FireDataMsg", xvm_script_FireDataChangeMessage);
	RegisterHostAPIFunc (-1, "GetCP24Time2a", xvm_script_GetCP24Time2a);
	RegisterHostAPIFunc (-1, "SetCP24Time2a", xvm_script_SetBbCurrValueCP24Time2a);
	RegisterHostAPIFunc (-1, "GetCP32Time2a", xvm_script_GetCP32Time2a);
	RegisterHostAPIFunc (-1, "SetCP32Time2a", xvm_script_SetBbCurrValueCP32Time2a);
	RegisterHostAPIFunc (-1, "GetCP56Time2a", xvm_script_GetCP56Time2a);
	RegisterHostAPIFunc (-1, "SetCP56Time2a", xvm_script_SetBbCurrValueCP56Time2a);
	RegisterHostAPIFunc (-1, "SetCP56Time2aEx", xvm_script_SetBbCurrValueCP56Time2aEx);
	RegisterHostAPIFunc (-1, "Set48TimeMs", xvm_script_SetBbCurrValue48TimeMs);
	RegisterHostAPIFunc (-1, "BindItemIndex", xvm_script_BindItemIndex);
	RegisterHostAPIFunc (-1, "GetBitInLong16", xvm_script_GetBitInLong16);
	RegisterHostAPIFunc (-1, "SetBitInLong16", xvm_script_SetBitInLong16);
	RegisterHostAPIFunc (-1, "ClearBitInLong16", xvm_script_ClearBitInLong16);
	RegisterHostAPIFunc (-1, "GetBitInLong32", xvm_script_GetBitInLong32);
	RegisterHostAPIFunc (-1, "SetBitInLong32", xvm_script_SetBitInLong32);
	RegisterHostAPIFunc (-1, "ClearBitInLong32", xvm_script_ClearBitInLong32);
	RegisterHostAPIFunc (-1, "GetBitInLong8", xvm_script_GetBitInLong8);
	RegisterHostAPIFunc (-1, "SetBitInLong8", xvm_script_SetBitInLong8);
	RegisterHostAPIFunc (-1, "ClearBitInLong8", xvm_script_ClearBitInLong8);
	RegisterHostAPIFunc (-1, "GetBitRangeInLong8", xvm_script_GetBitRangeInLong8);

	//RegisterHostAPIFunc (-1, "LogPrint", xvm_script_LogPrint);
	RegisterHostAPIFunc (-1, "GetFloatDigit", xvm_script_GetFloatDigit);
	RegisterHostAPIFunc (-1, "GetTimeStr1970", xvm_script_GetTimeStr1970);
	RegisterHostAPIFunc (-1, "GetTimeLong1970", xvm_script_GetTimeLong1970);

	RegisterHostAPIFunc (-1, "RandInRange", xvm_script_RandInRange);
	RegisterHostAPIFunc (-1, "FloatToLong", xvm_script_FloatToLong);
	RegisterHostAPIFunc (-1, "ShowMsg", xvm_script_ShowMsg);
	RegisterHostAPIFunc (-1, "SfCalFloat", xvm_script_SF_ToThreeFloat);
	RegisterHostAPIFunc (-1, "SfGetAna24Float", xvm_script_SF_GetANA24Float);
	RegisterHostAPIFunc (-1, "SfGetBcd24Float", xvm_script_SF_GetBcd24Float);
	RegisterHostAPIFunc (-1, "SfSetBcd24Float", xvm_script_SF_SetBcd24Float);
	RegisterHostAPIFunc (-1, "SfSetBcd24FloatEx", xvm_script_SF_SetBcd24FloatEx);
	RegisterHostAPIFunc (-1, "GetGlobal", xvm_script_GetGlobal);
	RegisterHostAPIFunc (-1, "SetGlobal", xvm_script_SetGlobal);
	//string.find()º¯ÊýÊµÏÖ
	RegisterHostAPIFunc (-1, "StrFind", xvm_script_StrFind);

	RegisterHostAPIFunc (-1, "GetGlobalDouble", xvm_script_GetGlobalDouble);
	RegisterHostAPIFunc (-1, "SetGlobalDouble", xvm_script_SetGlobalDouble);
	RegisterHostAPIFunc (-1, "AddGlobal", xvm_script_AddGlobal);
	RegisterHostAPIFunc (-1, "SubGlobal", xvm_script_SubGlobal);

	RegisterHostAPIFunc (-1, "GetDeviceAddr", xvm_script_GetDeviceAddr);
	RegisterHostAPIFunc (-1, "GetDeviceAttrL", xvm_script_GetDeviceAttrL);
	RegisterHostAPIFunc (-1, "SetDeviceAttrL", xvm_script_SetDeviceAttrL);
	RegisterHostAPIFunc (-1, "GetDeviceAttrStr", xvm_script_GetDeviceAttrStr);
	RegisterHostAPIFunc (-1, "SetDeviceAttrStr", xvm_script_SetDeviceAttrStr);
	RegisterHostAPIFunc (-1, "GetCmmMode", xvm_script_GetCmmMode);
	RegisterHostAPIFunc (-1, "GetPort", xvm_script_GetPort);
	RegisterHostAPIFunc (-1, "GetSystemPara", xvm_script_GetSystemPara);
	RegisterHostAPIFunc (-1, "GetIP", xvm_script_GetIP);
	RegisterHostAPIFunc (-1, "SetPort", xvm_script_SetPort);

	RegisterHostAPIFunc (-1, "IsProcedureExist", xvm_script_IsProcedureExist);
	RegisterHostAPIFunc (-1, "Run", xvm_script_Run);
	RegisterHostAPIFunc (-1, "Connect", xvm_script_Connect);
	RegisterHostAPIFunc (-1, "DisConnect", xvm_script_DisConnect);
	RegisterHostAPIFunc (-1, "GetRemoteIP", xvm_script_GetRemoteIP);
	RegisterHostAPIFunc (-1, "SetPpRunState", xvm_script_SetPpRunState);
	RegisterHostAPIFunc (-1, "SetPpValid", xvm_script_SetPpValid);

	RegisterHostAPIFunc (-1, "GetIEEE754", xvm_script_GetIEEE754);
	RegisterHostAPIFunc (-1, "SetIEEE754", xvm_script_SetIEEE754);
	RegisterHostAPIFunc (-1, "GetASCII", xvm_script_GetASCII);
	RegisterHostAPIFunc (-1, "CrcClear",xvm_script_CrcClear);
	RegisterHostAPIFunc (-1, "CrcPush",xvm_script_CrcPushback);
	RegisterHostAPIFunc (-1, "CrcPushBb",xvm_script_CrcPushbackBb);
	RegisterHostAPIFunc (-1, "CrcCDT",xvm_script_CrcCDT);
	RegisterHostAPIFunc (-1, "CrcSf2000",xvm_script_CrcSfWord);
	RegisterHostAPIFunc (-1, "CrcModbus16",xvm_script_CrcModbus16);

	RegisterHostAPIFunc (-1, "CombineDsPathStr", xvm_script_CombineDsPathStr);
	RegisterHostAPIFunc (-1, "CombineDsPathL", xvm_script_CombineDsPathL);
	RegisterHostAPIFunc (-1, "ClearDsPath", xvm_script_ClearDsPath);
	RegisterHostAPIFunc (-1, "GetDsPath",xvm_script_GetDsPath);
	RegisterHostAPIFunc (-1, "ClearDsDatas",xvm_script_ClearDsDatas);
	RegisterHostAPIFunc (-1, "GetDsDataCount",xvm_script_GetDsDataCount);
	RegisterHostAPIFunc (-1, "InsertDsData",xvm_script_InsertDsData);
	RegisterHostAPIFunc (-1, "InsertDataset", xvm_script_InsertDataset);
	RegisterHostAPIFunc (-1, "InsertLogicDevice", xvm_script_InsertLogicDevice);
	RegisterHostAPIFunc (-1, "InsertDevice", xvm_script_InsertDevice);
	RegisterHostAPIFunc (-1, "InsertDsDataEx",xvm_script_InsertDsDataEx);
	RegisterHostAPIFunc (-1, "InsertDatasetEx", xvm_script_InsertDatasetEx);
	RegisterHostAPIFunc (-1, "InsertLogicDeviceEx", xvm_script_InsertLogicDeviceEx);

	RegisterHostAPIFunc (-1, "SetDsDataL",xvm_script_SetDsDataL);
	RegisterHostAPIFunc (-1, "SetDsDataD",xvm_script_SetDsDataD);
	RegisterHostAPIFunc (-1, "SetDsDataDEx",xvm_script_SetDsDataDEx);
	RegisterHostAPIFunc (-1, "SetDsDataDBatch",xvm_script_SetDsDataDBatch);
	RegisterHostAPIFunc (-1, "SetDsDataStr", xvm_script_SetDsDataStr);
	RegisterHostAPIFunc (-1, "SetDatasetStr", xvm_script_SetDatasetStr);
	RegisterHostAPIFunc (-1, "SetLogicDeviceStr", xvm_script_SetLogicDeviceStr);
	RegisterHostAPIFunc (-1, "GetDsDataL", xvm_script_GetDsDataL);
	RegisterHostAPIFunc (-1, "CountDsData", xvm_script_CountDsData);
	RegisterHostAPIFunc (-1, "CountDsDataEx", xvm_script_CountDsDataEx);
	RegisterHostAPIFunc (-1, "GetSequenceDsDatas", xvm_script_GetSequenceDsDatas);
	RegisterHostAPIFunc (-1, "GetDsDataD", xvm_script_GetDsDataD);
	RegisterHostAPIFunc (-1, "GetDsDataDEx", xvm_script_GetDsDataDEx);
	RegisterHostAPIFunc (-1, "GetDsDataStr",xvm_script_GetDsDataStr);
	RegisterHostAPIFunc (-1, "SumDsDataD", xvm_script_SumDsDataD);
	RegisterHostAPIFunc (-1, "AdDsDataList",xvm_script_AdDsDataList);
	RegisterHostAPIFunc (-1, "AdDsPkgDetail",xvm_script_AdDsPkgDetail);
	RegisterHostAPIFunc (-1, "AdValPkgDetail",xvm_script_AdValPkgDetail);
	RegisterHostAPIFunc (-1, "GetRcvIdle",xvm_script_GetRcvIdle);
	RegisterHostAPIFunc (-1, "GetSendIdle",xvm_script_GetSendIdle);
	RegisterHostAPIFunc (-1, "AddSectionData",xvm_script_AddSectionData);
	RegisterHostAPIFunc (-1, "Fis103SaveRCDFile", xvm_script_Fis103SaveRCDFile);
	RegisterHostAPIFunc (-1, "Fis103SaveCommonFile", xvm_script_Fis103SaveCommonFile);
	RegisterHostAPIFunc (-1, "CreateFile", xvm_script_CreateFile);
	RegisterHostAPIFunc (-1, "WriteFile", xvm_script_WriteFile);
	RegisterHostAPIFunc (-1, "CloseFile", xvm_script_CloseFile);
	RegisterHostAPIFunc (-1, "OpenFile", xvm_script_OpenRcdFile);
	RegisterHostAPIFunc (-1, "ReadFile", xvm_script_ReadRcdFile);
	RegisterHostAPIFunc (-1, "GetFileLen", xvm_script_GetFileLength);
	RegisterHostAPIFunc (-1, "GetFileLeftLen", xvm_script_GetFileLeftLength);
	RegisterHostAPIFunc (-1, "Sleep", xvm_script_Sleep);

	//utf-8
	RegisterHostAPIFunc (-1, "GetBbValStrEx", xvm_script_GetBbCurrValueStringEx);

	RegisterHostAPIFunc (-1, "InitStrTok", xvm_script_InitStrTok);
	RegisterHostAPIFunc (-1, "StrTokCount", xvm_script_StrTokCount);
	RegisterHostAPIFunc (-1, "StrTokIndex", xvm_script_StrTokIndex);
	RegisterHostAPIFunc (-1, "StrTokNext", xvm_script_StrTokNext);

	//2024-7-8  lijunqing 
	RegisterHostAPIFunc (-1, "SetPkgRequiredLen", xvm_script_SetPkgRequiredLen);
}


