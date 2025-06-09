#ifndef _AUDIODEF_H_
#define _AUDIODEF_H_

#include <ShellAPI.h>

#define	BUFFER_SIZE	4096
#define VOICE_TIMER_EVENT 110
#define WM_VOICE_RESULT WM_USER + 101

//ȷ����Ϣ Flag����
#define ORDER_YES		"1"
#define ORDER_NO		"0"

//����Flag_Error  Flag_Question_ERROR �̶������ظ� orderWord��id 
#define ERROR_ORDERID "6"
#define QUESTION_ERROR_ORDERID "7"
#define QUESTION_TEMPLETE_ORDERID "31"  //ģ����

//����Flag_AnswerNo  �û���ʶ����������� �̶������ظ� orderWord��id 
#define ANSWER_NO_ORDERID "14"
//����Flag_AnswerYES  �û��϶�ʶ����������� �̶������ظ� orderWord��id 
#define ANSWER_YES_ORDERID "15"

////������ת ȷ��ѡ��𰸵� �̶������ظ� orderWord��id 
//#define CONFIRM_ORDERID "17"

//ѡ�����̴��� �̶������ظ� orderWord��id 
#define FLOW_ORDERID "22"
//���� 
#define WAKEUP_ORDERID "8"

// ��ǰ��һ��
#define STEP_STAR_ORDER "9"
// ��ǰ���һ��
#define STEP_END_ORDER "10"

//�����ļ��궨��
#define CFG_STARTKEY		"StartKey"
#define CFG_STOPKEY			"StopKey"
#define CFG_KEYWORD			"KeyWord"
#define CFG_VOICETIME		"VoiceTime"
#define CFG_ENABLELOG		"EnableLog"
//#define CFG_LOGPATH			"LogPath"
#define CFG_ENABLEUSERWORD	"EnableUserWord"
//#define CFG_USERWORDPATH	"UserWordPath"
//#define CFG_VOICEWORDPATH	"VoiceWordPath"


enum tagVoiceIndentifyEvent
{
	EVT_START = 0,
	EVT_STOP,
	EVT_QUIT,
	EVT_TOTAL
};

enum tagAutoTestState
{
	AUTOTEST_NULL = 0,
	AUTOTEST_CREATE,
	AUTOTEST_START,
	AUTOTEST_STOP,
	AUTOTEST_FINISH,
	AUTOTEST_CLOSE
};

enum tagVoiceParaDlgType
{
	DLG_InspectType = 0,
	DLG_DeviceType,
	DLG_PotocolType,
	DLG_TestTemplate,
	DLG_DeviceIPInspect,
	DLG_NUM
};

enum tagVoiceFlag
{
	Flag_NULL = 0,
	Flag_Error,
	Flag_Return,
	//������д ��״̬ 
	Flag_VoiceNULL,
	Flag_VoiceWait,  //��̨���У��ȴ�����
	Flag_VoiceWakeUp, //�Ѿ�����

	//��������  
	Flag_Flow_NULL,
	Flag_Flow,   //ʶ��ȷ������
	Flag_Flow_OK,   //ȷ������ ���
	Flag_TipWord, //�ʴ�״̬״̬
	Flag_StarTest, //����ƥ����ɣ��Ѿ���ʼ����
	Flag_StopTest,
	Flag_EndTest,
	Flag_TestWait, //����ƥ����ɣ��ȴ��´￪ʼ���Ե�ָ��

	//������������  �½�����
	Flag_Question_NULL, //û�н�������������׼������
	Flag_Question_ERROR,//����ʶ�����
	Flag_TW_Question,  //��������״̬
	Flag_AnswerFinish, // �ش����
	Flag_AnswerConfirm, // ��ʾ�ַ�������ʾ��,�û�ȷ��
	Flag_AnswerYse, // �ش�ȷ�� �϶�
	Flag_AnswerNo, // �ش�ȷ�� ��
	Flag_Answer_Success, // �ش� ��ƥ��ɹ�
	Flag_Answer_Fail, // �ش� ��ƥ��ʧ��
	Flag_AnswerCustom,  //���Զ���  IP
	Flag_AnswerCustomConfirm,
	Flag_AnswerWait  // �������� �ش����

};

enum tagFlow
{
	Flow_NewTest = 200,
	Flow_CheckRecord,
	Flow_SetSystem,
	Flow_QuitSystem
};

enum tagStepPageFlag
{
	//����������
	ReturnMain = 100,
	TestStar,
	TestEnd,
	TestStop,
	StarServer,
	StopServer,
	//���� ����,����
	TestProcessUp,
	TestProcessNext,
	TestProcessGo,
	//1��5����
	StepOne,
	StepTwo,
	StepThree,
	StepFour,
	StepFive,
	//��ҳ
	UpPage,
	NextPage,
	FlagPingIP,
	Step_NULL
};


//������ʾ
#define WM_ICON_NOTIFY WM_USER + 1999
inline void CreateTray(NOTIFYICONDATA& notify, HWND hWnd, LPCTSTR szTitle, LPCTSTR szInfo, UINT uTimeout)
{
	Shell_NotifyIcon(NIM_DELETE, &notify);

	char lpszDllName[128];
	GetWindowsDirectory(lpszDllName, _TRUNCATE);
	_tcsncat_s(lpszDllName, "\\System32\\Shell32.dll", _TRUNCATE);

	notify.cbSize = sizeof(NOTIFYICONDATA);
	notify.hWnd = hWnd;
	notify.uID = NULL;
	notify.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
	notify.hIcon = NULL;
	notify.uCallbackMessage = WM_ICON_NOTIFY;

	_tcscpy_s(notify.szTip, "VCϵͳ���̳���");
	_tcscpy_s(notify.szInfo, szInfo);
	_tcscpy_s(notify.szInfoTitle, szTitle);
	notify.dwInfoFlags = NIF_INFO;
	notify.uTimeout = uTimeout;

	Shell_NotifyIcon(NIM_ADD, &notify);
}

#endif