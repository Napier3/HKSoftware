// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

#pragma once
// CTestEventSink 包装类

#include "..\..\Module\BaseClass\ExBaseList.h"

class CTestEventSinkDispatch : public COleDispatchDriver, public CExBaseObject
{
public:
	CTestEventSinkDispatch(){} // 调用 COleDispatchDriver 默认构造函数
	CTestEventSinkDispatch(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTestEventSinkDispatch(const CTestEventSinkDispatch& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

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
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTestID, strEvent);
		return result;
	}
	long OnEngineEvent(LPCTSTR strTestID, long nDeviceIndex, LPCTSTR strEvent)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR;
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
		static BYTE parms[] = VTS_BSTR ;
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
	long OnUploadRptFile(LPCTSTR strDeviceID, LPCTSTR strFiles)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x0C, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, strFiles);
		return result;
	}
	long OnInputData(LPCTSTR strDatas, LPCTSTR strMsgs)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x0D, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDatas, strMsgs);
		return result;
	}
	// ITestEventSink 属性
public:

};

class CTestEventSinkMngr : public CExBaseList
{
public:
	CTestEventSinkMngr();
	virtual ~CTestEventSinkMngr();

	static CTestEventSinkMngr* Create();
	static void Release();

	static CTestEventSinkDispatch *XAddEventSink(const CString &strProgID, const CString &strDeviceID)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return NULL;
		}

		return g_pTestEventSinkMngr->AddEventSink(strProgID, strDeviceID);
	}

	static CTestEventSinkDispatch *XAddEventSink(const CString &strProgID)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return NULL;
		}

		return g_pTestEventSinkMngr->AddEventSink(strProgID);
	}

	static void XDeleteEventSink(const CString &strProgID, const CString &strDeviceID)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return ;
		}

		g_pTestEventSinkMngr->DeleteEventSink(strProgID, strDeviceID);
	}

	static void XDeleteEventSink(const CString &strProgID)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return ;
		}

		g_pTestEventSinkMngr->DeleteEventSink(strProgID);
	}

	static long XOnItemStateChanged(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, LPCTSTR strItemID, LPCTSTR strState)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnItemStateChanged(strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, strState);
	}

	static long XOnTestFinished(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnTestFinished(strTestID, nDeviceIndex, nReportIndex);
	}

	static long XOnTestStoped(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnTestStoped(strTestID, nDeviceIndex, nReportIndex);
	}

	static long XOnExportRptFinished(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnExportRptFinished(strTestID, nDeviceIndex, nReportIndex);
	}

	static long XOnTestAppEvent(LPCTSTR strTestID, LPCTSTR strEvent)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnTestAppEvent(strTestID, strEvent);
	}

	static long XOnEngineEvent(LPCTSTR strTestID, long nDeviceIndex, LPCTSTR strEvent)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnEngineEvent(strTestID, nDeviceIndex, strEvent);
	}

	static long XOnTestCreated(LPCTSTR strTestID)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnTestCreated(strTestID);
	}

	static long XOnOpenGbrptFileFailed(LPCTSTR strTestID)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnOpenGbrptFileFailed(strTestID);
	}

	static BOOL HasTestEventSinkMngr()
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return FALSE;
		}

		return (g_pTestEventSinkMngr->GetCount() > 0);
	}

	static long XOnTestProcess(LPCTSTR strDeviceID, LPCTSTR strTestID, long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, LPCTSTR strDeviceState)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnTestProcess(strDeviceID, strTestID, nTotalItems, nCurrItem, nTotalTime, nRemainTime, strDeviceState);
	}

	static long XOnTestStarted(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnTestStarted(strTestID, nDeviceIndex, nReportIndex);
	}

	static long XOnExportRptEvent(LPCTSTR strTestID, LPCTSTR strEvent, long nDeviceIndex, long nReportIndex)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnExportRptEvent(strTestID, strEvent, nDeviceIndex, nReportIndex);
	}

	static long XOnUploadRptFile(LPCTSTR strTestID, LPCTSTR strFiles)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnUploadRptFile(strTestID, strFiles);
	}

	static long XOnInputData(LPCTSTR strDatas, LPCTSTR strMsgs)
	{
		if (g_pTestEventSinkMngr == NULL)
		{
			return 0;
		}

		return g_pTestEventSinkMngr->OnInputData(strDatas, strMsgs);
	}

private:
	static CTestEventSinkMngr *g_pTestEventSinkMngr;
	static long g_nTestEventSinkMngr;

public:
	//shaolei 20220523
	void AddEventSinkEx(const CString &strProgID);
	static CTestEventSinkMngr* GetSinkMngr()	{	return CTestEventSinkMngr::g_pTestEventSinkMngr;	}

private:
	CTestEventSinkDispatch *AddEventSink(const CString &strProgID, const CString &strDeviceID);
	void DeleteEventSink(const CString &strProgID, const CString &strDeviceID){	}
	CTestEventSinkDispatch *AddEventSink(const CString &strProgID);
	void DeleteEventSink(const CString &strProgID);

	long OnItemStateChanged(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, LPCTSTR strItemID, LPCTSTR strState);
	long OnTestFinished(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex);
	long OnTestStoped(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex);
	long OnExportRptFinished(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex);
	long OnTestAppEvent(LPCTSTR strTestID, LPCTSTR strEvent);
	long OnEngineEvent(LPCTSTR strTestID, long nDeviceIndex, LPCTSTR strEvent);
	long OnTestCreated(LPCTSTR strTestID);
	long OnOpenGbrptFileFailed(LPCTSTR strTestID);
	long OnTestProcess(LPCTSTR strDeviceID, LPCTSTR strTestID,  long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, LPCTSTR strDeviceState);
	long OnTestStarted(LPCTSTR strTestID, long nDeviceIndex, long nReportIndex);
	long OnExportRptEvent(LPCTSTR strTestID, LPCTSTR strEvent, long nDeviceIndex, long nReportIndex);
	long OnUploadRptFile(LPCTSTR strDeviceID, LPCTSTR strFiles);
	long OnInputData(LPCTSTR strDatas, LPCTSTR strMsgs);
};

