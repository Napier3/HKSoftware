#include "StdAfx.h"
#include "RepeatComboBox.h"

CRepeatComboBox::CRepeatComboBox(void)
{
}

CRepeatComboBox::~CRepeatComboBox(void)
{
}

void CRepeatComboBox::InitComboBox(CExBaseObject *pGbItem)
{
	ResetContent();

	if (pGbItem == NULL)
	{
		return;
	}

	LONG nClassID = pGbItem->GetClassID();

	if ( !(GBCLASSID_MACROTEST == nClassID || GBCLASSID_COMMCMD == nClassID) )
	{
		return;
	}

	long nRepeatTimes = 0;
	CString strCalMode;

	if (GBCLASSID_MACROTEST == nClassID)
	{
		nRepeatTimes = ((CMacroTest*)pGbItem)->m_nRepeatTimes;
		strCalMode = ((CMacroTest*)pGbItem)->m_strReportMode;
	}

	if (GBCLASSID_COMMCMD == nClassID)
	{
		CGbItemBase *pParent = (CGbItemBase*)pGbItem->GetParent();
		nRepeatTimes = ((CCommCmd*)pGbItem)->GetRepeatTimes(&strCalMode);
	}

	m_nRepeatCount = nRepeatTimes;
	InitComboBox(nRepeatTimes, strCalMode);
}

void CRepeatComboBox::InitComboBox(long nRepeatCount, const CString &strCalMode)
{
	ResetContent();
	InitNumbers(1, nRepeatCount, 1);

	if (Gb_GetReportCalMode(strCalMode) != TEST_CALMODE_NONE)
	{
		CString strText = Gb_GetReportCalModeText(strCalMode);
		//strText = _T("¼ÆËã½á¹û£º") + strText;
		strText = g_sLangTxt_RepeatResultInfo + strText;
		AddString(strText);
		SetItemData(nRepeatCount, nRepeatCount+1);
	}
}

long CRepeatComboBox::GetRepeatIndex()
{
	return GetNumber()-1;
}

