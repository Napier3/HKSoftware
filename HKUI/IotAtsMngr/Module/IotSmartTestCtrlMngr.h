#pragma once

#include "IotSmartTestCtrl.h"
#include "SttMqttClientTool.h"

class CIotSmartTestCtrlMngr: public CExBaseList
{//子对象为CSmartTestCtrl
public:
	CIotSmartTestCtrlMngr();
	virtual ~CIotSmartTestCtrlMngr();

public:
	void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen);
	//启动后需要订阅的自动测试主题
	BOOL SubcribeMqttAtsTopic(int nQos);

	//事件处理接口
	LONG TES_OnItemStateChanged(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, LPCTSTR strItemID, LPCTSTR strState);
	LONG TES_OnTestFinished(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
	LONG TES_OnTestStoped(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
	LONG TES_OnExportRptFinished(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
	LONG TES_OnTestAppEvent(LPCTSTR strTestID, LPCTSTR strEvent);
	LONG TES_OnEngineEvent(LPCTSTR strTestID, LONG nDeviceIndex, LPCTSTR strEvent);
	LONG TES_OnTestCreated(LPCTSTR strTestID);
	LONG TES_OnOpenGbrptFileFailed(LPCTSTR strTestID);
};
