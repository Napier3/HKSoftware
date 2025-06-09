#include "SttIecDetectTest.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "../../RecordTest/SttRcdSendSocket.h"
#include "../../SttDevice/RelayTest/SttDriverOper.h"


CString CSttIecDetectTest::m_strMacroName = "Êý×Ö±¨ÎÄÌ½²â²âÊÔ";
CString CSttIecDetectTest::m_strMacroID = ("SttIecDetectTest");
CString CSttIecDetectTest::m_strFilePostFix = "stttst";
CString CSttIecDetectTest::m_strMacroVer ="1.0";

CSttIecDetectTest::CSttIecDetectTest()
{
	m_pParas=new CSttParas;
	m_pParas->m_strID=m_strMacroID;
	m_pszBuff=stt_test_get_global_buff();
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

CSttIecDetectTest::~CSttIecDetectTest()
{
	m_pszBuff = NULL;
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
#ifdef OS_QT_LINUX
	TtmToDrv();
#endif
}

void CSttIecDetectTest::Stop()
{
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
	if(m_oRecordPara.m_mode==0)
		CSttDriverOper::StopIecDetect();
}

CSttParas *CSttIecDetectTest::GetCurrParas()
{
	return m_pParas;
}

void CSttIecDetectTest::EventProcess()
{
	int ret=CSttDriverOper::readIecDetectResult(m_pszBuff);
	if(ret<43)
		return;

	QString str;
	for(int i=0;i<ret;i++)
	{
		str+=QString("%1").arg(m_pszBuff[i],2,16,QChar('0'));
	}
	qDebug()<<"str"<<str;

	int nPacketLen=0;
	for(int i=0;i<ret;)
	{
		if(m_pszBuff[i]==0x05&&m_pszBuff[i+1]==0x64&&m_pszBuff[i+2]==0x05&&m_pszBuff[i+3]==0x64)
		{
			nPacketLen=0;
			nPacketLen+=m_pszBuff[i+4]<<24;
			nPacketLen+=m_pszBuff[i+5]<<16;
			nPacketLen+=m_pszBuff[i+6]<<8;
			nPacketLen+=m_pszBuff[i+7];
			nPacketLen=nPacketLen*4;

			CDvmData *pData = m_pParas->AddNewData("",0);
			pData->AddValue("AppID",QString("0x")+QString("%1").arg(m_pszBuff[i+18],2,16,QChar('0'))+QString("%1").arg(m_pszBuff[i+19],2,16,QChar('0')));
			QString mac;
			for(int index=0;index<6;index++)
			{
				mac+=QString("%1").arg(m_pszBuff[i+28+index],2,16,QChar('0'));
				mac+="-";
			}
			pData->AddValue("DestMac",mac.toUpper().left(mac.length()-1));
			pData->AddValue("FiberIndex",QString::number(m_pszBuff[i+17]&0x0f));

			int n=(m_pszBuff[i+17]>>4)&0x0f;
			if(n==1)
			{
				pData->AddValue("IecType",CString("9-2"));
				if(m_pszBuff[i+40]==0x80)
				{
					int nSVIDLen=m_pszBuff[i+41];
					pData->AddValue("SVID",QString::fromAscii(&m_pszBuff[i+42],nSVIDLen));
				}
			}
			else if(n==2)
			{
				pData->AddValue("IecType",CString("GOOSE"));
				int nGcDatasetLen=0;
				if(m_pszBuff[i+40]==0x82)
				{
					nGcDatasetLen=m_pszBuff[i+41];
					pData->AddValue("GcDataset",QString::fromAscii(&m_pszBuff[i+42],nGcDatasetLen));
					nGcDatasetLen+=2;
				}
				if((i+40+nGcDatasetLen)>(ret-1))
					return;

				if(m_pszBuff[i+40+nGcDatasetLen]==0x83)
				{
					int nGcIDLen=m_pszBuff[i+41+nGcDatasetLen];
					pData->AddValue("GcID",QString::fromAscii(&m_pszBuff[i+42+nGcDatasetLen],nGcIDLen));
				}
			}

			i=i+nPacketLen+4;
		}
		else
			i++;
	}

}

void CSttIecDetectTest::TtmToDrv()
{
	if(m_oRecordPara.m_mode==1)
	{
		tmt_to_drv(this,&m_oDrvGooseSubData);
		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Record,(char*)&m_oDrvGooseSubData , sizeof(m_oDrvGooseSubData));
	}
	else
	{
		CSttDriverOper::StopIecDetect();
		memset(&m_oDrvGooseSubData,0,sizeof(GooseSubData));
		m_oDrvGooseSubData.nPort=0;
		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Record,(char*)&m_oDrvGooseSubData , sizeof(m_oDrvGooseSubData));
		CSttDriverOper::StartIecDetect();
	}
}
