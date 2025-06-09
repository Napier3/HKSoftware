#pragma once
#include "PpPackage.h"
#include "PpScript.h"

#include "WBbDataSets.h"

class CPpProducePackage :	public CPpPackage
{
public:
	CPpProducePackage(void);
	virtual ~CPpProducePackage(void);

public:
	virtual UINT GetClassID() {        return PPCLASSID_PPPRODUCEPACKGE;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strWPackageKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

public:
	CPpScript *m_pOnBbPckScript;
	CWBbDataSets* GetWBbDataSets();
	CPpScript* CreateOnBbPckScript();

public:
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
};
