#include "stdafx.h"
#include "SttElecRailwayDiffThrTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"
#include<cmath>

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttElecRailwayDiffThrTest::m_strMacroName = "差动启动电流测试(牵引变)";
CString CSttElecRailwayDiffThrTest::m_strMacroID = STT_MACRO_ID_ElecRailwayDiffTest;
CString CSttElecRailwayDiffThrTest::m_strFilePostFix = "erdffctst";
CString CSttElecRailwayDiffThrTest::m_strMacroVer ="1.0";

CSttElecRailwayDiffThrTest::CSttElecRailwayDiffThrTest() : CSttStateTest()
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

void CSttElecRailwayDiffThrTest::Init()
{ 
	CSttStateTest::Init();
	m_pStateTest->m_oStateParas.m_nStateNumbers = 3;//最后一态复制第一态的值
	m_pStateTest->m_oStateParas.m_bSearchNext = TRUE;
	m_pStateTest->m_oStateParas.init(3);
	m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
	tmt_ElecRailwayDiffParas::init();
	m_oResults.init();
}

long CSttElecRailwayDiffThrTest::SetParameter(DWORD dwState)
{
	return 0;
}

CSttElecRailwayDiffThrTest::~CSttElecRailwayDiffThrTest(void)
{

}

void CSttElecRailwayDiffThrTest::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
	m_oDiffCalTool.Init();
	m_oDiffCalTool.InitSysParas(100,g_theSystemConfig->m_fFNom);//20231120 zhoulei 由硬件资源去判断

	m_oDiffCalTool.InitParas5I_ElecRailway(m_fIbase,m_nSearchMode,m_bMinAxis,m_nIbiasCal,m_fKpl,
		m_nPhase,!m_bCTStarPoint,m_nRWCTconnect,m_nTranSort,m_nKphMode);//20220518 zhouhj  用户反馈,实际输出极性和界面设置不一致,且界面设置与保护厂家说明书一致,故此处改为反向

	InitSearch();
}

long CSttElecRailwayDiffThrTest::CalReport(UINT nState)
{
	if (IsAct())
	{
		m_oResults.m_fIdiffActValue = GetActValue();
		m_oResults.m_nActFlag = 1;
	} 
	else
	{
		m_oResults.m_fIdiffActValue = 0.0f;
		m_oResults.m_nActFlag = 0;
	}

	return 0;
}

void CSttElecRailwayDiffThrTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_thr(this,pXmlSerialize);

	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换
		m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreTime;
		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttElecRailwayDiffThrTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_thr(&m_oResults, pXmlSerialize);
}


void CSttElecRailwayDiffThrTest::SetStatePreFault_5U5I()
{
	float fAngle[DIFF_CURR_CAL_CHANNEL_MAX] = {0, -120.0, 120.0, 0, -120.0, 120.0};

	for (int nIndex=0;nIndex<5;nIndex++)
	{
		if (nIndex<3)
		{
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fAmp = m_fVg1;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fAmp = m_fVg1;
		} 
		else
		{
			m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fAmp = m_fVg2;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fAmp = m_fVg2;
		}
		
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fAngle = fAngle[nIndex];
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fAngle = fAngle[nIndex];
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;

		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fAmp = 0;
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fAngle = fAngle[nIndex];
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
	}

	m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[5].Harm[1].fAmp = 0;
	m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[5].Harm[1].fAmp = 0;
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[5].Harm[1].fAmp = 0;
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[5].Harm[1].fAmp = 0;

	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
	m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut,m_binOut);
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
}

void CSttElecRailwayDiffThrTest::SetResultValues_I1IeI2Ie_ElecRailway(float fIalpha,float fIbeta)
{
	ChannelUI_Diff *pDiffChs = m_oDiffCalTool.GetChannelCurrents();
	float fIe = 1.0f;
	m_oDiffCalTool.GetIet(fIe);

	if (m_nPhase == 1)
	{
		m_oResults.m_fI1Ie = pDiffChs[1].famptitude/fIe;
		m_oResults.m_fI1 = pDiffChs[1].famptitude;
		m_oResults.m_fI2Ie = pDiffChs[4].famptitude/fIe;
		m_oResults.m_fI2 = pDiffChs[4].famptitude;
	}
	else if (m_nPhase == 2)
	{
		m_oResults.m_fI1Ie = pDiffChs[2].famptitude/fIe;
		m_oResults.m_fI1 = pDiffChs[2].famptitude;
		m_oResults.m_fI2Ie = pDiffChs[5].famptitude/fIe;
		m_oResults.m_fI2 = pDiffChs[5].famptitude;
	}
	else
	{
		m_oResults.m_fI1Ie = pDiffChs[0].famptitude/fIe;
		m_oResults.m_fI1 = pDiffChs[0].famptitude;
		m_oResults.m_fI2Ie = pDiffChs[3].famptitude/fIe;
		m_oResults.m_fI2 = pDiffChs[3].famptitude;
	}

	m_oResults.m_fIalpha = fIalpha;
	m_oResults.m_fIalphaIe = fIalpha/fIe;
	m_oResults.m_fIbeta = fIbeta;
	m_oResults.m_fIbetaIe = fIbeta/fIe;
}

void CSttElecRailwayDiffThrTest::SetFaultCurrents_ElecRailway(float fIalpha,float fIbeta)
{
	ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();

	for (int nIndex = 0;nIndex<3;nIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAmp = pChCurrents[nIndex].famptitude;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAngle = pChCurrents[nIndex].fphase;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
	}

	m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[3].Harm[1].fAmp = fabs(fIalpha);
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[4].Harm[1].fAmp = fabs(fIbeta);
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[5].Harm[1].fAmp = 0;

	if (fIalpha>0)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[3].Harm[1].fAngle = 0;
	} 
	else
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[3].Harm[1].fAngle = 180;
	}

	if (fIbeta>0)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[4].Harm[1].fAngle = 0;
	} 
	else
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[4].Harm[1].fAngle = 180;
	}

	m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[3].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[4].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[5].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
}

void CSttElecRailwayDiffThrTest::TranslateToStateParas()
{
  	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	m_pStateTest->m_oStateParas.m_fTao = 0;
  
   	//////////////////////////////////////////////////////////////////////////
   	//故障前状态
	SetStatePreFault_5U5I();//在此函数中设置故障前电压电流、开入开出等,并设置故障态电压值
   	//////////////////////////////////////////////////////////////////////////
 	//故障状态
	float fIalpha = 0,fIbeta = 0;
	m_oDiffCalTool.CurrentCal_ElecRailway(&m_fCurrScanVal,m_fIbias,fIalpha,fIbeta);
	SetResultValues_I1IeI2Ie_ElecRailway(fIalpha,fIbeta);
	m_oResults.m_fIdiffSettingValue = m_fCurrScanVal;
	SetFaultCurrents_ElecRailway(fIalpha,fIbeta);
	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1],m_binIn,m_nBinLogic);
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fFaultTime;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut,m_binOut);
  
  	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
  	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
  	}
  
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
	m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

	memcpy(&m_pStateTest->m_oStateParas.m_paraState[2],
			&m_pStateTest->m_oStateParas.m_paraState[0],sizeof(tmt_StatePara));
	m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeState = 0.01;
	//////////////////////////////////////////////////////////////////////////
}

void CSttElecRailwayDiffThrTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();

	if (m_nStepIndex == 0)//只有第一个测试点,需要下发开始测试命令,后续测试点不需要
	{
		pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
	}

	pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}

void CSttElecRailwayDiffThrTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_diff_search_results(this,&m_oResults, pXmlSerialize);
}

void CSttElecRailwayDiffThrTest::ReturnTestStateEvent_SearchPoint(double dTime, double dRealTime, bool bWithEvent)
{
	// 	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("状态2动作结果(%d),开入A变位次数(%d),动作时间(%f)"),m_pStateTest->m_oStateResults.m_resultState[1].m_nAct,
	// 		m_pStateTest->m_oStateResults.m_resultState[1].m_nrBinSwitchCount[0],m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[0]);
	if (!IsSearchFinished(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct))
	{
		CSttStateTest::AfterSetParameter();
		SearchNext();
		TranslateToStateParas();
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(&m_pStateTest->m_oStateParas);//后续开始测试操作
		int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
		
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(nFd,0x14B,0);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
		return;
	}

	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;
	CalReport();

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
#endif
	SetTestStarting(FALSE);

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
}



