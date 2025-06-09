#include "StdAfx.h"
#include "PpNodes.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpNodes::CPpNodes(long nType)
{
	m_nTypeID = nType;
}

CPpNodes::~CPpNodes(void)
{
}

BSTR CPpNodes::GetXmlElementKey()
{
	BSTR strRtn;
	switch (m_nTypeID)
	{
	case PPNODE_TYPE_RESPONSE:
		strRtn = CProtocolXmlRWKeys::g_pXmlRWKeys->m_strResponseKey;
		break;
	case PPNODE_TYPE_PROCESS:
		strRtn = CProtocolXmlRWKeys::g_pXmlRWKeys->m_strProcessKey;
		break;
	default:
		break;
	}
	return strRtn;
}

CExBaseObject* CPpNodes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpNodeKey)
	{
		return new CPpNode(m_nTypeID);
	}

	return NULL;
}

CExBaseObject* CPpNodes::CreateNewChild(long nClassID)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpNodes::IsEqualOwn(CBaseObject* pObj)
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

	if (m_nTypeID != ((CPpNodes*)pObj)->m_nTypeID)
	{
		return FALSE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CPpNodes::Clone()
{
	CPpNodes* pNew = new CPpNodes(m_nTypeID);
	Copy(pNew);
	return pNew;
}

BOOL CPpNodes::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpNodes*)pDest)->m_nTypeID = m_nTypeID;

	return CExBaseList::CopyOwn(pDest);
}