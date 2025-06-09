#ifndef CSTTDEVICEPNS330_H
#define CSTTDEVICEPNS330_H

#include "../Module/Driver466/SttDeviceComm.h"
#include "stdafx.h"



#define UIModulePower_10A  2
#define UIModulePower_20A  1

typedef struct
{
	float fVolt;//电池电压
	float fCurr;//电池电流
}BatInfo;

class CSttDevicePNS330 : public CSttDeviceComm, public CSttDeviceBase
{
private:
    explicit CSttDevicePNS330();
    ~CSttDevicePNS330();
    static long g_nSttDeviceRef;

public:
    static void Create();
    static void Release();
    static CSttDevicePNS330 *g_pSttDevicePNS330;

    virtual int InitDevice(BOOL bHasAdjFile);
    virtual void SetRegisterValue(unsigned int nAddr, unsigned int nValue);
	virtual BOOL GetDevInputInfo(){return CSttDeviceComm::GetDevInputInfo();}

public:
    virtual void SetSystemConfig()
    {
        CSttDeviceComm::SetSystemConfig();
    }
    virtual void SetPeripheral();

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
		if((m_nRegCtrlDigital >> 6) & 0x01)
		{
			//开入量检测电源已打开
		}
		else
		{
			m_nRegCtrlDigital |= 1 << 6; //ON/OFF_KIO
			g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
			SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
			g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
		}

        CSttDeviceComm::SetBinaryOutTurnOnVaule(nValue);
    }
    virtual void SetBinaryOut(BOOL bOpen = FALSE)
    {
        CSttDeviceComm::SetBinaryOut(bOpen);
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

    virtual void SetAuxDcVolt(float fUdc)
    {
        CSttDeviceComm::SetAuxDcVolt(fUdc);
    }

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
//    virtual void InitGooseSub()
//    {
//        CSttDeviceComm::InitGooseSub();
//    }
    //Replay
public:
    virtual void tmt_to_drv_LtReplay(tmt_ReplayParas *pTmt, char *pszLtReplayCoef)
    {
        CSttDeviceComm::tmt_to_drv_LtReplay(pTmt, pszLtReplayCoef);
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

    virtual void FormatFlashData(PSTT_MODULE pModule, BYTE *pszBuf, long &nLen)
    {
        if(m_nBootMode == 1)
        {
            CSttDeviceComm::FormatFlashData(pModule, pszBuf, nLen);
        }
    }
    virtual int SetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int nLen)
    {
        if(m_nBootMode == 1)
        {
            CSttDeviceComm::SetModuleFlash(pModule, pszBuf, nLen);
        }
    }

    virtual BOOL GetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int &nOffset)
    {
        if(m_nBootMode == 1)
        {
            return CSttDeviceComm::GetModuleFlash(pModule, pszBuf, nOffset);
        }
    }

public:
    virtual void GetVoltCurRtData();
    virtual void SetDrvMoudlePara();
    virtual void InitModulePowerCtrl();

    virtual void DAPowerCtrl();
    virtual void PreStartTestPro();
    virtual void AfterTestFinishedPro();
    virtual BOOL OnTimer(BOOL bExec = FALSE);
    virtual void AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack, int nModulePos, int nModuleType);
	virtual BOOL SetOutputTime(tmt_channel *pChannel, BOOL bDc, float &fOutPutTime);
	virtual void GetModuleInfo(Drv_SysInfo *pSysInfo);
	virtual void Stt_Xml_Serialize_Channels(CSttXmlSerializeBase *pXmlSerialize);

private:
	unsigned int m_nBatErrCnt;
    int m_nBatCalcCnt;
    int m_nTestStopTick;
	BatInfo m_oBatInfoRef0;//开机时初始电池信息
	BatInfo m_oBatInfoRef1;//第一次输出时电池信息
	BatInfo m_oBatInfo;
	long m_nBatLastTime;
	long m_nUIModulePower;//0-null,1-20A,2-10A,
	long GetMainUIPowerMode();
	BOOL IsLargeCurrentOutput();
};

#endif // CSTTDEVICEPNS330_H
