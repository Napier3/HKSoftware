#include "StdAfx.h"
#include "GbWzdAiDO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
CGbWzdAiDoAttr::CGbWzdAiDoAttr(void)
{
	m_strName = _T("DoAttr");
	m_strID= _T("DoAttr");
}

CGbWzdAiDoAttr::~CGbWzdAiDoAttr(void)
{
}

long CGbWzdAiDoAttr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAttrIDKey, oNode, m_strAttrID);
	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CGbWzdAiDoAttr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAttrIDKey, oElement, m_strAttrID);
	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);

	return 0;
}

long CGbWzdAiDoAttr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	//CExBaseObject::SerializeOwn(oBinaryBuffer);


	return 0;
}


CBaseObject* CGbWzdAiDoAttr::Clone()
{
	CGbWzdAiDoAttr* pNew = new CGbWzdAiDoAttr();
	Copy(pNew);

	return pNew;
}

CExBaseObject* CGbWzdAiDoAttr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataKeyKey)
	{
		return new CGbAiDataKey();
	}

	return NULL;
}

CExBaseObject* CGbWzdAiDoAttr::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GbWzdAiDATAKEY)
	{
		return new CGbAiDataKey();
	}

	return NULL;
}

void CGbWzdAiDoAttr::InitGbAiDataKey(CXKeyDB *pKeyDB)
{
	
}

DWORD CGbWzdAiDoAttr::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
CGbWzdAiDO::CGbWzdAiDO(void)
{
	m_strName = _T("Func");
	m_strID= _T("Func");
}

CGbWzdAiDO::~CGbWzdAiDO(void)
{
}

long CGbWzdAiDO::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbWzdAiDO::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CGbWzdAiDO::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);


	return 0;
}


CBaseObject* CGbWzdAiDO::Clone()
{
	CGbWzdAiDO* pNew = new CGbWzdAiDO();
	Copy(pNew);

	return pNew;
}

CExBaseObject* CGbWzdAiDO::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataKeyKey)
	{
		return new CGbWzdAiDoAttr();
	}

	return NULL;
}

CExBaseObject* CGbWzdAiDO::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GbWzdAiDOAttr)
	{
		return new CGbWzdAiDoAttr();
	}

	return NULL;
}

void CGbWzdAiDO::InitGbAiDataKey(CXKeyDB *pKeyDB)
{
	
}

DWORD CGbWzdAiDO::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	POS pos = GetHeadPosition();
	CGbWzdAiDoAttr *pDoAttr = NULL;

	if (bAllMatchMode)
	{
		m_dwValue = 1;

		while (pos != NULL)
		{
			pDoAttr = (CGbWzdAiDoAttr *)GetNext(pos);

			if (! pDoAttr->ScptCal(pXMatchObj, TRUE, pSttGuideBook))
			{
				m_dwValue = 0;
				break;
			}
		}
	}
	else
	{
		m_dwValue = 0;

		while (pos != NULL)
		{
			pDoAttr = (CGbWzdAiDoAttr *)GetNext(pos);

			if (pDoAttr->ScptCal(pXMatchObj, TRUE, pSttGuideBook))
			{
				m_dwValue++;
			}
		}

		pXMatchObj->m_dwItemData = m_dwValue;
	}

	return m_dwValue;
}
