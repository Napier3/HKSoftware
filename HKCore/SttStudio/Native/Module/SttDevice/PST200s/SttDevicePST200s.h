#ifndef CSTTDEVICEPST200S_H
#define CSTTDEVICEPST200S_H

#include "../SttDeviceBase.h"
#include "../../../StableControl/Module/PstApp/SttPst200App.h"
#include "../../SttTest/PST/PST200s/SttSimulationPST200.h"
#include "stdafx.h"
#include "../Module/Driver466/IEC61850CfgMngr.h"

typedef struct
{
    unsigned int mSec;  //预估实验结束时间
    unsigned int freq;

    unsigned int module;
    unsigned int ch;
    unsigned int data[12]; //12*4=48
} DrvReplayPara;

typedef struct
{
    unsigned int usegps;
    unsigned int gpsSec;	   // gps time Sec when gps trip
    unsigned int gpsnSec;	   // gps time
} DrvReplayTrip;

typedef struct
{
    unsigned int lenth;
    long dat[4000000];
} DrvReplayData;

typedef struct
{
    unsigned int module;
    unsigned int pkglen;
    DrvReplayData oData;
} DrvReplayDatas;

typedef struct
{
    long nZero[48];
    long nModule;
} DrvPIA48SZero;

class CSttDevicePST200s : public CSttDeviceBase
{
private:
    explicit CSttDevicePST200s();
    ~CSttDevicePST200s();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();
    static CSttDevicePST200s *g_pSttDevicePST200s;
    CSttPst200App *m_pSttPst200App;

	virtual int InitDevice(BOOL bHasAdjFile);
    virtual void EventProcessEx();
    virtual BOOL OnTimer(BOOL bExec = FALSE);

    CPstRcdDataBuffer* m_pRtdsReplayData;
    CSttHdChRcdObject* m_pBinSampleData;
    DrvResultItem m_oResultItem;
    unsigned char *m_pDrvResults;
    DrvReplayPara oReplayPara;
    DrvReplayDatas oReplayDatas;
    void SendConfToDevice();
    void SendDataToDevice_Week();
    void SendDataToDevice_Digital();
    void SendDataToDevice_Switch();
    double GetCoefByRcdDataMaps(long nRcdDataIndex);
    REPLAY_HDCH_RCDDATA_MAPS_MNGR *m_pRtdsMapsMngr;

    CPstRcdDataBuffers* m_p2MReplay;
    DrvModuleDef m_oModuleDef;
    long m_nRtdsChLength;//接收的RTDS单帧报文长度
    long m_nPkgIndex;//接收的RTDS回放数据帧Idx;
    long m_nCurModule;//0-digital 1-week 2-switch
    CPstRtdsFiberOutputMap* m_pOutputMap;
    CIEC61850CfgMngr m_oCIEC61850CfgMngr;


public:
    virtual void* GetIecCfgDatasMngr()	{return &(m_oCIEC61850CfgMngr.m_oIecCfgDatasMngr);}
    virtual void Load_RcdData();
    virtual void SetIEC61850Para()  {m_oCIEC61850CfgMngr.InitIEC61850Para();}
    virtual void SetSystemConfig(){}
    virtual void SetTestStart(int nTestType);
    virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE);
    virtual void SetTestPara(int nTestType,char *pszBuff);

    virtual void InitDrvResult(){}
	virtual void ProCommDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
    {}
	virtual void tmt_to_drv_manu(tmt_ManualTest *pTmt,BOOL bIsStartTest=FALSE)
    { }

	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
    {}

	virtual void GetPI1000ModulesFPGAInfo()
    {}

    virtual void AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,int nModuleType){}

private:
    void InitReplayModule();
    void CalPower(CSttParas *pParas);
    void CalPower();
};

#endif // CSTTDEVICEPST200S_H
