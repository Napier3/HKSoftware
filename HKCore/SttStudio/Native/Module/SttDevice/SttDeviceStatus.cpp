#include "stdafx.h"
#include "SttDeviceStatus.h"

#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../SttTest/Common/tmt_common_def.h"
#include "../SttCmd/SttSysState.h"
#ifdef _PSX_QT_LINUX_
    #include "math.h"
#endif
PSTT_DEVICE_STATUS g_theSttDeviceStatus = NULL;
CRingMemBuf *g_pPPSBuf = NULL;

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
            pXmlModule->xml_serialize("����ԭ��:�ϱ���ģ�������������ļ���ƥ��", "DisableType", "", "long", nDisableType);
            break;

        case 2:
            pXmlModule->xml_serialize("����ԭ��:�����ϵ���ģ���״�ͨѶ�쳣", "DisableType", "", "long", nDisableType);
            break;

        case 3:
            pXmlModule->xml_serialize("����ԭ��:�����ļ�ģ��λ�÷Ƿ�", "DisableType", "", "long", nDisableType);
            break;

        case 4:
            pXmlModule->xml_serialize("����ԭ��:�����ļ�ģ�����ͷǷ�", "DisableType", "", "long", nDisableType);
            break;

        default:
            pXmlModule->xml_serialize("����ԭ��:δ֪����", "DisableType", "", "long", nDisableType);
    }
}

void stt_xml_serialize(PSTT_MODULE_CH_STATUS pPara, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pChannel = pXmlSerialize->xml_serialize("ͨ��", "Channel", nIndex, "Channel", stt_ParaGroupKey());

    if(pChannel == NULL)
    {
        return;
    }

    pChannel->xml_serialize("ͨ��ID", "ID", "", "string", pPara->m_pszChId);
    pChannel->xml_serialize("����ѹ", "VoltMax", "V", "float", pPara->m_fVoltMax);
    pChannel->xml_serialize("��С��ѹ", "VoltMin", "V", "float", pPara->m_fVoltMin);
	pChannel->xml_serialize("ͨ��״̬(Ӳ���ɼ��ź�),0-����,1-�쳣", "IsOverLoad", "", "long", pPara->m_bIsOverLoad);
}

void stt_xml_serialize(PSTT_MODULE_STATUS pPara, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize("ģ��", "Module", nIndex, "Module", stt_ParaGroupKey());

    if(pXmlModule == NULL)
    {
        return;
    }

    //2021-5-4  lijunqing  ��������  ��׼ID������֮���ת��
    stt_xml_serialize_data_type(pXmlModule, "ģ������", "ModuleType", "", "ModuleType", pPara->m_nModuleType);
    pXmlModule->xml_serialize("ģ��λ��", "ModulePos", "", "long", pPara->m_nModulePos);

    if(pPara->m_nNeedMonitor == 0)
    {
        //���ְ�������ϱ�������Ϣ��������
        return;
    }

    if(pPara->m_nDisable)
    {
		pXmlModule->xml_serialize("ģ��״̬�쳣��������(1:ģ�����Ͳ�ƥ��)", "Disable", "", "long", pPara->m_nDisable);
    }

    pXmlModule->xml_serialize("���Ƶ�Դ+", "VoltDc1", "V", "float", pPara->m_fVoltDc[0]);
    pXmlModule->xml_serialize("���Ƶ�Դ-", "VoltDc2", "V", "float", pPara->m_fVoltDc[1]);
    pXmlModule->xml_serialize("���ʵ�Դ+", "VoltDc3", "V", "float", pPara->m_fVoltDc[2]);
    pXmlModule->xml_serialize("���ʵ�Դ-", "VoltDc4", "V", "float", pPara->m_fVoltDc[3]);
    pXmlModule->xml_serialize("�¶�(��)", "T1", "deg", "long", pPara->m_nTemp[0]);
    pXmlModule->xml_serialize("�¶�(��)", "T2", "deg", "long", pPara->m_nTemp[1]);
    pXmlModule->xml_serialize("�¶�(��)", "T3", "deg", "long", pPara->m_nTemp[2]);
    pXmlModule->xml_serialize("��ѹ����", "IsVoltHot", "", "long", pPara->m_nIsVoltHot);
    pXmlModule->xml_serialize("ֱ������", "IsDCHot", "", "long", pPara->m_nIsDCHot);
    pXmlModule->xml_serialize("��ѹ�澯", "IsVoltWarining", "", "long", pPara->m_nIsVoltWarining);
    pXmlModule->xml_serialize("ʧ�ظ澯", "IsMissWarining", "", "long", pPara->m_nIsMissWarining);

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
		//����ģʽ
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

void stt_xml_serialize_device_utc(CSttXmlSerializeBase *pXmlSerialize)
{
    if(g_theSttDeviceStatus == NULL)
    {
        return;
    }

    CSttXmlSerializeBase *pXmlUtc = pXmlSerialize->xml_serialize("", SYS_STATE_XEVENT_EVENTID_SYNCTIME,
                                    SYS_STATE_XEVENT_EVENTID_SYNCTIME, stt_ParaGroupKey());
    pXmlUtc->xml_serialize("ͬ��(0-δ��ʱ,1-GPS,2-BCode,4-1588)", "Sync", "", "long", g_theSttDeviceStatus->m_nSync);
    pXmlUtc->xml_serialize("UTC-��", "Utc_s", "", "long", g_theSttDeviceStatus->m_nUtc_s);
    pXmlUtc->xml_serialize("UTC-����", "Utc_ns", "", "long", g_theSttDeviceStatus->m_nUtc_ns);
    pXmlUtc->xml_serialize("ʱ������", "TimeZone", "", "long", g_theSttDeviceStatus->m_nTimeZone);
//    pXmlUtc->xml_serialize("����ʱ��-��","User_s","","long", g_theSttDeviceStatus->m_nUser_s);
#ifdef _PSX_QT_LINUX_
//    QDateTime oDate = QDateTime::fromTime_t(g_theSttDeviceStatus->m_nUser_s);
//    CString strDate = oDate.toString("yyyy-MM-dd hh:mm:ss");
//    pXmlUtc->xml_serialize("����ʱ��","CurDate","","string", strDate);
    short nYear, nMon, nDay, nHour, nMin, nSec;
    CString strDate;
    TransTimer_t(g_theSttDeviceStatus->m_nUser_s, nYear, nMon, nDay, nHour, nMin, nSec);
    strDate.Format("%04d-%02d-%02d %02d:%02d:%02d", nYear, nMon, nDay, nHour, nMin, nSec);
    pXmlUtc->xml_serialize("����ʱ��", "CurDate", "", "string", strDate);
#endif
    pXmlUtc->xml_serialize("4G(0-�ر�,1-����)", "4G", "", "long", g_theSttDeviceStatus->m_b4G);
    pXmlUtc->xml_serialize("Wifi(0-�ر�,1-����)", "Wifi", "", "long", g_theSttDeviceStatus->m_bWifi);
    pXmlUtc->xml_serialize("����(0-�ر�,1-����)", "Ble", "", "long", g_theSttDeviceStatus->m_bBle);
    long nPowerAC = g_theSttDeviceStatus->m_bPowerAC;

    if(nPowerAC == 0)
    {
		if(g_theSttDeviceStatus->m_nBatErr)
		{
			nPowerAC = 2;
		}
    }

	pXmlUtc->xml_serialize("���(0-��,1-��,2-��ص�ѹ�ɼ��쳣)", "PowerAC", "", "long", nPowerAC);
    pXmlUtc->xml_serialize("USB(0-��,1-��)", "USB", "", "long", g_theSttDeviceStatus->m_bUSB);
    pXmlUtc->xml_serialize("���ʣ������%", "BatCap", "", "long", g_theSttDeviceStatus->m_nBatCap);

    if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
    {
        stt_xml_serialize_Digital_LightPower(pXmlUtc);
    }

    char pBuf[8];
    long nReadLen = g_pPPSBuf->ReadBuf2(pBuf, g_theSttDeviceStatus->m_nPPSReadPos,
                                        g_theSttDeviceStatus->m_nPPS64ReadSizeTotal, 8);

    if(nReadLen > 0)
    {
        int nData;
        memcpy(&nData, pBuf, 4);
        pXmlUtc->xml_serialize("��ʱ��ʱʵ����", "PPSIndex", "", "long", nData);
        memcpy(&nData, pBuf + 4, 4);
        pXmlUtc->xml_serialize("��ʱ��ʱʵ����", "PPSValue", "", "long", nData);
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
        pXmlSerialize->xml_serialize("ͬ��(0-δ��ʱ,1-GPS,2-BCode,4-1588)", "Sync", "", "long", g_theSttDeviceStatus->m_nSync);
        pXmlSerialize->xml_serialize("UTC-��", "Utc_s", "", "long", g_theSttDeviceStatus->m_nUtc_s);
        pXmlSerialize->xml_serialize("UTC-����", "Utc_ns", "", "long", g_theSttDeviceStatus->m_nUtc_ns);
        pXmlSerialize->xml_serialize("ʱ������", "TimeZone", "", "long", g_theSttDeviceStatus->m_nTimeZone);
#ifdef _PSX_QT_LINUX_
        short nYear, nMon, nDay, nHour, nMin, nSec;
        CString strDate;
        TransTimer_t(g_theSttDeviceStatus->m_nUser_s, nYear, nMon, nDay, nHour, nMin, nSec);
        strDate.Format("%04d-%02d-%02d %02d:%02d:%02d", nYear, nMon, nDay, nHour, nMin, nSec);
        pXmlSerialize->xml_serialize("����ʱ��", "CurDate", "", "string", strDate);
#endif
        pXmlSerialize->xml_serialize("4G(0-�ر�,1-����)", "4G", "", "long", g_theSttDeviceStatus->m_b4G);
        pXmlSerialize->xml_serialize("Wifi(0-�ر�,1-����)", "Wifi", "", "long", g_theSttDeviceStatus->m_bWifi);
        pXmlSerialize->xml_serialize("����(0-�ر�,1-����)", "Ble", "", "long", g_theSttDeviceStatus->m_bBle);
        pXmlSerialize->xml_serialize("���(0-��,1-��)", "PowerAC", "", "long", g_theSttDeviceStatus->m_bPowerAC);
        pXmlSerialize->xml_serialize("USB(0-��,1-��)", "USB", "", "long", g_theSttDeviceStatus->m_bUSB);
        pXmlSerialize->xml_serialize("���ʣ������%", "BatCap", "", "long", g_theSttDeviceStatus->m_nBatCap);

        if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
        {
            stt_xml_serialize_Digital_LightPower(pXmlSerialize);
        }
    }

    pXmlSerialize->xml_serialize("����ֹͣʵ��", "StopByHighT", "", "long", g_theSttDeviceStatus->m_bNeedStop);
    pXmlSerialize->xml_serialize("ģ����ģ����", "AnalogCount", "", "long", g_theSttDeviceStatus->m_nAnalogCount);
#ifdef _Board_PNS330
    PSTT_MODULE_STATUS pParaV = &g_theSttDeviceStatus->m_oModule[0];
    PSTT_MODULE_STATUS pParaI = &g_theSttDeviceStatus->m_oModule[1];
    long nTemp;
    nTemp = 0;
    CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize("ģ��", "Module", nTemp, "Module", stt_ParaGroupKey());

    if(pXmlModule == NULL)
    {
        return;
    }

    pXmlModule->xml_serialize("��ѹ���ʵ�Դ+", "VoltDc3", "V", "float", pParaV->m_fVoltDc[2]);
    pXmlModule->xml_serialize("��ѹ���ʵ�Դ-", "VoltDc4", "V", "float", pParaV->m_fVoltDc[3]);
    pXmlModule->xml_serialize("�������ʵ�Դ+", "CurrDc3", "V", "float", pParaI->m_fVoltDc[2]);
    pXmlModule->xml_serialize("�������ʵ�Դ-", "CurrDc4", "V", "float", pParaI->m_fVoltDc[3]);
    pXmlModule->xml_serialize("�����¶�", "T1", "deg", "long", pParaI->m_nTemp[0]);
    pXmlModule->xml_serialize("ɢ�����¶�", "T2", "deg", "long", pParaI->m_nTemp[1]);
    pXmlModule->xml_serialize("FPGA�¶�", "T3", "deg", "long", pParaI->m_nTemp[2]);
    pXmlModule->xml_serialize("������¶�1", "BAT_Temp1", "deg", "long", pParaI->m_fVoltDc[1]);
    pXmlModule->xml_serialize("������¶�2", "BAT_Temp2", "deg", "long", pParaI->m_fVoltDc[0]);
    pXmlModule->xml_serialize("��ص�ѹ", "BATV", "", "float", pParaV->m_fBAT[0]);
    pXmlModule->xml_serialize("��ص���", "BATI", "", "float", pParaI->m_fBAT[1]);
    pXmlModule->xml_serialize("4.2��ص�ѹ", "BAT_V4.2", "V", "float", pParaV->m_fVoltDc[0]);
    pXmlModule->xml_serialize("8.4��ص�ѹ", "BAT_V8.4", "V", "float", pParaV->m_fVoltDc[1]);
    long nValue;
    nValue = (pParaV->m_nWarningVal >> 11) & 0x01;
    pXmlModule->xml_serialize("VA����(0:����)", "OVL_V1", "", "long", nValue);
    nValue = (pParaV->m_nWarningVal >> 10) & 0x01;
    pXmlModule->xml_serialize("VB����(0:����)", "OVL_V2", "", "long", nValue);
    nValue = (pParaV->m_nWarningVal >> 9) & 0x01;
    pXmlModule->xml_serialize("VC����(0:����)", "OVL_V3", "", "long", nValue);
    nValue = (pParaV->m_nWarningVal >> 8) & 0x01;
    pXmlModule->xml_serialize("VZ����(0:����)", "OVL_V4", "", "long", nValue);
    nValue = (pParaV->m_nWarningVal >> 7) & 0x01;
    nValue = nValue > 0 ? 0 : 1; //Ӳ���ź�ȡ��
    pXmlModule->xml_serialize("����(1:����)", "OVT", "", "long", nValue);
    nValue = (pParaV->m_nWarningVal >> 6) & 0x01;
    pXmlModule->xml_serialize("��ع���(0:����)", "BAT_OVL", "", "long", nValue);
    nValue = (pParaV->m_nWarningVal >> 5) & 0x01;
    pXmlModule->xml_serialize("����Phy-Link", "ETH_LINK/ACT", "", "long", nValue);
    nValue = (pParaV->m_nWarningVal >> 4) & 0x01;
    pXmlModule->xml_serialize("����Phy-Speed", "ETH_SPEED", "", "long", nValue);
    nValue = (pParaV->m_nWarningVal >> 3) & 0x01;
    pXmlModule->xml_serialize("����Link(0:Link)", "BT_LINK", "", "long", nValue);
    nValue = (pParaV->m_nWarningVal >> 2) & 0x01;
    pXmlModule->xml_serialize("WiFi-Link(0:Link)", "WIFI_LINK", "", "long", nValue);
    nValue = (pParaV->m_nWarningVal >> 1) & 0x01;
    pXmlModule->xml_serialize("4G-Link(0:Link)", "4G_LINK", "", "long", nValue);
    nValue = pParaV->m_nWarningVal & 0x01;
    pXmlModule->xml_serialize("���(0:�����)", "CHRG", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 12) & 0x01;
	pXmlModule->xml_serialize("VBUS", "VBUS", "", "long", nValue);

    //4U6I
    for(long k = 0; k < 4; k++)
    {
        stt_xml_serialize(&pParaV->m_oChannel[k], k, pXmlModule);
    }

    for(long k = 0; k < 6; k++)
    {
        stt_xml_serialize(&pParaI->m_oChannel[k], k, pXmlModule);
    }

#else

    for(long k = 0; k < g_theSttDeviceStatus->m_nAnalogCount; k++)
    {
        stt_xml_serialize(&g_theSttDeviceStatus->m_oModule[k], k, pXmlSerialize);
    }

#endif
    pXmlSerialize->xml_serialize("ģ�����", STT_SYS_STATE_ID_OverHeat, "", "long", g_theSttDeviceStatus->m_nOverHeat);
    pXmlSerialize->xml_serialize("������·", STT_SYS_STATE_ID_IBreak, "", "long", g_theSttDeviceStatus->m_nIBreak);
    pXmlSerialize->xml_serialize("��ѹ��·", STT_SYS_STATE_ID_UShort, "", "long", g_theSttDeviceStatus->m_nUShort);
    pXmlSerialize->xml_serialize("������ѹ", STT_SYS_STATE_ID_Udc, "", "long", g_theSttDeviceStatus->m_nUdc);
}
