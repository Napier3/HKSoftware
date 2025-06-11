#pragma once
#include "ExBaseList.h"
#include "PpTtPackage.h"
#include "PpParsePackage.h"
#include "PpProducePackage.h"

class CPpPackages :	public CExBaseList
{
public:
	CPpPackages(void);
	virtual ~CPpPackages(void);

public:
	virtual UINT GetClassID() {        return PPCLASSID_PPPAKAGES;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackagesKey;     }

	// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	void InitPackageAllVariables(UINT nClassID);
};
