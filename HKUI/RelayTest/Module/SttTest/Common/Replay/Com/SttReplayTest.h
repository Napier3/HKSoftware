#pragma once

#include"../../../../SttTestBase/SttTestBase.h"
#include"../../tmt_replay_test.h"

#ifdef _PSX_QT_LINUX_
#include"../../../../SttDevice/SttDeviceBase.h"
#endif
#include "../../../../ReplayTest/SttComtradeRcvSocket.h"
#include "../../../../ReplayTest/ComtradeBufMngr.h"
#include "../../../../Engine/SttTestServerBase.h"


class CSttReplayTest : public CSttTestBase, public tmt_ReplayParas
{
public:
    CSttReplayTest();
    virtual ~CSttReplayTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttReplayTest();
	}
public:
    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

	int m_nModuleSelCount;
	int m_nChSelCount;


	//处理中间缓存，大小应该是共享缓存中最大缓存
	float *m_pOnceProcessBuf;
	float *m_pProcessBuf;

	int m_nCurrReqIndex;	//当前需要请求ABBuf Index
	int m_nCurrPlayIndex;	//播放Index
    int m_nCurrMdIndex;

	BOOL m_bSendFinish;		//Comtrade文件数据发送完

    float m_arrLastPoint[80];//每次插值最后一个点数据,按80路回放通道预留，实际受带宽限制会少

    Drv_ReplayCoef m_oReplayConf;
    Drv_ComReplayBuffer* m_pComReplayBuffer;

public:
	virtual void AfterSetParameter();
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Init();
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual BOOL EventProcess();
	virtual void Stop();

	virtual void Triger();
	virtual void OnSendDataFinish(int nIndex,int nSendNum);
	virtual void OnSendDataStart(int nIndex,int nSendNum);
	virtual void OnAfterMoveToComtradeBuf(int nIndex,int nDataLen);

	virtual bool NeedCheckHeartbeat()	{	return false;		}
    //将上层结构体转为底层结构体
public:
    virtual void TtmToDrv();

    void SendDataToDevice(long nMdIndex);
    void SendConfToDevice(long nMdIndex);
};
