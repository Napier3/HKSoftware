#ifndef	_WAVEPLAY_H__
#define _WAVEPLAY_H__

#include "MMSystem.h"

#pragma comment(lib,"winmm.lib")

class CWavePlay:public CObject
{
//Construction
public:
	CWavePlay();
	virtual ~CWavePlay();

//Operations
public:
	DWORD OpenDevice();
	DWORD CloseDevice();
	DWORD Play(CWnd *pParentWnd,const CString &strFileName);
	DWORD Stop();

//Implementation
protected:
	void DisplayErrorMsg(DWORD dwError);

//Members
protected:
	MCIDEVICEID m_nDeviceID;
	MCIDEVICEID m_nElementID;
};


#endif