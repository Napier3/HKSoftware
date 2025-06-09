#include "stdafx.h"
#include "SmartTestInterfaceApp.h"
#include "../../Module/API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSmartTestInterfaceApp *g_theSmartTestInterfaceApp = NULL;

CSmartTestInterfaceApp::CSmartTestInterfaceApp()
{
	g_theSmartTestInterfaceApp = this;
}

CSmartTestInterfaceApp::~CSmartTestInterfaceApp()
{

}

BOOL CSmartTestInterfaceApp::InitSmartTestAp()
{
	GetTestAppMngr();

	return TRUE;
}

void CSmartTestInterfaceApp::ExitSmartTestApp()
{
	if (m_oTestAppMngr == NULL)
	{
		return;
	}

	try
	{
//		m_oTestAppMngr.CloseTest(_T(""));
		m_oTestAppMngr.ReleaseDispatch();
	}
	catch (...)
	{
		
	}

	m_oTestAppMngr = NULL;
}

SmartTest::CTestAppMngr CSmartTestInterfaceApp::GetTestAppMngr()
{
	if (m_oTestAppMngr != NULL)
	{
		return m_oTestAppMngr;
	}

	try
	{
		m_oTestAppMngr.CreateDispatch(_T("SmartTest.TestAppMngr"));
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("******调用SmartTest.exe异常******"));
	}
	
	return m_oTestAppMngr;
}

long CSmartTestInterfaceApp::CreateTest(const CString &strTestID)
{
	SmartTest::CTestAppMngr oTestAppMngr = GetTestAppMngr();

	if (oTestAppMngr == NULL)
	{
		AfxMessageBox(_T("没有注册SmartTest"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

	m_oAtsRpcTestDefine.m_strID = strTestID;
	CString strTestDefine;
	m_oAtsRpcTestDefine.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strTestDefine);
	
	//写入临时记录文件，用于调试，不影响程序运行
	CString strFile;
	strFile = _P_GetBinPath();
	strFile += _T("$CreateTest.txt");
	m_oAtsRpcTestDefine.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	
	CFile oFile;
	strFile = ChangeFilePostfix(strFile, _T("txt"));
	oFile.Open(strFile, CFile::modeCreate | CFile::modeWrite);
	oFile.Write(strTestDefine, strTestDefine.GetLength());
	oFile.Close();

	try
	{
		m_oTestAppMngr.CreateTest(strTestDefine);
	}
	catch (...)
	{
		return -2;
	}

	return 0;
}

long CSmartTestInterfaceApp::BeginTest(const CString &strTestID)
{
	SmartTest::CTestAppMngr oTestAppMngr = GetTestAppMngr();

	if (oTestAppMngr == NULL)
	{
		AfxMessageBox(_T("没有注册SmartTest"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

	try
	{
		oTestAppMngr.BeginTest(strTestID);
	}
	catch (...)
	{
		return -2;
	}

	return 0;
}

long CSmartTestInterfaceApp::StopTest(const CString &strTestID)
{
	try
	{
		long nRet = m_oTestAppMngr.StopTest(strTestID);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("       【 CSmartTestInterfaceApp::StopTest】发送停止测试命令！"));
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

long CSmartTestInterfaceApp::Retest(const CString &strTestID, const CString &strCommConfig)
{
	try
	{
		m_oTestAppMngr.Retest(strTestID, strCommConfig);
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

long CSmartTestInterfaceApp::ExportRpt(const CString &strTestID)
{
	try
	{
		m_oTestAppMngr.ExportRpt(strTestID);
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

long CSmartTestInterfaceApp::CloseTest(const CString &strTestID)
{
	try
	{
		m_oTestAppMngr.CloseTest(strTestID);
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

long CSmartTestInterfaceApp::ViewItemRpt(const CString &strTestID, long nDeviceIndex, long nItemIndex)
{
	try
	{
		m_oTestAppMngr.ViewItemRpt(strTestID, nDeviceIndex, nItemIndex);
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

long CSmartTestInterfaceApp::TestAllInlegibleItems(const CString &strTestID)
{
	try
	{
		m_oTestAppMngr.TestAllInlegibleItems(strTestID);
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

long CSmartTestInterfaceApp::TestPoint(const CString &strTestID, long nDeviceIndex)
{
	try
	{
		long nRet = m_oTestAppMngr.TestPoint(strTestID, nDeviceIndex);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("       【 CSmartTestInterfaceApp::TestPoint】发送测试当前项命令！"));
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

long CSmartTestInterfaceApp::TestBelow(const CString &strTestID, long nDeviceIndex)
{
	try
	{
		m_oTestAppMngr.TestBelow(strTestID, nDeviceIndex);
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

long CSmartTestInterfaceApp::OpenGbrptFile(const CString &strFilePath, long nDeviceIndex)
{
	SmartTest::CTestAppMngr oTestAppMngr = GetTestAppMngr();

	if (oTestAppMngr == NULL)
	{
		AfxMessageBox(_T("没有注册SmartTest"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

	try
	{
		m_oTestAppMngr.OpenGbrptFile(strFilePath, nDeviceIndex);
	}
	catch (...)
	{
		return -2;
	}

	return 0;
}

CString CSmartTestInterfaceApp::GetAllTestItems(const CString &strTestID)
{
	CString strXmlData;
	try
	{
		strXmlData = m_oTestAppMngr.GetAllTestItems(strTestID);
	}
	catch (...)
	{

	}

	return strXmlData;
}

CString CSmartTestInterfaceApp::GetTestItemReports(const CString &strTestID)
{
	CString strXmlData;
	try
	{
		strXmlData = m_oTestAppMngr.GetTestItemReports(strTestID);
	}
	catch (...)
	{

	}

	return strXmlData;
}

long CSmartTestInterfaceApp::SetAppVisible(long nVisible)
{
	try
	{
		m_oTestAppMngr.SetAppVisible(nVisible);
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
LONG TES_OnItemStateChanged(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, LPCTSTR strItemID, LPCTSTR strState)
{
	ASSERT(pWnd != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);
	pWnd->PostMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnItemStateChanged);
	return 0;
}

LONG TES_OnTestFinished(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	ASSERT(pWnd != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, nReportIndex, 0, _T(""), _T(""));
	pWnd->PostMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnTestFinished);
	return 0;
}

LONG TES_OnTestStoped(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	ASSERT(pWnd != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, nReportIndex, 0, _T(""), _T(""));
	pWnd->PostMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnTestStoped);
	return 0;
}

LONG TES_OnExportRptFinished(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	ASSERT(pWnd != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, nReportIndex, 0, _T(""), _T(""));
	pWnd->PostMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnExportRptFinished);
	return 0;
}

LONG TES_OnTestAppEvent(CWnd *pWnd, LPCTSTR strTestID, LPCTSTR strEvent)
{
	ASSERT(pWnd != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, 0, 0, 0, _T(""), strEvent);
	pWnd->PostMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnTestAppEvent);
	return 0;
}

LONG TES_OnEngineEvent(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LPCTSTR strEvent)
{
	ASSERT(pWnd != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, 0, 0, _T(""), strEvent);
	pWnd->PostMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnEngineEvent);
	return 0;
}

LONG TES_OnTestCreated(CWnd *pWnd, LPCTSTR strTestID)
{
	ASSERT(pWnd != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, 0, 0, 0, _T(""), _T(""));
	pWnd->PostMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnTestCreated);
	return 0;
}

LONG TES_OnOpenGbrptFileFailed(CWnd *pWnd, LPCTSTR strTestID)
{
	ASSERT(pWnd != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, 0, 0, 0, _T(""), _T(""));
	pWnd->PostMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnOpenGbrptFileFailed);
	return 0;
}

//shaolie 20210511
LONG TES_OnItemStateChanged(CWinThread *pThread, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, LPCTSTR strItemID, LPCTSTR strState)
{
	ASSERT(pThread != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);
	pThread->PostThreadMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnItemStateChanged);
	return 0;
}

LONG TES_OnTestFinished(CWinThread *pThread, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	ASSERT(pThread != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, nReportIndex, 0, _T(""), _T(""));
	pThread->PostThreadMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnTestFinished);
	return 0;
}

LONG TES_OnTestStoped(CWinThread *pThread, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	ASSERT(pThread != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, nReportIndex, 0, _T(""), _T(""));
	pThread->PostThreadMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnTestStoped);
	return 0;
}

LONG TES_OnExportRptFinished(CWinThread *pThread, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	ASSERT(pThread != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, nReportIndex, 0, _T(""), _T(""));
	pThread->PostThreadMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnExportRptFinished);
	return 0;
}

LONG TES_OnTestAppEvent(CWinThread *pThread, LPCTSTR strTestID, LPCTSTR strEvent)
{
	ASSERT(pThread != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, 0, 0, 0, _T(""), strEvent);
	pThread->PostThreadMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnTestAppEvent);
	return 0;
}

LONG TES_OnEngineEvent(CWinThread *pThread, LPCTSTR strTestID, LONG nDeviceIndex, LPCTSTR strEvent)
{
	ASSERT(pThread != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, 0, 0, _T(""), strEvent);
	pThread->PostThreadMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnEngineEvent);
	return 0;	
}

LONG TES_OnTestCreated(CWinThread *pThread, LPCTSTR strTestID)
{
	ASSERT(pThread != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, 0, 0, 0, _T(""), _T(""));
	pThread->PostThreadMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnTestCreated);
	return 0;
}

LONG TES_OnOpenGbrptFileFailed(CWinThread *pThread, LPCTSTR strTestID)
{
	ASSERT(pThread != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, 0, 0, 0, _T(""), _T(""));
	pThread->PostThreadMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnOpenGbrptFileFailed);
	return 0;
}