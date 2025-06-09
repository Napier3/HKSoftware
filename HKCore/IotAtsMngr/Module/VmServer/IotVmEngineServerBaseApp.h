#pragma once

#include "../EngineServer/IotEngineServer_Mqtt.h"
#include "IotVmServer_Mqtt.h"

#include "..\ProtocolBase\XProtoSrvrBaseApp.h"


class CIotVmEngineServerBaseApp : public CXProtoSrvrBaseApp
{
public:
	CIotVmEngineServerBaseApp();
	virtual ~CIotVmEngineServerBaseApp();

	virtual void InitProtoSvrBaseApp();
	virtual void ExitProtoSvrBaseApp();

	virtual BOOL CheckDeviceInfo(const CString &strDeviceID,CString &strDvmFile,CString &strPpxmlFile);
	virtual CExBaseObject* FindDevice(const CString &strDeviceSN);

public:
	CIotVmServer_Mqtt m_oIotVmServer_Mqtt;
};

extern CIotVmEngineServerBaseApp *g_pVmEngineProtoSvrBaseApp;
