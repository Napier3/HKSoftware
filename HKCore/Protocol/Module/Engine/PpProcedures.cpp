#include "StdAfx.h"
#include "PpProcedures.h"
#include "../XLanguageResourcePp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpProcedures::CPpProcedures(void)
{
	m_strName = g_sLangTxt_PrtcPrcsDfn/*_T("规约过程定义")*/;
}

CPpProcedures::~CPpProcedures(void)
{
}

CExBaseObject* CPpProcedures::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpProcedureKey)
	{
		return new CPpProcedure();
	}

	return NULL;
}

CExBaseObject* CPpProcedures::CreateNewChild(long nClassID)
{
	return NULL;
}


DWORD CPpProcedures::Run(CPpPackageDetail* &pDetail)
{
	return PpParseError();
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpProcedures::IsEqualOwn(CBaseObject* pObj)
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

CBaseObject* CPpProcedures::Clone()
{
	CPpProcedures* pNew = new CPpProcedures();
	Copy(pNew);
	return pNew;
}

BOOL CPpProcedures::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CExBaseList::CopyOwn(pDest);
}