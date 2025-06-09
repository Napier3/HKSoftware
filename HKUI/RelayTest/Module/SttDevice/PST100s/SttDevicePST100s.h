#ifndef CSTTDEVICEPST100S_H
#define CSTTDEVICEPST100S_H

#include "../SttDeviceBase.h"
#include "../../../StableControl/Module/PstApp/SttPst100App.h"
#include "../../SttTest/PST/PST100s/SttSimulationPST100.h"
#include "stdafx.h"

typedef struct
{
    unsigned int length;
    long data[100];
} DrvReplayPkgBout;

typedef struct
{   
    unsigned int cnt;
    DrvReplayPkgBout pkg[8];//×î¶à8Ì¨PST200
} DrvReplayDataBout;

class CSttDevicePST100s : public CSttDeviceBase
{
private:
    explicit CSttDevicePST100s();
    ~CSttDevicePST100s();
    static long g_nSttDeviceRef;
    DrvResultItem m_oResultItem;
    unsigned char *m_pDrvResults;
    StPST100Para m_oPST100Para;
    CPstRcdDataBuffers* m_p2MReplay;
    CPstRcdDataBuffers* m_pBoutReplay;
    long m_nReadRTDSPort;
    DrvModuleDef m_oModuleDef;
    DrvReplayDataBout m_oReplayBout;
    long m_nValidRtdsPorts;

    void SendStartToDrv();
    void SetReplayBout(int nTestType);
    void AfterTestFinish();

public:
	static void Create();
	static void Release();
    static CSttDevicePST100s *g_pSttDevicePST100s;
    CSttPst100App *m_pSttPst100App;
    Drv2MTripLog m_o2MTripLog;

	virtual int InitDevice(BOOL bHasAdjFile);
    virtual void EventProcessEx();
    virtual BOOL OnTimer(BOOL bExec = FALSE);

public:
    virtual void SetSystemConfig(){}
    virtual void SetTestStart(int nTestType);
    virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE);
    virtual void SetTestPara(int nTestType,char *pszBuff){}

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

};

void *ProRtdsDataThread(LPVOID pParam);
#endif // CSTTDEVICEPST100S_H
