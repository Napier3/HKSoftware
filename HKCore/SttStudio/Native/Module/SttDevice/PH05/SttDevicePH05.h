#ifndef CSTTDEVICEPH05_H
#define CSTTDEVICEPH05_H

#include "../Module/Driver466/SttDeviceComm.h"
#include "stdafx.h"

class CSttDevicePH05 : public CSttDeviceComm,public CSttDeviceBase
{
private:
    explicit CSttDevicePH05();
    ~CSttDevicePH05();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();
    static CSttDevicePH05 *g_pSttDevicePH05;

	virtual int InitDevice(BOOL bHasAdjFile);

public:
	virtual void SetSystemConfig(){CSttDeviceComm::SetSystemConfig();}

	virtual void SetTestStart(int nTestType){CSttDeviceComm::SetTestStart(nTestType);}
	virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE){CSttDeviceComm::SetTestStop(bIsSysDefaultOutput);}
	virtual void SetTestPara(int nTestType,char *pszBuff){CSttDeviceComm::SetTestPara(nTestType,pszBuff);}
	virtual void SetManualBI(char* pszBuff,int nLen){CSttDeviceComm::SetManualBI(pszBuff,nLen);}
	virtual void SetBISetting(){CSttDeviceComm::SetBISetting();}

	virtual void SetBinaryOutTurnOnVaule(int nValue){CSttDeviceComm::SetBinaryOutTurnOnVaule(nValue);}
	virtual void SetBinaryOut(BOOL bOpen=FALSE){CSttDeviceComm::SetBinaryOut(bOpen);}

    virtual void InitWeekOutputDAData(){CSttDeviceComm::InitWeekOutputDAData();}
	virtual void InitDrvResult(){CSttDeviceComm::InitDrvResult();}
	virtual void ProCommDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
	{CSttDeviceComm::ProCommDrvResult(bTestFinished,oTestFinishedTime);}
	virtual void tmt_to_drv_manu(tmt_ManualTest *pTmt,BOOL bIsStartTest=FALSE)
	{ m_bCurTestIsGradient=FALSE;CSttDeviceComm::tmt_to_drv_manu(pTmt,bIsStartTest);}

	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
	{CSttDeviceComm::tmt_to_drv_moduleoutput(pTmt);}

	virtual void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt)
	{CSttDeviceComm::tmt_to_drv_systemdefaultoutput(pTmt);}

	virtual void SetStateTriger(){CSttDeviceComm::SetStateTriger();}
	virtual void tmt_to_drv_StatePara(tmt_StateParas *pTmt){CSttDeviceComm::tmt_to_drv_StatePara(pTmt);}
	virtual void tmt_to_drv_StateItem(tmt_StateParas *pTmt){CSttDeviceComm::tmt_to_drv_StateItem(pTmt);}
	virtual void ProStateDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
	{CSttDeviceComm::ProStateDrvResult(bTestFinished,oTestFinishedTime);}

	virtual void FormatFlashData(PSTT_MODULE pModule,BYTE *pszBuf,long &nLen)
	{CSttDeviceComm::FormatFlashData(pModule,pszBuf,nLen);}

	virtual int SetModuleFlash(PSTT_MODULE pModule,BYTE *pszBuf,int nLen)
	{CSttDeviceComm::SetModuleFlash(pModule,pszBuf,nLen);}

	virtual BOOL GetModuleFlash(PSTT_MODULE pModule,BYTE *pszBuf,int &nOffset)
	{return CSttDeviceComm::GetModuleFlash(pModule,pszBuf,nOffset);}

	virtual void GetPI1000ModulesFPGAInfo()
	{CSttDeviceComm::GetModulesFPGAInfo();}

    virtual void AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,int nModuleType);

    //ComReplay
public:
    virtual void tmt_to_drv_ComReplay(tmt_ReplayParas *pTmt,char *pszReplayCoef)
    {CSttDeviceComm::tmt_to_drv_ComReplay(pTmt,pszReplayCoef);}
};

#endif // CSTTDEVICEPI1000_H
