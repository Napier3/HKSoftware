#include "stdafx.h"
#include"SttHarmTest.h"
// #include<QtDebug>

CString CSttHarmTest::m_strMacroName = "谐波测试";
CString CSttHarmTest::m_strMacroID = ("SttHarmTest");
CString CSttHarmTest::m_strFilePostFix = "stthrt";
CString CSttHarmTest::m_strMacroVer ="1.0";

CSttHarmTest::CSttHarmTest() : CGradientBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttHarmTest::Init()
{
	tmt_HarmTest::init();
	CSttTestBase::Init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	//    memset(m_oDrvResults,0,sizeof(drv_gradient_result)*100);
}

long CSttHarmTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttHarmTest::~CSttHarmTest(void)
{
}

void CSttHarmTest::AfterSetParameter()
{
	if(m_oHarmParas.m_bAuto)
	{
		CGradientBase::SetChannelSelect(m_oHarmParas.m_nGradientChSelect,m_oHarmParas.m_nGradientTpSelect);

		CalStepValue_Gradient(m_oHarmParas.m_oHarmGradient.fStart, m_oHarmParas.m_oHarmGradient.fEnd, m_oHarmParas.m_oHarmGradient.fStep,
							  m_oHarmParas.m_uiVOL, m_oHarmParas.m_uiCUR, m_oHarmParas.m_oHarmGradient.nHarmIndex);
	}
}

double CSttHarmTest::GetTestTimeLong()
{
	float fTime;

	fTime = m_oHarmParas.m_fOutPutTime;
	fTime += TIME_ONLINE_DELAY;

	return fTime;
}

long CSttHarmTest::CalReport(UINT nState)
{

	return 0;
}

void CSttHarmTest::Stop()
{
	CSttTestBase::Stop();
}

long CSttHarmTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttHarmTest::StartTest()
{
	CSttTestBase::StartTest();
	TtmToDrv();

#ifdef _PSX_IDE_QT_
	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(ManualTest,\
												  (char*)&m_oDrvManuGradient.m_oManuStruct,\
												  sizeof(m_oDrvManuGradient.m_oManuStruct));

	CSttDeviceBase::g_pSttDeviceBase->SetManualBI((char*)&m_oDrvManuGradient.m_oManuBinStruct,\
												 sizeof(m_oDrvManuGradient.m_oManuBinStruct) );
	if(m_oHarmParas.m_bAuto)//auto
	{
		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(GradientTest,\
								(char*)&m_oDrvManuGradient.m_oGradientStruct,\
								sizeof(m_oDrvManuGradient.m_oGradientStruct));
		CSttDeviceBase::g_pSttDeviceBase->SetTestStart(GradientTest);
	}
	else//manu
	{
		CSttDeviceBase::g_pSttDeviceBase->SetTestStart(ManualTest);
	}
#endif

	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttHarmTest::DataDownload Finished");
}

void CSttHarmTest::CalStepValue(float fCurValue)
{
#ifdef _PSX_IDE_QT_
	int nHarmIndex = m_oHarmParas.m_oHarmGradient.nHarmIndex;
	for(int i=0;i<ChannelVolts.size();i++)
	{
		int chan=ChannelVolts.at(i);
		switch(m_oHarmParas.m_nGradientTpSelect)
		{
		case GRADIENT_AMP:
			m_oHarmParas.m_uiVOL[chan].Harm[nHarmIndex].fAmp = fCurValue;
			break;
		case GRADIENT_ANG:
			m_oHarmParas.m_uiVOL[chan].Harm[nHarmIndex].fAngle = fCurValue;
			break;
		case GRADIENT_FRE:
			m_oHarmParas.m_uiVOL[chan].Harm[nHarmIndex].fFreq = fCurValue;
			break;
		}
	}

	for(int i=0;i<ChannelCurrs.size();i++)
	{
		int chan=ChannelCurrs.at(i);
		switch(m_oHarmParas.m_nGradientTpSelect)
		{
		case GRADIENT_AMP:
			m_oHarmParas.m_uiCUR[chan].Harm[nHarmIndex].fAmp = fCurValue;
			break;
		case GRADIENT_ANG:
			m_oHarmParas.m_uiCUR[chan].Harm[nHarmIndex].fAngle = fCurValue;
			break;
		case GRADIENT_FRE:
			m_oHarmParas.m_uiCUR[chan].Harm[nHarmIndex].fFreq = fCurValue;
			break;
		}
	}
#endif
}

void CSttHarmTest::TtmToDrv()
{
#ifdef _PSX_IDE_QT_
	tmt_to_drv(this, &m_oGradientProcess, &m_oDrvManuGradient);
#endif
}

void CSttHarmTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oHarmParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}


