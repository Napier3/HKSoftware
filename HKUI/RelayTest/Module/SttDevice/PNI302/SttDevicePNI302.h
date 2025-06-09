#ifndef CSTTDEVICEPNI302_H
#define CSTTDEVICEPNI302_H

#include "stdafx.h"
#include "../Module/Driver466/SttDeviceComm.h"

typedef struct{
	unsigned int nModule;
	bool bIsVaild;
	double fChgTime[64];	//绝对时间
	double fBackTime[64];	//绝对时间
}STT_SoeItem;

typedef struct{
	STT_SoeItem item[5];
}STT_SoeResult;

class CSttDevicePNI302 : public CSttDeviceComm,public CSttDeviceBase
{
private:
	CSttDevicePNI302();
	static long g_nSttDevicePNI302Ref;

public:
	static void Create();
	static void Release();

	static CSttDevicePNI302 *g_pSttDevicePNI302;

	virtual int InitDevice(BOOL bHasAdjFile);

	//Step6U6I
	virtual void SetStep6U6IStart();
	virtual void SetStep6U6IStop();

	//MUTest
	virtual void SetRising(int nRising);
	virtual int GetPPS();

	//iecdetect
	virtual void SetIecdetectStart(tmt_RecordTest *pTmt);
	virtual void SetIecdetectStop(tmt_RecordTest *pTmt);
	virtual void ProIecdetectDrvResult();

	//iedtest
	virtual void SetIEDTestStart_B2G();
	virtual void SetIEDTestStop_B2G();
	virtual void tmt_to_drv_iedtest_B2G(tmt_IEDTest *pTmt);
	virtual void ProIEDTestDrvResult_B2G(tmt_IEDTest *pTmt,tmt_IEDPara *pPrePara);
	virtual void SetIEDTestStart_G2B();
	virtual void SetIEDTestStop_G2B();
	virtual void tmt_to_drv_iedtest_G2B(tmt_IEDTest *pTmt);
	virtual void ProIEDTestDrvResult_G2B(tmt_IEDTest *pTmt,tmt_IEDPara *pPrePara);

public:
	virtual void SetTestStart(int nTestType){CSttDeviceComm::SetTestStart(nTestType);}
	virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE){CSttDeviceComm::SetTestStop(bIsSysDefaultOutput);}
	virtual void SetTestPara(int nTestType,char *pszBuff){CSttDeviceComm::SetTestPara(nTestType,pszBuff);}

	virtual void SetSystemConfig();

	//IEC61850
	virtual void* GetIecCfgDatasMngr()	{return CSttDeviceComm::GetIecCfgDatasMngr();}
	virtual void SetIEC61850Para(){CSttDeviceComm::SetIEC61850Para();}
	virtual void InitGooseSub(){CSttDeviceComm::InitGooseSub();}
	virtual void SetGooseSub(char* pszBuff){CSttDeviceComm::SetGooseSub(pszBuff);}

	//Step6U6I
	virtual void tmt_to_drv_harm(tmt_HarmTest *pTmt){CSttDeviceComm::tmt_to_drv_harm(pTmt);}
	virtual void ProRecordDrvResult(){CSttDeviceComm::ProRecordDrvResult();}

	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
	{CSttDeviceComm::tmt_to_drv_moduleoutput(pTmt);}
private:
	void GetChgNum(CString strPreBiVal,CString strCurrBiVal,bool *bChgChan);

	//IED
	CString m_strPreBiVal;//64bit
	CString m_strCurrBiVal;//64bit
	bool m_bChgChan[64];
	STT_SoeResult m_oSTTSoeResult;
};

#endif // CSTTDEVICEPNI302_H
