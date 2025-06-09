#include "stdafx.h"
#include"SttPTTest.h"
#include "../../SttDevice/PTU/SttDriverOper.h"
#include "../../SttDevice/PTU/SttDevice.h"
#include "./define.h"
// #include<QtDebug>

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
	CSttTestBase::Init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	m_Start=false;
	//    memset(m_oDrvResults,0,sizeof(drv_gradient_result)*100);
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
	switch(m_oPtPara.value)
	{
	case 90:
		CSttDriverOper::IoCtrl(0x7000406C,0xf000);//90  1111 0000
		break;
	case 100:
		//CSttDriverOper::IoCtrl(0x7000406C,0x2000);//100  0010 0000
		//CSttDriverOper::IoCtrl(0x7000406C,0x6000);//100  0110 0000
		//CSttDriverOper::IoCtrl(0x7000406C,0xa000);//100  1010 0000
		CSttDriverOper::IoCtrl(0x7000406C,0xe000);//100  1110 0000
		break;
	case 120:
		//CSttDriverOper::IoCtrl(0x7000406C,0x4000);//120  0100 0000
		//CSttDriverOper::IoCtrl(0x7000406C,0x8000);//120  1000 0000
		CSttDriverOper::IoCtrl(0x7000406C,0xc000);//120  1100 0000
		break;		
	}
}

long CSttPtTest::CalReport(UINT nState)
{

	return 0;
}

void CSttPtTest::Stop()
{
	m_Start=false;
	if(CSttDeviceBase::g_pSttDeviceBase->IsStartTest_UserParameter())
	{
		CSttDeviceBase::g_pSttDeviceBase->StartTest_UserParameter();
	}
	else
		CSttDriverOper::Stop();
}

long CSttPtTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttPtTest::StartTest()
{
	if(!m_Start)
	{
		m_Start=true;
		CSttTestBase::StartTest();
	}
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

