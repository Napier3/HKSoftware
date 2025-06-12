#include "stdafx.h"
#include "GbWzdItemSetState.h"
#include "GbSmartGenWzd.h"


CGbWzdItemSetState::CGbWzdItemSetState(void)
{
	m_nSelect = 1;
	m_nEnable = 1;
	m_nShow = 1;
}

CGbWzdItemSetState::~CGbWzdItemSetState(void)
{

}


long CGbWzdItemSetState::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strParentItemsIDKey, oNode, m_strParentItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsNameKey, oNode, m_strItemsName);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsIDKey, oNode, m_strItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strSelectKey, oNode, m_nSelect);
	xml_GetAttibuteValue(pXmlKeys->m_strEnableKey, oNode, m_nEnable);
	xml_GetAttibuteValue(pXmlKeys->m_strShowKey, oNode, m_nShow);

	return 0;
}

long CGbWzdItemSetState::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strParentItemsIDKey, oElement, m_strParentItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strItemsNameKey, oElement, m_strItemsName);
	xml_SetAttributeValue(pXmlKeys->m_strItemsIDKey, oElement, m_strItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strSelectKey, oElement, m_nSelect);
	xml_SetAttributeValue(pXmlKeys->m_strEnableKey, oElement, m_nEnable);
	xml_SetAttributeValue(pXmlKeys->m_strShowKey, oElement, m_nShow);

	return 0;
}

long CGbWzdItemSetState::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDataGroup::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strDataType);
	}

	return 0;
}

BOOL CGbWzdItemSetState::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataGroup::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdItemSetState *p = (CGbWzdItemSetState*)pObj;

	if (m_strParentItemsID != p->m_strParentItemsID)
	{
		return FALSE;
	}

	if (m_strItemsName != p->m_strItemsName)
	{
		return FALSE;
	}

	if (m_strItemsID != p->m_strItemsID)
	{
		return FALSE;
	}

	if (m_nSelect != p->m_nSelect)
	{
		return FALSE;
	}

	if (m_nEnable != p->m_nEnable)
	{
		return FALSE;
	}

	if (m_nShow != p->m_nShow)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbWzdItemSetState::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CGbWzdItemSetState *p = (CGbWzdItemSetState*)pDest;
	p->m_strParentItemsID = m_strParentItemsID;
	p->m_strItemsName = m_strItemsName;
	p->m_strItemsID = m_strItemsID;
	p->m_nSelect = m_nSelect;
	p->m_nEnable = m_nEnable;
	p->m_nShow = m_nShow;

	return TRUE;
}

CBaseObject* CGbWzdItemSetState::Clone()
{
	CGbWzdItemSetState *p = new CGbWzdItemSetState();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdItemSetState::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdItemSetState *p = new CGbWzdItemSetState();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdItemSetState::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	pNew = CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CGbWzdItemSetState::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		pNew = new CDataGroup();
	}
	else
	{
		pNew = CDataGroup::CreateNewChild(nClassID);
	}

	return pNew;
}

void CGbWzdItemSetState::GetItemPath(CString &strItemPath)
{
	if (m_strParentItemsID.GetLength() > 0)
	{
		strItemPath = m_strParentItemsID + _T("$");
	}

	strItemPath += m_strItemsID;
}
