#include "stdafx.h"
#include"SttHarmTest.h"
#include "../../SttDevice/PTU/SttDriverOper.h"
#include "../../SttDevice/PTU/SttDevice.h"
#include "./define.h"
// #include<QtDebug>

CString CSttHarmTest::m_strMacroName = "谐波测试";
CString CSttHarmTest::m_strMacroID = ("SttHarmTest");
CString CSttHarmTest::m_strFilePostFix = "stthrt";
CString CSttHarmTest::m_strMacroVer ="1.0";

CSttHarmTest::CSttHarmTest()
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
	m_Start=false;
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
	TtmToDrv();
}



long CSttHarmTest::CalReport(UINT nState)
{

	return 0;
}

void CSttHarmTest::Stop()
{
	m_Start=false;
	if(CSttDeviceBase::g_pSttDeviceBase->IsStartTest_UserParameter())
	{
		CSttDeviceBase::g_pSttDeviceBase->StartTest_UserParameter();
	}
	else
	{
		CSttDriverOper::Stop();
	}
}

long CSttHarmTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttHarmTest::StartTest()
{
	if(!m_Start)
	{
		m_Start=true;
		CSttTestBase::StartTest();
		CSttDriverOper::Start(1);
	}
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttHarmTest::DataDownload Finished");
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

void CSttHarmTest::setTap()
{
	int nTap = 0;
	int nUtap = 0;
	for(int i=0;i<4;i++)
	{
		if(m_oHarmParas.m_uiVOL[i].Harm[1].fAmp > 300)
			nUtap |= 1<<i;
	}
	int nItap = 128;

	int nDCTap=0;
	long nTemp = 0/*d_Data->oacpara().oacanlogpara().fvoltdc(0)*/*1000000;
	if(nTemp<=120000)
	{
		nDCTap =1<<4;
	}
	else if(nTemp<=1200000 && nTemp>120000)
	{
		nDCTap=1<<5;
	}
	else if(nTemp<=12000000 && nTemp>1200000)
	{

	}
	else if(nTemp>1200000)
	{
		nDCTap=1<<6;
	}
	nTap |= nUtap;
	nTap |= nItap;
	nTap |= nDCTap;
	CSttDriverOper::setOutPutTap(nTap);
}

void CSttHarmTest::TtmToDrv()
{
#ifdef L336D
	TtmToDrv_L336D();
#else
	TtmToDrv_PTU();
#endif
}

void CSttHarmTest::TtmToDrv_L336D()
{
#ifdef L336D
#endif
}

void CSttHarmTest::TtmToDrv_PTU()
{
#ifndef L336D
	memset(&m_oDrvManu,0,sizeof(Drv_ManuPara));
	m_oDrvManu.moduleCount =2;
	m_oDrvManu.waveCount[0] = 6+3*6*31;
	m_oDrvManu.waveCount[1] = 6+3*6*31;

	Drv_ManuAnalogPara Curanal;
	Drv_ManuAnalogPara Voltanal;
	memset(&Curanal,0,sizeof(Drv_ManuAnalogPara));
	Curanal.module = 1;
	memset(&Voltanal,0,sizeof(Drv_ManuAnalogPara));
	Voltanal.module = 0;

	for(int i=0;i<4;i++)
	{
		if(m_oHarmParas.m_uiVOL[i].Harm[1].fAmp>300)
			m_oHarmParas.m_uiVOL[i].Harm[1].fAmp=300;

		if(m_oHarmParas.m_uiCUR[i].Harm[1].fAmp>20)
			m_oHarmParas.m_uiCUR[i].Harm[1].fAmp=20;

		//CSttDevice::g_pSttDevice->TranslateACVoltBufferDC(m_oHarmParas.m_uiVOL[i].Harm[1].fAmp,i,Voltanal.nDc);
		//CSttDevice::g_pSttDevice->TranslateACCurrentBufferDC(m_oHarmParas.m_uiCUR[i].Harm[1].fAmp,i,Curanal.nDc);
		CSttDevice::g_pSttDevice->TranslateACVoltBufferDC(m_oHarmParas.m_uiVOL[i].Harm[1].fAmp,i,Voltanal.dat);
		CSttDevice::g_pSttDevice->TranslateACCurrentBufferDC(m_oHarmParas.m_uiCUR[i].Harm[1].fAmp,i,Curanal.dat);

		for(int j=0;j<31;j++)
		{
			CSttDevice::g_pSttDevice->TranslateACVoltBuffer(m_oHarmParas.m_uiVOL[i].Harm[j+1].fAmp\
					,m_oHarmParas.m_uiVOL[i].Harm[j+1].fAngle,\
					m_oHarmParas.m_uiVOL[i].Harm[j+1].fFreq,\
					i,Voltanal.dat+6,j);

			CSttDevice::g_pSttDevice->TranslateACCurrentBuffer(m_oHarmParas.m_uiCUR[i].Harm[j+1].fAmp\
					,m_oHarmParas.m_uiCUR[i].Harm[j+1].fAngle,\
					m_oHarmParas.m_uiCUR[i].Harm[j+1].fFreq,\
					i,Curanal.dat+6,j);
		}
	}
	m_oDrvManu.stAlg[0] = Curanal;
	m_oDrvManu.stAlg[1] = Voltanal;

	setTap();
	float fDAValue[3]  ={300,7.5,300};
	CSttDevice::g_pSttDevice->SetDeviceInnerParaSet(fDAValue);

	CSttDriverOper::setManualAcAnalogPara((char*)&m_oDrvManu,sizeof(Drv_ManuPara));
#endif
}
