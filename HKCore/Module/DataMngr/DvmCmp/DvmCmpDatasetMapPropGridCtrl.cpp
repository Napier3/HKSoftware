#include "StdAfx.h"
#include "DvmCmpDatasetMapPropGridCtrl.h"
#include "..\..\XLanguage\XLanguageResource.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsMapPropGridProperty
IMPLEMENT_DYNAMIC(CDvmCmpDsPropGridProperty, CDvmCmpPropGridProperty)

CDvmCmpDsPropGridProperty::CDvmCmpDsPropGridProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
: CDvmCmpPropGridProperty(strGroupName, dwData, bIsValueList)
{

}

CDvmCmpDsPropGridProperty::CDvmCmpDsPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
												 LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
	: CDvmCmpPropGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{

}



void CDvmCmpDsPropGridProperty::OnDrawName(CDC* pDC, CRect rect)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pWndList);

	COLORREF clrTextOld = (COLORREF)-1;

	if (IsSelected() &&(!m_pWndList->IsVSDotNetLook() || !IsGroup() ||  m_bIsValueList))
	{
		CRect rectFill = rect;
		rectFill.top++;

		clrTextOld = pDC->SetTextColor(afxGlobalData.clrTextHilite);
		pDC->FillRect(rectFill, &afxGlobalData.brHilite);
	}

	if (m_pWndList->IsVSDotNetLook() && IsGroup())
	{
		clrTextOld = pDC->SetTextColor(RGB(0,0,0));
	}

	rect.DeflateRect(AFX_TEXT_MARGIN, 0);

	int nTextHeight = pDC->DrawText(m_strName, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

	m_bNameIsTruncated = pDC->GetTextExtent(m_strName).cx > rect.Width();

	if (IsSelected() && m_pWndList->IsVSDotNetLook() && IsGroup())
	{
		CRect rectFocus = rect;
		rectFocus.top = rectFocus.CenterPoint().y - nTextHeight / 2;
		rectFocus.bottom = rectFocus.top + nTextHeight;
		rectFocus.right = min(rect.right, rectFocus.left + pDC->GetTextExtent(m_strName).cx);
		rectFocus.InflateRect(2, 0);

		COLORREF clrShadow = afxGlobalData.clrBtnShadow;

		pDC->Draw3dRect(rectFocus, clrShadow, clrShadow);
	}

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor(clrTextOld);
	}
}
// 
// void CDvmCmpPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
// {
// 	//rect.right -= UNIT_GAP;
// 	CMFCPropertyGridProperty::OnDrawValue(pDC, rect);
// 	// 
// 	// 	ASSERT_VALID(this);
// 	// 	ASSERT_VALID(pDC);
// 	// 	ASSERT_VALID(m_pWndList);
// 	// 
// 	// 	if ((IsGroup() && !m_bIsValueList) || !HasValueField())
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	CShortData *pData = (CShortData*)m_dwData;
// 	// 
// 	// 	if (pData == NULL)
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	if (pData->GetClassID() != DTMCLASSID_CSHORTDATA)
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	if (pData->m_strUnit.GetLength() == 0)
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	if (pData->m_strUnit == _T("无"))
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	rect.DeflateRect(AFX_TEXT_MARGIN, 0);
// 	// 	rect.left = rect.right;
// 	// 	rect.right = rect.left + UNIT_GAP;
// 	// 	pDC->DrawText(pData->m_strUnit, rect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
// 
// }

void CDvmCmpDsPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
{
	CDvmCmpPropGridProperty::OnDrawValue(pDC, rect);
}

//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsPropGridCtrl
CDvmCmpDsPropGridCtrl::CDvmCmpDsPropGridCtrl()
{
	m_pDvmDeviceMap = NULL;
	m_pDatasetMap = NULL;
	m_pDataset    = NULL;
	m_bIngnoreSetCurrSel = FALSE;
}

CDvmCmpDsPropGridCtrl::~CDvmCmpDsPropGridCtrl()
{
	m_listDvmDsMapStand.RemoveAll();
}

void CDvmCmpDsPropGridCtrl::ShowDatasetMap(CDvmDatasetMap *pDvmDataset)
{
	CDvmDeviceMap *pDeviceMap = (CDvmDeviceMap*)pDvmDataset->GetAncestor(DMPCLASSID_CDVMDEVICEMAP);
	ShowDatasetMap(pDeviceMap, pDvmDataset);
}

void CDvmCmpDsPropGridCtrl::ShowDatasetMap(CDvmDeviceMap *pDeviceMap, CDvmDatasetMap *pDvmDataset)
{
	m_pDvmDeviceMap = pDeviceMap;
	m_pDatasetMap = pDvmDataset;
	InitDvmDsMapStand();
	ShowDatasets();
}

CDvmMapObject* CDvmCmpDsPropGridCtrl::GetSelMapObject()
{
	CExBaseObject *pSelObj = GetSelectData();
	CDvmMapObject *pMap = NULL;

	if (pSelObj == NULL)
	{
		return NULL;
	}

	if (pSelObj->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		pMap = (CDvmMapObject*)((CDvmData*)pSelObj)->m_pDvmMapObj;
	}
	else if  (pSelObj->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		pMap = (CDvmMapObject*)((CDvmValue*)pSelObj)->m_pDvmMapObj;
	}
	else
	{
	}

	return pMap;
}

CDvmDataset* CDvmCmpDsPropGridCtrl::GetDvmDatasetStand()
{
	long nCount = m_listDvmDsMapStand.GetCount();
	ASSERT( nCount > 0);

	if (nCount == 0)
	{
		return NULL;
	}

	long nIndex = 1;
	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)m_listDvmDsMapStand.GetHead();
	CDvmDataset *pDataset = (CDvmDataset*)pDatasetMap->m_pStand;
	
	return pDataset;
}

void CDvmCmpDsPropGridCtrl::InitDvmDsMapStand()
{
	m_pDvmDeviceMap->FindDvmMapObj_ByStand(DMPCLASSID_CDVMDATASETMAP, m_pDatasetMap->m_pStand, m_listDvmDsMapStand);
	ASSERT(m_listDvmDsMapStand.GetCount() > 0);
}

CDvmCmpDsPropGridProperty* CDvmCmpDsPropGridCtrl::NewDvmDataProp(CDvmData *pDvmData, long nIndex)
{
	return NULL;
}

void CDvmCmpDsPropGridCtrl::NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsPropGridProperty *pParent)
{
	
}

//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsStandPropGridProperty
IMPLEMENT_DYNAMIC(CDvmCmpDsStandPropGridProperty, CDvmCmpDsPropGridProperty)

CDvmCmpDsStandPropGridProperty::CDvmCmpDsStandPropGridProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
: CDvmCmpDsPropGridProperty(strGroupName, dwData, bIsValueList)
{

}

CDvmCmpDsStandPropGridProperty::CDvmCmpDsStandPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
													 LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
 : CDvmCmpDsPropGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{

}



void CDvmCmpDsStandPropGridProperty::OnDrawName(CDC* pDC, CRect rect)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pWndList);

	COLORREF clrTextOld = (COLORREF)-1;

	if (IsSelected() /*&&(!m_pWndList->IsVSDotNetLook() || !IsGroup() ||  m_bIsValueList)*/)
	{
		CRect rectFill = rect;
		rectFill.top++;

		clrTextOld = pDC->SetTextColor(afxGlobalData.clrTextHilite);
		pDC->FillRect(rectFill, &afxGlobalData.brHilite);
	}

// 	if (m_pWndList->IsVSDotNetLook() && IsGroup())
// 	{
// 		clrTextOld = pDC->SetTextColor(RGB(0,0,0));
// 	}

	CExBaseObject *pData = (CExBaseObject*)m_dwData;

	ASSERT (pData != NULL);
	rect.DeflateRect(AFX_TEXT_MARGIN, 0);
	CString *pStringName = NULL;

	if (pData->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		CDvmMapObject *pDataMap = (CDvmMapObject*)((CDvmData*)pData)->m_pDvmMapObj;

		if (pDataMap == NULL)
		{
			pStringName = &pData->m_strName;
			pDC->DrawText(pData->m_strName, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
		}
		else
		{
			pDataMap->StringCmp();
			CStringCmpBlocks *pStrCmpBlocks = pDataMap->GetNameCmp_Stand();

			if (pStrCmpBlocks != NULL)
			{
				pStrCmpBlocks->Draw(pDC, rect);
			}
			else
			{
				pDC->DrawText(pDataMap->m_pStand->m_strName, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
			}

			pStringName = &pDataMap->m_pStand->m_strName;
		}

	}
	else
	{
		CDvmMapObject *pDataMap = (CDvmMapObject*)((CDvmValue*)pData)->m_pDvmMapObj;

		if (pDataMap != NULL)
		{
			pDataMap->StringCmp();
			CStringCmpBlocks *pStrCmpBlocks = pDataMap->GetIDCmp_Stand();

			if (pStrCmpBlocks != NULL)
			{
				pStrCmpBlocks->Draw(pDC, rect);
			}
			else
			{
				pDC->DrawText(pDataMap->m_pStand->m_strID, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
			}
			
			//int nTextHeight = pDC->DrawText(m_strName, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
			pStringName = &pDataMap->m_pStand->m_strID;

		}
		else
		{
			pStringName = &pData->m_strID;
			pDC->DrawText(pData->m_strID, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
		}
	}

	m_bNameIsTruncated = pDC->GetTextExtent(*pStringName).cx > rect.Width();

// 	if (IsSelected() && m_pWndList->IsVSDotNetLook() && IsGroup())
// 	{
// 		CRect rectFocus = rect;
// 		rectFocus.top = rectFocus.CenterPoint().y - nTextHeight / 2;
// 		rectFocus.bottom = rectFocus.top + nTextHeight;
// 		rectFocus.right = min(rect.right, rectFocus.left + pDC->GetTextExtent(m_strName).cx);
// 		rectFocus.InflateRect(2, 0);
// 
// 		COLORREF clrShadow = afxGlobalData.clrBtnShadow;
// 
// 		pDC->Draw3dRect(rectFocus, clrShadow, clrShadow);
// 	}

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor(clrTextOld);
	}
}
// 
// void CDvmCmpDsStandPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
// {
// 	//rect.right -= UNIT_GAP;
// 	CMFCPropertyGridProperty::OnDrawValue(pDC, rect);
// 	// 
// 	// 	ASSERT_VALID(this);
// 	// 	ASSERT_VALID(pDC);
// 	// 	ASSERT_VALID(m_pWndList);
// 	// 
// 	// 	if ((IsGroup() && !m_bIsValueList) || !HasValueField())
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	CShortData *pData = (CShortData*)m_dwData;
// 	// 
// 	// 	if (pData == NULL)
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	if (pData->GetClassID() != DTMCLASSID_CSHORTDATA)
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	if (pData->m_strUnit.GetLength() == 0)
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	if (pData->m_strUnit == _T("无"))
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	rect.DeflateRect(AFX_TEXT_MARGIN, 0);
// 	// 	rect.left = rect.right;
// 	// 	rect.right = rect.left + UNIT_GAP;
// 	// 	pDC->DrawText(pData->m_strUnit, rect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
// 
// }

void CDvmCmpDsStandPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pWndList);

	CExBaseObject *pData = (CExBaseObject*)m_dwData;

	if (pData == NULL)
	{
		return;
	}

	CDvmMapObject *pDataMap = NULL;

	if (pData->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		pDataMap = (CDvmMapObject*)((CDvmData*)pData)->m_pDvmMapObj;
	}
	else
	{
		pDataMap = (CDvmMapObject*)((CDvmValue*)pData)->m_pDvmMapObj;
	}

	if (pDataMap == NULL)
	{
		return;
	}

	CDvmMapObject *pNewDataMap = NULL;

	if (pDataMap->m_pMap == NULL)
	{
		//查找其它映射对象中，跟当前对象ID一致的对象  shaolei
		pNewDataMap = pDataMap->GetMapByIDEx(pDataMap->m_strID);

// 		CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap *)pDataMap->GetAncestor(DMPCLASSID_CDVMDATASETMAP);
// 		CDvmLDeviceMap *pLDeviceMap = (CDvmLDeviceMap *)pDatasetMap->GetParent();
// 		POS pos = pLDeviceMap->GetHeadPosition();
// 
// 		while (pos != NULL)
// 		{
// 			CDvmDatasetMap *pMap = (CDvmDatasetMap *)pLDeviceMap->GetNext(pos);
// 
// 			if (pMap->m_strID != pDatasetMap->m_strID)
// 			{
// 				continue;
// 			}
// 
// 			pNewDataMap = pMap->GetMapByID(pDataMap->m_strID);
// 
// 			if (pNewDataMap != NULL)
// 			{
// 				break;
// 			}
// 		}

		pDataMap = pNewDataMap;
	}

	if (pDataMap == NULL)
	{
		return;
	}

	if (pDataMap->m_pMap == NULL)
	{
		return;
	}

	pDataMap->StringCmp();
	CStringCmpBlocks *pStrCmpBlocks = NULL;
	
	if (pData->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		pStrCmpBlocks = pDataMap->GetNameCmp_Dest();
	}
	else
	{
		pStrCmpBlocks = pDataMap->GetIDCmp_Dest();
	}

	rect.DeflateRect(AFX_TEXT_MARGIN, 0);

	if (pStrCmpBlocks != NULL)
	{
		pStrCmpBlocks->Draw(pDC, rect);
	}
	else
	{
		pDC->DrawText(pDataMap->m_pMap->m_strName, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
	}

// 	if (IsGroup())
// 	{
// 		
// 	}
// 	else
// 	{
// 		CDvmMapObject *pDataMap = (CDvmMapObject*)((CDvmValue*)pData)->m_pDvmMapObj;
// 	
// 		if (pDataMap->m_pMap == NULL)
// 		{
// 			return;
// 		}
// 
// 		pDataMap->StringCmp();
// 		CStringCmpBlocks *pStrCmpBlocks = pDataMap->GetNameCmp_Dest();
// 		rect.DeflateRect(AFX_TEXT_MARGIN, 0);
// 
// 		if (pStrCmpBlocks != NULL)
// 		{
// 			pStrCmpBlocks->Draw(pDC, rect);
// 		}
// 		else
// 		{
// 			pDC->DrawText(pDataMap->m_pMap->m_strName, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
// 		}	
// 	}
	

// 	CString strVal = FormatProperty();
// 
// 	rect.DeflateRect(AFX_TEXT_MARGIN, 0);
// 	pDC->DrawText(strVal, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
// 	m_bValueIsTruncated = pDC->GetTextExtent(strVal).cx > rect.Width();

	//
// 	rect.DeflateRect(AFX_TEXT_MARGIN, 0);
// 	rect.left = rect.right;
// 	rect.right = rect.left;
// 	pDC->DrawText(pData->m_strUnit, rect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

}


//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsStandPropGridCtrl
CDvmCmpDsStandPropGridCtrl::CDvmCmpDsStandPropGridCtrl()
{

}

CDvmCmpDsStandPropGridCtrl::~CDvmCmpDsStandPropGridCtrl()
{

}


void CDvmCmpDsStandPropGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
{
	if (m_bIngnoreSetCurrSel)
	{
		return;
	}

	if (pNewSel == NULL)
	{
		return;
	}

	CExBaseObject *pSelObj = (CExBaseObject*)pNewSel->GetData();
	CDvmMapObject *pMapObj = NULL;

	if (pSelObj == NULL)
	{
		return;
	}

	if (pSelObj->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		pMapObj = (CDvmMapObject*)((CDvmValue*)pSelObj)->m_pDvmMapObj;
	}
	else if  (pSelObj->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		pMapObj = (CDvmMapObject*)((CDvmData*)pSelObj)->m_pDvmMapObj;
	}

	if (m_pDvmCmpBasePropGridCtrlRef == NULL || pMapObj == NULL)
	{
		return;
	}

	if (pMapObj->m_pMap == NULL)
	{
		//如果是其它数据集映射的，也显示到StandGrid中，需要将其它数据集的映射对象查找到，并刷新右侧表格显示
		CDvmMapObject *pNewDataMap = pMapObj->GetMapByIDEx(pMapObj->m_strID);
		pMapObj = pNewDataMap;
	}

	if (pMapObj == NULL)
	{
		return;
	}

	if (pMapObj->m_pMap == NULL)
	{
		return;
	}

	CDvmCmpDsPropGridProperty *pProp = (CDvmCmpDsPropGridProperty*)pMapObj->m_pMap->m_dwItemData;

	if (pProp == NULL)
	{
		return;
	}

	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = TRUE;
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp, TRUE);
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp, TRUE);
	m_pDvmCmpBasePropGridCtrlRef->SetCurSel(pProp);
	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = FALSE;
}


BEGIN_MESSAGE_MAP(CDvmCmpDsStandPropGridCtrl, CMFCPropertyGridCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


CExBaseObject* CDvmCmpDsStandPropGridCtrl::GetSelDvmObject()
{
	CDvmMapObject *pMap = GetSelMapObject();

	if (pMap == NULL)
	{
		return NULL;
	}

	return pMap->m_pStand;
}

void CDvmCmpDsStandPropGridCtrl::DeleteMap(CExBaseObject *pDvmObject)
{
	CDvmMapObject *pMap = dvmmap_GetMpObject(pDvmObject);
	CDvmCmpDsPropGridProperty *pProp = NULL;
	pProp = (CDvmCmpDsPropGridProperty *)pMap->m_pStand->m_dwItemData;

	if (pProp == NULL)
	{
		return;
	}

	if (!pProp->IsGroup())
	{
		pProp->SetValue(_T(""));
	}

	POS pos = pMap->GetHeadPosition();
	CDvmMapObject *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMapObject *)pMap->GetNext(pos);
		DeleteMap(p);
	}

	pMap->DeleteMap();
}

void CDvmCmpDsStandPropGridCtrl::ConfirmMap(CExBaseObject *pDvmObject)
{
	CDvmMapObject *pMap = dvmmap_GetMpObject(pDvmObject);
	CDvmCmpDsPropGridProperty *pProp = NULL;
	pProp = (CDvmCmpDsPropGridProperty *)pMap->m_pStand->m_dwItemData;

	if (pProp == NULL)
	{
		return;
	}

	CRect rect = pProp->GetRect();
	CPaintDC dcPaint(this); // device context for painting
	CMemDC memDC(dcPaint, this);
	CDC* pDC = &memDC.GetDC();

	CStringCmpBlocks *pStrCmpBlocks = NULL;
	CDvmMapObject *pMapObj = NULL;

	if (pMap->m_pStand->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		pMapObj = (CDvmMapObject*)pDvmObject;
		pStrCmpBlocks = pMapObj->GetIDCmp_Stand();
	}
	else if  (pMap->m_pStand->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		pMapObj = (CDvmMapObject*)pDvmObject;
		pStrCmpBlocks = pMapObj->GetNameCmp_Stand();
	}

	pStrCmpBlocks->Draw(pDC, rect, DT_LEFT, RGB(0,0,0), RGB(0,0,0));

	POS pos = pMap->GetHeadPosition();
	CDvmMapObject *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMapObject *)pMap->GetNext(pos);
		ConfirmMap(p);
	}
}

void CDvmCmpDsStandPropGridCtrl::UpdateMap(CExBaseObject *pDvmObject)
{
	CDvmMapObject *pMap = dvmmap_GetMpObject(pDvmObject);
	CDvmCmpDsPropGridProperty *pProp = NULL;
	pProp = (CDvmCmpDsPropGridProperty *)pMap->m_pStand->m_dwItemData;

	if (!pProp->IsGroup())
	{
		if (pMap->m_pMap != NULL)
		{
			pProp->SetValue(pMap->m_pMap->m_strID);
		}
		else
		{
			pProp->SetValue(_T(""));
		}
	}

	POS pos = pMap->GetHeadPosition();
	CDvmMapObject *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMapObject *)pMap->GetNext(pos);
		UpdateMap(p);
	}
}

//显示每一个数据，从Map中获得所有映射的数据集的数据
void CDvmCmpDsStandPropGridCtrl::ShowDatasets()
{
	long nCount = m_listDvmDsMapStand.GetCount();
	ASSERT( nCount > 0);

	if (nCount == 0)
	{
		return;
	}

	long nIndex = 1;
	//CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)m_listDvmDsMapStand.GetHead();
	//shaolei 20220228 改为只显示当前选中的数据集映射下的所有映射数据
	CDvmDatasetMap *pDatasetMap = m_pDatasetMap;
	CDvmDataset *pDataset = (CDvmDataset*)pDatasetMap->m_pStand;
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmCmpDsPropGridProperty* pPropData = NULL;

	while (pos != NULL)
	{
		pDvmData = (CDvmData*)pDataset->GetNext(pos);

		if (CDvmMapTool::g_bOnlyShowNoMap == 1)
		{
			if (pDvmData->IsAllMap())
			{
				continue;
			}
		}

		pPropData = NewDvmDataProp(pDvmData, nIndex);
		nIndex++;
		AddProperty(pPropData,FALSE, FALSE);
	}

	AdjustLayout();
	Invalidate(FALSE);
}


CDvmCmpDsPropGridProperty* CDvmCmpDsStandPropGridCtrl::NewDvmDataProp(CDvmData *pDvmData, long nIndex)
{
	CDvmCmpDsPropGridProperty* pPropData = NULL;
	CString strName;
	strName.Format(_T("%03d  %s"), nIndex, pDvmData->m_strName);

	if (pDvmData->GetCount() == 0)
	{
		pPropData = new CDvmCmpDsStandPropGridProperty(strName, _T(""), _T(""));
	}
	else
	{
		pPropData = new CDvmCmpDsStandPropGridProperty(strName);
		NewDvmValuesProp(pDvmData, pPropData);
	}

	pDvmData->m_dwItemData = (DWORD)pPropData;
	pPropData->SetData((DWORD)pDvmData);
	pPropData->AllowEdit(FALSE);

	return pPropData;
}


void CDvmCmpDsStandPropGridCtrl::NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsPropGridProperty *pParent)
{
	POS pos = pDvmValues->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmValue *pDest = NULL;
	CDvmCmpDsPropGridProperty *pProp = NULL;
	CDvmValueMap *pValueMap = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pDvmValues->GetNext(pos);

		if (CDvmMapTool::g_bOnlyShowNoMap == 1)
		{
			if (pValue->IsAllMap())
			{
				continue;
			}
		}

		if (pValue->GetCount() == 0)
		{
			pValueMap = (CDvmValueMap *)pValue->m_pDvmMapObj;

			if (pValueMap == NULL)
			{
				pProp = new CDvmCmpDsStandPropGridProperty(pValue->m_strID, _T(""), _T(""));
			}
			else
			{
				//待修改 如果pValueMap->m_pMap != NULL， 则取m_pMap的id，否则从其它获取
				CString strMapID = pValueMap->GetMapID();
				pProp = new CDvmCmpDsStandPropGridProperty(pValue->m_strID, strMapID, _T(""));

// 				if (pValueMap->m_pMap != NULL)
// 				{
// 					pProp = new CDvmCmpDsStandPropGridProperty(pValue->m_strID, pValueMap->m_pMap->m_strID, _T(""));
// 				}
// 				else
// 				{
// 					pProp = new CDvmCmpDsStandPropGridProperty(pValue->m_strID, _T(""), _T(""));
// 				}
			}
		}
		else
		{
			pProp = new CDvmCmpDsStandPropGridProperty(pValue->m_strName);
			NewDvmValuesProp(pValue, pProp);
		}

		pValue->m_dwItemData = (DWORD)pProp;
		pProp->SetData((DWORD)pValue);
		pProp->AllowEdit(FALSE);

		pParent->AddSubItem(pProp);
	}
}

void CDvmCmpDsStandPropGridCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CDvmMapObject *pMap = GetSelMapObject();

	if (pMap == NULL)
	{
		return;
	}


	CMenu menu;		
	menu.CreatePopupMenu();

#ifdef NOT_USE_XLANGUAGE
	menu.AppendMenu(MF_STRING,ID_DVMMAP_CREATEDATAMAP_STAND, _T("新建数据映射")/*_T("创建数据映射")*/);	
#else
	menu.AppendMenu(MF_STRING,ID_DVMMAP_CREATEDATAMAP_STAND,g_sLangTxt_CreatDataMap/*_T("创建数据映射")*/);
#endif

	if (pMap->m_pMap != NULL)
	{
		//menu.AppendMenu(MF_STRING,ID_DVMMAP_MODIFYDATAMAP_STAND,_T("修改数据映射"));
		//menu.AppendMenu(MF_STRING,ID_DVMMAP_CONFIRMDATAMAP_STAND,_T("确认数据映射"));
#ifdef NOT_USE_XLANGUAGE
		menu.AppendMenu(MF_STRING,ID_DVMMAP_DELETEDATAMAP_STAND, _T("删除数据映射")/*_T("删除数据映射")*/);
#else
		menu.AppendMenu(MF_STRING,ID_DVMMAP_DELETEDATAMAP_STAND,g_sLangTxt_DeleteDataMap/*_T("删除数据映射")*/);
#endif
	}

	CWnd *pOwer = pWnd->GetParent();
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pOwer);	
}


//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsMapPropGridProperty
IMPLEMENT_DYNAMIC(CDvmCmpDsMapPropGridProperty, CDvmCmpDsPropGridProperty)

CDvmCmpDsMapPropGridProperty::CDvmCmpDsMapPropGridProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
: CDvmCmpDsPropGridProperty(strGroupName, dwData, bIsValueList)
{

}

CDvmCmpDsMapPropGridProperty::CDvmCmpDsMapPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
															   LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
															   : CDvmCmpDsPropGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{

}



void CDvmCmpDsMapPropGridProperty::OnDrawName(CDC* pDC, CRect rect)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pWndList);

	COLORREF clrTextOld = (COLORREF)-1;

	if (IsSelected() &&(!m_pWndList->IsVSDotNetLook() || !IsGroup() ||  m_bIsValueList))
	{
		CRect rectFill = rect;
		rectFill.top++;

		clrTextOld = pDC->SetTextColor(afxGlobalData.clrTextHilite);
		pDC->FillRect(rectFill, &afxGlobalData.brHilite);
	}

	if (m_pWndList->IsVSDotNetLook() && IsGroup())
	{
		clrTextOld = pDC->SetTextColor(RGB(0,0,0));
	}

	rect.DeflateRect(AFX_TEXT_MARGIN, 0);

	int nTextHeight = pDC->DrawText(m_strName, rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

	m_bNameIsTruncated = pDC->GetTextExtent(m_strName).cx > rect.Width();

	if (IsSelected() && m_pWndList->IsVSDotNetLook() && IsGroup())
	{
		CRect rectFocus = rect;
		rectFocus.top = rectFocus.CenterPoint().y - nTextHeight / 2;
		rectFocus.bottom = rectFocus.top + nTextHeight;
		rectFocus.right = min(rect.right, rectFocus.left + pDC->GetTextExtent(m_strName).cx);
		rectFocus.InflateRect(2, 0);

		COLORREF clrShadow = afxGlobalData.clrBtnShadow;

		pDC->Draw3dRect(rectFocus, clrShadow, clrShadow);
	}

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor(clrTextOld);
	}
}
// 
// void CDvmCmpDsMapPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
// {
// 	//rect.right -= UNIT_GAP;
// 	CMFCPropertyGridProperty::OnDrawValue(pDC, rect);
// 	// 
// 	// 	ASSERT_VALID(this);
// 	// 	ASSERT_VALID(pDC);
// 	// 	ASSERT_VALID(m_pWndList);
// 	// 
// 	// 	if ((IsGroup() && !m_bIsValueList) || !HasValueField())
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	CShortData *pData = (CShortData*)m_dwData;
// 	// 
// 	// 	if (pData == NULL)
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	if (pData->GetClassID() != DTMCLASSID_CSHORTDATA)
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	if (pData->m_strUnit.GetLength() == 0)
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	if (pData->m_strUnit == _T("无"))
// 	// 	{
// 	// 		return;
// 	// 	}
// 	// 
// 	// 	rect.DeflateRect(AFX_TEXT_MARGIN, 0);
// 	// 	rect.left = rect.right;
// 	// 	rect.right = rect.left + UNIT_GAP;
// 	// 	pDC->DrawText(pData->m_strUnit, rect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
// 
// }

void CDvmCmpDsMapPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
{
	CDvmCmpDsPropGridProperty::OnDrawValue(pDC, rect);
}

//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsMapPropGridCtrl
CDvmCmpDsMapPropGridCtrl::CDvmCmpDsMapPropGridCtrl()
{

}

CDvmCmpDsMapPropGridCtrl::~CDvmCmpDsMapPropGridCtrl()
{

}


void CDvmCmpDsMapPropGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
{
	if (m_bIngnoreSetCurrSel)
	{
		return;
	}

	if (pNewSel == NULL)
	{
		return;
	}

	CExBaseObject *pSelObj = (CExBaseObject*)pNewSel->GetData();
	CDvmMapObject *pMapObj = NULL;

	if (pSelObj == NULL)
	{
		return;
	}

	if (pSelObj->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		pMapObj = (CDvmMapObject*)((CDvmValue*)pSelObj)->m_pDvmMapObj;
	}
	else if  (pSelObj->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		pMapObj = (CDvmMapObject*)((CDvmData*)pSelObj)->m_pDvmMapObj;
	}

	if (m_pDvmCmpBasePropGridCtrlRef == NULL || pMapObj == NULL)
	{
		return;
	}

	if (pMapObj->m_pStand == NULL)
	{
		return;
	}

	CDvmCmpDsPropGridProperty *pProp = (CDvmCmpDsPropGridProperty*)pMapObj->m_pStand->m_dwItemData;

	if (pProp == NULL)
	{
		return;
	}

	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = TRUE;
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp, TRUE);
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp, TRUE);
	m_pDvmCmpBasePropGridCtrlRef->SetCurSel(pProp);
	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = FALSE;
}

BEGIN_MESSAGE_MAP(CDvmCmpDsMapPropGridCtrl, CMFCPropertyGridCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

//20231025 huangliang 右侧表格只显示对应数据集数据
void CDvmCmpDsMapPropGridCtrl::ShowDatasetMap(CDvmDatasetMap *pDvmDataset)
{
	CDvmDataset *pDataset = (CDvmDataset*)pDvmDataset->m_pMap;
	ShowDataset(pDataset, NULL);
}
void CDvmCmpDsMapPropGridCtrl::ShowDatasets()
{
	long nCount = m_listDvmDsMapStand.GetCount();
	ASSERT( nCount > 0);

	if (nCount == 0)
	{
		return;
	}

	CDvmCmpDsPropGridProperty* pPropDataset = NULL;
	CDvmDatasetMap *pDatasetMap = NULL;
	POS pos = m_listDvmDsMapStand.GetHeadPosition();
	CDvmDataset *pDataset = NULL;
	CString strDsPath;

	if (nCount == 1)
	{
		pDatasetMap = (CDvmDatasetMap *)m_listDvmDsMapStand.GetNext(pos);
		pDataset = (CDvmDataset*)pDatasetMap->m_pMap;
		ShowDataset(pDataset, NULL);
	}
	else
	{
		while (pos != NULL)
		{
			pDatasetMap = (CDvmDatasetMap *)m_listDvmDsMapStand.GetNext(pos);
			pDataset = (CDvmDataset*)pDatasetMap->m_pMap;

			if (pDataset == NULL)
			{
				continue;
			}

			strDsPath = pDataset->m_strID;

			if ( pDatasetMap->m_strLdviceMap != pDatasetMap->m_strLdvice)
			{
				strDsPath.Format(_T("%s$%s"), pDatasetMap->m_strLdviceMap, pDataset->m_strID);
			}
			
			pPropDataset = new CDvmCmpDsMapPropGridProperty(strDsPath);
			ShowDataset(pDataset, pPropDataset);
			AddProperty(pPropDataset, FALSE, FALSE);
		}
	}

	AdjustLayout();
	Invalidate(FALSE);
}

CExBaseObject* CDvmCmpDsMapPropGridCtrl::GetSelDvmObject()
{
	return GetSelectData();
}


void CDvmCmpDsMapPropGridCtrl::DeleteMap(CExBaseObject *pDvmObject)
{
	if (pDvmObject == NULL)
	{
		return;
	}

	CDvmCmpDsPropGridProperty *pProp = NULL;
	pProp = (CDvmCmpDsPropGridProperty *)pDvmObject->m_dwItemData;

	if (pProp == NULL)
	{
		return;
	}

	if (!pProp->IsGroup())
	{
		pProp->SetValue(_T(""));
	}

	if (!pDvmObject->IsBaseList())
	{
		return;
	}

	CExBaseList *pList = (CExBaseList*)pDvmObject;
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);
		DeleteMap(p);
	}
}

void CDvmCmpDsMapPropGridCtrl::UpdateMap(CExBaseObject *pDvmObject)
{
	CDvmCmpDsPropGridProperty *pProp = NULL;
	pProp = (CDvmCmpDsPropGridProperty *)pDvmObject->m_dwItemData;
	CDvmMapObject *pMap = dvmmap_GetMpObject(pDvmObject);

	if (!pProp->IsGroup())
	{
		if (pMap != NULL)
		{
			pProp->SetValue(pMap->m_strID);
		}
	}

	if (!pDvmObject->IsBaseList())
	{
		return;
	}

	CExBaseList *pList = (CExBaseList*)pDvmObject;
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);
		UpdateMap(p);
	}
}

void CDvmCmpDsMapPropGridCtrl::ConfirmMap(CExBaseObject *pDvmObject)
{
	if (pDvmObject == NULL)
	{
		return;
	}

	CDvmCmpDsPropGridProperty *pProp = NULL;
	pProp = (CDvmCmpDsPropGridProperty *)pDvmObject->m_dwItemData;

	if (pProp == NULL)
	{
		return;
	}

	CRect rect = pProp->GetRect();
	CPaintDC dcPaint(this); // device context for painting
	CMemDC memDC(dcPaint, this);
	CDC* pDC = &memDC.GetDC();

	CStringCmpBlocks *pStrCmpBlocks = NULL;
	CDvmMapObject *pMapObj = NULL;

	if (pDvmObject->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		pMapObj = (CDvmMapObject*)pDvmObject;
		pStrCmpBlocks = pMapObj->GetIDCmp_Dest();
	}
	else if  (pDvmObject->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		pMapObj = (CDvmMapObject*)pDvmObject;
		pStrCmpBlocks = pMapObj->GetNameCmp_Dest();
	}

	pStrCmpBlocks->Draw(pDC, rect, RGB(0,0,0), RGB(0,0,0));

	CExBaseList *pList = (CExBaseList*)pDvmObject;
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);
		ConfirmMap(p);
	}
}

void CDvmCmpDsMapPropGridCtrl::ShowDataset(CDvmDataset *pDataset, CDvmCmpDsPropGridProperty *pParent)
{
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmCmpDsPropGridProperty* pPropData = NULL;
	long nIndex = 1;

	while (pos != NULL)
	{
		pDvmData = (CDvmData*)pDataset->GetNext(pos);
		pPropData = NewDvmDataProp(pDvmData, nIndex);
		nIndex++;

		if (pParent == NULL)
		{
			AddProperty(pPropData,FALSE, FALSE);
		}
		else
		{
			pParent->AddSubItem(pPropData);
		}
	}
}


CDvmCmpDsPropGridProperty* CDvmCmpDsMapPropGridCtrl::NewDvmDataProp(CDvmData *pDvmData, long nIndex)
{
	CDvmCmpDsPropGridProperty* pPropData = NULL;
	CString strName;
	strName.Format(_T("%03d  %s"), nIndex, pDvmData->m_strName);

	if (pDvmData->GetCount() == 0)
	{
		CDvmMapObject *pMap = dvmmap_GetMpObject(pDvmData);
		if(pMap!= NULL)		//20231103 luozibing 当data和value 绑定时页面显示value信息
		{
			pPropData = new CDvmCmpDsMapPropGridProperty(strName, pMap->m_strID, _T(""));
		}
		else
		{
			pPropData = new CDvmCmpDsMapPropGridProperty(strName, _T(""), _T(""));
		}
	}
	else
	{
		pPropData = new CDvmCmpDsMapPropGridProperty(strName);
		NewDvmValuesProp(pDvmData, pPropData);
	}

	pDvmData->m_dwItemData = (DWORD)pPropData;
	pPropData->SetData((DWORD)pDvmData);
	pPropData->AllowEdit(FALSE);

	return pPropData;
}

void CDvmCmpDsMapPropGridCtrl::NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsPropGridProperty *pParent)
{
	POS pos = pDvmValues->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmCmpDsPropGridProperty *pProp = NULL;
	CDvmValueMap *pValueMap = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pDvmValues->GetNext(pos);

		if (pValue->GetCount() == 0)
		{
			pValueMap = (CDvmValueMap *)pValue->m_pDvmMapObj;

			if (pValueMap != NULL)
			{
				if (pValueMap->m_pStand != NULL)
				{
					pProp = new CDvmCmpDsMapPropGridProperty(pValue->m_strID, pValueMap->m_pStand->m_strID, _T(""));
				}
				else
				{
					pProp = new CDvmCmpDsMapPropGridProperty(pValue->m_strID, _T(""), _T(""));
				}
			}
			else
			{
				pProp = new CDvmCmpDsMapPropGridProperty(pValue->m_strID, _T(""), _T(""));
			}
		}
		else
		{
			pProp = new CDvmCmpDsMapPropGridProperty(pValue->m_strID);
			NewDvmValuesProp(pValue, pProp);
		}

		pValue->m_dwItemData = (DWORD)pProp;
		pProp->SetData((DWORD)pValue);
		pProp->AllowEdit(FALSE);

		pParent->AddSubItem(pProp);
	}
}

void CDvmCmpDsMapPropGridCtrl::InitDvmDsMapStand()
{
	//目标数据集侧，将匹配到相同ID的源数据集的，全部添加到链表，最后一个参数传TRUE
	m_pDvmDeviceMap->FindDvmMapObj_ByStand(DMPCLASSID_CDVMDATASETMAP, m_pDatasetMap->m_pStand, m_listDvmDsMapStand, TRUE);
	ASSERT(m_listDvmDsMapStand.GetCount() > 0);
}

void CDvmCmpDsMapPropGridCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CExBaseObject *pSelObj = GetSelectData();
	CDvmMapObject *pMap = NULL;

	if (pSelObj == NULL)
	{
		return;
	}

	if (pSelObj->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		pMap = (CDvmMapObject*)((CDvmData*)pSelObj)->m_pDvmMapObj;
	}
	else if  (pSelObj->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		pMap = (CDvmMapObject*)((CDvmValue*)pSelObj)->m_pDvmMapObj;
	}
	else
	{
		return ;
	}

	CMenu menu;		
	menu.CreatePopupMenu();

#ifdef NOT_USE_XLANGUAGE
	menu.AppendMenu(MF_STRING,ID_DVMMAP_CREATEDATAMAP_DEST,_T("创建数据映射")/*_T("创建数据映射")*/);
#else
	menu.AppendMenu(MF_STRING,ID_DVMMAP_CREATEDATAMAP_DEST,g_sLangTxt_CreatDataMap/*_T("创建数据映射")*/);
#endif

	if (pMap != NULL)
	{
#ifdef NOT_USE_XLANGUAGE
		//menu.AppendMenu(MF_STRING,ID_DVMMAP_MODIFYDATAMAP_DEST,_T("修改数据映射"));
		menu.AppendMenu(MF_STRING,ID_DVMMAP_DELETEDATAMAP_DEST,_T("删除数据映射")/*_T("删除数据映射")*/);
		//menu.AppendMenu(MF_STRING,ID_DVMMAP_CONFIRMDATAMAP_DEST,_T("确认数据映射"));
#else
		menu.AppendMenu(MF_STRING,ID_DVMMAP_DELETEDATAMAP_DEST,g_sLangTxt_DeleteDataMap/*_T("删除数据映射")*/);
#endif
	}

	CWnd *pOwer = pWnd->GetParent();
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pOwer);	
}
