#include "StdAfx.h"
#include "Binarys.h"
#include "Binary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBinarys::CBinarys(void)
{
}

CBinarys::~CBinarys(void)
{
	//DeleteAll();
}


long CBinarys::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CBinarys::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CBinarys::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

CExBaseObject* CBinarys::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strBinaryKey)
	{
		CBinary* pObject = new CBinary;
		return pObject;
	}

	return NULL;
}

CExBaseObject* CBinarys::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_BINARY)
	{
		CBinary* pObject = new CBinary;
		return pObject;
	}

	return NULL;
}

CBaseObject* CBinarys::Clone()
{
	CBinarys* pBinarys = new CBinarys();
	Copy(pBinarys);

	return pBinarys;
}

BOOL CBinarys::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_BINARY)
	{
		return TRUE;
	}

	return FALSE;
}


void CBinarys::InitDataSet(CDataSet *pDataSet)
{
	ASSERT(pDataSet != NULL);

	if (pDataSet == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CBinary *pTemp = NULL;
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pTemp = (CBinary *)GetNext(pos);
		pData = pDataSet->AddNewDataObj(pTemp->m_strName, pTemp->m_strID);
		pData->m_strValue = pTemp->m_strValue;
	}
}


void CBinarys::InitByDataSet(CDataSet *pDataSet, BOOL bAppend)
{
	ASSERT(pDataSet != NULL);

	if (pDataSet == NULL)
	{
		return;
	}

	if ((pDataSet->m_strType.Find(_T("Din")) < 0) && (pDataSet->m_strID.Find(_T("Din")) < 0))
	{
		return;
	}

	if (!bAppend)
	{
		DeleteAll();
	}

	POS pos = pDataSet->GetHeadPosition();
	CBinary *pTemp = NULL;
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDataObj *)pDataSet->GetNext(pos);
		pTemp = new CBinary();
		pTemp->m_strName = pData->m_strName;
		pTemp->m_strID = pData->m_strID;
		pTemp->m_strValue = pData->m_strValue;
		AddNewChild(pTemp);
	}	
}

