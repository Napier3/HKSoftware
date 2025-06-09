#include "stdafx.h"
#include "SttVolInverseTimeTest.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttVolInverseTimeTest::m_strMacroName = "电压反时限试验";
CString CSttVolInverseTimeTest::m_strMacroID = STT_MACRO_ID_VoltageInverseTime;
CString CSttVolInverseTimeTest::m_strFilePostFix = "vactt";
CString CSttVolInverseTimeTest::m_strMacroVer ="1.0";

CSttVolInverseTimeTest::CSttVolInverseTimeTest() : CSttStateTest()
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

void CSttVolInverseTimeTest::Init()
{ 
	CSttStateTest::Init();
	m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
	m_pStateTest->m_oStateParas.init(2);
	m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
    m_fPreFaultFre = g_theSystemConfig->m_fFNom;
    m_fFaultFre = g_theSystemConfig->m_fFNom;
	tmt_VolInverseTimeParas::init();
	m_oVolInverseResults.init();
}

CSttVolInverseTimeTest::~CSttVolInverseTimeTest(void)
{

}

void CSttVolInverseTimeTest::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
}

long CSttVolInverseTimeTest::CalReport(UINT nState)
{
	m_oVolInverseResults.m_fTripTime = 0.0f;

	if (m_nBinLogic == 0)//zhouhj 如果逻辑或
	{
        for(int nIndex = 0; nIndex < MAX_BINARYIN_COUNT; nIndex++) //任意一个选择的开入动作即为跳闸时间
		{
			if (m_binIn[nIndex].nSelect)
			{
				m_oVolInverseResults.m_fTripTime = GetMaxValue(m_oVolInverseResults.m_fTripTime,
															   m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[nIndex][0]);
			}
		}

		m_oVolInverseResults.m_nAct = (m_oVolInverseResults.m_fTripTime-0.0001) > 0 ? 1 : 0;//跳闸时间大于0即保护动作了
		return 0;
	}

    for(int nIndex = 0; nIndex < MAX_BINARYIN_COUNT; nIndex++) //对于开入与逻辑处理
	{
		if (m_binIn[nIndex].nSelect)//只看选择的开入
		{
			if (m_pStateTest->m_oStateResults.m_resultState[1].m_nrBinSwitchCount[nIndex] <= 0)//任意一个选择的开入未动作则未能成功动作
			{
				m_oVolInverseResults.m_fTripTime = 0.0f;
				break;
			}

			m_oVolInverseResults.m_fTripTime = GetMaxValue(m_oVolInverseResults.m_fTripTime,
														   m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[nIndex][0]);//取全部开入中最大的一个动作时间
		}
	}

	m_oVolInverseResults.m_nAct = (m_oVolInverseResults.m_fTripTime-0.0001) > 0 ? 1 : 0;
	return 0;
}

void CSttVolInverseTimeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_VolInverseTimeParas*)this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();//在读取完参数后进行参数设置,在此步骤后进行参数转换
		TranslateToStateParas();//参数设置完进行故障转换
		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttVolInverseTimeTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oVolInverseResults, pXmlSerialize);
}

long CSttVolInverseTimeTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttVolInverseTimeTest::TranslateToStateParas()
{
   	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	m_pStateTest->m_oStateParas.m_nPlusDC = 0;
	m_pStateTest->m_oStateParas.m_fTao = 0;
  
   	//////////////////////////////////////////////////////////////////////////
   	//故障前状态
   	Complex	oComplexUI[2][4];
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],m_fPreFaultVol,0.0f);//计算故障前三相电压
   	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],m_fPreFaultCur,-m_fPreFaultAngle);//计算故障前三相电流
   	m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3],oComplexUI[0],14);//无输出
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[0],oComplexUI[0],oComplexUI[1]);
    m_pStateTest->m_oStateParas.m_paraState[0].SetFundFreq(m_fPreFaultFre);
   
	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
	m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);

    for(int nIndex = 0; nIndex < MAX_BINARYOUT_COUNT; nIndex++)
	{
		m_pStateTest->m_oStateParas.m_paraState[0].m_binOut[nIndex].nState = m_binOut[0][nIndex].nState;
	}

	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
  	//////////////////////////////////////////////////////////////////////////
 	//故障状态
	float fIOutmax = 20.0f;
 	Complex p1,p2;
 	double fPhi,fV;
	float fFaultVolLN = m_fFaultVol;
 
 	switch(m_nFaultType)
 	{
 	case VOL_INVERSE_FAULT_TYPE_AN:
		oComplexUI[0][0] = p1.polar(m_fFaultVol,0.0f);
		oComplexUI[1][0] = p1.polar(m_fFaultCur,-m_fFaultAngle);
 		break;
 	case VOL_INVERSE_FAULT_TYPE_BN:
		oComplexUI[0][1] = p1.polar(m_fFaultVol,-120.0f);
		oComplexUI[1][1] = p1.polar(m_fFaultCur,-120-m_fFaultAngle);
 		break;
 	case VOL_INVERSE_FAULT_TYPE_CN:
		oComplexUI[0][2] = p1.polar(m_fFaultVol,120.0f);
		oComplexUI[1][2] = p1.polar(m_fFaultCur,120-m_fFaultAngle);
 		break;
 	case VOL_INVERSE_FAULT_TYPE_AB:
        fPhi=atan2(m_fFaultVol,(double)m_fPreFaultVol)*180.0/XPI;
		fV=m_fFaultVol;
        oComplexUI[0][0] = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
        oComplexUI[0][1] = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
		oComplexUI[0][2] = p1.polar(m_fPreFaultVol,90.0);
		oComplexUI[1][0] = p1.polar(m_fFaultCur,-m_fFaultAngle);
		oComplexUI[1][1] = p1.polar(m_fFaultCur,-m_fFaultAngle + 180.0);
		oComplexUI[1][2] = p1.polar(0.0,0.0);
 		break;
 	case VOL_INVERSE_FAULT_TYPE_BC:
        fPhi=atan2(m_fFaultVol,(double)m_fPreFaultVol)*180.0/XPI;
		fV=m_fFaultVol;
        oComplexUI[0][1] = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
        oComplexUI[0][2] = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
		oComplexUI[0][0] = p1.polar(m_fPreFaultVol,90.0);
		oComplexUI[1][1] = p1.polar(m_fFaultCur,-m_fFaultAngle);
		oComplexUI[1][2] = p1.polar(m_fFaultCur,-m_fFaultAngle + 180.0);
		oComplexUI[1][0] = p1.polar(0.0,0.0);
 		break;
 	case VOL_INVERSE_FAULT_TYPE_CA:
        fPhi=atan2(m_fFaultVol,(double)m_fPreFaultVol)*180.0/XPI;
		fV=m_fFaultVol;
        oComplexUI[0][2] = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0+fPhi);
        oComplexUI[0][0] = p1.polar(fV/2.0/sin(fPhi*XPI/180.0),-90.0-fPhi);
		oComplexUI[0][1] = p1.polar(m_fPreFaultVol,90.0);
		oComplexUI[1][2] = p1.polar(m_fFaultCur,-m_fFaultAngle);
		oComplexUI[1][0] = p1.polar(m_fFaultCur,-m_fFaultAngle + 180.0);
		oComplexUI[1][1] = p1.polar(0,0.0);
 		break;
 	case VOL_INVERSE_FAULT_TYPE_ABC:

		if (m_nFaultVolDef == VOL_INVERSE_FAULT_VOL_DEF_LL)
		{
			fFaultVolLN = m_fFaultVol/1.7320508; 
		}

		oComplexUI[0][0] = p1.polar(fFaultVolLN,0.0f);
		oComplexUI[1][0] = p1.polar(m_fFaultCur,-m_fFaultAngle);
		oComplexUI[0][1] = p1.polar(fFaultVolLN,-120.0f);
		oComplexUI[1][1] = p1.polar(m_fFaultCur,-120.0f-m_fFaultAngle);
		oComplexUI[0][2] = p1.polar(fFaultVolLN,120.0f);
		oComplexUI[1][2] = p1.polar(m_fFaultCur,120.0f-m_fFaultAngle);
 		break;
 	case VOL_INVERSE_FAULT_TYPE_3U0:
		oComplexUI[0][0]=p1.polar(fFaultVolLN/3.0,0.0);
		oComplexUI[0][1]=p1.polar(fFaultVolLN/3.0,0.0);
		oComplexUI[0][2]=p1.polar(fFaultVolLN/3.0,0.0);
		oComplexUI[1][0]=p1.polar(m_fFaultCur,-m_fFaultAngle);
		oComplexUI[1][1]=p1.polar(m_fFaultCur,-m_fFaultAngle);
		oComplexUI[1][2]=p1.polar(m_fFaultCur,-m_fFaultAngle);
 		break;
 	case VOL_INVERSE_FAULT_TYPE_U2:
		oComplexUI[0][0]=p1.polar(fFaultVolLN,0.0);
		oComplexUI[0][1]=p1.polar(fFaultVolLN,120.0);
		oComplexUI[0][2]=p1.polar(fFaultVolLN,-120.0);
		oComplexUI[1][0]=p1.polar(m_fFaultCur,-m_fFaultAngle);
		oComplexUI[1][1]=p1.polar(m_fFaultCur,-m_fFaultAngle+120);
		oComplexUI[1][2]=p1.polar(m_fFaultCur,-m_fFaultAngle-120);
 		break;

	default:
		break;
	}

	if(p1.norm(oComplexUI[1][0])>fIOutmax)oComplexUI[1][0]=p1.polar(fIOutmax,p2.arg(oComplexUI[1][0]));
	if(p1.norm(oComplexUI[1][1])>fIOutmax)oComplexUI[1][1]=p1.polar(fIOutmax,p2.arg(oComplexUI[1][1]));
	if(p1.norm(oComplexUI[1][2])>fIOutmax)oComplexUI[1][2]=p1.polar(fIOutmax,p2.arg(oComplexUI[1][2]));

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1],oComplexUI[0],oComplexUI[1]);
    m_pStateTest->m_oStateParas.m_paraState[1].SetFundFreq(m_fFaultFre);

	if (m_nCTPoint == 0)//如果CT极性指向母线,则反向
	{
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Harm[1].fAngle += 180;
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[1].Harm[1].fAngle += 180;
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[2].Harm[1].fAngle += 180;

		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fAngle += 180;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[1].fAngle += 180;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[2].Harm[1].fAngle += 180;
	}
   
 	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fSettingFaultTime + m_fFaultTimeMargin;
 	m_pStateTest->m_oStateParas.m_paraState[1].m_nBinLogic = m_nBinLogic;
 	m_pStateTest->m_oStateParas.m_paraState[1].m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
  
  	for (int nIndex=0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
  	{
 		m_pStateTest->m_oStateParas.m_paraState[1].m_binIn[nIndex].nSelect = m_binIn[nIndex].nSelect;
    }

    for(int nIndex = 0; nIndex < MAX_BINARYOUT_COUNT; nIndex++)
    {
 		m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nIndex].nState = m_binOut[1][nIndex].nState;
 	}
  
 	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
 	m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;
// 
// 	//////////////////////////////////////////////////////////////////////////
}
