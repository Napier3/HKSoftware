#include "stdafx.h"
#include"SttTURecloseAccTest.h"
#include "../SttSystemConfig.h"

CString CSttTURecloseAccTest::m_strMacroName = "�غ�բ������ٲ���(����)";
CString CSttTURecloseAccTest::m_strMacroID = STT_MACRO_ID_TURecloseAcc;
CString CSttTURecloseAccTest::m_strFilePostFix = "torcs";
CString CSttTURecloseAccTest::m_strMacroVer ="1.0";

CSttTURecloseAccTest::CSttTURecloseAccTest() : CSttRecloseAccTest()
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

void CSttTURecloseAccTest::Init()
{ 
	CSttRecloseAccTest::Init();
}

CSttTURecloseAccTest::~CSttTURecloseAccTest(void)
{

}

void CSttTURecloseAccTest::AfterSetParameter()
{
	CSttRecloseAccTest::AfterSetParameter();
}

void CSttTURecloseAccTest::TranslateToStateParas()
{
	double dFaultCurr1 = m_fSCCurrent[0];
	double dFaultCurr2 = m_fSCCurrent[1];
	CSttRecloseAccTest::TranslateToStateParas();
	m_fSCCurrent[0] = dFaultCurr1;//�����迹����ʱ,����������ϵ�ѹ�������ѹ,���Զ����͹��ϵ���,�˴���֤���ϵ�������
	m_fSCCurrent[1] = dFaultCurr2;
	CLogPrint::LogString(XLOGLEVEL_DEBUG,">>>>>>>>>>>CSttTURecloseAccTest::TranslateToStateParas");
 	float fStdLN_Vol = m_fUnom;//�����׼���ѹ,һ��57.735V

	//����,��ȡ��ѹʹ��UCA,�ʳ�ȡ��ѹΪ0
	m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[3].Harm[1].fAmp = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[3].Harm[1].fAmp = 0.0f;

	switch(m_nFaultType[0])
	{
	case IMPEDANCE_FAULT_TYPE_AN:
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fAmp = m_fSCCurrent[0];
		break;
	case IMPEDANCE_FAULT_TYPE_BN:
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[1].fAmp = m_fSCCurrent[0];
		break;
	case IMPEDANCE_FAULT_TYPE_CN:
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[2].Harm[1].fAmp = m_fSCCurrent[0];
		break;
	case IMPEDANCE_FAULT_TYPE_AB:
	case IMPEDANCE_FAULT_TYPE_ABN:
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fAmp = m_fSCCurrent[0];
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[1].fAmp = m_fSCCurrent[0];
		break;
	case IMPEDANCE_FAULT_TYPE_BC:
	case IMPEDANCE_FAULT_TYPE_BCN:
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[1].fAmp = m_fSCCurrent[0];
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[2].Harm[1].fAmp = m_fSCCurrent[0];
		break;
	case IMPEDANCE_FAULT_TYPE_CA:
	case IMPEDANCE_FAULT_TYPE_CAN:
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fAmp = m_fSCCurrent[0];
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[2].Harm[1].fAmp = m_fSCCurrent[0];
		break;
	case IMPEDANCE_FAULT_TYPE_ABC:
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[1].fAmp = m_fSCCurrent[0];
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[1].fAmp = m_fSCCurrent[0];
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[2].Harm[1].fAmp = m_fSCCurrent[0];
		break;

	default:
		break;
	}

	if (m_nFaultProperty != STT_FaultProperty_Transient)
	{
		m_pStateTest->m_oStateParas.m_paraState[3].m_uiVOL[3].Harm[1].fAmp = 0.0f;

		switch(m_nFaultType[1])
		{
		case IMPEDANCE_FAULT_TYPE_AN:
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[0].Harm[1].fAmp = m_fSCCurrent[1];
			break;
		case IMPEDANCE_FAULT_TYPE_BN:
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[1].Harm[1].fAmp = m_fSCCurrent[1];
			break;
		case IMPEDANCE_FAULT_TYPE_CN:
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[2].Harm[1].fAmp = m_fSCCurrent[1];
			break;
		case IMPEDANCE_FAULT_TYPE_AB:
		case IMPEDANCE_FAULT_TYPE_ABN:
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[0].Harm[1].fAmp = m_fSCCurrent[1];
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[1].Harm[1].fAmp = m_fSCCurrent[1];
			break;
		case IMPEDANCE_FAULT_TYPE_BC:
		case IMPEDANCE_FAULT_TYPE_BCN:
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[1].Harm[1].fAmp = m_fSCCurrent[1];
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[2].Harm[1].fAmp = m_fSCCurrent[1];
			break;
		case IMPEDANCE_FAULT_TYPE_CA:
		case IMPEDANCE_FAULT_TYPE_CAN:
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[0].Harm[1].fAmp = m_fSCCurrent[1];
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[2].Harm[1].fAmp = m_fSCCurrent[1];
			break;
		case IMPEDANCE_FAULT_TYPE_ABC:
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[0].Harm[1].fAmp = m_fSCCurrent[1];
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[1].Harm[1].fAmp = m_fSCCurrent[1];
			m_pStateTest->m_oStateParas.m_paraState[3].m_uiCUR[2].Harm[1].fAmp = m_fSCCurrent[1];
			break;

		default:
			break;
		}
	}

	Complex	oComplexUI[2][4];
	//��բ��,�ȴ��غ�բ״̬
	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0],fStdLN_Vol,0.0f);//�������ǰ�����ѹ
	m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1],m_fIfh,-m_fPowerAngle);//�������ǰ�������
	m_oFaultCalculatTool.Cal_VzAccordDefine(m_nVzDefine, oComplexUI[0],m_fUxInput_Mag,m_fUxInput_Ang, m_fUxHigh, m_fUxLow,TRUE);

	Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[2],oComplexUI[0],oComplexUI[1]);

	if ((m_nVzDefine>=IMPEDANCE_VZ_TYPE_Check_LineNoBusHas)&&
		(m_nVzDefine<=IMPEDANCE_VZ_TYPE_Check_LineHasBusHas))
	{
		tmt_StatePara *pCurrParaState = &m_pStateTest->m_oStateParas.m_paraState[2];
		pCurrParaState->m_uiVOL[0].Harm[1].fAmp /= SQRT3;
		pCurrParaState->m_uiVOL[1].Harm[1].fAmp /= SQRT3;

 		if (pCurrParaState->m_uiVOL[3].Harm[1].fAmp > pCurrParaState->m_uiVOL[1].Harm[1].fAmp)
 		{
 			//�����ȡ��ѹUZ����UB,��UC=UZ-UB
 			pCurrParaState->m_uiVOL[2].Harm[1].fAmp = 
 				pCurrParaState->m_uiVOL[3].Harm[1].fAmp - pCurrParaState->m_uiVOL[1].Harm[1].fAmp;
 			//UC��λ��UB�෴,��UbcΪUB+UC
 			pCurrParaState->m_uiVOL[2].Harm[1].fAngle = pCurrParaState->m_uiVOL[1].Harm[1].fAngle - 180.0f;
 		} 
 		else
 		{
 			//�����ȡ��ѹUZС��UB,��UC=UB - UZ
 			pCurrParaState->m_uiVOL[2].Harm[1].fAmp = 
 				pCurrParaState->m_uiVOL[1].Harm[1].fAmp - pCurrParaState->m_uiVOL[3].Harm[1].fAmp;
 			//UC��λ��UB�෴,��UbcΪUB+UC
 			pCurrParaState->m_uiVOL[2].Harm[1].fAngle = pCurrParaState->m_uiVOL[1].Harm[1].fAngle;
 		}

// 		//ȷ��Ubc���غ�״̬��ֵΪ0,Ub��Uc��ֵ��ͬ��������ͬ
// 		pCurrParaState->m_uiVOL[2].Harm[1].fAmp = pCurrParaState->m_uiVOL[1].Harm[1].fAmp;
// 		pCurrParaState->m_uiVOL[2].Harm[1].fAngle = pCurrParaState->m_uiVOL[1].Harm[1].fAngle;
	}

	m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[3].Harm[1].fAmp = 0.0f;
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttTURecloseAccTest::TranslateToStateParas>>>>>>>>>>>");
	//////////////////////////////////////////////////////////////////////////
}

void CSttTURecloseAccTest::StartTest()
{
	if(GetTestStarting())
	{
		//��״̬����ʵ���п��ܻ���StartTest
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
		CSttTestBase::Stop();
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttTURecloseAccTest is  Running,do CSttTestBase::Stop()");
	}

	CSttTestBase::StartTest();
	TtmToDrv();
	if(m_pStateTest->m_oStateParas.m_nStateNumbers == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttTURecloseAccTest StateNumber = 0");
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
	//������̬������������ʱ�����������
	//ʱ����������һ�η�ת���غ�̬��ʼ������к����̬���ں����̬�ָ�����һ̬��ʼֵ
	ioctl(nfd, 0x149, 3);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	CSttDeviceBase::g_pSttDeviceBase->SetTestStart(StateTest);
#endif
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttTURecloseAccTest::StartTest >>>>>>");
}
