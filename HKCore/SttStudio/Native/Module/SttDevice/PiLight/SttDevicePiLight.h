#ifndef CSTTDEVICEPILIGHT_H
#define CSTTDEVICEPILIGHT_H

#include "../Module/Driver466/SttDeviceComm.h"
#include "stdafx.h"

typedef struct{
	unsigned int nModule;
	long dat[564];	//模拟正弦参数 6+6*3*31 = 564
	DrvBITrip oTrip; //触发
	DrvComBoStatus  oBoStatus;
	unsigned int nBinStop;//1-开入停止 0-无效
	unsigned int nBiCtrl;//1-8开入量映射光源
}Drv_CurrentData;

class CSttDevicePiLight : public CSttDeviceComm,public CSttDeviceBase
{
private:
	explicit CSttDevicePiLight();
	~CSttDevicePiLight();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();
	static CSttDevicePiLight *g_pSttDevicePiLight;

	virtual int InitDevice(BOOL bHasAdjFile);

public:
	virtual void SetTestStart(int nTestType){CSttDeviceComm::SetTestStart(nTestType);}
	virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE);

	virtual void SetBinaryOutTurnOnVaule(int nValue){CSttDeviceComm::SetBinaryOutTurnOnVaule(nValue);}
	virtual void SetBinaryOut(BOOL bOpen=FALSE){CSttDeviceComm::SetBinaryOut(bOpen);}

	virtual void InitDrvResult(){CSttDeviceComm::InitDrvResult();}

	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
	{CSttDeviceComm::tmt_to_drv_moduleoutput(pTmt);}

	virtual void FormatFlashData(PSTT_MODULE pModule,BYTE *pszBuf,long &nLen)
	{CSttDeviceComm::FormatFlashData(pModule,pszBuf,nLen);}

	virtual int SetModuleFlash(PSTT_MODULE pModule,BYTE *pszBuf,int nLen)
	{CSttDeviceComm::SetModuleFlash(pModule,pszBuf,nLen);}

	virtual BOOL GetModuleFlash(PSTT_MODULE pModule,BYTE *pszBuf,int &nOffset)
	{return CSttDeviceComm::GetModuleFlash(pModule,pszBuf,nOffset);}

	virtual void GetPI1000ModulesFPGAInfo()
	{CSttDeviceComm::GetModulesFPGAInfo();}

    virtual void AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,int nModuleType);

	//Light 弧光
	virtual void ProLightDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime);
	virtual void tmt_to_drv_lightpara(void *pTmt);
	virtual void tmt_to_drv_lightangle(void *pTmt,unsigned int nType);

	void Light_current(tmt_channel *pTmt_channel,long *dat,float fAngleDiff);
};

#endif // CSTTDEVICEPILIGHT_H
