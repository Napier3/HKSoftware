#include "StdAfx.h"
#include "GbtDataTraverseObj.h"
#include "..\..\XLanguageResourceAts.h"
CGbtDataTraverseObj::CGbtDataTraverseObj(void)
{
	m_pDataRef = NULL;
	SetModeType(GBTDATATRAVERSE_MODE_VALRAMP_ID);

	m_dBeginVal = 0;
	m_dStep     = 0;
	m_nSteps    = 0;
}

CGbtDataTraverseObj::~CGbtDataTraverseObj(void)
{
}
// 
// long CGbtDataTraverseObj::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
// //	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strUnitKey,oNode,m_strUnit);
// //	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oNode,m_strType);
// 	return 0;
// }
// 
// long CGbtDataTraverseObj::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
// //	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strUnitKey,(_bstr_t)m_strUnit);
// //	oElement->setAttribute(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,(_bstr_t)m_strType);
// 	return 0;
// }
// 
// BOOL CGbtDataTraverseObj::CopyOwn(CBaseObject* pDesObj)
// {
// 	ASSERT(pDesObj != NULL);
// 	if(pDesObj == this)
// 		return TRUE;
// 
// 	CGbtDataTraverseObj* pGbtDataTraverseObj = (CGbtDataTraverseObj*)pDesObj;
// // 	GbtDataTraverseObj->m_strUnit = m_strUnit;
// // 	GbtDataTraverseObj->m_strType = m_strType;
// 
// 	CExBaseObject::CopyOwn(pGbtDataTraverseObj);
// 
// 	return TRUE;
// }
// 
// CBaseObject* CGbtDataTraverseObj::Clone()
// {
// 	CGbtDataTraverseObj* pGbtDataTraverseObj = new CGbtDataTraverseObj();
// 	Copy(pGbtDataTraverseObj);
// 
// 	return pGbtDataTraverseObj;
// }
// 
// BSTR CGbtDataTraverseObj::GetXmlElementKey()
// {
// 	return CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataTraverseObjKey;     
// }

void CGbtDataTraverseObj::SetModeType(const CString &strModelTypeID)
{
	if (strModelTypeID == GBTDATATRAVERSE_MODE_DATASET_ID)
	{
		m_dwModeType = GBTDATATRAVERSE_MODE_DATASET_INDEX;
		m_strModeType = strModelTypeID;
		return;
	}

	if (strModelTypeID == GBTDATATRAVERSE_MODE_VALRAMP_ID)
	{
		m_dwModeType = GBTDATATRAVERSE_MODE_VALRAMP_INDEX;
		m_strModeType = strModelTypeID;
		return;
	}

	m_dwModeType = GBTDATATRAVERSE_MODE_VALRAMP_INDEX;
	m_strModeType = GBTDATATRAVERSE_MODE_VALRAMP_ID;
}

void CGbtDataTraverseObj::SetModeType(DWORD dwtrModelTypeID)
{
	if (dwtrModelTypeID == GBTDATATRAVERSE_MODE_DATASET_INDEX)
	{
		m_dwModeType = GBTDATATRAVERSE_MODE_DATASET_INDEX;
		m_strModeType = GBTDATATRAVERSE_MODE_DATASET_ID;
		return;
	}

	if (dwtrModelTypeID == GBTDATATRAVERSE_MODE_VALRAMP_INDEX)
	{
		m_dwModeType = GBTDATATRAVERSE_MODE_VALRAMP_INDEX;
		m_strModeType = GBTDATATRAVERSE_MODE_VALRAMP_ID;
		return;
	}

	m_dwModeType = GBTDATATRAVERSE_MODE_VALRAMP_INDEX;
	m_strModeType = GBTDATATRAVERSE_MODE_VALRAMP_ID;
}

CString CGbtDataTraverseObj::GetModelTypeName()
{
	if (m_dwModeType == GBTDATATRAVERSE_MODE_DATASET_INDEX)
	{
		return /*GBTDATATRAVERSE_MODE_DATASET_NAME*/g_sLangTxt_DatasetTraverse;
	}

	if (m_dwModeType == GBTDATATRAVERSE_MODE_VALRAMP_INDEX)
	{
		return /*GBTDATATRAVERSE_MODE_VALRAMP_NAME*/g_sLangTxt_NumberArithmetic;
	}

	m_dwModeType = GBTDATATRAVERSE_MODE_VALRAMP_INDEX;
	m_strModeType = GBTDATATRAVERSE_MODE_VALRAMP_ID;
	return /*GBTDATATRAVERSE_MODE_VALRAMP_NAME*/g_sLangTxt_NumberArithmetic;
}
