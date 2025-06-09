#include "StdAfx.h"
#include "MacroTestDataEditPropGridCtrl.h"
#include "..\..\Module\TestMacroScript\MacroScriptMngrGlobal.h"
// #include "AutoTest.h"
#include "..\..\TestControl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define AFX_PROP_HAS_LIST 0x0001
#define AFX_PROP_HAS_BUTTON 0x0002
#define AFX_PROP_HAS_SPIN 0x0004

#define UNIT_GAP    24

IMPLEMENT_DYNAMIC(CMacroTestDataEditPropGridProperty, CMFCPropertyGridProperty)

CMacroTestDataEditPropGridProperty::CMacroTestDataEditPropGridProperty(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
: CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList)
{

}

CMacroTestDataEditPropGridProperty::CMacroTestDataEditPropGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
													   LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
													   : CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
{

}

void CMacroTestDataEditPropGridProperty::SetIsValueList(BOOL b)
{
	m_bIsValueList = b;
}


BOOL CMacroTestDataEditPropGridProperty::OnEdit(LPPOINT lptClick)
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
		CDataTypes *pDataTypes = mtde_GetMacroTestDataTypes(oDataPtr);

		if (pDataTypes != NULL)
		{
			CMacroTestDataEditPropGridCtrl *pGridCtrl = (CMacroTestDataEditPropGridCtrl*)m_pWndList;
			CDataType *pDataType = Gb_GetDataType((CExBaseObject*)pGridCtrl->m_pItemMacroTest, pDataTypes, strDataType);
			//CDataType *pDataType = (CDataType*)pDataTypes->FindByID(strDataType);

			if (pDataType != NULL)
			{
				InsertDataTypeToComboBox(pDataType, m_pWndCombo);
			}
		}
		
	}
	else
	{

	}

	return bRet;
}

CDataTypes* mtde_GetMacroTestDataTypes(CExBaseObject *pObj)
{
	CTestMacros *pTestMacros = (CTestMacros*)pObj->GetAncestor(TMCLASSID_CTESTMACROS);

	if (pTestMacros != NULL)
	{
		return pTestMacros->GetDataTypes();
	}
	else
	{
		return CGbDataTypeMngr::GetMacroTestDataTypes();
	}
}

void CMacroTestDataEditPropGridProperty::SetCombBoxType()
{
	m_dwFlags = AFX_PROP_HAS_LIST;
}

void CMacroTestDataEditPropGridProperty::OnDrawValue(CDC* pDC, CRect rect)
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

	if (pData->m_strUnit == CXLanguageResourceBase::g_sLangTxt_None/*_T("无")*/)
	{
		return;
	}

	rect.DeflateRect(AFX_TEXT_MARGIN, 0);
	rect.left = rect.right;
	rect.right = rect.left + UNIT_GAP;
	pDC->DrawText(pData->m_strUnit, rect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

}


CWnd* CMacroTestDataEditPropGridProperty::CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat)
{
	rectEdit.right -= UNIT_GAP;
	return CMFCPropertyGridProperty::CreateInPlaceEdit(rectEdit, bDefaultFormat);
}

void CMacroTestDataEditPropGridProperty::SetValue(const COleVariant& varValue)
{
	CMFCPropertyGridProperty::SetValue(varValue);
	//SetModifiedFlag();
}

void CMacroTestDataEditPropGridProperty::SetModifyFlagEx(BOOL bFlag)
{
	m_bIsModified = bFlag;
}

CMacroTestDataEditPropGridCtrl::CMacroTestDataEditPropGridCtrl()
{	
	m_pItemMacroTest = NULL;
// 	m_oExprTextUnitList = new CExprTextUnitList();
	m_clrLine = RGB(128, 128, 128);
}

CMacroTestDataEditPropGridCtrl::~CMacroTestDataEditPropGridCtrl()
{
// 	delete m_oExprTextUnitList;
// 	m_oExprTextUnitList = NULL;
}




void CMacroTestDataEditPropGridCtrl::OnPropertyChanged(CMFCPropertyGridProperty* pProp) const
{
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
			GetDataTypeValueByName(mtde_GetMacroTestDataTypes(pData), bstrDataTypeID, strValue, strText);
		}
	}
	else
	{
		strValue = strText;
	}

	pData->m_strValue = strValue;
	pProp->Redraw();

	CMacroTest *pMacroTest = (CMacroTest*)m_pItemMacroTest;
	pMacroTest->UpdateMacroTestParaData(pData, FALSE);

#ifdef GUIDEBOOK_DEV_MODE
#else
	CTestControl *pTestControl = (CTestControl*)pMacroTest->GetAncestor(GBCLASSID_TESTCONTROL);
	pTestControl->EditItemPara(pMacroTest, pData);
#endif

	//验证表达式的正确性
	if (!IsStringNumber(strValue))
	{
		if (bstrDataTypeID != CMtDataTypeMngr::g_strMtDataType_IECConfig
			&& bstrDataTypeID != CMtDataTypeMngr::g_strMtDataType_ComtradeFile)
		{
			//CExprTextUnitList *pCExprTextUnitList = &m_oExprTextUnitList;
			pMacroTest->ValidateMacroTestParaData(pData);
// 			m_oExprTextUnitList->SetExprScript(strText) ;
// 			m_oExprTextUnitList->GetExprScriptText(strText);
			pProp->SetValue( strText );
		}
	}

	CWnd *pParent = GetParent();
	pParent->PostMessage(WM_MACRO_PARA_VALUE_CHANGED, (WPARAM)pData, (LPARAM)0);

	if (pData->m_strFormat.GetLength() <= 1)
	{
		return;
	}

	CExBaseList listNew, listDelete;
	CTestMacro *pTestMacro = Gb_GetMacroPtr(pMacroTest);
	pTestMacro->OnSetParaValue(pData, listNew, listDelete);
	this->UpdatePropGridCtrl(listNew, listDelete);
	listNew.RemoveAll();
	listDelete.DeleteAll();
}

void CMacroTestDataEditPropGridCtrl::UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) const 
{
	POS pos = listDelete.GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CMFCPropertyGridProperty *pProp = NULL;
	CMFCPropertyGridProperty *pPropParent = NULL;
	CMacroTestDataEditPropGridCtrl *pTempProp = (CMacroTestDataEditPropGridCtrl*)this;

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
			pTempProp->SetMacroTestDatas((CDataGroup*)pObj, (CMacroTestDataEditPropGridProperty*)pPropParent);
// 			CMacroTestDataEditPropGridProperty* pGroup = new CMacroTestDataEditPropGridProperty(pObj->m_strName);
// 			pObj->m_dwItemData = (DWORD)pGroup;
// 			pTempProp->SetMacroTestDatas((CDataGroup*)pObj, (CMacroTestDataEditPropGridProperty *)pGroup);
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
			pTempProp->ShowValData((CShortData*)pObj, (CMacroTestDataEditPropGridProperty *)pPropParent);
		}

	}
}

void CMacroTestDataEditPropGridCtrl::UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) 
{

}

void CMacroTestDataEditPropGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
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

void CMacroTestDataEditPropGridCtrl::SetMacroTestDatas(CDataGroup  *pDataGroup, CShortDatas  *pDatas, CBaseObject *pMacroTest)
{
	if (m_pItemMacroTest == pMacroTest)
	{

	}

	m_pItemMacroTest = pMacroTest;
	m_pDataGroup = pDataGroup;
	m_pDatas = pDatas;
	RemoveAll();

	SetMacroTestDatas(pDatas, NULL);

	if (pDataGroup != NULL)
	{
		SetMacroTestDatasRoot(pDataGroup);
	}

	AdjustLayout();
	Invalidate(FALSE);
}

void CMacroTestDataEditPropGridCtrl::SetMacroTestDatas(CShortDatas  *pDatas, CMacroTestDataEditPropGridProperty *pParent)
{
	POS pos = pDatas->GetHeadPosition();
	CShortData  *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData*)pDatas->GetNext(pos);
		ShowValData(pData, pParent);
	}
}

void CMacroTestDataEditPropGridCtrl::SetMacroTestDatasRoot(CDataGroup  *pDataGroup)
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

void CMacroTestDataEditPropGridCtrl::SetMacroTestDatas(CDataGroup  *pDataGroup, CMacroTestDataEditPropGridProperty *pParent)
{
	CMacroTestDataEditPropGridCtrl *pTempProp = (CMacroTestDataEditPropGridCtrl*)this;
	CMacroTestDataEditPropGridProperty* pGroupProp = NULL;
	
	if (pDataGroup->m_strDataType == _T("channel"))
	{
		pGroupProp = new CMacroTestDataEditPropGridProperty(pDataGroup->m_strName, 0, TRUE);
	}
	else
	{
		pGroupProp = new CMacroTestDataEditPropGridProperty(pDataGroup->m_strName);
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
			//CMacroTestDataEditPropGridProperty* pGroup = new CMacroTestDataEditPropGridProperty(p->m_strName);
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

void CMacroTestDataEditPropGridCtrl::InitSetValueText(CString &strText, CShortData  *pData)
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
BOOL CMacroTestDataEditPropGridCtrl::IsDropList(CShortData  *pData)
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

CString CMacroTestDataEditPropGridCtrl::GetValueText(CShortData  *pData, const CString &strValue)
{
	CString bstrDataTypeID = pData->m_strDataTypeID;
	CString strText;

	if (IsComboMacroTestDataType(bstrDataTypeID) && IsStringNumber(strValue))
	{
		GetDataTypeNameByValue(mtde_GetMacroTestDataTypes(pData), bstrDataTypeID, strValue, strText);

		if (!IsStringNumber(strValue))
		{
// 			m_oExprTextUnitList->SetExprScript(strValue);
// 			strText = m_oExprTextUnitList->GetExprScriptText();
			strText = strValue;
		}
	}
	else
	{
		//验证表达式的正确性
// 		if (!IsStringNumber(strValue))
// 		{
// 			m_oExprTextUnitList->SetExprScript(strValue);
// 			strText = m_oExprTextUnitList->GetExprScriptText();
// 		}
// 		else
		{
			strText = strValue;
		}
	}

	return strText;
}

BOOL CMacroTestDataEditPropGridCtrl::ShowValData(CShortData  *pData, CMacroTestDataEditPropGridProperty *pParent)
{
	CString strValue = GetValueText(pData, pData->m_strValue);
	CString strDefValue = GetValueText(pData, pData->m_strDefaultValue);
	CMacroTestDataEditPropGridProperty *pPropValue = new CMacroTestDataEditPropGridProperty(pData->m_strName, strDefValue, _T(""));
	pData->m_dwItemData = (DWORD)pPropValue;

// 	if (!TMS_IsDataEnable(pData))
// 	{
// 		pPropValue->Enable(FALSE);
// 	}

	if (IsDropList(pData))
	{
		pPropValue->SetCombBoxType();
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

	return pPropValue->IsModified();
}

CShortData*  CMacroTestDataEditPropGridCtrl::SetItemValue(const CString &strValue)
{
	CMacroTestDataEditPropGridProperty *pProp = (CMacroTestDataEditPropGridProperty*)GetCurSel();
	CShortData  *pData = GetSelectData();

	if (pData == NULL)
	{
		return pData;
	}

	CString strValue2, strText;
 	strText = strValue;
 	pData->m_strValue = strText;

	CMacroTest *pMacroTest = (CMacroTest*)m_pItemMacroTest;
	pMacroTest->UpdateMacroTestParaData(pData, FALSE);
	
	//验证表达式的正确性
	if (!IsStringNumber(strValue))
	{
		pMacroTest->ValidateMacroTestParaData(pData);
// 		m_oExprTextUnitList->SetExprScript(strText);
// 		strText = m_oExprTextUnitList->GetExprScriptText();
		pProp->AllowEdit(FALSE);
	}
	else
	{
		pProp->AllowEdit(TRUE);
	}

	pProp->SetValue(strText);

	return pData;
}

CShortData*  CMacroTestDataEditPropGridCtrl::GetData(int nRow)
{
	return GetSelectData();
}


CShortData*  CMacroTestDataEditPropGridCtrl::GetSelectData()
{
	CMacroTestDataEditPropGridProperty *pProp = (CMacroTestDataEditPropGridProperty*)GetCurSel();

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

void CMacroTestDataEditPropGridCtrl::ShowColumnTitle()
{
	
}

void CMacroTestDataEditPropGridCtrl::SetGridRows()
{
	
}

void CMacroTestDataEditPropGridCtrl::GetEditTextValue(CString &strText, CString &strValue, CShortData *pPara)
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


BEGIN_MESSAGE_MAP(CMacroTestDataEditPropGridCtrl, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()


void CMacroTestDataEditPropGridCtrl::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)
{

}

