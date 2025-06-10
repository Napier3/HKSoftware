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

//���봥�����ݽṹ
typedef struct
{
    unsigned int nBiRef;			//0:��ת����	 1���½��ش���	2�������ش���
    unsigned int nBiLogic;		//0�������	1��������
    unsigned int nVal1;			//��Чλ��ֵ
} DrvPcapBITrip;

typedef struct
{
    unsigned int modules;
    unsigned int tripType;		//0�޴�����1�ֶ�������2GPS������3����������
    DrvPcapBITrip stBITrip;			//���봥������
    unsigned int gpsSec;
    unsigned int gpsnSec;

    unsigned int mSec;//ʵ��������ʱ��
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
    BOOL m_bSendFinish;		//Comtrade�ļ����ݷ�����

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
    //���ϲ�ṹ��תΪ�ײ�ṹ��
public:
    void SendDataToDevice();
};
