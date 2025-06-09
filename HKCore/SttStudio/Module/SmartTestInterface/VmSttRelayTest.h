#pragma once
#include "../ReplayTest/BigComtradeTransPlay.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../Engine/SttTestEngineClientData.h"

class CVmSttRelayTest
{
public:
	CVmSttRelayTest(void);
	virtual ~CVmSttRelayTest(void);

	long ComtradeReplayTestStart(CString strComtradeFile,CDataGroup *pParas);
	//与测试仪建立录波通道 19813，录波登录
	BOOL CreatComtradeSocket();

	//解析Comtrade文件，存入缓存(独立线程）
	BOOL AnalysisComtradeData(CString strComtradeFile,BOOL bInitDefault=TRUE);

	//下发Test_Start指令
	long Test_TestStart( CDataGroup *pParas);

	//录波通道收到回放请求后，以独立线程下发回放波形数据
	void SendComtradeData();

#ifndef _PSX_QT_LINUX_
	HANDLE m_pSendComtradeThread;
	static UINT SendComtradeThread(LPVOID pParam);
#endif

	void SetSttTestEngineClient(CSttTestEngineClientData *pSttTestEngineClientData);
	void InitReplayConfig(CDataGroup *pParas);

protected:
	CString m_strComtradeFile;
	CSttTestEngineClientData *m_pSttTestEngineClientDataRef;
	
};
