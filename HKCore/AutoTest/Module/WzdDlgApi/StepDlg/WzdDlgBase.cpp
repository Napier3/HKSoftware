#include "stdafx.h"
#include "WzdDlgBase.h"

IMPLEMENT_DYNAMIC(CWzdDlgBase, CDialog)

CWzdDlgBase::CWzdDlgBase(UINT nIDTemplate, CWnd* pParent/* = NULL*/)
{
	m_bIsActived = FALSE;
	m_bIsEnabled = TRUE;
	m_pDataCfg = NULL;
	m_pParentWnd = pParent;
	m_oBkBrush.CreateSolidBrush(RGB(255,255,255));
}

CWzdDlgBase::~CWzdDlgBase()
{
	//m_pWnd½çÃæ×ÊÔ´Ëæ¸¸¶ÔÏóÎö¹¹ÊÍ·Å
}

void CWzdDlgBase::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(CDialog::GetParent());
	CXUIAdjItem_Area::XUI_OnSize();
}

BOOL CWzdDlgBase::IsActived()
{
	return m_bIsActived;
}

void CWzdDlgBase::SetActived(BOOL bActive)
{
	m_bIsActived = bActive;
}

BOOL CWzdDlgBase::IsEnabled()
{
	return m_bIsEnabled;
}

void CWzdDlgBase::SetEnabled(BOOL bEnable)
{
	m_bIsEnabled = bEnable;
}

BOOL CWzdDlgBase::Create(UINT nIDTemplate, CWnd* pParentWnd)
{
	BOOL nRes = CDialog::Create(nIDTemplate, pParentWnd);
	m_pParentWnd = pParentWnd;
	return nRes;
}

void CWzdDlgBase::SetParentWnd(CWnd* pWnd)
{
	CDialog::SetParent(pWnd);
	m_pParentWnd = pWnd;
}

CWnd* CWzdDlgBase::GetParentWnd()
{
	return m_pParentWnd;
}

BOOL CWzdDlgBase::InitUI(CDataGroup* pDataGroup)
{
	m_pDataCfg = pDataGroup;
	return TRUE;
}

BOOL CWzdDlgBase::DoNext()
{
	return TRUE;
}

BOOL CWzdDlgBase::DoPrev()
{
	return TRUE;
}

BOOL CWzdDlgBase::DoNextForThead()
{
	return TRUE;
}

void CWzdDlgBase::XmlToUI(CEdit* pEdit, CDvmData* pDvmData, CButton* pCheckBox)
{
	if(pCheckBox)
	{
		CDvmValue* pValue = ParseUIXml(pDvmData, SENCESEL_ENABLE);
		if(pValue)
		{
			long nChecked = CString_To_long(pValue->m_strValue);
			pCheckBox->SetCheck(nChecked);
		}
	}

	CDvmValue* pFile = ParseUIXml(pDvmData, SENCESEL_FILEPATH);
	if(pFile)
	{
		pEdit->SetWindowText(pFile->m_strValue);
	}
}

void CWzdDlgBase::XmlToUI(CComboBox* pComboBox, CDvmData* pDvmData)
{
	POS pos = pDvmData->GetHeadPosition();
	while(pos)
	{
		CDvmValue* pValue = (CDvmValue*)pDvmData->GetNext(pos);
		pComboBox->InsertString(pComboBox->GetCount(), pValue->m_strValue);
	}
	long nIndex = CString_To_long(pDvmData->m_strValue);
	pComboBox->SetCurSel(nIndex);
}

CDvmData* CWzdDlgBase::ParseUIXml(CDataGroup* pDataGroup, const CString& strID)
{
	CDvmData* pData = (CDvmData*)pDataGroup->FindByID(strID);
	if(!pData)
	{
		CString strErr;
		strErr.Format("¡¾´íÎó¡¿¼ì²âµ½³ÌÐòÅäÖÃÎÄ¼þ´íÎó, ´íÎóID(%s)!\n", strID);
		m_strErrorLog += strErr;
		return 0;
	}
	return pData;
}

CDvmValue* CWzdDlgBase::ParseUIXml(CDvmData* pDvmData, const CString& strID)
{
	CDvmValue* pData = (CDvmValue*)pDvmData->FindByID(strID);
	if(!pData)
	{
		CString strErr;
		strErr.Format("¡¾´íÎó¡¿¼ì²âµ½³ÌÐòÅäÖÃÎÄ¼þ´íÎó, ´íÎóID(%s)!\n", strID);
		m_strErrorLog += strErr;
		return 0;
	}
	return pData;
}

BEGIN_MESSAGE_MAP(CWzdDlgBase, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

HBRUSH CWzdDlgBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_DLG)
	{
		return m_oBkBrush;
	}
	else if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(RGB(255, 255, 255));
	}

	return m_oBkBrush;
}