#pragma once
// CXSmartTestEventSink 包装类

class CXSmartTestEventSink
{
public:
	CXSmartTestEventSink(){}
	virtual ~CXSmartTestEventSink(){}

// IXSmartTestEventSink 方法
public:
	long OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString &strItemID, const CString &strState) = 0;
	long OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex) = 0;
	long OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex) = 0;
	long OnExportRptFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex) = 0;
	long OnTestAppEvent(const CString &strTestID, const CString &strEvent) = 0;
	long OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString &strEvent) = 0;
	long OnTestCreated(const CString &strTestID) = 0;
};
