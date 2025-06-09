#include "StdAfx.h"
#include "Analog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CAnalog::CAnalog(void)
{
	m_strType = _T("analog");
	m_strUnit = _T("");
	m_strValue = _T("0");
}

CAnalog::~CAnalog(void)
{
}

long CAnalog::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strUnitKey,oNode,m_strUnit);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oNode,m_strType);
	return 0;
}

long CAnalog::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strUnitKey,(_bstr_t)m_strUnit);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,(_bstr_t)m_strType);
	return 0;
}

long CAnalog::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_strUnit);
		BinarySerializeCalLen(oBinaryBuffer,m_strType);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_strUnit);
		BinarySerializeRead(oBinaryBuffer,m_strType);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strUnit);
		BinarySerializeWrite(oBinaryBuffer,m_strType);
	}
	return 0;
}

BOOL CAnalog::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CAnalog::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CAnalog* pAnalog = (CAnalog*)pDesObj;
	pAnalog->m_strUnit = m_strUnit;
	pAnalog->m_strType = m_strType;

	CExBaseObject::CopyOwn(pAnalog);

	return TRUE;
}

CBaseObject* CAnalog::Clone()
{
	CAnalog* pAnalog = new CAnalog();
	Copy(pAnalog);

	return pAnalog;
}

BSTR CAnalog::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strAnalogKey;     
}