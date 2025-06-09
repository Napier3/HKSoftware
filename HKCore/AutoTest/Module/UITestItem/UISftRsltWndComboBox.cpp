#include "stdafx.h"
#include "UISftRsltWndComboBox.h"
#include "../GuideBook/GbDataTypeMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CUISftRsltWndComboBox::CUISftRsltWndComboBox(CShortData *pData)
{
	m_pResultWndInterface = NULL;
	m_pData = pData;
}

CUISftRsltWndComboBox::~CUISftRsltWndComboBox()
{

}
BEGIN_MESSAGE_MAP(CUISftRsltWndComboBox, CComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CUISftRsltWndComboBox::OnCbnSelchange)
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CUISftRsltWndComboBox::OnCbnSelchange()
{
	// TODO: 在此添加控件通知处理程序代码
	long nIndex = GetCurSel();
	CString strData;
	this->GetLBText(nIndex, strData);

	if (m_pResultWndInterface != NULL)
	{
		m_pResultWndInterface->OnResultDataChanged(strData);
	}
}

int CUISftRsltWndComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CDataType* oDataType = (CDataType*)CGbDataTypeMngr::GetSafetyComboDataTypes()->FindByID(m_pData->m_strFormat);
	ASSERT(oDataType != NULL);
	
	if (oDataType == NULL)
	{
		return 0;
	}
	
	POS pos = oDataType->GetHeadPosition();
	long nSelIndex = 0;
	long nIndex = 0;
	
	while (pos != NULL)
	{
		CDataTypeValue* oValue = (CDataTypeValue*)oDataType->GetNext(pos);
		AddString(oValue->m_strName);

		if (oValue->m_strName == m_pData->m_strValue || oValue->m_strID == m_pData->m_strValue)
		{
			nSelIndex = nIndex;
		}

		nIndex++;
	}

	SetCurSel(nSelIndex);
	OnCbnSelchange();

	return 0;
}
