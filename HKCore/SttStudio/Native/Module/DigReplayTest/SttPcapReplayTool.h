#pragma once

#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "../SttSocket/TestTerminal/vc/SttClientSocket.h"
#include "../ReplayTest/ComtradeSendSocket.h"
#include "../ReplayTest/ComtradeBufMngr.h"
#include "SttPcapFileRead.h"


class CSttPcapReplayTool  : public CTestEventBaseInterface
{
private:
	static CSttPcapReplayTool *g_pSttPcapReplayTool;
	static long g_nSttPcapReplayTool;

public:
	static void Create();
	static void Create(CSttTestAppCfg *pSttTestAppCfg);
	static void Release();
public:
	CSttPcapReplayTool(void);
	virtual ~CSttPcapReplayTool(void);

	BOOL OnOpenPcapFile(const CString &strPcapFile);
	BOOL HasOpenPcapFile();

	//���Ӳ����Ǻ󴴽����ϻط�ͨ��
	BOOL CreateSttComtradeSocket();
	void FreeClientEngine();

	//��Ϊ¼���ļ������򿪶�Ӧ�����ļ���ʽ
	CSttTestAppCfg *m_pSttTestAppCfg;
	CSttPcapFileRead m_oSttPcapFileRead;

	//comtrade�ļ������߳�
	HANDLE m_pSttComtradeFileReadThread;
#ifdef _PSX_QT_LINUX_
	static void* SttComtradeFileReadThread(LPVOID pParam);
#else
	static UINT SttComtradeFileReadThread(LPVOID pParam);	
#endif

	//��ʼ�����¼�����ӿ�
	void OnStartTest();
	void OnStopTest();

	//20221028 zhouhj ¼��ͨ���ӿ�
	virtual long Event_OnProcessComtradeRequstData(long nIndex);
	virtual long Event_OnProcessComtradeSendDataStartAck(long nIndex);

	//�յ�������������
	long OnProcessComtradeRequstData(long nIndex);
	long OnProcessComtradeSendDataStartAck(long nIndex);

protected:
	
	
private:
	BOOL ComtradeControl_ConnServer(const CString &strIP);
	void WaitForThreadExit();
	//���ϻطŵ�¼socket,��Ϊ���ݷ���socket��
	CSttClientSocket m_oComtradeClientSocket;
	CComtradeSendSocket m_oComtradeSendSocket;
	CSttTestEngineClientData *m_pTestEngineClientData;

	BOOL m_bExitThread;
	BOOL m_bUseExternSttTestAppCfg;//����Ƿ�ʹ���ⲿCSttTestAppCfg����,δʹ���ⲿ����,������������,��Ҫ�����ڲ�����
};

extern CSttPcapReplayTool *g_theSttPcapReplayTool;
