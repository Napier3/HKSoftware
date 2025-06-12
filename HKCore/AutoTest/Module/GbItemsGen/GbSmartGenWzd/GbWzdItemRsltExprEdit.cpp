#include "stdafx.h"
#include "GbWzdItemRsltExprEdit.h"
#include "GbSmartGenWzd.h"


CGbWzdItemRsltExprEdit::CGbWzdItemRsltExprEdit(void)
{
	m_pRsltExpr = NULL;
}

CGbWzdItemRsltExprEdit::~CGbWzdItemRsltExprEdit(void)
{

}


long CGbWzdItemRsltExprEdit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strParentItemsIDKey, oNode, m_strParentItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsNameKey, oNode, m_strItemsName);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsIDKey, oNode, m_strItemsID);

	return 0;
}

long CGbWzdItemRsltExprEdit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strParentItemsIDKey, oElement, m_strParentItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strItemsNameKey, oElement, m_strItemsName);
	xml_SetAttributeValue(pXmlKeys->m_strItemsIDKey, oElement, m_strItemsID);
	
	return 0;
}

long CGbWzdItemRsltExprEdit::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbWzdItemRsltExprEdit::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataGroup::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdItemRsltExprEdit *p = (CGbWzdItemRsltExprEdit*)pObj;

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

BOOL CGbWzdItemRsltExprEdit::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CGbWzdItemRsltExprEdit *p = (CGbWzdItemRsltExprEdit*)pDest;
	p->m_strParentItemsID = m_strParentItemsID;
	p->m_strItemsName = m_strItemsName;
	p->m_strItemsID = m_strItemsID;

	return TRUE;
}

CBaseObject* CGbWzdItemRsltExprEdit::Clone()
{
	CGbWzdItemRsltExprEdit *p = new CGbWzdItemRsltExprEdit();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdItemRsltExprEdit::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdItemRsltExprEdit *p = new CGbWzdItemRsltExprEdit();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdItemRsltExprEdit::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCDataGroupKey)
	{
		pNew = new CDataGroup();
	}
	else if (strClassID == pXmlKeys->m_strContentsKey)
	{
		m_pRsltExpr = new CDvmContents();
		pNew = m_pRsltExpr;
	}
	else
	{
		pNew = CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
	}


	return pNew;
}

CExBaseObject* CGbWzdItemRsltExprEdit::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		pNew = new CDataGroup();
	}
	else if (nClassID == DTMCLASSID_CCONTENTS)
	{
		m_pRsltExpr = new CDvmContents();
		pNew = m_pRsltExpr;
	}
	else
	{
		pNew = CDataGroup::CreateNewChild(nClassID);
	}

	return pNew;
}

void CGbWzdItemRsltExprEdit::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->m_strID == STT_CMD_PARA_RsltEpxr)
		{
			m_pRsltExpr = (CDvmContents*)p;
		}
	}
}

void CGbWzdItemRsltExprEdit::SetRsltExpr(const CString &strRsltExpr)
{
	if (m_pRsltExpr == NULL)
	{
		m_pRsltExpr = new CDvmContents();
		m_pRsltExpr->m_strName = STT_CMD_PARA_RsltEpxr;
		m_pRsltExpr->m_strID = STT_CMD_PARA_RsltEpxr;
		AddNewChild(m_pRsltExpr);
	}

	m_pRsltExpr->m_strText = strRsltExpr;
}
