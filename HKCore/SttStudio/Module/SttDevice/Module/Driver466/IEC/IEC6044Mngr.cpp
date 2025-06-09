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
	double fRate;
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

	//U5-abcz
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("U5-abcz");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / (pSmvRate->m_fPrimValue * 1000);
		mi = m_Ft3ChannelType.find("Ua5");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ub5");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Uc5");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//U6-abcz
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("U6-abcz");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / (pSmvRate->m_fPrimValue * 1000);
		mi = m_Ft3ChannelType.find("Ua6");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ub6");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Uc6");

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
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Ip-abc");

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

	//I3-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("Is-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("Ia3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic3");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//I4-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("It-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("Ia4");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib4");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic4");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//I5-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("I5-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("Ia5");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib5");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic5");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}
	}

	//I6-abc
	pSmvRate = (CIecCfgSmvRate *)pIecSmvRates->FindByID("I6-abc");

	if(pSmvRate != NULL)
	{
		fRate = pSmvRate->m_nCodeValue / pSmvRate->m_fPrimValue;
		mi = m_Ft3ChannelType.find("Ia6");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ib6");

		if(mi != m_Ft3ChannelType.end())
		{
			map.fRatio = fRate;
			mi.value() = map;
		}

		mi = m_Ft3ChannelType.find("Ic6");

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
	m_ChanMapID.insert("Ua5", 17);
	m_nVoltDrvPos[nVoltCnt++] = 14;
	m_ChanMapID.insert("Ub5", 18);
	m_nVoltDrvPos[nVoltCnt++] = 15;
	m_ChanMapID.insert("Uc5", 19);
	m_nVoltDrvPos[nVoltCnt++] = 16;
	m_ChanMapID.insert("Ua6", 21);
	m_nVoltDrvPos[nVoltCnt++] = 17;
	m_ChanMapID.insert("Ub6", 22);
	m_nVoltDrvPos[nVoltCnt++] = 18;
	m_ChanMapID.insert("Uc6", 23);
	m_nVoltDrvPos[nVoltCnt++] = 19;
	m_ChanMapID.insert("Ia1", 25);
	m_nCurrDrvPos[nCurrCnt++] = 20;
	m_ChanMapID.insert("Ib1", 26);
	m_nCurrDrvPos[nCurrCnt++] = 21;
	m_ChanMapID.insert("Ic1", 27);
	m_nCurrDrvPos[nCurrCnt++] = 22;
	m_ChanMapID.insert("Ia2", 29);
	m_nCurrDrvPos[nCurrCnt++] = 23;
	m_ChanMapID.insert("Ib2", 30);
	m_nCurrDrvPos[nCurrCnt++] = 24;
	m_ChanMapID.insert("Ic2", 31);
	m_nCurrDrvPos[nCurrCnt++] = 25;
	m_ChanMapID.insert("Ia3", 35);
	m_nCurrDrvPos[nCurrCnt++] = 26;
	m_ChanMapID.insert("Ib3", 36);
	m_nCurrDrvPos[nCurrCnt++] = 27;
	m_ChanMapID.insert("Ic3", 37);
	m_nCurrDrvPos[nCurrCnt++] = 28;
	m_ChanMapID.insert("Ia4", 39);
	m_nCurrDrvPos[nCurrCnt++] = 29;
	m_ChanMapID.insert("Ib4", 40);
	m_nCurrDrvPos[nCurrCnt++] = 30;
	m_ChanMapID.insert("Ic4", 41);
	m_nCurrDrvPos[nCurrCnt++] = 31;
	m_ChanMapID.insert("Ia5", 43);
	m_nCurrDrvPos[nCurrCnt++] = 32;
	m_ChanMapID.insert("Ib5", 44);
	m_nCurrDrvPos[nCurrCnt++] = 33;
	m_ChanMapID.insert("Ic5", 45);
	m_nCurrDrvPos[nCurrCnt++] = 34;
	m_ChanMapID.insert("Ia6", 47);
	m_nCurrDrvPos[nCurrCnt++] = 35;
	m_ChanMapID.insert("Ib6", 48);
	m_nCurrDrvPos[nCurrCnt++] = 36;
	m_ChanMapID.insert("Ic6", 49);
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
	m_ChanMapID.insert("U05",38);
	m_ChanMapID.insert("U06",42);
	m_ChanMapID.insert("I05",46);
	m_ChanMapID.insert("I06",50);

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
	m_ChanMapList.append("Ua5");
	m_ChanMapList.append("Ub5");
	m_ChanMapList.append("Uc5");
	m_ChanMapList.append("Ua6");
	m_ChanMapList.append("Ub6");
	m_ChanMapList.append("Uc6");
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
	m_ChanMapList.append("Ia5");
	m_ChanMapList.append("Ib5");
	m_ChanMapList.append("Ic5");
	m_ChanMapList.append("Ia6");
	m_ChanMapList.append("Ib6");
	m_ChanMapList.append("Ic6");

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
	m_Ft3ChannelType.insert("Uc4", map);
	m_Ft3ChannelType.insert("Ua5", map);
	m_Ft3ChannelType.insert("Ub5", map);
	m_Ft3ChannelType.insert("Uc5", map);
	m_Ft3ChannelType.insert("Ua6", map);
	m_Ft3ChannelType.insert("Ub6", map);
	m_Ft3ChannelType.insert("Uc6", map);//Ud*_18
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
	m_Ft3ChannelType.insert("Ic4", map);
	m_Ft3ChannelType.insert("Ia5", map);
	m_Ft3ChannelType.insert("Ib5", map);
	m_Ft3ChannelType.insert("Ic5", map);
	m_Ft3ChannelType.insert("Ia6", map);
	m_Ft3ChannelType.insert("Ib6", map);
	m_Ft3ChannelType.insert("Ic6", map);//Id*_18

}

QString CIEC6044Mngr::GetFt3ChannelType(int nChannelType, int nFT3ChannelTypePos)
{
	int nIndex = -1;

	if(nChannelType == STT_MODULE_TYPE_VOLT)
	{
		if(nFT3ChannelTypePos < 18)
		{
			nIndex = nFT3ChannelTypePos;
		}
	}
	else if(nChannelType == STT_MODULE_TYPE_CURRENT)
	{
		nIndex = nFT3ChannelTypePos + 18;
	}

	if(nIndex < 0 || nIndex >= m_ChanMapList.size())
	{
		return "";
	}

	return m_ChanMapList.at(nIndex);
}
