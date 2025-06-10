#include "stdafx.h"
#include "SttLowVolActTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowVolActTest::m_strMacroName = "低压减载动作值测试";
CString CSttLowVolActTest::m_strMacroID = STT_MACRO_ID_PsuLowVolAct;
CString CSttLowVolActTest::m_strFilePostFix = "plva";
CString CSttLowVolActTest::m_strMacroVer ="1.0";

CSttLowVolActTest::CSttLowVolActTest() : CSttStateTest()
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

void CSttLowVolActTest::Init()
{ 
	CSttStateTest::Init();
	m_pStateTest->m_oStateParas.m_nStateNumbers = 3;
	m_pStateTest->m_oStateParas.init(3);
	m_nRunSearchCount = 1;
	m_nGradientCount = 0;
	tmt_LowVolParas::init();
	m_oResults.init();
}

CSttLowVolActTest::~CSttLowVolActTest(void)
{
}

void CSttLowVolActTest::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
	m_nGradientCount = fabs(m_fVstart-m_fVend)/m_fVstep;

	if (fabs((fabs(m_fVstart-m_fVend)-fabs(m_nGradientCount*m_fVstep)))>0.0001)
	{
		m_nGradientCount++;
	}
}

long CSttLowVolActTest::CalReport(UINT nState)
{
	m_oResults.m_nAct = 0;
	m_oResults.m_fLowUAct = 0.0f;

	if (m_fVstart>m_fVend)
	{
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct > 0))
		{
			m_oResults.m_nAct = 1;
			m_oResults.m_fLowUAct = m_fVstart-(m_nRunSearchCount-1)*m_fVstep;
		}
	} 
	else
	{
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 0)&&(m_nRunSearchCount>1))//20220722 zhouhj 从低值往高值搜索时,即从动作到不动作,至少保证动作一次
		{
			m_oResults.m_nAct = 1;
			m_oResults.m_fLowUAct = m_fVstart + (m_nRunSearchCount-1)*m_fVstep;
		}
	}

	if ((m_oResults.m_nAct == 1)&&(m_nRunSearchCount>m_nGradientCount))
	{
		m_oResults.m_fLowUAct = m_fVend;
	}

	return 0;
}

void CSttLowVolActTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_PsuLowVolAct(this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttLowVolActTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_PsuLowVolAct(&m_oResults, pXmlSerialize);
}

void CSttLowVolActTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_LowVol_search_results(this,&m_oResults, pXmlSerialize);
}

void CSttLowVolActTest::TranslateToStateParas()
{
  	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	m_pStateTest->m_oStateParas.m_fTao = 0;
	float fGradientTime = 0.0f,fLnDvDt = m_fDvdt;
  
   	//////////////////////////////////////////////////////////////////////////
   	//故障前状态
   	Complex p1;
   	Complex	oComplexUI[2][4];
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//计算故障前三相电压
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],1.2*m_fIAct,-78);//计算故障前三相电流
   	m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3],oComplexUI[0],0);
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[0],oComplexUI[0],oComplexUI[1]);
   
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
	m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut,m_binOut);
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
   	//////////////////////////////////////////////////////////////////////////
 	//故障状态
	float fEndVol = g_theSystemConfig->m_fFNom;
	m_pStateTest->m_oStateParas.m_paraState[1].m_nRampTimeGrad =  1;
	m_pStateTest->m_oStateParas.m_paraState[2].m_nRampTimeGrad =  1;

	if (m_fVstart>m_fVend)
	{
		fEndVol = m_fVstart-(m_nRunSearchCount-1)*m_fVstep;
	} 
	else
	{
		fEndVol = m_fVstart+(m_nRunSearchCount-1)*m_fVstep;
	}

	if (m_nRunSearchCount > m_nGradientCount)
	{
		fEndVol = m_fVend;
	}

	if (m_nUSetMode == 1)
	{
		fEndVol /= SQRT3;
		fLnDvDt = m_fDvdt/SQRT3;
	}

	m_fCurrSearchDvdt = fLnDvDt;
	fGradientTime = fabs(fStdLN_Vol-fEndVol)/fLnDvDt;
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1],oComplexUI[0],oComplexUI[1]);

	switch(m_nFaultType)
	{
	case 0://A相接地
	case 4://AB短路
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Ramp[0].fStep = fLnDvDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Ramp[0].fStepTime = 0.001f;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Ramp[0].fEnd = fEndVol;

		if (m_nUSetMode)
		{
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Ramp[0].fStep = fLnDvDt/1000;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Ramp[0].fEnd = fEndVol;
		}

		break;

	case 1://B相接地
	case 5://BC短路
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Ramp[0].fStep = fLnDvDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Ramp[0].fStepTime = 0.001f;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Ramp[0].fEnd = fEndVol;

		if (m_nUSetMode)
		{
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Ramp[0].fStep = fLnDvDt/1000;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Ramp[0].fEnd = fEndVol;
		}

		break;

	case 2://C相接地
	case 6://CA短路
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Ramp[0].fStep = fLnDvDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Ramp[0].fStepTime = 0.001f;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Ramp[0].fEnd = fEndVol;

		if (m_nUSetMode)
		{
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Ramp[0].fStep = fLnDvDt/1000;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Ramp[0].fEnd = fEndVol;
		}

		break;

	default:

		for (int nIndex = 0;nIndex<3;nIndex++)
		{
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt/1000;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fEnd = fEndVol;
		}

		break;
	}

	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1],m_binIn,m_nBinLogic);
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = fGradientTime + m_fHoldTime;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut,m_binOut);
 
 	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
 	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
 	}
 
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
	m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

	//////////////////////////////////////////////////////////////////////////
	//电压递边回稳态值

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[2],oComplexUI[0],oComplexUI[1]);

	switch(m_nFaultType)
	{
	case 0:
	case 4://AB短路
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[0].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[0].Ramp[0].fStep = fLnDvDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[0].Ramp[0].fStepTime = 0.001f;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[0].Harm[1].fAmp = fEndVol;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[0].Ramp[0].fEnd = fStdLN_Vol;

		if (m_nUSetMode)
		{
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[1].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[1].Ramp[0].fStep = fLnDvDt/1000;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[1].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[1].Harm[1].fAmp = fEndVol;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[1].Ramp[0].fEnd = fStdLN_Vol;
		}

		break;

	case 1:
	case 5://BC短路
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[1].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[1].Ramp[0].fStep = fLnDvDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[1].Ramp[0].fStepTime = 0.001f;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[1].Harm[1].fAmp = fEndVol;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[1].Ramp[0].fEnd = fStdLN_Vol;

		if (m_nUSetMode)
		{
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[2].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[2].Ramp[0].fStep = fLnDvDt/1000;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[2].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[2].Harm[1].fAmp = fEndVol;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[2].Ramp[0].fEnd = fStdLN_Vol;
		}

		break;

	case 2:
	case 6://CA短路
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[2].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[2].Ramp[0].fStep = fLnDvDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[2].Ramp[0].fStepTime = 0.001f;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[2].Harm[1].fAmp = fEndVol;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[2].Ramp[0].fEnd = fStdLN_Vol;

		if (m_nUSetMode)
		{
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[0].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[0].Ramp[0].fStep = fLnDvDt/1000;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[0].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[0].Harm[1].fAmp = fEndVol;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[0].Ramp[0].fEnd = fStdLN_Vol;
		}

		break;

	default:

		for (int nIndex = 0;nIndex<3;nIndex++)
		{
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].nIndex = 1;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt/1000;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Harm[1].fAmp = fEndVol;
			m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fEnd = fStdLN_Vol;
		}

		break;
	}

	m_pStateTest->m_oStateParas.m_paraState[2].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeState = fGradientTime + 0.5;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[2].m_binOut,m_binOut);

	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[2].m_binOut[nBoutIndex].fTimeTrig = 0;
	}

	m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeAfterTrigger = 0;
	m_pStateTest->m_oStateParas.m_paraState[2].m_bDC = FALSE;
	//////////////////////////////////////////////////////////////////////////
}

BOOL CSttLowVolActTest::IsGradientFinished()
{
	if (m_nGradientCount<=0)
	{
		return TRUE;
	}

	if (m_fVstart>m_fVend)
	{
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 0)&&(m_nRunSearchCount<=m_nGradientCount))
		{
			return FALSE;
		}

		return TRUE;
	} 
	else
	{
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 1)&&(m_nRunSearchCount<=m_nGradientCount))
		{
			return FALSE;
		}

		return TRUE;
	}
}

void CSttLowVolActTest::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
{
  	if (!IsGradientFinished())
  	{
  		CalNext();
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

void CSttLowVolActTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();

	if (m_nRunSearchCount == 1)//只有第一个测试点,需要下发开始测试命令,后续测试点不需要
	{
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
	}

	pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}

BOOL CSttLowVolActTest::CalNext()
{
	m_nRunSearchCount++;
	return TRUE;
}
