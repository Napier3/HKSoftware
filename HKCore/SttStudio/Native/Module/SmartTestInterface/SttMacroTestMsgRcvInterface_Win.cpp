#include "stdafx.h"
#include "SttMacroTestMsgRcvInterface_Win.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMacroTestMsgRcvInterface_Win::CSttMacroTestMsgRcvInterface_Win()
{
	CreateEx(0, AfxRegisterWndClass(0), _T("_Stt_Macro_Test_Msg_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
}

CSttMacroTestMsgRcvInterface_Win::~CSttMacroTestMsgRcvInterface_Win()
{
	
}

BEGIN_MESSAGE_MAP(CSttMacroTestMsgRcvInterface_Win, CWnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()
