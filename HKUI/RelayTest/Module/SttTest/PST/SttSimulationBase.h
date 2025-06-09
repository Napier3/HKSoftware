#pragma once

#include "../../SttTestBase/SttTestBase.h"
#include "../../../StableControl/Module/RecordDataBuffer/PstRcdDataBufferMngr_Multi.h"
#include "../../../StableControl/Module/SysConfig/PstRtdsFiberOutputMap.h"
#include "../../SttDevice/SttDeviceBase.h"

typedef struct
{
    unsigned int sec;
    unsigned int nSec;
    unsigned int ntype;	 // 1-start 0-stop 2-bichange 3-rtds ready
    unsigned int biValue_32; // 1-32个开入
    unsigned int biValue_64;
}DrvResultItem;

typedef struct
{
    long nRTDS1Pos;
    long nRTDS2Pos;
    long nDModulePos;//Digital
    long nSModulePos;//Switch
    long nWModulePos;//Week
    long n2MModulePos;//2M
} DrvModuleDef;

typedef struct
{
    unsigned int nEnable;
    unsigned int nSec;//相对于开始录波的时间
    unsigned int nNSec;
} Drv2MTripData;

typedef struct
{
    Drv2MTripData oData[9];//对应8个2M接收口,加RTDS开关
} Drv2MTripLog;

typedef struct
{
    unsigned char port;
    unsigned char framelen;
    unsigned char sqnum[6];
    unsigned char utch[4];
    unsigned char utcl[4];
    unsigned char framedata[48];//单帧报文长76字节
} DrvReplayPkg2M;

typedef struct
{
    unsigned int cnt;
    DrvReplayPkg2M pkg[20000];//每次下4800帧
} DrvReplayData2M;

typedef struct
{
    unsigned int nTimeDelayMs;//时间触发延时ms
    unsigned int n2MDelayMs;//2M切机触发延时ms
    unsigned int n2MReplayTripCount;//0-只有实验前握手数据
    unsigned int n2MReplayTripPosition[10];//2M报文回放分段
} StPST100Para;

class CSttSimulationBase : public CSttTestBase
{
public:
    CSttSimulationBase();
    virtual ~CSttSimulationBase(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

public:
    virtual void Init();
    virtual void StartTest(long nStateIdx);
    virtual void ReStart(long nStateIdx){}
    virtual void OnRecordFinished(){}
    virtual void InitModuleCoef(){}
    virtual void SetRtdsFiberOutputMap(CPstRtdsFiberOutputMap* pOutputMap){}
    virtual void Stop();
    void ResetThreadPara();
    Drv2MTripLog m_o2MTripLog;
    DrvReplayData2M m_oReplayData2M;
    long m_pszRtdsMapType[128];//0xXXFF: 0-Uw 1-Bout 2-Ud  0xFFXX: 1-32(Bout)
    long m_nOutputType;//0:week+switch 1:smv+goose 2:ft3
    double m_fCoefWeek[48];
    double m_fCoefSmv[48];
    long m_nReplayChCntWeek;
    long m_nReplayChCntSwitch;
    long m_nReplayChCntSmv;

    double GetWeekCoef(long nChannel)
    {
        return m_fCoefWeek[nChannel];
    }
    double GetSmvCoef(long nChannel)
    {
        return m_fCoefSmv[nChannel];
    }

    void ConnectTo2M_BeforeTest(CPstPort2mMaps *pPst2mMaps,StPST100Para *pStPST100Para,int nCommfd);
    void Send2MDataToDrv(CPstRcdDataBuffers* p2MReplay,int nCommfd);
    void Replay2MDataLog(CPstRcdDataBuffers* p2MReplay);
    void Record2MDataLog(CPstRcdDataBuffers* p2MSample);
    void GetRTDSDataDebug(CPstRcdDataBuffer* pRtdsReplayData);
    void SetRTDSDataDebug(CSttHdChRcdObject* pRtdsSampleRcdObject);
    void SaveRTDSDataDebug(CSttHdChRcdObject* pRtdsSampleRcdObject);
    void SaveRTDSDataDebug(CPstRcdDataBuffer* pRtdsReplayData);
};

extern CSttSimulationBase* g_pSttSimulationBase;
void *Pro2MRecordDataThread(LPVOID pParam);
extern CRingMemBuf *g_pRecvStable2MBuf;
extern CPstRcdDataBuffers* g_p2MSample;
