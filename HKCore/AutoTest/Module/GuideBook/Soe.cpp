#include "StdAfx.h"
#include "Soe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSoe::CSoe(void)
{
}

CSoe::~CSoe(void)
{
}

long CSoe::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strValueKey,oNode,m_strValue);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strUnitKey,oNode,m_strTime);
	return 0;
}

long CSoe::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strValueKey,(_bstr_t)m_strValue);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strTimeKey,(_bstr_t)m_strTime);
	return 0;
}

long CSoe::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_strValue);
		BinarySerializeCalLen(oBinaryBuffer,m_strTime);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_strValue);
		BinarySerializeRead(oBinaryBuffer,m_strTime);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strValue);
		BinarySerializeWrite(oBinaryBuffer,m_strTime);
	}
	return 0;
}

BOOL CSoe::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CSoe::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CSoe* pSoe = (CSoe*)pDesObj;
	pSoe->m_strValue = m_strValue;
	pSoe->m_strTime = m_strTime;

	CExBaseObject::CopyOwn(pSoe);

	return TRUE;
}

CBaseObject* CSoe::Clone()
{
	CSoe* pSoe = new CSoe();
	Copy(pSoe);

	return pSoe;
}

BSTR CSoe::GetXmlElementKey()
 {
	 return CGbXMLKeys::g_pGbXMLKeys->m_strSoeKey;     
}