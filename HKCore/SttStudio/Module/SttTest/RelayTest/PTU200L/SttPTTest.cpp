#include "stdafx.h"
#include"SttPTTest.h"
#include "../../../SttDevice/RelayTest/SttDriverOper.h"


CString CSttPtTest::m_strMacroName = "PT测试";
CString CSttPtTest::m_strMacroID = ("SttPtTest");
CString CSttPtTest::m_strFilePostFix = "sttptt";
CString CSttPtTest::m_strMacroVer ="1.0";

CSttPtTest::CSttPtTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttPtTest::Init()
{
	tmt_PtTest::init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

long CSttPtTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttPtTest::~CSttPtTest(void)
{
}

void CSttPtTest::AfterSetParameter()
{	
	unsigned int r = 0;
	switch(m_oPtPara.m_nPT1)
	{
	case 120:
		r |= PT100_R1_120_Ohm;
		break;
	case 100:
		r |= PT100_R1_100_Ohm;
		break;
	default:
		r |= PT100_R1_90_Ohm;
		break;
	}

	switch(m_oPtPara.m_nPT2)
	{
	case 120:
		r |= PT100_R2_120_Ohm;
		break;
	case 100:
		r |= PT100_R2_100_Ohm;
		break;
	default:
		r |= PT100_R2_90_Ohm;
		break;
	}

	CSttDriverOper::IoCtrl(0x135,r);
}

long CSttPtTest::CalReport(UINT nState)
{

	return 0;
}

void CSttPtTest::Stop()
{

}

long CSttPtTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttPtTest::StartTest()
{
	CSttTestBase::StartTest();
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttPtTest::DataDownload Finished");
}


void CSttPtTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oPtPara,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttPtTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	Para_XmlSerialize(pXmlSerialize);
}
