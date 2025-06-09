#include "StdAfx.h"
#include "HdResDatasPropGridCtrl.h"
// #include "..\..\..\Module\TestMacroScript\MacroScriptMngrGlobal.h"
#include "..\..\..\Module\DataMngr\UI\DlgDataGroup.h"
#include "..\..\..\Module\TestMacro\TUnits.h"

#define AFX_PROP_HAS_LIST 0x0001
#define AFX_PROP_HAS_BUTTON 0x0002
#define AFX_PROP_HAS_SPIN 0x0004

#define UNIT_GAP    24

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CHdResDatasPropGridProperty, CMFCPropertyGridProperty)

CHdResDatasPropGridProperty::CHdResDatasPropGridProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
: CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList)
{

}

CHdResDatasPropGridProperty::CHdResDatasPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
													   LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
													   : CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{

}

void CHdResDatasPropGridProperty::SetIsValueList(BOOL b)
{
	m_bIsValueList = b;
}


BOOL CHdResDatasPropGridProperty::OnEdit(LPPOINT lptClick)
{
	BOOL bRet = CMFCPropertyGridProperty::OnEdit(lptClick);

	if (!bRet)
	{
		return bRet;
	}

	if (m_dwFlags & AFX_PROP_HAS_LIST)
	{

	}
	else
	{
		return bRet;
	}

	CDvmData  *oDataPtr = (CDvmData*)GetData();
	ASSERT (oDataPtr != NULL);

	if (oDataPtr == NULL)
	{
		return bRet;
	}

	CString strDataType = oDataPtr->m_strDataType;
	m_pWndCombo->ResetContent();

	return bRet;
}

void CHdResDatasPropGridProperty::SetCombBoxType()
{
	m_dwFlags = AFX_PROP_HAS_LIST;
}

void CHdResDatasPropGridProperty::SetButtonType()
{
	m_dwFlags = AFX_PROP_HAS_BUTTON;
}


void CHdResDatasPropGridProperty::OnClickButton(CPoint point)
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndList);
	ASSERT_VALID(m_pWndInPlace);
	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	CDvmData  *oDataPtr = (CDvmData*)GetData();

	ASSERT (oDataPtr != NULL);
	m_bButtonIsDown = TRUE;
	Redraw();

}

void CHdResDatasPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
{
	rect.right -= UNIT_GAP;
	CMFCPropertyGridProperty::OnDrawValue(pDC, rect);

	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pWndList);

	if ((IsGroup() && !m_bIsValueList) || !HasValueField())
	{
		return;
	}

	CDvmData *pData = (CDvmData*)m_dwData;

	if (pData == NULL)
	{
		return;
	}

	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return;
	}

	if (pData->m_strUnit.GetLength() == 0)
	{
		return;
	}

	if (pData->m_strUnit == _T("无"))
	{
		return;
	}

	rect.DeflateRect(AFX_TEXT_MARGIN, 0);
	rect.left = rect.right;
	rect.right = rect.left + UNIT_GAP;

	CString strUnit = CTUnits::unit_xlang_TranslateUnit(pData->m_strUnit);
	pDC->DrawText(strUnit, rect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

}


void CHdResDatasPropGridProperty::OnDrawDescription(CDC* pDC, CRect rect)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pWndList);
	CDvmData *pData = (CDvmData*)m_dwData;

	//ASSERT (pData != NULL);
	CString strText;

	if (pData != NULL)
	{
		CHdResDatasPropGridCtrl *pGridCtrl = (CHdResDatasPropGridCtrl*)m_pWndList;
		pGridCtrl->m_oExprTextUnitList->SetExprScript(pData->m_strValue);
		strText = pGridCtrl->m_oExprTextUnitList->GetExprScriptText();
	}

	//HFONT hOldFont = (HFONT) ::SelectObject(pDC->GetSafeHdc(), m_pWndList->m_fontBold.GetSafeHandle());
	int nHeight = pDC->DrawText(strText, rect, DT_SINGLELINE | DT_NOPREFIX);

	//::SelectObject(pDC->GetSafeHdc(), hOldFont);

	rect.top += nHeight + 2;

	pDC->DrawText(m_strDescr, rect, DT_WORDBREAK | DT_NOPREFIX | DT_END_ELLIPSIS);
}

CWnd* CHdResDatasPropGridProperty::CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat)
{
	rectEdit.right -= UNIT_GAP;
	return CMFCPropertyGridProperty::CreateInPlaceEdit(rectEdit, bDefaultFormat);
}

void CHdResDatasPropGridProperty::SetValue(const COleVariant& varValue)
{
	CMFCPropertyGridProperty::SetValue(varValue);
	//SetModifiedFlag();
}

void CHdResDatasPropGridProperty::SetModifyFlagEx(BOOL bFlag)
{
	m_bIsModified = bFlag;
}

CHdResDatasPropGridCtrl::CHdResDatasPropGridCtrl()
{	
	m_pItemHdResDatasPropGridCtrl = NULL;
	m_oExprTextUnitList = new CExprTextUnitList();
	m_clrLine = RGB(128, 128, 128);
	m_pDataTypesRef = NULL;
	m_pDataGroup = NULL;
	m_pItemHdResDatasPropGridCtrl = NULL;
}

CHdResDatasPropGridCtrl::~CHdResDatasPropGridCtrl()
{
	delete m_oExprTextUnitList;
	m_oExprTextUnitList = NULL;
}




void CHdResDatasPropGridCtrl::OnPropertyChanged(CMFCPropertyGridProperty* pProp) const
{
	if (Gb_IsReadOnly((CExBaseObject*)m_pItemHdResDatasPropGridCtrl))
	{
		return;
	}

	CMFCPropertyGridCtrl::OnPropertyChanged(pProp);
	ASSERT_VALID(this);
	ASSERT_VALID(pProp);

	CDvmData  *pData = (CDvmData*)pProp->GetData();

	if (pData == NULL)
	{
		return;
	}

	CString bstrDataTypeID = pData->m_strDataType;
	CString strValue;
	CString strText = pProp->FormatProperty();

	{
		strValue = strText;
	}

	pData->m_strValue = strValue;
	pProp->Redraw();
}

void CHdResDatasPropGridCtrl::UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) const 
{

}

void CHdResDatasPropGridCtrl::UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) 
{

}

void CHdResDatasPropGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
{
	CWnd *pParent = GetParent();

	if (pNewSel == NULL)
	{
		pParent->PostMessage(WM_MACRO_PARA_SEL_CHANGED, (WPARAM)0, (LPARAM)0);
	}
	else
	{
		pParent->PostMessage(WM_MACRO_PARA_SEL_CHANGED, (WPARAM)pNewSel->GetData(), (LPARAM)pNewSel->GetData());
	}
}

void CHdResDatasPropGridCtrl::SetHdResDatasPropGridCtrlDatas(CDataGroup  *pDataGroup)
{
	m_bAllowEditPara = (m_pItemHdResDatasPropGridCtrl != NULL);
	m_pDataGroup = pDataGroup;
	RemoveAll();

	if (m_pDataGroup == NULL)
	{
		return;
	}

	SetHdResDatasPropGridCtrlDatasRoot(m_pDataGroup);

	AdjustLayout();
	Invalidate(FALSE);
}

void CHdResDatasPropGridCtrl::SetHdResDatasPropGridCtrlDatas(CDataGroup  *pDatas, CHdResDatasPropGridProperty *pParent)
{
	CHdResDatasPropGridProperty *pPropValue = new CHdResDatasPropGridProperty(pDatas->m_strName);
	pDatas->m_dwItemData = (DWORD)pPropValue;

	if (pParent == NULL)
	{
		AddProperty(pPropValue, FALSE, FALSE);
	}
	else
	{
		pParent->AddSubItem(pPropValue);
	}

	POS pos = pDatas->GetHeadPosition();
	CDvmData  *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)pDatas->GetNext(pos);
		ShowValData(pData, pPropValue);
	}
}

void CHdResDatasPropGridCtrl::SetHdResDatasPropGridCtrlDatasRoot(CDataGroup  *pDataGroup)
{
	POS pos = pDataGroup->GetHeadPosition();
	CDvmData  *pData = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pDataGroup->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			SetHdResDatasPropGridCtrlDatas((CDataGroup*)p, NULL);
		}
		else if (nClassID == DVMCLASSID_CDVMDATA)
		{
			pData = (CDvmData*)p;
			ShowValData(pData, NULL);
		}
		else
		{
			ASSERT (FALSE);
		}
	}
}

void CHdResDatasPropGridCtrl::InitSetValueText(CString &strText, CDvmData  *pData)
{
	if (!DS_InStringDataPath(strText))
	{
		return;
	}

	CDevice *pDevice = (CDevice*)GetDevice();
	strText = pData->m_strValue;
	CDataObj *pSet = pDevice->FindDataObjByID(strText, -1);

	if (pSet != NULL)
	{
		//CCpu *pCpu = (CCpu*)pSet->GetAncestor(GBCLASSID_CPU);
		strText = pSet->m_strName;
		//strText.Format(_T("%s(%s)"), pSet->m_strName, pCpu->m_strID);
	}
}

BOOL CHdResDatasPropGridCtrl::IsDropList(CDvmData  *pData)
{
	return FALSE;
}
BOOL CHdResDatasPropGridCtrl::IsButton(CDvmData  *pData)
{
	return FALSE;
}

CString CHdResDatasPropGridCtrl::GetValueText(CDvmData  *pData, const CString &strValue)
{
	CString bstrDataTypeID = pData->m_strDataType;
	CString strText;

	strText = strValue;

	return strText;
}

BOOL CHdResDatasPropGridCtrl::ShowValData(CDvmData  *pData, CHdResDatasPropGridProperty *pParent)
{
	CString strValue = GetValueText(pData, pData->m_strValue);
	CString strDefValue = GetValueText(pData, pData->m_strDefaultValue);
	CHdResDatasPropGridProperty *pPropValue = new CHdResDatasPropGridProperty(pData->m_strName, strDefValue, _T(""));
	pData->m_dwItemData = (DWORD)pPropValue;

	if (IsDropList(pData))
	{
		pPropValue->SetCombBoxType();
	}
	else if (IsButton(pData))
	{
		pPropValue->SetButtonType();
	}

	pPropValue->SetData((DWORD_PTR)pData);

	if (pParent == NULL)
	{
		AddProperty(pPropValue, FALSE, FALSE);
	}
	else
	{
		pParent->AddSubItem(pPropValue);
	}

	pPropValue->SetModifyFlagEx(pData->m_strValue != pData->m_strDefaultValue);
	pPropValue->SetValue(strValue);

	pPropValue->Enable(IsValDataEnable(pData));
	pPropValue->AllowEdit(m_bAllowEditPara);

	return pPropValue->IsModified();
}

BOOL CHdResDatasPropGridCtrl::IsCurrDataEnable()
{
	CHdResDatasPropGridProperty *pProp = (CHdResDatasPropGridProperty*)GetCurSel();

	if (pProp == NULL)
	{
		return FALSE;
	}

	return pProp->IsEnabled();
}

CDvmData*  CHdResDatasPropGridCtrl::SetItemValue(const CString &strValue)
{
	CHdResDatasPropGridProperty *pProp = (CHdResDatasPropGridProperty*)GetCurSel();

	if (!pProp->IsEnabled())
	{
		return NULL;
	}

	CDvmData  *pData = GetSelectData();

	if (pData == NULL)
	{
		return pData;
	}

	CString strValue2, strText;
 	strText = strValue;
 	pData->m_strValue = strText;

	pProp->AllowEdit(TRUE);
	pProp->SetValue(strText);

	return pData;
}

CDvmData*  CHdResDatasPropGridCtrl::GetData(int nRow)
{
	if (IsCurrDataEnable())
	{
		return GetSelectData();
	}
	else
	{
		return NULL;
	}
}


CDvmData*  CHdResDatasPropGridCtrl::GetSelectData()
{
	CHdResDatasPropGridProperty *pProp = (CHdResDatasPropGridProperty*)GetCurSel();

	if (pProp == NULL)
	{
		return NULL;
	}

	if (pProp->IsGroup())
	{
		return NULL;
	}

	CDvmData  *pData = (CDvmData*)pProp->GetData();

	return pData;
}

void CHdResDatasPropGridCtrl::ShowColumnTitle()
{
	
}

void CHdResDatasPropGridCtrl::SetGridRows()
{
	
}

void CHdResDatasPropGridCtrl::GetEditTextValue(CString &strText, CString &strValue, CDvmData *pPara)
{
	//数字
	if (IsStringNumber(strText))
	{
		strValue = strText;
		return;
	}

	strValue = strText;
	
}


BEGIN_MESSAGE_MAP(CHdResDatasPropGridCtrl, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()


void CHdResDatasPropGridCtrl::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)
{

}
