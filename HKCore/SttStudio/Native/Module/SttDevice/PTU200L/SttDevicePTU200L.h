#ifndef CSTTDEVICEPTU200L_H
#define CSTTDEVICEPTU200L_H

#include "../Module/Driver466/SttDeviceComm.h"
#include "stdafx.h"

class CSttDevicePTU200L : public CSttDeviceComm,public CSttDeviceBase
{
private:
	explicit CSttDevicePTU200L();
	~CSttDevicePTU200L();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();
	static CSttDevicePTU200L *g_pSttDevicePTU200L;

	virtual int InitDevice(BOOL bHasAdjFile);
	virtual void InitModulePowerCtrl();
	virtual void ProSoeDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
	{CSttDeviceComm::ProSoeDrvResult(bTestFinished,oTestFinishedTime);}
	virtual void tmt_to_drv_soe(tmt_SoeTest *pTmt)
	{
		pTmt->m_oSoeParas.m_nSelect = 0;//只有主板SOE
		pTmt->m_oSoeParas.m_nBiAct = 0;//无需开入结果
		CSttDeviceComm::tmt_to_drv_soe(pTmt);
	}
	virtual void SetPtValue(unsigned int nValue);
	virtual void AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack, int nModulePos, int nModuleType);

public:
	virtual void DAValueCalc_Comm(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt,
								  BOOL bDC, int nDirection, int nGradientHarm, float fGradientAmp, float fUdc);
	virtual void DAValueCalc_Manu_UpdateParameter(BOOL bDC);
	virtual void ProStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_StatePara  &oTmt_FirstState);
	virtual void SetSystemConfig()
	{
		CSttDeviceComm::SetSystemConfig();
	}
	virtual void SetTestStart(int nTestType)
	{
		CSttDeviceComm::SetTestStart(nTestType);
	}
	virtual void SetTestStop(BOOL bIsSysDefaultOutput = FALSE)
	{
		CSttDeviceComm::SetTestStop(bIsSysDefaultOutput);
	}
	virtual void SetTestPara(int nTestType, char *pszBuff)
	{
		CSttDeviceComm::SetTestPara(nTestType, pszBuff);
	}
	virtual void SetManualBI(char *pszBuff, int nLen)
	{
		CSttDeviceComm::SetManualBI(pszBuff, nLen);
	}
	virtual void SetBISetting()
	{
		CSttDeviceComm::SetBISetting();
	}

	virtual void SetGooseSub(char *pszBuff)
	{
		CSttDeviceComm::SetGooseSub(pszBuff);
	}
	virtual void SetFT3SubMap(char *pszBuff)
	{
		CSttDeviceComm::SetFT3SubMap(pszBuff);
	}
	virtual void SetBoMap(char *pszBuff)
	{
		CSttDeviceComm::SetBoMap(pszBuff);
	}
	virtual void SetBinaryOutTurnOnVaule(int nValue)
	{
		CSttDeviceComm::SetBinaryOutTurnOnVaule(nValue);
	}
	virtual void SetBinaryOut(BOOL bOpen = FALSE)
	{
		CSttDeviceComm::SetBinaryOut(bOpen);
	}

	virtual void InitWeekOutputDAData()
	{
		CSttDeviceComm::InitWeekOutputDAData();
	}
	virtual void InitDrvResult()
	{
		CSttDeviceComm::InitDrvResult();
	}
	virtual void ProCommDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
	{
		CSttDeviceComm::ProCommDrvResult(bTestFinished, oTestFinishedTime);
	}
	virtual void tmt_to_drv_manu(tmt_ManualTest *pTmt, BOOL bIsStartTest = FALSE)
	{
		m_bCurTestIsGradient = FALSE;
		CSttDeviceComm::tmt_to_drv_manu(pTmt, bIsStartTest);
	}

	virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
	{
		CSttDeviceComm::tmt_to_drv_moduleoutput(pTmt);
	}

	virtual void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt)
	{
		CSttDeviceComm::tmt_to_drv_systemdefaultoutput(pTmt);
	}

	virtual void tmt_to_drv_harm(tmt_HarmTest *pTmt, BOOL bIsStartTest = FALSE)
	{
		m_bCurTestIsGradient = FALSE;
		CSttDeviceComm::tmt_to_drv_harm(pTmt, bIsStartTest);
	}

	virtual void SetStateTriger()
	{
		CSttDeviceComm::SetStateTriger();
	}
	virtual void tmt_to_drv_StatePara(tmt_StateParas *pTmt)
	{
		CSttDeviceComm::tmt_to_drv_StatePara(pTmt);
	}
	virtual void tmt_to_drv_StateItem(tmt_StateParas *pTmt)
	{
		CSttDeviceComm::tmt_to_drv_StateItem(pTmt);
	}
	virtual void ProStateDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
	{
		CSttDeviceComm::ProStateDrvResult(bTestFinished, oTestFinishedTime);
	}
	//binarytest
	virtual void tmt_to_drv_BinaryManu(tmt_ManualTest *pTmt, BOOL bIsStartTest = FALSE)
	{
		CSttDeviceComm::tmt_to_drv_BinaryManu(pTmt,bIsStartTest);
	}
	virtual void tmt_to_drv_BinaryStateItem(tmt_StateParas *pTmt)
	{
		CSttDeviceComm::tmt_to_drv_BinaryStateItem(pTmt);
	}
	//IEC61850
public:
	virtual void *GetIecCfgDatasMngr()
	{
		return CSttDeviceComm::GetIecCfgDatasMngr();
	}
	virtual void SetIEC61850Para()
	{
		CSttDeviceComm::SetIEC61850Para();
	}
	//Replay
public:
	virtual void tmt_to_drv_LtReplay(tmt_ReplayParas *pTmt, char *pszReplayCoef)
	{
		CSttDeviceComm::tmt_to_drv_LtReplay(pTmt, pszReplayCoef);
	}
	virtual BOOL getLtReplayBufferAFlag()
	{
		return CSttDeviceComm::getLtReplayBufferAFlag();
	}
	virtual BOOL getLtReplayBufferBFlag()
	{
		return CSttDeviceComm::getLtReplayBufferBFlag();
	}
	virtual void setLtReplayBufferABLoop(unsigned int size, char *pszDrv, unsigned int ntype)
	{
		CSttDeviceComm::setLtReplayBufferABLoop(size, pszDrv, ntype);
	}

	//Gradient
public:
	virtual void tmt_to_drv_Gradient(tmt_GradientParas *pParas)
	{
		m_bCurTestIsGradient = TRUE;
		CSttDeviceComm::tmt_to_drv_Gradient(pParas);
	}
	virtual void tmt_to_drv_Gradient_NeedStepsValue(tmt_GradientParas *pParas)
	{
		m_bCurTestIsGradient = TRUE;
		CSttDeviceComm::tmt_to_drv_Gradient_NeedStepsValue(pParas);
	}

public:
	virtual void GetVoltCurRtData();
};

#endif // CSTTDEVICEPTU200L_H
