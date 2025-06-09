#include "StdAfx.h"
#include "BbDataRanges.h"
#include "BbDataRange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBbDataRanges::CBbDataRanges(void)
{
}

CBbDataRanges::~CBbDataRanges(void)
{
}


long CBbDataRanges::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}

long CBbDataRanges::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseList::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	return 0;
}

CExBaseObject* CBbDataRanges::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strRangeKey)
	{
		return new CBbDataRange();
	}

	return NULL;
}
CExBaseObject* CBbDataRanges::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CBbDataRanges::IsEqualOwn(CBaseObject* pObj)
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

CBaseObject* CBbDataRanges::Clone()
{
	CBbDataRanges* pNew = new CBbDataRanges();
	Copy(pNew);
	return pNew;
}

BOOL CBbDataRanges::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CExBaseList::CopyOwn(pDest);
}


void CBbDataRanges::SetCount(long nCount)
{	
	CBbDataRange *p = NULL;
	long nIndex = 0;

	DeleteAll();

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		p = new CBbDataRange();
		p->SetParent(this);
		AddTail(p);
	}
}