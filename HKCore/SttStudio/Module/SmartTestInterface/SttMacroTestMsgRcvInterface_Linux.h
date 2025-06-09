#pragma once

#include"SttMacroTestMsgRcvInterface.h"

//2020-10-17  lijunqing
class CSttMacroTestMsgRcvInterface_Linux : public CSttMacroTestMsgRcvInterface
{
public:
    CSttMacroTestMsgRcvInterface_Linux(){};
    virtual ~CSttMacroTestMsgRcvInterface_Linux(){};
	
public:
    virtual void PostTestWndMsg(WPARAM wParam, LPARAM lParam)
    {
        //结束消息，需要延迟发送；
        //shaolei   20201216
        if(wParam == MTMSG_TestFinished)
        {
            SetTimer(MTMSG_TestFinished, 1000, NULL);
            return;
        }

		CWnd *pWnd = (CWnd*)m_hMsgWnd;
		pWnd->PostMessage(m_nMsgID, wParam, lParam);  
    }

    virtual void OnWndTimer(unsigned int nIDEvent)
    {
        if(nIDEvent == MTMSG_TestFinished)
        {
            CWnd *pWnd = (CWnd*)m_hMsgWnd;
            pWnd->PostMessage(m_nMsgID, MTMSG_TestFinished, 0);
            KillTimer(nIDEvent);
        }
    }
};
