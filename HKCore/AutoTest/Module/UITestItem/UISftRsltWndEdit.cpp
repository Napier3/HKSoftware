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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CEdit::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strData;
	GetWindowText(strData);

	//如果m_strType == number，要对用户输入的数据进行限制
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

		//如果m_strType == number，要对用户输入的数据进行限制
		BSTR bstrTemp = strData.AllocSysString();
		if (m_pResultWndInterface != NULL)
		{
			if( !IsStringNumber(bstrTemp) && m_strType ==g_strGbDataTypeNumber)
			{
				strData = _T("");
				SetWindowText(strData);
				//MessageBox(_T("请输入一个数字"));
				SetFocus();
			}
		}
		::SysFreeString(bstrTemp);
	}
}
