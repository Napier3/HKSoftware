//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharMacroDrawLine.h  CCharMacroDrawLine

#pragma once

#include "CharacteristicGlobal.h"



class CCharMacroDrawLine : public CCharMacroDraw
{
public:
	CCharMacroDrawLine();
	virtual ~CCharMacroDrawLine();


	CString  m_strXb;
	CString  m_strXe;
	CString  m_strYe;
	CString  m_strYb;
	CString  m_strType;
	CString  m_strColor;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARMACRODRAWLINE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharMacroDrawLineKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

