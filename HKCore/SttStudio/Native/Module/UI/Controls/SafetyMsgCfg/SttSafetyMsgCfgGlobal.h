//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSafetyMsgCfgGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define SSMCFGCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define SSMCFGCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define SSMCFGCLASSID_CSTTSAFETYMSGCFGS       (SSMCFGCLASSID_EXLISTCLASS + 0X00000000)
#define SSMCFGCLASSID_CSTTSAFETYMSGCFG       (SSMCFGCLASSID_EXLISTCLASS + 0X00000001)
#define SSMCFGCLASSID_CSTTSAFETYMSG       (SSMCFGCLASSID_BASECLASS + 0X00000002)

class CSttSafetyMsgCfgXmlRWKeys : public CXmlRWKeys
{
protected:
	CSttSafetyMsgCfgXmlRWKeys();
	virtual ~CSttSafetyMsgCfgXmlRWKeys();
	static long g_nSSMCFGRef;

public:
	static CSttSafetyMsgCfgXmlRWKeys* g_pXmlKeys;
	static CSttSafetyMsgCfgXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSttSafetyMsgKey; //stt-safety-msg
	BSTR m_strCSttSafetyMsgCfgKey; //stt-safety-msg-cfg
	BSTR m_strCSttSafetyMsgCfgsKey; //stt-safety-msg-cfgs
	BSTR m_strMsgKey; //Msg

public:
	static BSTR CSttSafetyMsgKey()  {   return g_pXmlKeys->m_strCSttSafetyMsgKey;  }
	static BSTR CSttSafetyMsgCfgKey()  {   return g_pXmlKeys->m_strCSttSafetyMsgCfgKey;  }
	static BSTR CSttSafetyMsgCfgsKey()  {   return g_pXmlKeys->m_strCSttSafetyMsgCfgsKey;  }
	static BSTR MsgKey()  {   return g_pXmlKeys->m_strMsgKey;  }
};



class CSttSafetyMsgCfgConstGlobal
{
private:
	CSttSafetyMsgCfgConstGlobal();
	virtual ~CSttSafetyMsgCfgConstGlobal();

public:
	static CSttSafetyMsgCfgConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSttSafetyMsgCfgConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
