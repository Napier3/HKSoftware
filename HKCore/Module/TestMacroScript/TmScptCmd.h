//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmScptCmd.h  CTmScptCmd

#pragma once

#include "MacroScriptMngrGlobal.h"



class CTmScptCmd : public CExBaseObject
{
public:
	CTmScptCmd();
	virtual ~CTmScptCmd();


	CString  m_strDataID;
	CString  m_strAttrID;
	CString  m_strValue;
//重载函数
public:
	virtual UINT GetClassID() {    return MCSCLASSID_CTMSCPTCMD;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTmScptCmdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

//私有成员变量
private:

//私有成员变量访问方法
public:


public:
	virtual BOOL RunScript(CTestMacro *pMacro);

};

