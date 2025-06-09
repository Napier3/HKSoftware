#include "stdafx.h"
#include "SttActionTimeTest.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttActionTimeTest::m_strMacroName = "动作时间测试";
CString CSttActionTimeTest::m_strMacroID = STT_MACRO_ID_ActionTime;
CString CSttActionTimeTest::m_strFilePostFix = "actt";
CString CSttActionTimeTest::m_strMacroVer ="1.0";

CSttActionTimeTest::CSttActionTimeTest() : CSttStateTest()
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

void CSttActionTimeTest::Init()
{ 
	CSttStateTest::Init();
	m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
	m_pStateTest->m_oStateParas.init(2);
	m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
	tmt_ActionTimeParas::init();
	m_oActionTimeResults.init();
    m_fPreFaultFre = g_theSystemConfig->m_fFNom;
    m_fFaultFre = g_theSystemConfig->m_fFNom;
}

CSttActionTimeTest::~CSttActionTimeTest(void)
{

}

void CSttActionTimeTest::AfterSetParameter()
{
	CSttStateTest::AfterSetParameter();
}

long CSttActionTimeTest::CalReport(UINT nState)
{
	m_oActionTimeResults.m_fTripTime = 0.0f;

	if (m_nBinLogic == 0)//zhouhj 如果逻辑或
	{
        for(int nIndex = 0; nIndex < MAX_BINARYIN_COUNT; nIndex++) //任意一个选择的开入动作即为跳闸时间
		{
			if (m_binIn[nIndex].nSelect)
			{
				m_oActionTimeResults.m_fTripTime = GetMaxValue(m_oActionTimeResults.m_fTripTime,
															   m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[nIndex][0]);
			}
		}

		m_oActionTimeResults.m_nAct = (m_oActionTimeResults.m_fTripTime-0.0001) > 0 ? 1 : 0;//跳闸时间大于0即保护动作了
		return 0;
	}

    for(int nIndex = 0; nIndex < MAX_BINARYIN_COUNT; nIndex++) //对于开入与逻辑处理
	{
		if (m_binIn[nIndex].nSelect)//只看选择的开入
		{
			if (m_pStateTest->m_oStateResults.m_resultState[1].m_nrBinSwitchCount[nIndex] <= 0)//任意一个选择的开入未动作则未能成功动作
			{
				m_oActionTimeResults.m_fTripTime = 0.0f;
				break;
			}

			m_oActionTimeResults.m_fTripTime = GetMaxValue(m_oActionTimeResults.m_fTripTime,
														   m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[nIndex][0]);//取全部开入中最大的一个动作时间
		}
	}

	m_oActionTimeResults.m_nAct = (m_oActionTimeResults.m_fTripTime-0.0001) > 0 ? 1 : 0;
	return 0;
}

void CSttActionTimeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_ActionTimeParas*)this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();//在读取完参数后进行参数设置,在此步骤后进行参数转换
		TranslateToStateParas();//参数设置完进行故障转换
		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttActionTimeTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oActionTimeResults, pXmlSerialize);
}

long CSttActionTimeTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttActionTimeTest::TranslateToStateParas()
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
    for (int j=0;j<4;j++)
    {
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[j].Harm[1].fFreq = m_fPreFaultFre;
    }
    for (int j=0;j<3;j++)
    {
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[j].Harm[1].fFreq = m_fPreFaultFre;
    }
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
	Complex p1,p2;
	float fPhiTemp,fVTemp,fPhi,fV,fI,fPhif,fVf,fIf;
	float fIOutmax = 20.0;
	Complex fVa0,fVb0,fVc0,fVa,fVb,fVc;
	Complex fIa0=p1.polar(0.0,0.0);
	Complex fIb0=p1.polar(0.0,0.0);
	Complex fIc0=p1.polar(0.0,0.0);
	Complex fIa=p1.polar(0.0,0.0);
	Complex fIb=p1.polar(0.0,0.0);
	Complex fIc=p1.polar(0.0,0.0);

	fPhi = m_fPreFaultAngle;
	fV = m_fPreFaultVol;
	fI = m_fPreFaultCur;
	fPhif = m_fFaultAngle;
	fVf = m_fFaultVol;

	if (m_nRefValueType == 0)
	{
		fIf = m_fFaultCur*m_fIn;
	}
	else if (m_nRefValueType == 1)
	{
		fIf = m_fFaultCur*m_fIn*m_fIp;
	}
	else
	{
		fIf = m_fFaultCur;
	}

	fIf = m_fFaultCur;
    fPhiTemp=fabs(atan2(fVf,fV))*180.0/XPI;
	int nFaultType = m_nFaultType;
	int nVType = m_nFaultVolType;

	switch(nFaultType)
	{
	case ACTION_TIME_FAULT_TYPE_A:
		fVa0=p1.polar(fV,0.0);
		fVb0=p1.polar(fV,-120.0);
		fVc0=p1.polar(fV,120.0);
		fIa0=p1.polar(fI,0.0-fPhi);
		fIb0=p1.polar(fI,-120.0-fPhi);
		fIc0=p1.polar(fI,120.0-fPhi);
		fVa=p1.polar(fV,0.0);
		fVb=p1.polar(fV,-120.0);
		fVc=p1.polar(fV,120.0);
		fIa=p1.polar(fIf,0.0-fPhif);
		fIb=p1.polar(fIf/2.0,0.0-fPhif+180);
		fIc=p1.polar(fIf/2.0,0.0-fPhif+180);
		break;
	case ACTION_TIME_FAULT_TYPE_B:
		fVa0=p1.polar(fV,0.0);
		fVb0=p1.polar(fV,-120.0);
		fVc0=p1.polar(fV,120.0);
		fIa0=p1.polar(fI,0.0-fPhi);
		fIb0=p1.polar(fI,-120.0-fPhi);
		fIc0=p1.polar(fI,120.0-fPhi);
		fVa=p1.polar(fV,0.0);
		fVb=p1.polar(fV,-120.0);
		fVc=p1.polar(fV,120.0);
		fIa=p1.polar(fIf/2.0,0.0-fPhif+180);
		fIb=p1.polar(fIf,0.0-fPhif);
		fIc=p1.polar(fIf/2.0,0.0-fPhif+180);
		break;
	case ACTION_TIME_FAULT_TYPE_C:
		fVa0=p1.polar(fV,0.0);
		fVb0=p1.polar(fV,-120.0);
		fVc0=p1.polar(fV,120.0);
		fIa0=p1.polar(fI,0.0-fPhi);
		fIb0=p1.polar(fI,-120.0-fPhi);
		fIc0=p1.polar(fI,120.0-fPhi);
		fVa=p1.polar(fV,0.0);
		fVb=p1.polar(fV,-120.0);
		fVc=p1.polar(fV,120.0);
		fIa=p1.polar(fIf/2.0,0.0-fPhif+180);
		fIb=p1.polar(fIf/2.0,0.0-fPhif+180);
		fIc=p1.polar(fIf,0.0-fPhif);
		break;
	case ACTION_TIME_FAULT_TYPE_UaIa:
		fVa0=p1.polar(fV,0.0);
		fVb0=p1.polar(0.0,0.0);
		fVc0=p1.polar(0.0,0.0);
		fIa0=p1.polar(fI,-fPhi);
		fVa=p1.polar(fVf,0.0);
		fVb=p1.polar(0.0,0.0);
		fVc=p1.polar(0.0,0.0);
		fIa=p1.polar(fIf,0.0-fPhif);
		break;
	case ACTION_TIME_FAULT_TYPE_UaUb:
		fVa0=p1.polar(fV/2.0,0.0);
		fVb0=p1.polar(fV/2.0,180.0);
		fVc0=p1.polar(0.0,0.0);
		fVa=p1.polar(fVf/2.0,0.0);
		fVb=p1.polar(fVf/2.0,180.0);
		fVc=p1.polar(0.0,0.0);
		break;
	case ACTION_TIME_FAULT_TYPE_Iabc:
		fVa0=p1.polar(0.0,0.0);
		fVb0=p1.polar(0.0,0.0);
		fVc0=p1.polar(0.0,0.0);
		fIa0=p1.polar(fI/3.0,0.0);
		fIb0=p1.polar(fI/3.0,0.0);
		fIc0=p1.polar(fI/3.0,0.0);
		fIa=p1.polar(fIf/3.0,0.0);
		fIb=p1.polar(fIf/3.0,0.0);
		fIc=p1.polar(fIf/3.0,0.0);
		fVa=p1.polar(0.0,0.0);
		fVb=p1.polar(0.0,0.0);
		fVc=p1.polar(0.0,0.0);
		break;
	case ACTION_TIME_FAULT_TYPE_ABC:
		fVa0=p1.polar(fV,0.0);
		fVb0=p1.polar(fV,-120.0);
		fVc0=p1.polar(fV,120.0);

		fIa0=p1.polar(fI,0.0-fPhi);
		fIb0=p1.polar(fI,-120.0-fPhi);
		fIc0=p1.polar(fI,120.0-fPhi);
		fVa=p1.polar(fVf,0.0);
		fVb=p1.polar(fVf,-120.0);
		fVc=p1.polar(fVf,120.0);
		fIa=p1.polar(fIf,0.0-fPhif);
		fIb=p1.polar(fIf,-120.0-fPhif);
		fIc=p1.polar(fIf,120.0-fPhif);
		break;
	case ACTION_TIME_FAULT_TYPE_AN:
		if(nVType==ACTION_TIME_FAULT_VOL_TYPE_3U0)
			fVTemp=fV-fVf;
		else 
			fVTemp=fVf;
		fVa0=p1.polar(fV,0.0);
		fVb0=p1.polar(fV,-120.0);
		fVc0=p1.polar(fV,120.0);
		fIa0=p1.polar(fI,0.0-fPhi);
		fIb0=p1.polar(fI,-120.0-fPhi);
		fIc0=p1.polar(fI,120.0-fPhi);
		fVa=p1.polar(fVTemp,0.0);
		fVb=p1.polar(fV,-120.0);
		fVc=p1.polar(fV,120.0);
		fIa=p1.polar(fIf,0.0-fPhif);
		fIb=p1.polar(fI,-120.0-fPhif);
		fIc=p1.polar(fI,120.0-fPhif);
		break;
	case ACTION_TIME_FAULT_TYPE_BN:
		if(nVType==ACTION_TIME_FAULT_VOL_TYPE_3U0)fVTemp=fV-fVf;
		else fVTemp=fVf;
		fVa0=p1.polar(fV,0.0);
		fVb0=p1.polar(fV,-120.0);
		fVc0=p1.polar(fV,120.0);
		fIa0=p1.polar(fI,0.0-fPhi);
		fIb0=p1.polar(fI,-120.0-fPhi);
		fIc0=p1.polar(fI,120.0-fPhi);
		fVa=p1.polar(fV,0.0);
		fVb=p1.polar(fVTemp,-120.0);
		fVc=p1.polar(fV,120.0);
		fIa=p1.polar(fI,0.0-fPhif);
		fIb=p1.polar(fIf,-120.0-fPhif);
		fIc=p1.polar(fI,120.0-fPhif);
		break;
	case ACTION_TIME_FAULT_TYPE_CN:
		if(nVType==ACTION_TIME_FAULT_VOL_TYPE_3U0)fVTemp=fV-fVf;
		else fVTemp=fVf;
		fVa0=p1.polar(fV,0.0);
		fVb0=p1.polar(fV,-120.0);
		fVc0=p1.polar(fV,120.0);
		fIa0=p1.polar(fI,0.0-fPhi);
		fIb0=p1.polar(fI,-120.0-fPhi);
		fIc0=p1.polar(fI,120.0-fPhi);
		fVa=p1.polar(fV,0.0);
		fVb=p1.polar(fV,-120.0);
		fVc=p1.polar(fVTemp,120.0);
		fIa=p1.polar(fI,0.0-fPhif);
		fIb=p1.polar(fI,-120.0-fPhif);
		fIc=p1.polar(fIf,120.0-fPhif);
		break;
	case ACTION_TIME_FAULT_TYPE_AB:
		if(nVType==ACTION_TIME_FAULT_VOL_TYPE_U2)
		{
            fPhiTemp=atan2(3.0*fV-6.0*fVf,sqrt(3.0)*fV)*180.0/XPI;
			fVTemp=(3.0*fV-6.0*fVf)/sqrt(3.0);
		}
		else
		{
            fPhiTemp=atan2(fVf,fV)*180.0/XPI;
			fVTemp=fVf;
		}
		fVa0=p1.polar(fV,-30.0);
		fVb0=p1.polar(fV,-150.0);
		fVc0=p1.polar(fV,90.0);

		fIa0=p1.polar(fI,0.0-fPhi);
		fIb0=p1.polar(fI,180.0-fPhi);

        fVa=p1.polar(fVTemp/2.0/sin(fPhiTemp*XPI/180.0),-90.0+fPhiTemp);
        fVb=p1.polar(fVTemp/2.0/sin(fPhiTemp*XPI/180.0),-90.0-fPhiTemp);
		fVc=p1.polar(fV,90.0);
		fIa=p1.polar(fIf,0.0-fPhif);
		fIb=p1.polar(fIf,180.0-fPhif);
		fIc=p1.polar(fI,120.0-fPhif);
		break;
	case ACTION_TIME_FAULT_TYPE_BC:
		if(nVType==ACTION_TIME_FAULT_VOL_TYPE_U2)
		{
            fPhiTemp=atan2(3.0*fV-6.0*fVf,sqrt(3.0)*fV)*180.0/XPI;
			fVTemp=(3.0*fV-6.0*fVf)/sqrt(3.0);
		}
		else
		{
            fPhiTemp=atan2(fVf,fV)*180.0/XPI;
			fVTemp=fVf;
		}
		fVb0=p1.polar(fV,-30.0);
		fVc0=p1.polar(fV,-150.0);
		fVa0=p1.polar(fV,90.0);
		fIb0=p1.polar(fI,0.0-fPhi);
		fIc0=p1.polar(fI,180.0-fPhi);
        fVb=p1.polar(fVTemp/2.0/sin(fPhiTemp*XPI/180.0),-90.0+fPhiTemp);
        fVc=p1.polar(fVTemp/2.0/sin(fPhiTemp*XPI/180.0),-90.0-fPhiTemp);
		fVa=p1.polar(fV,90.0);
		fIb=p1.polar(fIf,0.0-fPhif);
		fIc=p1.polar(fIf,180.0-fPhif);
		fIa=p1.polar(fI,0.0-fPhif);
		break;
	case ACTION_TIME_FAULT_TYPE_CA:
		if(nVType==ACTION_TIME_FAULT_VOL_TYPE_U2)
		{
            fPhiTemp=atan2(3.0*fV-6.0*fVf,sqrt(3.0)*fV)*180.0/XPI;
			fVTemp=(3.0*fV-6.0*fVf)/sqrt(3.0);
		}
		else
		{
            fPhiTemp=atan2(fVf,fV)*180.0/XPI;
			fVTemp=fVf;
		}
		fVc0=p1.polar(fV,-30.0);
		fVa0=p1.polar(fV,-150.0);
		fVb0=p1.polar(fV,90.0);
		fIc0=p1.polar(fI,0.0-fPhi);
		fIa0=p1.polar(fI,180.0-fPhi);
        fVc=p1.polar(fVTemp/2.0/sin(fPhiTemp*XPI/180.0),-90.0+fPhiTemp);
        fVa=p1.polar(fVTemp/2.0/sin(fPhiTemp*XPI/180.0),-90.0-fPhiTemp);
		fVb=p1.polar(fV,90.0);
		fIc=p1.polar(fIf,0.0-fPhif);
		fIa=p1.polar(fIf,180.0-fPhif);
		fIb=p1.polar(fI,-120.0-fPhif);
		break;
	case ACTION_TIME_FAULT_TYPE_I2:
		fVa0=p1.polar(fV,0.0);
		fVb0=p1.polar(fV,-120.0);
		fVc0=p1.polar(fV,120.0);

		fIa0=p1.polar(fI,0.0-fPhi);
		fIb0=p1.polar(fI,120.0-fPhi);
		fIc0=p1.polar(fI,-120.0-fPhi);

		fVa=p1.polar(fVf,0.0);
		fVb=p1.polar(fVf,-120.0);
		fVc=p1.polar(fVf,120.0);
		fIa=p1.polar(fIf,0.0-fPhif);
		fIb=p1.polar(fIf,120.0-fPhif);
		fIc=p1.polar(fIf,-120.0-fPhif);
		break;
	case ACTION_TIME_FAULT_TYPE_3I0:
		fVa0=p1.polar(fV,0.0);
		fVb0=p1.polar(fV,-120.0);
		fVc0=p1.polar(fV,120.0);
		fIa0=p1.polar(fI,0.0-fPhi);
		fIb0=p1.polar(fI,0.0-fPhi);
		fIc0=p1.polar(fI,0.0-fPhi);
		fVa=p1.polar(fVf,0.0);
		fVb=p1.polar(fV,-120.0);
		fVc=p1.polar(fV,120.0);
		fIa=p1.polar(fIf/3.0,0.0-fPhif);
		fIb=p1.polar(fIf/3.0,0.0-fPhif);
		fIc=p1.polar(fIf/3.0,0.0-fPhif);
		break;

	default:
		break;
	}

	fIa0=p1.polar(p2.norm(fIa0),p2.arg(fVa0)-fPhi);
	fIb0=p1.polar(p2.norm(fIb0),p2.arg(fVb0)-fPhi);
	fIc0=p1.polar(p2.norm(fIc0),p2.arg(fVc0)-fPhi);
	if(p1.norm(fIa0)>fIOutmax)fIa0=p1.polar(fIOutmax,p2.arg(fIa0));
	if(p1.norm(fIb0)>fIOutmax)fIb0=p1.polar(fIOutmax,p2.arg(fIb0));
	if(p1.norm(fIc0)>fIOutmax)fIc0=p1.polar(fIOutmax,p2.arg(fIc0));

	if(p1.norm(fIa)>fIOutmax)
		fIa=p1.polar(fIOutmax,p2.arg(fIa));
	if(p1.norm(fIb)>fIOutmax)fIb=p1.polar(fIOutmax,p2.arg(fIb));
	if(p1.norm(fIc)>fIOutmax)fIc=p1.polar(fIOutmax,p2.arg(fIc));

	oComplexUI[0][0] = fVa;
	oComplexUI[0][1] = fVb;
	oComplexUI[0][2] = fVc;

	oComplexUI[1][0] = fIa;
	oComplexUI[1][1] = fIb;
	oComplexUI[1][2] = fIc;
 
	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1],oComplexUI[0],oComplexUI[1]);
    for (int j=0;j<4;j++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[j].Harm[1].fFreq = m_fFaultFre;
    }
    for (int j=0;j<3;j++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[j].Harm[1].fFreq = m_fFaultFre;
    }
	if (m_nCTPoint == 0)//如果CT极性指向母线,则反向
	{
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[0].Harm[1].fAngle += 180;
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[1].Harm[1].fAngle += 180;
		m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[2].Harm[1].fAngle += 180;

		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fAngle += 180;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[1].fAngle += 180;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[2].Harm[1].fAngle += 180;
	}
  
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fSettingFaultTime+m_fMarginTime;
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

	//////////////////////////////////////////////////////////////////////////
}
