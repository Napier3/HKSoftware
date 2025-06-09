#include "IEC92Mngr.h"
#include "OSInterface.h"
#include "../../../../SttTest/Common/SttSystemConfig.h"

CIEC92Mngr::CIEC92Mngr(QObject *parent) : QObject(parent)
{
	InitChanelMap();
	Init();
}

CIEC92Mngr::~CIEC92Mngr()
{
}

void CIEC92Mngr::Init()
{
	m_nSample = 4000;

	for(int i = 0; i < MAX_DIGITAL_GROUP_NUM; i++)
	{
		m_nDelayTime[i] = 0;
	}

	data_92.clear();
	data_92Sub.clear();
}

void CIEC92Mngr::InitChanelMap()
{
	m_ChanMapID.clear();
	m_ChanMapID.insert("0", 0);
	m_ChanMapID.insert("t-delay", 33);
	m_ChanMapID.insert("Uz1", 34);
	m_ChanMapID.insert("Ua1", 1);
	m_ChanMapID.insert("Ub1", 2);
	m_ChanMapID.insert("Uc1", 3);
	m_ChanMapID.insert("Ua2", 5);
	m_ChanMapID.insert("Ub2", 6);
	m_ChanMapID.insert("Uc2", 7);
	m_ChanMapID.insert("Ua3", 9);
	m_ChanMapID.insert("Ub3", 10);
	m_ChanMapID.insert("Uc3", 11);
	m_ChanMapID.insert("Ua4", 13);
	m_ChanMapID.insert("Ub4", 14);
	m_ChanMapID.insert("Uc4", 15);
	m_ChanMapID.insert("Ua5", 35);
	m_ChanMapID.insert("Ub5", 36);
	m_ChanMapID.insert("Uc5", 37);
	m_ChanMapID.insert("Ua6", 39);
	m_ChanMapID.insert("Ub6", 40);
	m_ChanMapID.insert("Uc6", 41);
	m_ChanMapID.insert("Ia1", 17);
	m_ChanMapID.insert("Ib1", 18);
	m_ChanMapID.insert("Ic1", 19);
	m_ChanMapID.insert("Ia2", 21);
	m_ChanMapID.insert("Ib2", 22);
	m_ChanMapID.insert("Ic2", 23);
	m_ChanMapID.insert("Ia3", 25);
	m_ChanMapID.insert("Ib3", 26);
	m_ChanMapID.insert("Ic3", 27);
	m_ChanMapID.insert("Ia4", 29);
	m_ChanMapID.insert("Ib4", 30);
	m_ChanMapID.insert("Ic4", 31);
	m_ChanMapID.insert("Ia5", 43);
	m_ChanMapID.insert("Ib5", 44);
	m_ChanMapID.insert("Ic5", 45);
	m_ChanMapID.insert("Ia6", 47);
	m_ChanMapID.insert("Ib6", 48);
	m_ChanMapID.insert("Ic6", 49);

	//以下电气量关联后无需下载幅值相位频率，由FPGA自动计算
	m_ChanMapID.insert("U01",4);
	m_ChanMapID.insert("U02",8);
	m_ChanMapID.insert("U03",12);
	m_ChanMapID.insert("U04",16);
	m_ChanMapID.insert("I01",20);
	m_ChanMapID.insert("I02",24);
	m_ChanMapID.insert("I03",28);
	m_ChanMapID.insert("I04",32);
	m_ChanMapID.insert("U05",38);
	m_ChanMapID.insert("U06",42);
	m_ChanMapID.insert("I05",46);
	m_ChanMapID.insert("I06",50);
}

void CIEC92Mngr::SetChanelMap(QMap<QString, int> oChanMap)
{
	m_ChanMapID.clear();
	m_ChanMapID.insert("0", 0);
	QMap<QString, int>::const_iterator oiterator = oChanMap.constBegin();

	while(oiterator != oChanMap.constEnd())
	{
		m_ChanMapID.insert(oiterator.key(), oiterator.value());
		oiterator++;
	}
}

void CIEC92Mngr::Create92TmtStruct(CIecCfg92Data *pIecData)
{
	if(pIecData->m_nUseFlag == 0)
	{
		return;
	}

	tmt_sv_92 m_tmt_sv_92;
	m_tmt_sv_92.port = pIecData->m_nFiberIndex;
	m_tmt_sv_92.m_AppID = QString::number(pIecData->m_dwAppID, 16);
	m_tmt_sv_92.m_ASDUNum = QString::number(pIecData->m_nAsduNum);
	m_tmt_sv_92.m_ChanNum = QString::number(pIecData->m_nChannelNum);
	m_tmt_sv_92.m_ConfRev = QString::number(pIecData->m_dwVersion);
	m_tmt_sv_92.m_DelayTimeValue = QString::number(pIecData->m_nDelay);
	m_tmt_sv_92.m_MacDesc = pIecData->m_strDestAddress.replace("-", "");
	m_tmt_sv_92.m_MacSrc = pIecData->m_strSrcAddress.replace("-", "");
	m_tmt_sv_92.m_SmpCnt = "0";
	m_tmt_sv_92.m_SmpRate = QString::number(pIecData->m_nSampleRate / g_theSystemConfig->m_fFNom);
	m_nSample = pIecData->m_nSampleRate;
	m_tmt_sv_92.m_SVID = pIecData->m_strSVID;
	m_tmt_sv_92.m_SyncMode = QString::number(pIecData->m_nSyn);
	m_tmt_sv_92.m_VLanID = QString::number(pIecData->m_dwVID);
	m_tmt_sv_92.m_VLanPri = QString::number(pIecData->m_nPriority);
	m_tmt_sv_92.m_NetType = "88BA";
	m_tmt_sv_92.m_Datset = pIecData->m_strDataSet;
	m_tmt_sv_92.nreserved1 = 0;
	m_tmt_sv_92.nreserved2 = 0;
	m_tmt_sv_92.m_bSecurity = pIecData->m_nUseEncrupt;
	m_tmt_sv_92.m_bDatset = pIecData->m_nUseDataSet;
	m_tmt_sv_92.m_bRefrTm = pIecData->m_nUseRefreshTime;
	m_tmt_sv_92.m_bSmpRate = pIecData->m_nUseSampRate;
	int chan_count = pIecData->m_nChannelNum;
	QString strHighQuality = "0000";
	QString strLowQuality;
	QString chanstr;
	BOOL bOk;
	int t_ChanID;
	BYTE t_ID;
	int nDelayGroup;

	for(int chanid = 0; chanid < chan_count; chanid++)
	{
		CIecCfg92Ch *m_pCIecCfg92Ch = (CIecCfg92Ch *)pIecData->m_pCfgChs->GetAtIndex(chanid);
		strLowQuality = QString("%1").arg(m_pCIecCfg92Ch->m_nQuality, 4, 16, QChar('0'));
		chanstr = m_pCIecCfg92Ch->m_strAppChID;

		if(chanstr.contains("t-delay"))
		{
			BOOL bFindUI = FALSE;

			for(int i = 0; i < chan_count; i++)
			{
				CIecCfg92Ch *pCIecCfg92Ch = (CIecCfg92Ch *)pIecData->m_pCfgChs->GetAtIndex(i);
				QString chanstrUI = pCIecCfg92Ch->m_strAppChID;

				if(chanstrUI.contains("U") || chanstrUI.contains("I"))
				{
					nDelayGroup = chanstrUI.right(1).toInt(&bOk, 10);

					if(bOk && nDelayGroup > 0)
					{
						bFindUI = TRUE;
					}

					break;
				}
			}

			if(bFindUI)
			{
				if(nDelayGroup <= MAX_DIGITAL_GROUP_NUM)
				{
					if(m_nDelayTime[nDelayGroup - 1] == 0)
					{
						m_nDelayTime[nDelayGroup - 1] = pIecData->m_nDelay;
					}
				}
			}
		}

		t_ChanID = m_ChanMapID[chanstr];

		if(t_ChanID > 0)
		{
			chanstr = QString("SV[%1] ChanId[%2]   MapId-%3 >> AppChID=%4").arg(data_92.size()).
					  arg(QString("%1").arg(chanid, 3, 10, QChar('0'))).arg(QString("%1").
							  arg(t_ChanID, 2, 10, QChar('0'))).arg(m_ChanMapID.key(t_ChanID));
			qDebug() << chanstr;
		}

		t_ID = static_cast<BYTE>(t_ChanID);
		m_tmt_sv_92.m_ChanValueList.append(t_ID);
		m_tmt_sv_92.m_FactorList.append(strHighQuality + strLowQuality);
	}

	data_92.append(m_tmt_sv_92);
}

void CIEC92Mngr::Create92SubTmtStruct(CIecCfg92InData *pIecData)
{
	if(pIecData->m_nUseFlag == 0)
	{
		return;
	}

	tmt_sv_92 m_tmt_sv_92;
	m_tmt_sv_92.port = pIecData->m_nFiberIndex;
	m_tmt_sv_92.m_AppID = QString::number(pIecData->m_dwAppID, 16);
	m_tmt_sv_92.m_ASDUNum = QString::number(pIecData->m_nAsduNum);
	m_tmt_sv_92.m_ChanNum = QString::number(pIecData->m_nChannelNum);
	m_tmt_sv_92.m_MacDesc = pIecData->m_strDestAddress.replace("-", "");
	m_tmt_sv_92.m_MacSrc = pIecData->m_strSrcAddress.replace("-", "");
	m_tmt_sv_92.m_SVID = pIecData->m_strSVID;
	m_tmt_sv_92.m_Datset = pIecData->m_strDataSet;
	data_92Sub.append(m_tmt_sv_92);
}

void CIEC92Mngr::Create92ByteArray(tmt_sv_92 &m_92Struct, QByteArray &m_ResultArray)
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
	//////////////////////////////////////////////
	int t_ASDUNum = m_92Struct.m_ASDUNum.toInt();
	int t_PDULength = 0;
	int t_ChanNum = m_92Struct.m_ChanNum.toInt();
	int t_OffsetChanValue = 0;

	for(int m = 0; m < t_ASDUNum; m++)
	{
		ASDUStruct *t_ASDU = new ASDUStruct;
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
		QString t_ConfRev;
		bool ok;
		unsigned int nConfRev = m_92Struct.m_ConfRev.toUInt(&ok, 10);
		t_ConfRev = QString("%1").arg(nConfRev, 8, 16, QChar('0'));
		t_ASDU->m_ConRev.push_back(GetIntegerFromString(t_ConfRev.mid(0, 2)));
		t_ASDU->m_ConRev.push_back(GetIntegerFromString(t_ConfRev.mid(2, 2)));
		t_ASDU->m_ConRev.push_back(GetIntegerFromString(t_ConfRev.mid(4, 2)));
		t_ASDU->m_ConRev.push_back(GetIntegerFromString(t_ConfRev.mid(6, 2)));

		//////////////////////refrtm/////////////////////////////////
		if(m_92Struct.m_bRefrTm)
		{
			t_ASDU->m_RefrTm.push_back(0x84);
			t_ASDU->m_RefrTm.push_back(0x06);

			for(int i = 0; i < 6; i++)
			{
				t_ASDU->m_RefrTm.push_back((char)0x0);//需要FPGA将发送时间填入
			}
		}

		//////////////////////SmpSync///////////////////////////////////////
		t_ASDU->m_SmpSynch.push_back(0x85);
		t_ASDU->m_SmpSynch.push_back(0x01);
		AddLongStrToByte(m_92Struct.m_SyncMode, t_ASDU->m_SmpSynch, 1);//SmpSync

		//////////////SmpRate////////////////////////////////////////////////
		if(m_92Struct.m_bSmpRate)
		{
			//每周波采样点数
			qDebug() << "m_SmprRate = " << m_92Struct.m_SmpRate;
			t_ASDU->m_SmpRate.push_back(0x86);
			t_ASDU->m_SmpRate.push_back(0x01);
			unsigned char byte = m_92Struct.m_SmpRate.toInt() & 0xFF;
			t_ASDU->m_SmpRate.push_back(byte);
		}

		/////////////////锟斤拷锟斤拷///////////////////////////////////////////
		t_ASDU->m_StartLength.push_back(0x30);
		int t_AllLength = t_ASDU->m_smvID.size() + t_ASDU->m_ConRev.size() + t_ASDU->m_SequenceData.size() + t_ASDU->m_SmpCnt.size() + t_ASDU->m_SmpSynch.size();
		t_AllLength += t_ASDU->m_RefrTm.size();
		t_AllLength += t_ASDU->m_Datset.size();
		t_AllLength += t_ASDU->m_SmpRate.size();

		////qDebug()<<"t_AllLength 0x30 ="<<t_AllLength;
		if(t_AllLength >= 0x80 && t_AllLength <= 0xFF)
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

		t_PDULength += t_AllLength;
		t_PDULength += t_ASDU->m_StartLength.size();
		m_92PacketStruct.m_PDU.p_ASDUVector.push_back(t_ASDU);
	}

	///////////////////////////PDU锟斤拷锟斤拷///////////////////////////////////////////////
	m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(0xA2);

	if(t_PDULength >= 0x80 && t_PDULength <= 0xFF)
	{
		m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(0x81);
		m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(t_PDULength);
	}
	else
	{
		if(t_PDULength > 0xFF)
		{
			m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(0x82);
			QString t_strPDUL = "";
			t_strPDUL = t_strPDUL.setNum(t_PDULength);
			QString t_HexPL = DecToHex(t_strPDUL);
			t_HexPL = Get0String(4 - t_HexPL.length()) + t_HexPL;
			m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(GetIntegerFromString(t_HexPL.mid(0, 2)));
			m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(GetIntegerFromString(t_HexPL.mid(2, 2)));
		}
		else
		{
			m_92PacketStruct.m_PDU.m_SequenceofASDU.push_back(t_PDULength);
		}
	}

	t_PDULength += m_92PacketStruct.m_PDU.m_SequenceofASDU.size();
	//////////////////////////////Number of ASDU/////////////////////////
	AddASN1StrToByte(m_92Struct.m_ASDUNum, m_92PacketStruct.m_PDU.m_NumOfASDU, 0x80, 1);
	t_PDULength += m_92PacketStruct.m_PDU.m_NumOfASDU.size();

	if(m_92Struct.m_bSecurity)
	{
		m_92PacketStruct.m_PDU.m_Security.push_back(0x81);
		m_92PacketStruct.m_PDU.m_Security.push_back(0x81);
		m_92PacketStruct.m_PDU.m_Security.push_back(0xAD);
	}

	t_PDULength += m_92PacketStruct.m_PDU.m_Security.size();
	//////////////////////////////pdu锟斤拷锟斤拷///////////////////////////////////////
	m_92PacketStruct.m_PDU.m_pduLength.push_back(0x60);

	if(t_PDULength >= 0x80 && t_PDULength <= 0xFF)
	{
		m_92PacketStruct.m_PDU.m_pduLength.push_back(0x81);
		m_92PacketStruct.m_PDU.m_pduLength.push_back(t_PDULength);
	}
	else
	{
		if(t_PDULength > 0xFF)
		{
			m_92PacketStruct.m_PDU.m_pduLength.push_back(0x82);
			QString t_strPDUL = "";
			t_strPDUL = t_strPDUL.setNum(t_PDULength);
			QString t_HexPL = DecToHex(t_strPDUL);
			t_HexPL = Get0String(4 - t_HexPL.length()) + t_HexPL;
			m_92PacketStruct.m_PDU.m_pduLength.push_back(GetIntegerFromString(t_HexPL.mid(0, 2)));
			m_92PacketStruct.m_PDU.m_pduLength.push_back(GetIntegerFromString(t_HexPL.mid(2, 2)));
		}
		else
		{
			m_92PacketStruct.m_PDU.m_pduLength.push_back(t_PDULength);
		}
	}

	t_PDULength += m_92PacketStruct.m_PDU.m_pduLength.size();
	/////////////////////////锟斤拷锟斤拷IEC_SMV92///////////////////////////////////
	int t_ApplicationLength = t_PDULength;
	AddLongStrToByte(m_92Struct.m_AppID, m_92PacketStruct.m_AppID, 2);
	m_92PacketStruct.m_Reserve1.push_back((unsigned char)(m_92Struct.nreserved1 >> 8));
	m_92PacketStruct.m_Reserve1.push_back((unsigned char)(m_92Struct.nreserved1));
	m_92PacketStruct.m_Reserve2.push_back((unsigned char)(m_92Struct.nreserved2 >> 8));
	m_92PacketStruct.m_Reserve2.push_back((unsigned char)(m_92Struct.nreserved2));
	//	AddLongStrToByte("0000", m_92PacketStruct.m_Reserve1, 2);
	//	AddLongStrToByte("0000", m_92PacketStruct.m_Reserve2, 2);
	t_ApplicationLength += 8;
	m_92PacketStruct.m_ApplicationLength.push_back(t_ApplicationLength >> 8 & ~(~0 << 8));
	m_92PacketStruct.m_ApplicationLength.push_back(t_ApplicationLength & ~(~0 << 8));
	/////////////////////////锟斤拷锟斤拷Ethernet///////////////////////////////////
	AddLongStrToByte(m_92Struct.m_MacDesc, m_92PacketStruct.m_DesMac, 4);
	AddLongStrToByte(m_92Struct.m_MacSrc, m_92PacketStruct.m_SrcMac, 4);
	AddLongStrToByte("88BA", m_92PacketStruct.m_Type, 2);
	//////////////////////////////////////////////////////////////////////////
	unsigned char t_SaveData[20000];
	int t_FLength = 0;

	for(int m = 0; m < 6; m++)
	{
		t_SaveData[m] = m_92PacketStruct.m_DesMac.at(m);
	}

	t_FLength += 6;

	for(int m = 0; m < 6; m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_SrcMac.at(m);
	}

	t_FLength += 6;

	for(int m = 0; m < 4; m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_VLan.at(m);
	}

	t_FLength += 4;

	for(int m = 0; m < 2; m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_Type.at(m);
	}

	t_FLength += 2;

	for(int m = 0; m < 2; m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_AppID.at(m);
	}

	t_FLength += 2;

	for(int m = 0; m < 2; m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_ApplicationLength.at(m);
	}

	t_FLength += 2;

	for(int m = 0; m < 2; m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_Reserve1.at(m);
	}

	t_FLength += 2;

	for(int m = 0; m < 2; m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_Reserve2.at(m);
	}

	t_FLength += 2;

	for(int m = 0; m < m_92PacketStruct.m_PDU.m_pduLength.size(); m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_PDU.m_pduLength.at(m);
	}

	t_FLength += m_92PacketStruct.m_PDU.m_pduLength.size();

	for(int m = 0; m < m_92PacketStruct.m_PDU.m_NumOfASDU.size(); m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_PDU.m_NumOfASDU.at(m);
	}

	t_FLength += m_92PacketStruct.m_PDU.m_NumOfASDU.size();

	for(int m = 0; m < m_92PacketStruct.m_PDU.m_Security.size(); m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_PDU.m_Security.at(m);
	}

	t_FLength += m_92PacketStruct.m_PDU.m_Security.size();

	for(int m = 0; m < m_92PacketStruct.m_PDU.m_SequenceofASDU.size(); m++)
	{
		t_SaveData[t_FLength + m] = m_92PacketStruct.m_PDU.m_SequenceofASDU.at(m);
	}

	t_FLength += m_92PacketStruct.m_PDU.m_SequenceofASDU.size();
	int nASDUStartPos = t_FLength;
	int t_SmpCntValePos = 0;
	int t_ChanValuePos = 0;
	int nASDULeng = 0;

	for(int q = 0; q < t_ASDUNum; q++)
	{
		ASDUStruct *pASDU = m_92PacketStruct.m_PDU.p_ASDUVector[q];

		for(int m = 0; m < pASDU->m_StartLength.size(); m++)
		{
			t_SaveData[t_FLength + m] = pASDU->m_StartLength.at(m);
		}

		t_FLength += pASDU->m_StartLength.size();

		for(int m = 0; m < pASDU->m_smvID.size(); m++)
		{
			t_SaveData[t_FLength + m] = pASDU->m_smvID.at(m);
		}

		t_FLength += pASDU->m_smvID.size();

		for(int m = 0; m < pASDU->m_Datset.size(); m++)
		{
			t_SaveData[t_FLength + m] = pASDU->m_Datset.at(m);
		}

		t_FLength += pASDU->m_Datset.size();

		for(int m = 0; m < pASDU->m_SmpCnt.size(); m++)
		{
			t_SaveData[t_FLength + m] = pASDU->m_SmpCnt.at(m);
		}

		t_FLength += pASDU->m_SmpCnt.size();

		if(q == 0)
		{
			t_SmpCntValePos = t_FLength - 2 - nASDUStartPos;
		}

		for(int m = 0; m < pASDU->m_ConRev.size(); m++)
		{
			t_SaveData[t_FLength + m] = pASDU->m_ConRev.at(m);
		}

		t_FLength += pASDU->m_ConRev.size();

		for(int m = 0; m < pASDU->m_RefrTm.size(); m++)
		{
			t_SaveData[t_FLength + m] = pASDU->m_RefrTm.at(m);
		}

		t_FLength += pASDU->m_RefrTm.size();

		for(int m = 0; m < pASDU->m_SmpSynch.size(); m++)
		{
			t_SaveData[t_FLength + m] = pASDU->m_SmpSynch.at(m);
		}

		t_FLength += pASDU->m_SmpSynch.size();

		for(int m = 0; m < pASDU->m_SmpRate.size(); m++)
		{
			t_SaveData[t_FLength + m] = pASDU->m_SmpRate.at(m);
		}

		t_FLength += pASDU->m_SmpRate.size();

		if(q == 0)
		{
			nASDULeng = pASDU->m_SequenceData.size() - t_OffsetChanValue;
			t_ChanValuePos = t_FLength + t_OffsetChanValue - nASDUStartPos;
		}

		for(int m = 0; m < pASDU->m_SequenceData.size(); m++)
		{
			t_SaveData[t_FLength + m] = pASDU->m_SequenceData.at(m);
		}

		t_FLength += pASDU->m_SequenceData.size();
		//qDebug()<<"asdu"<<q<<t_ASDUNum;
		//qDebug()<<"pASDU->m_SequenceData ="<<pASDU->m_SequenceData.toHex();
	}

	//qDebug()<<"ALLLength ="<<t_FLength;
	//qDebug()<<"t_SmpCntValePos ="<<t_SmpCntValePos;
	//    qDebug()<<"t_ChanValuePos ="<<t_ChanValuePos;
	QByteArray &t_WaitToSendStructArray = m_ResultArray;
	QString t_strAll = QString::number(t_FLength, 16);
	QString t_strSmpCntValePos = QString::number(t_SmpCntValePos, 16);
	QString t_strChanValuePos = QString::number(t_ChanValuePos, 16);
	//All
	AddLongStrToByte(Get0String(4 - t_strAll.length()) + t_strAll, t_WaitToSendStructArray, 2);
	unsigned char nASDUnum = t_ASDUNum;
	t_WaitToSendStructArray.push_back(nASDUnum);
	t_WaitToSendStructArray.push_back(char((nASDUStartPos & 0xFF00) >> 8));
	t_WaitToSendStructArray.push_back(char(nASDUStartPos & 0xFF));
	//SmpCntValuePos
	AddLongStrToByte(Get0String(4 - t_strSmpCntValePos.length()) + t_strSmpCntValePos, t_WaitToSendStructArray, 2);
	//ChanValuePos
	AddLongStrToByte(Get0String(4 - t_strChanValuePos.length()) + t_strChanValuePos, t_WaitToSendStructArray, 2);
	t_WaitToSendStructArray.push_back(char((nASDULeng & 0xFF00) >> 8));
	t_WaitToSendStructArray.push_back(char(nASDULeng & 0xFF));
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
