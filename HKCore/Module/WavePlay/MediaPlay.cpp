// MediaPlay.cpp: implementation of the CMediaPlay class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MediaPlay.h"
//#include "IVolume.h"
//#include "volumeoutwave.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#if _DEBUG
void DispatchMciError(MCIERROR mciError)
{
	
}
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMediaPlay::CMediaPlay()
{
	m_pause=FALSE;
	m_totalSec=0;
	m_curPlaySec=0;
	m_frameRate = 0;
	m_pParentWnd = NULL;
}

BOOL CMediaPlay::CreateMedia(CWnd *pParentWnd)
{
	if (m_hWnd == NULL)
	{
		CreateEx(0, AfxRegisterWndClass(0), _T("_media_play_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
	}

	m_pParentWnd = pParentWnd;
	return TRUE;
}

CMediaPlay::~CMediaPlay()
{

}

BEGIN_MESSAGE_MAP(CMediaPlay, CWnd)
	//{{AFX_MSG_MAP(CThreadSocket)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CMediaPlay::Open(const CString &strMedia,CString& szError)
{
	BOOL bSuccess = FALSE;
	m_strMedia=strMedia;
	MCIERROR mciError;
	CString strCommand;
	int iIndex=m_strMedia.ReverseFind('.');
	m_mediaSuffix=m_strMedia.Mid(iIndex+1,3);//get the file's suffix
	m_mediaSuffix.MakeLower();
	//////////mcisendString can not open media file whose filename has BLANK character 

	///////////select driver////////////////////////////////////////////
/*	if(m_mediaSuffix=="avi") //avi file
		strCommand.Format("open avivideo!%s alias myMedia",strMedia);
	else if(m_mediaSuffix=="wav") //wave form file
		strCommand.Format("open waveaudio!%s alias myMedia",strMedia);
	else if(m_mediaSuffix=="cda")
		strCommand.Format("open cdaudio!%s alias myMedia",strMedia);
	else
		strCommand.Format("open MPEGvideo2!%s alias myMedia",strMedia);
/////////////////////////////////////////////////////////////////////
	mciError=mciSendString(strCommand,NULL,0,NULL);

*/
/////////////////////////////////////////////////////////////
////test mciSendCommand////////////////////////
	MCI_OPEN_PARMS mciOpen;
	if(m_mediaSuffix==_T("avi"))
		mciOpen.lpstrDeviceType=_T("avivideo");
	else if(m_mediaSuffix==_T("wav")) //wave form file
		mciOpen.lpstrDeviceType=_T("waveaudio");
	else if(m_mediaSuffix==_T("cda") )
		mciOpen.lpstrDeviceType=_T("cdaudio");
	else
		mciOpen.lpstrDeviceType=_T("MPEGvideo2");
		
	mciOpen.lpstrElementName=m_strMedia;
	mciOpen.lpstrAlias=_T("myMedia");
	mciError=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT|MCI_OPEN_ALIAS|MCI_OPEN_TYPE ,(DWORD)&mciOpen);

	if(mciError)		//get error
	{
#ifdef _UNICODE
		WCHAR chError[100];
		mciGetErrorString(mciError,chError,sizeof(chError));
#else
		char chError[100];
		mciGetErrorString(mciError,chError,sizeof(chError));
#endif
		szError.Format(_T("%s"),chError);
		bSuccess = FALSE;
	}
	else		//no error
	{
		bSuccess = TRUE;
	}

	if(m_mediaSuffix==_T("mp3") || m_mediaSuffix==_T("wav") || m_mediaSuffix==_T("cda"))
	{
		m_bIsVideo=FALSE;
	}
	else
	{
		m_bIsVideo=TRUE;
	}

	m_curPlaySec=0;
	m_totalSec=GetTotalSec();
	return bSuccess;
}

BOOL CMediaPlay::Play(const CString &strFile)
{
	CString strError;
	
	if (! Open(strFile, strError))
	{
		return FALSE;
	}

	if(m_bIsVideo)
		m_frameRate=GetFrameRate();
	else
		m_frameRate=0;

	Play(0);	//play from 0 position
	
	return TRUE;
}

void CMediaPlay::Play(int iStartPos)
{	//the default parameter is CURRENTPOS
	ASSERT(iStartPos>=-1);
	m_pause=FALSE;

	if(iStartPos==CURRENTPOS)	
	{
		mciSendString(_T("play myMedia"),NULL,0,NULL);
	}
	else
	{
		CString strCommand;
		strCommand.Format(_T("play myMedia from %d"),iStartPos);
		mciSendString(strCommand,NULL,0,NULL);
	}

	if (iStartPos <= 0)
	{
		m_nTimer = SetTimer(1, 1000, 0);
	}

	m_curPlaySec = iStartPos;

	PostMediaMsg(MEDIA_STATE_BEGIN_PLAY);
}

void CMediaPlay::SetSpeed(int iSpeed)
{

}

void CMediaPlay::Close()
{
	KillTimer(m_nTimer);
	mciSendString(_T("close myMedia"),NULL,0,NULL);
}

void CMediaPlay::Stop()
{
	KillTimer(m_nTimer);
	mciSendString(_T("stop myMedia"),NULL,0,NULL);
	mciSendString(_T("seek myMedia to start"),NULL,0,NULL);
	PostMediaMsg(MEDIA_STATE_PLAY_STOP);
}

void CMediaPlay::Pause()
{
	if(m_pause)	//in pause state, then resume play
		mciSendString(_T("resume myMedia"),NULL,0,NULL);	
	else//else pause 
		mciSendString(_T("pause myMedia"), NULL,0,NULL);

	m_pause=!m_pause;
}

LONG CMediaPlay::GetLength()
{
	MCIERROR mciError;	

	if(!m_bIsVideo)	//music file ,get total length in milliseconds
	{
		mciError=mciSendString(_T("set myMedia time format milliseconds"),NULL,0,NULL);
#if _DEBUG
		DispatchMciError(mciError);
#endif
	}else //video file ,get total frames
	{
		mciError=mciSendString(_T("set myMedia time format frames"),NULL,0,NULL);
#if _DEBUG
		DispatchMciError(mciError);
#endif
	}
	
#ifdef _UNICODE
	WCHAR chLength[50];
	mciError=mciSendString(_T("status myMedia length"),chLength,sizeof(chLength),NULL);
#else
	char chLength[50];
	mciError=mciSendString(_T("status myMedia length"),chLength,sizeof(chLength),NULL);
#endif

#if _DEBUG
		DispatchMciError(mciError);
#endif
	if(mciError)
		return 0;	//0 means can not get length: ASF file can not get length
	CString strLength;
	strLength.Format(_T("%s"),chLength);
	return (LONG)(StrToLong((LPCTSTR)strLength));
	// music return in milliseconds 
	// video return in frames
}
//GetHwnd(),
//Get the handle of the VIDEO play window.
//this function only for Video media who has a play window
HWND CMediaPlay::GetHwnd()
{
	if(!IsVideo())	//music media
		return NULL;
	
#ifdef _UNICODE
	wchar_t chHandle[100];
	MCIERROR mciError=mciSendString(_T("status myMedia window handle"),chHandle,sizeof(chHandle),NULL);	
#else
	char chHandle[100];
	MCIERROR mciError=mciSendString(_T("status myMedia window handle"),chHandle,sizeof(chHandle),NULL);	
#endif
#if _DEBUG
	DispatchMciError(mciError);
#endif
	CString strHandle;
	strHandle.Format(_T("%s"),chHandle);
	return (HWND)(StrToLong((LPCTSTR)strHandle));
}
//the setVolume function have some problem in my computer
//I can not get the device handle while the media is playing
//that is, I can not get the audio divice handle while the handle is open by my media 
//I had used many ways , but failed
////////////////////////////////////
void CMediaPlay::SetVolume(int iFactor)
{
////// method 1//////////////////////
/*	MMRESULT mmResult;
	HWAVEOUT hWaveOut;
//	PCMWAVEFORMAT pFormat;
	WAVEFORMATEX waveFormat;
	waveFormat.wFormatTag=WAVE_FORMAT_PCM;
	waveFormat.nChannels=2;
	waveFormat.nSamplesPerSec=44.1;
	waveFormat.wBitsPerSample=16;
	waveFormat.nBlockAlign=waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
	waveFormat.nAvgBytesPerSec=waveFormat.nBlockAlign * waveFormat.nSamplesPerSec;
	waveFormat.cbSize=0;
	UINT numDevs=waveOutGetNumDevs();
	WAVEOUTCAPS waveOutCaps;
	for(UINT openDevId=0;openDevId < numDevs;openDevId++)
	{
		mmResult=waveOutGetDevCaps(openDevId,&waveOutCaps,sizeof(WAVEOUTCAPS));
		//		mmResult=waveOutOpen(&hWaveOut,openDevId,&waveFormat,NULL,NULL,NULL);
//		if(mmResult==MMSYSERR_NOERROR)
//			break;
		//ASSERT(mmResult==MMSYSERR_NOERROR);
	}

	mmResult=waveOutOpen(&hWaveOut,WAVE_MAPPER ,&waveFormat,NULL,0,WAVE_ALLOWSYNC );
	ASSERT(mmResult!=MMSYSERR_BADDEVICEID);
	ASSERT(mmResult==MMSYSERR_NOERROR);
	DWORD dwVolume;
	mmResult=waveOutGetVolume(hWaveOut,&dwVolume);
	ASSERT(mmResult==MMSYSERR_NOERROR);
	mmResult=waveOutSetVolume(hWaveOut,0);
	waveOutClose(hWaveOut);
*/

////////method 2///////////////////use a volume class whiched downloaded from net
/*	IVolume* pWaveVolume=(IVolume*)new CVolumeOutWave();
	if(!pWaveVolume || !pWaveVolume->IsAvailable())
		return;
	DWORD dwVolume=pWaveVolume->GetCurrentVolume();
*/

//////////method 3///////////////////use a volume class whiched downloaded from net
/*	IVolume* pMasterVolume = (IVolume*)new CVolumeOutMaster();
	if ( !pMasterVolume || !pMasterVolume->IsAvailable() )
	{
 		// handle error
		return;
	}
	DWORD dwVolume=pMasterVolume->GetCurrentVolume();
*/
}
//SetFullScreen(),
//Only for media play who has a play window
bool CMediaPlay::SetFullScreen()
{
	///////this functon can not be effected to the media window
	////// should close previous media window ,then call this function!
	if(!m_bIsVideo)			//not video file
		return FALSE;
	MCIERROR mciError=mciSendString(_T("window myMedia state minimized"),NULL,0,NULL);
	mciSendString(_T("play myMedia fullscreen"),NULL,0,NULL);

#if _DEBUG
	DispatchMciError(mciError);
#endif
	return TRUE;
}

bool CMediaPlay::IsVideo()
{
	return m_bIsVideo;
}

// function GetFrameRate() only for video file
int CMediaPlay::GetFrameRate()
{
	ASSERT(m_bIsVideo);
	MCIERROR mciError;	
//	mciError=mciSendString("set myMedia time format frames",NULL,0,NULL);
 	/////// frames format is default /////////////////
#ifdef _UNICODE
	wchar_t chFrameRate[50];
	mciError=mciSendString(_T("status myMedia frame rate"),chFrameRate,sizeof(chFrameRate),NULL);
#else
	char chFrameRate[50];
	mciError=mciSendString(_T("status myMedia frame rate"),chFrameRate,sizeof(chFrameRate),NULL);
#endif

#if _DEBUG
	DispatchMciError(mciError);
#endif
	CString strFrameRate;
	strFrameRate.Format(_T("%s"),chFrameRate);
	int temp=StrToInt((LPCTSTR)strFrameRate)/1000;
	return temp;
}

//GetTotalSec(),
//return media file's total length in seconds
LONG CMediaPlay::GetTotalSec()
{
	if(m_bIsVideo) //video file
	{
		int frameRate=GetFrameRate();
		if(frameRate)	//not failure
			return GetLength()/frameRate;
		else		//asf file can not get framerate
			return 3600; //an hour
	}
	else     //music file
	{
		return GetLength()/1000;
	}
}


void CMediaPlay::OnTimer(UINT nIDEvent) 
{
	///set slider 
	if(m_curPlaySec >= m_totalSec)
	{
		Stop();
		PostMediaMsg(MEDIA_STATE_PLAY_FINISH);
	}
	
	m_curPlaySec++;

	CWnd::OnTimer(nIDEvent);
}