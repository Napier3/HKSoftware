//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenSysParaEdit.cpp  CItemsGenSysParaEdit


#include "stdafx.h"
#include "ItemsGenSysParaEdit.h"
#include "ItemsGenDataMap.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenSysParaEdit::CItemsGenSysParaEdit()
{
	//初始化属性

	//初始化成员变量
}

CItemsGenSysParaEdit::~CItemsGenSysParaEdit()
{
}

long CItemsGenSysParaEdit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenSysParaEdit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CItemsGenSysParaEdit::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CItemsGenSysParaEdit::InitAfterRead()
{
}

BOOL CItemsGenSysParaEdit::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CItemsGenSysParaEdit *p = (CItemsGenSysParaEdit*)pObj;

	return TRUE;
}

BOOL CItemsGenSysParaEdit::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);
	CItemsGenSysParaEdit *p = (CItemsGenSysParaEdit*)pDest;

	return TRUE;
}

CBaseObject* CItemsGenSysParaEdit::Clone()
{
	CItemsGenSysParaEdit *p = new CItemsGenSysParaEdit();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenSysParaEdit::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenSysParaEdit *p = new CItemsGenSysParaEdit();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenSysParaEdit::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenSysParaEdit::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenDataMapKey)
	{
		pNew = new CItemsGenDataMap();
	}

	return pNew;
}

CExBaseObject* CItemsGenSysParaEdit::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
	{
		pNew = new CItemsGenDataMap();
	}

	return pNew;
}