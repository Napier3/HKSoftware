#include "StdAfx.h"
#include "GbWzdMacroTestAdd.h"
#include "GbSmartGenWzd.h"


CGbWzdMacroTestAdd::CGbWzdMacroTestAdd(void)
{

}

CGbWzdMacroTestAdd::~CGbWzdMacroTestAdd(void)
{

}


long CGbWzdMacroTestAdd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CGbWzdXItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strTestMacroUIKey, oNode, m_strTestMacroUI);

	return 0;
}

long CGbWzdMacroTestAdd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdXItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strTestMacroUIKey, oElement, m_strTestMacroUI);

	return 0;
}

long CGbWzdMacroTestAdd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbWzdMacroTestAdd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGbWzdXItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdMacroTestAdd *p = (CGbWzdMacroTestAdd*)pObj;

	return TRUE;
}

BOOL CGbWzdMacroTestAdd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbWzdXItemBase::CopyOwn(pDest);

	CGbWzdMacroTestAdd *p = (CGbWzdMacroTestAdd*)pDest;
	p->m_strParentItemsID = m_strParentItemsID;
	p->m_strTestMacroUI = m_strTestMacroUI;

	return TRUE;
}

CBaseObject* CGbWzdMacroTestAdd::Clone()
{
	CGbWzdMacroTestAdd *p = new CGbWzdMacroTestAdd();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdMacroTestAdd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdMacroTestAdd *p = new CGbWzdMacroTestAdd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdMacroTestAdd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	pNew = CGbWzdXItemBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CGbWzdMacroTestAdd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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
