#ifndef _XSmartTestInterface_h__
#define _XSmartTestInterface_h__

namespace SmartTest 
{
	// CSmartTest 包装类
	class CSmartTest : public COleDispatchDriver
	{
	public:
		CSmartTest(){} // 调用 COleDispatchDriver 默认构造函数
		CSmartTest(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CSmartTest(const CSmartTest& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ISmartTest 方法
	public:
		long GetCount()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem()
		{
			LPDISPATCH result;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long CreateTest(LPCTSTR strTestCreateXml)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestCreateXml);
			return result;
		}
		long BeginTest(LPCTSTR strDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID);
			return result;
		}
		long StopTest(LPCTSTR strDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID);
			return result;
		}
		long TestAllInlegibleItems(LPCTSTR strDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID);
			return result;
		}
		long CloseTest(LPCTSTR strDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID);
			return result;
		}
		long ExportRpt(LPCTSTR strDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID);
			return result;
		}
		long ViewItemRpt(LPCTSTR strDeviceID, long nItemIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, nItemIndex);
			return result;
		}
		CString GetAllTestItems(LPCTSTR strDeviceID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDeviceID);
			return result;
		}
		CString GetTestItemReport(LPCTSTR strDeviceID, long nItemIndex)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDeviceID, nItemIndex);
			return result;
		}
		long TestItem(LPCTSTR strDeviceID, long nItemIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, nItemIndex);
			return result;
		}
		LPDISPATCH GetDeviceTest(LPCTSTR strDeviceID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strDeviceID);
			return result;
		}
		long AddEventSink(LPCTSTR bstrEventSinkProgID, LPCTSTR bstrDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrEventSinkProgID, bstrDeviceID);
			return result;
		}
		long RemoveEventSink(LPCTSTR bstrEventSinkProgID, LPCTSTR bstrDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrEventSinkProgID, bstrDeviceID);
			return result;
		}
		long ClearReport(LPCTSTR strDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID);
			return result;
		}
		long Retest(LPCTSTR strDeviceID, LPCTSTR strCommConfig)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, strCommConfig);
			return result;
		}
		long TestPoint(LPCTSTR strDeviceID, LPCTSTR bstrItemPath)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, bstrItemPath);
			return result;
		}
		long TestBelow(LPCTSTR strDeviceID, LPCTSTR bstrItemPath)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, bstrItemPath);
			return result;
		}
		long OpenTestFile(LPCTSTR strFilePath)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFilePath);
			return result;
		}
		void GetReports(LPCTSTR strDeviceID, LPCTSTR strItemPath, VARIANT &vReports)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_VARIANT, (void*)&vReports, parms, strDeviceID, strItemPath);
		}
		long SetReports(LPCTSTR strDeviceID, LPCTSTR strItemPath, LPCTSTR bstrReports)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, strItemPath, bstrReports);
			return result;
		}
		long SetAppVisible(long nVisible)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nVisible);
			return result;
		}
		void QueryItems(LPCTSTR strDeviceID, LPCTSTR strItemPath, VARIANT &vItems)
		{
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x18, DISPATCH_METHOD, VT_VARIANT, (void*)&vItems, parms, strDeviceID, strItemPath);
		}
		long FinishInputData(LPCTSTR strDeviceID, LPCTSTR bstrReports)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, bstrReports);
			return result;
		}
		long ConfigTest(LPCTSTR strDeviceID, LPCTSTR bstrConfig)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, bstrConfig);
			return result;
		}
		long QueryAtsFile(LPCTSTR strDeviceID, LPCTSTR bstrConfig)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, bstrConfig);
			return result;
		}
		CString GetDataset(LPCTSTR strDatasetPath)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDatasetPath);
			return result;
		}
		long SetDataset(LPCTSTR strDatasetPath, LPCTSTR bstrDataset)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDatasetPath, bstrDataset);
			return result;
		}
		long RunProcedure(LPCTSTR strProcedureID, LPCTSTR bstrParas)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strProcedureID, bstrParas);
			return result;
		}
		long SetItemState(LPCTSTR bstrParas)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrParas);
			return result;
		}
		long SetItemStateEx(LPCTSTR bstrItemPath, long nSelect, long nEnable, long nShow, long nState)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrItemPath, nSelect, nEnable, nShow, nState);
			return result;
		}
		void GetGuideBook(LPCTSTR strDeviceID, VARIANT &vGuideBook)
		{
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x21, DISPATCH_METHOD, VT_VARIANT, (void*)&vGuideBook, parms, strDeviceID);
		}
		long OpenGbrptFile(LPCTSTR strFilePath, long nDeviceIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x22, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFilePath, nDeviceIndex);
			return result;
		}
		CString GetTestItemReports(LPCTSTR strDeviceID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x23, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDeviceID);
			return result;
		}
		CString GetReportFiles(LPCTSTR strDeviceID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x24, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDeviceID);
			return result;
		}
		long GetTotalItemsCount(LPCTSTR strDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID);
			return result;
		}
		CString QueryTestParas(LPCTSTR strDeviceID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x26, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDeviceID);
			return result;
		}
		long SetTestParas(LPCTSTR strDeviceID, LPCTSTR strTestParas)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR;
			InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, strTestParas);
			return result;
		}
		long AdjustMainWnd(LONG hMainParent, LONG hLogParent)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_I4;
			InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMainParent, hLogParent);
			return result;
		}
		long AttatchLogWnd(unsigned long hWnd)
		{
			long result;
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hWnd);
			return result;
		}
		// ISmartTest 属性
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
		CString GetDataset(LPCTSTR strDatasetPath)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDatasetPath);
			return result;
		}
		long SetDataset(LPCTSTR strDatasetPath, LPCTSTR bstrDataset)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDatasetPath, bstrDataset);
			return result;
		}
		long RunProcedure(LPCTSTR strProcedureID, LPCTSTR bstrParas)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strProcedureID, bstrParas);
			return result;
		}
		long SetItemState(LPCTSTR bstrParas)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrParas);
			return result;
		}
		long SetItemStateEx(LPCTSTR bstrItemPath, long nSelect, long nEnable, long nShow, long nState)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrItemPath, nSelect, nEnable, nShow, nState);
			return result;
		}

		// IDeviceTest 属性
	public:

	};
	// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类


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
			InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, nDeviceIndex);
			return result;
		}
		long TestBelow(LPCTSTR strTestID, long nDeviceIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, nDeviceIndex);
			return result;
		}
		long OpenGbrptFile(LPCTSTR strFilePath, long nDeviceIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFilePath, nDeviceIndex);
			return result;
		}
		CString GetTestItemReports(LPCTSTR strTestID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strTestID);
			return result;
		}
		long SetAppVisible(long nVisible)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nVisible);
			return result;
		}

		// ITestAppMngr 属性
	public:

	};

	// CTestEventSink 包装类

	class CTestEventSink : public COleDispatchDriver
	{
	public:
		CTestEventSink(){} // 调用 COleDispatchDriver 默认构造函数
		CTestEventSink(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CTestEventSink(const CTestEventSink& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ITestEventSink 方法
	public:
		long OnItemStateChanged(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, LPCTSTR strItemID, LPCTSTR strState)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);
			return result;
		}
		long OnTestFinished(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, nDeviceIndex, nReportIndex);
			return result;
		}
		long OnTestStoped(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, nDeviceIndex, nReportIndex);
			return result;
		}
		long OnExportRptEvent(LPCTSTR strTestID, LPCTSTR strEvent, long nDeviceIndex, long nReportIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, strEvent, nDeviceIndex, nReportIndex);
			return result;
		}
		long OnTestAppEvent(LPCTSTR strTestID, LPCTSTR strEvent)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, strEvent);
			return result;
		}
		long OnEngineEvent(LPCTSTR strTestID, long nDeviceIndex, LPCTSTR strEvent)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, nDeviceIndex, strEvent);
			return result;
		}
		long OnTestCreated(LPCTSTR strTestID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID);
			return result;
		}
		long OnOpenGbrptFileFailed(LPCTSTR strTestID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID);
			return result;
		}
		long OnInitByDeviceID(LPCTSTR strTestID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID);
			return result;
		}
		long OnTestProcess(LPCTSTR strDeviceID, LPCTSTR strTestID, long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, LPCTSTR strDeviceState)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;
			InvokeHelper(0x0a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, strTestID, nTotalItems, nCurrItem, nTotalTime, nRemainTime, strDeviceState);
			return result;
		}
		long OnTestStarted(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
			InvokeHelper(0x0b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, nDeviceIndex, nReportIndex);
			return result;
		}
		long OnUploadRptFile(LPCTSTR strTestID, LPCTSTR strFiles)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR;
			InvokeHelper(0x0c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, strFiles);
			return result;
		}

		// ITestEventSink 属性
	public:

	};
};

#endif // _XSmartTestInterface_h__

