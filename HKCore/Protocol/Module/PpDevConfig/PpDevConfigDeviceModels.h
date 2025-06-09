#pragma once 

#include "PpDevConfigXMLKeys.h"
#include "PpDevConfigDeviceModel.h"

class CPpDevConfigDeviceModels : public CExBaseList
{
public:
	virtual UINT GetClassID()	{	return 0;}
	virtual BSTR GetXmlElementKey()	{	return CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strDeviceModelsKey;}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	CExBaseObject* FindDeviceModelDefine(const CString &strModelDefineFile);
};