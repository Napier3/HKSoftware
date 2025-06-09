#include "StdAfx.h"
#include "GbWzdAiMacroPara.h"
#include "GbWzdAiSwitch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CGbWzdAiValueSet
CGbWzdAiValueSet::CGbWzdAiValueSet(void)
{
	
}

CGbWzdAiValueSet::~CGbWzdAiValueSet(void)
{
}

long CGbWzdAiValueSet::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//xml_GetAttibuteValue(pXmlRWKeys->m_strIDKey, oNode, m_strID);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);

	return 0;
}

long CGbWzdAiValueSet::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//xml_SetAttributeValue(pXmlRWKeys->m_strIDKey, oElement, m_strID);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);

	return 0;
}

long CGbWzdAiValueSet::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);


	return 0;
}

CBaseObject* CGbWzdAiValueSet::Clone()
{
	CGbWzdAiValueSet* pNew = new CGbWzdAiValueSet();
	Copy(pNew);

	return pNew;
}

void CGbWzdAiValueSet::SetParaValue(CDvmData *pPara, CDvmData *pDvmData, CSttGuideBook *pSttGuideBook)
{
	if (m_strType == _T("value"))
	{
		pPara->m_strValue = m_strValue;
		return;
	}

	if (m_strType == _T("dvm-data"))
	{
		pPara->m_strValue = pDvmData->m_strValue;
	}

	pPara->m_strValue = m_strValue;
}

DWORD CGbWzdAiValueSet::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//CGbWzdAiMacroPara
CGbWzdAiMacroPara::CGbWzdAiMacroPara(void)
{
	m_pMacroParaRef = NULL;
	m_strName = _T("");

	m_pScript = NULL;
	m_pValSet = NULL;
	m_dwValue = 0;
}

CGbWzdAiMacroPara::~CGbWzdAiMacroPara(void)
{
}

long CGbWzdAiMacroPara::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strExprKey, oNode, m_strExpr);

	
	return 0;
}

long CGbWzdAiMacroPara::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strExprKey, oElement, m_strExpr);

	return 0;
}

long CGbWzdAiMacroPara::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);


	return 0;
}

CExBaseObject* CGbWzdAiMacroPara::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiScriptKey)
	{
		m_pScript =  new CGbAiParaScript();
		return m_pScript;
	}
	else if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiValSetKey)
	{
		m_pValSet = new CGbWzdAiValueSet();
		return m_pValSet;
	}

	return NULL;
}

CExBaseObject* CGbWzdAiMacroPara::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GbWzdAiScript)
	{
		m_pScript = new CGbAiParaScript();
		return m_pScript;
	}
	else if (nClassID == GBCLASSID_GbWzdAiValSet)
	{
		m_pValSet = new CGbWzdAiValueSet();
		return m_pValSet;
	}

	return NULL;
}

CBaseObject* CGbWzdAiMacroPara::Clone()
{
	CGbWzdAiMacroPara* pNew = new CGbWzdAiMacroPara();
	Copy(pNew);

	return pNew;
}

DWORD CGbWzdAiMacroPara::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	if (m_dwValue)
	{
		return 0;
	}

	if (m_pScript != NULL)
	{
		m_pScript->ScptCal(pXMatchObj, TRUE, pSttGuideBook);

		if (m_pScript->m_dwValue == 0)
		{
			return m_pScript->m_dwValue;
		}

		m_dwValue = 1;
		CDvmData *pData = GbAiGetMacroPara(this);

		if (pData == NULL)
		{
			return m_pScript->m_dwValue;
		}

		SetParaValue(pData, (CDvmData*)((CXMatchObject*)pXMatchObj)->m_pRefObject, pSttGuideBook);

		return m_pScript->m_dwValue;
	}

	return 0;
}

void CGbWzdAiMacroPara::SetParaValue(CDvmData *pPara, CDvmData *pDvmData, CSttGuideBook *pSttGuideBook)
{
	if (m_pValSet != NULL)
	{
		m_pValSet->SetParaValue(pPara, pDvmData, pSttGuideBook);
		return;
	}

	if (m_pScript->m_strDataType == _T("BOOL"))
	{
		pPara->m_strValue = _T("1");
		return;
	}

	if (m_strExpr.GetLength() <= 5)
	{
		pPara->m_strValue = pDvmData->m_strValue;
		return;
	}

	float fValue = 1;

	if (pSttGuideBook->GetDataValueByID(m_strExpr, fValue))
	{
		float fCurr = CString_To_double(pDvmData->m_strValue);
		fCurr = fCurr * fValue;
		pPara->m_strValue.Format(_T("%f"), fCurr);
	}
	else
	{
		pPara->m_strValue = pDvmData->m_strValue;
	}
}

void CGbWzdAiMacroPara::InitGbAiDataKey(CXKeyDB *pKeyDB)
{
	POS pos = GetHeadPosition();
	CGbAiOptrInterface *p = NULL;

	while (pos != NULL)
	{
		p = (CGbAiOptrInterface *)GetNext(pos);
		p->InitGbAiDataKey(pKeyDB);
	}
}

void CGbWzdAiMacroPara::InitMacroPara(CDataGroup *pMacroParas)
{
	m_pMacroParaRef = (CDvmData *)pMacroParas->FindByID(m_strID);

	if (m_pMacroParaRef == NULL)
	{
		m_pMacroParaRef = (CDvmData *)pMacroParas->FindByName(m_strName);
	}
}
