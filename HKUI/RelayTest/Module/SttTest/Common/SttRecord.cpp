#include "SttRecord.h"
#include "../../RecordTest/SttRcdSendSocket.h"


CString CSttRecord::m_strMacroName = "数字报文采集测试";
CString CSttRecord::m_strMacroID = ("SttRecord");
CString CSttRecord::m_strFilePostFix = "stttst";
CString CSttRecord::m_strMacroVer ="1.0";

CSttRecord::CSttRecord()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

CSttRecord::~CSttRecord()
{

}

void CSttRecord::Init()
{
	CSttTestBase::Init();
	m_oRecordPara.m_nSubNumber=0;
}

void CSttRecord::AfterSetParameter()
{

}

void CSttRecord::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oRecordPara,pXmlSerialize);
}

void CSttRecord::StartTest()
{
#ifdef _PSX_QT_LINUX_
	TtmToDrv();
//	CSttDeviceBase::g_pSttDeviceBase->SetRecordStart();
#endif
}

void CSttRecord::Stop()
{
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
//	CSttDeviceBase::g_pSttDeviceBase->SetRecordStop();
}

BOOL CSttRecord::EventProcess()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProRecordDrvResult();
#endif
	return FALSE;
}

long CSttRecord::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	g_oSttRcdSendSocket.CheckRcdInfo();
}

void CSttRecord::TtmToDrv()
{
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_record(this);
}
