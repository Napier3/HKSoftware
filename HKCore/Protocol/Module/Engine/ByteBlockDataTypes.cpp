#include "StdAfx.h"
#include "ByteBlockDataTypes.h"
#include "PpGlobalDefine.h"
#include "../XLanguageResourcePp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CByteBlockDataTypes::CByteBlockDataTypes(void)
{
}

CByteBlockDataTypes::~CByteBlockDataTypes(void)
{
	DeleteAll();
}


void CByteBlockDataTypes::InitByTemplate(const CString &strEncodeMode)
{
	DeleteAll();

	AddNew(g_sLangTxt_Constant, g_strBbDataTypeConst);
 	AddNew(g_sLangTxt_FormatText/*g_strBbDataTypeTextName*/, g_strBbDataTypeText);
	AddNew(g_sLangTxt_Script/*g_strBbDataTypeVariableName*/, g_strBbDataTypeVariable);
	//AddNew(g_strBbDataTypeRangeName, g_strBbDataTypeRang);
	//AddNew(g_strBbDataTypeListName, g_strBbDataTypeList);
	AddNew(g_sLangTxt_SumCheck/*g_strBbDataTypeSumCheckName*/, g_strBbDataTypeSumCheck);
	AddNew(g_sLangTxt_CRCCheck/*g_strBbDataTypeCrcCheckName*/, g_strBbDataTypeCrcCheck);
	AddNew(g_sLangTxt_CRCCheck2/*g_strBbDataTypeCrcCheckFFName*/, g_strBbDataTypeCrcCheckFF);
	AddNew(g_sLangTxt_CRCCheck3/*g_strBbDataTypeCrcCheckTableName*/, g_strBbDataTypeCrcCheckTable);


	//if (strEncodeMode == g_strEncodeModeSendName)
	if(strEncodeMode == g_strEncodeModeSend)
	{
		AddNew(g_sLangTxt_EncodeModeSendName/*g_strEncodeModeDataTypeSendName*/, g_strEncodeModeDataTypeSendID);
	}
	else if (strEncodeMode == g_strEncodeModeReceive)
	{
		AddNew(g_sLangTxt_EncodeModeReceiveName/*g_strEncodeModeDataTypeReceiveName*/, g_strEncodeModeDataTypeReceiveID);
	}
	//else if (strEncodeMode == g_strEncodeModeSOrRName)
	else if(strEncodeMode == g_strEncodeModeSOrR)
	{
		AddNew(g_sLangTxt_EncodeModeSendName/*g_strEncodeModeDataTypeSendName*/, g_strEncodeModeDataTypeSendID);
		AddNew(g_sLangTxt_EncodeModeReceiveName/*g_strEncodeModeDataTypeReceiveName*/, g_strEncodeModeDataTypeReceiveID);
	}
	else if (strEncodeMode == g_strEncodeModeSAndR)
	{
		AddNew(g_sLangTxt_EncodeName/*g_strEncodeModeDataTypeEncodeName*/, g_strEncodeModeDataTypeEncodeID);
	}
}


CPpTemplateEncodeModes::CPpTemplateEncodeModes(void)
{
	AddNew(g_sLangTxt_EncodeModeNoneName/*g_strEncodeModeNoneName*/, g_strEncodeModeNone);
	AddNew(g_sLangTxt_EncodeModeSendName/*g_strEncodeModeSendName*/, g_strEncodeModeSend);
	AddNew(g_sLangTxt_EncodeModeReceiveName /*g_strEncodeModeReceiveName*/, g_strEncodeModeReceive);
	AddNew(g_sLangTxt_EncodeModeSAndRName/*g_strEncodeModeSAndRName*/, g_strEncodeModeSAndR);
	AddNew(g_sLangTxt_EncodeModeSOrRName/*g_strEncodeModeSOrRName*/, g_strEncodeModeSOrR);
}

CPpTemplateEncodeModes::~CPpTemplateEncodeModes(void)
{
	DeleteAll();
}
