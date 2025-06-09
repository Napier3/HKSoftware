#include "StdAfx.h"
#include "ZoneSelComboBox.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CZoneSelComboBox::CZoneSelComboBox(void)
{
}

CZoneSelComboBox::~CZoneSelComboBox(void)
{
}

void CZoneSelComboBox::InitComboBox()
{
	ResetContent();

	long nItemIndex = 0;
	
	nItemIndex = AddString(/*_T("当前定值区")*/g_sLangTxt_CurrZoneIndex);
	SetItemData(nItemIndex, 0);
	CString strText;

	for (long nIndex=1; nIndex<32; nIndex++)
	{
		strText.Format(/*_T("%d区")*/g_sLangTxt_ZoneIndex, nIndex);
		nItemIndex = AddString(strText);
		SetItemData(nItemIndex, nIndex);
	}
}

long CZoneSelComboBox::GetZoneSelIndex()
{
	long nSel = GetCurSel();
	
	if (nSel == CB_ERR)
	{
		return 0;
	}
	
	return GetItemData(nSel);
}

void CZoneSelComboBox::SetZoneSelIndex(long nZoneIndex)
{
	SetCurSel(nZoneIndex);
}

