#include "stdafx.h"
#include"SttRecloseAccTest.h"
#include "../SttSystemConfig.h"

CString CSttRecloseAccTest::m_strMacroName = "重合闸及后加速测试";
CString CSttRecloseAccTest::m_strMacroID = STT_MACRO_ID_RecloseAcc;
CString CSttRecloseAccTest::m_strFilePostFix = "orcs";
CString CSttRecloseAccTest::m_strMacroVer ="1.0";

CSttRecloseAccTest::CSttRecloseAccTest() : CSttStateTest()
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

void CSttRecloseAccTest::Init()
{ 
	CSttStateTest::Init();
	m_pStateTest->m_oStateParas.m_nStateNumbers = 4;
	m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
    
	m_fUnom = g_theSystemConfig->m_fVNom/SQRT3;
	m_pStateTest->m_oStateParas.init(4);
	tmt_RecloseAccParas::init();
m_fVzFreq = g_theSystemConfig->m_fFNom;
	m_oResults.init();
	m_pStateTest->m_oStateParas.m_nBinTripRef = 0;
}

CSttRecloseAccTest::~CSttRecloseAccTest(void)
{

}

void CSttRecloseAccTest::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
	m_pStateTest->m_oStateParas.m_paraState[0].m_tGps = m_tGps;
}

long CSttRecloseAccTest::CalReport(UINT nState)
{
	long nBeginIndex,nEndIndex;

	if (m_nBinSelect == 1)
	{
		nBeginIndex = 4;
	} 
	else
	{
		nBeginIndex = 0;
	}

	nEndIndex = (nBeginIndex+4);
	
	long nTripIndex = 0;
	bool bHasMapReclose = false;
	float fTimeBin = 0;

	for (int nIndex = nBeginIndex;nIndex<nEndIndex;nIndex++)
	{
		if (m_nDInputState[nIndex] == STT_IMPEDANCE_BIN_STATE_RECLOCE)
		{
			fTimeBin = m_pStateTest->m_oStateResults.m_resultState[2].m_frTimeBinAct[nIndex][0];
			if(g_theSystemConfig->m_nBinBoutMode)
			{
				if(m_pStateTest->m_oStateResults.m_resultState[2].m_frTimeBinExAct[nIndex][0] > fTimeBin)
				{
					fTimeBin = m_pStateTest->m_oStateResults.m_resultState[2].m_frTimeBinExAct[nIndex][0];
				}
			}
			m_oResults.SetRecloseTime(fTimeBin);
			bHasMapReclose = true;
		} 
		else
		{
			fTimeBin = m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[nIndex][0];
			if(g_theSystemConfig->m_nBinBoutMode)
			{
				if(m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinExAct[nIndex][0] > fTimeBin)
				{
					fTimeBin = m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinExAct[nIndex][0];
				}
			}
			m_oResults.SetFault1TripTime(nTripIndex,m_nDInputState[nIndex],fTimeBin,bHasMapReclose);
			fTimeBin = m_pStateTest->m_oStateResults.m_resultState[3].m_frTimeBinAct[nIndex][0];
			if(g_theSystemConfig->m_nBinBoutMode)
			{
				if(m_pStateTest->m_oStateResults.m_resultState[3].m_frTimeBinExAct[nIndex][0] > fTimeBin)
				{
					fTimeBin = m_pStateTest->m_oStateResults.m_resultState[3].m_frTimeBinExAct[nIndex][0];
				}
			}
			m_oResults.SetFault2TripTime(nTripIndex,m_nDInputState[nIndex],fTimeBin);
			nTripIndex++;
		}
	}

	m_oResults.m_nActA = (m_oResults.m_fFirstTripTime[0] - 0.0001) > 0 ? 1 : 0;
	m_oResults.m_nActB = (m_oResults.m_fFirstTripTime[1] - 0.0001) > 0 ? 1 : 0;
	m_oResults.m_nActC = (m_oResults.m_fFirstTripTime[2] - 0.0001) > 0 ? 1 : 0;
	m_oResults.m_nActD = (m_oResults.m_fRecloseTime - 0.0001) > 0 ? 1 : 0;
	m_oResults.m_nActAcc = (m_oResults.m_fSecondTripTime - 0.0001) > 0 ? 1 : 0;

	m_oResults.m_fTripTime = 0;

	for (int i=0;i<8;i++)
	{
		m_oResults.m_fTripTime = GetMaxValue(m_oResults.m_fTripTime,m_oResults.m_fFirstTripTime[i]);
	}

	m_oResults.m_fImp = m_fImpedance[0];
	m_oResults.m_fImpAngle = m_fImpAngle[0];
//	Global_AddSimulateBreakTimeToResults(this,&m_oResults);  20220615 zhouhj北京要求实际动作时间中去除模断时间的添加与老版PowerTest一致
	return 0;
}

void CSttRecloseAccTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_RecloseAccParas*)this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttRecloseAccTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oResults, pXmlSerialize);
}

long CSttRecloseAccTest::SetParameter(DWORD dwState)
{
	return 0;
}

void Cal_SetVzFreq(tmt_StatePara *pStatePara, int nVzDefine, float fVzFreq)
{
    switch(nVzDefine)
    {
    case 4:		//检同期A
        pStatePara->m_uiVOL[0].Harm[1].fFreq = fVzFreq;
        break;
    case 5:		//检同期B
        pStatePara->m_uiVOL[1].Harm[1].fFreq = fVzFreq;
        break;
    case 6:		//检同期C
        pStatePara->m_uiVOL[2].Harm[1].fFreq = fVzFreq;
        break;
    case 7:		//检同期AB
        pStatePara->m_uiVOL[0].Harm[1].fFreq = fVzFreq;
        pStatePara->m_uiVOL[1].Harm[1].fFreq = fVzFreq;
        break;
    case 8:		//检同期BC
        pStatePara->m_uiVOL[1].Harm[1].fFreq = fVzFreq;
        pStatePara->m_uiVOL[2].Harm[1].fFreq = fVzFreq;
        break;
    case 9:     //检同期CA
        pStatePara->m_uiVOL[2].Harm[1].fFreq = fVzFreq;
        pStatePara->m_uiVOL[0].Harm[1].fFreq = fVzFreq;
        break;
    }
}
void CSttRecloseAccTest::TranslateToStateParas()
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG,">>>>>>>>>>>CSttRecloseAccTest::TranslateToStateParas");

	if (m_nFaultProperty==STT_FaultProperty_Transient)
	{
		m_pStateTest->m_oStateParas.m_nStateNumbers = 3;
	}
	else
	{
		m_pStateTest->m_oStateParas.m_nStateNumbers = 4;
	}

 	float fStdLN_Vol = m_fUnom;//计算标准相电压,一般57.735V
	m_pStateTest->m_oStateParas.m_nPlusDC = m_bIPlusDC;
	m_pStateTest->m_oStateParas.m_fTao = m_oFaultCalculatTool.CalImpPlusDC_Tao(m_fImpedance[0],m_fImpAngle[0]);
 	//////////////////////////////////////////////////////////////////////////
 	//故障前状态
 	Complex p1;
 	Complex	oComplexUI[2][4];
 	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//计算故障前三相电压
 	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],m_fIfh,-m_fPowerAngle);//计算故障前三相电流
 	m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3],oComplexUI[0],m_nVzDefine);
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[0],oComplexUI[0],oComplexUI[1]);
 
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
	m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = GetSttTrigMode();
	Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
    Global_SetStateBoutPreFault(m_pStateTest->m_oStateParas.m_paraState,m_nStateBOut,m_nOutputSwitchMode,m_nBinSelect,m_fBoutTimeTrig,m_fBoutHoldTime);
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
 	//////////////////////////////////////////////////////////////////////////
 	//故障状态
 
 	Global_FaultCalculatUI(this,0,oComplexUI[0],oComplexUI[1]);
	m_oResults.m_fFaultVol = m_fSCVoltage[0];
	m_oResults.m_fFaultCurrent = m_fSCCurrent[0];
 	m_oFaultCalculatTool.Cal_VzAccordDefine(m_nVzDefine, oComplexUI[0],m_fUxInput_Mag,m_fUxInput_Ang, m_fUxHigh, m_fUxLow,FALSE);
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1],oComplexUI[0],oComplexUI[1]);
 
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fTSetting[0]+m_fMarginTime;
	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1],m_nDInputState,m_nBinSelect,
		Global_IsLNFaultType(m_nFaultType[0]));

	if (m_bCBSimulation)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = m_fCBTripTime;
	} 
	else
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
	}

	m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

	//////////////////////////////////////////////////////////////////////////
	//跳闸后,等待重合闸状态
	if (m_nPTPoint == 0)//PT安装在母线侧,跳闸后电压恢复57.74
	{
		m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//计算故障前三相电压
	} 
	else//PT安装在线路侧,跳闸后电压0
	{
		m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],0,0.0f);//计算故障前三相电压
	}

//	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//计算故障前三相电压
	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],m_fIfh,-m_fPowerAngle);//计算故障前三相电流
	m_oFaultCalculatTool.Cal_VzAccordDefine(m_nVzDefine, oComplexUI[0],m_fUxInput_Mag,m_fUxInput_Ang, m_fUxHigh, m_fUxLow,TRUE);

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[2],oComplexUI[0],oComplexUI[1]);
    Cal_SetVzFreq(&m_pStateTest->m_oStateParas.m_paraState[2], m_nVzDefine, m_fVzFreq);//设置抽取电压频率

	m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeState = m_fRecloseTime+m_fMarginTime;
	Global_SetStateBinReclose(&m_pStateTest->m_oStateParas.m_paraState[2],m_nDInputState,m_nBinSelect);

	if (m_bCBSimulation)
	{
		m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeAfterTrigger = m_fCBCloseTime;
	} 
	else
	{
		m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeAfterTrigger = 0;
	}

	m_pStateTest->m_oStateParas.m_paraState[2].m_bDC = FALSE;

	//////////////////////////////////////////////////////////////////////////
	//后加速状态

	if (m_nFaultProperty == STT_FaultProperty_Transient)	//瞬时性故障
	{
		m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//计算故障前三相电压
		m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],m_fIfh,-m_fPowerAngle);//计算故障前三相电流
	}
	else
	{
		Global_FaultCalculatUI(this,1,oComplexUI[0],oComplexUI[1]);
	}

	m_oFaultCalculatTool.Cal_VzAccordDefine(m_nVzDefine, oComplexUI[0],m_fUxInput_Mag,m_fUxInput_Ang, m_fUxHigh, m_fUxLow,FALSE);
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[3],oComplexUI[0],oComplexUI[1]);
	m_pStateTest->m_oStateParas.m_paraState[3].m_fTimeState = m_fTSetting[1]+m_fMarginTime;
	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[3],m_nDInputState,m_nBinSelect,
		Global_IsLNFaultType(m_nFaultType[1]));

	if (m_bCBSimulation)
	{
		m_pStateTest->m_oStateParas.m_paraState[3].m_fTimeAfterTrigger = m_fCBTripTime;
	}
	else
	{
		m_pStateTest->m_oStateParas.m_paraState[3].m_fTimeAfterTrigger = 0;
	}

	m_pStateTest->m_oStateParas.m_paraState[3].m_bDC = FALSE;

	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttRecloseAccTest::TranslateToStateParas>>>>>>>>>>>");
	//////////////////////////////////////////////////////////////////////////
}

void CSttRecloseAccTest::StartTest()
{
	if(GetTestStarting())
	{
		//仅状态序列实验有可能会多次StartTest
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
		CSttTestBase::Stop();
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttRecloseAccTest is  Running,do CSttTestBase::Stop()");
	}

	CSttTestBase::StartTest();
	TtmToDrv();
	if(m_pStateTest->m_oStateParas.m_nStateNumbers == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttRecloseAccTest StateNumber = 0");
		ReturnTestStateEvent_TestFinish(0, 0, FALSE);
		return;
	}

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
	SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
	int nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	//按故障态开出设置来，时间或开入量启动
	//时间启动：第一次翻转在重合态开始计时，如果有后加速态，在后加速态恢复到第一态初始值
	ioctl(nfd, 0x149, 1);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	CSttDeviceBase::g_pSttDeviceBase->SetTestStart(StateTest);
#endif
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttRecloseAccTest::StartTest >>>>>>");
}
