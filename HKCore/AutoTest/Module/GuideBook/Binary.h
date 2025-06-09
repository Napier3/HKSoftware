#pragma once

#include "GuideBookDefine.h"

class CBinary :public CExBaseObject
{
public:
	CBinary(void);
	virtual ~CBinary(void);

	static CBinary* _New(CBaseObject *pParent=NULL)
	{
		CBinary *pNew = new CBinary();
		return pNew;
	}

public:
	//attribute
	CString m_strValue;
public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()			{		return GBCLASSID_BINARY;	}
	virtual BSTR GetXmlElementKey() ;

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

protected:

private:

};