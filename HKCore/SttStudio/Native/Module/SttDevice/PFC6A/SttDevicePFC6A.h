#ifndef CSTTDEVICEPFC6A_H
#define CSTTDEVICEPFC6A_H

#include "stdafx.h"
#include "../Module/Driver466/SttDeviceComm.h"


class CSttDevicePFC6A : public CSttDeviceComm,public CSttDeviceBase
{
private:
	explicit CSttDevicePFC6A();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();

	static CSttDevicePFC6A *g_pSttDevicePFC6A;

	virtual int InitDevice(BOOL bHasAdjFile);
	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt);
	virtual void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt);
	virtual void tmt_to_drv_manu(tmt_ManualTest *pTmt,BOOL bIsStartTest=FALSE);
	virtual void tmt_to_drv_harm(tmt_HarmTest *pTmt,BOOL bIsStartTest=FALSE);
	virtual void tmt_to_drv_StateItem(tmt_StateParas *pTmt);
    virtual void GetVoltCurRtData(){}
    virtual void GetRtData(){}
    virtual void EventProcessEx(){}
public:
	virtual void SetSystemConfig(){CSttDeviceComm::SetSystemConfig();}
	virtual void SetTestStart(int nTestType){CSttDeviceComm::SetTestStart(nTestType);}
	virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE){CSttDeviceComm::SetTestStop(bIsSysDefaultOutput);}	
	virtual void SetStateTriger(){CSttDeviceComm::SetStateTriger();}
	virtual void tmt_to_drv_StatePara(tmt_StateParas *pTmt){CSttDeviceComm::tmt_to_drv_StatePara(pTmt);}
	virtual void SetDrvMoudlePara();
    virtual void AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,int nModuleType);
	virtual void ProCommDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
	{CSttDeviceComm::ProCommDrvResult(bTestFinished,oTestFinishedTime);}
	virtual void ProStateDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
	{CSttDeviceComm::ProStateDrvResult(bTestFinished,oTestFinishedTime);}
	virtual void InitDrvResult(){CSttDeviceComm::InitDrvResult();}

private:
	void Manual_Current_PFC6A(tmt_channel *pTmt_channel,char *pszDrv,int nHarm,int nIndex,BOOL bIsDc,BOOL bIsModuleOutPut=FALSE);
	void Manual_Current_1000A(tmt_channel *pTmt_channel,char *pszDrv,int nHarm,int nIndex,BOOL bIsDc,BOOL bIsModuleOutPut=FALSE);
	void TransAnalogCurToDrv_1000A(float fAmp,float fAng,float fFre,int nChannel,int nModuleIIndex,long *pnDrvData);
	long TranslateACCurrentAmp_1000A(float fAmp,int nChannel,int nModuleIIndex,int nHarm);

	void State_Current_PFC6A(Drv_StateItem *oDrv_StateItem,tmt_StatePara  oTmt_paraState,int nModuleIIndex);
	void State_Current_1000A(Drv_StateItem *oDrv_StateItem,tmt_StatePara  oTmt_paraState,int nModuleIIndex);

};

#endif // CSTTDEVICEPFC6A_H
