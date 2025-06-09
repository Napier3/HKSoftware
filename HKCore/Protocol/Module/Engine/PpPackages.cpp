#include "StdAfx.h"
#include "PpPackages.h"
#include "PpParsePackage.h"
#include "PpProducePackage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpPackages::CPpPackages(void)
{
}

CPpPackages::~CPpPackages(void)
{
}



CExBaseObject* CPpPackages::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strTPackageKey)
	{
		return new CPpTtPackage();
	}

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strRPackageKey)
	{
		return new CPpParsePackage();
	}

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strWPackageKey)
	{
		return new CPpProducePackage();
	}

	return NULL;
}

CExBaseObject* CPpPackages::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpPackages::IsEqualOwn(CBaseObject* pObj)
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

CBaseObject* CPpPackages::Clone()
{
	CPpPackages* pNew = new CPpPackages();
	Copy(pNew);
	return pNew;
}

BOOL CPpPackages::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CExBaseList::CopyOwn(pDest);
}

void CPpPackages::InitPackageAllVariables(UINT nClassID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CPpTtPackage *pTtPackage = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != nClassID)
		{
			continue;
		}

		if (nClassID == PPCLASSID_PPPARSEPACKGE || nClassID == PPCLASSID_PPPRODUCEPACKGE)
		{
			CPpPackage *pPackage = (CPpPackage*)p;
			pPackage->InitOwnAllVariables(TRUE);
		}
		else if (nClassID == PPCLASSID_PPTTPACKAGE)
		{
			CPpTtPackage *pTtPackage = (CPpTtPackage*)p;
			pTtPackage->InitOwnAllVariables();
		}
	}
}

