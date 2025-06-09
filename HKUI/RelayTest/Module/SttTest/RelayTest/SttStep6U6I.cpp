#include "SttStep6U6I.h"
#include "IEC61850CfgMngr.h"
#include "../../SttDevice/RelayTest/SttDriverOper.h"

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
	m_Start=FALSE;
	m_pCSttRecord=new CSttRecord;
}

CSttStep6U6I::~CSttStep6U6I()
{
	delete m_pCSttRecord;
	m_pCSttRecord=NULL;
}

void CSttStep6U6I::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	memset(&m_oHarmParas, 0, sizeof(tmt_HarmParas));
	stt_xml_serialize(&m_oHarmParas,pXmlSerialize);
}

void CSttStep6U6I::StartTest()
{
#ifdef _PSX_QT_LINUX_
	TtmToDrv();
#endif
	if(!m_Start)
	{
		CSttDriverOper::setPollingsyncsecond(1);
		CSttDriverOper::startDMA();
		CSttDriverOper::IoCtrl(0x100,1);
		Sleep(50);
		CSttDeviceBase::g_pSttDeviceBase->SetRecordStart();
		CSttDriverOper::Start(1);
		m_Start=TRUE;
	}
}

void CSttStep6U6I::Stop()
{
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
	CSttDriverOper::StopRecord();
	CSttDriverOper::IoCtrl(0x100,0);
	CSttDriverOper::setPollingsyncsecond(0);
	m_Start=FALSE;
}


void CSttStep6U6I::EventProcess()
{
	m_pCSttRecord->EventProcess();
}

void CSttStep6U6I::TtmToDrv()
{
	if(!m_Start)
	{		
		structModuleParam modulepara;
		memset(&modulepara,0,sizeof(structModuleParam));
		modulepara.nAlgCnt = 2;
		modulepara.nAlgTable[0]=VOL_CHANNEL_MARK;
		modulepara.nAlgTable[1]=CUR_CHANNEL_MARK;

		modulepara.nbIntCnt = 1;
		modulepara.nbITable[0] = 0x8000;
		modulepara.nBoCnt = 1;
		modulepara.nBoTable[0] = 0x8000;
		CSttDriverOper::SetModuleInfo((char*)&modulepara,sizeof(structModuleParam));
	}

	tmt_to_drv(this,&m_oManuData);

	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(ManualTest,(char*)&m_oManuData,\
												  sizeof(structManuData));
}
