#pragma once

#include "GbtDataInterface.h"
#include "GbtData.h"

class CGbtDataInterfaces :public CExBaseList
{
public:
	CGbtDataInterfaces(void);
	virtual ~CGbtDataInterfaces(void);

	CGbtDatas *m_pGbtDatas;
public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GBTDATAINTERFACES;		}
	virtual BSTR GetXmlElementKey() {		return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataInterfacesKey ;	}

	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual void InitAfterRead();

public:
	void SetGbtDataInterfaceCount(long nCount);
	BOOL IsBatchGbtDataMode();

	CGbtDatas* CreateGbtDatas(CExBaseList *pDatas);
	CGbtDataInterface* CreateGbtDataInterface();
};

