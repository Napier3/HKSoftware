// D:\WorkLiJQ\Source\SttStudio\Module\MfcCtrl\SttComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SttComboBox.h"


//////////////////////////////////////////////////////////////////////////
// CSttComboBox
CSttComboBox::CSttComboBox()
{
	m_nValueDataMode = STT_CMB_DATA_MODE_INDEX;
}

CSttComboBox::~CSttComboBox()
{
}

BEGIN_MESSAGE_MAP(CSttComboBox, CExBaseListComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CSttComboBox::OnCbnSelchange)
END_MESSAGE_MAP()

// CSttComboBox 消息处理程序

void CSttComboBox::OnCbnSelchange()
{
	SaveData();

	OnSttDataChanged();
}


void CSttComboBox::ShowData()
{
	if (m_pRefData == NULL)
	{
		return;
	}

	if (m_nValueDataMode == STT_CMB_DATA_MODE_ID)
	{
		SetCurrSelByID(m_pRefData->m_strValue);
	}
	else
	{
		long nIndex = CString_To_long(m_pRefData->m_strValue);
		SetCurSel(nIndex);
	}
}

void CSttComboBox::SaveData()
{
	if (m_pRefData == NULL)
	{
		return;
	}

	if (m_nValueDataMode == STT_CMB_DATA_MODE_ID)
	{
		GetSelectID(m_pRefData->m_strValue);
	}
	else
	{
		long nIndex = GetCurSel();
		m_pRefData->m_strValue.Format(_T("%d"), nIndex);
	}
}

//////////////////////////////////////////////////////////////////////////
// CSttNumberComboBox
CSttNumberComboBox::CSttNumberComboBox()
{

}

CSttNumberComboBox::~CSttNumberComboBox()
{
}

BEGIN_MESSAGE_MAP(CSttNumberComboBox, CNumberComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CSttNumberComboBox::OnCbnSelchange)
END_MESSAGE_MAP()

// CSttComboBox 消息处理程序

void CSttNumberComboBox::OnCbnSelchange()
{
	SaveData();

	OnSttDataChanged();
}


void CSttNumberComboBox::ShowData()
{
	if (m_pRefData == NULL)
	{
		return;
	}

	long nNumber = CString_To_long(m_pRefData->m_strValue);
	SelNumber(nNumber);
}

void CSttNumberComboBox::SaveData()
{
	if (m_pRefData == NULL)
	{
		return;
	}

	// mym 2012-4-22 注销；为了在外面赋值；
	m_pRefData->m_strValue.Format(_T("%d"), GetNumber());
}
