#include "SttIecDetectTest.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "../../RecordTest/SttRcdSendSocket.h"
#include "../../SttDevice/RelayTest/SttDriverOper.h"
#include "../../Engine/SttServerTestCtrlCntr.h"


CString CSttIecDetectTest::m_strMacroName = "Êý×Ö±¨ÎÄÌ½²â²âÊÔ";
CString CSttIecDetectTest::m_strMacroID = ("SttIecDetectTest");
CString CSttIecDetectTest::m_strFilePostFix = "stttst";
CString CSttIecDetectTest::m_strMacroVer ="1.0";

CSttIecDetectTest::CSttIecDetectTest()
{
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
#ifdef _PSX_QT_LINUX_
	TtmToDrv();
#endif
}

void CSttIecDetectTest::Stop()
{
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
	if(m_oRecordPara.m_mode==0)
		CSttDriverOper::StopIecDetect();
}

void CSttIecDetectTest::EventProcess()
{
	int ret=CSttDriverOper::readIecDetectResult(m_pszBuff);
	if(ret<24)
		return;
	//05640564 00000005 5f0c8d8e 2e27cd3c aa12 4009 00f7 340e
//	QString str;
//	for(int i=0;i<ret;i++)
//	{
//		str+=QString("%1").arg(m_pszBuff[i],2,16,QChar('0'));
//	}
//	qDebug()<<"str"<<str;

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

			if(nPacketLen!=20)
			{
				i=i+nPacketLen+4;
				continue;
			}
			CSttParas *pParas=CSttServerTestCtrlCntr::GetCurrParas();
			CDvmData *pData = pParas->AddNewData("",0);
			pData->AddValue("AppID",QString("0x")+QString("%1").arg(m_pszBuff[i+18],2,16,QChar('0'))+QString("%1").arg(m_pszBuff[i+19],2,16,QChar('0')));
			pData->AddValue("FiberIndex",QString::number(m_pszBuff[i+17]&0x0f));
			int nCRC=0;
			nCRC+=m_pszBuff[i+22]<<8;
			nCRC+=m_pszBuff[i+23];
			pData->AddValue("CRC",QString::number(nCRC));
			qDebug()<<QString::number(nCRC);

			int n=(m_pszBuff[i+17]>>4)&0x0f;
			if(n==1)
			{
				pData->AddValue("IecType",CString("9-2"));
			}
			else if(n==2)
			{
				pData->AddValue("IecType",CString("GOOSE"));
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
		memset(&m_oDrvGooseSubData,0,sizeof(GooseSubData));
		m_oDrvGooseSubData.ncount=1;
		m_oDrvGooseSubData.nPort=4;
		m_oDrvGooseSubData.gooseSub[0].CRC=m_oRecordPara.m_crc;
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
