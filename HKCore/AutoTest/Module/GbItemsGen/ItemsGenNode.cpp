//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
����ģ�����ɶ�������ɽڵ��࣬�ڵ������Ƕ�ף�
Ƕ�׵Ľṹ��ģ��Ľṹ����һ�¡�һ��Node�ඨ��һ��������Ŀ
*/
CItemsGenNode::CItemsGenNode()
{
	//��ʼ������
	m_pRsltExpr = NULL;
	//��ʼ����Ա����
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

//��ȡNameAdd���ַ���
//�ȸ��������name-add�ӽڵ㣬�����ڣ���ֱ�ӻ�ȡ�ַ�����
//�ٻ�ȡ���ڵ��NameAdd�ַ�������ƴ���������NameAdd�ַ���
//��ȡ���ڵ��NameAdd�ַ���ʱ����Ҫ�жϸ��ڵ�����
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

//��ȡNameAdd���ַ���
//�ȸ��������name-add�ӽڵ㣬�����ڣ���ֱ�ӻ�ȡ�ַ�����
//�ٻ�ȡ���ڵ��NameAdd�ַ�������ƴ���������NameAdd�ַ���
//��ȡ���ڵ��NameAdd�ַ���ʱ����Ҫ�жϸ��ڵ�����
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

//��ȡ�����NameAdd�ַ����������и��ڵ����
CString CItemsGenNode::GetNameAdd_Name_Own(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup)
{
	CString strNameAdd;

	if (GetItemsGenNameAdd() != NULL)
	{
		strNameAdd = GetItemsGenNameAdd()->GetNameAdd_Name(pParasMap, pDataGroup);
	}

	return strNameAdd;
}

//��ȡ�����NameAdd�ַ����������и��ڵ����
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