//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenInterface.cpp  CItemsGenInterface


#include "stdafx.h"
#include "ItemsGenInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenInterface::CItemsGenInterface()
{
	//初始化属性

	//初始化成员变量
}

CItemsGenInterface::~CItemsGenInterface()
{
}

long CItemsGenInterface::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenInterface::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenInterface::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CItemsGenInterface::InitAfterRead()
{
}

BOOL CItemsGenInterface::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CItemsGenInterface *p = (CItemsGenInterface*)pObj;

	return TRUE;
}

BOOL CItemsGenInterface::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CItemsGenInterface *p = (CItemsGenInterface*)pDest;

	return TRUE;
}

CBaseObject* CItemsGenInterface::Clone()
{
	CItemsGenInterface *p = new CItemsGenInterface();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenInterface::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenInterface *p = new CItemsGenInterface();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenInterface::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenInterface::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenDataKey)
	{
		pNew = new CItemsGenData();
	}

	return pNew;
}

CExBaseObject* CItemsGenInterface::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATA)
	{
		pNew = new CItemsGenData();
	}

	return pNew;
}

void CItemsGenInterface::InitDataValue(CItemsGenParasMap *pParasMap)
{
	if (pParasMap == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CItemsGenData *pData = (CItemsGenData *)GetNext(pos);
		
		CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)pParasMap->FindByID(pData->m_strID);

		if (pDataMap != NULL)
		{
			pData->m_strValue = pDataMap->m_strValue;
		}
	}
}