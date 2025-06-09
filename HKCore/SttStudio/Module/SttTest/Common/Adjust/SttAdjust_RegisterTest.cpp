#include "stdafx.h"
#include"SttAdjust_RegisterTest.h"
#include "../../../SttDevice/SttDeviceBase.h"

CString CSttAdjust_RegisterTest::m_strMacroName = "FPGA¼Ä´æÆ÷²âÊÔ";
CString CSttAdjust_RegisterTest::m_strMacroID = STT_MACRO_ID_RegisterTest;
CString CSttAdjust_RegisterTest::m_strFilePostFix = "stthrt";
CString CSttAdjust_RegisterTest::m_strMacroVer ="1.0";

CSttAdjust_RegisterTest::CSttAdjust_RegisterTest() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttAdjust_RegisterTest::Init()
{
	TMT_ADJ_REGISTER_OUTPUT::init();
}

CSttAdjust_RegisterTest::~CSttAdjust_RegisterTest(void)
{

}

void CSttAdjust_RegisterTest::StartTest()
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttAdjust_RegisterTest::StartTest >>>>>>");
}

void CSttAdjust_RegisterTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(this,pXmlSerialize);
	unsigned int nRegAddr=0;
	unsigned int nRegValue=0;

#ifdef _PSX_QT_LINUX_
	CString str = m_nRegAddr;
	BOOL bOk;
	nRegAddr = str.toUInt(&bOk,16);
	str = m_nRegValue;
	nRegValue = str.toUInt(&bOk,16);
	
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	CSttDeviceBase::g_pSttDeviceBase->SetRegisterValue(nRegAddr,nRegValue);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
}


