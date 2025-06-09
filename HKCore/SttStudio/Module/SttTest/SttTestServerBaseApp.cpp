#include "stdafx.h"
#include "SttTestServerBaseApp.h"

#ifndef _PSX_QT_LINUX_
#include "../../Module/SttSocket/TestServer/VC/SttTestServerSocket.h"
#else
#include "../../Module/SttSocket/TestServer/QT/SttTestServerSocket.h"
#endif

#include "../../Module/Engine/SttTestServerBase.h"
#include "../../Module/Engine/SttServerTestCtrlCntr.h"
#include "../../../Module/API/GlobalConfigApi.h"

CSttTestServerBaseApp::CSttTestServerBaseApp()
{

}

CSttTestServerBaseApp::~CSttTestServerBaseApp()
{

}

void CSttTestServerBaseApp::InitSttTestServerBaseApp()
{
	CDataMngrXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CSttServerTestCtrlCntr::Create();
}

void CSttTestServerBaseApp::ExitSttTestServerBaseApp()
{
	CSttServerTestCtrlCntr::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
}

