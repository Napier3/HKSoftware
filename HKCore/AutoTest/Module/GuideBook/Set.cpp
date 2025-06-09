#include "StdAfx.h"
#include "Set.h"
#include "GuideBook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSet::CSet(void)
{
	m_strDataType = _T("float");
	m_bNewCreate = FALSE;
}

CSet::~CSet(void)
{
}

long CSet::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strValueKey,oNode,m_strValue);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strUnitKey,oNode,m_strUnit);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDataTypeKey,oNode,m_strDataType);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strMinValKey,oNode,m_strMinVal);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strMaxValKey,oNode,m_strMaxVal);
	
	try
	{
		xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDefaultValueKey,oNode,m_strDefaultValue);
	}
	catch (...)
	{
		xml_GetAttibuteValue(_bstr_t("defalut-value"),oNode,m_strDefaultValue);	
	}

	 
	return 0;
}

long CSet::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

#ifdef GUIDEBOOK_DEV_MODE
	//把DefaultValue保存到Value中;
	m_strValue = m_strDefaultValue;
#endif

	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strValueKey,(_bstr_t)m_strValue);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strUnitKey,(_bstr_t)m_strUnit);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strDataTypeKey,(_bstr_t)m_strDataType);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strMinValKey,(_bstr_t)m_strMinVal);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strMaxValKey,(_bstr_t)m_strMaxVal);
	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strDefaultValueKey,(_bstr_t)m_strDefaultValue);

	return 0;
}

long CSet::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_strValue);
		BinarySerializeCalLen(oBinaryBuffer,m_strUnit);
		BinarySerializeCalLen(oBinaryBuffer,m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer,m_strMinVal);
		BinarySerializeCalLen(oBinaryBuffer,m_strMaxVal);
		BinarySerializeCalLen(oBinaryBuffer,m_strDefaultValue);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_strValue);
		BinarySerializeRead(oBinaryBuffer,m_strUnit);
		BinarySerializeRead(oBinaryBuffer,m_strDataType);
		BinarySerializeRead(oBinaryBuffer,m_strMinVal);
		BinarySerializeRead(oBinaryBuffer,m_strMaxVal);
		BinarySerializeRead(oBinaryBuffer,m_strDefaultValue);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strValue);
		BinarySerializeWrite(oBinaryBuffer,m_strUnit);
		BinarySerializeWrite(oBinaryBuffer,m_strDataType);
		BinarySerializeWrite(oBinaryBuffer,m_strMinVal);
		BinarySerializeWrite(oBinaryBuffer,m_strMaxVal);
		BinarySerializeWrite(oBinaryBuffer,m_strDefaultValue);
	}
	return 0;
}

BOOL CSet::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CSet::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CSet* pSet = (CSet*)pDesObj;
	pSet->m_strValue = m_strValue;
	pSet->m_strDefaultValue = m_strDefaultValue;
	pSet->m_strUnit = m_strUnit;
	pSet->m_strDataType = m_strDataType;
	pSet->m_strMinVal = m_strMinVal;
	pSet->m_strMaxVal = m_strMaxVal;

	CExBaseObject::CopyOwn(pSet);

	return TRUE;
}

CBaseObject* CSet::Clone()
{
	CSet* pSet = new CSet();
	Copy(pSet);

	return pSet;
}

BSTR CSet::GetXmlElementKey()
 {
	 return CGbXMLKeys::g_pGbXMLKeys->m_strSetKey;     
}

void  CSet::GetIDForPath(CString &strID, const CString &strPathSp)
{
	CExBaseObject *pParent = (CExBaseObject*)GetParent();
	strID.Format(_T("%s%s%s"), pParent->m_strID, strPathSp, m_strID);
}

void CSet::InitValueByData(CShortData *pData)
{
	m_strValue = pData->m_strValue;
}

void CSet::WriteToData(CShortData *pData)
{
	pData->m_strName = m_strName;
	pData->m_strID = m_strID;
	pData->m_strValue = m_strValue;
}

void CSet::InitAfterRead()
{
	m_dMinVal = CString_To_double(m_strMinVal);
	m_dMaxVal = CString_To_double(m_strMaxVal);
}

CDataTypes* CSet::GetDataTypes()
{
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
	//2017-10-29 m_strTestMacroFile==>m_strTestMacroFileID
	CTestMacros* pMacros = TM_GetTestMacros(pGuideBook->m_strTestMacroFileID);

	if (pMacros != NULL)
	{
		return pMacros->GetDataTypes();
	}
	else
	{
		return NULL;
	}
}

