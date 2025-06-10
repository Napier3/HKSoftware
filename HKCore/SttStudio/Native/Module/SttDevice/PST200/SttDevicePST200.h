#ifndef CSTTDEVICEPST200_H
#define CSTTDEVICEPST200_H

#include "../Module/Driver466/SttDeviceComm.h"
#include "stdafx.h"

class CSttDevicePST200 : public CSttDeviceComm,public CSttDeviceBase
{
private:
    explicit CSttDevicePST200();
    ~CSttDevicePST200();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();
    static CSttDevicePST200 *g_pSttDevicePST200;    

	virtual int InitDevice(BOOL bHasAdjFile);
    virtual void EventProcessEx();
    virtual void PreStartTestPro();
    virtual void AfterTestFinishedPro();

public:
	virtual void SetSystemConfig(){CSttDeviceComm::SetSystemConfig();}
	virtual void SetAuxDcVolt(float fUdc){CSttDeviceComm::SetAuxDcVolt(fUdc);}

	virtual void SetTestStart(int nTestType){CSttDeviceComm::SetTestStart(nTestType);}
	virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE){CSttDeviceComm::SetTestStop(bIsSysDefaultOutput);}
	virtual void SetTestPara(int nTestType,char *pszBuff){CSttDeviceComm::SetTestPara(nTestType,pszBuff);}
	virtual void SetManualBI(char* pszBuff,int nLen){CSttDeviceComm::SetManualBI(pszBuff,nLen);}
	virtual void SetBISetting(){CSttDeviceComm::SetBISetting();}

	virtual void SetGooseSub(char* pszBuff){CSttDeviceComm::SetGooseSub(pszBuff);}
	virtual void SetBoMap(char* pszBuff){CSttDeviceComm::SetBoMap(pszBuff);}
	virtual void SetBinaryOutTurnOnVaule(int nValue){CSttDeviceComm::SetBinaryOutTurnOnVaule(nValue);}
	virtual void SetBinaryOut(BOOL bOpen=FALSE){CSttDeviceComm::SetBinaryOut(bOpen);}

	virtual void InitDrvResult(){CSttDeviceComm::InitDrvResult();}
	virtual void ProCommDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
	{CSttDeviceComm::ProCommDrvResult(bTestFinished,oTestFinishedTime);}
	virtual void tmt_to_drv_manu(tmt_ManualTest *pTmt,BOOL bIsStartTest=FALSE)
	{ m_bCurTestIsGradient=FALSE;CSttDeviceComm::tmt_to_drv_manu(pTmt,bIsStartTest);}

	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
	{CSttDeviceComm::tmt_to_drv_moduleoutput(pTmt);}

	virtual void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt)
	{CSttDeviceComm::tmt_to_drv_systemdefaultoutput(pTmt);}

	virtual void tmt_to_drv_harm(tmt_HarmTest *pTmt,BOOL bIsStartTest=FALSE)
	{m_bCurTestIsGradient=FALSE;CSttDeviceComm::tmt_to_drv_harm(pTmt,bIsStartTest);}

	virtual void SetStateTriger(){CSttDeviceComm::SetStateTriger();}
	virtual void tmt_to_drv_StatePara(tmt_StateParas *pTmt){CSttDeviceComm::tmt_to_drv_StatePara(pTmt);}
	virtual void tmt_to_drv_StateItem(tmt_StateParas *pTmt){CSttDeviceComm::tmt_to_drv_StateItem(pTmt);}
	virtual void ProStateDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
	{CSttDeviceComm::ProStateDrvResult(bTestFinished,oTestFinishedTime);}

	//soe
	virtual void tmt_to_drv_soe(tmt_SoeTest *pTmt)
	{CSttDeviceComm::tmt_to_drv_soe(pTmt);}
	virtual void ProSoeDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
	{CSttDeviceComm::ProSoeDrvResult(bTestFinished,oTestFinishedTime);}

	//cboper
	virtual void tmt_to_drv_CboperPara(tmt_ImpBaseParas *pTmt)
	{CSttDeviceComm::tmt_to_drv_CboperPara(pTmt);}
	//abnormal
	virtual void tmt_to_drv_AbnPara(tmt_StateParas *pTmt,long nAbnType)
	{CSttDeviceComm::tmt_to_drv_AbnPara(pTmt,nAbnType);}

	virtual void FormatFlashData(PSTT_MODULE pModule,BYTE *pszBuf,long &nLen)
	{CSttDeviceComm::FormatFlashData(pModule,pszBuf,nLen);}

	virtual int SetModuleFlash(PSTT_MODULE pModule,BYTE *pszBuf,int nLen)
	{CSttDeviceComm::SetModuleFlash(pModule,pszBuf,nLen);}

	virtual BOOL GetModuleFlash(PSTT_MODULE pModule,BYTE *pszBuf,int &nOffset)
	{return CSttDeviceComm::GetModuleFlash(pModule,pszBuf,nOffset);}

	virtual void GetPI1000ModulesFPGAInfo()
	{CSttDeviceComm::GetModulesFPGAInfo();}

    virtual void AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,int nModuleType);

	virtual void tmt_to_drv_SwingTestPara(tmt_SwingParas *pTmt,int nStepCnt,char *pszDrv)
	{CSttDeviceComm::tmt_to_drv_SwingTestPara(pTmt,nStepCnt,pszDrv);}
	virtual void tmt_to_drv_SwingAcPara(tmt_StepUI *pTmt,char *pszDrv,int nStep,int nType)
	{CSttDeviceComm::tmt_to_drv_SwingAcPara(pTmt,pszDrv,nStep,nType);}
    virtual void SetSwingPara(char *pszDrv){CSttDeviceComm::SetSwingPara(pszDrv);}
	virtual void ProSwingDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
	{CSttDeviceComm::ProSwingDrvResult(bTestFinished,oTestFinishedTime);}

	virtual void tmt_to_drv_SynPara(tmt_SynParasEx *pTmt){CSttDeviceComm::tmt_to_drv_SynPara(pTmt);}
	virtual void ProSynDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
	{CSttDeviceComm::ProSynDrvResult(bTestFinished,oTestFinishedTime);}
	//IEC61850
public:
	virtual void* GetIecCfgDatasMngr(){return CSttDeviceComm::GetIecCfgDatasMngr();}
	virtual void SetIEC61850Para(){CSttDeviceComm::SetIEC61850Para();}
	virtual void InitGooseSub(){CSttDeviceComm::InitGooseSub();}
	//Replay
public:
    virtual void tmt_to_drv_LtReplay(tmt_ReplayParas *pTmt,char *pszReplayCoef)
    {CSttDeviceComm::tmt_to_drv_LtReplay(pTmt,pszReplayCoef);}
    virtual BOOL getLtReplayBufferAFlag(){return CSttDeviceComm::getLtReplayBufferAFlag();}
    virtual BOOL getLtReplayBufferBFlag(){return CSttDeviceComm::getLtReplayBufferBFlag();}
    virtual void setLtReplayBufferABLoop(unsigned int size, char *pszDrv, unsigned int ntype)
    {CSttDeviceComm::setLtReplayBufferABLoop(size, pszDrv, ntype);}

	//Gradient
public:
	virtual void tmt_to_drv_Gradient(tmt_GradientTest *pTmt)
	{m_bCurTestIsGradient=TRUE;CSttDeviceComm::tmt_to_drv_Gradient(pTmt);}
	virtual void tmt_to_drv_Gradient_NeedStepsValue(tmt_GradientTest *pTmt)
	{m_bCurTestIsGradient=TRUE;CSttDeviceComm::tmt_to_drv_Gradient_NeedStepsValue(pTmt);}

public:
	virtual void GetVoltCurRtData();
    virtual void GetRtData(){}
};

void *ProStableDataThread(LPVOID pParam);
extern CRingMemBuf *g_pRecvStable2MBuf;

#endif // CSTTDEVICEPST200_H
