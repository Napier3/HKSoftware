//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroScript.h  CTestMacroScript

#pragma once

#include "MacroScriptMngrGlobal.h"


#include "TmScptData.h"

class CTestMacroScript : public CExBaseList
{
public:
	CTestMacroScript();
	virtual ~CTestMacroScript();


	CString  m_strMacroID;
	CString  m_strUIDLL;

//重载函数
public:
	virtual UINT GetClassID() {    return MCSCLASSID_CTESTMACROSCRIPT;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTestMacroScriptKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

//私有成员变量
private:
	BOOL m_bHasInit;

//私有成员变量访问方法
public:

public:
	void InitScript(CTestMacro *pMacro);
	BOOL RunScript(CTestMacro *pMacro, CShortData *pData);
};

