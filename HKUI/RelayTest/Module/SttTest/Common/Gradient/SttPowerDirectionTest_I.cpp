#include "stdafx.h"
#include "SttPowerDirectionTest_I.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

CString CSttPowerDirectionTest_I::m_strMacroName = "功率方向试验(国际版）";
CString CSttPowerDirectionTest_I::m_strMacroID = STT_MACRO_ID_PowerDirection_I;
CString CSttPowerDirectionTest_I::m_strFilePostFix = "ppd";
CString CSttPowerDirectionTest_I::m_strMacroVer ="1.0";

CSttPowerDirectionTest_I::CSttPowerDirectionTest_I() : CSttGradientMaxAngleTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
	Init();
}

void CSttPowerDirectionTest_I::Init()
{ 
    CSttGradientMaxAngleTest::Init();
    m_oPowerDirectionParas_I.init();
    m_oPowerDirectionParas_I.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
	m_oResultParas.init();
#ifdef _PSX_QT_LINUX_
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	pTmtGradientProcess->m_nDiretionMode = 0;
#endif
}

CSttPowerDirectionTest_I::~CSttPowerDirectionTest_I(void)
{

}

void CSttPowerDirectionTest_I::AfterSetParameter()
{
    m_oPowerDirectionParas_I.m_fStart = m_oPowerDirectionParas_I.m_fMaxSensAngle - m_oPowerDirectionParas_I.m_fAngleRange/2.0 - m_oPowerDirectionParas_I.m_fAngleMargin;
    m_oPowerDirectionParas_I.m_fStop = m_oPowerDirectionParas_I.m_fMaxSensAngle + m_oPowerDirectionParas_I.m_fAngleRange/2.0 + m_oPowerDirectionParas_I.m_fAngleMargin;

    m_oPowerDirectionParas_I.CopyOwn(&m_oGradientParas,4,3);
	m_oGradientParas.m_fEDU = m_oGradientParas.m_fG1Volt;
	m_oGradientParas.m_fEDI = m_oGradientParas.m_fG1Current;
	m_oGradientParas.m_fG2Volt = 0;
	m_oGradientParas.m_fG2Current = 0;

    m_oGradientParas.m_fStepTime += m_oGradientParas.m_fMarginTime;
//	CSttGradientMaxAngleTest::AfterSetParameter();//zhouhj 20210710 在故障计算里进行基类中的操作
}

long CSttPowerDirectionTest_I::CalReport(UINT nState)
{
	if ((m_oResultParas.m_oMaxAngle.m_nActF == 0)||(m_oResultParas.m_oMaxAngle.m_nActS == 0))
	{
		m_oResultParas.m_nAct = 0;
		return 0;
	}

	m_oResultParas.m_nAct = 1;
	float fStart,fEnd;
	fStart = m_fAngleF;
	fEnd = m_fAngleS;

    if (m_oPowerDirectionParas_I.m_nAngleMode == 0)
	{
		if (fEnd<fStart)
		{
			fStart -= 360;
		}

		m_oResultParas.m_oMaxAngle.m_fMaxAngle = fEnd - (fEnd - fStart)/2;
	}
	else
	{
		if (fStart<fEnd)
		{
			fEnd -= 360;
		}

//		m_oResultParas.m_oMaxAngle.m_fMaxAngle = fStart - (fStart - fEnd)/2; //修改前  zhouhj  2024.1.18
		//修改在电流超前电压为正时,最大灵敏角计算不对的问题
		m_oResultParas.m_oMaxAngle.m_fMaxAngle = fStart + (360 - (fStart - fEnd))/2;
	}

	if (m_oResultParas.m_oMaxAngle.m_fMaxAngle<-180)
	{
		m_oResultParas.m_oMaxAngle.m_fMaxAngle += 360;
	}
	else if (m_oResultParas.m_oMaxAngle.m_fMaxAngle > 180)
	{
		m_oResultParas.m_oMaxAngle.m_fMaxAngle -= 360;
	}

	return 0;
}

void CSttPowerDirectionTest_I::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize((tmt_PowerDirectionParas_I*)&m_oPowerDirectionParas_I,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttPowerDirectionTest_I::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_power_dir(&m_oResultParas, pXmlSerialize);
}

long CSttPowerDirectionTest_I::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttPowerDirectionTest_I::ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType)
{
#ifdef _PSX_QT_LINUX_
	STT_RTDATA_EVENT oRtdata;
	oRtdata.oTime.dTime=dTime1;
	oRtdata.oTime.dRealTime=dTime2;
	oRtdata.m_nVolChCount=0;
	oRtdata.m_nCurChCount=0;
	oRtdata.m_nHasFaultVolCur=1;//增加序分量实时数据
	oRtdata.m_oFaultVolCh.m_fMag = 0;
	oRtdata.m_oFaultVolCh.m_fAng = 0;
	oRtdata.m_oFaultVolCh.m_fFreq = 0;
	oRtdata.m_oFaultCurCh.m_fMag = 0;
	oRtdata.m_oFaultCurCh.m_fAng = 0;
	oRtdata.m_oFaultCurCh.m_fFreq = 0;

	float fVal = 0.0f;
	int nRtIndex=0;
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	long nActStepIndex = 0;//zhouhj 20211021 兼容正反向的StepIndex

	float fMagA,fAngA,fMagB,fAngB,fMagC,fAngC,fMagDest,fAngDest;
	int nMode = m_oPowerDirectionParas_I.m_nTestPhase;

	if(nType == 0)
	{
		//开始实验
		if(m_oPowerDirectionParas_I.m_fPrepareTime > 0.0001)
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
		else if(m_oPowerDirectionParas_I.m_fPreFaultTime > 0.0001)
		{
			//故障前数据
			for(int nIndex=0;nIndex<3;nIndex++)
			{
				fVal=fabs(m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAmp);

				nRtIndex=oRtdata.m_nVolChCount;
				oRtdata.m_oVolCh[nRtIndex].m_nIndex=nIndex;
				oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oVolCh[nRtIndex].m_fAng=
						m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAngle;
				oRtdata.m_oVolCh[nRtIndex].m_fFreq=
						m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fFreq;
				oRtdata.m_nVolChCount++;
			}

			for(int nIndex=0;nIndex<3;nIndex++)
			{
				fVal=fabs(m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAmp);
				nRtIndex=oRtdata.m_nCurChCount;
				oRtdata.m_oCurCh[nRtIndex].m_nIndex=nIndex;
				oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oCurCh[nRtIndex].m_fAng=
						m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAngle;
				oRtdata.m_oCurCh[nRtIndex].m_fFreq=
						m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fFreq;
				oRtdata.m_nCurChCount++;
			}
		}
		else
		{
			for(int nIndex=0;nIndex<3;nIndex++)
			{
				fVal=fabs(pTmtGradientProcess->m_uiStepData[0].fU[nIndex][0]);
				nRtIndex=oRtdata.m_nVolChCount;
				oRtdata.m_oVolCh[nRtIndex].m_nIndex=nIndex;
				oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oVolCh[nRtIndex].m_fAng=
						pTmtGradientProcess->m_uiStepData[0].fU[nIndex][1];
				oRtdata.m_oVolCh[nRtIndex].m_fFreq=
						pTmtGradientProcess->m_uiStepData[0].fU[nIndex][2];
				oRtdata.m_nVolChCount++;

				fVal=fabs(pTmtGradientProcess->m_uiStepData[0].fI[nIndex][0]);
				nRtIndex=oRtdata.m_nCurChCount;
				oRtdata.m_oCurCh[nRtIndex].m_nIndex=nIndex;
				oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
				oRtdata.m_oCurCh[nRtIndex].m_fAng=
						pTmtGradientProcess->m_uiStepData[0].fI[nIndex][1];
				oRtdata.m_oCurCh[nRtIndex].m_fFreq=
						pTmtGradientProcess->m_uiStepData[0].fI[nIndex][2];
				oRtdata.m_nCurChCount++;
			}
		}

		fMagA = oRtdata.m_oVolCh[0].m_fMag;
		fAngA = oRtdata.m_oVolCh[0].m_fAng;
		fMagB = oRtdata.m_oVolCh[1].m_fMag;
		fAngB = oRtdata.m_oVolCh[1].m_fAng;
		fMagC = oRtdata.m_oVolCh[2].m_fMag;
		fAngC = oRtdata.m_oVolCh[2].m_fAng;
		oRtdata.m_oFaultVolCh.m_fFreq = oRtdata.m_oVolCh[0].m_fFreq;
		CalSequence_ByABC(fMagA,fAngA,fMagB,fAngB,fMagC,fAngC,nMode,fMagDest,fAngDest);
		oRtdata.m_oFaultVolCh.m_fMag = fMagDest;
		oRtdata.m_oFaultVolCh.m_fAng = fAngDest;
	}
	else if((nStep <= pTmtGradientProcess->m_nStepCount)&&(nStep<GRADIENT_MAX_COUNT))
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

			fMagA = pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[0][0];
			fAngA = pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[0][1];
			fMagB = pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[1][0];
			fAngB = pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[1][1];
			fMagC = pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[2][0];
			fAngC = pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[2][1];
			oRtdata.m_oFaultVolCh.m_fFreq = oRtdata.m_oVolCh[0].m_fFreq;
			CalSequence_ByABC(fMagA,fAngA,fMagB,fAngB,fMagC,fAngC,nMode,fMagDest,fAngDest);
			oRtdata.m_oFaultVolCh.m_fMag = fMagDest;
			oRtdata.m_oFaultVolCh.m_fAng = fAngDest;
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

			fMagA = m_oGradientParas.m_uiVOL[1][0].Harm[1].fAmp;
			fAngA = m_oGradientParas.m_uiVOL[1][0].Harm[1].fAngle;
			fMagB = m_oGradientParas.m_uiVOL[1][1].Harm[1].fAmp;
			fAngB = m_oGradientParas.m_uiVOL[1][1].Harm[1].fAngle;
			fMagC = m_oGradientParas.m_uiVOL[1][2].Harm[1].fAmp;
			fAngC = m_oGradientParas.m_uiVOL[1][2].Harm[1].fAngle;
			oRtdata.m_oFaultVolCh.m_fFreq = oRtdata.m_oVolCh[0].m_fFreq;
			CalSequence_ByABC(fMagA,fAngA,fMagB,fAngB,fMagC,fAngC,nMode,fMagDest,fAngDest);
			oRtdata.m_oFaultVolCh.m_fMag = fMagDest;
			oRtdata.m_oFaultVolCh.m_fAng = fAngDest;
		}
	}

	UpdateMonitorCur(oRtdata);

	if(oRtdata.m_nCurChCount>0||oRtdata.m_nVolChCount>0)
		stt_add_rtdatas(oRtdata);
#endif
}

void CSttPowerDirectionTest_I::TranslateToStateParas()
{
	InitParaBeforeGradient();
	CalStepValue_Gradient(&m_oGradientParas);
}

void CSttPowerDirectionTest_I::InitParaBeforeGradient(long nGradientChCount)
{
	CSttGradientMaxAngleTest::InitParaBeforeGradient(&m_oGradientParas,nGradientChCount);
 	GradientAllChAndAllType();
}

void CSttPowerDirectionTest_I::TtmToDrv()
 {
#ifdef _PSX_QT_LINUX_
	 if(m_oGradientParas.m_fPrepareTime<EPSINON)
	 {
		 m_nCurStepIndex=0;
	 }

     CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_Gradient_NeedStepsValue(&m_oGradientParas);
#endif
 }

void CSttPowerDirectionTest_I::CalStepValue(tmt_GradientParas *pTmt_GradientParas,float fCurValue,int nHarmIndex)
{
#ifdef _PSX_QT_LINUX_
 	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
#endif
	Complex fV1,fV2,fV3,fI1,fI2,fI3;
	Complex p1,p2,p3,Vpol,Vol2,Vol3;
	float fPhi,fAngle,Volp,fSign = 1;
	int nPhaseRef[10]={1,2,0,2,0,1,2,0,1,0};
	float nAngle[10] = {0.0,-120.0,120,30.0,-120+30.0,120+30.0,30.0,-120+30.0,120+30.0,0.0};
	int m_nReference = 1;
	fI1=p1.polar(0,0.0);
	fI2=p1.polar(0,0.0);
	fI3=p1.polar(0,0.0);
	Vol2=p1.polar(1.0,240);
	Vol3=p1.polar(1.0,120);
	p2=p1.polar(1.0,240);
	p3=p1.polar(1.0,120);

    if(m_oPowerDirectionParas_I.m_nAngleMode == 0)//电压超前电流为正
		fSign= 1;
	else
		fSign= -1;

	float fV;
    fPhi = fabs(atan2(m_oPowerDirectionParas_I.m_fSCVoltage,m_oGradientParas.m_fEDU))*180.0/_PI;
 
    switch(m_oPowerDirectionParas_I.m_nFaultPhase)
 	{
 	case POWER_DIR_FAULT_PHASE_A:
//		m_nChanelPhChange[0] = 1;

        fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage,0.0);
		fV2=p1.polar(m_oGradientParas.m_fEDU,-120.0);
		fV3=p1.polar(m_oGradientParas.m_fEDU,120.0);

        if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_A)
		{
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)//0度接线
			{
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign);
			}
			else
			{
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign-90.0);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_ZERO)
		{
			fV=p1.arg(fV1+fV2+fV3);
			fV1=p1.polar(p2.norm(fV1),p3.arg(fV1)-fV);
			fV2=p1.polar(p2.norm(fV2),p3.arg(fV2)-fV);
			fV3=p1.polar(p2.norm(fV3),p3.arg(fV3)-fV);
            fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign+p2.arg(fV1+fV2+fV3)-p2.arg(fI1+fI2+fI3));
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_NEG)
		{
			fV=p1.arg(fV1+fV2*p2+fV3*p3);
			fV1=p1.polar(p2.norm(fV1),p3.arg(fV1)-fV);
			fV2=p1.polar(p2.norm(fV2),p3.arg(fV2)-fV);
			fV3=p1.polar(p2.norm(fV3),p3.arg(fV3)-fV);
            fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign+p2.arg(fV1+fV2*Vol2+fV3*Vol3)-p2.arg(fI1+fI2*Vol2+fI3*Vol3));
		}
	
 		break;
 
 	case POWER_DIR_FAULT_PHASE_B:
//		m_nChanelPhChange[1] = 1;
		//		if(m_nVariable<3)
		//		{
		fV1=p1.polar(m_oGradientParas.m_fEDU,0.0);
        fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage,-120.0);
		fV3=p1.polar(m_oGradientParas.m_fEDU,120.0);
		//		}
		//		else
        if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_B)
		{
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-120.0-fCurValue*fSign);
			}
			else
			{
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-120.0-fCurValue*fSign-90.0);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_ZERO)
		{
			fV=p1.arg(fV1+fV2+fV3);
			fV1=p1.polar(p2.norm(fV1),p3.arg(fV1)-fV);
			fV2=p1.polar(p2.norm(fV2),p3.arg(fV2)-fV);
			fV3=p1.polar(p2.norm(fV3),p3.arg(fV3)-fV);
            fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign+p2.arg(fV1+fV2+fV3)-p2.arg(fI1+fI2+fI3));
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_NEG)
		{
			fV=p1.arg(fV1+fV2*p2+fV3*p3);
			fV1=p1.polar(p2.norm(fV1),p3.arg(fV1)-fV);
			fV2=p1.polar(p2.norm(fV2),p3.arg(fV2)-fV);
			fV3=p1.polar(p2.norm(fV3),p3.arg(fV3)-fV);
            fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign-120.0+p2.arg(fV1+fV2*Vol2+fV3*Vol3)-p2.arg(fI1+fI2*Vol2+fI3*Vol3)-120.0);
		}
		
 		break;
 
 	case POWER_DIR_FAULT_PHASE_C:
//		m_nChanelPhChange[2] = 1;
		fV1=p1.polar(m_oGradientParas.m_fEDU,0.0);
		fV2=p1.polar(m_oGradientParas.m_fEDU,-120.0);
        fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage,120.0);

        if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_C)
		{
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,120.0-fCurValue*fSign);
			}
			else
			{
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,120.0-fCurValue*fSign+30.0-120.0);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_ZERO)
		{
			fV=p1.arg(fV1+fV2+fV3);
			fV1=p1.polar(p2.norm(fV1),p3.arg(fV1)-fV);
			fV2=p1.polar(p2.norm(fV2),p3.arg(fV2)-fV);
			fV3=p1.polar(p2.norm(fV3),p3.arg(fV3)-fV);
            fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign+p2.arg(fV1+fV2+fV3)-p2.arg(fI1+fI2+fI3));
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_NEG)
		{
			fV=p1.arg(fV1+fV2*p2+fV3*p3);
			fV1=p1.polar(p2.norm(fV1),p3.arg(fV1)-fV);
			fV2=p1.polar(p2.norm(fV2),p3.arg(fV2)-fV);
			fV3=p1.polar(p2.norm(fV3),p3.arg(fV3)-fV);
            fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign+120.0+p2.arg(fV1+fV2*Vol2+fV3*Vol3)-p2.arg(fI1+fI2*Vol2+fI3*Vol3)+120.0);
		}

 		break;
 
 	case POWER_DIR_FAULT_PHASE_AB:
// 		m_nChanelPhChange[0] = 1;
// 		m_nChanelPhChange[1] = 1;
        if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
		{
            fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),0);
            fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-2*fPhi);
			fV3=p1.polar(m_oGradientParas.m_fEDU,180-fPhi);
		}
		else
		{
            fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0+fPhi);
            fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0-fPhi);
			fV3=p1.polar(m_oGradientParas.m_fEDU,90.0);
		}

        if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_A)
		{

            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
				fAngle=p3.arg(fV1);
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign+fAngle);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign+fAngle);
			}
			else
			{
				fAngle=p3.arg(fV2-fV3)-p3.arg(fV1-fV2)+90.0;
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0+fAngle);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-90.0+fAngle);
			}

		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_B)
		{

            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
				fAngle=p3.arg(fV2)-60.0;
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-120.0+fAngle);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-120.0+fAngle);
			}
			else
			{
				fAngle=p3.arg(fV3-fV1)-p3.arg(fV1-fV2)+30.0;
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0-120.0+fAngle);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-90.0-120.0+fAngle);
			}

		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_C)
		{
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign+120.0);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign+120.0);
			}
			else
			{
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0+120.0);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-90.0+120.0);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_NEG)
		{
			p2=p1.polar(1.0,240);
			p3=p1.polar(1.0,120);
			float fV=p1.arg(fV1+fV2*p2+fV3*p3);
			fV1=p1.polar(p2.norm(fV1),p3.arg(fV1)-fV);
			fV2=p1.polar(p2.norm(fV2),p3.arg(fV2)-fV);
			fV3=p1.polar(p2.norm(fV3),p3.arg(fV3)-fV);

			Volp=p2.arg(fV1+fV2*Vol2+fV3*Vol3)-p2.arg(fI1+fI2*Vol2+fI3*Vol3);
            fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign-30.0+Volp);
            fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign+Volp-30.0+180.0);
        }
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_AB)//xzt
        {
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
            {
                fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0+fPhi);
                fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0-fPhi);
                fV3=p1.polar(m_oGradientParas.m_fEDU,90.0);

                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign);
            }
            else
            {
                fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),fPhi);
                fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),fPhi);
                fV3=p1.polar(m_oGradientParas.m_fEDU,180.0);

                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign);
            }
        }
 		break;
 
 	case POWER_DIR_FAULT_PHASE_BC:
// 		m_nChanelPhChange[1] = 1;
// 		m_nChanelPhChange[2] = 1;
        if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
		{
            fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),0);
            fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-2*fPhi);
			fV1=p1.polar(m_oGradientParas.m_fEDU,180-fPhi);
		}
		else
		{
            fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0+fPhi);
            fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0-fPhi);
			fV1=p1.polar(m_oGradientParas.m_fEDU,90.0);
		}

        if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_A)
		{
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign);
			}
			else
			{
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-90.0);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_B)
		{

            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
				fAngle=p3.arg(fV2)+120.0;
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-120.0+fAngle);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-120.0+fAngle);
			}
			else
			{
				fAngle=p3.arg(fV3-fV1)-p3.arg(fV2-fV3)-150.0;
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0-120.0+fAngle);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-90.0-120.0+fAngle);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_C)
		{

            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
				fAngle=p3.arg(fV3)-300.0;
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign+120.0+fAngle);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign+120.0+fAngle);

			}
			else
			{
				fAngle=p3.arg(fV1-fV2)-p3.arg(fV2-fV3)-210.0;
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0+120.0+fAngle);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-90.0+120.0+fAngle);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_NEG)
		{
			p2=p1.polar(1.0,240);
			p3=p1.polar(1.0,120);
			float fV=p1.arg(fV1+fV2*p2+fV3*p3);
			fV1=p1.polar(p2.norm(fV1),p3.arg(fV1)-fV);
			fV2=p1.polar(p2.norm(fV2),p3.arg(fV2)-fV);
			fV3=p1.polar(p2.norm(fV3),p3.arg(fV3)-fV);

			Volp=p2.arg(fV1+fV2*Vol2+fV3*Vol3)-p2.arg(fI1+fI2*Vol2+fI3*Vol3);
            fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign-30.0+Volp-240.0);
            fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign+Volp-30.0+180.0-240.0);
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_BC)//xzt
        {
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
            {
                fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0+fPhi);
                fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0-fPhi);
                fV1=p1.polar(m_oGradientParas.m_fEDU,90.0);

                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign);
            }
            else
            {
                fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),fPhi);
                fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),fPhi);
                fV1=p1.polar(m_oGradientParas.m_fEDU,180.0);

                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign);
            }
        }

 		break;

	case POWER_DIR_FAULT_PHASE_CA:
// 		m_nChanelPhChange[0] = 1;
// 		m_nChanelPhChange[2] = 1;
        if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
		{
            fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),0);
            fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-2*fPhi);
			fV2=p1.polar(m_oGradientParas.m_fEDU,180-fPhi);
		}
		else
		{
            fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0+fPhi);
            fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0-fPhi);
			fV2=p1.polar(m_oGradientParas.m_fEDU,90.0);
		}

        if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_A)
		{

            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
				fAngle=p3.arg(fV1)-180.0;
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign+fAngle);
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign+fAngle);
			}
			else
			{
				fAngle=p3.arg(fV2-fV3)-p3.arg(fV3-fV1)-90.0;
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0+fAngle);
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-90.0+fAngle);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_B)
		{
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-120.0);
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-120.0);
			}
			else
			{
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0-120.0);
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-90.0-120.0);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_C)
		{

            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
				fAngle=p3.arg(fV3)-120.0;
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign+120.0+fAngle);
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign+120.0+fAngle);
			}
			else
			{
				fAngle=p3.arg(fV1-fV2)-p3.arg(fV3-fV1)-30.0;
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0+120.0+fAngle);
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign-90.0+120.0+fAngle);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_NEG)
		{
			p2=p1.polar(1.0,240);
			p3=p1.polar(1.0,120);
			float fV=p1.arg(fV1+fV2*p2+fV3*p3);
			fV1=p1.polar(p2.norm(fV1),p3.arg(fV1)-fV);
			fV2=p1.polar(p2.norm(fV2),p3.arg(fV2)-fV);
			fV3=p1.polar(p2.norm(fV3),p3.arg(fV3)-fV);

			Volp=p2.arg(fV1+fV2*Vol2+fV3*Vol3)-p2.arg(fI1+fI2*Vol2+fI3*Vol3);
            fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign-30.0+Volp-120.0);
            fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-fCurValue*fSign+Volp-30.0+180.0-120.0);
        }
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_CA)//xzt
        {
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
            {
                fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0+fPhi);
                fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),-90.0-fPhi);
                fV2=p1.polar(m_oGradientParas.m_fEDU,90.0);

                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign);
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign);
            }
            else
            {
                fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),fPhi);
                fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/2.0/sin(fPhi*_PI/180.0),fPhi);
                fV2=p1.polar(m_oGradientParas.m_fEDU,180.0);

                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign);
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,180.0-fCurValue*fSign);
            }
        }
		break;

	case POWER_DIR_FAULT_PHASE_ABC:
// 		m_nChanelPhChange[0] = 1;
// 		m_nChanelPhChange[1] = 1;
// 		m_nChanelPhChange[2] = 1;
        fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage,0.0);
        fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage,-120.0);
        fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage,120.0);

        if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_A || m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_ABC)
		{
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
				fAngle=p3.arg(fV1);
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign+fAngle);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-120.0-fCurValue*fSign+fAngle);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,120.0-fCurValue*fSign+fAngle);
			}
			else
			{
				fAngle=p3.arg(fV2-fV3)-p3.arg(fV1)+90.0;
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0+fAngle);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-120.0-fCurValue*fSign-90.0+fAngle);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,120.0-fCurValue*fSign-90.0+fAngle);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase ==POWER_DIR_TEST_PHASE_B)
		{
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
				fAngle=p3.arg(fV2)-120.0;
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-120.0+fAngle);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-120.0-fCurValue*fSign-120.0+fAngle);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,120.0-fCurValue*fSign-120.0+fAngle);
			}
			else
			{
				fAngle=p3.arg(fV3-fV1)-p3.arg(fV1)-30.0;
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0-120.0+fAngle);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-120.0-fCurValue*fSign-90.0-120.0+fAngle);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,120.0-fCurValue*fSign-90.0-120.0+fAngle);
			}
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_C)
		{
            if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
			{
				fAngle=p3.arg(fV3)+120.0;
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign+120.0+fAngle);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-120.0-fCurValue*fSign+120.0+fAngle);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,120.0-fCurValue*fSign+120.0+fAngle);
			}
			else
			{
				fAngle=p3.arg(fV1-fV2)-p3.arg(fV1)-150.0;
                fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign-90.0+120.0+fAngle);
                fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-120.0-fCurValue*fSign-90.0+120.0+fAngle);
                fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,120.0-fCurValue*fSign-90.0+120.0+fAngle);
			}
        }
		break;

	case POWER_DIR_FAULT_PHASE_ZERO:
// 		m_nChanelPhChange[0] = 1;
// 		m_nChanelPhChange[1] = 1;
// 		m_nChanelPhChange[2] = 1;

        fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/3.0,0.0);
        fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/3.0,0.0);
        fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage/3.0,0.0);
        fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent/3.0,0.0-fCurValue*fSign);
        fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent/3.0,0.0-fCurValue*fSign);
        fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent/3.0,0.0-fCurValue*fSign);

		break;
 
	case POWER_DIR_FAULT_PHASE_NEG:
// 		m_nChanelPhChange[0] = 1;
// 		m_nChanelPhChange[1] = 1;
// 		m_nChanelPhChange[2] = 1;
        fV1=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage,0.0);
        fV2=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage,120.0);
        fV3=p1.polar(m_oPowerDirectionParas_I.m_fSCVoltage,-120.0);
        fI1=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,0.0-fCurValue*fSign);
        fI2=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,120.0-fCurValue*fSign);
        fI3=p1.polar(m_oPowerDirectionParas_I.m_fSCCurrent,-120.0-fCurValue*fSign);

		break;
	default:
 		break;
 	}

    if(m_oPowerDirectionParas_I.m_nConnectMode == 0)
	{
        if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_A)
		{
			Vpol=fV1;
			//               qDebug()<<"the Vpol "<<fV1.arg();
			fV1=p1.polar(p2.norm(fV1),p2.arg(fV1)-p2.arg(Vpol));
			fV2=p1.polar(p2.norm(fV2),p2.arg(fV2)-p2.arg(Vpol));
			fV3=p1.polar(p2.norm(fV3),p2.arg(fV3)-p2.arg(Vpol));
			fI1=p1.polar(p2.norm(fI1),p2.arg(fI1)-p2.arg(Vpol));
			fI2=p1.polar(p2.norm(fI2),p2.arg(fI2)-p2.arg(Vpol));
			fI3=p1.polar(p2.norm(fI3),p2.arg(fI3)-p2.arg(Vpol));
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_B)
		{
			Vpol=fV2;
			fV1=p1.polar(p2.norm(fV1),p2.arg(fV1)-p2.arg(Vpol));
			fV2=p1.polar(p2.norm(fV2),p2.arg(fV2)-p2.arg(Vpol));
			fV3=p1.polar(p2.norm(fV3),p2.arg(fV3)-p2.arg(Vpol));
			fI1=p1.polar(p2.norm(fI1),p2.arg(fI1)-p2.arg(Vpol));
			fI2=p1.polar(p2.norm(fI2),p2.arg(fI2)-p2.arg(Vpol));
			fI3=p1.polar(p2.norm(fI3),p2.arg(fI3)-p2.arg(Vpol));
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_C)
		{
			Vpol=fV3;
			fV1=p1.polar(p2.norm(fV1),p2.arg(fV1)-p2.arg(Vpol));
			fV2=p1.polar(p2.norm(fV2),p2.arg(fV2)-p2.arg(Vpol));
			fV3=p1.polar(p2.norm(fV3),p2.arg(fV3)-p2.arg(Vpol));
			fI1=p1.polar(p2.norm(fI1),p2.arg(fI1)-p2.arg(Vpol));
			fI2=p1.polar(p2.norm(fI2),p2.arg(fI2)-p2.arg(Vpol));
			fI3=p1.polar(p2.norm(fI3),p2.arg(fI3)-p2.arg(Vpol));
		}
	}
	else
	{
        if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_A)
		{
			Vpol=fV2-fV3;
			fV1=p1.polar(p2.norm(fV1),p2.arg(fV1)-p2.arg(Vpol));
			fV2=p1.polar(p2.norm(fV2),p2.arg(fV2)-p2.arg(Vpol));
			fV3=p1.polar(p2.norm(fV3),p2.arg(fV3)-p2.arg(Vpol));
			fI1=p1.polar(p2.norm(fI1),p2.arg(fI1)-p2.arg(Vpol));
			fI2=p1.polar(p2.norm(fI2),p2.arg(fI2)-p2.arg(Vpol));
			fI3=p1.polar(p2.norm(fI3),p2.arg(fI3)-p2.arg(Vpol));
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_B)
		{
			Vpol=fV3-fV1;
			fV1=p1.polar(p2.norm(fV1),p2.arg(fV1)-p2.arg(Vpol));
			fV2=p1.polar(p2.norm(fV2),p2.arg(fV2)-p2.arg(Vpol));
			fV3=p1.polar(p2.norm(fV3),p2.arg(fV3)-p2.arg(Vpol));
			fI1=p1.polar(p2.norm(fI1),p2.arg(fI1)-p2.arg(Vpol));
			fI2=p1.polar(p2.norm(fI2),p2.arg(fI2)-p2.arg(Vpol));
			fI3=p1.polar(p2.norm(fI3),p2.arg(fI3)-p2.arg(Vpol));
		}
        else if(m_oPowerDirectionParas_I.m_nTestPhase==POWER_DIR_TEST_PHASE_C)
		{
			Vpol=fV1-fV2;
			fV1=p1.polar(p2.norm(fV1),p2.arg(fV1)-p2.arg(Vpol));
			fV2=p1.polar(p2.norm(fV2),p2.arg(fV2)-p2.arg(Vpol));
			fV3=p1.polar(p2.norm(fV3),p2.arg(fV3)-p2.arg(Vpol));
			fI1=p1.polar(p2.norm(fI1),p2.arg(fI1)-p2.arg(Vpol));
			fI2=p1.polar(p2.norm(fI2),p2.arg(fI2)-p2.arg(Vpol));
			fI3=p1.polar(p2.norm(fI3),p2.arg(fI3)-p2.arg(Vpol));
		}
	}
 
 	pTmt_GradientParas->m_uiVOL[2][TMT_GRADIENT_CHANNEL_A].Harm[nHarmIndex].fAmp = (float)fV1.norm();
 	pTmt_GradientParas->m_uiVOL[2][TMT_GRADIENT_CHANNEL_B].Harm[nHarmIndex].fAmp = (float)fV2.norm();
 	pTmt_GradientParas->m_uiVOL[2][TMT_GRADIENT_CHANNEL_C].Harm[nHarmIndex].fAmp = (float)fV3.norm();
 	pTmt_GradientParas->m_uiVOL[2][TMT_GRADIENT_CHANNEL_A].Harm[nHarmIndex].fAngle = (float)fV1.arg();
 	pTmt_GradientParas->m_uiVOL[2][TMT_GRADIENT_CHANNEL_B].Harm[nHarmIndex].fAngle = (float)fV2.arg();
 	pTmt_GradientParas->m_uiVOL[2][TMT_GRADIENT_CHANNEL_C].Harm[nHarmIndex].fAngle = (float)fV3.arg();
 	pTmt_GradientParas->m_uiCUR[2][TMT_GRADIENT_CHANNEL_A].Harm[nHarmIndex].fAmp = (float)fI1.norm();
 	pTmt_GradientParas->m_uiCUR[2][TMT_GRADIENT_CHANNEL_B].Harm[nHarmIndex].fAmp = (float)fI2.norm();
 	pTmt_GradientParas->m_uiCUR[2][TMT_GRADIENT_CHANNEL_C].Harm[nHarmIndex].fAmp = (float)fI3.norm();
 	pTmt_GradientParas->m_uiCUR[2][TMT_GRADIENT_CHANNEL_A].Harm[nHarmIndex].fAngle = (float)fI1.arg();
 	pTmt_GradientParas->m_uiCUR[2][TMT_GRADIENT_CHANNEL_B].Harm[nHarmIndex].fAngle = (float)fI2.arg();
 	pTmt_GradientParas->m_uiCUR[2][TMT_GRADIENT_CHANNEL_C].Harm[nHarmIndex].fAngle = (float)fI3.arg();
}

void CSttPowerDirectionTest_I::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
{
	if(!m_bAngleF_TestFinished)
	{		
		if(m_oResultParas.m_oMaxAngle.m_nActF==1)
		{
			m_bAngleF_TestFinished=TRUE;
#ifdef _PSX_QT_LINUX_
			tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
			pTmtGradientProcess->m_nDiretionMode = 1;
#endif

			//反向搜索
// 			AngleTestTransPara(FALSE);
// 			TranslateToStateParas();
			StartTest();
			return;
		}
	}

	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;
	CalReport();

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
	SetTestStarting(FALSE);
}

void CSttPowerDirectionTest_I::SyncGradientResult(int nStep,double dTime,int nTripType)
{
	if (/*nTripType == 0*/!m_bAngleF_TestFinished)
	{
//		m_bAngleF_TestFinished=FALSE;
        m_fAngleF = m_oPowerDirectionParas_I.m_fStart + m_oPowerDirectionParas_I.m_fStep*nStep;
		m_oResultParas.m_oMaxAngle.m_fAngleF = GetStdAngle(m_fAngleF);
		m_fAngleF = m_oResultParas.m_oMaxAngle.m_fAngleF;
		m_oResultParas.m_oMaxAngle.m_nActF=1;
		m_oResultParas.m_oMaxAngle.m_nAngleF_StepIndex=nStep;
	} 
	else
	{
        m_fAngleS = m_oPowerDirectionParas_I.m_fStop - m_oPowerDirectionParas_I.m_fStep*nStep;
		m_oResultParas.m_oMaxAngle.m_fAngleS = GetStdAngle(m_fAngleS);
		m_fAngleS = m_oResultParas.m_oMaxAngle.m_fAngleS;
		m_oResultParas.m_oMaxAngle.m_nActS=1;
		m_oResultParas.m_oMaxAngle.m_nAngleS_StepIndex=nStep;
	}
}


