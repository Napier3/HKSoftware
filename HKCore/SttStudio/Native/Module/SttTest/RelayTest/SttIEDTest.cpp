#include "SttIEDTest.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "../../SttDevice/RelayTest/SttDriverOper.h"
#include "IEC61850CfgMngr.h"


CString CSttIEDTest::m_strMacroName = "÷«ƒ‹÷’∂À≤‚ ‘";
CString CSttIEDTest::m_strMacroID = ("SttIecTest");
CString CSttIEDTest::m_strFilePostFix = "stttst";
CString CSttIEDTest::m_strMacroVer ="1.0";

CSttIEDTest::CSttIEDTest()
{
	m_pszBuff=stt_test_get_global_buff();
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

CSttIEDTest::~CSttIEDTest()
{
	m_pszBuff = NULL;
}


void CSttIEDTest::AfterSetParameter()
{

}

void CSttIEDTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oIEDParas,pXmlSerialize);
}

void CSttIEDTest::StartTest()
{
#ifdef OS_QT_LINUX
	TtmToDrv();
#endif
}

void CSttIEDTest::Stop()
{

}


void CSttIEDTest::EventProcess()
{
	if(m_oIEDParas.m_nTestType==2)
		return;


}

void CSttIEDTest::TtmToDrv()
{
	if(m_oIEDParas.m_nDataMode==0)//gse2bin
	{

	}
	else if(m_oIEDParas.m_nDataMode==1)//bin2gse
	{

	}
}
