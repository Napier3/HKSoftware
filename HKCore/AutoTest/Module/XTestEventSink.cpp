#include "stdafx.h"
#include "XTestEventSink.h"

CTestEventSinkMngr* CTestEventSinkMngr::g_pTestEventSinkMngr = NULL;
long CTestEventSinkMngr::g_nTestEventSinkMngr = 0;

CTestEventSinkMngr::CTestEventSinkMngr()
{

}

CTestEventSinkMngr::~CTestEventSinkMngr()
{

}

CTestEventSinkMngr* CTestEventSinkMngr::Create()
{
	g_nTestEventSinkMngr++;

	if (g_nTestEventSinkMngr == 1)
	{
		g_pTestEventSinkMngr = new CTestEventSinkMngr();
	}

	return g_pTestEventSinkMngr;
}

void CTestEventSinkMngr::Release()
{
	g_nTestEventSinkMngr--;

	if (g_nTestEventSinkMngr == 0)
	{
		delete g_pTestEventSinkMngr;
		g_pTestEventSinkMngr = NULL;
	}
}

void CTestEventSinkMngr::AddEventSinkEx(const CString &strProgID)
{
	AddEventSink(strProgID);
}

CTestEventSinkDispatch* CTestEventSinkMngr::AddEventSink(const CString &strProgID)
{
	CTestEventSinkDispatch *pFind = (CTestEventSinkDispatch*)FindByID(strProgID);

	if (pFind == NULL)
	{
		pFind = new CTestEventSinkDispatch();
		pFind->CreateDispatch(strProgID);

		pFind->m_strID = strProgID;

		if (pFind->m_lpDispatch == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Create EventSink [%s] failed"), strProgID);
			delete pFind;
			pFind = NULL;
		}
		else
		{
			AddTail(pFind);
		}
	}

	return pFind;
}

CTestEventSinkDispatch* CTestEventSinkMngr::AddEventSink(const CString &strProgID, const CString &strDeviceID)
{
	CTestEventSinkDispatch *pNew = AddEventSink(strProgID);

	return pNew;
}


void CTestEventSinkMngr::DeleteEventSink(const CString &strProgID)
{
	CTestEventSinkDispatch *pFind = (CTestEventSinkDispatch*)FindByID(strProgID);

	if (pFind != NULL)
	{
		Delete(pFind);
	}
}


long CTestEventSinkMngr::OnItemStateChanged(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, LPCTSTR strItemID, LPCTSTR strState)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnItemStateChanged(strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);
		}
		catch (...)
		{
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnTestFinished(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnTestFinished(strTestID, nDeviceIndex, nReportIndex);
		}
		catch (...)
		{
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnTestStoped(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnTestStoped(strTestID, nDeviceIndex, nReportIndex);
		}
		catch (...)
		{
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnExportRptFinished(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
{
// 	POS pos = GetHeadPosition();
// 	CTestEventSinkDispatch *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CTestEventSinkDispatch*)GetNext(pos);
// 		ASSERT (p->m_lpDispatch != NULL);
// 
// 		if (p->m_lpDispatch == NULL)
// 		{
// 			continue;
// 		}
// 
// 		try
// 		{
// 			p->OnExportRptEvent(strTestID, nDeviceIndex, nReportIndex);
// 		}
// 		catch (...)
// 		{
// 		}
// 	}

	return 0;
}

long CTestEventSinkMngr::OnTestAppEvent(LPCTSTR strTestID, LPCTSTR strEvent)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnTestAppEvent(strTestID, strEvent);
		}
		catch (...)
		{
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnEngineEvent(LPCTSTR strTestID, long nDeviceIndex, LPCTSTR strEvent)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnEngineEvent(strTestID, nDeviceIndex, strEvent);
		}
		catch (...)
		{
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnTestCreated(LPCTSTR strTestID)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnTestCreated(strTestID);
		}
		catch (...)
		{
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnOpenGbrptFileFailed(LPCTSTR strTestID)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnOpenGbrptFileFailed(strTestID);
		}
		catch (...)
		{
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnTestProcess(LPCTSTR strDeviceID, LPCTSTR strTestID,  long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, LPCTSTR strDeviceState)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnTestProcess(strDeviceID, strTestID, nTotalItems, nCurrItem, nTotalTime, nRemainTime, strDeviceState);
		}
		catch (...)
		{
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnTestStarted(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnTestStarted(strTestID, nDeviceIndex, nReportIndex);
		}
		catch (...)
		{
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnExportRptEvent(LPCTSTR strTestID, LPCTSTR strEvent, long nDeviceIndex, long nReportIndex)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnExportRptEvent(strTestID, strEvent, nDeviceIndex, nReportIndex);
		}
		catch (...)
		{
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnUploadRptFile(LPCTSTR strDeviceID, LPCTSTR strFiles)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnUploadRptFile(strDeviceID, strFiles);
		}
		catch (...)
		{
			
		}
	}

	return 0;
}

long CTestEventSinkMngr::OnInputData(LPCTSTR strDatas, LPCTSTR strMsgs)
{
	POS pos = GetHeadPosition();
	CTestEventSinkDispatch *p = NULL;

	while (pos != NULL)
	{
		p = (CTestEventSinkDispatch*)GetNext(pos);
		ASSERT (p->m_lpDispatch != NULL);

		if (p->m_lpDispatch == NULL)
		{
			continue;
		}

		try
		{
			p->OnInputData(strDatas, strMsgs);
		}
		catch (...)
		{
		}
	}

	return 0;
}