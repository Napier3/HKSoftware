#pragma once
#include "ExBaseList.h"
#include "PpProcedure.h"
#include "PpPackageDetail.h"

class CPpProcedures :
	public CExBaseList
{
public:
	CPpProcedures(void);
	virtual ~CPpProcedures(void);

public:

	virtual UINT GetClassID(){ return PPCLASSID_PPPROCEDURES; };
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpProceduresKey;     }
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
	DWORD Run(CPpPackageDetail* &pDetail);
public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
};
