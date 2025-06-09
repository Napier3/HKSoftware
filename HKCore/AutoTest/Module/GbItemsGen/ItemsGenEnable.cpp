//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenEnable.cpp  CItemsGenEnable


#include "stdafx.h"
#include "ItemsGenEnable.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenEnable::CItemsGenEnable()
{
	//初始化属性

	//初始化成员变量
}

CItemsGenEnable::~CItemsGenEnable()
{
}

long CItemsGenEnable::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strMode);
	return 0;
}

long CItemsGenEnable::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strMode);
	return 0;
}

long CItemsGenEnable::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMode);
	}
	return 0;
}

void CItemsGenEnable::InitAfterRead()
{
}

BOOL CItemsGenEnable::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CItemsGenEnable *p = (CItemsGenEnable*)pObj;

	if(m_strMode != p->m_strMode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CItemsGenEnable::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CItemsGenEnable *p = (CItemsGenEnable*)pDest;

	p->m_strMode = m_strMode;
	return TRUE;
}

CBaseObject* CItemsGenEnable::Clone()
{
	CItemsGenEnable *p = new CItemsGenEnable();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenEnable::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenEnable *p = new CItemsGenEnable();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenEnable::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenEnable::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenDataKey)
	{
		pNew = new CItemsGenData();
	}

	return pNew;
}

CExBaseObject* CItemsGenEnable::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATA)
	{
		pNew = new CItemsGenData();
	}

	return pNew;
}

BOOL CItemsGenEnable::IsEnable(CItemsGenInterface *pInterface)
{
	if (IsEnableMode_And())
	{
		return IsEnable_And(pInterface);
	}

	if (IsEnableMode_Or())
	{
		return IsEnable_Or(pInterface);
	}

	if (IsEnableMode_Not())
	{
		return IsEnable_Not(pInterface);
	}

	return FALSE;
}

//And模式下，要求所有的数据都使能成功
BOOL CItemsGenEnable::IsEnable_And(CItemsGenInterface *pInterface)
{
	POS pos = GetHeadPosition();
	CItemsGenData *pData = NULL;
	BOOL bEnable = FALSE;

	while (pos != NULL)
	{
		pData = (CItemsGenData *)GetNext(pos);
		bEnable = pData->IsEnable(pInterface);

		if (!bEnable)
		{
			return FALSE;
		}
	}

	return TRUE;
}

//Or模式下，只要有一个数据使能成功即可
BOOL CItemsGenEnable::IsEnable_Or(CItemsGenInterface *pInterface)
{
	POS pos = GetHeadPosition();
	CItemsGenData *pData = NULL;
	BOOL bEnable = TRUE;

	while (pos != NULL)
	{
		pData = (CItemsGenData *)GetNext(pos);
		bEnable = pData->IsEnable(pInterface);

		if (bEnable)
		{
			break;
		}
	}

	return bEnable;
}

//Not模式下，要求每一个数据均不使能
BOOL CItemsGenEnable::IsEnable_Not(CItemsGenInterface *pInterface)
{
	POS pos = GetHeadPosition();
	CItemsGenData *pData = NULL;
	BOOL bEnable = 0;

	while (pos != NULL)
	{
		pData = (CItemsGenData *)GetNext(pos);
		bEnable = pData->IsEnable(pInterface);

		if (bEnable)
		{
			return FALSE;
		}
	}

	return TRUE;
}