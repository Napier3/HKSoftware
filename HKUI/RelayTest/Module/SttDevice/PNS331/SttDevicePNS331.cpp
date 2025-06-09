#include "SttDevicePNS331.h"
#include "../Module/PowerCtrl/UI/PNS331/SttPowerCtrl_PNS331.h"

CSttDevicePNS331 *CSttDevicePNS331::g_pSttDevicePNS331 = NULL;
long CSttDevicePNS331::g_nSttDeviceRef = 0;
QList<float> fBatList;
#define WAIT_FOR_FIBER_POWEROK 1000

CSttDevicePNS331::CSttDevicePNS331()
{
    //����ST��ģʽ���ã�330Ĭ��RX2��B��
	//00-None 01:FT3 10:PPS 11:BCode
	m_nMainSTMode = 0b1110;
}

CSttDevicePNS331::~CSttDevicePNS331()
{
	if(g_pFpgaUart)
    {
		delete(g_pFpgaUart);
		g_pFpgaUart = NULL;
    }
}

void CSttDevicePNS331::Create()
{
    g_nSttDeviceRef++;

    if(g_nSttDeviceRef == 1)
    {
        g_pSttDevicePNS331 = new CSttDevicePNS331;
        g_pSttDeviceBase = (CSttDeviceBase *)g_pSttDevicePNS331;
    }
}

void CSttDevicePNS331::Release()
{
    g_nSttDeviceRef--;

    if(g_nSttDeviceRef == 0)
    {
        delete g_pSttDevicePNS331;
        g_pSttDevicePNS331 = NULL;
    }
}

void RegisterValueInit(unsigned int &nRegisterVal)
{
    nRegisterVal &= ~(1 << 8); //ON/OFF_PA default=0
    nRegisterVal &= ~(1 << 9); //ON/OFF_VI default=0
    nRegisterVal |= 1 << 19; //LED_VOUT     default=1
    nRegisterVal &= ~(1 << 21); //K_IPout   default=0
    nRegisterVal &= ~(1 << 20); //K_VPout   default=0
}

int CSttDevicePNS331::InitDevice(BOOL bHasAdjFile)
{
	m_nBatLastTime = 0;
    m_nVoltPowerRefVal = 0;
    m_nCurrPowerRefVal = 0;
    fBatList.clear();
    m_nTestStopTick = -1;
    m_nBatCalcCnt = 0;
	m_nBatErrCnt = 0;
    //PNS330ֻ��һ��bit31��ģ���źź�һ��bit30�����ź�
    g_theDeviceSystemParameter->m_nModuleCount_U = 0;
    g_theDeviceSystemParameter->m_nModuleCount_I = 0;

    if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
    {
        g_theDeviceSystemParameter->m_nModuleCount_UI = 1;
        PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[0];

        if(pModule != NULL)
        {
            pModule->m_oModuleAttr.m_nModuleIndex = 16;//bit31ģ���ź� 270V10A
            pModule->m_oModuleAttr.m_nChannelNum = 8;
            pModule->m_oModuleAttr.m_nModulePower = STT_MODULE_UI_PNS331;
            pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrl_PNS331);
            PSTT_MODULE_CH_DEFS pChDefs = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs;
            PSTT_CH_DRV_POS pChDrvPos = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDrvPos;
            pChDrvPos->m_nChDrvPos[0] = 6;
            pChDrvPos->m_nChDrvPos[1] = 7;
            pChDrvPos->m_nChDrvPos[2] = 4;
            pChDrvPos->m_nChDrvPos[3] = 5;
            pChDrvPos->m_nChDrvPos[4] = 2;
            pChDrvPos->m_nChDrvPos[5] = 3;
            pChDrvPos->m_nChDrvPos[6] = 0;
            pChDrvPos->m_nChDrvPos[7] = 1;
            pModule->init_ch_drv_pos();
            //4U4I
            strcpy(pChDefs->m_oChDef[0].m_pszChId, "U1_1");
            strcpy(pChDefs->m_oChDef[1].m_pszChId, "U1_2");
            strcpy(pChDefs->m_oChDef[2].m_pszChId, "U1_3");
            strcpy(pChDefs->m_oChDef[3].m_pszChId, "U1_4");
            strcpy(pChDefs->m_oChDef[4].m_pszChId, "I1_1");
            strcpy(pChDefs->m_oChDef[5].m_pszChId, "I1_2");
            strcpy(pChDefs->m_oChDef[6].m_pszChId, "I1_3");
            strcpy(pChDefs->m_oChDef[7].m_pszChId, "I1_4");
            pChDefs->m_oChDef[0].m_nEeType = STT_CH_EETYPE_VOLTAGE;
            pChDefs->m_oChDef[1].m_nEeType = STT_CH_EETYPE_VOLTAGE;
            pChDefs->m_oChDef[2].m_nEeType = STT_CH_EETYPE_VOLTAGE;
            pChDefs->m_oChDef[3].m_nEeType = STT_CH_EETYPE_VOLTAGE;
            pChDefs->m_oChDef[4].m_nEeType = STT_CH_EETYPE_CURRENT;
            pChDefs->m_oChDef[5].m_nEeType = STT_CH_EETYPE_CURRENT;
            pChDefs->m_oChDef[6].m_nEeType = STT_CH_EETYPE_CURRENT;
            pChDefs->m_oChDef[7].m_nEeType = STT_CH_EETYPE_CURRENT;
        }
    }

    if(g_theDeviceSystemParameter->m_nModuleCount_FT3 > 0)
    {
        g_theDeviceSystemParameter->m_nModuleCount_FT3 = 1;
        PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_FT3[0];

        if(pModule != NULL)
        {
            pModule->m_oModuleAttr.m_nModuleIndex = 15;//bit30�����ź�
            pModule->m_oModuleAttr.m_nFiberPortNum_STSend = 2;
			pModule->m_oModuleAttr.m_nFiberPortNum_STRecv = 0;
        }
    }

    if(g_theDeviceSystemParameter->m_nModuleCount_WEEK > 0)
    {
        g_theDeviceSystemParameter->m_nModuleCount_WEEK = 1;
        PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[0];

        if(pModule != NULL)
        {
            pModule->m_oModuleAttr.m_nModuleIndex = 14;//bit29�ź�
            pModule->m_oModuleAttr.m_nModulePower = STT_MODULE_WEEK_PNS331;
            pModule->m_oModuleAttr.m_nChannelNum = 8;
            PSTT_MODULE_CH_DEFS pChDefs = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs;
            PSTT_CH_DRV_POS pChDrvPos = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDrvPos;
            pChDrvPos->m_nChDrvPos[0] = 6;
            pChDrvPos->m_nChDrvPos[1] = 7;
            pChDrvPos->m_nChDrvPos[2] = 4;
            pChDrvPos->m_nChDrvPos[3] = 5;
            pChDrvPos->m_nChDrvPos[4] = 2;
            pChDrvPos->m_nChDrvPos[5] = 3;
            pChDrvPos->m_nChDrvPos[6] = 0;
            pChDrvPos->m_nChDrvPos[7] = 1;
            pModule->init_ch_drv_pos();
            //4U4I
            pChDefs->m_oChDef[0].m_nEeType = STT_CH_EETYPE_VOLTAGE;
            pChDefs->m_oChDef[1].m_nEeType = STT_CH_EETYPE_VOLTAGE;
            pChDefs->m_oChDef[2].m_nEeType = STT_CH_EETYPE_VOLTAGE;
            pChDefs->m_oChDef[3].m_nEeType = STT_CH_EETYPE_VOLTAGE;
            pChDefs->m_oChDef[4].m_nEeType = STT_CH_EETYPE_CURRENT;
            pChDefs->m_oChDef[5].m_nEeType = STT_CH_EETYPE_CURRENT;
            pChDefs->m_oChDef[6].m_nEeType = STT_CH_EETYPE_CURRENT;
            pChDefs->m_oChDef[7].m_nEeType = STT_CH_EETYPE_CURRENT;
        }
    }

    g_theDeviceSystemParameter->m_nModuleCount_D = 0;
    g_theDeviceSystemParameter->m_nModuleCount_S = 0;
    g_theSystemConfig->m_oPeripheral.m_b4G = 1;
    g_theSystemConfig->m_oPeripheral.m_bBle = 0;
    g_theSystemConfig->m_oPeripheral.m_bNetRj45 = 1;
    g_theSystemConfig->m_oPeripheral.m_bNetWifi = 0;
    g_theSystemConfig->m_oPeripheral.m_nLcdTimes = 0;
    m_nCommfd = open("/dev/SttDriver_PNS330", O_RDWR);
	g_nStateCount = read(m_nCommfd,NULL,0x201);
	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nStateCount = g_nStateCount;
	InitBuff();
    m_nTouchfd = open("/dev/exc7200dev", O_RDWR);	
	m_pMMapBuf = (Drv_MMapBuf *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
	qDebug() << "Driver Mmap = " << m_pMMapBuf;
#endif
    m_nRegCtrlDigital = 0;
    m_nRegCtrlDigital |= 1 << 0;
    //    m_nRegCtrlDigital |= 1<<1;//Ble default
    m_nRegCtrlDigital |= 1 << 2; //ON/OFF_FX1  default=1
    m_nRegCtrlDigital |= 1 << 3; //ON/OFF_FX2  default=1
    m_nRegCtrlDigital |= 1 << 4; //ON/OFF_FX3  default=1
    m_nRegCtrlDigital |= 1 << 5; //ON/OFF_FX4  default=1
    m_nRegCtrlDigital |= 1 << 7; //ON/OFF_FT3  default=1
    InitDApara(m_nCommfd, bHasAdjFile);
	long nFT3Idx = m_pIECConfigFt3->mdCnt;
	m_pIECConfigFt3->item[nFT3Idx].moduletype = STT_MODULE_TYPE_DIGITAL_2G6M;
	m_pIECConfigFt3->item[nFT3Idx].module = 0x4000;//�����ְ�ͬλ��
	m_pIECConfigFt3->item[nFT3Idx].nSTSendBeginIdx = -1;
	m_pIECConfigFt3->item[nFT3Idx].nSTSendEndIdx = -1;
	m_pIECConfigFt3->item[nFT3Idx].nSTRecvBeginIdx = 0;
	m_pIECConfigFt3->item[nFT3Idx].nSTRecvEndIdx = 1;
	m_pIECConfigFt3->mdCnt += 1;

    g_theSttDeviceStatus->m_nAnalogCount = 2;
    g_theSttDeviceStatus->m_oModule[0].m_nModuleType = STT_MODULE_TYPE_VOLT;
    g_theSttDeviceStatus->m_oModule[0].m_nModulePos = 0;
    g_theSttDeviceStatus->m_oModule[0].m_nChanNum = 6;
    g_theSttDeviceStatus->m_oModule[0].m_nNeedMonitor = 1;
    g_theSttDeviceStatus->m_oModule[1].m_nModuleType = STT_MODULE_TYPE_CURRENT;
    g_theSttDeviceStatus->m_oModule[1].m_nModulePos = 0;
    g_theSttDeviceStatus->m_oModule[1].m_nChanNum = 6;
    g_theSttDeviceStatus->m_oModule[1].m_nNeedMonitor = 1;
    g_theSttDeviceStatus->m_b4G = 1;
    g_theSttDeviceStatus->m_bBle = 0;
    g_theSttDeviceStatus->m_bWifi = 0;
    m_nRegCtrlAnalog = 0;
    RegisterValueInit(m_nRegCtrlAnalog);
    SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
    //Uart0
    SetRegisterValue(0xe0000018, 62); //4G
    SetRegisterValue(0xe0000034, 6);
    //���ڿ�����ʱ���ȡһ�ε�� 4G ������״̬,���ڵ�һ�ν�ʵ���ͼ����ʾ
    g_nGetSystemStateTickCnt = 1;
	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nSTModeSet = 2;
	m_oBatInfoRef0.fVolt = 0;
	m_oBatInfoRef0.fCurr = 0;
	m_oBatInfoRef1.fVolt = 0;
	m_oBatInfoRef1.fCurr = 0;
	g_pFpgaUart = new CFpgaUart;
	g_pFpgaUart->m_nUartType = 1;
	UartSettings *pUartSettings = &g_pFpgaUart->m_oUartSettings;
	pUartSettings->nUartCnt = 1;
	pUartSettings->oUartSetting[0].nBand = 115200;
	pUartSettings->oUartSetting[0].nStopBit = 0;
	pUartSettings->oUartSetting[0].nDatalen = 8;
	pUartSettings->oUartSetting[0].nCheck = 0;
	pUartSettings->oUartSetting[0].nOutput = 0;

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	g_nDrvMainSTMode = ioctl(m_nCommfd, 0x506, 0);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

    return m_nCommfd;
}

void CSttDevicePNS331::SetDrvMoudlePara()
{
    Drv_ModulePara oDrv_ModulePara;
    memset(&oDrv_ModulePara, 0, sizeof(Drv_ModulePara));
    oDrv_ModulePara.nAlgCnt = 3;
    memset(&m_oModuleMaxVaildCnt, 0, sizeof(Drv_ModuleMaxVaildCnt));
    int nHarmCnt = 31;
    oDrv_ModulePara.nAlgTable[0] = 0x8000;
    m_oModuleMaxVaildCnt.maxVaildCnt[0] = 8 + 8 * 3 * nHarmCnt;
    oDrv_ModulePara.nAlgTable[1] = 0x2000;
    m_oModuleMaxVaildCnt.maxVaildCnt[1] = 8 + 8 * 3 * nHarmCnt;
    oDrv_ModulePara.nAlgTable[2] = 0x4000;
	oDrv_ModulePara.nAlgType[2] = 1;
    m_oModuleMaxVaildCnt.maxVaildCnt[2] = DIGITAL_CHANNEL_MAX * nHarmCnt * 3;
    //BIO
    oDrv_ModulePara.nBiCnt = 1;
    oDrv_ModulePara.nBiTable[0] = 0x8000;
    oDrv_ModulePara.nBoCnt = 1;
    oDrv_ModulePara.nBoTable[0] = 0x8000;

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nfd, 0x331, 0);
	write(m_nfd, (char *)&oDrv_ModulePara, sizeof(Drv_ModulePara));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	Sleep(20);

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nfd, 0x356, 0);
	write(m_nfd, (char *)&m_oModuleMaxVaildCnt, sizeof(Drv_ModuleMaxVaildCnt));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void ResetPeripheralRtData()
{
    PSTT_MODULE_STATUS pParaV = &g_theSttDeviceStatus->m_oModule[0];
    long nValue;
    //��ѡЧ��Ϊ ��������
    g_theSttDeviceStatus->m_bWifi = 0;

    if(g_theSystemConfig->m_oPeripheral.m_bNetRj45)
    {
    }
    else if(g_theSystemConfig->m_oPeripheral.m_bNetWifi)
    {
        g_theSttDeviceStatus->m_bWifi = 1;
    }

    //��ѡЧ��Ϊ ����
    nValue = (pParaV->m_nWarningVal >> 3) & 0x01;

    if(nValue)
    {
        g_theSttDeviceStatus->m_bBle = 0;
    }
    else
    {
        g_theSttDeviceStatus->m_bBle = 1;
    }

    g_theSttDeviceStatus->m_b4G = 0;

    if(g_theSystemConfig->m_oPeripheral.m_b4G)
    {
        if(g_theSystemConfig->m_oPeripheral.m_bBle)
        {
        }
        else
        {
            g_theSttDeviceStatus->m_bBle = 0;
            nValue = (pParaV->m_nWarningVal >> 1) & 0x01;

            if(nValue)
            {
                g_theSttDeviceStatus->m_b4G = 0;
            }
            else
            {
                g_theSttDeviceStatus->m_b4G = 1;
            }
        }
    }
}

float BatCap_trans(float fV)
{
	float fBat = fV/3.0;

	if(fBat < 3.054)
	{
		return 5;
	}

	if(fBat < 3.15)
	{
		return 10;
	}

	if(fBat < 3.267)
	{
		return 20;
	}

	if(fBat < 3.310)
	{
		return 25;
	}

	if(fBat < 3.351)
	{
		return 30;
	}

	if(fBat < 3.418)
	{
		return 40;
	}

	if(fBat < 3.4876)
	{
		return 50;
	}

	if(fBat < 3.574)
	{
		return 60;
	}

	if(fBat < 3.6626)
	{
		return 70;
	}

	if(fBat < 3.699)
	{
		return 75;
	}

	if(fBat < 3.749)
	{
		return 80;
	}

	if(fBat < 3.857)
	{
		return 90;
	}

	if(fBat < 3.91)
	{
		return 95;
	}

	return 100;
}

void CSttDevicePNS331::GetModuleInfo(Drv_SysInfo *pSysInfo)
{
	char *pModule_cs = m_pDrvModuleBase + 0x1058;
	char *pModule_addr = m_pDrvModuleBase + 0x1054;
	char *pModule_data = m_pDrvModuleBase + 0x1014;

	for(int j = 0;j < 2;j++)
	{
		*pModule_cs = 0x01 << j;
		Sleep(1);
		for (int i = 0; i < 11; i++)
		{
			*pModule_addr = i;
			usleep(100);
			memcpy(&pSysInfo->stBack[j].dat[i],pModule_data,4);
		}
	}
}

int nFirstBatCap = -1;
unsigned int nPNS331Second = 0;
BOOL CSttDevicePNS331::IsLargeCurrentOutput()
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase != NULL && pSttTestBase->GetTestStarting() && g_theSystemConfig->m_nHasAnalog)
	{
		for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_UI;i++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[i];
			if(pModule != NULL && pModule->m_oModuleAttr.m_nModuleIndex == 16)
			{
				for(int j = 0; j < pModule->m_oModuleAttr.m_nChannelNum; j++)
				{
					PSTT_MODULE_CH_DEF pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j];
					if(pChDef->m_nEeType == STT_CH_EETYPE_CURRENT)
					{
						float fOutput = pChDef->m_fTotalCurAmp;
						if(fOutput > 5.0)
						{
							//����5A�������µ���
							return TRUE;
						}
					}
				}
			}
		}
	}

	return FALSE;
}

BOOL CSttDevicePNS331::OnTimer(BOOL bExec)
{
    GetVoltCurRtData();

    if(!bExec)
    {
        m_nDeviceOnTimerCount++;

		if(m_nDeviceOnTimerCount < 20)
        {
            return FALSE;
        }

        m_nDeviceOnTimerCount = 0;
    }

    if(!m_bDevStaIsInit)
    {
        return FALSE;
    }

    if(m_nTestStopTick >= 0)
    {
        m_nTestStopTick++;
    }

	nPNS331Second++;
    stt_init_stt_device_status();
    g_theSttDeviceStatus->m_nUdc = g_fAuxVolt > 0.001 ? 1 : 0;
#ifdef _PSX_QT_LINUX_
    memset(&m_oSysUtc, 0, sizeof(Drv_SysUtc));
	GetUtcInfo(&m_oSysUtc);

    g_theSttDeviceStatus->m_nUtc_s = m_oSysUtc.tm_h; //Ĭ��B����GPS����һ�£�ͳһΪ0ʱ��
	g_theSttDeviceStatus->m_nUtc_ns = m_oSysUtc.tm_l;
    g_theSttDeviceStatus->m_nUser_s = g_theSttDeviceStatus->m_nUtc_s
                                      + g_theSttDeviceStatus->m_nTimeZone * 3600;

    if(m_oSysUtc.tmFlag != 0)
    {
        g_theSttDeviceStatus->m_nSync = m_oSysUtc.tmFlag;
    }

    memset(&m_oSysInfo, 0, sizeof(Drv_SysInfo));
	GetModuleInfo(&m_oSysInfo);

    if(g_nGetSystemStateTickCnt > 0)
    {
        m_nBatCalcCnt = 21;
        g_nGetSystemStateTickCnt--;
    }

    if(m_nBatCalcCnt > 20)
    {
        if((m_nRegCtrlDigital >> 6) & 0x01)
        {
        }
        else
		{
			if(g_oDrvMutex.trylock(__FILE__,__FUNCTION__,__LINE__))
			{
				m_nRegCtrlDigital |= 1 << 6; //ON/OFF_KIO
				SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
				g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
				Sleep(50);
			}
        }
    }

    m_nBatCalcCnt++;
    AnalysisDrvSysInfo(m_oSysInfo.stBack[1], 0, STT_MODULE_TYPE_VOLT);
    AnalysisDrvSysInfo(m_oSysInfo.stBack[0], 1, STT_MODULE_TYPE_CURRENT);
	if(g_theSystemConfig->m_nHasAnalog == 0)
	{
		g_theSttDeviceStatus->m_nOverHeat = 0;//ģ�����
		g_theSttDeviceStatus->m_nIBreak = 0;//������·
		g_theSttDeviceStatus->m_nUShort = 0;//��ѹ��·
	}

	if((m_nRegCtrlDigital >> 6) & 0x01)
	{
		m_oBatInfo.fVolt = g_theSttDeviceStatus->m_oModule[0].m_fBAT[0];
		m_oBatInfo.fCurr = g_theSttDeviceStatus->m_oModule[1].m_fBAT[1];

		if(m_oBatInfo.fVolt > 9.0 && m_oBatInfo.fVolt < 13.0)
		{
			if(nFirstBatCap < 0)
			{
				g_theSttDeviceStatus->m_nBatCap = BatCap_trans(m_oBatInfo.fVolt);
				nFirstBatCap++;
			}
			m_nBatErrCnt = 0;
			g_theSttDeviceStatus->m_nBatErr = 0;
			int nValue = g_theSttDeviceStatus->m_oModule[0].m_nWarningVal & 0x01;
			//����̬
			if(m_oBatInfoRef0.fVolt < 9.0)
			{
				if(nValue == 1)
				{
					m_oBatInfoRef0.fVolt = m_oBatInfo.fVolt;
				}
			}

			if(nValue == 1 && m_oBatInfo.fCurr > 1.5)
			{
				//���̬
				if(m_oBatInfoRef1.fVolt < 9.0)
				{
					//��ǵ�һ�����
					m_oBatInfoRef1.fVolt = m_oBatInfo.fVolt;
					m_oBatInfoRef1.fCurr = m_oBatInfo.fCurr;
				}

				float fV = (m_oBatInfoRef0.fVolt - m_oBatInfoRef1.fVolt);
				fV = fV / m_oBatInfoRef1.fCurr;
				fV = fV * m_oBatInfo.fCurr;
				if(fV < 0)
					fV = 0;
				m_oBatInfo.fVolt = m_oBatInfo.fVolt + fV;
			}
			else
			{
				//���貹���������
			}

			if((nPNS331Second - m_nBatLastTime) > 10 || fBatList.count() > 10)
			{
				fBatList.clear();
			}

			m_nBatLastTime = nPNS331Second;
			if(!IsLargeCurrentOutput())
			{
				fBatList.append(m_oBatInfo.fVolt);
			}
		}
		else
		{
			m_nBatErrCnt++;
			if(m_nBatErrCnt > 2)
				g_theSttDeviceStatus->m_nBatErr = 1;//��ص�ѹ�ɼ��쳣
		}
	}

	if(fBatList.count() > 3)
	{
		float fMax = 0;
		float fMin = 13;
		float fValue;

		for(int i = 0; i < fBatList.count(); i++)
		{
			fValue = fBatList.at(i);

			if(fValue > fMax)
			{
				fMax = fValue;
			}

			if(fValue < fMin)
			{
				fMin = fValue;
			}
		}

		float fTotal = 0;
		for(int i = 0; i < fBatList.count(); i++)
		{
			fTotal += fBatList.at(i);
		}

		fTotal -= fMax;
		fTotal -= fMin;
		fTotal = fTotal/(fBatList.count() - 2);
		g_theSttDeviceStatus->m_nBatCap = BatCap_trans(fTotal);
	}

#endif
	QDir oDir("/mnt/Stt/Usb/1");

    if(oDir.exists())
    {
        g_theSttDeviceStatus->m_bUSB = 1;
    }
    else
    {
        g_theSttDeviceStatus->m_bUSB = 0;
    }

    int nValue = g_theSttDeviceStatus->m_oModule[0].m_nWarningVal & 0x01;

    if(nValue)
    {
        g_theSttDeviceStatus->m_bPowerAC = 0;
    }
    else
    {
        g_theSttDeviceStatus->m_bPowerAC = 1;
    }

    CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

    if(pSttTestBase == NULL)
    {
        if(m_nBatCalcCnt > 26)
        {
            if((m_nRegCtrlDigital >> 6) & 0x01)
			{
				if(g_oDrvMutex.trylock(__FILE__,__FUNCTION__,__LINE__))
				{
					m_nRegCtrlDigital &= ~(1 << 6); //ON/OFF_KIO
					SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
					m_nBatCalcCnt = 0;
					g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
				}
            }
        }
    }
    else
    {
        if(pSttTestBase->GetTestStarting())
        {
        }
        else
        {
			if(m_nTestStopTick > 10)
			{
                if((m_nRegCtrlDigital >> 6) & 0x01)
				{
					if(g_oDrvMutex.trylock(__FILE__,__FUNCTION__,__LINE__))
					{
						m_nTestStopTick = -1;
						m_nRegCtrlDigital &= ~(1 << 6); //ON/OFF_KIO
						SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
						m_nBatCalcCnt = 0;
						g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
					}
                }
            }
            else
            {
                if(m_nBatCalcCnt > 26)
                {
                    if((m_nRegCtrlDigital >> 6) & 0x01)
					{
						if(g_oDrvMutex.trylock(__FILE__,__FUNCTION__,__LINE__))
						{
							m_nRegCtrlDigital &= ~(1 << 6); //ON/OFF_KIO
							SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
							m_nBatCalcCnt = 0;
							g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
						}
                    }
                }
            }
        }
    }

    ResetPeripheralRtData();
    return TRUE;
}

float BatTemp_trans(float fVdcmV)
{
	if(fVdcmV < 907)
	{
		return 80;
	}
	else if(fVdcmV > 1885)
	{
		return -40;
	}
	else
	{
		float fDiff = fVdcmV - 907;
		return 80.0 - fDiff/(1885.0 - 907.0)*120.0;
	}
}

float VoltPower_trans(float fVdcmV)
{
	if(fVdcmV < -3041.68)
	{
		return -180 + (3041.68 + fVdcmV)*(180 - 380)/(3041.68 - 6421.33);
	}
	else if(fVdcmV < 3041.68)
	{
		return fVdcmV/3041.68*180;
	}
	else
	{
		return 180 + (fVdcmV-3041.68)*(380-180)/(6421.33-3041.68);
	}
}

void CSttDevicePNS331::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack, int nModulePos, int nModuleType)
{
    //bit0-volt //bit1-current
#ifdef _PSX_QT_LINUX_
    STT_MODULE_STATUS &oModuleStatus = g_theSttDeviceStatus->m_oModule[nModulePos];
    unsigned short unmin, unMax, voltdc;
    float fBatTemp;

    if(nModuleType == STT_MODULE_TYPE_CURRENT)
    {
        unmin = oDrv_FeedBack.dat[0] & 0xfff;
        unMax = (oDrv_FeedBack.dat[0] >> 16) & 0xfff;
        oModuleStatus.m_oChannel[2].m_fVoltMin = translateVoltBase(unmin, 10.4);
        oModuleStatus.m_oChannel[2].m_fVoltMax = translateVoltBase(unMax, 10.4);
        unmin = oDrv_FeedBack.dat[2] & 0xfff;
        unMax = (oDrv_FeedBack.dat[2] >> 16) & 0xfff;
        oModuleStatus.m_oChannel[0].m_fVoltMin = translateVoltBase(unmin, 10.4);
        oModuleStatus.m_oChannel[0].m_fVoltMax = translateVoltBase(unMax, 10.4);
        unmin = oDrv_FeedBack.dat[3] & 0xfff;
        unMax = (oDrv_FeedBack.dat[3] >> 16) & 0xfff;
        oModuleStatus.m_oChannel[1].m_fVoltMin = translateVoltBase(unmin, 10.4);
        oModuleStatus.m_oChannel[1].m_fVoltMax = translateVoltBase(unMax, 10.4);
        unmin = oDrv_FeedBack.dat[5] & 0xfff;
        unMax = (oDrv_FeedBack.dat[5] >> 16) & 0xfff;
        oModuleStatus.m_oChannel[5].m_fVoltMin = translateVoltBase(unmin, 10.4);
        oModuleStatus.m_oChannel[5].m_fVoltMax = translateVoltBase(unMax, 10.4);
        unmin = oDrv_FeedBack.dat[6] & 0xfff;
        unMax = (oDrv_FeedBack.dat[6] >> 16) & 0xfff;
        oModuleStatus.m_oChannel[4].m_fVoltMin = translateVoltBase(unmin, 10.4);
        oModuleStatus.m_oChannel[4].m_fVoltMax = translateVoltBase(unMax, 10.4);
        unmin = oDrv_FeedBack.dat[7] & 0xfff;
        unMax = (oDrv_FeedBack.dat[7] >> 16) & 0xfff;
        oModuleStatus.m_oChannel[3].m_fVoltMin = translateVoltBase(unmin, 10.4);
        oModuleStatus.m_oChannel[3].m_fVoltMax = translateVoltBase(unMax, 10.4);
        unMax = (oDrv_FeedBack.dat[8] >> 16) & 0xfff;
		float fBatI = translateVoltBase(unMax, 19.6);
		oModuleStatus.m_fBAT[1] = fBatI * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBatICoef;

        //���Ƶ�Դ
        voltdc = (oDrv_FeedBack.dat[4] >> 16) & 0xfff; //BAT_temp1
		fBatTemp = translateVoltBase(voltdc, 10.0);
        oModuleStatus.m_fVoltDc[1] = BatTemp_trans(fBatTemp * 1000);
		// CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("FPGA BAT_temp1 Code=%d, Volt=%f, Temp=%f"),
		// 						   voltdc,fBatTemp,oModuleStatus.m_fVoltDc[1]);
        voltdc =  oDrv_FeedBack.dat[4] & 0xfff; //BAT_temp2
		fBatTemp = translateVoltBase(voltdc, 10.0);
        oModuleStatus.m_fVoltDc[0] = BatTemp_trans(fBatTemp * 1000);
		// CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("FPGA BAT_temp2 Code=%d, Volt=%f, Temp=%f"),
		// 						   voltdc,fBatTemp,oModuleStatus.m_fVoltDc[0]);
    }
    else
    {
        oModuleStatus.m_nWarningVal = oDrv_FeedBack.dat[9];
        unMax = (oDrv_FeedBack.dat[8] >> 16) & 0xfff;
		float fBatV = translateVoltBase(unMax, 14.0);
		oModuleStatus.m_fBAT[0] = fBatV * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBatVCoef;

        //���Ƶ�Դ
        voltdc = (oDrv_FeedBack.dat[4] >> 16) & 0xfff; //BAT_V8.4
        oModuleStatus.m_fVoltDc[1] = translateVoltBase(voltdc, 10) / 7.85 * 8.31;
        voltdc =  oDrv_FeedBack.dat[4] & 0xfff; //BAT_V4.2
        oModuleStatus.m_fVoltDc[0] = translateVoltBase(voltdc, 5) / 4.23 * 4.15;
    }

    //���ʵ�Դ
    if(nModuleType == STT_MODULE_TYPE_VOLT)
    {
        voltdc = (oDrv_FeedBack.dat[1] >> 16) & 0xfff;
		float fADC = 0;
		fADC = translateVoltBase(voltdc, 10.0);
		oModuleStatus.m_fVoltDc[2] = VoltPower_trans(fADC * 1000);
		// CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("VOLT+ Code=%d, ADC=%f, Volt=%f"),
		// 						   voltdc,fADC,oModuleStatus.m_fVoltDc[2]);
        voltdc =  oDrv_FeedBack.dat[1] & 0xfff;
		fADC = translateVoltBase(voltdc, 10.0);
		oModuleStatus.m_fVoltDc[3] = VoltPower_trans(fADC * 1000);
		// CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("VOLT- Code=%d, ADC=%f, Volt=%f"),
		// 						   voltdc,fADC,oModuleStatus.m_fVoltDc[3]);
    }
    else
    {
        voltdc = (oDrv_FeedBack.dat[1] >> 16) & 0xfff;
        oModuleStatus.m_fVoltDc[2] = translateVoltBase(voltdc, 10.4);
        voltdc =  oDrv_FeedBack.dat[1] & 0xfff;
        oModuleStatus.m_fVoltDc[3] = translateVoltBase(voltdc, 10.4);
    }

    unsigned short tempMax = 0;
	// unsigned short temp = (oDrv_FeedBack.dat[9] >> 16) & 0xfff;
	int temp = oDrv_FeedBack.dat[9]&0xffff0000;
	temp = temp>>16;
    temp  = temp * 0.0625;
    oModuleStatus.m_nTemp[0] = temp;

	if(temp > 0 && tempMax < temp)
    {
        tempMax = temp;
    }

	// temp = (oDrv_FeedBack.dat[9]) & 0xfff;
	temp = oDrv_FeedBack.dat[9]<<16;
	temp = temp>>16;
    temp  = temp * 0.0625;
    oModuleStatus.m_nTemp[1] = temp;

	if(temp > 0 && tempMax < temp)
    {
        tempMax = temp;
    }

	// temp = (oDrv_FeedBack.dat[10] >> 16) & 0xfff;
	temp = oDrv_FeedBack.dat[10]&0xffff0000;
	temp = temp>>16;
    temp  = temp * 503.975 / 4096 - 273.15;
    oModuleStatus.m_nTemp[2] = temp;

	if(temp > 0 && tempMax < temp)
    {
        tempMax = temp;
    }

    unsigned short nH = (oDrv_FeedBack.dat[10]) & 0x1;
    oModuleStatus.m_nIsVoltHot = nH; //��ѹ����

    if(nModuleType == STT_MODULE_TYPE_VOLT)
    {
        long nValue;
        nValue = (oModuleStatus.m_nWarningVal >> 11) & 0x01;

        if(nValue == 0)
        {
            oModuleStatus.m_oChannel[0].m_bIsOverLoad = 1;
            g_theSttDeviceStatus->m_nUShort = 1;
        }

        nValue = (oModuleStatus.m_nWarningVal >> 10) & 0x01;

        if(nValue == 0)
        {
            oModuleStatus.m_oChannel[1].m_bIsOverLoad = 1;
            g_theSttDeviceStatus->m_nUShort = 1;
        }

        nValue = (oModuleStatus.m_nWarningVal >> 9) & 0x01;

        if(nValue == 0)
        {
            oModuleStatus.m_oChannel[2].m_bIsOverLoad = 1;
            g_theSttDeviceStatus->m_nUShort = 1;
        }

        nValue = (oModuleStatus.m_nWarningVal >> 8) & 0x01;

        if(nValue == 0)
        {
            oModuleStatus.m_oChannel[3].m_bIsOverLoad = 1;
            g_theSttDeviceStatus->m_nUShort = 1;
        }

        nValue = (oModuleStatus.m_nWarningVal >> 7) & 0x01;
        nValue = nValue > 0 ? 0 : 1; //Ӳ���ź�ȡ��

        if(nValue)
        {
            g_theSttDeviceStatus->m_nOverHeat = 1;
        }
    }
    else
    {
        long nChanNum = 3;//3I
        PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule == NULL)
        {
			return;
        }

		if(pModule->m_oModuleAttr.m_nChannelNum > 7)
		{
			nChanNum = 6;//6I
		}

        CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

        if(pSttTestBase != NULL && pSttTestBase->GetTestStarting() && g_theSystemConfig->m_nHasAnalog)
        {
			float fChannelVoltMax, fChannelVoltMin, fChannelVolt;
			float fOutput = 0.0;
			long nCurIndex = 0;

			for(int j = 0; j < pModule->m_oModuleAttr.m_nChannelNum; j++)
			{
				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					nCurIndex = j;
					break;
				}
			}

			for(int j = 0; j < 6; j++)
			{
				if(j < nChanNum)
				{
					fChannelVoltMax = fabs(oModuleStatus.m_oChannel[j].m_fVoltMax);
					fChannelVoltMin = fabs(oModuleStatus.m_oChannel[j].m_fVoltMin);
					fChannelVolt = (fChannelVoltMax + fChannelVoltMin)/2.0;
					fOutput = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nCurIndex+j].m_fTotalCurAmp;

					if(fOutput > 0.099)
					{
						if(fChannelVolt < 1.5)
						{
							//������·
						}
						else
						{
							//������·
							oModuleStatus.m_oChannel[j].m_bIsOverLoad = 1;
							g_theSttDeviceStatus->m_nIBreak = 1;
						}
					}
				}
			}
        }
    }

    nH = (oDrv_FeedBack.dat[10] >> 7) & 0x1;
    oModuleStatus.m_nIsDCHot = nH; //ֱ������

    if(nModuleType == STT_MODULE_TYPE_VOLT)
    {
        nH = (oDrv_FeedBack.dat[10] >> 8) & 0x1;
        oModuleStatus.m_nIsVoltWarining = nH; //��ѹ�澯
    }

    nH = (oDrv_FeedBack.dat[10] >> 9) & 0x1;
    oModuleStatus.m_nIsMissWarining = nH; //���Ը澯
#endif
}

void CSttDevicePNS331::GetVoltCurRtData()
{
    CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

    if(pSttTestBase == NULL)
    {
        return;
    }

    GetRtData();
}

void CSttDevicePNS331::SetRegisterValue(unsigned int nAddr, unsigned int nValue)
{
	//���Ƶ����ô�
    ioctl(m_nfd, nAddr, nValue);
}

void CSttDevicePNS331::DAPowerCtrl()
{
	unsigned int nFPGADelay = 1;//б�ʿ���
	nFPGADelay |= 50<<16;

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	SetRegisterValue(PNS330_RegAddr_FPGACtrl, nFPGADelay);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttDevicePNS331::PreStartTestPro()
{
    m_nTestStopTick = -1;
	m_nRegCtrlDigital |= 1 << 6; //ON/OFF_KIO

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	if(g_theSystemConfig->m_nHasAnalog)
	{
		m_nRegCtrlAnalog |= 1 << 8; //ON/OFF_PA
		m_nRegCtrlAnalog &= ~(1 << 19); //LED_VOUT
		m_nRegCtrlAnalog |= 1 << 9; //ON/OFF_VI
		m_nRegCtrlAnalog |= 1 << 20; //K_VPout
		m_nRegCtrlAnalog |= 1 << 21; //K_IPout

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
		Sleep(500);//�ȴ���ѹ��Դ�͵�����Դ��ȫ����
	}
	else
	{
		if(g_theSystemConfig->m_nHasWeek)
		{
			//С�ź���Ҫ��һ���Դ
			m_nRegCtrlAnalog |= 1 << 9; //ON/OFF_VI

			g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
			SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
			g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
		}
	}
}

void CSttDevicePNS331::SetPeripheral()
{
    tmt_Peripheral *pPeripheral = &g_theSystemConfig->m_oPeripheral;
    //Һ������ ����bit7-bit0 [0,100] ���ú��ɴ��������Զ�ά��������ʱ��,��λ���� bit15-bit8 [0,10],0����һֱ����
    //bit23-bit16 ��������,bit31-bit24 ��������
	unsigned int nMaxLcdLight = 70;//���Ȱٷֱ�
	if(pPeripheral->m_nLcdLight >= 1 && pPeripheral->m_nLcdLight <= 5)
	{
		nMaxLcdLight = pPeripheral->m_nLcdLight * 14;
	}

	unsigned int nValue = nMaxLcdLight;
    if(pPeripheral->m_nLcdTimes > 10)
    {
        pPeripheral->m_nLcdTimes = 10;
    }

    if(pPeripheral->m_nLcdTimes < 0)
    {
        pPeripheral->m_nLcdTimes = 0;
    }

    nValue |= pPeripheral->m_nLcdTimes << 8;
    nValue |= 5 << 16;//ʵ�����Ȼ�����
	nValue |= nMaxLcdLight << 24;
    ioctl(m_nTouchfd, 0x7000002c, nValue);
    m_nRegCtrlDigital |= 1 << 0; //1-100M,0-wifi

    if(pPeripheral->m_bNetRj45)
    {
    }
    else if(pPeripheral->m_bNetWifi)
    {
        m_nRegCtrlDigital &= ~(1 << 0);
    }

    long nBleMode = 1;

    if(pPeripheral->m_bBle)
    {
    }
    else if(pPeripheral->m_b4G)
    {
        nBleMode = 0;
    }

    if(nBleMode)
    {
        m_nRegCtrlDigital |= 1 << 1; //1-ble,0-4G

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		SetRegisterValue(0xe0000018, 124); //57600
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
    }
    else
    {
        m_nRegCtrlDigital &= ~(1 << 1);

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		SetRegisterValue(0xe0000018, 62); //115200
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
    }

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
	//����ST��ģʽ���ã�330Ĭ��RX2��B��
	ioctl(m_nfd, 0x102, m_nMainSTMode); //00-None 01:FT3 10:PPS 11:BCode
	g_nDrvMainSTMode = m_nMainSTMode;
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttDevicePNS331::AfterTestFinishedPro()
{
    BOOL bUse = FALSE;

    if(g_theSystemConfig->m_nHasAnalog)
    {
        m_nRegCtrlAnalog &= ~(1 << 8); //ON/OFF_PA
        m_nRegCtrlAnalog &= ~(1 << 9); //ON/OFF_VI
        m_nRegCtrlAnalog &= ~(1 << 20); //K_VPout
        m_nRegCtrlAnalog &= ~(1 << 21); //K_IPout
        bUse = TRUE;
    }

    if(g_theSystemConfig->m_nHasWeek)
    {
        m_nRegCtrlAnalog &= ~(1 << 9); //ON/OFF_VI
        bUse = TRUE;
    }

    if(bUse)
	{
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
    }

    m_nTestStopTick = 0;
}

BOOL CSttDevicePNS331::SetOutputTime(tmt_channel *pChannel, BOOL bDc, float &fOutPutTime)
{
    if(!g_theSystemConfig->m_nHasAnalog)
    {
		return FALSE;
    }

    if(pChannel == NULL)
    {
		return FALSE;
    }

    PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[0];

    if(pModule == NULL)
    {
		return FALSE;
    }

    float fIMax = 0;
    float fAmp;
	float fCTRate = 1.0;

	for(int k = 0; k < pModule->m_oModuleAttr.m_nChannelNum; k++)
    {
        if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE) //'U'
        {
            continue;
        }

        m_nTmtPos = pModule->m_nChTmtPos[k];

        if(m_nTmtPos < 0)
        {
            continue;
        }

		if(g_nTmtParaMode == 0)
		{
			//����һ��ֵ
			fCTRate = g_theSystemConfig->GetCTRate(m_nTmtPos/3);
		}
		else
		{
			fCTRate = 1.0;
		}

        fAmp = pChannel[m_nTmtPos].Harm[1].fAmp;

		for(int i = 2; i <= 31; i++)
		{
			fAmp += pChannel[m_nTmtPos].Harm[i].fAmp;
		}

        if(fAmp > fIMax)
        {
            fIMax = fAmp;
        }
    }

	if(bDc)
	{
		fIMax = fIMax * 2;
	}

	long nPowerMode = STT_CurrentMODULE_POWER_LOW;

    for(int nIndex = 0; nIndex < g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum; nIndex++)
    {
        tmt_CurModuleGear &oCurModuleGear = g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];

        if(oCurModuleGear.m_nModulePos == pModule->m_oModuleAttr.m_nModuleIndex)
        {
            nPowerMode = oCurModuleGear.m_nIPowerMode;
            break;
        }
    }

	fOutPutTime = 0.0;

    if(nPowerMode == STT_CurrentMODULE_POWER_HIGH)
    {
        if(fIMax > 5)
        {
            fOutPutTime = 0.5 * 10.0 * 10.0 / fIMax;
        }
        else
        {
            fOutPutTime = 0.5 * 90.0 * 10.0 / fIMax;
        }
    }
    else
    {
        if(fIMax > 5)
        {
            fOutPutTime = 10.0 * 10.0 / fIMax;
        }
        else
        {
            fOutPutTime = 90.0 * 10.0 / fIMax;
        }
    }

	return TRUE;
}

void CSttDevicePNS331::Stt_Xml_Serialize_Channels(CSttXmlSerializeBase *pXmlSerialize)
{
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
	pXmlModule->xml_serialize("�����¶�", "T1", "deg", "long", pParaI->m_nTemp[1]);
	pXmlModule->xml_serialize("ɢ�����¶�", "T2", "deg", "long", pParaI->m_nTemp[0]);
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
}
