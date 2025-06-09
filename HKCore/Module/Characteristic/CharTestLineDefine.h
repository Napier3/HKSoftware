//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharTestLineDefine.h  CCharTestLineDefine

#pragma once

#include "CharacteristicGlobal.h"



class CCharTestLineDefine : public CExBaseObject
{
public:
	CCharTestLineDefine();
	virtual ~CCharTestLineDefine();


	CString  m_strExprAngle;
	CString  m_strExprX;
	CString  m_strExprY;
	CString  m_strExprR;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARTESTLINEDEFINE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharTestLineDefineKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

