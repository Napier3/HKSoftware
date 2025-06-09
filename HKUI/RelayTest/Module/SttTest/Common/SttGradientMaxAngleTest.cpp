#include "stdafx.h"
#include "SttGradientMaxAngleTest.h"
#include "../../Engine/SttTestServerBase.h"

CString CSttGradientMaxAngleTest::m_strMacroName = "×î´óÁéÃô½Ç²âÊÔ";
CString CSttGradientMaxAngleTest::m_strMacroID = STT_MACRO_ID_GradientMaxAngleTest;
CString CSttGradientMaxAngleTest::m_strFilePostFix = "sttGDTMaxAngle";
CString CSttGradientMaxAngleTest::m_strMacroVer ="1.0";

CSttGradientMaxAngleTest::CSttGradientMaxAngleTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

void CSttGradientMaxAngleTest::Init()
{
	CSttGradientTest::Init();
	m_bAngleF_TestFinished=FALSE;
}

long CSttGradientMaxAngleTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return true;
}

CSttGradientMaxAngleTest::~CSttGradientMaxAngleTest(void)
{
}

void CSttGradientMaxAngleTest::AfterSetParameter()
{
	m_oGradientParas.m_nType=GRADIENT_ANG;

	AngleTestTransPara();

#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->InitParaBeforeGradient(m_oGradientParas);
    CSttDeviceBase::g_pSttDeviceBase->SetChannelSelect(m_oGradientParas);
    CSttDeviceBase::g_pSttDeviceBase->CalStepValue_Gradient(m_oGradientParas);
#endif
}

double CSttGradientMaxAngleTest::GetTestTimeLong()
{
	float	fTime = 0.000;

	return fTime;
}

long CSttGradientMaxAngleTest::CalReport(UINT nState)
{
	return 0;
}

long CSttGradientMaxAngleTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttGradientMaxAngleTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
	if (m_bAngleF_TestFinished)
	{
		return;
	}

	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
}

void CSttGradientMaxAngleTest::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
{
#ifdef _PSX_QT_LINUX_
	GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;

	if(!m_bAngleF_TestFinished)
	{
		if(oRampRestCom.m_nAct==1)
		{
			m_bAngleF_TestFinished=TRUE;
            m_fAngleF=GetStdAngle(oRampRestCom.m_fTripValue);
            oRampRestCom.m_fTripValue = 0;
			m_oResultParas.m_oMaxAngle.m_nActF=1;
			m_oResultParas.m_oMaxAngle.m_nAngleF_StepIndex=m_nCurStepIndex;

			//·´ÏòËÑË÷
			float fStartAngle = m_oGradientParas.m_fStart;
			float fStopAngle = m_oGradientParas.m_fStop;
			m_oGradientParas.m_fStart = fStopAngle;
			m_oGradientParas.m_fStop = fStartAngle;
			AngleTestTransPara(FALSE);
			CSttDeviceBase::g_pSttDeviceBase->InitParaBeforeGradient(m_oGradientParas);
			CSttDeviceBase::g_pSttDeviceBase->SetChannelSelect(m_oGradientParas);
			CSttDeviceBase::g_pSttDeviceBase->CalStepValue_Gradient(m_oGradientParas);
			StartTest();
			return;
		}
	}

	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	if(oRampRestCom.m_nAct==1)
	{
		m_oResultParas.m_oMaxAngle.m_nActS=1;
		m_oResultParas.m_oMaxAngle.m_nAngleS_StepIndex=m_nCurStepIndex;
        m_fAngleS=GetStdAngle(oRampRestCom.m_fTripValue);
        oRampRestCom.m_fTripValue = 0;
        if(m_fAngleF < (m_fAngleS + EPSINON))
        {
            m_fMaxAngle=(m_fAngleS + m_fAngleF)/2.0;
        }
        else
        {
            m_fMaxAngle=GetStdAngle((m_fAngleS + m_fAngleF)/2.0 + 180.0);
        }
	}

	CalReport();
	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
	SetTestStarting(FALSE);
#endif
}
