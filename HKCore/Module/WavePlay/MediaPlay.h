// MediaPlay.h: interface for the CMediaPlay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__MEDIAPLAY_H__)
#define __MEDIAPLAY_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mmsystem.h"
#pragma comment(lib,"Winmm.lib")

#define CURRENTPOS -1
#define NORMAL -1
#define FAST -2
#define SPECIALFAST -3
#define SLOW -4
#define _OPENTYPE "Music Files(*.mp3;*.wav;*.cda)|*.mp3;*.wav;*.cda|Video File(*.avi;*.asf;*.wmv)|*.avi;*.asf;*.wmv|Mpegvideo File(*.dat;*.mpg;*.mpeg)|*.dat;*.mpg;*.mpeg;*.mpe|"

#define WM_MEDIAPLAY  (WM_USER + 1219)
#define MEDIA_STATE_ERROR    0
#define MEDIA_STATE_BEGIN_PLAY    1
#define MEDIA_STATE_PLAY_FINISH   2
#define MEDIA_STATE_PLAY_STOP   3

class CMediaPlay : public CWnd
{
public:
	CMediaPlay();

private:
	void PostMediaMsg(UINT nMediaState)
	{
		if (m_pParentWnd != NULL)
		{
			m_pParentWnd->PostMessage(WM_MEDIAPLAY, nMediaState, nMediaState);
		}
	}

public:
	BOOL CreateMedia(CWnd *pParentWnd);
	LONG GetTotalSec(void);
	int GetFrameRate(void);
	bool IsVideo(void);	//video:return true , else return false
	bool SetFullScreen(void);
	void SetVolume(int iFactor);
	//get the HWND of the media window
	HWND GetHwnd(void);
	//get total length,in frames,nBufLength: the length of input buffer
	LONG GetLength(void);
	void Pause(void);
	void Stop(void);
	//close the media device
	void Close(void);
	//parameter: FULLSCREEN and WINDOWSCREEN
	//iSpeed :set the play speed, NORMAL,FAST,SPECIALFAST,SLOW, and other specify speed data (int)
	void SetSpeed(int iSpeed=NORMAL);
	//play from the iStartPos position,-1 means CURRENT position
	void Play(int iStartPos=CURRENTPOS);	

////////////////////////////////////////////////////////////
	//strMedia: device file name
	//szError : obtain the error message ,"OK" means no error
	BOOL Open(const CString &strMedia,CString& szError);
	BOOL Play(const CString &strFile);
////////////////////////////////////////////////////////////	

private:
	bool m_bIsVideo;
	CString m_mediaSuffix;
	bool m_pause;
	CString m_strMedia;

	LONG m_nTimer;
	LONG m_curPlaySec;
	LONG m_totalSec;
	int m_frameRate;
	CWnd *m_pParentWnd;

public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadSocket)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CMediaPlay();

	// Generated message map functions
protected:
	//{{AFX_MSG(CThreadSocket)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(__MEDIAPLAY_H__)
