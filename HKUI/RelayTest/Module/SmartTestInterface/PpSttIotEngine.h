#pragma once

#include "PpXIotEngineBase.h"
#include "../../../Module/MemBuffer/TxRingPtrBuffer.h"
#define STT_PP_IOT_ENGINE_SPY_DATA_MAX_NUM          100//循环缓存最大存储报文数量


class CPpSttIotDevice : public CPpSttIotDeviceBase, public CTestEventBaseInterface
{
public:
	CPpSttIotDevice();
	virtual ~CPpSttIotDevice();

public:

    CPpSttIotClient *m_pSttIotClient;
	//事件接口
	virtual void On_SysState_IOT(CSttSysState *pSysState);

public:
	virtual long X_SendIotCmd(CSttIotCmd &oIotCmd);

	virtual BOOL IsConnectIotServerSucc();
	virtual long IsConnectSuccessful();
	virtual BOOL ConnectSttServer();
	virtual void NewSttIotClient();
    virtual void SetSttCmdDataFormat(long nSttCmdForat);
	virtual void DisConnect();
	virtual void DisConnectForClose(BOOL bDelete);  //断开连接

	BOOL GetRunProcedureRltValue(const CString &strID,long &nValue);//获取通讯命令运行结果 zhouhj 2024.3.14

	//zhouhj 2024.1.23 增加用于报文监视
	virtual long Event_OnPkgSpy(CSttParas *pSttParas);
//	CExBaseList m_oPkgSpyList;
	CTxRingPtrBuffer<CExBaseObject> m_oPkgSpyList;
};

class CPpSttIotEngine : public CPpXIotEngineBase
{
public:
	CPpSttIotEngine();
	virtual ~CPpSttIotEngine(void);

public:
	virtual CPpSttIotDeviceBase* CreateNewDevice();

};
