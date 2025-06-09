#include "StdAfx.h"
#include "MacroTestDatasPropGridCtrl.h"
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


IMPLEMENT_DYNAMIC(CMacroTestDatasPropGridProperty, CMFCPropertyGridProperty)

CMacroTestDatasPropGridProperty::CMacroTestDatasPropGridProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
: CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList)
{

}

CMacroTestDatasPropGridProperty::CMacroTestDatasPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
													   LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
													   : CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{

}

void CMacroTestDatasPropGridProperty::SetIsValueList(BOOL b)
{
	m_bIsValueList = b;
}


BOOL CMacroTestDatasPropGridProperty::OnEdit(LPPOINT lptClick)
{
	BOOL bRet = CMFCPropertyGridProperty::OnEdit(lptClick);

	if (!bRet)
	{
		return bRet;
	}

	if (m_dwFlags & AFX_PROP_HAS_LIST)
	{
		//m_pWndCombo->ResetContent();
// 		m_pWndCombo->AddString(_T("Test333"));
	}
	else
	{
		return bRet;
	}

	CShortData  *oDataPtr = (CShortData*)GetData();
	ASSERT (oDataPtr != NULL);

	if (oDataPtr == NULL)
	{
		return bRet;
	}

	CString strDataType = oDataPtr->m_strDataTypeID;
	m_pWndCombo->ResetContent();

	if (IsComboMacroTestDataType(strDataType))
	{
		//CDataTypes *pDataTypes = CGbDataTypeMngr::GetMacroTestDataTypes();
		CDataTypes *pDataTypes = ((CMacroTestDatasPropGridCtrl*)m_pWndList)->m_pDataTypesRef;
		//CDataType *pDataType = (CDataType*)pDataTypes->FindByID(strDataType);
		
		//从m_pParent获得数据类型
		CMacroTestDatasPropGridCtrl *pGridCtrl = (CMacroTestDatasPropGridCtrl*)m_pWndList;
		CDataType *pDataType = Gb_GetDataType(pGridCtrl->GettemMacroTest(), pDataTypes, strDataType);
		//CDataType *pDataType = CMtDataTypeMngr::FindDataType(pDataTypes, strDataType);

		if (pDataType != NULL)
		{
			InsertDataTypeToComboBox(pDataType, m_pWndCombo);
		}
	}
	else
	{

	}

	return bRet;
}

void CMacroTestDatasPropGridProperty::SetCombBoxType()
{
	m_dwFlags = AFX_PROP_HAS_LIST;
}

void CMacroTestDatasPropGridProperty::SetButtonType()
{
	m_dwFlags = AFX_PROP_HAS_BUTTON;
}


void CMacroTestDatasPropGridProperty::OnClickButton(CPoint point)
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndList);
	ASSERT_VALID(m_pWndInPlace);
	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	CShortData  *oDataPtr = (CShortData*)GetData();

	ASSERT (oDataPtr != NULL);
	if (oDataPtr->m_strDataTypeID != CMtDataTypeMngr::g_strMtDataType_ConfigFile)
	{
		CMFCPropertyGridProperty::OnClickButton(point);
		return;
	}

	m_bButtonIsDown = TRUE;
	Redraw();


	if (oDataPtr == NULL)
	{
		m_bButtonIsDown = FALSE;
		return;
	}

	if (oDataPtr->m_strDataTypeID != CMtDataTypeMngr::g_strMtDataType_ConfigFile)
	{
		m_bButtonIsDown = FALSE;
		return;
	}

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile.AppendFormat(_T("%s.xml"), oDataPtr->m_strID);

	if (!::IsFileExist(strFile))
	{
		m_bButtonIsDown = FALSE;
		return;
	}

	CDlgDataGroup dlg(strFile, oDataPtr->m_strValue);

	if (dlg.DoModal() == IDCANCEL)
	{
		m_bButtonIsDown = FALSE;
		return;
	}

	oDataPtr->m_strValue = dlg.m_strDatas;

	if (m_pWndInPlace != NULL)
	{
		m_pWndInPlace->SetWindowText(oDataPtr->m_strValue);
	}

	m_varValue = (LPCTSTR) oDataPtr->m_strValue;

	m_bButtonIsDown = FALSE;
	Redraw();

	if (m_pWndInPlace != NULL)
	{
		m_pWndInPlace->SetFocus();
	}
	else
	{
		m_pWndList->SetFocus();
	}
}

void CMacroTestDatasPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
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

	CShortData *pData = (CShortData*)m_dwData;

	if (pData == NULL)
	{
		return;
	}

	if (pData->GetClassID() != DTMCLASSID_CSHORTDATA)
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


void CMacroTestDatasPropGridProperty::OnDrawDescription(CDC* pDC, CRect rect)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pWndList);
	CShortData *pData = (CShortData*)m_dwData;

	//ASSERT (pData != NULL);
	CString strText;

	if (pData != NULL)
	{
		CMacroTestDatasPropGridCtrl *pGridCtrl = (CMacroTestDatasPropGridCtrl*)m_pWndList;
		pGridCtrl->m_oExprTextUnitList->SetExprScript(pData->m_strValue);
		strText = pGridCtrl->m_oExprTextUnitList->GetExprScriptText();
	}

	//HFONT hOldFont = (HFONT) ::SelectObject(pDC->GetSafeHdc(), m_pWndList->m_fontBold.GetSafeHandle());
	int nHeight = pDC->DrawText(strText, rect, DT_SINGLELINE | DT_NOPREFIX);

	//::SelectObject(pDC->GetSafeHdc(), hOldFont);

	rect.top += nHeight + 2;

	pDC->DrawText(m_strDescr, rect, DT_WORDBREAK | DT_NOPREFIX | DT_END_ELLIPSIS);
}

CWnd* CMacroTestDatasPropGridProperty::CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat)
{
	rectEdit.right -= UNIT_GAP;
	return CMFCPropertyGridProperty::CreateInPlaceEdit(rectEdit, bDefaultFormat);
}

void CMacroTestDatasPropGridProperty::SetValue(const COleVariant& varValue)
{
	CMFCPropertyGridProperty::SetValue(varValue);
	//SetModifiedFlag();
}

void CMacroTestDatasPropGridProperty::SetModifyFlagEx(BOOL bFlag)
{
	m_bIsModified = bFlag;
}

CMacroTestDatasPropGridCtrl::CMacroTestDatasPropGridCtrl()
{	
	m_pItemMacroTest = NULL;
	m_oExprTextUnitList = new CExprTextUnitList();
	m_clrLine = RGB(128, 128, 128);
	m_pDataTypesRef = NULL;
	m_pDataGroup = NULL;
	m_pItemMacroTest = NULL;
}

CMacroTestDatasPropGridCtrl::~CMacroTestDatasPropGridCtrl()
{
	delete m_oExprTextUnitList;
	m_oExprTextUnitList = NULL;
}




void CMacroTestDatasPropGridCtrl::OnPropertyChanged(CMFCPropertyGridProperty* pProp) const
{
	if (Gb_IsReadOnly((CExBaseObject*)m_pItemMacroTest))
	{
		return;
	}

	CMFCPropertyGridCtrl::OnPropertyChanged(pProp);
	ASSERT_VALID(this);
	ASSERT_VALID(pProp);

	CShortData  *pData = (CShortData*)pProp->GetData();

	if (pData == NULL)
	{
		return;
	}

	CString bstrDataTypeID = pData->m_strDataTypeID;
	CString strValue;
	CString strText = pProp->FormatProperty();

	if (IsComboMacroTestDataType(bstrDataTypeID))
	{
		if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_IECConfig)
		{
			strValue = strText;
		}
		else if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_ComtradeFile)
		{
			strValue = strText;
		}
		else
		{
			//GetDataTypeValueByName(CGbDataTypeMngr::GetMacroTestDataTypes(), bstrDataTypeID, strValue, strText);
			GetDataTypeValueByName(m_pDataTypesRef, bstrDataTypeID, strValue, strText);
		}
	}
	else
	{
		strValue = strText;
	}

	pData->m_strValue = strValue;
	pProp->Redraw();

	CMacroTestPara *pMacroTestPara = this->GetMacroTestPara();
	ASSERT (pMacroTestPara != NULL);
	pMacroTestPara->UpdateMacroTestParaData(pData, FALSE, TRUE);

	//验证表达式的正确性
	if (!IsStringNumber(strValue))
	{
		if (bstrDataTypeID != CMtDataTypeMngr::g_strMtDataType_IECConfig
			&& bstrDataTypeID != CMtDataTypeMngr::g_strMtDataType_ComtradeFile)
		{
			//CExprTextUnitList *pCExprTextUnitList = &m_oExprTextUnitList;
			pMacroTestPara->ValidateMacroTestParaData(pData);
#ifdef GUIDEBOOK_DEV_MODE
			m_oExprTextUnitList->SetExprScript(strText) ;
			m_oExprTextUnitList->GetExprScriptText(strText);
#endif
			pProp->SetValue( strText );
		}
	}

	CWnd *pParent = GetParent();
	pParent->PostMessage(WM_MACRO_PARA_VALUE_CHANGED, (WPARAM)pData, (LPARAM)0);

	if (pData->m_strFormat.GetLength() <= 1)
	{
		return;
	}

	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("CMacroTestDatasPropGridCtrl::OnPropertyChanged error, 后续改进"));
// 	CExBaseList listNew, listDelete;
// 	CTestMacro *pTestMacro = Gb_GetMacroPtr((CExBaseObject*)m_pItemMacroTest);
// 	pTestMacro->OnSetParaValue(pData, listNew, listDelete);
// 	this->UpdatePropGridCtrl(listNew, listDelete);
// 	listNew.RemoveAll();
// 	listDelete.DeleteAll();
}

void CMacroTestDatasPropGridCtrl::UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) const 
{
	POS pos = listDelete.GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CMFCPropertyGridProperty *pProp = NULL;
	CMFCPropertyGridProperty *pPropParent = NULL;
	CMacroTestDatasPropGridCtrl *pTempProp = (CMacroTestDatasPropGridCtrl*)this;

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

		if (pObj->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			pTempProp->SetMacroTestDatas((CDataGroup*)pObj, (CMacroTestDatasPropGridProperty*)pPropParent);
// 			CMacroTestDatasPropGridProperty* pGroup = new CMacroTestDatasPropGridProperty(pObj->m_strName);
// 			pObj->m_dwItemData = (DWORD)pGroup;
// 			pTempProp->SetMacroTestDatas((CDataGroup*)pObj, (CMacroTestDatasPropGridProperty *)pGroup);
//
// 			if (pPropParent == NULL)
// 			{
// 				pTempProp->AddProperty(pGroup);
// 			}
// 			else
// 			{
// 				pPropParent->AddSubItem(pGroup);
// 			}

		}
		else
		{
			ASSERT(FALSE);
			pTempProp->ShowValData((CShortData*)pObj, (CMacroTestDatasPropGridProperty *)pPropParent);
		}

	}
}

void CMacroTestDatasPropGridCtrl::UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) 
{

}

void CMacroTestDatasPropGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
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

void CMacroTestDatasPropGridCtrl::SetMacroTestDatas(CDataGroup  *pDataGroup, CShortDatas  *pDatas, CBaseObject *pMacroTest)
{
	if (m_pItemMacroTest == pMacroTest)
	{

	}

	m_pItemMacroTest = pMacroTest;
	m_bAllowEditPara = (m_pItemMacroTest != NULL);
	m_pDataGroup = pDataGroup;
	m_pDatas = pDatas;
	RemoveAll();

	if (pDatas != NULL)
	{
		SetMacroTestDatas(pDatas, NULL);
	}

	if (pDataGroup != NULL)
	{
		SetMacroTestDatasRoot(pDataGroup);
	}

	AdjustLayout();
	Invalidate(FALSE);
}

void CMacroTestDatasPropGridCtrl::SetMacroTestDatas(CShortDatas  *pDatas, CMacroTestDatasPropGridProperty *pParent)
{
	POS pos = pDatas->GetHeadPosition();
	CShortData  *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData*)pDatas->GetNext(pos);
		ShowValData(pData, pParent);
	}
}

void CMacroTestDatasPropGridCtrl::SetMacroTestDatasRoot(CDataGroup  *pDataGroup)
{
	POS pos = pDataGroup->GetHeadPosition();
	CShortData  *pData = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pDataGroup->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			SetMacroTestDatas((CDataGroup*)p, NULL);
		}
		else if (nClassID == DTMCLASSID_CSHORTDATA)
		{
			pData = (CShortData*)p;
			ShowValData(pData, NULL);
		}
		else
		{
			ASSERT (FALSE);
		}
	}
}

void CMacroTestDatasPropGridCtrl::SetMacroTestDatas(CDataGroup  *pDataGroup, CMacroTestDatasPropGridProperty *pParent)
{
	CMacroTestDatasPropGridCtrl *pTempProp = (CMacroTestDatasPropGridCtrl*)this;
	CMacroTestDatasPropGridProperty* pGroupProp = NULL;
	
	if (pDataGroup->m_strDataType == _T("channel"))
	{
		pGroupProp = new CMacroTestDatasPropGridProperty(pDataGroup->m_strName, 0, TRUE);
	}
	else
	{
		pGroupProp = new CMacroTestDatasPropGridProperty(pDataGroup->m_strName);
	}

	pDataGroup->m_dwItemData = (DWORD)pGroupProp;

	POS pos = pDataGroup->GetHeadPosition();
	CShortData  *pData = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	BOOL bModified = FALSE;

	while (pos != NULL)
	{
		p = pDataGroup->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			//CMacroTestDatasPropGridProperty* pGroup = new CMacroTestDatasPropGridProperty(p->m_strName);
			//p->m_dwItemData = (DWORD)pGroup;
			SetMacroTestDatas((CDataGroup*)p, pGroupProp);

// 			if (pParent == NULL)
// 			{
// 				AddProperty(pGroup, FALSE, FALSE);
// 			}
// 			else
// 			{
// 				pParent->AddSubItem(pGroup);
// 			}
		}
		else if (nClassID == DTMCLASSID_CSHORTDATA)
		{
			pData = (CShortData*)p;

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

void CMacroTestDatasPropGridCtrl::InitSetValueText(CString &strText, CShortData  *pData)
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

BOOL CMacroTestDatasPropGridCtrl::IsDropList(CShortData  *pData)
{
	CString bstrDataTypeID = pData->m_strDataTypeID;

	if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_IECConfig)
	{
		return TRUE;
	}

	if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_ComtradeFile)
	{
		return TRUE;
	}

	if (IsComboMacroTestDataType(bstrDataTypeID))
	{
		if (!IsStringNumber(pData->m_strValue))
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}
BOOL CMacroTestDatasPropGridCtrl::IsButton(CShortData  *pData)
{
	CString bstrDataTypeID = pData->m_strDataTypeID;

	if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_ConfigFile)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CString CMacroTestDatasPropGridCtrl::GetValueText(CShortData  *pData, const CString &strValue)
{
	CString bstrDataTypeID = pData->m_strDataTypeID;
	CString strText;

	if (IsComboMacroTestDataType(bstrDataTypeID) && IsStringNumber(strValue))
	{
		//GetDataTypeNameByValue(CGbDataTypeMngr::GetMacroTestDataTypes(), bstrDataTypeID, strValue, strText);
		GetDataTypeNameByValue(m_pDataTypesRef, bstrDataTypeID, strValue, strText);

		if (!IsStringNumber(strValue))
		{
#ifdef GUIDEBOOK_DEV_MODE
			m_oExprTextUnitList->SetExprScript(strValue);
			strText = m_oExprTextUnitList->GetExprScriptText();
#else
			strText = strValue;
#endif
		}
	}
	else
	{
		//验证表达式的正确性
		if (!IsStringNumber(strValue))
		{
#ifdef GUIDEBOOK_DEV_MODE
			m_oExprTextUnitList->SetExprScript(strValue);
			strText = m_oExprTextUnitList->GetExprScriptText();
#else
			strText = strValue;
#endif
		}
		else
		{
			strText = strValue;
		}
	}

	return strText;
}

BOOL CMacroTestDatasPropGridCtrl::ShowValData(CShortData  *pData, CMacroTestDatasPropGridProperty *pParent)
{
	CString strValue = GetValueText(pData, pData->m_strValue);
	CString strDefValue = GetValueText(pData, pData->m_strDefaultValue);
	CMacroTestDatasPropGridProperty *pPropValue = new CMacroTestDatasPropGridProperty(pData->m_strName, strDefValue, _T(""));
	pData->m_dwItemData = (DWORD)pPropValue;

	if (!TMS_IsDataEnable(pData))
	{
		pPropValue->Enable(FALSE);
	}

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

BOOL CMacroTestDatasPropGridCtrl::IsCurrDataEnable()
{
	CMacroTestDatasPropGridProperty *pProp = (CMacroTestDatasPropGridProperty*)GetCurSel();

	if (pProp == NULL)
	{
		return FALSE;
	}

	return pProp->IsEnabled();
}

CMacroTestPara* CMacroTestDatasPropGridCtrl::GetMacroTestPara()
{
	CMacroTestPara *pMacroTestPara = NULL;

	if (m_pItemMacroTest->GetClassID() == GBCLASSID_MACROTEST)
	{
		CMacroTest *pMacroTest = (CMacroTest*)m_pItemMacroTest;
		pMacroTestPara = pMacroTest->GetMacroTestPara();
	}
	else if (m_pItemMacroTest->GetClassID() == GBCLASSID_MACROPARA)
	{
		pMacroTestPara = (CMacroTestPara*)m_pItemMacroTest;
	}
	else if (m_pItemMacroTest->GetClassID() == GBCLASSID_MACROCHARITEMS)
	{
		CMacroCharItems *pMacroCharItems = (CMacroCharItems*)m_pItemMacroTest;
		pMacroTestPara = pMacroCharItems->GetMacroTestPara();
	}

	return pMacroTestPara;
}

CMacroTestPara* CMacroTestDatasPropGridCtrl::GetMacroTestPara() const 
{
	CMacroTestPara *pMacroTestPara = NULL;

	if (m_pItemMacroTest->GetClassID() == GBCLASSID_MACROTEST)
	{
		CMacroTest *pMacroTest = (CMacroTest*)m_pItemMacroTest;
		pMacroTestPara = pMacroTest->GetMacroTestPara();
	}
	else if (m_pItemMacroTest->GetClassID() == GBCLASSID_MACROPARA)
	{
		pMacroTestPara = (CMacroTestPara*)m_pItemMacroTest;
	}
	else if (m_pItemMacroTest->GetClassID() == GBCLASSID_MACROCHARITEMS)
	{
		CMacroCharItems *pMacroCharItems = (CMacroCharItems*)m_pItemMacroTest;
		pMacroTestPara = pMacroCharItems->GetMacroTestPara();
	}

	return pMacroTestPara;
}

CShortData*  CMacroTestDatasPropGridCtrl::SetItemValue(const CString &strValue)
{
	CMacroTestDatasPropGridProperty *pProp = (CMacroTestDatasPropGridProperty*)GetCurSel();

	if (!pProp->IsEnabled())
	{
		return NULL;
	}

	CShortData  *pData = GetSelectData();

	if (pData == NULL)
	{
		return pData;
	}

	CString strValue2, strText;
 	strText = strValue;
 	pData->m_strValue = strText;

	CMacroTestPara *pMacroTestPara = GetMacroTestPara();
	ASSERT (pMacroTestPara != NULL);

// 
// 	if (m_pItemMacroTest->GetClassID() == GBCLASSID_MACROTEST)
// 	{
// 		CMacroTest *pMacroTest = (CMacroTest*)m_pItemMacroTest;
// 		pMacroTestPara = pMacroTest->GetMacroTestPara();
// 	}
// 	else if (m_pItemMacroTest->GetClassID() == GBCLASSID_MACROPARA)
// 	{
// 		pMacroTestPara = (CMacroTestPara*)m_pItemMacroTest;
// 	}
// 	else if (m_pItemMacroTest->GetClassID() == GBCLASSID_MACROCHARITEMS)
// 	{
// 		CMacroCharItems *pMacroCharItems = (CMacroCharItems*)m_pItemMacroTest;
// 		pMacroTestPara = pMacroCharItems->GetMacroTestPara();
// 	}

	pMacroTestPara->UpdateMacroTestParaData(pData, FALSE, TRUE);
	
	//验证表达式的正确性
	if (!IsStringNumber(strValue))
	{
		pMacroTestPara->ValidateMacroTestParaData(pData);
#ifdef GUIDEBOOK_DEV_MODE
		m_oExprTextUnitList->SetExprScript(strText);
		strText = m_oExprTextUnitList->GetExprScriptText();
#else
		strText = strValue;
#endif
		pProp->AllowEdit(FALSE);
	}
	else
	{
		pProp->AllowEdit(TRUE);
	}

	pProp->SetValue(strText);

	return pData;
}

CShortData*  CMacroTestDatasPropGridCtrl::GetData(int nRow)
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


CShortData*  CMacroTestDatasPropGridCtrl::GetSelectData()
{
	CMacroTestDatasPropGridProperty *pProp = (CMacroTestDatasPropGridProperty*)GetCurSel();

	if (pProp == NULL)
	{
		return NULL;
	}

	if (pProp->IsGroup())
	{
		return NULL;
	}

	CShortData  *pData = (CShortData*)pProp->GetData();

	return pData;
}

void CMacroTestDatasPropGridCtrl::ShowColumnTitle()
{
	
}

void CMacroTestDatasPropGridCtrl::SetGridRows()
{
	
}

void CMacroTestDatasPropGridCtrl::GetEditTextValue(CString &strText, CString &strValue, CShortData *pPara)
{
	//数字
	if (IsStringNumber(strText))
	{
		strValue = strText;
		return;
	}

	CDevice *pDevice = (CDevice*)GetDevice();
	CDataObj *pSet = NULL;

	//如果是路径字符串
	if (DS_InStringDataPath(strText))
	{
		pSet = pDevice->FindDataObjByID(strText, -1);
		
		if (pSet != NULL)
		{
			strValue = strText;
			strText = pSet->m_strName;
			return;
		}
	}
	else
	{
		//是否为测试参数
		pSet = pDevice->FindDataObjByID(strText, -1);

		if (pSet != NULL)
		{
			strValue = pSet->m_strID;
			strText = pSet->m_strName;
			return;
		}
		
		//是否数据集数据
		pSet = pDevice->FindDataObjByName(strText);

		if (pSet != NULL)
		{
			UINT nClassID = pSet->GetClassID();

			if (nClassID == GBCLASSID_DATAOBJ)
			{
				if(pPara->m_strValue == pSet->m_strID)
				{
					strValue = pPara->m_strValue;
				}
				else
				{
					pSet->GetIDForPath(strValue);
				}

				strText = pSet->m_strName;
			}
			else if (nClassID == GBCLASSID_GBTDATA)
			{
				strValue = pSet->m_strID;
				strText = pSet->m_strName;
			}
			else
			{
				strValue = pSet->m_strID;
				strText = pSet->m_strName;
			}

			return;
		}
	}

	//判断原来的数据时什么，显示原来的数据
	//是否数据集数据
	
	//判断表达式是否有效
	strValue = strText;
	
}


BEGIN_MESSAGE_MAP(CMacroTestDatasPropGridCtrl, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()


void CMacroTestDatasPropGridCtrl::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)
{

}

//////////////////////////////////////////////////////////////////////////
//CMacroChaTestrDatasPropGridCtrl
CMacroChaTestrDatasPropGridCtrl::CMacroChaTestrDatasPropGridCtrl()
{

}

CMacroChaTestrDatasPropGridCtrl::~CMacroChaTestrDatasPropGridCtrl()
{

}


BOOL CMacroChaTestrDatasPropGridCtrl::IsValDataEnable(CShortData  *pData)
{
	if (m_pCMacroCharTestDataEnableState != NULL)
	{
		return m_pCMacroCharTestDataEnableState->IsDataEnable(pData);
	}
	else
	{
		return TRUE;
	}
}


