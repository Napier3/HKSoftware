//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttIotNode.cpp  CSttIotNode


#include "stdafx.h"
#include "SttIotNode.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttIotNode::CSttIotNode()
{
	//初始化属性
	m_nType = 0;
	m_nCat = 0;
	m_nState = 0;

	//初始化成员变量
}

CSttIotNode::~CSttIotNode()
{
}

long CSttIotNode::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSNKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_nType);
	xml_GetAttibuteValue(pXmlKeys->m_strCatKey, oNode, m_nCat);
	xml_GetAttibuteValue(pXmlKeys->m_strParentKey, oNode, m_strParent);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_nState);
	return 0;
}

long CSttIotNode::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSNKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_nType);
	xml_SetAttributeValue(pXmlKeys->m_strCatKey, oElement, m_nCat);
	xml_SetAttributeValue(pXmlKeys->m_strParentKey, oElement, m_strParent);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_nState);
	return 0;
}

long CSttIotNode::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nType);
		BinarySerializeCalLen(oBinaryBuffer, m_nCat);
		BinarySerializeCalLen(oBinaryBuffer, m_strParent);
		BinarySerializeCalLen(oBinaryBuffer, m_nState);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_nType);
		BinarySerializeRead(oBinaryBuffer, m_nCat);
		BinarySerializeRead(oBinaryBuffer, m_strParent);
		BinarySerializeRead(oBinaryBuffer, m_nState);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nType);
		BinarySerializeWrite(oBinaryBuffer, m_nCat);
		BinarySerializeWrite(oBinaryBuffer, m_strParent);
		BinarySerializeWrite(oBinaryBuffer, m_nState);
	}
	return 0;
}

void CSttIotNode::InitAfterRead()
{
}

BOOL CSttIotNode::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttIotNode *p = (CSttIotNode*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_nType != p->m_nType)
	{
		return FALSE;
	}

	if(m_nCat != p->m_nCat)
	{
		return FALSE;
	}

	if(m_strParent != p->m_strParent)
	{
		return FALSE;
	}

	if(m_nState != p->m_nState)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttIotNode::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttIotNode *p = (CSttIotNode*)pDest;

	p->m_strID = m_strID;
	p->m_nType = m_nType;
	p->m_nCat = m_nCat;
	p->m_strParent = m_strParent;
	p->m_nState = m_nState;
	return TRUE;
}

CBaseObject* CSttIotNode::Clone()
{
	CSttIotNode *p = new CSttIotNode();
	Copy(p);
	return p;
}

CBaseObject* CSttIotNode::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttIotNode *p = new CSttIotNode();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttIotNode::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CSttIotNode::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CSttIotNode::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
