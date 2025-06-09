//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrService.cpp  CAtsSvrService


#include "stdafx.h"
#include "AtsSvrServiceWnd.h"
#include "../../../SttStudio/Module/Engine/SttEngineInterface.h"

CAtsSvrServiceWnd::CAtsSvrServiceWnd()
{
	m_pAtsService = NULL;
}

CAtsSvrServiceWnd::~CAtsSvrServiceWnd()
{
}

void CAtsSvrServiceWnd::CreateAtsSvrServiceWnd(CAtsSvrService *pService)
{
	m_pAtsService = pService;

	CreateEx(0, AfxRegisterWndClass(0), _T("_Ats_Svr_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
}


BEGIN_MESSAGE_MAP(CAtsSvrServiceWnd, CWnd)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ON_STT_ENGINE_CMD_RCV, &CAtsSvrServiceWnd::OnSttEngineCmdRcv)
END_MESSAGE_MAP()

//消息来源参见：
//long CSttAtsSvrMqttImpBase::OnTestMsg()
//	m_pServiceWnd->PostMessage(WM_ON_STT_ENGINE_CMD_RCV, (WPARAM)this, (LPARAM)pAtsCmd);
LRESULT CAtsSvrServiceWnd::OnSttEngineCmdRcv(WPARAM wParam, LPARAM lParam)
{
	CSttAtsSvrMqttImpBase *pAtsSvrMattImp = (CSttAtsSvrMqttImpBase*)wParam;

	//CSttAtsSvrMqttImpBase::OnTestMsg 已经 oDriver.AddRef();，此处直接关联即可
	CXObjectRefDriver oAtsCmdDrv((CSttAtsCmd*)lParam);

	pAtsSvrMattImp->Process_Cmd_Ats(oAtsCmdDrv);

	return 0;
}

