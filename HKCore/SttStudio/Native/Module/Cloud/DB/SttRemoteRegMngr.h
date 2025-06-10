#pragma once

#include "RemoteCtrlMngrGlobal.h"

#include "Stt_RemoteRegRTs.h"

class CSttRemoteRegMngr : public CStt_RemoteRegRTs
{
public:
	CSttRemoteRegMngr();
	virtual ~CSttRemoteRegMngr();

public:
	CWnd *m_pMsgWnd;
	virtual void SetMsgWnd(CWnd *pWnd)	{m_pMsgWnd = pWnd;}

};