#pragma once

#include "ComtradeBufMngr.h"
#include "BigComtradeFileRead.h"
#include "../SttSocket/TestTerminal/vc/SttClientSocket.h"
#include "ComtradeSendSocket.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
//#include "../Engine/SttTestEngineBase.h"


class CBigComtradeTransPlay : /*public CSttTestMsgViewInterface,*/public CTestEventBaseInterface
{
//2022-11-13  lijunqing
private:
	static CBigComtradeTransPlay *g_pBigComtradeTransPlay;
	static long g_nBigComtradeTransPlay;

public:
	static void Create();
	static void Create(CSttTestAppCfg *pSttTestAppCfg);
	static void Release();

public:
	CBigComtradeTransPlay(void);
	virtual ~CBigComtradeTransPlay(void);
	long GetPlaySampleRate();

	//20221028 zhouhj 录波通道接口
	virtual long Event_OnProcessComtradeRequstData(long nIndex);
	virtual long Event_OnProcessComtradeSendDataStartAck(long nIndex);
	void SetSystemOutputType(int nHasAnalog, int nHasDigital, int nHasWeek);
	void FreeClientEngine();

	BOOL m_bDrawSrcComtrade;  //2021-11-2  lijuniqing true：绘制原始comtrade波形图；false：绘制通道波形图
	CBigComtradeFileRead m_oBigComtradeFileRead;	//Comtrade文件解析对象
	CComtradePlayConfig m_oComtradePlayConfig;		//回放配置对象

private:
	BOOL ComtradeControl_ConnServer(const CString &strIP);
	//故障回放登录socket,作为数据发送socket绑定
	CSttClientSocket m_oComtradeClientSocket;
	CComtradeSendSocket m_oComtradeSendSocket;
	CSttTestEngineClientData *m_pTestEngineClientData;

	BOOL m_bExitThread;
	BOOL m_bUseExternSttTestAppCfg;//标记是否使用外部CSttTestAppCfg对象,未使用外部对象,在析构函数中,需要析构内部对象
	void WaitForThreadExit();

public:
	//根据硬件配置文件初始化配置对象
	BOOL UpdateChMapConfig();
	BOOL SaveComtradeReplayConfig(const CString &strFile);

	//打开Comtrade文件事件处理接口
	BOOL OnOpenComtradeFile(const CString &strComtradeFile,BOOL bInitDefault=TRUE);
	BOOL HasComtradeDataNeedDraw(); //2021-9-19  lijunqing  是否有波形数据需要绘图
	CRcdComtradeFile* GetSrcComtradeFile(); //2021-9-20  lijunqing
	CRcdComtradeFile* GetPlayComtradeFile(); //2021-9-20  lijunqing
	void GenerateComtradeChDatas(BOOL bSeekToBegin);

	//开始测试事件处理接口
	void OnStartTest();
	void OnStopTest();

	//收到请求数据命令
	long OnProcessComtradeRequstData(long nIndex);
	long OnProcessComtradeSendDataStartAck(long nIndex);

	//连接测试仪后创建故障回放通道
	BOOL CreateSttComtradeSocket();

	CExBaseList *GetAnalogs();
	CExBaseList *GetRates();
	CExBaseList *GetBinarys();

	//20230425 zhouhj 改为录波文件独立打开对应配置文件方式
	CSttTestAppCfg *m_pSttTestAppCfg;

	//comtrade文件解析线程
	HANDLE m_pSttComtradeFileReadThread;
#ifdef _PSX_QT_LINUX_
    static void* SttComtradeFileReadThread(LPVOID pParam);
#else
	static UINT SttComtradeFileReadThread(LPVOID pParam);	
#endif
};

extern CBigComtradeTransPlay *g_theBigComtradeTransPlay;
extern CSttTestAppCfg g_oSttTestAppCfg;



