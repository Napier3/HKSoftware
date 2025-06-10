#include "stdafx.h"
#include "SttDcIncrementTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDcIncrementTest::m_strMacroName = "直流增量保护专项测试";
CString CSttDcIncrementTest::m_strMacroID = STT_MACRO_ID_DcIncrementTest;
CString CSttDcIncrementTest::m_strFilePostFix = "dcict";
CString CSttDcIncrementTest::m_strMacroVer ="1.0";

CSttDcIncrementTest::CSttDcIncrementTest() : CSttStateTest()
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

void CSttDcIncrementTest::Init()
{ 
	CSttStateTest::Init();
	tmt_DcIncrementParas::init();
	m_oResults.init();
// 	m_nRunSearchCount = 1;
// 	m_nGradientCount = 0;
	m_pStateTest->m_oStateParas.m_nStateNumbers = g_nStateCount;
}

CSttDcIncrementTest::~CSttDcIncrementTest(void)
{
}

void CSttDcIncrementTest::AfterSetParameter()
{
 	CSttStateTest::AfterSetParameter();
	InitSearch();

// 	if (m_nGradSelected)
// 	{
// 		m_nGradientCount = fabs(m_fScanFrom-m_fScanTo)/m_fStep;
// 
// 		if (fabs((fabs(m_fScanFrom-m_fScanTo)-fabs(m_nGradientCount*m_fStep)))>0.0001)
// 		{
// 			m_nGradientCount++;
// 		}
// 	}
// 	else
// 	{
// 		m_nGradientCount = 0;
// 	}
}

long CSttDcIncrementTest::GetDcIncActTime(float &fAcgtTime)
{
	if (m_nTimingCurveIndex>= m_nCurveNum)
	{
		return 0;
	}

	long nStateIndex = m_nTimingCurveIndex+1;
	long nActFlag = 0;
	fAcgtTime = 0.0f;

	for (;nStateIndex < m_pStateTest->m_oStateParas.m_nStateNumbers;nStateIndex++)
	{
		if (m_pStateTest->m_oStateResults.m_resultState[nStateIndex].m_nAct)
		{
			fAcgtTime += (m_pStateTest->m_oStateResults.m_resultState[nStateIndex].m_frTestTime + ((float)m_pStateTest->m_oStateResults.m_resultState[nStateIndex].m_nCurStepIndex)/1000);
// 			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("State%ld,m_frTestTime=%f,fAcgtTime=%f,m_nCurStepIndex=%d."),nStateIndex,m_pStateTest->m_oStateResults.m_resultState[nStateIndex].m_frTestTime,fAcgtTime
// 				,m_pStateTest->m_oStateResults.m_resultState[nStateIndex].m_nCurStepIndex);
			nActFlag = 1;
			break;
		}

		fAcgtTime += m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_fTimeState;
	}

	return nActFlag;
}

long CSttDcIncrementTest::CalReport(UINT nState)
{
	m_oResults.m_nAct = 0;

	if (m_nTimingCurveIndex>= m_nCurveNum)
	{
		return 0;
	}

	long nStateIndex = m_nTimingCurveIndex+1;
//	double dActTime = 0.0f;
	long nActFlag = GetDcIncActTime(m_oResults.m_fActTime);


	//如果是非递变模式,返回动作标记及动作时间
	if (!m_nGradSelected)
	{
		m_oResults.m_nAct = nActFlag;
		return 0;
	}

	if (IsAct())
	{
		m_oResults.m_fActValue = GetActValue();
		m_oResults.m_nAct = 1;
	} 
	else
	{
		m_oResults.m_fActValue = 0.0f;
		m_oResults.m_nAct = 0;
	}

	//以下为递变模式
// 	if (m_fScanFrom>m_fScanTo)
// 	{
// 		if (nActFlag)
// 		{
// 			m_oResults.m_nAct = 1;
// 			m_oResults.m_fActValue = m_fScanFrom-(m_nRunSearchCount-1)*m_fStep;
// 		}
// 	} 
// 	else
// 	{
// 		if (nActFlag == 0)
// 		{
// 			m_oResults.m_nAct = 1;
// 			m_oResults.m_fActValue = m_fScanFrom + (m_nRunSearchCount-1)*m_fStep;
// 		}
// 	}
// 
// 	if ((m_oResults.m_nAct == 1)&&(m_nRunSearchCount>m_nGradientCount))
// 	{
// 		m_oResults.m_fActValue = m_fScanTo;
// 	}

	return 0;
}

void CSttDcIncrementTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_DcIncrement(this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttDcIncrementTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_DcIncrement(&m_oResults, pXmlSerialize);
}

void CSttDcIncrementTest::TranslateToStateParas()
{
  	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	m_pStateTest->m_oStateParas.m_fTao = 0;
    	//////////////////////////////////////////////////////////////////////////
	if (m_nCurveNum >= g_nStateCount)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("当前曲线数(%ld),超出最大曲线数量(%ld),强制设置为%ld."),m_nCurveNum,(g_nStateCount-1),(g_nStateCount-1));
		m_nCurveNum = g_nStateCount - 1;
	}
 
	m_pStateTest->m_oStateParas.m_nStateNumbers = m_nCurveNum + 1;
   	//////////////////////////////////////////////////////////////////////////
	double dCurrGradientValue = m_fCurrScanVal;

// 	if (m_fScanFrom>m_fScanTo)
// 	{
// 		dCurrGradientValue = m_fScanFrom-(m_nRunSearchCount-1)*m_fStep;
// 	} 
// 	else
// 	{
// 		dCurrGradientValue = m_fScanFrom+(m_nRunSearchCount-1)*m_fStep;
// 	}

   	//////////////////////////////////////////////////////////////////////////
   	//准备时间输出状态
	float oAngValue[3] = {0.0f,-120.0f,120.0f};
	int nChIndex = 0;

	for (nChIndex = 0;nChIndex<3;nChIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nChIndex].Harm[1].fAmp = m_fVolAmp[nChIndex];
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nChIndex].Ramp[0].fEnd = m_fVolAmp[nChIndex];
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nChIndex].Harm[1].fAmp = m_fCurAmp[nChIndex];
		//准备时间输出状态的递变结束幅值与当前输出的幅值一致,用于曲线输出状态循环遍历,不影响实际输出
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nChIndex].Ramp[0].fEnd = m_fCurAmp[nChIndex];

		m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nChIndex].Harm[1].fAngle = oAngValue[nChIndex];
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nChIndex].Harm[1].fAngle = oAngValue[nChIndex];
	}

	m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[3].Harm[1].fAmp = m_fVolAmp[nChIndex];
	m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[3].Ramp[0].fEnd = m_fVolAmp[nChIndex];

	m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = TRUE;

	//如果是初值递变,在此处重新设置初值
	if (m_nGradSelected && (m_nGradType == STT_DC_INCREMENT_GradType_InitValue))
	{
		switch(m_nGradientChIndex)
		{
		case _STT_DC_INCREMENT_GradientIndex_Ua:
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[0].Harm[1].fAmp = dCurrGradientValue;
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[0].Ramp[0].fEnd = dCurrGradientValue;
			break;

		case _STT_DC_INCREMENT_GradientIndex_Ub:
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[1].Harm[1].fAmp = dCurrGradientValue;
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[1].Ramp[0].fEnd = dCurrGradientValue;
			break;

		case _STT_DC_INCREMENT_GradientIndex_Uc:
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[2].Harm[1].fAmp = dCurrGradientValue;
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[2].Ramp[0].fEnd = dCurrGradientValue;
			break;
		case _STT_DC_INCREMENT_GradientIndex_Uz:
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[3].Harm[1].fAmp = dCurrGradientValue;
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[3].Ramp[0].fEnd = dCurrGradientValue;
			break;
		case _STT_DC_INCREMENT_GradientIndex_Ia:
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Harm[1].fAmp = dCurrGradientValue;
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Ramp[0].fEnd = dCurrGradientValue;
			break;

		case _STT_DC_INCREMENT_GradientIndex_Ib:
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[1].Harm[1].fAmp = dCurrGradientValue;
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[1].Ramp[0].fEnd = dCurrGradientValue;
			break;

		case _STT_DC_INCREMENT_GradientIndex_Ic:
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[2].Harm[1].fAmp = dCurrGradientValue;
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[2].Ramp[0].fEnd = dCurrGradientValue;
			break;

// 		case _STT_DC_INCREMENT_GradientIndex_Iab:
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Harm[1].fAmp = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Ramp[0].fEnd = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[1].Harm[1].fAmp = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[1].Ramp[0].fEnd = dCurrGradientValue;
// 			break;
// 
// 		case _STT_DC_INCREMENT_GradientIndex_Ibc:
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[1].Harm[1].fAmp = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[1].Ramp[0].fEnd = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[2].Harm[1].fAmp = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[2].Ramp[0].fEnd = dCurrGradientValue;
// 			break;
// 
// 		case _STT_DC_INCREMENT_GradientIndex_Ica:
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[2].Harm[1].fAmp = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[2].Ramp[0].fEnd = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Harm[1].fAmp = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Ramp[0].fEnd = dCurrGradientValue;
// 			break;
// 
// 		case _STT_DC_INCREMENT_GradientIndex_Iabc:
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Harm[1].fAmp = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Ramp[0].fEnd = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[1].Harm[1].fAmp = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[1].Ramp[0].fEnd = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[2].Harm[1].fAmp = dCurrGradientValue;
// 			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[2].Ramp[0].fEnd = dCurrGradientValue;
// 			break;

		default:
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Harm[1].fAmp = dCurrGradientValue;
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Ramp[0].fEnd = dCurrGradientValue;

			break;
		}
	}
   
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPrepTime;
	m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut,m_binOut);
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
//	m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = TRUE;
    	//////////////////////////////////////////////////////////////////////////
  	//特性曲线输出状态
	double dCurrOutputTime = 0.0f;
	double dCurrDaDt = 0.0f;

	for (int nStateIndex = 1;nStateIndex<m_pStateTest->m_oStateParas.m_nStateNumbers;nStateIndex++)
	{
		for (nChIndex = 0;nChIndex<3;nChIndex++)
		{
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[nChIndex].Harm[1].fAmp = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiVOL[nChIndex].Ramp[0].fEnd;//m_fVolAmp[nChIndex];
			//特性曲线每个状态的开始输出的幅值与上一个状态递变结束的幅值保持一致
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[nChIndex].Harm[1].fAmp = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[nChIndex].Ramp[0].fEnd;//m_fCurAmp[nChIndex]; 

			//先将当前状态结束的幅值与开始输出的幅值设置为一致,如当前通道为递变通道,该结束幅值会重新赋值
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[nChIndex].Ramp[0].fEnd = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiVOL[nChIndex].Ramp[0].fEnd;

			//先将当前状态结束的幅值与开始输出的幅值设置为一致,如当前通道为递变通道,该结束幅值会重新赋值
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[nChIndex].Ramp[0].fEnd = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[nChIndex].Ramp[0].fEnd;

			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[nChIndex].Harm[1].fAngle = oAngValue[nChIndex];
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[nChIndex].Harm[1].fAngle = oAngValue[nChIndex];
		}

		m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[3].Harm[1].fAmp = 
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiVOL[3].Ramp[0].fEnd;//m_fVolAmp[3];
		//先将当前状态结束的幅值与开始输出的幅值设置为一致,如当前通道为递变通道,该结束幅值会重新赋值
		m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[3].Ramp[0].fEnd = 
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiVOL[3].Ramp[0].fEnd;

		m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_bDC = TRUE;
		dCurrOutputTime = m_fOutputTime[nStateIndex-1]/1000;
		dCurrDaDt = m_fDaDt[nStateIndex-1];
		m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_fTimeState = dCurrOutputTime;
		Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[nStateIndex],m_binIn,m_nBinLogic);
		SetStateBout(m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_binOut,m_binOut);
		m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_fTimeAfterTrigger = 0.0f;
//		m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_bDC = FALSE;
		m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_nRampTimeGrad =  1;

		if (m_nTimingCurveIndex > (nStateIndex-1))
		{
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		}

		if (m_nGradSelected && (m_nGradType == STT_DC_INCREMENT_GradType_RiseTime)&&(m_nGradCurveSel == (nStateIndex - 1)))
		{
			dCurrOutputTime = dCurrGradientValue/1000;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_fTimeState = dCurrOutputTime;
		}
		else if (m_nGradSelected && (m_nGradType == STT_DC_INCREMENT_GradType_Slope)&&(m_nGradCurveSel == (nStateIndex - 1)))
		{
			dCurrDaDt = dCurrGradientValue;
		}

		switch(m_nGradientChIndex)
		{
		case _STT_DC_INCREMENT_GradientIndex_Ua:
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[0].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[0].Ramp[0].fStep = dCurrDaDt;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[0].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[0].Ramp[0].fEnd = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiVOL[0].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
			break;

		case _STT_DC_INCREMENT_GradientIndex_Ub:
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[1].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[1].Ramp[0].fStep = dCurrDaDt;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[1].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[1].Ramp[0].fEnd = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiVOL[1].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
			break;

		case _STT_DC_INCREMENT_GradientIndex_Uc:
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[2].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[2].Ramp[0].fStep = dCurrDaDt;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[2].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[2].Ramp[0].fEnd = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiVOL[2].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
			break;

		case _STT_DC_INCREMENT_GradientIndex_Uz:
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[3].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[3].Ramp[0].fStep = dCurrDaDt;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[3].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiVOL[3].Ramp[0].fEnd = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiVOL[3].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
			break;

		case _STT_DC_INCREMENT_GradientIndex_Ia:
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fStep = dCurrDaDt;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fEnd = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[0].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
			break;

		case _STT_DC_INCREMENT_GradientIndex_Ib:
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[0].fStep = dCurrDaDt;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[0].fEnd = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[1].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
			break;

		case _STT_DC_INCREMENT_GradientIndex_Ic:
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].fStep = dCurrDaDt;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].fEnd = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[2].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
			break;

// 		case _STT_DC_INCREMENT_GradientIndex_Iab:
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].nIndex = 1;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fStep = dCurrDaDt;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fStepTime = 0.001f;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fEnd = 
// 				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[0].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
// 
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].nIndex = 1;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].fStep = dCurrDaDt;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].fStepTime = 0.001f;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].fEnd = 
// 				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[1].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
// 			break;
// 
// 		case _STT_DC_INCREMENT_GradientIndex_Ibc:
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].nIndex = 1;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].fStep = dCurrDaDt;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].fStepTime = 0.001f;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].fEnd = 
// 				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[1].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
// 
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].nIndex = 1;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].fStep = dCurrDaDt;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].fStepTime = 0.001f;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].fEnd = 
// 				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[2].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
// 			break;
// 
// 		case _STT_DC_INCREMENT_GradientIndex_Ica:
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[1].nIndex = 1;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[1].fStep = dCurrDaDt;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[1].fStepTime = 0.001f;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[1].fEnd = 
// 				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[2].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
// 
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].nIndex = 1;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fStep = dCurrDaDt;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fStepTime = 0.001f;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fEnd = 
// 				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[0].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
// 			break;
// 
// 		case _STT_DC_INCREMENT_GradientIndex_Iabc:
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].nIndex = 1;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fStep = dCurrDaDt;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fStepTime = 0.001f;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fEnd = 
// 				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[0].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
// 
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].nIndex = 1;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].fStep = dCurrDaDt;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].fStepTime = 0.001f;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[1].Ramp[1].fEnd = 
// 				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[1].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
// 
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].nIndex = 1;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].fStep = dCurrDaDt;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].fStepTime = 0.001f;
// 			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[2].Ramp[0].fEnd = 
// 				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[2].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;
// 			break;

		default:

			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fStep = dCurrDaDt;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_uiCUR[0].Ramp[0].fEnd = 
				m_pStateTest->m_oStateParas.m_paraState[nStateIndex-1].m_uiCUR[0].Ramp[0].fEnd + dCurrDaDt*dCurrOutputTime*1000;

			break;
		}
	}
// 	//////////////////////////////////////////////////////////////////////////
}

// BOOL CSttDcIncrementTest::IsGradientFinished()
// {
// 	if (m_nGradientCount<=0)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (m_fScanFrom>m_fScanTo/*m_fGradEndValue*/)
// 	{
// 		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 0)&&(m_nRunSearchCount<=m_nGradientCount))
// 		{
// 			return FALSE;
// 		}
// 
// 		return TRUE;
// 	} 
// 	else
// 	{
// 		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 1)&&(m_nRunSearchCount<=m_nGradientCount))
// 		{
// 			return FALSE;
// 		}
// 
// 		return TRUE;
// 	}
// }

void CSttDcIncrementTest::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
{
// 	if (!IsGradientFinished())
// 	{
// 		CalNext();
// 		TranslateToStateParas();
// 
// 		StartTest();//后续开始测试操作
// 		return;
// 	}

	float fActTime = 0.0f;

	if (m_nGradSelected && (!IsSearchFinished(GetDcIncActTime(fActTime)/*m_pStateTest->m_oStateResults.m_resultState[1].m_nAct*/)))
	{
		CSttStateTest::AfterSetParameter();
		SearchNext();
		TranslateToStateParas();
		StartTest();//后续开始测试操作
		return;
	}

	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;
	CalReport();//zhouhj 20210613在返回测试结束消息时,计算报告结果值
	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
	SetTestStarting(FALSE);
}

void CSttDcIncrementTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
//	stt_xml_serialize_dc_search_results(this,&m_oResults, pXmlSerialize);
}

void CSttDcIncrementTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
// 	if (m_nRunSearchCount > 1)//只有第一个测试点,需要下发开始测试命令,后续测试点不需要
// 	{
// 		return;
// 	}

	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();

	if (m_nStepIndex == 0)//只有第一个测试点,需要下发开始测试命令,后续测试点不需要
	{
		pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
	}

//	pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
//	pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
}
// 
// BOOL CSttDcIncrementTest::CalNext()
// {
// 	m_nRunSearchCount++;
// 	return TRUE;
// }

void CSttDcIncrementTest::SyncSingleStateTmtResult()
{
	CSttStateTest::SyncSingleStateTmtResult();

#ifdef _PSX_QT_LINUX_
	GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;

	if (oRampRestCom.m_nAct)
	{
		 CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
	}
#endif
}

