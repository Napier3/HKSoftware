#include "StdAfx.h"
#include "GbWzdItemPaste.h"
#include "GbSmartGenWzd.h"


CGbWzdItemPaste::CGbWzdItemPaste(void)
{
	
}

CGbWzdItemPaste::~CGbWzdItemPaste(void)
{

}


long CGbWzdItemPaste::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strSrcParentItemsIDKey, oNode, m_strSrcParentItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strSrcItemsNameKey, oNode, m_strSrcItemsName);
	xml_GetAttibuteValue(pXmlKeys->m_strSrcItemsIDKey, oNode, m_strSrcItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strDestParentItemsIDKey, oNode, m_strDestParentItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strDestItemsNameKey, oNode, m_strDestItemsName);
	xml_GetAttibuteValue(pXmlKeys->m_strDestItemsIDKey, oNode, m_strDestItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strItemTypeKey, oNode, m_strItemType);

	return 0;
}

long CGbWzdItemPaste::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strSrcParentItemsIDKey, oElement, m_strSrcParentItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strSrcItemsNameKey, oElement, m_strSrcItemsName);
	xml_SetAttributeValue(pXmlKeys->m_strSrcItemsIDKey, oElement, m_strSrcItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strDestParentItemsIDKey, oElement, m_strDestParentItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strDestItemsNameKey, oElement, m_strDestItemsName);
	xml_SetAttributeValue(pXmlKeys->m_strDestItemsIDKey, oElement, m_strDestItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strItemTypeKey, oElement, m_strItemType);
	
	return 0;
}

long CGbWzdItemPaste::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbWzdItemPaste::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataGroup::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdItemPaste *p = (CGbWzdItemPaste*)pObj;

	if (m_strSrcParentItemsID != p->m_strSrcParentItemsID)
	{
		return FALSE;
	}

	if (m_strSrcItemsName != p->m_strSrcItemsName)
	{
		return FALSE;
	}

	if (m_strSrcItemsID != p->m_strSrcItemsID)
	{
		return FALSE;
	}

	if (m_strDestParentItemsID != p->m_strDestParentItemsID)
	{
		return FALSE;
	}

	if (m_strDestItemsName != p->m_strDestItemsName)
	{
		return FALSE;
	}

	if (m_strDestItemsID != p->m_strDestItemsID)
	{
		return FALSE;
	}

	if (m_strItemType != p->m_strItemType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbWzdItemPaste::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CGbWzdItemPaste *p = (CGbWzdItemPaste*)pDest;
	p->m_strSrcParentItemsID = m_strSrcParentItemsID;
	p->m_strSrcItemsName = m_strSrcItemsName;
	p->m_strSrcItemsID = m_strSrcItemsID;
	p->m_strDestParentItemsID = m_strDestParentItemsID;
	p->m_strDestItemsName = m_strDestItemsName;
	p->m_strDestItemsID = m_strDestItemsID;
	p->m_strItemType = m_strItemType;

	return TRUE;
}

CBaseObject* CGbWzdItemPaste::Clone()
{
	CGbWzdItemPaste *p = new CGbWzdItemPaste();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdItemPaste::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdItemPaste *p = new CGbWzdItemPaste();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdItemPaste::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	pNew = CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CGbWzdItemPaste::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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

void CGbWzdItemPaste::GetDestItemPath(CString &strDestItemPath)
{
	if (m_strDestParentItemsID.GetLength() > 0)
	{
		strDestItemPath = m_strDestParentItemsID + _T("$");
	}

	strDestItemPath += m_strDestItemsID;
}