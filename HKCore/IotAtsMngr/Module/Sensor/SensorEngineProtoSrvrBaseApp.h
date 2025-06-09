#pragma once

#include "../EngineServer/IotEngineServer_MqttClient.h"
#include "IotSensorSvrEngine.h"
#include "..\..\..\Module\mysqlapp\mysqlbaseapp.h"

#include "..\ProtocolBase\XEngineProtoSrvrBaseApp.h"

class CSensorEngineProtoSrvrBaseApp: public CMySqlBaseApp, public CXEngineProtoSrvrBaseApp
{
public:
	CSensorEngineProtoSrvrBaseApp();
	virtual ~CSensorEngineProtoSrvrBaseApp();

	virtual void InitProtoSvrBaseApp();
	virtual void ExitProtoSvrBase();
	virtual BOOL CheckDeviceInfo(const CString &strDeviceID,CString &strDvmFile,CString &strPpxmlFile);
	virtual CExBaseObject* FindDevice(const CString &strDeviceSN);

};

extern CSensorEngineProtoSrvrBaseApp *g_pSensorEngineProtoSvrBaseApp;
