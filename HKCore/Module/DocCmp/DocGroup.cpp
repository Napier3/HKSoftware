//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocGroup.cpp  CDocGroup


#include "stdafx.h"
#include "DocGroup.h"

CDocGroup::CDocGroup()
{
	//初始化属性

	//初始化成员变量
	m_pConfig = NULL;
}

CDocGroup::~CDocGroup()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == DOCMPCLASSID_CDOCGROUP)
		{
			delete p;
		}
	}

	RemoveAll();
	m_listDocElement.RemoveAll();
}

long CDocGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCmp_IdKey, oNode, m_strCmp_Id);
	return 0;
}

long CDocGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCmp_IdKey, oElement, m_strCmp_Id);
	return 0;
}

void CDocGroup::InitAfterRead()
{
}

BOOL CDocGroup::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDocGroup *p = (CDocGroup*)pObj;

	if(m_strCmp_Id != p->m_strCmp_Id)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDocGroup::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDocGroup *p = (CDocGroup*)pDest;

	p->m_strCmp_Id = m_strCmp_Id;
	return TRUE;
}

CBaseObject* CDocGroup::Clone()
{
	CDocGroup *p = new CDocGroup();
	Copy(p);
	return p;
}

CExBaseObject* CDocGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDocGroupKey)
	{
		pNew = new CDocGroup();
	}
	else if (strClassID == pXmlKeys->m_strCDocTextKey)
	{
		pNew = new CDocText();
	}
	else if (strClassID == pXmlKeys->m_strCDocTableKey)
	{
		pNew = new CDocTable();
	}

	return pNew;
}

CExBaseObject* CDocGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DOCMPCLASSID_CDOCGROUP)
	{
		pNew = new CDocGroup();
	}
	else if (nClassID == DOCMPCLASSID_CDOCTEXT)
	{
		pNew = new CDocText();
	}
	else if (nClassID == DOCMPCLASSID_CDOCTABLE)
	{
		pNew = new CDocTable();
	}

	return pNew;
}

void CDocGroup::SetConfig(CDataGroup *pConfig)
{
	m_pConfig = pConfig;
	m_strName = m_pConfig->m_strName;

	if ( pConfig->m_strValue.GetLength() == 0 )
	{
		int i = 0;
	}
}

void CDocGroup::AddDocElement(CExBaseObject *pDocElement)
{
	m_listDocElement.AddTail(pDocElement);
}

void CDocGroup::Group()
{
	if (m_pConfig->GetCount() == 0)
	{
		Append(m_listDocElement);
	}
	else
	{
		doccmp_Group(&m_listDocElement, m_pConfig, this);

		if (GetCount() > 0)
		{//分组成功
			AddHead(m_listDocElement.GetHead());
		}
	}
}

CDocText* CDocGroup::GetTitle()
{
	CExBaseObject *p = NULL;
	p = GetHead();

	if (p->GetClassID() == DOCMPCLASSID_CDOCTEXT)
	{
		return (CDocText*)p;
	}
	else
	{
		return NULL;
	}
}

void CDocGroup::CmpText(CDocText* pText, long nIndexText, CDocGroup *pSrc)
{
	CDocText *pFind = (CDocText*)pSrc->FindByClassID(DOCMPCLASSID_CDOCTEXT, nIndexText);
	pText->m_strCmp_Id = docmp_GenDocCmpID();

	if (pFind == NULL)
	{
		pText->m_nError = 1;
		return;
	}

	pText->Cmp(pFind);
}

void CDocGroup::CmpTable(CDocTable* pTable, long nIndexTable, CDocGroup *pSrc)
{
	CDocTable *pFind = (CDocTable*)pSrc->FindByClassID(DOCMPCLASSID_CDOCTABLE, nIndexTable);

	if (pFind == NULL)
	{
		pTable->m_strCmp_Id = docmp_GenDocCmpID();
		pTable->SetCmpError();
		return;
	}

	pTable->Cmp(pFind);
}

void CDocGroup::CmpGroup(CDocGroup* pGroup, long nIndexGroup, CDocGroup *pSrc)
{
	CDocGroup *pFind = (CDocGroup*)pSrc->FindByClassID(DOCMPCLASSID_CDOCGROUP, nIndexGroup);

	if (pFind == NULL)
	{
		pGroup->m_strCmp_Id = docmp_GenDocCmpID();
		pGroup->SetCmpError();
		return;
	}

	pGroup->Cmp(pFind);
}


void CDocGroup::Cmp(CDocGroup *pSrc)
{
	if (pSrc == NULL)
	{
		return;
	}

	if (m_pConfig == NULL)
	{
		return;
	}

	if (m_pConfig->m_strValue != _T("1"))
	{
		return;
	}

	m_strCmp_Id = docmp_GenDocCmpID();
	pSrc->m_strCmp_Id = m_strCmp_Id;

	long nIndexText = 0, nIndexTable=0, nIndexGroup=0;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DOCMPCLASSID_CDOCTEXT)
		{
			CmpText((CDocText*)p, nIndexText, pSrc);
			nIndexText++;
		}
		else if (nClassID == DOCMPCLASSID_CDOCTABLE)
		{
			CmpTable((CDocTable*)p, nIndexTable, pSrc);
			nIndexTable++;
		}
		else if (nClassID == DOCMPCLASSID_CDOCGROUP)
		{
			CmpGroup((CDocGroup*)p, nIndexGroup, pSrc);
			nIndexGroup++;
		}
	}
}

CDocGroup* CDocGroup::FindChildGroup(CDocGroup *pRef)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDocGroup *pGroup = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DOCMPCLASSID_CDOCGROUP)
		{
			pGroup = (CDocGroup *)p;

			if(pGroup->CmpOwn(pRef))
			{
				return pGroup;
			}
		}
	}

	return NULL;
}

BOOL CDocGroup::CmpOwn(CDocGroup *pRef)
{
	if (m_pConfig != pRef->m_pConfig)
	{
		return FALSE;
	}

	CDocText *pTitle = GetTitle();
	CDocText *pTitleRef = pRef->GetTitle();

	if (pTitle == NULL || pTitleRef == NULL)
	{
		return FALSE;
	}
	
	return pTitle->Cmp(pTitleRef);
}

BOOL CDocGroup::CmpChildren(CDocGroup *pRef)
{
	return TRUE;
}

void CDocGroup::SetCmpError()
{
	if (m_pConfig != NULL)
	{
		if (m_pConfig->m_strValue != _T("1"))
		{
			return;
		}
	}

	if (m_strCmp_Id.GetLength() == 0)
	{
		m_strCmp_Id = docmp_GenDocCmpID();
	}

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DOCMPCLASSID_CDOCTEXT)
		{
			((CDocText*)p)->SetCmpError();
		}
		else if (nClassID == DOCMPCLASSID_CDOCTABLE)
		{
			((CDocTable*)p)->SetCmpError();
		}
		else if (nClassID == DOCMPCLASSID_CDOCGROUP)
		{
			((CDocGroup*)p)->SetCmpError();
		}
	}
}


//////////////////////////////////////////////////////////////////////////
void doccmp_GroupLevel1(CExBaseList *pDocElementList, CDataGroup *pGroupLevel, CDocGroup *pDocGroupRoot)
{
	POS pos = pDocElementList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CDocText *pText = NULL;

	while (pos != NULL)
	{
		p = pDocElementList->GetNext(pos);

		if (p->GetClassID() == DOCMPCLASSID_CDOCTEXT)
		{
			pText = (CDocText *)p;

			if (pText->m_dwItemData != 0)
			{//当前Text对象已经被使用
				continue;
			}

			if ( ((CDocText*)p)->m_strTxt.Find(pGroupLevel->m_strName) >= 0)
			{//是标题
				CDocGroup *pDocGroup = new CDocGroup();
				pText->m_dwItemData = (DWORD)pDocGroup; //pText指向DocGroup
				pDocGroup->SetConfig(pGroupLevel);
				pDocGroupRoot->AddNewChild(pDocGroup);
			}
		}
	}
}

BOOL docmp_IsPrevGroup(CDocText *pText, CDataGroup *pGroupLevel1, CDataGroup *pChild)
{
	POS pos = pGroupLevel1->GetHeadPosition();
	CDataGroup *p = NULL;

	while (pos != NULL)
	{
		p = (CDataGroup *)pGroupLevel1->GetNext(pos);

		if (p == pChild)
		{
			return FALSE;
		}

		if ( pText->m_strTxt.Find(p->m_strName) >= 0)
		{//是标题
			return TRUE;
		}
	}

	return FALSE;
}

bool docmp_IsTextInGroup(CDocText *pText,  CDataGroup *pGroupLevel)
{
	POS pos = pGroupLevel->GetHeadPosition();
	CDataGroup *p = NULL;

	while (pos != NULL)
	{
		p = (CDataGroup*)pGroupLevel->GetNext(pos);

		if ( pText->m_strTxt.Find(p->m_strName) >= 0)
		{//是标题
			return TRUE;
		}
	}

	return FALSE;
}

bool docmp_OffsetTextInGroup(CExBaseList *pDocElementList, CDataGroup *pGroupLevel, POS &pos,CDocGroup *pDocGroupRoot, CDocText **ppTitleText)
{
	CExBaseObject *p = NULL;
	CDocText *pText = NULL;

	while (pos != NULL)
	{
		p = pDocElementList->GetAt(pos);

		if (p->GetClassID() != DOCMPCLASSID_CDOCTEXT)
		{
			pDocElementList->GetNext(pos);
			continue;
		}

		pText = (CDocText *)p;

		if (pText->m_dwItemData != 0)
		{//当前Text对象已经被使用
			continue;
		}

		if (docmp_IsTextInGroup(pText, pGroupLevel))
		{
			return TRUE;
		}

		*ppTitleText = pText;
		pDocElementList->GetNext(pos);
	}

	return FALSE;
}

POS doccmp_MatchAllChild(CExBaseList *pDocElementList, POS posFrom, CDataGroup *pGroupLevel1, CDocGroup *pDocGroupRoot)
{
	POS pos = posFrom;
	long nIndex = 0;
	CExBaseObject *p = NULL;
	CDocText *pText = NULL;
	CDataGroup *pCurrChild = NULL;
	POS posChild = pGroupLevel1->GetHeadPosition();
	pCurrChild = (CDataGroup*)pGroupLevel1->GetAt(posChild);

	if (! docmp_OffsetTextInGroup(pDocElementList, pGroupLevel1, pos, pDocGroupRoot, &pText))
	{//跳转到是当前分组子对象的位置，然后开始往下匹配
		return pos;
	}

	CDocGroup *pDocGroupTop = new CDocGroup();
	pDocGroupTop->m_strName = pGroupLevel1->m_strName;
	pDocGroupTop->m_strID = pGroupLevel1->m_strID;
	pDocGroupTop->SetConfig(pGroupLevel1);
	pDocGroupRoot->AddNewChild(pDocGroupTop);

	CDocGroup *pNewDocChild = NULL;

	if (pText != NULL)
	{//默认认为最后一个text为大标题
		pDocGroupTop->AddTail(pText);
		pText->m_dwItemData = (DWORD)pDocGroupTop; //pText指向DocGroup
	}

	while (pos != NULL)
	{
		p = pDocElementList->GetAt(pos);

		if (p->GetClassID() != DOCMPCLASSID_CDOCTEXT)
		{
			if (pNewDocChild != NULL)
			{
				pNewDocChild->AddTail(p);
			}
			else
			{
				pDocGroupTop->AddTail(p);
			}

			pDocElementList->GetNext(pos);
			continue;
		}
		else
		{
			
		}

		pText = (CDocText *)p;

		if (pText->m_dwItemData != 0)
		{//当前Text对象已经被使用
			continue;
		}

		if (docmp_IsPrevGroup(pText, pGroupLevel1, pCurrChild))
		{//【遇到文本结束】 如果检测到是前面的兄弟节点，则结束
			break;
		}
		else
		{
			if (pCurrChild == NULL)
			{//如果是文本对象，可能是下一个分组的标题，因此跳过不处理
				if (pNewDocChild != NULL)
				{
					pNewDocChild->AddTail(p);
				}
				else
				{
					pDocGroupTop->AddTail(p);
				}

				pDocElementList->GetNext(pos);
				continue;
			}
		}
		
		if ( pText->m_strTxt.Find(pCurrChild->m_strName) >= 0)
		{//是子对象标题
			pNewDocChild = new CDocGroup();
			pNewDocChild->SetConfig(pCurrChild);
			pNewDocChild->AddTail(pText);
			pGroupLevel1->GetNext(posChild);
			pText->m_dwItemData = (DWORD)pNewDocChild; //pText指向DocGroup
			pDocGroupTop->AddTail(pNewDocChild);

			if (posChild == NULL)
			{//已经匹配玩全部分子子对象，继续处理其他的对象（主要是表格，如果遇到文本，则结束，参见【遇到文本结束】），直到找到下一个对象分组
				pCurrChild = NULL;  
			}
			else
			{//下一个子对象
				pCurrChild = (CDataGroup*)pGroupLevel1->GetAt(posChild);
			}
		}
		else
		{//不是标题，则添加到分组中
			if (pNewDocChild != NULL)
			{
				pNewDocChild->AddTail(p);
			}
			else
			{
				pDocGroupTop->AddTail(p);
			}
		}

		pDocElementList->GetNext(pos);
	}

	return pos;
}

void doccmp_GroupLevel1Child(CExBaseList *pDocElementList, CDataGroup *pGroupLevel, CDocGroup *pDocGroupRoot)
{
	POS pos = pDocElementList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CDocText *pText = NULL;

	while (pos != NULL)
	{
		p = pDocElementList->GetAt(pos);

		if (p->GetClassID() != DOCMPCLASSID_CDOCTEXT)
		{
			continue;
		}

		pText = (CDocText *)p;

		if (pText->m_dwItemData != 0)
		{//当前Text对象已经被使用
			pDocElementList->GetNext(pos);
			continue;
		}

		//按照pGroupLevel，从pos开始切割子对象组
		pos = doccmp_MatchAllChild(pDocElementList, pos, pGroupLevel, pDocGroupRoot);
	}
}

void doccmp_AddElementToGroupLevel1(CExBaseList *pDocElementList)
{
	CDocGroup *pDocGroup = NULL;

	POS pos = pDocElementList->GetHeadPosition();
	CExBaseObject *p = NULL;

	//跳过前部没有分组的对象
	while (pos != NULL)
	{
		p = pDocElementList->GetAt(pos);

		if (p->m_dwItemData != 0)
		{
			break;
		}

		p = pDocElementList->GetNext(pos);
	}

	//第一个分组
	pDocGroup = (CDocGroup *)p->m_dwItemData;

	if (pDocGroup == NULL)
	{
		return;
	}

	while (pos != NULL)
	{
		p = pDocElementList->GetNext(pos);

		if (p->m_dwItemData == 0)
		{
			pDocGroup->AddDocElement(p);
		}
		else
		{
			pDocGroup = (CDocGroup *)p->m_dwItemData;
			pDocGroup->AddDocElement(p);
		}
	}
}


void doccmp_Group(CExBaseList *pDocElementList, CDataGroup *pConfig, CDocGroup *pDocGroupRoot)
{
	//按照标题进行枚举，找到一级标题
	POS pos = pConfig->GetHeadPosition();
	CDataGroup *pLevel = NULL;

	while (pos != NULL)
	{
		pLevel = (CDataGroup *)pConfig->GetNext(pos);
		doccmp_GroupLevel1(pDocElementList, pLevel, pDocGroupRoot);
	}

	//没有找到分组，按照“child”进行模糊分组
	if (pDocGroupRoot->GetCount() == 0)
	{
		pos = pConfig->GetHeadPosition();

		while (pos != NULL)
		{
			pLevel = (CDataGroup *)pConfig->GetNext(pos);
			doccmp_GroupLevel1Child(pDocElementList, pLevel, pDocGroupRoot);
		}
	}
	else
	{
		//按照分类，对所有的对象进行归纳到分组中
		doccmp_AddElementToGroupLevel1(pDocElementList);

		//对每个一级分组，递归进行再次分组
		pos = pDocGroupRoot->GetHeadPosition();
		CDocGroup *pDocGroup = NULL;

		while (pos != NULL)
		{
			pDocGroup = (CDocGroup *)pDocGroupRoot->GetNext(pos);
			pDocGroup->Group();
		}
	}
}

