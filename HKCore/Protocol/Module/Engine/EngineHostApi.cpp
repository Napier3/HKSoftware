#include "StdAfx.h"
#include "EngineHostApi.h"

#include "ScriptFunc_SF.h"
#include "ScriptFunc_103.h"
#include "ScriptFunc_Engine.h"
#include "ScriptFunc_System.h"

#ifndef _PSX_IDE_QT_
#include "ScriptFunc_File.h"
#endif

#include "../../../Module/XVM/TVMSingle.h"
#include "PpEngineBaseApp.h"
#include "PpEngineDataMngrCntr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//ScriptFunc_103
// 获取带品质描述的被测值
void xvm_script_GetMEA(LPVOID pXvm)//long nIndex, long nBytes);		
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetMEA(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_CalMEA(LPVOID pXvm)//long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_CalMEA(nValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

// 时间函数
void xvm_script_GetCP32Time2a(LPVOID pXvm)//long nIndex, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char *vRet = script_GetCP32Time2a(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_SetBbCurrValueCP32Time2a(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValueCP32Time2a(pSingleVm, nIndex);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetCP24Time2a(LPVOID pXvm)//long nIndex, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char *vRet = script_GetCP24Time2a(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_SetBbCurrValueCP24Time2a(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValueCP24Time2a(pSingleVm, nIndex);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetCP56Time2a(LPVOID pXvm)//long nIndex, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char *vRet = script_GetCP56Time2a(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_SetBbCurrValueCP56Time2a(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValueCP56Time2a(pSingleVm, nIndex);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetBbCurrValueCP56Time2aEx(LPVOID pXvm)//long nIndex, const char *pszDateTime);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	char *pszDateTime = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValueCP56Time2aEx(pSingleVm, nIndex, pszDateTime);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetBbCurrValue48TimeMs(LPVOID pXvm)//long nIndex, const char *pszDateTime);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	char *pszDateTime = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValue48TimeMs(pSingleVm, nIndex, pszDateTime);
	pSingleVm->TS_Return(nParas+1);
}

// 获取IEEE754
void xvm_script_GetIEEE754(LPVOID pXvm)//long nIndex);		
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float fValue = script_GetIEEE754(pSingleVm, nIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, fValue);
}

void xvm_script_SetIEEE754(LPVOID pXvm)//long nIndex, float fValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	float fValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetIEEE754(pSingleVm, nIndex, fValue);
	pSingleVm->TS_Return(nParas+1);
}

// 获取ASCII
void xvm_script_GetASCII(LPVOID pXvm)//long nIndex, long nBytes);		
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char *vRet = script_GetASCII(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

//////////////////////////////////////////////////////////////////////////
//ScriptFunc_Engine.h

//////////////////////////////////////////////////////////////////////////
//设置绑定关系:设置
//ItemIndex
void xvm_script_BindItemIndex(LPVOID pXvm)//long nItemIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_BindItemIndex(pSingleVm, nIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//data
//获取当前关联的数据的数据类型
void xvm_script_GetCurrValueDataType(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetCurrValueDataType(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获取当前关联的数据的数据长度
void xvm_script_GetCurrValueDataLength(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetCurrValueDataLength(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//////////////////////////////////////////////////////////////////////////
//Byte/long
void xvm_script_GetBbCurrValue(LPVOID pXvm)//long nIndex,long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetBbCurrValue(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnInt(nParas+1,vRet);
}

void xvm_script_GetBbCurrValueTimeStr1970(LPVOID pXvm)//long nIndex,long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_GetBbCurrValueTimeStr1970(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnString(nParas+1,vRet);
}

void xvm_script_GetBbCurrValueTimeStr1970_ms(LPVOID pXvm)//long nIndex,long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_GetBbCurrValueTimeStr1970_ms(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnString(nParas+1,vRet);
}

void xvm_script_GetBbCurrValue1(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetBbCurrValue1(pSingleVm, nIndex);
	pSingleVm->TS_ReturnInt(nParas+1,vRet);
}

void xvm_script_GetBbCurrValue2(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetBbCurrValue2(pSingleVm, nIndex);
	pSingleVm->TS_ReturnInt(nParas+1,vRet);
}

//设置当前ByteBlock的缓冲数据  nIndex为索引值，从1开始编号
void xvm_script_SetBbCurrValue(LPVOID pXvm)//long nIndex, long nValue, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(3);
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValue(pSingleVm, nIndex, nValue, nBytes);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetBbCurrValue1(LPVOID pXvm)//long nIndex, long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValue1(pSingleVm, nIndex, nValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetBbCurrValue2(LPVOID pXvm)//long nIndex, long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValue2(pSingleVm, nIndex, nValue);
	pSingleVm->TS_Return(nParas+1);
}

//////////////////////////////////////////////////////////////////////////
//string
void xvm_script_SetBbCurrValueString(LPVOID pXvm)//long nIndex, const char* pString, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(3);
	char* vValue = pSingleVm->TS_GetParamAsString(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValueString(pSingleVm, nIndex, vValue, nBytes);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetBbCurrValueStringUtf8(LPVOID pXvm)//long nIndex, const char* pUtf8String, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(3);
	char* vValue = pSingleVm->TS_GetParamAsString(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValueStringUtf8(pSingleVm, nIndex, vValue, nBytes);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetBbCurrValueString(LPVOID pXvm)//long nIndex, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_GetBbCurrValueString(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_GetBbCurrValueStringEx(LPVOID pXvm)//long nIndex, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_GetBbCurrValueStringEx(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_GetBbFormatDataString(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_GetBbFormatDataString(pSingleVm, nIndex);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_GetBbFormatDataFloat(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = script_GetBbFormatDataFloat(pSingleVm, nIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_GetBbFormatDataLong(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetBbFormatDataLong(pSingleVm, nIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}


//////////////////////////////////////////////////////////////////////////
//float
void xvm_script_SetBbCurrValueFloat(LPVOID pXvm)//long nIndex, float nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	float vValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValueFloat(pSingleVm, nIndex, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetBbCurrValueFloat(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet = script_GetBbCurrValueFloat(pSingleVm, nIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

//////////////////////////////////////////////////////////////////////////
//byte
void xvm_script_SetBbCurrValueByte(LPVOID pXvm)//long nIndex, const char* pString, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(3);
	char* vValue = pSingleVm->TS_GetParamAsString(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBbCurrValueByte(pSingleVm, nIndex, vValue, nBytes);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetBbCurrValueByte(LPVOID pXvm)//long nIndex, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex  = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_GetBbCurrValueByte(pSingleVm, nIndex, nBytes);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_BbTranspos(LPVOID pXvm)//long nIndex1, long nIndex2);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex1  = pSingleVm->TS_GetParamAsInt(2);
	long nIndex2 = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_BbTranspos(pSingleVm, nIndex1, nIndex2);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetDeviceNodeDataAttrValueL(LPVOID pXvm)//const char* pszPath, const char* pszAttrID, long nItemIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath  = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	long nItemIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetDeviceNodeDataAttrValueL(pSingleVm, pszPath, pszAttrID, nItemIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetDeviceNodeDataAttrValueD(LPVOID pXvm)//const char* pszPath, const char* pszAttrID, long nItemIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath  = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	long nItemIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet =  (float)script_GetDeviceNodeDataAttrValueD(pSingleVm, pszPath, pszAttrID, nItemIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_GetNextDeviceNodeDataByAttrValue(LPVOID pXvm)//const char* pszPath, const char* pszAttrID, double dValue, long nCurrIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath  = pSingleVm->TS_GetParamAsString(4);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(3);
	double dValue = pSingleVm->TS_GetParamAsFloat(2);
	long nItemIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetNextDeviceNodeDataByAttrValue(pSingleVm, pszPath, pszAttrID, dValue, nItemIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_SetDeviceNodeDataAttrs(LPVOID pXvm)//const char* pszPath, const char* pszAttrID, double dValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath  = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	double vValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetDeviceNodeDataAttrs(pSingleVm, pszPath, pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetDeviceNodeDataAttr(LPVOID pXvm)//const char* pszPath, const char* pszAttrID, double dValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath  = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	double vValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetDeviceNodeDataAttr(pSingleVm, pszPath, pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}
// 
// BOOL PPS_GetBindData(LPVOID pXvm)//const char* pszAttrID, CString &strValue);
// BOOL PPS_GetWBindData(LPVOID pXvm)//long nIndex, const char* pszAttrID, CString &strValue);

void xvm_script_InsertBindData(LPVOID pXvm)//long nTableRowIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nTableRowIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_InsertBindData(pSingleVm, nTableRowIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_InsertBindDataset(LPVOID pXvm)//long nTableRowIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nTableRowIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_InsertBindDataset(pSingleVm, nTableRowIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_InsertBindLogicDevice(LPVOID pXvm)//long nTableRowIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nTableRowIndex  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_InsertBindLogicDevice(pSingleVm, nTableRowIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetBindDataL(LPVOID pXvm)//const char* pszAttrID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetBindDataL(pSingleVm, pszAttrID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetBindDataD(LPVOID pXvm)//const char* pszAttrID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet =  (float)script_GetBindDataD(pSingleVm, pszAttrID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_GetBindDataStr(LPVOID pXvm)//const char* pszAttrID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	char* vRet = script_GetBindDataStr(pSingleVm, pszAttrID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_GetWBindDataL(LPVOID pXvm)//long nIndex, const char* pszAttrID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(2);
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetWBindDataL(pSingleVm, nIndex, pszAttrID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetWBindDataD(LPVOID pXvm)//long nIndex, const char* pszAttrID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(2);
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet =  (float)script_GetWBindDataD(pSingleVm, nIndex, pszAttrID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_GetWBindDataStr(LPVOID pXvm)//long nIndex, const char* pszAttrID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(2);
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	char* vRet = script_GetWBindDataStr(pSingleVm, nIndex, pszAttrID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

//设置数据绑定的数据的属性值
void xvm_script_SetBindDataL(LPVOID pXvm)//const char* pszAttrID, long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(2);
	long vValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBindDataL(pSingleVm, pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetBindDataD(LPVOID pXvm)//const char* pszAttrID, double dValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(2);
	float vValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBindDataD(pSingleVm, pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetWBindDataL(LPVOID pXvm)//long nIndex, const char* pszAttrID, long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(3);
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(2);
	long vValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetWBindDataL(pSingleVm, nIndex, pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetWBindDataD(LPVOID pXvm)//long nIndex, const char* pszAttrID, double dValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(3);
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(2);
	float vValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetWBindDataD(pSingleVm, nIndex, pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetBindDataStr(LPVOID pXvm)//const char* pszAttrID, const char* pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(2);
	char* vValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBindDataStr(pSingleVm, pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetBindDatasetStr(LPVOID pXvm)//const char* pszAttrID, const char* pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(2);
	char* vValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBindDatasetStr(pSingleVm, pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetBindLogicDeviceStr(LPVOID pXvm)//const char* pszAttrID, const char* pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID  = pSingleVm->TS_GetParamAsString(2);
	char* vValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetBindLogicDeviceStr(pSingleVm, pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

//拷贝数据到链表
void xvm_script_AdBindDataList(LPVOID pXvm)//const char *pszListID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszListID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_AdBindDataList(pSingleVm, pszListID);
	pSingleVm->TS_Return(nParas+1);
}

//数据改变消息
void xvm_script_FireDataChangeMessage(LPVOID pXvm)//long wPara, long lPara);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long wPara  = pSingleVm->TS_GetParamAsInt(2);
	long lPara  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_FireDataChangeMessage(pSingleVm, wPara, lPara);
	pSingleVm->TS_Return(nParas+1);
}


//////////////////////////////////////////////////////////////////////////
//byteblock
void xvm_script_SetByteBlockEnable(LPVOID pXvm)//const char *pszBbID, long nShow);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszBbID  = pSingleVm->TS_GetParamAsString(2);
	long vVlaue  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetByteBlockEnable(pSingleVm, pszBbID, vVlaue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetByteBlockEnable2(LPVOID pXvm)//const char *pszBbID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszBbID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_SetByteBlockEnable2(pSingleVm, pszBbID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_SetByteBlockLength(LPVOID pXvm)//const char *pszBbID, long nLen);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszBbID  = pSingleVm->TS_GetParamAsString(2);
	long vVlaue  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetByteBlockLength(pSingleVm, pszBbID, vVlaue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetByteBlockLength(LPVOID pXvm)//const char *pszBbID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszBbID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetByteBlockLength(pSingleVm, pszBbID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//////////////////////////////////////////////////////////////////////////
// 获取变量值
void xvm_script_GetValue(LPVOID pXvm)//const char *pszVariableID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetValue(pSingleVm, pszVariableID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_Sleep(LPVOID pXvm)//const char *pszVariableID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;

	long nParas = pSingleVm->TS_GetParamAsInt(0);
	int sleep_time = pSingleVm->TS_GetParamAsInt(1);//in ms

	script_Sleep(sleep_time);

	pSingleVm->TS_Return(nParas+1);
}
void xvm_script_GetValueDouble(LPVOID pXvm)//const char *pszVariableID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = script_GetValueDouble(pSingleVm, pszVariableID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_GetValueString(LPVOID pXvm)//const char *pszVariableID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_GetValueString(pSingleVm, pszVariableID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_SetValueLong(LPVOID pXvm)//const char *pszVariableID, long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID  = pSingleVm->TS_GetParamAsString(2);
	long vValue  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetValueLong(pSingleVm, pszVariableID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetValueDouble(LPVOID pXvm)//const char *pszVariableID, double nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID  = pSingleVm->TS_GetParamAsString(2);
	double vValue  = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetValueDouble(pSingleVm, pszVariableID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetValueString(LPVOID pXvm)//const char *pszVariableID, const char *pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID  = pSingleVm->TS_GetParamAsString(2);
	char* vValue  = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetValueString(pSingleVm, pszVariableID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

//报文桢解析匹配长度
void xvm_script_SetPkgLen(LPVOID pXvm)//long nLen);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long vValue  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetPkgLen(pSingleVm, vValue);
	pSingleVm->TS_Return(nParas+1);
}

//报文桢解析匹配长度
void xvm_script_SetPkgRequiredLen(LPVOID pXvm)//long nLen);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long vValue  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetPkgRequiredLen(pSingleVm, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetPkgValid(LPVOID pXvm)//long nValid);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long vValue  = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetPkgValid(pSingleVm, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetPkgLen(LPVOID pXvm)//);	// 当前打包的报文总长度
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet =script_GetPkgLen(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetPkgMaxLen(LPVOID pXvm)//);  //当前规约支持的最大长度
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet =script_GetPkgMaxLen(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetPkgParsePos(LPVOID pXvm)//);	// 当前打包的报文总长度
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet =script_GetPkgParsePos(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetPkgCurrBufVal(LPVOID pXvm)//);	// 当前打包的报文总长度
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long vValue =pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet =script_GetPkgCurrBufVal(pSingleVm, vValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

// 报文编号
void xvm_script_GetPkgNum(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet =script_GetPkgNum(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

// 全局变量
void xvm_script_AddGlobal(LPVOID pXvm)//const char *pszVariableID, long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID = pSingleVm->TS_GetParamAsString(2);
	long vValue =pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_AddGlobal(pSingleVm, pszVariableID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SubGlobal(LPVOID pXvm)//const char *pszVariableID, long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID = pSingleVm->TS_GetParamAsString(2);
	long vValue =pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SubGlobal(pSingleVm, pszVariableID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetGlobal(LPVOID pXvm)//const char *pszVariableID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetGlobal(pSingleVm, pszVariableID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetGlobalDouble(LPVOID pXvm)//const char *pszVariableID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = script_GetGlobalDouble(pSingleVm, pszVariableID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_SetGlobal(LPVOID pXvm)//const char *pszVariableID, long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID = pSingleVm->TS_GetParamAsString(2);
	long vValue =pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetGlobal(pSingleVm, pszVariableID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetGlobalDouble(LPVOID pXvm)//const char *pszVariableID, Double nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID = pSingleVm->TS_GetParamAsString(2);
	double vValue =pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetGlobalDouble(pSingleVm, pszVariableID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

//引擎执行部分
void xvm_script_IsProcedureExist(LPVOID pXvm)//const char *pszProcedureID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszProcedureID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_IsProcedureExist(pSingleVm, pszProcedureID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_Run(LPVOID pXvm)//const char *pszProcedureID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszProcedureID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_Run(pSingleVm, pszProcedureID);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_Connect(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_Connect(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_DisConnect(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_DisConnect(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetPpRunState(LPVOID pXvm)//long nRunState);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nRunState = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetPpRunState(pSingleVm, nRunState);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetPpValid(LPVOID pXvm)//long nValid);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValid = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetPpValid(pSingleVm, nValid);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_CrcClear(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_CrcClear(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_CrcPushback(LPVOID pXvm)//BYTE ch);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	BYTE ch = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_CrcPushback(pSingleVm, ch);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_CrcPushbackBb(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_CrcPushbackBb(pSingleVm, nIndex);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_CrcCDT(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_CrcCDT(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_CrcSfWord(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_CrcSfWord(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_CrcModbus16(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_CrcModbus16(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_CrcModbus1600(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_CrcModbus1600(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_PostConnectFinishedMsg(LPVOID pXvm)//long bConnectFinished);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long bConnectFinished = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_PostConnectFinishedMsg(pSingleVm, bConnectFinished);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}


//数据集操作函数
void xvm_script_CombineDsPathStr(LPVOID pXvm)//const char *pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_CombineDsPathStr(pszValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_CombineDsPathL(LPVOID pXvm)//long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_CombineDsPathL(nValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_ClearDsPath(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_ClearDsPath();
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetDsPath(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	char* vRet = script_GetDsPath();
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_ClearDsDatas(LPVOID pXvm)//const char* pszPath);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_ClearDsDatas(pSingleVm, pszPath);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetDsDataCount(LPVOID pXvm)//const char* pszPath);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetDsDataCount(pSingleVm, pszPath);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_InsertDsData(LPVOID pXvm)//const char* pszPath,long nTableRowIndex, long nItemIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	long nTableRowIndex = pSingleVm->TS_GetParamAsInt(2);
	long nItemIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_InsertDsData(pSingleVm, pszPath,nTableRowIndex,nItemIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_InsertDataset(LPVOID pXvm)//const char* pszPath, long nTableRowIndex, long nItemIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	long nTableRowIndex = pSingleVm->TS_GetParamAsInt(2);
	long nItemIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_InsertDataset(pSingleVm, pszPath,nTableRowIndex,nItemIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_InsertLogicDevice(LPVOID pXvm)//const char* pszPath, long nTableRowIndex, long nItemIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	long nTableRowIndex = pSingleVm->TS_GetParamAsInt(2);
	long nItemIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_InsertLogicDevice(pSingleVm, pszPath,nTableRowIndex,nItemIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_InsertDevice(LPVOID pXvm)//long nDeviceIndex, const char* pszDeviceName);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDeviceIndex = pSingleVm->TS_GetParamAsInt(2);
	char* pszDeviceName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_InsertDevice(pSingleVm, nDeviceIndex,pszDeviceName);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_InsertDsDataEx(LPVOID pXvm)//const char* pszPath,long nTableRowIndex, long nItemIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	char* pszName = pSingleVm->TS_GetParamAsString(2);
	long nItemIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_InsertDsDataEx(pSingleVm, pszPath,pszName,nItemIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_InsertDatasetEx(LPVOID pXvm)//const char* pszPath, long nTableRowIndex, long nItemIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	char* pszName = pSingleVm->TS_GetParamAsString(2);
	long nItemIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_InsertDatasetEx(pSingleVm, pszPath,pszName,nItemIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_InsertLogicDeviceEx(LPVOID pXvm)//const char* pszPath, long nTableRowIndex, long nItemIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	char* pszName = pSingleVm->TS_GetParamAsString(2);
	long nItemIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_InsertLogicDeviceEx(pSingleVm, pszPath,pszName,nItemIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_SetDsDataL(LPVOID pXvm)//const char* pszPath, const char *pszAttrID, long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	long nValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetDsDataL(pSingleVm, pszPath,pszAttrID, nValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetDsDataD(LPVOID pXvm)//const char* pszPath, const char *pszAttrID, double dValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	double vValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetDsDataD(pSingleVm, pszPath,pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetDsDataDEx(LPVOID pXvm)//long nDvIndex, const char* pszPath, const char *pszAttrID, double dValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDvIndex = pSingleVm->TS_GetParamAsInt(4);
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	double vValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetDsDataDEx(pSingleVm, nDvIndex, pszPath,pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetDsDataDBatch(LPVOID pXvm)//const char* pszDatasetID, const char* pszDataID, const char *pszAttrID, double dValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszDatasetID = pSingleVm->TS_GetParamAsString(4);
	char* pszDataID = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	double vValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetDsDataDBatch(pSingleVm, pszDatasetID, pszDataID, pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetDsDataStr(LPVOID pXvm)//const char* pszPath, const char *pszAttrID, const char* pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	char* vValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetDsDataStr(pSingleVm, pszPath,pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetDatasetStr(LPVOID pXvm)//const char* pszPath, const char *pszAttrID, const char* pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	char* vValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetDatasetStr(pSingleVm, pszPath,pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetLogicDeviceStr(LPVOID pXvm)//const char* pszPath, const char *pszAttrID, const char* pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	char* vValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetLogicDeviceStr(pSingleVm, pszPath,pszAttrID, vValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetSequenceDsDatas(LPVOID pXvm)	//const char* pszPath, const char *pszAttrID, const char* pszValue, const char* pszBeginIndexVar
																		//, const char* pszEndIndexVar, long nMaxCount);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(6);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(5);
	char* vValue = pSingleVm->TS_GetParamAsString(4);
	char* pszBeginIndexVar = pSingleVm->TS_GetParamAsString(3);
	char* pszEndIndexVar = pSingleVm->TS_GetParamAsString(2);
	long nMaxCount = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetSequenceDsDatas(pSingleVm, pszPath,pszAttrID, vValue, pszBeginIndexVar, pszEndIndexVar, nMaxCount);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_CountDsData(LPVOID pXvm)//const char* pszPath, const char *pszAttrID, const char* pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(3);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	char* vValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_CountDsData(pSingleVm, pszPath,pszAttrID, vValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_CountDsDataEx(LPVOID pXvm)//const char* pszPath, const char *pszAttrID, const char *pszExpr);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(2);
	char* pszExpr = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_CountDsDataEx(pSingleVm, pszPath,pszExpr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetDsDataL(LPVOID pXvm)//const char* pszPath, const char *pszAttrID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(2);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetDsDataL(pSingleVm, pszPath,pszAttrID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetDsDataD(LPVOID pXvm)//const char* pszPath, const char *pszAttrID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(2);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet = (float)script_GetDsDataD(pSingleVm, pszPath,pszAttrID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_GetDsDataDEx(LPVOID pXvm)//long nDvIndex, const char* pszPath, const char *pszAttrID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDvIndex = pSingleVm->TS_GetParamAsInt(3);
	char* pszPath = pSingleVm->TS_GetParamAsString(2);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet = (float)script_GetDsDataDEx(pSingleVm, nDvIndex, pszPath,pszAttrID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_GetDsDataStr(LPVOID pXvm)//const char* pszPath, const char *pszAttrID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(2);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	char* vRet = script_GetDsDataStr(pSingleVm, pszPath,pszAttrID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_SumDsDataD(LPVOID pXvm)//const char* pszPath, const char *pszAttrID, long nBeginDvIndex, long nEndDvIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(4);
	char* pszAttrID = pSingleVm->TS_GetParamAsString(3);
	long nBeginDvIndex = pSingleVm->TS_GetParamAsInt(2);
	long nEndDvIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet = (float)script_SumDsDataD(pSingleVm, pszPath,pszAttrID, nBeginDvIndex, nEndDvIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_AdDsDataList(LPVOID pXvm)//const char* pszPath, const char *pszListID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(2);
	char* pszListID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_AdDsDataList(pSingleVm, pszPath,pszListID);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_AdDsPkgDetail(LPVOID pXvm)//const char* pszPath);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_AdDsPkgDetail(pSingleVm, pszPath);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_AdValPkgDetail(LPVOID pXvm)//const char* pszName, const char *pszID, const char *pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszName = pSingleVm->TS_GetParamAsString(3);
	char *pszID = pSingleVm->TS_GetParamAsString(2);
	char *pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_AdValPkgDetail(pSingleVm, pszName, pszID, pszValue);
	pSingleVm->TS_Return(nParas+1);
}


void xvm_script_SF_GetANA24Float(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet = script_SF_GetANA24Float(pSingleVm, nIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_SF_GetANA32Float(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet = script_SF_GetANA32Float(pSingleVm, nIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_SF_GetBcd24Float(LPVOID pXvm)//long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet = script_SF_GetBcd24Float(pSingleVm, nIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_SF_SetBcd24Float(LPVOID pXvm)//float fValue, long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	float fValue = pSingleVm->TS_GetParamAsFloat(2);
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SF_SetBcd24Float(pSingleVm, fValue, nIndex);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SF_SetBcd24FloatEx(LPVOID pXvm)//float fValue, long nIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	float fValue = pSingleVm->TS_GetParamAsFloat(2);
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SF_SetBcd24FloatEx(pSingleVm, fValue, nIndex);
	pSingleVm->TS_Return(nParas+1);
}


//发送报文、接收报文的时间间隔函数
void xvm_script_GetRcvIdle(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetRcvIdle(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetSendIdle(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetSendIdle(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//////////////////////////////////////////////////////////////////////////
//ScriptFunc_File.h
void xvm_script_AddSectionData(LPVOID pXvm)//long nIndex, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

#ifndef _PSX_IDE_QT_
    script_AddSectionData(pSingleVm, nIndex, nBytes);
#endif
    pSingleVm->TS_Return(nParas+1);
}

void xvm_script_Fis103SaveRCDFile(LPVOID pXvm)//const char* strPath, long nFileNameLen);			//保存录波文件
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* strPath = pSingleVm->TS_GetParamAsString(2);
	long nFileNameLen = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

#ifndef _PSX_IDE_QT_
    script_Fis103SaveRCDFile(pSingleVm, strPath, nFileNameLen);
#endif
    pSingleVm->TS_Return(nParas+1);
}

void xvm_script_Fis103SaveCommonFile(LPVOID pXvm)//const char* strPath, long nFileNameLen);			//保存普通文件
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* strPath = pSingleVm->TS_GetParamAsString(2);
	long nFileNameLen = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

#ifndef _PSX_IDE_QT_
    script_Fis103SaveCommonFile(pSingleVm, strPath, nFileNameLen);
#endif
    pSingleVm->TS_Return(nParas+1);
}

void xvm_script_CreateFile(LPVOID pXvm)//, const char *pszPath, const char* pszFileName);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* strPath = pSingleVm->TS_GetParamAsString(2);
	char* pszFileName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

#ifndef _PSX_IDE_QT_
    script_CreateFile(pSingleVm, strPath, pszFileName);
#endif
    pSingleVm->TS_Return(nParas+1);
}

void xvm_script_WriteFile(LPVOID pXvm)//, long nIndex, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

#ifndef _PSX_IDE_QT_
    script_WriteFile(pSingleVm, nIndex, nBytes);
#endif
    pSingleVm->TS_Return(nParas+1);
}

void xvm_script_CloseFile(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

#ifndef _PSX_IDE_QT_
    script_CloseFile(pSingleVm);
#endif
    pSingleVm->TS_Return(nParas+1);
}

void xvm_script_OpenRcdFile(LPVOID pXvm)//, const char *pszPathPath, const char *pszFileName);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* strPath = pSingleVm->TS_GetParamAsString(2);
	char* pszFileName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

#ifndef _PSX_IDE_QT_
	script_OpenRcdFile(pSingleVm, strPath, pszFileName);
#endif
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_ReadRcdFile(LPVOID pXvm)//, long nIndex, long nBytes);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(2);
	long nBytes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

#ifndef _PSX_IDE_QT_
	script_ReadRcdFile(pSingleVm, nIndex, nBytes);
#endif
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_GetFileLength(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* strPath = pSingleVm->TS_GetParamAsString(2);
	char* pszFileName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);
	long nLen = 0;

#ifndef _PSX_IDE_QT_
	nLen = script_GetFileLength(pSingleVm);
#endif

	pSingleVm->TS_ReturnInt(nParas+1, nLen);
}

void xvm_script_GetFileLeftLength(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* strPath = pSingleVm->TS_GetParamAsString(2);
	char* pszFileName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);
	long nLen = 0;

#ifndef _PSX_IDE_QT_
	nLen = script_GetFileLeftLength(pSingleVm);
#endif

	pSingleVm->TS_ReturnInt(nParas+1, nLen);
}



//////////////////////////////////////////////////////////////////////////
//ScriptFunc_SF.h
void xvm_script_SF_ToThreeFloat(LPVOID pXvm)//FLOAT fData);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	float fData = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_SF_ToThreeFloat(fData);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//////////////////////////////////////////////////////////////////////////
//ScriptFunc_System.h
//logic
void xvm_script_LAnd(LPVOID pXvm)//long nVal1, long nVal2);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal1 = pSingleVm->TS_GetParamAsInt(2);
	long nVal2 = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_LAnd(nVal1, nVal2);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_LOr(LPVOID pXvm)//long nVal1, long nVal2);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal1 = pSingleVm->TS_GetParamAsInt(2);
	long nVal2 = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_LOr(nVal1, nVal2);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_LNot(LPVOID pXvm)//long nVal);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal1 = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_LNot(nVal1);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_LComplement(LPVOID pXvm)//long nVal);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_LComplement(nVal);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_LComplement2(LPVOID pXvm)//short nVal);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_LComplement2((short)nVal);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_LComplement1(LPVOID pXvm)//char nVal);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_LComplement1((char)nVal);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_LInverse(LPVOID pXvm)//long nVal);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_LInverse(nVal);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_LInverse2(LPVOID pXvm)//short nVal);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_LInverse2((short)nVal);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_LInverse1(LPVOID pXvm)//char nVal);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_LInverse1((char)nVal);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}
// 
// void xvm_script_LRComplement(LPVOID pXvm)//long nVal);
// {
// 	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
// 	long nVal = pSingleVm->TS_GetParamAsInt(1);
// 	long nParas = pSingleVm->TS_GetParamAsInt(0);
// 
// 	long vRet = script_LComplement(nVal);
// 	pSingleVm->TS_ReturnInt(nParas+1, vRet);
// }


//bit
void xvm_script_LShift(LPVOID pXvm)//long nVal, long nShift);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal = pSingleVm->TS_GetParamAsInt(2);
	long nShift = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_LShift(nVal, nShift);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_RShift(LPVOID pXvm)//long nVal, long nShift);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal = pSingleVm->TS_GetParamAsInt(2);
	long nShift = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_RShift(nVal, nShift);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_MkWord(LPVOID pXvm)//long nHigh, long nLow);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nHigh = pSingleVm->TS_GetParamAsInt(2);
	long nLow = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_MkWord(nHigh, nLow);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//time
void xvm_script_GetYear(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetYear();
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetMonth(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetMonth();
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetDay(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetDay();
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetHour(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetHour();
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetMinute(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetMinute();
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetSecond(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetSecond();
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetMillionSecond(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetMillionSecond();
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetSystemTime(LPVOID pXvm)//);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_GetSystemTime();
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

//BCD/HEX
void xvm_script_BcdToHex(LPVOID pXvm)//long nVal);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_BcdToHex(nVal);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_HexToBcd(LPVOID pXvm)//long nVal);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nVal = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_HexToBcd(nVal);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_StrBcdToHex(LPVOID pXvm)//const char* pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_StrBcdToHex(pszValue);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_StrHexToBcd(LPVOID pXvm)//const char*);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_StrHexToBcd(pszValue);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}


//系统相关的函数
void xvm_script_GetIP(LPVOID pXvm)//const char *pszTcpOrUdp);    //获取设备的IP地址
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszTcpOrUdp = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	//long vRet = script_GetIP(pSingleVm, pszTcpOrUdp);
	//pSingleVm->TS_ReturnInt(nParas+1, vRet);
	const char* vRet = script_GetIP(pSingleVm, pszTcpOrUdp);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_GetRemoteIP(LPVOID pXvm)//const char *pszTcpOrUdp);    //获取远程的IP地址
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszTcpOrUdp = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetRemoteIP(pSingleVm, pszTcpOrUdp);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetDeviceAddr(LPVOID pXvm)//);   //获取设备地址
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetDeviceAddr(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetDeviceAttrL(LPVOID pXvm)//const char* pszAttrID);   //获取设备地址
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetDeviceAttrL(pSingleVm, pszAttrID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetDeviceAttrStr(LPVOID pXvm)//const char* pszAttrID);   //获取设备地址
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_GetDeviceAttrStr(pSingleVm, pszAttrID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_GetCmmMode(LPVOID pXvm)//);   //获取通讯模式
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetCmmMode(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetPort(LPVOID pXvm)//const char *pszCmmMode);  //获取通讯的端口
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszCmmMode = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetPort(pSingleVm, pszCmmMode);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_SetPort(LPVOID pXvm)//long nPort
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nPort= pSingleVm->TS_GetParamAsInt(2);
	char* pszTcpOrUdp = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_SetPort(pSingleVm, pszTcpOrUdp, nPort);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetSystemPara(LPVOID pXvm)//const char* pszParaID);   //获取系统的参数
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszParaID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetSystemPara(pSingleVm, pszParaID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_SetDeviceAttrL(LPVOID pXvm)//const char* pszAttrID, long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	long nValue= pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_SetDeviceAttrL(pSingleVm, pszAttrID, nValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_SetDeviceAttrStr(LPVOID pXvm)//const char* pszAttrID, const char *pszValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszAttrID = pSingleVm->TS_GetParamAsString(2);
	char *pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_SetDeviceAttrStr(pSingleVm, pszAttrID, pszValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//timer
void xvm_script_KillTimer(LPVOID pXvm)//const char *pszTimerID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszTimerID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_KillTimer(pszTimerID);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_ResetTimer(LPVOID pXvm)//const char *pszTimerID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszTimerID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_ResetTimer(pszTimerID);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_SetTimerLong(LPVOID pXvm)//const char *pszTimerID, long nMs);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszTimerID = pSingleVm->TS_GetParamAsString(2);
	long nMs = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_SetTimerLong(pszTimerID, nMs);
	pSingleVm->TS_Return(nParas+1);
}


void xvm_script_GetBitInLong(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetBitInLong(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_SetBitInLong(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_SetBitInLong(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_ClearBitInLong(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_ClearBitInLong(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetBitInLong16(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetBitInLong16(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_SetBitInLong16(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_SetBitInLong16(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_ClearBitInLong16(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_ClearBitInLong16(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}


void xvm_script_GetBitInLong32(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetBitInLong32(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_SetBitInLong32(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_SetBitInLong32(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_ClearBitInLong32(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_ClearBitInLong32(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetBitInLong8(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetBitInLong8(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_SetBitInLong8(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_SetBitInLong8(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_ClearBitInLong8(LPVOID pXvm)//long nValue, long nBitIndex);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(2);
	long nBitIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_ClearBitInLong8(nValue, nBitIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_GetBitRangeInLong8(LPVOID pXvm)//long nValue, long nBitStart, long nBitEnd);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(3);
	long nBitStart = pSingleVm->TS_GetParamAsInt(2);
	long nBitEnd = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetBitRangeInLong8(nValue, nBitStart, nBitEnd);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_LogPrint(LPVOID pXvm)//const char *pszVariableID,long nValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID = pSingleVm->TS_GetParamAsString(2);
	long nValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_LogPrint(pszVariableID, nValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_ShowMsg(LPVOID pXvm)//const char *pszMsg);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszMsg = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	script_ShowMsg(pszMsg);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_script_RandInRange(LPVOID pXvm)//(float fMinVal, float fMaxValue);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	float fMinVal = pSingleVm->TS_GetParamAsFloat(2);
	float fMaxValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet = script_RandInRange(fMinVal, fMaxValue);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_script_FloatToLong(LPVOID pXvm)//(float fVal);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	float fValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_FloatToLong(fValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获取指定数位的数值
void xvm_script_GetFloatDigit(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	float fValue = pSingleVm->TS_GetParamAsFloat(2);
	 long nDigit = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetFloatDigit(fValue, nDigit);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//时间转换函数
void xvm_script_GetTimeStr1970(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nSeconds = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = script_GetTimeStr1970(pSingleVm, nSeconds);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_GetTimeLong1970(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszTime = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = script_GetTimeLong1970(pszTime);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_StrFind(LPVOID pXvm)//const char *pszVariableID, const char *pszVariableID);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszVariableID = pSingleVm->TS_GetParamAsString(2);
	char *pszVariableID0 = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	
	long vRet = script_StrFind(pszVariableID, pszVariableID0);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_InitStrTok(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	CPpEngineData *pEngineData = (CPpEngineData*)pSingleVm->m_pRefData;
	ASSERT( pEngineData != NULL );

	char *pszString = pSingleVm->TS_GetParamAsString(2);
	char *pControl = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = pEngineData->PPS_InitStrTok(pszString, pControl);

	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_StrTokCount(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	CPpEngineData *pEngineData = (CPpEngineData*)pSingleVm->m_pRefData;
	ASSERT( pEngineData != NULL );

	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = pEngineData->PPS_StrTokCount();

	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_script_StrTokIndex(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	CPpEngineData *pEngineData = (CPpEngineData*)pSingleVm->m_pRefData;
	ASSERT( pEngineData != NULL );

	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = pEngineData->PPS_StrTokIndex(nIndex);

	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_script_StrTokNext(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	CPpEngineData *pEngineData = (CPpEngineData*)pSingleVm->m_pRefData;
	ASSERT( pEngineData != NULL );

	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = pEngineData->PPS_StrTokNext();

	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

// 
// long GBS_InitStrTok(char *pszString, char *pControl);
// long GBS_StrTokCount();
// const char* GBS_StrTokIndex(long nIndex);
// const char* GBS_StrTokNext();
