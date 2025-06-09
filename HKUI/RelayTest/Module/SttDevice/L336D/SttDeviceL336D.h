#ifndef CSTTDEVICEL336D_H
#define CSTTDEVICEL336D_H

#include "../Module/Driver466/SttDeviceComm.h"
#include "stdafx.h"

typedef struct
{
	BOOL bHasBat;
	float fV1;
	float fV2;
	float fI1;
	float fI2;
	float fT1;
	float fT2;
}BattaryInfo;

typedef struct
{
	float fVolt;//电池电压
	float fCurr;//电池电流
}BatInfo;

class CSttDeviceL336D : public CSttDeviceComm, public CSttDeviceBase
{
public:
	CSttDeviceL336D();
	virtual ~CSttDeviceL336D();
private:
    static long g_nSttDeviceRef;

public:
    static void Create();
    static void Release();
    static CSttDeviceL336D *g_pSttDeviceL336D;

    virtual int InitDevice(BOOL bHasAdjFile);
	virtual BOOL GetDevInputInfo(){return CSttDeviceComm::GetDevInputInfo();}

public:
    virtual void DAValueCalc_Comm(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt,
                                  BOOL bDC, int nDirection, int nGradientHarm, float fGradientAmp, float fUdc);
    virtual void DAValueCalc_Manu_UpdateParameter(BOOL bDC);
    virtual void ProStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_StatePara  &oTmt_FirstState);
    virtual void SetSystemConfig()
    {
        CSttDeviceComm::SetSystemConfig();
    }
    virtual long TransAuxDcVolt(float fUdc);
    virtual void SetAuxDcVolt(float fUdc);
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

    virtual void tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
    {
        CSttDeviceComm::tmt_to_drv_moduleoutput(pTmt);
    }
	virtual BOOL CheckCurrLoadIsSafe(tmt_channel *pChannel, BOOL bIsDc);
	virtual BOOL CheckCurrLoadIsSafe_moduleoutput(tmt_channel *pChannel, BOOL bIsDc, PSTT_MODULE pModule);

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
	virtual void *GetIec61850CfgMngr()
	{
		return CSttDeviceComm::GetIec61850CfgMngr();
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
public:
	virtual void GetModuleInfo(Drv_SysInfo *pSysInfo);
	virtual void Stt_Xml_Serialize_Channels(CSttXmlSerializeBase *pXmlSerialize);
	virtual BOOL OnTimer(BOOL bExec = FALSE);
    virtual void GetVoltCurRtData();
	virtual void PreStartTestPro();
    virtual void SetPeripheral();
	virtual BOOL SetOutputTime(tmt_channel *pChannel, BOOL bDc, float &fOutPutTime);
	virtual void FormatFlashData(PSTT_MODULE pModule, BYTE *pszBuf, long &nLen)
	{
		if(pModule->m_oModuleAttr.m_nModuleIndex != 4)
		{
			return;
		}
		CSttDeviceComm::FormatFlashData(pModule, pszBuf, nLen);
	}
	virtual int SetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int nLen)
	{
		if(pModule->m_oModuleAttr.m_nModuleIndex != 4)
		{
			return 0;
		}
		return CSttDeviceComm::SetModuleFlash(pModule, pszBuf, nLen);
	}
	virtual BOOL GetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int &nOffset)
	{
		if(pModule->m_oModuleAttr.m_nModuleIndex != 4)
		{
			return FALSE;
		}
		return CSttDeviceComm::GetModuleFlash(pModule, pszBuf, nOffset);
	}

protected:
	BattaryInfo m_oBat485Info;
	unsigned int m_nBatErrCnt;
	int m_nBatCalcCnt;
	BatInfo m_oBatInfo;
	BOOL IsBatPower();//判断当前是否电池供电
	BOOL IsLargeCurrentOutput();
};

#endif // CSTTDEVICEL336D_H
