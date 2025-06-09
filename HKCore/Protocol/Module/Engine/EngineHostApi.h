//EngineHostApi.h

#ifndef _EngineHostApi_h__
#define _EngineHostApi_h__


//////////////////////////////////////////////////////////////////////////
//ScriptFunc_103
// 获取带品质描述的被测值
void xvm_script_GetMEA(LPVOID pXvm);//long nIndex, long nBytes);		
void xvm_script_CalMEA(LPVOID pXvm);//long nValue);

// 时间函数
void xvm_script_GetCP32Time2a(LPVOID pXvm);//long nIndex, long nBytes);
void xvm_script_SetBbCurrValueCP32Time2a(LPVOID pXvm);//long nIndex);

void xvm_script_GetCP24Time2a(LPVOID pXvm);//long nIndex, long nBytes);
void xvm_script_SetBbCurrValueCP24Time2a(LPVOID pXvm);//long nIndex);

void xvm_script_GetCP56Time2a(LPVOID pXvm);//long nIndex, long nBytes);
void xvm_script_SetBbCurrValueCP56Time2a(LPVOID pXvm);//long nIndex);
void xvm_script_SetBbCurrValueCP56Time2aEx(LPVOID pXvm);//long nIndex, const char *pszDateTime);
void xvm_script_SetBbCurrValue48TimeMs(LPVOID pXvm);//long nIndex, const char *pszDateTime);

// 获取IEEE754
void xvm_script_GetIEEE754(LPVOID pXvm);//long nIndex);		
void xvm_script_SetIEEE754(LPVOID pXvm);//long nIndex, float fValue);

// 获取ASCII
void xvm_script_GetASCII(LPVOID pXvm);//long nIndex, long nBytes);		

//////////////////////////////////////////////////////////////////////////
//ScriptFunc_Engine.h

//////////////////////////////////////////////////////////////////////////
//设置绑定关系:设置
//ItemIndex
void xvm_script_BindItemIndex(LPVOID pXvm);//long nItemIndex);

//data
//获取当前关联的数据的数据类型
void xvm_script_GetCurrValueDataType(LPVOID pXvm);//);

//获取当前关联的数据的数据长度
void xvm_script_GetCurrValueDataLength(LPVOID pXvm);//);

//////////////////////////////////////////////////////////////////////////
//Byte/long
void xvm_script_GetBbCurrValue(LPVOID pXvm);//long nIndex,long nBytes);
void xvm_script_GetBbCurrValue1(LPVOID pXvm);//long nIndex);
void xvm_script_GetBbCurrValue2(LPVOID pXvm);//long nIndex);
void xvm_script_GetBbCurrValueTimeStr1970(LPVOID pXvm);//long nIndex,long nBytes);
void xvm_script_GetBbCurrValueTimeStr1970_ms(LPVOID pXvm);//long nIndex,long nBytes);

//设置当前ByteBlock的缓冲数据  nIndex为索引值，从1开始编号
void xvm_script_SetBbCurrValue(LPVOID pXvm);//long nIndex, long nValue, long nBytes);
void xvm_script_SetBbCurrValue1(LPVOID pXvm);//long nIndex, long nValue);
void xvm_script_SetBbCurrValue2(LPVOID pXvm);//long nIndex, long nValue);

//////////////////////////////////////////////////////////////////////////
//string
void xvm_script_SetBbCurrValueString(LPVOID pXvm);//long nIndex, const char* pString, long nBytes);
void xvm_script_SetBbCurrValueStringUtf8(LPVOID pXvm);//long nIndex, const char* pUtf8String, long nBytes);
void xvm_script_GetBbCurrValueString(LPVOID pXvm);//long nIndex, long nBytes);
void xvm_script_GetBbCurrValueStringEx(LPVOID pXvm);//long nIndex, long nBytes);

void xvm_script_GetBbFormatDataString(LPVOID pXvm);//long nIndex);
void xvm_script_GetBbFormatDataFloat(LPVOID pXvm);//long nIndex);
void xvm_script_GetBbFormatDataLong(LPVOID pXvm);//long nIndex);

//////////////////////////////////////////////////////////////////////////
//float
void xvm_script_SetBbCurrValueFloat(LPVOID pXvm);//long nIndex, float nValue);
void xvm_script_GetBbCurrValueFloat(LPVOID pXvm);//long nIndex);

//////////////////////////////////////////////////////////////////////////
//byte
void xvm_script_SetBbCurrValueByte(LPVOID pXvm);//long nIndex, const char* pString, long nBytes);
void xvm_script_GetBbCurrValueByte(LPVOID pXvm);//long nIndex, long nBytes);
void xvm_script_BbTranspos(LPVOID pXvm);//long nIndex1, long nIndex2);

//获取数据绑定的数据的属性
void xvm_script_GetDeviceNodeDataAttrValueString(LPVOID pXvm);//const char* pszPath, const char* pszAttrID, long nItemIndex);
void xvm_script_GetDeviceNodeDataAttrValueL(LPVOID pXvm);//const char* pszPath, const char* pszAttrID, long nItemIndex);
void xvm_script_GetDeviceNodeDataAttrValueD(LPVOID pXvm);//const char* pszPath, const char* pszAttrID, long nItemIndex);
void xvm_script_GetNextDeviceNodeDataByAttrValue(LPVOID pXvm);//const char* pszPath, const char* pszAttrID, double dValue, long nCurrIndex);
void xvm_script_SetDeviceNodeDataAttrs(LPVOID pXvm);//const char* pszPath, const char* pszAttrID, double dValue);
void xvm_script_SetDeviceNodeDataAttr(LPVOID pXvm);//const char* pszPath, const char* pszAttrID, double dValue);

void PPS_GetBindData(LPVOID pXvm);//const char* pszAttrID, CString &strValue);
void PPS_GetWBindData(LPVOID pXvm);//long nIndex, const char* pszAttrID, CString &strValue);

void xvm_script_InsertBindData(LPVOID pXvm);//long nTableRowIndex);
void xvm_script_InsertBindDataset(LPVOID pXvm);//long nTableRowIndex);
void xvm_script_InsertBindLogicDevice(LPVOID pXvm);//long nTableRowIndex);
void xvm_script_GetBindDataL(LPVOID pXvm);//const char* pszAttrID);
void xvm_script_GetBindDataD(LPVOID pXvm);//const char* pszAttrID);
void xvm_script_GetBindDataStr(LPVOID pXvm);//const char* pszAttrID);
void xvm_script_GetWBindDataL(LPVOID pXvm);//long nIndex, const char* pszAttrID);
void xvm_script_GetWBindDataD(LPVOID pXvm);//long nIndex, const char* pszAttrID);
void xvm_script_GetWBindDataStr(LPVOID pXvm);//long nIndex, const char* pszAttrID);

//设置数据绑定的数据的属性值
void xvm_script_SetBindDataL(LPVOID pXvm);//const char* pszAttrID, long nValue);
void xvm_script_SetBindDataD(LPVOID pXvm);//const char* pszAttrID, double dValue);

void xvm_script_SetWBindDataL(LPVOID pXvm);//long nIndex, const char* pszAttrID, long nValue);
void xvm_script_SetWBindDataD(LPVOID pXvm);//long nIndex, const char* pszAttrID, double dValue);

void xvm_script_SetBindDataStr(LPVOID pXvm);//const char* pszAttrID, const char* pszValue);
void xvm_script_SetBindDatasetStr(LPVOID pXvm);//const char* pszAttrID, const char* pszValue);
void xvm_script_SetBindLogicDeviceStr(LPVOID pXvm);//const char* pszAttrID, const char* pszValue);
void PPS_SetBindData(LPVOID pXvm);//const char* pszAttrID, CString &strValue);
void PPS_SetWBindData(LPVOID pXvm);//long nIndex,const char* pszAttrID, CString &strValue);
void PPS_CalBindData(LPVOID pXvm);//CExBaseObject *pDvNodeData, CString &strValue, const CString &strScriptID);

//拷贝数据到链表
void xvm_script_AdBindDataList(LPVOID pXvm);//const char *pszListID);

//数据改变消息
void xvm_script_FireDataChangeMessage(LPVOID pXvm);//long wPara, long lPara);
//延时
void xvm_script_Sleep(LPVOID pXvm);

//////////////////////////////////////////////////////////////////////////
//byteblock
void xvm_script_SetByteBlockEnable(LPVOID pXvm);//const char *pszBbID, long nShow);
void xvm_script_SetByteBlockEnable2(LPVOID pXvm);//const char *pszBbID);
void xvm_script_SetByteBlockLength(LPVOID pXvm);//const char *pszBbID, long nLen);
void xvm_script_GetByteBlockLength(LPVOID pXvm);//const char *pszBbID);

//////////////////////////////////////////////////////////////////////////
// 获取变量值
void xvm_script_GetValue(LPVOID pXvm);//const char *pszVariableID);
void xvm_script_GetValueDouble(LPVOID pXvm);//const char *pszVariableID);
void xvm_script_GetValueString(LPVOID pXvm);//const char *pszVariableID);
void xvm_script_SetValueLong(LPVOID pXvm);//const char *pszVariableID, long nValue);
void xvm_script_SetValueDouble(LPVOID pXvm);//const char *pszVariableID, double nValue);
void xvm_script_SetValueString(LPVOID pXvm);//const char *pszVariableID, const char *pszValue);

//报文桢解析匹配长度
void xvm_script_SetPkgLen(LPVOID pXvm);//long nLen);
void xvm_script_SetPkgValid(LPVOID pXvm);//long nValid);
void xvm_script_SetPkgRequiredLen(LPVOID pXvm);//long nLen);

void xvm_script_GetPkgLen(LPVOID pXvm);//);	// 当前打包的报文总长度
void xvm_script_GetPkgMaxLen(LPVOID pXvm);//);  //当前规约支持的最大长度
void xvm_script_GetPkgParsePos(LPVOID pXvm);//);	// 当前打包的报文总长度
void xvm_script_GetPkgCurrBufVal(LPVOID pXvm);//);	// 当前报文缓冲区的值

// 报文编号
void xvm_script_GetPkgNum(LPVOID pXvm);//);

// 全局变量
void xvm_script_AddGlobal(LPVOID pXvm);//const char *pszVariableID, long nValue);
void xvm_script_SubGlobal(LPVOID pXvm);//const char *pszVariableID, long nValue);
void xvm_script_GetGlobal(LPVOID pXvm);//const char *pszVariableID);
void xvm_script_GetGlobalEx(LPVOID pXvm);//const char *pszVariableID, CExBaseObject *pPpObj);
void xvm_script_SetGlobal(LPVOID pXvm);//const char *pszVariableID, long nValue);
void xvm_script_GetGlobalDouble(LPVOID pXvm);//const char *pszVariableID);
void xvm_script_SetGlobalDouble(LPVOID pXvm);//const char *pszVariableID, Double nValue);

//引擎执行部分
void xvm_script_IsProcedureExist(LPVOID pXvm);//const char *pszProcedureID);
void xvm_script_Run(LPVOID pXvm);//const char *pszProcedureID);
void xvm_script_Connect(LPVOID pXvm);//);
void xvm_script_DisConnect(LPVOID pXvm);//);
void xvm_script_SetPpRunState(LPVOID pXvm);//long nRunState);
void xvm_script_SetPpValid(LPVOID pXvm);//long nValid);

void xvm_script_CrcClear(LPVOID pXvm);//);
void xvm_script_CrcPushback(LPVOID pXvm);//BYTE ch);
void xvm_script_CrcPushbackBb(LPVOID pXvm);//long nIndex);
void xvm_script_CrcCDT(LPVOID pXvm);//);
void xvm_script_CrcSfWord(LPVOID pXvm);//);
void xvm_script_CrcModbus16(LPVOID pXvm);//);
void xvm_script_CrcModbus1600(LPVOID pXvm);//);
void xvm_script_PostConnectFinishedMsg(LPVOID pXvm);//long bConnectFinished);


//数据集操作函数
void xvm_script_CombineDsPathStr(LPVOID pXvm);//const char *pszValue);
void xvm_script_CombineDsPathL(LPVOID pXvm);//long nValue);
void xvm_script_ClearDsPath(LPVOID pXvm);//);
void xvm_script_GetDsPath(LPVOID pXvm);//);

void xvm_script_ClearDsDatas(LPVOID pXvm);//const char* pszPath);
void xvm_script_GetDsDataCount(LPVOID pXvm);//const char* pszPath);
void xvm_script_InsertDsData(LPVOID pXvm);//const char* pszPath,long nTableRowIndex, long nItemIndex);
void xvm_script_InsertDataset(LPVOID pXvm);//const char* pszPath, long nTableRowIndex, long nItemIndex);
void xvm_script_InsertLogicDevice(LPVOID pXvm);//const char* pszPath, long nTableRowIndex, long nItemIndex);
void xvm_script_InsertDevice(LPVOID pXvm);//long nDeviceIndex, const char* pszDeviceName);
void xvm_script_InsertDsDataEx(LPVOID pXvm);//const char* pszPath,long nTableRowIndex, long nItemIndex);
void xvm_script_InsertDatasetEx(LPVOID pXvm);//const char* pszPath, long nTableRowIndex, long nItemIndex);
void xvm_script_InsertLogicDeviceEx(LPVOID pXvm);//const char* pszPath, long nTableRowIndex, long nItemIndex);
void xvm_script_InsertDeviceEx(LPVOID pXvm);//long nDeviceIndex, const char* pszDeviceName);

void xvm_script_SetDsDataL(LPVOID pXvm);//const char* pszPath, const char *pszAttrID, long nValue);
void xvm_script_SetDsDataD(LPVOID pXvm);//const char* pszPath, const char *pszAttrID, double dValue);
void xvm_script_SetDsDataDEx(LPVOID pXvm);//long nDvIndex, const char* pszPath, const char *pszAttrID, double dValue);
void xvm_script_SetDsDataDBatch(LPVOID pXvm);//const char* pszDatasetID, const char* pszDataID, const char *pszAttrID, double dValue);
void xvm_script_SetDsDataStr(LPVOID pXvm);//const char* pszPath, const char *pszAttrID, const char* pszValue);
void xvm_script_SetDatasetStr(LPVOID pXvm);//const char* pszPath, const char *pszAttrID, const char* pszValue);
void xvm_script_SetLogicDeviceStr(LPVOID pXvm);//const char* pszPath, const char *pszAttrID, const char* pszValue);

void xvm_script_GetSequenceDsDatas(LPVOID pXvm);//const char* pszPath, const char *pszAttrID, const char* pszValue, const char* pszBeginIndexVar, const char* pszEndIndexVar, long nMaxCount);
void xvm_script_CountDsData(LPVOID pXvm);//const char* pszPath, const char *pszAttrID, const char* pszValue);
void xvm_script_CountDsDataEx(LPVOID pXvm);//const char* pszPath, const char *pszExpr);
void xvm_script_GetDsDataL(LPVOID pXvm);//const char* pszPath, const char *pszAttrID);
void xvm_script_GetDsDataD(LPVOID pXvm);//const char* pszPath, const char *pszAttrID);
void xvm_script_GetDsDataDEx(LPVOID pXvm);//long nDvIndex, const char* pszPath, const char *pszAttrID);
void xvm_script_GetDsDataStr(LPVOID pXvm);//const char* pszPath, const char *pszAttrID);
void xvm_script_SumDsDataD(LPVOID pXvm);//const char* pszPath, const char *pszAttrID, long nBeginDvIndex, long nEndDvIndex


void xvm_script_AdDsDataList(LPVOID pXvm);//const char* pszPath, const char *pszListID);
void xvm_script_AdDsPkgDetail(LPVOID pXvm);//const char* pszPath);
void xvm_script_AdValPkgDetail(LPVOID pXvm);//const char* pszName, const char *pszID, const char *pszValue);


void xvm_script_SF_GetANA24Float(LPVOID pXvm);//long nIndex);
void xvm_script_SF_GetANA32Float(LPVOID pXvm);//long nIndex);
void xvm_script_SF_GetBcd24Float(LPVOID pXvm);//long nIndex);
void xvm_script_SF_SetBcd24Float(LPVOID pXvm);//float fValue, long nIndex);
void xvm_script_SF_SetBcd24FloatEx(LPVOID pXvm);//float fValue, long nIndex);


//发送报文、接收报文的时间间隔函数
void xvm_script_GetRcvIdle(LPVOID pXvm);//);
void xvm_script_GetSendIdle(LPVOID pXvm);//);

//////////////////////////////////////////////////////////////////////////
//ScriptFunc_File.h
void xvm_script_AddSectionData(LPVOID pXvm);//long nIndex, long nBytes);
void xvm_script_Fis103SaveRCDFile(LPVOID pXvm);//const char* strPath, long nFileNameLen);			//保存录波文件
void xvm_script_Fis103SaveCommonFile(LPVOID pXvm);//const char* strPath, long nFileNameLen);			//保存普通文件

void xvm_script_CreateFile(LPVOID pXvm);//, const char *pszPath, const char* pszFileName);
void xvm_script_WriteFile(LPVOID pXvm);//, long nIndex, long nBytes);
void xvm_script_CloseFile(LPVOID pXvm);//);

void xvm_script_OpenRcdFile(LPVOID pXvm);//, const char *pszPathPath, const char *pszFileName);
void xvm_script_ReadRcdFile(LPVOID pXvm);//, long nIndex, long nBytes);
void xvm_script_GetFileLength(LPVOID pXvm);
void xvm_script_GetFileLeftLength(LPVOID pXvm);

//////////////////////////////////////////////////////////////////////////
//ScriptFunc_SF.h
void xvm_script_SF_ToThreeFloat(LPVOID pXvm);//FLOAT fData);

//////////////////////////////////////////////////////////////////////////
//ScriptFunc_System.h
//logic
void xvm_script_LAnd(LPVOID pXvm);//long nVal1, long nVal2);
void xvm_script_LOr(LPVOID pXvm);//long nVal1, long nVal2);
void xvm_script_LNot(LPVOID pXvm);//long nVal);
void xvm_script_LComplement(LPVOID pXvm);//long nVal);
void xvm_script_LComplement2(LPVOID pXvm);//short nVal);
void xvm_script_LComplement1(LPVOID pXvm);//char nVal);
void xvm_script_LInverse(LPVOID pXvm);//long nVal);
void xvm_script_LInverse2(LPVOID pXvm);//short nVal);
void xvm_script_LInverse1(LPVOID pXvm);//char nVal);
// void xvm_script_LRComplement(LPVOID pXvm);//long nVal);

//bit

void xvm_script_LShift(LPVOID pXvm);//long nVal, long nShift);
void xvm_script_RShift(LPVOID pXvm);//long nVal, long nShift);
void xvm_script_MkWord(LPVOID pXvm);//long nHigh, long nLow);

//time
void xvm_script_GetYear(LPVOID pXvm);//);
void xvm_script_GetMonth(LPVOID pXvm);//);
void xvm_script_GetDay(LPVOID pXvm);//);
void xvm_script_GetHour(LPVOID pXvm);//);
void xvm_script_GetMinute(LPVOID pXvm);//);
void xvm_script_GetSecond(LPVOID pXvm);//);
void xvm_script_GetMillionSecond(LPVOID pXvm);//);
void xvm_script_GetSystemTime(LPVOID pXvm);//);

//BCD/HEX
void xvm_script_BcdToHex(LPVOID pXvm);//long nVal);
void xvm_script_HexToBcd(LPVOID pXvm);//long nVal);
void xvm_script_StrBcdToHex(LPVOID pXvm);//const char*);
void xvm_script_StrHexToBcd(LPVOID pXvm);//const char*);


//系统相关的函数
void xvm_script_GetIP(LPVOID pXvm);//const char *pszTcpOrUdp);    //获取设备的IP地址
void xvm_script_GetRemoteIP(LPVOID pXvm);//const char *pszTcpOrUdp);    //获取远程的IP地址
void xvm_script_GetDeviceAddr(LPVOID pXvm);//);   //获取设备地址
void xvm_script_GetDeviceAttrL(LPVOID pXvm);//const char* pszAttrID);   //获取设备地址
void xvm_script_GetDeviceAttrStr(LPVOID pXvm);//const char* pszAttrID);   //获取设备地址
void xvm_script_GetCmmMode(LPVOID pXvm);//);   //获取通讯模式
void xvm_script_GetPort(LPVOID pXvm);//const char *pszCmmMode);  //获取通讯的端口
void xvm_script_GetSystemPara(LPVOID pXvm);//const char* pszParaID);   //获取系统的参数
void xvm_script_SetPort(LPVOID pXvm);//long nPort); 

void xvm_script_SetDeviceAttrL(LPVOID pXvm);//const char* pszAttrID, long nValue);
void xvm_script_SetDeviceAttrStr(LPVOID pXvm);//const char* pszAttrID, const char *pszValue);

//timer
void xvm_script_KillTimer(LPVOID pXvm);//const char *pszTimerID);
void xvm_script_ResetTimer(LPVOID pXvm);//const char *pszTimerID);
void xvm_script_SetTimerLong(LPVOID pXvm);//const char *pszTimerID, long nMs);


void xvm_script_GetBitInLong(LPVOID pXvm);//long nValue, long nBitIndex);
void xvm_script_SetBitInLong(LPVOID pXvm);//long nValue, long nBitIndex);
void xvm_script_ClearBitInLong(LPVOID pXvm);//long nValue, long nBitIndex);

void xvm_script_GetBitInLong16(LPVOID pXvm);//long nValue, long nBitIndex);
void xvm_script_SetBitInLong16(LPVOID pXvm);//long nValue, long nBitIndex);
void xvm_script_ClearBitInLong16(LPVOID pXvm);//long nValue, long nBitIndex);

void xvm_script_GetBitInLong32(LPVOID pXvm);//long nValue, long nBitIndex);
void xvm_script_SetBitInLong32(LPVOID pXvm);//long nValue, long nBitIndex);
void xvm_script_ClearBitInLong32(LPVOID pXvm);//long nValue, long nBitIndex);

void xvm_script_GetBitInLong8(LPVOID pXvm);//long nValue, long nBitIndex);
void xvm_script_SetBitInLong8(LPVOID pXvm);//long nValue, long nBitIndex);
void xvm_script_ClearBitInLong8(LPVOID pXvm);//long nValue, long nBitIndex);

void xvm_script_GetBitRangeInLong8(LPVOID pXvm);//long nValue, long nBitStart, long nBitEnd);

void xvm_script_LogPrint(LPVOID pXvm);//const char *pszVariableID,long nValue);
void xvm_script_ShowMsg(LPVOID pXvm);//const char *pszMsg);
void xvm_script_RandInRange(LPVOID pXvm);//(float fMinVal, float fMaxValue);
void xvm_script_FloatToLong(LPVOID pXvm);//(float fVal);

void xvm_script_GetFloatDigit(LPVOID pXvm);
void xvm_script_GetTimeStr1970(LPVOID pXvm);
void xvm_script_GetTimeLong1970(LPVOID pXvm);
//strfind
void xvm_script_StrFind(LPVOID pXvm);//const char *string

//字符串切割
void xvm_script_InitStrTok(LPVOID pXvm);
void xvm_script_StrTokCount(LPVOID pXvm);
void xvm_script_StrTokIndex(LPVOID pXvm);
void xvm_script_StrTokNext(LPVOID pXvm);

#endif