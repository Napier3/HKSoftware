#include "stdafx.h"
#include "SttLowFreqActTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowFreqActTest::m_strMacroName = "低周频率动作值测试";
CString CSttLowFreqActTest::m_strMacroID = STT_MACRO_ID_PsuLowFreqAct;
CString CSttLowFreqActTest::m_strFilePostFix = "plfa";
CString CSttLowFreqActTest::m_strMacroVer ="1.0";

CSttLowFreqActTest::CSttLowFreqActTest() : CSttStateTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
    Init();
}

void CSttLowFreqActTest::Init()
{ 
	CSttStateTest::Init();
	m_pStateTest->m_oStateParas.m_nStateNumbers = 3;
	m_pStateTest->m_oStateParas.init(3);
	m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
	m_nRunSearchCount = 1;
	m_nGradientCount = 0;
	tmt_LowFreqParas::init();
	m_oResults.init();
}

CSttLowFreqActTest::~CSttLowFreqActTest(void)
{
}

void CSttLowFreqActTest::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
	m_nGradientCount = fabs(m_fFstart-m_fFend)/m_fFstep;

	if (fabs((fabs(m_fFstart-m_fFend)-fabs(m_nGradientCount*m_fFstep)))>0.0001)
	{
		m_nGradientCount++;
	}

	m_fDrvDfDt = m_fDfdt;//最小允许0.001Hz/S
	m_fDrvStepTime = 0.001;
	double fDrvStep = m_fDrvDfDt / 1000;//1ms对应的步长
	if(fDrvStep < 0.0001)
	{
		BOOL bValid = FALSE;
		for(int i = 2;i <= 100;i++)
		{
			if(fDrvStep*i > 0.0001)
			{
				m_fDrvDfDt = fDrvStep*i*1000;
				m_fDrvStepTime = m_fDrvStepTime*i;
				bValid = TRUE;
				break;
			}
		}

		if(!bValid)
		{
			m_fDrvDfDt = 0.1;
			m_fDrvStepTime = 0.1;
		}
	}
}

long CSttLowFreqActTest::CalReport(UINT nState)
{
	m_oResults.m_nAct = 0;
	m_oResults.m_fLowFAct = 0.0f;

	if (m_fFstart>m_fFend)
	{
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct > 0))
		{
			m_oResults.m_nAct = 1;
			m_oResults.m_fLowFAct = m_fFstart-(m_nRunSearchCount-1)*m_fFstep;
		}
	} 
	else
	{
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 0)&&(m_nRunSearchCount>1))//20220722 zhouhj 从低值往高值搜索时,即从动作到不动作,至少保证动作一次
		{
			m_oResults.m_nAct = 1;
			m_oResults.m_fLowFAct = m_fFstart + (m_nRunSearchCount-1)*m_fFstep;
		}
	}

	if ((m_oResults.m_nAct == 1)&&(m_nRunSearchCount>m_nGradientCount))
	{
		m_oResults.m_fLowFAct = m_fFend;
	}

	return 0;
}

void CSttLowFreqActTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_PsuLowFreqAct(this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttLowFreqActTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_PsuLowFreqAct(&m_oResults, pXmlSerialize);
}

void CSttLowFreqActTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_LowFreq_search_results(this,&m_oResults, pXmlSerialize);
}

void CSttLowFreqActTest::TranslateToStateParas()
{
  	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	m_pStateTest->m_oStateParas.m_fTao = 0;
  
	m_fCurrSearchDfdt = m_fDfdt;
   	//////////////////////////////////////////////////////////////////////////
   	//故障前状态
   	Complex p1;
   	Complex	oComplexUI[2][4];
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//计算故障前三相电压
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],1.2*m_fILow,-78);//计算故障前三相电流
   	m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3],oComplexUI[0],0);
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[0],oComplexUI[0],oComplexUI[1]);
   
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
	m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut,m_binOut);
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
	m_pStateTest->m_oStateParas.m_paraState[1].m_nRampTimeGrad =  m_fDrvStepTime * 1000;
	m_pStateTest->m_oStateParas.m_paraState[2].m_nRampTimeGrad =  m_fDrvStepTime * 1000;
    //////////////////////////////////////////////////////////////////////////    
	//故障状态
	float fEndFreq = g_theSystemConfig->m_fFNom;

	if (m_fFstart>m_fFend)
	{
		fEndFreq = m_fFstart-(m_nRunSearchCount-1)*m_fFstep;
	} 
	else
	{
		fEndFreq = m_fFstart+(m_nRunSearchCount-1)*m_fFstep;
	}

	if (m_nRunSearchCount > m_nGradientCount)
	{
		fEndFreq = m_fFend;
	}

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1],oComplexUI[0],oComplexUI[1]);

	for (int nIndex = 0;nIndex<3;nIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].fStep = m_fDrvDfDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].fStep = m_fDrvDfDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;

		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].fEnd = fEndFreq;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].fEnd = fEndFreq;
    }	

	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1],m_binIn,m_nBinLogic);
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = fabs(g_theSystemConfig->m_fFNom-fEndFreq)/m_fDfdt + m_fHoldTime;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut,m_binOut);
 
 	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
 	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
 	}
 
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
	m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

	//////////////////////////////////////////////////////////////////////////
	//频率递边回稳态值

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[2],oComplexUI[0],oComplexUI[1]);

	for (int nIndex = 0;nIndex<3;nIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[nIndex].Ramp[2].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[2].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[nIndex].Ramp[2].fStep = m_fDrvDfDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[2].fStep = m_fDrvDfDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;

		m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[nIndex].Harm[1].fFreq = fEndFreq;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Harm[1].fFreq = fEndFreq;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[nIndex].Ramp[2].fEnd = g_theSystemConfig->m_fFNom;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[2].fEnd = g_theSystemConfig->m_fFNom;
	}

	m_pStateTest->m_oStateParas.m_paraState[2].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeState = fabs(g_theSystemConfig->m_fFNom-fEndFreq)/m_fDfdt + 0.5;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[2].m_binOut,m_binOut);

	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[2].m_binOut[nBoutIndex].fTimeTrig = 0;
	}

	m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeAfterTrigger = 0;
	m_pStateTest->m_oStateParas.m_paraState[2].m_bDC = FALSE;

	//////////////////////////////////////////////////////////////////////////
}

BOOL CSttLowFreqActTest::IsGradientFinished()
{
	if (m_nGradientCount<=0)
	{
		return TRUE;
	}

	if (m_fFstart>m_fFend)
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

void CSttLowFreqActTest::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
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

void CSttLowFreqActTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
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

BOOL CSttLowFreqActTest::CalNext()
{
	m_nRunSearchCount++;
	return TRUE;
}
