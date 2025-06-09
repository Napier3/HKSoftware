#ifndef CSTTDEVICEAT02D_H
#define CSTTDEVICEAT02D_H

#include "stdafx.h"
#include "../Module/Driver466/SttDeviceComm.h"


class CSttDeviceAT02D : public CSttDeviceComm,public CSttDeviceBase
{
private:
		explicit CSttDeviceAT02D();
		static long g_nSttDeviceRef;

public:
		static void Create();
        static void Release();
		static CSttDeviceAT02D *g_pSttDeviceAT02D;
        float m_nDelayTime[MAX_DIGITAL_GROUP_NUM];

public:
		virtual int InitDevice(BOOL bHasAdjFile);

		virtual void SetTestStart(int nTestType){CSttDeviceComm::SetTestStart(nTestType);}
		virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE){CSttDeviceComm::SetTestStop(bIsSysDefaultOutput);}
		virtual void SetTestPara(int nTestType,char *pszBuff){CSttDeviceComm::SetTestPara(nTestType,pszBuff);}

		//IEC61850
		virtual void SetIEC61850Para(){CSttDeviceComm::SetIEC61850Para();}
		virtual void InitGooseSub(){CSttDeviceComm::InitGooseSub();}
		virtual void* GetIecCfgDatasMngr()	{return CSttDeviceComm::GetIecCfgDatasMngr();}
		virtual void SetGooseSub(char* pszBuff){CSttDeviceComm::SetGooseSub(pszBuff);}

		virtual void InitDrvResult(){CSttDeviceComm::InitDrvResult();}
		virtual void tmt_to_drv_record(tmt_RecordTest *pTmt){CSttDeviceComm::tmt_to_drv_record(pTmt);}
		virtual void SetRecordStart(){CSttDeviceComm::SetRecordStart();}
		virtual void SetRecordStop(){CSttDeviceComm::SetRecordStop();}
		virtual void ProRecordDrvResult(){CSttDeviceComm::ProRecordDrvResult();}
		virtual void ProStateDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
		{CSttDeviceComm::ProStateDrvResult(bTestFinished,oTestFinishedTime);}
		virtual void ProCommDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
		{CSttDeviceComm::ProCommDrvResult(bTestFinished,oTestFinishedTime);}

		virtual void SetStep6U6IStart();
		virtual void SetStep6U6IStop();
};

#endif // CSTTDEVICEAT02D_H
