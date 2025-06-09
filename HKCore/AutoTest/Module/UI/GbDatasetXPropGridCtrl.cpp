#include "StdAfx.h"
#include "GbDatasetXPropGridCtrl.h"
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


IMPLEMENT_DYNAMIC(CGbDatasetXPropGridCtrlProperty, CMFCPropertyGridProperty)

CGbDatasetXPropGridCtrlProperty::CGbDatasetXPropGridCtrlProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
: CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList)
{

}

CGbDatasetXPropGridCtrlProperty::CGbDatasetXPropGridCtrlProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
													   LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
													   : CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{

}

void CGbDatasetXPropGridCtrlProperty::SetIsValueList(BOOL b)
{
	m_bIsValueList = b;
}


// BOOL CGbDatasetXPropGridCtrlProperty::OnEdit(LPPOINT lptClick)
// {
// 	BOOL bRet = CMFCPropertyGridProperty::OnEdit(lptClick);
// 
// 	if (!bRet)
// 	{
// 		return bRet;
// 	}
// 
// 	if (m_dwFlags & AFX_PROP_HAS_LIST)
// 	{
// 		//m_pWndCombo->ResetContent();
// // 		m_pWndCombo->AddString(_T("Test333"));
// 	}
// 	else
// 	{
// 		return bRet;
// 	}
// 
// 	CDataObj  *oDataPtr = (CDataObj*)GetData();
// 	ASSERT (oDataPtr != NULL);
// 
// 	if (oDataPtr == NULL)
// 	{
// 		return bRet;
// 	}
// 
// 	CString strDataType = oDataPtr->m_strDataType;
// 	m_pWndCombo->ResetContent();
// 
// 	if (IsComboMacroTestDataType(strDataType))
// 	{
// 		//CDataTypes *pDataTypes = CGbDataTypeMngr::GetMacroTestDataTypes();
// 		CDataTypes *pDataTypes = ((CGbDatasetXPropGridCtrlCtrl*)m_pWndList)->m_pDataTypesRef;
// 		//CDataType *pDataType = (CDataType*)pDataTypes->FindByID(strDataType);
// 		
// 		//从m_pParent获得数据类型
// 		CGbDatasetXPropGridCtrlCtrl *pGridCtrl = (CGbDatasetXPropGridCtrlCtrl*)m_pWndList;
// 		CDataType *pDataType = Gb_GetDataType(pGridCtrl->GettemMacroTest(), pDataTypes, strDataType);
// 		//CDataType *pDataType = CMtDataTypeMngr::FindDataType(pDataTypes, strDataType);
// 
// 		if (pDataType != NULL)
// 		{
// 			InsertDataTypeToComboBox(pDataType, m_pWndCombo);
// 		}
// 	}
// 	else
// 	{
// 
// 	}
// 
// 	return bRet;
// }

void CGbDatasetXPropGridCtrlProperty::SetCombBoxType()
{
	m_dwFlags = AFX_PROP_HAS_LIST;
}

void CGbDatasetXPropGridCtrlProperty::SetButtonType()
{
	m_dwFlags = AFX_PROP_HAS_BUTTON;
}

// 
// void CGbDatasetXPropGridCtrlProperty::OnClickButton(CPoint point)
// {
// 	ASSERT_VALID(this);
// 	ASSERT_VALID(m_pWndList);
// 	ASSERT_VALID(m_pWndInPlace);
// 	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));
// 
// 	CDataObj  *oDataPtr = (CDataObj*)GetData();
// 
// 	ASSERT (oDataPtr != NULL);
// 	if (oDataPtr->m_strDataType != CMtDataTypeMngr::g_strMtDataType_ConfigFile)
// 	{
// 		CMFCPropertyGridProperty::OnClickButton(point);
// 		return;
// 	}
// 
// 	m_bButtonIsDown = TRUE;
// 	Redraw();
// 
// 
// 	if (oDataPtr == NULL)
// 	{
// 		m_bButtonIsDown = FALSE;
// 		return;
// 	}
// 
// 	if (oDataPtr->m_strDataType != CMtDataTypeMngr::g_strMtDataType_ConfigFile)
// 	{
// 		m_bButtonIsDown = FALSE;
// 		return;
// 	}
// 
// 	CString strFile;
// 	strFile = _P_GetConfigPath();
// 	strFile.AppendFormat(_T("%s.xml"), oDataPtr->m_strID);
// 
// 	if (!::IsFileExist(strFile))
// 	{
// 		m_bButtonIsDown = FALSE;
// 		return;
// 	}
// 
// 	CDlgDataGroup dlg(strFile, oDataPtr->m_strValue);
// 
// 	if (dlg.DoModal() == IDCANCEL)
// 	{
// 		m_bButtonIsDown = FALSE;
// 		return;
// 	}
// 
// 	oDataPtr->m_strValue = dlg.m_strDatas;
// 
// 	if (m_pWndInPlace != NULL)
// 	{
// 		m_pWndInPlace->SetWindowText(oDataPtr->m_strValue);
// 	}
// 
// 	m_varValue = (LPCTSTR) oDataPtr->m_strValue;
// 
// 	m_bButtonIsDown = FALSE;
// 	Redraw();
// 
// 	if (m_pWndInPlace != NULL)
// 	{
// 		m_pWndInPlace->SetFocus();
// 	}
// 	else
// 	{
// 		m_pWndList->SetFocus();
// 	}
// }
// 
// void CGbDatasetXPropGridCtrlProperty::OnDrawValue(CDC* pDC, CRect rect)
// {
// 	rect.right -= UNIT_GAP;
// 	CMFCPropertyGridProperty::OnDrawValue(pDC, rect);
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
// 	CDataObj *pData = (CDataObj*)m_dwData;
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
// 
// 	CString strUnit = CTUnits::unit_xlang_TranslateUnit(pData->m_strUnit);
// 	pDC->DrawText(strUnit, rect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);
// 
// }
// 
// 
// void CGbDatasetXPropGridCtrlProperty::OnDrawDescription(CDC* pDC, CRect rect)
// {
// 	ASSERT_VALID(this);
// 	ASSERT_VALID(pDC);
// 	ASSERT_VALID(m_pWndList);
// 	CDataObj *pData = (CDataObj*)m_dwData;
// 
// 	//ASSERT (pData != NULL);
// 	CString strText;
// 
// 	if (pData != NULL)
// 	{
// 		CGbDatasetXPropGridCtrlCtrl *pGridCtrl = (CGbDatasetXPropGridCtrlCtrl*)m_pWndList;
// 		pGridCtrl->m_oExprTextUnitList->SetExprScript(pData->m_strValue);
// 		strText = pGridCtrl->m_oExprTextUnitList->GetExprScriptText();
// 	}
// 
// 	//HFONT hOldFont = (HFONT) ::SelectObject(pDC->GetSafeHdc(), m_pWndList->m_fontBold.GetSafeHandle());
// 	int nHeight = pDC->DrawText(strText, rect, DT_SINGLELINE | DT_NOPREFIX);
// 
// 	//::SelectObject(pDC->GetSafeHdc(), hOldFont);
// 
// 	rect.top += nHeight + 2;
// 
// 	pDC->DrawText(m_strDescr, rect, DT_WORDBREAK | DT_NOPREFIX | DT_END_ELLIPSIS);
// }

CWnd* CGbDatasetXPropGridCtrlProperty::CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat)
{
	rectEdit.right -= UNIT_GAP;
	return CMFCPropertyGridProperty::CreateInPlaceEdit(rectEdit, bDefaultFormat);
}

void CGbDatasetXPropGridCtrlProperty::SetValue(const COleVariant& varValue)
{
	CMFCPropertyGridProperty::SetValue(varValue);
	//SetModifiedFlag();
}

void CGbDatasetXPropGridCtrlProperty::SetModifyFlagEx(BOOL bFlag)
{
	m_bIsModified = bFlag;
}

//////////////////////////////////////////////////////////////////////////
//CGbDatasetXPropGridCtrlCtrl
CGbDatasetXPropGridCtrl::CGbDatasetXPropGridCtrl()
{	
	m_oExprTextUnitList = new CExprTextUnitList();
	m_clrLine = RGB(128, 128, 128);
	m_pDataTypesRef = NULL;
	m_pDataSet = NULL;
}

CGbDatasetXPropGridCtrl::~CGbDatasetXPropGridCtrl()
{
	delete m_oExprTextUnitList;
	m_oExprTextUnitList = NULL;
}




void CGbDatasetXPropGridCtrl::OnPropertyChanged(CMFCPropertyGridProperty* pProp) const
{
	CMFCPropertyGridCtrl::OnPropertyChanged(pProp);
	ASSERT_VALID(this);
	ASSERT_VALID(pProp);

	CExBaseObject  *pData = (CDataObj*)pProp->GetData();

	if (pData == NULL)
	{
		return;
	}

	//CString bstrDataTypeID = pData->m_strDataType;
	CString strText = pProp->FormatProperty();

	if (pData->GetClassID() == GBCLASSID_DATAOBJ)
	{
		((CDataObj*)pData)->m_strValue = strText;
	}
	else
	{
		((CDataObjValue*)pData)->m_strValue = strText;
	}

	//是否关联了CValue
	if (pData->m_dwReserved != 0 && pData->m_dwReserved != 0x0FFFFFFF)
	{
		CValue *pValue = (CValue*)pData->m_dwReserved;
		if (pValue->GetClassID() == DTMCLASSID_CVALUE)
		{
			pValue->m_strValue = strText;
		}
	}

	pProp->Redraw();
}

void CGbDatasetXPropGridCtrl::UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) const 
{
	POS pos = listDelete.GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CMFCPropertyGridProperty *pProp = NULL;
	CMFCPropertyGridProperty *pPropParent = NULL;
	CGbDatasetXPropGridCtrl *pTempProp = (CGbDatasetXPropGridCtrl*)this;

	while (pos != NULL)
	{
		pObj = listDelete.GetNext(pos);
		pProp = (CMFCPropertyGridProperty *)pObj->m_dwItemData;
		pPropParent = (CMFCPropertyGridProperty*)pProp->GetParent();

		if(pPropParent == NULL)
		{
			pTempProp->DeleteProperty(pProp);
		}
		else
		{
			pPropParent->RemoveSubItem(pProp);
		}
	}

	pProp = GetCurSel();

	if (pProp == NULL)
	{
		return;
	}

	pPropParent = (CMFCPropertyGridProperty*)pProp->GetParent();
	pos = listNew.GetHeadPosition();
	CExBaseObject *pObjParent = NULL;

	while (pos != NULL)
	{
		pObj = listNew.GetNext(pos);
		pObjParent = (CExBaseObject *)pObj->GetParent();
		pPropParent = (CMFCPropertyGridProperty*)pObjParent->m_dwItemData;

		if (pObj->GetClassID() == GBCLASSID_DATASETGROUP)
		{
			pTempProp->InsertGbDatasetGroup((CDataSetGroup*)pObj, (CGbDatasetXPropGridCtrlProperty*)pPropParent);
		}
		else
		{
			ASSERT(FALSE);
			pTempProp->ShowValData((CDataObj*)pObj, (CGbDatasetXPropGridCtrlProperty *)pPropParent);
		}

	}
}

void CGbDatasetXPropGridCtrl::UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) 
{

}

void CGbDatasetXPropGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
{
	CWnd *pParent = GetParent();



	if (pNewSel == NULL)
	{
		pParent->PostMessage(WM_GBSET_SEL_CHANGED, (WPARAM)0, (LPARAM)0);
	}
	else
	{
		pParent->PostMessage(WM_GBSET_SEL_CHANGED, (WPARAM)pNewSel->GetData(), (LPARAM)pNewSel->GetData());
	}
}


void CGbDatasetXPropGridCtrl::ShowDatas(CExBaseList *pDatas, BOOL bAllowEditPara)
{
	if (pDatas == NULL)
	{
		RemoveAll();
		AdjustLayout();
		Invalidate(FALSE);
		return;
	}

	UINT nClassID = pDatas->GetClassID();

	if (GBCLASSID_DATASET != nClassID && GBCLASSID_DATASETGROUP != nClassID)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("GbDatasetXPropGridCtrl::ShowDatas : error......"));
		RemoveAll();
		AdjustLayout();
		Invalidate(FALSE);
		return;
	}

	ShowGbDataset((CDataSet*)pDatas, bAllowEditPara);
}

void CGbDatasetXPropGridCtrl::GetCurrSelDatas(CExBaseList &oList, long nCol)
{
	CDataObj *pSel = GetSelectData();

	if (pSel != NULL)
	{
		oList.AddTail(pSel);
	}
}

void CGbDatasetXPropGridCtrl::Filter(const CString &strFilter)
{

}

void CGbDatasetXPropGridCtrl::ShowGbDataset(CDataSet  *pDataSet, BOOL bAllowEditPara)
{
	m_bAllowEditPara = bAllowEditPara;
	m_pDataSet = pDataSet;
	RemoveAll();

	if (pDataSet != NULL)
	{
		SetGbDatasetRoot(pDataSet);
	}

	AdjustLayout();
	Invalidate(FALSE);
}

void CGbDatasetXPropGridCtrl::SetGbDatasetRoot(CDataSet  *pDataSet)
{
	POS pos = pDataSet->GetHeadPosition();
	CDataObj  *pData = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pDataSet->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_DATASETGROUP)
		{
			InsertGbDatasetGroup((CDataSetGroup*)p, NULL);
		}
		else if (nClassID == GBCLASSID_DATAOBJ)
		{
			pData = (CDataObj*)p;
			ShowValData(pData, NULL);
		}
		else
		{
			ASSERT (FALSE);
		}
	}
}

void CGbDatasetXPropGridCtrl::InsertGbDatasetGroup(CDataSetGroup  *pDataGroup, CGbDatasetXPropGridCtrlProperty *pParent)
{
	CGbDatasetXPropGridCtrl *pTempProp = (CGbDatasetXPropGridCtrl*)this;
	CGbDatasetXPropGridCtrlProperty* pGroupProp = NULL;
	
	if (pDataGroup->m_strType == _T("channel"))
	{
		pGroupProp = new CGbDatasetXPropGridCtrlProperty(pDataGroup->m_strName, 0, TRUE);
	}
	else
	{
		pGroupProp = new CGbDatasetXPropGridCtrlProperty(pDataGroup->m_strName);
	}

	pDataGroup->m_dwItemData = (DWORD)pGroupProp;
	pGroupProp->SetData((DWORD)pDataGroup);

	POS pos = pDataGroup->GetHeadPosition();
	CDataObj  *pData = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	BOOL bModified = FALSE;

	while (pos != NULL)
	{
		p = pDataGroup->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_DATASETGROUP)
		{
			//CGbDatasetXPropGridCtrlProperty* pGroup = new CGbDatasetXPropGridCtrlProperty(p->m_strName);
			//p->m_dwItemData = (DWORD)pGroup;
			InsertGbDatasetGroup((CDataSetGroup*)p, pGroupProp);

// 			if (pParent == NULL)
// 			{
// 				AddProperty(pGroup, FALSE, FALSE);
// 			}
// 			else
// 			{
// 				pParent->AddSubItem(pGroup);
// 			}
		}
		else if (nClassID == GBCLASSID_DATAOBJ)
		{
			pData = (CDataObj*)p;

			if(  ShowValData(pData, pGroupProp) )
			{
				bModified = TRUE;
			}
		}
		else
		{
			ASSERT (FALSE);
		}
	}

	pGroupProp->Expand(TRUE);

	if (pParent == NULL)
	{
		pTempProp->AddProperty(pGroupProp);
	}
	else
	{
		pParent->AddSubItem(pGroupProp);
	}

	pGroupProp->SetModifyFlagEx(bModified);
}

void CGbDatasetXPropGridCtrl::InitSetValueText(CString &strText, CDataObj  *pData)
{
	if (!DS_InStringDataPath(strText))
	{
		return;
	}

// 	CDevice *pDevice = (CDevice*)GetDevice();
// 	strText = pData->m_strValue;
// 	CDataObj *pSet = pDevice->FindDataObjByID(strText, -1);
// 
// 	if (pSet != NULL)
// 	{
// 		//CCpu *pCpu = (CCpu*)pSet->GetAncestor(GBCLASSID_CPU);
// 		strText = pSet->m_strName;
// 		//strText.Format(_T("%s(%s)"), pSet->m_strName, pCpu->m_strID);
// 	}
}

BOOL CGbDatasetXPropGridCtrl::IsDropList(CDataObj  *pData)
{
// 	CString bstrDataTypeID = pData->m_strDataType;
// 
// 	if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_IECConfig)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_ComtradeFile)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (IsComboMacroTestDataType(bstrDataTypeID))
// 	{
// 		if (!IsStringNumber(pData->m_strValue))
// 		{
// 			return FALSE;
// 		}
// 		else
// 		{
// 			return TRUE;
// 		}
// 	}
// 	else
	{
		return FALSE;
	}
}
BOOL CGbDatasetXPropGridCtrl::IsButton(CDataObj  *pData)
{
	CString bstrDataTypeID = pData->m_strDataType;

	if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_ConfigFile)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CString CGbDatasetXPropGridCtrl::GetValueText(CDataObj  *pData, const CString &strValue)
{
	CString bstrDataTypeID = pData->m_strDataType;
	CString strText;

	strText = pData->m_strValue;
// 	if (IsComboMacroTestDataType(bstrDataTypeID) && IsStringNumber(strValue))
// 	{
// 		//GetDataTypeNameByValue(CGbDataTypeMngr::GetMacroTestDataTypes(), bstrDataTypeID, strValue, strText);
// 		GetDataTypeNameByValue(m_pDataTypesRef, bstrDataTypeID, strValue, strText);
// 
// 		if (!IsStringNumber(strValue))
// 		{
// #ifdef GUIDEBOOK_DEV_MODE
// 			m_oExprTextUnitList->SetExprScript(strValue);
// 			strText = m_oExprTextUnitList->GetExprScriptText();
// #else
// 			strText = strValue;
// #endif
// 		}
// 	}
// 	else
// 	{
// 		//验证表达式的正确性
// 		if (!IsStringNumber(strValue))
// 		{
// #ifdef GUIDEBOOK_DEV_MODE
// 			m_oExprTextUnitList->SetExprScript(strValue);
// 			strText = m_oExprTextUnitList->GetExprScriptText();
// #else
// 			strText = strValue;
// #endif
// 		}
// 		else
// 		{
// 			strText = strValue;
// 		}
// 	}

	return strText;
}

BOOL CGbDatasetXPropGridCtrl::ShowValData(CDataObj  *pData, CGbDatasetXPropGridCtrlProperty *pParent)
{
	CString strValue = GetValueText(pData, pData->m_strValue);
	CString strDefValue = GetValueText(pData, pData->m_strDefaultValue);
	CGbDatasetXPropGridCtrlProperty *pPropValue = new CGbDatasetXPropGridCtrlProperty(pData->m_strName, strDefValue, _T(""));
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

BOOL CGbDatasetXPropGridCtrl::IsCurrDataEnable()
{
	CGbDatasetXPropGridCtrlProperty *pProp = (CGbDatasetXPropGridCtrlProperty*)GetCurSel();

	if (pProp == NULL)
	{
		return FALSE;
	}

	return pProp->IsEnabled();
}

CDataObj*  CGbDatasetXPropGridCtrl::SetItemValue(const CString &strValue)
{
	CGbDatasetXPropGridCtrlProperty *pProp = (CGbDatasetXPropGridCtrlProperty*)GetCurSel();

	if (!pProp->IsEnabled())
	{
		return NULL;
	}

	CDataObj  *pData = GetSelectData();

	if (pData == NULL)
	{
		return pData;
	}

	CString strValue2, strText;
 	strText = strValue;
 	pData->m_strValue = strText;

	//验证表达式的正确性
	if (!IsStringNumber(strValue))
	{
		strText = strValue;
		pProp->AllowEdit(FALSE);
	}
	else
	{
		pProp->AllowEdit(TRUE);
	}

	pProp->SetValue(strText);

	return pData;
}

CDataObj*  CGbDatasetXPropGridCtrl::GetData(int nRow)
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


CDataObj*  CGbDatasetXPropGridCtrl::GetSelectData()
{
	CGbDatasetXPropGridCtrlProperty *pProp = (CGbDatasetXPropGridCtrlProperty*)GetCurSel();

	if (pProp == NULL)
	{
		return NULL;
	}

	CDataObj  *pData = (CDataObj*)pProp->GetData();

	return pData;
}

void CGbDatasetXPropGridCtrl::ShowColumnTitle()
{
	
}

void CGbDatasetXPropGridCtrl::SetGridRows()
{
	
}

void CGbDatasetXPropGridCtrl::GetEditTextValue(CString &strText, CString &strValue, CDataObj *pPara)
{
	//数字
	if (IsStringNumber(strText))
	{
		strValue = strText;
		return;
	}

	//判断表达式是否有效
	strValue = strText;
	
}


BEGIN_MESSAGE_MAP(CGbDatasetXPropGridCtrl, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()


void CGbDatasetXPropGridCtrl::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)
{

}


//////////////////////////////////////////////////////////////////////////
//
CGbDatasetXPropEditGridCtrl::CGbDatasetXPropEditGridCtrl()
{
	m_pCommCmd	 = NULL;		//关联的数据对象
}

CGbDatasetXPropEditGridCtrl::~CGbDatasetXPropEditGridCtrl()
{

}

void CGbDatasetXPropEditGridCtrl::InitGbDatasetGroup_Values(CExBaseList *pGbDataset, CExBaseList *pValues)
{
	POS pos = pValues->GetHeadPosition();
	CValue *pValue = NULL;
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)pValues->GetNext(pos);
		pData = new CDataObj();
		m_oGbDatasetGroup.AddNewChild(pData);

		if (pValue != NULL)
		{
			pData->m_strName = pValue->m_strName;
			pData->m_strID = pValue->m_strID;
			pData->m_strValue = pValue->m_strValue;
		}

		pData->m_dwReserved = (DWORD)pValue;
		pValue->m_dwReserved = (DWORD)pData;
	}
}

void CGbDatasetXPropEditGridCtrl::InitGbDatasetGroup_Dataset(CExBaseList *pGbDataset, CExBaseList *pValues)
{
	POS pos = NULL;
	CDataObj *pNewData = NULL;
	CExBaseObject *p = NULL;

	CDataSet *pDataset = (CDataSet*)pGbDataset;
	pos = pGbDataset->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CExBaseObject *)pDataset->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATAOBJ)
		{
			CString strID = ((CDataObj*)p)->GetIDPath_Root_Dataset();

			if (pValues->FindByID(strID) != NULL)
			{
				pNewData = AddData((CDataObj*)p, (CValues*)pValues);
			}
		}
		else
		{
			InitGbDatasetGroup_Dataset((CExBaseList*)p, pValues);
		}
	}
}

CDataObj* CGbDatasetXPropEditGridCtrl::AddData(CDataObj *pData, CValue *pValue)
{
	CDataObj *pNewData = NULL;

	if (pData != NULL)
	{
		pNewData = m_oGbDatasetGroup.InsertData(pData);
	}
	else
	{
		pNewData = new CDataObj();
		pNewData->m_strName = pValue->m_strName;
		pNewData->m_strID = pValue->m_strID;
		m_oGbDatasetGroup.AddNewChild(pNewData);
	}

	pNewData->m_strValue = pValue->m_strValue;
	pNewData->m_dwReserved = (DWORD)pValue;
	pValue->m_dwReserved = (DWORD)pNewData;

	return pNewData;
}

CDataObj* CGbDatasetXPropEditGridCtrl::AddData(CDataObj *pData, CValues *pValues)
{
	CDataObj *pNewData = NULL;

	if (pData != NULL)
	{
		pNewData = m_oGbDatasetGroup.InsertData(pData);
	}
	else
	{
		pNewData = new CDataObj();
		m_oGbDatasetGroup.AddNewChild(pNewData);
	}

	pNewData->InitByValues(pValues, TRUE);

	return pNewData;
}
// 
// CDataObjValue* CGbDatasetXPropEditGridCtrl::AddData(CDataObjValue *pDataValue, CValues *pValues)
// {
// 	CValue *pNewValue =  pValues->AddValue(pDataValue->GetIDPath_Root_Dataset(), pDataValue->m_strValue);
// 	pDataValue->m_strValue = pNewValue->m_strValue;
// 	pDataValue->m_dwReserved = (DWORD)pNewValue;
// 	pNewValue->m_dwReserved = (DWORD)pDataValue;
// 
// 	POS pos = pDataValue->GetHeadPosition();
// 	CDataObjValue *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CDataObjValue *)pDataValue->GetNext(pos);
// 		AddData(p, pValues);
// 	}
// 
// 	return NULL;
// }

void CGbDatasetXPropEditGridCtrl::InsertDataToCtrl(CDataObj *pData)
{
	CExBaseList *pParent = (CExBaseList*)pData->GetParent();

	if (pParent->GetClassID() != GBCLASSID_DATASETGROUP)
	{
		ShowValData(pData, NULL);
	}
	else
	{
		CExBaseList listGroup;
		pData->GetAllAncestorEqClassID(&listGroup, GBCLASSID_DATASETGROUP);
		POS pos = listGroup.GetHeadPosition();
		listGroup.GetNext(pos);
		CDataSetGroup *pDataGroup = NULL;
		CGbDatasetXPropGridCtrl *pTempProp = (CGbDatasetXPropGridCtrl*)this;
		CGbDatasetXPropGridCtrlProperty* pGroupProp = NULL;
		CGbDatasetXPropGridCtrlProperty *pParentProp = NULL;

		while (pos != NULL)
		{
			pDataGroup = (CDataSetGroup*)listGroup.GetNext(pos);

			if (pDataGroup->m_dwItemData != 0)
			{
				break;
			}

			pGroupProp = new CGbDatasetXPropGridCtrlProperty(pDataGroup->m_strName);
			pDataGroup->m_dwItemData = (DWORD)pGroupProp;
			pGroupProp->Expand(TRUE);

			if (pParentProp == NULL)
			{
				pTempProp->AddProperty(pGroupProp);
			}
			else
			{
				pParentProp->AddSubItem(pGroupProp);
			}

			pParentProp = pGroupProp;
		}

		pGroupProp = (CGbDatasetXPropGridCtrlProperty*)pParent->m_dwItemData;
		ShowValData(pData, pGroupProp);
		listGroup.RemoveAll();
	}

	AdjustLayout();
	Invalidate(FALSE);
}


void CGbDatasetXPropEditGridCtrl::InitGbDatasetGroup_List(CExBaseList *pGbDataset, CExBaseList *pValues)
{
	CExBaseObject *p = NULL;
	POS pos = pGbDataset->GetHeadPosition();
	CValue *pValue = NULL;
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		p = pGbDataset->GetNext(pos);
		pValue = (CValue *)pValues->FindByID(p->m_strID);
		pData = new CDataObj();
		m_oGbDatasetGroup.AddNewChild(pData);

		if (pValue != NULL)
		{
			pData->m_strName = pValue->m_strName;
			pData->m_strID = pValue->m_strID;
			pData->m_strValue = pValue->m_strValue;
			pData->m_dwReserved = (DWORD)pValue;
			pValue->m_dwReserved = (DWORD)pData;
		}
		else
		{
			pData->m_strName = p->m_strName;
			pData->m_strID = p->m_strID;
		}
	}

}

void CGbDatasetXPropEditGridCtrl::InitGbDatasetGroup(CExBaseList *pGbDataset, CExBaseList *pValues)
{
	m_oGbDatasetGroup.DeleteAll();

	if (pGbDataset == NULL)
	{
		InitGbDatasetGroup_Values(pGbDataset, pValues);
		return ;
	}

	UINT nClassID = pGbDataset->GetClassID();
	POS pos = NULL;
	CValue *pValue = NULL;
	CDataObj *pData = NULL;

	if (nClassID == GBCLASSID_DATASETGROUP || nClassID == GBCLASSID_DATASET)
	{
		InitGbDatasetGroup_Dataset(pGbDataset, pValues);
	}
	else
	{
		InitGbDatasetGroup_List(pGbDataset, pValues);
	}
}


void CGbDatasetXPropEditGridCtrl::InsertGbDataObjValue(CDataObjValue  *pDataObjValue, CGbDatasetXPropGridCtrlProperty *pParent)
{
	CGbDatasetXPropGridCtrl *pTempProp = (CGbDatasetXPropGridCtrl*)this;
	CGbDatasetXPropGridCtrlProperty* pGroupProp = NULL;

	if (pDataObjValue->GetCount() > 0)
	{
		pGroupProp = new CGbDatasetXPropGridCtrlProperty(pDataObjValue->GetText(), 0, TRUE);
		pGroupProp->Expand(TRUE);
	}
	else
	{
		pGroupProp = new CGbDatasetXPropGridCtrlProperty(pDataObjValue->GetText(), pDataObjValue->m_strValue, _T(""));
	}

	pDataObjValue->m_dwItemData = (DWORD)pGroupProp;
	pGroupProp->SetData((DWORD)pDataObjValue);
	pGroupProp->SetModifyFlagEx(FALSE);

	POS pos = pDataObjValue->GetHeadPosition();
	CDataObjValue  *pDataValue = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	BOOL bModified = FALSE;
	pGroupProp->AllowEdit(TRUE);

	while (pos != NULL)
	{
		p = pDataObjValue->GetNext(pos);
		InsertGbDataObjValue((CDataObjValue*)p, pGroupProp);
	}


	if (pParent == NULL)
	{
		pTempProp->AddProperty(pGroupProp);
	}
	else
	{
		pParent->AddSubItem(pGroupProp);
	}

	pGroupProp->SetModifyFlagEx(bModified);
}

BOOL CGbDatasetXPropEditGridCtrl::ShowValData(CDataObj  *pData, CGbDatasetXPropGridCtrlProperty *pParent)
{
	if (pData->GetCount() == 0)
	{
		return CGbDatasetXPropGridCtrl::ShowValData(pData, pParent);
	}

	CString strValue = GetValueText(pData, pData->m_strValue);
	CString strDefValue = GetValueText(pData, pData->m_strDefaultValue);
	CGbDatasetXPropGridCtrlProperty *pPropData = new CGbDatasetXPropGridCtrlProperty(pData->m_strName);
	pData->m_dwItemData = (DWORD)pPropData;
	pPropData->SetData((DWORD_PTR)pData);
	pPropData->Expand(TRUE);

	if (pParent == NULL)
	{
		this->AddProperty(pPropData);
	}
	else
	{
		pParent->AddSubItem(pPropData);
	}

	pPropData->SetModifyFlagEx(pData->m_strValue != pData->m_strDefaultValue);
	pPropData->SetValue(strValue);

	POS pos = pData->GetHeadPosition();
	CDataObjValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)pData->GetNext(pos);
		InsertGbDataObjValue(pValue, pPropData);
	}

	return TRUE;
}

void CGbDatasetXPropEditGridCtrl::ShowDatas(CExBaseList *pGbDataset, CExBaseList *pValues)
{
	m_bAllowEditPara = TRUE;
	RemoveAll();

	if(pGbDataset == NULL && pValues == NULL)
	{
		return;
	}

	InitGbDatasetGroup(pGbDataset, pValues);
	SetGbDatasetRoot(&m_oGbDatasetGroup);

	AdjustLayout();
	Invalidate(FALSE);
}

void CGbDatasetXPropEditGridCtrl::InsertData(CDataObj *pData, CValue *pValue)
{
	CDataObj *pNewData = AddData(pData, pValue);
	InsertDataToCtrl(pNewData);
}

void CGbDatasetXPropEditGridCtrl::InsertData(CDataObj *pData, CValues *pValues)
{
	CDataObj *pNew = m_oGbDatasetGroup.InsertData(pData);
	pNew->InitByValues(pValues, TRUE);
	InsertDataToCtrl(pNew);
}

void CGbDatasetXPropEditGridCtrl::SetItemText(long nRow, long nCol, const CString &strText)
{
	
}


void CGbDatasetXPropEditGridCtrl::DeleteSelRows_Data(CDataObj *pData)
{
	CValue *pValue = (CValue*)pData->m_dwReserved;

	if (pValue == NULL)
	{
		return;
	}

	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)(pData->m_dwItemData);
	CMFCPropertyGridProperty *pPropParent = (CMFCPropertyGridProperty*)pProp->GetParent();

	if(pPropParent == NULL)
	{
		DeleteProperty(pProp);
	}
	else
	{
		pPropParent->RemoveSubItem(pProp);
	}

	CExBaseList *pParent = (CExBaseList*)pData->GetParent();
	CString strID = pData->GetIDPath_Root_Dataset();
	pParent->Delete(pData);

	CValues *pValues = (CValues*)pValue->GetParent();
	POS pos = pValues->GetHeadPosition();
	strID += _T("$");
	POS posPrev = NULL;
	pValues->Delete(pValue);

	while (pos != NULL)
	{
		posPrev = pos;
		pValue = (CValue *)pValues->GetNext(pos);

		if (pValue->m_strID.Find(strID) >= 0)
		{
			pValues->DeleteAt(posPrev);
		}
	}
}

void CGbDatasetXPropEditGridCtrl::DeleteSelRows_DataGroup(CDataSetGroup *pDataGroup)
{
	POS pos = pDataGroup->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pDataGroup->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATAOBJ)
		{
			DeleteSelRows_Data((CDataObj*)p);
		}
		else
		{
			DeleteSelRows_DataGroup((CDataSetGroup*)p);
		}
	}
}

void CGbDatasetXPropEditGridCtrl::DeleteSelRows(BOOL bDeleteData, int nStateForCol)
{
	CDataObj *pData = GetSelectData();

	if (pData == NULL)
	{
		return;
	}

	if (pData->GetClassID() == GBCLASSID_DATAOBJ)
	{
		DeleteSelRows_Data(pData);
	}
	else
	{
		CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)(pData->m_dwItemData);
		CMFCPropertyGridProperty *pPropParent = (CMFCPropertyGridProperty*)pProp->GetParent();

		DeleteSelRows_DataGroup((CDataSetGroup*)pData);

		if(pPropParent == NULL)
		{
			DeleteProperty(pProp);
		}
		else
		{
			pPropParent->RemoveSubItem(pProp);
		}
	}

	AdjustLayout();
	Invalidate(FALSE);
}

long CGbDatasetXPropEditGridCtrl::GetRowCount()
{
	return GetPropertyCount();
}

void CGbDatasetXPropEditGridCtrl::UpdateData(CExBaseObject *pData)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID == GBCLASSID_DATAOBJ)
	{
		CDataObj *pDest = (CDataObj*)pData;
		CDataObj *pDataObj = (CDataObj*)(pData->m_dwReserved);
		CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty *)(pDest->m_dwItemData);
		pProp->SetValue(pDest->m_strValue);
	}
	else if (nClassID == DTMCLASSID_CVALUE)
	{
		CValue *pValue = (CValue*)pData;
		CDataObj *pDataObj = (CDataObj*)(pData->m_dwReserved);
		CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty *)(pDataObj->m_dwReserved);
		pProp->SetValue(pValue->m_strValue);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++[CGbDatasetXPropEditGridCtrl::UpdateData]不支持的数据类型+++++"));
	}
	
}

void CGbDatasetXPropEditGridCtrl::AutoSizeColumn(long nCol)
{

}

