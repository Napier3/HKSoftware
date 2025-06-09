#include "stdafx.h"
#include"SttStateTest.h"
#include "../../SttDevice/PTU/SttDevice.h"

CString CSttStateTest::m_strMacroName = "状态序列测试";
CString CSttStateTest::m_strMacroID = ("SttStateTest");
CString CSttStateTest::m_strFilePostFix = "stttst";
CString CSttStateTest::m_strMacroVer ="1.0";

CSttStateTest::CSttStateTest() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	Init(MAX_STATETEST_COUNT);
}

void CSttStateTest::Init(long nStateNums)
{ 
	tmt_StateTest::init(nStateNums);
	CSttTestBase::Init();
	m_nCurStateIndex = -1;
	m_Start=false;
}

CSttStateTest::~CSttStateTest(void)
{
}

void CSttStateTest::AfterSetParameter()
{	
	TtmToDrv();
}

void CSttStateTest::EventProcess()
{
	int nret = CSttDriverOper::readManualResult((char*)&m_oDrvResult,sizeof(Drv_Result));

	if(nret <28)
	{
		return;
	}

	for(int i=0;i<m_oDrvResult.nCount;i++)
	{
		qDebug()<<"type "<<m_oDrvResult.stResult[i].type;
		//		qDebug()<<"biValue "<<m_oDrvResult.stResult[i].biValue;
		//		qDebug()<<"sec "<<m_oDrvResult.stResult[i].nSec;
		//		qDebug()<<"NanoSec "<<m_oDrvResult.stResult[i].nNanoSec;

		switch(m_oDrvResult.stResult[i].type)
		{
		case RESULT_START:
			m_nCurStateIndex=0;
			nPreBiVal=m_oDrvResult.stResult[i].biValue;
			break;
		case RESULT_STOP:
			if(m_Start)
			{
				m_Start=false;
				if(CSttDeviceBase::g_pSttDeviceBase->IsStartTest_UserParameter())
				{
					CSttDeviceBase::g_pSttDeviceBase->StartTest_UserParameter();
				}
			}
			break;
		case RESULT_BI_CHANGE:
			break;
		case RESULT_STATE_CHANGE:
			m_nCurStateIndex=m_oDrvResult.stResult[i].step;
			break;
		}
	}
}

long CSttStateTest::CalReport(UINT nState)
{
	return 0;
}

void CSttStateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oStateParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

long CSttStateTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttStateTest::Stop()
{	
	if(m_Start)
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

		CSttDriverOper::setOutPutStatue(0x00);
	}
}

void CSttStateTest::Triger()
{
#ifdef OS_QT_LINUX
	CSttDeviceBase::g_pSttDeviceBase->SetStateTriger();
#endif
}

void CSttStateTest::StartTest()
{	
	if(!m_Start)
	{
		m_Start=true;
		CSttTestBase::StartTest();
		CSttDriverOper::Start(2);
		CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttStateTest::DataDownload Finished");
	}
}

void CSttStateTest::TtmToDrv()
{
#ifdef L336D
	TtmToDrv_L336D();
#else
	TtmToDrv_PTU();
#endif
}

void CSttStateTest::TtmToDrv_L336D()
{
#ifdef L336D
#endif
}

void CSttStateTest::TtmToDrv_PTU()
{
#ifndef L336D
	memset(&m_oDrvStateParas,0,sizeof(Drv_StateParas));

	for(int nIndex = 0;nIndex<m_oStateParas.m_nStateNumbers;nIndex++)
	{
		m_oStateResults.m_resultState[nIndex].init();
	}

	m_nCurStateIndex = 0;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;

	int nStateCount = 0;

	m_oDrvStateParas.moduleCount = 2;
	m_oDrvStateParas.isLoop =m_oStateParas.m_nRepeatNumbers;


	float fDAValue[3]  ={0,0,300};

	for(int j=0;j<m_oStateParas.m_nStateNumbers;j++)
	{
		Drv_StateAnalogPara Cur,Volt;
		memset(&Cur,0,sizeof(Drv_StateAnalogPara));
		Cur.module = 1;
		Cur.cnt=42;
		memset(&Volt,0,sizeof(Drv_StateAnalogPara));
		Volt.module = 0;
		Volt.cnt=42;

		Drv_ManuAnalogPara Voltanal,Curanal;
		memset(&Voltanal,0,sizeof(Drv_ManuAnalogPara));
		memset(&Curanal,0,sizeof(Drv_ManuAnalogPara));

		tmt_StatePara otmt_StatePara=m_oStateParas.m_paraState[j];

		Drv_StatePara oDrv_StatePara;
		memset(&oDrv_StatePara,0,sizeof(Drv_StatePara));
		oDrv_StatePara.state = nStateCount;

		for(int i=0;i<4;i++)
		{
			if(otmt_StatePara.m_uiVOL[i].Harm[1].fAmp>300)
				otmt_StatePara.m_uiVOL[i].Harm[1].fAmp=300;

			CSttDevice::g_pSttDevice->TranslateACVoltBuffer(otmt_StatePara.m_uiVOL[i].Harm[1].fAmp
					,otmt_StatePara.m_uiVOL[i].Harm[1].fAngle,
					otmt_StatePara.m_uiVOL[i].Harm[1].fFreq,i,Voltanal.dat);

			if(otmt_StatePara.m_uiCUR[i].Harm[1].fAmp>20)
				otmt_StatePara.m_uiCUR[i].Harm[1].fAmp=20;

			CSttDevice::g_pSttDevice->TranslateACCurrentBuffer(otmt_StatePara.m_uiCUR[i].Harm[1].fAmp
					,otmt_StatePara.m_uiCUR[i].Harm[1].fAngle,otmt_StatePara.m_uiCUR[i].Harm[1].fFreq,
					i,Curanal.dat);

			CSttDevice::g_pSttDevice->TranslateACVoltBufferDC(otmt_StatePara.m_uiVOL[i].Harm[1].fAmp,i,Volt.dat);
			CSttDevice::g_pSttDevice->TranslateACCurrentBufferDC(otmt_StatePara.m_uiCUR[i].Harm[1].fAmp,i,Cur.dat);

			fDAValue[0]=qMax(otmt_StatePara.m_uiVOL[i].Harm[1].fAmp,fDAValue[0]);
		}

		for(int i=0;i<18;i++)
		{
			Cur.dat[6+i]=Curanal.dat[i];
			Volt.dat[6+i]=Voltanal.dat[i];
		}
		oDrv_StatePara.dat[1] = Cur;
		oDrv_StatePara.dat[0] = Volt;

		int nBo=0;
		for (int i=0; i<8; i++)//bo
		{
			oDrv_StatePara.BO += ((otmt_StatePara.m_binOut[i].nState)<<i);
		}


		//触发类型	0：手动1：时间2：GPS	3:	开入量
		switch(otmt_StatePara.m_nTriggerCondition)
		{
		case TMT_MDSTATE_TIMETRIGGER:
		{
			oDrv_StatePara.trip = 1;
			structTmTrip	tm;
			tm.mSec = otmt_StatePara.m_fTimeState*1000;
			oDrv_StatePara.tripData.tm = tm;
		}
			break;
		case TMT_MDSTATE_GPSBTRIGGER:
		{
			oDrv_StatePara.trip = 2;
			structGPSTrip 	gps;
			QDate date;
			date.setYMD(otmt_StatePara.m_tGps.nYear,otmt_StatePara.m_tGps.nMonth,otmt_StatePara.m_tGps.nDay);
			QTime time;
			time.setHMS(otmt_StatePara.m_tGps.nHour,otmt_StatePara.m_tGps.nMinutes,otmt_StatePara.m_tGps.nSeconds);
			QDateTime datetime;
			datetime.setDate(date);
			datetime.setTime(time);
			gps.sec =datetime.toTime_t();
			gps.nSec = otmt_StatePara.m_tGps.nMilliSeconds*1000*1000;
			oDrv_StatePara.tripData.gps = gps;
		}
			break;
		case TMT_MDSTATE_BINTRIGGER:
		{
			oDrv_StatePara.trip = 3;
			structBITrip	bi;
			bi.logic= 0;
			if(otmt_StatePara.m_nBinLogic==0)
				bi.logic=1;

			bi.valid=0;

			for(int nIndex = 0;nIndex<MAX_PARACOUNT_BINARY;nIndex++)
			{
				bi.valid += ((otmt_StatePara.m_binIn[nIndex].nSelect)<<nIndex);
			}

			bi.ref = 0;
			oDrv_StatePara.tripData.bi = bi;
			oDrv_StatePara.mdelay = otmt_StatePara.m_fTimeAfterTrigger*1000;
		}
			break;
		case TMT_MDSTATE_MEARSURETRIGGER:
		{
			oDrv_StatePara.trip = 0;
			oDrv_StatePara.mdelay = otmt_StatePara.m_fTimeAfterTrigger*1000;
		}
			break;
		}

		m_oDrvStateParas.state[nStateCount] = oDrv_StatePara;
		nStateCount++;
	}

	m_oDrvStateParas.stateCount = nStateCount;

	CSttDriverOper::setOutPutTap(0x80);

	fDAValue[0] = fDAValue[0]+fDAValue[0]*0.1;
	if(fDAValue[0] > 300.0)
		fDAValue[0] = 300.0;

	fDAValue[1] =CSttDevice::g_pSttDevice->getCurrentDa();
	CSttDevice::g_pSttDevice->SetDeviceInnerParaSet(fDAValue);

	CSttDriverOper::setStatePara((char*)&m_oDrvStateParas,12+sizeof(Drv_StatePara)*m_oDrvStateParas.stateCount);
#endif
}
