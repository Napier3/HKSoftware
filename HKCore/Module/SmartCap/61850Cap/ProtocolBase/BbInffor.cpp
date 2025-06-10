#include "stdafx.h"
#include "BbInffor.h"


CBbInffor::CBbInffor(const CString &strID, BYTE &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = val;
}

CBbInffor::CBbInffor(const CString &strID, short &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = val;
}

CBbInffor::CBbInffor(const CString &strID, WORD &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = val;
}

CBbInffor::CBbInffor(const CString &strID, DWORD &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = val;
}

CBbInffor::CBbInffor(const CString &strID, long &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = val;
}

CBbInffor::CBbInffor(const CString &strID, float &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = val;
}

CBbInffor::CBbInffor(const CString &strID, double &val, long nDxBegin, long nDxEnd)
{
	m_strID = strID;
	m_nDxBegin = nDxBegin;
	m_nDxEnd = nDxEnd;
	m_var = val;
}

CBbInffor::CBbInffor(const CString &strID, const CString &val)
{
	m_strID = strID;
	m_nDxBegin = -1;
	m_nDxEnd = -1;
	m_var = val;
}

// CBbInffor::CBbInffor(const CString &strID, TIME64 &val, long nDxBegin, long nDxEnd)
// {
// 	m_strID = strID;
// 	m_nDxBegin = nDxBegin;
// 	m_nDxEnd = nDxEnd;
// 	m_var = &(val.n64Time);
// }


CBbInffor::~CBbInffor(void)
{
	
}

//树形控件相关的操作
void CBbInffor::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	CString strTemp;
	GetBbInfor(strTemp);

	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strTemp, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

void CBbInffor::GetBbInfor(CString &strInfor)
{
	CString strVal = m_var.ToString();

	if (m_nDxEnd < 0)
	{
        strInfor.Format(_T("%s(D%d) : %s"), m_strID.GetString(), m_nDxBegin, strVal.GetString());
	}
	else
	{
        strInfor.Format(_T("%s(D%d ~ D%d) : %s"), m_strID.GetString(), m_nDxBegin, m_nDxEnd, strVal.GetString());
	}
}


void CBbInffor::GetBbInforVal(CString &strInfor, CString &strDesc)
{
// 	if (m_var.vt == CVariantDataAddress::VDOT_N64)
// 	{
// 		TIME64 tm;
// 		tm.n64Time = *m_var.n64Val;
// 		_TIME64_To_String(tm, strInfor);	
// 		strDesc = strInfor;
// 	}
// 	else
	{
		strInfor = m_var.ToString();
//		strDesc = _GetFrameAnalyseStringValue(m_strID, strInfor);
	}
}

