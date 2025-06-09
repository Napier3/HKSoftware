//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ScriptFuncs.h  CScriptFuncs

#pragma once

#include "ScriptFuncGlobal.h"


#include "ScriptFunc.h"

class CScriptFuncs : public CExBaseList
{
public:
	CScriptFuncs();
	virtual ~CScriptFuncs();

	BOOL OpenConfigFile(const CString &strFile);

//重载函数
public:
	virtual UINT GetClassID() {    return SFNCLASSID_CSCRIPTFUNCS;   }
	virtual BSTR GetXmlElementKey()  {      return CScriptFuncXmlRWKeys::CScriptFuncsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

class  CScriptFuncsList : public CExBaseList
{
protected:
	CScriptFuncsList();
	virtual ~CScriptFuncsList();

	static CScriptFuncsList *g_pScriptFuncsList;
	static long g_nScriptFuncsList;

public:
	static void Create();
	static void Release();
	static CScriptFuncs* OpenFile(const CString &strFile);

};

