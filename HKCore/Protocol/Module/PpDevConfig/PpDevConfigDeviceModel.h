#pragma once

#include "../../../Module/BaseClass/ExBaseObject.h"
#include "PpDevConfigXMLKeys.h"

class CPpDevConfigDeviceModel : public CExBaseObject
{
public:
	CPpDevConfigDeviceModel()	
	{
		m_pDeviceModel = NULL;
	}

	virtual ~CPpDevConfigDeviceModel()
	{
		if (m_pDeviceModel != NULL)
		{
			delete m_pDeviceModel;
			m_pDeviceModel = NULL;
		}
	}

public:
	CString m_strFile;
	CString m_strDeviceFile;

public:
	virtual UINT GetClassID()	{	return 0;}
	virtual BSTR GetXmlElementKey()	{	return CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strDevcieModelKey;}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	CExBaseObject* GetDeviceModel();
private:
	CExBaseObject *m_pDeviceModel;
};