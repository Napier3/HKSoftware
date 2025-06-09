#include "stdafx.h"
#include"SttGradientTest.h"

CString CSttGradientTest::m_strMacroName = "递变测试";
CString CSttGradientTest::m_strMacroID = ("SttGradientTest");
CString CSttGradientTest::m_strFilePostFix = "sttGDT";
CString CSttGradientTest::m_strMacroVer ="1.0";
//#include<QtDebug>

CSttGradientTest::CSttGradientTest() : CGradientBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

void CSttGradientTest::Init()
{ 
	float fAng[3] = {0, -120, 120};
	for (int j=0;j<MAX_VOLTAGE_COUNT;j++)
	{
		m_oGradientParas.m_uiVOL[0][j].Harm[1].nIndex = m_oGradientParas.m_uiVOL[1][j].Harm[1].nIndex = m_oGradientParas.m_uiVOL[2][j].Harm[1].nIndex = 1;
		m_oGradientParas.m_uiCUR[0][j].Harm[1].nIndex = m_oGradientParas.m_uiCUR[1][j].Harm[1].nIndex = m_oGradientParas.m_uiCUR[2][j].Harm[1].nIndex = 1;
		m_oGradientParas.m_uiVOL[0][j].Harm[1].fContent = m_oGradientParas.m_uiVOL[1][j].Harm[1].fContent = m_oGradientParas.m_uiVOL[2][j].Harm[1].fContent = 100;
		m_oGradientParas.m_uiCUR[0][j].Harm[1].fContent = m_oGradientParas.m_uiCUR[1][j].Harm[1].fContent = m_oGradientParas.m_uiCUR[2][j].Harm[1].fContent = 100;
		m_oGradientParas.m_uiVOL[0][j].Harm[1].fAmp = m_oGradientParas.m_uiVOL[1][j].Harm[1].fAmp = m_oGradientParas.m_uiVOL[2][j].Harm[1].fAmp = m_oGradientParas.m_fU;
		m_oGradientParas.m_uiCUR[0][j].Harm[1].fAmp = m_oGradientParas.m_uiCUR[1][j].Harm[1].fAmp = m_oGradientParas.m_uiCUR[2][j].Harm[1].fAmp = m_oGradientParas.m_fI;
		m_oGradientParas.m_uiVOL[0][j].Harm[1].fAngle = m_oGradientParas.m_uiVOL[1][j].Harm[1].fAngle = m_oGradientParas.m_uiVOL[2][j].Harm[1].fAngle = fAng[j%3];
		m_oGradientParas.m_uiCUR[0][j].Harm[1].fAngle = m_oGradientParas.m_uiCUR[1][j].Harm[1].fAngle = m_oGradientParas.m_uiCUR[2][j].Harm[1].fAngle = fAng[j%3];
		m_oGradientParas.m_uiVOL[0][j].Harm[1].fFreq = m_oGradientParas.m_uiVOL[1][j].Harm[1].fFreq = m_oGradientParas.m_uiVOL[0][j].Harm[1].fFreq = m_oGradientParas.m_fFreq;
		m_oGradientParas.m_uiCUR[0][j].Harm[1].fFreq = m_oGradientParas.m_uiCUR[1][j].Harm[1].fFreq = m_oGradientParas.m_uiCUR[2][j].Harm[1].fFreq = m_oGradientParas.m_fFreq;
	}
}

long CSttGradientTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{

	return true;
}

CSttGradientTest::~CSttGradientTest(void)
{
}

void CSttGradientTest::AfterSetParameter()
{
	CGradientBase::SetChannelSelect(m_oGradientParas.m_nChannel,m_oGradientParas.m_nType);

	CalStepValue_Gradient(m_oGradientParas.m_fStart, m_oGradientParas.m_fStop, m_oGradientParas.m_fStep,
						  m_oGradientParas.m_uiVOL[2], m_oGradientParas.m_uiCUR[2]/*, m_oGradientProcess.m_uiStepData*/);
}

double CSttGradientTest::GetTestTimeLong()
{
	float	fTime = 0.000;

	return fTime;
}

long CSttGradientTest::CalReport(UINT nState)
{

	return 0;
}

long CSttGradientTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttGradientTest::StartTest()
{
	CSttTestBase::StartTest();
	TtmToDrv();

#ifdef _PSX_IDE_QT_

	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(ManualTest,\
												  (char*)&m_oDrvManuGradient.m_oManuStruct,\
												  sizeof(m_oDrvManuGradient.m_oManuStruct));

	CSttDeviceBase::g_pSttDeviceBase->SetManualBI((char*)&m_oDrvManuGradient.m_oManuBinStruct,\
												  sizeof(m_oDrvManuGradient.m_oManuBinStruct));

	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(GradientTest,\
												  (char*)&m_oDrvManuGradient.m_oGradientStruct,\
												  sizeof(m_oDrvManuGradient.m_oGradientStruct));

	CSttDeviceBase::g_pSttDeviceBase->SetTestStart(GradientTest);

#endif
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttGradientTest::DataDownload Finished");
}

void CSttGradientTest::Stop()
{  
	CSttTestBase::Stop();
}

void CSttGradientTest::TtmToDrv()
{
#ifdef _PSX_IDE_QT_
	tmt_to_drv(this, &m_oDrvManuGradient, &m_oGradientProcess);
#endif
}

void CSttGradientTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oGradientParas, pXmlSerialize);
	
	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttGradientTest::CalStepValue(float fCurValue)
{
#ifdef _PSX_IDE_QT_
	for(int i=0;i<ChannelVolts.size();i++)
	{
		int chan=ChannelVolts.at(i);
		switch(m_oGradientParas.m_nType)
		{
		case GRADIENT_AMP:
			m_oGradientParas.m_uiVOL[2][chan].Harm[1].fAmp = fCurValue;
			break;
		case GRADIENT_ANG:
			m_oGradientParas.m_uiVOL[2][chan].Harm[1].fAngle = fCurValue;
			break;
		case GRADIENT_FRE:
			m_oGradientParas.m_uiVOL[2][chan].Harm[1].fFreq = fCurValue;
			break;
		}
	}

	for(int i=0;i<ChannelCurrs.size();i++)
	{
		int chan=ChannelCurrs.at(i);
		switch(m_oGradientParas.m_nType)
		{
		case GRADIENT_AMP:
			m_oGradientParas.m_uiCUR[2][chan].Harm[1].fAmp = fCurValue;
			break;
		case GRADIENT_ANG:
			m_oGradientParas.m_uiCUR[2][chan].Harm[1].fAngle = fCurValue;
			break;
		case GRADIENT_FRE:
			m_oGradientParas.m_uiCUR[2][chan].Harm[1].fFreq = fCurValue;
			break;
		}
	}
#endif
}


