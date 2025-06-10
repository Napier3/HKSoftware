#include "stdafx.h"
#include "SttBP2CBOperateTest.h"
#include "../../SttSystemConfig.h"
#include "../../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttBP2CBOperateTest::m_strMacroName = "BP2差动整组试验";
CString CSttBP2CBOperateTest::m_strMacroID = STT_MACRO_ID_BP2CBOperateTest;
CString CSttBP2CBOperateTest::m_strFilePostFix = "bpcbodct";
CString CSttBP2CBOperateTest::m_strMacroVer ="1.0";

CSttBP2CBOperateTest::CSttBP2CBOperateTest() : CSttBP2DiffThrTest()
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

CSttBP2CBOperateTest::~CSttBP2CBOperateTest(void)
{

}

long CSttBP2CBOperateTest::CalReport(UINT nState)
{
	m_oResults.m_fTripTime = m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime;
	m_oResults.m_nActFlag = m_pStateTest->m_oStateResults.m_resultState[1].m_nAct;
	return 0;
}

void CSttBP2CBOperateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_cboperate(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		m_fScanFrom = m_fIdiff;
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttBP2CBOperateTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_cboperate(&m_oResults, pXmlSerialize);
}

void CSttBP2CBOperateTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
	m_fCurrScanVal = m_fIdiff;
	pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}


void CSttBP2CBOperateTest::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
{
	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;
	CalReport();
	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
	SetTestStarting(FALSE);
}

void CSttBP2CBOperateTest::TranslateToStateParas()
{
	CSttBP2DiffThrTest::TranslateToStateParas();
	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fAngle = 0.0f;
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fAngle = -120.0f;
	m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fAngle = 120.0f;

	if (m_nULockType == BP2_DIFF_U_LOCK_TYPE_UA)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fAmp = m_fULockValue;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fAmp = m_fULockValue;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fAmp = m_fULockValue;
	}
	else if (m_nULockType == BP2_DIFF_U_LOCK_TYPE_UAB)
	{
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fAmp = m_fULockValue/1.7320508;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fAmp = m_fULockValue/1.7320508;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fAmp = m_fULockValue/1.7320508;
	}
	else if (m_nULockType == BP2_DIFF_U_LOCK_TYPE_3U0)
	{
		if (fStdLN_Vol>m_fULockValue)
		{
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fAmp = fStdLN_Vol-m_fULockValue;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fAmp = fStdLN_Vol;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fAmp = fStdLN_Vol;
		} 
		else
		{
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fAmp = m_fULockValue;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fAmp = 0;
			m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fAmp = 0;
		}
	}
	else if (m_nULockType == BP2_DIFF_U_LOCK_TYPE_U2)
	{
		Complex oUa,oUb,oUc,p1;
		float fPhi=(float)(atan2(3.0*fStdLN_Vol-6.0*m_fULockValue,sqrt(3.0)*fStdLN_Vol)*180.0f/pi);
		oUa = p1.polar((float)((3.0f*fStdLN_Vol-6.0f*m_fULockValue)/sqrt(3.0f)/2.0f/sin(fPhi*pi/180.0f)),-90.0+fPhi);
		oUb = p1.polar((float)((3.0f*fStdLN_Vol-6.0f*m_fULockValue)/sqrt(3.0f)/2.0f/sin(fPhi*pi/180.0f)),-90.0-fPhi);
		oUc = p1.polar(fStdLN_Vol,90.0);

		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fAmp = oUa.norm();
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fAmp = oUb.norm();
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fAmp = oUc.norm();

		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fAngle = oUa.arg();
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fAngle = oUb.arg();
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fAngle = oUc.arg();
	}
}




