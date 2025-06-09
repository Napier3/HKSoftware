#include "StdAfx.h"
#include "DvmCmpPropGridCtrl.h"



#define AFX_PROP_HAS_LIST 0x0001
#define AFX_PROP_HAS_BUTTON 0x0002
#define AFX_PROP_HAS_SPIN 0x0004

// #define UNIT_GAP    24

IMPLEMENT_DYNAMIC(CDvmCmpPropGridProperty, CMFCPropertyGridProperty)

CDvmCmpPropGridProperty::CDvmCmpPropGridProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
: CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList)
{

}

CDvmCmpPropGridProperty::CDvmCmpPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
													   LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
													   : CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{

}

void CDvmCmpPropGridProperty::SetIsValueList(BOOL b)
{
	m_bIsValueList = b;
}

void CDvmCmpPropGridProperty::SetCombBoxType()
{
	m_dwFlags = AFX_PROP_HAS_LIST;
}


void CDvmCmpPropGridProperty::OnDrawName(CDC* pDC, CRect rect)
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

void CDvmCmpPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
{
	//rect.right -= UNIT_GAP;
	CMFCPropertyGridProperty::OnDrawValue(pDC, rect);
// 
// 	ASSERT_VALID(this);
// 	ASSERT_VALID(pDC);
// 	ASSERT_VALID(m_pWndList);
// 
// 	if ((IsGroup() && !m_bIsValueList) || !HasValueField())
// 	{
// 		return;
// 	}
// 
// 	CShortData *pData = (CShortData*)m_dwData;
// 
// 	if (pData == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (pData->GetClassID() != DTMCLASSID_CSHORTDATA)
// 	{
// 		return;
// 	}
// 
// 	if (pData->m_strUnit.GetLength() == 0)
// 	{
// 		return;
// 	}
// 
// 	if (pData->m_strUnit == _T("无"))
// 	{
// 		return;
// 	}
// 
// 	rect.DeflateRect(AFX_TEXT_MARGIN, 0);
// 	rect.left = rect.right;
// 	rect.right = rect.left + UNIT_GAP;
// 	pDC->DrawText(pData->m_strUnit, rect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

}


CWnd* CDvmCmpPropGridProperty::CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat)
{
	//rectEdit.right -= UNIT_GAP;
	return CMFCPropertyGridProperty::CreateInPlaceEdit(rectEdit, bDefaultFormat);
}

void CDvmCmpPropGridProperty::SetValue(const COleVariant& varValue)
{
	CMFCPropertyGridProperty::SetValue(varValue);
}

void CDvmCmpPropGridProperty::SetModifyFlagEx(BOOL bFlag)
{
	m_bIsModified = bFlag;
}


//////////////////////////////////////////////////////////////////////////
//

CExBaseObject*  CDvmCmpBasePropGridCtrl::GetSelectData()
{
	CDvmCmpPropGridProperty *pProp = (CDvmCmpPropGridProperty*)GetCurSel();

	if (pProp == NULL)
	{
		return NULL;
	}

	if (pProp->IsGroup())
	{
		return NULL;
	}

	CExBaseObject  *pData = (CExBaseObject*)pProp->GetData();

	return pData;
}


void CDvmCmpBasePropGridCtrl::EnsurePropVisible(CMFCPropertyGridProperty* pProp, BOOL bExpandParents/* = FALSE*/)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pProp);

	if (m_nRowHeight == 0)
	{
		return;
	}

	if (bExpandParents && pProp->GetParent() != NULL)
	{
		CMFCPropertyGridProperty* pParent = pProp;

		while ((pParent = pParent->GetParent()) != NULL)
		{
			ASSERT_VALID(pParent);
			pParent->Expand(TRUE);
		}
	}

	CRect rect = pProp->GetRect();

	if (rect.top >= m_rectList.top - 1 && rect.bottom <= m_rectList.bottom)
	{
		return;
	}

	if (rect.top < m_rectList.top - 1 && rect.bottom >= m_rectList.top - 1)
	{
		OnVScroll(SB_LINEUP, 0, NULL);
	}
	else if (rect.bottom > m_rectList.bottom && rect.top <= m_rectList.bottom)
	{
		OnVScroll(SB_LINEDOWN, 0, NULL);
	}
	else
	{
		OnVScroll(SB_THUMBPOSITION, rect.top / m_nRowHeight - m_nVertScrollOffset-5, NULL);
		//SetScrollPos(SB_VERT, rect.top + 5);
	}

	pProp->AdjustButtonRect();
	pProp->Redraw();
}


//////////////////////////////////////////////////////////////////////////
//CDvmCmpCatalogPropGridCtrl
CDvmCmpCatalogPropGridCtrl::CDvmCmpCatalogPropGridCtrl()
{	
	m_clrLine = RGB(128, 128, 128);
	m_pMsgRcvWnd = NULL;
	m_bIngnoreSetCurrSel = FALSE;
	m_pDvmDeviceMap = NULL;
}

CDvmCmpCatalogPropGridCtrl::~CDvmCmpCatalogPropGridCtrl()
{
	
}

void CDvmCmpCatalogPropGridCtrl::UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) 
{

}

// 
// void CDvmCmpCatalogPropGridCtrl::SetDevice(CDvmDevice *pDvmDevice)
// {
// 	m_pDvmDevice = pDvmDevice;
// 
// 	CDvmCmpPropGridProperty* pRoot = NULL;
// 
// 	pRoot = new CDvmCmpPropGridProperty(m_pDvmDevice->m_strName);
// 
// 	POS pos = m_pDvmDevice->GetHeadPosition();
// 	CDvmLogicDevice *pLdDevice = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pLdDevice = (CDvmLogicDevice *)m_pDvmDevice->GetNext(pos);
// 		AddDvmLdevice(pLdDevice, pRoot);
// 	}
// 	
// 	AddProperty(pRoot);
// 	
// 	AdjustLayout();
// 	Invalidate(FALSE);
// }
// 
// void CDvmCmpCatalogPropGridCtrl::AddDvmLdevice(CDvmLogicDevice  *pDvmLdevice, CDvmCmpPropGridProperty *pParent)
// {
// 	CDvmCmpPropGridProperty* pLdProp = NULL;
// 	CDvmCmpPropGridProperty* pDsProp = NULL;
// 
// 	pLdProp = new CDvmCmpPropGridProperty(pDvmLdevice->m_strName);
// 	pDvmLdevice->m_dwItemData = (DWORD)pLdProp;
// 	pLdProp->SetData((DWORD)pDvmLdevice);
// 
// 	POS pos = pDvmLdevice->GetHeadPosition();
// 	CDvmDataset *pDataset = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pDataset = (CDvmDataset *)pDvmLdevice->GetNext(pos);
// 		pDsProp = new CDvmCmpPropGridProperty(pDataset->m_strName, pDataset->m_strID, _T(""));
// 		pLdProp->AddSubItem(pDsProp);
// 		pDataset->m_dwItemData = (DWORD)pDsProp;
// 		pDsProp->SetData((DWORD)pDataset);
// 		pDsProp->AllowEdit(FALSE);
// 	}
// 
// 	pParent->AddSubItem(pLdProp);
// }


BEGIN_MESSAGE_MAP(CDvmCmpCatalogPropGridCtrl, CMFCPropertyGridCtrl)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


void CDvmCmpCatalogPropGridCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnLButtonDblClkMsg();

	__super::OnLButtonDblClk(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
//CDvmCmpCatalogStandPropGridCtrl
CDvmCmpCatalogStandPropGridCtrl::CDvmCmpCatalogStandPropGridCtrl()
{
	
}

CDvmCmpCatalogStandPropGridCtrl::~CDvmCmpCatalogStandPropGridCtrl()
{

}

void CDvmCmpCatalogStandPropGridCtrl::ShowDvmCmpCatalog(CDvmDeviceMap *pDvmDeviceMap)
{
	m_pDvmDeviceMap = pDvmDeviceMap;
	m_pDvmDevice = (CDvmDevice*)pDvmDeviceMap->m_pStand;
	CDvmCmpPropGridProperty* pRoot = NULL;
	pRoot = new CDvmCmpPropGridProperty(m_pDvmDevice->m_strName);
	pRoot->SetData((DWORD)pDvmDeviceMap);
	pDvmDeviceMap->m_dwItemData = (DWORD)pRoot;
	POS pos = pDvmDeviceMap->GetHeadPosition();
	CDvmLDeviceMap *pLdDevice = NULL;

	while (pos != NULL)
	{
		pLdDevice = (CDvmLDeviceMap *)pDvmDeviceMap->GetNext(pos);
		AddDvmLdevice(pLdDevice, pRoot);
	}

	AddProperty(pRoot);

	AdjustLayout();
	Invalidate(FALSE);
}


void CDvmCmpCatalogStandPropGridCtrl::AddDvmLdevice(CDvmLDeviceMap  *pDvmLdevice, CDvmCmpPropGridProperty *pParent)
{
	CDvmCmpPropGridProperty* pLdProp = NULL;
	CDvmCmpPropGridProperty* pDsProp = NULL;

	pLdProp = new CDvmCmpPropGridProperty(pDvmLdevice->m_strName);
	pDvmLdevice->m_dwItemData = (DWORD)pLdProp;
	pLdProp->SetData((DWORD)pDvmLdevice);

	POS pos = pDvmLdevice->GetHeadPosition();
	CDvmDatasetMap *pDatasetMap = NULL;

	while (pos != NULL)
	{
		pDatasetMap = (CDvmDatasetMap *)pDvmLdevice->GetNext(pos);

		if (pDatasetMap->m_pMap != NULL)
		{
			pDsProp = new CDvmCmpPropGridProperty(pDatasetMap->m_pStand->m_strName, pDatasetMap->m_pMap->m_strID, _T(""));
		}
		else
		{
			pDsProp = new CDvmCmpPropGridProperty(pDatasetMap->m_pStand->m_strName, _T(""), _T(""));
		}

		pLdProp->AddSubItem(pDsProp);
		pDatasetMap->m_dwItemData = (DWORD)pDsProp;
		pDsProp->SetData((DWORD)pDatasetMap);
		pDsProp->AllowEdit(FALSE);
	}

	pParent->AddSubItem(pLdProp);
}

void CDvmCmpCatalogStandPropGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
{
	if (m_bIngnoreSetCurrSel)
	{
		return;
	}

	CExBaseObject *pSelObj = (CExBaseObject*)pNewSel->GetData();

	if (pSelObj == NULL)
	{
		return;
	}

	if (pSelObj->GetClassID() != DMPCLASSID_CDVMDATASETMAP)
	{
		return;
	}

	if (m_pDvmCmpBasePropGridCtrlRef == NULL)
	{
		return;
	}

	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)pSelObj;

	if (pDatasetMap->m_pMap == NULL)
	{
		return;
	}

	CDvmCmpPropGridProperty *pProp = (CDvmCmpPropGridProperty*)pDatasetMap->m_pMap->m_dwItemData;

	if (pProp == NULL)
	{
		return;
	}

	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = TRUE;
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp);
	m_pDvmCmpBasePropGridCtrlRef->SetCurSel(pProp);
	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = FALSE;
}


void CDvmCmpCatalogStandPropGridCtrl::OnLButtonDblClkMsg()
{
	CExBaseObject *pSelObj = GetSelectData();

	if (pSelObj == NULL)
	{
		return;
	}

	if (pSelObj->GetClassID() != DMPCLASSID_CDVMDATASETMAP)
	{
		return;
	}

	CWnd *pParent = GetParent();
	pParent->PostMessage(WM_OPEN_DVMCMP_DATASET, (WPARAM)pSelObj, (LPARAM)pSelObj);
}



//////////////////////////////////////////////////////////////////////////
//CDvmCmpCatalogMapPropGridCtrl
CDvmCmpCatalogMapPropGridCtrl::CDvmCmpCatalogMapPropGridCtrl()
{
	m_pDvmDeviceMap = NULL;
}

CDvmCmpCatalogMapPropGridCtrl::~CDvmCmpCatalogMapPropGridCtrl()
{

}

void CDvmCmpCatalogMapPropGridCtrl::ShowDvmCmpCatalog(CDvmDeviceMap *pDvmDeviceMap)
{
	m_pDvmDeviceMap = pDvmDeviceMap;
	m_pDvmDevice = (CDvmDevice*)pDvmDeviceMap->m_pMap;
	CDvmCmpPropGridProperty* pRoot = NULL;
	pRoot = new CDvmCmpPropGridProperty(m_pDvmDevice->m_strName);
	pRoot->SetData((DWORD)pDvmDeviceMap);
	m_pDvmDevice->m_dwItemData = (DWORD)pRoot;
	POS pos = m_pDvmDevice->GetHeadPosition();
	CDvmLogicDevice *pLdDevice = NULL;

	while (pos != NULL)
	{
		pLdDevice = (CDvmLogicDevice *)pDvmDeviceMap->GetNext(pos);
		AddDvmLdevice(pLdDevice, pRoot);
	}

	AddProperty(pRoot);

	AdjustLayout();
	Invalidate(FALSE);
}

void CDvmCmpCatalogMapPropGridCtrl::AddDvmLdevice(CDvmLogicDevice  *pDvmLdevice, CDvmCmpPropGridProperty *pParent)
{
	CDvmCmpPropGridProperty* pLdProp = NULL;
	CDvmCmpPropGridProperty* pDsProp = NULL;

	pLdProp = new CDvmCmpPropGridProperty(pDvmLdevice->m_strName);
	pDvmLdevice->m_dwItemData = (DWORD)pLdProp;
	pLdProp->SetData((DWORD)pDvmLdevice);

	POS pos = pDvmLdevice->GetHeadPosition();
	CDvmDataset *pDataset = NULL;
	CDvmDatasetMap *pDsMap = NULL;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)pDvmLdevice->GetNext(pos);
		pDsMap = (CDvmDatasetMap*)m_pDvmDeviceMap->FindDvmMapObj_ByMap(DMPCLASSID_CDVMDATASETMAP, pDataset);

		if (pDsMap == NULL)
		{
			pDsProp = new CDvmCmpPropGridProperty(pDataset->m_strName, _T(""), _T(""));
		}
		else
		{
			pDsProp = new CDvmCmpPropGridProperty(pDataset->m_strName, pDsMap->m_pStand->m_strID, _T(""));
		}

		pLdProp->AddSubItem(pDsProp);
		pDataset->m_dwItemData = (DWORD)pDsProp;
		pDsProp->SetData((DWORD)pDataset);
		pDsProp->AllowEdit(FALSE);
	}

	pParent->AddSubItem(pLdProp);
}
// 
// void CDvmCmpCatalogMapPropGridCtrl::AddDvmLdevice(CDvmLDeviceMap  *pDvmLdevice, CDvmCmpPropGridProperty *pParent)
// {
// 	CDvmCmpPropGridProperty* pLdProp = NULL;
// 	CDvmCmpPropGridProperty* pDsProp = NULL;
// 
// 	pLdProp = new CDvmCmpPropGridProperty(pDvmLdevice->m_strName);
// 	pDvmLdevice->m_dwItemData = (DWORD)pLdProp;
// 	pLdProp->SetData((DWORD)pDvmLdevice);
// 
// 	POS pos = pDvmLdevice->GetHeadPosition();
// 	CDvmDatasetMap *pDatasetMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pDatasetMap = (CDvmDatasetMap *)pDvmLdevice->GetNext(pos);
// 
// 		if (pDatasetMap->m_pMap != NULL)
// 		{
// 			pDsProp = new CDvmCmpPropGridProperty(pDatasetMap->m_pStand->m_strName, pDatasetMap->m_pMap->m_strID, _T(""));
// 		}
// 		else
// 		{
// 			pDsProp = new CDvmCmpPropGridProperty(pDatasetMap->m_pStand->m_strName, _T(""), _T(""));
// 		}
// 
// 		pLdProp->AddSubItem(pDsProp);
// 		pDatasetMap->m_dwItemData = (DWORD)pDsProp;
// 		pDsProp->SetData((DWORD)pDatasetMap);
// 		pDsProp->AllowEdit(FALSE);
// 	}
// 
// 	pParent->AddSubItem(pLdProp);
// }

void CDvmCmpCatalogMapPropGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
{
	if (m_bIngnoreSetCurrSel)
	{
		return;
	}

	CExBaseObject *pSelObj = (CExBaseObject*)pNewSel->GetData();

	if (pSelObj == NULL)
	{
		return;
	}

	if (pSelObj->GetClassID() != DVMCLASSID_CDVMDATASET)
	{
		return;
	}

	if (m_pDvmCmpBasePropGridCtrlRef == NULL)
	{
		return;
	}

	CDvmCmpCatalogStandPropGridCtrl *pStandProp = (CDvmCmpCatalogStandPropGridCtrl*)m_pDvmCmpBasePropGridCtrlRef;
	CDvmDataset *pDataset = (CDvmDataset*)pSelObj;
	CDvmDeviceMap *pDvmDeviceMap = m_pDvmDeviceMap;
	CExBaseList oList;
	pDvmDeviceMap->FindDvmMapObj_ByMap(DMPCLASSID_CDVMDATASETMAP, pDataset, oList);

	if (oList.GetCount() == 0)
	{
		return;
	}

	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)oList.GetHead();
	CDvmCmpPropGridProperty *pProp = (CDvmCmpPropGridProperty*)pDatasetMap->m_dwItemData;
	oList.RemoveAll();

	if (pProp == NULL)
	{
		return;
	}

	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = TRUE;
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp);
	m_pDvmCmpBasePropGridCtrlRef->SetCurSel(pProp);
	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = FALSE;

}

void CDvmCmpCatalogMapPropGridCtrl::OnLButtonDblClkMsg()
{

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//CDvmCmpDsMapPropGridProperty
IMPLEMENT_DYNAMIC(CDvmCmpDsMapPropGridProperty, CDvmCmpPropGridProperty)

CDvmCmpDsMapPropGridProperty::CDvmCmpDsMapPropGridProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
: CDvmCmpPropGridProperty(strGroupName, dwData, bIsValueList)
{

}

CDvmCmpDsMapPropGridProperty::CDvmCmpDsMapPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
												 LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
	: CDvmCmpPropGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
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

void CDvmCmpDsMapPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
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


void CDvmCmpDsPropGridCtrl::InitDvmDsMapStand()
{
	m_pDvmDeviceMap->FindDvmMapObj_ByStand(DMPCLASSID_CDVMDATASETMAP, m_pDatasetMap->m_pStand, m_listDvmDsMapStand);
	ASSERT(m_listDvmDsMapStand.GetCount() > 0);
}

CDvmCmpDsMapPropGridProperty* CDvmCmpDsPropGridCtrl::NewDvmDataProp(CDvmData *pDvmData, long nIndex)
{
	return NULL;
}

void CDvmCmpDsPropGridCtrl::NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsMapPropGridProperty *pParent)
{
	
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
		return;
	}

	CDvmCmpPropGridProperty *pProp = (CDvmCmpPropGridProperty*)pMapObj->m_pMap->m_dwItemData;

	if (pProp == NULL)
	{
		return;
	}

	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = TRUE;
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp);
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp);
	m_pDvmCmpBasePropGridCtrlRef->SetCurSel(pProp);
	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = FALSE;
}


BEGIN_MESSAGE_MAP(CDvmCmpDsStandPropGridCtrl, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()

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
	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)m_listDvmDsMapStand.GetHead();
	CDvmDataset *pDataset = (CDvmDataset*)pDatasetMap->m_pStand;
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmCmpDsMapPropGridProperty* pPropData = NULL;

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


CDvmCmpDsMapPropGridProperty* CDvmCmpDsStandPropGridCtrl::NewDvmDataProp(CDvmData *pDvmData, long nIndex)
{
	CDvmCmpDsMapPropGridProperty* pPropData = NULL;
	CString strName;
	strName.Format(_T("%03d  %s"), nIndex, pDvmData->m_strName);

	if (pDvmData->GetCount() == 0)
	{
		pPropData = new CDvmCmpDsMapPropGridProperty(strName, _T(""), _T(""));
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


void CDvmCmpDsStandPropGridCtrl::NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsMapPropGridProperty *pParent)
{
	POS pos = pDvmValues->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmValue *pDest = NULL;
	CDvmCmpDsMapPropGridProperty *pProp = NULL;
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
				pProp = new CDvmCmpDsMapPropGridProperty(pValue->m_strID, _T(""), _T(""));
			}
			else
			{
				if (pValueMap->m_pMap != NULL)
				{
					pProp = new CDvmCmpDsMapPropGridProperty(pValue->m_strID, pValueMap->m_pMap->m_strID, _T(""));
				}
				else
				{
					pProp = new CDvmCmpDsMapPropGridProperty(pValue->m_strID, _T(""), _T(""));
				}
			}
		}
		else
		{
			pProp = new CDvmCmpDsMapPropGridProperty(pValue->m_strName);
			NewDvmValuesProp(pValue, pProp);
		}

		pValue->m_dwItemData = (DWORD)pProp;
		pProp->SetData((DWORD)pValue);
		pProp->AllowEdit(FALSE);

		pParent->AddSubItem(pProp);
	}
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

	CDvmCmpPropGridProperty *pProp = (CDvmCmpPropGridProperty*)pMapObj->m_pStand->m_dwItemData;

	if (pProp == NULL)
	{
		return;
	}

	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = TRUE;
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp);
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp);
	m_pDvmCmpBasePropGridCtrlRef->SetCurSel(pProp);
	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = FALSE;
}

BEGIN_MESSAGE_MAP(CDvmCmpDsMapPropGridCtrl, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()


void CDvmCmpDsMapPropGridCtrl::ShowDatasets()
{
	long nCount = m_listDvmDsMapStand.GetCount();
	ASSERT( nCount > 0);

	if (nCount == 0)
	{
		return;
	}

	CDvmCmpDsMapPropGridProperty* pPropDataset = NULL;
	CDvmDatasetMap *pDatasetMap = NULL;
	POS pos = m_listDvmDsMapStand.GetHeadPosition();
	CDvmDataset *pDataset = NULL;

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
			pPropDataset = new CDvmCmpDsMapPropGridProperty(pDataset->m_strID);
			ShowDataset(pDataset, pPropDataset);
			AddProperty(pPropDataset, FALSE, FALSE);
		}
	}

	AdjustLayout();
	Invalidate(FALSE);
}


void CDvmCmpDsMapPropGridCtrl::ShowDataset(CDvmDataset *pDataset, CDvmCmpDsMapPropGridProperty *pParent)
{
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmCmpDsMapPropGridProperty* pPropData = NULL;
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


CDvmCmpDsMapPropGridProperty* CDvmCmpDsMapPropGridCtrl::NewDvmDataProp(CDvmData *pDvmData, long nIndex)
{
	CDvmCmpDsMapPropGridProperty* pPropData = NULL;
	CString strName;
	strName.Format(_T("%03d  %s"), nIndex, pDvmData->m_strName);

	if (pDvmData->GetCount() == 0)
	{
		pPropData = new CDvmCmpDsMapPropGridProperty(strName, _T(""), _T(""));
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

void CDvmCmpDsMapPropGridCtrl::NewDvmValuesProp(CExBaseList *pDvmValues, CDvmCmpDsMapPropGridProperty *pParent)
{
	POS pos = pDvmValues->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmCmpDsMapPropGridProperty *pProp = NULL;
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
			pProp = new CDvmCmpDsMapPropGridProperty(pValue->m_strName);
			NewDvmValuesProp(pValue, pProp);
		}

		pValue->m_dwItemData = (DWORD)pProp;
		pProp->SetData((DWORD)pValue);
		pProp->AllowEdit(FALSE);

		pParent->AddSubItem(pProp);
	}
}
