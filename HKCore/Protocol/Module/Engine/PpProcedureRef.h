#pragma once
#include "../../../module/baseclass/exbaseobject.h"
#include "PpGlobalDefine.h"
#include "ProtocolXmlRWKeys.h"

class CPpProcedureRef :	public CExBaseObject
{
public:
	CPpProcedureRef(void);
	virtual ~CPpProcedureRef(void);

	CString m_strProcedureId;

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	virtual UINT GetClassID(){ return PPCLASSID_PPPROCEDUREREF; }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strProcedureRefKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
};
