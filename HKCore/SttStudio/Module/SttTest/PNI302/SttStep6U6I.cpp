#include "SttStep6U6I.h"


CString CSttStep6U6I::m_strMacroName = "合并单元精确度测试";
CString CSttStep6U6I::m_strMacroID = ("SttStep6U6I");
CString CSttStep6U6I::m_strFilePostFix = "stttst";
CString CSttStep6U6I::m_strMacroVer ="1.0";

CSttStep6U6I::CSttStep6U6I()
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

CSttStep6U6I::~CSttStep6U6I()
{
	delete m_pCSttRecord;
	m_pCSttRecord=NULL;
}

void CSttStep6U6I::Init()
{
	tmt_harm_test::init();
	CSttTestBase::Init();
}

void CSttStep6U6I::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oHarmParas,pXmlSerialize);
}

void CSttStep6U6I::StartTest()
{	
	TtmToDrv();
	if(!GetTestStarting())
	{
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->SetStep6U6IStart();
#endif
		SetTestStarting(TRUE);
	}
}

void CSttStep6U6I::Stop()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetStep6U6IStop();
#endif
	SetTestStarting(FALSE);
}

void CSttStep6U6I::EventProcess()
{
	m_pCSttRecord->EventProcess();
}

void CSttStep6U6I::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_harm(this);
#endif
}
