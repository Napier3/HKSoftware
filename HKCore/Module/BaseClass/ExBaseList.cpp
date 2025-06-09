// ExBaseList.cpp: implementation of the CExBaseList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExBaseList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExBaseList::CExBaseList()
{

}

CExBaseList::~CExBaseList()
{
	DeleteAll();
}

void CExBaseList::Append(CExBaseList &oListSrc, unsigned int nClassID)
{
	POS pos = oListSrc.GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = oListSrc.GetNext(pos);

		if (pObj->GetClassID() == nClassID)
		{
			AddTail(pObj);
		}
	}
}

void CExBaseList::Append(CExBaseList &oListSrc)
{
	POS pos = oListSrc.GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = oListSrc.GetNext(pos);
		AddTail(pObj);
	}
}

void CExBaseList::AppendEx(CExBaseList &oListSrc, BOOL bSetParent)
{
	POS pos = oListSrc.GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = oListSrc.GetNext(pos);
		AddTail(pObj);

		if (bSetParent)
		{
			pObj->SetParent(this);
		}
	}
}

void CExBaseList::AppendClone(CExBaseList &oListSrc, BOOL bAddSame)
{
	POS pos = oListSrc.GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CExBaseObject *pObjNew = NULL;

	if (bAddSame)
	{
		while (pos != NULL)
		{
			pObj = oListSrc.GetNext(pos);
			pObjNew = (CExBaseObject*)pObj->Clone();
			AddNewChild(pObjNew);
		}
	}
	else
	{
		while (pos != NULL)
		{
			pObj = oListSrc.GetNext(pos);

			if (FindByID(pObj->m_strID) == NULL)
			{
				pObjNew = (CExBaseObject*)pObj->Clone();
				AddNewChild(pObjNew);
			}
		}
	}
}

void CExBaseList::AppendClone(CExBaseList &oListSrc)
{
	POS pos = oListSrc.GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CExBaseObject *pObjNew = NULL;

	while (pos != NULL)
	{
		pObj = oListSrc.GetNext(pos);
		pObjNew = (CExBaseObject*)pObj->Clone();
		AddTail(pObjNew);
	}
}

void CExBaseList::AppendCloneEx(CExBaseList &oListSrc, BOOL bSetParent)
{
	POS pos = oListSrc.GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CExBaseObject *pObjNew = NULL;

	if (bSetParent)
	{
		while (pos != NULL)
		{
			pObj = oListSrc.GetNext(pos);
			pObjNew = (CExBaseObject*)pObj->Clone();
			AddTail(pObjNew);
			pObjNew->SetParent(this);
		}
	}	
	else
	{
		while (pos != NULL)
		{
			pObj = oListSrc.GetNext(pos);
			pObjNew = (CExBaseObject*)pObj->Clone();
			AddTail(pObjNew);
		}
	}
}

void CExBaseList::AppendCloneEx2(CExBaseList &oListSrc, BOOL bSetParent, BOOL bCopyOwn, BOOL bCopyChildren)
{
	POS pos = oListSrc.GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CExBaseObject *pObjNew = NULL;

	if (bSetParent)
	{
		while (pos != NULL)
		{
			pObj = oListSrc.GetNext(pos);
			pObjNew = (CExBaseObject*)pObj->CloneEx(bCopyOwn, bCopyChildren);
			AddTail(pObjNew);
			pObjNew->SetParent(this);
		}
	}	
	else
	{
		while (pos != NULL)
		{
			pObj = oListSrc.GetNext(pos);
			pObjNew = (CExBaseObject*)pObj->CloneEx(bCopyOwn, bCopyChildren);
			AddTail(pObjNew);
		}
	}
}

void CExBaseList::Append(CExBaseList &oListSrc, long nBegin, long nCount, BOOL bSetParent)
{
	POS pos = oListSrc.FindIndex(nBegin);

	if (pos == NULL || nCount == 0)
	{
		return;
	}

	long nAppend = 0;

	CExBaseObject *pObj = NULL;

	if (bSetParent)
	{
		while (pos != NULL)
		{
			pObj = oListSrc.GetNext(pos);
			AddTail(pObj);
			pObj->SetParent(this);
			nAppend++;

			if (nAppend >= nCount)
			{
				break;
			}
		}
	}
	else
	{
		while (pos != NULL)
		{
			pObj = oListSrc.GetNext(pos);
			AddTail(pObj);
			nAppend++;

			if (nAppend >= nCount)
			{
				break;
			}
		}
	}
}

void CExBaseList::AppendClone(CExBaseList &oListSrc, long nBegin, long nCount)
{
	POS pos = oListSrc.FindIndex(nBegin);

	if (pos == NULL || nCount == 0)
	{
		return;
	}

	long nAppend = 0;

	CExBaseObject *pObj = NULL;
	CExBaseObject *pNew = NULL;

	while (pos != NULL)
	{
		pObj = oListSrc.GetNext(pos);
		pNew = (CExBaseObject*)pObj->Clone();
		AddTail(pNew);
		pNew->SetParent(this);
		nAppend++;

		if (nAppend >= nCount)
		{
			break;
		}
	}
}

CExBaseObject* CExBaseList::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)  {    return NULL;     }
CExBaseObject* CExBaseList::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)            {    return NULL;     }

CExBaseObject* CExBaseList::AddNew(long nClassID)
{
	CExBaseObject *pNew = CreateNewChild(nClassID);

	if (pNew != NULL)
	{
		pNew->SetParent(this);
		AddTail(pNew);
	}

	return pNew;
}

long CExBaseList::XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys)
{
	long nCount = oNodes.GetNodeNum();
	long nIndex = 0;
	CExBaseObject *pNew = NULL;
	CXmlRWNodeBase *pNode = NULL;
	CString strNodeName;
	BOOL bAddToTail = TRUE;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pNode = oNodes.GetChild(nIndex);

		if (pNode == NULL)
		{
			continue;
		}

		pNew = CreateNewChild(*pNode, bAddToTail, pXmlRWKeys);

		if (pNew != NULL && bAddToTail)
		{
			pNew->SetParent(this);
			AddTail(pNew);
		}

		if (pNew)
		{
			pNew->XmlRead(*pNode, pXmlRWKeys);
		}

		bAddToTail = TRUE;
	}

	return 0;
}

//WriteXml
long CExBaseList::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}

long CExBaseList::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	long nClassID = 0;
	long nCount = 0;
	long nIndex = 0;
	
	if (oBinaryBuffer.IsCalSizeMode())
	{
		nCount = GetCount();
		oBinaryBuffer.AddBufferLength(sizeof(nCount));
		oBinaryBuffer.AddBufferLength(sizeof(nClassID) * nCount);

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			ASSERT (pos != NULL);
			pObj = GetNext(pos);
			pObj->Serialize(oBinaryBuffer);
		}
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		nCount = oBinaryBuffer.GetLong();
		
		for (nIndex=0;nIndex<nCount;nIndex++)
		{
			nClassID = oBinaryBuffer.GetLong();
			pObj = CreateNewChild(nClassID);
			ASSERT (pObj != NULL);
			
			if (pObj == NULL)
			{
				throw(-1);

			}

			pObj->SetParent(this);
			pObj->Serialize(oBinaryBuffer);
			AddNode(pObj);
		}
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		nCount = GetCount();
		oBinaryBuffer.PutLong(nCount);
		
		while (pos)
		{
			pObj = GetNext(pos);
			nClassID = pObj->GetClassID();
			oBinaryBuffer.PutLong(nClassID);
			pObj->Serialize(oBinaryBuffer);
		}
	}
	
	return 0;
}

long CExBaseList::InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	long nCount = 0;
	
	while (pos)
	{
		pObj = GetNext(pos);
		pObj->InsertTreeCtrl(pTreeCtrl,htiParent, dwParam);
		nCount++;
	}
	
	return nCount;
}

long CExBaseList::InsertChildToListCtrl(CListCtrl *pListCtrl, long nBeginIndex)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pObj = GetNext(pos);
		ASSERT(pObj != NULL);
		pObj->InsertToListCtrl(pListCtrl, nBeginIndex);	
		nBeginIndex++;
	}
	
	return nBeginIndex;
}

long CExBaseList::UpdateChildListCtrl(CListCtrl *pListCtrl, long nBeginIndex)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		ASSERT(pObj != NULL);
		pObj->UpdateListCtrl(pListCtrl, nBeginIndex);	
		nBeginIndex++;
	}

	return nBeginIndex;
}

long CExBaseList::UpdateChildListCtrlIndex(CListCtrl *pListCtrl, long nBeginIndex)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	CString strText;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		ASSERT(pObj != NULL);
		strText.Format(_T("%d"), nBeginIndex+1);
		pListCtrl->SetItemText(nBeginIndex, 0, strText);
		nBeginIndex++;
	}

	return nBeginIndex;
}

long CExBaseList::InsertChildreComboBox(CComboBox *pComboBox)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		pObj->InsertComboBox(pComboBox);		
	}

	return 0;
}

long CExBaseList::InsertChildreListBox(CListBox *pListBox)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
//	pListBox->ResetContent();

	while (pos != NULL)
	{
		pObj = GetNext(pos);

#ifndef exbase_not_use_m_dwReserved
		if (pObj->m_dwReserved != 0)
#endif
		{
			pObj->InsertListBox(pListBox);		
		}
	}

	return 0;
}

BOOL CExBaseList::CopyChildren(CBaseObject* pDest)
{
	if (pDest->IsBaseObject() || IsBaseObject())
	{
		return FALSE;
	}

	CExBaseList *pList = (CExBaseList*)pDest;
	CExBaseObject *pObj = NULL;
	CExBaseObject *pNew = NULL;
	POS pos = GetHeadPosition();
	pList->DeleteAll();

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		ASSERT(pObj != NULL);
		pNew = (CExBaseObject*)pObj->Clone();

		if (pNew != NULL)
		{
			pList->AddTail(pNew);
			pNew->SetParent(pList);
		}
	}

	return TRUE;
}

BOOL CExBaseList::IsEqualChildren(CBaseObject* pObj)
{
	if (pObj->IsBaseObject() && IsBaseObject())
	{
		return TRUE;
	}

	if (pObj->IsBaseObject() || IsBaseObject())
	{
		return FALSE;
	}

	CExBaseList *pList = (CExBaseList*)pObj;
	CExBaseObject *pObja = NULL, *pObjb = NULL;

	if (GetCount() != pList->GetCount())
	{
		return FALSE;
	}

	POS posa = GetHeadPosition();
	POS posb = pList->GetHeadPosition();

	while (posa != NULL && posb != NULL)
	{
		pObja = GetNext(posa);
		pObjb = GetNext(posb);
		ASSERT(pObja != NULL);
		ASSERT(pObjb != NULL);
		if (pObja->IsEqual(pObjb) == FALSE)
		{
			return FALSE;
		}
	}

	if (posa == NULL && posb == NULL)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

BOOL CExBaseList::UpdateChildren(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return FALSE;
	}

	if (!pDest->IsBaseList())
	{
		return FALSE;
	}

	CExBaseList *pDestList = (CExBaseList*)pDest;
	CExBaseObject *pObj = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();
// 	CExBaseList listAppend;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		ASSERT(pObj != NULL);
		pFind = (CExBaseObject *)pDestList->FindSame(pObj);

		if (pFind != NULL)
		{
			pObj->Update(pFind);
		}
// 		else
// 		{
// 			listAppend.AddTail(pObj);
// 		}
	}

// 	pDestList->AppendClone(listAppend);
// 	listAppend.RemoveAll();

	return TRUE;
}

CBaseObject* CExBaseList::FindSame(CBaseObject* pObj)
{
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);
		
		if (pObj->IsSame(p))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//删除子对象，并清空成员指针
void CExBaseList::DeleteChildren()
{
	DeleteAll();
}


BOOL CExBaseList::CanPaste(UINT nClassID)
{
	return FALSE;
}

BOOL CExBaseList::CanPaste(CExBaseObject *pObj)
{
	if (pObj == NULL)	
	{
		return FALSE;
	}

	return CanPaste(pObj->GetClassID());
}

BOOL CExBaseList::CanPaste(CExBaseList *pList)
{
	CExBaseObject *pObj = NULL;
	POS pos = pList->GetHeadPosition();
	BOOL bCanPaste = TRUE;

	while (pos != NULL)
	{
		pObj = pList->GetNext(pos);

		if (!CanPaste(pObj))
		{
			bCanPaste = FALSE;
			break;
		}
	}

	return bCanPaste;
}

long exbaselist_GetStrTailIndex(CString &strName)
{
	if (strName.GetLength() == 0)
	{
		return 1;
	}

	long nIndex = 1;
	char *pszName = NULL;

	CString_to_char(strName, &pszName);
	char *pEnd = pszName + strlen(pszName);
	char *pTemp = pEnd-1;

	while (pTemp >= pszName)
	{
		if ('0' <= *pTemp && *pTemp <= '9')
		{
			pTemp--;
		}
		else
		{
			break;
		}
	}

	if (pTemp != pEnd)
	{
		nIndex = atol(pTemp+1);
		*(pTemp+1) = 0;
		strName = pszName;
	}

	delete pszName;

	return nIndex;
}


void CExBaseList::InitNameAndIDForPaste(CExBaseObject *pObj)
{
	if ((FindByName(pObj->m_strName) == NULL) && (FindByID(pObj->m_strID) == NULL))
	{
		return;
	}

// 	if (FindByID(pObj->m_strID) == NULL)
// 	{
// 		return;
// 	}

	CString strName = pObj->m_strName;
	CString strID = pObj->m_strID;

	int nIndex = exbaselist_GetStrTailIndex(strName);
	CString strTemp = strName;
	nIndex = 1;

	while(FindByName(strTemp) != NULL)
	{
        //strTemp.Format(_T("%s%d"),strName.GetString(),nIndex++);
		//qt下，中文乱码
		strTemp.Format(_T("%d"), nIndex);
		strTemp = strName + strTemp;
		nIndex++;
	}

	pObj->m_strName = strTemp;
	nIndex = exbaselist_GetStrTailIndex(strID);
	strTemp = strID;
	nIndex = 1;

	while (FindByID(strTemp) != NULL)
	{
        //strTemp.Format(_T("%s%d"),strID.GetString(),nIndex++);
		//qt下，中文乱码
		strTemp.Format(_T("%d"), nIndex);
		strTemp = strID + strTemp;
		nIndex++;
	}

	pObj->m_strID = strTemp;
}

CExBaseObject* CExBaseList::Paste(CExBaseObject *pObj)
{
	if (!CanPaste(pObj))
	{
		return NULL;
	}

	CExBaseObject *pNew = (CExBaseObject*)pObj->Clone();
	InitNameAndIDForPaste(pNew);
	AddNewChild(pNew);

	return pNew;
}

CExBaseObject* CExBaseList::Paste(CExBaseList *pList)
{
	if (!CanPaste(pList))
	{
		return NULL;
	}

	CExBaseObject *pNew = NULL;
	CExBaseObject *p = NULL;
	POS pos = pList->GetHeadPosition();
	
	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		pNew = (CExBaseObject*)p->Clone();
		InitNameAndIDForPaste(pNew);
		AddNewChild(pNew);
	}
	
	return pNew;
}

CExBaseObject* CExBaseList::AddNew(const CString &strName, const CString &strID)
{
	CExBaseObject *p = new CExBaseObject();
	p->m_strName = strName;
	p->m_strID = strID;
	p->SetParent(this);
	AddTail(p);
	return p;
}

CBaseObject* CExBaseList::Clone()
{
	CExBaseList *pList = new CExBaseList();
	Copy(pList);
	return pList;
}

CExBaseObject* CExBaseList::AddNewChild(CExBaseObject *pNew, BOOL bInitNameAndId)
{
	if (bInitNameAndId)
	{
		InitNameAndIDForPaste(pNew);
	}

	AddTail(pNew);
	pNew->SetParent(this);
	return pNew;
}

CExBaseObject* CExBaseList::FindByClassID(DWORD dwClassID)
{
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (dwClassID == p->GetClassID())
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//2023-3-28  lijunqing
CExBaseObject* CExBaseList::FindByClassID(DWORD dwClassID, long nIndex)
{
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();
	long nTemp = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (dwClassID == p->GetClassID())
		{
			if (nTemp == nIndex)
			{
				pFind = p;
				break;
			}

			nTemp++;
		}
	}

	return pFind;
}

BOOL CExBaseList::AddChildren(UINT nChildClassID, long nCount)
{
	CExBaseObject *pNew = NULL;
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pNew = CreateNewChild(nChildClassID);

		if (pNew == NULL)
		{
			break;
		}

		AddNewChild(pNew);
	}

	return (pNew != NULL);
}

DWORD CExBaseList::FilterChildren(const CString &strTxtFilter, DWORD dwMode)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	DWORD dwTemp = 0;
	DWORD dwRet = 0;

	while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
	{
		pObj = (CExBaseObject*)GetNext(pos);
		dwTemp = pObj->Filter(strTxtFilter, dwMode);

		if (dwTemp > 0)
		{
			dwRet = max(dwTemp, dwRet);
		}
	}

#ifndef exbase_not_use_m_dwReserved
	m_dwReserved = max(dwRet, m_dwReserved);

	if (dwMode == FILTERMODE_CLEAR)
	{
		m_dwReserved = 0x0FFFFFFF;
	}

	return m_dwReserved;
#else
	return 0;
#endif
}

DWORD CExBaseList::FilterChildren_ID(const CString &strTxtFilter, DWORD dwMode)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	DWORD dwTemp = 0;
	DWORD dwRet = 0;

	while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
	{
		pObj = (CExBaseObject*)GetNext(pos);
		dwTemp = pObj->Filter_ID(strTxtFilter, dwMode);

		if (dwTemp > 0)
		{
			dwRet = max(dwTemp, dwRet);
		}
	}

#ifndef exbase_not_use_m_dwReserved
	m_dwReserved = max(dwRet, m_dwReserved);

	if (dwMode == FILTERMODE_CLEAR)
	{
		m_dwReserved = 0x0FFFFFFF;
	}

	return m_dwReserved;
#else
	return 0;
#endif
}

DWORD CExBaseList::FilterChildren_ID_Name(const CString &strTxtFilter, DWORD dwMode)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	DWORD dwTemp = 0;
	DWORD dwRet = 0;

	while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
	{
		pObj = (CExBaseObject*)GetNext(pos);
		dwTemp = pObj->Filter_ID_Name(strTxtFilter, dwMode);

		if (dwTemp > 0)
		{
			dwRet = max(dwTemp, dwRet);
		}
	}

#ifndef exbase_not_use_m_dwReserved
	m_dwReserved = max(dwRet, m_dwReserved);

	if (dwMode == FILTERMODE_CLEAR)
	{
		m_dwReserved = 0x0FFFFFFF;
	}

	return m_dwReserved;
#else
	return 0;
#endif
}

DWORD CExBaseList::FilterChildren_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	DWORD dwTemp = 0;
	DWORD dwRet = 0;

	while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
	{
		pObj = (CExBaseObject*)GetNext(pos);
		dwTemp = pObj->Filter_ID_Name_NoCase(strTxtFilter, dwMode);

		if (dwTemp > 0)
		{
			dwRet = max(dwTemp, dwRet);
		}
	}

#ifndef exbase_not_use_m_dwReserved
	m_dwReserved = max(dwRet, m_dwReserved);

	if (dwMode == FILTERMODE_CLEAR)
	{
		m_dwReserved = 0x0FFFFFFF;
	}

	return m_dwReserved;
#else
	return 0;
#endif
}
// 
// //////////////////////////////////////////////////////////////////////////
// //根据路径查找节点 匹配节点ID
// //CString &strPath			路径 
// //CExBaseList &oListDest	查找到的节点
// long CExBaseList::SelectEx(CString &strPath, CExBaseList &oListDest)
// {
// 	bool bIsBaseObject = IsBaseObject();
// 	CString strPathLeft, strPathRight;
// 	CExBaseObject* pObjTemp;
// 	CExBaseList* pListTemp;
// 
// 	//跳转至根节点 排除路径中的绝对路径
// 	int sep = strPath.ReverseFind('/');
// 	if (sep != -1)
// 	{
// 		pListTemp = (CExBaseList*)GetRoot();
// 		return pListTemp == NULL ? -1 : pListTemp->SelectEx(strPath.Mid(sep+1), oListDest);
// 	}
// 
// 	//路径开始处的'\'符号为冗余符号 在此处跳过这些冗余符号
// 	if (strPath[0] == '\\')
// 	{
// 		int i;
// 		for (i = 1;strPath[i] == '\\'; i++){}
// 		return SelectEx(strPath.Mid(i), oListDest);
// 	}
// 
// 	if (strPath == "")				//路径为空 当前节点符合条件
// 	{
// 		pObjTemp = (CExBaseObject*)this->Clone();
// 		pObjTemp->SetParent(this->GetParent());
// 		oListDest.AddTail(pObjTemp);
// 		return 0;
// 	}
// 
// 	sep = strPath.Find('\\');		//寻找第一个'\'符号，将路径分为两部分 左部为要跳转至的节点 右部为传递给下一节点的参数
// 	if (sep == -1)
// 	{
// 		strPathLeft = strPath;
// 		strPathRight = "";
// 	}
// 	else
// 	{
// 		strPathLeft = strPath.Left(sep);
// 		strPathRight = strPath.Mid(sep+1);
// 	}
// 	
// 	if (strPathLeft == ".")			//选择当前节点 继续查找
// 	{
// 		return this->SelectEx(strPathRight, oListDest);
// 	} 
// 	else if (strPathLeft == "..")	//选中父节点 继续查找
// 	{
// 		pListTemp = (CExBaseList*)GetParent();//parent一定是CExBaseList对象
// 		return pListTemp == NULL ? -1 : pListTemp->SelectEx(strPathRight, oListDest);
// 	}
// 	else if (strPathLeft == "?")	//匹配一级任意路径
// 	{
// 		if (bIsBaseObject == true)	//BaseObject 不存在子节点
// 		{
// 			return -1;
// 		}
// 
// 		CExBaseObject *pObj = NULL;
// 		POS pos = GetHeadPosition();
// 
// 		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
// 		{
// 			pObj = GetNext(pos);
// 			ASSERT(pObj != NULL);
// 			((CExBaseList*)pObj)->SelectEx(strPathRight, oListDest);//将指针pObj指定为CExBaseList*类型 可以调用SelectEx方法 即使它不是CExBaseList对象
// 		}
// 
// 		return 0;
// 	}
// 	else if (strPathLeft == "*")	//匹配任意级数的任意路径
// 	{
// 		this->SelectEx(strPathRight, oListDest);//将"*"匹配为空(零级)
// 
// 		if (bIsBaseObject == true)	//BaseObject 不存在子节点
// 		{
// 			return -1;
// 		}
// 
// 		CExBaseObject *pObj = NULL;
// 		POS pos = GetHeadPosition();
// 
// 		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
// 		{
// 			pObj = GetNext(pos);
// 			ASSERT(pObj != NULL);
// 			//((CExBaseList*)pObj)->SelectEx(strPathRight, oListDest);//将"*"匹配为"?"(一级)
// 			((CExBaseList*)pObj)->SelectEx(strPath, oListDest);     //将"*"传递至子节点(增加一级)
// 		}
// 	}
// 	else							//根据子节点ID查找
// 	{
// 		if (bIsBaseObject == true)	//BaseObject 不存在子节点
// 		{
// 			return -1;
// 		}
// 
// 		pListTemp = (CExBaseList*)this->FindByID(strPathLeft);
// 		return pListTemp == NULL ? -1 : pListTemp->SelectEx(strPathRight, oListDest);
// 	}
// 
// 	return 0;
// }

long CExBaseList::SelectChildren(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator)
{
//	CString strPathLeft, strPathRight;

	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();

	if (strPath.GetLength() == 0)
	{
		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
		{
			pObj = GetNext(pos);
			oListDest.AddTail(pObj);
		}
	}
	else
	{
		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
		{
			pObj = GetNext(pos);
			ASSERT(pObj != NULL);
			pObj->Select(strPath, oListDest, chSeperator);//将指针pObj指定为CExBaseList*类型 可以调用Select方法 即使它不是CExBaseList对象
		}
	}

	return 0;
}


long CExBaseList::FindByPathChildren(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	long nFindCount = 0;

	if (strPath.GetLength() == 0)
	{
		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
		{
			pObj = GetNext(pos);
			oListDest.AddTail(pObj);
		}

		nFindCount = m_nCount;
	}
	else
	{
		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
		{
			pObj = GetNext(pos);
			ASSERT(pObj != NULL);
			nFindCount += pObj->FindByPath(strPath, oListDest, chSeperator);//将指针pObj指定为CExBaseList*类型 可以调用Select方法 即使它不是CExBaseList对象
		}
	}

	return nFindCount;
}

//通过Name形成的路径，查找子对象  shaolei 20220527
long CExBaseList::FindByPathChildren_Name(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	long nFindCount = 0;

	if (strPath.GetLength() == 0)
	{
		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
		{
			pObj = GetNext(pos);
			oListDest.AddTail(pObj);
		}

		nFindCount = m_nCount;
	}
	else
	{
		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
		{
			pObj = GetNext(pos);
			ASSERT(pObj != NULL);
			nFindCount += pObj->FindByPath_Name(strPath, oListDest, chSeperator);//将指针pObj指定为CExBaseList*类型 可以调用Select方法 即使它不是CExBaseList对象
		}
	}

	return nFindCount;
}

long CExBaseList::SelectDatas(const CString &strIDPath, CExBaseList &oListDest, const CString &strSeperator)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (strIDPath.CompareNoCase(pObj->m_strID) == 0)
		{
			oListDest.AddTail(pObj);
		}
		else
		{
			if (pObj->IsBaseList())
			{
				strTemp = pObj->m_strID + strSeperator;

                if (str_n_compare(strTemp, strIDPath, strTemp.GetLength()) == 0)
                {
                    strTemp = strIDPath.Mid(strTemp.GetLength());
                    ((CExBaseList*)pObj)->SelectDatas(strTemp, oListDest, strSeperator);
                }

			}
			else
			{
				if (pObj->m_strID == strIDPath)
				{
					oListDest.AddTail(pObj);
				}
			}
		}
	}

// 	if (strPath.GetLength() == 0)
// 	{
// 		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
// 		{
// 			pObj = GetNext(pos);
// 			oListDest.AddTail(pObj);
// 		}
// 	}
// 	else
// 	{
// 		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
// 		{
// 			pObj = GetNext(pos);
// 			ASSERT(pObj != NULL);
// 			pObj->Select(strPath, oListDest, chSeperator);//将指针pObj指定为CExBaseList*类型 可以调用Select方法 即使它不是CExBaseList对象
// 		}
// 	}

	return NULL;
}

CExBaseObject* CExBaseList::SelectData(const CString &strIDPath, const CString &strSeperator)
{
	CExBaseList oList;
	SelectDatas(strIDPath, oList, strSeperator);
	CExBaseObject *pFind = NULL;

	if (oList.GetCount() == 1)
	{
		pFind = oList.GetHead();
	}

	oList.RemoveAll();

	return pFind;
}

CExBaseObject* CExBaseList::FindChildByIDEx(const CString &strID)
{
	CExBaseObject *pFind = FindByID(strID);

	if (pFind != NULL)
	{
		return pFind;
	}

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->IsBaseList())
		{
			pFind = ((CExBaseList*)p)->FindChildByIDEx(strID);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

CExBaseObject* CExBaseList::FindByIDPathEx(UINT nRootClassID, BOOL bHasRoot, const CString &strIDPath)
{
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (strIDPath == p->GetIDPathEx(nRootClassID, bHasRoot))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}


void CExBaseList::RemoveTail(UINT nRemoveClassID, long nCountRemove, CExBaseList &oListRemove)
{
	POS pos = GetTailPosition();
	long nIndex = 0;
	POS posCurr = NULL;
	CExBaseObject *p = NULL;

	if (nRemoveClassID <= 0)
	{
		while (pos != NULL)
		{
			p = GetAt(pos);
			oListRemove.AddTail(p);
			posCurr = pos;
			GetPrev(pos);
			RemoveAt(posCurr);
			nIndex++;

			if (nIndex >= nCountRemove)
			{
				break;
			}
		}
	}
	else
	{
		while (pos != NULL)
		{
			p = GetAt(pos);
			posCurr = pos;
			GetPrev(pos);

			if (p->GetClassID() == nRemoveClassID)
			{
				oListRemove.AddTail(p);
				RemoveAt(posCurr);
				nIndex++;

				if (nIndex >= nCountRemove)
				{
					break;
				}
			}
		}
	}

}

long CExBaseList::SelectChildrenByClassID(CExBaseList &listChild, UINT nChildClassID)
{
	POS pos  =GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == nChildClassID)
		{
			listChild.AddTail(p);
		}
	}

	return listChild.GetCount();
}

long CExBaseList::SelectChildrenByClassIDEx(CExBaseList &listChild, UINT nChildClassID)
{
	POS pos  =GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == nChildClassID)
		{
			listChild.AddTail(p);
		}

		if (p->IsBaseList(nClassID))
		{
			((CExBaseList*)p)->SelectChildrenByClassIDEx(listChild, nChildClassID);
		}
	}

	return listChild.GetCount();
}
long CExBaseList::QueryByID(const CString &strID, CExBaseList &oList)
{
	POS pos  =GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->m_strID == strID)
		{
			oList.AddTail(p);
		}

		if (p->IsBaseList())
		{
			((CExBaseList*)p)->QueryByID(strID, oList);
		}
	}

	return oList.GetCount();
}

void CExBaseList::DeleteByID(const CString &strID)
{
	CExBaseObject *pFind = (CExBaseObject*)FindByID(strID);

	if (pFind != NULL)
	{
		Delete(pFind);
	}
}

void CExBaseList::InitReserved(DWORD dwReserved)
{
	CExBaseObject::InitReserved(dwReserved);

	POS pos  =GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		p->InitReserved(dwReserved);
	}
}


void CExBaseList::InitItemData(DWORD dwItemData)
{
	CExBaseObject::InitItemData(dwItemData);

	POS pos  =GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		p->InitItemData(dwItemData);
	}
}


void CExBaseList::SortByID()
{
	CExBaseList listTemp;

	POS posSrc = GetHeadPosition();
	POS posDest = NULL;
	CExBaseObject *pSrc = NULL;
	CExBaseObject *pDest = NULL;
	POS pos = NULL;

	while (posSrc != NULL)
	{
		pSrc = GetNext(posSrc);
		posDest = listTemp.GetHeadPosition();
		pos = NULL;

		while (posDest != NULL)
		{
			pDest = (CExBaseObject *)listTemp.GetAt(posDest);

            if (str_compare( pSrc->m_strID, pDest->m_strID) < 0)
			{
				pos = posDest;
				break;
			}

			GetNext(posDest);
		}

		if (pos == NULL)
		{
			listTemp.AddTail(pSrc);
		}
		else
		{
			listTemp.InsertBefore(pos, pSrc);
		}
	}

	RemoveAll();
	Append(listTemp);
	listTemp.RemoveAll();
}

CString CExBaseList::GetXLangID(CExBaseObject *pChildObj)
{
	CString strXLangID;
	GetXLangID(pChildObj, strXLangID);
	return strXLangID;
}

void CExBaseList::GetXLangID(CExBaseObject *pChildObj, CString &strXLangID)
{
    strXLangID.Format(_T("#s%s_%s"), m_strID.GetString(), pChildObj->m_strID.GetString());
}



BOOL CExBaseList::ValidateForNew(CExBaseObject* pNewObj)
{
	return ValidateForNew(pNewObj, TRUE, TRUE);
}

BOOL CExBaseList::ValidateForNew(CExBaseObject* pNewObj, BOOL bValidateName, BOOL bValidateID)
{
	ASSERT(bValidateID || bValidateName);
	if (!bValidateName && !bValidateID)
	{
		bValidateName = TRUE;
	}

	CExBaseObject *pFind_Name = NULL, *pFind_ID=NULL;

	if (bValidateName)
	{
		pFind_Name = (CExBaseObject *)FindByName(pNewObj->m_strName);
	}

	if (bValidateID)
	{
		pFind_ID = (CExBaseObject *)FindByID(pNewObj->m_strID);
	}

	if (bValidateID && bValidateName)
	{
		return (pFind_ID == NULL && pFind_Name == NULL);
	}
	else
	{
		if (bValidateName)
		{
			return (pFind_Name == NULL);
		}

		return (pFind_ID == NULL);
	}
}


BOOL CExBaseList::ValidateForEdit(CExBaseObject* pEditRef, CExBaseObject *pEditTempData)
{
	return ValidateForEdit(pEditRef, pEditTempData, TRUE, TRUE);
}

void CExBaseList::CalChildrenSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile)
{
	POS pos  =GetHeadPosition();
	CExBaseObject *p = NULL;

#ifdef _DEBUG
	if (GetCount() >= 400)
	{
		int i = 0;
	}
#endif

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->CalObjSize(bCalChild, nObjCount, nTotalSize, pFile);
	}
}


void CExBaseList::Sort(BOOL bAscending)
{
	POS pos1 = GetHeadPosition();
	POS pos2 = pos1;

	CExBaseObject *p1 = NULL, *p2 = NULL;

	while (pos1 != NULL)
	{
		p1 = (CExBaseObject*)GetAt(pos1);
		pos2 = pos1;
		GetNext(pos2);

		while (pos2 != NULL)
		{
			p2  = (CExBaseObject*)GetAt(pos2);

			if (bAscending)
			{
				if (p2->ValCmp(p1) < 0)
				{
					SetAt(pos1, p2);
					SetAt(pos2, p1);
					p1 = p2;
				}
			}
			else
			{
				if (p2->ValCmp(p1) > 0)
				{
					SetAt(pos1, p2);
					SetAt(pos2, p1);
					p1 = p2;
				}
			}

			GetNext(pos2);
		}

		GetNext(pos1);
	}
}

void CExBaseList::Sort(DWORD dwAttrID, BOOL bAscending)
{
	POS pos1 = GetHeadPosition();
	POS pos2 = pos1;

	CExBaseObject *p1 = NULL, *p2 = NULL;

	while (pos1 != NULL)
	{
		p1 = (CExBaseObject*)GetAt(pos1);
		pos2 = pos1;
		GetNext(pos2);

		while (pos2 != NULL)
		{
			p2  = (CExBaseObject*)GetAt(pos2);

			if (bAscending)
			{
				if (p2->ValCmp(p1, dwAttrID) < 0)
				{
					SetAt(pos1, p2);
					SetAt(pos2, p1);
					p1 = p2;
				}
			}
			else
			{
				if (p2->ValCmp(p1, dwAttrID) > 0)
				{
					SetAt(pos1, p2);
					SetAt(pos2, p1);
					p1 = p2;
				}
			}

			GetNext(pos2);
		}

		GetNext(pos1);
	}
}

void CExBaseList::Sort(const CString &strAttrID, BOOL bAscending)
{
	POS pos1 = GetHeadPosition();
	POS pos2 = pos1;

	CExBaseObject *p1 = NULL, *p2 = NULL;

	while (pos1 != NULL)
	{
		p1 = (CExBaseObject*)GetAt(pos1);
		pos2 = pos1;
		GetNext(pos2);

		while (pos2 != NULL)
		{
			p2  = (CExBaseObject*)GetAt(pos2);

			if (bAscending)
			{
				if (p2->ValCmp(p1, strAttrID) < 0)
				{
					SetAt(pos1, p2);
					SetAt(pos2, p1);
					p1 = p2;
				}
			}
			else
			{
				if (p2->ValCmp(p1, strAttrID) > 0)
				{
					SetAt(pos1, p2);
					SetAt(pos2, p1);
					p1 = p2;
				}
			}

			GetNext(pos2);
		}

		GetNext(pos1);
	}
}

//
BOOL ExBaseObject_ValidateForEdit(CExBaseObject* pEditRef, CExBaseObject *pEditTempData, CExBaseObject *pCurr, BOOL bValidateName, BOOL bValidateID)
{
	if (bValidateID && bValidateName)
	{
		if (pCurr->m_strName == pEditTempData->m_strName || pCurr->m_strID == pEditTempData->m_strID)
		{
			return (pCurr == pEditRef);
		}
		else
		{
			return TRUE;
		}
	}

	if (bValidateName)
	{
		if (pCurr->m_strName == pEditTempData->m_strName)
		{
			return (pCurr == pEditRef);
		}
		else
		{
			return TRUE;
		}
	}

	if (pCurr->m_strID == pEditTempData->m_strID)
	{
		return (pCurr == pEditRef);
	}
	else
	{
		return TRUE;
	}
}

BOOL CExBaseList::ValidateForEdit(CExBaseObject* pEditRef, CExBaseObject *pEditTempData, BOOL bValidateName, BOOL bValidateID)
{
	ASSERT(bValidateID || bValidateName);
	if (!bValidateName && !bValidateID)
	{
		bValidateName = TRUE;
	}

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (ExBaseObject_ValidateForEdit(pEditRef, pEditTempData, p, bValidateName, bValidateID))
		{
			continue;
		}
		else
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

BOOL CExBaseList::ValidateForEdit(CExBaseObject *pEditTempData, BOOL bValidateName, BOOL bValidateID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);
		
		if (p == pEditTempData)
		{
			continue;
		}

		if (bValidateID && bValidateName)
		{
			if (p->m_strName == pEditTempData->m_strName || p->m_strID == pEditTempData->m_strID)
			{
				bTrue = FALSE;
				break;
			}
		}
		else
		{
			if (bValidateName)
			{
				if (p->m_strName == pEditTempData->m_strName)
				{
					bTrue = FALSE;
					break;
				}
			}
			else
			{
				if (p->m_strID == pEditTempData->m_strID)
				{
					bTrue = FALSE;
					break;
				}
			}
		}
	}

	return bTrue;
}

//////////////////////////////////////////////////////////////////////////
BOOL ValidateExBaseObjectName(CExBaseObject *pObj, CString &strName)
{
	CExBaseList *pParent = (CExBaseList*)pObj->GetParent();

	if (pParent == NULL)
	{
		return TRUE;
	}

	CExBaseObject *pFind = pParent->FindByName(strName);

	if (pFind != NULL && pFind != pObj)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Name=[%s] is already exist!"), strName.GetString());
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL ValidateExBaseObjectID(CExBaseObject *pObj, CString &strID)
{
	CExBaseList *pParent = (CExBaseList*)pObj->GetParent();

	if (pParent == NULL)
	{
		return TRUE;
	}

	CExBaseObject *pFind = pParent->FindByID(strID);

	if (pFind != NULL && pFind != pObj)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ID=[%s] is already exist!"), strID.GetString());
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL ValidateExBaseObjectNameAndID(CExBaseObject *pObj, CString &strName, CString &strID)
{
	if (!ValidateExBaseObjectName(pObj, strName))
	{
		return FALSE;
	}

	return ValidateExBaseObjectID(pObj, strID);
}

#ifndef NO_XDbBaseLib

BOOL CExBaseList::DB_SelectChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->DB_Select(pXDbLib, pXmlRWKeys, pXdbQueryMask);				
	}

	return TRUE;
}

BOOL CExBaseList::DB_Select(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask)
{
	if (DB_GetChildTableName(pXmlRWKeys) == NULL)
	{
		return DB_SelectChildren(pXDbLib, pXmlRWKeys, pXdbQueryMask);
	}

	CString strSQL;
	BOOL bRet = TRUE;

	if (m_pParent != NULL)
	{//作为子对象，从自身关联的数据表中，查询“外键”=“外键值”的数据集合
		bRet = DB_GetSQL_Select_Childrenren_ForeignKey(pXDbLib, pXmlRWKeys, strSQL);
	}
	else
	{
		bRet = DB_GetSQL_Select_Childrenren(pXDbLib, pXmlRWKeys, strSQL);
	}

	if (!bRet)
	{
		return bRet;
	}

	CXDbRecordsetBase *pRecordset = pXDbLib->ExecuteQuery(strSQL);

	if (pRecordset == NULL)
	{
		return FALSE;
	}

	CExBaseObject *pNew = NULL;

	while (!pRecordset->IsEof())
	{
		pNew = DB_CreateNewChild(); //【数据库模式下，永远只有一个子对象】

		if (pNew == NULL)
		{
			ASSERT (FALSE);
			break;
		}

		AddNewChild(pNew);
		pNew->DB_ReadFields(pRecordset, pXmlRWKeys);
// 		AddTail(pNew);
// 		pNew->SetParent(this);
		pNew->InitAfterRead();
		pRecordset->MoveNext();
	}

	pRecordset->Free();
	if (pXdbQueryMask != NULL)
	{
		if (pXdbQueryMask->NeedQueryChildren(GetClassID()))
		{
			DB_SelectChildren(pXDbLib, pXmlRWKeys, pXdbQueryMask);
		}
	}
	else
	{
		DB_SelectChildren(pXDbLib, pXmlRWKeys, pXdbQueryMask);
	}
	return TRUE;
}

BOOL CExBaseList::DB_DeleteChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->DB_Delete(pXDbLib, pXmlRWKeys);
	}

	return TRUE;
}

BOOL CExBaseList::DB_Insert_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	if (pXdbQueryMask != NULL)
	{
		while (pos != NULL)
		{
			p = GetNext(pos);

			if (pXdbQueryMask->NeedQueryChildren(p->GetClassID()))
			{
				p->DB_Insert(pXDbLib, pXmlRWKeys, pXdbQueryMask);
			}						
		}
	}
	else
	{
		while (pos != NULL)
		{
			p = GetNext(pos);
			p->DB_Insert(pXDbLib, pXmlRWKeys, pXdbQueryMask);
		}
	}

	return TRUE;
}


BOOL CExBaseList::DB_SetForeignKeyValue_Children(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->DB_SetForeignKeyValue(pXmlRWKeys, oPKeyValue);
	}

	return TRUE;
}

BOOL CExBaseList::DB_Update_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->DB_Update(pXDbLib,pXmlRWKeys);
	}

	return TRUE;
}

BOOL CExBaseList::DB_Update_Children_Cmd(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->DB_Update_Cmd(pXDbLib,pXmlRWKeys);
	}

	return TRUE;
}

BOOL CExBaseList::DB_UpdateEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	pXDbLib->StartTransaction();

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->DB_Update_Cmd(pXDbLib,pXmlRWKeys);
//		p->DB_Update(pXDbLib,pXmlRWKeys);	
	}

	pXDbLib->Commit();

	return TRUE;
}

BOOL CExBaseList::DB_SelectEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString strFK, CString strFKVal)
{
	CString strSQL, strTable;
	strTable = DB_GetChildTableName(pXmlRWKeys);
	if (strTable.IsEmpty())
	{
		return FALSE;
	}

	if (strFK.IsEmpty() || strFKVal.IsEmpty())
	{
        strSQL.Format(_T("select * from %s"), strTable.GetString());
	}
	else
	{
        strSQL.Format(_T("select * from %s where %s=\"%s\""), strTable.GetString(), strFK.GetString(), strFKVal.GetString());
	}
	
	CXDbRecordsetBase *pRecordset = pXDbLib->ExecuteQuery(strSQL);

	if (pRecordset == NULL)
	{
		return FALSE;
	}

	CExBaseObject *pNew = NULL;

	while (!pRecordset->IsEof())
	{
		pNew = DB_CreateNewChild(); //【数据库模式下，永远只有一个子对象】

		if (pNew == NULL)
		{
			ASSERT (FALSE);
			break;
		}

		AddNewChild(pNew);
		pNew->DB_ReadFields(pRecordset, pXmlRWKeys);
// 		AddTail(pNew);
// 		pNew->SetParent(this);
		pNew->InitAfterRead();
		pRecordset->MoveNext();
	}

	pRecordset->Free();
	return TRUE;
}

BOOL CExBaseList::DB_SelectSqlEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSql)
{
	if (strSql.IsEmpty())
	{
		return FALSE;
	}

	CXDbRecordsetBase *pRecordset = pXDbLib->ExecuteQuery(strSql);
	if (pRecordset == NULL)
	{
		return FALSE;
	}

	CExBaseObject *pNew = NULL;

	while (!pRecordset->IsEof())
	{
		pNew = DB_CreateNewChild(); //【数据库模式下，永远只有一个子对象】

		if (pNew == NULL)
		{
			ASSERT (FALSE);
			break;
		}

		AddNewChild(pNew);
		pNew->DB_ReadFields(pRecordset, pXmlRWKeys);
// 		AddTail(pNew);
// 		pNew->SetParent(this);
		pNew->InitAfterRead();
		pRecordset->MoveNext();
	}

	pRecordset->Free();
	return TRUE;
}

BOOL CExBaseList::DB_InsertEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CExBaseObject *pObj = NULL;

	CXDbRecordsetBase *pRecordset = NULL;
	CString strTable, strPkey, strPkeyValue;

	//DB_SetForeignKeyValue_Children(pXmlRWKeys, oPKeyValue);

	strTable = DB_GetChildTableName(pXmlRWKeys);
	pRecordset = pXDbLib->SQLNewRecordset(strTable, strPkey, strPkeyValue);

	pXDbLib->StartTransaction();

	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pObj = GetNext(pos);
		pObj->DB_Insert_Own(pXDbLib, pRecordset, pXmlRWKeys, NULL);
	}

	pXDbLib->Commit();
	pRecordset->Free();

	return TRUE;
}

CExBaseObject* CExBaseList::FindByPkValue(__int64 &n64FindPKVal)
{
	CXDb_PKeyValue oKeyValue;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL; 

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);
		p->Db_GetPkeyValue(oKeyValue);

		if (oKeyValue == n64FindPKVal)
		{
			return p;
		}
	}

	return NULL;
}

CExBaseObject* CExBaseList::FindByPkValue(long &nFindPKVal)
{
	if (nFindPKVal <= 0)
	{
		return NULL;
	}

	CXDb_PKeyValue oKeyValue;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL; 

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);
		p->Db_GetPkeyValue(oKeyValue);

		if (oKeyValue == nFindPKVal)
		{
			return p;
		}
	}

	return NULL;
}

CExBaseObject* CExBaseList::FindByPkValue(const CString &strFindPKVal)
{
	CXDb_PKeyValue oKeyValue;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL; 

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);
		p->Db_GetPkeyValue(oKeyValue);

		if (oKeyValue == strFindPKVal)
		{
			return p;
		}
	}

	return NULL;
}

CExBaseObject* CExBaseList::FindByPkValue(CXDb_PKeyValue &oPkValue)
{
	CXDb_PKeyValue oKeyValue;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL; 

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);
		p->Db_GetPkeyValue(oKeyValue);

		if (oKeyValue == oPkValue)
		{
			return p;
		}
	}

	return NULL;
}

void CExBaseList::DB_InitNameAttrs()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);
		p->DB_InitNameAttrs();
	}
}

//////////////////////////////////////////////////////////////////////////
BOOL DB_ValidateExBaseObjectNameAndPk_New(CExBaseObject *pObj, const CString &strName, CString &strMsg)
{
	CExBaseList *pList = (CExBaseList*)pObj->GetParent();
	CExBaseObject *p = NULL;
	POS pos = pList->GetHeadPosition();
	BOOL bTue = TRUE;
	CXDb_PKeyValue oPkVal, oPkValCurr;
	pObj->Db_GetPkeyValue(oPkValCurr);

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->m_strName == strName)
		{
            strMsg.Format(_T("存在相同的名称【%s】"), strName.GetString());
			bTue = FALSE;
			break;
		}

		p->Db_GetPkeyValue(oPkVal);

		if (oPkVal == oPkValCurr)
		{
			CString strValue;
			oPkVal.GetValue(strValue);
            strMsg.Format(_T("存在相同的值【%s】"), strValue.GetString());
			bTue = FALSE;
			break;
		}
	}

	return bTue;
}

BOOL DB_ValidateExBaseObjectNameAndPk_Edit(CExBaseObject *pObj, CExBaseObject *pRefObj, const CString &strName, CString &strMsg)
{
	CExBaseList *pList = (CExBaseList*)pObj->GetParent();
	CExBaseObject *p = NULL;
	POS pos = pList->GetHeadPosition();
	BOOL bTue = TRUE;
	CXDb_PKeyValue oPkVal, oPkValCurr;
	pObj->Db_GetPkeyValue(oPkValCurr);

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->m_strName == strName && p != pRefObj)
		{
            strMsg.Format(_T("存在相同的名称【%s】"), strName.GetString());
			bTue = FALSE;
			break;
		}

		p->Db_GetPkeyValue(oPkVal);

		if (oPkVal == oPkValCurr && p != pRefObj)
		{
			CString strValue;
			oPkVal.GetValue(strValue);
            strMsg.Format(_T("存在相同的值【%s】"), strValue.GetString());
			bTue = FALSE;
			break;
		}
	}

	return bTue;
}
#endif