#pragma once

#include"MacroTestInterface.h"
#include "../Engine/SttClientTestEngine.h"
#include "SttMacroTestMsgRcvInterface.h"
#include "../TestClient/SttTestClientBase.h"
#include "VmSttRelayTest.h"
#include "../../../Module/BaseClass/TxCycleArray.h"

#ifdef _USE_SMARTTEST_INTERFACE_STT_

//2020-11-6  lijunqing
#include "../../../Module/BaseClass/StringSerializeBufferAscii.h"

#ifdef _PSX_IDE_QT_

#else
#include "VC/VmSttMacroTestSpyDlg.h"
#endif

//2020-10-17  lijunqing
extern BOOL g_bIsSendTestCmding;  //�Ƿ����ڷ���TestCmdָ��

class CVmSttMacroTest : public CMacroTestInterface
	, public CMacroTestEventInterface
	, public CSttCmdOverTimeMsgRcv
{
public:
	CVmSttMacroTest();
	virtual ~CVmSttMacroTest(void);

    virtual void Release();

    //CSttMacroTestMsgRcvInterface *m_pTestMsgRcv;
	unsigned long m_hMsgWnd;
	unsigned long m_nMsgID;

	//2021-8-13  lijunqing use CSttTestClientBase::m_oTestAppCfg, delete CSttTestAppCfg
	CSttTestClientBase m_oSttTestClient;
	CVmSttRelayTest *m_pSttReplayTest;
	BOOL m_bConnected;
	//PNS330����λ���޸�ϵͳ�������ú�����ִ��StartTest��ͬʱ������Ե������ʼ���ԡ���
	//Ϊ�˷�ֹϵͳ��������δ���������·���һ��StartTestָ������Ӵ˱���
	//2024-2-1 �ƶ�������CMacroTestInterface
	//BOOL m_bTestStarted;

	//2020-11-6  lijunqing
    //CString m_strReport;
    CStringSerializeBufferAscii m_oReportBuffer;
	//���ڱ���ReadDeviceParameterָ��ص����ݣ��Ա�Native�ͻ��˵�¼�󣬷��ظ���
	//CSttParas m_oReadDeviceParameter;  //shaolei 2023-12-19.��Ϊȫ��
	CDataGroup m_oSearchRslts;  //�����������

	//2023-4-22  lijunqing
#ifndef _PSX_QT_LINUX_
	CVmSttMacroTestSpyDlg *m_pVmSttMacroTestSpyDlg;
#endif

	//BOOL m_bIsSendTestCmding;
	BOOL m_bIsReleaseing;  //�Ƿ��������������������Ļ������ٴ���������ָ��
	//��Ϊ19815�����ʱ����Ҫת����λ����TestCmdָ��
	TxCycleArray<CSttTestCmd> m_oArrSttTestCmd;  //�����TestCmd�����б������������
	//TxCycleArray<CSttTestCmd> *m_ppArray;
	CAutoCriticSection m_oTestCriticSection;	//ִ��Test�Ļ�����

protected:
	BOOL m_bStopFlag;
public:
	void SetStopFlag(BOOL bStop);

public:
	virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);

public:
	virtual long SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID);
	virtual CString GetConfig();
	virtual long SetConfig(CSttTestAppCfg *pSttTestAppCfg);
	virtual long SetConfig(const CString & bstrConfig);
	virtual long Test(const CString & strMacroID, const CString & strParameter);
	virtual CString GetReport();
	virtual long StopTest();
	virtual long CloseDevice();
	virtual CString GetSearchReport();
	virtual long FinishTest(long nState);
	virtual long ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter);
	virtual unsigned long GetExternMsgRcvWnd();
	virtual unsigned long GetExternMsgID();
	virtual unsigned long StopDevice(void);
    virtual long UpdateParameter(const CString &strMacroID, CDataGroup *pParas);
    virtual long ManualTrigger();
	
	//2022-4-20 shaolei lijunq 
	virtual long SendTestCmd(BYTE *pBuf, long nLen);
	virtual long SendTestCmd(CSttTestCmd *pTestCmd);
	virtual long SendTestCmdEx(CSttTestCmd *pTestCmd);
	long SendNextTestCmd();


    //2022-2-12  lijunqing  Ϊͨ��ͨ���ƶ�ת�����ĵĶ���ָ��
    virtual void AddPkgDispatchInterface(CSttPkgDispatchInterface *p);
	virtual void RemovePkgDispatchInterface(CSttPkgDispatchInterface *p);

	//add by shaolei
	BOOL SetParameter(CTestMacro *pTestMacro, const CString & strParameter);
    BOOL SetParameter_ChMapsConfig(CDataGroup &oDataGroup, const CString &strParameter);
    //shaolei 20220215
    BOOL SetParameter_ChMapsConfig_UIParas(CDataGroup &oDataGroup, const CString &strParameter);
    BOOL SetParameter_IECConfig(CDataGroup &oDataGroup, const CString &strParameter);
	BOOL SetParameter_IECConfig_UIParas(CDataGroup &oDataGroup, const CString &strParameter);
	BOOL SetParameter_SystemConfig(CDataGroup &oDataGroup, const CString &strParameter);
	BOOL ConnectDevice();
	BOOL IsConnectSuccess();
	long System_Login();
	long Adjust_ReadDeviceParameter(CStringArray &astrTypes, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);
	void PostTestWndMsg(WPARAM wParam, LPARAM lParam);
	long Test_StartTest(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);
	long ComtradeReplayTest();

	//���Թ����¼��ӿ�
	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);

	virtual void OnReport(CDataGroup *pParas);
	virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas);
	virtual long OnAts_Stop(CDataGroup *pParas);

public:
	//add by shaolei 20210515
	void SetConfig_TestApp();
	//add by  shaolei  20210729
	void GetParaIDPath(CString &strPath, CDvmData *pData);
	void GetParaNamePath(CString &strPath, CDvmData *pData);
	void AppendReport_ResultEx(CDataGroup *pRsltGroup);
	void AppendReport_ResultEx(CDvmValues *pValues, CDataGroup *pRsltGroup);
	void GetResultFromTestMacro();

	//�����ض��Ĳ��Թ��ܣ��Բ��Թ���ID����������������ݱ���Ե��������������
	void GenGbItem_MacroID_Revise(CString &strMacroID);
	void ResetParasByStateCount(long nStateCount);
	void ResetParasByStateCount(CDataGroup *pParas, long nStateCount);
	void ResetParas_RsltEvalute();

private:
	BOOL IsAdjust(const CString &strMacroID);
};


class CSttMacroTestCreator : public CMacroTestCreatorInterface
{
public:
	CSttMacroTestCreator();
	virtual ~CSttMacroTestCreator();

public:
	virtual CMacroTestEngineInterface* CreateMacroTestEngine(const CString &strMacroFile);
	virtual CMacroTestEngineInterface* GetMacroTestEngine(const CString &strType, const CString &strProgID, const CString &strMacroFile);
	virtual CMacroTestInterface* GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps);
	virtual void ReleaseMacroTestEngine();
	virtual void ReleaseMacroTestEngine(const CString &strProgID);
	virtual void InitMacroTestEngineShowSpyWnd();
	virtual void ShowSpyWnd();
	virtual void ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara);
	virtual long ConfigEngine(const CString &strMacroFile, const CString &strIP);
	virtual long AttatchLogWnd(unsigned long hWnd);
};

#endif  //#ifdef _USE_SMARTTEST_INTERFACE_STT_
