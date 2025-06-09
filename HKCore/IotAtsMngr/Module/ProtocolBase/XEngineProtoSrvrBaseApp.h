#pragma once

#include "XProtoSrvrBaseApp.h"
#include "../EngineServer/IotEngineServer_Mqtt.h"

class CXEngineProtoSrvrBaseApp : public CXProtoSrvrBaseApp
{
public:
	CXEngineProtoSrvrBaseApp();
	virtual ~CXEngineProtoSrvrBaseApp();

	virtual void InitProtoSvrBaseApp();
	virtual void ExitProtoSvrBaseApp();

public:
	CIotEngineServer_Mqtt m_oIotEngineMqttServer;

};

extern CXEngineProtoSrvrBaseApp *g_pEngineProtoSvrBaseApp;
