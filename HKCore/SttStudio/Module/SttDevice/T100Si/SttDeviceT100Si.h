#include "../Module/Driver466/SttDeviceComm.h"
#include "stdafx.h"

typedef struct{
	unsigned int init_time[8]; //初始时间
	unsigned int firstfliptime[8]; // 第一次翻转时间
	unsigned int secondfliptime[8]; // 第二次翻转时间
	unsigned int flipcnt[8]; //翻转次数
	unsigned int init_val[8]; //初始值
}Drv_SoeState;

typedef struct{
	unsigned int triptype; //0: 立即触发 1: GPS 触发
	unsigned int sec;           //GPS s
	unsigned int nsec;          //GPS ns
	unsigned int holdtime;      //持续时间毫秒值
	Drv_SoeState soe;
}Drv_SOETest;

class CSttDeviceT100Si : public CSttDeviceComm,public CSttDeviceBase
{
private:
	explicit CSttDeviceT100Si();
	~CSttDeviceT100Si();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();
	static CSttDeviceT100Si *g_pSttDeviceT100Si;

	virtual int InitDevice(BOOL bHasAdjFile);
	virtual void GetBoardInfo(BOOL bHasAdjFile);
	void Manual_volt_current(tmt_channel *pTmt_channel,char *pszDrv,int nHarm,
									 BOOL bIsDc,BOOL bIsModuleOutput=FALSE);
	void TransAnalogDCToDrv(float fAmp,int nChannel,long *pDrvData);
	long TranslateACAmp(float fAmp,int nChannel,int nHarm);
	void TransAnalogToDrv(float fAmp,float fAng,float fFre,int nChannel,long *pnDrvData);

public:
	virtual void SetSystemConfig(){CSttDeviceComm::SetSystemConfig();}

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
	virtual void tmt_to_drv_manu(tmt_ManualTest *pTmt,BOOL bIsStartTest=FALSE);
	virtual void ProCommDrvResult(){CSttDeviceComm::ProCommDrvResult();}

	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
	{CSttDeviceComm::tmt_to_drv_moduleoutput(pTmt);}

	virtual void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt)
	{CSttDeviceComm::tmt_to_drv_systemdefaultoutput(pTmt);}

	virtual void tmt_to_drv_harm(tmt_HarmTest *pTmt,BOOL bIsStartTest=FALSE)
	{CSttDeviceComm::tmt_to_drv_harm(pTmt,bIsStartTest);}

	virtual void SetStateTriger(){CSttDeviceComm::SetStateTriger();}
	virtual void tmt_to_drv_StatePara(tmt_StateTest *pTmt){CSttDeviceComm::tmt_to_drv_StatePara(pTmt);}
	virtual void tmt_to_drv_StateItem(tmt_StateTest *pTmt){CSttDeviceComm::tmt_to_drv_StateItem(pTmt);}
	virtual void ProStateDrvResult(tmt_StateTest *pTmt){CSttDeviceComm::ProStateDrvResult(pTmt);}
	virtual void tmt_to_drv_Gradient(tmt_GradientTest *pTmt){m_bCurTestIsGradient=TRUE;CSttDeviceComm::tmt_to_drv_Gradient(pTmt);}

	virtual void FormatFlashData(PSTT_MODULE pModule,BYTE *pszBuf,long &nLen)
	{CSttDeviceComm::FormatFlashData(pModule,pszBuf,nLen);}

	virtual int SetModuleFlash(PSTT_MODULE pModule,BYTE *pszBuf,int nLen)
	{CSttDeviceComm::SetModuleFlash(pModule,pszBuf,nLen);}

	virtual BOOL GetModuleFlash(PSTT_MODULE pModule,BYTE *pszBuf,int &nOffset)
	{return CSttDeviceComm::GetModuleFlash(pModule,pszBuf,nOffset);}

	virtual void AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,BOOL IsVolt=FALSE);

	//IEC61850
public:
	virtual void* GetIecCfgDatasMngr(){return CSttDeviceComm::GetIecCfgDatasMngr();}
	virtual void SetIEC61850Para(){CSttDeviceComm::SetIEC61850Para();}
	virtual void InitGooseSub(){CSttDeviceComm::InitGooseSub();}
	//Replay
public:
	virtual void tmt_to_drv_replay(tmt_ReplayTest *pTmt,char *pszLtReplayParam,char *pszLtReplayCoef)
	{CSttDeviceComm::tmt_to_drv_replay(pTmt,pszLtReplayParam,pszLtReplayCoef);}
	virtual int GetReplayIrp(){return CSttDeviceComm::GetReplayIrp();}
	virtual BOOL getLtReplayBufferAFlag(){return CSttDeviceComm::getLtReplayBufferAFlag();}
	virtual BOOL getLtReplayBufferBFlag(){return CSttDeviceComm::getLtReplayBufferBFlag();}
	virtual void setLtReplayBufferAFlag(){CSttDeviceComm::setLtReplayBufferAFlag();}
	virtual void setLtReplayBufferBFlag(){CSttDeviceComm::setLtReplayBufferBFlag();}
	virtual void setLtReplayBufferLoopFlag(){CSttDeviceComm::setLtReplayBufferLoopFlag();}
	virtual void* getMmapBuffer(){return g_start;}
	virtual void ClearReplayBufferBFlag(){CSttDeviceComm::ClearReplayBufferBFlag();}

};
