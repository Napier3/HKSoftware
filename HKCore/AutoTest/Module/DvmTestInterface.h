#ifndef _DvmTestInterface_h__
#define _DvmTestInterface_h__

namespace DvmTest 
{
	// CTestAppMngr 包装类
	class CTestAppMngr : public COleDispatchDriver
	{
	public:
		CTestAppMngr(){} // 调用 COleDispatchDriver 默认构造函数
		CTestAppMngr(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CTestAppMngr(const CTestAppMngr& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ITestAppMngr 方法
	public:
		long GetCount()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		long CreateTest(LPCTSTR strTestCreateXml)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestCreateXml);
			return result;
		}
		long BeginTest(LPCTSTR strTestID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID);
			return result;
		}
		long StopTest(LPCTSTR strTestID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID);
			return result;
		}
		long TestAllInlegibleItems(LPCTSTR strTestID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID);
			return result;
		}
		long CloseTest(LPCTSTR strTestID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID);
			return result;
		}
		long ExportRpt(LPCTSTR strTestID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID);
			return result;
		}
		long ViewItemRpt(LPCTSTR strTestID, long nReportIndex, long nItemIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, nReportIndex, nItemIndex);
			return result;
		}
		CString GetAllTestItems(LPCTSTR strTestID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strTestID);
			return result;
		}
		CString GetTestItemReport(LPCTSTR strTestID, long nReportIndex, long nItemIndex)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strTestID, nReportIndex, nItemIndex);
			return result;
		}
		long TestItem(LPCTSTR strTestID, long nItemIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, nItemIndex);
			return result;
		}
		LPDISPATCH GetDeviceTest(LPCTSTR strTestID, long nDeviceIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strTestID, nDeviceIndex);
			return result;
		}
		long AddEventSink(LPCTSTR bstrEventSinkProgID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrEventSinkProgID);
			return result;
		}
		long RemoveEventSink(LPCTSTR bstrEventSinkProgID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrEventSinkProgID);
			return result;
		}
		long ClearReport(LPCTSTR strTestID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID);
			return result;
		}
		long Retest(LPCTSTR strTestID, LPCTSTR strCommConfig)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, strCommConfig);
			return result;
		}

		// ITestAppMngr 属性
	public:

	};


	// CTestApplication 包装类

	class CTestApplication : public COleDispatchDriver
	{
	public:
		CTestApplication(){} // 调用 COleDispatchDriver 默认构造函数
		CTestApplication(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CTestApplication(const CTestApplication& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ITestApplication 方法
	public:
		long GetCount()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		long BeginTest()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long StopTest()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long TestAllInlegibleItems()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long CloseTest()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long ExportRpt()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long ViewItemRpt(long nReportIndex, long nItemIndex)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nReportIndex, nItemIndex);
			return result;
		}
		CString GetAllTestItems()
		{
			CString result;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetTestItemReport(long nReportIndex, long nItemIndex)
		{
			CString result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, nReportIndex, nItemIndex);
			return result;
		}
		long TestItem(long nItemIndex)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nItemIndex);
			return result;
		}

		// ITestApplication 属性
	public:

	};

	class CDeviceTest : public COleDispatchDriver
	{
	public:
		CDeviceTest(){} // 调用 COleDispatchDriver 默认构造函数
		CDeviceTest(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CDeviceTest(const CDeviceTest& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


	// IDeviceTest 方法
	public:
		long GetCount()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		long ExportRpt()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long ViewItemRpt(long nReportIndex, long nItemIndex)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nReportIndex, nItemIndex);
			return result;
		}
		CString GetAllTestItems()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetTestItemReport(long nReportIndex, long nItemIndex)
		{
			CString result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, nReportIndex, nItemIndex);
			return result;
		}
		CString GetDeviceModel()
		{
			CString result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long ClearReport(LPCTSTR strTestID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID);
			return result;
		}
		long Retest(LPCTSTR strTestID, LPCTSTR strCommConfig)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, strCommConfig);
			return result;
		}

		// IDeviceTest 属性
	public:

	};

};
//////////////////////////////////////////////////////////////////////////
//
class CDvmTestEventMsg
{
public:
	CDvmTestEventMsg(const CString &strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, const CString &strItemID, const CString &strState)
	{
		m_strTestID = strTestID;
		m_nDeviceIndex = nDeviceIndex;
		m_nReportIndex = nReportIndex;
		m_nItemIndex = nItemIndex;
		m_strItemID = strItemID;
		m_strState = strState;
	}
	virtual ~CDvmTestEventMsg(){}

public:
	CString m_strTestID;
	LONG   m_nDeviceIndex;
	LONG   m_nReportIndex;
	LONG   m_nItemIndex;
	CString m_strItemID;
	CString m_strState;
};

#define WM_DVMTEST_EVENT_SINK   (WM_USER + 1528)

#define DVMTEST_EVENT_OnTestCreated			7
#define DVMTEST_EVENT_OnEngineEvent			6
#define DVMTEST_EVENT_OnTestAppEvent		5
#define DVMTEST_EVENT_OnExportRptFinished	4
#define DVMTEST_EVENT_OnTestStoped			3
#define DVMTEST_EVENT_OnTestFinished		2
#define DVMTEST_EVENT_OnItemStateChanged	1

LONG DVM_OnItemStateChanged(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, LPCTSTR strItemID, LPCTSTR strState);
LONG DVM_OnTestFinished(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG DVM_OnTestStoped(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG DVM_OnExportRptFinished(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG DVM_OnTestAppEvent(CWnd *pWnd, LPCTSTR strTestID, LPCTSTR strEvent);
LONG DVM_OnEngineEvent(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LPCTSTR strEvent);
LONG DVM_OnTestCreated(CWnd *pWnd, LPCTSTR strTestID);

#endif // _DvmTestInterface_h__

