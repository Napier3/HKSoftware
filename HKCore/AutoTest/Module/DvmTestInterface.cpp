#include "stdafx.h"
#include "DvmTestInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
LONG DVM_OnItemStateChanged(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, LPCTSTR strItemID, LPCTSTR strState)
{
	ASSERT(pWnd != NULL);
	CDvmTestEventMsg *pEventMsg = new CDvmTestEventMsg(strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);
	pWnd->PostMessage(WM_DVMTEST_EVENT_SINK, (WPARAM)pEventMsg, DVMTEST_EVENT_OnItemStateChanged);
	return 0;
}

LONG DVM_OnTestFinished(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	ASSERT(pWnd != NULL);
	CDvmTestEventMsg *pEventMsg = new CDvmTestEventMsg(strTestID, nDeviceIndex, nReportIndex, 0, _T(""), _T(""));
	pWnd->PostMessage(WM_DVMTEST_EVENT_SINK, (WPARAM)pEventMsg, DVMTEST_EVENT_OnTestFinished);
	return 0;
}

LONG DVM_OnTestStoped(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	ASSERT(pWnd != NULL);
	CDvmTestEventMsg *pEventMsg = new CDvmTestEventMsg(strTestID, nDeviceIndex, nReportIndex, 0, _T(""), _T(""));
	pWnd->PostMessage(WM_DVMTEST_EVENT_SINK, (WPARAM)pEventMsg, DVMTEST_EVENT_OnTestStoped);
	return 0;
}

LONG DVM_OnExportRptFinished(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	ASSERT(pWnd != NULL);
	CDvmTestEventMsg *pEventMsg = new CDvmTestEventMsg(strTestID, nDeviceIndex, nReportIndex, 0, _T(""), _T(""));
	pWnd->PostMessage(WM_DVMTEST_EVENT_SINK, (WPARAM)pEventMsg, DVMTEST_EVENT_OnExportRptFinished);
	return 0;
}

LONG DVM_OnTestAppEvent(CWnd *pWnd, LPCTSTR strTestID, LPCTSTR strEvent)
{
	ASSERT(pWnd != NULL);
	CDvmTestEventMsg *pEventMsg = new CDvmTestEventMsg(strTestID, 0, 0, 0, _T(""), strEvent);
	pWnd->PostMessage(WM_DVMTEST_EVENT_SINK, (WPARAM)pEventMsg, DVMTEST_EVENT_OnTestAppEvent);
	return 0;
}

LONG DVM_OnEngineEvent(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LPCTSTR strEvent)
{
	ASSERT(pWnd != NULL);
	CDvmTestEventMsg *pEventMsg = new CDvmTestEventMsg(strTestID, nDeviceIndex, 0, 0, _T(""), strEvent);
	pWnd->PostMessage(WM_DVMTEST_EVENT_SINK, (WPARAM)pEventMsg, DVMTEST_EVENT_OnEngineEvent);
	return 0;
}

LONG DVM_OnTestCreated(CWnd *pWnd, LPCTSTR strTestID)
{
	ASSERT(pWnd != NULL);
	CDvmTestEventMsg *pEventMsg = new CDvmTestEventMsg(strTestID, 0, 0, 0, _T(""), _T(""));
	pWnd->PostMessage(WM_DVMTEST_EVENT_SINK, (WPARAM)pEventMsg, DVMTEST_EVENT_OnTestCreated);
	return 0;
}

