//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbUIMacro.h  CGbUIMacro

#pragma once

#include "MacroScriptMngrGlobal.h"



class CGbUIMacro : public CExBaseObject
{
public:
	CGbUIMacro();
	virtual ~CGbUIMacro();


	CString  m_strDLL;
//重载函数
public:
	virtual UINT GetClassID() {    return TMSCLASSID_CGBUIMACRO;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CGbUIMacroKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

