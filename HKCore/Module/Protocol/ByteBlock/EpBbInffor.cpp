#include "StdAfx.h"
#include "EpBbInffor.h"


CEpBbInffor::CEpBbInffor(const CString &strID, BYTE &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = &val;
}

CEpBbInffor::CEpBbInffor(const CString &strID, short &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = &val;
}

CEpBbInffor::CEpBbInffor(const CString &strID, long &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = &val;
}

CEpBbInffor::CEpBbInffor(const CString &strID, float &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = &val;
}

CEpBbInffor::CEpBbInffor(const CString &strID, double &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = &val;
}

CEpBbInffor::CEpBbInffor(const CString &strID, EPTIME64 &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = &(val.n64Time);
}


CEpBbInffor::~CEpBbInffor(void)
{
	
}

//树形控件相关的操作
void CEpBbInffor::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	CString strTemp;
	GetBbInfor(strTemp);

	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strTemp, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

void CEpBbInffor::GetBbInfor(CString &strInfor)
{
	CString strVal = m_var.ToString();

	if (m_nDxEnd < 0)
	{
		strInfor.Format(_T("%s(D%d) : %s"), m_strID, m_nDxBegin, strVal);
	}
	else
	{
		strInfor.Format(_T("%s(D%d ~ D%d) : %s"), m_strID, m_nDxBegin, m_nDxEnd, strVal);
	}
}


void CEpBbInffor::GetBbInforVal(CString &strInfor, CString &strDesc)
{
	if (m_var.vt == CVariantDataAddress::VDOT_N64)
	{
		EPTIME64 tm;
		tm.n64Time = *m_var.n64Val;
		Ep_EPTIME64_To_String(tm, strInfor);	
		strDesc = strInfor;
	}
	else
	{
		strInfor = m_var.ToString();
		strDesc = Ep_GetFrameAnalyseStringValue(m_strID, strInfor);
	}
}

