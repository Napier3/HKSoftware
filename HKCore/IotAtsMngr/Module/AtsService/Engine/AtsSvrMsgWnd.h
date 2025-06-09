//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrService.h  CAtsSvrService

#pragma once

#include "SttAtsSvrMqttImpBase.h"

//��ʱʱ�ӣ����ڼ����
#define ATS_SVR_WATCH_TIMER_ID      1040

class CAtsSvrMsgWnd : public CWnd
{
public:
	CAtsSvrMsgWnd();
	virtual ~CAtsSvrMsgWnd();

	void CreateAtsSvrMsgWnd(CSttAtsSvrMqttImpBase *pService);

	/*�ƶ���CSttSmartTestCom��  shaolei 20230605
	BOOL DownLoadAllFiles(CSttAtsCmd *pAtsCmd);
	BOOL DownLoadFiles_Devices(CDataGroup *pDevices);  //����ģ���ļ��͹�Լģ��
	BOOL DownLoadFiles_TestApps(CDataGroup *pTestApps);  //���ز����������ļ�
	*/

protected:
	CSttAtsSvrMqttImpBase *m_pAtsService;
	char *m_pDestBuffer;

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnSttEngineCmdRcv(WPARAM wParam, LPARAM lParam);   //��ӦCAtsCmd
	afx_msg LRESULT OnSttEngineCmdRcv_JSON(WPARAM wParam, LPARAM lParam);  //shaolei 20210927   //ֻ��������JSON���ġ�UploadReportFinish
	afx_msg LRESULT OnSttEngineCmdRcv_IotCmd(WPARAM wParam, LPARAM lParam);   //��ӦCIotCmd
	afx_msg LRESULT OnSttEngineCmdRcv_TestCmd(WPARAM wParam, LPARAM lParam);   //��ӦCTestCmd
	afx_msg LRESULT OnSttEngineCmdRcv_SysState(WPARAM wParam, LPARAM lParam);   //��ӦCSysState
	afx_msg void OnTimer(UINT nIDEvent);

};

