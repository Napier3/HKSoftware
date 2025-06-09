#include "stdafx.h"
#include"SttAdjust_Switch.h"
// #include<QtDebug>

CString CSttAdjust_Switch::m_strMacroName = "开关量切换";
CString CSttAdjust_Switch::m_strMacroID = STT_ADJUST_MACRO_ID_AdjustSwitch;
CString CSttAdjust_Switch::m_strFilePostFix = "stthrt";
CString CSttAdjust_Switch::m_strMacroVer ="1.0";

CSttAdjust_Switch::CSttAdjust_Switch() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttAdjust_Switch::Init()
{
	TMT_ADJ_SWITCH_OUTPUT::init();
}

long CSttAdjust_Switch::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttAdjust_Switch::~CSttAdjust_Switch(void)
{
}

void CSttAdjust_Switch::AfterSetParameter()
{
}

double CSttAdjust_Switch::GetTestTimeLong()
{
    float fTime = TIME_ONLINE_DELAY;

//	fTime = m_oHarmParas.m_fOutPutTime;
//	fTime += TIME_ONLINE_DELAY;

	return fTime;
}

long CSttAdjust_Switch::CalReport(UINT nState)
{

	return 0;
}

void CSttAdjust_Switch::Stop()
{
	CSttTestBase::Stop();
}

long CSttAdjust_Switch::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttAdjust_Switch::StartTest()
{
	CSttTestBase::StartTest();
    //TtmToDrv();

    /*
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
*/

	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttAdjust_Three::DataDownload Finished");
}


void CSttAdjust_Switch::TtmToDrv()
{

}

void CSttAdjust_Switch::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}


