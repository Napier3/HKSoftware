#include "stdafx.h"
#include "ItemMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbWzdAutoItems::CGbWzdAutoItems()
{
	
}

CGbWzdAutoItems::~CGbWzdAutoItems()
{

}

long CGbWzdAutoItems::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		
	}

	return 0;
}

long CGbWzdAutoItems::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CGbWzdAutoItems::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

BOOL CGbWzdAutoItems::IsEqual(CBaseObject* pObj)
{
	if(pObj != NULL)
	{
		CGbWzdAutoItems* pSingleItem = (CGbWzdAutoItems*)pObj;

		if(CExBaseObject::IsEqual(pObj))
		{
			return TRUE;
		}
	}
	
	return FALSE;
}	

BOOL CGbWzdAutoItems::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CExBaseObject::CopyOwn(pDesObj);

	return TRUE;
}

CBaseObject* CGbWzdAutoItems::Clone()
{
	CGbWzdAutoItems* pItems = new CGbWzdAutoItems();
	Copy(pItems);

	return pItems;
}

CExBaseObject* CGbWzdAutoItems::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strwzdAutoItemsKey)
	{
		pNew = new CGbWzdAutoItems();
	}

	else if (strClassID == pXmlKeys->m_strwzdAutoSafetyKey)
	{
		pNew = new CGbWzdAutoSafety();
	}

	return pNew;
}

CExBaseObject* CGbWzdAutoItems::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBCLASSID_GBWZDAUTOITEMS)
	{
		pNew = new CGbWzdAutoItems();
	}

	else if (nClassID == GBCLASSID_GBWZDAUTOSAFETY)
	{
		pNew = new CGbWzdAutoSafety();
	}

	return pNew;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CGbWzdAutoSafety::CGbWzdAutoSafety()
{
	m_nManyRptTestMode = 0;
}

CGbWzdAutoSafety::~CGbWzdAutoSafety()
{

}

long CGbWzdAutoSafety::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strItemType);
		BinarySerializeCalLen(oBinaryBuffer, m_nManyRptTestMode);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer, m_strItemType);
		BinarySerializeRead(oBinaryBuffer, m_nManyRptTestMode);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strItemType);
		BinarySerializeWrite(oBinaryBuffer, m_nManyRptTestMode);
	}

	return 0;
}

long CGbWzdAutoSafety::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strItemTypeKey, oNode, m_strItemType);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strManyDeviceTestModeKey,oNode,m_nManyRptTestMode);

	return 0;
}

long CGbWzdAutoSafety::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strItemTypeKey, oElement, m_strItemType);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strManyDeviceTestModeKey,oElement,m_nManyRptTestMode);

	return 0;
}

BOOL CGbWzdAutoSafety::IsEqual(CBaseObject* pObj)
{
	if(pObj != NULL)
	{
		CGbWzdAutoSafety* pSafety = (CGbWzdAutoSafety*)pObj;

		if(CExBaseObject::IsEqual(pObj) && pSafety->m_strItemType == m_strItemType && pSafety->m_nManyRptTestMode == m_nManyRptTestMode)
		{
			return TRUE;
		}
	}

	return FALSE;
}	

BOOL CGbWzdAutoSafety::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CGbWzdAutoSafety* pSafety = (CGbWzdAutoSafety*)pDesObj;
	pSafety->m_strItemType = m_strItemType;
	pSafety->m_nManyRptTestMode = m_nManyRptTestMode;

	CExBaseObject::CopyOwn(pSafety);

	return TRUE;
}

CBaseObject* CGbWzdAutoSafety::Clone()
{
	CGbWzdAutoSafety* pSafety = new CGbWzdAutoSafety();
	Copy(pSafety);

	return pSafety;
}

CExBaseObject* CGbWzdAutoSafety::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strScriptInitKey)
	{
		pNew = new CScriptTextInit();
	}

	else if (strClassID == pXmlKeys->m_strScriptResultKey)
	{
		pNew = new CScriptTextResult();
	}

	return pNew;
}

CExBaseObject* CGbWzdAutoSafety::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == GBCLASSID_SCRIPTTEXT_INIT)
	{
		pNew = new CScriptTextInit();
	}

	else if (nClassID == GBCLASSID_SCRIPTTEXT_RESULT)
	{
		pNew = new CScriptTextResult();
	}

	return pNew;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CTestItemMngr::CTestItemMngr()
{

}

CTestItemMngr::~CTestItemMngr()
{

}

long CTestItemMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);
	return 0;
}

long CTestItemMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CTestItemMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

BOOL CTestItemMngr::IsEqual(CBaseObject* pObj)
{
	return CExBaseObject::IsEqual(pObj);
}

BOOL CTestItemMngr::CopyOwn(CBaseObject* pDesObj)
{
	CExBaseObject::CopyOwn(pDesObj);
	return TRUE;
}

CBaseObject* CTestItemMngr::Clone()
{
	CTestItemMngr* pObj = new CTestItemMngr();
	Copy(pObj);

	return pObj;
}


CExBaseObject* CTestItemMngr::CreateNewChild(long nClassID)
{
	return new CGbWzdAutoItems();
}

CExBaseObject* CTestItemMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return new CGbWzdAutoItems();
}