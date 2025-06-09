#include "StdAfx.h"
#include "SttTestResource_6U6I.h"

CSttTestResource_6U6I::CSttTestResource_6U6I(void)
{
}

CSttTestResource_6U6I::~CSttTestResource_6U6I(void)
{
}

void CSttTestResource_6U6I::CreateSoftResource()
{
	DeleteAll();
	AddNewData(_T("Ua1"), _T("U1"));
	AddNewData(_T("Ub1"), _T("U2"));
	AddNewData(_T("Uc1"), _T("U3"));
	AddNewData(_T("Ua2"), _T("U4"));
	AddNewData(_T("Ub2"), _T("U5"));
	AddNewData(_T("Uc2"), _T("U6"));

	AddNewData(_T("Ia1"), _T("I1"));
	AddNewData(_T("Ib1"), _T("I2"));
	AddNewData(_T("Ic1"), _T("I3"));
	AddNewData(_T("Ia2"), _T("I4"));
	AddNewData(_T("Ib2"), _T("I5"));
	AddNewData(_T("Ic2"), _T("I6"));
}

void CSttTestResource_6U6I::InitAfterCreated()
{
	CSttTestResourceBase::InitAfterCreated();
	POS pos = GetHeadPosition();
	CSttChResource *pCh = NULL;

	while(pos)
	{
		pCh = (CSttChResource *)GetNext(pos);

		if (pCh->GetChIndex()>6)
		{
			Delete(pCh);
		}
	}

	long nCurChNum = m_oCurChRsListRef.GetCount();
	long nVolChNum = m_oVolChRsListRef.GetCount();
	CString strName,strID;

	for (int nIndex = nCurChNum;nIndex<6;nIndex++)
	{
		strName.Format(_T("I%ld"),nIndex+1);
		strID = strName;
		AddNewData(strName, strID);
	}

	for (int nIndex = nVolChNum;nIndex<6;nIndex++)
	{
		strName.Format(_T("U%ld"),nIndex+1);
		strID = strName;
		AddNewData(strName, strID);
	}
}
