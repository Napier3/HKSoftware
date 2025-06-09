#include "StdAfx.h"
#include "PpProcedureRefs.h"
#include "PpProcedureRef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpProcedureRefs::CPpProcedureRefs(void)
{
	
}

CPpProcedureRefs::~CPpProcedureRefs(void)
{
}
CExBaseObject* CPpProcedureRefs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strProcedureRefKey)
	{
		return new CPpProcedureRef();
	}

	return NULL;
}

CExBaseObject* CPpProcedureRefs::CreateNewChild(long nClassID)
{
	return NULL;
}
//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpProcedureRefs::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CPpProcedureRefs::Clone()
{
	CPpProcedureRefs* pNew = new CPpProcedureRefs();
	Copy(pNew);
	return pNew;
}

BOOL CPpProcedureRefs::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CExBaseList::CopyOwn(pDest);
}
