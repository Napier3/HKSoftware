#include "StdAfx.h"
#include "TestMacroUiParas.h"

CTestMacroUiParas::CTestMacroUiParas(void)
{
}

CTestMacroUiParas::~CTestMacroUiParas(void)
{
}

long CTestMacroUiParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

long CTestMacroUiParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetCDATA(oNode, m_strParaText);

	return 0;
}

long CTestMacroUiParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetCDATA(oXMLDoc, oElement, m_strParaText);

	return 0;
}

BOOL CTestMacroUiParas::IsEqual(CBaseObject* pObj)
{
	if(pObj != NULL)
	{
		CTestMacroUiParas* pTestMacroUiParas = (CTestMacroUiParas*)pObj;

		if(pTestMacroUiParas->m_strParaText == m_strParaText)
		{
			return TRUE;
		}
	}

	return FALSE;
}	

BOOL CTestMacroUiParas::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CTestMacroUiParas* pTestMacroUiParas = (CTestMacroUiParas*)pDesObj;
	pTestMacroUiParas->m_strParaText = m_strParaText;

	CExBaseObject::CopyOwn(pTestMacroUiParas);

	return TRUE;
}

CBaseObject* CTestMacroUiParas::Clone()
{
	CTestMacroUiParas* pTestMacroUiParas = new CTestMacroUiParas();
	Copy(pTestMacroUiParas);

	return pTestMacroUiParas;
}

BOOL CTestMacroUiParas::UpdateOwn(CBaseObject* pDest)
{
	CTestMacroUiParas* pTestMacroUiParas = (CTestMacroUiParas*)pDest;
	pTestMacroUiParas->m_strParaText = m_strParaText;

	return TRUE;
}