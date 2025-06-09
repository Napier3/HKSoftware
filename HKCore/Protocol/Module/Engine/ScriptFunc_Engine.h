#pragma once

#include "BbData.h"
#include "WBbData.h"
#include "RBbData.h"

class CPpTemplate;
class CTScriptSingleVM;

extern long g_bLogBindQueryErrorInfor;

//////////////////////////////////////////////////////////////////////////
//设置绑定关系:设置
//ItemIndex
long script_BindItemIndex(CTScriptSingleVM *pXvm,long nItemIndex);

//data
//获取当前关联的数据的数据类型
long script_GetCurrValueDataType(CTScriptSingleVM *pXvm);

//获取当前关联的数据的数据长度
long script_GetCurrValueDataLength(CTScriptSingleVM *pXvm);

//////////////////////////////////////////////////////////////////////////
//Byte/long
long script_GetBbValLong10(long nIndex,long nBytes);
void script_SetBbValLong10(long nIndex,long nValue,long nBytes);

long script_GetBbCurrValue(CTScriptSingleVM *pXvm, long nIndex,long nBytes);
long script_GetBbCurrValue1(CTScriptSingleVM *pXvm, long nIndex);
long script_GetBbCurrValue2(CTScriptSingleVM *pXvm, long nIndex);
const char* script_GetBbCurrValueTimeStr1970(CTScriptSingleVM *pXvm, long nIndex,long nBytes);
const char* script_GetBbCurrValueTimeStr1970_ms(CTScriptSingleVM *pXvm, long nIndex,long nBytes);

//设置当前ByteBlock的缓冲数据  nIndex为索引值，从1开始编号
void script_SetBbCurrValue(CTScriptSingleVM *pXvm, long nIndex, long nValue, long nBytes);
void script_SetBbCurrValue1(CTScriptSingleVM *pXvm, long nIndex, long nValue);
void script_SetBbCurrValue2(CTScriptSingleVM *pXvm, long nIndex, long nValue);

//////////////////////////////////////////////////////////////////////////
//string
void script_SetBbCurrValueString(CTScriptSingleVM *pXvm, long nIndex, const char* pString, long nBytes);
void script_SetBbCurrValueStringUtf8(CTScriptSingleVM *pXvm, long nIndex, const char* pUft8String, long nBytes);
const char* script_GetBbCurrValueString(CTScriptSingleVM *pXvm, long nIndex, long nBytes);
const char* script_GetBbCurrValueStringEx(CTScriptSingleVM *pXvm, long nIndex, long nBytes);

const char* script_GetBbFormatDataString(CTScriptSingleVM *pXvm, long nIndex);
double script_GetBbFormatDataFloat(CTScriptSingleVM *pXvm, long nIndex);
long script_GetBbFormatDataLong(CTScriptSingleVM *pXvm, long nIndex);

//////////////////////////////////////////////////////////////////////////
//float
void script_SetBbCurrValueFloat(CTScriptSingleVM *pXvm, long nIndex, float nValue);
float script_GetBbCurrValueFloat(CTScriptSingleVM *pXvm, long nIndex);
float script_GetBbCurrValueFloatDM05();
long script_GetBbCurrValueLongFromASCII();
void script_SetBbCurrValueLongToASCII(long nValue);

//////////////////////////////////////////////////////////////////////////
//byte
void script_SetBbCurrValueByte(CTScriptSingleVM *pXvm, long nIndex, const char* pString, long nBytes);
const char* script_GetBbCurrValueByte(CTScriptSingleVM *pXvm, long nIndex, long nBytes);

void script_BbTranspos(CTScriptSingleVM *pXvm, long nIndex1, long nIndex2);


//获取数据绑定的数据的属性
CExBaseObject* PPS_GetBindDeviceNodeData(CTScriptSingleVM *pXvm, const char* pszAttrID);
CExBaseObject* PPS_GetBindDeviceDataNode(CTScriptSingleVM *pXvm);

CString script_GetDeviceNodeDataAttrValueString(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, long nItemIndex);
long script_GetDeviceNodeDataAttrValueL(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, long nItemIndex);
double script_GetDeviceNodeDataAttrValueD(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, long nItemIndex);
long script_GetNextDeviceNodeDataByAttrValue(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, double dValue, long nCurrIndex);
void script_SetDeviceNodeDataAttrs(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, double dValue);
void script_SetDeviceNodeDataAttr(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, double dValue);

BOOL PPS_GetBindData(CTScriptSingleVM *pXvm, const char* pszAttrID, CString &strValue);
BOOL PPS_GetWBindData(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID, CString &strValue);

long script_InsertBindData(CTScriptSingleVM *pXvm, long nTableRowIndex);
long script_InsertBindDataset(CTScriptSingleVM *pXvm, long nTableRowIndex);
long script_InsertBindLogicDevice(CTScriptSingleVM *pXvm, long nTableRowIndex);
long script_GetBindDataL(CTScriptSingleVM *pXvm, const char* pszAttrID);
double script_GetBindDataD(CTScriptSingleVM *pXvm, const char* pszAttrID);
char* script_GetBindDataStr(CTScriptSingleVM *pXvm, const char* pszAttrID);
long script_GetWBindDataL(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID);
double script_GetWBindDataD(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID);
char* script_GetWBindDataStr(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID);

//设置数据绑定的数据的属性值
void script_SetBindDataL(CTScriptSingleVM *pXvm, const char* pszAttrID, long nValue);
void script_SetBindDataD(CTScriptSingleVM *pXvm, const char* pszAttrID, double dValue);

void script_SetWBindDataL(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID, long nValue);
void script_SetWBindDataD(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID, double dValue);

void script_SetBindDataStr(CTScriptSingleVM *pXvm, const char* pszAttrID, const char* pszValue);
void script_SetBindDatasetStr(CTScriptSingleVM *pXvm, const char* pszAttrID, const char* pszValue);
void script_SetBindLogicDeviceStr(CTScriptSingleVM *pXvm, const char* pszAttrID, const char* pszValue);
BOOL PPS_SetBindData(CTScriptSingleVM *pXvm, const char* pszAttrID, CString &strValue);
BOOL PPS_SetWBindData(CTScriptSingleVM *pXvm, long nIndex,const char* pszAttrID, CString &strValue);
void PPS_CalBindData(CTScriptSingleVM *pXvm, CExBaseObject *pDvNodeData, CString &strValue, const CString &strScriptID);

//拷贝数据到链表
void script_AdBindDataList(CTScriptSingleVM *pXvm, const char *pszListID);
void script_AddReceivePkgList(const char* pszListID,const char* pszReceivePkgName,const char* pszReceivePkgID);

//数据改变消息
void script_FireDataChangeMessage(CTScriptSingleVM *pXvm, long wPara, long lPara);


//////////////////////////////////////////////////////////////////////////
//byteblock
void script_SetByteBlockEnable(CTScriptSingleVM *pXvm, const char *pszBbID, long nShow);
long script_SetByteBlockEnable2(CTScriptSingleVM *pXvm, const char *pszBbID);
void script_SetByteBlockLength(CTScriptSingleVM *pXvm, const char *pszBbID, long nLen);
long script_GetByteBlockLength(CTScriptSingleVM *pXvm, const char *pszBbID);

//////////////////////////////////////////////////////////////////////////
// 获取变量值
long script_GetValue(CTScriptSingleVM *pXvm, const char *pszVariableID);
double script_GetValueDouble(CTScriptSingleVM *pXvm, const char *pszVariableID);
const char* script_GetValueString(CTScriptSingleVM *pXvm, const char *pszVariableID);
void script_SetValueLong(CTScriptSingleVM *pXvm, const char *pszVariableID, long nValue);
void script_SetValueDouble(CTScriptSingleVM *pXvm, const char *pszVariableID, double nValue);
void script_SetValueString(CTScriptSingleVM *pXvm, const char *pszVariableID, const char *pszValue);

//报文桢解析匹配长度
void script_SetPkgLen(CTScriptSingleVM *pXvm, long nLen);
void script_SetPkgValid(CTScriptSingleVM *pXvm, long nValid);
void script_SetPkgRequiredLen(CTScriptSingleVM *pXvm, long nLen);

long script_GetPkgLen(CTScriptSingleVM *pXvm);	// 当前打包的报文总长度
long script_GetPkgMaxLen(CTScriptSingleVM *pXvm);  //当前规约支持的最大长度
long script_GetPkgParsePos(CTScriptSingleVM *pXvm);	// 当前打包的报文总长度
long script_GetPkgCurrBufVal(CTScriptSingleVM *pXvm, long nOffset);	// 当前报文缓冲区的值

// 报文编号
long script_GetPkgNum(CTScriptSingleVM *pXvm);
CByteBlock* PPS_GetByteBlock(CExBaseObject *pEngineData);
CPpScript* PPS_GetPpScript(CTScriptSingleVM *pXvm);

// 全局变量
void script_AddGlobal(CTScriptSingleVM *pXvm, const char *pszVariableID, long nValue);
void script_SubGlobal(CTScriptSingleVM *pXvm, const char *pszVariableID, long nValue);
long script_GetGlobal(CTScriptSingleVM *pXvm, const char *pszVariableID);
long script_GetGlobalEx(const char *pszVariableID, CExBaseObject *pPpObj);
long script_GetGlobalEx(const CString &strVariableID, CExBaseObject *pPpObj);
long script_GetGlobalEx(const CString &strVariableID, CPpTemplate *pTemplate);
void script_SetGlobal(CTScriptSingleVM *pXvm, const char *pszVariableID, long nValue);
double script_GetGlobalDouble(CTScriptSingleVM *pXvm, const char *pszVariableID);
void script_SetGlobalDouble(CTScriptSingleVM *pXvm, const char *pszVariableID, double nValue);
void script_AddGlobalDouble(CTScriptSingleVM *pXvm, const char *pszVariableID, double nValue);

//引擎执行部分
long script_IsProcedureExist(CTScriptSingleVM *pXvm, const char *pszProcedureID);
void script_Run(CTScriptSingleVM *pXvm, const char *pszProcedureID);
void script_Connect(CTScriptSingleVM *pXvm);
void script_DisConnect(CTScriptSingleVM *pXvm);
void script_SetPpRunState(CTScriptSingleVM *pXvm, long nRunState);
void script_SetPpValid(CTScriptSingleVM *pXvm, long nValid);

void script_CrcClear(CTScriptSingleVM *pXvm);
void script_CrcPushback(CTScriptSingleVM *pXvm, BYTE ch);
void script_CrcPushbackBb(CTScriptSingleVM *pXvm, long nIndex);
BYTE script_CrcCDT(CTScriptSingleVM *pXvm);
WORD script_CrcSfWord(CTScriptSingleVM *pXvm);
long script_CrcModbus16(CTScriptSingleVM *pXvm);
long script_CrcModbus1600(CTScriptSingleVM *pXvm);
long script_XOrVector();

long script_PostConnectFinishedMsg(CTScriptSingleVM *pXvm, long bConnectFinished);


//数据集操作函数
void script_CombineDsPathStr(const char *pszValue);
void script_CombineDsPathL(long nValue);
void script_ClearDsPath();
char* script_GetDsPath();

long script_ClearDsDatas(CTScriptSingleVM *pXvm, const char* pszPath);
long script_GetDsDataCount(CTScriptSingleVM *pXvm, const char* pszPath);
long script_InsertDsData(CTScriptSingleVM *pXvm, const char* pszPath,long nTableRowIndex, long nItemIndex);
long script_InsertDataset(CTScriptSingleVM *pXvm, const char* pszPath, long nTableRowIndex, long nItemIndex);
long script_InsertLogicDevice(CTScriptSingleVM *pXvm, const char* pszPath, long nTableRowIndex, long nItemIndex);
long script_InsertDevice(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszDeviceName);
long script_InsertDsDataEx(CTScriptSingleVM *pXvm, const char* pszPath,const char *pszName, long nItemIndex);
long script_InsertDatasetEx(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszName, long nItemIndex);
long script_InsertLogicDeviceEx(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszName, long nItemIndex);

void script_SetDsDataL(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, long nValue);
void script_SetDsDataD(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, double dValue);
void script_SetDsDataDEx(CTScriptSingleVM *pXvm, long nDvIndex, const char* pszPath, const char *pszAttrID, double dValue);
void script_SetDsDataDBatch(CTScriptSingleVM *pXvm, const char* pszDatasetID, const char* pszDataID, const char *pszAttrID, double dValue);
void script_SetDsDataStr(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, const char* pszValue);
void script_SetDatasetStr(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, const char* pszValue);
void script_SetLogicDeviceStr(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, const char* pszValue);

long script_GetSequenceDsDatas(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, const char* pszValue, const char* pszBeginIndexVar, const char* pszEndIndexVar, long nMaxCount);
long script_CountDsData(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, const char* pszValue);
long script_CountDsDataEx(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszExprs);
long script_GetDsDataL(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID);
double script_GetDsDataD(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID);
double script_GetDsDataDEx(CTScriptSingleVM *pXvm, long nDvIndex, const char* pszPath, const char *pszAttrID);
char* script_GetDsDataStr(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID);
double script_SumDsDataD(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, long nBeginDvIndex, long nEndDvIndex);


void script_AdDsDataList(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszListID);
void script_AdDsPkgDetail(CTScriptSingleVM *pXvm, const char* pszPath);
void script_AdValPkgDetail(CTScriptSingleVM *pXvm, const char* pszName, const char *pszID, const char *pszValue);


float script_SF_GetANA24Float(CTScriptSingleVM *pXvm, long nIndex);
float script_SF_GetANA32Float(CTScriptSingleVM *pXvm, long nIndex);
float script_SF_GetBcd24Float(CTScriptSingleVM *pXvm, long nIndex);
void script_SF_SetBcd24Float(CTScriptSingleVM *pXvm, float fValue, long nIndex);
void script_SF_SetBcd24FloatEx(CTScriptSingleVM *pXvm, float fValue, long nIndex);


//发送报文、接收报文的时间间隔函数
long script_GetRcvIdle(CTScriptSingleVM *pXvm);
long script_GetSendIdle(CTScriptSingleVM *pXvm);
//strfind
long script_StrFind(const char *pszVariableID, const char *pszVariableID0);
