#include "StdAfx.h"
#include "TestMacroCharParas.h"

CTestMacroCharParas::CTestMacroCharParas(void)
{
}

CTestMacroCharParas::~CTestMacroCharParas(void)
{
}

long CTestMacroCharParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

long CTestMacroCharParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetCDATA(oNode, m_strParaText);

	return 0;
}

long CTestMacroCharParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetCDATA(oXMLDoc, oElement, m_strParaText);

	return 0;
}

BOOL CTestMacroCharParas::IsEqual(CBaseObject* pObj)
{
	if(pObj != NULL)
	{
		CTestMacroCharParas* pTestMacroCharParas = (CTestMacroCharParas*)pObj;

		if(pTestMacroCharParas->m_strParaText == m_strParaText)
		{
			return TRUE;
		}
	}

	return FALSE;
}	

BOOL CTestMacroCharParas::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CTestMacroCharParas* pTestMacroCharParas = (CTestMacroCharParas*)pDesObj;
	pTestMacroCharParas->m_strParaText = m_strParaText;

	CExBaseObject::CopyOwn(pTestMacroCharParas);

	return TRUE;
}

CBaseObject* CTestMacroCharParas::Clone()
{
	CTestMacroCharParas* pTestMacroCharParas = new CTestMacroCharParas();
	Copy(pTestMacroCharParas);

	return pTestMacroCharParas;
}

BOOL CTestMacroCharParas::UpdateOwn(CBaseObject* pDest)
{
	CTestMacroCharParas* pTestMacroCharParas = (CTestMacroCharParas*)pDest;
	pTestMacroCharParas->m_strParaText = m_strParaText;

	return TRUE;
}