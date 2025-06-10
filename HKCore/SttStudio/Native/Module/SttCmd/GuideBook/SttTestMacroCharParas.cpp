#include "stdafx.h"
#include "SttTestMacroCharParas.h"

CSttTestMacroCharParas::CSttTestMacroCharParas(void)
{
}

CSttTestMacroCharParas::~CSttTestMacroCharParas(void)
{
}

long CSttTestMacroCharParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strParaText);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer, m_strParaText);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strParaText);
	}

	return 0;
}

long CSttTestMacroCharParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetCDATA(oNode, m_strParaText);

	return 0;
}

long CSttTestMacroCharParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetCDATA(oXMLDoc, oElement, m_strParaText);

	return 0;
}

BOOL CSttTestMacroCharParas::IsEqual(CBaseObject* pObj)
{
	if(pObj != NULL)
	{
		CSttTestMacroCharParas* pTestMacroCharParas = (CSttTestMacroCharParas*)pObj;

		if(pTestMacroCharParas->m_strParaText == m_strParaText)
		{
			return TRUE;
		}
	}

	return FALSE;
}	

BOOL CSttTestMacroCharParas::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CSttTestMacroCharParas* pTestMacroCharParas = (CSttTestMacroCharParas*)pDesObj;
	pTestMacroCharParas->m_strParaText = m_strParaText;

	CExBaseObject::CopyOwn(pTestMacroCharParas);

	return TRUE;
}

CBaseObject* CSttTestMacroCharParas::Clone()
{
	CSttTestMacroCharParas* pTestMacroCharParas = new CSttTestMacroCharParas();
	Copy(pTestMacroCharParas);

	return pTestMacroCharParas;
}

BOOL CSttTestMacroCharParas::UpdateOwn(CBaseObject* pDest)
{
	CSttTestMacroCharParas* pTestMacroCharParas = (CSttTestMacroCharParas*)pDest;
	pTestMacroCharParas->m_strParaText = m_strParaText;

	return TRUE;
}
