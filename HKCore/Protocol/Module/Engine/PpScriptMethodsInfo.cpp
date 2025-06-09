#include "stdafx.h"
#include "PpScriptMethodsInfo.h"

CString CPpScriptMethodInfo::GetMethodString()
{
	CString strMethodString;
	
    strMethodString.Format(_T("函数名称：%s\n 返回值：%s\n 参数列表：%s\n 函数说明：%s\n")
        , m_strMethodName.GetString(),m_strReturnType.GetString()
        ,m_strParaList.GetString(),m_strMethodInfo.GetString());

	return strMethodString;
}

long CPpScriptMethodsInfo::g_nRef = 0;
CPpScriptMethodsInfo* CPpScriptMethodsInfo::g_pPpScriptMethods = NULL;

CPpScriptMethodsInfo::CPpScriptMethodsInfo()
{
	//构造函数，初始化所有Lua绑定函数

	//1	data
	CPpScriptMethodInfo* pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetValDataType");
	pMethod->m_strMethodInfo = _T("获取当前关联的数据的数据类型");
	pMethod->m_strParaList = _T("空");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//2
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetValDataLen");
	pMethod->m_strMethodInfo = _T("获取当前关联的数据的数据长度");
	pMethod->m_strParaList = _T("空");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//3	Byte/long
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValLong");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex,long nBytes");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValLong1");
	pMethod->m_strMethodInfo = _T("返回2个字节的整数，高位字节在前，低位字节在后");
	pMethod->m_strParaList = _T("long nIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValLong2");
	pMethod->m_strMethodInfo = _T("返回4个字节的整数，高位字节在前，低位字节在后");
	pMethod->m_strParaList = _T("long nIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//4	string
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValLong");
	pMethod->m_strMethodInfo = _T("设置当前ByteBlock的缓冲数据  nIndex为索引值，从1开始编号");
	pMethod->m_strParaList = _T("long nIndex, long nValue, long nBytes");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValLong1");
	pMethod->m_strMethodInfo = _T("设置当前ByteBlock的缓冲数据  nIndex为索引值，从1开始编号  设置2个字节的整数，高位字节在前，低位字节在后");
	pMethod->m_strParaList = _T("long nIndex, long nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValLong2");
	pMethod->m_strMethodInfo = _T("设置当前ByteBlock的缓冲数据  nIndex为索引值，从1开始编号  设置4个字节的整数，高位字节在前，低位字节在后");
	pMethod->m_strParaList = _T("long nIndex, long nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//5
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pString, long nBytes");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//6
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, long nBytes");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbFdataStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//7
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValFloat");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, float nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//8
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValFloat");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex");
	pMethod->m_strReturnType = _T("float");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValByte");
	pMethod->m_strMethodInfo = _T("设置当前ByteBlock的缓冲数据，nIndex为索引值，pString填入实际报文（如FF F1 00）,设置nBytes字节");
	pMethod->m_strParaList = _T("long nIndex, const char* pString, long nBytes");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValByte");
	pMethod->m_strMethodInfo = _T("获取当前ByteBlock的缓冲数据，从nIndex处获取nBytes字节，返回报文的内容");
	pMethod->m_strParaList = _T("long nIndex, long nBytes");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//9
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LAnd");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal1, long nVal2");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//10
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LOr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal1, long nVal2");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//11
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LNot");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//11
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LComp");
	pMethod->m_strMethodInfo = _T("求反码");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LComp2");
	pMethod->m_strMethodInfo = _T("求short反码");
	pMethod->m_strParaList = _T("short nVal");
	pMethod->m_strReturnType = _T("short");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LComp1");
	pMethod->m_strMethodInfo = _T("求char反码");
	pMethod->m_strParaList = _T("char nVal");
	pMethod->m_strReturnType = _T("char");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//11
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LRComp");
	pMethod->m_strMethodInfo = _T("求补码");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//12
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LShift");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//13
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("RShift");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//14
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("MkWord");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nHigh, long nLow");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////15 time
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetYear");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////16 
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetMonth");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////17
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDay");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////18
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetHour");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////19
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetMinute");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////20
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetSecond");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////21
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetMSecond");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////21
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetSystemTime");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//22 BCD/HEX
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("BcdToHex");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//23 
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("HexToBcd");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//24
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("StrBcdToHex");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char*");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//25
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("StrHexToBcd");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char*");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//26 byteblock
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbEnable");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszBbID, long nShow");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//27
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetByteBlockEnable2");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszBbID");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//28
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbLen");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszBbID, long nLen");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//29
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbLen");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszBbID");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

// 	//30 timer
// 	pMethod = new CPpScriptMethodInfo();
// 	pMethod->m_strMethodName = _T("KillTimer");
// 	pMethod->m_strMethodInfo = _T("");
// 	pMethod->m_strParaList = _T("const char *pszTimerID");
// 	pMethod->m_strReturnType = _T("void");
// 	AddTail(pMethod);
// 	pMethod->SetParent(this);
// 
// 	//31
// 	pMethod = new CPpScriptMethodInfo();
// 	pMethod->m_strMethodName = _T("ResetTimer");
// 	pMethod->m_strMethodInfo = _T("");
// 	pMethod->m_strParaList = _T("const char *pszTimerID");
// 	pMethod->m_strReturnType = _T("void");
// 	AddTail(pMethod);
// 	pMethod->SetParent(this);
// 
// 	//32
// 	pMethod = new CPpScriptMethodInfo();
// 	pMethod->m_strMethodName = _T("SetTimerLong");
// 	pMethod->m_strMethodInfo = _T("");
// 	pMethod->m_strParaList = _T("const char *pszTimerID, long nMs");
// 	pMethod->m_strReturnType = _T("void");
// 	AddTail(pMethod);
// 	pMethod->SetParent(this);
// 
// 	//33 返回值
// 	pMethod = new CPpScriptMethodInfo();
// 	pMethod->m_strMethodName = _T("SetMatchResult");
// 	pMethod->m_strMethodInfo = _T("");
// 	pMethod->m_strParaList = _T("long nResult");
// 	pMethod->m_strReturnType = _T("void");
// 	AddTail(pMethod);
// 	pMethod->SetParent(this);
// 
// 	//34
// 	pMethod = new CPpScriptMethodInfo();
// 	pMethod->m_strMethodName = _T("SetParseResult");
// 	pMethod->m_strMethodInfo = _T("");
// 	pMethod->m_strParaList = _T("long nResult");
// 	pMethod->m_strReturnType = _T("void");
// 	AddTail(pMethod);
// 	pMethod->SetParent(this);

	//35 获取变量
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("GetValue");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszVariableID");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//陈哲添加于2015.05.13
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("GetValueStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszVariableID");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//36
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("SetValueLong");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszVariableID, long nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("SetValueDouble");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszVariableID, double dValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("SetValueStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszVariableID, const char* strValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//37
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetPkgLen");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nLen");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetPkgValid");
	pMethod->m_strMethodInfo = _T("设置报文对象的有效状态");
	pMethod->m_strParaList = _T("long nValid");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//38
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetPkgLen");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetPkgParsePos");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetPkgCurrBufVal");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nOffset");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//39
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetPkgNum");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//40
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBindDataL");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID, long nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetWBindDataL");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pszAttrID, long nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//40
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("InsertBindData");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nTableRowIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("InsertBindDataset");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nTableRowIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("InsertBindLogicDevice");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nTableRowIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//41
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBindDataL");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetWBindDataL");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pszAttrID");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//42
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBindDataD");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID, double dValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetWBindDataD");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pszAttrID, double dValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//43
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBindDataD");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID");
	pMethod->m_strReturnType = _T("double");
	AddTail(pMethod);
	pMethod->SetParent(this);
	
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("SetNdDatasAttr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszPath, const char* pszAttrID, double dValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);
	
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("GetNdDataAttrL");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszPath, const char* pszAttrID, long nItemIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("GetNdDataAttrD");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszPath, const char* pszAttrID, long nItemIndex");
	pMethod->m_strReturnType = _T("double");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("GetNextNdDataByAttr");
	pMethod->m_strMethodInfo = _T("获取数据集的下一个属性值等于传入的数值的item-index");
	pMethod->m_strParaList = _T("const char* pszPath, const char* pszAttrID, double dValue, long nCurrItemIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetWBindDataD");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pszAttrID");
	pMethod->m_strReturnType = _T("double");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBindDataStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID");
	pMethod->m_strReturnType = _T("char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetWBindDataStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pszAttrID");
	pMethod->m_strReturnType = _T("char*");
	AddTail(pMethod);
	pMethod->SetParent(this);
	//43
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBindDataStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID, const char* pszValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBindDatasetStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID, const char* pszValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBindLogicDeviceStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID, const char* pszValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//44
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetPkgMaxLen");
	pMethod->m_strMethodInfo = _T("获取当前规约支持的最大长度");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("AdBindDataList");
	pMethod->m_strMethodInfo = _T("添加当前绑定的数据到链表中，例如添加YX到临时链表SOE中");
	pMethod->m_strParaList = _T("参数1：设备数据模型下的临时链表");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetMEA");
	pMethod->m_strMethodInfo = _T("添加当前绑定的数据到链表中，例如添加YX到临时链表SOE中");
	pMethod->m_strParaList = _T("参数1：设备数据模型下的临时链表");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("CalMEA");
	pMethod->m_strMethodInfo = _T("计算MEA值");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("FireDataMsg");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetCP24Time2a");
	pMethod->m_strMethodInfo = _T("计算当前绑定的数据对象的值，数据值为24位表示的前时间");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetCP24Time2a");
	pMethod->m_strMethodInfo = _T("设置字节块的值，用24位的当前时间数据填充");
	pMethod->m_strParaList = _T("参数1：从字节块缓冲区填充的起始位置");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	
	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetCP32Time2a");
	pMethod->m_strMethodInfo = _T("计算当前绑定的数据对象的值，数据值为32位表示的前时间");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetCP32Time2a");
	pMethod->m_strMethodInfo = _T("设置字节块的值，用32位的当前时间数据填充");
	pMethod->m_strParaList = _T("参数1：从字节块缓冲区填充的起始位置");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	
	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetCP56Time2a");
	pMethod->m_strMethodInfo = _T("计算当前绑定的数据对象的值，数据值为56位表示的前时间");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetCP56Time2a");
	pMethod->m_strMethodInfo = _T("设置字节块的值，用56位的当前时间数据填充");
	pMethod->m_strParaList = _T("参数1：从字节块缓冲区填充的起始位置");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetCP56Time2aEx");
	pMethod->m_strMethodInfo = _T("设置字节块的值，用56位的当前时间数据填充");
	pMethod->m_strParaList = _T("参数1：从字节块缓冲区填充的起始位置,参数2：时间文本，例如2015-4-23 8:00");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("BindItemIndex");
	pMethod->m_strMethodInfo = _T("绑定数据对象的条目号，更改系统设置的绑定");
	pMethod->m_strParaList = _T("参数：条目号的数值");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetBitInLong16");
	pMethod->m_strMethodInfo = _T("获取16位整数指定位的值");
	pMethod->m_strParaList = _T("参数1：源数据，16位整数；参数2：整数的位索引");
	pMethod->m_strReturnType = _T("指定位的值，0或者1");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetBitInLong16");
	pMethod->m_strMethodInfo = _T("设置16位整数的指定位等于1");
	pMethod->m_strParaList = _T("参数1：源数据，16位整数；参数2：整数的位索引");
	pMethod->m_strReturnType = _T("返回结果数据，16位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	


	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ClearBitInLong16");
	pMethod->m_strMethodInfo = _T("设置16位整数的指定位等于0");
	pMethod->m_strParaList = _T("参数1：源数据，16位整数；参数2：整数的位索引");
	pMethod->m_strReturnType = _T("返回结果数据，16位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);		

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetBitInLong32");
	pMethod->m_strMethodInfo = _T("获取32位整数指定位的值");
	pMethod->m_strParaList = _T("参数1：源数据，32位整数；参数2：整数的位索引");
	pMethod->m_strReturnType = _T("指定位的值，0或者1");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetBitInLong32");
	pMethod->m_strMethodInfo = _T("设置32位整数的指定位等于1");
	pMethod->m_strParaList = _T("参数1：源数据，32位整数；参数2：整数的位索引");
	pMethod->m_strReturnType = _T("返回结果数据，32位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	


	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ClearBitInLong32");
	pMethod->m_strMethodInfo = _T("设置32位整数的指定位等于0");
	pMethod->m_strParaList = _T("参数1：源数据，32位整数；参数2：整数的位索引");
	pMethod->m_strReturnType = _T("返回结果数据，32位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetBitInLong8");
	pMethod->m_strMethodInfo = _T("获取8位整数指定位的值");
	pMethod->m_strParaList = _T("参数1：源数据，8位整数；参数2：整数的位索引");
	pMethod->m_strReturnType = _T("指定位的值，0或者1");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetBitInLong8");
	pMethod->m_strMethodInfo = _T("设置8位整数的指定位等于1");
	pMethod->m_strParaList = _T("参数1：源数据，8位整数；参数2：整数的位索引");
	pMethod->m_strReturnType = _T("返回结果数据，8位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);
	
	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ClearBitInLong8");
	pMethod->m_strMethodInfo = _T("设置8位整数的指定位等于0");
	pMethod->m_strParaList = _T("参数1：源数据，8位整数；参数2：整数的位索引");
	pMethod->m_strReturnType = _T("返回结果数据，8位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetBitRangeInLong8");
	pMethod->m_strMethodInfo = _T("获取8位整数指定位范围的值");
	pMethod->m_strParaList = _T("参数1：源数据，8位整数；参数2：整数的位索引开始位置；参数3：整数的位索引结束位置");
	pMethod->m_strReturnType = _T("指定位范围的值");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SfCalFloat");
	pMethod->m_strMethodInfo = _T("四方浮点数计算方法，将浮点数转换为3字节数据");
	pMethod->m_strParaList = _T("参数：需要转换的浮点数");
	pMethod->m_strReturnType = _T("返回转换成功的DWORD数据");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SfGetAna24Float");
	pMethod->m_strMethodInfo = _T("四方浮点数计算方法，将3字节数据转换为浮点数");
	pMethod->m_strParaList = _T("参数1：字节块缓冲区的位置");
	pMethod->m_strReturnType = _T("返回浮点数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SfGetBcd24Float");
	pMethod->m_strMethodInfo = _T("四方浮点数计算方法，将3字节BCD数据转换为浮点数");
	pMethod->m_strParaList = _T("参数1：字节块缓冲区的位置");
	pMethod->m_strReturnType = _T("返回浮点数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SfSetBcd24Float");
	pMethod->m_strMethodInfo = _T("将浮点数写入3字节BCD数据缓冲区");
	pMethod->m_strParaList = _T("参数1：浮点数；参数2：字节块缓冲区的起始位置");
	pMethod->m_strReturnType = _T("返回无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SfSetBcd24FloatEx");
	pMethod->m_strMethodInfo = _T("将浮点数写入3字节BCD数据缓冲区【按照最大小数精度来计算】");
	pMethod->m_strParaList = _T("参数1：浮点数；参数2：字节块缓冲区的起始位置");
	pMethod->m_strReturnType = _T("返回无");
	AddTail(pMethod);
	pMethod->SetParent(this);	


	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetGlobal");
	pMethod->m_strMethodInfo = _T("获取全局变量");
	pMethod->m_strParaList = _T("参数1：变量ID");
	pMethod->m_strReturnType = _T("返回结果数据，32位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetGlobal");
	pMethod->m_strMethodInfo = _T("设置全局变量");
	pMethod->m_strParaList = _T("参数1：变量ID，参数2： 值");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("AddGlobal");
	pMethod->m_strMethodInfo = _T("设置全局变量的值增加一个数值");
	pMethod->m_strParaList = _T("参数1：变量ID，参数2： 值");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SubGlobal");
	pMethod->m_strMethodInfo = _T("设置全局变量的值增加一个数值");
	pMethod->m_strParaList = _T("参数1：变量ID，参数2： 值");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetIP");
	pMethod->m_strMethodInfo = _T("获取通讯通道本地IP地址");
	pMethod->m_strParaList = _T("参数：传入网络通讯的方式，为文本\"udp\"、\"tcp\"");
	pMethod->m_strReturnType = _T("返回结果数据，32位整数，IP地址，如果不存在，返回192.168.1.10");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetRemoteIP");
	pMethod->m_strMethodInfo = _T("获取通讯通道远程IP地址");
	pMethod->m_strParaList = _T("参数：传入网络通讯的方式，为文本\"udp\"、\"tcp\"");
	pMethod->m_strReturnType = _T("返回结果数据，32位整数，IP地址，如果不存在，返回192.168.1.10");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PROCEDURE);
	pMethod->m_strMethodName = _T("SetPpRunState");
	pMethod->m_strMethodInfo = _T("设置过程执行的状态");
	pMethod->m_strParaList = _T("参数：过程执行的状态，0=正常结束；1=通讯错误；2=通讯复位");
	pMethod->m_strReturnType = _T("返回结果数据，无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PROCEDURE);
	pMethod->m_strMethodName = _T("SetPpValid");
	pMethod->m_strMethodInfo = _T("设置过程有效的状态");
	pMethod->m_strParaList = _T("参数：过程有效的状态，0=无效；1=有效；");
	pMethod->m_strReturnType = _T("返回结果数据，无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDeviceAddr");
	pMethod->m_strMethodInfo = _T("获取设备地址");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("返回结果数据，32位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDeviceAttrL");
	pMethod->m_strMethodInfo = _T("获取设备属性数据");
	pMethod->m_strParaList = _T("属性的ID,字符串");
	pMethod->m_strReturnType = _T("返回结果数据，32位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDeviceAttrStr");
	pMethod->m_strMethodInfo = _T("获取设备属性数据");
	pMethod->m_strParaList = _T("属性的ID,字符串");
	pMethod->m_strReturnType = _T("返回结果数据，字符串");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDeviceAttrL");
	pMethod->m_strMethodInfo = _T("设置设备属性数据");
	pMethod->m_strParaList = _T("参数1：属性的ID,字符串；参数2：属性整数值");
	pMethod->m_strReturnType = _T("返回无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDeviceAttrStr");
	pMethod->m_strMethodInfo = _T("设置设备属性数据");
	pMethod->m_strParaList = _T("参数1：属性的ID,字符串；参数2：属性字符串值");
	pMethod->m_strReturnType = _T("返回无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetCmmMode");
	pMethod->m_strMethodInfo = _T("获取通讯模式");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("返回结果数据，32位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetPort");
	pMethod->m_strMethodInfo = _T("获取通讯的端口");
	pMethod->m_strParaList = _T("参数：通讯模式");
	pMethod->m_strReturnType = _T("返回结果数据，32位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetSystemPara");
	pMethod->m_strMethodInfo = _T("获取系统的参数");
	pMethod->m_strParaList = _T("参数：ID");
	pMethod->m_strReturnType = _T("返回结果数据，32位整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LogPrint");
	pMethod->m_strMethodInfo = _T("打印变量");
	pMethod->m_strParaList = _T("参数1：输出字符，参数2： 值");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ShowMsg");
	pMethod->m_strMethodInfo = _T("输出文本信息");
	pMethod->m_strParaList = _T("参数1：输出文本信息字符串");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PROCEDURE);
	pMethod->m_strMethodName = _T("Run");
	pMethod->m_strMethodInfo = _T("运行过程");
	pMethod->m_strParaList = _T("参数：过程ID");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PROCEDURE);
	pMethod->m_strMethodName = _T("Connect");
	pMethod->m_strMethodInfo = _T("连接");
	pMethod->m_strParaList = _T("参数：无");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PROCEDURE);
	pMethod->m_strMethodName = _T("DisConnect");
	pMethod->m_strMethodInfo = _T("断开连接");
	pMethod->m_strParaList = _T("参数：无");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	


	//////////////////////////////////////////////////////////////////////////
	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CombineDsPathStr");
	pMethod->m_strMethodInfo = _T("组合路径缓冲区，添加一个字符串路径");
	pMethod->m_strParaList = _T("参数1：数据");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CombineDsPathL");
	pMethod->m_strMethodInfo = _T("组合路径缓冲区，添加一个整数路径");
	pMethod->m_strParaList = _T("参数1：数据");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ClearDsPath");
	pMethod->m_strMethodInfo = _T("清空用于组合的字符串路径缓冲区");
	pMethod->m_strParaList = _T("参数：无");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsPath");
	pMethod->m_strMethodInfo = _T("获取组合的数据路径");
	pMethod->m_strParaList = _T("参数：无");
	pMethod->m_strReturnType = _T("返回路径字符串");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("InsertDsData");
	pMethod->m_strMethodInfo = _T("向数据集中插入一个数据对象");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“Device1$CPU1$dsEna”；参数2：数据索引号；参数3：新数据的条目号");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataCount");
	pMethod->m_strMethodInfo = _T("获取数据集数据对象数目");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“Device1$CPU1$dsEna”；");
	pMethod->m_strReturnType = _T("数据集数目");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataCount");
	pMethod->m_strMethodInfo = _T("获取数据集数据对象数目");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“Device1$CPU1$dsEna”；");
	pMethod->m_strReturnType = _T("数据集数目");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ClearDsDatas");
	pMethod->m_strMethodInfo = _T("清空数据集数据对象");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“Device1$CPU1$dsEna”；");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("InsertDataset");
	pMethod->m_strMethodInfo = _T("向逻辑设备中插入一个数据集");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“Device1$CPU1”；参数2：数据索引号；参数3：新数据的条目号");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("InsertLogicDevice");
	pMethod->m_strMethodInfo = _T("向设备中插入一个逻辑设备");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“Device1”；参数2：数据索引号；参数3：新数据的条目号");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("InsertDevice");
	pMethod->m_strMethodInfo = _T("向多设备数据模型中添加一个新的设备");
	pMethod->m_strParaList = _T("参数1：设备ID，整形；参数2：设备名称");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDsDataL");
	pMethod->m_strMethodInfo = _T("设置数据属性值");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“CPU1$dsEna$Yb000”或者“数据编号”；参数2：属性ID，例如“value”；参数3：数据值，整数");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDsDataD");
	pMethod->m_strMethodInfo = _T("设置数据属性值");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“CPU1$dsEna$Yb000”或者“数据编号”；参数2：属性ID，例如“value”；参数3：数据值，浮点数");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDsDataDEx");
	pMethod->m_strMethodInfo = _T("设置数据属性值");
	pMethod->m_strParaList = _T("参数1：装置索引，参数2：数据路径，例如“CPU1$dsEna$Yb000”或者“数据编号”；参数3：属性ID，例如“value”；参数4：数据值，浮点数");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDsDataDBatch");
	pMethod->m_strMethodInfo = _T("设置数据属性值");
	pMethod->m_strParaList = _T("参数1：数据集ID（例如YC），参数2：数据ID，例如“YC001”；参数3：属性ID，例如“value”；参数4：数据值，浮点数");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDsDataStr");
	pMethod->m_strMethodInfo = _T("设置数据属性值");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“CPU1$dsEna$Yb000”或者“数据编号”；参数2：属性ID，例如“value”；参数3：数据值，字符串");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDatasetStr");
	pMethod->m_strMethodInfo = _T("设置数据集的属性值");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“CPU1$dsEna”；参数2：属性ID，例如“name”；参数3：数据值，字符串");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetLogicDeviceStr");
	pMethod->m_strMethodInfo = _T("设置逻辑设备的属性值");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“CPU1”；参数2：属性ID，例如“name”；参数3：数据值，字符串");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CountDsData");
	pMethod->m_strMethodInfo = _T("统计数据集满足要求的数据的个数");
	pMethod->m_strParaList = _T("参数1：数据路径，包括【ID路径“CPU1$dsEna$Yb000”】、【编号路径“1$23$2”】、【数据编号】、【全局变量的ID】；参数2：属性ID，例如“value”；参数3：数据属性ID对象的值");
	pMethod->m_strReturnType = _T("数据属性，整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	
	
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CountDsDataEx");
	pMethod->m_strMethodInfo = _T("统计数据集满足要求的数据的个数");
	pMethod->m_strParaList = _T("参数1：数据路径，包括【ID路径“CPU1$dsEna$Yb000”】、【编号路径“1$23$2”】、【数据编号】、【全局变量的ID】；参数2：属性等式，例如【change=1;datatype-id=3;】");
	pMethod->m_strReturnType = _T("数据属性，整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetSequenceDsDatas");
	pMethod->m_strMethodInfo = _T("统计数据集满足要求的数据的个数");
	pMethod->m_strParaList = _T("参数1：数据路径，包括【ID路径“CPU1$dsEna$Yb000”】、【编号路径“1$23$2”】、【数据编号】、【全局变量的ID】；参数2：属性ID，例如“value”；参数3：数据属性ID对象的值；参数4：起始索引号的全局变量；变量5：终止索引号的全部变量；参数6：最大统计个数");
	pMethod->m_strReturnType = _T("数据属性，整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataL");
	pMethod->m_strMethodInfo = _T("获取数据属性值");
	pMethod->m_strParaList = _T("参数1：数据路径，包括【ID路径“CPU1$dsEna$Yb000”】、【编号路径“1$23$2”】、【数据编号】、【全局变量的ID】；参数2：属性ID，例如“value”");
	pMethod->m_strReturnType = _T("数据属性，整数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataD");
	pMethod->m_strMethodInfo = _T("获取数据属性值");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“CPU1$dsEna$Yb000”或者“数据编号”；参数2：属性ID，例如“value”");
	pMethod->m_strReturnType = _T("数据属性，浮点数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataDEx");
	pMethod->m_strMethodInfo = _T("获取数据属性值");
	pMethod->m_strParaList = _T("参数1：装置索引号；参数2：数据路径，例如“CPU1$dsEna$Yb000”或者“数据编号”；参数3：属性ID，例如“value”");
	pMethod->m_strReturnType = _T("数据属性，浮点数");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataStr");
	pMethod->m_strMethodInfo = _T("获取数据属性值");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“CPU1$dsEna$Yb000”或者“数据编号”；参数2：属性ID，例如“value”");
	pMethod->m_strReturnType = _T("数据属性，字符串值");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SumDsDataD");
	pMethod->m_strMethodInfo = _T("获取数据属性值");
	pMethod->m_strParaList = _T("参数1：数据路径，例如“CPU1$dsEna$Yb000”或者“数据编号”；参数2：属性ID，例如“value”；参数3：装置的起始索引；参数4：装置的终止索引");
	pMethod->m_strReturnType = _T("数据属性，浮点数");
	AddTail(pMethod);
	pMethod->SetParent(this);	


	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("AdDsDataList");
	pMethod->m_strMethodInfo = _T("添加数据对象到报告数据集中");
	pMethod->m_strParaList = _T("参数1：数据对象的路径，参数2：报告数据集的ID");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("AdDsPkgDetail");
	pMethod->m_strMethodInfo = _T("添加数据集（点表）数据对象到当前的报文对象中");
	pMethod->m_strParaList = _T("参数1：数据对象的路径");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("AdValPkgDetail");
	pMethod->m_strMethodInfo = _T("添加数据对象到当前的报文对象中");
	pMethod->m_strParaList = _T("参数1：数据名称，字符串；参数2：数据ID，字符串；参数3：数据值，字符串");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetRcvIdle");
	pMethod->m_strMethodInfo = _T("获取没有接收到报文的时间长度");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("时间长度，毫秒");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetSendIdle");
	pMethod->m_strMethodInfo = _T("获取没有报文报文的时间长度");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("时间长度，毫秒");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("AddSectionData");
	pMethod->m_strMethodInfo = _T("添加报文数据到一个数据列表中，用于随后对其解析并存储为文件");
	pMethod->m_strParaList = _T("参数1：添加的首字节索引，整数；参数2：添加的字节数，整数");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("Fis103SaveRCDFile");
	pMethod->m_strMethodInfo = _T("将数据列表中的数据存储为录波文件");
	pMethod->m_strParaList = _T("参数1：存储的路径，字符串；参数2：报文中录波文件名的长度");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("Fis103SaveCommonFile");
	pMethod->m_strMethodInfo = _T("将数据列表中的数据存储为普通文件");
	pMethod->m_strParaList = _T("参数1：存储的路径，字符串；参数2：报文中文件名的长度");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//	RegisterHostAPIFunc (-1, "CreateFile", xvm_script_CreateFile);
	//RegisterHostAPIFunc (-1, "WriteFile", xvm_script_WriteFile);
	//RegisterHostAPIFunc (-1, "CloseFile", xvm_script_CloseFile);
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CreateFile");
	pMethod->m_strMethodInfo = _T("创建文件");
	pMethod->m_strParaList = _T("参数1：存储的路径，字符串；参数2：文件名称");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("WriteFile");
	pMethod->m_strMethodInfo = _T("写文件");
	pMethod->m_strParaList = _T("参数1：字节快开始字节编号，整数；参数2：字节数目，整数");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CloseFile");
	pMethod->m_strMethodInfo = _T("关闭文件");
	pMethod->m_strParaList = _T("无");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CrcClear");
	pMethod->m_strMethodInfo = _T("清空CRC校验用缓冲区");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CrcPush");
	pMethod->m_strMethodInfo = _T("向CRC校验用缓冲区添加一个BYTE");
	pMethod->m_strParaList = _T("参数1：BYTE数值");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CrcPushBb");
	pMethod->m_strMethodInfo = _T("向CRC校验用缓冲区添加一个BYTE");
	pMethod->m_strParaList = _T("参数1：字节块缓冲区的编号");
	pMethod->m_strReturnType = _T("无");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CrcSf2000");
	pMethod->m_strMethodInfo = _T("计算缓冲区的CRC数值");
	pMethod->m_strParaList = _T("无");
	pMethod->m_strReturnType = _T("返回Word");
	AddTail(pMethod);
	pMethod->SetParent(this);
}

CPpScriptMethodsInfo* CPpScriptMethodsInfo::Create()
{
	g_nRef ++;

	if(g_nRef == 1)
	{
		g_pPpScriptMethods = new CPpScriptMethodsInfo();
	}

	return g_pPpScriptMethods;
}

void CPpScriptMethodsInfo::Release()
{
	g_nRef -- ;

	if(g_nRef == 0)
	{
		delete g_pPpScriptMethods;
		g_pPpScriptMethods = NULL;
	}
}
