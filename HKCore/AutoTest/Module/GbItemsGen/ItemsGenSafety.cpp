//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenSafety.cpp  CItemsGenSafety


#include "stdafx.h"
#include "ItemsGenSafety.h"
#include "ItemsGenDataMap.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenSafety::CItemsGenSafety()
{
	//初始化属性

	//初始化成员变量
}

CItemsGenSafety::~CItemsGenSafety()
{
}

long CItemsGenSafety::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenSafety::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenSafety::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CItemsGenSafety::InitAfterRead()
{
}

BOOL CItemsGenSafety::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CItemsGenSafety *p = (CItemsGenSafety*)pObj;

	return TRUE;
}

BOOL CItemsGenSafety::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}
	
	CExBaseObject::CopyOwn(pDest);
	CItemsGenSafety *p = (CItemsGenSafety*)pDest;
	return TRUE;
}

CBaseObject* CItemsGenSafety::Clone()
{
	CItemsGenSafety *p = new CItemsGenSafety();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenSafety::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenSafety *p = new CItemsGenSafety();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenSafety::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenSafety::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenDataMapKey)
	{
		pNew = new CItemsGenDataMap();
	}

	return pNew;
}

CExBaseObject* CItemsGenSafety::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
	{
		pNew = new CItemsGenDataMap();
	}

	return pNew;
}