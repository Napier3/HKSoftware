#include "StdAfx.h"
#include "GbWzdItemMove.h"
#include "GbSmartGenWzd.h"


CGbWzdItemMove::CGbWzdItemMove(void)
{
	m_nMoveTimes = 1;
}

CGbWzdItemMove::~CGbWzdItemMove(void)
{

}


long CGbWzdItemMove::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strParentItemsIDKey, oNode, m_strParentItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsNameKey, oNode, m_strItemsName);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsIDKey, oNode, m_strItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strMoveTypeKey, oNode, m_strMoveType);
	xml_GetAttibuteValue(pXmlKeys->m_strMoveTimesKey, oNode, m_nMoveTimes);

	return 0;
}

long CGbWzdItemMove::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strParentItemsIDKey, oElement, m_strParentItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strItemsNameKey, oElement, m_strItemsName);
	xml_SetAttributeValue(pXmlKeys->m_strItemsIDKey, oElement, m_strItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strMoveTypeKey, oElement, m_strMoveType);
	xml_SetAttributeValue(pXmlKeys->m_strMoveTimesKey, oElement, m_nMoveTimes);
	return 0;
}

long CGbWzdItemMove::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbWzdItemMove::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataGroup::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdItemMove *p = (CGbWzdItemMove*)pObj;

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

	if (m_strMoveType != p->m_strMoveType)
	{
		return FALSE;
	}

	if (m_nMoveTimes != p->m_nMoveTimes)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbWzdItemMove::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CGbWzdItemMove *p = (CGbWzdItemMove*)pDest;
	p->m_strParentItemsID = m_strParentItemsID;
	p->m_strItemsName = m_strItemsName;
	p->m_strItemsID = m_strItemsID;
	p->m_strMoveType = m_strMoveType;
	p->m_nMoveTimes = m_nMoveTimes;

	return TRUE;
}

CBaseObject* CGbWzdItemMove::Clone()
{
	CGbWzdItemMove *p = new CGbWzdItemMove();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdItemMove::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdItemMove *p = new CGbWzdItemMove();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdItemMove::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	pNew = CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CGbWzdItemMove::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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

void CGbWzdItemMove::GetItemPath(CString &strItemPath)
{
	if (m_strParentItemsID.GetLength() > 0)
	{
		strItemPath = m_strParentItemsID + _T("$");
	}

	strItemPath += m_strItemsID;
}