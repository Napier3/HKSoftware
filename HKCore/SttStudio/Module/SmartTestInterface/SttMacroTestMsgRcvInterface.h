#pragma once

#ifdef _PSX_QT_LINUX_
#include "../../../Module/OSInterface/QT/CXCtrl_QT_CWnd.h"
#endif

//2020-10-17  lijunqing
class CSttMacroTestMsgRcvInterface : public CWnd
{
public:
	CSttMacroTestMsgRcvInterface()
	{
		
	}

	virtual ~CSttMacroTestMsgRcvInterface()
	{

	}

public:
    unsigned long m_hMsgWnd;
    unsigned long m_nMsgID;

    virtual long SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID)
    {
    	m_hMsgWnd = hMainWnd;
    	m_nMsgID = nMsgID;

		return 0;
    }
    virtual void PostTestWndMsg(WPARAM wParam, LPARAM lParam) = 0;

public:
	afx_msg void OnTimer(unsigned int  nIDEvent)
	{
		
	}

};
