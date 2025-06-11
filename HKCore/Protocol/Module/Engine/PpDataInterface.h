#pragma once
#include "ExBaseObject.h"
#include "ProtocolXmlRWKeys.h"
class CPpDataInterface :	public CExBaseObject
{
public:
	CPpDataInterface(const CString &strPackageDataID, const CString &strProcedureDataID)
	{
		m_strPackageDataID = strPackageDataID;
		m_strID = m_strPackageDataID;
		m_strProcedureDataID = strProcedureDataID;
	}

	CPpDataInterface(void);
	virtual ~CPpDataInterface(void);

	virtual UINT GetClassID(){ return PPCLASSID_PPDATAINTERFACE; };
	virtual BSTR GetXmlElementKey()  {  return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataMapKey;   }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	CString m_strPackageDataID;
	CString m_strProcedureDataID;
};
