//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroScriptMngr.h  CTestMacroScriptMngr

#pragma once

#include "MacroScriptMngrGlobal.h"


#include "TestMacroScript.h"
#include "../TestMacro/TestMacros.h"

class CTestMacroScriptMngr : public CExBaseList
{
public:
	CTestMacroScriptMngr();
	virtual ~CTestMacroScriptMngr();

	CString m_strScriptFile;

//重载函数
public:
	virtual UINT GetClassID() {    return MCSCLASSID_CTESTMACROSCRIPTMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTestMacroScriptMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

