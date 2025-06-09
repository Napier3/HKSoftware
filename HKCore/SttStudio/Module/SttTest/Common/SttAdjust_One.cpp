#include "stdafx.h"
#include"SttAdjust_One.h"
// #include<QtDebug>

CString CSttAdjust_One::m_strMacroName = "单通道校准";
CString CSttAdjust_One::m_strMacroID = STT_ADJUST_MACRO_ID_AdjustOne;
CString CSttAdjust_One::m_strFilePostFix = "stthrt";
CString CSttAdjust_One::m_strMacroVer ="1.0";

CSttAdjust_One::CSttAdjust_One() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttAdjust_One::Init()
{
    TMT_ADJUST_ONE::init();
}

long CSttAdjust_One::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttAdjust_One::~CSttAdjust_One(void)
{
}

void CSttAdjust_One::AfterSetParameter()
{
}

double CSttAdjust_One::GetTestTimeLong()
{
    float fTime = TIME_ONLINE_DELAY;

//	fTime = m_oHarmParas.m_fOutPutTime;
//	fTime += TIME_ONLINE_DELAY;

	return fTime;
}

long CSttAdjust_One::CalReport(UINT nState)
{

	return 0;
}

void CSttAdjust_One::Stop()
{
	CSttTestBase::Stop();
}

long CSttAdjust_One::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttAdjust_One::StartTest()
{
	CSttTestBase::StartTest();
    //TtmToDrv();

	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttAdjust_One::DataDownload Finished");
}


void CSttAdjust_One::TtmToDrv()
{

}

void CSttAdjust_One::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}


