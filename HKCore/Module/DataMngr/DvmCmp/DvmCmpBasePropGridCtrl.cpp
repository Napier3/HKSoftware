#include "StdAfx.h"
#include "DvmCmpBasePropGridCtrl.h"



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

void CDvmCmpPropGridProperty::SetNameEx(CDvmDatasetMap *pDatasetMap)
{
	CString strName;
	strName = pDatasetMap->GetDvmCmpPropGridPropertyName();
// 	strName.Format(_T("%s_(%s)"), pDatasetMap->m_pStand->m_strName, pDatasetMap->m_pStand->m_strID);
// 
// 	CString strID = pDatasetMap->m_pStand->m_strID;
// 	long nCount = 0;
// 
// 	//对于定值、压板、设备参数数据集，分子为匹配映射的数据个数，分母为目标数据集中数据个数
// 	if (strID.Find(_T("Setting")) >= 0 || strID.Find(_T("Ena")) >= 0 || strID.Find(_T("Parameter")) >= 0)
// 	{
// 		CDvmDataset *pMap = (CDvmDataset *)pDatasetMap->m_pMap;
// 		nCount = pMap->GetCount();
// 	}
// 	else
// 	{
// 		nCount = pDatasetMap->GetCount();
// 	}
// 
// 	long nFullCmpCount = pDatasetMap->GetCount() - pDatasetMap->m_nCmpErrCount;
// 	strName.AppendFormat(_T("------------------%d/%d"), nFullCmpCount, nCount);
	SetName(strName);
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

	CExBaseObject *pObj = (CExBaseObject *)GetData();

	if (pObj->GetClassID() == DMPCLASSID_CDVMDATASETMAP)
	{
		CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap *)pObj;
		BOOL bIsFullMap = pDatasetMap->IsAllMaped();

		if (bIsFullMap)
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("+++%s++++绿色"), pDatasetMap->m_strName);
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("+++%s++++红色"), pDatasetMap->m_strName);
			clrTextOld = pDC->SetTextColor(RGB(255, 0, 0));
		}
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

//  	if (clrTextOld != (COLORREF)-1)
//  	{
//  		pDC->SetTextColor(clrTextOld);
//  	}
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

// 	if (pProp->IsGroup())
// 	{
// 		return NULL;
// 	}

	CExBaseObject  *pData = (CExBaseObject*)pProp->GetData();

	return pData;
}


CExBaseObject*  CDvmCmpBasePropGridCtrl::GetSelectData(UINT nClassID)
{
	CDvmCmpPropGridProperty *pProp = (CDvmCmpPropGridProperty*)GetCurSel();

	if (pProp == NULL)
	{
		return NULL;
	}

	CExBaseObject  *pData = (CExBaseObject*)pProp->GetData();

	if (pData == NULL)
	{
		return NULL;
	}

	if (pData->GetClassID() != nClassID)
	{
		return NULL;
	}

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
