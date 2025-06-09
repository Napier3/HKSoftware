// ExBaseObject.cpp: implementation of the CExBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExBaseObject.h"
#include "ExBaseList.h"
#include "../API/GlobalConfigApi.h"

//QT Windows  SysFreeString......
#ifndef _PSX_QT_LINUX_
#include "oleauto.h"
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExBaseObject::CExBaseObject()
{
	m_dwItemData = 0;
	m_pParent = NULL;
#ifndef exbase_not_use_m_dwReserved
	m_dwReserved = 0x0FFFFFFF;
#endif
}

CExBaseObject::~CExBaseObject()
{

}


long CExBaseObject::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	if (xml_GetAttibuteValue(pXmlRWKeys->m_strNameKey, oNode, m_strName))
	{
	}
	else
	{
	}
	
	xml_GetAttibuteValue(pXmlRWKeys->m_strIDKey, oNode, m_strID);
	
	return 0;
}

long CExBaseObject::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlRWKeys->m_strIDKey, oElement, m_strID);
	
	return 0;
}

long CExBaseObject::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
	{
		//oBinaryBuffer.AddBufferLength((m_strName.GetLength()+1)*2);
		//oBinaryBuffer.AddBufferLength((m_strID.GetLength()+1)*2);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strName);
		BinarySerializeWrite(oBinaryBuffer,m_strID);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strID);
	}
	else
	{
	}

	return 0;
}

//树形控件相关的操作
void CExBaseObject::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	InsertOwnTreeCtrl(pTreeCtrl, htiParent, dwParam);
	
	InsertChildrenTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData, dwParam);
}

void CExBaseObject::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(m_strName, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

long CExBaseObject::InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)  {   return 0;  }

long CExBaseObject::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	PFuc_InitListCtrlColumns *pFunc = GetInitListCtrlColumnsFunc();
	pListCtrl->DeleteAllItems();

	while (TRUE)
	{
		BOOL b = pListCtrl->DeleteColumn(0);

		if (!b)
		{
			break;
		}
	}

	if (pFunc != NULL)
	{
		pFunc(pListCtrl);
		return TRUE;
	}

	return FALSE;
}

long CExBaseObject::InsertChildToListCtrl(CListCtrl *pListCtrl, long nBeginIndex) {	return 0;  }

long CExBaseObject::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)  {	return 0;  }

// 将对象插入到列表视图中
long CExBaseObject::InsertToListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
#ifdef _UNICODE
	pListCtrl->InsertItem(lItemIndex, _T(""), 0);
#else
	pListCtrl->InsertItem(lItemIndex, "", 0);
#endif

	return UpdateListCtrl(pListCtrl, lItemIndex);
}

long CExBaseObject::InsertComboBox(CComboBox *pComboBox)
{
	long nIndex = pComboBox->AddString(m_strName);
	pComboBox->SetItemDataPtr(nIndex, this);
	return nIndex;
}

long CExBaseObject::InsertChildreComboBox(CComboBox *pComboBox)  {   return 0;  }


long CExBaseObject::InsertListBox(CListBox *pListBox)
{
	long nIndex = pListBox->AddString(m_strName);
	pListBox->SetItemDataPtr(nIndex, this);
	return nIndex;
}

long CExBaseObject::InsertChildreListBox(CListBox *pListBox)  {   return 0;  }

DWORD CExBaseObject::Filter(const CString &strTxtFilter, DWORD dwMode)
{
	FilterOwn(strTxtFilter, dwMode);
	FilterChildren(strTxtFilter, dwMode);

#ifndef exbase_not_use_m_dwReserved
	return m_dwReserved;
#else
	return 0;
#endif
}

DWORD CExBaseObject::FilterOwn(const CString &strTxtFilter, DWORD dwMode)
{
#ifndef exbase_not_use_m_dwReserved
	if (dwMode == FILTERMODE_EQUAL)
	{
		if (m_strName == strTxtFilter)
		{
			m_dwReserved = 1;
		}
		else
		{
			m_dwReserved = 0;
		}
	}
	else if (dwMode == FILTERMODE_HAS)
	{
		if (m_strName.Find(strTxtFilter) >= 0)
		{
			m_dwReserved = 1;
		}
		else
		{
			m_dwReserved = 0;
		}
	}
	else if (dwMode == FILTERMODE_CLEAR)
	{
		m_dwReserved = 0x0FFFFFFF;
	}

#endif
	return dwMode;
}

DWORD CExBaseObject::FilterChildren(const CString &strTxtFilter, DWORD dwMode)
{
	return 0;
}

DWORD CExBaseObject::Filter_ID(const CString &strTxtFilter, DWORD dwMode)
{
#ifndef exbase_not_use_m_dwReserved
	FilterOwn_ID(strTxtFilter, dwMode);
	FilterChildren_ID(strTxtFilter, dwMode);

	return m_dwReserved;
#else
	return 0;
#endif
}

DWORD CExBaseObject::FilterOwn_ID(const CString &strTxtFilter, DWORD dwMode)
{
#ifndef exbase_not_use_m_dwReserved
	if (dwMode == FILTERMODE_EQUAL)
	{
		if (m_strID == strTxtFilter)
		{
			m_dwReserved = 1;
		}
		else
		{
			m_dwReserved = 0;
		}
	}
	else if (dwMode == FILTERMODE_HAS)
	{
		if (m_strID.Find(strTxtFilter) >= 0)
		{
			m_dwReserved = 1;
		}
		else
		{
			m_dwReserved = 0;
		}
	}
	else if (dwMode == FILTERMODE_CLEAR)
	{
		m_dwReserved = 0x0FFFFFFF;
	}

#endif
	return dwMode;
}

DWORD CExBaseObject::FilterChildren_ID(const CString &strTxtFilter, DWORD dwMode)
{
	return 0;
}

DWORD CExBaseObject::Filter_ID_Name(const CString &strTxtFilter, DWORD dwMode)
{
#ifndef exbase_not_use_m_dwReserved
	FilterOwn_ID_Name(strTxtFilter, dwMode);
	FilterChildren_ID_Name(strTxtFilter, dwMode);

	return m_dwReserved;
#else
	return 0;
#endif
}

DWORD CExBaseObject::FilterOwn_ID_Name(const CString &strTxtFilter, DWORD dwMode)
{
#ifndef exbase_not_use_m_dwReserved
	if (dwMode == FILTERMODE_EQUAL)
	{
		if (m_strID == strTxtFilter)
		{
			m_dwReserved = 1;
		}
		else if (m_strName == strTxtFilter)
		{
			m_dwReserved = 1;
		}
		else
		{
			m_dwReserved = 0;
		}
	}
	else if (dwMode == FILTERMODE_HAS)
	{
		if (m_strID.Find(strTxtFilter) >= 0)
		{
			m_dwReserved = 1;
		}
		else if (m_strName.Find(strTxtFilter) >= 0)
		{
			m_dwReserved = 1;
		}
		else
		{
			m_dwReserved = 0;
		}
	}
	else if (dwMode == FILTERMODE_CLEAR)
	{
		m_dwReserved = 0x0FFFFFFF;
	}

#endif
	return dwMode;
}

DWORD CExBaseObject::FilterChildren_ID_Name(const CString &strTxtFilter, DWORD dwMode)
{
	return 0;
}

DWORD CExBaseObject::Filter_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode)
{
#ifndef exbase_not_use_m_dwReserved
	FilterOwn_ID_Name_NoCase(strTxtFilter, dwMode);
	FilterChildren_ID_Name_NoCase(strTxtFilter, dwMode);

	return m_dwReserved;
#else
	return 0;
#endif
}

DWORD CExBaseObject::FilterOwn_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode)
{
	CString strFilter,strID,strName;
	strFilter = strTxtFilter;
	strID = m_strID;
	strName = m_strName;

	strFilter.MakeLower();
	strID.MakeLower();
	strName.MakeLower();

#ifndef exbase_not_use_m_dwReserved
	if (dwMode == FILTERMODE_EQUAL)
	{
		if (strID == strFilter)
		{
			m_dwReserved = 1;
		}
		else if (strName == strFilter)
		{
			m_dwReserved = 1;
		}
		else
		{
			m_dwReserved = 0;
		}
	}
	else if (dwMode == FILTERMODE_HAS)
	{
		if (strID.Find(strFilter) >= 0)
		{
			m_dwReserved = 1;
		}
		else if (strName.Find(strFilter) >= 0)
		{
			m_dwReserved = 1;
		}
		else
		{
			m_dwReserved = 0;
		}
	}
	else if (dwMode == FILTERMODE_CLEAR)
	{
		m_dwReserved = 0x0FFFFFFF;
	}

#endif
	return dwMode;
}

DWORD CExBaseObject::FilterChildren_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//编辑：复制、克隆
BOOL CExBaseObject::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj != NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	if (m_strName != ((CExBaseObject*)pObj)->m_strName)
	{
		return FALSE;
	}

	if (m_strID != ((CExBaseObject*)pObj)->m_strID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CExBaseObject::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CExBaseObject*)pDest)->m_strID = m_strID;
	((CExBaseObject*)pDest)->m_strName = m_strName;

#ifndef exbase_not_use_m_dwReserved
	((CExBaseObject*)pDest)->m_dwReserved = m_dwReserved;
#endif

	return TRUE;
}

CBaseObject* CExBaseObject::Clone()
{
	CExBaseObject *pNew = new CExBaseObject();
	Copy(pNew);
	return pNew;
}

CBaseObject* CExBaseObject::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CExBaseObject *pNew = new CExBaseObject();
	if(bCopyOwn)
	{
		CopyOwn(pNew);
	}
	if(bCopyChildren)
	{
		CopyChildren(pNew);
	}	
	return pNew;
}

BOOL CExBaseObject::IsSame(CBaseObject* pObj)
{
	if (GetClassID() != pObj->GetClassID())
	{
		return FALSE;
	}

	if (GetXmlElementKey() != pObj->GetXmlElementKey())
	{
		return FALSE;
	}

	if (m_strName != ((CExBaseObject*)pObj)->m_strName)
	{
		return FALSE;
	}

	if (m_strID != ((CExBaseObject*)pObj)->m_strID)
	{
		return FALSE;
	}

	return TRUE;
}

void CExBaseObject::InitReserved(DWORD dwReserved)
{
#ifndef exbase_not_use_m_dwReserved
	m_dwReserved = dwReserved;
#endif
}

void CExBaseObject::InitItemData(DWORD dwItemData)
{
	m_dwItemData = dwItemData;
}

long CExBaseObject::GetAllAncestor(CExBaseList *pList)
{
	ASSERT (pList != NULL);
	CExBaseObject *pParent = (CExBaseObject*)m_pParent;

	while (pParent != NULL)
	{
		pList->AddHead(pParent);
		pParent = (CExBaseObject *)pParent->GetParent();
	}

	return pList->GetCount();
}

long CExBaseObject::GetAllAncestor(CExBaseList *pList, UINT nClassID)
{
	ASSERT (pList != NULL);
	CExBaseObject *pParent = (CExBaseObject*)m_pParent;


	while (pParent != NULL)
	{
		pList->AddHead(pParent);

		if (pParent->GetClassID() == nClassID)
		{
			break;
		}

		pParent = (CExBaseObject *)pParent->GetParent();
	}

	return pList->GetCount();
}

long CExBaseObject::GetAllAncestorEqClassID(CExBaseList *pList, UINT nClassID)
{
	ASSERT (pList != NULL);
	CExBaseObject *pParent = (CExBaseObject*)m_pParent;


	while (pParent != NULL)
	{
		if (pParent->GetClassID() != nClassID)
		{
			break;
		}

		pList->AddHead(pParent);
		pParent = (CExBaseObject *)pParent->GetParent();
	}

	return pList->GetCount();
}

BOOL CExBaseObject::GetRefObjPath(CExBaseObject *pRefObj, CString &strPath)
{
	if (this == pRefObj)
	{
		strPath = _T("");
		return TRUE;
	}

	CExBaseList oListOwn;
	CExBaseList oListRef;

	long nCountOwn = GetAllAncestor(&oListOwn);
	long nCountRef = pRefObj->GetAllAncestor(&oListRef);
	oListOwn.AddTail(this);
	oListRef.AddTail(pRefObj);
	long nSameDepth = 0;
	long nIndex = 0;
	long nCount = min(nCountOwn, nCountRef)+1;
	CExBaseObject *p1 = NULL;
	CExBaseObject *p2 = NULL;
	CExBaseObject *pAncester = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		p1 = oListOwn.GetAtIndex(nIndex);
		p2 = oListRef.GetAtIndex(nIndex);

		if (p1 != p2)
		{
			break;
		}

		pAncester = p1;
		nSameDepth++;
	}

	strPath.Empty();

	//自身到最后一个共同祖先的路径
	POS pos = oListOwn.GetTailPosition();
	oListOwn.GetPrev(pos);
	
	while (pos != NULL)
	{
		p1 = (CExBaseObject *)oListOwn.GetPrev(pos);
		strPath += _T("..\\\\");
		
		if (pAncester == p1)
		{
			break;
		}

		//oListOwn.GetPrev(pos);
	}

	//到参考节点的路径
	pos = oListRef.Find(pAncester);

	if (pos == NULL)
	{
		oListOwn.RemoveAll();
		oListRef.RemoveAll();
		return FALSE;
	}

	oListRef.GetNext(pos);

	while (pos != NULL)
	{
		p2 = (CExBaseObject *)oListRef.GetNext(pos);
		strPath += p2->m_strID;

		if (pos != NULL)
		{
			strPath += _T("\\\\");
		}

		//oListRef.GetNext(pos);
	}

	//strPath += pRefObj->m_strID;

	oListOwn.RemoveAll();
	oListRef.RemoveAll();

	return TRUE;
}

CString CExBaseObject::GetPath()
{
	CString strTemp, strRet;
	CBaseObject* pTemp;

	strRet = "";

	for (pTemp = this; pTemp != NULL; pTemp = pTemp->GetParent())
	{
		strTemp = strRet;
		strRet = ((CExBaseObject*)pTemp)->m_strID;
		strRet += "\\\\";
		strRet += strTemp;
	}

	strRet.TrimRight('\\');
	return strRet;
}


//////////////////////////////////////////////////////////////////////////
//根据路径查找节点 匹配节点ID
//CString &strPath			路径 
//CExBaseList &oListDest	查找到的节点
long CExBaseObject::Select(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator)
{
	bool bIsBaseObject = IsBaseObject();
	CString strPathLeft, strPathRight;
	CExBaseList* pListTemp;

	//跳转至根节点 排除路径中的绝对路径
	int nSepPos = strPath.ReverseFind('/');
	
	if (nSepPos != -1)
	{
		pListTemp = (CExBaseList*)GetRoot();
        CString strPath2 = strPath.Mid(nSepPos+1);
        return pListTemp == NULL ? -1 : pListTemp->Select(strPath2, oListDest, chSeperator);
	}

	if (strPath[0] == chSeperator)
	{	//路径开始处的'\'符号为分隔符号 在此处跳过这些符号
		int i = 1;
		for (i = 1;strPath[i] == chSeperator; i++);
        CString strPath2 = strPath.Mid(i);
        return Select(strPath2, oListDest, chSeperator);
	}

	if (strPath == "")	
	{//路径为空 当前节点符合条件
		oListDest.AddTail(this);
		return 0;
	}

	nSepPos = strPath.Find(chSeperator);		//寻找第一个'\'符号，将路径分为两部分 左部为要跳转至的节点 右部为传递给下一节点的参数

	if (nSepPos == -1)
	{
		strPathLeft = strPath;
		strPathRight = "";
	}
	else
	{
		strPathLeft = strPath.Left(nSepPos);
		strPathRight = strPath.Mid(nSepPos+1);
	}

	if (strPathLeft == ".")			//选择当前节点 继续查找
	{
		Select(strPathRight, oListDest, chSeperator);
	} 
	else if (strPathLeft == "..")	//选中父节点 继续查找
	{
		pListTemp = (CExBaseList*)GetParent();//parent一定是CExBaseList对象
		pListTemp == NULL ? -1 : pListTemp->Select(strPathRight, oListDest, chSeperator);
	}
	else if (strPathLeft == "?")	//匹配一级任意路径
	{
		if (! bIsBaseObject)	
		{//BaseObject 不存在子节点
			SelectChildren(strPathRight, oListDest, chSeperator);
		}
	}
	else if (strPathLeft == "*")	//匹配任意级数的任意路径
	{
		Select(strPathRight, oListDest, chSeperator);//将"*"匹配为空(零级)

		if ( ! bIsBaseObject)	//BaseObject 不存在子节点
		{
			//SelectChildren(strPathRight, oListDest);
			SelectChildren(strPath, oListDest, chSeperator);
		}
	}
	else
	{
		SelectLeft_Var(strPath, strPathLeft, strPathRight, oListDest, chSeperator);
	}

	return 0;
}

long CExBaseObject::SelectChildren(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator)		{		return 0;		};

long CExBaseObject::SelectLeft_Var(CString &strPath, CString &strPathLeft, CString &strPathRight, CExBaseList &oListDest, TCHAR chSeperator)
{
	BOOL bIsBaseObject = IsBaseObject();

	if (bIsBaseObject)	//BaseObject 不存在子节点
	{
		if (strPathRight == "")
		{
			if (strPath == m_strID)
			{
				oListDest.AddTail(this);
			}
		}

		return 0;
	}
	else
	{
		CExBaseObject *pObj = NULL;

		if (strPathRight == "")
		{
			pObj = ((CExBaseList*)this)->FindByID(strPathLeft);

			if (pObj != NULL)
			{
				oListDest.AddTail(pObj);
			}
			else if (strPath == m_strID)
			{
				oListDest.AddTail(this);
			}
		}
		else
		{
			pObj = ((CExBaseList*)this)->FindByID(strPathLeft);

			if (pObj == NULL)
			{
				return -1;
			}
			else
			{
				pObj->Select(strPathRight, oListDest, chSeperator);
			}
		}
	}

	return 0;
}

long CExBaseObject::FindByPath(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator)
{
	bool bIsBaseObject = IsBaseObject();
	CString strPathLeft, strPathRight;

	if (m_strID.GetLength() == 0)
	{
		return FindByPathChildren(strPath, oListDest, chSeperator);
	}

	if (strPath == "")	
	{//路径为空 当前节点符合条件
		oListDest.AddTail(this);
		return 1;
	}

	long nLen = m_strID.GetLength();
	long nPathLen = strPath.GetLength();

	if (nPathLen < nLen)
	{
		return 0;
	}

	if (nPathLen == nLen)
	{
		if (m_strID == strPath)
		{
			oListDest.AddTail(this);
			return 1;
		}

		return 0;
	}

	if (strPath.GetAt(nLen) == chSeperator)
	{
		if (m_strID == strPath.Left(nLen))
		{
			strPath = strPath.Mid(nLen + 1);
			return FindByPathChildren(strPath, oListDest, chSeperator);
		}
	}

	return 0;
}

long CExBaseObject::FindByPathChildren(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator)
{	
	return 0;	
};

//通过Name形成的路径，查找子对象  shaolei 20220527
long CExBaseObject::FindByPath_Name(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator)
{
	bool bIsBaseObject = IsBaseObject();
	CString strPathLeft, strPathRight;

	if (m_strName.GetLength() == 0)
	{
		return FindByPathChildren_Name(strPath, oListDest, chSeperator);
	}

	if (strPath == "")	
	{//路径为空 当前节点符合条件
		oListDest.AddTail(this);
		return 1;
	}

	long nLen = m_strName.GetLength();
	long nPathLen = strPath.GetLength();

	if (nPathLen < nLen)
	{
		return 0;
	}

	if (nPathLen == nLen)
	{
		if (m_strName == strPath)
		{
			oListDest.AddTail(this);
			return 1;
		}

		return 0;
	}

	if (strPath.GetAt(nLen) == chSeperator)
	{
		if (m_strName == strPath.Left(nLen))
		{
			strPath = strPath.Mid(nLen + 1);
			return FindByPathChildren_Name(strPath, oListDest, chSeperator);
		}
	}

	return 0;
}

long CExBaseObject::FindByPathChildren_Name(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator)
{
	return 0;
};

CString CExBaseObject::GetIDPathEx(UINT nRootClassID, BOOL bHasRoot, const CString &strSeperator)
{
	CString strPath;
	CExBaseObject *pParent = this;
	CString strTemp;

	if (bHasRoot)
	{
		while (pParent != NULL)
		{
            strTemp.Format(_T("%s%s"), pParent->m_strID.GetString(), strSeperator.GetString());
			strPath = strTemp + strPath;

			if (pParent->GetClassID() == nRootClassID)
			{
				break;
			}

			pParent = (CExBaseObject *)pParent->GetParent();
		}
	}
	else
	{
		while (pParent != NULL)
		{
			if (pParent->GetClassID() == nRootClassID)
			{
				break;
			}

            strTemp.Format(_T("%s%s"), pParent->m_strID.GetString(), strSeperator.GetString());
			strPath = strTemp + strPath;
			pParent = (CExBaseObject *)pParent->GetParent();
		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		nLen = nLen - strSeperator.GetLength();
		strPath = strPath.Left(nLen);
	}

	return strPath;
}

CString CExBaseObject::GetNamePathEx(UINT nRootClassID, BOOL bHasRoot, const CString &strSeperator)
{
	CString strPath;
	CExBaseObject *pParent = this;
	CString strTemp;

	if (bHasRoot)
	{
		while (pParent != NULL)
		{
            //strTemp.Format(_T("%s%s"), pParent->m_strName.GetString(), strSeperator.GetString());
			//QT下，Format中文乱码，改为不用Format
			strTemp = pParent->m_strName + strSeperator;
			strPath = strTemp + strPath;

			if (nRootClassID != 0xFFFFFFFF)
			{
				if (pParent->GetClassID() == nRootClassID)
				{
					break;
				}
			}

			pParent = (CExBaseObject *)pParent->GetParent();
		}
	}
	else
	{
		while (pParent != NULL)
		{
			if (nRootClassID != 0xFFFFFFFF)
			{
				if (pParent->GetClassID() == nRootClassID)
				{
					break;
				}
			}

            //strTemp.Format(_T("%s%s"), pParent->m_strName.GetString(), strSeperator.GetString());
			//QT下，Format中文乱码，改为不用Format
			strTemp = pParent->m_strName + strSeperator;
			strPath = strTemp + strPath;
			pParent = (CExBaseObject *)pParent->GetParent();
		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		//删除最右边的分隔符
		nLen = nLen - strSeperator.GetLength();
		strPath = strPath.Left(nLen);
	}

	if (nLen > 0)
	{
		//shaolei 2023-2-24
		//删除最左边的分隔符：若最左边的字符 = 分隔符，说明root节点的ID为空
		if (strPath.Find(strSeperator) == 0)
		{
			strPath = strPath.Mid(strSeperator.GetLength());
		}
	}

	return strPath;
}

//2022-9-17  lijunqing
CString CExBaseObject::GetIDPathEx(CExBaseObject *pRoot, BOOL bHasRoot, const CString &strSeperator)
{
	CString strPath;
	CExBaseObject *pParent = this;
	CString strTemp;

	if (bHasRoot)
	{
		while (pParent != NULL)
		{
			strTemp.Format(_T("%s%s"), pParent->m_strID.GetString(), strSeperator.GetString());
			strPath = strTemp + strPath;

			if (pParent == pRoot)
			{
				break;
			}

			pParent = (CExBaseObject *)pParent->GetParent();
		}
	}
	else
	{
		while (pParent != NULL)
		{
			if (pParent == pRoot)
			{
				break;
			}

			strTemp.Format(_T("%s%s"), pParent->m_strID.GetString(), strSeperator.GetString());
			strPath = strTemp + strPath;
			pParent = (CExBaseObject *)pParent->GetParent();
		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		//删除最右边的分隔符
		nLen = nLen - strSeperator.GetLength();
		strPath = strPath.Left(nLen);
	}

	if (nLen > 0)
	{
		//shaolei 2023-2-24
		//删除最左边的分隔符：若最左边的字符 = 分隔符，说明root节点的ID为空
		if (strPath.Find(strSeperator) == 0)
		{
			strPath = strPath.Mid(strSeperator.GetLength());
		}
	}

	return strPath;
}

//2023-9-1 shaolei
CString CExBaseObject::GetNamePathEx(CExBaseObject *pRoot, BOOL bHasRoot, const CString &strSeperator)
{
	CString strPath;
	CExBaseObject *pParent = this;
	CString strTemp;

	if (bHasRoot)
	{
		while (pParent != NULL)
		{
			strTemp.Format(_T("%s%s"), pParent->m_strName.GetString(), strSeperator.GetString());
			strPath = strTemp + strPath;

			if (pParent == pRoot)
			{
				break;
			}

			pParent = (CExBaseObject *)pParent->GetParent();
		}
	}
	else
	{
		while (pParent != NULL)
		{
			if (pParent == pRoot)
			{
				break;
			}

			strTemp.Format(_T("%s%s"), pParent->m_strName.GetString(), strSeperator.GetString());
			strPath = strTemp + strPath;
			pParent = (CExBaseObject *)pParent->GetParent();
		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		//删除最右边的分隔符
		nLen = nLen - strSeperator.GetLength();
		strPath = strPath.Left(nLen);
	}

	if (nLen > 0)
	{
		//shaolei 2023-2-24
		//删除最左边的分隔符：若最左边的字符 = 分隔符，说明root节点的ID为空
		if (strPath.Find(strSeperator) == 0)
		{
			strPath = strPath.Mid(strSeperator.GetLength());
		}
	}

	return strPath;
}

CString CExBaseObject::GetXLangID()
{
	CString strXLangID;
	GetXLangID(strXLangID);
	return strXLangID;
}

void CExBaseObject::GetXLangID(CString &strLangID)
{
    strLangID.Format(_T("#s%s"), m_strID.GetString());
}

#ifndef NO_XDbBaseLib

//////////////////////////////////////////////////////////////////////////
BSTR CExBaseObject::DB_GetTableName(CXmlRWKeys *pXmlRWKeys)				{	return GetXmlElementKey();				}
BSTR CExBaseObject::DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)				{	return DB_GetTableName(pXmlRWKeys);				}
BSTR CExBaseObject::DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)				{	return NULL;				}
BSTR CExBaseObject::DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)					{	return NULL;	}

CString CExBaseObject::DB_GetPrimaryKeyValue()	
{
	CXDb_PKeyValue oPKeyValue;
	CString strPkValue;

	Db_GetPkeyValue(oPKeyValue);
	oPKeyValue.GetValue(strPkValue);

	return strPkValue;
}

BSTR CExBaseObject::DB_GetForeignKey(CXmlRWKeys *pXmlRWKeys)
{
	if (m_pParent == NULL)
		return NULL;
	else
	{
		return ((CExBaseObject*)m_pParent)->DB_GetPrimaryKey(pXmlRWKeys);
	}		
}

CString CExBaseObject::DB_GetForeignKeyValue()
{
	if (m_pParent == NULL)
		return _T("");
	else
		return ((CExBaseObject*)m_pParent)->DB_GetPrimaryKeyValue();
}

BOOL CExBaseObject::DB_Select(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask) {return FALSE;}

CXDbRecordsetBase* CExBaseObject::DB_Select_Own(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	CString strPkey, strPkeyValue, strTable;

	strPkey = DB_GetPrimaryKey(pXmlRWKeys);
	strPkeyValue = DB_GetPrimaryKeyValue();
	strTable = DB_GetOwnTableName(pXmlRWKeys);
//	strTable = DB_GetTableName(pXmlRWKeys);
		
	return pXDbLib->SQLSelect(strTable, strPkey, strPkeyValue);
}

BOOL CExBaseObject::DB_SelectChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask)	{	return FALSE;	}


//读数据
long CExBaseObject::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	pRecordset->GetFieldValue(pXmlRWKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlRWKeys->m_strIDKey, m_strID);

	return 0;
}

//写数据
long CExBaseObject::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	pRecordset->SetFieldValue(pXmlRWKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlRWKeys->m_strIDKey, m_strID);
	
	return 0;
}

BOOL CExBaseObject::DB_Update(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	if (DB_GetPrimaryKey(pXmlRWKeys) == NULL)
	{
		return DB_Update_Children(pXDbLib, pXmlRWKeys);
	}

	CXDbRecordsetBase *pRecordset = DB_Select_Own(pXDbLib, pXmlRWKeys);

	if (pRecordset == NULL || pRecordset->IsEof())
	{
		if (pRecordset != NULL)
		{
			pRecordset->Free();
		}
		return FALSE;
	}

	DB_WriteFields(pRecordset, pXmlRWKeys);   //写字段值
	pRecordset->Update(DB_GetPrimaryKey(pXmlRWKeys));   //更新数据库
	pRecordset->Free();

	return TRUE;
}

BOOL CExBaseObject::DB_Update_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys) {	return FALSE;		}

BOOL CExBaseObject::DB_Update_Cmd(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	CString strTable, strPkey, strPkeyValue;
	strTable = DB_GetOwnTableName(pXmlRWKeys);

	CXDbRecordsetBase *pRecordset = pXDbLib->SQLNewRecordset(strTable, strPkey, strPkeyValue);

	if (pRecordset == NULL)
	{
		return FALSE;
	}

	DB_WriteFields(pRecordset, pXmlRWKeys);   //写字段值
	BOOL bRet = pRecordset->Update(DB_GetPrimaryKey(pXmlRWKeys));   //更新数据库
	pRecordset->Free();

	return bRet;
}

BOOL CExBaseObject::DB_Delete(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	if (DB_GetPrimaryKey(pXmlRWKeys) == NULL)
	{
		return DB_DeleteChildren(pXDbLib, pXmlRWKeys);
	}

	DB_Delete_Own(pXDbLib, pXmlRWKeys);

	return TRUE;
}

BOOL CExBaseObject::DB_Delete_Own(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)
{
	CString strTableName, strPkey, strPkeyValue;

	strTableName = DB_GetTableName(pXmlRWKeys);
	strPkey = DB_GetPrimaryKey(pXmlRWKeys);
	strPkeyValue = DB_GetPrimaryKeyValue();

	pXDbLib->SQLDelete(strTableName , strPkey , strPkeyValue );

	return TRUE;
}

BOOL CExBaseObject::DB_DeleteChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys)		{	return FALSE;		}

//把BaseObject中的字段组成sql语句写入数据库中,插入成功反回插入后的ID标号
BOOL CExBaseObject::DB_Insert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask) 
{
	DB_Insert_Own(pXDbLib, NULL, pXmlRWKeys, pXdbQueryMask);

	return DB_Insert_Children(pXDbLib, pXmlRWKeys, pXdbQueryMask);
}

BOOL CExBaseObject::DB_Insert_Own(CXDbBaseLib *pXDbLib,CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask) 
{
	if (DB_GetPrimaryKey(pXmlRWKeys) != NULL)
	{
		CXDbRecordsetBase *pRecordset_New = NULL;

		if (pRecordset == NULL)
		{
			CString strTable, strPkey, strPkeyValue;
			strTable = DB_GetTableName(pXmlRWKeys);
			pRecordset_New = pXDbLib->SQLNewRecordset(strTable, strPkey, strPkeyValue);

			if (pRecordset_New == NULL)
				return FALSE;
		}
		else
		{
			pRecordset_New = pRecordset;
		}

		pRecordset_New->AddNew();
		DB_WriteFields(pRecordset_New, pXmlRWKeys);
		pRecordset_New->Update(DB_GetPrimaryKey(pXmlRWKeys), TRUE);

		DB_UpdatePrimaryKeyValue(pRecordset_New);		//插入后更新主键值
		
		if (pRecordset == NULL)
		{
			pRecordset_New->Free();
		}

		CXDb_PKeyValue oPKeyValue(this, pXmlRWKeys);
		DB_SetForeignKeyValue_Children(pXmlRWKeys, oPKeyValue);
	}

	return TRUE;
}

BOOL CExBaseObject::DB_Insert_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask)		{	return FALSE;	}


BOOL CExBaseObject::DB_Insert_Cmd(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys) 
{
	CString strSQL;

	DB_GetSQL_Insert(pXDbLib, pXmlRWKeys, strSQL);
	
	return pXDbLib->ExecuteCmd(strSQL);
}


BOOL CExBaseObject::DB_GetSQL_Select_Own(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL)
{
	CString strPkey,strPkeyValue,strTable;

	strPkey = DB_GetPrimaryKey(pXmlRWKeys);
	strPkeyValue = DB_GetPrimaryKeyValue();
	strTable = DB_GetTableName(pXmlRWKeys);

	return pXDbLib->GetSQLSelect(strSQL, strTable, strPkey, strPkeyValue);
}

BOOL CExBaseObject::DB_GetSQL_Select_Childrenren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL)
{
	CString strPkey, strPkeyValue, strTable;

	strPkey = DB_GetForeignKey(pXmlRWKeys);
	strPkeyValue = DB_GetForeignKeyValue();
	strTable = DB_GetChildTableName(pXmlRWKeys);

	return pXDbLib->GetSQLSelect(strSQL, strTable, strPkey, strPkeyValue);
}

BOOL CExBaseObject::DB_GetSQL_Select_Childrenren_ForeignKey(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL)
{
	CString strPkey, strPkeyValue, strTable;
	
	if (DB_GetPrimaryKey(pXmlRWKeys) == NULL)
	{
		strPkey = DB_GetForeignKey(pXmlRWKeys);
		strPkeyValue = DB_GetForeignKeyValue();
	}
	else
	{
		strPkey = DB_GetPrimaryKey(pXmlRWKeys);
		strPkeyValue = DB_GetPrimaryKeyValue();
	}
	
	strTable = DB_GetChildTableName(pXmlRWKeys);

	return pXDbLib->GetSQLSelect(strSQL, strTable, strPkey, strPkeyValue);
}

BOOL CExBaseObject::DB_GetSQL_Insert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL)	{	return FALSE;		}

long CExBaseObject::DB_WriteFields_BlobBinary(CXDbRecordsetBase *pRecordset, BSTR bstrKey)
{
	//二进制串行化
	//将二进制数据写入数据库

	char* pbuffer = NULL;
	long lLen = 0;

#ifdef _DBLIB_USE_SHAREMEM_
	CShareMemSerialize *pBuffer = pRecordset->GetShareMemSerialize();
	SerializeWrite(*pBuffer);
	pBuffer->GetBuffer(&pbuffer, &lLen);
#else
	CBinarySerialBuffer oBuffer;
	SerializeWrite(oBuffer);
	oBuffer.GetBuffer(&pbuffer, &lLen);
#endif

	if (pbuffer)
	{
		pRecordset->SetFieldValue(bstrKey, &pbuffer, lLen);

#ifdef _DBLIB_USE_SHAREMEM_

#else
		oBuffer.DettachBuffer();
#endif
		
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("SetFieldValue BLOB字段出错"));
	}

	return 0;
}

long CExBaseObject::DB_WriteFields_BlobXML(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys, BSTR bstrKey)
{
	BSTR bstrXml = GetXml(pXmlRWKeys);

	pRecordset->SetFieldValue_Blob(bstrKey,bstrXml);

	return 0;
}

long CExBaseObject::DB_ReadFields_BlobBinary(CXDbRecordsetBase *pRecordset, BSTR bstrKey)
{
	//读blob字段（自身对象）,解析其中的data对象添加到链表中
	char *pblobData =NULL;
	long nLen = 0;
	pRecordset->GetFieldValue(bstrKey, &pblobData, nLen);

	CBinarySerialBuffer oBuffer;
	oBuffer.AttachBuffer(pblobData, nLen);
	oBuffer.SetReadMode();
//	oBuffer.RepalceChar((CHAR)0xFF, (CHAR)0x22, nLen);  //lijq  SQL语句：BLOB不能包含 " 
	
	try
	{
		SerializeRead(oBuffer);
	}
	catch(...)
	{
		CString strPath;
		strPath = _P_GetWorkspacePath();
		CString strFile;
		CString strPK = pRecordset->GetFieldName(0);
		long nPKVal;
		pRecordset->GetFieldValue(strPK,nPKVal);
        strFile.Format(_T("%s-%d.Errdat"),strPK.GetString(),nPKVal);
		strFile = strPath + strFile;
		oBuffer.SaveToFile(strFile);
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DB_ReadFields_BlobBinary Error:【Saved >> %s】"),strFile.GetString());
	}

	return 0;
}

long CExBaseObject::DB_ReadFields_BlobXML(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys, 
										BSTR bstrKey, CExBaseList *pTempList)
{
	//读blob字段（自身对象）,解析其中的data对象添加到链表中
	char *pBlobData =NULL;
	long nLen = 0;
	pRecordset->GetFieldValue(bstrKey, &pBlobData, nLen);

	CString strXml;
	strXml = pBlobData;
	BSTR bstrXml = strXml.AllocSysString();  

	if (pTempList != NULL)
	{
		if (IsBaseList())
		{
			pTempList->SetXml(bstrXml,pXmlRWKeys);
			CExBaseList *pThis = (CExBaseList*)this;
			pThis->AppendEx(*pTempList);
			pTempList->RemoveAll();
		}
		else
		{
			SetXml(bstrXml,pXmlRWKeys);
		}
	}
	else
	{
		SetXml(bstrXml,pXmlRWKeys);
	}

#ifdef _PSX_IDE_QT_
    delete bstrXml;
#else
    ::SysFreeString(bstrXml); // 用完释放
#endif

	return 0;
}

void CExBaseObject::DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset) {}


void CExBaseObject::Db_SetPkeyValue(CXDb_PKeyValue &oPKeyValue)
{
	CXDb_PKeyValue oPkValOwn;
	Db_GetPkeyValue(oPkValOwn);
	oPkValOwn.SetValue(oPKeyValue);
}

void CExBaseObject::Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)	{}


void CExBaseObject::Db_SetPkeyValue(CExBaseObject *pRefObj)
{
	CXDb_PKeyValue oPkVal;
	pRefObj->Db_GetPkeyValue(oPkVal);
	Db_SetPkeyValue(oPkVal);
}

BOOL CExBaseObject::DB_SetForeignKeyValue(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	DB_SetForeignKeyValue_Own(pXmlRWKeys, oPKeyValue);
	
	DB_SetForeignKeyValue_Children(pXmlRWKeys, oPKeyValue);
	
	return TRUE;
}

BOOL CExBaseObject::DB_SetForeignKeyValue_Children(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue) {	return TRUE; }
BOOL CExBaseObject::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue) {	return TRUE; }

BOOL CExBaseObject::DB_SelectEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString strFK, CString strFKVal) {return FALSE;}
BOOL CExBaseObject::DB_InsertEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue){return FALSE;}
BOOL CExBaseObject::DB_UpdateEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys){return FALSE;}

//没找到插入，返回FALSE,找到，更新对象，返回TRUE
BOOL CExBaseObject::DB_UpdateOrInsert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
									  ,BOOL bInsert, CString strSQL,BOOL bUpdateSelf)
{
	CXDbRecordsetBase *pRecordset = NULL;
	if (strSQL.IsEmpty())
	{
		pRecordset = DB_Select_Own(pXDbLib, pXmlRWKeys);
	}
	else
	{
		pRecordset = pXDbLib->ExecuteQuery(strSQL);
	}	
	if (pRecordset == NULL || pRecordset->IsEof())
	{
		if (pRecordset != NULL)
		{
			pRecordset->Free();
		}
		
		if(bInsert == TRUE)
		{
			DB_Insert_Own(pXDbLib,NULL,pXmlRWKeys,NULL);
		}		
		return FALSE;
	}
	else
	{
		if(bUpdateSelf == TRUE)
		{
			DB_ReadFields(pRecordset, pXmlRWKeys);
		}	
		pRecordset->Free();
		return TRUE;
	}	
}

//根据条件查询并更新自身对象
BOOL CExBaseObject::DB_Select_OwnEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
									,CString strQuerySql)
{
	CXDbRecordsetBase *pRecordset = NULL;
	if (strQuerySql.IsEmpty())
	{
		pRecordset = DB_Select_Own(pXDbLib, pXmlRWKeys);
	}
	else
	{
		pRecordset = pXDbLib->ExecuteQuery(strQuerySql);
	}	
	if (pRecordset == NULL || pRecordset->IsEof())
	{
		if (pRecordset != NULL)
		{
			pRecordset->Free();
		}
		return FALSE;
	}

	DB_ReadFields(pRecordset, pXmlRWKeys);
	pRecordset->Free();

	return TRUE;
}

//没找到插入数据库，找到更新数据库，返回操作结果
BOOL CExBaseObject::DB_Insert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString strQuerySql)
{
	CXDbRecordsetBase *pRecordset = NULL;
	
	if (strQuerySql.IsEmpty())
	{
		pRecordset = DB_Select_Own(pXDbLib, pXmlRWKeys);
	}
	else
	{
		pRecordset = pXDbLib->ExecuteQuery(strQuerySql);
	}	
	
	if (pRecordset == NULL || pRecordset->IsEof())
	{
		if (pRecordset != NULL)
		{
			pRecordset->Free();
		}
		
		return DB_Insert_Own(pXDbLib,NULL,pXmlRWKeys,NULL);
	}
	else
	{//李俊庆  2019-4-14
		BSTR bstrPKKey;
		CString strPkVal;
		CXDb_PKeyValue oPKeyValue;
		BOOL bRet;

		bstrPKKey = DB_GetPrimaryKey(pXmlRWKeys);
		pRecordset->GetFieldValue(bstrPKKey, strPkVal);
		Db_GetPkeyValue(oPKeyValue);
		oPKeyValue.SetValue(strPkVal);

		if (!strQuerySql.IsEmpty())
		{
			pRecordset->m_strTableName = DB_GetOwnTableName(pXmlRWKeys);
		}	
		DB_WriteFields(pRecordset, pXmlRWKeys);   //写字段值
		bRet = pRecordset->Update(bstrPKKey);   //更新数据库
		pRecordset->Free();

		return bRet;

// 		BSTR bstrPKKey = DB_GetPrimaryKey(pXmlRWKeys);
// 		CString strPkVal;
// 		pRecordset->GetFieldValue(bstrPKKey, strPkVal);
// 		pRecordset->Free();
// 		
// 		CXDb_PKeyValue oPKeyValue;
// 		Db_GetPkeyValue(oPKeyValue);
// 
// 		oPKeyValue.SetValue(strPkVal);
// 		return DB_Update(pXDbLib,pXmlRWKeys);	
	}
}

BOOL CExBaseObject::DB_SelectSqlEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSql) {return FALSE;}

void CExBaseObject::DB_InitNameAttrs()
{
//	ASSERT (FALSE);
}
#endif

void CExBaseObject::CalObjSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile)
{
	nObjCount++;
	long nSizeOwn = sizeof(*this);
	long nSizeChildren = 0;

	if (bCalChild)
	{
		CalChildrenSize(bCalChild, nObjCount, nSizeChildren, pFile);
	}

	if (pFile != NULL)
	{
		CString strMsg;
        strMsg.Format(_T("[%s]:[%s] sz-own=%d  sz-children=%d\r\n"), m_strName.GetString(), m_strID.GetString(), nSizeOwn, nSizeChildren);
        pFile->Write(strMsg.GetString(), strMsg.GetLength());
	}

	nTotalSize = nTotalSize + nSizeOwn + nSizeChildren;
}

void CExBaseObject::CalChildrenSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile)	{		}
