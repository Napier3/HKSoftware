#pragma once

#include "../DataMngr/DataGroup.h"
#define BTMNGRCLASSID_BASE					 _T("Base")
#define BTMNGRCLASSID_JINANXINGLONG			 _T("济南兴隆站")
#define BTMNGRCLASSID_GANSUSHENGDIAO		 _T("甘肃省调")


#define WM_SMARTTEST_CREAT		 (WM_USER + 2056)
#define WM_SMARTTEST_CLOSE		 (WM_USER + 2056)

class CBtSmartTestEventInterface
{
public:
	CBtSmartTestEventInterface()	{}
	virtual ~CBtSmartTestEventInterface()	{}

public:
	virtual CString GetClassID() {    return BTMNGRCLASSID_BASE;   }
	virtual void OpenBlueToothServer() = 0;
	virtual void CloseBlueToothServer() = 0;

	virtual long OnUploadRptFile(const CString& strDeviceID, const CString &strFiles){	return 0;	};
	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState){	return 0;	}
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){	return 0;	}
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex){	return 0;	}
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex){	return 0;	}
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent){	return 0;	}
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent) {	return 0;	}
	virtual long OnTestCreated(const CString& strDeviceID){	return 0;	}
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID){	return 0;	}
	virtual long OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState){	return 0;	}
	virtual long OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex) {	return 0;	}
};
