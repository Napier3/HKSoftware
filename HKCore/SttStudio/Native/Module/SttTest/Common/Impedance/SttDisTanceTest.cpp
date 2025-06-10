#include "stdafx.h"
#include "SttDisTanceTest.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDisTanceTest::m_strMacroName = "距离保护测试";
CString CSttDisTanceTest::m_strMacroID = STT_MACRO_ID_Distance;
CString CSttDisTanceTest::m_strFilePostFix = "odis";
CString CSttDisTanceTest::m_strMacroVer ="1.0";


#ifdef USE_SttImpBaseTest
CSttDisTanceTest::CSttDisTanceTest() : CSttImpBaseTest()
#else
CSttDisTanceTest::CSttDisTanceTest() : CSttStateTest()
#endif
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

void CSttDisTanceTest::Init()
{ 
#ifdef USE_SttImpBaseTest
	CSttImpBaseTest::Init();
#else
	CSttStateTest::Init();
	m_oStateParas.m_nStateNumbers = 2;
	m_oStateParas.m_oStateParas.init(8);
#endif
	tmt_DistanceParas::init();
    m_fUNom = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
}

CSttDisTanceTest::~CSttDisTanceTest(void)
{

}

void CSttDisTanceTest::AfterSetParameter()
{
#ifdef USE_SttImpBaseTest
	CSttImpBaseTest::AfterSetParameter();
	m_pImpBaseParas->m_bSearchNext = FALSE;
	m_pImpBaseParas->m_pStateParas->m_paraState[0].m_tGps = m_tGps;
#else
	CSttStateTest::AfterSetParameter();
#endif
	m_oDistanceResults.init();//zhouhj 20210804  在设置参数后调用,在搜索阻抗边界等模块,需要在同一个测试项多次调用开始测试时,需要对结果进行初始化
	m_oDistanceResults.m_fImp = m_fImpedance[0] = m_fSetting[0]*m_fRate[0];
	m_oDistanceResults.m_fImpAngle = m_fImpAngle[0];
}

long CSttDisTanceTest::CalReport(UINT nState)
{
#ifdef USE_SttImpBaseTest
	CalReport_ImpBase(this,&m_oDistanceResults);
#else
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

	for (int nIndex = nBeginIndex;nIndex<nEndIndex;nIndex++)
	{
		if (m_nDInputState[nIndex] == STT_IMPEDANCE_BIN_STATE_RECLOCE)
		{
			m_oDistanceResults.SetRecloseTime(m_oStateResults.m_resultState[2].m_frTimeBinAct[nIndex][0]);
			bHasMapReclose = true;
		} 
		else
		{
			m_oDistanceResults.SetFault1TripTime(nTripIndex,m_nDInputState[nIndex],m_oStateResults.m_resultState[1].m_frTimeBinAct[nIndex][0],bHasMapReclose);
			nTripIndex++;
		}
	}

	m_oDistanceResults.m_nActA = (m_oDistanceResults.m_fFirstTripTime[0]-0.0001) > 0 ? 1 : 0;
	m_oDistanceResults.m_nActB = (m_oDistanceResults.m_fFirstTripTime[1]-0.0001) > 0 ? 1 : 0;
	m_oDistanceResults.m_nActC = (m_oDistanceResults.m_fFirstTripTime[2]-0.0001) > 0 ? 1 : 0;
	m_oDistanceResults.m_nActD = (m_oDistanceResults.m_fRecloseTime - 0.0001) > 0 ? 1 : 0;

	m_oDistanceResults.m_fTripTime = 0;

	for (int i=0;i<8;i++)
	{
		m_oDistanceResults.m_fTripTime = GetMaxValue(m_oDistanceResults.m_fTripTime,m_oDistanceResults.m_fFirstTripTime[i]);
	}

	m_oDistanceResults.m_fImp = m_fImpedance[0];
	m_oDistanceResults.m_fImpAngle = m_fImpAngle[0];
#endif
	return 0;
}

void CSttDisTanceTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_DistanceParas*)this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttDisTanceTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oDistanceResults, pXmlSerialize);
}

long CSttDisTanceTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttDisTanceTest::TranslateToStateParas()
{
#ifdef USE_SttImpBaseTest
	m_fMaxFaultTime = m_fTSetting+m_fMarginTime;
    TranslateToStateParas_ImpBase(this,m_fUNom);
	m_oDistanceResults.m_fFaultVol = m_fSCVoltage[0];
	m_oDistanceResults.m_fFaultCurrent = m_fSCCurrent[0];
#else
  	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	m_oStateParas.m_bPlusDC = m_bIPlusDC;
	m_oStateParas.m_fTao = m_oFaultCalculatTool.CalImpPlusDC_Tao(m_fImpedance[0],m_fImpAngle[0]);
 
  	//////////////////////////////////////////////////////////////////////////
  	//故障前状态
  	Complex p1;
  	Complex	oComplexUI[2][4];
  	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//计算故障前三相电压
  	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],m_fIfh,-m_fPowerAngle);//计算故障前三相电流
  	m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3],oComplexUI[0],m_nVzDefine);
  	Global_SetStateUIFromCpl(&m_oStateParas.m_paraState[0],oComplexUI[0],oComplexUI[1]);
  
  	m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
  	m_oStateParas.m_paraState[0].m_nTriggerCondition = GetSttTrigMode();
  	Global_SetStateBinPreFault(&m_oStateParas.m_paraState[0]);
	Global_SetStateBoutPreFault(m_oStateParas.m_paraState,m_nStateBOut,m_nOutputSwitchMode,m_fBoutTimeTrig,m_fBoutHoldTime);
  	m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
  	m_oStateParas.m_paraState[0].m_bDC = FALSE;
  	//////////////////////////////////////////////////////////////////////////
 	//故障状态
 
 	Global_FaultCalculatUI(this,0,oComplexUI[0],oComplexUI[1]);
	m_oDistanceResults.m_fFaultVol = m_fSCVoltage[0];
	m_oDistanceResults.m_fFaultCurrent = m_fSCCurrent[0];
 	m_oFaultCalculatTool.Cal_VzAccordDefine(m_nVzDefine, oComplexUI[0],m_fUxInput_Mag,m_fUxInput_Ang, m_fUxHigh, m_fUxLow,FALSE);
 	Global_SetStateUIFromCpl(&m_oStateParas.m_paraState[1],oComplexUI[0],oComplexUI[1]);
 
 	m_oStateParas.m_paraState[1].m_fTimeState = m_fTSetting+m_fMarginTime;
	Global_SetStateBinFault(&m_oStateParas.m_paraState[1],m_nDInputState,m_nBinSelect);
 
 	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
 	{
 		m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
 	}
 
 	m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = m_fPostFaultTime;
 	m_oStateParas.m_paraState[1].m_bDC = FALSE;

	//////////////////////////////////////////////////////////////////////////
#endif
}
