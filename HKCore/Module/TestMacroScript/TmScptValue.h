//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmScptValue.h  CTmScptValue

#pragma once

#include "MacroScriptMngrGlobal.h"


#include "TmScptCmd.h"
#include "TmScptGroupCmd.h"

class CTmScptValue : public CExBaseList
{
public:
	CTmScptValue();
	virtual ~CTmScptValue();


	CString  m_strValue;
//重载函数
public:
	virtual UINT GetClassID() {    return MCSCLASSID_CTMSCPTVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTmScptValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

//私有成员变量
private:

//私有成员变量访问方法
public:

public:
	BOOL RunScript(CTestMacro *pMacro);
};

