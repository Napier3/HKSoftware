//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenNode.cpp  CItemsGenNode


#include "stdafx.h"
#include "ItemsGenNode.h"
#include "ItemsGenDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
测试模板生成定义的生成节点类，节点类可以嵌套，
嵌套的结构与模板的结构保持一致。一个Node类定义一个测试项目
*/
CItemsGenNode::CItemsGenNode()
{
	//初始化属性
	m_pRsltExpr = NULL;
	//初始化成员变量
}

CItemsGenNode::~CItemsGenNode()
{
}

long CItemsGenNode::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return CGenNodeBase::XmlReadOwn(oNode, pXmlRWKeys);
}

long CItemsGenNode::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return CGenNodeBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
}

long CItemsGenNode::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return CGenNodeBase::SerializeOwn(oBinaryBuffer);
}

void CItemsGenNode::InitAfterRead()
{
	CGenNodeBase::InitAfterRead();
}

BOOL CItemsGenNode::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGenNodeBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CItemsGenNode *p = (CItemsGenNode*)pObj;

	return TRUE;
}

BOOL CItemsGenNode::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGenNodeBase::CopyOwn(pDest);

	CItemsGenNode *p = (CItemsGenNode*)pDest;

	return TRUE;
}

CBaseObject* CItemsGenNode::Clone()
{
	CItemsGenNode *p = new CItemsGenNode();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenNode::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenNode *p = new CItemsGenNode();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenNode::CanPaste(UINT nClassID)
{
	if (CGenNodeBase::CanPaste(nClassID))
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNODE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenNode::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	pNew = CGenNodeBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	if (pNew)
	{
		return pNew;
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenNodeKey)
	{
		pNew = new CItemsGenNode();
	}
	else if(strClassID == pXmlKeys->m_strCItemRsltExprKey)
	{
		pNew = new CItemGenRsltExpr();
		m_pRsltExpr = (CItemGenRsltExpr *)pNew;
	}

	return pNew;
}

CExBaseObject* CItemsGenNode::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CGenNodeBase::CreateNewChild(nClassID);

	if (pNew)
	{
		return pNew;
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNODE)
	{
		pNew = new CItemsGenNode();
	}
	else if(nClassID == GBITEMSGENMNGRCLASSID_CITEMGENRSLTEXPR)
	{
		pNew = new CItemGenRsltExpr();
		m_pRsltExpr = (CItemGenRsltExpr *)pNew;
	}


	return pNew;
}

CItemGenRsltExpr* CItemsGenNode::GetRsltExpr()
{
	return m_pRsltExpr;
}

//获取NameAdd的字符串
//先根据自身的name-add子节点，若存在，则直接获取字符串；
//再获取父节点的NameAdd字符串，并拼接上自身的NameAdd字符串
//获取父节点的NameAdd字符串时，需要判断父节点类型
CString CItemsGenNode::GetNameAdd_Name(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	CString strNameAdd = GetNameAdd_Name_Own(pParasMap, pDataGroup);

	CString strNameAppend;
	CExBaseObject *pParent = (CExBaseObject *)GetParent();

	while (pParent != NULL)
	{
		if (pParent->GetClassID() != GBITEMSGENMNGRCLASSID_CITEMSGENNODE)
		{
			break;
		}

		CItemsGenNode *pParentNode = (CItemsGenNode *)pParent;

		if (pParentNode->IsNodeType_Items())
		{
			break;
		}

		strNameAppend = pParentNode->GetNameAdd_Name_Own(pParasMap, pDataGroup) + strNameAppend;

		pParent = (CExBaseObject *)pParent->GetParent();
	}
	
	strNameAdd = strNameAppend + strNameAdd;
	return strNameAdd;
}

//获取NameAdd的字符串
//先根据自身的name-add子节点，若存在，则直接获取字符串；
//再获取父节点的NameAdd字符串，并拼接上自身的NameAdd字符串
//获取父节点的NameAdd字符串时，需要判断父节点类型
CString CItemsGenNode::GetNameAdd_ID(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	CString strNameAdd = GetNameAdd_ID_Own(pParasMap, pDataGroup);

	CString strNameAppend;
	CExBaseObject *pParent = (CExBaseObject *)GetParent();

	while (pParent != NULL)
	{
		if (pParent->GetClassID() != GBITEMSGENMNGRCLASSID_CITEMSGENNODE)
		{
			break;
		}

		CItemsGenNode *pParentNode = (CItemsGenNode *)pParent;

		if (pParentNode->IsNodeType_Items())
		{
			break;
		}

		strNameAppend = pParentNode->GetNameAdd_ID_Own(pParasMap, pDataGroup) + strNameAppend;

		pParent = (CExBaseObject *)pParent->GetParent();
	}

	strNameAdd = strNameAppend + strNameAdd;
	return strNameAdd;
}

//获取自身的NameAdd字符串，不进行父节点遍历
CString CItemsGenNode::GetNameAdd_Name_Own(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	CString strNameAdd;

	if (GetItemsGenNameAdd() != NULL)
	{
		strNameAdd = GetItemsGenNameAdd()->GetNameAdd_Name(pParasMap, pDataGroup);
	}

	return strNameAdd;
}

//获取自身的NameAdd字符串，不进行父节点遍历
CString CItemsGenNode::GetNameAdd_ID_Own(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	CString strNameAdd;

	if (GetItemsGenNameAdd() != NULL)
	{
		strNameAdd = GetItemsGenNameAdd()->GetNameAdd_ID(pParasMap, pDataGroup);
	}

	return strNameAdd;
}

CItemsGenInterface* CItemsGenNode::GetGenInterface()
{
	CItemsGenDefine *pDefine = (CItemsGenDefine *)GetAncestor(GBITEMSGENMNGRCLASSID_CITEMSGENDEFINE);

	if (pDefine == NULL)
	{
		return NULL;
	}

	return pDefine->GetItemsGenInterface();
}

CItemsGenInterface* CItemsGenNode::GetGenInterface_BK()
{
	CItemsGenDefine *pDefine = (CItemsGenDefine *)GetAncestor(GBITEMSGENMNGRCLASSID_CITEMSGENDEFINE);

	if (pDefine == NULL)
	{
		return NULL;
	}

	return pDefine->GetItemsGenInterface_BK();
}