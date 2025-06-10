#include "Stt_GSEtoBin_Test.h"
#include "../../Engine/SttServerTestCtrlCntr.h"



CString CSttGSEtoBinTest::m_strMacroName = "智能终端GOOSE转开入";
CString CSttGSEtoBinTest::m_strMacroID = ("SttGSEtoBinTest");
CString CSttGSEtoBinTest::m_strFilePostFix = "stttst";
CString CSttGSEtoBinTest::m_strMacroVer ="1.0";

CSttGSEtoBinTest::CSttGSEtoBinTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	SetRecvStopCmd(FALSE);
	m_dTestStartTime=0;
}

CSttGSEtoBinTest::~CSttGSEtoBinTest()
{

}

void CSttGSEtoBinTest::Init()
{
	CSttTestBase::Init();
}

void CSttGSEtoBinTest::AfterSetParameter()
{

}

void CSttGSEtoBinTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	m_oIEDParas.init();
	stt_xml_serialize(&m_oIEDParas,pXmlSerialize);
}

void CSttGSEtoBinTest::StartTest()
{
	TtmToDrv();

	if(!GetTestStarting())
	{
		for(int nIndex=0;nIndex<256;nIndex++)
		{
			m_oPreTmtIEDPara.m_binOut[nIndex].nState=m_oIEDParas.m_otmt_IEDPara[0].m_binOut[nIndex].nState;
		}
		SetTestStarting(TRUE);

#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->SetIEDTestStart_G2B();
#endif
	}

}

void CSttGSEtoBinTest::Stop()
{
	SetTestStarting(FALSE);

	if(m_oIEDParas.m_nTestType==SOEMode)
	{
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->SetIEDTestStop_G2B();
#endif
	}

	if(m_oIEDParas.m_nTestType==DelayMode)
	{
		for(int i=0;i<48;i++)
		{
			m_oIEDParas.m_otmt_IEDPara[0].m_binOut[i+8].init();
		}

		TtmToDrv();
	}
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
#endif
}

void CSttGSEtoBinTest::EventProcess()
{
	if(!GetTestStarting())
		return;

	if(m_oIEDParas.m_nTestType==RepeatMode)
		return;

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProIEDTestDrvResult_G2B(this,&m_oPreTmtIEDPara);
#endif
}

void CSttGSEtoBinTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_iedtest_G2B(this);
#endif
}
