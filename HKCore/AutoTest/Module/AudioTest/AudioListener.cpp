#include "stdafx.h"
#include "AudioParser.h"
#include "AudioListener.h"
#include "MSP/msp_cmn.h"
#include "MSP/msp_errors.h"
#include "../../AudioTest/AudioTest.h"
#include "../../AudioTest/AudioTestDlg.h"

#include <Windows.h>
#include <mmsystem.h>   
#include "MSP/winrec.h"

#pragma comment(lib, "msc.lib")

typedef BOOL(*DllFunc)(void);
typedef void(*DllStr)(CString);
typedef void(*DllStrFunc)(DllStr);

CAudioListener* g_pAudioListener = NULL;

CAudioListener::CAudioListener()
{
	m_bExited = false;
	m_bEnableKey = true;
	m_bStartParse = false;
	m_bAutioPowerFlag = true;
	if(!g_pAudioListener)
	{
		g_pAudioListener = this;
	}

	for (int i = 0; i < 1024; i++)
	{
		m_strLoginParams[i] = 0;
		m_strVoiceParams[i] = 0;
	}
	SetInitState();
	m_pAudioParser = NULL;
	m_strVoiceTime = "7000";
}

CAudioListener::~CAudioListener()
{
	if(m_bEnableKey)
	{
		//ExitKeyboardHook();
	}
	
}

BOOL CAudioListener::InitMSP()
{
	// 登录参数，appid与msc库绑定,请勿随意改动
	CString strMSCPath = _P_GetConfigPath();
	strMSCPath += "Audio";
	CString strLogin;
	strLogin.Format("%s,work_dir=%s", "appid=ce9e07ec", strMSCPath);
	strcpy(m_strLoginParams, strLogin.GetString());

	/*
	* sub:				请求业务类型
	* domain:			领域
	* language:			语言
	* accent:			方言
	* sample_rate:		音频采样率
	* result_type:		识别结果格式
	* result_encoding:	结果编码格式
	*
	*/

	CString strVoiceParams;
	strVoiceParams.Format("sub=iat,domain=iat,language=zh_cn,accent=mandarin,"
		"sample_rate=16000,result_type=plain,result_encoding=gb2312,vad_eos=%s", m_strVoiceTime);
	strcpy(m_strVoiceParams, strVoiceParams.GetString());

	/*strcpy(m_strVoiceParams, "sub=iat,domain=iat,language=zh_cn,accent=mandarin,"
		"sample_rate=16000,result_type=plain,result_encoding=gb2312,vad_eos=7000");*/

	MSPLogout();
	if(MSPLogin(NULL, NULL, m_strLoginParams) != MSP_SUCCESS)
	{
		return FALSE;
	}

	return TRUE;
}

void CAudioListener::InitKeyboardHook()
{
	/*HMODULE hDLL = LoadLibrary("AudioHook.dll");
	if (hDLL == NULL)
	{ 
		CLogPrint::LogString(XLOGLEVEL_INFOR, "AudioHook   NULL 22");
		return;
	}

	DllFunc dllFunc = NULL;

	dllFunc = (DllFunc)GetProcAddress(hDLL, "Hook_Install");
	if(dllFunc == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, "AudioHook   NULL 00");
		return;
	}
	dllFunc();
	DllStrFunc dllStrFunc = NULL;
	dllStrFunc = (DllStrFunc)GetProcAddress(hDLL, "Hook_SetCallBack");
	if(dllStrFunc == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, "AudioHook   NULL 11");
		return;
	}
	dllStrFunc(GetHookKeyName);*/
}

void CAudioListener::ExitKeyboardHook()
{
	/*HMODULE hDLL = LoadLibrary("AudioHook.dll");
	if (hDLL == NULL)
	{ 
		CLogPrint::LogString(XLOGLEVEL_INFOR, "AudioHook   NULL 33");
		return;
	}

	DllFunc dllFunc = (DllFunc)GetProcAddress(hDLL, "Hook_Uninstall");
	dllFunc();*/
}

void CAudioListener::setAudioParser(CAudioParser* pAudioParser)
{
	m_pAudioParser = pAudioParser;
}

void CAudioListener::OnAudioTimer()
{
	SetEvent(g_pAudioListener->m_hEvents[EVT_STOP]);
//	CLogPrint::LogString(XLOGLEVEL_INFOR, "结束监听");
}

BOOL CAudioListener::SetupListener()
{

	if(!InitMSP())
	{
		return FALSE;
	}
	//InitKeyboardHook();

	m_nWholeFlag = Flag_Flow;
	AfxBeginThread(ListenerThread, this);

	CTickCount32 event;
	event.DoEvents(1000);

	SetEvent(m_hEvents[EVT_START]);

	return TRUE;
}

BOOL CAudioListener::SetupListener(CString strKeyWord, CString strStartKey, CString strStopKey,CString strVoiceTime)
{
	m_strStartKey = strStartKey.MakeUpper();
	m_strStopKey = strStopKey.MakeUpper();
	m_strVoiceTime = strVoiceTime;
	m_strKeyWord = strKeyWord;

	//m_nVoiceListenFlag = Flag_VoiceNULL;
	return SetupListener();
}

void CAudioListener::AddToBuffer(CString strBuffer)
{
	m_lockerReadWrite.Lock();
	m_vecBuffer.push_back(strBuffer);
	m_lockerReadWrite.Unlock();
}

void CAudioListener::MoveToBuffer(std::vector<CString>& vecBuffer)
{
	m_lockerReadWrite.Lock();

	for (int i = 0; i < m_vecBuffer.size(); i++)
	{
		vecBuffer.push_back(m_vecBuffer[i]);
	}
	m_vecBuffer.clear();

	m_lockerReadWrite.Unlock();
}

void CAudioListener::Clear()
{
	m_lockerReadWrite.Lock();
	m_vecBuffer.clear();
	m_lockerReadWrite.Unlock();
}

void CAudioListener::SetBtnKey(CString strKey)
{
	GetHookKeyName(strKey);
}

void CAudioListener::SetInitState()
{
	//m_nVoiceListenFlag = Flag_VoiceNULL;
	m_nWholeFlag = Flag_Flow_NULL;
	m_nTipWordFlag = Flag_Question_NULL;
	m_nSetpPageFlag = Step_NULL;
}

void CAudioListener::SetStateNoSatrTest()
{
	m_nTipWordFlag = Flag_AnswerWait;
	m_nWholeFlag = Flag_TestWait;
}

void on_speech_begin()
{
	//CreateTray(g_pAudioListener->m_notify, theApp.GetMainWnd()->GetSafeHwnd(), "语音识别自动测试", "开始监听", 3000);
	//if()
	//SetEvent(g_pAudioListener->m_hEvents[EVT_START]);
	//CLogPrint::LogString(XLOGLEVEL_INFOR,"on_speech_begin  star");
}

void on_speech_end(int nFlag)
{
	//11201
	/*	//CLogPrint::LogString(XLOGLEVEL_INFOR,"on_speech_end");
	CString strFlag;
	strFlag.Format("%d",nFlag);
	strFlag += "on_speech_end  Flag \n";
	//CLogPrint::LogString(XLOGLEVEL_INFOR,strFlag);	
	
CString strState;
	strState.Format("%d",g_pAudioListener->m_iat.state);
	strState += "State";
	CLogPrint::LogString(XLOGLEVEL_INFOR,strState);

	CString strEP_Stat;
	strEP_Stat.Format("%d",g_pAudioListener->m_iat.ep_stat);
	strEP_Stat += "strEP_Stat";
	CLogPrint::LogString(XLOGLEVEL_INFOR,strEP_Stat);

	CString strREC_Stat;
	strREC_Stat.Format("%d",g_pAudioListener->m_iat.rec_stat);
	strREC_Stat += "strREC_Stat";
	CLogPrint::LogString(XLOGLEVEL_INFOR,strREC_Stat);

	CString strAudio_Status;
	strAudio_Status.Format("%d",g_pAudioListener->m_iat.audio_status);
	strAudio_Status += "strAudio_Status";
	CLogPrint::LogString(XLOGLEVEL_INFOR,strAudio_Status);*/

	/*if(g_pAudioListener->m_bEnableKey )
	{
		g_pAudioListener->Clear();
		g_pAudioListener->m_bEnableKey = false;
		
	}
	g_pAudioListener->m_bEnableKey = false;
	*/
	if(!g_pAudioListener->m_bAutioPowerFlag)
	{
		return;
	}

	if(nFlag == MSP_ERROR_AUTH_NO_ENOUGH_LICENSE)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("【提示信息：】 授权不足，语音已经无法使用"));
		g_pAudioListener->m_bAutioPowerFlag = false;
		return;
	}

	if(nFlag == MSP_ERROR_TIME_OUT)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("【提示信息：】 网络没有连接，语音无法使用"));
		g_pAudioListener->m_bAutioPowerFlag = false;
		g_pAudioListener->m_bStartParse = false;
		g_pAudioTestDlg->UpdateState(false);
		return;
	}

	g_pAudioListener->m_bStartParse = false;
 	//if(nFlag == END_REASON_VAD_DETECT || nFlag == MSP_ERROR_NO_DATA)
 	{
 		SetEvent(g_pAudioListener->m_hEvents[EVT_START]);
	//	CLogPrint::LogString(XLOGLEVEL_INFOR,"on_speech_end  star");
 	}
	g_pAudioListener->Clear();
}

void on_result(const char *result, char is_last)
{
	//CLogPrint::LogString(XLOGLEVEL_INFOR,"on_result");

	if(!g_pAudioListener->m_bStartParse)
	{
		//CLogPrint::LogString(XLOGLEVEL_INFOR,result);

		/*CString strResult = result;
		if(strResult.Find(g_pAudioListener->m_strKeyWord) != -1)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,result);
			g_pAudioListener->m_bStartParse = true;

			g_pAudioListener->m_bEnableKey = false;
			g_pAudioTestDlg->UpdateState(true);


			g_pAudioTestDlg->StartAudioTimer();
			return;
		}*/
		CString strResult = result;
		if(g_pAudioListener->m_pAudioParser->ParseWakeUp(strResult))
		{
			return;
		}
	}

	if(is_last == MSP_REC_STATUS_NO_DEL_TEXT)
	{
		//g_pAudioListener->m_iat.rec_stat = MSP_REC_STATUS_COMPLETE;

		/*CString str = result;
		str += "   on_result   11";
		CLogPrint::LogString(XLOGLEVEL_INFOR,str);
		
		CString str2;
		str2.Format("%d",g_pAudioListener->m_iat.state);
		str2 += "   on_result 22";
		CLogPrint::LogString(XLOGLEVEL_INFOR,str2);*/

		
		//有時候  state 为1  但是后台的程序为启动 目前不知  
		if(g_pAudioListener->m_iat.state == 0)
		{
			SetEvent(g_pAudioListener->m_hEvents[EVT_START]);
			//CLogPrint::LogString(XLOGLEVEL_INFOR,"on_result333  star");
		}
		return;
	}

	else if(g_pAudioListener->m_bStartParse)
	{
		if(result)
		{
			g_pAudioListener->AddToBuffer(result);
		}
	
		if(g_pAudioListener->m_iat.state == 0)
		{
			if(g_pAudioListener->m_nTipWordFlag == Flag_TW_Question)
			{
				g_pAudioListener->m_nTipWordFlag = Flag_AnswerFinish;
			}
			g_pAudioListener->m_bStartParse = false;

			if(!g_pAudioListener->m_bEnableKey)
			{
				g_pAudioTestDlg->UpdateState();
				g_pAudioListener->m_bEnableKey = true;
			}
			g_pAudioListener->m_pAudioParser->ParseResult();
			
			//g_pAudioTestDlg->UpdateState();
		}
	}

	{
		SetEvent(g_pAudioListener->m_hEvents[EVT_START]);
		//CLogPrint::LogString(XLOGLEVEL_INFOR,"on_result  star");
	}
}

UINT ListenerThread(LPVOID pParam)
{

	CAudioListener* pListener = (CAudioListener*)pParam;
	DWORD dwWaitRet = 0;
	struct speech_rec* pIat = &pListener->m_iat;
	struct speech_rec_notifier recnotifier = 
	{
		on_result,
		on_speech_begin,
		on_speech_end
	};

	int nErrCode = sr_init(pIat, pListener->m_strVoiceParams, SR_MIC, DEFAULT_INPUT_DEVID, &recnotifier);
	if (nErrCode) 
	{
		return nErrCode;
	}

	for (int i = 0; i < EVT_TOTAL; ++i) 
	{
		pListener->m_hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	while (1)
	{
		dwWaitRet = WaitForMultipleObjects(EVT_TOTAL, pListener->m_hEvents, FALSE, INFINITE);
		switch (dwWaitRet) 
		{

		case WAIT_FAILED:
		case WAIT_TIMEOUT:
			break;
		case WAIT_OBJECT_0 + EVT_START:
			if(pIat->state == 0)
			{
				nErrCode = sr_start_listening(pIat);
				/*CString str;
				str.Format("%d",nErrCode);
				str += " sr_start_listening  \n";
				//CLogPrint::LogString(XLOGLEVEL_INFOR,"sr_start_listeningTTT " +str);
				OutputDebugString(str);*/

				if (nErrCode != 0 && nErrCode != E_SR_ALREADY) 
				{
					/*CString strError322;
					strError322.Format("%d",nErrCode);
					strError322 += "  strError322";
					CLogPrint::LogString(XLOGLEVEL_INFOR,strError322);*/
					//pListener->m_bExited = true;
					//return nErrCode;
				}
			}
			break;
		case WAIT_OBJECT_0 + EVT_STOP:
			if(pIat->state == 1)
			{
				//CLogPrint::LogString(XLOGLEVEL_INFOR,"sr_stop_listening 11111");
				nErrCode = sr_stop_listening(pIat);

				/*CString str;
				str.Format("%d",nErrCode);
				str += "sr_stop_listening \n";
				OutputDebugString(str);*/

				if (nErrCode != 0) 
				{
					/*CString strError;
					strError.Format("%d",nErrCode);
					strError += "  strError";
					CLogPrint::LogString(XLOGLEVEL_INFOR,strError);*/

					//pListener->m_bExited = true;
					//return nErrCode;
				}
			}
			break;
		default:
			break;
		}
	}
	
	pListener->m_bExited = false;
	return 0;
}


void GetHookKeyName(CString strKeyName)
{
	/*CString strTemp = "GetHookKeyName   ";
	CString strState = "";
	strState.Format("%d",g_pAudioListener->m_bStartParse);
	CLogPrint::LogString(XLOGLEVEL_INFOR,strTemp+strState);*/

	//CLogPrint::LogString(XLOGLEVEL_INFOR,"GetHookKeyName");

	if(!g_pAudioListener->m_bAutioPowerFlag)
	{
		return;
	}
	if(g_pAudioListener->m_pAudioParser->m_bVoiceFlag)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("【提示信息：】 正在播报语音，请稍后！"));
		return;
	}

	//if(g_pAudioListener->m_iat.state == 0)
	//{
	//	return;
	//}

	if(g_pAudioListener->m_strStartKey == strKeyName && !g_pAudioListener->m_bStartParse)
	{
		
		//clear_rec_buffer((WAVEHDR*)g_pAudioListener->m_iat.recorder->bufheader);
		g_pAudioListener->m_nRec_Stat = g_pAudioListener->m_iat.rec_stat;
		g_pAudioListener->m_iat.rec_stat = MSP_REC_STATUS_NO_DEL_TEXT;
		g_pAudioListener->m_bStartParse = true;

		//g_pAudioListener->m_bEnableKey = true;

		/*g_pAudioListener->m_iat.ep_stat = MSP_EP_LOOKING_FOR_SPEECH;
		g_pAudioListener->m_iat.rec_stat = MSP_REC_STATUS_SUCCESS;
		g_pAudioListener->m_iat.audio_status = MSP_AUDIO_SAMPLE_FIRST;*/

		/*free_rec_buffer((HWAVEIN)g_pAudioListener->m_iat.recorder->wavein_hdl,(WAVEHDR *)g_pAudioListener->m_iat.recorder->bufheader, 
									g_pAudioListener->m_iat.recorder->bufcount);*/

		//int length = strlen(((WAVEHDR *)g_pAudioListener->m_iat.recorder->bufheader)->lpData);

		/*int length = ((WAVEHDR *)g_pAudioListener->m_iat.recorder->bufheader)->dwBufferLength;
		memset(((WAVEHDR *)g_pAudioListener->m_iat.recorder->bufheader)->lpData, 0, sizeof(char)*length);

		std::string str = ((WAVEHDR *)g_pAudioListener->m_iat.recorder->bufheader)->lpData;

		CString strTTT(str.c_str());
		strTTT += "   wwwww";
		CLogPrint::LogString(XLOGLEVEL_INFOR,strTTT);*/

		
		g_pAudioTestDlg->UpdateState(true);
		//CLogPrint::LogString(XLOGLEVEL_INFOR,"开始监听");
		//CLogPrint::LogString(XLOGLEVEL_INFOR,"GetHookKeyName  Star");
		//SetEvent(g_pAudioListener->m_hEvents[EVT_START]);
	}
	else if(g_pAudioListener->m_strStopKey == strKeyName && g_pAudioListener->m_bStartParse)
	{
		//g_pAudioListener->m_bStartParse = false;
		//CLogPrint::LogString(XLOGLEVEL_INFOR,"GetHookKeyName  Stop");
		SetEvent(g_pAudioListener->m_hEvents[EVT_STOP]);

		g_pAudioTestDlg->UpdateState(false);
	}
}
