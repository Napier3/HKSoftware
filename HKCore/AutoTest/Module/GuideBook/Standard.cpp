#include "stdafx.h"
#include "Standard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CStandard::CStandard()
{

}

CStandard::~CStandard()
{

}

long CStandard::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strStandard);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer, m_strStandard);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strStandard);
	}

	return 0;
}

long CStandard::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	m_strStandard =oNode.Gettext();

	return 0;
}

long CStandard::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	oElement.put_text(m_strStandard);

	return 0;
}

BSTR CStandard::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strStandardKey;
}

BOOL CStandard::IsEqual(CBaseObject* pObj)
{
	return 0;
}

BOOL CStandard::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CExBaseObject::CopyOwn(pDesObj);
	CStandard* pStandard = (CStandard*)pDesObj;
	pStandard->m_strStandard = m_strStandard;

	return TRUE;
}

CBaseObject* CStandard::Clone()
{
	CStandard* pStandard = new CStandard();
	Copy(pStandard);
	return pStandard;
}