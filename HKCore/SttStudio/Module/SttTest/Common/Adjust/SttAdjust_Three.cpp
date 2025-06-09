#include "stdafx.h"
#include"SttAdjust_Three.h"
// #include<QtDebug>

CString CSttAdjust_Three::m_strMacroName = "三通道校准";
CString CSttAdjust_Three::m_strMacroID = STT_ADJUST_MACRO_ID_AdjustThree;
CString CSttAdjust_Three::m_strFilePostFix = "stthrt";
CString CSttAdjust_Three::m_strMacroVer ="1.0";

CSttAdjust_Three::CSttAdjust_Three() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttAdjust_Three::Init()
{
    TMT_ADJUST_THREE::init();
}

long CSttAdjust_Three::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttAdjust_Three::~CSttAdjust_Three(void)
{
}

void CSttAdjust_Three::AfterSetParameter()
{
}

double CSttAdjust_Three::GetTestTimeLong()
{
    float fTime = TIME_ONLINE_DELAY;

//	fTime = m_oHarmParas.m_fOutPutTime;
//	fTime += TIME_ONLINE_DELAY;

	return fTime;
}

long CSttAdjust_Three::CalReport(UINT nState)
{

	return 0;
}

void CSttAdjust_Three::Stop()
{
	CSttTestBase::Stop();
}

long CSttAdjust_Three::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttAdjust_Three::StartTest()
{
	CSttTestBase::StartTest();
    //TtmToDrv();

	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttAdjust_Three::DataDownload Finished");
}


void CSttAdjust_Three::TtmToDrv()
{

}

void CSttAdjust_Three::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}


