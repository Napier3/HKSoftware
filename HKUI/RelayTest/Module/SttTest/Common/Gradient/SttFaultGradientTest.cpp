#include "stdafx.h"
#include "SttFaultGradientTest.h"
#include "../SttSystemConfig.h"
#include "../../../SttTestBase/SttFaultCalculatTool.h"

CString CSttFaultGradientTest::m_strMacroName = "递变试验(故障)";
CString CSttFaultGradientTest::m_strMacroID = STT_MACRO_ID_FaultGradientTest;
CString CSttFaultGradientTest::m_strFilePostFix = "sttGDT";
CString CSttFaultGradientTest::m_strMacroVer = "1.0";

CSttFaultGradientTest::CSttFaultGradientTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
}

void CSttFaultGradientTest::Init()
{
    CSttTestBase::Init();    
	m_oFaultGradientParas.init();
	m_oFaultResult.init();
	m_oGradientParas.init();
	m_oGradientParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
}

CSttFaultGradientTest::~CSttFaultGradientTest(void)
{

}

void CSttFaultGradientTest::AfterSetParameter()
{

}

double CSttFaultGradientTest::GetTestTimeLong()
{
    float	fTime = 0.000;
    return fTime;
}

long CSttFaultGradientTest::CalReport(UINT nState)
{
    return 0;
}

long CSttFaultGradientTest::SetParameter(DWORD dwState)
{
    return 0;
}

BOOL CSttFaultGradientTest::EventProcess()
{
    if(!GetTestStarting())
    {
        return FALSE;
    }

    BOOL bTestFinished = FALSE;
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->ProCommDrvResult(bTestFinished, m_oTestFinishedTime);
#endif
    return bTestFinished;
}

void CSttFaultGradientTest::StartTest()
{
    CSttTestBase::StartTest();

    if(!GetTestStarting())
    {
        TtmToDrv();
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
        SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->SetTestStart(GradientTest);
#endif
    }

	CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttFaultGradientTest::StartTest >>>>>>");
}

void CSttFaultGradientTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_

	if(m_oFaultGradientParas.m_fPrepareTime < EPSINON)
    {
        m_nCurStepIndex = 0;
    }

    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_Gradient_NeedStepsValue(&m_oGradientParas);
#endif
}

void CSttFaultGradientTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_faultGradientParas*)&m_oFaultGradientParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttFaultGradientTest::ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType)
{
#ifdef _PSX_QT_LINUX_
    STT_RTDATA_EVENT oRtdata;
    oRtdata.oTime.dTime = dTime1;
    oRtdata.oTime.dRealTime = dTime2;
    oRtdata.m_nVolChCount = 0;
    oRtdata.m_nCurChCount = 0;
	oRtdata.m_nHasFaultVolCur = 1;
    int nRtIndex = 0;
    float fVal;
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;

    if(nType == 0)
    {
		//开始实验,判断变化前和故障前时间
		if(m_oFaultGradientParas.m_fPrepareTime > 0.0001)
		{
			//变化前
			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				nRtIndex = oRtdata.m_nVolChCount;
				oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oVolCh[nRtIndex].m_fMag =
					m_oGradientParas.m_uiVOL[0][nIndex].Harm[1].fAmp;
				oRtdata.m_oVolCh[nRtIndex].m_fAng =
					m_oGradientParas.m_uiVOL[0][nIndex].Harm[1].fAngle;
				oRtdata.m_oVolCh[nRtIndex].m_fFreq =
					m_oGradientParas.m_uiVOL[0][nIndex].Harm[1].fFreq;
				oRtdata.m_nVolChCount++;
			}

			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				nRtIndex = oRtdata.m_nCurChCount;
				oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oCurCh[nRtIndex].m_fMag =
					m_oGradientParas.m_uiCUR[0][nIndex].Harm[1].fAmp;
				oRtdata.m_oCurCh[nRtIndex].m_fAng =
					m_oGradientParas.m_uiCUR[0][nIndex].Harm[1].fAngle;
				oRtdata.m_oCurCh[nRtIndex].m_fFreq =
					m_oGradientParas.m_uiCUR[0][nIndex].Harm[1].fFreq;
				oRtdata.m_nCurChCount++;
			}
		}
		else if(m_oFaultGradientParas.m_fPreFaultTime > 0.0001)
		{
			//故障前
			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				nRtIndex = oRtdata.m_nVolChCount;
				oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oVolCh[nRtIndex].m_fMag =
					m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAmp;
				oRtdata.m_oVolCh[nRtIndex].m_fAng =
					m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAngle;
				oRtdata.m_oVolCh[nRtIndex].m_fFreq =
					m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fFreq;
				oRtdata.m_nVolChCount++;
			}

			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				nRtIndex = oRtdata.m_nCurChCount;
				oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oCurCh[nRtIndex].m_fMag =
					m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAmp;
				oRtdata.m_oCurCh[nRtIndex].m_fAng =
					m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAngle;
				oRtdata.m_oCurCh[nRtIndex].m_fFreq =
					m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fFreq;
				oRtdata.m_nCurChCount++;
			}
		}
		else
		{
			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				fVal = fabs(pTmtGradientProcess->m_uiStepData[0].fU[nIndex][0]);
				nRtIndex = oRtdata.m_nVolChCount;
				oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oVolCh[nRtIndex].m_fMag = fVal;
				oRtdata.m_oVolCh[nRtIndex].m_fAng =
					pTmtGradientProcess->m_uiStepData[0].fU[nIndex][1];
				oRtdata.m_oVolCh[nRtIndex].m_fFreq =
					pTmtGradientProcess->m_uiStepData[0].fU[nIndex][2];
				oRtdata.m_nVolChCount++;
			}

			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				fVal = fabs(pTmtGradientProcess->m_uiStepData[0].fI[nIndex][0]);
				nRtIndex = oRtdata.m_nCurChCount;
				oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oCurCh[nRtIndex].m_fMag = fVal;
				oRtdata.m_oCurCh[nRtIndex].m_fAng =
					pTmtGradientProcess->m_uiStepData[0].fI[nIndex][1];
				oRtdata.m_oCurCh[nRtIndex].m_fFreq =
					pTmtGradientProcess->m_uiStepData[0].fI[nIndex][2];
				oRtdata.m_nCurChCount++;
			}
		}

		oRtdata.m_oFaultVolCh.m_fMag = pTmtGradientProcess->m_uiStepData[0].oStepFault.fVAmp;
		oRtdata.m_oFaultVolCh.m_fAng = pTmtGradientProcess->m_uiStepData[0].oStepFault.fAng;
		oRtdata.m_oFaultVolCh.m_fFreq = pTmtGradientProcess->m_uiStepData[0].oStepFault.fFre;

		oRtdata.m_oFaultCurCh.m_fMag = pTmtGradientProcess->m_uiStepData[0].oStepFault.fIAmp;
		oRtdata.m_oFaultCurCh.m_fAng = pTmtGradientProcess->m_uiStepData[0].oStepFault.fAng;
		oRtdata.m_oFaultCurCh.m_fFreq = pTmtGradientProcess->m_uiStepData[0].oStepFault.fFre;

		oRtdata.m_oFaultZCh.m_fMag = pTmtGradientProcess->m_uiStepData[0].oStepFault.fZ;
		oRtdata.m_oFaultZCh.m_fAng = pTmtGradientProcess->m_uiStepData[0].oStepFault.fZAng;
	}
    else
	{
		if((nStep <= pTmtGradientProcess->m_nStepCount) && (nStep < GRADIENT_MAX_COUNT))
        {
            if(nType == 2)
            {
                for(int nIndex = 0; nIndex < 3; nIndex++)
                {
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

				oRtdata.m_oFaultVolCh.m_fMag = pTmtGradientProcess->m_uiStepData[nStep].oStepFault.fVAmp;
				oRtdata.m_oFaultVolCh.m_fAng = pTmtGradientProcess->m_uiStepData[nStep].oStepFault.fAng;
				oRtdata.m_oFaultVolCh.m_fFreq = pTmtGradientProcess->m_uiStepData[nStep].oStepFault.fFre;

				oRtdata.m_oFaultCurCh.m_fMag = pTmtGradientProcess->m_uiStepData[nStep].oStepFault.fIAmp;
				oRtdata.m_oFaultCurCh.m_fAng = pTmtGradientProcess->m_uiStepData[nStep].oStepFault.fAng;
				oRtdata.m_oFaultCurCh.m_fFreq = pTmtGradientProcess->m_uiStepData[nStep].oStepFault.fFre;

				oRtdata.m_oFaultZCh.m_fMag = pTmtGradientProcess->m_uiStepData[nStep].oStepFault.fZ;
				oRtdata.m_oFaultZCh.m_fAng = pTmtGradientProcess->m_uiStepData[nStep].oStepFault.fZAng;
			}
            else
            {
                //故障前
                for(int nIndex = 0; nIndex < 3; nIndex++)
                {
                    nRtIndex = oRtdata.m_nVolChCount;
                    oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
					oRtdata.m_oVolCh[nRtIndex].m_fMag =
						m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAmp;
					oRtdata.m_oVolCh[nRtIndex].m_fAng =
						m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAngle;
					oRtdata.m_oVolCh[nRtIndex].m_fFreq =
						m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fFreq;
                    oRtdata.m_nVolChCount++;
                }

                for(int nIndex = 0; nIndex < 3; nIndex++)
                {
                    nRtIndex = oRtdata.m_nCurChCount;
                    oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
					oRtdata.m_oCurCh[nRtIndex].m_fMag =
						m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAmp;
					oRtdata.m_oCurCh[nRtIndex].m_fAng =
						m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAngle;
					oRtdata.m_oCurCh[nRtIndex].m_fFreq =
						m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fFreq;
					oRtdata.m_nCurChCount++;
                }

				oRtdata.m_oFaultVolCh.m_fMag = pTmtGradientProcess->m_uiStepData[0].oStepFault.fVAmp;
				oRtdata.m_oFaultVolCh.m_fAng = pTmtGradientProcess->m_uiStepData[0].oStepFault.fAng;
				oRtdata.m_oFaultVolCh.m_fFreq = pTmtGradientProcess->m_uiStepData[0].oStepFault.fFre;

				oRtdata.m_oFaultCurCh.m_fMag = pTmtGradientProcess->m_uiStepData[0].oStepFault.fIAmp;
				oRtdata.m_oFaultCurCh.m_fAng = pTmtGradientProcess->m_uiStepData[0].oStepFault.fAng;
				oRtdata.m_oFaultCurCh.m_fFreq = pTmtGradientProcess->m_uiStepData[0].oStepFault.fFre;

				oRtdata.m_oFaultZCh.m_fMag = pTmtGradientProcess->m_uiStepData[0].oStepFault.fZ;
				oRtdata.m_oFaultZCh.m_fAng = pTmtGradientProcess->m_uiStepData[0].oStepFault.fZAng;
			}
        }
    }

	UpdateMonitorCur(oRtdata);

    if(oRtdata.m_nCurChCount > 0 || oRtdata.m_nVolChCount > 0)
    {
        stt_add_rtdatas(oRtdata);
    }

#endif
}

void CSttFaultGradientTest::SyncGradientResult(int nStep, double dTime, int nTripType)
{
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
}

void CSttFaultGradientTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
	m_oFaultResult.m_fTripValue = oRampRestCom.m_fTripValue;
	m_oFaultResult.m_nAct = oRampRestCom.m_nAct;
	m_oFaultResult.m_fReturnValue = oRampRestCom.m_fReturnValue;
	m_oFaultResult.m_fReturnCoef = oRampRestCom.m_fReturnCoef;
	m_oFaultResult.m_fTripTime = oRampRestCom.m_fTripTime; //zhouhj 20211125 记录动作时间

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
		m_oFaultResult.m_fTripValueChl[i] = oRampRestCom.m_fTripValueChl[i];
    }

    SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

    for(int i = 0; i < oSwitchModules.m_nModulesBiCount; i++)
    {
		m_oFaultResult.m_fTripValueExChl[i] = oRampRestCom.m_fTripValueChlEx[i];
    }

#endif
	stt_xml_serialize(&m_oFaultResult,  pXmlSerialize);
}

void CSttFaultGradientTest::Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if(g_theSystemConfig->m_nHasDigital)
    {
        stt_xml_serialize(m_oGradientParas.m_oGoosePub, pXmlSerialize); //获取Gout信息
    }
}

void CSttFaultGradientTest::TranslateToStateParas()
{
	float fAngle[3] = {0, -120.0, 120.0};

	m_oGradientParas.m_fPrepareTime = m_oFaultGradientParas.m_fPrepareTime;
	m_oGradientParas.m_fPreFaultTime = m_oFaultGradientParas.m_fPreFaultTime;
	m_oGradientParas.m_fEDU = g_theSystemConfig->m_fVNom/SQRT3;

	m_oGradientParas.m_nTestMode = m_oFaultGradientParas.m_nTestMode;
	m_oGradientParas.m_fStepTime = m_oFaultGradientParas.m_fFaultTime;
	m_oGradientParas.m_fStart = m_oFaultGradientParas.m_fStart;
	m_oGradientParas.m_fStop = m_oFaultGradientParas.m_fStop;
	m_oGradientParas.m_fStep = m_oFaultGradientParas.m_fStep;

	m_oGradientParas.m_nBinLogic = m_oFaultGradientParas.m_nBinLogic;
	for(int j = 0; j < MAX_BINARYIN_COUNT; j++)
	{
		m_oGradientParas.m_binIn[j].nSelect =
			m_oFaultGradientParas.m_binIn[j].nSelect;
	}

	for(int j = 0; j < MAX_BINARYOUT_COUNT; j++)
	{
		for(int i = 0;i < 2;i++)
		{
			m_oGradientParas.m_binOut[i][j].nState =
				m_oFaultGradientParas.m_binOut[i][j].nState;
			m_oGradientParas.m_binOut[i][j].nMode =
				m_oFaultGradientParas.m_binOut[i][j].nMode;
		}
	}

	for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
	{
		m_oGradientParas.m_oGoosePub[nIndex].m_bUseFlag =
			m_oFaultGradientParas.m_oGoosePub[nIndex].m_bUseFlag;
		m_oGradientParas.m_oGoosePub[nIndex].m_bHasTest =
			m_oFaultGradientParas.m_oGoosePub[nIndex].m_bHasTest;
		m_oGradientParas.m_oGoosePub[nIndex].m_nTest =
			m_oFaultGradientParas.m_oGoosePub[nIndex].m_nTest;

		for(int nCh = 0; nCh < MAX_GOOSE_CHANNEL_COUNT; nCh++)
		{
			m_oGradientParas.m_oGoosePub[nIndex].m_strChannel[nCh] =
				m_oFaultGradientParas.m_oGoosePub[nIndex].m_strChannel[nCh];
		}
	}

	//////////////////////////////////////////////////////////////////////////
    tmt_channel *pCh_Vol, *pCh_Cur;
    //Prepare
    pCh_Vol = m_oGradientParas.m_uiVOL[0];
    pCh_Cur = m_oGradientParas.m_uiCUR[0];
	for(int i = 0;i < 4;i++)
	{
		pCh_Vol[i].Harm[1].fAmp = m_oGradientParas.m_fEDU;
		pCh_Vol[i].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
		pCh_Vol[i].Harm[1].fAngle = fAngle[i];
	}
	for(int i = 0;i < 3;i++)
	{
		pCh_Cur[i].Harm[1].fAmp = g_theSystemConfig->m_fINom;
		pCh_Cur[i].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
		pCh_Cur[i].Harm[1].fAngle = fAngle[i];
	}

    //Prefault
    pCh_Vol = m_oGradientParas.m_uiVOL[1];
    pCh_Cur = m_oGradientParas.m_uiCUR[1];
	for(int i = 0;i < 4;i++)
	{
		pCh_Vol[i].Harm[1].fAmp = m_oFaultGradientParas.m_fPreFaultEDU;
		pCh_Vol[i].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
		pCh_Vol[i].Harm[1].fAngle = fAngle[i];
	}
	for(int i = 0;i < 3;i++)
	{
		pCh_Cur[i].Harm[1].fAmp = m_oFaultGradientParas.m_fPreFaultEDI;
		pCh_Cur[i].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
		pCh_Cur[i].Harm[1].fAngle = fAngle[i] - m_oFaultGradientParas.m_fEDUaIaAngle;
	}

    //Fault
    pCh_Vol = m_oGradientParas.m_uiVOL[2];
    pCh_Cur = m_oGradientParas.m_uiCUR[2];
	for(int i = 0;i < 4;i++)
	{
		pCh_Vol[i].Harm[1].fAmp = m_oGradientParas.m_uiVOL[1][i].Harm[1].fAmp;
		pCh_Vol[i].Harm[1].fFreq = m_oGradientParas.m_uiVOL[1][i].Harm[1].fFreq;
		pCh_Vol[i].Harm[1].fAngle = m_oGradientParas.m_uiVOL[1][i].Harm[1].fAngle;
	}
	for(int i = 0;i < 3;i++)
	{
		pCh_Cur[i].Harm[1].fAmp = m_oGradientParas.m_uiCUR[1][i].Harm[1].fAmp;
		pCh_Cur[i].Harm[1].fFreq = m_oGradientParas.m_uiCUR[1][i].Harm[1].fFreq;
		pCh_Cur[i].Harm[1].fAngle = m_oGradientParas.m_uiCUR[1][i].Harm[1].fAngle;
	}

#ifdef _PSX_QT_LINUX_
    memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bUChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);
    memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bIChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);
#endif

    //保证故障所有通道刷新一遍    
	GradientAllChAndAllType();

    CalStepValue_Gradient(&m_oGradientParas, 1, 3);
    //////////////////////////////////////////////////////////////////////////
}

void CSttFaultGradientTest::GetFaultValue(tmt_StepUI *pUIStepData, float fCurValue)
{
	if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_ShortVM)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_ShortVA)
	{
		pUIStepData->oStepFault.fIAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_ImpedeAngle)
	{
		pUIStepData->oStepFault.fZAng = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_ShortImpede)
	{
		pUIStepData->oStepFault.fZ = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Frequency)
	{
		pUIStepData->oStepFault.fFre = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_PlusVM)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_MinusVM)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_ZeroVM)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Uab_c)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Ic_ab)
	{
		pUIStepData->oStepFault.fIAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Uab_Ic)
	{
		pUIStepData->oStepFault.fAng = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Ubc_a)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Ia_bc)
	{
		pUIStepData->oStepFault.fIAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Ubc_Ia)
	{
		pUIStepData->oStepFault.fAng = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Uca_b)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Ib_ca)
	{
		pUIStepData->oStepFault.fIAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Uca_Ib)
	{
		pUIStepData->oStepFault.fAng = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Uab_b)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Ib_ab)
	{
		pUIStepData->oStepFault.fIAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Uab_Ib)
	{
		pUIStepData->oStepFault.fAng = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Ubc_c)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Ic_bc)
	{
		pUIStepData->oStepFault.fIAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Ubc_Ic)
	{
		pUIStepData->oStepFault.fAng = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Uca_a)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Ia_ca)
	{
		pUIStepData->oStepFault.fIAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_Uca_Ia)
	{
		pUIStepData->oStepFault.fAng = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_VM)
	{
		pUIStepData->oStepFault.fVAmp = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_HZ)
	{
		pUIStepData->oStepFault.fFre = fCurValue;
	}
	else if(m_oFaultGradientParas.m_nChangeValue == FG_FM_Vaule_I2)
	{
		pUIStepData->oStepFault.fIAmp = fCurValue;
	}
}

void CSttFaultGradientTest::CalStepValue_Fault(tmt_channel *pCh_Vol, tmt_channel *pCh_Cur, float fCurValue)
{
	Complex p1,fVa,fVb,fVc,fIa,fIb,fIc;
	double fPhi,fV;

	fIa = p1.polar(0,0.0);
	fIb = p1.polar(0,0.0);
	fIc = p1.polar(0,0.0);
	fV = m_oFaultGradientParas.m_fShortVm;

	BOOL bFind = FALSE;
	switch(m_oFaultGradientParas.m_nChangeValue)
	{
	case FG_FM_Vaule_ShortImpede:
	{
		int nFaultMode = m_oFaultGradientParas.m_nFaultMode;
		switch(m_oFaultGradientParas.m_nFaultMode)
		{
		case FG_FaultMode_ABC:
		{
			bFind = TRUE;
			nFaultMode = 9;
		}
			break;
		case FG_FaultMode_A:
		{
			bFind = TRUE;
			nFaultMode = 0;
		}
			break;
		case FG_FaultMode_B:
		{
			bFind = TRUE;
			nFaultMode = 1;
		}
			break;
		case FG_FaultMode_C:
		{
			bFind = TRUE;
			nFaultMode = 2;
		}
			break;
		case FG_FaultMode_AB:
		{
			bFind = TRUE;
			nFaultMode = 3;
		}
			break;
		case FG_FaultMode_BC:
		{
			bFind = TRUE;
			nFaultMode = 4;
		}
			break;
		case FG_FaultMode_CA:
		{
			bFind = TRUE;
			nFaultMode = 5;
		}
			break;
		}

		if(bFind)
		{
			CSttFaultCalculatTool oFaultCalculatTool;
			float fVOutmax = 120.0f;//暂时默认最大输出电压120V
			float fIOutmax = 30.0f;//暂时默认最大输出电压30A
			float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
			int nPhaseRef[10]={1,2,0,2,0,1,2,0,1,0};
			float nAngle[10] = {0,-120,120,30,-120+30,120+30,30,-120+30,120+30,0};
			float fVFactor=1.0f,fIFactor=1.0f,fValueFactor = 1.0f;

			// if(g_theSystemConfig->m_nParaMode == 0)//如果参数设置为一次值
			// {
			// 	fValueFactor=1000.0;
			// 	fVFactor = g_theSystemConfig->m_fVPrimary[0]/g_theSystemConfig->m_fVSecondary[0];
			// 	fIFactor = g_theSystemConfig->m_fIPrimary[0]/g_theSystemConfig->m_fISecondary[0];
			// }

			double fIt = m_oFaultGradientParas.m_fShortVa/fIFactor;
			double fVt = m_oFaultGradientParas.m_fShortVm/fVFactor;

			Complex p2,p3;
			p3=p1.polar(0,0);
			oFaultCalculatTool.Calculat(1.0f,TRUE,TRUE,0,nFaultMode,
										nPhaseRef[nFaultMode],nAngle[nPhaseRef[nFaultMode]],
					fVOutmax/fVFactor,fStdLN_Vol/fVFactor,fIOutmax/fIFactor,
					&fIt,&fVt,
					p1.polar(0,0),
					p1.polar((double)fCurValue/fVFactor/fValueFactor*fIFactor,m_oFaultGradientParas.m_fAngle),
					p1.polar(p2.norm(p3),p2.arg(p3)),
					p1.polar(0,0),
					p1.polar(0,0),
					&fVa,&fVb,&fVc,&fIa,&fIb,&fIc);

			fVa = fVa*fVFactor;
			fVb = fVb*fVFactor;
			fVc = fVc*fVFactor;
			fIa = fIa*fIFactor;
			fIb = fIb*fIFactor;
			fIc = fIc*fIFactor;

			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[0].Harm[1].fAmp = (float)fIa.norm();
			pCh_Cur[0].Harm[1].fAngle = (float)fIa.arg();
			pCh_Cur[1].Harm[1].fAmp = (float)fIb.norm();
			pCh_Cur[1].Harm[1].fAngle = (float)fIb.arg();
			pCh_Cur[2].Harm[1].fAmp = (float)fIc.norm();
			pCh_Cur[2].Harm[1].fAngle = (float)fIc.arg();
		}
	}
		break;
	case FG_FM_Vaule_PlusVM:
	{
		switch(m_oFaultGradientParas.m_nFaultMode)
		{
		case FG_FaultMode_ABC:
		{
			bFind = TRUE;
		}
			break;
		case FG_FaultMode_A:
		{
			bFind = TRUE;
		}
			break;
		case FG_FaultMode_B:
		{
			bFind = TRUE;
		}
			break;
		case FG_FaultMode_C:
		{
			bFind = TRUE;
		}
			break;
		case FG_FaultMode_AB:
		{
			bFind = TRUE;
		}
			break;
		case FG_FaultMode_BC:
		{
			bFind = TRUE;
		}
			break;
		case FG_FaultMode_CA:
		{
			bFind = TRUE;
		}
			break;
		}

		if(bFind)
		{
			fVa = p1.polar(fCurValue,0.0);
			fVb = p1.polar(fCurValue,-120.0);
			fVc = p1.polar(fCurValue,120.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,-120.0-m_oFaultGradientParas.m_fAngle);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,120.0-m_oFaultGradientParas.m_fAngle);

			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[0].Harm[1].fAmp = (float)fIa.norm();
			pCh_Cur[0].Harm[1].fAngle = (float)fIa.arg();
			pCh_Cur[1].Harm[1].fAmp = (float)fIb.norm();
			pCh_Cur[1].Harm[1].fAngle = (float)fIb.arg();
			pCh_Cur[2].Harm[1].fAmp = (float)fIc.norm();
			pCh_Cur[2].Harm[1].fAngle = (float)fIc.arg();
		}
	}
		break;
	}

	bFind = FALSE;
	switch(m_oFaultGradientParas.m_nFaultMode)
	{
	case FG_FaultMode_A:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_ShortVM:
		{
			bFind = TRUE;
			fVa = p1.polar(fCurValue,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,120.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ShortVA:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Zero)
			{
				fV = m_oFaultGradientParas.m_fPreFaultEDU - m_oFaultGradientParas.m_fShortVm;
			}
			else
			{
				fV = m_oFaultGradientParas.m_fShortVm;
			}

			fVa = p1.polar(fV,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,120.0);
			fIa = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ImpedeAngle:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Zero)
			{
				fV = m_oFaultGradientParas.m_fPreFaultEDU - m_oFaultGradientParas.m_fShortVm;
			}
			else
			{
				fV = m_oFaultGradientParas.m_fShortVm;
			}

			fVa = p1.polar(fV,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,120.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
		}
			break;
		case FG_FM_Vaule_Frequency:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Zero)
			{
				fV = m_oFaultGradientParas.m_fPreFaultEDU - m_oFaultGradientParas.m_fShortVm;
			}
			else
			{
				fV = m_oFaultGradientParas.m_fShortVm;
			}

			fVa = p1.polar(fV,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,120.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			pCh_Vol[0].Harm[1].fFreq = fCurValue;
			pCh_Vol[1].Harm[1].fFreq = fCurValue;
			pCh_Vol[2].Harm[1].fFreq = fCurValue;
			pCh_Cur[0].Harm[1].fFreq = fCurValue;
			pCh_Cur[1].Harm[1].fFreq = fCurValue;
			pCh_Cur[2].Harm[1].fFreq = fCurValue;
		}
			break;
		case FG_FM_Vaule_ZeroVM:
		{
			bFind = TRUE;
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU - fCurValue,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,120.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[0].Harm[1].fAmp = (float)fIa.norm();
			pCh_Cur[0].Harm[1].fAngle = (float)fIa.arg();
		}
	}
		break;
	case FG_FaultMode_B:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_ShortVM:
		{
			bFind = TRUE;
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,0.0);
			fVb = p1.polar(fCurValue,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,120.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,-120.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ShortVA:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Zero)
			{
				fV = m_oFaultGradientParas.m_fPreFaultEDU - m_oFaultGradientParas.m_fShortVm;
			}
			else
			{
				fV = m_oFaultGradientParas.m_fShortVm;
			}

			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,0.0);
			fVb = p1.polar(fV,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,120.0);
			fIb = p1.polar(fCurValue,-120.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ImpedeAngle:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Zero)
			{
				fV = m_oFaultGradientParas.m_fPreFaultEDU - m_oFaultGradientParas.m_fShortVm;
			}
			else
			{
				fV = m_oFaultGradientParas.m_fShortVm;
			}

			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,0.0);
			fVb = p1.polar(fV,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,120.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,-120.0-fCurValue);
		}
			break;
		case FG_FM_Vaule_Frequency:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Zero)
			{
				fV = m_oFaultGradientParas.m_fPreFaultEDU - m_oFaultGradientParas.m_fShortVm;
			}
			else
			{
				fV = m_oFaultGradientParas.m_fShortVm;
			}

			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,0.0);
			fVb = p1.polar(fV,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,120.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,-120.0-m_oFaultGradientParas.m_fAngle);
			pCh_Vol[0].Harm[1].fFreq = fCurValue;
			pCh_Vol[1].Harm[1].fFreq = fCurValue;
			pCh_Vol[2].Harm[1].fFreq = fCurValue;
			pCh_Cur[0].Harm[1].fFreq = fCurValue;
			pCh_Cur[1].Harm[1].fFreq = fCurValue;
			pCh_Cur[2].Harm[1].fFreq = fCurValue;
		}
			break;
		case FG_FM_Vaule_ZeroVM:
		{
			bFind = TRUE;
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU - fCurValue,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,120.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,-120.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[1].Harm[1].fAmp = (float)fIb.norm();
			pCh_Cur[1].Harm[1].fAngle = (float)fIb.arg();
		}
	}
		break;
	case FG_FaultMode_C:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_ShortVM:
		{
			bFind = TRUE;
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,-120.0);
			fVc = p1.polar(fCurValue,120.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,120.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ShortVA:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Zero)
			{
				fV = m_oFaultGradientParas.m_fPreFaultEDU - m_oFaultGradientParas.m_fShortVm;
			}
			else
			{
				fV = m_oFaultGradientParas.m_fShortVm;
			}

			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,-120.0);
			fVc = p1.polar(fV,120.0);
			fIc = p1.polar(fCurValue,120.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ImpedeAngle:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Zero)
			{
				fV = m_oFaultGradientParas.m_fPreFaultEDU - m_oFaultGradientParas.m_fShortVm;
			}
			else
			{
				fV = m_oFaultGradientParas.m_fShortVm;
			}

			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,-120.0);
			fVc = p1.polar(fV,120.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,120.0-fCurValue);
		}
			break;
		case FG_FM_Vaule_Frequency:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Zero)
			{
				fV = m_oFaultGradientParas.m_fPreFaultEDU - m_oFaultGradientParas.m_fShortVm;
			}
			else
			{
				fV = m_oFaultGradientParas.m_fShortVm;
			}

			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,-120.0);
			fVc = p1.polar(fV,120.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,120.0-m_oFaultGradientParas.m_fAngle);
			pCh_Vol[0].Harm[1].fFreq = fCurValue;
			pCh_Vol[1].Harm[1].fFreq = fCurValue;
			pCh_Vol[2].Harm[1].fFreq = fCurValue;
			pCh_Cur[0].Harm[1].fFreq = fCurValue;
			pCh_Cur[1].Harm[1].fFreq = fCurValue;
			pCh_Cur[2].Harm[1].fFreq = fCurValue;
		}
			break;
		case FG_FM_Vaule_ZeroVM:
		{
			bFind = TRUE;
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU - fCurValue,120.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,120.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[2].Harm[1].fAmp = (float)fIc.norm();
			pCh_Cur[2].Harm[1].fAngle = (float)fIc.arg();
		}
	}
		break;
	case FG_FaultMode_ABC:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_ShortVM:
		{
			bFind = TRUE;
			fVa = p1.polar(fCurValue,0.0);
			fVb = p1.polar(fCurValue,-120.0);
			fVc = p1.polar(fCurValue,120.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,-120.0-m_oFaultGradientParas.m_fAngle);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,120.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ShortVA:
		{
			bFind = TRUE;
			fVa = p1.polar(m_oFaultGradientParas.m_fShortVm,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fShortVm,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fShortVm,120.0);
			fIa = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
			fIb = p1.polar(fCurValue,-120.0-m_oFaultGradientParas.m_fAngle);
			fIc = p1.polar(fCurValue,120.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ImpedeAngle:
		{
			bFind = TRUE;
			fVa = p1.polar(m_oFaultGradientParas.m_fShortVm,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fShortVm,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fShortVm,120.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,-120.0-fCurValue);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,120.0-fCurValue);
		}
			break;
		case FG_FM_Vaule_Frequency:
		{
			bFind = TRUE;
			fVa = p1.polar(m_oFaultGradientParas.m_fShortVm,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fShortVm,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fShortVm,120.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,-120.0-m_oFaultGradientParas.m_fAngle);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,120.0-m_oFaultGradientParas.m_fAngle);

			pCh_Vol[0].Harm[1].fFreq = fCurValue;
			pCh_Vol[1].Harm[1].fFreq = fCurValue;
			pCh_Vol[2].Harm[1].fFreq = fCurValue;
			pCh_Cur[0].Harm[1].fFreq = fCurValue;
			pCh_Cur[1].Harm[1].fFreq = fCurValue;
			pCh_Cur[2].Harm[1].fFreq = fCurValue;
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[0].Harm[1].fAmp = (float)fIa.norm();
			pCh_Cur[0].Harm[1].fAngle = (float)fIa.arg();
			pCh_Cur[1].Harm[1].fAmp = (float)fIb.norm();
			pCh_Cur[1].Harm[1].fAngle = (float)fIb.arg();
			pCh_Cur[2].Harm[1].fAmp = (float)fIc.norm();
			pCh_Cur[2].Harm[1].fAngle = (float)fIc.arg();
		}
	}
		break;
	case FG_FaultMode_AB:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_ShortVM:
		{
			bFind = TRUE;
            fPhi = fabs(atan2(fCurValue,m_oFaultGradientParas.m_fPreFaultEDU))*180.0/XPI;
            fVa = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ShortVA:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Minus)
			{
                fPhi = atan2(3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm,sqrt(3.0)*m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = (3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm)/sqrt(3.0);
			}
			else
			{
                fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = m_oFaultGradientParas.m_fShortVm;
			}

            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
			fIb = p1.polar(fCurValue,180.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ImpedeAngle:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Minus)
			{
                fPhi = atan2(3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm,sqrt(3.0)*m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = (3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm)/sqrt(3.0);
			}
			else
			{
                fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = m_oFaultGradientParas.m_fShortVm;
			}

            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-fCurValue);
		}
			break;
		case FG_FM_Vaule_Frequency:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Minus)
			{
                fPhi = atan2(3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm,sqrt(3.0)*m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = (3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm)/sqrt(3.0);
			}
			else
			{
                fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = m_oFaultGradientParas.m_fShortVm;
			}

            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-m_oFaultGradientParas.m_fAngle);

			pCh_Vol[0].Harm[1].fFreq = fCurValue;
			pCh_Vol[1].Harm[1].fFreq = fCurValue;
			pCh_Vol[2].Harm[1].fFreq = fCurValue;
			pCh_Cur[0].Harm[1].fFreq = fCurValue;
			pCh_Cur[1].Harm[1].fFreq = fCurValue;
			pCh_Cur[2].Harm[1].fFreq = fCurValue;
		}
			break;
		case FG_FM_Vaule_MinusVM:
		{
			bFind = TRUE;
            fPhi = atan2(3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*fCurValue,sqrt(3.0)*m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = (3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*fCurValue)/sqrt(3.0);
            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[0].Harm[1].fAmp = (float)fIa.norm();
			pCh_Cur[0].Harm[1].fAngle = (float)fIa.arg();
			pCh_Cur[1].Harm[1].fAmp = (float)fIb.norm();
			pCh_Cur[1].Harm[1].fAngle = (float)fIb.arg();
		}
	}
		break;
	case FG_FaultMode_BC:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_ShortVM:
		{
			bFind = TRUE;
            fPhi = fabs(atan2(fCurValue,m_oFaultGradientParas.m_fPreFaultEDU))*180.0/XPI;
            fVb = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ShortVA:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Minus)
			{
                fPhi = atan2(3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm,sqrt(3.0)*m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = (3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm)/sqrt(3.0);
			}
			else
			{
                fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = m_oFaultGradientParas.m_fShortVm;
			}

            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
			fIc = p1.polar(fCurValue,180.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ImpedeAngle:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-fCurValue);
		}
			break;
		case FG_FM_Vaule_Frequency:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Minus)
			{
                fPhi = atan2(3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm,sqrt(3.0)*m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = (3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm)/sqrt(3.0);
			}
			else
			{
                fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = m_oFaultGradientParas.m_fShortVm;
			}

            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-m_oFaultGradientParas.m_fAngle);

			pCh_Vol[0].Harm[1].fFreq = fCurValue;
			pCh_Vol[1].Harm[1].fFreq = fCurValue;
			pCh_Vol[2].Harm[1].fFreq = fCurValue;
			pCh_Cur[0].Harm[1].fFreq = fCurValue;
			pCh_Cur[1].Harm[1].fFreq = fCurValue;
			pCh_Cur[2].Harm[1].fFreq = fCurValue;
		}
			break;
		case FG_FM_Vaule_MinusVM:
		{
			bFind = TRUE;
            fPhi = atan2(3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*fCurValue,sqrt(3.0)*m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = (3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*fCurValue)/sqrt(3.0);
            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[1].Harm[1].fAmp = (float)fIb.norm();
			pCh_Cur[1].Harm[1].fAngle = (float)fIb.arg();
			pCh_Cur[2].Harm[1].fAmp = (float)fIc.norm();
			pCh_Cur[2].Harm[1].fAngle = (float)fIc.arg();
		}
	}
		break;
	case FG_FaultMode_CA:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_ShortVM:
		{
			bFind = TRUE;
            fPhi = fabs(atan2(fCurValue,m_oFaultGradientParas.m_fPreFaultEDU))*180.0/XPI;
            fVc = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ShortVA:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Minus)
			{
                fPhi = atan2(3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm,sqrt(3.0)*m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = (3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm)/sqrt(3.0);
			}
			else
			{
                fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = m_oFaultGradientParas.m_fShortVm;
			}

            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
			fIa = p1.polar(fCurValue,180.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_ImpedeAngle:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-fCurValue);
		}
			break;
		case FG_FM_Vaule_Frequency:
		{
			bFind = TRUE;
			if(m_oFaultGradientParas.m_nShortVmType == FG_Type_VM_Minus)
			{
                fPhi = atan2(3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm,sqrt(3.0)*m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = (3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*m_oFaultGradientParas.m_fShortVm)/sqrt(3.0);
			}
			else
			{
                fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
				fV = m_oFaultGradientParas.m_fShortVm;
			}

            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-m_oFaultGradientParas.m_fAngle);

			pCh_Vol[0].Harm[1].fFreq = fCurValue;
			pCh_Vol[1].Harm[1].fFreq = fCurValue;
			pCh_Vol[2].Harm[1].fFreq = fCurValue;
			pCh_Cur[0].Harm[1].fFreq = fCurValue;
			pCh_Cur[1].Harm[1].fFreq = fCurValue;
			pCh_Cur[2].Harm[1].fFreq = fCurValue;
		}
			break;
		case FG_FM_Vaule_MinusVM:
		{
			bFind = TRUE;
            fPhi = atan2(3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*fCurValue,sqrt(3.0)*m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = (3.0*m_oFaultGradientParas.m_fPreFaultEDU - 6.0*fCurValue)/sqrt(3.0);
            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,180.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[0].Harm[1].fAmp = (float)fIa.norm();
			pCh_Cur[0].Harm[1].fAngle = (float)fIa.arg();
			pCh_Cur[2].Harm[1].fAmp = (float)fIc.norm();
			pCh_Cur[2].Harm[1].fAngle = (float)fIc.arg();
		}
	}
		break;
	case FG_FaultMode_AB_C:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_Uab_c:
		{
			bFind = TRUE;
            fPhi = fabs(atan2(fCurValue,m_oFaultGradientParas.m_fPreFaultEDU))*180.0/XPI;
            fVa = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Ic_ab:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Uab_Ic:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[2].Harm[1].fAmp = (float)fIc.norm();
			pCh_Cur[2].Harm[1].fAngle = (float)fIc.arg();
		}
	}
		break;
	case FG_FaultMode_BC_A:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_Ubc_a:
		{
			bFind = TRUE;
            fPhi = fabs(atan2(fCurValue,m_oFaultGradientParas.m_fPreFaultEDU))*180.0/XPI;
            fVb = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Ia_bc:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Ubc_Ia:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[0].Harm[1].fAmp = (float)fIa.norm();
			pCh_Cur[0].Harm[1].fAngle = (float)fIa.arg();
		}
	}
		break;
	case FG_FaultMode_CA_B:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_Uca_b:
		{
			bFind = TRUE;
            fPhi = fabs(atan2(fCurValue,m_oFaultGradientParas.m_fPreFaultEDU))*180.0/XPI;
            fVc = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Ib_ca:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Uca_Ib:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
		}
	}
		break;
	case FG_FaultMode_AB_B:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_Uab_b:
		{
			bFind = TRUE;
            fPhi = fabs(atan2(fCurValue,m_oFaultGradientParas.m_fPreFaultEDU))*180.0/XPI;
            fVa = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Ib_ab:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Uab_Ib:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVc = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[1].Harm[1].fAmp = (float)fIb.norm();
			pCh_Cur[1].Harm[1].fAngle = (float)fIb.arg();
		}
	}
		break;
	case FG_FaultMode_BC_C:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_Ubc_c:
		{
			bFind = TRUE;
            fPhi = fabs(atan2(fCurValue,m_oFaultGradientParas.m_fPreFaultEDU))*180.0/XPI;
            fVb = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Ic_bc:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Ubc_Ic:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVb = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVa = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[2].Harm[1].fAmp = (float)fIc.norm();
			pCh_Cur[2].Harm[1].fAngle = (float)fIc.arg();
		}
	}
		break;
	case FG_FaultMode_CA_A:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_Uca_a:
		{
			bFind = TRUE;
            fPhi = fabs(atan2(fCurValue,m_oFaultGradientParas.m_fPreFaultEDU))*180.0/XPI;
            fVc = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fCurValue/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Ia_ca:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);
		}
			break;
		case FG_FM_Vaule_Uca_Ia:
		{
			bFind = TRUE;
            fPhi = atan2(m_oFaultGradientParas.m_fShortVm,m_oFaultGradientParas.m_fPreFaultEDU)*180.0/XPI;
			fV = m_oFaultGradientParas.m_fShortVm;

            fVc = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
            fVa = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
			fVb = p1.polar(m_oFaultGradientParas.m_fPreFaultEDU,90.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-fCurValue);
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[0].Harm[1].fAmp = (float)fIa.norm();
			pCh_Cur[0].Harm[1].fAngle = (float)fIa.arg();
		}
	}
		break;
	case FG_FaultMode_UF:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_VM:
		{
			bFind = TRUE;
			fVa = p1.polar(fCurValue,0.0);
			fVb = p1.polar(fCurValue,-120.0);
			fVc = p1.polar(fCurValue,120.0);
			fIa = p1.polar(0.0,0.0);
			fIb = p1.polar(0.0,0.0);
			fIc = p1.polar(0.0,0.0);
		}
			break;
		case FG_FM_Vaule_HZ:
		{
			bFind = TRUE;
			fVa = p1.polar(m_oFaultGradientParas.m_fShortVm,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fShortVm,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fShortVm,120.0);
			fIa = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fIb = p1.polar(m_oFaultGradientParas.m_fShortVa,-120.0-m_oFaultGradientParas.m_fAngle);
			fIc = p1.polar(m_oFaultGradientParas.m_fShortVa,120.0-m_oFaultGradientParas.m_fAngle);

			pCh_Vol[0].Harm[1].fFreq = fCurValue;
			pCh_Vol[1].Harm[1].fFreq = fCurValue;
			pCh_Vol[2].Harm[1].fFreq = fCurValue;
			pCh_Cur[0].Harm[1].fFreq = fCurValue;
			pCh_Cur[1].Harm[1].fFreq = fCurValue;
			pCh_Cur[2].Harm[1].fFreq = fCurValue;
		}
			break;
		}

		if(bFind)
		{
			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[0].Harm[1].fAmp = (float)fIa.norm();
			pCh_Cur[0].Harm[1].fAngle = (float)fIa.arg();
			pCh_Cur[1].Harm[1].fAmp = (float)fIb.norm();
			pCh_Cur[1].Harm[1].fAngle = (float)fIb.arg();
			pCh_Cur[2].Harm[1].fAmp = (float)fIc.norm();
			pCh_Cur[2].Harm[1].fAngle = (float)fIc.arg();
		}
	}
		break;
	case FG_FaultMode_I2I1:
	{
		switch(m_oFaultGradientParas.m_nChangeValue)
		{
		case FG_FM_Vaule_I2:
		{
			bFind = TRUE;
		}
			break;
		}

		if(bFind)
		{
			fVa = p1.polar(m_oFaultGradientParas.m_fShortVm,0.0);
			fVb = p1.polar(m_oFaultGradientParas.m_fShortVm,-120.0);
			fVc = p1.polar(m_oFaultGradientParas.m_fShortVm,120.0);

			Complex fI1,fI2,p2,p3;
			p2 = p1.polar(1.0,-120.0);
			p3 = p1.polar(1.0,120.0);
			fI1 = p1.polar(m_oFaultGradientParas.m_fShortVa,0.0-m_oFaultGradientParas.m_fAngle);
			fI2 = p1.polar(fCurValue,0.0-m_oFaultGradientParas.m_fAngle);

			fIa = fI1 + fI2;
			fIb = fI1*p2 + fI2*p3;
			fIc = fI1*p3 + fI2*p2;

			pCh_Vol[0].Harm[1].fAmp = (float)fVa.norm();
			pCh_Vol[0].Harm[1].fAngle = (float)fVa.arg();
			pCh_Vol[1].Harm[1].fAmp = (float)fVb.norm();
			pCh_Vol[1].Harm[1].fAngle = (float)fVb.arg();
			pCh_Vol[2].Harm[1].fAmp = (float)fVc.norm();
			pCh_Vol[2].Harm[1].fAngle = (float)fVc.arg();
			pCh_Cur[0].Harm[1].fAmp = (float)fIa.norm();
			pCh_Cur[0].Harm[1].fAngle = (float)fIa.arg();
			pCh_Cur[1].Harm[1].fAmp = (float)fIb.norm();
			pCh_Cur[1].Harm[1].fAngle = (float)fIb.arg();
			pCh_Cur[2].Harm[1].fAmp = (float)fIc.norm();
			pCh_Cur[2].Harm[1].fAngle = (float)fIc.arg();
		}
	}
		break;
	}
}

void CSttFaultGradientTest::CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex)
{
    tmt_channel *pCh_Vol = m_oGradientParas.m_uiVOL[2];
    tmt_channel *pCh_Cur = m_oGradientParas.m_uiCUR[2];
	for(int i = 0;i < 3;i++)
	{
		pTmt_GradientParas->m_uiVOL[2][i].Harm[1].fAmp = pCh_Vol[i].Harm[1].fAmp;
		pTmt_GradientParas->m_uiVOL[2][i].Harm[1].fAngle = pCh_Vol[i].Harm[1].fAngle;
		pTmt_GradientParas->m_uiVOL[2][i].Harm[1].fFreq = pCh_Vol[i].Harm[1].fFreq;

		pTmt_GradientParas->m_uiCUR[2][i].Harm[1].fAmp = pCh_Cur[i].Harm[1].fAmp;
		pTmt_GradientParas->m_uiCUR[2][i].Harm[1].fAngle = pCh_Cur[i].Harm[1].fAngle;
		pTmt_GradientParas->m_uiCUR[2][i].Harm[1].fFreq = pCh_Cur[i].Harm[1].fFreq;
	}

	CalStepValue_Fault(pTmt_GradientParas->m_uiVOL[2], pTmt_GradientParas->m_uiCUR[2], fCurValue);
}
