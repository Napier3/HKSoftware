#include "Stt_BotoGSE_Test.h"
#include "../../Engine/SttServerTestCtrlCntr.h"


CString CSttBOtoGSETest::m_strMacroName = "智能终端开出转GOOSE";
CString CSttBOtoGSETest::m_strMacroID = ("SttBOtoGSETest");
CString CSttBOtoGSETest::m_strFilePostFix = "stttst";
CString CSttBOtoGSETest::m_strMacroVer ="1.0";

CSttBOtoGSETest::CSttBOtoGSETest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	SetRecvStopCmd(FALSE);
	m_dTestStartTime=0;
	m_pCSttRecord=new CSttRecord;
}

CSttBOtoGSETest::~CSttBOtoGSETest()
{
	delete m_pCSttRecord;
	m_pCSttRecord=NULL;
}


void CSttBOtoGSETest::AfterSetParameter()
{

}

void CSttBOtoGSETest::Init()
{
	tmt_IEDTest::init();
//	m_oSwitchPara.nModule=8;
//	m_oSwitchPara.nBOCnt=48;
}

void CSttBOtoGSETest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oIEDParas,pXmlSerialize);
}

void CSttBOtoGSETest::StartTest()
{
#ifdef _PSX_QT_LINUX_
	TtmToDrv();

	if(!GetTestStarting())
	{
		memcpy(&m_oPreTmtIEDPara,&m_oIEDParas.m_otmt_IEDPara[0],sizeof(tmt_IEDPara));
		SetTestStarting(TRUE);

		CSttDeviceBase::g_pSttDeviceBase->SetIEDTestStart_B2G();
	}
#endif
}

void CSttBOtoGSETest::Stop()
{		
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetIEDTestStop_B2G();
#endif
	SetTestStarting(FALSE);
}

void CSttBOtoGSETest::EventProcess()
{
	if(!GetTestStarting())
		return;

	if(m_oIEDParas.m_nTestType==RepeatMode)
		return;

	if(m_oIEDParas.m_nTestType==DelayMode)
	{
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->ProIEDTestDrvResult_B2G(this,&m_oPreTmtIEDPara);
#endif
	}
	m_pCSttRecord->EventProcess();
}

void CSttBOtoGSETest::TtmToDrv()
{	
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_iedtest_B2G(this);
#endif
}
