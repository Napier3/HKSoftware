#include "StdAfx.h"
#include "Binary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBinary::CBinary(void)
{
}

CBinary::~CBinary(void)
{
}

long CBinary::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strValueKey,oNode,m_strValue);
	return 0;
}

long CBinary::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strValueKey,(_bstr_t)m_strValue);
	return 0;
}

long CBinary::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_strValue);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_strValue);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strValue);
	}
	return TRUE;
}

BOOL CBinary::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CBinary::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CBinary* pBinary = (CBinary*)pDesObj;
	pBinary->m_strValue = m_strValue;

	CExBaseObject::CopyOwn(pBinary);
	
	return TRUE;
}

CBaseObject* CBinary::Clone()
{
	CBinary* pBinary = new CBinary();
	Copy(pBinary);

	return pBinary;
}

BSTR CBinary::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strBinaryKey;     
}