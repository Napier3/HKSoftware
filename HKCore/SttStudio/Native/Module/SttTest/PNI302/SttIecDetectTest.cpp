#include "SttIecDetectTest.h"
#include "../../RecordTest/SttRcdSendSocket.h"
#include "../../Engine/SttServerTestCtrlCntr.h"


CString CSttIecDetectTest::m_strMacroName = "Êý×Ö±¨ÎÄÌ½²â²âÊÔ";
CString CSttIecDetectTest::m_strMacroID = ("SttIecDetectTest");
CString CSttIecDetectTest::m_strFilePostFix = "stttst";
CString CSttIecDetectTest::m_strMacroVer ="1.0";

CSttIecDetectTest::CSttIecDetectTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

CSttIecDetectTest::~CSttIecDetectTest()
{

}

void CSttIecDetectTest::Init()
{
	tmt_RecordTest::init(0);
}

void CSttIecDetectTest::AfterSetParameter()
{

}

void CSttIecDetectTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oRecordPara,pXmlSerialize);
}

void CSttIecDetectTest::StartTest()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetIecdetectStart(this);
#endif
}

void CSttIecDetectTest::Stop()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetIecdetectStop(this);
#endif
}

void CSttIecDetectTest::EventProcess()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProIecdetectDrvResult();
#endif
}

