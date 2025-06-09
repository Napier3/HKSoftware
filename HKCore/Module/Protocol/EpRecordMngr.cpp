#include "StdAfx.h"
#include "EpRecordMngr.h"

CEpRecordMngr::CEpRecordMngr()
{
}

CEpRecordMngr::~CEpRecordMngr(void)
{
	m_astrFrameID.RemoveAll();
}

LONG CEpRecordMngr::RecordFrame(const CString &strPkgID)
{
	if (!IsFrameIDExist(strPkgID))
	{
		m_astrFrameID.Add(strPkgID);
	}

	return m_astrFrameID.GetCount();
}

LONG CEpRecordMngr::UnRecordFrame(const CString &strPkgID)
{
	BOOL bTrue = FALSE;
	long nCount = m_astrFrameID.GetCount();
	long nIndex = 0;
	CString strText;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strText = m_astrFrameID.GetAt(nIndex);

		if (strText == strPkgID)
		{
			m_astrFrameID.RemoveAt(nIndex);
			break;
		}
	}

	return 0;
}

BOOL CEpRecordMngr::IsFrameIDExist(const CString &strPkgID)
{
	BOOL bTrue = FALSE;
	long nCount = m_astrFrameID.GetCount();
	long nIndex = 0;
	CString strText;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strText = m_astrFrameID.GetAt(nIndex);

		if (strText == strPkgID)
		{
			bTrue = TRUE;
			break;
		}
	}

	return bTrue;
}

void CEpRecordMngr::AddFrame(CExBaseObject *pPkg)
{
	CAutoSimpleLock oLock(m_oAutoCriticSection);
	AddTail(pPkg);
}

void CEpRecordMngr::DeleteAllFrame()
{
	CAutoSimpleLock oLock(m_oAutoCriticSection);
	DeleteAll();
}

