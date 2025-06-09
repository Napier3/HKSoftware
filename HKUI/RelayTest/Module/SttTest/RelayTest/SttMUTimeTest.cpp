#include "SttMUTimeTest.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "../../RecordTest/SttRcdSendSocket.h"
#include "../../SttDevice/RelayTest/SttDriverOper.h"
#include "../../Engine/SttServerTestCtrlCntr.h"


CString CSttMUTimeTest::m_strMacroName = "合并单元守时对时测试";
CString CSttMUTimeTest::m_strMacroID = ("SttMUTimeTest");
CString CSttMUTimeTest::m_strFilePostFix = "stttst";
CString CSttMUTimeTest::m_strMacroVer ="1.0";

CSttMUTimeTest::CSttMUTimeTest()
{
	m_pszBuff=stt_test_get_global_buff();
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_pMUThread=new MUThread;
}

CSttMUTimeTest::~CSttMUTimeTest()
{
	m_pszBuff = NULL;
}


void CSttMUTimeTest::AfterSetParameter()
{

}

void CSttMUTimeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	m_oMUTIMEPara.init();
	stt_xml_serialize(&m_oMUTIMEPara,pXmlSerialize);
}

void CSttMUTimeTest::StartTest()
{	
#ifdef _PSX_QT_LINUX_
	if(!m_pMUThread->getRun())
	{
		TtmToDrv();
		CSttParas *pParas=CSttServerTestCtrlCntr::GetCurrParas();
		pParas->DeleteAll();
		m_pMUThread->start();
	}
#endif
}

void CSttMUTimeTest::Stop()
{
	CSttParas *pParas=CSttServerTestCtrlCntr::GetCurrParas();
	pParas->DeleteAll();
	CSttDriverOper::Stop();
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
	CSttDriverOper::setRising(m_oMUTIMEPara.m_nRising);
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
	CSttParas *pParas=CSttServerTestCtrlCntr::GetCurrParas();
	pParas->AddNewData("TestStart",0);

	CSttDriverOper::IoCtrl(0x503,0);
	int nCount =0;
	CString strID;
	while(nCount< m_nCount&&m_bRun)
	{
		int ret=CSttDriverOper::IoCtrl(0x503,0);
		strID.Format("PPSTime%03d",nCount+1);
		pParas->AddNewData(strID.GetString(),QString::number(ret));

		nCount++;
		msleep(1000);
	}
	pParas->AddNewData("TestStop",0);
	m_bRun=FALSE;
}
