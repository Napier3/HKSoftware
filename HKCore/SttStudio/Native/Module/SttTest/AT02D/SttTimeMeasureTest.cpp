#include "SttTimeMeasureTest.h"
#include "../../SttDevice/AT02D/SttDeviceAT02D.h"

CString CSttTimeMeasureTest::m_strMacroName = "Ê±¼ä²âÁ¿²âÊÔ";
CString CSttTimeMeasureTest::m_strMacroID = ("SttTimeMeasureTest");
CString CSttTimeMeasureTest::m_strFilePostFix = "stttst";
CString CSttTimeMeasureTest::m_strMacroVer ="1.0";

CSttTimeMeasureTest::CSttTimeMeasureTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	Init();
}

CSttTimeMeasureTest::~CSttTimeMeasureTest()
{
	if(GetTestStarting())
	{
		Stop();
	}
}

void CSttTimeMeasureTest::Init()
{
	m_oTimeMeasureParas.init();
	CSttTestBase::Init();
	m_nCurStateIndex = 0;
}

void CSttTimeMeasureTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oTimeMeasureParas,pXmlSerialize);
}

void CSttTimeMeasureTest::StartTest()
{	
	if(GetTestStarting())
	{
		Stop();
		Sleep(100);
	}

	CSttTestBase::StartTest();

		TtmToDrv();
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
		SetTestStarting(TRUE);
		CSttDeviceBase::g_pSttDeviceBase->SetTestStart(BinaryStateTest);

	CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttTimeMeasureTest::StartTest >>>>>>");
}

BOOL CSttTimeMeasureTest::EventProcess()
{
	if(!GetTestStarting())
		return FALSE;

	BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProStateDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
	return bTestFinished;
}

void CSttTimeMeasureTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->m_nCurStateCount = m_oTimeMeasureParas.m_nStateCount;
	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	char *pBuf = stt_test_get_drvparas_buff();
	Drv_StatePara para;
	memset(&para,0,sizeof(Drv_StatePara));
	para.nStateCount = m_oTimeMeasureParas.m_nStateCount;
	para.nIsLoop = 0;
	para.nbiRefFirst = 0;

	Drv_BIStatus gooseInit;
	memset(&gooseInit,0,sizeof(Drv_BIStatus));
	para.oGooseInit = gooseInit;

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nFd,0x301,0);
	write(nFd,(char*)&para,sizeof(Drv_StatePara));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	int nSize = sizeof(Drv_StateItem)*para.nStateCount;

	for(int i=0;i<para.nStateCount;i++)
	{
		Drv_StateItem state;
		memset(&state,0,sizeof(Drv_StateItem));
		if(m_oTimeMeasureParas.m_oTimeMeasurePara[i].m_nTrigType == TMT_MDSTATE_GPSBTRIGGER)
		{
			state.nTirpType = State_Trig_GPS;
			int nSecSet = m_oTimeMeasureParas.m_oTimeMeasurePara[i].m_nOutputTime*0.001;
			state.oTm.oGps.nNsec=0;			

			CString strDate;
			short nYear, nMon, nDay, nHour, nMin, nSec;
			unsigned int ntime_t = g_theSttDeviceStatus->m_nUser_s+nSecSet;
			TransTimer_t(ntime_t, nYear, nMon, nDay, nHour, nMin, nSec);
			ntime_t -= g_theSttDeviceStatus->m_nTimeZone * 3600;
			state.oTm.oGps.nSec = ntime_t;

			strDate.Format("GPSTrip %04d-%02d-%02d %02d:%02d:%02d[Zone %d]",
						   nYear, nMon, nDay, nHour, nMin, nSec,g_theSttDeviceStatus->m_nTimeZone);
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("%s"),strDate.GetString());
		}
		else
		{
			state.nTirpType = State_Trig_TimeDelay;
			state.oTm.oTime.nMsec =m_oTimeMeasureParas.m_oTimeMeasurePara[i].m_nOutputTime;
		}

		for (int nIndex = 0;nIndex < 16;nIndex++)
		{
			int	nState = m_oTimeMeasureParas.m_oTimeMeasurePara[i].m_binOut[nIndex].nState;
			state.oStBo.boValue.item[0].nVal1 += ((!nState)*(1<<nIndex));
		}		

		memcpy(pBuf+sizeof(Drv_StateItem)*i,&state,sizeof(Drv_StateItem));
	}

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nFd,0x301,1);
	write(nFd,pBuf,nSize);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
}
