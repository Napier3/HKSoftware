#include "stdafx.h"
#include "SttRelayTestServerApp.h"

#include "../../../SttSocket/TestServer/VC/SttTestServerSocket.h"

#include "../../../Engine/SttTestServerBase.h"
#include "../../../Engine/SttServerTestCtrlCntr.h"
#include "../../../../../Module/API/GlobalConfigApi.h"

#include "../../../SttTest/DebugServer/SttTestFactoryForDebug.h"
#include "../../../Engine/VC/SttTestServerEngine.h"

CSttRelayTestServerApp::CSttRelayTestServerApp()
{
    
}

CSttRelayTestServerApp::~CSttRelayTestServerApp()
{
    
}

void CSttRelayTestServerApp::InitSttTestServerBaseApp()
{
	_P_InitSystemPath();

	CDataMngrXmlRWKeys::Create();
	CSttCmdOverTimeTool::Create();
	CSttCmdDefineXmlRWKeys::Create();

	//2020-10-25  lijunqing
	//”√”⁄≤‚ ‘
	CSttTestFactoryForDebug *pSttFactory = CSttTestFactoryForDebug::Create();

	CSttServerTestCtrlCntr::Create();
	CSttTestServerEngine::Create("",STT_PORT_TEST_SERVER);
}

void CSttRelayTestServerApp::ExitSttTestServerBaseApp()
{
	CSttTestServerEngine::Release();
	CSttServerTestCtrlCntr::Release();
	CSttTestFactoryForDebug::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CSttCmdOverTimeTool::Release();
	CDataMngrXmlRWKeys::Release();
}

