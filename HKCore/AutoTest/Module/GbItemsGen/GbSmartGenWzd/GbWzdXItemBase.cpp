#include "StdAfx.h"
#include "GbWzdXItemBase.h"
#include "GbSmartGenWzd.h"

extern CGbSmartGenWzd *g_theGbSmartGenWzd;

CGbWzdXItemBase::CGbWzdXItemBase(void)
{
	m_pParas = NULL;
}

CGbWzdXItemBase::~CGbWzdXItemBase(void)
{

}


long CGbWzdXItemBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strParentItemsIDKey, oNode, m_strParentItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsNameKey, oNode, m_strItemsName);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsIDKey, oNode, m_strItemsID);

	return 0;
}

long CGbWzdXItemBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strParentItemsIDKey, oElement, m_strParentItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strItemsNameKey, oElement, m_strItemsName);
	xml_SetAttributeValue(pXmlKeys->m_strItemsIDKey, oElement, m_strItemsID);

	return 0;
}

long CGbWzdXItemBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbWzdXItemBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataGroup::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdXItemBase *p = (CGbWzdXItemBase*)pObj;

	return TRUE;
}

BOOL CGbWzdXItemBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CGbWzdXItemBase *p = (CGbWzdXItemBase*)pDest;
	p->m_strParentItemsID = m_strParentItemsID;
	p->m_strItemsName = m_strItemsName;
	p->m_strItemsID = m_strItemsID;

	return TRUE;
}

CExBaseObject* CGbWzdXItemBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCDataGroupKey)
	{
		pNew = new CDataGroup();
	}
	else if (strClassID == pXmlKeys->m_strContentsKey)
	{
		m_pParas = new CDvmContents();
		pNew = m_pParas;
	}
	else
	{
		pNew = CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CGbWzdXItemBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		pNew = new CDataGroup();
	}
	else if (nClassID == DTMCLASSID_CCONTENTS)
	{
		m_pParas = new CDvmContents();
		pNew = m_pParas;
	}
	else
	{
		pNew = CDataGroup::CreateNewChild(nClassID);
	}

	return pNew;
}

void CGbWzdXItemBase::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->m_strID == STT_CMD_PARA_ItemParas)
		{
			m_pParas = (CDvmContents*)p;
		}
	}
}


void CGbWzdXItemBase::SetParas(const CString &strParas)
{
	if (m_pParas == NULL)
	{
		m_pParas = new CDvmContents();
		m_pParas->m_strName = STT_CMD_PARA_ItemParas;
		m_pParas->m_strID = STT_CMD_PARA_ItemParas;
		AddNewChild(m_pParas);
	}

	m_pParas->m_strText = strParas;
}

void CGbWzdXItemBase::GetItemPath(CString &strItemPath)
{
	if (m_strParentItemsID.GetLength() > 0)
	{
		strItemPath = m_strParentItemsID + _T("$");
	}

	strItemPath += m_strItemsID;
}