#pragma once 

#include "../../../Module/BaseClass/ExBaseList.h"
#include "PpDevConfigXMLKeys.h"
#include "PpDevConfigDeviceModels.h"

const CString g_strPpDevFileName = _T("PpDevConfig.xml");

CString GetPpDevConfigFile();

class CPpDevConfigFileMngr : public CExBaseList
{
private:
	CPpDevConfigFileMngr();
	virtual ~CPpDevConfigFileMngr()	{}

	static long g_nPpRefs;
	CString m_strXSINoNamespaceSchemaLocation;		//XSDÎÄ¼þ
	CString m_strXmlns;

public:
	CPpDevConfigDeviceModels* m_pDeviceModelFiles;

	static CPpDevConfigFileMngr* g_pPpDevConfigFileMngr;
	static CPpDevConfigFileMngr* Create();
	static void Release();

public:
	virtual UINT GetClassID()	{	return 0;}
	virtual BSTR GetXmlElementKey()	{	return CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strPpDevConfigKey;}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL SaveXmlFile(const CString& strFileName);
	virtual BOOL OpenXmlFile(const CString& strFileName);

};