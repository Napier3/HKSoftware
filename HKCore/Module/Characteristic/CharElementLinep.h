//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLinep.h  CCharElementLinep

#pragma once

#include "CharacteristicGlobal.h"



class CCharElementLinep : public CCharElement
{
public:
	CCharElementLinep();
	virtual ~CCharElementLinep();


	CString  m_strZ;
	CString  m_strPh;
	CString  m_strAngle;
	CString  m_strDir;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTLINEP;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementLinepKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

	virtual CString ReturnXml();
//私有成员变量
private:

//私有成员变量访问方法
public:
};

