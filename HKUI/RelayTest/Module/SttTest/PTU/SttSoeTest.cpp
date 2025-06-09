#include "stdafx.h"
#include"SttSoeTest.h"
#include "../../SttDevice/PTU/SttDriverOper.h"
#include "../../SttDevice/PTU/SttDevice.h"
#include "./define.h"
// #include<QtDebug>

CString CSttSoeTest::m_strMacroName = "开出测试";
CString CSttSoeTest::m_strMacroID = ("SttSoeTest");
CString CSttSoeTest::m_strFilePostFix = "sttsoet";
CString CSttSoeTest::m_strMacroVer ="1.0";

CSttSoeTest::CSttSoeTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttSoeTest::Init()
{
	tmt_SoeTest::init();
	CSttTestBase::Init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	m_Start=false;
	//    memset(m_oDrvResults,0,sizeof(drv_gradient_result)*100);
}

long CSttSoeTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttSoeTest::~CSttSoeTest(void)
{
}

void CSttSoeTest::AfterSetParameter()
{
	memset(&m_oDrvSoe,0,sizeof(Drv_SOETest));
	m_oDrvSoe.type=m_oSoeParas.m_nMode;
	if(m_oDrvSoe.type==1)
	{
		QDate date;
		date.setYMD(m_oSoeParas.m_tGps.nYear,m_oSoeParas.m_tGps.nMonth,m_oSoeParas.m_tGps.nDay);
		QTime time;
		time.setHMS(m_oSoeParas.m_tGps.nHour,m_oSoeParas.m_tGps.nMinutes,m_oSoeParas.m_tGps.nSeconds);
		QDateTime datetime;
		datetime.setDate(date);
		datetime.setTime(time);
		m_oDrvSoe.tm_h =datetime.toTime_t();
		m_oDrvSoe.tm_l = m_oSoeParas.m_tGps.nMilliSeconds*1000*1000;
	}

	for(int i=0;i<8;i++)
	{
		m_oDrvSoe.st[i].isValid=m_oSoeParas.m_binOut[i].isValid;
		m_oDrvSoe.st[i].cnt=m_oSoeParas.m_binOut[i].cnt;

		m_oDrvSoe.st[i].state[0].val=0;
		m_oDrvSoe.st[i].state[1].val=1;
		m_oDrvSoe.st[i].state[2].val=0;

		for(int j=0;j<3;j++)
		{
			m_oDrvSoe.st[i].state[j].sec=m_oSoeParas.m_binOut[i].otmt_SoeState[j].time;
			m_oDrvSoe.st[i].state[j].nSec=(m_oSoeParas.m_binOut[i].otmt_SoeState[j].time-\
										   m_oDrvSoe.st[i].state[j].sec)*1000*1000*1000;
		}
	}

	CSttDriverOper::setSearchAcAnalogPara((char*)&m_oDrvSoe,sizeof(Drv_SOETest),0);
}

long CSttSoeTest::CalReport(UINT nState)
{

	return 0;
}

void CSttSoeTest::Stop()
{
	m_Start=false;
	CSttDriverOper::Stop();
}

long CSttSoeTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttSoeTest::StartTest()
{
	if(!m_Start)
	{
		m_Start=true;
		CSttTestBase::StartTest();
		CSttDriverOper::Start(8);
		CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttSoeTest::DataDownload Finished");
	}
}


void CSttSoeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oSoeParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

