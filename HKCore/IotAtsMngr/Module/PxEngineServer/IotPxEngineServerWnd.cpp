// D:\WorkPM\Source\PMTest\Module\IotPxEngineServerWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "IotPxEngineServerWnd.h"
#include "IotPxEngineServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIotPxEngineServerWnd
CIotPxEngineServerWnd::CIotPxEngineServerWnd()
{
	m_pIotPxEngineServer = NULL;
}

CIotPxEngineServerWnd::~CIotPxEngineServerWnd()
{
}


BOOL CIotPxEngineServerWnd::CreateIotPxEngineServerWnd()
{
	return TRUE;
}

unsigned long CIotPxEngineServerWnd::OnIotCmd(unsigned long wParam, unsigned long lParam)
{
	if (m_pIotPxEngineServer != NULL)
	{
		CIotPxCommChannelInterface *pPxCommChn = (CIotPxCommChannelInterface*)wParam;
		CSttIotCmd *pIotCmd = (CSttIotCmd*)lParam;
		m_pIotPxEngineServer->OnIotCmd(pPxCommChn, pIotCmd);
	}

	return 0;
}
