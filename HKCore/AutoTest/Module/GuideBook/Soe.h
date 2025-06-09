#pragma once

#include "GuideBookDefine.h"

class CSoe :public CExBaseObject
{
public:
	CSoe(void);
	virtual ~CSoe(void);

	static CSoe* _New(CBaseObject *pParent=NULL)
	{
		CSoe *pNew = new CSoe();
		return pNew;
	}

public:
	//attribute
	CString m_strValue;
	CString m_strTime;

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_SOE;	}
	virtual BSTR GetXmlElementKey() ;

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

protected:

private:

};