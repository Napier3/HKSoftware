//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharMacroDrawPoint.h  CCharMacroDrawPoint

#pragma once

#include "CharacteristicGlobal.h"



class CCharMacroDrawPoint : public CCharMacroDraw
{
public:
	CCharMacroDrawPoint();
	virtual ~CCharMacroDrawPoint();


	CString  m_strX;
	CString  m_strY;
	CString  m_strType;
	CString  m_strColor;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARMACRODRAWPOINT;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharMacroDrawPointKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

