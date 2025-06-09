#include "stdafx.h"
#include "SttULockOverCurrentTest.h"
#include "../SttSystemConfig.h"

CString CSttULockOverCurrentTest::m_strMacroName = "复压闭锁过流试验";
CString CSttULockOverCurrentTest::m_strMacroID = STT_MACRO_ID_ULockOverCurrent;
CString CSttULockOverCurrentTest::m_strFilePostFix = "ouoc";
CString CSttULockOverCurrentTest::m_strMacroVer ="1.0";

CSttULockOverCurrentTest::CSttULockOverCurrentTest() : CSttGradientTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
	Init();
}

void CSttULockOverCurrentTest::Init()
{ 
	CSttGradientTest::Init();
	m_oULockOverCurrentParas.init();
	m_oULockOverCurrentParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
#ifdef _PSX_QT_LINUX_
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	pTmtGradientProcess->m_nDiretionMode = 0;
#endif
}

CSttULockOverCurrentTest::~CSttULockOverCurrentTest(void)
{

}

void CSttULockOverCurrentTest::AfterSetParameter()
{
	m_oULockOverCurrentParas.CopyOwn(&m_oGradientParas,4,3);
	m_oGradientParas.m_fEDU = m_oGradientParas.m_fG1Volt;
	m_oGradientParas.m_fEDI = m_oGradientParas.m_fG1Current;
	m_oGradientParas.m_fG2Volt = 0;
	m_oGradientParas.m_fG2Current = 0;
//	CSttGradientTest::AfterSetParameter();//zhouhj 20210710 在故障计算里进行基类中的操作
 	m_oResultParas.init();
}

long CSttULockOverCurrentTest::CalReport(UINT nState)
{
	return 0;
}

void CSttULockOverCurrentTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_ULockOverCurrentParas*)&m_oULockOverCurrentParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttULockOverCurrentTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oResultParas, pXmlSerialize);
}

long CSttULockOverCurrentTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttULockOverCurrentTest::TranslateToStateParas()
{
	InitParaBeforeGradient();
	CalStepValue_Gradient(&m_oGradientParas);
}

void CSttULockOverCurrentTest::SyncGradientResult(int nStep,double dTime,int nTripType)
{
	long nSymbol = 1;

	if (m_oGradientParas.m_fStart>m_oGradientParas.m_fStop)
	{
		nSymbol = -1;
	}

	if (nTripType == 0)
	{
		m_oResultParas.m_fTripValue = m_oGradientParas.m_fStart + m_oGradientParas.m_fStep*nStep*nSymbol;
		m_oResultParas.m_nAct = 1;
	} 
	else
	{
		m_oResultParas.m_fReturnValue = m_oResultParas.m_fTripValue - m_oGradientParas.m_fStep*nStep*nSymbol;
		m_oResultParas.m_fReturnCoef = m_oResultParas.m_fReturnValue/m_oResultParas.m_fTripValue;
	}
}

void CSttULockOverCurrentTest::InitParaBeforeGradient(long nGradientChCount)
{
	CSttGradientTest::InitParaBeforeGradient(&m_oGradientParas,nGradientChCount);
//	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	GradientAllChAndAllType();

// 	switch(m_oULockOverCurrentParas.m_nULockFaultType)
// 	{
// 	case ULOCK_FAULT_TYPE_LOW_VOLTAGE:
// 		pTmtGradientProcess->m_bUChange[TMT_GRADIENT_CHANNEL_A][GRADIENT_AMP] = TRUE;
// 		pTmtGradientProcess->m_bUChange[TMT_GRADIENT_CHANNEL_B][GRADIENT_AMP] = TRUE;
// 		pTmtGradientProcess->m_bUChange[TMT_GRADIENT_CHANNEL_C][GRADIENT_AMP] = TRUE;
// 		break;
// 
// 	case ULOCK_FAULT_TYPE_NEG_SEQ_VOL:
// 		pTmtGradientProcess->m_bUChange[TMT_GRADIENT_CHANNEL_A][GRADIENT_AMP] = TRUE;
// 		pTmtGradientProcess->m_bUChange[TMT_GRADIENT_CHANNEL_B][GRADIENT_AMP] = TRUE;
// 		break;
// 
// 	case ULOCK_FAULT_TYPE_LOW_CURRENT_A:
// 		pTmtGradientProcess->m_bIChange[TMT_GRADIENT_CHANNEL_A][GRADIENT_AMP] = TRUE;
// 		break;
// 
// 	case ULOCK_FAULT_TYPE_LOW_CURRENT_B:
// 		pTmtGradientProcess->m_bIChange[TMT_GRADIENT_CHANNEL_B][GRADIENT_AMP] = TRUE;
// 		break;
// 
// 	case ULOCK_FAULT_TYPE_LOW_CURRENT_C:
// 		pTmtGradientProcess->m_bIChange[TMT_GRADIENT_CHANNEL_C][GRADIENT_AMP] = TRUE;
// 		break;
// 
// 	default:
// 		break;
// 	}
}

void CSttULockOverCurrentTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	if(m_oGradientParas.m_fPrepareTime<EPSINON)
	{
		m_nCurStepIndex=0;
	}

    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_Gradient_NeedStepsValue(&m_oGradientParas);
#endif
}

void CSttULockOverCurrentTest::ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType)
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
	int nMode = 0;
	if(m_oULockOverCurrentParas.m_nULockFaultType == ULOCK_FAULT_TYPE_NEG_SEQ_VOL)
	{
		nMode = 4;
	}
	else if(m_oULockOverCurrentParas.m_nULockFaultType == ULOCK_FAULT_TYPE_LOW_VOLTAGE)
	{
		nMode = 0;//Ua
	}
	else if(m_oULockOverCurrentParas.m_nULockFaultType == ULOCK_FAULT_TYPE_LOW_CURRENT_A)
	{
		nMode = 1;//Ia
	}
	else if(m_oULockOverCurrentParas.m_nULockFaultType == ULOCK_FAULT_TYPE_LOW_CURRENT_B)
	{
		nMode = 2;//Ib
	}
	else if(m_oULockOverCurrentParas.m_nULockFaultType == ULOCK_FAULT_TYPE_LOW_CURRENT_C)
	{
		nMode = 3;//Ic
	}

	if(nType == 0)
	{
		//开始实验
		if(m_oULockOverCurrentParas.m_fPrepareTime > 0.0001)
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
		else if(m_oULockOverCurrentParas.m_fPreFaultTime > 0.0001)
		{
			//测试前额定数据
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

		if(nMode == 4)
		{
			fMagA = oRtdata.m_oVolCh[0].m_fMag;
			fAngA = oRtdata.m_oVolCh[0].m_fAng;
			fMagB = oRtdata.m_oVolCh[1].m_fMag;
			fAngB = oRtdata.m_oVolCh[1].m_fAng;
			fMagC = oRtdata.m_oVolCh[2].m_fMag;
			fAngC = oRtdata.m_oVolCh[2].m_fAng;
			oRtdata.m_oFaultVolCh.m_fFreq = oRtdata.m_oCurCh[0].m_fFreq;
			CalSequence_ByABC(fMagA,fAngA,fMagB,fAngB,fMagC,fAngC,nMode,fMagDest,fAngDest);
			oRtdata.m_oFaultVolCh.m_fMag = fMagDest;
			oRtdata.m_oFaultVolCh.m_fAng = fAngDest;
		}
		else
		{
			switch(nMode)
			{
			case 0:
			{
				oRtdata.m_oFaultVolCh.m_fFreq = oRtdata.m_oVolCh[0].m_fFreq;
				oRtdata.m_oFaultVolCh.m_fMag = oRtdata.m_oVolCh[0].m_fMag;
				oRtdata.m_oFaultVolCh.m_fAng = oRtdata.m_oVolCh[0].m_fAng;
			}
				break;
			case 1:
			{
				oRtdata.m_oFaultCurCh.m_fFreq = oRtdata.m_oCurCh[0].m_fFreq;
				oRtdata.m_oFaultCurCh.m_fMag = oRtdata.m_oCurCh[0].m_fMag;
				oRtdata.m_oFaultCurCh.m_fAng = oRtdata.m_oCurCh[0].m_fAng;
			}
				break;
			case 2:
			{
				oRtdata.m_oFaultCurCh.m_fFreq = oRtdata.m_oCurCh[1].m_fFreq;
				oRtdata.m_oFaultCurCh.m_fMag = oRtdata.m_oCurCh[1].m_fMag;
				oRtdata.m_oFaultCurCh.m_fAng = oRtdata.m_oCurCh[1].m_fAng;
			}
				break;
			case 3:
			{
				oRtdata.m_oFaultCurCh.m_fFreq = oRtdata.m_oCurCh[2].m_fFreq;
				oRtdata.m_oFaultCurCh.m_fMag = oRtdata.m_oCurCh[2].m_fMag;
				oRtdata.m_oFaultCurCh.m_fAng = oRtdata.m_oCurCh[2].m_fAng;
			}
				break;
			}
		}
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

			if(nMode == 4)
			{
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
				switch(nMode)
				{
				case 0:
				{
					oRtdata.m_oFaultVolCh.m_fFreq = oRtdata.m_oVolCh[0].m_fFreq;
					oRtdata.m_oFaultVolCh.m_fMag = pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[0][0];
					oRtdata.m_oFaultVolCh.m_fAng = pTmtGradientProcess->m_uiStepData[nActStepIndex].fU[0][1];
				}
					break;
				case 1:
				{
					oRtdata.m_oFaultCurCh.m_fFreq = oRtdata.m_oCurCh[0].m_fFreq;
					oRtdata.m_oFaultCurCh.m_fMag = pTmtGradientProcess->m_uiStepData[nActStepIndex].fI[0][0];
					oRtdata.m_oFaultCurCh.m_fAng = pTmtGradientProcess->m_uiStepData[nActStepIndex].fI[0][1];
				}
					break;
				case 2:
				{
					oRtdata.m_oFaultCurCh.m_fFreq = oRtdata.m_oCurCh[1].m_fFreq;
					oRtdata.m_oFaultCurCh.m_fMag = pTmtGradientProcess->m_uiStepData[nActStepIndex].fI[1][0];
					oRtdata.m_oFaultCurCh.m_fAng = pTmtGradientProcess->m_uiStepData[nActStepIndex].fI[1][1];
				}
					break;
				case 3:
				{
					oRtdata.m_oFaultCurCh.m_fFreq = oRtdata.m_oCurCh[2].m_fFreq;
					oRtdata.m_oFaultCurCh.m_fMag = pTmtGradientProcess->m_uiStepData[nActStepIndex].fI[2][0];
					oRtdata.m_oFaultCurCh.m_fAng = pTmtGradientProcess->m_uiStepData[nActStepIndex].fI[2][1];
				}
					break;
				}
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

			if(nMode == 4)
			{
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
			else
			{
				switch(nMode)
				{
				case 0:
				{
					oRtdata.m_oFaultVolCh.m_fFreq = oRtdata.m_oVolCh[0].m_fFreq;
					oRtdata.m_oFaultVolCh.m_fMag = m_oGradientParas.m_uiVOL[1][0].Harm[1].fAmp;
					oRtdata.m_oFaultVolCh.m_fAng = m_oGradientParas.m_uiVOL[1][0].Harm[1].fAngle;
				}
					break;
				case 1:
				{
					oRtdata.m_oFaultCurCh.m_fFreq = oRtdata.m_oCurCh[0].m_fFreq;
					oRtdata.m_oFaultCurCh.m_fMag = m_oGradientParas.m_uiCUR[1][0].Harm[1].fAmp;
					oRtdata.m_oFaultCurCh.m_fAng = m_oGradientParas.m_uiCUR[1][0].Harm[1].fAngle;
				}
					break;
				case 2:
				{
					oRtdata.m_oFaultCurCh.m_fFreq = oRtdata.m_oCurCh[1].m_fFreq;
					oRtdata.m_oFaultCurCh.m_fMag = m_oGradientParas.m_uiCUR[1][1].Harm[1].fAmp;
					oRtdata.m_oFaultCurCh.m_fAng = m_oGradientParas.m_uiCUR[1][1].Harm[1].fAngle;
				}
					break;
				case 3:
				{
					oRtdata.m_oFaultCurCh.m_fFreq = oRtdata.m_oCurCh[2].m_fFreq;
					oRtdata.m_oFaultCurCh.m_fMag = m_oGradientParas.m_uiCUR[1][2].Harm[1].fAmp;
					oRtdata.m_oFaultCurCh.m_fAng = m_oGradientParas.m_uiCUR[1][2].Harm[1].fAngle;
				}
					break;
				}
			}
		}
	}

	UpdateMonitorCur(oRtdata);

	if(oRtdata.m_nCurChCount>0||oRtdata.m_nVolChCount>0)
		stt_add_rtdatas(oRtdata);
#endif
}

void CSttULockOverCurrentTest::CalStepValue(tmt_GradientParas *pTmt_GradientParas,float fCurValue,int nHarmIndex)
{
#ifdef _PSX_QT_LINUX_
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
#endif

	int nPhaseRef[10]={1,2,0,2,0,1,2,0,1,0};
	float nAngle[10] = {0.0,-120.0,120,30.0,-120+30.0,120+30.0,30.0,-120+30.0,120+30.0,0.0};
	Complex p1,fV1,fV2,fV3,fI1,fI2,fI3;
	double fPhi,fV;

	fI1 = p1.polar(0,0.0);
	fI2 = p1.polar(0,0.0);
	fI3 = p1.polar(0,0.0);

	switch(m_oULockOverCurrentParas.m_nULockFaultType)
	{
	case ULOCK_FAULT_TYPE_LOW_VOLTAGE:

		if (m_oULockOverCurrentParas.m_nUSetMode == 1)//如果是线电压,需要将电压除以根号3
		{
			fCurValue /= SQRT3;
		}

		fV1 = p1.polar(fCurValue,0.0);
		fV2 = p1.polar(fCurValue,-120.0);
		fV3 = p1.polar(fCurValue,120.0);
		fI1 = p1.polar(m_oULockOverCurrentParas.m_fSCCurrent,-m_oULockOverCurrentParas.m_fImpAngle);
		fI2 = p1.polar(m_oULockOverCurrentParas.m_fSCCurrent,-120.0-m_oULockOverCurrentParas.m_fImpAngle);
		fI3 = p1.polar(m_oULockOverCurrentParas.m_fSCCurrent,120.0-m_oULockOverCurrentParas.m_fImpAngle);
		break;

	case ULOCK_FAULT_TYPE_NEG_SEQ_VOL:
        fPhi=(float)(atan2(3.0*pTmt_GradientParas->m_fEDU-6.0*fCurValue,sqrt(3.0)*pTmt_GradientParas->m_fEDU)*180.0f/XPI);
        fV1 = p1.polar((float)((3.0f*pTmt_GradientParas->m_fEDU-6.0f*fCurValue)/sqrt(3.0f)/2.0f/sin(fPhi*XPI/180.0f)),-90.0+fPhi);
        fV2 = p1.polar((float)((3.0f*pTmt_GradientParas->m_fEDU-6.0f*fCurValue)/sqrt(3.0f)/2.0f/sin(fPhi*XPI/180.0f)),-90.0-fPhi);
		fV3 = p1.polar(pTmt_GradientParas->m_fEDU,90.0);
		fI1 = p1.polar(m_oULockOverCurrentParas.m_fSCCurrent,0.0-m_oULockOverCurrentParas.m_fImpAngle);
		fI2 = p1.polar(m_oULockOverCurrentParas.m_fSCCurrent,180.0-m_oULockOverCurrentParas.m_fImpAngle);
		break;

	case ULOCK_FAULT_TYPE_LOW_CURRENT_A:
//		fPhi=fabs(atan2(m_oULockOverCurrentParas.m_fSCVoltage,pTmt_GradientParas->m_fEDU))*180.0/XPI;
        fPhi=atan2(m_oULockOverCurrentParas.m_fSCVoltage,pTmt_GradientParas->m_fEDU)*180.0/XPI;
		fV=m_oULockOverCurrentParas.m_fSCVoltage;
        fV2 = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
        fV3 = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
		fV1 = p1.polar(pTmt_GradientParas->m_fEDU,90.0);
		fI1 = p1.polar(fCurValue,0.0-m_oULockOverCurrentParas.m_fImpAngle);
		break;

	case ULOCK_FAULT_TYPE_LOW_CURRENT_B:
//		fPhi=fabs(atan2(m_oULockOverCurrentParas.m_fSCVoltage,pTmt_GradientParas->m_fEDU))*180.0/XPI;
        fPhi=atan2(m_oULockOverCurrentParas.m_fSCVoltage,pTmt_GradientParas->m_fEDU)*180.0/XPI;
		fV=m_oULockOverCurrentParas.m_fSCVoltage;
        fV3 = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
        fV1 = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
		fV2 = p1.polar(pTmt_GradientParas->m_fEDU,90.0);
		fI2 = p1.polar(fCurValue,0.0-m_oULockOverCurrentParas.m_fImpAngle);	
		break;

	case ULOCK_FAULT_TYPE_LOW_CURRENT_C:
//		fPhi=fabs(atan2(m_oULockOverCurrentParas.m_fSCVoltage,pTmt_GradientParas->m_fEDU))*180.0/XPI;
        fPhi=atan2(m_oULockOverCurrentParas.m_fSCVoltage,pTmt_GradientParas->m_fEDU)*180.0/XPI;
		fV=m_oULockOverCurrentParas.m_fSCVoltage;
        fV1 = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
        fV2 = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
		fV3 = p1.polar(pTmt_GradientParas->m_fEDU,90.0);
		fI3 = p1.polar(fCurValue,0.0-m_oULockOverCurrentParas.m_fImpAngle);
		break;

	default:
		break;
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

