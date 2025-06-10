#include "SttRecord.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "../../RecordTest/SttRcdSendSocket.h"


CString CSttRecord::m_strMacroName = "数字报文采集测试";
CString CSttRecord::m_strMacroID = ("SttRecord");
CString CSttRecord::m_strFilePostFix = "stttst";
CString CSttRecord::m_strMacroVer ="1.0";

CSttRecord::CSttRecord()
{
	m_pszBuff=stt_test_get_global_buff();
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

CSttRecord::~CSttRecord()
{
	m_pszBuff = NULL;
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
#ifdef _PSX_IDE_QT_
	TtmToDrv();
	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Record,(char*)&m_oDrvGooseSubData , sizeof(m_oDrvGooseSubData));
	CSttDeviceBase::g_pSttDeviceBase->SetRecordStart();
#endif
}

void CSttRecord::Stop()
{
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
	CSttDeviceBase::g_pSttDeviceBase->SetRecordStop();	
}

void CSttRecord::EventProcess()
{
	int ret=CSttDeviceBase::g_pSttDeviceBase->GetTestResult(RecordResult,m_pszBuff);

	if(ret>0)
	{
		g_oSttRcdSendSocket.WriteRecordBuf(m_pszBuff,ret);
	}
}

long CSttRecord::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	g_oSttRcdSendSocket.CheckRcdInfo();
}

void CSttRecord::TtmToDrv()
{
#ifdef _PSX_IDE_QT_
	tmt_to_drv(this,&m_oDrvGooseSubData);
#endif
}
