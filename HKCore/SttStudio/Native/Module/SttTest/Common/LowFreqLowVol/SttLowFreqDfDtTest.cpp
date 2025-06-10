#include "stdafx.h"
#include "SttLowFreqDfDtTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowFreqDfDtTest::m_strMacroName = "低周滑差闭锁值测试";
CString CSttLowFreqDfDtTest::m_strMacroID = STT_MACRO_ID_PsuLowFreqDfdt;
CString CSttLowFreqDfDtTest::m_strFilePostFix = "olfd";
CString CSttLowFreqDfDtTest::m_strMacroVer ="1.0";

CSttLowFreqDfDtTest::CSttLowFreqDfDtTest() : CSttLowFreqActTest()
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

void CSttLowFreqDfDtTest::Init()
{ 
	CSttLowFreqActTest::Init();
}

CSttLowFreqDfDtTest::~CSttLowFreqDfDtTest(void)
{

}

void CSttLowFreqDfDtTest::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
	m_nGradientCount = fabs(m_fDfdtStart-m_fDfdtEnd)/m_fDfdtStep;

	if (fabs((fabs(m_fDfdtStart-m_fDfdtEnd)-fabs(m_nGradientCount*m_fDfdtStep)))>0.0001)
	{
		m_nGradientCount++;
	}
}

long CSttLowFreqDfDtTest::CalReport(UINT nState)
{
	m_oResults.m_nAct = 0;
	m_oResults.m_fDfdtAct = 0.0f;

	if (m_fDfdtStart>m_fDfdtEnd)
	{
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct > 0))
		{
			m_oResults.m_nAct = 1;
			m_oResults.m_fDfdtAct = m_fDfdtStart-(m_nRunSearchCount-1)*m_fDfdtStep;
		}
	} 
	else
	{
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 0)&&(m_nRunSearchCount>1))//20220722 zhouhj 从低值往高值搜索时,即从不闭锁搜索到闭锁,从动作到不动作,至少保证动作一次
		{
			m_oResults.m_nAct = 1;
			m_oResults.m_fDfdtAct = m_fDfdtStart + (m_nRunSearchCount-1)*m_fDfdtStep;
		}
	}

	if ((m_oResults.m_nAct == 1)&&(m_nRunSearchCount>m_nGradientCount))
	{
		m_oResults.m_fDfdtAct = m_fDfdtEnd;
	}

	return 0;
}

void CSttLowFreqDfDtTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_PsuLowFreqDfDt(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttLowFreqDfDtTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_PsuLowFreqDfDt(&m_oResults, pXmlSerialize);
}

void CSttLowFreqDfDtTest::TranslateToStateParas()
{
  	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	m_pStateTest->m_oStateParas.m_fTao = 0;
  
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
   	//////////////////////////////////////////////////////////////////////////
 	//故障状态
    float fCurDfDt = 0.0f;	

	if (m_nRunSearchCount > m_nGradientCount)
	{
		fCurDfDt = m_fDfdtEnd;
	}
	else if (m_fDfdtStart>m_fDfdtEnd)
	{
		fCurDfDt = m_fDfdtStart - (m_nRunSearchCount-1)*m_fDfdtStep;
	} 
	else
	{
		fCurDfDt = m_fDfdtStart + (m_nRunSearchCount-1)*m_fDfdtStep;
	}

	m_fDrvDfDt = fCurDfDt;
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
	m_pStateTest->m_oStateParas.m_paraState[1].m_nRampTimeGrad =  m_fDrvStepTime * 1000;
	m_pStateTest->m_oStateParas.m_paraState[2].m_nRampTimeGrad =  m_fDrvStepTime * 1000;

	m_fCurrSearchDfdt = fCurDfDt;
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1],oComplexUI[0],oComplexUI[1]);

	for (int nIndex = 0;nIndex<3;nIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].fStep = m_fDrvDfDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].fStep = m_fDrvDfDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;

		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].fEnd = m_fFend;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].fEnd = m_fFend;
	}

	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1],m_binIn,m_nBinLogic);
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = fabs(g_theSystemConfig->m_fFNom-m_fFend)/fCurDfDt + m_fHoldTime;
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

		m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[nIndex].Harm[1].fFreq = m_fFend;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Harm[1].fFreq = m_fFend;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[nIndex].Ramp[2].fEnd = g_theSystemConfig->m_fFNom;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[2].fEnd = g_theSystemConfig->m_fFNom;
	}

	m_pStateTest->m_oStateParas.m_paraState[2].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeState = fabs(g_theSystemConfig->m_fFNom-m_fFend)/fCurDfDt + 0.5;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[2].m_binOut,m_binOut);

	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[2].m_binOut[nBoutIndex].fTimeTrig = 0;
	}

	m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeAfterTrigger = 0;
	m_pStateTest->m_oStateParas.m_paraState[2].m_bDC = FALSE;

	//////////////////////////////////////////////////////////////////////////
}

BOOL CSttLowFreqDfDtTest::IsGradientFinished()
{
	if (m_nGradientCount<=0)
	{
		return TRUE;
	}

	if (m_fDfdtStart>m_fDfdtEnd)
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
