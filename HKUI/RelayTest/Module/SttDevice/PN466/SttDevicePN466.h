#ifndef CSTTDEVICEPN466_H
#define CSTTDEVICEPN466_H

#include "../Module/Driver466/SttDeviceComm.h"
#include "stdafx.h"

class CSttDevicePN466 : public CSttDeviceComm, public CSttDeviceBase
{
private:
	explicit CSttDevicePN466();
	~CSttDevicePN466();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();
	static CSttDevicePN466 *g_pSttDevicePN466;

	virtual void GetModuleInfo(Drv_SysInfo *pSysInfo);
	virtual int InitDevice(BOOL bHasAdjFile);
	virtual void SetSystemLocalTime(CString strTime_t);
	virtual BOOL GetBinaryVolt()
	{
		if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinVoltMeas)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	virtual BOOL OnTimer(BOOL bExec = FALSE);

public:
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
	virtual void SetFT3SubCRC(char *pszBuff)
	{
		CSttDeviceComm::SetFT3SubCRC(pszBuff);
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
	virtual void tmt_to_drv_AsyncManu(tmt_AsyncManualTest *pTmt, BOOL bIsStartTest = FALSE)
	{
		m_bCurTestIsGradient = FALSE;
		CSttDeviceComm::tmt_to_drv_AsyncManu(pTmt, bIsStartTest);
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

	//state
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
	virtual void tmt_to_drv_AsyncStatePara(tmt_AsyncStateParas *pTmt)
	{
		CSttDeviceComm::tmt_to_drv_AsyncStatePara(pTmt);
	}
	virtual void tmt_to_drv_AsyncStateItem(tmt_AsyncStateParas *pTmt)
	{
		CSttDeviceComm::tmt_to_drv_AsyncStateItem(pTmt);
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

	//cboper
	virtual void tmt_to_drv_CboperPara(tmt_ImpBaseParas *pTmt)
	{
		CSttDeviceComm::tmt_to_drv_CboperPara(pTmt);
	}
	//abnormal
	virtual void tmt_to_drv_AbnPara(tmt_StateParas *pTmt, long nAbnType)
	{
		CSttDeviceComm::tmt_to_drv_AbnPara(pTmt, nAbnType);
	}
	//soe
	virtual void tmt_to_drv_soe(tmt_SoeTest *pTmt)
	{
		CSttDeviceComm::tmt_to_drv_soe(pTmt);
	}
	virtual void ProSoeDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
	{
		CSttDeviceComm::ProSoeDrvResult(bTestFinished, oTestFinishedTime);
	}

	virtual void FormatFlashData(PSTT_MODULE pModule, BYTE *pszBuf, long &nLen)
	{
		CSttDeviceComm::FormatFlashData(pModule, pszBuf, nLen);
	}

	virtual int SetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int nLen)
	{
		return CSttDeviceComm::SetModuleFlash(pModule, pszBuf, nLen);
	}

	virtual BOOL GetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int &nOffset)
	{
		return CSttDeviceComm::GetModuleFlash(pModule, pszBuf, nOffset);
	}

	virtual void tmt_to_drv_SwingTestPara(tmt_SwingParas *pTmt, int nStepCnt, char *pszDrv)
	{
		CSttDeviceComm::tmt_to_drv_SwingTestPara(pTmt, nStepCnt, pszDrv);
	}
	virtual void tmt_to_drv_SwingAcPara(tmt_StepUI *pTmt, char *pszDrv, int nStep, int nType)
	{
		CSttDeviceComm::tmt_to_drv_SwingAcPara(pTmt, pszDrv, nStep, nType);
	}
	virtual void SetSwingPara(char *pszDrv)
	{
		CSttDeviceComm::SetSwingPara(pszDrv);
	}
	virtual void ProSwingDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
	{
		CSttDeviceComm::ProSwingDrvResult(bTestFinished, oTestFinishedTime);
	}

	virtual void tmt_to_drv_SynPara(tmt_SynParas *pTmt)
	{
		CSttDeviceComm::tmt_to_drv_SynPara(pTmt);
	}
	virtual void ProSynDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
	{
		CSttDeviceComm::ProSynDrvResult(bTestFinished, oTestFinishedTime);
	}

	virtual void SetAuxDcVolt(float fUdc)
	{
		CSttDeviceComm::SetAuxDcVolt(fUdc);
	}
	//IEC61850
public:
	virtual void *GetIec61850CfgMngr()
	{
		return CSttDeviceComm::GetIec61850CfgMngr();
	}
	virtual void SetIEC61850Para()
	{
		CSttDeviceComm::SetIEC61850Para();
	}
//	virtual void InitGooseSub()
//	{
//		CSttDeviceComm::InitGooseSub();
//	}
	//Replay
public:
	virtual void tmt_to_drv_LtReplay(tmt_ReplayParas *pTmt, char *pszReplayCoef)
	{
		CSttDeviceComm::tmt_to_drv_LtReplay(pTmt, pszReplayCoef);
	}
	virtual int getLtReplayBufferFlag()
	{
		return CSttDeviceComm::getLtReplayBufferFlag();
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

	//MUTest
public:
	virtual void tmt_to_drv_MUTest(tmt_ManualTest *pTmt, BOOL bIsStartTest = FALSE)
	{
		m_bCurTestIsGradient = FALSE;
		CSttDeviceComm::tmt_to_drv_MUTest(pTmt, bIsStartTest);
	}
	virtual void tmt_to_drv_MUHarmTest(tmt_HarmTest *pTmt, BOOL bIsStartTest = FALSE)
	{
		m_bCurTestIsGradient = FALSE;
		CSttDeviceComm::tmt_to_drv_MUHarmTest(pTmt, bIsStartTest);
	}
	virtual void SetRising(int nRising)
	{
		CSttDeviceComm::SetRising(nRising);
	}
	virtual void SetPPSTestStart()
	{
		CSttDeviceComm::SetPPSTestStart();
	}
	virtual void SetPPSTestStop()
	{
		CSttDeviceComm::SetPPSTestStop();
	}
	virtual void SetADMUChannel(tmt_ManualTest *pTmt)
	{
		CSttDeviceComm::SetADMUChannel(pTmt);
	}
	virtual void SetADMUChannel(tmt_HarmTest *pTmt)
	{
		CSttDeviceComm::SetADMUChannel(pTmt);
	}
public:
	virtual void GetVoltCurRtData();
	virtual void PreStartTestPro();
	virtual BOOL SetOutputTime(tmt_channel *pChannel, BOOL bDc, float &fOutPutTime);
	virtual void ProStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_StatePara  &oTmt_FirstState);
	virtual void ProAsyncStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_AsyncStatePara  &oTmt_FirstState);
	virtual void DAValueCalc_Comm(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt,
								  BOOL bDC, int nDirection, int nGradientHarm, float fGradientAmp, float fUdc);
	virtual void DAValueCalc_Manu_UpdateParameter(BOOL bDC);
	virtual void DAValueCalc_AsyncManu_UpdateParameter();
	//PN机箱位置4的3U3I模块电源非标处理
	void DAValue_PN_3U3I(tmt_channel *pVolt, tmt_channel *pCurrent, DeviceDAPara *pDAPara, int nHarmCnt, BOOL bDC,
						 int nDirection, int nGradientHarm, float fGradientAmp, float fUdc);
	void GetBinAndDC();
};

#endif // CSTTDEVICEPN466_H
