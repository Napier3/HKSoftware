//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLine.h  CCharElementLine

#pragma once

#include "CharacteristicGlobal.h"



class CCharElementLine : public CCharElement
{
public:
	CCharElementLine();
	virtual ~CCharElementLine();


	CString  m_strX;
	CString  m_strY;
	CString  m_strAngle;
	CString  m_strDir;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTLINE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementLineKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual CString ReturnXml();
//私有成员变量
private:

//私有成员变量访问方法
public:
};

