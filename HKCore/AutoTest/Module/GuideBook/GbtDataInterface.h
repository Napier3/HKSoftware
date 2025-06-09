#pragma once

#include "GbtDataScript.h"

class CGbtDataInterface :public CExBaseList
{
public:
	CGbtDataInterface(void);
	virtual ~CGbtDataInterface(void);

	static CGbtDataInterface* _New(CExBaseObject *pParent)
	{
		CGbtDataInterface *pNew = new CGbtDataInterface();
		pNew->SetParent(pParent);
		return pNew;
	}
	
public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATAINTERFACE;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataInterfaceKey ;	}

	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

public:
	void InitByGbtDatas(CGbtDatas *pDatas);
};

