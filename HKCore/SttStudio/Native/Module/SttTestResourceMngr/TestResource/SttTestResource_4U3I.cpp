#include "stdafx.h"
#include "SttTestResource_4U3I.h"

CSttTestResource_4U3I::CSttTestResource_4U3I(void)
{
}

CSttTestResource_4U3I::~CSttTestResource_4U3I(void)
{
}

void CSttTestResource_4U3I::CreateSoftResource()
{
	DeleteAll();
	AddNewData(_T("Ua"), _T("U1"));
	AddNewData(_T("Ub"), _T("U2"));
	AddNewData(_T("Uc"), _T("U3"));
	AddNewData(_T("U0"), _T("U4"));
	AddNewData(_T("Ia"), _T("I1"));
	AddNewData(_T("Ib"), _T("I2"));
	AddNewData(_T("Ic"), _T("I3"));
}

void CSttTestResource_4U3I::InitAfterCreated()
{
	CSttTestResourceBase::InitAfterCreated();
	POS pos = GetHeadPosition();
	CSttChResource *pCh = NULL;

	while(pos)
	{
		pCh = (CSttChResource *)GetNext(pos);

		if (pCh->IsVolCh())
		{
			if (pCh->GetChIndex()>4)
			{
				Delete(pCh);
			}
		} 
		else
		{
			if (pCh->GetChIndex()>3)
			{
				Delete(pCh);
			}
		}
	}

	long nCurChNum = m_oCurChRsListRef.GetCount();
	long nVolChNum = m_oVolChRsListRef.GetCount();
	CString strName,strID;

	for (int nIndex = nVolChNum;nIndex<4;nIndex++)
	{
		strName.Format(_T("U%ld"),nIndex+1);
		strID = strName;
		AddNewData(strName, strID);
	}

	for (int nIndex = nCurChNum;nIndex<3;nIndex++)
	{
		strName.Format(_T("I%ld"),nIndex+1);
		strID = strName;
		AddNewData(strName, strID);
	}
}



