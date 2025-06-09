#include "StdAfx.h"
#include "Sets.h"
#include "Set.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSets::CSets(void)
{
	m_strName = CXLanguageResourceAtsBase::g_sLangTxt_SetValue/*L"Õû¶¨Öµ"*/;
}

CSets::~CSets(void)
{
}

long CSets::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CSets::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CSets::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

CExBaseObject* CSets::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSetKey)
	{
		CSet* pObject= new CSet;
		return pObject;
	}

	return NULL;
}

CExBaseObject* CSets::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_SET)
	{
		CSet* pObject= new CSet;
		return pObject;
	}

	return NULL;
}

CBaseObject* CSets::Clone()
{
	CSets* pSets = new CSets();
	Copy(pSets);

	return pSets;
}



BOOL CSets::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_SET)
	{
		return TRUE;
	}

	return FALSE;
}


BSTR CSets::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strSetsKey;     
}

void CSets::SetSetsValue(CValues* pValues)
{
	CValue *pValue = NULL;
	CSet *pSet = NULL;
	POS pos = pValues->GetHeadPosition();

	while (pos != NULL)
	{
		pValue = (CValue*)pValues->GetNext(pos);
		pSet = (CSet*)FindByID(pValue->m_strID);

		if (pSet != NULL && pValue->m_strValue.GetLength() > 0)
		{
			pSet->m_strValue = pValue->m_strValue;
		}
	}
}

void CSets::InitValueByDatas(CShortDatas *pDatas)
{
	CSet *pSet = NULL;
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pSet = (CSet *)GetNext(pos);
		pData = (CShortData*)pDatas->FindByName(pSet->m_strName);

		if (pData != NULL)
		{
			pSet->InitValueByData(pData);
			continue;
		}

		pData = (CShortData*)pDatas->FindByID(pSet->m_strID);

		if (pData != NULL)
		{
			pSet->InitValueByData(pData);
			continue;
		}
	}
}

void CSets::WriteToDatas(CShortDatas *pDatas)
{
	CSet *pSet = NULL;
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pSet = (CSet *)GetNext(pos);
		pData = new CShortData();
		pSet->WriteToData(pData);
		pDatas->AddNewChild(pData);
	}
}


void CSets::InitDataSet(CDataSet *pDataSet)
{
	ASSERT(pDataSet != NULL);

	if (pDataSet == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CSet *pTemp = NULL;
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pTemp = (CSet *)GetNext(pos);
		pData = pDataSet->AddNewDataObj(pTemp->m_strName, pTemp->m_strID);
		pData->m_strValue = pTemp->m_strValue;
		pData->m_strDefaultValue = pTemp->m_strDefaultValue;
		pData->m_strUnit = pTemp->m_strUnit;
		pData->m_strDataType = pTemp->m_strDataType;
// 		pData->m_strMinVal = pTemp->m_strMinVal;
// 		pData->m_strMaxVal = pTemp->m_strMaxVal;
	}
}


void CSets::InitByDataSet(CDataSet *pDataSet, BOOL bAppend)
{
	ASSERT(pDataSet != NULL);

	if (pDataSet == NULL)
	{
		return;
	}

	if (pDataSet->m_strType.Find(_T("Ena")) >= 0 || pDataSet->m_strType.Find(_T("Setting")) >= 0)
	{
	}
	else
	{
		if (pDataSet->m_strID.Find(_T("Ena")) >= 0 || pDataSet->m_strID.Find(_T("Setting")) >= 0)
		{

		}
		else
		{
			return;
		}
	}

	if (!bAppend)
	{
		DeleteAll();
	}

	POS pos = pDataSet->GetHeadPosition();
	CSet *pTemp = NULL;
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDataObj *)pDataSet->GetNext(pos);
		pTemp = new CSet();
		pTemp->m_strName = pData->m_strName;
		pTemp->m_strID = pData->m_strID;
		pTemp->m_strValue = pData->m_strValue;
		pTemp->m_strDefaultValue = pData->m_strDefaultValue;
		pTemp->m_strUnit = pData->m_strUnit;
		pTemp->m_strDataType = pData->m_strDataType;
// 		pTemp->m_dMinVal = pData->m_strMinVal;
// 		pTemp->m_dMaxVal = pData->m_strMaxVal;
		AddNewChild(pTemp);
	}	
}

