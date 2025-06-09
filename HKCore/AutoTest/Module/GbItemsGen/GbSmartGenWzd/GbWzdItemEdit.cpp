#include "StdAfx.h"
#include "GbWzdItemEdit.h"
#include "GbSmartGenWzd.h"


CGbWzdItemEdit::CGbWzdItemEdit(void)
{
	m_nRepeatTimes = 0;  //重复次数。只有CSttItems编辑时，才有重复次数编辑
	m_nRptTitle = 0;
	m_nTitleLevel = 1;
}

CGbWzdItemEdit::~CGbWzdItemEdit(void)
{

}


long CGbWzdItemEdit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CGbWzdXItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strItemsID_OldKey, oNode, m_strItemsID_Old);
	xml_GetAttibuteValue(pXmlKeys->m_strRepeatTimesKey, oNode, m_nRepeatTimes);
	xml_GetAttibuteValue(pXmlKeys->m_strRptTitleKey, oNode, m_nRptTitle);
	xml_GetAttibuteValue(pXmlKeys->m_strTitleLevelKey, oNode, m_nTitleLevel);

	return 0;
}

long CGbWzdItemEdit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdXItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strItemsID_OldKey, oElement, m_strItemsID_Old);
	xml_SetAttributeValue(pXmlKeys->m_strRepeatTimesKey, oElement, m_nRepeatTimes);
	xml_SetAttributeValue(pXmlKeys->m_strRptTitleKey, oElement, m_nRptTitle);
	xml_SetAttributeValue(pXmlKeys->m_strTitleLevelKey, oElement, m_nTitleLevel);

	return 0;
}

long CGbWzdItemEdit::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbWzdItemEdit::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGbWzdXItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdItemEdit *p = (CGbWzdItemEdit*)pObj;

	if (m_strItemsID_Old != p->m_strItemsID_Old)
	{
		return FALSE;
	}

	if (m_nRepeatTimes != p->m_nRepeatTimes)
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

BOOL CGbWzdItemEdit::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbWzdXItemBase::CopyOwn(pDest);

	CGbWzdItemEdit *p = (CGbWzdItemEdit*)pDest;
	p->m_strItemsID_Old = m_strItemsID_Old;
	p->m_nRepeatTimes = m_nRepeatTimes;
	p->m_nRptTitle = m_nRptTitle;
	p->m_nTitleLevel = m_nTitleLevel;

	return TRUE;
}

CBaseObject* CGbWzdItemEdit::Clone()
{
	CGbWzdItemEdit *p = new CGbWzdItemEdit();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdItemEdit::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdItemEdit *p = new CGbWzdItemEdit();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdItemEdit::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	pNew = CGbWzdXItemBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CGbWzdItemEdit::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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
