#include "IEC6044Mngr.h"

CIEC6044Mngr::CIEC6044Mngr()
{
}

CIEC6044Mngr::~CIEC6044Mngr()
{
}

void CIEC6044Mngr::InitFT3Rates(CIecCfgSmvRates *pIecSmvRates)
{
	FT3MapPointer map;
	QMap<QString, FT3MapPointer>::iterator mi;
	double fRate,fRateM;
	//Uabcz
	CIecCfgSmvRate *pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Uabcz");

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

	//U2-abcz
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Up-abcz");

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

	//U3-abcz
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Us-abcz");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / (pSmvRate->m_fPrimValue * 1000);
		mi = m_Ft3ChannelType.find("Ua3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ub3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Uc3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//U4-abcz
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Ut-abcz");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / (pSmvRate->m_fPrimValue * 1000);
		mi = m_Ft3ChannelType.find("Ua4");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ub4");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Uc4");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//Iabc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Iabc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		fRateM = pSmvRate->m_nMeasCurrCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("Ia1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ia1M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib1M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic1");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic1M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}
	}

	//I2-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Ip-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		fRateM = pSmvRate->m_nMeasCurrCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("Ia2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ia2M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib2M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic2");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic2M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}
	}

	//I3-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Is-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		fRateM = pSmvRate->m_nMeasCurrCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("Ia3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ia3M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib3M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic3M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}
	}

	//I4-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("It-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		fRateM = pSmvRate->m_nMeasCurrCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("Ia4");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ia4M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib4");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib4M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRateM;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic4");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic4M");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}
}

void CIEC6044Mngr::InitChanelMap()
{
	long nVoltCnt = 0;
	long nCurrCnt = 0;
	m_ChanMapID.clear();
	m_ChanMapID.insert("0", 0);
//    m_ChanMapID.insert("t-delay", 33);
//    m_ChanMapID.insert("Uz1", 34);
	m_ChanMapID.insert("Ua1", 1);
	m_nVoltDrvPos[nVoltCnt++] = 1;
	m_ChanMapID.insert("Ub1", 2);
	m_nVoltDrvPos[nVoltCnt++] = 2;
	m_ChanMapID.insert("Uc1", 3);
	m_nVoltDrvPos[nVoltCnt++] = 3;
	m_ChanMapID.insert("Ua2", 5);
	m_nVoltDrvPos[nVoltCnt++] = 5;
	m_ChanMapID.insert("Ub2", 6);
	m_nVoltDrvPos[nVoltCnt++] = 6;
	m_ChanMapID.insert("Uc2", 7);
	m_nVoltDrvPos[nVoltCnt++] = 7;
	m_ChanMapID.insert("Ua3", 9);
	m_nVoltDrvPos[nVoltCnt++] = 8;
	m_ChanMapID.insert("Ub3", 10);
	m_nVoltDrvPos[nVoltCnt++] = 9;
	m_ChanMapID.insert("Uc3", 11);
	m_nVoltDrvPos[nVoltCnt++] = 10;
	m_ChanMapID.insert("Ua4", 13);
	m_nVoltDrvPos[nVoltCnt++] = 11;
	m_ChanMapID.insert("Ub4", 14);
	m_nVoltDrvPos[nVoltCnt++] = 12;
	m_ChanMapID.insert("Uc4", 15);
	m_nVoltDrvPos[nVoltCnt++] = 13;

	m_ChanMapID.insert("Ia1", 17);
	m_nCurrDrvPos[nCurrCnt++] = 14;
	m_ChanMapID.insert("Ib1", 18);
	m_nCurrDrvPos[nCurrCnt++] = 15;
	m_ChanMapID.insert("Ic1", 19);
	m_nCurrDrvPos[nCurrCnt++] = 16;
	m_ChanMapID.insert("Ia2", 21);
	m_nCurrDrvPos[nCurrCnt++] = 17;
	m_ChanMapID.insert("Ib2", 22);
	m_nCurrDrvPos[nCurrCnt++] = 18;
	m_ChanMapID.insert("Ic2", 23);
	m_nCurrDrvPos[nCurrCnt++] = 19;
	m_ChanMapID.insert("Ia3", 25);
	m_nCurrDrvPos[nCurrCnt++] = 20;
	m_ChanMapID.insert("Ib3", 26);
	m_nCurrDrvPos[nCurrCnt++] = 21;
	m_ChanMapID.insert("Ic3", 27);
	m_nCurrDrvPos[nCurrCnt++] = 22;
	m_ChanMapID.insert("Ia4", 29);
	m_nCurrDrvPos[nCurrCnt++] = 23;
	m_ChanMapID.insert("Ib4", 30);
	m_nCurrDrvPos[nCurrCnt++] = 24;
	m_ChanMapID.insert("Ic4", 31);
	m_nCurrDrvPos[nCurrCnt++] = 25;
	m_ChanMapID.insert("Ia1M", 35);
	m_nCurrDrvPos[nCurrCnt++] = 26;
	m_ChanMapID.insert("Ib1M", 36);
	m_nCurrDrvPos[nCurrCnt++] = 27;
	m_ChanMapID.insert("Ic1M", 37);
	m_nCurrDrvPos[nCurrCnt++] = 28;
	m_ChanMapID.insert("Ia2M", 39);
	m_nCurrDrvPos[nCurrCnt++] = 29;
	m_ChanMapID.insert("Ib2M", 40);
	m_nCurrDrvPos[nCurrCnt++] = 30;
	m_ChanMapID.insert("Ic2M", 41);
	m_nCurrDrvPos[nCurrCnt++] = 31;
	m_ChanMapID.insert("Ia3M", 43);
	m_nCurrDrvPos[nCurrCnt++] = 32;
	m_ChanMapID.insert("Ib3M", 44);
	m_nCurrDrvPos[nCurrCnt++] = 33;
	m_ChanMapID.insert("Ic3M", 45);
	m_nCurrDrvPos[nCurrCnt++] = 34;
	m_ChanMapID.insert("Ia4M", 47);
	m_nCurrDrvPos[nCurrCnt++] = 35;
	m_ChanMapID.insert("Ib4M", 48);
	m_nCurrDrvPos[nCurrCnt++] = 36;
	m_ChanMapID.insert("Ic4M", 49);
	m_nCurrDrvPos[nCurrCnt++] = 37;

	//零序
	m_ChanMapID.insert("U01",4);
	m_ChanMapID.insert("U02",8);
	m_ChanMapID.insert("U03",12);
	m_ChanMapID.insert("U04",16);
	m_ChanMapID.insert("I01",20);
	m_ChanMapID.insert("I02",24);
	m_ChanMapID.insert("I03",28);
	m_ChanMapID.insert("I04",32);
	m_ChanMapID.insert("I01M",38);
	m_ChanMapID.insert("I02M",42);
	m_ChanMapID.insert("I03M",46);
	m_ChanMapID.insert("I04M",50);

	m_ChanMapList.clear();
	m_ChanMapList.append("Ua1");
	m_ChanMapList.append("Ub1");
	m_ChanMapList.append("Uc1");
	m_ChanMapList.append("Ua2");
	m_ChanMapList.append("Ub2");
	m_ChanMapList.append("Uc2");
	m_ChanMapList.append("Ua3");
	m_ChanMapList.append("Ub3");
	m_ChanMapList.append("Uc3");
	m_ChanMapList.append("Ua4");
	m_ChanMapList.append("Ub4");
	m_ChanMapList.append("Uc4");
	m_ChanMapList.append("Ia1");
	m_ChanMapList.append("Ib1");
	m_ChanMapList.append("Ic1");
	m_ChanMapList.append("Ia2");
	m_ChanMapList.append("Ib2");
	m_ChanMapList.append("Ic2");
	m_ChanMapList.append("Ia3");
	m_ChanMapList.append("Ib3");
	m_ChanMapList.append("Ic3");
	m_ChanMapList.append("Ia4");
	m_ChanMapList.append("Ib4");
	m_ChanMapList.append("Ic4");
	m_ChanMapList.append("Ia1M");
	m_ChanMapList.append("Ib1M");
	m_ChanMapList.append("Ic1M");
	m_ChanMapList.append("Ia2M");
	m_ChanMapList.append("Ib2M");
	m_ChanMapList.append("Ic2M");
	m_ChanMapList.append("Ia3M");
	m_ChanMapList.append("Ib3M");
	m_ChanMapList.append("Ic3M");
	m_ChanMapList.append("Ia4M");
	m_ChanMapList.append("Ib4M");
	m_ChanMapList.append("Ic4M");

	m_nVoltDrvCnt = nVoltCnt;
	m_nCurrDrvCnt = nCurrCnt;
}

void CIEC6044Mngr::InitFT3ChanelType()
{
	FT3MapPointer map;
	map.fRatio = 1;//变比
	map.nSampleLen = 2;//电气量字节长度
	m_Ft3ChannelType.clear();
	//交流电压
	m_Ft3ChannelType.insert("Ua1", map);//Ud*_1
	m_Ft3ChannelType.insert("Ub1", map);
	m_Ft3ChannelType.insert("Uc1", map);
	m_Ft3ChannelType.insert("Ua2", map);
	m_Ft3ChannelType.insert("Ub2", map);
	m_Ft3ChannelType.insert("Uc2", map);
	m_Ft3ChannelType.insert("Ua3", map);
	m_Ft3ChannelType.insert("Ub3", map);
	m_Ft3ChannelType.insert("Uc3", map);
	m_Ft3ChannelType.insert("Ua4", map);
	m_Ft3ChannelType.insert("Ub4", map);
	m_Ft3ChannelType.insert("Uc4", map);//Ud*_12
	//交流电流
	m_Ft3ChannelType.insert("Ia1", map);//Id*_1
	m_Ft3ChannelType.insert("Ib1", map);
	m_Ft3ChannelType.insert("Ic1", map);
	m_Ft3ChannelType.insert("Ia2", map);
	m_Ft3ChannelType.insert("Ib2", map);
	m_Ft3ChannelType.insert("Ic2", map);
	m_Ft3ChannelType.insert("Ia3", map);
	m_Ft3ChannelType.insert("Ib3", map);
	m_Ft3ChannelType.insert("Ic3", map);
	m_Ft3ChannelType.insert("Ia4", map);
	m_Ft3ChannelType.insert("Ib4", map);
	m_Ft3ChannelType.insert("Ic4", map);//Id*_12
	m_Ft3ChannelType.insert("Ia1M", map);//Id*_13
	m_Ft3ChannelType.insert("Ib1M", map);
	m_Ft3ChannelType.insert("Ic1M", map);
	m_Ft3ChannelType.insert("Ia2M", map);
	m_Ft3ChannelType.insert("Ib2M", map);
	m_Ft3ChannelType.insert("Ic2M", map);
	m_Ft3ChannelType.insert("Ia3M", map);
	m_Ft3ChannelType.insert("Ib3M", map);
	m_Ft3ChannelType.insert("Ic3M", map);
	m_Ft3ChannelType.insert("Ia4M", map);
	m_Ft3ChannelType.insert("Ib4M", map);
	m_Ft3ChannelType.insert("Ic4M", map);//Id*_24

}

QString CIEC6044Mngr::GetFt3ChannelType(int nChannelType, int nFT3ChannelTypePos)
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
void CIEC6044Mngr::Create6044ComSubTmtStruct(CIecCfg6044CommonInData *pIecData)
{
	if(pIecData->m_nUseFlag == 0
			|| m_strRecvProtocolID != pIecData->m_strProtocolID
			|| m_nRecvCRCType == 2)
	{
		//只订阅满足16字节校验的开关量变位
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

void CIEC6044Mngr::InsertCRCFlag_GDW60044_STD12Ch(QByteArray &oPackage)
{
	QByteArray oPackage2;
	oPackage2.clear();
	oPackage2.append(oPackage.at(0));
	oPackage2.append(oPackage.at(1));

	for(int i = 2;i < 16;i++)
	{
		oPackage2.append(oPackage.at(i));
	}
	//块之间CRC
	oPackage2.append(0xab);//取0xABBA,便于识别，最终数值由FPGA自动替换
	oPackage2.append(0xba);
	for(int i = 16;i < 32;i++)
	{
		oPackage2.append(oPackage.at(i));
	}
	//块之间CRC
	oPackage2.append(0xab);//取0xABBA,便于识别，最终数值由FPGA自动替换
	oPackage2.append(0xba);
	for(int i = 32;i < oPackage.size();i++)
	{
		oPackage2.append(oPackage.at(i));
	}
	//块之间CRC
	oPackage2.append(0xab);//取0xABBA,便于识别，最终数值由FPGA自动替换
	oPackage2.append(0xba);

	m_oEncoderInfo.nSmpcntPos = 49;
	m_oEncoderInfo.nACDataPos = 19;//第二个数据块首地址
	m_oEncoderInfo.nACDataLen = 26;//12*2+CRC

	oPackage.clear();
	oPackage.swap(oPackage2);
}

//FPGA不支持发送报文长度是奇数的情况
void CIEC6044Mngr::Create6044ComByteArray(tmt_ft3_6044 otmt_6044, QByteArray &m_oPackage)
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
	else if(m_nSendCRCType == 2)
	{
		InsertCRCFlag_GDW60044_STD12Ch(m_oPackage);
	}
	else
	{
		InsertCRCFlag_Standard(m_oPackage);
	}

	EnCoderHeader(otmt_6044, m_oPackage);
}
