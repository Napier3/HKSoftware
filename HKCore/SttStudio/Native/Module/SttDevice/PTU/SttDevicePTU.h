#ifndef CSTTDEVICEPTU_H
#define CSTTDEVICEPTU_H

#include "stdafx.h"
#include "../Module/DriverPTU/SttDeviceComm.h"

class CSttDevicePTU : public CSttDeviceComm,public CSttDeviceBase
{
private:
	explicit CSttDevicePTU();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();

	static CSttDevicePTU *g_pSttDevicePTU;

	virtual int InitDevice(BOOL bHasAdjFile);
	virtual void tmt_to_drv_manu(tmt_ManualTest *pTmt){CSttDeviceComm::tmt_to_drv_manu(pTmt);}
	virtual void tmt_to_drv_harm(tmt_HarmTest *pTmt){CSttDeviceComm::tmt_to_drv_harm(pTmt);}
	virtual void tmt_to_drv_StatePara(tmt_StateTest *pTmt){CSttDeviceComm::tmt_to_drv_StatePara(pTmt);}

public:	
	virtual void SetBISetting(){CSttDeviceComm::SetBISetting();}
	virtual void SetManualBI(char* pszBuff,int nLen){CSttDeviceComm::SetManualBI(pszBuff,nLen);}

	virtual void SetSystemConfig(){CSttDeviceComm::SetSystemConfig();}

	virtual void SetStateTriger(){CSttDeviceComm::SetStateTriger();}

	/******基础功能，无硬件切档******/
	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
	{CSttDeviceComm::tmt_to_drv_moduleoutput(pTmt);}
	virtual void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt)
	{CSttDeviceComm::tmt_to_drv_systemdefaultoutput(pTmt);}
	virtual void ProManuDrvResult(){CSttDeviceComm::ProManuDrvResult();}
	virtual void ProStateDrvResult(){CSttDeviceComm::ProStateDrvResult();}
	virtual void SetTestStart(int nTestType){CSttDeviceComm::SetTestStart(nTestType);}
	virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE){CSttDeviceComm::SetTestStop(bIsSysDefaultOutput);}
	/******基础功能，无硬件切档******/
};

#endif // CSTTDEVICEPTU_H
