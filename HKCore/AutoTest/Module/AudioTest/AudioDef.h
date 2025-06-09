#ifndef _AUDIODEF_H_
#define _AUDIODEF_H_

#include <ShellAPI.h>

#define	BUFFER_SIZE	4096
#define VOICE_TIMER_EVENT 110
#define WM_VOICE_RESULT WM_USER + 101

//确认信息 Flag定义
#define ORDER_YES		"1"
#define ORDER_NO		"0"

//返回Flag_Error  Flag_Question_ERROR 固定语音回复 orderWord的id 
#define ERROR_ORDERID "6"
#define QUESTION_ERROR_ORDERID "7"
#define QUESTION_TEMPLETE_ORDERID "31"  //模板多个

//返回Flag_AnswerNo  用户否定识别出来的文字 固定语音回复 orderWord的id 
#define ANSWER_NO_ORDERID "14"
//返回Flag_AnswerYES  用户肯定识别出来的文字 固定语音回复 orderWord的id 
#define ANSWER_YES_ORDERID "15"

////步骤跳转 确认选择答案的 固定语音回复 orderWord的id 
//#define CONFIRM_ORDERID "17"

//选择流程错误 固定语音回复 orderWord的id 
#define FLOW_ORDERID "22"
//唤醒 
#define WAKEUP_ORDERID "8"

// 当前第一步
#define STEP_STAR_ORDER "9"
// 当前最后一步
#define STEP_END_ORDER "10"

//配置文件宏定义
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
	//语音听写 的状态 
	Flag_VoiceNULL,
	Flag_VoiceWait,  //后台运行，等待唤醒
	Flag_VoiceWakeUp, //已经唤醒

	//整体流程  
	Flag_Flow_NULL,
	Flag_Flow,   //识别，确认流程
	Flag_Flow_OK,   //确认流程 完成
	Flag_TipWord, //问答状态状态
	Flag_StarTest, //参数匹配完成，已经开始测试
	Flag_StopTest,
	Flag_EndTest,
	Flag_TestWait, //参数匹配完成，等待下达开始测试的指令

	//完整问题流程  新建测试
	Flag_Question_NULL, //没有进入语音问他，准备进入
	Flag_Question_ERROR,//语音识别错误
	Flag_TW_Question,  //语音提问状态
	Flag_AnswerFinish, // 回答完成
	Flag_AnswerConfirm, // 显示字符串在提示框,用户确认
	Flag_AnswerYse, // 回答确认 肯定
	Flag_AnswerNo, // 回答确认 否定
	Flag_Answer_Success, // 回答 答案匹配成功
	Flag_Answer_Fail, // 回答 答案匹配失败
	Flag_AnswerCustom,  //答案自定义  IP
	Flag_AnswerCustomConfirm,
	Flag_AnswerWait  // 所有问题 回答完成

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
	//返回主界面
	ReturnMain = 100,
	TestStar,
	TestEnd,
	TestStop,
	StarServer,
	StopServer,
	//步骤 上下,继续
	TestProcessUp,
	TestProcessNext,
	TestProcessGo,
	//1到5步骤
	StepOne,
	StepTwo,
	StepThree,
	StepFour,
	StepFive,
	//翻页
	UpPage,
	NextPage,
	FlagPingIP,
	Step_NULL
};


//气泡提示
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

	_tcscpy_s(notify.szTip, "VC系统托盘程序");
	_tcscpy_s(notify.szInfo, szInfo);
	_tcscpy_s(notify.szInfoTitle, szTitle);
	notify.dwInfoFlags = NIF_INFO;
	notify.uTimeout = uTimeout;

	Shell_NotifyIcon(NIM_ADD, &notify);
}

#endif