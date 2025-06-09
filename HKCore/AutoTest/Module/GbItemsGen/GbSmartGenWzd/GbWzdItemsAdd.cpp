#include "StdAfx.h"
#include "GbWzdItemsAdd.h"
#include "GbSmartGenWzd.h"


CGbWzdItemsAdd::CGbWzdItemsAdd(void)
{
	m_nRepeatTimes = 0;
	m_nRptTitle = 0;
	m_nTitleLevel = 1;
}

CGbWzdItemsAdd::~CGbWzdItemsAdd(void)
{

}


long CGbWzdItemsAdd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CGbWzdXItemBase::XmlReadOwn(oNode, pXmlRWKeys);
	xml_GetAttibuteValue(pXmlKeys->m_strRepeatTimesKey, oNode, m_nRepeatTimes);
	xml_GetAttibuteValue(pXmlKeys->m_strRptTitleKey, oNode, m_nRptTitle);
	xml_GetAttibuteValue(pXmlKeys->m_strTitleLevelKey, oNode, m_nTitleLevel);

	return 0;
}

long CGbWzdItemsAdd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdXItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strRepeatTimesKey, oElement, m_nRepeatTimes);
	xml_SetAttributeValue(pXmlKeys->m_strRptTitleKey, oElement, m_nRptTitle);
	xml_SetAttributeValue(pXmlKeys->m_strTitleLevelKey, oElement, m_nTitleLevel);

	return 0;
}

long CGbWzdItemsAdd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbWzdXItemBase::SerializeOwn(oBinaryBuffer);

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

BOOL CGbWzdItemsAdd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGbWzdXItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdItemsAdd *p = (CGbWzdItemsAdd*)pObj;

	if (p->m_nRepeatTimes != m_nRepeatTimes)
	{
		return FALSE;
	}

	if (m_nRptTitle != p->m_nRptTitle)
	{
		return FALSE;
	}

	if (m_nTitleLevel != p->m_nTitleLevel)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CGbWzdItemsAdd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbWzdXItemBase::CopyOwn(pDest);

	CGbWzdItemsAdd *p = (CGbWzdItemsAdd*)pDest;
	p->m_strParentItemsID = m_strParentItemsID;
	p->m_nRepeatTimes = m_nRepeatTimes;
	p->m_nRptTitle = m_nRptTitle;
	p->m_nTitleLevel = m_nTitleLevel;

	return TRUE;
}

CBaseObject* CGbWzdItemsAdd::Clone()
{
	CGbWzdItemsAdd *p = new CGbWzdItemsAdd();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdItemsAdd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdItemsAdd *p = new CGbWzdItemsAdd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdItemsAdd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	pNew = CGbWzdXItemBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CGbWzdItemsAdd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		pNew = new CDataGroup();
	}
	else
	{
		pNew = CGbWzdXItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}

/////////////////////////////////////////////////////////////////////////////////////////////
CGbWzdItemsDelete::CGbWzdItemsDelete(void)
{

}

CGbWzdItemsDelete::~CGbWzdItemsDelete(void)
{

}


long CGbWzdItemsDelete::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strParentItemsIDKey, oNode, m_strParentItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsNameKey, oNode, m_strItemsName);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsIDKey, oNode, m_strItemsID);

	return 0;
}

long CGbWzdItemsDelete::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strParentItemsIDKey, oElement, m_strParentItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strItemsNameKey, oElement, m_strItemsName);
	xml_SetAttributeValue(pXmlKeys->m_strItemsIDKey, oElement, m_strItemsID);

	return 0;
}

long CGbWzdItemsDelete::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbWzdItemsDelete::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataGroup::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdItemsDelete *p = (CGbWzdItemsDelete*)pObj;

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

	return TRUE;
}

BOOL CGbWzdItemsDelete::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CGbWzdItemsDelete *p = (CGbWzdItemsDelete*)pDest;
	p->m_strParentItemsID = m_strParentItemsID;
	p->m_strItemsName = m_strItemsName;
	p->m_strItemsID = m_strItemsID;

	return TRUE;
}

CBaseObject* CGbWzdItemsDelete::Clone()
{
	CGbWzdItemsDelete *p = new CGbWzdItemsDelete();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdItemsDelete::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdItemsDelete *p = new CGbWzdItemsDelete();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdItemsDelete::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	pNew = CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CGbWzdItemsDelete::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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

void CGbWzdItemsDelete::GetItemPath(CString &strItemPath)
{
	if (m_strParentItemsID.GetLength() > 0)
	{
		strItemPath = m_strParentItemsID + _T("$");
	}

	strItemPath += m_strItemsID;
}