//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseAxises.cpp  CUIBaseAxises


#include "stdafx.h"
#include "UIBaseItems.h"

CUIBaseItems::CUIBaseItems()
{
	//初始化属性


	//初始化成员变量
}

CUIBaseItems::~CUIBaseItems()
{
}

long CUIBaseItems::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;
	return 0;
}

long CUIBaseItems::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIBaseItems::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{

	}
	else if(oBinaryBuffer.IsReadMode())
	{
		
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		
	}
	return 0;
}

void CUIBaseItems::InitAfterRead()
{
	
}

BOOL CUIBaseItems::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIBaseItems *p = (CUIBaseItems*)pObj;

	return TRUE;
}

BOOL CUIBaseItems::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIBaseItems *p = (CUIBaseItems*)pDest;


	return TRUE;
}

CBaseObject* CUIBaseItems::Clone()
{
	CUIBaseItems *p = new CUIBaseItems();
	Copy(p);
	return p;
}

BOOL CUIBaseItems::CanPaste(UINT nClassID)
{
	if (nClassID == UICLASSID_CUIBASEITEM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUIBaseItems::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUIBaseItemKey)
	{
		pNew = new CUIBaseItem();
	}

	return pNew;
}

CExBaseObject* CUIBaseItems::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CUIBASEITEM)
	{
		pNew = new CUIBaseItem();
	}

	return pNew;
}
