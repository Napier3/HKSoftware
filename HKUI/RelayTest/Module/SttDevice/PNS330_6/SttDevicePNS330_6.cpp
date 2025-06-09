#include "SttDevicePNS330_6.h"
#include "math.h"
#include "../Module/PowerCtrl/UI/PNS330/SttPowerCtrl_PNS330.h"

CSttDevicePNS330_6 *CSttDevicePNS330_6::g_pSttDevicePNS330_6 = NULL;
long CSttDevicePNS330_6::g_nSttDeviceRef = 0;

QList<float> fBatList;

CSttDevicePNS330_6::CSttDevicePNS330_6()
{
	//主板ST口模式设置，330默认RX2是B码
	//00-None 01:FT3 10:PPS 11:BCode
	m_nMainSTMode = 0b1110;
}

CSttDevicePNS330_6::~CSttDevicePNS330_6()
{
}

void CSttDevicePNS330_6::Create()
{
	g_nSttDeviceRef++;

	if(g_nSttDeviceRef == 1)
	{
		g_pSttDevicePNS330_6 = new CSttDevicePNS330_6;
		g_pSttDeviceBase = (CSttDeviceBase *)g_pSttDevicePNS330_6;
	}
}

void CSttDevicePNS330_6::Release()
{
	g_nSttDeviceRef--;

	if(g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePNS330_6;
		g_pSttDevicePNS330_6 = NULL;
	}
}

void RegisterValueInit(unsigned int &nRegisterVal)
{
	nRegisterVal &= ~(1 << 8); //ON/OFF_PA default=0
	nRegisterVal &= ~(1 << 9); //ON/OFF_VI default=0
	nRegisterVal |= 1 << 19; //LED_VOUT     default=1
	nRegisterVal &= ~(1 << 21); //K_IPout   default=0
	nRegisterVal &= ~(1 << 20); //K_VPout   default=0
	nRegisterVal &= ~(1 << 17);//K_IPout2   default=0
}

int CSttDevicePNS330_6::InitDevice(BOOL bHasAdjFile)
{
	m_nBatVoltAD = 0;
	m_nBatCurAD = 0;
	m_nBatLastTime = 0;
	fBatList.clear();
	m_nCommfd = open("/dev/SttDriver_PNS330", O_RDWR);
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	g_nStateCount = read(m_nCommfd,NULL,0x201);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nStateCount = g_nStateCount;
	InitBuff();

	m_nRegCtrlDigital = 0;
	m_nRegCtrlDigital |= 1 << 0;
	m_nRegCtrlDigital |= 1 << 7; //ON/OFF_FT3  default=1

	m_nVoltPowerRefVal = 0;
	m_nCurrPowerRefVal = 0;
	m_nTestStopTick = -1;
	m_nBatCalcCnt = 0;
	m_nBatErrCnt = 0;
	//PNS330只有一个bit31的模拟信号和一个bit30数字信号

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		g_theDeviceSystemParameter->m_nModuleCount_UI = 1;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule != NULL)
		{
			pModule->m_oModuleAttr.m_nModuleIndex = 16;//bit31模拟信号

			//默认机型配置 120V10A
			pModule->m_oModuleAttr.m_nModulePower = STT_MODULE_UI_PNS330_6;
			pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrl_PNS330);

			PSTT_MODULE_CH_DEFS pChDefs = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs;
			PSTT_CH_DRV_POS pChDrvPos = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDrvPos;

			if(pModule->m_oModuleAttr.m_nChannelNum == 12)
			{
				//6U6I
				pChDrvPos->m_nChDrvPos[0] = 6;
				pChDrvPos->m_nChDrvPos[1] = 7;
				pChDrvPos->m_nChDrvPos[2] = 4;
				pChDrvPos->m_nChDrvPos[3] = 5;
				pChDrvPos->m_nChDrvPos[4] = 10;
				pChDrvPos->m_nChDrvPos[5] = 11;
				pChDrvPos->m_nChDrvPos[6] = 2;
				pChDrvPos->m_nChDrvPos[7] = 3;
				pChDrvPos->m_nChDrvPos[8] = 0;
				pChDrvPos->m_nChDrvPos[9] = 1;
				pChDrvPos->m_nChDrvPos[10] = 8;
				pChDrvPos->m_nChDrvPos[11] = 9;
				pModule->init_ch_drv_pos();

				strcpy(pChDefs->m_oChDef[0].m_pszChId, "U1_1");
				strcpy(pChDefs->m_oChDef[1].m_pszChId, "U1_2");
				strcpy(pChDefs->m_oChDef[2].m_pszChId, "U1_3");
				strcpy(pChDefs->m_oChDef[3].m_pszChId, "U1_4");
				strcpy(pChDefs->m_oChDef[4].m_pszChId, "U1_5");
				strcpy(pChDefs->m_oChDef[5].m_pszChId, "U1_6");
				strcpy(pChDefs->m_oChDef[6].m_pszChId, "I1_1");
				strcpy(pChDefs->m_oChDef[7].m_pszChId, "I1_2");
				strcpy(pChDefs->m_oChDef[8].m_pszChId, "I1_3");
				strcpy(pChDefs->m_oChDef[9].m_pszChId, "I1_4");
				strcpy(pChDefs->m_oChDef[10].m_pszChId, "I1_5");
				strcpy(pChDefs->m_oChDef[11].m_pszChId, "I1_6");
				pChDefs->m_oChDef[0].m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDefs->m_oChDef[1].m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDefs->m_oChDef[2].m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDefs->m_oChDef[3].m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDefs->m_oChDef[4].m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDefs->m_oChDef[5].m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDefs->m_oChDef[6].m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDefs->m_oChDef[7].m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDefs->m_oChDef[8].m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDefs->m_oChDef[9].m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDefs->m_oChDef[10].m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDefs->m_oChDef[11].m_nEeType = STT_CH_EETYPE_CURRENT;
			}
		}
	}

	if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
	{
		g_theDeviceSystemParameter->m_nModuleCount_D = 1;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[0];

		if(pModule != NULL)
		{
			pModule->m_oModuleAttr.m_nModuleIndex = 15;//bit30数字信号
			pModule->m_oModuleAttr.m_nFiberPortNum_LC = 4;
			pModule->m_oModuleAttr.m_nFiberPortNum_STSend = 2;
			pModule->m_oModuleAttr.m_nFiberPortNum_STRecv = 0;
		}

		//打开4个光模块电源
		m_nRegCtrlDigital &= ~(1 << 2);
		m_nRegCtrlDigital &= ~(1 << 3);
		m_nRegCtrlDigital &= ~(1 << 4);
		m_nRegCtrlDigital &= ~(1 << 5);

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}

	g_theSystemConfig->m_oPeripheral.m_b4G = 1;//默认4G启动
	g_theSystemConfig->m_oPeripheral.m_bBle = 0;
	g_theSystemConfig->m_oPeripheral.m_bNetRj45 = 1;
	g_theSystemConfig->m_oPeripheral.m_bNetWifi = 0;
	g_theSystemConfig->m_oPeripheral.m_nLcdTimes = 0;
	m_nTouchfd = open("/dev/exc7200dev", O_RDWR);
	m_pMMapBuf = (Drv_MMapBuf *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
	qDebug() << "Driver Mmap = " << m_pMMapBuf;
#endif

	InitDApara(m_nCommfd, bHasAdjFile);
	long nFT3Idx = m_pIECConfigFt3->mdCnt;
	m_pIECConfigFt3->item[nFT3Idx].moduletype = STT_MODULE_TYPE_DIGITAL_2G6M;
	m_pIECConfigFt3->item[nFT3Idx].module = 0x4000;//与数字板同位置
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
	g_theSttDeviceStatus->m_nBatCap = 100;
	m_nRegCtrlAnalog = 0;
	RegisterValueInit(m_nRegCtrlAnalog);

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
	//Uart0
	SetRegisterValue(0xe0000018, 62); //4G
	SetRegisterValue(0xe0000034, 6);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	//便于开机的时候获取一次电池 4G 蓝牙的状态,用于第一次进实验的图标显示
	g_nGetSystemStateTickCnt = 1;
	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nSTModeSet = 2;
	m_oBatInfoRef0.fVolt = 0;
	m_oBatInfoRef0.fCurr = 0;
	m_oBatInfoRef1.fVolt = 0;
	m_oBatInfoRef1.fCurr = 0;

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	g_nDrvMainSTMode = ioctl(m_nCommfd, 0x506, 0);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	return m_nCommfd;
}

void CSttDevicePNS330_6::SetDrvMoudlePara()
{
	Drv_ModulePara oDrv_ModulePara;
	memset(&oDrv_ModulePara, 0, sizeof(Drv_ModulePara));
	oDrv_ModulePara.nAlgCnt = 0;
	memset(&m_oModuleMaxVaildCnt, 0, sizeof(Drv_ModuleMaxVaildCnt));
	int nHarmCnt = 31;

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		int nIndex = oDrv_ModulePara.nAlgCnt;
		oDrv_ModulePara.nAlgTable[nIndex] = 0x8000;
		m_oModuleMaxVaildCnt.maxVaildCnt[nIndex] = 12 + 12 * 3 * nHarmCnt;
		oDrv_ModulePara.nAlgCnt++;
	}

	if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
	{
		int nIndex = oDrv_ModulePara.nAlgCnt;
		oDrv_ModulePara.nAlgTable[nIndex] = 0x4000;
		oDrv_ModulePara.nAlgType[nIndex] = 1;
		m_oModuleMaxVaildCnt.maxVaildCnt[nIndex] = DIGITAL_CHANNEL_MAX * nHarmCnt * 3;
		oDrv_ModulePara.nAlgCnt++;
	}

	//BIO
	oDrv_ModulePara.nBiCnt = 1;
	oDrv_ModulePara.nBiTable[0] = 0x8000;
	oDrv_ModulePara.nBoCnt = 1;
	oDrv_ModulePara.nBoTable[0] = 0x8000;

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nfd, 0x331, 0);
	write(m_nfd, (char *)&oDrv_ModulePara, sizeof(Drv_ModulePara));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	Sleep(10);

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nfd, 0x356, 0);
	write(m_nfd, (char *)&m_oModuleMaxVaildCnt, sizeof(Drv_ModuleMaxVaildCnt));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void ResetPeripheralRtData()
{
	PSTT_MODULE_STATUS pParaV = &g_theSttDeviceStatus->m_oModule[0];
	long nValue;
	//复选效果为 有线网卡
	g_theSttDeviceStatus->m_bWifi = 0;

	if(g_theSystemConfig->m_oPeripheral.m_bNetRj45)
	{
	}
	else if(g_theSystemConfig->m_oPeripheral.m_bNetWifi)
	{
		g_theSttDeviceStatus->m_bWifi = 1;
	}

	//复选效果为 蓝牙
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
	float fBat = fV/4.0;

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

void CSttDevicePNS330_6::GetModuleInfo(Drv_SysInfo *pSysInfo)
{
	char *pModule_cs,*pModule_addr,*pModule_data;
	pModule_cs = m_pDrvModuleBase + 0x1058;
	pModule_addr = m_pDrvModuleBase + 0x1054;
	pModule_data = m_pDrvModuleBase + 0x1014;

	*pModule_cs = 0x01 << 0;
	Sleep(1);
	for (int i = 0; i < 11; i++)
	{
		*pModule_addr = i;
		Sleep(1);
		memcpy(&pSysInfo->stBack[0].dat[i],pModule_data,4);
	}

	*pModule_cs = 0x01 << 1;
	Sleep(1);
	for (int i = 0; i < 11; i++)
	{
		*pModule_addr = i;
		Sleep(1);
		memcpy(&pSysInfo->stBack[1].dat[i],pModule_data,4);
	}
}

int nFirstBatCap = -1;
unsigned int nPNS330Second = 0;
BOOL CSttDevicePNS330_6::IsLargeCurrentOutput()
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
							//超过5A，不更新电量
							return TRUE;
						}
					}
				}
			}
		}
	}

	return FALSE;
}

BOOL CSttDevicePNS330_6::OnTimer(BOOL bExec)
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

	nPNS330Second++;
	stt_init_stt_device_status();
	g_theSttDeviceStatus->m_nUdc = g_fAuxVolt > 0.001 ? 1 : 0;
#ifdef _PSX_QT_LINUX_
	memset(&m_oSysUtc, 0, sizeof(Drv_SysUtc));
	GetUtcInfo(&m_oSysUtc);

	g_theSttDeviceStatus->m_nUtc_s = m_oSysUtc.tm_h; //默认B码与GPS保持一致，统一为0时区
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
		g_theSttDeviceStatus->m_nOverHeat = 0;//模块过热
		g_theSttDeviceStatus->m_nIBreak = 0;//电流开路
		g_theSttDeviceStatus->m_nUShort = 0;//电压短路
	}

	if((m_nRegCtrlDigital >> 6) & 0x01)
	{
		m_oBatInfo.fVolt = g_theSttDeviceStatus->m_oModule[0].m_fBAT[0];
		m_oBatInfo.fCurr = g_theSttDeviceStatus->m_oModule[1].m_fBAT[1];

		if(m_oBatInfo.fVolt > 12.0 && m_oBatInfo.fVolt < 17.0)
		{
			if(nFirstBatCap < 0)
			{
				g_theSttDeviceStatus->m_nBatCap = BatCap_trans(m_oBatInfo.fVolt);
				nFirstBatCap++;
			}
			m_nBatErrCnt = 0;
			g_theSttDeviceStatus->m_nBatErr = 0;
			int nValue = g_theSttDeviceStatus->m_oModule[0].m_nWarningVal & 0x01;
			//待机态
			if(m_oBatInfoRef0.fVolt < 12.0)
			{
				if(nValue == 1)
				{
					m_oBatInfoRef0.fVolt = m_oBatInfo.fVolt;
				}
			}

			//待机时电流可能是一个[-0.0009～0.01]内的小值
			if(m_oBatInfo.fCurr > 1.5)
			{
				//输出态,打开DA电源，采到电流值
				if(m_oBatInfoRef1.fVolt < 12.0)
				{
					//标记第一次输出
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
				//无需补偿电池内阻
			}

			if((nPNS330Second - m_nBatLastTime) > 10 || fBatList.count() > 10)
			{
				fBatList.clear();
			}

			m_nBatLastTime = nPNS330Second;
			if(!IsLargeCurrentOutput())
			{
				fBatList.append(m_oBatInfo.fVolt);
			}
		}
		else
		{
			m_nBatErrCnt++;
			if(m_nBatErrCnt > 2)
				g_theSttDeviceStatus->m_nBatErr = 1;//电池电压采集异常
		}
	}

	if(fBatList.count() > 3)
	{
		float fMax = 0;
		float fMin = 16.8;
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
			if(m_nTestStopTick > 15)
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
	float fRt = 10.0/(7.4/fVdcmV - 1.0);
	float fT = 1.0/(log(fRt/10.0)/3950.0 + 1.0/298.15) - 273.15;

	return fT;
}

float VoltPower_trans(float fVdcmV)
{
	if(fVdcmV < -3323.49)
	{
		return -100 + (3323.49 + fVdcmV)*(100 - 180)/(3323.49 - 5982.28);
	}
	else if(fVdcmV < 3323.49)
	{
		return fVdcmV/3323.49*100;
	}
	else
	{
		return 100 + (fVdcmV-3323.49)*(180-100)/(5982.28-3323.49);
	}
}

void CSttDevicePNS330_6::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack, int nModulePos, int nModuleType)
{
	//bit0-volt //bit1-current
#ifdef _PSX_QT_LINUX_
	STT_MODULE_STATUS &oModuleStatus = g_theSttDeviceStatus->m_oModule[nModulePos];
	unsigned short unmin, unMax, voltdc;

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
		float fBatI = translateVoltBase(unMax, 10.0);
		if(fBatI < 0)
		{
			fBatI = fBatI * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBatICoef;
		}
		else
		{
			fBatI = 0;
		}

		oModuleStatus.m_fBAT[1] = -6.0612 * fBatI;
	}
	else
	{
		oModuleStatus.m_nWarningVal = oDrv_FeedBack.dat[9];
		unMax = (oDrv_FeedBack.dat[8] >> 16) & 0xfff;
		float fBatV = translateVoltBase(unMax, 14.0) * 1.43;
		fBatV = fBatV * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBatVCoef;
		oModuleStatus.m_fBAT[0] = fBatV;
		//控制电源
		voltdc = (oDrv_FeedBack.dat[4] >> 16) & 0xfff; //BAT_V8.4
		oModuleStatus.m_fVoltDc[1] = translateVoltBase(voltdc, 10) / 7.85 * 8.31;
		voltdc =  oDrv_FeedBack.dat[4] & 0xfff; //BAT_V4.2
		float fBatT = translateVoltBase(voltdc, 10) / 4.23 * 4.15;
		oModuleStatus.m_fVoltDc[0] = BatTemp_trans(fBatT);
	}

	//功率电源
	if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		voltdc = (oDrv_FeedBack.dat[1] >> 16) & 0xfff;
		float fADC = 0;
		fADC = translateVoltBase(voltdc, 10.0);
		oModuleStatus.m_fVoltDc[2] = VoltPower_trans(fADC * 1000);
		voltdc =  oDrv_FeedBack.dat[1] & 0xfff;
		fADC = translateVoltBase(voltdc, 10.0);
		oModuleStatus.m_fVoltDc[3] = VoltPower_trans(fADC * 1000);
	}
	else
	{
		voltdc = (oDrv_FeedBack.dat[1] >> 16) & 0xfff;
		oModuleStatus.m_fVoltDc[2] = translateVoltBase(voltdc, 10.4);
		voltdc =  oDrv_FeedBack.dat[1] & 0xfff;
		oModuleStatus.m_fVoltDc[3] = translateVoltBase(voltdc, 10.4);
	}

	if(nModuleType == STT_MODULE_TYPE_CURRENT)
	{
		int temp = oDrv_FeedBack.dat[9]&0xffff0000;
		temp = temp>>16;
		temp  = temp * 0.0625;
		oModuleStatus.m_nTemp[0] = temp;

		temp = oDrv_FeedBack.dat[9]<<16;
		temp = temp>>16;
		temp  = temp * 0.0625;
		oModuleStatus.m_nTemp[1] = temp;		

		temp = oDrv_FeedBack.dat[10]&0xffff0000;
		temp = temp>>16;
		temp  = temp * 503.975 / 4096 - 273.15;
		oModuleStatus.m_nTemp[2] = temp;		
	}
	else
	{
		//光功率
		oModuleStatus.m_fLCPortPower[0] = translateLightPower((oDrv_FeedBack.dat[2] >> 16) & 0xFFFF);
		oModuleStatus.m_fLCPortPower[1] = translateLightPower(oDrv_FeedBack.dat[2] & 0xFFFF);
		oModuleStatus.m_fLCPortPower[2] = translateLightPower((oDrv_FeedBack.dat[3] >> 16) & 0xFFFF);
		oModuleStatus.m_fLCPortPower[3] = translateLightPower(oDrv_FeedBack.dat[3] & 0xFFFF);
	}

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
		nValue = nValue > 0 ? 0 : 1; //硬件信号取反

		if(nValue)
		{
			g_theSttDeviceStatus->m_nOverHeat = 1;
		}
	}
	else
	{
		long nChanNum = 0;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule == NULL)
		{
			return;
		}

		for(int j = 0; j < pModule->m_oModuleAttr.m_nChannelNum; j++)
		{
			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_nEeType == STT_CH_EETYPE_CURRENT)
			{
				nChanNum++;
			}
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
							//电流回路
						}
						else
						{
							//电流开路
							oModuleStatus.m_oChannel[j].m_bIsOverLoad = 1;
							g_theSttDeviceStatus->m_nIBreak = 1;
						}
					}
				}
			}
		}
	}
#endif
}

void CSttDevicePNS330_6::GetVoltCurRtData()
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase == NULL)
	{
		return;
	}

	GetRtData();
}

void CSttDevicePNS330_6::SetRegisterValue(unsigned int nAddr, unsigned int nValue)
{
	//将锁移到调用处
	ioctl(m_nfd, nAddr, nValue);
}

void CSttDevicePNS330_6::DAPowerCtrl()
{
	long nPowerMode = GetMainUIPowerMode();
	if(nPowerMode == STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A)
	{
		return;
	}

	unsigned int nFPGADelay = 2;//斜率控制 UIModulePower_10A
	nFPGADelay |= 50<<16;

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	SetRegisterValue(PNS330_RegAddr_FPGACtrl, nFPGADelay);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

long CSttDevicePNS330_6::GetMainUIPowerMode()
{
	long nPowerMode = STT_CurrentMODULE_POWER_LOW;

	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_UI[0];
	if(pModule!=NULL)
	{
		for(int nIndex=0;nIndex<g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
		{
			tmt_CurModuleGear &oCurModuleGear = g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];
			if(oCurModuleGear.m_nModulePos == 16)
			{
				nPowerMode = oCurModuleGear.m_nIPowerMode;
				break;
			}
		}
	}

	return 	nPowerMode;
}

void CSttDevicePNS330_6::PreStartTestPro()
{
	m_nTestStopTick = -1;
	m_nRegCtrlDigital |= 1 << 6; //ON/OFF_KIO

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	if(g_theSystemConfig->m_nHasAnalog)
	{
		m_nRegCtrlAnalog |= 1 << 8; //ON/OFF_PA
		m_nRegCtrlAnalog |= 1 << 9; //ON/OFF_VI
		m_nRegCtrlAnalog &= ~(1 << 19); //LED_VOUT
		m_nRegCtrlAnalog |= 1 << 20; //K_VPout
		m_nRegCtrlAnalog |= 1 << 21; //K_IPout

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

		long nPowerMode = GetMainUIPowerMode();
		if(nPowerMode == STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A)
		{
			return;
		}

		Sleep(50);//一档固有时间

		if(nPowerMode > STT_CurrentMODULE_POWER_LOW)
		{
			float nDA = 3.5;
			if(nPowerMode == STT_CurrentMODULE_POWER_HIGH)
			{
				nDA = 6.5;
			}
			float fDelay = nDA*200/6.5;
			Sleep((long)fDelay);
		}
		Sleep(150);
	}
}

void CSttDevicePNS330_6::SetPeripheral()
{
	tmt_Peripheral *pPeripheral = &g_theSystemConfig->m_oPeripheral;
	//液晶背光 亮度bit7-bit0 [0,100] 配置后由触摸驱动自动维护。背光时间,单位分钟 bit15-bit8 [0,10],0代表一直高亮
	//bit23-bit16 额定最低亮度,bit31-bit24 额定最高亮度
	unsigned int nMaxLcdLight = 70;//亮度百分比
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
	nValue |= 5 << 16;//实测亮度还可以
	nValue |= nMaxLcdLight << 24;

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nTouchfd, 0x7000002c, nValue);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

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
	//主板ST口模式设置，330默认RX2是B码
	ioctl(m_nfd, 0x102, m_nMainSTMode); //00:None 01:FT3 10:PPS 11:BCode
	g_nDrvMainSTMode = m_nMainSTMode;
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttDevicePNS330_6::AfterTestFinishedPro()
{
	//停止实验后重置秒同步配置
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	if(g_theSystemConfig->m_bSyncSecond)
	{
		ioctl(m_nfd, 0x110, 1);
	}
	else
	{
		ioctl(m_nfd, 0x110, 0);
	}
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	if(g_theSystemConfig->m_nHasAnalog)
	{
		// m_nRegCtrlAnalog &= ~(1 << 8); //ON/OFF_PA 由FPGA延时15秒后自动关
		// m_nRegCtrlAnalog &= ~(1 << 9); //ON/OFF_VI
		m_nRegCtrlAnalog &= ~(1 << 20); //K_VPout
		m_nRegCtrlAnalog &= ~(1 << 21); //K_IPout

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}

	m_nTestStopTick = 0;
}

BOOL CSttDevicePNS330_6::SetOutputTime(tmt_channel *pChannel, BOOL bDc, float &fOutPutTime)
{
	if(!g_theSystemConfig->m_nHasAnalog)
	{
		return FALSE;
	}

	if(pChannel == NULL)
	{
		return FALSE;
	}

	PSTT_MODULE pModule = NULL;

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_UI; i++)
	{
		pModule = g_theDeviceSystemParameter->m_oModules_UI[i];

		if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_6)
		{
			break;
		}
		else
		{
			pModule = NULL;
		}
	}

	if(pModule == NULL)
	{
		return FALSE;
	}

	float fIMax = 0;
	float fAmp;
	float fChTmtCoef;
	float fCTRate = 1.0;

	for(int k = 0; k < pModule->m_oModuleAttr.m_nChannelNum; k++)
	{
		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE) //'U'
		{
			continue;
		}

		m_nTmtPos = pModule->m_nChTmtPos[k];
		fChTmtCoef = pModule->m_fChTmtCoef[k];

		if(m_nTmtPos < 0)
		{
			continue;
		}

		if(g_nTmtParaMode == 0)
		{
			//界面一次值
			fCTRate = g_theSystemConfig->GetCTRate(m_nTmtPos/3);
		}
		else
		{
			fCTRate = 1.0;
		}

		fAmp = pChannel[m_nTmtPos].Harm[1].fAmp*fCTRate;

		for(int i = 2; i <= 31; i++)
		{
			fAmp += pChannel[m_nTmtPos].Harm[i].fAmp*fCTRate;
		}

		fAmp = fAmp * fChTmtCoef;
		if(fAmp > fIMax)
		{
			fIMax = fAmp;
		}
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

	if(bDc)
	{
		fIMax = fIMax * 2;
	}

	fOutPutTime = 0.0;

	if(nPowerMode == STT_CurrentMODULE_POWER_HIGH || nPowerMode == STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A)
	{
		if(fIMax > 5.001)
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
		if(fIMax > 5.001)
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

BOOL CSttDevicePNS330_6::CheckCurrLoadIsSafe(tmt_channel *pChannel, BOOL bIsDc)
{
	long nChannelNum;
	long nTmtPos;
	float fTmtCoef;
	float fChMax;
	float fCTRate = 1.0;
	PSTT_MODULE pModule = NULL;

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_I; i++)
	{
		pModule = g_theDeviceSystemParameter->m_oModules_I[i];

		if(pModule == NULL)
		{
			continue;
		}

		if(bIsDc)
		{
			fChMax = pModule->m_oModuleAttr.m_fDefChDcMax;
		}
		else
		{
			fChMax = pModule->m_oModuleAttr.m_fDefChMax;
		}

		nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;

		for(int j = 0; j < nChannelNum; j++)
		{
			nTmtPos = pModule->m_nChTmtPos[j];
			fTmtCoef = pModule->m_fChTmtCoef[j];
			if(nTmtPos < 0)
			{
				continue;
			}

			if(g_nTmtParaMode == 0)
			{
				//界面一次值
				fCTRate = g_theSystemConfig->GetCTRate(nTmtPos/3);
			}
			else
			{
				fCTRate = 1.0;
			}

			float fAmp = pChannel[nTmtPos].Harm[1].fAmp*fCTRate;
			fAmp = fAmp * fTmtCoef; //电流模块通道合并时使用

			if(fAmp > (fChMax + EPSINON))
			{
				return FALSE;
			}
		}
	}

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_UI; i++)
	{
		pModule = g_theDeviceSystemParameter->m_oModules_UI[i];

		if(pModule == NULL)
		{
			continue;
		}

		nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;

		if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_6)
		{
			//核算周波最大值
			float fAmp[6], fAng[6], fFre[6];
			int nCnt = 0;

			for(int nChannel = 0; nChannel < nChannelNum; nChannel++)
			{
				nTmtPos = pModule->m_nChTmtPos[nChannel];

				if(nTmtPos < 0)
				{
					continue;
				}

				if(g_nTmtParaMode == 0)
				{
					//界面一次值
					fCTRate = g_theSystemConfig->GetCTRate(nTmtPos/3);
				}
				else
				{
					fCTRate = 1.0;
				}

				STT_MODULE_CH_DEF &oChDef = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel];

				if(oChDef.m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					fAmp[nCnt] = pChannel[nTmtPos].Harm[1].fAmp*fCTRate;
					fAng[nCnt] = pChannel[nTmtPos].Harm[1].fAngle;
					fFre[nCnt] = pChannel[nTmtPos].Harm[1].fFreq;
					nCnt++;
				}
			}

			float fMaxPoint = CalWaveMaxValue(fAmp, fAng, fFre, nCnt, bIsDc);

			if(bIsDc)
			{
				fChMax = 15.0;
				for(int nIndex=0;nIndex<g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
				{
					tmt_CurModuleGear &oCurModuleGear = g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];
					if(oCurModuleGear.m_nModulePos == pModule->m_oModuleAttr.m_nModuleIndex)
					{
						if(oCurModuleGear.m_nIPowerMode == STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A)
						{
							fChMax = 0.0;
						}
						break;
					}
				}
			}
			else
			{
				fChMax = 14.143;
				for(int nIndex=0;nIndex<g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
				{
					tmt_CurModuleGear &oCurModuleGear = g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];
					if(oCurModuleGear.m_nModulePos == pModule->m_oModuleAttr.m_nModuleIndex)
					{
						if(oCurModuleGear.m_nIPowerMode == STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A)
						{
							fChMax = 42.42;
						}
						break;
					}
				}
			}

			if(fMaxPoint > (fChMax + EPSINON))
			{
				return FALSE;
			}
		}
		else
		{
			//核算最大有效值
			for(int nChannel = 0; nChannel < nChannelNum; nChannel++)
			{
				nTmtPos = pModule->m_nChTmtPos[nChannel];

				if(nTmtPos < 0)
				{
					continue;
				}

				if(g_nTmtParaMode == 0)
				{
					//界面一次值
					fCTRate = g_theSystemConfig->GetCTRate(nTmtPos/3);
				}
				else
				{
					fCTRate = 1.0;
				}

				STT_MODULE_CH_DEF &oChDef = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel];

				if(oChDef.m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					if(bIsDc)
					{
						fChMax = oChDef.m_fChDCMaxValue;
					}
					else
					{
						fChMax = oChDef.m_fChACMaxValue;
					}

					float fAmp = pChannel[nTmtPos].Harm[1].fAmp*fCTRate;

					if(fAmp > (fChMax + EPSINON))
					{
						return FALSE;
					}
				}
			}
		}
	}

	return TRUE;
}

BOOL CSttDevicePNS330_6::CheckCurrLoadIsSafe_moduleoutput(tmt_channel *pChannel, BOOL bIsDc, PSTT_MODULE pModule)
{
	long nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;
	float fChMax;

	if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_CURRENT)
	{
		if(bIsDc)
		{
			fChMax = pModule->m_oModuleAttr.m_fDefChDcMax;
		}
		else
		{
			fChMax = pModule->m_oModuleAttr.m_fDefChMax;
		}

		for(int nChannel = 0; nChannel < nChannelNum; nChannel++)
		{
			float fAmp = pChannel[nChannel].Harm[1].fAmp;

			if(fAmp > (fChMax + EPSINON))
			{
				return FALSE;
			}
		}
	}
	else if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
	{
		if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_6)
		{
			//核算周波最大值
			float fAmp[6], fAng[6], fFre[6];
			int nCnt = 0;

			for(int nChannel = 0; nChannel < nChannelNum; nChannel++)
			{
				STT_MODULE_CH_DEF &oChDef = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel];

				if(oChDef.m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					fAmp[nCnt] = pChannel[nChannel].Harm[1].fAmp;
					fAng[nCnt] = pChannel[nChannel].Harm[1].fAngle;
					fFre[nCnt] = pChannel[nChannel].Harm[1].fFreq;
					nCnt++;
				}
			}

			float fMaxPoint = CalWaveMaxValue(fAmp, fAng, fFre, nCnt, bIsDc);

			if(bIsDc)
			{
				fChMax = 15.0;
				for(int nIndex=0;nIndex<g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
				{
					tmt_CurModuleGear &oCurModuleGear = g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];
					if(oCurModuleGear.m_nModulePos == pModule->m_oModuleAttr.m_nModuleIndex)
					{
						if(oCurModuleGear.m_nIPowerMode == STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A)
						{
							fChMax = 0.0;
						}
						break;
					}
				}
			}
			else
			{
				fChMax = 14.143;
				for(int nIndex=0;nIndex<g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
				{
					tmt_CurModuleGear &oCurModuleGear = g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];
					if(oCurModuleGear.m_nModulePos == pModule->m_oModuleAttr.m_nModuleIndex)
					{
						if(oCurModuleGear.m_nIPowerMode == STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A)
						{
							fChMax = 42.42;
						}
						break;
					}
				}
			}

			if(fMaxPoint > (fChMax + EPSINON))
			{
				return FALSE;
			}
		}
		else
		{
			//核算最大有效值
			for(int nChannel = 0; nChannel < nChannelNum; nChannel++)
			{
				STT_MODULE_CH_DEF &oChDef = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel];

				if(oChDef.m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					if(bIsDc)
					{
						fChMax = oChDef.m_fChDCMaxValue;
					}
					else
					{
						fChMax = oChDef.m_fChACMaxValue;
					}

					float fAmp = pChannel[nChannel].Harm[1].fAmp;

					if(fAmp > (fChMax + EPSINON))
					{
						return FALSE;
					}
				}
			}
		}
	}

	return TRUE;
}

void CSttDevicePNS330_6::Stt_Xml_Serialize_Channels(CSttXmlSerializeBase *pXmlSerialize)
{
	PSTT_MODULE_STATUS pParaV = &g_theSttDeviceStatus->m_oModule[0];
	PSTT_MODULE_STATUS pParaI = &g_theSttDeviceStatus->m_oModule[1];
	long nTemp;
	nTemp = 0;
	CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize("模块", "Module", nTemp, "Module", stt_ParaGroupKey());

	if(pXmlModule == NULL)
	{
		return;
	}

	pXmlModule->xml_serialize("电压功率电源+", "VoltDc3", "V", "float", pParaV->m_fVoltDc[2]);
	pXmlModule->xml_serialize("电压功率电源-", "VoltDc4", "V", "float", pParaV->m_fVoltDc[3]);
	pXmlModule->xml_serialize("电流功率电源+", "CurrDc3", "V", "float", pParaI->m_fVoltDc[2]);
	pXmlModule->xml_serialize("电流功率电源-", "CurrDc4", "V", "float", pParaI->m_fVoltDc[3]);
	pXmlModule->xml_serialize("环境温度", "T1", "deg", "long", pParaI->m_nTemp[1]);
	pXmlModule->xml_serialize("散热器温度", "T2", "deg", "long", pParaI->m_nTemp[0]);
	pXmlModule->xml_serialize("FPGA温度", "T3", "deg", "long", pParaI->m_nTemp[2]);
	pXmlModule->xml_serialize("电池组温度", "BAT_Temp1", "deg", "long", pParaV->m_fVoltDc[0]);
	pXmlModule->xml_serialize("电池电压", "BATV", "", "float", pParaV->m_fBAT[0]);
	pXmlModule->xml_serialize("电池电流", "BATI", "", "float", pParaI->m_fBAT[1]);
	pXmlModule->xml_serialize("8.4电池电压", "BAT_V8.4", "V", "float", pParaV->m_fVoltDc[1]);
	long nValue;
	nValue = (pParaV->m_nWarningVal >> 11) & 0x01;
	pXmlModule->xml_serialize("VA过载(0:报警)", "OVL_V1", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 10) & 0x01;
	pXmlModule->xml_serialize("VB过载(0:报警)", "OVL_V2", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 9) & 0x01;
	pXmlModule->xml_serialize("VC过载(0:报警)", "OVL_V3", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 8) & 0x01;
	pXmlModule->xml_serialize("VZ过载(0:报警)", "OVL_V4", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 7) & 0x01;
	nValue = nValue > 0 ? 0 : 1; //硬件信号取反
	pXmlModule->xml_serialize("过热(1:报警)", "OVT", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 6) & 0x01;
	pXmlModule->xml_serialize("电池过载(0:报警)", "BAT_OVL", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 5) & 0x01;
	pXmlModule->xml_serialize("网口Phy-Link", "ETH_LINK/ACT", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 4) & 0x01;
	pXmlModule->xml_serialize("网口Phy-Speed", "ETH_SPEED", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 3) & 0x01;
	pXmlModule->xml_serialize("蓝牙Link(0:Link)", "BT_LINK", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 2) & 0x01;
	pXmlModule->xml_serialize("WiFi-Link(0:Link)", "WIFI_LINK", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 1) & 0x01;
	pXmlModule->xml_serialize("4G-Link(0:Link)", "4G_LINK", "", "long", nValue);
	nValue = pParaV->m_nWarningVal & 0x01;
	pXmlModule->xml_serialize("充电(0:充电中)", "CHRG", "", "long", nValue);
	nValue = (pParaV->m_nWarningVal >> 12) & 0x01;
	pXmlModule->xml_serialize("VBUS", "VBUS", "", "long", nValue);

	//6U6I
	for(long k = 0; k < 6; k++)
	{
		stt_xml_serialize(&pParaV->m_oChannel[k], k, pXmlModule);
	}

	for(long k = 0; k < 6; k++)
	{
		stt_xml_serialize(&pParaI->m_oChannel[k], k + 6, pXmlModule);
	}
}

void CSttDevicePNS330_6::SetCurMergeConfig()
{
	long nIPowerMode = GetMainUIPowerMode();
	if(nIPowerMode == STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A)
	{
		g_nEnableDCCurr = 0;
		m_nRegCtrlAnalog |= 1 << 17;//K_IPout2

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}
	else
	{
		g_nEnableDCCurr = 1;
		m_nRegCtrlAnalog &= ~(1 << 17); //K_IPout2

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}
	Sleep(100);
}
