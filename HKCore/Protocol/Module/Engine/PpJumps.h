#pragma once
#include "../../../module/baseclass/exbaselist.h"
#include "ProtocolXmlRWKeys.h"
#include "PpJump.h"

class CPpJumps :	public CExBaseList
{
public:
	CPpJumps(void);
	virtual ~CPpJumps(void);

public:
	virtual UINT GetClassID(){ return PPCLASSID_PPJUMPS; };
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpJumpsKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);


public:
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	CPpNode* RunJumps(CPpPackageDetail *pPkgDetail);

};
