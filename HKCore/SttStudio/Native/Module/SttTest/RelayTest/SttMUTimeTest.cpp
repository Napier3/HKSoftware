#include "SttMUTimeTest.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "../../RecordTest/SttRcdSendSocket.h"
#include "../../SttDevice/RelayTest/SttDriverOper.h"


CString CSttMUTimeTest::m_strMacroName = "合并单元守时对时测试";
CString CSttMUTimeTest::m_strMacroID = ("SttMUTimeTest");
CString CSttMUTimeTest::m_strFilePostFix = "stttst";
CString CSttMUTimeTest::m_strMacroVer ="1.0";

CSttMUTimeTest::CSttMUTimeTest()
{
	m_pParas=new CSttParas;
	m_pParas->m_strID=m_strMacroID;
	m_pszBuff=stt_test_get_global_buff();
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
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
	stt_xml_serialize(&m_oRecordPara,pXmlSerialize);
}

void CSttMUTimeTest::StartTest()
{
#ifdef OS_QT_LINUX
	TtmToDrv();
#endif
}

void CSttMUTimeTest::Stop()
{
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
	if(m_oRecordPara.m_mode==0)
		CSttDriverOper::StopIecDetect();
}

CSttParas *CSttMUTimeTest::GetCurrParas()
{
	return m_pParas;
}

void CSttMUTimeTest::EventProcess()
{
	int ret=CSttDriverOper::readIecDetectResult(m_pszBuff);
	if(ret<=0)
		return;

	int nPacketLen=0;
	for(int i=0;i<ret;)
	{
		if(m_pszBuff[i]==0x05&&m_pszBuff[i+1]==0x64&&m_pszBuff[i+2]==0x05&&m_pszBuff[i+3]==0x64)
		{
			nPacketLen+=m_pszBuff[i+4]<<24;
			nPacketLen+=m_pszBuff[i+5]<<16;
			nPacketLen+=m_pszBuff[i+6]<<8;
			nPacketLen+=m_pszBuff[i+7];
			nPacketLen=nPacketLen*4;

			CDvmData *pData = m_pParas->AddNewData("",0);
			pData->AddValue("APPID",QString("%1").arg(m_pszBuff[i+18],2,16,QChar('0'))+QString("%1").arg(m_pszBuff[i+19],2,16,QChar('0')));
			pData->AddValue("DestMac","");
			pData->AddValue("Fiber",QString::number(m_pszBuff[i+17]&0x0f));

			int n=(m_pszBuff[i+17]>>4)&0x0f;
			if(n==1)
			{
				pData->AddValue("IecType",CString("1"));
				if(m_pszBuff[i+24]==0x80)
				{
					int nSVIDLen=m_pszBuff[i+25];
					pData->AddValue("SVID",QString::fromAscii(&m_pszBuff[i+26],nSVIDLen));
				}
			}
			else if(n==2)
			{
				pData->AddValue("IecType",CString("2"));
				int nGcDatasetLen=0;
				if(m_pszBuff[i+24]==0x82)
				{
					nGcDatasetLen=m_pszBuff[i+25];
					pData->AddValue("GcDataset",QString::fromAscii(&m_pszBuff[i+26],nGcDatasetLen));
					nGcDatasetLen+=2;
				}
				if(m_pszBuff[i+24+nGcDatasetLen]==0x83)
				{
					int nGcIDLen=m_pszBuff[i+25+nGcDatasetLen];
					pData->AddValue("GcID",QString::fromAscii(&m_pszBuff[i+26+nGcDatasetLen],nGcIDLen));
				}
			}

			i=i+nPacketLen+4;
		}
	}

}

void CSttMUTimeTest::TtmToDrv()
{
	if(m_oRecordPara.m_mode==1)
	{
		tmt_to_drv(this,&m_oDrvGooseSubData);
		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Record,(char*)&m_oDrvGooseSubData , sizeof(m_oDrvGooseSubData));
	}
	else
	{		
		memset(&m_oDrvGooseSubData,0,sizeof(GooseSubData));
		m_oDrvGooseSubData.nPort=0;
		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Record,(char*)&m_oDrvGooseSubData , sizeof(m_oDrvGooseSubData));
		CSttDriverOper::StartIecDetect();
	}
}
