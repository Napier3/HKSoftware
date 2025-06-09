// D:/WorkPM/Source/Protocol/PpDev/PpDev/ScriptMethodsComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "ScriptMethodsComboBox.h"
#include "PpScriptMethodsInfo.h"

// CScriptMethodsComboBox

IMPLEMENT_DYNAMIC(CScriptMethodsComboBox, CComboBox)

CScriptMethodsComboBox::CScriptMethodsComboBox()
{

}

CScriptMethodsComboBox::~CScriptMethodsComboBox()
{
}


BEGIN_MESSAGE_MAP(CScriptMethodsComboBox, CComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CScriptMethodsComboBox::OnCbnSelchange)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CScriptMethodsComboBox 消息处理程序

void CScriptMethodsComboBox::InitComboBox(DWORD dwFlag)
{
	ResetContent();
	ASSERT(CPpScriptMethodsInfo::g_pPpScriptMethods != NULL);

	if(CPpScriptMethodsInfo::g_pPpScriptMethods != NULL)
	{
		POS pos = CPpScriptMethodsInfo::g_pPpScriptMethods->GetHeadPosition();
		CPpScriptMethodInfo* pMethod = NULL;
		int nIndex = 0;

		while (pos != NULL)
		{
			pMethod = (CPpScriptMethodInfo*)CPpScriptMethodsInfo::g_pPpScriptMethods->GetNext(pos);

			if ( (pMethod->m_dwFlag & dwFlag) > 0)
			{
				nIndex = AddString(pMethod->m_strMethodName);
				SetItemData(nIndex,(DWORD_PTR)pMethod);
			}
		}

		SetCurSel(0);
	}
}

void CScriptMethodsComboBox::PreSubclassWindow()
{
	//InitComboBox();

	CComboBox::PreSubclassWindow();
}

void CScriptMethodsComboBox::OnCbnSelchange()
{
	int nSel = GetCurSel();

	if(nSel != CB_ERR)
	{
		CPpScriptMethodInfo* pMethod = (CPpScriptMethodInfo*)GetItemData(nSel);
		CString strInfo;

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("函数名称：%s"),pMethod->m_strMethodName);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("返回值：%s"),pMethod->m_strReturnType);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("参数列表：%s"),pMethod->m_strParaList);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("函数说明：%s"),pMethod->m_strMethodInfo);
	}
}

void CScriptMethodsComboBox::AddStringEx()
{
	ASSERT(m_pEdit != NULL);

	if(m_pEdit != NULL)
	{
		CString strSel;
		GetWindowText(strSel);
		m_pEdit->ReplaceSel(strSel);
		m_pEdit->SetFocus();
	}
}

CString CScriptMethodsComboBox::GetFuncText(BOOL bHasParaList)
{
	CPpScriptMethodInfo* pMethod = NULL;
	int nIndex = GetCurSel();
	CString strText;

	if (nIndex == CB_ERR)
	{
		GetWindowText(strText);
	}
	else
	{
		pMethod = (CPpScriptMethodInfo*)GetItemDataPtr(nIndex);

		if (bHasParaList)
		{
			if (pMethod->m_strParaList.GetLength() <= 3)
			{
				strText.Format(_T("%s();"), pMethod->m_strMethodName);
			}
			else
			{
				strText.Format(_T("%s(%s);"), pMethod->m_strMethodName, pMethod->m_strParaList);
			}
		}
		else
		{
				strText.Format(_T("%s(   );"), pMethod->m_strMethodName);
		}
	}

	return strText;
}

void CScriptMethodsComboBox::OnRButtonDown(UINT nFlags, CPoint point)
{
	AddStringEx();

	CComboBox::OnRButtonDown(nFlags, point);
}
