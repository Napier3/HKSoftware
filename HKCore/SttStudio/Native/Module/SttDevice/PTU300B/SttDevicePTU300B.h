#ifndef CSTTDEVICEPTU300B_H
#define CSTTDEVICEPTU300B_H

#include "stdafx.h"
#include "../Module/DriverPTU/SttDeviceComm.h"

class CSttDevicePTU300B : public CSttDeviceComm,public CSttDeviceBase
{
private:
	explicit CSttDevicePTU300B();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();

	static CSttDevicePTU300B *g_pSttDevicePTU300B;

	virtual int InitDevice();	
	virtual BOOL CheckHarmTestPara(tmt_HarmTest *pTmt);
	virtual void tmt_to_drv_manu(tmt_ManualTest *pTmt);
	virtual void tmt_to_drv_harm(tmt_HarmTest *pTmt);
	virtual void tmt_to_drv_StatePara(tmt_StateTest *pTmt);

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

#endif // CSTTDEVICEPTU300B_H
