#pragma once

class CXSmartTestEventInterface
{
public:
	CXSmartTestEventInterface()	{}
	virtual ~CXSmartTestEventInterface()	{}

public:
	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState) = 0;
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex) = 0;
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex) = 0;
	virtual long OnExportRptFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex) = 0;
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent) = 0;
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent) = 0;
	virtual long OnTestCreated(const CString& strDeviceID) = 0;
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID) = 0;

};
