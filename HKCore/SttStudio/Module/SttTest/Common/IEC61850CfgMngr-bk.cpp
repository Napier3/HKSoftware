#include "IEC61850CfgMngr.h"
#include "OSInterface.h"
#include "../../SttDevice/SttDeviceBase.h"
#include "../../SttDevice/SttDriverOper.h"

CIEC61850CfgMngr *CIEC61850CfgMngr::g_pIEC61850CfgMngr=NULL;
long CIEC61850CfgMngr::g_nIEC61850CfgMngrRef = 0;

CIEC61850CfgMngr::CIEC61850CfgMngr(QObject *parent) : QObject(parent)
{
	confsv=(SendConfSV*)malloc(sizeof(SendConfSV));
	fiber=(FiberConf*)malloc(sizeof(FiberConf));
	confgse=(SendConfGSE*)malloc(sizeof(SendConfGSE));
	m_pIECConfig=(StructIECConfig*)malloc(sizeof(StructIECConfig));
	ft3sub=(Ft3SubData*)malloc(sizeof(Ft3SubData));
	gsesub=(GooseSubData*)malloc(sizeof(GooseSubData));
	stMaps=(structGSOutMap*)malloc(sizeof(structGSOutMap));
	stGseTest=(StructGSTest*)malloc(sizeof(StructGSTest));
	goosechange=(GooseChangedItems*)malloc(sizeof(GooseChangedItems));
	m_pIECFiberInfo=new IECFiberInfo;
	InitBoMap();
}

CIEC61850CfgMngr::~CIEC61850CfgMngr()
{
	free(confsv);
	free(fiber);
	free(confgse);
	free(m_pIECConfig);
	free(ft3sub);
	free(gsesub);
	free(stMaps);
	free(stGseTest);
	free(goosechange);
	delete m_pIECFiberInfo;
	m_pIECFiberInfo=NULL;
}

void CIEC61850CfgMngr::Create()
{
	g_nIEC61850CfgMngrRef++;

	if (g_nIEC61850CfgMngrRef == 1)
	{
		g_pIEC61850CfgMngr=new CIEC61850CfgMngr;
		g_pIEC61850CfgMngr->Init();
	}
}

void CIEC61850CfgMngr::Release()
{
	g_nIEC61850CfgMngrRef--;

	if (g_nIEC61850CfgMngrRef == 0)
	{
		delete g_pIEC61850CfgMngr;
		g_pIEC61850CfgMngr = NULL;
	}
}

void CIEC61850CfgMngr::Init()
{
	nSample=4000;
	InitChanelMap();

	memset(confsv,0,sizeof(SendConfSV));
	memset(fiber,0,sizeof(FiberConf));
	memset(confgse,0,sizeof(SendConfGSE));
	memset(m_pIECConfig,0,sizeof(StructIECConfig));
	memset(ft3sub,0,sizeof(Ft3SubData));
	memset(gsesub,0,sizeof(GooseSubData));
	memset(stMaps,0,sizeof(structGSOutMap));
	memset(stGseTest,0,sizeof(StructGSTest));
	memset(goosechange,0,sizeof(GooseChangedItems));
	memset(m_pIECFiberInfo,0,sizeof(IECFiberInfo));
}

void CIEC61850CfgMngr::InitChanelMap()
{
	m_ChanMapID.clear();
	m_ChanMapID.insert("0",0);

	m_ChanMapID.insert("Ua1",1);
	m_ChanMapID.insert("Ub1",2);
	m_ChanMapID.insert("Uc1",3);
	m_ChanMapID.insert("U01",4);

	m_ChanMapID.insert("Ua2",5);
	m_ChanMapID.insert("Ub2",6);
	m_ChanMapID.insert("Uc2",7);
	m_ChanMapID.insert("U02",8);

	m_ChanMapID.insert("Ua3",9);
	m_ChanMapID.insert("Ub3",10);
	m_ChanMapID.insert("Uc3",11);
	m_ChanMapID.insert("U03",12);

	m_ChanMapID.insert("Ua4",13);
	m_ChanMapID.insert("Ub4",14);
	m_ChanMapID.insert("Uc4",15);
	m_ChanMapID.insert("U04",16);

	m_ChanMapID.insert("Ia1",17);
	m_ChanMapID.insert("Ib1",18);
	m_ChanMapID.insert("Ic1",19);
	m_ChanMapID.insert("I01",20);

	m_ChanMapID.insert("Ia2",21);
	m_ChanMapID.insert("Ib2",22);
	m_ChanMapID.insert("Ic2",23);
	m_ChanMapID.insert("I02",24);

	m_ChanMapID.insert("Ia3",25);
	m_ChanMapID.insert("Ib3",26);
	m_ChanMapID.insert("Ic3",27);
	m_ChanMapID.insert("I03",28);

	m_ChanMapID.insert("Ia4",29);
	m_ChanMapID.insert("Ib4",30);
	m_ChanMapID.insert("Ic4",31);
	m_ChanMapID.insert("I04",32);

	m_ChanMapID.insert("t-delay",33);
	m_ChanMapID.insert("Uz",34);

	m_ChanMapID.insert("Ua5",35);
	m_ChanMapID.insert("Ub5",36);
	m_ChanMapID.insert("Uc5",37);
	m_ChanMapID.insert("U05",38);

	m_ChanMapID.insert("Ua6",39);
	m_ChanMapID.insert("Ub6",40);
	m_ChanMapID.insert("Uc6",41);
	m_ChanMapID.insert("U06",42);

	//	m_ChanMapID.insert("Ua7",9);
	//	m_ChanMapID.insert("Ub7",10);
	//	m_ChanMapID.insert("Uc7",11);
	//	m_ChanMapID.insert("U07",12);

	//	m_ChanMapID.insert("Ua8",13);
	//	m_ChanMapID.insert("Ub8",14);
	//	m_ChanMapID.insert("Uc8",15);
	//	m_ChanMapID.insert("U08",16);

	m_ChanMapID.insert("Ia5",43);
	m_ChanMapID.insert("Ib5",44);
	m_ChanMapID.insert("Ic5",45);
	m_ChanMapID.insert("I05",46);

	m_ChanMapID.insert("Ia6",47);
	m_ChanMapID.insert("Ib6",48);
	m_ChanMapID.insert("Ic6",49);
	m_ChanMapID.insert("I06",50);

	//	m_ChanMapID.insert("Ia7",25);
	//	m_ChanMapID.insert("Ib7",26);
	//	m_ChanMapID.insert("Ic7",27);
	//	m_ChanMapID.insert("I07",28);

	//	m_ChanMapID.insert("Ia8",29);
	//	m_ChanMapID.insert("Ib8",30);
	//	m_ChanMapID.insert("Ic8",31);
	//	m_ChanMapID.insert("I08",32);
}

void CIEC61850CfgMngr::FiberClose()
{
	for(int i=0;i<m_pIECConfig->moduleCount;i++)
	{
		memset(fiber,0,sizeof(FiberConf));
		fiber->data0=m_pIECConfig->item[i].module;
		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(FiberCtrlCfg,(char*)fiber,sizeof(FiberConf));
	}
}

void CIEC61850CfgMngr::FiberOpen()
{
	for(int i=0;i<m_pIECConfig->moduleCount;i++)
	{
		memset(fiber,0,sizeof(FiberConf));
		fiber->data0=m_pIECConfig->item[i].module;

		for(int index=0;index<m_pIECConfig->item[i].smvCount;index++)
		{
			int group=m_pIECFiberInfo->item[i].sv[index].group;
			int port=m_pIECFiberInfo->item[i].sv[index].port;
			if(group<5)
			{
				fiber->data4|=(1<<port)<<((4-group)*8);//sv1-4
			}
			else
			{
				fiber->data5|=(1<<port)<<((8-group)*8);//sv5-8
			}
		}

		for(int index=0;index<m_pIECConfig->item[i].gsCount;index++)
		{
			int group=m_pIECFiberInfo->item[i].gs[index].group;
			int port=m_pIECFiberInfo->item[i].gs[index].port;
			switch(group)
			{
			case 1:
			case 2:
			case 3:
			case 4:
				fiber->data6|=(1<<port)<<((4-group)*8);
				break;
			case 5:
			case 6:
			case 7:
			case 8:
				fiber->data7|=(1<<port)<<((8-group)*8);
				break;
			case 9:
			case 10:
			case 11:
			case 12:
				fiber->data8|=(1<<port)<<((12-group)*8);
				break;
			case 13:
			case 14:
			case 15:
			case 16:
				fiber->data9|=(1<<port)<<((16-group)*8);
				break;
			}
		}

		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(FiberCtrlCfg,(char*)fiber,sizeof(FiberConf));
	}
}

QString DecToBin(QString strDec)//10è¿›åˆ¶ï¿½ï¿½?2è¿›åˆ¶
{
	int nDec= strDec.toInt();
	QString strBin("%1");
	strBin = strBin.arg(nDec,4,2,QChar('0'));
	return strBin;
}

QString HexToBin(QString m_Value)//16-2
{
	int t_Value = m_Value.toInt();
	QString t_strValue = "";
	t_strValue.setNum(t_Value);
	return DecToBin(t_strValue);
}

QString BinToHex(QString m_strBin)//2-16
{
	bool ok;
	long t_V = m_strBin.toLong(&ok,2);
	QString t_Dec = "";
	t_Dec =t_Dec.setNum(t_V,16);
	return t_Dec;
}

QString DecToHex(QString strDec)//10->16
{
	bool ok;
	long t_V = strDec.toLong(&ok,10);
	QString t_Hex = "";
	return t_Hex.setNum(t_V,16);
}

unsigned long GetIntegerFromString(QString pStr)
{
	int t_Length = pStr.length();
	char*  ch;
	QByteArray ba = pStr.toLatin1();
	ch=ba.data();

	unsigned long nValue = 0;
	for (int i = 0; i<t_Length; i++)
	{
		int nLetterValue ;

		switch (ch[i])
		{
		case 'a':case 'A':
			nLetterValue = 10;break;
		case 'b':case 'B':
			nLetterValue = 11;break;
		case 'c': case 'C':
			nLetterValue = 12;break;
		case 'd':case 'D':
			nLetterValue = 13;break;
		case 'e': case 'E':
			nLetterValue = 14;break;
		case 'f': case 'F':
			nLetterValue = 15;break;
		default:nLetterValue = ch[i] - '0';

		}
		nValue = nValue * 16 + nLetterValue; //16è¿›åˆ¶
	}
	return nValue;
}

void CIEC61850CfgMngr::AddLongStrToByte(QString m_Value, QByteArray &m_ByteArray, int m_Length)
{
	int m_StratPos = 0;
	QString t_temp = "";

	for (int m = 0; m < m_Length; m++)
	{
		m_StratPos = m * 2;
		t_temp = m_Value.mid(m_StratPos, 2);
		unsigned char t_V = GetIntegerFromString(t_temp);
		m_ByteArray.push_back(t_V);
	}
}

QString Get0String(int m_0Length)
{
	if (m_0Length <= 0)
	{
		return "";
	}
	QString t_R1 = "";
	QString t_0 = "0";
	for (int p = 0; p < m_0Length; p++)
	{
		t_R1 += t_0;
	}
	return t_R1;
}

void CIEC61850CfgMngr::AddASN1StrToByte(QString m_Value, QByteArray &m_ByteArray, unsigned short m_Flag, int m_Length)
{
	int t_V = GetIntegerFromString(m_Value);
	if(t_V >= 0x80)
	{
		m_ByteArray.push_back(m_Flag);
		m_ByteArray.push_back(0x80 + m_Length);
		AddLongStrToByte(m_Value, m_ByteArray, m_Length);//SrcMac
	}
	else
	{
		m_ByteArray.push_back(m_Flag);
		m_ByteArray.push_back(m_Length);
		AddLongStrToByte(m_Value, m_ByteArray, m_Length);//SrcMac
	}
}

void CIEC61850CfgMngr::GetASDUData(QByteArray & m_ASDUDataArray, QByteArray & m_ChanListData, QStringList & m_ChanFactorList, int & m_OffsetChanValue, int m_ChanNum)
{
	m_ASDUDataArray.push_back(0x87);
	QByteArray t_Array;
	int t_ChanNum = m_ChanNum;

	for (int m = 0; m < t_ChanNum; m++)
	{
		if(m>=m_ChanListData.size())//2
		{
			AddLongStrToByte("00000000", t_Array, 4);
			AddLongStrToByte("00000000", t_Array, 4);

			continue;
		}

		unsigned char t_ChanID = m_ChanListData[m];

		for(int tt = 0; tt < 4; tt++)
		{
			t_Array.push_back(t_ChanID);
		}

		AddLongStrToByte(m_ChanFactorList[m], t_Array, 4);
	}

	int t_CDataLength = t_Array.size();
	if (t_CDataLength >= 0x80 && t_CDataLength <= 0xFF)
	{
		m_OffsetChanValue = 3;
		m_ASDUDataArray.push_back(0x81);
		m_ASDUDataArray.push_back(t_CDataLength);
	}
	else
	{
		if (t_CDataLength > 0xFF)
		{
			m_OffsetChanValue = 4;
			m_ASDUDataArray.push_back(0x82);
			QString t_strCDataLength = "";
			t_strCDataLength = t_strCDataLength.setNum(t_CDataLength);
			QString t_HexCL = DecToHex(t_strCDataLength);
			t_HexCL = Get0String(4 - t_HexCL.length()) + t_HexCL;
			m_ASDUDataArray.push_back(GetIntegerFromString(t_HexCL.mid(0, 2)));
			m_ASDUDataArray.push_back(GetIntegerFromString(t_HexCL.mid(2, 2)));
		}
		else
		{
			m_OffsetChanValue = 2;
			m_ASDUDataArray.push_back(t_CDataLength);
		}
	}

	for (int j = 0; j < t_CDataLength;j++)
	{
		m_ASDUDataArray.push_back(t_Array.at(j));
	}
}

void CIEC61850CfgMngr::Create92Packet(tmt_sv_92 &m_92Struct,QByteArray & m_ResultArray,QString m_SavePath, int m_pcapmode)
{
	SMV92Struct m_92PacketStruct;
	m_ResultArray.clear();

	//////////////////////////////////////
	AddLongStrToByte(m_92Struct.m_MacDesc, m_92PacketStruct.m_DesMac, 6);//DesMac
	AddLongStrToByte(m_92Struct.m_MacSrc, m_92PacketStruct.m_SrcMac, 6);//SrcMac
	AddLongStrToByte(m_92Struct.m_NetType, m_92PacketStruct.m_Type, 2);//TYPE
	QString t2 = HexToBin(m_92Struct.m_VLanID);
	QString t1 = HexToBin(m_92Struct.m_VLanPri);
	while(t2.length() < 12)
	{
		QString t3 = "0";
		t3 += t2;
		t2 = t3;
	}
	QString t_VLANValue = BinToHex(t1 + "0" + t2);

	AddLongStrToByte("8100", m_92PacketStruct.m_VLan, 2);     //VLAN
	AddLongStrToByte(t_VLANValue, m_92PacketStruct.m_VLan, 2);//VLAN

	//    qDebug()<<"the m_92PacketStruct.m_VLan"<<t_VLANValue<<m_92PacketStruct.m_VLan;

	//////////////////////////////////////////////
	int t_ASDUNum = m_92Struct.m_ASDUNum.toInt();
	int t_PDULength = 0;
	int t_ChanNum = m_92Struct.m_ChanNum.toInt();
	int t_OffsetChanValue = 0;
	for (int m = 0; m < t_ASDUNum; m++)
	{
		ASDUStruct * t_ASDU = new ASDUStruct;
		GetASDUData(t_ASDU->m_SequenceData, m_92Struct.m_ChanValueList, m_92Struct.m_FactorList, t_OffsetChanValue, t_ChanNum);

		//////////////////svid///////////////////////
		int t_svidlength = m_92Struct.m_SVID.length();
		t_ASDU->m_smvID.push_back(0x80);
		t_ASDU->m_smvID.push_back(t_svidlength);
		t_ASDU->m_smvID.append(m_92Struct.m_SVID);
		////qDebug()<<"t_ASDU->m_smvID="<<t_ASDU->m_smvID.toHex();
		//////////////////smpc/////////////////////////////
		if(m_92Struct.m_bDatset)
		{
			t_ASDU->m_Datset.push_back(0x81);
			t_ASDU->m_Datset.push_back(m_92Struct.m_Datset.size());
			t_ASDU->m_Datset.append(m_92Struct.m_Datset);
		}
		t_ASDU->m_SmpCnt.push_back(0x82);
		t_ASDU->m_SmpCnt.push_back(0x02);
		int t_CurSmpCnt = m_92Struct.m_SmpCnt.toInt() + m;
		QString t_StrCurSmpCnt = "";
		t_StrCurSmpCnt = t_StrCurSmpCnt.setNum(t_CurSmpCnt);
		QString t_HexSmpCnt = DecToHex(t_StrCurSmpCnt);
		AddLongStrToByte(Get0String(4 - t_HexSmpCnt.length()) + t_HexSmpCnt, t_ASDU->m_SmpCnt, 2);//smpcnt
		//////////////////////conRev/////////////////////////////////
		t_ASDU->m_ConRev.push_back(0x83);
		t_ASDU->m_ConRev.push_back(0x04);
		QString t_ConfRev = DecToHex(m_92Struct.m_ConfRev);
		AddLongStrToByte(Get0String(8 - t_ConfRev.length()) + t_ConfRev, t_ASDU->m_ConRev, 4);//ConRev
		//////////////////////refrtm/////////////////////////////////
		if(m_92Struct.m_bRefrTm)
		{
			t_ASDU->m_RefrTm.push_back(0x84);
			t_ASDU->m_RefrTm.push_back(0x06);
			for(int i =0;i<6;i++)
			{
				t_ASDU->m_RefrTm.push_back(0xBB);
			}
		}

		//////////////////////SmpSync///////////////////////////////////////
		t_ASDU->m_SmpSynch.push_back(0x85);
		t_ASDU->m_SmpSynch.push_back(0x01);
		AddLongStrToByte(m_92Struct.m_SyncMode, t_ASDU->m_SmpSynch, 1);//SmpSync
		//////////////SmpRate////////////////////////////////////////////////
		if(m_92Struct.m_bSmpRate)
		{
			t_ASDU->m_SmpRate.push_back(0x86);
			t_ASDU->m_SmpRate.push_back(0x02);
			qDebug()<<"m_smprate"<<QString::number(4000,16);
			int nLen = 4000;
			for (int i=1;i>=0;i--)
			{
				char byte = 0;
				byte = nLen>>i*8 & 0xFF;
				t_ASDU->m_SmpRate.push_back(byte); //ï¿½ï¿½ï¿½Ä³ï¿½ï¿½ï¿½
			}
		}
		// 		AddLongStrToByte(m_92Struct,t_ASDU->m_SmpSynch,2);//SmpRate
		/////////////////ï¿½ï¿½ï¿½ï¿½///////////////////////////////////////////
		t_ASDU->m_StartLength.push_back(0x30);
		int t_AllLength = t_ASDU->m_smvID.size() + t_ASDU->m_ConRev.size() + t_ASDU->m_SequenceData.size() + t_ASDU->m_SmpCnt.size() + t_ASDU->m_SmpSynch.size();
		t_AllLength += t_ASDU->m_RefrTm.size();
		t_AllLength += t_ASDU->m_Datset.size();
		t_AllLength += t_ASDU->m_SmpRate.size();
		////qDebug()<<"t_AllLength 0x30 ="<<t_AllLength;
		if (t_AllLength>=0x80 && t_AllLength<=0xFF)
		{
			t_ASDU->m_StartLength.push_back(0x81);
			t_ASDU->m_StartLength.push_back(t_AllLength);
		}
		else if(t_AllLength > 0xFF)
		{
			t_ASDU->m_StartLength.push_back(0x82);

			QString t_strt_AllLength;
			t_strt_AllLength = t_strt_AllLength.setNum(t_AllLength);
			QString t_HexPL = DecToHex(t_strt_AllLength);
			t_HexPL = Get0String(4 - t_HexPL.length()) + t_HexPL;
			t_ASDU->m_StartLength.push_back(GetIntegerFromString(t_HexPL.mid(0, 2)));
			t_ASDU->m_StartLength.push_back(GetIntegerFromString(t_HexPL.mid(2, 2)));
		}
		else
		{
			t_ASDU->m_StartLength.push_back(t_AllLength);
		}
		t_PDULength+=t_AllLength;
		t_PDULength+=t_ASDU->m_StartLength.size();
		m_92PacketStruct.m_PDU.p_ASDUVector.push_back(t_ASDU);
	}
	///////////////////////////PDUï¿½ï¿½ï¿½ï¿½///////////////////////////////////////////////
	m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(0xA2);
	if(m_92Struct.m_bSecurity)
	{
		m_92PacketStruct.m_PDU.m_Security.push_back(0x81);
		m_92PacketStruct.m_PDU.m_Security.push_back(0x01);
	}
	if (t_PDULength>=0x80&&t_PDULength<=0xFF)
	{
		m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(0x81);
		m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(t_PDULength);
	}
	else
	{
		if (t_PDULength>0xFF)
		{
			m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(0x82);
			QString t_strPDUL = "";
			t_strPDUL= t_strPDUL.setNum(t_PDULength);
			QString t_HexPL = DecToHex(t_strPDUL);
			t_HexPL = Get0String(4-t_HexPL.length())+t_HexPL;
			m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(GetIntegerFromString(t_HexPL.mid(0,2)));
			m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(GetIntegerFromString(t_HexPL.mid(2,2)));
		}
		else
		{
			m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(t_PDULength);
		}
	}
	t_PDULength+=m_92PacketStruct.m_PDU.m_SequenceofASDU.size();
	//////////////////////////////Number of ASDU/////////////////////////
	AddASN1StrToByte(m_92Struct.m_ASDUNum,m_92PacketStruct.m_PDU.m_NumOfASDU,0x80,1);
	t_PDULength+=m_92PacketStruct.m_PDU.m_NumOfASDU.size();
	//////////////////////////////pduï¿½ï¿½ï¿½ï¿½///////////////////////////////////////
	m_92PacketStruct.m_PDU.m_pduLength.push_back(0x60);
	if (t_PDULength>=0x80&&t_PDULength<=0xFF)
	{
		m_92PacketStruct.m_PDU.m_pduLength.push_back(0x81);
		m_92PacketStruct.m_PDU.m_pduLength.push_back(t_PDULength);
	}
	else
	{
		if (t_PDULength>0xFF)
		{
			m_92PacketStruct.m_PDU.m_pduLength.push_back(0x82);
			QString t_strPDUL = "";
			t_strPDUL= t_strPDUL.setNum(t_PDULength);
			QString t_HexPL = DecToHex(t_strPDUL);
			t_HexPL = Get0String(4-t_HexPL.length())+t_HexPL;
			m_92PacketStruct.m_PDU.m_pduLength.push_back(GetIntegerFromString(t_HexPL.mid(0,2)));
			m_92PacketStruct.m_PDU.m_pduLength.push_back(GetIntegerFromString(t_HexPL.mid(2,2)));
		}
		else
		{
			m_92PacketStruct.m_PDU.m_pduLength.push_back(t_PDULength);
		}
	}
	t_PDULength+=m_92PacketStruct.m_PDU.m_pduLength.size();
	/////////////////////////ï¿½ï¿½ï¿½ï¿½IEC_SMV92///////////////////////////////////
	int t_ApplicationLength = t_PDULength;
	AddLongStrToByte(m_92Struct.m_AppID, m_92PacketStruct.m_AppID, 2);

	m_92PacketStruct.m_Reserve1.push_back((unsigned char)(m_92Struct.nreserved1>>8));
	m_92PacketStruct.m_Reserve1.push_back((unsigned char)(m_92Struct.nreserved1));
	m_92PacketStruct.m_Reserve2.push_back((unsigned char)(m_92Struct.nreserved2>>8));
	m_92PacketStruct.m_Reserve2.push_back((unsigned char)(m_92Struct.nreserved2));
	//	AddLongStrToByte("0000", m_92PacketStruct.m_Reserve1, 2);
	//	AddLongStrToByte("0000", m_92PacketStruct.m_Reserve2, 2);
	t_ApplicationLength += 8;
	m_92PacketStruct.m_ApplicationLength.push_back(t_ApplicationLength>>8&~(~0<<8));
	m_92PacketStruct.m_ApplicationLength.push_back(t_ApplicationLength&~(~0<<8));
	/////////////////////////ï¿½ï¿½ï¿½ï¿½Ethernet///////////////////////////////////
	AddLongStrToByte(m_92Struct.m_MacDesc, m_92PacketStruct.m_DesMac, 4);
	AddLongStrToByte(m_92Struct.m_MacSrc, m_92PacketStruct.m_SrcMac, 4);
	AddLongStrToByte("88BA", m_92PacketStruct.m_Type, 2);
	//////////////////////////////////////////////////////////////////////////
	unsigned char t_SaveData[20000];

	int t_FLength = 0;
	for (int m = 0; m < 6; m++)
	{
		t_SaveData[m] = m_92PacketStruct.m_DesMac.at(m);
	}
	t_FLength += 6;
	for (int m = 0; m < 6; m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_SrcMac.at(m);
	}
	t_FLength += 6;

	for (int m=0;m<4;m++)
	{
		t_SaveData[t_FLength+m] = m_92PacketStruct.m_VLan.at(m);
	}
	t_FLength+=4;

	for (int m=0;m<2;m++)
	{
		t_SaveData[t_FLength+m] = m_92PacketStruct.m_Type.at(m);
	}
	t_FLength+=2;
	for (int m=0;m<2;m++)
	{
		t_SaveData[t_FLength+m] = m_92PacketStruct.m_AppID.at(m);
	}
	t_FLength+=2;
	for (int m=0;m<2;m++)
	{
		t_SaveData[t_FLength+m] = m_92PacketStruct.m_ApplicationLength.at(m);
	}
	t_FLength+=2;
	for (int m=0;m<2;m++)
	{
		t_SaveData[t_FLength+m] = m_92PacketStruct.m_Reserve1.at(m);
	}
	t_FLength+=2;
	for (int m=0;m<2;m++)
	{
		t_SaveData[t_FLength+m] = m_92PacketStruct.m_Reserve2.at(m);
	}
	t_FLength+=2;

	for (int m=0;m<m_92PacketStruct.m_PDU.m_pduLength.size();m++)
	{
		t_SaveData[t_FLength+m] = m_92PacketStruct.m_PDU.m_pduLength.at(m);
	}
	t_FLength+=m_92PacketStruct.m_PDU.m_pduLength.size();

	for (int m=0;m<m_92PacketStruct.m_PDU.m_NumOfASDU.size();m++)
	{
		t_SaveData[t_FLength+m] = m_92PacketStruct.m_PDU.m_NumOfASDU.at(m);
	}
	t_FLength+=m_92PacketStruct.m_PDU.m_NumOfASDU.size();

	//    for (int m=0;m<m_92PacketStruct.m_PDU.m_Security.size();m++)
	//    {
	//        t_SaveData[t_FLength+m] = m_92PacketStruct.m_PDU.m_Security.at(m);
	//    }
	//    t_FLength+=m_92PacketStruct.m_PDU.m_Security.size();


	for (int m=0;m<m_92PacketStruct.m_PDU.m_SequenceofASDU.size();m++)
	{
		t_SaveData[t_FLength+m] = m_92PacketStruct.m_PDU.m_SequenceofASDU.at(m);
	}
	t_FLength += m_92PacketStruct.m_PDU.m_SequenceofASDU.size();

	int nASDUStartPos = t_FLength;
	int t_SmpCntValePos = 0;
	int t_ChanValuePos = 0;
	int nASDULeng = 0;

	for (int q = 0; q < t_ASDUNum; q++)
	{
		ASDUStruct * pASDU = m_92PacketStruct.m_PDU.p_ASDUVector[q];
		for (int m = 0; m < pASDU->m_StartLength.size(); m++)
		{
			t_SaveData[t_FLength+m] = pASDU->m_StartLength.at(m);
		}
		t_FLength+=pASDU->m_StartLength.size();

		for (int m=0;m<pASDU->m_smvID.size();m++)
		{
			t_SaveData[t_FLength+m] = pASDU->m_smvID.at(m);
		}

		t_FLength+=pASDU->m_smvID.size();

		for (int m=0;m<pASDU->m_Datset.size();m++)
		{
			t_SaveData[t_FLength+m] = pASDU->m_Datset.at(m);
		}
		t_FLength+=pASDU->m_Datset.size();

		for (int m=0;m<pASDU->m_SmpCnt.size();m++)
		{
			t_SaveData[t_FLength+m] = pASDU->m_SmpCnt.at(m);
		}
		t_FLength+=pASDU->m_SmpCnt.size();

		if(q == 0){
			t_SmpCntValePos = t_FLength-2 - nASDUStartPos;
		}


		for (int m=0;m<pASDU->m_ConRev.size();m++)
		{
			t_SaveData[t_FLength+m] = pASDU->m_ConRev.at(m);
		}
		t_FLength+=pASDU->m_ConRev.size();

		for (int m=0;m<pASDU->m_RefrTm.size();m++)
		{
			t_SaveData[t_FLength+m] = pASDU->m_RefrTm.at(m);
		}
		t_FLength+=pASDU->m_RefrTm.size();

		for (int m=0;m<pASDU->m_SmpSynch.size();m++)
		{
			t_SaveData[t_FLength+m] = pASDU->m_SmpSynch.at(m);
		}
		t_FLength+=pASDU->m_SmpSynch.size();

		for (int m=0;m<pASDU->m_SmpRate.size();m++)
		{
			t_SaveData[t_FLength+m] = pASDU->m_SmpRate.at(m);
		}
		t_FLength+=pASDU->m_SmpRate.size();

		if(q == 0){
			nASDULeng =pASDU->m_SequenceData.size() - t_OffsetChanValue;

			t_ChanValuePos = t_FLength + t_OffsetChanValue - nASDUStartPos;
		}


		for (int m=0;m<pASDU->m_SequenceData.size();m++)
		{
			t_SaveData[t_FLength+m] = pASDU->m_SequenceData.at(m);
		}


		t_FLength+=pASDU->m_SequenceData.size();
		//qDebug()<<"asdu"<<q<<t_ASDUNum;
		//qDebug()<<"pASDU->m_SequenceData ="<<pASDU->m_SequenceData.toHex();
	}
	//qDebug()<<"ALLLength ="<<t_FLength;
	//qDebug()<<"t_SmpCntValePos ="<<t_SmpCntValePos;
	//    qDebug()<<"t_ChanValuePos ="<<t_ChanValuePos;
	if(m_pcapmode==0)
	{
		QByteArray & t_WaitToSendStructArray = m_ResultArray;
		QString t_strAll = QString::number(t_FLength, 16);
		QString t_strSmpCntValePos = QString::number(t_SmpCntValePos, 16);
		QString t_strChanValuePos = QString::number(t_ChanValuePos, 16);

		//All
		AddLongStrToByte(Get0String(4 - t_strAll.length()) + t_strAll, t_WaitToSendStructArray, 2);
		unsigned char nASDUnum = t_ASDUNum;
		t_WaitToSendStructArray.push_back(nASDUnum);

		t_WaitToSendStructArray.push_back(char((nASDUStartPos&0xFF00)>>8));
		t_WaitToSendStructArray.push_back(char(nASDUStartPos&0xFF));

		//SmpCntValuePos
		AddLongStrToByte(Get0String(4 - t_strSmpCntValePos.length()) + t_strSmpCntValePos, t_WaitToSendStructArray, 2);

		//ChanValuePos
		AddLongStrToByte(Get0String(4 - t_strChanValuePos.length()) + t_strChanValuePos, t_WaitToSendStructArray, 2);

		t_WaitToSendStructArray.push_back(char((nASDULeng&0xFF00)>>8));
		t_WaitToSendStructArray.push_back(char(nASDULeng&0xFF));

		QString t_TimeHex = DecToHex(m_92Struct.m_DelayTimeValue);

		//ChanValuePos
		AddLongStrToByte(Get0String(4 - t_TimeHex.length()) + t_TimeHex, t_WaitToSendStructArray, 2);
		AddLongStrToByte("0000", t_WaitToSendStructArray, 2);
		AddLongStrToByte("0000", t_WaitToSendStructArray, 2);

		//qDebug()<<"savedata"<<t_FLength;
		for(int m = 0; m < t_FLength; m++)
		{
			t_WaitToSendStructArray.push_back(t_SaveData[m]);
		}
	}
	else if (m_pcapmode==1)//pcapï¿½Ä¼ï¿½ï¿½ï¿½Ê½ï¿½ï¿½ï¿½ï¿½
	{
		QByteArray t_FHead;
		QByteArray t_PHead1;
		QByteArray t_PHead2;
		for(int i = 0; i < 24; i++)
		{
			unsigned char t_V = 0x00;
			t_FHead.push_back(t_V);
		}

		for(int i = 0; i < 8; i++)
		{
			unsigned char t_V = 0x00;
			t_PHead1.push_back(t_V);
		}
		;
		QString t_StrFLength = "";
		t_StrFLength =  t_StrFLength.setNum(t_FLength);
		QString t_Hex = DecToHex(t_StrFLength);
		int t_HL = t_Hex.length();
		QString t_R = "";
		QString t_0 = "0";
		for (int p = 0; p < 8 - t_HL; p++)
		{
			t_R += t_0;
		}
		t_R += t_Hex;

		t_PHead2.push_back(GetIntegerFromString(t_R.mid(6, 2)));
		t_PHead2.push_back(GetIntegerFromString(t_R.mid(4, 2)));
		t_PHead2.push_back(GetIntegerFromString(t_R.mid(2, 2)));
		t_PHead2.push_back(GetIntegerFromString(t_R.mid(0, 2)));

		t_PHead2.push_back(GetIntegerFromString(t_R.mid(6, 2)));
		t_PHead2.push_back(GetIntegerFromString(t_R.mid(4, 2)));
		t_PHead2.push_back(GetIntegerFromString(t_R.mid(2, 2)));
		t_PHead2.push_back(GetIntegerFromString(t_R.mid(0, 2)));

		QByteArray t_SaveDataArray;
		for(int m = 0; m < t_FLength; m++)
		{
			t_SaveDataArray.push_back(t_SaveData[m]);
		}
		//qDebug()<<"t_SaveDataArray"<<t_SaveDataArray.toHex();
		QFile t_DataFile(m_SavePath + "SMV_Test.pcap");
		if (t_DataFile.open(QIODevice::WriteOnly/*|QIODevice::Append*/))
		{
			t_DataFile.write(t_FHead, 24);
			t_DataFile.write(t_PHead1, 8);
			t_DataFile.write(t_PHead2, 8);
			t_DataFile.write(t_SaveDataArray);
		}
		t_DataFile.close();
	}
}

void CIEC61850CfgMngr::ProcessGooseDataSetList(QByteArray& oAr)
{
	QByteArray oByteArray;
	oByteArray.push_back(0xAB);
	int t_L = oAr.size();
	if (t_L >= 0x80 && t_L <= 0xFF)
	{
		oByteArray.push_back(0x81);
		oByteArray.push_back(t_L);
	}
	else
	{
		if (t_L > 0xFF)
		{
			oByteArray.push_back(0x82);
			QString t_strL = "";
			t_strL = t_strL.setNum(t_L);
			QString t_HexL = DecToHex(t_strL);
			t_HexL = Get0String(4 - t_HexL.length()) + t_HexL;
			oByteArray.push_back(GetIntegerFromString(t_HexL.mid(0, 2)));
			oByteArray.push_back(GetIntegerFromString(t_HexL.mid(2, 2)));
		}
		else
		{
			oByteArray.push_back(t_L);
		}
	}

	for(int i=oByteArray.size()-1;i>-1;i--)
	{
		oAr.push_front(oByteArray.at(i));
	}
}

void CIEC61850CfgMngr::CreateGooseDataSetList(QByteArray& oAr, ChanelInfo &chan,char timequality)
{
	QString data_type=chan.data_type;

	if(QString::compare(data_type,"BOOLEAN")==0)
	{
		char value=0x01;
		if(QString::compare(chan.firstvalue,"FALSE")==0)
		{
			value=0x00;
		}
		oAr.push_back(0x83);
		oAr.push_back(0x01);
		oAr.push_back(value);

		chan.nFalseVlaue = 0;
		chan.nTrueValue = 1;
		chan.nBoPos = chan.nPos+2;
		return;
	}

	if(QString::compare(data_type,"Dbpos")==0)
	{
		//2bits
		bool ok;
		unsigned char value =chan.firstvalue.toInt(&ok,2)&0xff;
		oAr.push_back(0x84);
		unsigned char Zl= 2;//ï¿½ï¿½ï¿½ï¿½
		oAr.push_back(Zl);
		//ï¿½î³¤
		int CL = 6;
		oAr.push_back(CL);
		oAr.push_back(value<<CL);

		chan.nFalseVlaue = 0x40;
		chan.nTrueValue = 0x80;
		chan.nBoPos = chan.nPos+3;
		return;
	}

	if(QString::compare(data_type,"Timestamp")==0)
	{
		BYTE t_V = 0x00;
		long nSecond=0;
		long nNS = 0;
		//		CSttDeviceBase::g_pSttDeviceBase->GetUTCTime(nSecond,nNS);

		int t_HexTime = nSecond;

		QString t_strHexTime("%1");
		t_strHexTime = t_strHexTime.arg(t_HexTime, 2, 16, QChar('0'));
		t_strHexTime = Get0String(8 - t_strHexTime.length()) + t_strHexTime;
		oAr.push_back(0x91);
		oAr.push_back(0x08);
		oAr.push_back(GetIntegerFromString(t_strHexTime.mid(0, 2)));
		oAr.push_back(GetIntegerFromString(t_strHexTime.mid(2, 2)));
		oAr.push_back(GetIntegerFromString(t_strHexTime.mid(4, 2)));
		oAr.push_back(GetIntegerFromString(t_strHexTime.mid(6, 2)));
		oAr.push_back(t_V);
		oAr.push_back(t_V);
		oAr.push_back(t_V);
		oAr.push_back(timequality);
		return;
	}

	if(QString::compare(data_type,"VisString64")==0||QString::compare(data_type,"Quality")==0)
	{
		//13bits
		bool ok;
		short value=chan.firstvalue.toShort(&ok,2);//= pAtom->vuint();
		oAr.push_back(0x84);
		unsigned char Zl= 3;//ï¿½ï¿½ï¿½ï¿½
		oAr.push_back(Zl);
		//ï¿½î³¤
		int CL = 3;
		oAr.push_back(CL);
		value = value<<CL;

		oAr.append(value>>8);
		oAr.append(value&0xff);
		return;
	}

	if(QString::compare(data_type,"INT32")==0)
	{
		int value = chan.firstvalue.toInt();
		oAr.push_back(0x85);
		oAr.push_back(4);
		oAr.push_back((unsigned char)(value>>24));
		oAr.push_back((unsigned char)(value>>16));

		oAr.push_back((unsigned char)(value>>8));
		oAr.push_back((unsigned char)(value));
		return;
	}

	if(QString::compare(data_type,"INT32U")==0)
	{
		unsigned int value = chan.firstvalue.toUInt();
		oAr.push_back(0x85);
		oAr.push_back(4);
		oAr.push_back((unsigned char)(value>>24));
		oAr.push_back((unsigned char)(value>>16));
		oAr.push_back((unsigned char)(value>>8));
		oAr.push_back((unsigned char)(value));
		return;
	}

	if(QString::compare(data_type,"FLOAT32")==0)
	{
		float value = chan.firstvalue.toFloat();

		ConverStruct t_s;//ï¿½ï¿½ï¿½Ã¹ï¿½ï¿½ï¿½ï¿½ï¿½×ª
		t_s.f = value;
		oAr.push_back(0x87);
		oAr.push_back(0x05);
		oAr.push_back(0x08);
		oAr.push_back(t_s.b[3]);
		oAr.push_back(t_s.b[2]);
		oAr.push_back(t_s.b[1]);
		oAr.push_back(t_s.b[0]);
		return;
	}

	/******
	if(QString::compare(data_type,"STRUCT")==0)
	{
		QByteArray ot;
		int nSize = pAtom->vstru_size();
		for(int j=0;j<nSize;j++)
		{
			EncoDerGooseDataAtom(ot,pA);
		}

		oAr.push_back(0xA2);
		oAr.push_back(ot.size());

		oAr.append(ot);
	}
	*****/
}

void CIEC61850CfgMngr::CreateGooseData(QByteArray& oAr, tmt_goose &t_GOOSE)
{
	GooseStruct GoosePacketStruct;

	//ï¿½ï¿½ï¿½ï¿½Í·ï¿½ï¿½ï¿½ï¿½
	AddLongStrToByte(t_GOOSE.m_MacDesc,GoosePacketStruct.m_DesMac,6);//DesMac
	AddLongStrToByte(t_GOOSE.m_MacSrc,GoosePacketStruct.m_SrcMac,6);//SrcMac
	QString t2 = HexToBin(t_GOOSE.m_VLanID);
	QString t1 = HexToBin(t_GOOSE.m_VLanPri);
	while(t2.length() < 12)
	{
		QString t3 = ("0");
		t3 += t2;
		t2 = t3;
	}

	QString t_VLANValue = BinToHex(t1 + ("0") + t2);
	AddLongStrToByte( ("8100"), GoosePacketStruct.m_VLan, 2);   //VLAN
	AddLongStrToByte(t_VLANValue, GoosePacketStruct.m_VLan, 2); //VLAN
	AddLongStrToByte( t_GOOSE.m_NetType, GoosePacketStruct.m_Type, 2);   //TYPE

	//GooseDataProcess
	GoosePacketStruct.m_GoosePdu.m_DataSetList.append(t_GOOSE.m_DataSetList);
	int nDataSetLen = GoosePacketStruct.m_GoosePdu.m_DataSetList.size();
	ProcessGooseDataSetList(GoosePacketStruct.m_GoosePdu.m_DataSetList);

	int t_PduLength = GoosePacketStruct.m_GoosePdu.m_DataSetList.size();

	GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(0x8A);

	if (t_GOOSE.m_ChanNum<=0xFF)
	{
		GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(0x01);
		GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(t_GOOSE.m_ChanNum);
	}
	else
	{
		GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(0x02);
		QString t_DecStr = "";
		QString t_HexPduLength ="";
		t_DecStr = t_DecStr.setNum(t_GOOSE.m_ChanNum);
		t_HexPduLength = DecToHex(t_DecStr);
		t_HexPduLength = Get0String(4 - t_HexPduLength.length()) + t_HexPduLength;
		GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(GetIntegerFromString(t_HexPduLength.mid(0, 2)));
		GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(GetIntegerFromString(t_HexPduLength.mid(2, 2)));
	}
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_EntriesNum.size();

	///////////////////////////////////ndscom////////////////////////////////////////
	GoosePacketStruct.m_GoosePdu.m_NdsCom.push_back(0x89);
	GoosePacketStruct.m_GoosePdu.m_NdsCom.push_back(0x01);
	GoosePacketStruct.m_GoosePdu.m_NdsCom.push_back(t_GOOSE.m_NdsCom.toInt());
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_NdsCom.size();

	///////////////////////////////////ConfRev/////////////////////////////////
	GoosePacketStruct.m_GoosePdu.m_ConfRev.push_back(0x88);
	GoosePacketStruct.m_GoosePdu.m_ConfRev.push_back(0x02);
	QString t_RevHex = DecToHex(t_GOOSE.m_ConfRev);
	t_RevHex = Get0String(4 - t_RevHex.length()) + t_RevHex;
	GoosePacketStruct.m_GoosePdu.m_ConfRev.push_back(GetIntegerFromString(t_RevHex.mid(0, 2)));
	GoosePacketStruct.m_GoosePdu.m_ConfRev.push_back(GetIntegerFromString(t_RevHex.mid(2, 2)));
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_ConfRev.size();

	///////////////////////////////////TestMode//////////////////////////////////////////
	GoosePacketStruct.m_GoosePdu.m_TestMode.push_back(0x87);
	GoosePacketStruct.m_GoosePdu.m_TestMode.push_back(0x01);
	GoosePacketStruct.m_GoosePdu.m_TestMode.push_back(t_GOOSE.m_TestMode.toInt());
	qDebug()<<"testMode"<<t_GOOSE.m_TestMode.toInt()<<t_GOOSE.m_AppID;
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_TestMode.size();

	////////////////////////////////////SqNum/////////////////////////////////////////////////////////
	GoosePacketStruct.m_GoosePdu.m_SqNum.push_back(0x86);
	QString t_SqNum = t_GOOSE.m_SqNum;
	t_SqNum.replace( (" "), (""));
	int t_SqLength =  t_SqNum.length()/2;
	GoosePacketStruct.m_GoosePdu.m_SqNum.push_back(t_SqLength);
	for (int m = 0; m < t_SqLength; m++)
	{
		GoosePacketStruct.m_GoosePdu.m_SqNum.push_back(GetIntegerFromString(t_SqNum.mid(m * 2, 2)));
	}
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_SqNum.size();

	///////////////////////////////////StNum/////////////////////////////////////////////////////
	GoosePacketStruct.m_GoosePdu.m_StNum.push_back(0x85);
	QString t_StNum = t_GOOSE.m_StNum;
	t_StNum.replace( (" "), (""));
	int t_StLength =  t_StNum.length()/2;
	GoosePacketStruct.m_GoosePdu.m_StNum.push_back(t_StLength);
	for (int m = 0; m < t_StLength; m++)
	{
		GoosePacketStruct.m_GoosePdu.m_StNum.push_back(GetIntegerFromString(t_StNum.mid(m * 2, 2)));
	}
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_StNum.size();
	BYTE t_V0 = 0x00;

	/////////////////////////////////Event Time/////////////////////////////////////////////////////
	GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(0x84);
	GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(0x08);
	GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(t_V0);
	GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(t_V0);
	GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(t_V0);
	GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(t_V0);
	GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(t_V0);
	GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(t_V0);
	GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(t_V0);
	GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(t_GOOSE.ntimequality);
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_TimeStamp.size();

	/////////////////////////////////goID///////////////////////////////////////////////
	int t_GoIDLength = t_GOOSE.m_GoID.length();
	GoosePacketStruct.m_GoosePdu.m_GoID.push_back(0x83);
	GoosePacketStruct.m_GoosePdu.m_GoID.push_back(t_GoIDLength);
	GoosePacketStruct.m_GoosePdu.m_GoID.append(t_GOOSE.m_GoID.toLatin1());
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_GoID.size();

	/////////////////////////////////DataSetRef///////////////////////////////////
	int t_DataSetLength = t_GOOSE.m_DataSetRef.length();
	GoosePacketStruct.m_GoosePdu.m_DataSetRef.push_back(0x82);
	GoosePacketStruct.m_GoosePdu.m_DataSetRef.push_back(t_DataSetLength);
	GoosePacketStruct.m_GoosePdu.m_DataSetRef.append(t_GOOSE.m_DataSetRef.toLatin1());
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_DataSetRef.size();

	/////////////////////////////////TTL////////////////////////////////////////////////////
	GoosePacketStruct.m_GoosePdu.m_TTL.push_back(0x81);
	//qDebug()<<"m_GooseSrcStruct.m_TTL="<<m_GooseSrcStruct.m_TTL;
	QString t_TTLHex = DecToHex(t_GOOSE.m_TTL);
	t_TTLHex = Get0String(4 - t_TTLHex.length()) + t_TTLHex;
	GoosePacketStruct.m_GoosePdu.m_TTL.push_back(0x02);
	GoosePacketStruct.m_GoosePdu.m_TTL.push_back(GetIntegerFromString(t_TTLHex.mid(0, 2)));
	GoosePacketStruct.m_GoosePdu.m_TTL.push_back(GetIntegerFromString(t_TTLHex.mid(2, 2)));
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_TTL.size();

	///////////////////////////////GcRef////////////////////////////////////////
	int t_GcRef = t_GOOSE.m_GcRef.length();
	GoosePacketStruct.m_GoosePdu.m_GcRef.push_back(0x80);
	GoosePacketStruct.m_GoosePdu.m_GcRef.push_back(t_GcRef);
	GoosePacketStruct.m_GoosePdu.m_GcRef.append(t_GOOSE.m_GcRef.toLatin1());
	t_PduLength += GoosePacketStruct.m_GoosePdu.m_GcRef.size();

	////////////////////////////////PDU Length//////////////////////////////////////////////////
	GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(0x61);
	if (t_PduLength>=0x80 && t_PduLength<=0xFF)
	{
		GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(0x81);
		GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(t_PduLength);
	}
	else
	{
		if (t_PduLength > 0xFF)
		{
			GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(0x82);
			QString t_DecStr = "";
			QString t_HexPduLength = "";
			t_DecStr = t_DecStr.setNum(t_PduLength);
			t_HexPduLength = DecToHex(t_DecStr);
			t_HexPduLength = Get0String(4 - t_HexPduLength.length()) + t_HexPduLength;
			GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(GetIntegerFromString(t_HexPduLength.mid(0, 2)));
			GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(GetIntegerFromString(t_HexPduLength.mid(2, 4)));
		}
		else
		{
			GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(t_PduLength);
		}
	}
	int t_ApplicationLength = t_PduLength + GoosePacketStruct.m_GoosePdu.m_PduLength.size();
	BYTE t_V00 = 0x00;
	/////////////////////////////////////ReServed1,Resverved2,AppID,Length////////////////////////////////////////////////////

	GoosePacketStruct.m_Reserve1.push_back((unsigned char)(t_GOOSE.nreserved1>>8));
	GoosePacketStruct.m_Reserve1.push_back((unsigned char)(t_GOOSE.nreserved1));

	GoosePacketStruct.m_Reserve2.push_back((unsigned char)(t_GOOSE.nreserved2>>8));
	GoosePacketStruct.m_Reserve2.push_back((unsigned char)(t_GOOSE.nreserved2));

	QString t_AppID = t_GOOSE.m_AppID;
	t_AppID = Get0String(4 - t_AppID.length()) + t_AppID;
	GoosePacketStruct.m_AppID.push_back(GetIntegerFromString(t_AppID.mid(0, 2)));
	GoosePacketStruct.m_AppID.push_back(GetIntegerFromString(t_AppID.mid(2, 2)));

	t_ApplicationLength += 8;

	QString t_HexAppLength = "";
	t_HexAppLength = t_HexAppLength.setNum(t_ApplicationLength);
	t_HexAppLength = DecToHex(t_HexAppLength);
	t_HexAppLength = Get0String(4 - t_HexAppLength.length()) + t_HexAppLength;
	GoosePacketStruct.m_ApplicationLength.push_back(GetIntegerFromString(t_HexAppLength.mid(0, 2)));
	GoosePacketStruct.m_ApplicationLength.push_back(GetIntegerFromString(t_HexAppLength.mid(2, 2)));
	/////////////////////////////////////////////////////////////////////////////////
	BYTE t_SaveData[20000];
	int t_FLength = 0;
	for (int m = 0; m < 6; m++)
	{
		t_SaveData[m] = GoosePacketStruct.m_DesMac.at(m);
	}
	t_FLength += 6;
	for (int m = 0; m < 6; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_SrcMac.at(m);
	}
	t_FLength += 6;

	for (int m = 0; m < 4; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_VLan.at(m);
	}
	t_FLength += 4;

	for (int m = 0; m < 2; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_Type.at(m);
	}
	t_FLength += 2;
	for (int m = 0; m < 2; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_AppID.at(m);
	}
	t_FLength += 2;
	for (int m = 0; m < 2; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_ApplicationLength.at(m);
	}
	t_FLength += 2;
	for (int m = 0; m < 2; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_Reserve1.at(m);
	}
	t_FLength += 2;
	for (int m = 0; m < 2;m++)
	{
		t_SaveData[t_FLength+m] = GoosePacketStruct.m_Reserve2.at(m);
	}
	t_FLength+=2;

	int l = GoosePacketStruct.m_GoosePdu.m_PduLength.size();
	for (int m=0;m<l;m++)
	{
		t_SaveData[t_FLength+m] = GoosePacketStruct.m_GoosePdu.m_PduLength.at(m);
	}
	t_FLength+=l;

	l = GoosePacketStruct.m_GoosePdu.m_GcRef.size();
	for (int m=0;m<l;m++)
	{
		t_SaveData[t_FLength+m] = GoosePacketStruct.m_GoosePdu.m_GcRef.at(m);
	}
	t_FLength+=l;

	l = GoosePacketStruct.m_GoosePdu.m_TTL.size();
	for (int m=0;m<l;m++)
	{
		t_SaveData[t_FLength+m] = GoosePacketStruct.m_GoosePdu.m_TTL.at(m);
	}
	t_FLength+=l;

	l = GoosePacketStruct.m_GoosePdu.m_DataSetRef.size();
	for (int m=0;m<l;m++)
	{
		t_SaveData[t_FLength+m] = GoosePacketStruct.m_GoosePdu.m_DataSetRef.at(m);
	}
	t_FLength+=l;

	l = GoosePacketStruct.m_GoosePdu.m_GoID.size();
	for (int m=0;m<l;m++)
	{
		t_SaveData[t_FLength+m] = GoosePacketStruct.m_GoosePdu.m_GoID.at(m);
	}
	t_FLength+=l;


	l = GoosePacketStruct.m_GoosePdu.m_TimeStamp.size();
	for (int m=0;m<l;m++)
	{
		t_SaveData[t_FLength+m] = GoosePacketStruct.m_GoosePdu.m_TimeStamp.at(m);
	}
	int t_iUTCPos = t_FLength+2;
	t_FLength+=l;

	l = GoosePacketStruct.m_GoosePdu.m_StNum.size();
	for (int m=0;m<l;m++)
	{
		t_SaveData[t_FLength+m] = GoosePacketStruct.m_GoosePdu.m_StNum.at(m);
	}
	t_FLength+=l;

	l = GoosePacketStruct.m_GoosePdu.m_SqNum.size();
	for (int m = 0; m < l; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_SqNum.at(m);
	}
	t_FLength += l;

	t_GOOSE.nTestModePos = t_FLength+2;
	l = GoosePacketStruct.m_GoosePdu.m_TestMode.size();
	for (int m = 0; m < l; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_TestMode.at(m);
	}
	t_FLength += l;

	l = GoosePacketStruct.m_GoosePdu.m_ConfRev.size();
	for (int m = 0; m < l; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_ConfRev.at(m);
	}
	t_FLength += l;

	l = GoosePacketStruct.m_GoosePdu.m_NdsCom.size();
	for (int m = 0; m < l; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_NdsCom.at(m);
	}
	t_FLength += l;


	l = GoosePacketStruct.m_GoosePdu.m_EntriesNum.size();
	for (int m = 0; m < l; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_EntriesNum.at(m);
	}
	t_FLength += l;

	l = GoosePacketStruct.m_GoosePdu.m_DataSetList.size();
	int t_iGooseDataPos;
	if (nDataSetLen>=0x80 && nDataSetLen<=0xFF)
	{
		t_iGooseDataPos = t_FLength + 3;//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý¼ï¿½
	}
	else if(nDataSetLen > 0xFF)
	{
		t_iGooseDataPos = t_FLength + 4;
	}
	else if(nDataSetLen < 0x80)
	{
		t_iGooseDataPos = t_FLength + 2;
	}

	t_GOOSE.nDataSetPos = t_iGooseDataPos;
	//   qDebug()<<"gooseDataPos"<<t_iGooseDataPos<<l<<t_FLength<<nDataSetLen;
	//oSendItem.m_nDataSetBeginPos = t_iGooseDataPos;

	for (int m = 0; m < l; m++)
	{
		t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_DataSetList.at(m);
	}
	t_FLength += l;

	QByteArray & t_WaitToSendStructArray = oAr;
	//
	QString t_strAll = QString::number(t_FLength,16);
	QString t_UTCPos;
	t_UTCPos = QString("%1").arg(t_iUTCPos,2,16,QChar('0'));
	t_UTCPos = Get0String(4-t_UTCPos.length())+t_UTCPos;
	AddLongStrToByte(Get0String(4-t_strAll.length())+t_strAll,t_WaitToSendStructArray,2);//All
	AddLongStrToByte(t_UTCPos,t_WaitToSendStructArray,2);//UTCPos
	for(int m=0;m<t_FLength;m++)
	{
		t_WaitToSendStructArray.push_back(t_SaveData[m]);
	}
	t_GOOSE.nUTCPos=t_iUTCPos;
	t_GOOSE.nDataSetPos += 4;
	t_GOOSE.nTestModePos += 4;
}

void InitChan(ChanelInfo &chaninfo,CIecCfgGoutCh *ch)
{
	chaninfo.firstvalue=ch->m_strDefaultValue;
	chaninfo.data_type=ch->m_strDataType;
	chaninfo.nBiIndex=0;
	chaninfo.nBiPos=0;
	chaninfo.nBOIndex=0;
	chaninfo.nBoPos=0;
	chaninfo.nLen=0;
	chaninfo.nPos=0;
	chaninfo.bHasUTC=0;
	chaninfo.nUTCPos=0;
	chaninfo.nTrueValue=0;
	chaninfo.nFalseVlaue=0;
}

unsigned short CalCRC(QString appid,QString dest_mac,int port)
{
	QString type="aa2";
	type+=QString::number(port,16);//aa1*-SV,aa2*-goose,aa3*-ft3,½ÓÊÕ¹â¿ÚÐòºÅ£º0-15£¬Ê¾ÀýÎª¹â¿Ú3ÊÕSV

	unsigned char data[10];
	bool ok;
	data[0]=dest_mac.mid(0,2).toInt(&ok,16);
	data[1]=dest_mac.mid(2,2).toInt(&ok,16);
	data[2]=dest_mac.mid(4,2).toInt(&ok,16);
	data[3]=dest_mac.mid(6,2).toInt(&ok,16);
	data[4]=dest_mac.mid(8,2).toInt(&ok,16);
	data[5]=dest_mac.mid(10,2).toInt(&ok,16);

	data[6]=type.mid(0,2).toInt(&ok,16);
	data[7]=type.mid(2,2).toInt(&ok,16);

	data[8]=appid.mid(0,2).toInt(&ok,16);
	data[9]=appid.mid(2,2).toInt(&ok,16);

	unsigned int datalen=10;

	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x3D65;
	unsigned char wChar = 0;

	for(int i=0;i<datalen;i++)
	{
		wChar = data[i];
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}

	return wCRCin;
}

void CIEC61850CfgMngr::InitPara()
{
	memset(stMaps,0,sizeof(structGSOutMap));
	memset(gsesub,0,sizeof(GooseSubData));
	gsesub->nPort=4;

	int nsvcount = m_oIecCfgDatasMngr->GetSMVCount();
	int ngincount = m_oIecCfgDatasMngr->GetGINCount();
	gsesub->ncount=ngincount;
	int ngoutcount=m_oIecCfgDatasMngr->GetGOUTCount();

	int sv_use=m_oIecCfgDatasMngr->GetSmvMngr()->m_nDatasUse;
	if(sv_use==0)
		nsvcount=0;
	int gseout_use=m_oIecCfgDatasMngr->GetGoutMngr()->m_nDatasUse;
	if(gseout_use==0)
		ngoutcount=0;

	long ntype=m_oIecCfgDatasMngr->GetSmvType();
	data_92.clear();
	data_gseout.clear();

	int group=1;

	if(ntype==SMVTYPE_92&&nsvcount!=0)
	{
		int sample=nSample;
		//confsv->data0=CSttDevice::g_pSttDevice->m_nDrv_DIGITALBoard.pos[0];//module
		//confsv->data0=g_theDeviceSystemParameter->m_oModules_D[0]->m_oModuleAttr.m_nModuleIndex;
#ifdef _AT02D_
	   confsv->data0=1<<(4-1);//Î»ÖÃ4
#else
	   confsv->data0=1;
#endif
		unsigned short nT = 10000000/sample;
		confsv->data4=sample<<16|nT;
		//		pSendConfSV->data5|=(4000&0xffff)<<16;
		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(SvCtrlCfg,(char*)confsv,sizeof(SendConfSV));

		for(int index=0;index<nsvcount;index++)
		{
			CIecCfg92Data *smv_data=(CIecCfg92Data *)m_oIecCfgDatasMngr->GetSmvCfgData(index);
			tmt_sv_92 m_tmt_sv_92;
			m_tmt_sv_92.port=smv_data->m_nFiberIndex;
			m_tmt_sv_92.group=group;
			m_tmt_sv_92.m_AppID=QString::number(smv_data->m_dwAppID,16);
			m_tmt_sv_92.m_ASDUNum=QString::number(smv_data->m_nAsduNum);
			m_tmt_sv_92.m_ChanNum=QString::number(smv_data->m_nChannelNum);
			m_tmt_sv_92.m_ConfRev=QString::number(smv_data->m_dwVersion);
			m_tmt_sv_92.m_DelayTimeValue=QString::number(smv_data->m_nDelay);
			m_tmt_sv_92.m_MacDesc=smv_data->m_strDestAddress.replace("-","");
			m_tmt_sv_92.m_MacSrc=smv_data->m_strSrcAddress.replace("-","");
			m_tmt_sv_92.m_SmpCnt="0";
			m_tmt_sv_92.m_SmpRate=QString::number(smv_data->m_nSampleRate);
			m_tmt_sv_92.m_SVID=smv_data->m_strSVID;
			m_tmt_sv_92.m_SyncMode=QString::number(smv_data->m_nSyn);
			m_tmt_sv_92.m_VLanID=QString::number(smv_data->m_dwVID);
			m_tmt_sv_92.m_VLanPri=QString::number(smv_data->m_nPriority);
			m_tmt_sv_92.m_NetType="88BA";
			m_tmt_sv_92.m_Datset=smv_data->m_strDataSet;
			m_tmt_sv_92.nreserved1=0;
			m_tmt_sv_92.nreserved2=0;
			m_tmt_sv_92.m_bSecurity=false;
			m_tmt_sv_92.m_bDatset=false;
			m_tmt_sv_92.m_bRefrTm=false;
			m_tmt_sv_92.m_bSmpRate=false;

			int chan_count=smv_data->m_nChannelNum;
			for(int chanid=0;chanid<chan_count;chanid++)
			{
				CIecCfg92Ch * m_pCIecCfg92Ch=(CIecCfg92Ch *)smv_data->m_pCfgChs->GetAtIndex(chanid);

				QString m_strHighQuality=QString("%1").arg(m_pCIecCfg92Ch->m_nQuality,4,16,QChar('0'));
				QString m_strLowQuality="0000";
				QString chanstr=m_pCIecCfg92Ch->m_strAppChID;
				int t_ChanID = CIEC61850CfgMngr::g_pIEC61850CfgMngr->m_ChanMapID[chanstr];
				BYTE t_ID = static_cast<BYTE>(t_ChanID);
				m_tmt_sv_92.m_ChanValueList.append(t_ID);
				m_tmt_sv_92.m_FactorList.append(m_strHighQuality+m_strLowQuality);
			}
			data_92.append(m_tmt_sv_92);
			group++;
		}
	}


	group=1;
	for(int index=0;index<ngoutcount;index++)
	{
		CIecCfgGooseDataBase *gseout_data=(CIecCfgGooseDataBase *)m_oIecCfgDatasMngr->GetGoutCfgData(index);
		tmt_goose m_tmt_goose;
		m_tmt_goose.port=gseout_data->m_nFiberIndex;
		m_tmt_goose.group=group;
		m_tmt_goose.m_AppID=QString::number(gseout_data->m_dwAppID,16);
		m_tmt_goose.m_MacDesc=gseout_data->m_strDestAddress.replace("-","");
		m_tmt_goose.m_MacSrc=gseout_data->m_strSrcAddress.replace("-","");
		m_tmt_goose.m_VLanID=QString::number(gseout_data->m_dwVLandID);
		m_tmt_goose.m_VLanPri=QString::number(gseout_data->m_dwVLandPriority);
		m_tmt_goose.m_NetType="88B8";
		m_tmt_goose.m_GcRef=gseout_data->m_strgocbRef;
		m_tmt_goose.m_TTL=QString::number(gseout_data->m_nLiveTime);
		m_tmt_goose.m_DataSetRef=gseout_data->m_strDataSet;
		m_tmt_goose.m_GoID=gseout_data->m_strGooseId;
		m_tmt_goose.m_NdsCom=QString::number(gseout_data->m_bNdsCom);
		m_tmt_goose.m_ConfRev=QString::number(gseout_data->m_dwVersion);
		m_tmt_goose.m_TestMode=QString::number(gseout_data->m_bTest);
		m_tmt_goose.m_StNum="00000001";
		m_tmt_goose.m_SqNum="00000001";
		m_tmt_goose.nreserved1=0;
		m_tmt_goose.nreserved2=0;
		bool ok;
		m_tmt_goose.ntimequality =(BYTE)(gseout_data->m_strTQuality.toInt(&ok,16)&0xff);

		m_tmt_goose.nDataSetPos=0;
		m_tmt_goose.nTestModePos=0;
		m_tmt_goose.m_DataSetList.clear();
		m_tmt_goose.m_ChanNum=gseout_data->m_nChannelNum;

		for(int chanid=0;chanid<m_tmt_goose.m_ChanNum;chanid++)
		{
			CIecCfgGoutCh *ch=(CIecCfgGoutCh *)gseout_data->m_pCfgChs->GetAtIndex(chanid);
			ChanelInfo chaninfo;
			InitChan(chaninfo,ch);
			chaninfo.nPos = m_tmt_goose.m_DataSetList.size();

			QByteArray chanbytes;
			CIEC61850CfgMngr::g_pIEC61850CfgMngr->CreateGooseDataSetList(chanbytes,chaninfo,m_tmt_goose.ntimequality);
			m_tmt_goose.m_DataSetList.append(chanbytes);
			chaninfo.nLen = chanbytes.size();

			if(chaninfo.bHasUTC)
			{
				chaninfo.nUTCPos = m_tmt_goose.m_DataSetList.size()+2;//struct:+5
			}

			QString m_strMap=ch->m_strAppChID;
			if(QString::compare(m_strMap,"UTCTime")==0)
			{
				int count=m_tmt_goose.vChanelInfo.count();
				if(count>0)
				{
					ChanelInfo &last_chaninfo=m_tmt_goose.vChanelInfo[count-1];
					last_chaninfo.bHasUTC=1;
				}
			}
			else if(m_strMap.length()>4)
			{
				if(m_strMap.contains("boutex"))
				{
					chaninfo.nBOIndex=m_strMap.replace("boutex","").toInt()+8;
				}
				else if(QString::compare(m_strMap.left(4),"bout")==0)
				{
					chaninfo.nBOIndex=m_strMap.mid(4,m_strMap.length()-4).toInt();
				}
			}

			m_tmt_goose.vChanelInfo.append(chaninfo);
		}
		data_gseout.append(m_tmt_goose);
		group++;

		//confgse->data0=CSttDevice::g_pSttDevice->m_nDrv_DIGITALBoard.pos[0];
		//confgse->data0=g_theDeviceSystemParameter->m_oModules_D[0]->m_oModuleAttr.m_nModuleIndex;
#ifdef _AT02D_
	   confgse->data0=1<<(4-1);//Î»ÖÃ4
#else
	   confgse->data0=1;
#endif

		confgse->data4=gseout_data->m_nT0*50000;
		confgse->data5=gseout_data->m_nT1*50000;
		confgse->data6=gseout_data->m_nT2*50000;
		confgse->data7=gseout_data->m_nT3*50000;

		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(GseCtrlCfg,(char*)confgse,sizeof(SendConfGSE));

	}

	int ngsesubIndex=0;
	for(int index=0;index<ngincount;index++)
	{
		CIecCfgGooseDataBase *gsein_data=(CIecCfgGooseDataBase *)m_oIecCfgDatasMngr->GetGinCfgData(index);

		if(gsein_data->m_nUseFlag==0)
			continue;

		QString m_AppID=QString("%1").arg(gsein_data->m_dwAppID,4,16,QChar('0'));
		QString m_MacDesc=gsein_data->m_strDestAddress.replace("-","");

		gsesub->gooseSub[ngsesubIndex].CRC=CalCRC(m_AppID,m_MacDesc,gsein_data->m_nFiberIndex);

		unsigned long nLastByte,nTrueValue,nFalseValue;

		gsesub->gooseSub[ngsesubIndex].count=0;
		for(int chanid=0;chanid<gsein_data->m_nChannelNum;chanid++)
		{
			CIecCfgGoutCh *ch=(CIecCfgGoutCh *)gsein_data->m_pCfgChs->GetAtIndex(chanid);
			QString m_strBiMap=ch->m_strAppChID;

			QStringList binlist=m_strBiMap.split(";");
			if(binlist.count()<2)
				continue;

			GetGooseDataPosAndValue(gsein_data,chanid,nLastByte,nTrueValue,nFalseValue);

			int nBiIndex=0;
			foreach(QString strbin,binlist)
			{
				if(strbin.contains("binex"))
				{
					nBiIndex=strbin.replace("binex","").toInt();
					if(nBiIndex<=64)
					{
						gsesub->gooseSub[ngsesubIndex].val[gsesub->gooseSub[ngsesubIndex].count].mdPos=1;
					}
					else
					{
						nBiIndex-=64;
						if(nBiIndex<=64)
						{
							gsesub->gooseSub[ngsesubIndex].val[gsesub->gooseSub[ngsesubIndex].count].mdPos=2;
						}
						else
						{
							nBiIndex-=64;
							if(nBiIndex<=64)
							{
								gsesub->gooseSub[ngsesubIndex].val[gsesub->gooseSub[ngsesubIndex].count].mdPos=3;
							}
							else
							{
								nBiIndex-=64;
								if(nBiIndex<=64)
								{
									gsesub->gooseSub[ngsesubIndex].val[gsesub->gooseSub[ngsesubIndex].count].mdPos=4;
								}
								else
									continue;
							}
						}
					}
				}
				else if(strbin.contains("bin"))
				{
					nBiIndex=strbin.replace("bin","").toInt();
					gsesub->gooseSub[ngsesubIndex].val[gsesub->gooseSub[ngsesubIndex].count].mdPos=0;
				}
				else
					continue;

				gsesub->gooseSub[ngsesubIndex].val[gsesub->gooseSub[ngsesubIndex].count].pos = nLastByte;
				gsesub->gooseSub[ngsesubIndex].val[gsesub->gooseSub[ngsesubIndex].count].falseValue = nFalseValue;
				gsesub->gooseSub[ngsesubIndex].val[gsesub->gooseSub[ngsesubIndex].count].trueValue = nTrueValue;
				gsesub->gooseSub[ngsesubIndex].val[gsesub->gooseSub[ngsesubIndex].count].index=nBiIndex-1;

				gsesub->gooseSub[ngsesubIndex].count++;
			}
		}
		ngsesubIndex++;
	}
	CSttDeviceBase::g_pSttDeviceBase->SetGooseSub((char*)gsesub,sizeof(GooseSubData));
}

void CIEC61850CfgMngr::GetGooseDataPosAndValue(CIecCfgGooseDataBase *gsein_data,int nIndex,unsigned long& nlastByte,unsigned long& nTrueValue,unsigned long& nFalseValue)
{
	QByteArray t_DataArray;
	int nDecount = 0;

	int nSize = gsein_data->m_nChannelNum;
	for(int i=0;i<nSize;i++)
	{
		if(i<nIndex)
		{
			continue;
		}

		CIecCfgGoutCh *ch=(CIecCfgGoutCh *)gsein_data->m_pCfgChs->GetAtIndex(i);
		EncoDerGooseDataAtom(t_DataArray,ch);

		if(i == nIndex)
		{
			if(QString::compare(ch->m_strDataType,"BOOLEAN")==0)
			{
				nTrueValue = 1;
				nFalseValue = 0;
				nDecount = 2;
				continue;
			}

			if(QString::compare(ch->m_strDataType,"VisString64")==0)
			{
				nDecount = 3;
				nTrueValue = 0x80;
				nFalseValue = 0x40;
				continue;
			}

			if(QString::compare(ch->m_strDataType,"Dbpos")==0)
			{
				nDecount = 3;
				nTrueValue = 0x80;
				nFalseValue = 0x40;
				continue;
			}
		}
	}

	nlastByte = t_DataArray.size() - nDecount - 1;
}


void CIEC61850CfgMngr::EncoDerGooseDataAtom(QByteArray& oAr, CIecCfgGoutCh *ch)
{
	if(QString::compare(ch->m_strDataType,"BOOLEAN")==0)
	{
		char value=0x01;
		if(QString::compare(ch->m_strDefaultValue,"FALSE")==0)
		{
			value=0x00;
		}
		oAr.push_back(0x83);
		oAr.push_back(0x01);
		oAr.push_back(value);
		return;
	}

	if(QString::compare(ch->m_strDataType,"Dbpos")==0)
	{
		//2bits
		bool ok;
		unsigned char value =ch->m_strDefaultValue.toInt(&ok,2)&0xff;
		oAr.push_back(0x84);
		unsigned char Zl= 2;//ï¿½ï¿½ï¿½ï¿½
		oAr.push_back(Zl);
		//ï¿½î³¤
		int CL = 6;
		oAr.push_back(CL);
		oAr.push_back(value<<CL);

		return;
	}

	if(QString::compare(ch->m_strDataType,"VisString64")==0||QString::compare(ch->m_strDataType,"Quality")==0)
	{
		//13bits
		bool ok;
		short value=ch->m_strDefaultValue.toShort(&ok,2);//= pAtom->vuint();
		oAr.push_back(0x84);
		unsigned char Zl= 3;//ï¿½ï¿½ï¿½ï¿½
		oAr.push_back(Zl);
		//ï¿½î³¤
		int CL = 3;
		oAr.push_back(CL);
		value = value<<CL;

		oAr.append(value>>8);
		oAr.append(value&0xff);
		return;
	}

	if(QString::compare(ch->m_strDataType,"INT32")==0)
	{
		int value = ch->m_strDefaultValue.toInt();
		oAr.push_back(0x85);
		oAr.push_back(4);
		oAr.push_back((unsigned char)(value>>24));
		oAr.push_back((unsigned char)(value>>16));

		oAr.push_back((unsigned char)(value>>8));
		oAr.push_back((unsigned char)(value));
		return;
	}

	if(QString::compare(ch->m_strDataType,"INT32U")==0)
	{
		unsigned int value = ch->m_strDefaultValue.toUInt();
		oAr.push_back(0x85);
		oAr.push_back(4);
		oAr.push_back((unsigned char)(value>>24));
		oAr.push_back((unsigned char)(value>>16));
		oAr.push_back((unsigned char)(value>>8));
		oAr.push_back((unsigned char)(value));
		return;
	}

	if(QString::compare(ch->m_strDataType,"FLOAT32")==0)
	{
		float value = ch->m_strDefaultValue.toFloat();

		ConverStruct t_s;//ï¿½ï¿½ï¿½Ã¹ï¿½ï¿½ï¿½ï¿½ï¿½×ª
		t_s.f = value;
		oAr.push_back(0x87);
		oAr.push_back(0x05);
		oAr.push_back(0x08);
		oAr.push_back(t_s.b[3]);
		oAr.push_back(t_s.b[2]);
		oAr.push_back(t_s.b[1]);
		oAr.push_back(t_s.b[0]);
		return;
	}

	if(QString::compare(ch->m_strDataType,"Timestamp")==0)
	{
		BYTE t_V = 0x00;
		long nSecond=0;
		long nNS = 0;
		//CSttDeviceBase::g_pSttDeviceBase->GetUTCTime(nSecond,nNS);

		int t_HexTime = nSecond;

		QString t_strHexTime("%1");
		t_strHexTime = t_strHexTime.arg(t_HexTime, 2, 16, QChar('0'));
		t_strHexTime = Get0String(8 - t_strHexTime.length()) + t_strHexTime;
		oAr.push_back(0x91);
		oAr.push_back(0x08);
		oAr.push_back(GetIntegerFromString(t_strHexTime.mid(0, 2)));
		oAr.push_back(GetIntegerFromString(t_strHexTime.mid(2, 2)));
		oAr.push_back(GetIntegerFromString(t_strHexTime.mid(4, 2)));
		oAr.push_back(GetIntegerFromString(t_strHexTime.mid(6, 2)));
		oAr.push_back(t_V);
		oAr.push_back(t_V);
		oAr.push_back(t_V);
		oAr.push_back(0x01);
		return;
	}

	if(QString::compare(ch->m_strDataType,"STRUCT")==0)
	{
		//		QByteArray ot;
		//		int nSize = pAtom->vstru_size();
		//		for(int j=0;j<nSize;j++)
		//		{
		//			 hqyGooseCommon::DataAtom* pA = pAtom->mutable_vstru(j);
		//			EncoDerGooseDataAtom(ot,pA);
		//		}

		//		oAr.push_back(0xA2);
		//		oAr.push_back(ot.size());
		//		oAr.append(ot);
	}
}


void CIEC61850CfgMngr::SetPara()
{
	memset(m_pIECConfig,0,sizeof(StructIECConfig));
	memset(m_pIECFiberInfo,0,sizeof(IECFiberInfo));

	QByteArray ba;
	//m_pIECConfig->moduleCount=CSttDevice::g_pSttDevice->m_nDrv_DIGITALBoard.m_nDIGITALModuleCount;
	//m_pIECConfig->moduleCount=g_theDeviceSystemParameter->m_nModuleCount_D;
	m_pIECConfig->moduleCount=1;

	for(int i=0;i<m_pIECConfig->moduleCount;i++)
	{
		//m_pIECConfig->item[i].module=CSttDevice::g_pSttDevice->m_nDrv_DIGITALBoard.pos[i];
		//m_pIECConfig->item[i].module=g_theDeviceSystemParameter->m_oModules_D[i]->m_oModuleAttr.m_nModuleIndex;;
		m_pIECConfig->item[i].module=1;
	}

#ifdef _AT02D_
	   m_pIECConfig->item[0].module=1<<(4-1);//Î»ÖÃ4
#else
	   m_pIECConfig->item[0].module=1;
#endif

	for(int index=0;index<data_92.count();index++)
	{
		ba.clear();
		tmt_sv_92 m_tmt_sv_92 = data_92.at(index);
		int nIecPort=m_tmt_sv_92.port;
		int nBoard=nIecPort/8;
		if(nBoard>DIGITAL_MODULE_MAX-1)
			continue;
		nBoard=0;
		Create92Packet(m_tmt_sv_92,ba,"",0);
		if(ba.size()>1536)
			continue;

		if(m_pIECConfig->item[nBoard].smvCount==8)
			continue;

		m_pIECConfig->item[nBoard].sv[m_pIECConfig->item[nBoard].smvCount].count=ba.size();
		//m_pIECConfig->item[nBoard].sv[m_pIECConfig->item[nBoard].smvCount].group=m_pIECConfig->item[nBoard].smvCount+1;
		m_pIECConfig->item[nBoard].sv[m_pIECConfig->item[nBoard].smvCount].group=1<<(m_tmt_sv_92.group-1);
		memcpy(m_pIECConfig->item[nBoard].sv[m_pIECConfig->item[nBoard].smvCount].dat,ba.constData(),ba.size());

		//		m_pIECFiberInfo->item[nBoard].sv[m_pIECConfig->item[nBoard].smvCount].group=\
		//				m_pIECConfig->item[nBoard].sv[m_pIECConfig->item[nBoard].smvCount].group;
		m_pIECFiberInfo->item[nBoard].sv[m_pIECConfig->item[nBoard].smvCount].group=m_tmt_sv_92.group;
		m_pIECFiberInfo->item[nBoard].sv[m_pIECConfig->item[nBoard].smvCount].port=\
				nIecPort%8;
		m_pIECConfig->item[nBoard].smvCount++;
	}

	for(int index=0;index<data_gseout.count();index++)
	{
		ba.clear();
		tmt_goose &m_tmt_goose=data_gseout[index];
		int nIecPort=m_tmt_goose.port;
		int nBoard=nIecPort/8;
		if(nBoard>DIGITAL_MODULE_MAX-1)
			continue;
		nBoard=0;
		CreateGooseData(ba,m_tmt_goose);
		if(ba.size()>1536)
			continue;

		if(m_pIECConfig->item[nBoard].gsCount==16)
			continue;

		m_pIECConfig->item[nBoard].gs[m_pIECConfig->item[nBoard].gsCount].count=ba.size();
		//m_pIECConfig->item[nBoard].gs[m_pIECConfig->item[nBoard].gsCount].group=m_pIECConfig->item[nBoard].gsCount+1;
		m_pIECConfig->item[nBoard].gs[m_pIECConfig->item[nBoard].gsCount].group=1<<(m_tmt_goose.group-1);
		memcpy(m_pIECConfig->item[nBoard].gs[m_pIECConfig->item[nBoard].gsCount].dat,ba.constData(),ba.size());
		//		m_pIECFiberInfo->item[nBoard].gs[m_pIECConfig->item[nBoard].gsCount].group=\
		//				m_pIECConfig->item[nBoard].gs[m_pIECConfig->item[nBoard].gsCount].group;
		m_pIECFiberInfo->item[nBoard].gs[m_pIECConfig->item[nBoard].gsCount].group=m_tmt_goose.group;
		m_pIECFiberInfo->item[nBoard].gs[m_pIECConfig->item[nBoard].gsCount].port=\
				nIecPort%8;
		//m_tmt_goose.group=m_pIECConfig->item[nBoard].gs[m_pIECConfig->item[nBoard].gsCount].group;
		m_pIECConfig->item[nBoard].gsCount++;
	}

	FiberOpen();

	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(IECDataCfg,(char*)m_pIECConfig,sizeof(StructIECConfig));

	InitBoMap();
}

void CIEC61850CfgMngr::GseChange(int chan,QString value)
{
	//	goosechange->moduleCount=1;

	//	goosechange->items[0].module=1;
	//	goosechange->items[0].groupCount=1;

	//	goosechange->items[0].dat[0].group=1;
	//	goosechange->items[0].dat[0].count=1;

	//	int num=gsedata.m_ChanItemVector[chan].length;
	//	goosechange->items[0].dat[0].dat[0].count=num;
	//	goosechange->items[0].dat[0].dat[0].pos=gsedata.m_ChanItemVector[chan].Pos;
	//	for(int i=0;i<num;i++)
	//	{
	//		bool ok;
	//		goosechange->items[0].dat[0].dat[0].dat[i]=(value.mid(i*2,2).toUInt(&ok,16))&0xff;
	//	}

	//	CSttDriverOper::setGooseChangedCoderData((char*)goosechange,sizeof(GooseChangedItems));
}

void CIEC61850CfgMngr::SetTestMode(bool Mode)
{
	//	stGseTest->cnt=1;
	//	stGseTest->dat[0].module=1;
	//	stGseTest->dat[0].cnt=1;
	//	stGseTest->dat[0].gs[0].group=1;
	//	stGseTest->dat[0].gs[0].pos=gsedata.testmode_pos;
	//	stGseTest->dat[0].gs[0].value=Mode?1:0;

	//	CSttDriverOper::setGooseTestMode(stGseTest,sizeof(StructGSTest));
}

void CIEC61850CfgMngr::InitBoMap()
{
	memset(stMaps,0,sizeof(structGSOutMap));

	for(int i=0;i<data_gseout.count();i++)
	{
		tmt_goose otmt_goose=data_gseout[i];
		for(int chan=0;chan<otmt_goose.vChanelInfo.count();chan++)
		{
			ChanelInfo oChanelInfo=otmt_goose.vChanelInfo[chan];
			if(oChanelInfo.nBOIndex>0)
			{
				if(oChanelInfo.nBOIndex<9)
				{
					int index=stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].cnt;
					if(index==16)
						continue;

					stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].stMap[index].group=1<<(otmt_goose.group-1);
					//stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].stMap[index].module=CSttDevice::g_pSttDevice->m_nDrv_DIGITALBoard.pos[0];
					//stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].stMap[index].module=g_theDeviceSystemParameter->m_oModules_D[0]->m_oModuleAttr.m_nModuleIndex;
#ifdef _AT02D_
	   stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].stMap[index].module=1<<(4-1);//Î»ÖÃ4
#else
	   stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].stMap[index].module=1;
#endif

					stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].stMap[index].falseValue=oChanelInfo.nFalseVlaue;
					stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].stMap[index].trueValue=oChanelInfo.nTrueValue;
					stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].stMap[index].hasUTC=0;
					stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].stMap[index].pos=otmt_goose.nDataSetPos+oChanelInfo.nBoPos;
					stMaps->boMd[0].info[0][oChanelInfo.nBOIndex-1].cnt++;
				}
				else
				{
					//À©Õ¹¿ª¹ØÁ¿°å

					int nBoIndex=oChanelInfo.nBOIndex-9;
					int nFlag=0;
					if(nBoIndex>31)
						nFlag=1;

					int index=stMaps->boMd[0].info[nFlag][nBoIndex-nFlag*32].cnt;

					stMaps->boMd[0].info[nFlag][nBoIndex-nFlag*32].stMap[index].group=1<<(otmt_goose.group-1);
					//stMaps->boMd[0].info[nFlag][nBoIndex-nFlag*32].stMap[index].module=g_theDeviceSystemParameter->m_oModules_D[0]->m_oModuleAttr.m_nModuleIndex;
#ifdef _AT02D_
	   stMaps->boMd[0].info[nFlag][nBoIndex-nFlag*32].stMap[index].module=1<<(4-1);//Î»ÖÃ4
#else
	   stMaps->boMd[0].info[nFlag][nBoIndex-nFlag*32].stMap[index].module=1;
#endif

					stMaps->boMd[0].info[nFlag][nBoIndex-nFlag*32].stMap[index].falseValue=oChanelInfo.nFalseVlaue;
					stMaps->boMd[0].info[nFlag][nBoIndex-nFlag*32].stMap[index].trueValue=oChanelInfo.nTrueValue;
					stMaps->boMd[0].info[nFlag][nBoIndex-nFlag*32].stMap[index].hasUTC=0;
					stMaps->boMd[0].info[nFlag][nBoIndex-nFlag*32].stMap[index].pos=otmt_goose.nDataSetPos+oChanelInfo.nBoPos;
					stMaps->boMd[0].info[nFlag][nBoIndex-nFlag*32].cnt++;
				}
			}
		}
	}

	CSttDriverOper::setGooseBoMapData((char*)stMaps,sizeof(structGSOutMap));
}

void CIEC61850CfgMngr::InitGooseSub()
{
	memset(gsesub,0,sizeof(GooseSubData));

	CSttDeviceBase::g_pSttDeviceBase->SetGooseSub((char*)gsesub,sizeof(GooseSubData));
}

/***
void CIEC61850CfgMngr::InitGooseSubMap()
{
	m_mapGooseSubMap.clear();
	int nSize = d_Data->mutable_ogoosesub()->block_size();
	unsigned long nLastByte,nTrueValue,nFalseValue;
	m_nGooseSubPort = 0;
	for(int i=0;i<nSize;i++)
	{
		hqyGoose_Sub_Setting::Control_Block* pBlock = d_Data->mutable_ogoosesub()->mutable_block(i);
		GooseSubItem oGooseItem;
		memset(&oGooseItem,0,sizeof(GooseSubItem));
		oGooseItem.paramAdvance = pBlock->nogocb()?0:1;
		oGooseItem.testMode = pBlock->testflag()?1:0;
		oGooseItem.gocbLen = pBlock->gocbref().size();
		memcpy(oGooseItem.GOCB,pBlock->gocbref().data(),oGooseItem.gocbLen);
		oGooseItem.dataSetLen = pBlock->dataset().size();
		memcpy(oGooseItem.dataSet,pBlock->dataset().data(),oGooseItem.dataSetLen);
		oGooseItem.goidLen = pBlock->goid().size();
		memcpy(oGooseItem.GOID,pBlock->goid().data(),oGooseItem.goidLen);


		QString strMac = QString::fromStdString(pBlock->destmac());
		strMac = strMac.replace("-","");

		unsigned char szChar[10];
		for(int i=0;i<6;i++)
		{
			QString strChild = strMac.mid(i*2,2);
			bool bok;
			szChar[i] = strChild.toULong(&bok,16);
		}
		szChar[6] = 0xAA;
		short nType = 0x20;// sv0x10;  GOOSE 0x20;  FT3 0x30
		nType += pBlock->port();
		szChar[7] = nType & 0xFF;
		szChar[8] = (pBlock->appid()>>8) & 0xFF;
		szChar[9] = pBlock->appid() & 0xFF;

		int nCrc = GetCheckNum(szChar,10);
		oGooseItem.CRC = nCrc;

		int nChanelSize = pBlock->channel_size();

		int nCount = 0;

		for(int j=0;j<nChanelSize;j++)
		{
			hqyGooseCommon::Channel_Info* pChanel = pBlock->mutable_channel(j);
			QString strMap = QString::fromStdString(pChanel->mutable_data()->mapchannel());
			if(!strMap.isEmpty()&&strMap.indexOf("DBI")!= -1)
			{
				long nIndex = strMap.replace("DBI","").toLong();

				if(nIndex >10)
				{
					oGooseItem.val[nCount].mdPos = 1;
					nIndex = nIndex - 10 + 48;
				}
				else
					oGooseItem.val[nCount].mdPos = 0;

				nIndex -= 1;
				oGooseItem.val[nCount].index = nIndex;

				GetGooseDataPosAndValue(pBlock,j,nLastByte,nTrueValue,nFalseValue);
				oGooseItem.val[nCount].pos = nLastByte;

				oGooseItem.val[nCount].falseValue = nFalseValue;
				oGooseItem.val[nCount].trueValue = nTrueValue;
				oGooseItem.count = nCount+1;
				nCount++;
			}
		}
		m_nGooseSubPort |= 1<<pBlock->port();
		m_mapGooseSubMap.insert(oGooseItem.nCRC,oGooseItem);



 //       GOOSESUBITEM oGooseItem;

//		GOOSESUBITEM oGooseItem;
//		memset(&oGooseItem,0,sizeof(GOOSESUBITEM));
//		oGooseItem.nAPPID = pBlock->appid();

//		oGooseItem.nParsedAdvance = pBlock->nogocb()?0:1;
//		oGooseItem.nParseTestMode = pBlock->testflag()?1:0;
//		QString strMac = QString::fromStdString(pBlock->destmac());
//		strMac = strMac.replace("-","");

//		for(int i=0;i<6;i++)
//		{
//			QString strChild = strMac.mid(i*2,2);
//			bool bok;
//			oGooseItem.nMac[i] = strChild.toULong(&bok,16);
//		}

//		oGooseItem.ngocblen = pBlock->gocbref().size();
//		memcpy(oGooseItem.GoCB,pBlock->gocbref().data(),oGooseItem.ngocblen);
//		oGooseItem.nDataSetlen = pBlock->dataset().size();
//		memcpy(oGooseItem.DataSet,pBlock->dataset().data(),oGooseItem.nDataSetlen);
//		oGooseItem.nGOIDlen = pBlock->goid().size();
//		memcpy(oGooseItem.GOID,pBlock->goid().data(),oGooseItem.nGOIDlen);

//		int nChanelSize = pBlock->channel_size();

//		int nCount = 0;

//		for(int j=0;j<nChanelSize;j++)
//		{
//			hqyGooseCommon::Channel_Info* pChanel = pBlock->mutable_channel(j);
//			QString strMap = QString::fromStdString(pChanel->mutable_data()->mapchannel());
//			if(!strMap.isEmpty()&&strMap.indexOf("DBI")!= -1)
//			{
//				long nIndex = strMap.replace("DBI","").toLong();
//				nIndex -= 1;


//				oGooseItem.oChanel[nCount].nDBIIndex = nIndex;

//				MsgEnCodeOper::g_MsgEnCodeOper->GetGooseDataPosAndValue(pBlock,j,nLastByte,nTrueValue,nFalseValue);
//				oGooseItem.oChanel[nCount].nPos = nLastByte;

//				oGooseItem.oChanel[nCount].nFalseValue = nFalseValue;
//				oGooseItem.oChanel[nCount].nTrueValue = nTrueValue;
//				oGooseItem.ncount = nCount+1;
//				nCount++;
//			}
//		}
//		m_nGooseSubPort |= 1<<pBlock->port();
//		m_mapGooseSubMap.insert(oGooseItem.nAPPID,oGooseItem);

	}
}
***/

void CIEC61850CfgMngr::InitFt3Sub()
{
	//CSttDriverOper::setFT3SubData((char*)ft3sub,sizeof(Ft3SubData));
}

//void CIEC61850CfgMngr::SetGooseValue(tmt_StateParas &oStateParas,int nIndex,drv_state *pDrvState)
//{
//	qDebug()<<"SetGooseValue";
//	pDrvState->GooseChangedItems.nModuleCount=1;
//	pDrvState->GooseChangedItems.datModules[0].module=1;
//	pDrvState->GooseChangedItems.datModules[0].group=data_gseout.count();

//	for(int index=0;index<data_gseout.count();index++)
//	{
//		qDebug()<<"index"<<index;
//		tmt_goose otmt_goose=data_gseout.at(index);

//		bool testmode_old=oStateParas.m_paraState[nIndex-1].m_oGoosePub[index].m_bTest;
//		bool testmode_new=oStateParas.m_paraState[nIndex].m_oGoosePub[index].m_bTest;
//		if(testmode_old!=testmode_new)
//		{
//			pDrvState->GooseTestItems.nCount=1;
//			pDrvState->GooseTestItems.dat[0].module=1;
//			pDrvState->GooseTestItems.dat[0].nCount=1;
//			pDrvState->GooseTestItems.dat[0].gs[index].group=index+1;
//			pDrvState->GooseTestItems.dat[0].gs[index].value=testmode_new;
//			pDrvState->GooseTestItems.dat[0].gs[index].pos=otmt_goose.nTestModePos;
//		}

//		int count=0;
//		//gseout_data->m_nChannelNum
//		for(int chanid=0;chanid<1;chanid++)
//		{
//			ChanelInfo oChanelInfo=otmt_goose.vChanelInfo.at(chanid);
//			QString m_strMap=oChanelInfo.data_type;
//			if(QString::compare(m_strMap,"Timestamp")!=0)
//			{
//				QString chanvalue_old=oStateParas.m_paraState[nIndex-1].m_oGoosePub[index].m_strChannel[chanid];
//				QString chanvalue_new=oStateParas.m_paraState[nIndex].m_oGoosePub[index].m_strChannel[chanid];
//				if(chanvalue_old.compare(chanvalue_new)!=0)
//				{
//					pDrvState->GooseChangedItems.datModules[0].dat[index].nUTCChanelCount=0;
//					pDrvState->GooseChangedItems.datModules[0].dat[index].group=index+1;

//					pDrvState->GooseChangedItems.datModules[0].dat[index].dat[count].nCount=oChanelInfo.nLen;
//					pDrvState->GooseChangedItems.datModules[0].dat[index].dat[count].nPos=otmt_goose.nDataSetPos+oChanelInfo.nPos;

//					oChanelInfo.firstvalue=chanvalue_new;
//					QByteArray ovalue;
//					CreateGooseDataSetList(ovalue,oChanelInfo,0);
//					memcpy(pDrvState->GooseChangedItems.datModules[0].dat[index].dat[count].dat,ovalue,ovalue.size());
//				}
//			}
//			count++;
//		}
//		pDrvState->GooseChangedItems.datModules[0].dat[index].count=count;
//	}

//}
