#pragma once
#include "../../../module/baseclass/exbaselist.h"
#include "PpGlobalDefine.h"
#include "ProtocolXmlRWKeys.h"
class CPpProcedureRefs :	public CExBaseList
{
public:
	CPpProcedureRefs(void);
	virtual ~CPpProcedureRefs(void);

	CString m_strXmlKey;

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual UINT GetClassID(){ return PPCLASSID_PPPROCEDUREREFS; }
	virtual BSTR GetXmlElementKey()	{	return m_strXmlKey.AllocSysString();		};

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
};
