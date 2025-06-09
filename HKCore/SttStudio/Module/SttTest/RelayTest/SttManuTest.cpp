#include "stdafx.h"
#include"SttManuTest.h"
#include "../../SttDevice/SttDeviceBase.h"

CString CSttManuTest::m_strMacroName = "电压电流试验";
CString CSttManuTest::m_strMacroID = ("SttManuTest");
CString CSttManuTest::m_strFilePostFix = "sttuit";
//#include<QtDebug>

CSttManuTest::CSttManuTest() : CGradientBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	Init();
}

void CSttManuTest::Init()
{
	tmt_ManualTest::init();
	CSttTestBase::Init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	memset(m_oDrvResults,0,sizeof(structRampResult)*100);
}

long CSttManuTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	int nNum;
	int nRet =CSttDeviceBase::g_pSttDeviceBase->GetTestResult(GradientResult,(char *)&m_oDrvResults);
	nNum = nRet/sizeof(structRampResult);  // Result   nums
	if(nRet <= 0)
		return false;

	if(nNum<1)//
	{
		return 0;
	}

	UINT nBinOrg=0x3FF;
	for(int i=0; i<nNum; i++)
	{
		int nSec=m_oDrvResults[i].nSec;
		int nNanoSec=m_oDrvResults[i].nNanoSec/65536.0/65536.0;

		switch(m_oDrvResults[i].nType)
		{
		case GRADIENT_RESULT_START:
			m_uStartTimeS = nSec;
			m_uStartTimeMS = nNanoSec;
			break;
		case GRADIENT_RESULT_CHANGE:
			m_uChangeTime = nSec;
			m_uChangeTimeMS = nNanoSec;
			break;
		case GRADIENT_RESULT_DI_CHANGE:
			if(m_bIsReturn)
			{
				m_oManuResult.m_fReturnTime = nSec + nNanoSec - \
						m_uReturnTime - m_uReturnTimeMS;

				m_oManuResult.m_fReturnValue = m_oDrvResults[i].nStep*m_oManuParas.m_manuGradient.fStep + \
						m_oManuParas.m_manuGradient.fStart;
			}
			else
			{
				m_oManuResult.m_fTripTime = nSec + nNanoSec - m_uChangeTime - m_uChangeTimeMS;

				m_oManuResult.m_fActValue = m_oDrvResults[i].nStep*m_oManuParas.m_manuGradient.fStep +\
						m_oManuParas.m_manuGradient.fStart;
			}
			break;
		case GRADIENT_RESULT_RETURN:
			m_bIsReturn = true;
			m_uReturnTime = nSec;
			m_uReturnTimeMS = nNanoSec;
			break;
		case GRADIENT_RESULT_STOP:
			bFinish = true;
			m_bIsReturn = false;
			break;
		}
	}
	return true;
}

CSttManuTest::~CSttManuTest(void)
{
}

void CSttManuTest::AfterSetParameter()
{
	m_oManuResult.m_fTripTime = 0;
	m_oManuResult.m_fActValue = 0;
	m_oManuResult.m_fReturnValue = 0;
	m_oManuResult.m_fReturnTime = 0;

	if (m_oManuParas.m_bDC)
	{
		for (int j=0;j<MAX_VOLTAGE_COUNT;j++)
			m_oManuParas.m_uiVOL[j].Harm[1].fFreq = m_oManuParas.m_uiVOL[j].Harm[1].fAngle = 0;
		for (int j=0;j<MAX_CURRENT_COUNT;j++)
			m_oManuParas.m_uiCUR[j].Harm[1].fFreq = m_oManuParas.m_uiCUR[j].Harm[1].fAngle = 0;
	}

	if(m_oManuParas.m_bAuto)
	{
		CGradientBase::SetChannelSelect(m_oManuParas.m_nGradientChSelect,m_oManuParas.m_nGradientTpSelect);

		CalStepValue_Gradient(m_oManuParas.m_manuGradient.fStart, m_oManuParas.m_manuGradient.fEnd, m_oManuParas.m_manuGradient.fStep,
							  m_oManuParas.m_uiVOL, m_oManuParas.m_uiCUR/*, m_oGradientProcess.m_uiStepData*/);
	}
}

double CSttManuTest::GetTestTimeLong()
{
	float fTime;

	fTime = m_oManuParas.m_fOutPutTime;
	fTime += TIME_ONLINE_DELAY;

	return fTime;
}

long CSttManuTest::CalReport(UINT nState)
{

	return 0;
}

void CSttManuTest::Stop()
{
	CSttTestBase::Stop();
}

long CSttManuTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttManuTest::StartTest()
{
	CSttTestBase::StartTest();
	TtmToDrv();

	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(ManualTest,(char*)&m_oDrvManuGradient.m_oManuStruct,\
												  sizeof(m_oDrvManuGradient.m_oManuStruct));

	CSttDeviceBase::g_pSttDeviceBase->SetManualBI((char*)&m_oDrvManuGradient.m_oManuBinStruct,\
												  sizeof(m_oDrvManuGradient.m_oManuBinStruct));

	if(m_oManuParas.m_bAuto)//auto
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

	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttManuTest::DataDownload Finished");
}

void CSttManuTest::CalStepValue(float fCurValue)
{
#ifdef _PSX_IDE_QT_
	for(int i=0;i<ChannelVolts.size();i++)
	{
		int chan=ChannelVolts.at(i);
		switch(m_oManuParas.m_nGradientTpSelect)
		{
		case GRADIENT_AMP:
			m_oManuParas.m_uiVOL[chan].Harm[1].fAmp = fCurValue;
			break;
		case GRADIENT_ANG:
			m_oManuParas.m_uiVOL[chan].Harm[1].fAngle = fCurValue;
			break;
		case GRADIENT_FRE:
			m_oManuParas.m_uiVOL[chan].Harm[1].fFreq = fCurValue;
			break;
		}
	}

	for(int i=0;i<ChannelCurrs.size();i++)
	{
		int chan=ChannelCurrs.at(i);
		switch(m_oManuParas.m_nGradientTpSelect)
		{
		case GRADIENT_AMP:
			m_oManuParas.m_uiCUR[chan].Harm[1].fAmp = fCurValue;
			break;
		case GRADIENT_ANG:
			m_oManuParas.m_uiCUR[chan].Harm[1].fAngle = fCurValue;
			break;
		case GRADIENT_FRE:
			m_oManuParas.m_uiCUR[chan].Harm[1].fFreq = fCurValue;
			break;
		}
	}
#endif
}

void CSttManuTest::TtmToDrv()
{
#ifdef _PSX_IDE_QT_
	tmt_to_drv(this, &m_oGradientProcess, &m_oDrvManuGradient);
#endif
}

void CSttManuTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oManuParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}


