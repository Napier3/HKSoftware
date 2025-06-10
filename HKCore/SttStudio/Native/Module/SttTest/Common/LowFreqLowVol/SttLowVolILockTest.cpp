#include "stdafx.h"
#include "SttLowVolILockTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowVolILockTest::m_strMacroName = "低压低电流闭锁值测试";
CString CSttLowVolILockTest::m_strMacroID = STT_MACRO_ID_PsuLowVolILock;
CString CSttLowVolILockTest::m_strFilePostFix = "olvi";
CString CSttLowVolILockTest::m_strMacroVer ="1.0";

CSttLowVolILockTest::CSttLowVolILockTest() : CSttLowVolActTest()
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

void CSttLowVolILockTest::Init()
{ 
	CSttLowVolActTest::Init();
}

CSttLowVolILockTest::~CSttLowVolILockTest(void)
{

}

void CSttLowVolILockTest::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
	m_nGradientCount = fabs(m_fIEnd-m_fIStart)/m_fIStep/*+1*/;

	if (fabs((fabs(m_fIEnd-m_fIStart)-fabs(m_nGradientCount*m_fIStep)))>0.0001)
	{
		m_nGradientCount++;
	}
}

long CSttLowVolILockTest::CalReport(UINT nState)
{
	m_oResults.m_nAct = 0;
	m_oResults.m_fIAct = 0.0f;

	if (m_fIEnd>m_fIStart)
	{
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct > 0))
		{
			m_oResults.m_nAct = 1;
			m_oResults.m_fIAct = m_fIStart+(m_nRunSearchCount-1)*m_fIStep;
		}
	} 
	else
	{
		if ((m_pStateTest->m_oStateResults.m_resultState[1].m_nAct == 0)&&(m_nRunSearchCount>1))////20220722 zhouhj 从高值往低值搜索时,即从不闭锁到闭锁,从动作到不动作,至少保证动作一次
		{
			m_oResults.m_nAct = 1;
			m_oResults.m_fIAct = m_fIStart - (m_nRunSearchCount-1)*m_fIStep;
		}
	}

	if ((m_oResults.m_nAct == 1)&&(m_nRunSearchCount>m_nGradientCount))
	{
		m_oResults.m_fIAct = m_fIEnd;
	}

	return 0;
}

void CSttLowVolILockTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_PsuLowVolILock(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttLowVolILockTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_PsuLowVolILock(&m_oResults, pXmlSerialize);
}

void CSttLowVolILockTest::TranslateToStateParas()
{
  	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	m_pStateTest->m_oStateParas.m_fTao = 0;
	float fGradientTime = 0.0f, fLnDvDt = m_fDvdt, fLnEndVol = m_fVend;
  
   	//////////////////////////////////////////////////////////////////////////
   	//故障前状态
   	Complex p1;
   	Complex	oComplexUI[2][4];
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//计算故障前三相电压
	//zhouhj 2024.4.7 将故障前非测试相电流修改为闭锁电流的1.2倍
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],1.2*m_fIAct,-78);//计算故障前三相电流
   	m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3],oComplexUI[0],0);
	float fPreFaultCur = 0;

	if (m_fIEnd>m_fIStart)
	{
		fPreFaultCur = m_fIStart;
	} 
	else
	{
		fPreFaultCur = m_fIEnd;
	}

	if ((m_nIPhase>=0)&&(m_nIPhase<3))
	{
		oComplexUI[1][m_nIPhase].SetMag(fPreFaultCur);
	} 
	else
	{
		oComplexUI[1][0].SetMag(fPreFaultCur);
		oComplexUI[1][1].SetMag(fPreFaultCur);
		oComplexUI[1][2].SetMag(fPreFaultCur);
	}

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[0],oComplexUI[0],oComplexUI[1]);
   
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
	m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut,m_binOut);
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
   	//////////////////////////////////////////////////////////////////////////
 	//故障状态
	float fCurI_Amp = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[1].m_nRampTimeGrad =  1;
	m_pStateTest->m_oStateParas.m_paraState[2].m_nRampTimeGrad =  1;

	if(m_nUSetMode == 1)
	{
		fLnDvDt = m_fDvdt / SQRT3;
		fLnEndVol = m_fVend / SQRT3;
	}

	m_fCurrSearchDvdt = fLnDvDt;
	fGradientTime = fabs(fStdLN_Vol - fLnEndVol) / fLnDvDt;

	if (m_nRunSearchCount > m_nGradientCount)
	{
		fCurI_Amp = m_fIEnd;
	}
	else if (m_fIEnd>m_fIStart)
	{
		fCurI_Amp = m_fIStart + (m_nRunSearchCount-1)*m_fIStep;
	} 
	else
	{
		fCurI_Amp = m_fIStart - (m_nRunSearchCount-1)*m_fIStep;
	}

	if ((m_nIPhase>=0)&&(m_nIPhase<3))
	{
		oComplexUI[1][m_nIPhase].SetMag(fCurI_Amp);
	} 
	else
	{
		oComplexUI[1][0].SetMag(fCurI_Amp);
		oComplexUI[1][1].SetMag(fCurI_Amp);
		oComplexUI[1][2].SetMag(fCurI_Amp);
	}
//	oComplexUI[1][m_nIPhase].SetMag(fCurI_Amp);

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1],oComplexUI[0],oComplexUI[1]);

	for (int nIndex = 0;nIndex<3;nIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fEnd = fLnEndVol;
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
	//频率递边回稳态值
	if ((m_nIPhase>=0)&&(m_nIPhase<3))
	{
		oComplexUI[1][m_nIPhase].SetMag(fPreFaultCur);
	} 
	else
	{
		oComplexUI[1][0].SetMag(fPreFaultCur);
		oComplexUI[1][1].SetMag(fPreFaultCur);
		oComplexUI[1][2].SetMag(fPreFaultCur);
	}
//	oComplexUI[1][m_nIPhase].SetMag(fPreFaultCur);

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[2],oComplexUI[0],oComplexUI[1]);

	for (int nIndex = 0;nIndex<3;nIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt/1000;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;

		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Harm[1].fAmp = fLnEndVol;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fEnd = fStdLN_Vol;
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

BOOL CSttLowVolILockTest::IsGradientFinished()
{
	if (m_nGradientCount<=0)
	{
		return TRUE;
	}

	if (m_fIEnd > m_fIStart)
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
