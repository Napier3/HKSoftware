//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenParaDef.cpp  CItemsGenParaDef


#include "stdafx.h"
#include "ItemsGenParaDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenParaDef::CItemsGenParaDef()
{
	//初始化属性

	//初始化成员变量
}

CItemsGenParaDef::~CItemsGenParaDef()
{
}

long CItemsGenParaDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenParaDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenParaDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CItemsGenParaDef::InitAfterRead()
{
}

BOOL CItemsGenParaDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CItemsGenParaDef *p = (CItemsGenParaDef*)pObj;

	return TRUE;
}

BOOL CItemsGenParaDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CItemsGenParaDef *p = (CItemsGenParaDef*)pDest;

	return TRUE;
}

CBaseObject* CItemsGenParaDef::Clone()
{
	CItemsGenParaDef *p = new CItemsGenParaDef();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenParaDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenParaDef *p = new CItemsGenParaDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenParaDef::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenParaDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenParaKey)
	{
		pNew = new CItemsGenPara();
	}

	return pNew;
}

CExBaseObject* CItemsGenParaDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARA)
	{
		pNew = new CItemsGenPara();
	}

	return pNew;
}
