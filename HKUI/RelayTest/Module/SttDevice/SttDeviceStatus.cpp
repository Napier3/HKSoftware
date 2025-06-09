#include "stdafx.h"
#include "SttDeviceStatus.h"

#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../SttTest/Common/tmt_common_def.h"
#include "../SttCmd/SttSysState.h"
#ifdef _PSX_QT_LINUX_
    #include "math.h"
	#include "SttDeviceBase.h"
#endif
PSTT_DEVICE_STATUS g_theSttDeviceStatus = NULL;
CRingMemBuf *g_pPPSBuf = NULL;
unsigned int g_nDrvMainSTMode = 0;

void stt_init_stt_device_status()
{
    if(g_theSttDeviceStatus == NULL)
    {
        g_theSttDeviceStatus = (PSTT_DEVICE_STATUS)malloc(sizeof(STT_DEVICE_STATUS));
        memset(g_theSttDeviceStatus, 0, sizeof(STT_DEVICE_STATUS));
        g_theSttDeviceStatus->init();
        g_pPPSBuf = new CRingMemBuf;
        g_pPPSBuf->Create(8 * 50);
    }
    else
    {
        g_theSttDeviceStatus->m_bNeedStop = FALSE;
        g_theSttDeviceStatus->m_nSync = 0;
        g_theSttDeviceStatus->m_b4G = 0;
        g_theSttDeviceStatus->m_bWifi = 0;
        g_theSttDeviceStatus->m_bBle = 0;
        g_theSttDeviceStatus->m_bPowerAC = 0;
        g_theSttDeviceStatus->m_bUSB = 0;
        g_theSttDeviceStatus->m_nOverHeat = 0;
        g_theSttDeviceStatus->m_nIBreak = 0;
        g_theSttDeviceStatus->m_nUShort = 0;
        g_theSttDeviceStatus->m_nUdc = 0;

        for(int i = 0; i < g_theSttDeviceStatus->m_nAnalogCount; i++)
        {
            g_theSttDeviceStatus->m_oModule[i].m_nIsDCHot = 0;
            g_theSttDeviceStatus->m_oModule[i].m_nIsMissWarining = 0;
            g_theSttDeviceStatus->m_oModule[i].m_nIsVoltHot = 0;
            g_theSttDeviceStatus->m_oModule[i].m_nIsVoltWarining = 0;
            g_theSttDeviceStatus->m_oModule[i].m_fBAT[0] = 0;
            g_theSttDeviceStatus->m_oModule[i].m_fBAT[1] = 0;
            g_theSttDeviceStatus->m_oModule[i].m_nWarningVal = 0;

            for(int j = 0; j < CHANNEL_MAX; j++)
            {
                g_theSttDeviceStatus->m_oModule[i].m_oChannel[j].m_bIsOverLoad = 0;
            }

            for(int j = 0; j < 8; j++)
            {
                g_theSttDeviceStatus->m_oModule[i].m_fLCPortPower[j] = 0;
            }
        }
    }
}

void stt_free_stt_device_status()
{
    if(g_theSttDeviceStatus != NULL)
    {
        free(g_theSttDeviceStatus);
        g_theSttDeviceStatus = NULL;
    }

    if(g_pPPSBuf != NULL)
    {
        delete g_pPPSBuf;
        g_pPPSBuf = NULL;
    }
}


void stt_xml_serialize_register_device_status()
{
    stt_init_stt_device_status();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CDataGroup oDataGroup;
    oDataGroup.m_strID = "DeviceStatus";
    oDataGroup.m_strName = "DeviceStatus";
    oDataGroup.m_strDataType = "DeviceStatus";
    CSttXmlSerializeBase *pSttXmlSerialize = oSttXmlSerializeTool.CreateXmlSerializeRegister(&oDataGroup);
    stt_xml_serialize_device_status(pSttXmlSerialize, FALSE);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("DeviceStatus.xml");
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

void stt_xml_serialize_disable(long nDisableType, CSttXmlSerializeBase *pXmlModule)
{
    switch(nDisableType)
    {
        case 1:
            pXmlModule->xml_serialize("禁用原因:上报的模块类型与配置文件不匹配", "DisableType", "", "long", nDisableType);
            break;

        case 2:
            pXmlModule->xml_serialize("禁用原因:主板上电与模块首次通讯异常", "DisableType", "", "long", nDisableType);
            break;

        case 3:
            pXmlModule->xml_serialize("禁用原因:配置文件模块位置非法", "DisableType", "", "long", nDisableType);
            break;

        case 4:
            pXmlModule->xml_serialize("禁用原因:配置文件模块类型非法", "DisableType", "", "long", nDisableType);
            break;

        default:
            pXmlModule->xml_serialize("禁用原因:未知错误", "DisableType", "", "long", nDisableType);
    }
}

void stt_xml_serialize(PSTT_MODULE_CH_STATUS pPara, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pChannel = pXmlSerialize->xml_serialize("通道", "Channel", nIndex, "Channel", stt_ParaGroupKey());

    if(pChannel == NULL)
    {
        return;
    }

    pChannel->xml_serialize("通道ID", "ID", "", "string", pPara->m_pszChId);
    pChannel->xml_serialize("最大电压", "VoltMax", "V", "float", pPara->m_fVoltMax);
    pChannel->xml_serialize("最小电压", "VoltMin", "V", "float", pPara->m_fVoltMin);
	pChannel->xml_serialize("通道状态(硬件采集信号),0-正常,1-异常", "IsOverLoad", "", "long", pPara->m_bIsOverLoad);
}

void stt_xml_serialize(PSTT_MODULE_STATUS pPara, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize("模块", "Module", nIndex, "Module", stt_ParaGroupKey());

    if(pXmlModule == NULL)
    {
        return;
    }

    //2021-5-4  lijunqing  数据类型  标准ID和整数之间的转换
    stt_xml_serialize_data_type(pXmlModule, "模块类型", "ModuleType", "", "ModuleType", pPara->m_nModuleType);
    pXmlModule->xml_serialize("模块位置", "ModulePos", "", "long", pPara->m_nModulePos);

    if(pPara->m_nNeedMonitor == 0)
    {
        //数字板等无需上报监视信息具体内容
        return;
    }

    if(pPara->m_nDisable)
    {
		pXmlModule->xml_serialize("模块状态异常，被禁用(1:模块类型不匹配)", "Disable", "", "long", pPara->m_nDisable);
    }

    pXmlModule->xml_serialize("控制电源+", "VoltDc1", "V", "float", pPara->m_fVoltDc[0]);
    pXmlModule->xml_serialize("控制电源-", "VoltDc2", "V", "float", pPara->m_fVoltDc[1]);
    pXmlModule->xml_serialize("功率电源+", "VoltDc3", "V", "float", pPara->m_fVoltDc[2]);
    pXmlModule->xml_serialize("功率电源-", "VoltDc4", "V", "float", pPara->m_fVoltDc[3]);
    pXmlModule->xml_serialize("温度(上)", "T1", "deg", "long", pPara->m_nTemp[0]);
    pXmlModule->xml_serialize("温度(下)", "T2", "deg", "long", pPara->m_nTemp[1]);
    pXmlModule->xml_serialize("温度(中)", "T3", "deg", "long", pPara->m_nTemp[2]);
    pXmlModule->xml_serialize("电压过热", "IsVoltHot", "", "long", pPara->m_nIsVoltHot);
    pXmlModule->xml_serialize("直流过热", "IsDCHot", "", "long", pPara->m_nIsDCHot);
    pXmlModule->xml_serialize("电压告警", "IsVoltWarining", "", "long", pPara->m_nIsVoltWarining);
    pXmlModule->xml_serialize("失地告警", "IsMissWarining", "", "long", pPara->m_nIsMissWarining);

    for(long k = 0; k < pPara->m_nChanNum; k++)
    {
        stt_xml_serialize(&pPara->m_oChannel[k], k, pXmlModule);
    }
}

void stt_xml_serialize_Digital_LightPower(CSttXmlSerializeBase *pXmlSerialize)
{
    CString strID;

#ifdef _Board_PNS330
	if(g_theDeviceSystemParameter->m_oModules_D[0]->m_oModuleAttr.m_nModuleIndex == 15)
	{
		//主机模式
		CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize("", "ModulePos_15", "LightPower", stt_ParaGroupKey());

		if(pXmlModule != NULL)
		{
			for(int j = 0; j < 4; j++)
			{
				strID.Format("Port%d", j + 1);
				float fdbm = 0;
	#ifdef _PSX_QT_LINUX_
				fdbm = 10 * log10(g_theSttDeviceStatus->m_oModule[0].m_fLCPortPower[j] * 0.001);

				if(fdbm < -35)
				{
					fdbm = -54;
				}

	#endif
				pXmlModule->xml_serialize("", strID.GetString(), "dbm", "number", fdbm);
			}
		}

		return;
	}
#endif

    for(int i = 0; i < g_theSttDeviceStatus->m_nAnalogCount; i++)
    {
        PSTT_MODULE_STATUS pModule = &g_theSttDeviceStatus->m_oModule[i];

        if(pModule->m_nModuleType == STT_MODULE_TYPE_DIGITAL_0G8M
                || pModule->m_nModuleType == STT_MODULE_TYPE_DIGITAL_2G6M
                || pModule->m_nModuleType == STT_MODULE_TYPE_DIGITAL_4G4M)
        {
            strID.Format("ModulePos_%d", pModule->m_nModulePos);
            CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize("", strID.GetString(), "LightPower", stt_ParaGroupKey());

            if(pXmlModule != NULL)
            {
                for(int j = 0; j < 8; j++)
                {
                    strID.Format("Port%d", j + 1);
                    float fdbm = 0;
#ifdef _PSX_QT_LINUX_
                    fdbm = 10 * log10(pModule->m_fLCPortPower[j] * 0.001);

					if(fdbm < -35)
                    {
                        fdbm = -54;
                    }

#endif                   
					pXmlModule->xml_serialize("", strID.GetString(), "dbm", "number", fdbm);
                }
            }
        }
    }

}

void stt_xml_serialize_STMode(CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize("", "STMode", "STMode", stt_ParaGroupKey());
	int nCnt = g_theDeviceSystemParameter->m_oDeviceAttrs.m_nSTModeSet;
	CString strID;

	for(int i = 0;i < nCnt;i++)
	{
		unsigned char nMainSTMode = (g_nDrvMainSTMode >> (i*2))&0x3;
		strID.Format("Port%d",i+1);
		switch(nMainSTMode)
		{
		case 0:
			pXmlModule->xml_serialize("", strID.GetString(), "Mode", "", "None");
			break;
		case 1:
			pXmlModule->xml_serialize("", strID.GetString(), "Mode", "", "FT3");
			break;
		case 2:
			pXmlModule->xml_serialize("", strID.GetString(), "Mode", "", "PPS");
			break;
		case 3:
			pXmlModule->xml_serialize("", strID.GetString(), "Mode", "", "BCode");
			break;
		}
	}
}

void stt_xml_serialize_CurPower(CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize("CurrModules", "CurrModules", "CurrModules", stt_ParaGroupKey());
	if(pXmlModule == NULL)
	{
		return;
	}

	long nCnt = g_theDeviceSystemParameter->m_nModuleCount_I + g_theDeviceSystemParameter->m_nModuleCount_UI;
	pXmlModule->xml_serialize("电流模块数量", "CurrModuleNum", "", "number", nCnt);
	CString strID;
	long nIndex = 0;

	for(int nModuleIndex = 1; nModuleIndex <= 16; nModuleIndex++)
	{
		for(int i = 0;i < g_theDeviceSystemParameter->m_nModuleCount;i++)
		{
			PSTT_MODULE pModule = &g_theDeviceSystemParameter->m_oModules[i];
			if(pModule == NULL)
			{
				continue;
			}

			if(pModule->m_oModuleAttr.m_nModuleIndex != nModuleIndex)
			{
				continue;
			}

			if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_CURRENT
					||pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
			{
				strID.Format(_T("CurrModule%d"), nIndex++);
				CSttXmlSerializeBase *pChildSerialize = pXmlModule->xml_serialize("", strID.GetString(), "CurrModule", stt_ParaGroupKey());

				if(pChildSerialize != NULL)
				{
					pChildSerialize->xml_serialize(_T("电流模块位置"), _T("ModulePos"), "", "number", nModuleIndex);
					long nPowerMode = STT_CurrentMODULE_POWER_LOW;
					float fVset = 0;
					long nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_SUPPORT;
					long nLargeCurOutTerm = STT_LARGE_CUR_OUT_NULL;

					for(int nIndex=0;nIndex<g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
					{
						tmt_CurModuleGear &oCurModuleGear=g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];
						if(oCurModuleGear.m_nModulePos == nModuleIndex)
						{
							nPowerMode = oCurModuleGear.m_nIPowerMode;
							fVset = oCurModuleGear.m_fVoltSet;
							nMergeCurTerminal = oCurModuleGear.m_nMergeCurTerminal;
							nLargeCurOutTerm = oCurModuleGear.m_nLargeCurOutTerm;
							break;
						}
					}

					pChildSerialize->xml_serialize(_T("电流模块档位值"), _T("CurModuleGear"), "", "number", nPowerMode);
					pChildSerialize->xml_serialize(_T("电流通道最大端口电压"), _T("MaxPortVol"), "", "float", fVset);
					pChildSerialize->xml_serialize(_T("合并电流端子"), _T("MergeCurTerminal"), "", "float", nMergeCurTerminal);
					pChildSerialize->xml_serialize(_T("大电流输出端口"), _T("LargeCurOutTerm"), "", "number", nLargeCurOutTerm);

				}
			}
		}
	}
}

void stt_xml_serialize_device_utc(CSttXmlSerializeBase *pXmlSerialize)
{
    if(g_theSttDeviceStatus == NULL)
    {
        return;
    }

    CSttXmlSerializeBase *pXmlUtc = pXmlSerialize->xml_serialize("", SYS_STATE_XEVENT_EVENTID_SYNCTIME,
                                    SYS_STATE_XEVENT_EVENTID_SYNCTIME, stt_ParaGroupKey());
    pXmlUtc->xml_serialize("同步(0-未对时,1-GPS,2-BCode,4-1588)", "Sync", "", "long", g_theSttDeviceStatus->m_nSync);
    pXmlUtc->xml_serialize("UTC-秒", "Utc_s", "", "long", g_theSttDeviceStatus->m_nUtc_s);
    pXmlUtc->xml_serialize("UTC-纳秒", "Utc_ns", "", "long", g_theSttDeviceStatus->m_nUtc_ns);
    pXmlUtc->xml_serialize("时区补偿", "TimeZone", "", "long", g_theSttDeviceStatus->m_nTimeZone);
//    pXmlUtc->xml_serialize("本地时间-秒","User_s","","long", g_theSttDeviceStatus->m_nUser_s);
#ifdef _PSX_QT_LINUX_
//    QDateTime oDate = QDateTime::fromTime_t(g_theSttDeviceStatus->m_nUser_s);
//    CString strDate = oDate.toString("yyyy-MM-dd hh:mm:ss");
//    pXmlUtc->xml_serialize("本地时间","CurDate","","string", strDate);
    short nYear, nMon, nDay, nHour, nMin, nSec;
    CString strDate;
    TransTimer_t(g_theSttDeviceStatus->m_nUser_s, nYear, nMon, nDay, nHour, nMin, nSec);
    strDate.Format("%04d-%02d-%02d %02d:%02d:%02d", nYear, nMon, nDay, nHour, nMin, nSec);
    pXmlUtc->xml_serialize("本地时间", "CurDate", "", "string", strDate);
#endif
    pXmlUtc->xml_serialize("4G(0-关闭,1-开启)", "4G", "", "long", g_theSttDeviceStatus->m_b4G);
    pXmlUtc->xml_serialize("Wifi(0-关闭,1-开启)", "Wifi", "", "long", g_theSttDeviceStatus->m_bWifi);
    pXmlUtc->xml_serialize("蓝牙(0-关闭,1-开启)", "Ble", "", "long", g_theSttDeviceStatus->m_bBle);
    long nPowerAC = g_theSttDeviceStatus->m_bPowerAC;

    if(nPowerAC == 0)
    {
		if(g_theSttDeviceStatus->m_nBatErr)
		{
			nPowerAC = 2;
		}
    }

	pXmlUtc->xml_serialize("充电(0-无,1-有,2-电池电压采集异常)", "PowerAC", "", "long", nPowerAC);
    pXmlUtc->xml_serialize("USB(0-无,1-有)", "USB", "", "long", g_theSttDeviceStatus->m_bUSB);
    pXmlUtc->xml_serialize("电池剩余容量%", "BatCap", "", "long", g_theSttDeviceStatus->m_nBatCap);
	pXmlUtc->xml_serialize("风扇模式(0-静音风速,1-正常风速)", "WindSpeed", "", "long", g_theSystemConfig->m_nWindSpeed);
	pXmlUtc->xml_serialize("Lcd背光时长", "LcdTimes", "", "long", g_theSystemConfig->m_oPeripheral.m_nLcdTimes);
	pXmlUtc->xml_serialize("Lcd最大背光亮度", "LcdLight", "", "long", g_theSystemConfig->m_oPeripheral.m_nLcdLight);

    if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
    {
		if(g_nRTDATAMode == 0)
		{
			stt_xml_serialize_Digital_LightPower(pXmlUtc);
		}
    }

	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nSTModeSet > 0)
	{
		if(g_nRTDATAMode == 0)
		{
			stt_xml_serialize_STMode(pXmlUtc);
		}
	}

	if(g_theDeviceSystemParameter->m_nModuleCount_I > 0 || g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		if(g_nRTDATAMode == 0)
		{
			stt_xml_serialize_CurPower(pXmlUtc);
		}
	}

#ifdef _PSX_QT_LINUX_
	if(CSttDeviceBase::g_pSttDeviceBase->GetDevInputInfo())
	{
		CSttXmlSerializeBase *pXmlModule = pXmlUtc->xml_serialize("", "InputDev", "InputDev", stt_ParaGroupKey());
		if(pXmlModule != NULL)
		{
			DevInputInfo *pDevInputInfo = &CSttDeviceBase::g_pSttDeviceBase->m_oDevInputInfo;
			pXmlModule->xml_serialize("输入设备状态序号", "VerIdx", "", "long", pDevInputInfo->m_nVerIdx);
			pXmlModule->xml_serialize("(0-无鼠标,1-有鼠标)", "Mouse", "", "long", pDevInputInfo->m_bMouse);
			pXmlModule->xml_serialize("设置键盘环境变量", "QWS_KEYBOARD", "", "string", pDevInputInfo->m_strKeyBoard);
		}
	}

	if(CSttDeviceBase::g_pSttDeviceBase->GetBinaryVolt() && g_nRTDATAMode == 0)
	{
		CSttXmlSerializeBase *pXmlModule = pXmlUtc->xml_serialize("", "BinaryVolt", "BinaryVolt", stt_ParaGroupKey());
		if(pXmlModule != NULL)
		{
			char pszName[11] = "ABCDEFGHIJ";
			CString strName,strID;
			for(int i = 0;i < 10;i++)
			{
				strID.Format("BinVolt%d",i+1);
				strName.Format("开入%c测量电压",pszName[i]);
				unsigned int nCurBinaryGear = CSttDeviceBase::g_pSttDeviceBase->m_nCurBinaryGear[i];
				unsigned int nCurBinaryCode = CSttDeviceBase::g_pSttDeviceBase->m_nCurBinaryCode[i];
				float fVolt = CSttDeviceBase::g_pSttDeviceBase->CalBinaryVolt(i, nCurBinaryGear, nCurBinaryCode);
				pXmlModule->xml_serialize(strName.GetString(), strID.GetString(), "", "float", fVolt);

				strID.Format("BinCode%d",i+1);
				strName.Format("开入%c测量电压码值",pszName[i]);
				pXmlModule->xml_serialize(strName.GetString(), strID.GetString(), "", "long", nCurBinaryCode);

				strName.Format("开入%c测量档位",pszName[i]);
				switch(nCurBinaryGear)
				{
				case Gear_Null:
				{
					strID.Format("BinGear%d",i+1);
					pXmlModule->xml_serialize(strName.GetString(), strID.GetString(), "", "float", "");
				}
					break;
				case Gear_01V:
				{
					fVolt = 0.1;
					strID.Format("BinGear%d",i+1);
					pXmlModule->xml_serialize(strName.GetString(), strID.GetString(), "", "float", fVolt);
				}
					break;
				case Gear_1V:
				{
					fVolt = 1.0;
					strID.Format("BinGear%d",i+1);
					pXmlModule->xml_serialize(strName.GetString(), strID.GetString(), "", "float", fVolt);
				}
					break;
				case Gear_10V:
				{
					fVolt = 10.0;
					strID.Format("BinGear%d",i+1);
					pXmlModule->xml_serialize(strName.GetString(), strID.GetString(), "", "float", fVolt);
				}
					break;
				case Gear_100V:
				{
					fVolt = 100.0;
					strID.Format("BinGear%d",i+1);
					pXmlModule->xml_serialize(strName.GetString(), strID.GetString(), "", "float", fVolt);
				}
					break;
				case Gear_600V:
				{
					fVolt = 600.0;
					strID.Format("BinGear%d",i+1);
					pXmlModule->xml_serialize(strName.GetString(), strID.GetString(), "", "float", fVolt);
				}
					break;
				}
			}
		}
	}

	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nDCMeas && g_nRTDATAMode == 0)
	{
		CSttXmlSerializeBase *pXmlModule = pXmlUtc->xml_serialize("", "DCMeas", "DCMeas", stt_ParaGroupKey());
		if(pXmlModule != NULL)
		{
			long nModuleIndex = 0;
			double fRet = 0;
			CSttXmlSerializeBase *pChildSerialize = pXmlModule->xml_serialize("", "MeasModule", "MeasModule", stt_ParaGroupKey());
			if(pChildSerialize != NULL)
			{
				pChildSerialize->xml_serialize(_T("模块位置"), _T("ModulePos"), "", "long", nModuleIndex);
				fRet = CSttDeviceBase::g_pSttDeviceBase->CalDCMeas(TRUE, CSttDeviceBase::g_pSttDeviceBase->m_nReadInCode_V);

				pChildSerialize->xml_serialize(_T("直流电压"), _T("DC_V"), "", "double", fRet);
				pChildSerialize->xml_serialize(_T("直流电压码值"), _T("VCode"), "", "long",
											   CSttDeviceBase::g_pSttDeviceBase->m_nReadInCode_V);
				fRet = CSttDeviceBase::g_pSttDeviceBase->CalDCMeas(FALSE, CSttDeviceBase::g_pSttDeviceBase->m_nReadInCode_I);

				pChildSerialize->xml_serialize(_T("直流电流"), _T("DC_I"), "", "double", fRet);
				pChildSerialize->xml_serialize(_T("直流电流码值"), _T("ICode"), "", "long",
											   CSttDeviceBase::g_pSttDeviceBase->m_nReadInCode_I);
			}
		}
	}

	if(CSttDeviceBase::g_pSttDeviceBase->GetBinConfig() && g_nRTDATAMode == 0)
	{
		CSttXmlSerializeBase *pXmlModule = pXmlUtc->xml_serialize("", "BinConfig", "BinConfig", stt_ParaGroupKey());
		if(pXmlModule != NULL)
		{
			Drv_BinarySetting *pBinSetting = &CSttDeviceBase::g_pSttDeviceBase->m_oBinSetting;

			CString strID;
			char pszBInName[21] = "ABCDEFGHIJKLMNOPQRST";
			for(int i = 0;i < g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinCount && i < MAX_BINARYIN_COUNT;i++)
			{
				strID.Format("Bin%cType",pszBInName[i]);

				if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinVoltMeas)
				{
					pXmlModule->xml_serialize(_T("开入模式(0-电压，1-空接点)"), strID.GetString(), "", "long", pBinSetting->nEType[i]);
					if(pBinSetting->nEType[i] == 0)
					{
						strID.Format("Bin%cVolt",pszBInName[i]);
						pXmlSerialize->xml_serialize("开入翻转阈值", strID.GetString(), "", "float", pBinSetting->fTripVolt[i]);
					}
				}
				else
				{
					pXmlModule->xml_serialize(_T("开入模式(0-电压，1-空接点)"), strID.GetString(), "", "long", _T("1"));
				}
			}
		}
	}
#endif

    char pBuf[8];
    long nReadLen = g_pPPSBuf->ReadBuf2(pBuf, g_theSttDeviceStatus->m_nPPSReadPos,
                                        g_theSttDeviceStatus->m_nPPS64ReadSizeTotal, 8);

    if(nReadLen > 0)
    {
        int nData;
        memcpy(&nData, pBuf, 4);
        pXmlUtc->xml_serialize("对时守时实验结果", "PPSIndex", "", "long", nData);
        memcpy(&nData, pBuf + 4, 4);
        pXmlUtc->xml_serialize("对时守时实验结果", "PPSValue", "", "long", nData);
    }
}

void stt_xml_serialize_device_status(CSttXmlSerializeBase *pXmlSerialize, BOOL IsReport)
{
    if(g_theSttDeviceStatus == NULL)
    {
        return;
    }

    if(IsReport)
    {
        pXmlSerialize->xml_serialize("同步(0-未对时,1-GPS,2-BCode,4-1588)", "Sync", "", "long", g_theSttDeviceStatus->m_nSync);
        pXmlSerialize->xml_serialize("UTC-秒", "Utc_s", "", "long", g_theSttDeviceStatus->m_nUtc_s);
        pXmlSerialize->xml_serialize("UTC-纳秒", "Utc_ns", "", "long", g_theSttDeviceStatus->m_nUtc_ns);
        pXmlSerialize->xml_serialize("时区补偿", "TimeZone", "", "long", g_theSttDeviceStatus->m_nTimeZone);
#ifdef _PSX_QT_LINUX_
        short nYear, nMon, nDay, nHour, nMin, nSec;
        CString strDate;
        TransTimer_t(g_theSttDeviceStatus->m_nUser_s, nYear, nMon, nDay, nHour, nMin, nSec);
        strDate.Format("%04d-%02d-%02d %02d:%02d:%02d", nYear, nMon, nDay, nHour, nMin, nSec);
        pXmlSerialize->xml_serialize("本地时间", "CurDate", "", "string", strDate);
#endif
        pXmlSerialize->xml_serialize("4G(0-关闭,1-开启)", "4G", "", "long", g_theSttDeviceStatus->m_b4G);
        pXmlSerialize->xml_serialize("Wifi(0-关闭,1-开启)", "Wifi", "", "long", g_theSttDeviceStatus->m_bWifi);
        pXmlSerialize->xml_serialize("蓝牙(0-关闭,1-开启)", "Ble", "", "long", g_theSttDeviceStatus->m_bBle);
        pXmlSerialize->xml_serialize("充电(0-无,1-有)", "PowerAC", "", "long", g_theSttDeviceStatus->m_bPowerAC);
        pXmlSerialize->xml_serialize("USB(0-无,1-有)", "USB", "", "long", g_theSttDeviceStatus->m_bUSB);
        pXmlSerialize->xml_serialize("电池剩余容量%", "BatCap", "", "long", g_theSttDeviceStatus->m_nBatCap);

        if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
        {
            stt_xml_serialize_Digital_LightPower(pXmlSerialize);
        }
    }

    pXmlSerialize->xml_serialize("高温停止实验", "StopByHighT", "", "long", g_theSttDeviceStatus->m_bNeedStop);
    pXmlSerialize->xml_serialize("模拟量模块数", "AnalogCount", "", "long", g_theSttDeviceStatus->m_nAnalogCount);

	CSttDeviceBase::g_pSttDeviceBase->Stt_Xml_Serialize_Channels(pXmlSerialize);

    pXmlSerialize->xml_serialize("模块过热", STT_SYS_STATE_ID_OverHeat, "", "long", g_theSttDeviceStatus->m_nOverHeat);
    pXmlSerialize->xml_serialize("电流开路", STT_SYS_STATE_ID_IBreak, "", "long", g_theSttDeviceStatus->m_nIBreak);
    pXmlSerialize->xml_serialize("电压短路", STT_SYS_STATE_ID_UShort, "", "long", g_theSttDeviceStatus->m_nUShort);
	pXmlSerialize->xml_serialize("辅助电压", STT_SYS_STATE_ID_Udc, "", "long", g_theSttDeviceStatus->m_nUdc);
}
