#ifndef _AUDIOLISTENER_H_
#define _AUDIOLISTENER_H_

#include "AudioDef.h"
#include <vector>
#include "MSP/speech_recognizer.h"

class CAudioParser;

//����ʶ��ģ��+�������ݻ���
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
	//������ʱ�� �������ý��� 
	void setAudioParser(CAudioParser* pAudioParser);
	void OnAudioTimer();

	void SetBtnKey(CString strKey);
	//����״̬��ʼ״̬ 
	void SetInitState();

	//����״̬ ,��ʼ���Ժ󣬲�������ʧ�ܣ���״̬�ָ����ȴ�����״̬
	void SetStateNoSatrTest();

	//MSP��
public:
	//��ʼ������
	HANDLE	m_hEvents[EVT_TOTAL];
	char m_strLoginParams[1024];
	char m_strVoiceParams[1024];
	//��ݼ�,���ѹؼ���
	CString m_strKeyWord;
	CString	m_strStartKey;
	CString	m_strStopKey;
	CString	m_strVoiceTime;
	CAudioParser *m_pAudioParser;

	//��������״̬Id  ��һ������һ������ҳ��
	tagStepPageFlag m_nSetpPageFlag;
	//���� ��д��״̬ ���� �ͻ��� ��Ҫ������������
	//tagVoiceFlag m_nVoiceListenFlag;  //����
	//�������״̬
	tagVoiceFlag m_nWholeFlag;
	//�ʴ�״̬
	tagVoiceFlag m_nTipWordFlag;
	//������������
	struct speech_rec m_iat;

	int		m_nRec_Stat;

	BOOL InitMSP();

	//ȫ�ּ��̹���
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