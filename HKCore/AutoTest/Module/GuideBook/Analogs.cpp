#include "StdAfx.h"
#include "Analogs.h"
#include "Analog.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CAnalogs::CAnalogs(void)
{
	m_strName = CXLanguageResourceAtsBase::g_sLangTxt_AnalogValue/*L"Ä£ÄâÁ¿"*/;

}

CAnalogs::~CAnalogs(void)
{
}

long CAnalogs::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CAnalogs::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CAnalogs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

CExBaseObject* CAnalogs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strAnalogKey)
	{
		CAnalog* pObject = new CAnalog;
		return pObject;
	}

	return NULL;
}

CExBaseObject* CAnalogs::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_ANALOG)
	{
		CAnalog* pObject = new CAnalog;
		return pObject;
	}

	return NULL;
}

CBaseObject* CAnalogs::Clone()
{
	CAnalogs* pAnalogs = new CAnalogs();
	Copy(pAnalogs);

	return pAnalogs;
}

BOOL CAnalogs::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_ANALOG)
	{
		return TRUE;
	}

	return FALSE;
}

void CAnalogs::InitDataSet(CDataSet *pDataSet)
{
	ASSERT(pDataSet != NULL);

	if (pDataSet == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CAnalog *pTemp = NULL;
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pTemp = (CAnalog *)GetNext(pos);
		pData = pDataSet->AddNewDataObj(pTemp->m_strName, pTemp->m_strID);
		pData->m_strUnit = pTemp->m_strUnit;
		pData->m_strDataType = pTemp->m_strType;
		pData->m_strValue = pTemp->m_strValue;
	}
}

void CAnalogs::InitByDataSet(CDataSet *pDataSet, BOOL bAppend)
{
	ASSERT(pDataSet != NULL);

	if (pDataSet == NULL)
	{
		return;
	}

	if ((pDataSet->m_strType.Find(_T("Ain")) < 0) && (pDataSet->m_strID.Find(_T("Ain")) < 0))
	{
		return;
	}

	if (!bAppend)
	{
		DeleteAll();
	}

	POS pos = pDataSet->GetHeadPosition();
	CAnalog *pTemp = NULL;
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDataObj *)pDataSet->GetNext(pos);
		pTemp = new CAnalog();
		pTemp->m_strName = pData->m_strName;
		pTemp->m_strID = pData->m_strID;
		pTemp->m_strUnit = pData->m_strUnit;
		pTemp->m_strType = pData->m_strDataType;
		pTemp->m_strValue = pData->m_strValue;
		AddNewChild(pTemp);
	}	
}

