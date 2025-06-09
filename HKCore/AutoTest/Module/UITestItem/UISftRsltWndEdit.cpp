#include "stdafx.h"
#include "UISftRsltWndEdit.h"
#include "UISftRsltWndInterface.h"
#include "../../../Module/api/GlobalApi.h"
#include "../GuideBook/GbDataTypeMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CUISftRsltWndEdit, CEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, &CUISftRsltWndEdit::OnEnChange)
//	ON_CONTROL_REFLECT(EN_KILLFOCUS, &CUISftRsltWndEdit::OnEnKillfocus)
ON_CONTROL_REFLECT(EN_KILLFOCUS, &CUISftRsltWndEdit::OnEnKillfocus)
END_MESSAGE_MAP()


CUISftRsltWndEdit::CUISftRsltWndEdit(const CString &strType)
{
	m_strType = strType;
}

CUISftRsltWndEdit::~CUISftRsltWndEdit()
{

}

void CUISftRsltWndEdit::OnEnChange()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CEdit::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strData;
	GetWindowText(strData);

	//���m_strType == number��Ҫ���û���������ݽ�������
	BSTR bstrTemp = strData.AllocSysString();

	if (m_pResultWndInterface != NULL)
	{
		if( !IsStringNumber(bstrTemp) && m_strType ==g_strGbDataTypeNumber)
		{
			strData = _T("");
		}
		m_pResultWndInterface->OnResultDataChanged(strData);
	}

	::SysFreeString(bstrTemp);
}

void CUISftRsltWndEdit::OnEnKillfocus()
{
	if(GetSafeHwnd())
	{
		CString strData;
		GetWindowText(strData);

		//���m_strType == number��Ҫ���û���������ݽ�������
		BSTR bstrTemp = strData.AllocSysString();
		if (m_pResultWndInterface != NULL)
		{
			if( !IsStringNumber(bstrTemp) && m_strType ==g_strGbDataTypeNumber)
			{
				strData = _T("");
				SetWindowText(strData);
				//MessageBox(_T("������һ������"));
				SetFocus();
			}
		}
		::SysFreeString(bstrTemp);
	}
}
