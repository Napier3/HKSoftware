#ifndef _AUDIOLISTENER_H_
#define _AUDIOLISTENER_H_

#include "AudioDef.h"
#include <vector>
#include "MSP/speech_recognizer.h"

class CAudioParser;

//语音识别模块+文字数据缓存
class CAudioListener
{
public:
	bool m_bExited;
	bool m_bEnableKey;
	std::vector<CString> m_vecBuffer;
	CMutex m_lockerReadWrite;
	NOTIFYICONDATA m_notify;

	bool m_bStartParse;
	bool m_bAutioPowerFlag;

public:
	CAudioListener();
	virtual ~CAudioListener();

	BOOL SetupListener();
	BOOL SetupListener(CString strKeyWord, CString strStartKey, CString strStopKey,CString strVoiceTime = "7000");
	void AddToBuffer(CString strBuffer);
	void MoveToBuffer(std::vector<CString>& vecBuffer);
	void Clear();
	//按键的时候 主动调用解析 
	void setAudioParser(CAudioParser* pAudioParser);
	void OnAudioTimer();

	void SetBtnKey(CString strKey);
	//设置状态初始状态 
	void SetInitState();

	//设置状态 ,开始测试后，测试启动失败，将状态恢复到等待测试状态
	void SetStateNoSatrTest();

	//MSP库
public:
	//初始化参数
	HANDLE	m_hEvents[EVT_TOTAL];
	char m_strLoginParams[1024];
	char m_strVoiceParams[1024];
	//快捷键,唤醒关键词
	CString m_strKeyWord;
	CString	m_strStartKey;
	CString	m_strStopKey;
	CString	m_strVoiceTime;
	CAudioParser *m_pAudioParser;

	//语音命令状态Id  上一步，下一步，翻页等
	tagStepPageFlag m_nSetpPageFlag;
	//语音 听写的状态 监听 和唤醒 主要用于自主监听
	//tagVoiceFlag m_nVoiceListenFlag;  //不用
	//整体测试状态
	tagVoiceFlag m_nWholeFlag;
	//问答状态
	tagVoiceFlag m_nTipWordFlag;
	//语音监听对象
	struct speech_rec m_iat;

	int		m_nRec_Stat;

	BOOL InitMSP();

	//全局键盘钩子
public:
	void InitKeyboardHook();
	void ExitKeyboardHook();
};

static void on_speech_begin();
static void on_result(const char *result, char is_last);	
static void on_speech_end(int nFlag);
static UINT ListenerThread(LPVOID pParam);

extern CAudioListener* g_pAudioListener;
static void GetHookKeyName(CString strKeyName);

#endif