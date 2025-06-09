#include "StdAfx.h"
#include "PpProcedureRef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpProcedureRef::CPpProcedureRef(void)
{
	m_strProcedureId = L"";
}
long CPpProcedureRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strProcedureRefIDKey,oNode,m_strProcedureId);

	return 0;
}
CPpProcedureRef::~CPpProcedureRef(void)
{
}

long CPpProcedureRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	xml_SetAttributeValue(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strProcedureRefIDKey,oElement,m_strProcedureId);

	return 0;
}

long CPpProcedureRef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpProcedureRef::IsEqualOwn(CBaseObject* pObj)
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

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CPpProcedureRef::Clone()
{
	CPpProcedureRef* pNew = new CPpProcedureRef();
	Copy(pNew);
	return pNew;
}

BOOL CPpProcedureRef::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpProcedureRef*)pDest)->m_strProcedureId = m_strProcedureId;

	return CExBaseObject::CopyOwn(pDest);
}