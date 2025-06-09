//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceChRecordMngr.cpp  CCapDeviceChRecordMngr


#include "stdafx.h"
#include "CapDeviceChRecordMngr.h"

//////////////////////////////////////////////////////////////////////////
CCapDeviceChRecord::CCapDeviceChRecord()
{
	m_pRecfCh = NULL;
	m_crColor = RGB(255, 255, 0);
	m_nMinValue = 6553600;
	m_nMaxValue = -6553600;
}

CCapDeviceChRecord::~CCapDeviceChRecord()
{

}

void CCapDeviceChRecord::CapRecord(WORD wValue)
{
	m_oBufferUShort.AddValue(wValue);
}

void CCapDeviceChRecord::CapRecord(long wValue)
{
	
}

void CCapDeviceChRecord::CapRecord(float fValue)
{

}

void CCapDeviceChRecord::CapRecord(double dValue)
{

}


//////////////////////////////////////////////////////////////////////////
CCapDeviceSmvChRecord::CCapDeviceSmvChRecord()
{
	m_fChRate = 1.0f;
	m_oBufferUShort.SetBufferLength(CAP_RECORD_POINTS);
}

CCapDeviceSmvChRecord::~CCapDeviceSmvChRecord()
{


}

//////////////////////////////////////////////////////////////////////////
CCapDeviceGooseChRecord::CCapDeviceGooseChRecord()
{

}

CCapDeviceGooseChRecord::~CCapDeviceGooseChRecord()
{

}


//////////////////////////////////////////////////////////////////////////
CCapDeviceChRecordMngr::CCapDeviceChRecordMngr()
{
	m_pRecordDevice = NULL;
}

CCapDeviceChRecordMngr::~CCapDeviceChRecordMngr()
{
	m_listRemove.DeleteAll();
}

CCapDeviceChRecord* CCapDeviceChRecordMngr::FindByCh(CCapDeviceChBase *pCh)
{
	POS pos = GetHeadPosition();
	CCapDeviceChRecord *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CCapDeviceChRecord *)GetNext(pos);

		if (p->m_pRecfCh == pCh)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CCapDeviceChRecord* CCapDeviceChRecordMngr::AddRecordCh(CCapDeviceChBase *pCh)
{
	CCapDeviceChRecord *pFind = FindByCh(pCh);

	if (pFind != NULL)
	{
		return pFind;
	}

	m_listRemove.DeleteAll();

	UINT nClassID = pCh->GetClassID();

	if (nClassID == CPDCLASSID_GOOSECH)
	{
		pFind = new CCapDeviceGooseChRecord();
		pFind->m_pRecfCh = pCh;
		AddNewChild(pFind);
	}
	else if (nClassID == CPDCLASSID_SMVCH)
	{
		pFind = new CCapDeviceSmvChRecord();
		pFind->m_pRecfCh = pCh;
		AddNewChild(pFind);
	}

	if (pFind != NULL)
	{
		pCh->AttachCapRecord(pFind);
	}

	return pFind;
}

CCapDeviceChRecord* CCapDeviceChRecordMngr::RemoveRecord(CCapDeviceChBase *pCh)
{
	CCapDeviceChRecord *pFind = FindByCh(pCh);

	if (pFind != NULL)
	{
		if (m_listRemove.Find(pFind) == NULL)
		{
			m_listRemove.AddTail(pFind);
		}

		POS pos = Find(pFind);

		if (pos != NULL)
		{
			RemoveAt(pos);
		}
	}

	return pFind;
}

void CCapDeviceChRecordMngr::BeginCap(BOOL bClearDevices)
{
	if (bClearDevices)
	{
		m_pRecordDevice = NULL;
		DeleteAll();
	}
	else
	{
		if (m_pRecordDevice != NULL)
		{
			m_pRecordDevice->BeginCap();
		}
	}
}

