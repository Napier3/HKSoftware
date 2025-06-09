#ifndef CSTTDEVICEAT02D_H
#define CSTTDEVICEAT02D_H

#include "stdafx.h"
#include "../Module/Driver466/SttDeviceComm.h"


class CSttDeviceAT02D : public CSttDeviceComm, public CSttDeviceBase
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
		virtual BOOL OnTimer(BOOL bExec = FALSE);

		virtual void SetTestStart(int nTestType){CSttDeviceComm::SetTestStart(nTestType);}
		virtual void SetTestStop(BOOL bIsSysDefaultOutput=FALSE){CSttDeviceComm::SetTestStop(bIsSysDefaultOutput);}
		virtual void SetTestPara(int nTestType,char *pszBuff){CSttDeviceComm::SetTestPara(nTestType,pszBuff);}

		virtual void tmt_to_drv_manu(tmt_ManualTest *pTmt, BOOL bIsStartTest = FALSE)
		{
			m_bCurTestIsGradient = FALSE;
			CSttDeviceComm::tmt_to_drv_manu(pTmt, bIsStartTest);
		}
		virtual void tmt_to_drv_StatePara(tmt_StateParas *pTmt)
		{
			CSttDeviceComm::tmt_to_drv_StatePara(pTmt);
		}
		virtual void tmt_to_drv_StateItem(tmt_StateParas *pTmt)
		{
			CSttDeviceComm::tmt_to_drv_StateItem(pTmt);
		}
		//IEC61850
		virtual void SetIEC61850Para(){CSttDeviceComm::SetIEC61850Para();}
		virtual void *GetIec61850CfgMngr()
		{
			return CSttDeviceComm::GetIec61850CfgMngr();
		}
		virtual void SetGooseSub(char* pszBuff){CSttDeviceComm::SetGooseSub(pszBuff);}
		virtual void SetBoMap(char *pszBuff){CSttDeviceComm::SetBoMap(pszBuff);}
		virtual void SetFT3SubCRC(char *pszBuff){CSttDeviceComm::SetFT3SubCRC(pszBuff);}

		virtual void InitDrvResult(){CSttDeviceComm::InitDrvResult();}
		virtual void ProStateDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
		{CSttDeviceComm::ProStateDrvResult(bTestFinished,oTestFinishedTime);}
		virtual void ProCommDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
		{CSttDeviceComm::ProCommDrvResult(bTestFinished,oTestFinishedTime);}
};

#endif // CSTTDEVICEAT02D_H
