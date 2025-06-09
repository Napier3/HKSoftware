//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchObject.cpp  CXMatchObject


#include "stdafx.h"
#include "XMatchObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

long CXMatchObject::g_bNumberKeyMatchRatioAdd = 0;

CXMatchObject::CXMatchObject()
{
	//初始化属性

	//初始化成员变量
	m_pRefObject = NULL;	//待匹配的数据对象引用
// 	m_listMatchXKeys.m_strName = _T("MatchXKeys");
// 	m_listMatchXKeys.m_strID = _T("MatchXKeys");
	m_listMacthRefObject.m_strName = _T("Macths");
	m_listMacthRefObject.m_strID = _T("Macths");
	m_bFullMatchString = FALSE;
}

CXMatchObject::CXMatchObject(CExBaseObject *pRefObj, CXKeyDB *pKeyDb)
{
// 	m_listMatchXKeys.m_strName = _T("MatchXKeys");
// 	m_listMatchXKeys.m_strID = _T("MatchXKeys");
	m_listMacthRefObject.m_strName = _T("Macths");
	m_listMacthRefObject.m_strID = _T("Macths");
	m_listMacthObjectRatio.m_strName = _T("MacthRatio");
	m_listMacthObjectRatio.m_strID = _T("MacthRatio");
	Init(pRefObj, pKeyDb);
	m_bFullMatchString = FALSE;
}

CXMatchObject::~CXMatchObject()
{
	m_listMatchXKeys.DeleteAll();
	m_listMacthRefObject.RemoveAll();
	m_listMacthObjectRatio.DeleteAll();
}

void CXMatchObject::FreeMatch()
{
	m_listMacthRefObject.RemoveAll();
	m_listMacthObjectRatio.DeleteAll();
	m_bFullMatchString = FALSE;
}

//2022-5-9 lijunqing 开放的接口
BOOL CXMatchObject::XMatch(CXKeyMatchRefList *pSrcXKeys, CXKeyMatchRefList *pDstXKeys, long &nMatchRatio)
{
	return Match(pSrcXKeys, pDstXKeys, nMatchRatio);
}

void CXMatchObject::XAddXMatchRatioObject(long nRatio, CExBaseObject *pRefObj)
{
	AddXMatchRatioObject(nRatio, pRefObj);
}


BOOL CXMatchObject::Match(CXKeyMatchRefList *pSrcXKeys, CXKeyMatchRefList *pDstXKeys, long &nMatchRatio)
{
	ASSERT (pSrcXKeys != NULL && pDstXKeys != NULL);

	long nCountSrc = pSrcXKeys->GetCount();
	long nCountDst = pDstXKeys->GetCount();

	if ((nCountSrc == 0) || (nCountDst == 0))
	{
		nMatchRatio = 0;
		return FALSE;
	}

	BOOL bTrue1 = TRUE;
	BOOL bTrue2 = TRUE;
	BOOL bTrue = TRUE;

	//bTrue = IsSubKeys(pSrcXKeys, pDstXKeys, nMatchRatio);
	//if (nCountSrc == nCountDst)
	//{
	//	bTrue = IsSubKeys(pSrcXKeys, pDstXKeys, nMatchRatio);
	//}
	//else
	{
		long nMatch1 = 0;
		long nMatch2 = 0;

		bTrue1 = IsSubKeys(pDstXKeys, pSrcXKeys, nMatch1);

		if (nMatch1 == 0)
		{
			nMatchRatio = 0;
			return FALSE;
		}

		bTrue2 = IsSubKeys(pSrcXKeys, pDstXKeys, nMatch2);
		
		if (nMatch2 == 0)
		{
			nMatchRatio = 0;
			return FALSE;
		}
		
		nMatchRatio = nMatch2 + nMatch1;
		nMatchRatio /= 2;

		bTrue = bTrue1 || bTrue2;
// 		if (nCountSrc > nCountDst)
// 		{
// 			bTrue = IsSubKeys(pDstXKeys, pSrcXKeys, nMatchRatio);
// 		}
// 		else
// 		{
// 			bTrue = IsSubKeys(pSrcXKeys, pDstXKeys, nMatchRatio);
// 		}
	}

	return bTrue;
}
// 
// BOOL CXMatchObject::Match(CExBaseList *pSrcXKeys, CExBaseList *pDstXKeys, long &nMatchRatio)
// {
// 	ASSERT (pSrcXKeys != NULL && pDstXKeys != NULL);
// 
// 	long nCountSrc = pSrcXKeys->GetCount();
// 	long nCountDst = pDstXKeys->GetCount();
// 
// 	if ((nCountSrc == 0) || (nCountDst == 0))
// 	{
// 		nMatchRatio = 0;
// 		return FALSE;
// 	}
// 
// 	BOOL bTrue = TRUE;
// 
// 	//bTrue = IsSubKeys(pSrcXKeys, pDstXKeys, nMatchRatio);
// 	if (nCountSrc == nCountDst)
// 	{
// 		bTrue = IsSubKeys(pSrcXKeys, pDstXKeys, nMatchRatio);
// 	}
// 	else
// 	{
// 		long nMatch1 = 0;
// 		long nMatch2 = 0;
// 
// 		bTrue = IsSubKeys(pDstXKeys, pSrcXKeys, nMatch1);
// 
// 		if (nMatch1 == 0)
// 		{
// 			nMatchRatio = 0;
// 			return FALSE;
// 		}
// 
// 		bTrue = IsSubKeys(pSrcXKeys, pDstXKeys, nMatch2);
// 		
// 		if (nMatch2 == 0)
// 		{
// 			nMatchRatio = 0;
// 			return FALSE;
// 		}
// 		
// 		nMatchRatio = nMatch2 + nMatch1;
// 
// // 		if (nCountSrc > nCountDst)
// // 		{
// // 			bTrue = IsSubKeys(pDstXKeys, pSrcXKeys, nMatchRatio);
// // 		}
// // 		else
// // 		{
// // 			bTrue = IsSubKeys(pSrcXKeys, pDstXKeys, nMatchRatio);
// // 		}
// 	}
// 
// 	return bTrue;
// }

BOOL CXMatchObject::IsSubKey(CXKeyMatchRefList *pXKeys, CXKeyMatchRef *pXKey, long &nImportance)
{
	ASSERT (pXKey != NULL);
	nImportance = pXKey->GetImportance();

	return pXKeys->Match(pXKey);
}
// 
// BOOL CXMatchObject::IsSubKey(CExBaseList *pXKeys, CExBaseObject *pXKey, long &nImportance)
// {
// 	UINT nClassID = pXKey->GetClassID();
// 
// 	if (nClassID == KDBCLASSID_CXKEYBASE)
// 	{
// 		nImportance = ((CXKeyBase*)pXKey)->m_nImportance;
// 	}
// 	else if (nClassID == KDBCLASSID_CXKEYGROUPBASE)
// 	{
// 		nImportance = ((CXKeyGroupBase*)pXKey)->m_nImportance;
// 	}
// 	else if (nClassID == KDBCLASSID_CXMULTIKEYBASE)
// 	{
// 		nImportance = ((CXMultiKeyBase*)pXKey)->m_nImportance;
// 	}
// 
// 	return pXKeys->Find(pXKey) != NULL;
// }

BOOL CXMatchObject::IsSubKeys(CXKeyMatchRefList *pSrcXKeys, CXKeyMatchRefList *pDstXKeys, long &nMatchRatio)
{
	ASSERT (pSrcXKeys != NULL && pDstXKeys != NULL);

	BOOL bTrue = TRUE;
	POS pos = pSrcXKeys->GetHeadPosition();
	CXKeyMatchRef *p = NULL;
	long nMatchCount = 0;
	long nSrcCount = pSrcXKeys->GetCount();
	long nClassID = 0;
	long nImportance = 0;
	BOOL bIsSubKey = FALSE;
	long nTotal = 0;

	while (pos != NULL)
	{
		p = pSrcXKeys->GetNext(pos);

		bIsSubKey = IsSubKey(pDstXKeys, p, nImportance);
		//nTotal += nImportance * bIsSubKey;
		
		if (bIsSubKey)
		{
			nMatchCount++;

			if (p->IsNumber())
			{
				nMatchCount += g_bNumberKeyMatchRatioAdd;
			}
		}
// 		if ((nImportance > 90) && (!bIsSubKey))
// 		{
// 			nMatchCount = 0;
// 			break;
// 		}
// 		else if (bIsSubKey)
// 		{
// 			nMatchCount++;
// 		}
	}

	long nTemp = nMatchCount * 200;
	nTemp = nTemp / (pSrcXKeys->GetCount() + pDstXKeys->GetCount());
	bTrue = (nSrcCount == nMatchCount);
	nMatchRatio += nTemp;

	return bTrue;
}
// 
// BOOL CXMatchObject::IsSubKeys(CExBaseList *pSrcXKeys, CExBaseList *pDstXKeys, long &nMatchRatio)
// {
// 	ASSERT (pSrcXKeys != NULL && pDstXKeys != NULL);
// 
// 	BOOL bTrue = TRUE;
// 	POS pos = pSrcXKeys->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 	long nMatchCount = 0;
// 	long nSrcCount = pSrcXKeys->GetCount();
// 	long nClassID = 0;
// 	long nImportance = 0;
// 	BOOL bIsSubKey = FALSE;
// 
// 	while (pos != NULL)
// 	{
// 		p = pSrcXKeys->GetNext(pos);
// 		bIsSubKey = IsSubKey(pDstXKeys, p, nImportance);
// 
// 		if ((nImportance > 90) && (!bIsSubKey))
// 		{
// 			nMatchCount = 0;
// 			break;
// 		}
// 		else if (bIsSubKey)
// 		{
// 			nMatchCount++;
// 		}
// 	}
// 
// 	long nTemp = nMatchCount * 200;
// 	nTemp = nTemp / (pSrcXKeys->GetCount() + pDstXKeys->GetCount());
// 	bTrue = (nSrcCount == nMatchCount);
// 	nMatchRatio += nTemp;
// 
// 	return bTrue;
// }

void CXMatchObject::Match(CExBaseList *pMachList, BOOL bFreeMatchList, BOOL bUseFullMatchString)
{
	if (bFreeMatchList)
	{
		m_listMacthRefObject.RemoveAll();
	}

	POS pos = pMachList->GetHeadPosition();
	CXMatchObject *p = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject *)pMachList->GetNext(pos);
		Match(p, bUseFullMatchString);
	}
}

void CXMatchObject::Match(CXMatchObject *pMatchObj, BOOL bUseFullMatchString)
{
	if (m_bFullMatchString || pMatchObj->m_bFullMatchString)
	{
		return;
	}

	ASSERT (pMatchObj != NULL);
	ASSERT (pMatchObj->m_pRefObject != NULL);

	if (pMatchObj == NULL)
	{
		return;
	}

	if (pMatchObj->m_pRefObject == NULL)
	{
		return;
	}

	if (bUseFullMatchString)
	{
		if (pMatchObj->m_pRefObject->m_strName == m_pRefObject->m_strName
			|| pMatchObj->m_pRefObject->m_strID == m_pRefObject->m_strID)
		{
			CString strID1, strID2;
			strID1 = m_pRefObject->m_strID;
			strID1.MakeLower();
			strID2 = pMatchObj->m_pRefObject->m_strID;
			strID2.MakeLower();

			//跳闸矩阵：OUTMATR;
			//控制字：Enable
			//跳过跳闸矩阵和控制字：一边是跳闸矩阵或控制字，一边是定值。有可能存在名称全匹配，不应建立映射关系  shaolei 20220512
			if (strID1.Find(_T("outmatr")) < 0 && strID2.Find(_T("outmatr")) >= 0)
			{
				return;
			}

			if (strID1.Find(_T("enable")) < 0 && strID2.Find(_T("enable")) >= 0)
			{
				return;
			}

			pMatchObj->m_bFullMatchString = TRUE;
			m_bFullMatchString = TRUE;
			m_listMacthRefObject.RemoveAll();
			m_listMacthRefObject.AddTail(pMatchObj->m_pRefObject);
			AddXMatchRatioObject(100, pMatchObj->m_pRefObject);
			return;
		}
	}

	long nMatchRatio = 0;
	BOOL bMatch = Match(&m_listMatchXKeys, &pMatchObj->m_listMatchXKeys, nMatchRatio);

	if (bMatch && nMatchRatio == 100)
	{
		//m_pRefObject = pMatchObj->m_pRefObject;
		m_listMacthRefObject.AddTail(pMatchObj->m_pRefObject);
	}

	if (0 < nMatchRatio && nMatchRatio < 100)
	{
		AddXMatchRatioObject(nMatchRatio, pMatchObj->m_pRefObject);
	}

	if (bUseFullMatchString)
	{
		if (m_pRefObject->m_strName.Find(pMatchObj->m_pRefObject->m_strName) >= 0)
		{
			if (m_listMacthRefObject.FindByName(pMatchObj->m_pRefObject->m_strName) == NULL)
			{
				m_listMacthRefObject.AddTail(pMatchObj->m_pRefObject);
			}
		}

		if (pMatchObj->m_pRefObject->m_strName.Find(m_pRefObject->m_strName) >= 0)
		{
			if (m_listMacthRefObject.FindByName(pMatchObj->m_pRefObject->m_strName) == NULL)
			{
				m_listMacthRefObject.AddTail(pMatchObj->m_pRefObject);
			}
		}
	}

}

void CXMatchObject::Init(CExBaseObject *pRefObj, CXKeyDB *pKeyDb)
{
	ASSERT(pRefObj != NULL);
	ASSERT(pKeyDb != NULL);

	m_pRefObject = pRefObj;
	pKeyDb->QueryKeys(pRefObj->m_strName, &m_listMatchXKeys);
}

//树形控件相关的操作
void CXMatchObject::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	m_pRefObject->InsertOwnTreeCtrl(pTreeCtrl, htiParent, dwParam);
	m_listMatchXKeys.InsertTreeCtrl(pTreeCtrl, (HTREEITEM)m_pRefObject->m_dwItemData, dwParam);
	m_listMacthRefObject.InsertTreeCtrl(pTreeCtrl, (HTREEITEM)m_pRefObject->m_dwItemData, dwParam);
	m_listMacthObjectRatio.InsertTreeCtrl(pTreeCtrl, (HTREEITEM)m_pRefObject->m_dwItemData, dwParam);
}

CExBaseObject* CXMatchObject::GetMatchRef()
{
	//ASSERT (m_listMacthRefObject.GetCount() == 1);
	return (CExBaseObject*)m_listMacthRefObject.GetHead();
}

BOOL CXMatchObject::HasRefObj(CExBaseObject *pRefObj)
{
	return (m_listMacthRefObject.Find(pRefObj) != NULL);
}

void CXMatchObject::FilterMatch(CExBaseObject *pRefObj)
{
	if (m_bFullMatchString)
	{
		return;
	}

	POS pos = m_listMacthRefObject.Find(pRefObj);

	if (pos != NULL)
	{
		m_listMacthRefObject.RemoveAt(pos);
	}
}

void CXMatchObject::FilterMatch(CXMatchObject *pMatchObj)
{
	if (m_bFullMatchString)
	{
		return;
	}

	//如果被匹配的对象已经被完全匹配，则要过滤掉此对象
	if (pMatchObj->m_bFullMatchString )
	{
		POS pos = m_listMacthRefObject.Find(pMatchObj->m_pRefObject);

		if (pos != NULL)
		{
			m_listMacthRefObject.RemoveAt(pos);
		}
	}

	POS pos = pMatchObj->m_listMacthRefObject.GetHeadPosition();
	CExBaseObject *pRefObj = NULL;

	while (pos != NULL)
	{
		pRefObj = (CExBaseObject *)pMatchObj->m_listMacthRefObject.GetNext(pos);
		FilterMatch(pRefObj);
	}
}

void CXMatchObject::FilterMatchRatio(long nRatioMin)
{
	if (m_bFullMatchString)
	{//如果是全字符匹配，则不处理
		return;
	}

	POS pos = m_listMacthObjectRatio.GetHeadPosition();
	CXMatchObjectRatio *p = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObjectRatio *)m_listMacthObjectRatio.GetNext(pos);
		
		//for debug
// 		if (m_pRefObject->m_strName == _T("接地变零序过流Ⅱ段"))
// 		{
// 			int x = 0;
// 		}
// 
// 		if (p->m_pRefObject->m_strName == _T("零序过流Ⅱ段"))
// 		{
// 			int x = 0;
// 		}

		if (p->m_nMatchRatio > nRatioMin)
		{
			if (m_listMacthRefObject.Find(p->m_pRefObject) == NULL)
			{
				m_listMacthRefObject.AddTail(p->m_pRefObject);
			}
		}
	}
}

void CXMatchObject::FilterSortByRatio()
{
	if (m_bFullMatchString)
	{
		return;
	}

	POS pos = m_listMacthObjectRatio.GetHeadPosition();
	CXMatchObjectRatio *p = NULL;
	CXMatchObjectRatio *pSort = NULL;
	CExBaseList oListTemp;

	while (pos != NULL)
	{
		p = (CXMatchObjectRatio *)m_listMacthObjectRatio.GetNext(pos);
		POS posSort = oListTemp.GetHeadPosition();
		BOOL bSort = FALSE;

		if (posSort == NULL)
		{
			oListTemp.AddHead(p);
			continue;
		}

		while (posSort != NULL)
		{
			pSort = (CXMatchObjectRatio *)oListTemp.GetAt(posSort);

			if (p->m_nMatchRatio >= pSort->m_nMatchRatio)
			{
				oListTemp.InsertBefore(posSort, p);
				bSort = TRUE;
				break;
			}

			oListTemp.GetNext(posSort);
		}

		if (!bSort)
		{
			oListTemp.AddTail(p);
		}
	}

	m_listMacthObjectRatio.RemoveAll();
	m_listMacthObjectRatio.Append(oListTemp);
	oListTemp.RemoveAll();
}

void CXMatchObject::GetXMatchsString(CString &strText, BOOL bGetID, long nMaxCount)
{
	strText.Empty();

	long nCount = m_listMacthRefObject.GetCount();
	CExBaseObject *pRefObj = NULL;

	if (nCount == 0)
	{
		
	}
	else if (nCount == 1)
	{
		pRefObj = GetMatchRef();

		if (bGetID)
		{
            strText.Format(_T("%s[%s]"), pRefObj->m_strName.GetString(), pRefObj->m_strID.GetString());
		}
		else
		{
			strText = pRefObj->m_strName;
		}
	}
	else
	{
		if (nMaxCount <= 0)
		{
			nMaxCount = m_listMacthRefObject.GetCount();
		}

		POS pos = m_listMacthRefObject.GetHeadPosition();
		long nIndex = 0;

		while (pos != NULL)
		{
			pRefObj = m_listMacthRefObject.GetNext(pos);

			if (nIndex >= nMaxCount)
			{
				strText += _T("{...}");
				break;
			}

			if (bGetID)
			{
                strText.AppendFormat(_T("{%s[%s]}"), pRefObj->m_strName.GetString(), pRefObj->m_strID.GetString());
			}
			else
			{
                strText.AppendFormat(_T("{%s}"), pRefObj->m_strName.GetString());
			}

			nIndex++;
		}
	}
}

void CXMatchObject::SelFirstMatch()
{
	long nCount = m_listMacthRefObject.GetCount();

	if (nCount == 1)
	{
		return;
	}

	if (nCount == 0)
	{
		if (m_listMacthObjectRatio.GetCount() > 0)
		{
			m_listMacthRefObject.AddTail(m_listMacthObjectRatio.GetHead());
		}

		return;
	}

	CExBaseObject *pHead = m_listMacthRefObject.GetHead();
	m_listMacthRefObject.RemoveAll();
	m_listMacthRefObject.AddTail(pHead);
}

BOOL CXMatchObject::ValidateMatch()
{
	long nCount = m_listMacthRefObject.GetCount();

	return (nCount == 1);
}
