#include "IEC6044ComMngr.h"

CIEC6044ComMngr::CIEC6044ComMngr()
{
}

CIEC6044ComMngr::~CIEC6044ComMngr()
{
}

void CIEC6044ComMngr::InitFT3Rates(CIecCfgSmvRates *pIecSmvRates)
{
	FT3MapPointer map;
	QMap<QString, FT3MapPointer>::iterator mi;
	double fRate;
	//U1-123
	CIecCfgSmvRate *pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Uabcz");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / (pSmvRate->m_fPrimValue * 1000);
		mi = m_Ft3ChannelType.find("U1-1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("U1-2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("U1-3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//U2-123
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Up-abcz");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / (pSmvRate->m_fPrimValue * 1000);
		mi = m_Ft3ChannelType.find("U2-1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("U2-2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("U2-3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//U1-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Us-abcz");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / (pSmvRate->m_fPrimValue * 1000);
		mi = m_Ft3ChannelType.find("Ua1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ub1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Uc1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//U2-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Ut-abcz");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / (pSmvRate->m_fPrimValue * 1000);
		mi = m_Ft3ChannelType.find("Ua2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ub2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Uc2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//I1-123
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Iabc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("I1-1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("I1-2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("I1-3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//I2-123
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Ip-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("I2-1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("I2-2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("I2-3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//I3-123
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Is-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("I3-1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("I3-2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("I3-3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//I4-123
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("It-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("I4-1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("I4-2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("I4-3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//I1-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("I5-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("Ia1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//I2-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("I6-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("Ia2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}
}

void CIEC6044ComMngr::InitChanelMap()
{
	long nVoltCnt = 0;
	long nCurrCnt = 0;
	m_ChanMapID.clear();
	m_ChanMapID.insert("0", 0);
//    m_ChanMapID.insert("t-delay", 33);
//    m_ChanMapID.insert("Uz1", 34);
	m_ChanMapID.insert("U1-1", 1);//UdL1
	m_nVoltDrvPos[nVoltCnt++] = 1;
	m_ChanMapID.insert("U1-2", 2);//UdL2
	m_nVoltDrvPos[nVoltCnt++] = 2;
	m_ChanMapID.insert("U1-3", 3);//UdL3
	m_nVoltDrvPos[nVoltCnt++] = 3;
	m_ChanMapID.insert("U2-1", 5);//UdN1
	m_nVoltDrvPos[nVoltCnt++] = 5;
	m_ChanMapID.insert("U2-2", 6);//UdN2
	m_nVoltDrvPos[nVoltCnt++] = 6;
	m_ChanMapID.insert("U2-3", 7);//UdN3
	m_nVoltDrvPos[nVoltCnt++] = 7;
	m_ChanMapID.insert("Ua1", 9);
	m_nVoltDrvPos[nVoltCnt++] = 8;
	m_ChanMapID.insert("Ub1", 10);
	m_nVoltDrvPos[nVoltCnt++] = 9;
	m_ChanMapID.insert("Uc1", 11);
	m_nVoltDrvPos[nVoltCnt++] = 10;
	m_ChanMapID.insert("Ua2", 13);
	m_nVoltDrvPos[nVoltCnt++] = 11;
	m_ChanMapID.insert("Ub2", 14);
	m_nVoltDrvPos[nVoltCnt++] = 12;
	m_ChanMapID.insert("Uc2", 15);
	m_nVoltDrvPos[nVoltCnt++] = 13;
	m_ChanMapID.insert("I1-1", 17);//IdH1
	m_nCurrDrvPos[nCurrCnt++] = 14;
	m_ChanMapID.insert("I1-2", 18);//IdN1
	m_nCurrDrvPos[nCurrCnt++] = 15;
	m_ChanMapID.insert("I1-3", 19);//IdL1
	m_nCurrDrvPos[nCurrCnt++] = 16;
	m_ChanMapID.insert("I2-1", 21);//IdE1
	m_nCurrDrvPos[nCurrCnt++] = 17;
	m_ChanMapID.insert("I2-2", 22);//IdH2
	m_nCurrDrvPos[nCurrCnt++] = 18;
	m_ChanMapID.insert("I2-3", 23);//IdN2
	m_nCurrDrvPos[nCurrCnt++] = 19;
	m_ChanMapID.insert("I3-1", 25);//IdL2
	m_nCurrDrvPos[nCurrCnt++] = 20;
	m_ChanMapID.insert("I3-2", 26);//IdE2
	m_nCurrDrvPos[nCurrCnt++] = 21;
	m_ChanMapID.insert("I3-3", 27);//IdH3
	m_nCurrDrvPos[nCurrCnt++] = 22;
	m_ChanMapID.insert("I4-1", 29);//IdN3
	m_nCurrDrvPos[nCurrCnt++] = 23;
	m_ChanMapID.insert("I4-2", 30);//IdL3
	m_nCurrDrvPos[nCurrCnt++] = 24;
	m_ChanMapID.insert("I4-3", 31);//IdE3
	m_nCurrDrvPos[nCurrCnt++] = 25;
	m_ChanMapID.insert("Ia1", 35);
	m_nCurrDrvPos[nCurrCnt++] = 26;
	m_ChanMapID.insert("Ib1", 36);
	m_nCurrDrvPos[nCurrCnt++] = 27;
	m_ChanMapID.insert("Ic1", 37);
	m_nCurrDrvPos[nCurrCnt++] = 28;
	m_ChanMapID.insert("Ia2", 39);
	m_nCurrDrvPos[nCurrCnt++] = 29;
	m_ChanMapID.insert("Ib2", 40);
	m_nCurrDrvPos[nCurrCnt++] = 30;
	m_ChanMapID.insert("Ic2", 41);
	m_nCurrDrvPos[nCurrCnt++] = 31;

	//零序
	m_ChanMapID.insert("U01",12);
	m_ChanMapID.insert("U02",16);
	m_ChanMapID.insert("I01",38);
	m_ChanMapID.insert("I02",42);

	m_ChanMapList.clear();
	m_ChanMapList.append("U1-1");//UdL1
	m_ChanMapList.append("U1-2");//UdL2
	m_ChanMapList.append("U1-3");//UdL3
	m_ChanMapList.append("U2-1");//UdN1
	m_ChanMapList.append("U2-2");//UdN2
	m_ChanMapList.append("U2-3");//UdN3
	m_ChanMapList.append("Ua1");
	m_ChanMapList.append("Ub1");
	m_ChanMapList.append("Uc1");
	m_ChanMapList.append("Ua2");
	m_ChanMapList.append("Ub2");
	m_ChanMapList.append("Uc2");
	m_ChanMapList.append("I1-1");//IdH1
	m_ChanMapList.append("I1-2");//IdN1
	m_ChanMapList.append("I1-3");//IdL1
	m_ChanMapList.append("I2-1");//IdE1
	m_ChanMapList.append("I2-2");//IdH2
	m_ChanMapList.append("I2-3");//IdN2
	m_ChanMapList.append("I3-1");//IdL2
	m_ChanMapList.append("I3-2");//IdE2
	m_ChanMapList.append("I3-3");//IdH3
	m_ChanMapList.append("I4-1");//IdN3
	m_ChanMapList.append("I4-2");//IdL3
	m_ChanMapList.append("I4-3");//IdE3
	m_ChanMapList.append("Ia1");
	m_ChanMapList.append("Ib1");
	m_ChanMapList.append("Ic1");
	m_ChanMapList.append("Ia2");
	m_ChanMapList.append("Ib2");
	m_ChanMapList.append("Ic2");


	m_nVoltDrvCnt = nVoltCnt;
	m_nCurrDrvCnt = nCurrCnt;
}

void CIEC6044ComMngr::InitFT3ChanelType()
{
	FT3MapPointer map;
	map.fRatio = 1;//变比
	map.nSampleLen = 2;//电气量字节长度
	m_Ft3ChannelType.clear();
	//直流中性母线电压
	m_Ft3ChannelType.insert("U1-1", map); //Ud*_1、UdL1
	m_Ft3ChannelType.insert("U1-2", map);//UdL2
	m_Ft3ChannelType.insert("U1-3", map);//UdL3
	//直流电压
	m_Ft3ChannelType.insert("U2-1", map);//UdN1
	m_Ft3ChannelType.insert("U2-2", map);//UdN2
	m_Ft3ChannelType.insert("U2-3", map);//UdN3
	//交流电压
	m_Ft3ChannelType.insert("Ua1", map);
	m_Ft3ChannelType.insert("Ub1", map);
	m_Ft3ChannelType.insert("Uc1", map);
	m_Ft3ChannelType.insert("Ua2", map);
	m_Ft3ChannelType.insert("Ub2", map);
	m_Ft3ChannelType.insert("Uc2", map); //Ud*_12
	//直流电流
	m_Ft3ChannelType.insert("I1-1", map); //Id*_1、IdH1
	m_Ft3ChannelType.insert("I1-2", map);//IdN1
	m_Ft3ChannelType.insert("I1-3", map);//IdL1
	m_Ft3ChannelType.insert("I2-1", map);//IdE1
	m_Ft3ChannelType.insert("I2-2", map);//IdH2
	m_Ft3ChannelType.insert("I2-3", map);//IdN2
	m_Ft3ChannelType.insert("I3-1", map);//IdL2
	m_Ft3ChannelType.insert("I3-2", map);//IdE2
	m_Ft3ChannelType.insert("I3-3", map);//IdH3
	m_Ft3ChannelType.insert("I4-1", map);//IdN3
	m_Ft3ChannelType.insert("I4-2", map);//IdL3
	m_Ft3ChannelType.insert("I4-3", map);//IdE3
	//交流电流
	m_Ft3ChannelType.insert("Ia1", map);
	m_Ft3ChannelType.insert("Ib1", map);
	m_Ft3ChannelType.insert("Ic1", map);
	m_Ft3ChannelType.insert("Ia2", map);
	m_Ft3ChannelType.insert("Ib2", map);
	m_Ft3ChannelType.insert("Ic2", map); //Id*_18
}

QString CIEC6044ComMngr::GetFt3ChannelType(int nChannelType, int nFT3ChannelTypePos)
{
	int nIndex = -1;

	if(nChannelType == STT_MODULE_TYPE_VOLT)
	{
		if(nFT3ChannelTypePos < 12)
		{
			nIndex = nFT3ChannelTypePos;
		}
	}
	else if(nChannelType == STT_MODULE_TYPE_CURRENT)
	{
		nIndex = nFT3ChannelTypePos + 12;
	}

	if(nIndex < 0 || nIndex >= m_ChanMapList.size())
	{
		return "";
	}

	return m_ChanMapList.at(nIndex);
}

//FPGA不支持接收报文长度是奇数的情况
void CIEC6044ComMngr::Create6044ComSubTmtStruct(CIecCfg6044CommonInData *pIecData)
{
	if(pIecData->m_nUseFlag == 0 || m_strRecvProtocolID != pIecData->m_strProtocolID)
	{
		return;
	}

	tmt_ft3_6044 otmt_6044;
	otmt_6044.port = pIecData->m_nFiberIndex;
	otmt_6044.m_nChanNum = pIecData->m_nChannelNum;
	otmt_6044.m_nBaudValSub = pIecData->m_nBaudRate;
	otmt_6044.m_nSampleValSub = pIecData->m_nSampleRate;
	QString strDevChID;
	int n = 0;
	int nOffset = 2;//0564

	for(int nChan = 0; nChan < otmt_6044.m_nChanNum; nChan++)
	{
		CIecCfg6044CommonChIn *pCIecCfg6044ComCh = (CIecCfg6044CommonChIn *)pIecData->m_pCfgChs->GetAtIndex(nChan);
		FT3ChanInfo  oChanInfo;
		oChanInfo.nLen = pCIecCfg6044ComCh->m_nChLenth;
		oChanInfo.nFirstValue = nChan + 1;//按通道顺序编号，便于查看
		strDevChID = pCIecCfg6044ComCh->m_strDevChID;
		oChanInfo.nValidBitSub = 0;
		memset(oChanInfo.nBiIdxSub, 0, 16 * 4); //初始化
		oChanInfo.nChanPos1 = nOffset;

		if(m_nRecvCRCType == 0)
		{
			if((n + oChanInfo.nLen) > 16)
			{
				oChanInfo.nChanLen1 = 16 - n;
				oChanInfo.nChanLen2 = oChanInfo.nLen - oChanInfo.nChanLen1;
				oChanInfo.nChanPos2 = oChanInfo.nChanPos1 + oChanInfo.nChanLen1 + 2;
			}
			else
			{
				oChanInfo.nChanLen1 = oChanInfo.nLen;
				oChanInfo.nChanLen2 = 0;
				oChanInfo.nChanPos2 = 0;
			}
		}
		else
		{
			oChanInfo.nChanLen1 = oChanInfo.nLen;
			oChanInfo.nChanLen2 = 0;
			oChanInfo.nChanPos2 = 0;
		}


		if(pCIecCfg6044ComCh->m_strChType == "StateValue"
				|| (pCIecCfg6044ComCh->m_strChType == "Other" && pCIecCfg6044ComCh->m_strAppChID == "Other"))
		{
			QList<QString> oDevChList = strDevChID.split(";");

			if(oDevChList.count() > 0)
			{
				QString strBitIdx, strBinIdx;
				long nBitIdx, nBinIdx;

				for(int nDevChIdx = 0; nDevChIdx < oDevChList.count(); nDevChIdx++)
				{
					QString strDevCh = oDevChList.at(nDevChIdx);

					if(strDevCh.contains("="))
					{
						strBitIdx = strDevCh.split("=")[0];
						strBitIdx = strBitIdx.replace("bit", "");
						nBitIdx = strBitIdx.toInt();
						strBinIdx = strDevCh.split("=")[1];
						strBinIdx = strBinIdx.replace("bin", "");
						nBinIdx = strBinIdx.toInt();

						if(nBitIdx < 16)
						{
							if(nBinIdx > 0 && nBinIdx <= 8)
							{
								oChanInfo.nBiIdxSub[nBitIdx] = nBinIdx;//1~8
								oChanInfo.nValidBitSub |= 1 << nBitIdx; //0~15
							}
						}
					}
				}
			}
		}

		oChanInfo.strMap = "Other";
		otmt_6044.m_oChanList.append(oChanInfo);
		nOffset += oChanInfo.nLen;

		if(m_nRecvCRCType == 0)
		{
			if((n + oChanInfo.nLen) >= 16)
			{
				nOffset += 2;//CRC
				n = oChanInfo.nChanLen2;
			}
			else
			{
				n += oChanInfo.nLen;
			}
		}
	}

	QByteArray ba;
	Create6044ComByteArray(otmt_6044, ba);
//    qDebug()<<"SubBlock"<<ba.right(ba.size() - 12).toHex();
	otmt_6044.m_nTotalSizeSub = ba.size() - 12;//下载的报文头12字节
	data_6044Sub.append(otmt_6044);
}

//FPGA不支持发送报文长度是奇数的情况
void CIEC6044ComMngr::Create6044ComByteArray(tmt_ft3_6044 otmt_6044, QByteArray &m_oPackage)
{
	m_oPackage.clear();
	BOOL bFindDataPos = FALSE;
	m_oEncoderInfo.nACDataLen = 0;
	m_oEncoderInfo.nACDataPos = 0;
	m_oEncoderInfo.nSmpcntPos = 0;
	m_oEncoderInfo.nSmpcntType = otmt_6044.m_nSampleType;
	m_oEncoderInfo.nACDataEnd = 0;
	m_bACDataBegin = FALSE;
	BOOL bFindEnd = FALSE;
	long nFirstValue;
	m_oPackage.push_back(0x05);
	m_oPackage.push_back(0x64);

	for(int i = 0; i < otmt_6044.m_nChanNum; i++)
	{
		FT3ChanInfo  oChanInfo = otmt_6044.m_oChanList.at(i);
		nFirstValue = oChanInfo.nFirstValue;
		QString strMap = oChanInfo.strMap;

		if(strMap.compare("Other") == 0 ||
				strMap.compare("BOOLEAN") == 0 ||
				strMap.compare("Dbpos") == 0 ||
				strMap.compare("zero") == 0)
		{
			if(m_bACDataBegin && !bFindEnd)
			{
				bFindEnd = true;
				m_oEncoderInfo.nACDataEnd = m_oPackage.size();
			}

			if(oChanInfo.nLen == 1)
			{
				m_oPackage.push_back((unsigned char)(nFirstValue & 0xFF));
			}
			else  if(oChanInfo.nLen == 2)
			{
				m_oPackage.push_back((nFirstValue >> 8) & 0xFF);
				m_oPackage.push_back((nFirstValue & 0xFF));
			}
			else if(oChanInfo.nLen == 3)
			{
				m_oPackage.push_back((nFirstValue >> 16) & 0xFF);
				m_oPackage.push_back((nFirstValue >> 8) & 0xFF);
				m_oPackage.push_back((nFirstValue & 0xFF));
			}
			else if(oChanInfo.nLen == 4)
			{
				m_oPackage.push_back((nFirstValue >> 24) & 0xFF);
				m_oPackage.push_back((nFirstValue >> 16) & 0xFF);
				m_oPackage.push_back((nFirstValue >> 8) & 0xFF);
				m_oPackage.push_back((nFirstValue & 0xFF));
			}
		}
		else if(strMap.compare("SmpCnt") == 0)
		{
			if(m_bACDataBegin && !bFindEnd)
			{
				bFindEnd = true;
				m_oEncoderInfo.nACDataEnd = m_oPackage.size();
			}

			//cnt
			m_oEncoderInfo.nSmpcntPos = m_oPackage.size() + 1;

			if(oChanInfo.nLen == 1)
			{
				m_oPackage.push_back((char) 0x0);
			}
			else
			{
				m_oPackage.push_back((char) 0x0);
				m_oPackage.push_back((char) 0x0);
			}
		}
		else if(strMap.compare("t-delay") == 0)
		{
			if(m_bACDataBegin && !bFindEnd)
			{
				bFindEnd = true;
				m_oEncoderInfo.nACDataEnd = m_oPackage.size();
			}

			//delay
			if(oChanInfo.nLen == 1)
			{
				m_oPackage.push_back((unsigned char)(otmt_6044.m_nDelayTimeValue & 0xFF));
			}
			else
			{
				m_oPackage.push_back((otmt_6044.m_nDelayTimeValue >> 8) & 0xFF);
				m_oPackage.push_back((otmt_6044.m_nDelayTimeValue & 0xFF));
			}
		}
		else
		{
			long nMap = m_ChanMapID[strMap];

			if(nMap < 1)
			{
				CString strInfo = strMap;
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] IEC6044 MapID = %s"), strInfo.GetString());
			}

			//U,I
			m_bACDataBegin = true;

			if(!bFindEnd)
			{
				m_oEncoderInfo.nACDataLen += oChanInfo.nLen;
			}

			if(!bFindDataPos)
			{
				bFindDataPos = true;
				m_oEncoderInfo.nACDataPos = m_oPackage.size() + 1;
			}

			if(oChanInfo.nLen == 1)
			{
				m_oPackage.push_back((unsigned char)(nMap));
			}
			else
			{
				for(int i = 0; i < oChanInfo.nLen; i++)
				{
					m_oPackage.push_back((unsigned char)(nMap));
				}
			}
		}
	}

	if(m_nSendCRCType == 0)
	{
		InsertCRCFlag_Standard(m_oPackage);
	}
	else if(m_nSendCRCType == 1)
	{
		//尾部CRC
		m_oPackage.append(0xab);
		m_oPackage.append(0xba);
	}
	else
	{
		InsertCRCFlag_Standard(m_oPackage);
	}

	EnCoderHeader(otmt_6044, m_oPackage);
}
