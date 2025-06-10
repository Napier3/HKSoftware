#include "stdafx.h"
#include "SttManuaImpedTest.h"
#include "../SttSystemConfig.h"
#include "../SttStateTest.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttManuaImpedTest::m_strMacroName = "通用试验阻抗测试";
CString CSttManuaImpedTest::m_strMacroID = STT_MACRO_ID_ImpedManualTest;
CString CSttManuaImpedTest::m_strFilePostFix = "mimp";
CString CSttManuaImpedTest::m_strMacroVer ="1.0";


CSttManuaImpedTest::CSttManuaImpedTest() : CSttManuTest()
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

void CSttManuaImpedTest::Init()
{
    CSttManuTest::Init();
    m_pManualTest->m_oManuParas.SetFundFreq(g_theSystemConfig->m_fFNom);
    tmt_ManualImpedParas::init();
	m_oManualImpedResults.init();
	m_oGradientParas.init();
	m_oGradientParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
	m_oGradientParas.m_nSttTestMode = GradientTest_Base;
}

CSttManuaImpedTest::~CSttManuaImpedTest(void)
{

}

void CSttManuaImpedTest::AfterSetParameter()
{
    CSttManuTest::AfterSetParameter();
    m_oManualImpedResults.init();//zhouhj 20210804  在设置参数后调用,在搜索阻抗边界等模块,需要在同一个测试项多次调用开始测试时,需要对结果进行初始化

	if(m_bAuto && !m_bMutation)
    {
		m_fPrepareTime = 0;
		m_fPreFaultTime = 0;
    }
}

long CSttManuaImpedTest::CalReport(UINT nState)
{
	return CSttManuTest::CalReport(nState);
}

void CSttManuaImpedTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize((tmt_ManualImpedParas*)this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttManuaImpedTest::SyncGradientResult(int nStep, double dTime, int nTripType)
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

void CSttManuaImpedTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    m_oManualImpedResults.m_frTestTime = oRampRestCom.m_fTripTime;
    m_oManualImpedResults.m_fTripTime = m_oManualImpedResults.m_frTestTime;
    int nrBinSwitchCount, nrBinExSwitchCount;

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        nrBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[i];
        m_oManualImpedResults.m_nrBinSwitchCount[i] = nrBinSwitchCount;

        for(int j = 0; j < nrBinSwitchCount && j <= 64; j++)
        {
            m_oManualImpedResults.m_frTimeBinAct[i][j] = oRampRestCom.m_frTimeBinAct[i][j];
        }
    }

    SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

    for(int i = 0; i < oSwitchModules.m_nModulesBiCount; i++)
    {
        nrBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[i];
        m_oManualImpedResults.m_nrBinExSwitchCount[i] = nrBinExSwitchCount;

        for(int j = 0; j < nrBinExSwitchCount && j <= 64; j++)
        {
            m_oManualImpedResults.m_frTimeBinExAct[i][j] = oRampRestCom.m_frTimeBinExAct[i][j];
        }
    }

    m_oManualImpedResults.m_nTripFlag = oRampRestCom.m_nAct;
    m_oManualImpedResults.m_fActValue = oRampRestCom.m_fTripValue;
    m_oManualImpedResults.m_fReturnValue = oRampRestCom.m_fReturnValue;
    m_oManualImpedResults.m_fReturnCoef = oRampRestCom.m_fReturnCoef;
    m_oManualImpedResults.m_fReturnTime = oRampRestCom.m_fReturnTime;
#endif
    stt_xml_serialize(&m_oManualImpedResults, pXmlSerialize);
}

long CSttManuaImpedTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttManuaImpedTest::TtmToDrv()
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

void CSttManuaImpedTest::Global_FaultCalculatUI(tmt_ManualImpedParas *pManualImpParas,Complex *pVol_Complex,Complex *pCur_Complex)
{
    CSttFaultCalculatTool oFaultCalculatTool;
    float fVOutmax = 120.0f;//暂时默认最大输出电压120V
    float fIOutmax = 30.0f;//暂时默认最大输出电压30A
    float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
    int nPhaseRef[11]={1,2,0,2,0,1,2,0,1,0,0};
    float nAngle[11] = {(float)pVol_Complex[0].arg(),(float)pVol_Complex[1].arg(),(float)pVol_Complex[2].arg(),(float)pVol_Complex[0].arg()+30.0f
                        ,(float)pVol_Complex[1].arg()+30.0f,(float)pVol_Complex[2].arg()+30.0f,(float)pVol_Complex[0].arg()+30.0f,(float)pVol_Complex[1].arg()+30.0f
                        ,(float)pVol_Complex[2].arg()+30.0f,(float)pVol_Complex[0].arg(),(float)pVol_Complex[2].arg()};
    float fVFactor=1.0f,fIFactor=1.0f,fValueFactor = 1.0f;
    Complex fUI[7];
    Complex Comp1;
    float	fK0AmpCal;		//计算后的 m_fK0Amp
    float	fK0AngleCal;		//计算后的 m_fK0Angle
    Comp1 = oFaultCalculatTool.GroundFactor(pManualImpParas->m_nOffsetsMode,pManualImpParas->m_fAmplitudeOrKr,pManualImpParas->m_fPhaseOrKx,pManualImpParas->m_fZAngle);
    fK0AmpCal=(float)Comp1.norm();
    fK0AngleCal=(float)Comp1.arg();

    if(g_theSystemConfig->m_nParaMode == 0)//如果参数设置为一次值
    {
        fValueFactor=1000.0;
        fVFactor = g_theSystemConfig->m_fVPrimary[0]/g_theSystemConfig->m_fVSecondary[0];
        fIFactor = g_theSystemConfig->m_fIPrimary[0]/g_theSystemConfig->m_fISecondary[0];
    }

    double fIt = pManualImpParas->m_fSCCurrent/fIFactor;
    double fVt = pManualImpParas->m_fSCVoltage/fVFactor;
    oFaultCalculatTool.Calculat(1.0f,1,1,pManualImpParas->m_nCalMode,pManualImpParas->m_nFaultType,
                                nPhaseRef[pManualImpParas->m_nFaultType],nAngle[nPhaseRef[pManualImpParas->m_nFaultType]],
            fVOutmax/fVFactor,fStdLN_Vol/fVFactor,fIOutmax/fIFactor,
            &fIt,&fVt,
            Comp1.polar(0,-20),	//不再检测负荷电流是否允许有值，交给平台决定
            Comp1.polar(pManualImpParas->m_fZAmp/fVFactor/fValueFactor*fIFactor,pManualImpParas->m_fZAngle),
            Comp1.polar(fK0AmpCal,fK0AngleCal),
            Comp1.polar(pManualImpParas->m_fSZSAmp/fVFactor/fValueFactor*fIFactor,pManualImpParas->m_fSZSAngle),
            Comp1.polar(0,0),
            &fUI[0],&fUI[1],&fUI[2],&fUI[4],&fUI[5],&fUI[6]);

    for (int i=0;i<3;i++)
    {
        pVol_Complex[i] = fUI[i]*fVFactor;
        pCur_Complex[i] = fUI[i+4]*fIFactor;
    }
}

void CSttManuaImpedTest::Global_SetStateUIFromCpl(tmt_ManualParas *pManualPara,Complex *pVol_Complex,Complex *pCur_Complex)
{
    for (int j=0;j<3;j++)
    {
        pManualPara->m_uiVOL[j].Harm[1].fAmp = (float)pVol_Complex[j].norm();
        pManualPara->m_uiVOL[j].Harm[1].fAngle = (float)pVol_Complex[j].arg();
        pManualPara->m_uiCUR[j].Harm[1].fAmp = (float)pCur_Complex[j].norm();
        pManualPara->m_uiCUR[j].Harm[1].fAngle = (float)pCur_Complex[j].arg();
    }

    pManualPara->m_uiVOL[3].Harm[1].fAmp = (float)pVol_Complex[3].norm();
    pManualPara->m_uiVOL[3].Harm[1].fAngle = (float)pVol_Complex[3].arg();
}

void CSttManuaImpedTest::TranslateToStateParas()
{
    Complex	oComplexUI[2][4];
    if(m_nImped == 1)
    {
        Complex oComplexImp(m_fR,m_fX);
        m_fZAmp = oComplexImp.norm();
        m_fZAngle = oComplexImp.arg();
    }
    m_pManualTest->m_oManuParas.m_bLockChanged = m_bLockChanged;
    
    Global_FaultCalculatUI(this,oComplexUI[0],oComplexUI[1]);
    Global_SetStateUIFromCpl(&m_pManualTest->m_oManuParas,oComplexUI[0],oComplexUI[1]);
    for(int i = 0; i<MAX_BINARYIN_COUNT; i++)
    {
        m_pManualTest->m_oManuParas.m_binIn[i] = m_binIn[i];
        m_pManualTest->m_oManuParas.m_binOut[i] = m_binOut[i];
    }
    for(int i = 0; i<MAX_ExBINARY_COUNT; i++)
    {
        m_pManualTest->m_oManuParas.m_binInEx[i] = m_binInEx[i];
        m_pManualTest->m_oManuParas.m_binOutEx[i] = m_binOutEx[i];
    }
    m_pManualTest->m_oManuParas.m_nBinLogic = m_nBinLogic;

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
			for(int i = 0;i < 2;i++)
			{
				m_oGradientParas.m_binOut[i][j].nState =
					m_pManualTest->m_oManuParas.m_binOut[j].nState;
				m_oGradientParas.m_binOut[i][j].nMode =
					m_pManualTest->m_oManuParas.m_binOut[j].nMode;
				m_oGradientParas.m_binOut[i][j].fTimeTrig =
					m_pManualTest->m_oManuParas.m_binOut[j].fTimeTrig;
				m_oGradientParas.m_binOut[i][j].fHoldTime =
					m_pManualTest->m_oManuParas.m_binOut[j].fHoldTime;
			}
		}

		for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
		{
			for(int i = 0;i < 2;i++)
			{
				m_oGradientParas.m_binOutEx[i][j].nState =
					m_pManualTest->m_oManuParas.m_binOutEx[j].nState;
				m_oGradientParas.m_binOutEx[i][j].nMode =
					m_pManualTest->m_oManuParas.m_binOutEx[j].nMode;
				m_oGradientParas.m_binOutEx[i][j].fTimeTrig =
					m_pManualTest->m_oManuParas.m_binOutEx[j].fTimeTrig;
				m_oGradientParas.m_binOutEx[i][j].fHoldTime =
					m_pManualTest->m_oManuParas.m_binOutEx[j].fHoldTime;
			}
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

		m_oGradientParas.m_nTestMode = m_pManualTest->m_oManuParas.m_manuGradient.nMode;
		m_oGradientParas.m_fStart = m_pManualTest->m_oManuParas.m_manuGradient.fStart;
		m_oGradientParas.m_fStop = m_pManualTest->m_oManuParas.m_manuGradient.fEnd;
		m_oGradientParas.m_fStep = m_pManualTest->m_oManuParas.m_manuGradient.fStep;
		m_oGradientParas.m_fPrepareTime = m_fPrepareTime;
		m_oGradientParas.m_fPreFaultTime = m_fPreFaultTime;
		m_oGradientParas.m_fStepTime = m_pManualTest->m_oManuParas.m_manuGradient.fStepTime;

		//设置故障前所有通道始值
		float fAngle[3] = {0, -120.0, 120.0};
		for(int nIndex = 0; nIndex < 3; nIndex++)
		{
			for(int i = 0;i < 2;i++)
			{
				m_oGradientParas.m_uiVOL[i][nIndex].Harm[1].fAmp = g_theSystemConfig->m_fVNom/SQRT3;
				m_oGradientParas.m_uiVOL[i][nIndex].Harm[1].fAngle = fAngle[nIndex%3];
				m_oGradientParas.m_uiVOL[i][nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
				m_oGradientParas.m_uiCUR[i][nIndex].Harm[1].fAmp = 0;
				m_oGradientParas.m_uiCUR[i][nIndex].Harm[1].fAngle = fAngle[nIndex%3];;
				m_oGradientParas.m_uiCUR[i][nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
			}
		}

		for(int i = 0;i < 2;i++)
		{
			m_oGradientParas.m_uiVOL[i][3].Harm[1].fAmp = g_theSystemConfig->m_fVNom/SQRT3;
			m_oGradientParas.m_uiVOL[i][3].Harm[1].fAngle = 0;
			m_oGradientParas.m_uiVOL[i][3].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
		}

#ifdef _PSX_QT_LINUX_
		memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bUChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);
		memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bIChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);

		tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;

		pTmtGradientProcess->m_bUChange[0][0] = 1;
		pTmtGradientProcess->m_bUChange[1][0] = 1;
		pTmtGradientProcess->m_bUChange[2][0] = 1;
		pTmtGradientProcess->m_bUChange[0][1] = 1;
		pTmtGradientProcess->m_bUChange[1][1] = 1;
		pTmtGradientProcess->m_bUChange[2][1] = 1;
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

void CSttManuaImpedTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
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
	CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttManuaImpedTest::UpdatePara Finished");
}

void CSttManuaImpedTest::CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex)
{
	switch(m_nFirstMode)
	{
	case 0:
		if(m_nSecondMode == 0)
		{
			m_fZAmp = fCurValue;
		}
		else
		{
			m_fZAngle = fCurValue;
		}
		break;
	case 1:
		m_fR = fCurValue;
		break;
	case 2:
		m_fX = fCurValue;
		break;
	case 3:
		if(m_nCalMode == 0)
		{
			m_fSCCurrent = fCurValue;
		}
		else if(m_nCalMode == 1)
		{
			m_fSCVoltage = fCurValue;
		}
		break;
	}

	Complex	oComplexUI[2][4];
	if(m_nImped == 1)
	{
		Complex oComplexImp(m_fR,m_fX);
		m_fZAmp = oComplexImp.norm();
		m_fZAngle = oComplexImp.arg();
	}

	Global_FaultCalculatUI(this,oComplexUI[0],oComplexUI[1]);
	Global_SetStateUIFromCpl(&m_pManualTest->m_oManuParas,oComplexUI[0],oComplexUI[1]);

	for(int nIndex = 0; nIndex < 3; nIndex++)
	{
		pTmt_GradientParas->m_uiVOL[2][nIndex].Harm[1].fAmp =
				m_pManualTest->m_oManuParas.m_uiVOL[nIndex].Harm[1].fAmp;
		pTmt_GradientParas->m_uiVOL[2][nIndex].Harm[1].fAngle =
				m_pManualTest->m_oManuParas.m_uiVOL[nIndex].Harm[1].fAngle;
		pTmt_GradientParas->m_uiCUR[2][nIndex].Harm[1].fAmp =
				m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fAmp;
		pTmt_GradientParas->m_uiCUR[2][nIndex].Harm[1].fAngle =
				m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fAngle;
	}
}

void CSttManuaImpedTest::ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType)
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
