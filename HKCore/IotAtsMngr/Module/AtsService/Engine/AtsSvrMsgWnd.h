//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrService.h  CAtsSvrService

#pragma once

#include "SttAtsSvrMqttImpBase.h"

//定时时钟，定期检查与
#define ATS_SVR_WATCH_TIMER_ID      1040

class CAtsSvrMsgWnd : public CWnd
{
public:
	CAtsSvrMsgWnd();
	virtual ~CAtsSvrMsgWnd();

	void CreateAtsSvrMsgWnd(CSttAtsSvrMqttImpBase *pService);

	/*移动到CSttSmartTestCom类  shaolei 20230605
	BOOL DownLoadAllFiles(CSttAtsCmd *pAtsCmd);
	BOOL DownLoadFiles_Devices(CDataGroup *pDevices);  //下载模型文件和规约模板
	BOOL DownLoadFiles_TestApps(CDataGroup *pTestApps);  //下载测试仪配置文件
	*/

protected:
	CSttAtsSvrMqttImpBase *m_pAtsService;
	char *m_pDestBuffer;

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnSttEngineCmdRcv(WPARAM wParam, LPARAM lParam);   //对应CAtsCmd
	afx_msg LRESULT OnSttEngineCmdRcv_JSON(WPARAM wParam, LPARAM lParam);  //shaolei 20210927   //只处理单纯的JSON报文。UploadReportFinish
	afx_msg LRESULT OnSttEngineCmdRcv_IotCmd(WPARAM wParam, LPARAM lParam);   //对应CIotCmd
	afx_msg LRESULT OnSttEngineCmdRcv_TestCmd(WPARAM wParam, LPARAM lParam);   //对应CTestCmd
	afx_msg LRESULT OnSttEngineCmdRcv_SysState(WPARAM wParam, LPARAM lParam);   //对应CSysState
	afx_msg void OnTimer(UINT nIDEvent);

};

