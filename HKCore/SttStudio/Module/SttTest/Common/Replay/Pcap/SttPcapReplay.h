#pragma once

#include"../../../../SttTestBase/SttTestBase.h"
#include"../../tmt_dig_replay_test.h"

#ifdef _PSX_QT_LINUX_
    #include"../../../../SttDevice/SttDeviceBase.h"
#endif
#include "../../../../ReplayTest/SttComtradeRcvSocket.h"
#include "../../../../ReplayTest/ComtradeBufMngr.h"
#include "../../../../Engine/SttTestServerBase.h"

#define REPLAY_FLAG_WRITE_FINISH        0x01
#define REPLAY_FLAG_TEST_FINISH			0x02

typedef struct
{
    unsigned int module;
    unsigned int pkglen;
    long dat[3000000];//10*1024*1024 / 4
} DrvPcapData;

//开入触发数据结构
typedef struct
{
    unsigned int nBiRef;			//0:翻转触发	 1：下降沿触发	2：上升沿触发
    unsigned int nBiLogic;		//0：开入或	1：开入与
    unsigned int nVal1;			//有效位的值
} DrvPcapBITrip;

typedef struct
{
    unsigned int modules;
    unsigned int tripType;		//0无触发，1手动触发，2GPS触发，3开入量触发
    DrvPcapBITrip stBITrip;			//开入触发配置
    unsigned int gpsSec;
    unsigned int gpsnSec;

    unsigned int mSec;//实验运行总时长
} DrvPcapParam;

class CSttPcapReplay : public CSttTestBase, public tmt_DigReplayParas
{
public:
    CSttPcapReplay();
    virtual ~CSttPcapReplay(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase *CreateTest()
    {
        return new CSttPcapReplay();
    }
public:
    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

    long m_nCurReqIndex;
    long m_nCurReplayIndex;
    long m_nCurReplayLoopIndex;
    BOOL m_bInLooping;
    BOOL m_bSendFinish;		//Comtrade文件数据发送完

    DrvPcapData *m_pPcapData;
    DrvPcapParam m_oPcapParam;

public:
    virtual void AfterSetParameter();
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Init();
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
    virtual BOOL EventProcess();
	virtual BOOL EventProcessEx();
    virtual void Triger();

    virtual void OnSendDataFinish(int nIndex, int nSendNum);
    virtual void OnSendDataStart(int nIndex, int nSendNum);
    virtual void OnAfterMoveToComtradeBuf(int nIndex, int nDataLen);

    virtual bool NeedCheckHeartbeat()
    {
        return false;
    }
    //将上层结构体转为底层结构体
public:
    void SendDataToDevice();
};
