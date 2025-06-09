//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementArc.h  CCharElementArc

#pragma once

#include "CharacteristicGlobal.h"



class CCharElementArc : public CCharElement
{
public:
	CCharElementArc();
	virtual ~CCharElementArc();


	CString  m_strX;
	CString  m_strY;
	CString  m_strRadius;
	CString  m_strStartAngle;
	CString  m_strEndAngle;
	CString  m_strDir;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTARC;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementArcKey();     }
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

