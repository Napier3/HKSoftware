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

	//连接测试仪后创建故障回放通道
	BOOL CreateSttComtradeSocket();
	void FreeClientEngine();

	//改为录波文件独立打开对应配置文件方式
	CSttTestAppCfg *m_pSttTestAppCfg;
	CSttPcapFileRead m_oSttPcapFileRead;

	//comtrade文件解析线程
	HANDLE m_pSttComtradeFileReadThread;
#ifdef _PSX_QT_LINUX_
	static void* SttComtradeFileReadThread(LPVOID pParam);
#else
	static UINT SttComtradeFileReadThread(LPVOID pParam);	
#endif

	//开始测试事件处理接口
	void OnStartTest();
	void OnStopTest();

	//20221028 zhouhj 录波通道接口
	virtual long Event_OnProcessComtradeRequstData(long nIndex);
	virtual long Event_OnProcessComtradeSendDataStartAck(long nIndex);

	//收到请求数据命令
	long OnProcessComtradeRequstData(long nIndex);
	long OnProcessComtradeSendDataStartAck(long nIndex);

protected:
	
	
private:
	BOOL ComtradeControl_ConnServer(const CString &strIP);
	void WaitForThreadExit();
	//故障回放登录socket,作为数据发送socket绑定
	CSttClientSocket m_oComtradeClientSocket;
	CComtradeSendSocket m_oComtradeSendSocket;
	CSttTestEngineClientData *m_pTestEngineClientData;

	BOOL m_bExitThread;
	BOOL m_bUseExternSttTestAppCfg;//标记是否使用外部CSttTestAppCfg对象,未使用外部对象,在析构函数中,需要析构内部对象
};

extern CSttPcapReplayTool *g_theSttPcapReplayTool;
