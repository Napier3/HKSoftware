#include "StdAfx.h"
#include "JobGuide.h"
#include "GbXMLKeys.h"
#include "Items.h"
#include "Safety.h"
#include "../XLanguageResourceAts.h"

CJobGuide::CJobGuide(void)
{
	m_strName = g_sLangTxt_TaskGuide2/*L"作业指导"*/;
	m_strID = L"JobGuide";
}

CJobGuide::~CJobGuide(void)
{
	int i = 0;
}


long CJobGuide::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	return 0;
}

long CJobGuide::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	return 0;
}

long CJobGuide::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbItemBase::SerializeOwn(oBinaryBuffer);
	return 0;
}

CExBaseObject* CJobGuide::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strItemsKey)
	{
		CItems *pItems = new CItems;
		return pItems;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSafetyKey)
	{
		CSafety* pSafety = new CSafety;
		return pSafety;
	}

	return CGbItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CJobGuide::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_ITEMS)
	{
		CItems *pItems = new CItems;
		return pItems;
	}
	else if (nClassID == GBCLASSID_SAFETY)
	{
		CSafety* pSafety = new CSafety;
		return pSafety;
	}

	return CGbItemBase::CreateNewChild(nClassID);
}

CBaseObject* CJobGuide::Clone()
{
	CJobGuide* pJobGuide = new CJobGuide();
	Copy(pJobGuide);

	return pJobGuide;
}


BOOL CJobGuide::CanPaste(CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();

	if (nClassID == GBCLASSID_SAFETY)
	{
		return TRUE;
	}

	if (nClassID == GBCLASSID_ITEMS)
	{
		if (GbItems_HasItem((CExBaseList*)pObj, GBCLASSID_MACROTEST))
		{
			return FALSE;
		}

		if (GbItems_HasItem((CExBaseList*)pObj, GBCLASSID_MACROCHARITEMS))
		{
			return FALSE;
		}

		if (GbItems_HasItem((CExBaseList*)pObj, GBCLASSID_COMMCMD))
		{
			return FALSE;
		}

		if (GbItems_HasItem((CExBaseList*)pObj, GBCLASSID_SYSPARAEDIT))
		{
			return FALSE;
		}

		return TRUE;
	}
	
	return FALSE;
}

