#pragma once

#include "../EngineServer/IotEngineServer_Mqtt.h"
#include "IotEdgeServer_Mqtt.h"

#include "..\ProtocolBase\XEngineProtoSrvrBaseApp.h"
#include "..\..\..\Module\XHttpServer\XHttpServer.h"
#include "..\..\Module\MySqlApp\MySqlBaseApp.h"

class CEdgeEngineProtoSvrBaseApp : public CXEngineProtoSrvrBaseApp, public CMySqlBaseApp
{
public:
	enum tagTestState
	{
		STATE_NONE,
		STATE_POWER,
		STATE_CREATETEST,
		STATE_TESTING
	};

	CFormView* m_pEdgeServerView;
	CFormView* m_pMqttServerView;
	CIotEdgeServer_Mqtt m_oIotEdgeMqttServer;
	BOOL m_bViewMode;
	BOOL m_bLocalMode;
	tagTestState m_nState;

public:
	CEdgeEngineProtoSvrBaseApp();
	virtual ~CEdgeEngineProtoSvrBaseApp();

	virtual void InitProtoSvrBaseApp();
	virtual void ExitProtoSvrBaseApp();

	virtual BOOL CheckDeviceInfo(const CString &strDeviceID,CString &strDvmFile,CString &strPpxmlFile);
	virtual CExBaseObject* FindDevice(const CString &strDeviceSN);
	virtual void CloseDevice(const CString& strDeviceSN);
	virtual void SetMsgWnd(const HWND hWnd);
	virtual void UpdateCurrentView();

};

extern CEdgeEngineProtoSvrBaseApp *g_pEdgeEngineProtoSvrBaseApp;
