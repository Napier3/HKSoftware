#pragma once

#include "GuideBookDefine.h"
#include "Analog.h"
#include "DataSet.h"

class CAnalogs :public CExBaseList
{
public:
	CAnalogs(void);
	virtual ~CAnalogs(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()			{		return GBCLASSID_ANALOGS;	}
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::g_pGbXMLKeys->m_strAnalogsKey;     }

	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

protected:

private:

public:
	void InitDataSet(CDataSet *pDataSet);
	void InitByDataSet(CDataSet *pDataSet, BOOL bAppend=FALSE);
};

