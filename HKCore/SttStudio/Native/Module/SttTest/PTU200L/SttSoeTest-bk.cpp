#include "stdafx.h"
#include"SttSoeTest.h"
#include "../../SttDevice/SttDriverOper.h"
#include "../../SttDevice/SttDeviceBase.h"
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
	SetTestStarting(FALSE);
	Init();
}

void CSttSoeTest::Init()
{
	tmt_SoeTest::init();
	CSttTestBase::Init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
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
	memset(&m_oDrv_SOETest,0,sizeof(Drv_SOETest));
	m_oDrv_SOETest.triptype=m_oSoeParas.m_nMode;
	m_oDrv_SOETest.holdtime=m_oSoeParas.m_nHoldTime*1000;

	if(m_oDrv_SOETest.triptype==SOETYPE_GPS)
	{
		QDate date;
		date.setYMD(m_oSoeParas.m_tGps.nYear,m_oSoeParas.m_tGps.nMonth,m_oSoeParas.m_tGps.nDay);
		QTime time;
		time.setHMS(m_oSoeParas.m_tGps.nHour,m_oSoeParas.m_tGps.nMinutes,m_oSoeParas.m_tGps.nSeconds);
		QDateTime datetime;
		datetime.setDate(date);
		datetime.setTime(time);
		m_oDrv_SOETest.sec =datetime.toTime_t();
		m_oDrv_SOETest.nsec = m_oSoeParas.m_tGps.nMilliSeconds*1000*1000;
	}

	for(int i=0;i<8;i++)
	{
		if(m_oSoeParas.m_binOut[i].isValid==0)
		{
			m_oDrv_SOETest.soe.flipcnt[i]=0;
		}
		else
		{
			m_oDrv_SOETest.soe.flipcnt[i]=m_oSoeParas.m_binOut[i].cnt/2;
		}

		m_oDrv_SOETest.soe.init_val[i]=1;//实验从开关断开状态开始
		m_oDrv_SOETest.soe.init_time[i]=m_oSoeParas.m_binOut[i].otmt_SoeState[0].time*10;

		m_oDrv_SOETest.soe.firstfliptime[i]=m_oSoeParas.m_binOut[i].otmt_SoeState[1].time*10;
		m_oDrv_SOETest.soe.secondfliptime[i]=m_oSoeParas.m_binOut[i].otmt_SoeState[2].time*10;
	}

	if(!GetTestStarting())
	{
#ifdef _PSX_QT_LINUX_
		CSttDriverOper::IoCtrl(0x354,0);
		CSttDriverOper::WriteData((char*)&m_oDrv_SOETest,sizeof(Drv_SOETest));
#endif
	}
}

long CSttSoeTest::CalReport(UINT nState)
{

	return 0;
}

void CSttSoeTest::Stop()
{
	CSttTestBase::Stop();
}

long CSttSoeTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttSoeTest::EventProcess()
{
	if(!GetTestStarting())
		return;

	int nLen = sizeof(Drv_ResultItem);
#ifdef _PSX_QT_LINUX_
	int nret =CSttDeviceBase::g_pSttDeviceBase->GetTestResult(StateResult,m_pDrvResults);

	if(nret <=0)
	{
		return;
	}

	Drv_Results* pResult;
	pResult = (Drv_Results*)(m_pDrvResults);

	for(int i=0;i<nret/nLen;i++)
	{
		Drv_ResultItem oItem = pResult->oItem[i];
		double dTime=oItem.nSec+oItem.nNanoSec*0.000000001;

		switch(oItem.nType)
		{
		case Result_Type_TestStart:
			m_dTestStartTime=dTime;
			ReturnTestStateEvent_TestStart(m_dTestStartTime, 0, TRUE);
			break;
		case Result_Type_TestFinish:
			if(!IsRecvStopCmd())
				ReturnTestStateEvent_TestFinish(dTime, dTime-m_dTestStartTime, TRUE);
			SetTestStarting(FALSE);
			break;
		}
	}
#endif
}

void CSttSoeTest::StartTest()
{
	CSttTestBase::StartTest();
	if(!GetTestStarting())
	{
		CSttDriverOper::Start(0x0e);
		SetTestStarting(TRUE);
	}
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttSoeTest::DataDownload Finished");
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

