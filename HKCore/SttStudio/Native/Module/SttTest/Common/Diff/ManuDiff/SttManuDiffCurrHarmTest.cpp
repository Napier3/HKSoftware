#include "stdafx.h"
#include "SttManuDiffCurrHarmTest.h"
#include "../../SttSystemConfig.h"
#include "../../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttManuDiffCurrHarmTest::m_strMacroName = "差动谐波制动搜索(手动递变)";
CString CSttManuDiffCurrHarmTest::m_strMacroID = STT_MACRO_ID_PsuManuDiffHarmTest;
CString CSttManuDiffCurrHarmTest::m_strFilePostFix = "pdffhtst";
CString CSttManuDiffCurrHarmTest::m_strMacroVer ="1.0";

CSttManuDiffCurrHarmTest::CSttManuDiffCurrHarmTest() : CSttManuDiffCurrThrTest()
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

CSttManuDiffCurrHarmTest::~CSttManuDiffCurrHarmTest(void)
{

}

long CSttManuDiffCurrHarmTest::CalReport(UINT nState)
{
	if (IsAct())
	{
		m_oResults.m_fIrCoef = GetActValue()/100;
		m_oResults.m_nActFlag = 1;
		ChannelUI_Diff *pDiffChs = m_oDiffCalTool.GetChannelCurrents();
		m_oResults.m_fIRbase[0] = pDiffChs[0].famptitude;
		m_oResults.m_fIRbase[1] = pDiffChs[1].famptitude;
		m_oResults.m_fIRbase[2] = pDiffChs[2].famptitude;

		m_oResults.m_fIharm[0] = pDiffChs[0].famptitude*m_oResults.m_fIrCoef;
		m_oResults.m_fIharm[1] = pDiffChs[1].famptitude*m_oResults.m_fIrCoef;
		m_oResults.m_fIharm[2] = pDiffChs[2].famptitude*m_oResults.m_fIrCoef;
	} 
	else
	{
		m_oResults.m_fIrCoef = 0.0f;
		m_oResults.m_nActFlag = 0;
	}

	return 0;
}

void CSttManuDiffCurrHarmTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_harm(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttManuDiffCurrHarmTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_harm(&m_oResults, pXmlSerialize);
}

void CSttManuDiffCurrHarmTest::AfterSetParameter()
{
	CSttManuDiffCurrThrTest::AfterSetParameter();
}

void CSttManuDiffCurrHarmTest::TranslateToStateParas()
{
 	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
 
 	//////////////////////////////////////////////////////////////////////////
 	//故障前状态
 	InitManuDiffParas_6U6I();//在此函数中设置故障前电压电流、开入开出等,并设置故障态电压值
 	//////////////////////////////////////////////////////////////////////////
 	//故障状态
 	m_oDiffCalTool.CurrentCal(&m_fIdiff,m_fIbias);
 	SetResultValues_I1IeI2Ie();
 	m_oResults.m_fIdiffSettingValue = m_fIdiff;
 	ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();
 
 	long nHarmIndex = m_nHarmIndex;
 	BOOL bHarmValid = TRUE;
 
 	if ((m_nHarmIndex<0)||(m_nHarmIndex>2))
 	{
 		bHarmValid = FALSE;
 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前谐波次数(%ld)有误."),m_nHarmIndex);
 	}
 	else if (m_nHarmIndex == 2)
 	{
 		nHarmIndex = 5;
 	}
 	else
 		nHarmIndex += 2;
 
 	for (int nIndex = 0;nIndex<DIFF_CURR_CAL_CHANNEL_MAX;nIndex++)
 	{
 		m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fAmp = pChCurrents[nIndex].famptitude;
 		m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fAngle = pChCurrents[nIndex].fphase;
 		m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
 
 		m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[nHarmIndex].m_bSelect = TRUE;
 		m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[nHarmIndex].fAmp = pChCurrents[nIndex].famptitude*m_fIdSetting/100;
 		m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[nHarmIndex].fAngle = pChCurrents[nIndex].fphase;
 		m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[nHarmIndex].fFreq = g_theSystemConfig->m_fFNom*nHarmIndex;
 	}
 
 	//////////////////////////////////////////////////////////////////////////
}



