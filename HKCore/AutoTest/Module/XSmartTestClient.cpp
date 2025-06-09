#include "stdafx.h"
#include "XSmartTestClient.h"
#include "../../Module/API/FileApi.h"
#include "..\..\Module\Interface\ComGlobalDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CXSmartTestClient::CXSmartTestClient()
{
}

CXSmartTestClient::~CXSmartTestClient()
{

}

BOOL CXSmartTestClient::InitXSmartTestClient()
{
	GetSmartTest();

	return TRUE;
}

void CXSmartTestClient::ExitXSmartTestClient()
{
	if (m_oSmartTest == NULL)
	{
		return;
	}

	try
	{
		m_oSmartTest.ReleaseDispatch();
	}
	catch (...)
	{
		
	}

	m_oSmartTest = NULL;
}

SmartTest::CSmartTest CXSmartTestClient::GetSmartTest()
{
	if (m_oSmartTest != NULL)
	{
		return m_oSmartTest;
	}

	try
	{
		m_oSmartTest.CreateDispatch(_T("SmartTest.Application"));
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("******调用SmartTest.exe异常******"));
	}
	
	if (m_oSmartTest == NULL)
	{
		AfxMessageBox(_T("没有注册SmartTest"), MB_OK | MB_ICONEXCLAMATION);
	}

	return m_oSmartTest;
}

long CXSmartTestClient::CreateTest(const CString &strTestDefine)
{
	SmartTest::CSmartTest oSmartTest = GetSmartTest();

	if (oSmartTest == NULL)
	{
		return -1;
	}

	//2022-2-5  lijunqing : 通用模块，不使用STT
	//CString strTestDefine;
	//pParas->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strTestDefine);
	
	//写入临时记录文件，用于调试，不影响程序运行
	CString strFile;
	strFile = _P_GetBinPath();
	strFile += _T("$CreateTest.txt");
	//pParas->SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	
	CFile oFile;
	//strFile = ChangeFilePostfix(strFile, _T("txt"));
	oFile.Open(strFile, CFile::modeCreate | CFile::modeWrite);
	oFile.Write(strTestDefine, strTestDefine.GetLength());
	oFile.Close();

	try
	{
		m_oSmartTest.CreateTest(strTestDefine);
	}
	catch (...)
	{
		return -2;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::BeginTest(const CString &strDeviceID)
{
	SmartTest::CSmartTest oSmartTest = GetSmartTest();

	if (oSmartTest == NULL)
	{
		return -1;
	}

	try
	{
		oSmartTest.BeginTest(strDeviceID);
	}
	catch (...)
	{
		return -2;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::StopTest(const CString &strDeviceID)
{
	try
	{
		long nRet = m_oSmartTest.StopTest(strDeviceID);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("       【 CSmartTestInterfaceApp::StopTest】发送停止测试命令！"));
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::Retest(const CString &strDeviceID, const CString &strCommConfig)
{
	try
	{
		m_oSmartTest.Retest(strDeviceID, strCommConfig);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::ExportRpt(const CString &strDeviceID)
{
	try
	{
		m_oSmartTest.ExportRpt(strDeviceID);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::CloseTest(const CString &strDeviceID)
{
	try
	{
		m_oSmartTest.CloseTest(strDeviceID);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::ViewItemRpt(const CString &strDeviceID, long nItemIndex)
{
	try
	{
		m_oSmartTest.ViewItemRpt(strDeviceID, nItemIndex);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::TestAllInlegibleItems(const CString &strDeviceID)
{
	try
	{
		m_oSmartTest.TestAllInlegibleItems(strDeviceID);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::TestPoint(const CString &strDeviceID, const CString &strItemPath)
{
	try
	{
		long nRet = m_oSmartTest.TestPoint(strDeviceID, strItemPath);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("       【 CSmartTestInterfaceApp::TestPoint】发送测试当前项命令！"));
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::TestBelow(const CString &strDeviceID, const CString &strItemPath)
{
	try
	{
		m_oSmartTest.TestBelow(strDeviceID, strItemPath);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::OpenGbrptFile(const CString &strFilePath, long nDeviceIndex)
{
	SmartTest::CSmartTest oSmartTest = GetSmartTest();

	if (oSmartTest == NULL)
	{
		return -1;
	}

	try
	{
		m_oSmartTest.OpenGbrptFile(strFilePath, nDeviceIndex);
	}
	catch (...)
	{
		return -2;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

CString CXSmartTestClient::GetAllTestItems(const CString &strDeviceID)
{
	CString strXmlData;
	try
	{
		strXmlData = m_oSmartTest.GetAllTestItems(strDeviceID);
	}
	catch (...)
	{

	}

	return strXmlData;
}

CString CXSmartTestClient::GetTestItemReports(const CString &strDeviceID)
{
	CString strXmlData;
	try
	{
		strXmlData = m_oSmartTest.GetTestItemReports(strDeviceID);
	}
	catch (...)
	{

	}

	return strXmlData;
}

long CXSmartTestClient::SetAppVisible(long nVisible)
{
	try
	{
		m_oSmartTest.SetAppVisible(nVisible);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::FinishInputData(const CString& strDeviceID, const CString& strReports)
{
	try
	{
		m_oSmartTest.FinishInputData(strDeviceID, strReports);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::SetItemStateEx(const CString& strItemPath, long nSelect, long nEnable, long nShow, long nState)
{
	try
	{
		m_oSmartTest.SetItemStateEx(strItemPath, nSelect, nEnable, nShow, nState);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::AddEventSink(const CString &strEventSinkProgID, const CString& strDeviceID)
{
	SmartTest::CSmartTest oSmartTest = GetSmartTest();

	if (oSmartTest == NULL)
	{
		return -1;
	}

	try
	{
		m_oSmartTest.AddEventSink(strEventSinkProgID, strDeviceID);
	}
	catch (...)
	{
		return -2;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::RemoveEventSink(const CString &strEventSinkProgID, const CString& strDeviceID)
{
	try
	{
		m_oSmartTest.RemoveEventSink(strEventSinkProgID, strDeviceID);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::ClearReport(const CString &strDeviceID)
{
	try
	{
		m_oSmartTest.ClearReport(strDeviceID);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::GetReports(const CString &strDeviceID, const CString &strItemPath, char **ppszReports)
{
	try
	{
		VARIANT vReports;

		m_oSmartTest.GetReports(strDeviceID, strItemPath, vReports);

		BYTE *pBuff = NULL;
		long nDataCount = GetDataFromSafeArray_UI1(&pBuff, &vReports);

		if (nDataCount > 0)
		{
			//销毁安全数组，防止内存泄露
			SafeArrayDestroy(V_ARRAY(&vReports));	
			*ppszReports = (char*)pBuff;
			return nDataCount;
		}
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::SetReports(const CString &strDeviceID, const CString &strItemPath, const CString &strReports)
{
	try
	{
		m_oSmartTest.SetReports(strDeviceID, strItemPath, strReports);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::QueryItems(const CString &strDeviceID, const CString &strItemPath, char **ppszItemsUft8)
{
	try
	{
		VARIANT vItems;
		m_oSmartTest.QueryItems(strDeviceID, strItemPath, vItems);

		BYTE *pBuff = NULL;
		long nDataCount = GetDataFromSafeArray_UI1(&pBuff, &vItems);

		if (nDataCount > 0)
		{
			//销毁安全数组，防止内存泄露
			SafeArrayDestroy(V_ARRAY(&vItems));	
			*ppszItemsUft8 = (char*)pBuff;
			return nDataCount;
		}
	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

long CXSmartTestClient::ConfigTest(const CString &strDeviceID, const CString &strConfig)
{
	try
	{
		m_oSmartTest.ConfigTest(strDeviceID, strConfig);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::QueryAtsFile(const CString &strDeviceID, const CString &strConfig)
{
	try
	{
		m_oSmartTest.QueryAtsFile(strDeviceID, strConfig);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

CString CXSmartTestClient::GetDataset(const CString &strDatasetPath)
{
	CString strXmlData;
	try
	{
		strXmlData = m_oSmartTest.GetDataset(strDatasetPath);
	}
	catch (...)
	{

	}

	return strXmlData;
}

long CXSmartTestClient::SetDataset(const CString &strDatasetPath, const CString &strDataset)
{
	try
	{
		m_oSmartTest.SetDataset(strDatasetPath, strDataset);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::RunProcedure(const CString &strProcedureID, const CString &strParas)
{
	try
	{
		m_oSmartTest.RunProcedure(strProcedureID, strParas);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::SetItemState(const CString &strParas)
{
	try
	{
		m_oSmartTest.SetItemState(strParas);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

//2021-7-25  lijunqing  因为返回的文本可能比较大，通过返回CString的方式会多出一次构造析构
//效率相对比较低，所以改为传址返回
long CXSmartTestClient::GetGuideBook(const CString &strDeviceID, char **ppszGuideBookUft8)
{
	try
	{
		VARIANT vGuideBook;
		m_oSmartTest.GetGuideBook(strDeviceID, vGuideBook);

		BYTE *pBuff = NULL;
		long nDataCount = GetDataFromSafeArray_UI1(&pBuff, &vGuideBook);

		if (nDataCount > 0)
		{
			//销毁安全数组，防止内存泄露
			SafeArrayDestroy(V_ARRAY(&vGuideBook));	
			*ppszGuideBookUft8 = (char*)pBuff;
			return nDataCount;
		}
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::GetReportFiles(const CString &strDeviceID, CString &strFile)
{
	try
	{
		strFile = m_oSmartTest.GetReportFiles(strDeviceID);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::GetTotalItemsCount(const CString &strDeviceID, long &nCount)
{
	try
	{
		nCount = m_oSmartTest.GetTotalItemsCount(strDeviceID);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::QueryTestParas(const CString &strDeviceID, CString &strTestParas)
{
	try
	{
		strTestParas = m_oSmartTest.QueryTestParas(strDeviceID);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::SetTestParas(const CString &strDeviceID, CString &strTestParas)
{
	try
	{
		m_oSmartTest.SetTestParas(strDeviceID, strTestParas);
	}
	catch (...)
	{
		return -1;
	}

	return SMART_TEST_COM_EXEC_SUCC;
}

long CXSmartTestClient::AdjustMainWnd(LONG hMainParent, LONG hLogParent)
{
	try
	{
		return m_oSmartTest.AdjustMainWnd(hMainParent, hLogParent);
	}
	catch (...)
	{
		return 0;
	}

	return 0;
}

long CXSmartTestClient::AttatchLogWnd(unsigned long hWnd)
{
	try
	{
		return m_oSmartTest.AttatchLogWnd(hWnd);
	}
	catch (...)
	{
		return 0;
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

LONG TES_OnExportRptEvent(CWnd *pWnd, LPCTSTR strTestID, LPCTSTR strEvnet, LONG nDeviceIndex, LONG nReportIndex)
{
	ASSERT(pWnd != NULL);
	CSmartTestEventMsg *pEventMsg = new CSmartTestEventMsg(strTestID, nDeviceIndex, nReportIndex, 0, _T(""), strEvnet);
	pWnd->PostMessage(WM_SMARTTEST_EVENT_SINK, (WPARAM)pEventMsg, SMARTTEST_EVENT_OnExportRptEvent);
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