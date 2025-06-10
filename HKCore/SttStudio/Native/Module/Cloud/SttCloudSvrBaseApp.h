#pragma once

#include "SttCloudServerConfig.h"
#include "../../../Module/mysqlapp/mysqlbaseapp.h"

#include "../../Module/SttSocket/Cloud/VC/SttCloudServerSocket.h"
#include "../../Module/Cloud/SttRemoteRegMngr.h"

class CSttCloudSvrBaseApp : public CMySqlBaseApp
{
public:
	CSttCloudSvrBaseApp();
	virtual ~CSttCloudSvrBaseApp();

public:
	virtual void InitSttCloudSvrBaseApp();
	virtual void ExitSttCloudSvrBaseApp();

public:
	CSttCloudServerSocket m_oSttCloudServerSocket;
};

extern CSttCloudSvrBaseApp *g_theSttCloudSvrApp;