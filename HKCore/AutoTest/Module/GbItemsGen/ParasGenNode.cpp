//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ParasGenNode.cpp  CParasGenNode


#include "stdafx.h"
#include "ParasGenNode.h"
#include "ItemsGenClass.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CParasGenNode::CParasGenNode()
{
	//初始化属性
	m_nNewItems = 0;

	//初始化成员变量
	m_pItemsGenParaDef = NULL;
}

CParasGenNode::~CParasGenNode()
{
}

long CParasGenNode::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGenNodeBase::XmlReadOwn(oNode, pXmlRWKeys);

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNew_ItemsKey, oNode, m_nNewItems);
	return 0;
}

long CParasGenNode::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGenNodeBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNew_ItemsKey, oElement, m_nNewItems);
	return 0;
}

long CParasGenNode::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGenNodeBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nNewItems);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nNewItems);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nNewItems);
	}
	return 0;
}

void CParasGenNode::InitAfterRead()
{
	CGenNodeBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARADEF)
		{
			m_pItemsGenParaDef = (CItemsGenParaDef*)p;
		}
	}
}

BOOL CParasGenNode::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGenNodeBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CParasGenNode *p = (CParasGenNode*)pObj;

	if(m_nNewItems != p->m_nNewItems)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CParasGenNode::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGenNodeBase::CopyOwn(pDest);

	CParasGenNode *p = (CParasGenNode*)pDest;
	p->m_nNewItems = m_nNewItems;
	return TRUE;
}

CBaseObject* CParasGenNode::Clone()
{
	CParasGenNode *p = new CParasGenNode();
	Copy(p);
	return p;
}

CBaseObject* CParasGenNode::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CParasGenNode *p = new CParasGenNode();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CParasGenNode::CanPaste(UINT nClassID)
{
	if (CGenNodeBase::CanPaste(nClassID))
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CPARASGENNODE)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARADEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CParasGenNode::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	pNew = CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	if (pNew)
	{
		return pNew;
	}
	else if (strClassID == pXmlKeys->m_strCParasGenNodeKey)
	{
		pNew = new CParasGenNode();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenParaDefKey)
	{
		pNew = new CItemsGenParaDef();
	}

	return pNew;
}

CExBaseObject* CParasGenNode::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CGenNodeBase::CreateNewChild(nClassID);

	if (pNew)
	{
		return pNew;
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CPARASGENNODE)
	{
		pNew = new CParasGenNode();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARADEF)
	{
		pNew = new CItemsGenParaDef();
	}


	return pNew;
}

//获取NameAdd的字符串
//先根据自身的name-add子节点，若存在，则直接获取字符串；
//自身不存在name-add子节点，则通过父节点的name-add子节点获取，并传递自身的paras-map节点
CString CParasGenNode::GetNameAdd_Name(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	CString strNameAdd;

	if (GetItemsGenNameAdd() != NULL)
	{
		strNameAdd = GetItemsGenNameAdd()->GetNameAdd_Name(pParasMap, pDataGroup);
	}
 	else 
 	{
 		CExBaseObject *pParent = (CExBaseObject *)GetParent();
 
 		if (pParent->GetClassID() != GBITEMSGENMNGRCLASSID_CPARASGENNODE)
 		{
 			return strNameAdd;
 		}
 
 		CParasGenNode *pParentNode = (CParasGenNode *)pParent;
 		return pParentNode->GetNameAdd_Name(GetItemsGenParaMap(), pDataGroup);
 	}

	return strNameAdd;
}

//获取NameAdd的字符串
//先根据自身的name-add子节点，若存在，则直接获取字符串；
//自身不存在name-add子节点，则通过父节点的name-add子节点获取，并传递自身的paras-map节点
CString CParasGenNode::GetNameAdd_ID(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	CString strNameAdd;

	if (GetItemsGenNameAdd() != NULL)
	{
		strNameAdd = GetItemsGenNameAdd()->GetNameAdd_ID(pParasMap, pDataGroup);
	}
	else 
	{
		CExBaseObject *pParent = (CExBaseObject *)GetParent();

		if (pParent->GetClassID() != GBITEMSGENMNGRCLASSID_CPARASGENNODE)
		{
			return strNameAdd;
		}

		CParasGenNode *pParentNode = (CParasGenNode *)pParent;
		return pParentNode->GetNameAdd_ID(GetItemsGenParaMap(), pDataGroup);
	}

	return strNameAdd;
}

CItemsGenInterface* CParasGenNode::GetGenInterface()
{
	CItemsGenClass *pClass = (CItemsGenClass *)GetAncestor(GBITEMSGENMNGRCLASSID_CITEMSGENCLASS);

	if (pClass == NULL)
	{
		return NULL;
	}

	return pClass->GetItemsGenInterface();
}

CItemsGenInterface* CParasGenNode::GetGenInterface_BK()
{
	CItemsGenClass *pClass = (CItemsGenClass *)GetAncestor(GBITEMSGENMNGRCLASSID_CITEMSGENCLASS);

	if (pClass == NULL)
	{
		return NULL;
	}

	return pClass->GetItemsGenInterface_BK();
}