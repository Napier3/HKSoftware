//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CmdExecGlobal.h

#pragma once

#include "../../../Module/DataMngr/DataMngrGlobal.h"

//#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00060000)
#define CmdMngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00060000)

#define MNGRCLASSID_CCMDEXECRSLT       (CmdMngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CEXECRESULT       (CmdMngrCLASSID_EXLISTCLASS + 0X00000001)

class CCmdExecXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CCmdExecXmlRWKeys();
	virtual ~CCmdExecXmlRWKeys();
	static long g_nMngrRef;

public:
	static CCmdExecXmlRWKeys* g_pXmlKeys;
	static CCmdExecXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCExecResultKey; //rslt
	BSTR m_strCCmdExecRsltKey; //cmd-exec-rslt

public:
	static BSTR CExecResultKey()  {   return g_pXmlKeys->m_strCExecResultKey;  }
	static BSTR CCmdExecRsltKey()  {   return g_pXmlKeys->m_strCCmdExecRsltKey;  }
};



class CCmdExecConstGlobal
{
private:
	CCmdExecConstGlobal();
	virtual ~CCmdExecConstGlobal();

public:
	static CCmdExecConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CCmdExecConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
