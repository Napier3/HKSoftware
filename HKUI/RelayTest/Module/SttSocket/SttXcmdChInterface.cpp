#include "stdafx.h"
#include "SttXcmdChInterface.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../Engine/SttTestEngineBase.h"
#include "../SttCmdToolMngr.h"

#include "../SttCmd/SttSystemCmd.h"
#include "../SttCmd/SttSysState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttXcmdChInterface::CSttXcmdChInterface()
{
	m_nIDTester = 0;
	m_nSocketType = 0;

	m_pTestEngine = NULL;
	m_pUser = NULL;
	m_nSttCmdDataFormat = _PUGI_XML_TYPE_;
}

CSttXcmdChInterface::~CSttXcmdChInterface()
{
}


long CSttXcmdChInterface::XSendSysState(CSttSysState *pSysState)
{
    return 0;
}

DWORD CSttXcmdChInterface::GetIDTest()
{
	return m_nIDTester;
}

bool CSttXcmdChInterface::Match_IdSoft(const CString &strIdSoft)
{
	if (m_pUser == NULL)
	{
		return false;
	}

	return strIdSoft == m_pUser->id_soft() ;
}

BOOL CSttXcmdChInterface::ProcessCmd_System_DownFolder(CSttSystemCmd &oSysCmd)
{
	return 0;
}

BOOL CSttXcmdChInterface::ProcessCmd_System_CreateFolder(CSttSystemCmd &oSysCmd)
{
	return 0;
}

BOOL CSttXcmdChInterface::ProcessCmd_System_DeleteFolder(CSttSystemCmd &oSysCmd)
{
	return 0;
}

long CSttXcmdChInterface::ProcessCmd_System_DeleteFile(CSttSystemCmd &oSysCmd)
{
	return 0;
}

