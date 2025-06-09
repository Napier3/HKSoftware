#include <stdafx.h>
#include "WavePlay.h"

// ('', 'AVIVideo', 'CDAudio', 'DAT',
//'DigitalVideo', 'MMMovie', 'Other', 'Overlay', 'Scanner', 'Sequencer',
//'VCR', 'Videodisc', 'WaveAudio');

CWavePlay::CWavePlay()
{
	m_nDeviceID=0;
	m_nElementID=0;
}

CWavePlay::~CWavePlay()
{
	if(m_nElementID)
		Stop();
	if(m_nDeviceID)
		CloseDevice();
}

DWORD CWavePlay::OpenDevice()
{
	DWORD dwResult=0;

	if (m_nDeviceID)
	{
		MCI_OPEN_PARMS mciOpenParms;
		
		mciOpenParms.lpstrDeviceType=_T("WaveAudio");
		
		//open the wave device
		dwResult = mciSendCommand(NULL,
 				MCI_OPEN,
				MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_WAIT,
				(DWORD)(LPVOID)&mciOpenParms);

		//save device identifier,will use eith other MCI commands
		m_nDeviceID = mciOpenParms.wDeviceID;

		//display error message if failed 
		if(dwResult)
			DisplayErrorMsg(dwResult);
	}

	//return result of MCI operation
	return dwResult;
}

DWORD CWavePlay::CloseDevice()
{
	DWORD dwResult=0;

	//close if currently open
	if(m_nDeviceID)
	{
		//close the MCI device
		dwResult=mciSendCommand(m_nDeviceID,MCI_CLOSE,NULL,NULL);
		//display error message if failed
		if(dwResult)
			DisplayErrorMsg(dwResult);
		else //set identifier to close state
			m_nDeviceID=0;
	}

	//return result of MCI operation
	return dwResult;
}

DWORD CWavePlay::Play(CWnd* pWnd ,const CString &strFileName)
{
	MCI_OPEN_PARMS mciOpenParms;
    //initialize structure
	memset(&mciOpenParms,0,sizeof(MCI_OPEN_PARMS));

	//set the WAV file name to be played
	mciOpenParms.lpstrElementName = strFileName;

	//first open the device
	DWORD dwResult=mciSendCommand(m_nDeviceID,MCI_OPEN,
		MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciOpenParms);

	//display error message if failed
	if(dwResult)
	{
		DisplayErrorMsg(dwResult);
	}
    else	
    {//if successful,instruct the device to play the WAV file
		//save element indentifier
		m_nElementID=mciOpenParms.wDeviceID;

		MCI_PLAY_PARMS mciPlayParms;

		//set the window that will receive notification message
		mciPlayParms.dwCallback=(DWORD)pWnd->m_hWnd;

		//instruct device to play file
		dwResult=mciSendCommand(m_nElementID,MCI_PLAY,
			MCI_NOTIFY,(DWORD)(LPVOID)&mciPlayParms);

		//display error and close element if failed
		if(dwResult)
		{
			DisplayErrorMsg(dwResult);
			Stop();
		}


		////
		OnMciSiginal
	}

	//return result of MCI operation
	return dwResult;
}

DWORD CWavePlay::Stop()
{
	DWORD dwResult=0;

	//close if element is currently open
	if(m_nElementID)
	{
		dwResult=mciSendCommand(m_nElementID,MCI_CLOSE,NULL,NULL);

		//display error message if failed
		if(dwResult)
			DisplayErrorMsg(dwResult);
        else//set identifier to closed state
            m_nElementID=0;
	}
	return dwResult;
}

void CWavePlay::DisplayErrorMsg(DWORD dwError)
{
	//check if there was an error
	if(dwError)
	{
		//character string that contains error message
		wchar_t szErrorMsg[MAXERRORLENGTH];

		//retrieve string associated error message
		if(!mciGetErrorString(dwError,szErrorMsg,sizeof(szErrorMsg)))
		{
			wcscpy(szErrorMsg,L"Unknown Error");
		}
		//display error string in message box
		AfxMessageBox(szErrorMsg);
	}
}      

