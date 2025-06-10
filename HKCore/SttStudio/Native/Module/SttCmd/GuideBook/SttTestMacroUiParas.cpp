#include "stdafx.h"
#include "SttTestMacroUiParas.h"

CSttTestMacroUiParas::CSttTestMacroUiParas(void)
{
}

CSttTestMacroUiParas::~CSttTestMacroUiParas(void)
{
}

long CSttTestMacroUiParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

long CSttTestMacroUiParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetCDATA(oNode, m_strParaText);

	return 0;
}

long CSttTestMacroUiParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetCDATA(oXMLDoc, oElement, m_strParaText);

	return 0;
}

BOOL CSttTestMacroUiParas::IsEqual(CBaseObject* pObj)
{
	if(pObj != NULL)
	{
		CSttTestMacroUiParas* pTestMacroUiParas = (CSttTestMacroUiParas*)pObj;

		if(pTestMacroUiParas->m_strParaText == m_strParaText)
		{
			return TRUE;
		}
	}

	return FALSE;
}	

BOOL CSttTestMacroUiParas::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CSttTestMacroUiParas* pTestMacroUiParas = (CSttTestMacroUiParas*)pDesObj;
	pTestMacroUiParas->m_strParaText = m_strParaText;

	CExBaseObject::CopyOwn(pTestMacroUiParas);

	return TRUE;
}

CBaseObject* CSttTestMacroUiParas::Clone()
{
	CSttTestMacroUiParas* pTestMacroUiParas = new CSttTestMacroUiParas();
	Copy(pTestMacroUiParas);

	return pTestMacroUiParas;
}

BOOL CSttTestMacroUiParas::UpdateOwn(CBaseObject* pDest)
{
	CSttTestMacroUiParas* pTestMacroUiParas = (CSttTestMacroUiParas*)pDest;
	pTestMacroUiParas->m_strParaText = m_strParaText;

	return TRUE;
}
