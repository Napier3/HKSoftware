#include "SttMUTimeTest.h"
#include "../../RecordTest/SttRcdSendSocket.h"
#include "../../Engine/SttServerTestCtrlCntr.h"


CString CSttMUTimeTest::m_strMacroName = "合并单元守时对时测试";
CString CSttMUTimeTest::m_strMacroID = ("SttMUTimeTest");
CString CSttMUTimeTest::m_strFilePostFix = "stttst";
CString CSttMUTimeTest::m_strMacroVer ="1.0";

CSttMUTimeTest::CSttMUTimeTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_pMUThread=new MUThread;
}

CSttMUTimeTest::~CSttMUTimeTest()
{

}


void CSttMUTimeTest::AfterSetParameter()
{

}

void CSttMUTimeTest::Init()
{
	tmt_MUTIMETest::init();
}

void CSttMUTimeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oMUTIMEPara,pXmlSerialize);
}

void CSttMUTimeTest::StartTest()
{	
#ifdef _PSX_QT_LINUX_
	if(!m_pMUThread->getRun())
	{
		TtmToDrv();
		m_pMUThread->start();
	}
#endif
}

void CSttMUTimeTest::Stop()
{	
	CSttTestBase::Stop();
	if(m_pMUThread->getRun())
	{
		m_pMUThread->setRun(FALSE);
		Sleep(1100);
	}
}

void CSttMUTimeTest::TtmToDrv()
{
	/***
	switch(m_oMUTIMEPara.m_nLogic)
	{
	case 1:
	{

	}
		break;
	case 0:
	default:
	{

	}
		break;
	}
	***/
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetRising(m_oMUTIMEPara.m_nRising);
#endif

	m_pMUThread->setCount(m_oMUTIMEPara.m_nSec);
	m_pMUThread->setRun(TRUE);
}

MUThread::MUThread()
{
	m_nCount=0;
	m_bRun=FALSE;
}

MUThread::~MUThread()
{

}

void MUThread::run()
{
	ReturnTestStateEvent_TestStart(0, 0, TRUE);
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->GetPPS();
	int nCount =0;

	while(nCount< m_nCount&&m_bRun)
	{
		int ret=CSttDeviceBase::g_pSttDeviceBase->GetPPS();
		STT_TEST_EVENT bufEvent;
		bufEvent.oTime.dTime=0;
		bufEvent.oTime.dRealTime=0;
		bufEvent.oEventInfo[0].nType=SttResult_Type_PPSTime;
		bufEvent.oEventInfo[0].nStateIndex=nCount+1;
		bufEvent.oEventInfo[0].nStepIndex=-1;
		bufEvent.oEventInfo[0].nChannel=0;
		bufEvent.oEventInfo[0].nValue=ret;
		bufEvent.nEventInfoCnt=1;
		stt_add_test_event(bufEvent);
//		stt_add_test_event(Result_Type_PPSTime, nCount+1, -1, 0, ret, 0, 0);
		ReturnRealTimeEvent();
		nCount++;
		msleep(1000);
	}
#endif
	ReturnTestStateEvent_TestFinish(0, 0, TRUE);
	m_bRun=FALSE;
}
