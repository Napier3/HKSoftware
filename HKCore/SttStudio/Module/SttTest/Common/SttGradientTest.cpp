#include "stdafx.h"
#include"SttGradientTest.h"
#include "SttSystemConfig.h"

CString CSttGradientTest::m_strMacroName = "递变测试";
CString CSttGradientTest::m_strMacroID = STT_MACRO_ID_GradientTest;
CString CSttGradientTest::m_strFilePostFix = "sttGDT";
CString CSttGradientTest::m_strMacroVer ="1.0";

CSttGradientTest::CSttGradientTest()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
}

void CSttGradientTest::Init()
{ 
    CSttTestBase::Init();
    m_oGradientParas.init();
	m_oGradientParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
    m_oResultParas.init();
    m_fAngleF = 0;
    m_fAngleS = 0;
    m_fMaxAngle = 0;
}

long CSttGradientTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    return true;
}

CSttGradientTest::~CSttGradientTest(void)
{
}

float CSttGradientTest::GetStdAngle(float fCurAngle)
{
    float fStart2 = fCurAngle;

    while((fStart2>=360)||(fStart2<0))
    {
        if(fStart2>=360)
        {
            fStart2-=360;
        }
        else
        {
            fStart2 += 360;
        }
    }

    return fStart2;
}

void CSttGradientTest::AngleTestTransPara(BOOL bCCW)
{
    if(m_oGradientParas.m_nType!=GRADIENT_ANG)
        return;

    float fStart=m_oGradientParas.m_fStart;
    float fEnd=m_oGradientParas.m_fStop;

    float fStart2=fStart;
    float fEnd2=fEnd;
    //将角度转换成0-359范围
    fStart2 = GetStdAngle(fStart);
    fEnd2 = GetStdAngle(fEnd);

    m_oGradientParas.m_fStart=fStart2;
    if(bCCW)
    {
        //遵循逆时针
        if(fStart2 > fEnd2)
            fEnd2 += 360;
        m_oGradientParas.m_fStop=fEnd2;
    }
    else
    {
        if(fStart2 < fEnd2)
            fEnd2 -= 360;
        m_oGradientParas.m_fStop=fEnd2;
    }
}

void CSttGradientTest::AfterSetParameter()
{
    if(m_oGradientParas.m_nPhaseGradDir == 0)
        AngleTestTransPara();
    else
        AngleTestTransPara(FALSE);

#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->InitParaBeforeGradient(m_oGradientParas);
    CSttDeviceBase::g_pSttDeviceBase->SetChannelSelect(m_oGradientParas);
    CSttDeviceBase::g_pSttDeviceBase->CalStepValue_Gradient(m_oGradientParas);
#endif
}

double CSttGradientTest::GetTestTimeLong()
{
    float	fTime = 0.000;

    return fTime;
}

long CSttGradientTest::CalReport(UINT nState)
{
    return 0;
}

long CSttGradientTest::SetParameter(DWORD dwState)
{
    return 0;
}

BOOL CSttGradientTest::EventProcess()
{
    if(!GetTestStarting())
        return FALSE;

    BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->ProCommDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
    return bTestFinished;
}

void CSttGradientTest::StartTest()
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
    CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttGradientTest::StartTest >>>>>>");
}

void CSttGradientTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    if(m_oGradientParas.m_fPrepareTime<EPSINON)
    {
        m_nCurStepIndex=0;
    }
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_Gradient(&m_oGradientParas);
#endif
}

void CSttGradientTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    m_oGradientParas.m_fEDU = g_theSystemConfig->m_fVNom/SQRT3;
    m_oGradientParas.m_fEDFreq = g_theSystemConfig->m_fFNom;
#endif

    m_oGradientParas.m_fG1Volt=m_oGradientParas.m_fEDU;
    m_oGradientParas.m_fG2Volt=m_oGradientParas.m_fEDU;

	m_oGradientParas.m_nChannel2 = Null;
    stt_xml_serialize(&m_oGradientParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

void CSttGradientTest::ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType)
{
#ifdef _PSX_QT_LINUX_
    STT_RTDATA_EVENT oRtdata;
    oRtdata.oTime.dTime=dTime1;
    oRtdata.oTime.dRealTime=dTime2;
    oRtdata.m_nVolChCount=0;
    oRtdata.m_nCurChCount=0;
	oRtdata.m_nHasFaultVolCur=0;

    tmt_GradientParas &oGradientParas=CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;
    if(nStep <= oGradientParas.m_nStepCnt)
    {
        ProGradientRtDatasEvent(oRtdata,nStep,nType);
    }

    if(oRtdata.m_nCurChCount>0||oRtdata.m_nVolChCount>0)
        stt_add_rtdatas(oRtdata);
#endif
}

void CSttGradientTest::ProRtDatasEvent_FixSteps(double dTime1,double dTime2,int nStep,int nType)
{
#ifdef _PSX_QT_LINUX_
    STT_RTDATA_EVENT oRtdata;
    oRtdata.oTime.dTime=dTime1;
    oRtdata.oTime.dRealTime=dTime2;
    oRtdata.m_nVolChCount=0;
    oRtdata.m_nCurChCount=0;
	oRtdata.m_nHasFaultVolCur=0;
    float fVal = 0.0f;
    int nRtIndex=0;
    tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
    long nActStepIndex = 0;//zhouhj 20211021 兼容正反向的StepIndex

    if(nType == 0)
    {
        //测试前额定数据
        for(int nIndex=0;nIndex<3;nIndex++)
        {
            fVal=fabs(m_oGradientParas.m_uiVOL[0][nIndex].Harm[1].fAmp);

            nRtIndex=oRtdata.m_nVolChCount;
            oRtdata.m_oVolCh[nRtIndex].m_nIndex=nIndex;
			oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
			oRtdata.m_oVolCh[nRtIndex].m_fAng=
					m_oGradientParas.m_uiVOL[0][nIndex].Harm[1].fAngle;
			oRtdata.m_oVolCh[nRtIndex].m_fFreq=
					m_oGradientParas.m_uiVOL[0][nIndex].Harm[1].fFreq;
            oRtdata.m_nVolChCount++;
        }

        for(int nIndex=0;nIndex<3;nIndex++)
        {
            fVal=fabs(m_oGradientParas.m_uiCUR[0][nIndex].Harm[1].fAmp);
            nRtIndex=oRtdata.m_nCurChCount;
            oRtdata.m_oCurCh[nRtIndex].m_nIndex=nIndex;
			oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
			oRtdata.m_oCurCh[nRtIndex].m_fAng=
					m_oGradientParas.m_uiCUR[0][nIndex].Harm[1].fAngle;
			oRtdata.m_oCurCh[nRtIndex].m_fFreq=
					m_oGradientParas.m_uiCUR[0][nIndex].Harm[1].fFreq;
            oRtdata.m_nCurChCount++;
        }
    }
    else if((nStep < pTmtGradientProcess->m_nStepCount)&&(nStep<GRADIENT_MAX_COUNT))
    {
        if(nType == 2)
        {
            if (pTmtGradientProcess->m_nDiretionMode == 0)//正向搜索
            {
                nActStepIndex = nStep;
            }
            else//否则反向搜索
            {
                nActStepIndex = pTmtGradientProcess->m_nStepCount -1 - nStep;
            }

            for(int nIndex=0;nIndex<3;nIndex++)
            {
                fVal=fabs(pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[nIndex][0]);
                nRtIndex=oRtdata.m_nVolChCount;
                oRtdata.m_oVolCh[nRtIndex].m_nIndex=nIndex;
				oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oVolCh[nRtIndex].m_fAng=
						pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[nIndex][1];
				oRtdata.m_oVolCh[nRtIndex].m_fFreq=
						pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[nIndex][2];
                oRtdata.m_nVolChCount++;

                fVal=fabs(pTmtGradientProcess->m_uiStepData[nActStepIndex].fI[nIndex][0]);
                nRtIndex=oRtdata.m_nCurChCount;
                oRtdata.m_oCurCh[nRtIndex].m_nIndex=nIndex;
				oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oCurCh[nRtIndex].m_fAng=
						pTmtGradientProcess->m_uiStepData[nActStepIndex].fI[nIndex][1];
				oRtdata.m_oCurCh[nRtIndex].m_fFreq=
						pTmtGradientProcess->m_uiStepData[nActStepIndex].fI[nIndex][2];
                oRtdata.m_nCurChCount++;

            }
        }
        else
        {
            //故障前
            for(int nIndex=0;nIndex<g_nRtDataVoltCnt;nIndex++)
            {
                nRtIndex=oRtdata.m_nVolChCount;
                oRtdata.m_oVolCh[nRtIndex].m_nIndex=nIndex;

                fVal=m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAmp;
				oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oVolCh[nRtIndex].m_fAng=
						m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAngle;
				oRtdata.m_oVolCh[nRtIndex].m_fFreq=
						m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fFreq;
                oRtdata.m_nVolChCount++;
            }

            for(int nIndex=0;nIndex<g_nRtDataCurrCnt;nIndex++)
            {
                nRtIndex=oRtdata.m_nCurChCount;
                oRtdata.m_oCurCh[nRtIndex].m_nIndex=nIndex;

                fVal=m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAmp;
				oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oCurCh[nRtIndex].m_fAng=
						m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAngle;
				oRtdata.m_oCurCh[nRtIndex].m_fFreq=
						m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fFreq;
                oRtdata.m_nCurChCount++;

            }
        }
    }

    if(oRtdata.m_nCurChCount>0||oRtdata.m_nVolChCount>0)
        stt_add_rtdatas(oRtdata);
#endif
}

void CSttGradientTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    long nCoef = 1;

    if (((m_oGradientParas.m_nChannel == I1abcAdd)||(m_oGradientParas.m_nChannel == I2abcAdd))&&(m_oGradientParas.m_nType == GRADIENT_AMP))//zhouhj 20211025 并联输出的时候,动作值需要乘以3
    {
        nCoef *= 3;
    }

    GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    m_oResultParas.m_fTripValue=oRampRestCom.m_fTripValue*nCoef;
    m_oResultParas.m_nAct=oRampRestCom.m_nAct;
    m_oResultParas.m_fReturnValue=oRampRestCom.m_fReturnValue*nCoef;
    m_oResultParas.m_fReturnCoef=oRampRestCom.m_fReturnCoef;
    m_oResultParas.m_fPhiAngleValue=oRampRestCom.m_fPhiAngleValue;
    m_oResultParas.m_oMaxAngle.m_fAngleF=m_fAngleF;
    m_oResultParas.m_oMaxAngle.m_fAngleS=m_fAngleS;
    m_oResultParas.m_oMaxAngle.m_fMaxAngle=m_fMaxAngle;
    m_oResultParas.m_fTripTime=oRampRestCom.m_fTripTime;//zhouhj 20211125 记录动作时间

    for(int i=0; i<MAX_BINARYIN_COUNT; i++)
    {
        m_oResultParas.m_fTripValueChl[i] = nCoef*oRampRestCom.m_fTripValueChl[i];
    }

    SwitchModules oSwitchModules=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
    for(int i=0; i<oSwitchModules.m_nModulesBiCount; i++)
    {
        m_oResultParas.m_fTripValueExChl[i] = nCoef*oRampRestCom.m_fTripValueChlEx[i];
    }
#endif

    stt_xml_serialize(&m_oResultParas,  pXmlSerialize);
}

void CSttGradientTest::Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if (g_theSystemConfig->m_nHasDigital)
    {
        stt_xml_serialize(m_oGradientParas.m_oGoosePub,pXmlSerialize);//获取Gout信息
    }
}

void CSttGradientTest::InitBeforeFaultParas_BySequenceSet(tmt_GradientParas *pTmt_GradientParas)
{
	float fAngleVoltage[6] = {0, -120.0, 120.0, 0, -120.0, 120.0};//20220719 zhouhj 增加电压电流相序设置功能
	float fAngleCurrent[6] = {0, -120.0, 120.0, 0, -120.0, 120.0};

	if (pTmt_GradientParas->m_nPhaseSet[0] == 1)//电压相序负序
	{
		fAngleVoltage[1] = 120.0f;
		fAngleVoltage[2] = -120.0f;
		fAngleVoltage[4] = 120.0f;
		fAngleVoltage[5] = -120.0f;
	}
	else if (pTmt_GradientParas->m_nPhaseSet[0] == 2)//电压相序零序
	{
		fAngleVoltage[1] = 0.0f;
		fAngleVoltage[2] = 0.0f;
		fAngleVoltage[4] = 0.0f;
		fAngleVoltage[5] = 0.0f;
	}

	if (pTmt_GradientParas->m_nPhaseSet[1] == 1)//电流相序负序
	{
		fAngleCurrent[1] = 120.0f;
		fAngleCurrent[2] = -120.0f;
		fAngleCurrent[4] = 120.0f;
		fAngleCurrent[5] = -120.0f;
	}
	else if (pTmt_GradientParas->m_nPhaseSet[1] == 2)//电流相序零序
	{
		fAngleCurrent[1] = 0.0f;
		fAngleCurrent[2] = 0.0f;
		fAngleCurrent[4] = 0.0f;
		fAngleCurrent[5] = 0.0f;
	}

	for(int i=3;i<6;i++)//6I电流差动使用
	{
		fAngleVoltage[i] = fAngleVoltage[i] - pTmt_GradientParas->m_fDiffIAngle;
		fAngleCurrent[i] = fAngleCurrent[i] - pTmt_GradientParas->m_fDiffIAngle;
	}

	//变化前,额定
	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		pTmt_GradientParas->m_uiVOL[0][i].Harm[0].fAmp=0;
		pTmt_GradientParas->m_uiVOL[0][i].Harm[1].fAmp=pTmt_GradientParas->m_fEDU;
		pTmt_GradientParas->m_uiVOL[0][i].Harm[1].fFreq=pTmt_GradientParas->m_fEDFreq;
		pTmt_GradientParas->m_uiVOL[0][i].Harm[1].fAngle=fAngleVoltage[i];
	}

	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		pTmt_GradientParas->m_uiCUR[0][i].Harm[0].fAmp=0;
		pTmt_GradientParas->m_uiCUR[0][i].Harm[1].fAmp=pTmt_GradientParas->m_fEDI;
		pTmt_GradientParas->m_uiCUR[0][i].Harm[1].fFreq=pTmt_GradientParas->m_fEDFreq;
		pTmt_GradientParas->m_uiCUR[0][i].Harm[1].fAngle=fAngleCurrent[i]-pTmt_GradientParas->m_fEDUaIaAngle;
	}
	//故障前
	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		pTmt_GradientParas->m_uiVOL[1][i].Harm[0].fAmp=0;
		pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fAmp=(i<3)?pTmt_GradientParas->m_fG1Volt:pTmt_GradientParas->m_fG2Volt;
		pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fFreq=pTmt_GradientParas->m_fHz;
		pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fAngle=fAngleVoltage[i];
	}
	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		pTmt_GradientParas->m_uiCUR[1][i].Harm[0].fAmp=0;
		pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fAmp=(i<3)?pTmt_GradientParas->m_fG1Current:pTmt_GradientParas->m_fG2Current;
		pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fFreq=pTmt_GradientParas->m_fHz;
		pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fAngle=fAngleCurrent[i]-pTmt_GradientParas->m_fEDUaIaAngle;
	}

    //故障
    if(pTmt_GradientParas->m_nSttTestMode == GradientTest_IRamp)
    {
        for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
        {
            pTmt_GradientParas->m_uiCUR[2][i].Harm[0].fAmp=0;
            pTmt_GradientParas->m_uiCUR[2][i].Harm[1].fAmp=
                    pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fAmp;
            pTmt_GradientParas->m_uiCUR[2][i].Harm[1].fFreq=
                    pTmt_GradientParas->m_uiCUR[1][i].Harm[1].fFreq;			
        }
		//第二组相位延续故障前的值
		pTmt_GradientParas->m_uiCUR[2][3].Harm[1].fAngle=
				pTmt_GradientParas->m_uiCUR[1][3].Harm[1].fAngle;
		pTmt_GradientParas->m_uiCUR[2][4].Harm[1].fAngle=
				pTmt_GradientParas->m_uiCUR[1][4].Harm[1].fAngle;
		pTmt_GradientParas->m_uiCUR[2][5].Harm[1].fAngle=
				pTmt_GradientParas->m_uiCUR[1][5].Harm[1].fAngle;
    }
	else if(pTmt_GradientParas->m_nSttTestMode == GradientTest_URamp)
    {
        for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
        {
            pTmt_GradientParas->m_uiVOL[2][i].Harm[0].fAmp=0;
            pTmt_GradientParas->m_uiVOL[2][i].Harm[1].fAmp=
                    pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fAmp;
            pTmt_GradientParas->m_uiVOL[2][i].Harm[1].fFreq=
					pTmt_GradientParas->m_uiVOL[1][i].Harm[1].fFreq;
        }
		pTmt_GradientParas->m_uiVOL[2][3].Harm[1].fAngle=
				pTmt_GradientParas->m_uiVOL[1][3].Harm[1].fAngle;
		pTmt_GradientParas->m_uiVOL[2][4].Harm[1].fAngle=
				pTmt_GradientParas->m_uiVOL[1][4].Harm[1].fAngle;
		pTmt_GradientParas->m_uiVOL[2][5].Harm[1].fAngle=
				pTmt_GradientParas->m_uiVOL[1][5].Harm[1].fAngle;
    }
}

//0-Ubc,1-Uca,2-Uab,3-3U0,4-U2
void CSttGradientTest::CalSequence_ByABC(float fMagA, float fAngA,float fMagB, float fAngB,float fMagC, float fAngC,long nMode,float &fMagDest, float &fAngDest)
{
	Complex Ua,Ub,Uc,p1,p2;
	Ua = p1.polar(fMagA,fAngA);
	Ub = p1.polar(fMagB,fAngB);
	Uc = p1.polar(fMagC,fAngC);
	switch(nMode)
	{
	case 0:
	{
		p2 = Ub - Uc;
		fMagDest = (double)p2.norm();
	}
		break;
	case 1:
	{
		p2 = Uc - Ua;
		fMagDest = (double)p2.norm();
	}
		break;
	case 2:
	{
		p2 = Ua - Ub;
		fMagDest = (double)p2.norm();
	}
		break;
	case 3:
	{
		p2 = Ua + Ub + Uc;
		fMagDest = (double)p2.norm();
		fMagDest = fMagDest/3.0;
	}
		break;
	case 4:
	{
		Ub = p1.polar(fMagB,fAngB - 120);
		Uc = p1.polar(fMagC,fAngC + 120);
		p2 = Ua + Ub + Uc;
		fMagDest = (double)p2.norm();
		fMagDest = fMagDest/3.0;
	}
		break;
	}

	fAngDest = (double)p2.arg();
	fAngDest = GetStdAngle(fAngDest);
}

