#ifndef _SmartTestInterface_h__
#define _SmartTestInterface_h__

namespace SmartTest 
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
		long TestPoint(LPCTSTR strTestID, long nDeviceIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strTestID, nDeviceIndex);
			return result;
		}
		long TestBelow(LPCTSTR strTestID, long nDeviceIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strTestID, nDeviceIndex);
			return result;
		}
		long OpenGbrptFile(LPCTSTR strFilePath, long nDeviceIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strFilePath, nDeviceIndex);
			return result;
		}
		CString GetTestItemReports(LPCTSTR strTestID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strTestID);
			return result;
		}
		LONG SetAppVisible(LONG nVisible)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nVisible);
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

	// CDeviceTest 包装类

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

	// CTestReport 包装类

	class CTestReport : public COleDispatchDriver
	{
	public:
		CTestReport(){} // 调用 COleDispatchDriver 默认构造函数
		CTestReport(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CTestReport(const CTestReport& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ITestReport 方法
	public:
		CString GetAllItems(LPCTSTR strMode)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strMode);
			return result;
		}
		CString GetDeviceModel()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long GetCount()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		CString GetItemReport(LPCTSTR varItemIndex)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, varItemIndex);
			return result;
		}
		CString GetItemTestState(LPCTSTR varItemIndex)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, varItemIndex);
			return result;
		}

		// ITestReport 属性
	public:

	};

	// CTestItemBase 包装类

	class CTestItemBase : public COleDispatchDriver
	{
	public:
		CTestItemBase(){} // 调用 COleDispatchDriver 默认构造函数
		CTestItemBase(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CTestItemBase(const CTestItemBase& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ITestItemBase 方法
	public:

		// ITestItemBase 属性
	public:

	};

};

#endif // _SmartTestInterface_h__

