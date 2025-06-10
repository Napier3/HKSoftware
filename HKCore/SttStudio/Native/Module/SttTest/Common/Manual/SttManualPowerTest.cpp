#include "stdafx.h"
#include "SttManualPowerTest.h"
#include "../SttSystemConfig.h"
#include "../SttStateTest.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttManualPowerTest::m_strMacroName = "通用试验功率测试";
CString CSttManualPowerTest::m_strMacroID = STT_MACRO_ID_PowerManuTest;
CString CSttManualPowerTest::m_strFilePostFix = "mpow";
CString CSttManualPowerTest::m_strMacroVer ="1.0";


CSttManualPowerTest::CSttManualPowerTest() : CSttManuTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
}

void CSttManualPowerTest::Init()
{
    CSttManuTest::Init();
    m_pManualTest->m_oManuParas.SetFundFreq(g_theSystemConfig->m_fFNom);
	float fAngle[3] = {0, -120.0, 120.0};
	for(int i = 0; i < 4; i++)
	{
		m_uiVOL[i].Harm[0].fAmp = 0;
		m_uiVOL[i].Harm[1].fAmp = 0;
		m_uiVOL[i].Harm[1].fAngle = fAngle[i % 3];
		m_uiVOL[i].Harm[1].fFreq = 50;

		for(int harm = 0; harm < MAX_HARM_COUNT; harm++)
		{
			m_uiVOL[i].Harm[harm].init();
		}
	}

	for(int i = 0; i < 3; i++)
	{
		m_uiPOW[i].init();
	}
	m_oManualPowerResults.init();
	m_oGradientParas.init();
	m_oGradientParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
	m_oGradientParas.m_nSttTestMode = GradientTest_Base;
}

CSttManualPowerTest::~CSttManualPowerTest(void)
{

}

void CSttManualPowerTest::AfterSetParameter()
{
    CSttManuTest::AfterSetParameter();
    m_oManualPowerResults.init();//zhouhj 20210804  在设置参数后调用,在搜索阻抗边界等模块,需要在同一个测试项多次调用开始测试时,需要对结果进行初始化
}

long CSttManualPowerTest::CalReport(UINT nState)
{
	return 0;
}

void CSttManualPowerTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_Power(&m_pManualTest->m_oManuParas,pXmlSerialize,m_uiVOL,m_uiPOW);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttManualPowerTest::SyncGradientResult(int nStep, double dTime, int nTripType)
{
#ifdef _PSX_QT_LINUX_
	GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
	long nDirection = 1;

	if(m_oGradientParas.m_fStart > m_oGradientParas.m_fStop)
	{
		nDirection = -1;
	}

	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	float fUIStepValue;

	if(nStep == pTmtGradientProcess->m_nStepCount)
	{
		fUIStepValue = m_oGradientParas.m_fStop;
	}
	else
	{
		fUIStepValue = m_oGradientParas.m_fStart + m_oGradientParas.m_fStep * nDirection * nStep;
	}

	if(nTripType == 0)
	{
		oRampRestCom.m_fTripValue = fUIStepValue;
		oRampRestCom.m_fTripTime = dTime;
	}
	else
	{
		oRampRestCom.m_fReturnValue = fUIStepValue;
		oRampRestCom.m_fReturnTime = dTime;

		if(fabs(oRampRestCom.m_fTripValue) < EPSINON)
		{
			oRampRestCom.m_fReturnCoef = 0;
		}
		else
		{
			oRampRestCom.m_fReturnCoef = oRampRestCom.m_fReturnValue / oRampRestCom.m_fTripValue; //返回值/动作值
		}
	}
#endif
}

void CSttManualPowerTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    m_oManualPowerResults.m_frTestTime = oRampRestCom.m_fTripTime;
    m_oManualPowerResults.m_fTripTime = m_oManualPowerResults.m_frTestTime;
    int nrBinSwitchCount, nrBinExSwitchCount;

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        nrBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[i];
        m_oManualPowerResults.m_nrBinSwitchCount[i] = nrBinSwitchCount;

        for(int j = 0; j < nrBinSwitchCount && j <= 64; j++)
        {
            m_oManualPowerResults.m_frTimeBinAct[i][j] = oRampRestCom.m_frTimeBinAct[i][j];
        }
    }

    SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

    for(int i = 0; i < oSwitchModules.m_nModulesBiCount; i++)
    {
        nrBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[i];
        m_oManualPowerResults.m_nrBinExSwitchCount[i] = nrBinExSwitchCount;

        for(int j = 0; j < nrBinExSwitchCount && j <= 64; j++)
        {
            m_oManualPowerResults.m_frTimeBinExAct[i][j] = oRampRestCom.m_frTimeBinExAct[i][j];
        }
    }

    m_oManualPowerResults.m_nTripFlag = oRampRestCom.m_nAct;
    m_oManualPowerResults.m_fActValue = oRampRestCom.m_fTripValue;
    m_oManualPowerResults.m_fReturnValue = oRampRestCom.m_fReturnValue;
    m_oManualPowerResults.m_fReturnCoef = oRampRestCom.m_fReturnCoef;
    m_oManualPowerResults.m_fReturnTime = oRampRestCom.m_fReturnTime;
#endif
    stt_xml_serialize(&m_oManualPowerResults, pXmlSerialize);
}

long CSttManualPowerTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttManualPowerTest::TtmToDrv()
{
	if(m_pManualTest->m_oManuParas.m_bAuto)
    {
		m_nCurStepIndex = 0;
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_Gradient_NeedStepsValue(&m_oGradientParas);
#endif
	}
	else
	{
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_manu(m_pManualTest, TRUE);
#endif
    }
}

void CSttManualPowerTest::TranslateToStateParas()
{
    float dI_mag[3],dI_ang[3];
    for (int j=0;j<3;j++)
    {
        CalABCValues_ByPowerValues_Float(dI_mag[j],dI_ang[j],m_uiPOW[j].m_fPpower,m_uiPOW[j].m_fQpower,m_uiVOL[j].Harm[1].fAmp,m_uiVOL[j].Harm[1].fAngle);

        m_pManualTest->m_oManuParas.m_uiVOL[j].Harm[1].fAmp = m_uiVOL[j].Harm[1].fAmp;
        m_pManualTest->m_oManuParas.m_uiVOL[j].Harm[1].fAngle = m_uiVOL[j].Harm[1].fAngle;
		m_pManualTest->m_oManuParas.m_uiVOL[j].Harm[1].fFreq = m_uiVOL[j].Harm[1].fFreq;
        m_pManualTest->m_oManuParas.m_uiCUR[j].Harm[1].fAmp = dI_mag[j];
        m_pManualTest->m_oManuParas.m_uiCUR[j].Harm[1].fAngle = dI_ang[j];
		m_pManualTest->m_oManuParas.m_uiCUR[j].Harm[1].fFreq = m_uiVOL[j].Harm[1].fFreq;
    }

    m_pManualTest->m_oManuParas.m_uiVOL[3].Harm[1].fAmp = m_uiVOL[3].Harm[1].fAmp;
	m_pManualTest->m_oManuParas.m_uiVOL[3].Harm[1].fAngle = m_uiVOL[3].Harm[1].fAngle;
	m_pManualTest->m_oManuParas.m_uiVOL[3].Harm[1].fFreq = m_uiVOL[3].Harm[1].fFreq;

	if(m_pManualTest->m_oManuParas.m_bAuto)
	{
		m_oGradientParas.m_nBinLogic = m_pManualTest->m_oManuParas.m_nBinLogic;

		for(int j = 0; j < MAX_BINARYIN_COUNT; j++)
		{
			m_oGradientParas.m_binIn[j].nSelect =
				m_pManualTest->m_oManuParas.m_binIn[j].nSelect;
		}

		for(int j = 0; j < g_nBinExCount && j < MAX_ExBINARY_COUNT; j++)
		{
			m_oGradientParas.m_binInEx[j].nSelect =
				m_pManualTest->m_oManuParas.m_binInEx[j].nSelect;
		}

		for(int j = 0; j < MAX_BINARYOUT_COUNT; j++)
		{
			m_oGradientParas.m_binOut[1][j].nState =
				m_pManualTest->m_oManuParas.m_binOut[j].nState;
			m_oGradientParas.m_binOut[1][j].nMode =
				m_pManualTest->m_oManuParas.m_binOut[j].nMode;
			m_oGradientParas.m_binOut[1][j].fTimeTrig =
				m_pManualTest->m_oManuParas.m_binOut[j].fTimeTrig;
			m_oGradientParas.m_binOut[1][j].fHoldTime =
				m_pManualTest->m_oManuParas.m_binOut[j].fHoldTime;
		}

		for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
		{
			m_oGradientParas.m_binOutEx[1][j].nState =
				m_pManualTest->m_oManuParas.m_binOutEx[j].nState;
			m_oGradientParas.m_binOutEx[1][j].nMode =
				m_pManualTest->m_oManuParas.m_binOutEx[j].nMode;
			m_oGradientParas.m_binOutEx[1][j].fTimeTrig =
				m_pManualTest->m_oManuParas.m_binOutEx[j].fTimeTrig;
			m_oGradientParas.m_binOutEx[1][j].fHoldTime =
				m_pManualTest->m_oManuParas.m_binOutEx[j].fHoldTime;
		}

		for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
		{
			m_oGradientParas.m_oGoosePub[nIndex].m_bUseFlag =
				m_pManualTest->m_oManuParas.m_oGoosePub[nIndex].m_bUseFlag;
			m_oGradientParas.m_oGoosePub[nIndex].m_bHasTest =
				m_pManualTest->m_oManuParas.m_oGoosePub[nIndex].m_bHasTest;
			m_oGradientParas.m_oGoosePub[nIndex].m_nTest =
				m_pManualTest->m_oManuParas.m_oGoosePub[nIndex].m_nTest;

			for(int nCh = 0; nCh < MAX_GOOSE_CHANNEL_COUNT; nCh++)
			{
				m_oGradientParas.m_oGoosePub[nIndex].m_strChannel[nCh] =
					m_pManualTest->m_oManuParas.m_oGoosePub[nIndex].m_strChannel[nCh];
			}
		}

		tmt_ManuGradient *pmanuGradient = &m_pManualTest->m_oManuParas.m_manuGradient;
		m_oGradientParas.m_nTestMode = pmanuGradient->nMode;
		m_oGradientParas.m_fStart = pmanuGradient->fStart;
		m_oGradientParas.m_fStop = pmanuGradient->fEnd;
		m_oGradientParas.m_fStep = pmanuGradient->fStep;
		m_oGradientParas.m_fStepTime = pmanuGradient->fStepTime;

		int	 nType = m_pManualTest->m_oManuParas.m_nVarIndexType;
		switch(m_pManualTest->m_oManuParas.m_nGradientChSelect)
		{
		case STT_Power_Gradient_Ch_Sa:
		{
			if(nType == 0)
			{
				m_uiPOW[0].m_fPpower = m_oGradientParas.m_fStart;
			}
			else
			{
				m_uiPOW[0].m_fQpower = m_oGradientParas.m_fStart;
			}
		}
			break;
		case STT_Power_Gradient_Ch_Sb:
		{
			if(nType == 0)
			{
				m_uiPOW[1].m_fPpower = m_oGradientParas.m_fStart;
			}
			else
			{
				m_uiPOW[1].m_fQpower = m_oGradientParas.m_fStart;
			}
		}
			break;
		default:
		{
			if(nType == 0)
			{
				m_uiPOW[2].m_fPpower = m_oGradientParas.m_fStart;
			}
			else
			{
				m_uiPOW[2].m_fQpower = m_oGradientParas.m_fStart;
			}
		}
		}

		//设置故障前所有通道始值
		for (int j=0;j<3;j++)
    {
			CalABCValues_ByPowerValues_Float(dI_mag[j],dI_ang[j],m_uiPOW[j].m_fPpower,m_uiPOW[j].m_fQpower,m_uiVOL[j].Harm[1].fAmp,m_uiVOL[j].Harm[1].fAngle);

			m_oGradientParas.m_uiVOL[1][j].Harm[1].fAmp = m_uiVOL[j].Harm[1].fAmp;
			m_oGradientParas.m_uiVOL[1][j].Harm[1].fAngle = m_uiVOL[j].Harm[1].fAngle;
			m_oGradientParas.m_uiVOL[1][j].Harm[1].fFreq = m_uiVOL[j].Harm[1].fFreq;
			m_oGradientParas.m_uiCUR[1][j].Harm[1].fAmp = dI_mag[j];
			m_oGradientParas.m_uiCUR[1][j].Harm[1].fAngle = dI_ang[j];
			m_oGradientParas.m_uiCUR[1][j].Harm[1].fFreq = m_uiVOL[j].Harm[1].fFreq;
    }

		m_oGradientParas.m_uiVOL[1][3].Harm[1].fAmp = m_uiVOL[3].Harm[1].fAmp;
		m_oGradientParas.m_uiVOL[1][3].Harm[1].fAngle = m_uiVOL[3].Harm[1].fAngle;
		m_oGradientParas.m_uiVOL[1][3].Harm[1].fFreq = m_uiVOL[3].Harm[1].fFreq;

#ifdef _PSX_QT_LINUX_
		memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bUChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);
		memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bIChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);

		tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;

		pTmtGradientProcess->m_bIChange[0][0] = 1;
		pTmtGradientProcess->m_bIChange[1][0] = 1;
		pTmtGradientProcess->m_bIChange[2][0] = 1;
		pTmtGradientProcess->m_bIChange[0][1] = 1;
		pTmtGradientProcess->m_bIChange[1][1] = 1;
		pTmtGradientProcess->m_bIChange[2][1] = 1;

		CalStepValue_Gradient(&m_oGradientParas, 1, 3);
#endif
	}

}

void CSttManualPowerTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	if(!CheckBeforeUpdatePara())
    {
		return;
    }

	Para_XmlSerialize(pXmlSerialize);
	CSttTestBase::StartTest();//实验开始时间重新赋值
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Manu_UpdateParameter(FALSE);
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_manu(m_pManualTest);
#endif
	CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttManualPowerTest::UpdatePara Finished");
}

void CSttManualPowerTest::CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex)
{
	int	 nType = m_pManualTest->m_oManuParas.m_nVarIndexType;
	switch(m_pManualTest->m_oManuParas.m_nGradientChSelect)
	{
	case STT_Power_Gradient_Ch_Sa:
	{
		if(nType == 0)
		{
			m_uiPOW[0].m_fPpower = fCurValue;
		}
		else
		{
			m_uiPOW[0].m_fQpower = fCurValue;
		}
	}
		break;
	case STT_Power_Gradient_Ch_Sb:
	{
		if(nType == 0)
		{
			m_uiPOW[1].m_fPpower = fCurValue;
		}
		else
		{
			m_uiPOW[1].m_fQpower = fCurValue;
		}
	}
		break;
	default:
	{
		if(nType == 0)
		{
			m_uiPOW[2].m_fPpower = fCurValue;
		}
		else
		{
			m_uiPOW[2].m_fQpower = fCurValue;
		}
	}
	}

    float dI_mag[3],dI_ang[3];
    for (int j=0;j<3;j++)
    {
        CalABCValues_ByPowerValues_Float(dI_mag[j],dI_ang[j],m_uiPOW[j].m_fPpower,m_uiPOW[j].m_fQpower,m_uiVOL[j].Harm[1].fAmp,m_uiVOL[j].Harm[1].fAngle);

		pTmt_GradientParas->m_uiCUR[2][j].Harm[1].fAmp = dI_mag[j];
		pTmt_GradientParas->m_uiCUR[2][j].Harm[1].fAngle = dI_ang[j];
		pTmt_GradientParas->m_uiCUR[2][j].Harm[1].fFreq = m_uiVOL[j].Harm[1].fFreq;
	}
}

void CSttManualPowerTest::ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType)
{
	STT_RTDATA_EVENT oRtdata;
	oRtdata.oTime.dTime = dTime1;
	oRtdata.oTime.dRealTime = dTime2;
	oRtdata.m_nVolChCount = 0;
	oRtdata.m_nCurChCount = 0;
	oRtdata.m_nHasFaultVolCur=0;
	int nRtIndex = 0;
	float fVal;

	if(m_pManualTest->m_oManuParas.m_bAuto)
	{
#ifdef _PSX_QT_LINUX_

		if(nType == 0 || nType == 1)
		{
			//变化前
			for(int nIndex = 0; nIndex < g_nRtDataVoltCnt; nIndex++)
			{
				nRtIndex = oRtdata.m_nVolChCount;
				oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oVolCh[nRtIndex].m_fMag =
					m_oGradientParas.m_uiVOL[nType][nIndex].Harm[1].fAmp;
				oRtdata.m_oVolCh[nRtIndex].m_fAng =
					m_oGradientParas.m_uiVOL[nType][nIndex].Harm[1].fAngle;
				oRtdata.m_oVolCh[nRtIndex].m_fFreq =
					m_oGradientParas.m_uiVOL[nType][nIndex].Harm[1].fFreq;
				oRtdata.m_nVolChCount++;
			}

			for(int nIndex = 0; nIndex < g_nRtDataCurrCnt; nIndex++)
			{
				nRtIndex = oRtdata.m_nCurChCount;
				oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oCurCh[nRtIndex].m_fMag =
					m_oGradientParas.m_uiCUR[nType][nIndex].Harm[1].fAmp;
				oRtdata.m_oCurCh[nRtIndex].m_fAng =
					m_oGradientParas.m_uiCUR[nType][nIndex].Harm[1].fAngle;
				oRtdata.m_oCurCh[nRtIndex].m_fFreq =
					m_oGradientParas.m_uiCUR[nType][nIndex].Harm[1].fFreq;
				oRtdata.m_nCurChCount++;
			}
		}
		else
		{
			tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;

			if((nStep < pTmtGradientProcess->m_nStepCount) && (nStep < GRADIENT_MAX_COUNT))
			{
				for(int nIndex = 0; nIndex < 3; nIndex++)
				{
					if(pTmtGradientProcess->m_bUChange[nIndex][0] == 0
							&& pTmtGradientProcess->m_bUChange[nIndex][1] == 0)
					{
						continue;
					}

					fVal = fabs(pTmtGradientProcess->m_uiStepData[nStep].fU[nIndex][0]);
					nRtIndex = oRtdata.m_nVolChCount;
					oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
					oRtdata.m_oVolCh[nRtIndex].m_fMag = fVal;
					oRtdata.m_oVolCh[nRtIndex].m_fAng =
						pTmtGradientProcess->m_uiStepData[nStep].fU[nIndex][1];
					oRtdata.m_oVolCh[nRtIndex].m_fFreq =
						pTmtGradientProcess->m_uiStepData[nStep].fU[nIndex][2];
					oRtdata.m_nVolChCount++;
				}

				for(int nIndex = 0; nIndex < 3; nIndex++)
				{
					if(pTmtGradientProcess->m_bIChange[nIndex][0] == 0
							&& pTmtGradientProcess->m_bIChange[nIndex][1] == 0)
					{
						continue;
					}

					fVal = fabs(pTmtGradientProcess->m_uiStepData[nStep].fI[nIndex][0]);
					nRtIndex = oRtdata.m_nCurChCount;
					oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
					oRtdata.m_oCurCh[nRtIndex].m_fMag = fVal;
					oRtdata.m_oCurCh[nRtIndex].m_fAng =
						pTmtGradientProcess->m_uiStepData[nStep].fI[nIndex][1];
					oRtdata.m_oCurCh[nRtIndex].m_fFreq =
						pTmtGradientProcess->m_uiStepData[nStep].fI[nIndex][2];
					oRtdata.m_nCurChCount++;
				}
			}
		}

#endif
	}
	else
	{
#ifdef _PSX_QT_LINUX_

		if(CSttDeviceBase::g_pSttDeviceBase->m_oManuRtList.isEmpty())
		{
			return;
		}

		ManuRtData oManuRtData = CSttDeviceBase::g_pSttDeviceBase->m_oManuRtList.takeFirst();

		for(int nIndex = 0; nIndex < 3; nIndex++)
		{
			fVal = fabs(oManuRtData.uiVOL[nIndex].Harm[1].fAmp);
			nRtIndex = oRtdata.m_nVolChCount;
			oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
			oRtdata.m_oVolCh[nRtIndex].m_fMag = fVal;
			oRtdata.m_oVolCh[nRtIndex].m_fAng =
				oManuRtData.uiVOL[nIndex].Harm[1].fAngle;
			oRtdata.m_oVolCh[nRtIndex].m_fFreq =
				oManuRtData.uiVOL[nIndex].Harm[1].fFreq;
			oRtdata.m_nVolChCount++;
    }

		for(int nIndex = 0; nIndex < 3; nIndex++)
    {
			fVal = fabs(oManuRtData.uiCUR[nIndex].Harm[1].fAmp);
			nRtIndex = oRtdata.m_nCurChCount;
			oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
			oRtdata.m_oCurCh[nRtIndex].m_fMag = fVal;
			oRtdata.m_oCurCh[nRtIndex].m_fAng =
				oManuRtData.uiCUR[nIndex].Harm[1].fAngle;
			oRtdata.m_oCurCh[nRtIndex].m_fFreq =
				oManuRtData.uiCUR[nIndex].Harm[1].fFreq;
			oRtdata.m_nCurChCount++;
		}

#endif
    }

	if(oRtdata.m_nCurChCount > 0 || oRtdata.m_nVolChCount > 0)
    {
		stt_add_rtdatas(oRtdata);
    }
}
