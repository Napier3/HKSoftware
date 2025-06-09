#pragma once

#ifdef _PSX_IDE_QT_
#include "../OSInterface/QT/CXCtrl_QT_CWnd.h"
#endif
// 
// class CXTimerBase : public CWnd
// {
// public:
// 	CXTimerBase();
// 	virtual ~CXTimerBase();
// 
// 	virtual void CreateXTimer() = 0;
// 
// public:
// 	DWORD SetXTimer(DWORD dwTimerID,DWORD dwTimeLong);
// 	void KillXTimer(DWORD dwTimerID);
// 	virtual void OnXTimer(DWORD dwTimerID)	{};
// 
// public:
// #ifdef _PSX_IDE_QT_
// 	void OnTimer(unsigned int  nIDEvent);
// #else
// 	afx_msg void OnTimer(unsigned int  nIDEvent);
// #endif
// 
// };


class CXTimer : public CWnd/*CXTimerBase*/
{
#ifndef _PSX_IDE_QT_
	DECLARE_DYNAMIC(CXTimer)
#endif

public:
	CXTimer();
	virtual ~CXTimer();

	virtual void CreateXTimer();

#ifdef _PSX_IDE_QT_
	virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
	virtual void OnWndTimer(unsigned int nIDEvent);
#else

protected:
	DECLARE_MESSAGE_MAP()
#endif

public:
	DWORD SetXTimer(DWORD dwTimerID,DWORD dwTimeLong);
	void KillXTimer(DWORD dwTimerID);
	virtual void OnXTimer(DWORD dwTimerID)	{};

#ifdef _PSX_IDE_QT_
	void OnTimer(unsigned int  nIDEvent);
#else
	afx_msg void OnTimer(unsigned int  nIDEvent);
#endif
};
