//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmScptData.h  CTmScptData

#pragma once

#include "MacroScriptMngrGlobal.h"
#include "TmScptValue.h"

class CTmScptData : public CExBaseList
{
public:
	CTmScptData();
	virtual ~CTmScptData();


//重载函数
public:
	virtual UINT GetClassID() {    return MCSCLASSID_CTMSCPTDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTmScptDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

//私有成员变量
private:
	CString m_strOldData;

//私有成员变量访问方法
public:

public:
	CTmScptValue* FindByValue(const CString &strValue);
	BOOL RunScript(CTestMacro *pMacro, CShortData *pData);
};

