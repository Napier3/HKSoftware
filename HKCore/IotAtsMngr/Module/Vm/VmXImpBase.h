#pragma once

#include"../../../SttStudio/Module/SmartTestInterface/MacroTestInterface.h"
#include"../../../SttStudio/Module/TestClient/SttMacroTestInterface.h"
#include "../../../SttStudio/Module/SmartTestInterface/SttMacroTestMsgRcvInterface.h"

#include "../../../Module/BaseClass/StringSerializeBufferAscii.h"
#include "../../../SttStudio/Module/SmartTestInterface/SttMacroTestServerInterface.h"
#include "../../../Module/BaseClass/XTimer.h"

class CVmXImpBase;

class CVmXImpBaseMsgWnd : public CWnd
{
public:
	CVmXImpBaseMsgWnd();
	virtual ~CVmXImpBaseMsgWnd();

	void CreateVmXImpBaseMsgWnd(CVmXImpBase *pInterface);

protected:
	CVmXImpBase *m_pVmXImp;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnVmServerCmdRcv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnElectricTestMsg(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnMacroTestMsgConnect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMacroTestMsgBegin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMacroTestMsgStop(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMacroTestMsgException(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMacroTestMsgEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMacroTestMsgRtData(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnConfigDevice(WPARAM wParam, LPARAM lParam);
};

//2021-8-29  lijunqing
class CVmXImpBase : public CSttMacroTestServerInterface
	, public CSttCmdOverTimeMsgRcv
{
public:
	CVmXImpBase();
	virtual ~CVmXImpBase(void);

    CStringSerializeBufferAscii m_oReportBuffer;

	//2021-9-1  lijunqing
	CDataGroup m_oTestMacroParas;

	//2021-9-5  lijunqing
	CVmXImpBaseMsgWnd *m_pVmImpMsgWnd;
	CSttMacroTestEventServerInterface *m_pSttMacroTestEventServerInterface;
	CSttCmmOptrInterface* m_pCmmOptrInterface;
	CString m_strDeviceSN;

public:
	unsigned long m_hMsgWnd;
	unsigned long m_nMsgID;


public:
	virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);

// 	virtual void Release();
// 	virtual long SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID);
// 	virtual CString GetConfig();
// 	virtual long SetConfig(CSttTestAppCfg *pSttTestAppCfg);
// 	virtual long SetConfig(const CString & bstrConfig);
// 	virtual void SetConfig(CDataGroup *pAppConfig);
// 	virtual long Test(const CString & strMacroID, const CString & strParameter);
// 	virtual CString GetReport();
// 	virtual long StopTest();
// 	virtual long CloseDevice();
// 	virtual CString GetSearchReport();
// 	virtual long FinishTest(long nState);
// 	virtual long ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter);
// 	virtual unsigned long GetExternMsgRcvWnd();
// 	virtual unsigned long GetExternMsgID();
// 	virtual unsigned long StopDevice(void);

	//add by shaolei
// 	virtual void SetParameter(CTestMacro *pTestMacro, CDataGroup &oDataGroup, const CString & strParameter);
// 	virtual long System_Login();
	virtual void PostTestWndMsg(WPARAM wParam, LPARAM lParam);

	//���Թ����¼��ӿ�
// 	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas);
// 	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas);
// 	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
// 	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
// 	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas);
// 
// 	virtual void OnReport(CDataGroup *pParas);
// 	virtual long OnAts_Stop(CDataGroup *pParas);


public:
// 	//add by shaolei 20210515
// 	void SetConfig_TestApp();
// 	//add by  shaolei  20210729
// 	void GetParaIDPath(CString &strPath, CDvmData *pData);
// 	void AppendReport_ResultEx(CDataGroup *pRsltGroup);
// 	void GetResultFromTestMacro();

//VM���Թ�����Ϣ������
public:
	LRESULT OnVmServerCmdRcv(WPARAM wParam, LPARAM lParam);
	LRESULT OnElectricTestMsg(WPARAM wParam, LPARAM lParam);

	virtual void OnXTimer(DWORD dwTimerID);
	virtual long TestExec(CDataGroup *pParas);
	virtual long StopTest();
	virtual BOOL ConnectDeviceExec();
	virtual BOOL ConnectDevice();

	virtual void SendRtData();

//CSttMacroTestServerInterface
public:
	virtual void PostVmServerRcvCmd(CSttCmmOptrInterface *pCmmOptrInterface, CSttTestCmd *pTestCmd);
	virtual long SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID);

	virtual long TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);  //����������
	virtual long TestCmd_ConnectDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);  //����������
	virtual long TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);    //ֹͣ������������Ͽ�����
	virtual long TestCmd_SetParameter(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro);    //���ò���
	virtual long TestCmd_UpdateParameter(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro); //���²���
	virtual long TestCmd_StartTest(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro);   //��ʼ���ԣ����Ʋ��������
	virtual long TestCmd_StopTest(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);   //ֹͣ���ԣ�������ֹͣ���
	virtual long TestCmd_GetReport(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro);   //��ȡ����
	virtual long TestCmd_GetSystemState(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);   //��ȡϵͳ״̬
	virtual long TestCmd_TriggerTest(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);   //�ֶ�����
	virtual long TestCmd_FinishInputData(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas);   //�����˹�����������

	virtual BOOL IsTestFinished(DWORD dwPara);
	virtual BOOL IsConnectSuccess();

	virtual long GetEvents(CDataGroup *pSttParas);    //��ȡ�����¼�
	virtual long GetRtDatas(CDataGroup *pSttParas);  //��ȡ�����������ʵʱֵ
	virtual long GetExceptions(CDataGroup *pSttParas);   //��ȡ�쳣

//////////////////////////////////////////////////////////////////////////
//��Ϣ�¼�����
public:
	virtual void OnMacroTestMsgConnect(WPARAM wParam, LPARAM lParam);    //���Զ����Է��������ɹ���ʧ����Ϣ
	virtual void OnMacroTestMsgBegin(WPARAM wParam, LPARAM lParam);      //���Զ����Է��ز��Կ�ʼ��Ϣ
	virtual void OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam);     //���Զ����Է��ز��Խ�����Ϣ
	virtual void OnMacroTestMsgStop(WPARAM wParam, LPARAM lParam);       //���Զ����Է��ز���ֹͣ��Ϣ
	virtual void OnMacroTestMsgException(WPARAM wParam, LPARAM lParam);  //���Զ����Է��ز����쳣��Ϣ
	virtual void OnMacroTestMsgEvent(WPARAM wParam, LPARAM lParam);     
	virtual void OnMacroTestMsgRtData(WPARAM wParam, LPARAM lParam);     //���Զ����Է��ز���ʵʱ������Ϣ
	virtual void OnConfigDevice(WPARAM wParam, LPARAM lParam);
};

