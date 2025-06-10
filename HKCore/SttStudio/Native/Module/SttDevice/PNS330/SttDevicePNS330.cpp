#include "SttDevicePNS330.h"
#include "../Module/PowerCtrl/UI/PNS330/SttPowerCtrl_PNS330.h"
#include "../Module/PowerCtrl/UI/PNS330/SttPowerCtrl_PNS330_H.h"
#include "../Module/PowerCtrl/Volt/PI/SttPowerCtrl_PI_V130.h"
#include "../Module/PowerCtrl/Volt/PI/SttPowerCtrl_PI_V270.h"
#include "../Module/PowerCtrl/Volt/PI/SttPowerCtrl_PI_V300.h"
#include "../Module/PowerCtrl/UI/PI/SttPowerCtrl_PI_V130C20.h"
#include "../Module/PowerCtrl/Current/SttPowerCtrl_C12_5.h"
#include "../Module/PowerCtrl/Current/SttPowerCtrl_C20.h"
#include "../Module/PowerCtrl/Current/SttPowerCtrl_C32.h"

CSttDevicePNS330 *CSttDevicePNS330::g_pSttDevicePNS330 = NULL;
long CSttDevicePNS330::g_nSttDeviceRef = 0;

QList<float> fBatList;

CSttDevicePNS330::CSttDevicePNS330()
{
	//主板ST口模式设置，330默认RX2是B码
	//00-None 01:FT3 10:PPS 11:BCode
	m_nMainSTMode = 0b1110;
}

CSttDevicePNS330::~CSttDevicePNS330()
{
}

void CSttDevicePNS330::Create()
{
	g_nSttDeviceRef++;

	if(g_nSttDeviceRef == 1)
	{
		g_pSttDevicePNS330 = new CSttDevicePNS330;
		g_pSttDeviceBase = (CSttDeviceBase *)g_pSttDevicePNS330;
	}
}

void CSttDevicePNS330::Release()
{
	g_nSttDeviceRef--;

	if(g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePNS330;
		g_pSttDevicePNS330 = NULL;
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

void init_module_ref(long &nCount, PSTT_MODULE *ppModuleRef, long nModuleType)
{
	for(int nModuleIndex = 1; nModuleIndex <= 4; nModuleIndex++)
	{
		for(long k = 0; k < g_theDeviceSystemParameter->m_nModuleCount; k++)
		{
			PST_MODULE_ATTR pModuleAttr = &g_theDeviceSystemParameter->m_oModules[k].m_oModuleAttr;

			if(pModuleAttr->m_nUsed)
			{
				if(pModuleAttr->m_nModuleType == nModuleType)
				{
					if(pModuleAttr->m_nModuleIndex == nModuleIndex)
					{
						ppModuleRef[nCount] = &g_theDeviceSystemParameter->m_oModules[k];
						ppModuleRef[nCount]->InitChTmtCoef();
						nCount++;
						break;
					}
				}
			}
		}
	}
}

void ReDefine_DeviceSystemParameter()
{
	for(long k = 0; k < g_theDeviceSystemParameter->m_nModuleCount; k++)
	{
		PST_MODULE_ATTR pModuleAttr = &g_theDeviceSystemParameter->m_oModules[k].m_oModuleAttr;

		if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
		{
			if(pModuleAttr->m_nModuleIndex == 16)
			{
				//内部模块
			}
			else if(pModuleAttr->m_nModuleIndex > 4)
			{
				pModuleAttr->m_nUsed = 0;
			}
		}
		else
		{
			if(pModuleAttr->m_nModuleIndex > 4)
			{
				pModuleAttr->m_nUsed = 0;
			}
		}
	}

	g_theDeviceSystemParameter->m_nModuleCount_U = 0;
	init_module_ref(g_theDeviceSystemParameter->m_nModuleCount_U,
					g_theDeviceSystemParameter->m_oModules_U, STT_MODULE_TYPE_VOLT);
	g_theDeviceSystemParameter->m_nModuleCount_I = 0;
	init_module_ref(g_theDeviceSystemParameter->m_nModuleCount_I,
					g_theDeviceSystemParameter->m_oModules_I, STT_MODULE_TYPE_CURRENT);
	g_theDeviceSystemParameter->m_nModuleCount_UI = 0;
	init_module_ref(g_theDeviceSystemParameter->m_nModuleCount_UI,
					g_theDeviceSystemParameter->m_oModules_UI, STT_MODULE_TYPE_VOLT_CURRENT);

	for(long k = 0; k < g_theDeviceSystemParameter->m_nModuleCount; k++)
	{
		PST_MODULE_ATTR pModuleAttr = &g_theDeviceSystemParameter->m_oModules[k].m_oModuleAttr;

		if(pModuleAttr->m_nUsed)
		{
			if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
			{
				if(pModuleAttr->m_nModuleIndex == 16)
				{
					long nModuleCount_UI = g_theDeviceSystemParameter->m_nModuleCount_UI;
					g_theDeviceSystemParameter->m_oModules_UI[nModuleCount_UI] = &g_theDeviceSystemParameter->m_oModules[k];
					g_theDeviceSystemParameter->m_oModules_UI[nModuleCount_UI]->InitChTmtCoef();
					g_theDeviceSystemParameter->m_nModuleCount_UI++;
					break;
				}
			}
		}
	}

	g_theDeviceSystemParameter->m_nModuleCount_D = 0;
	init_module_ref(g_theDeviceSystemParameter->m_nModuleCount_D,
					g_theDeviceSystemParameter->m_oModules_D, STT_MODULE_TYPE_DIGITAL_0G8M);
	init_module_ref(g_theDeviceSystemParameter->m_nModuleCount_D,
					g_theDeviceSystemParameter->m_oModules_D, STT_MODULE_TYPE_DIGITAL_2G6M);
	init_module_ref(g_theDeviceSystemParameter->m_nModuleCount_D,
					g_theDeviceSystemParameter->m_oModules_D, STT_MODULE_TYPE_DIGITAL_4G4M);
	g_theDeviceSystemParameter->m_nModuleCount_WEEK = 0;
	init_module_ref(g_theDeviceSystemParameter->m_nModuleCount_WEEK,
					g_theDeviceSystemParameter->m_oModules_WEEK, STT_MODULE_TYPE_WEEK_EX);
	g_theDeviceSystemParameter->m_nModuleCount_FT3 = 0;
	init_module_ref(g_theDeviceSystemParameter->m_nModuleCount_FT3,
					g_theDeviceSystemParameter->m_oModules_FT3, STT_MODULE_TYPE_FT3);
	g_theDeviceSystemParameter->m_nModuleCount_S = 0;
	init_module_ref(g_theDeviceSystemParameter->m_nModuleCount_S,
					g_theDeviceSystemParameter->m_oModules_S, STT_MODULE_TYPE_SWITCH);
	g_theDeviceSystemParameter->init_module_ChDefMap();
	g_theDeviceSystemParameter->init_hd_ch_id();
}

int CSttDevicePNS330::InitDevice(BOOL bHasAdjFile)
{
	m_nBatLastTime = 0;
	fBatList.clear();
	m_nCommfd = open("/dev/SttDriver_PNS330", O_RDWR);
	g_oDrvMutex.lock();
	g_nStateCount = read(m_nCommfd,NULL,0x201);
	g_oDrvMutex.unlock();
	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nStateCount = g_nStateCount;
	InitBuff();
	g_oDrvMutex.lock();
	int nFlag = ioctl(m_nCommfd, 0x106, 0);
	g_oDrvMutex.unlock();
	nFlag = nFlag >> 24;

	if(nFlag == 0x34)
	{
		m_nBootMode = 1;//主板版本号首字节用于判断当前模式
		ReDefine_DeviceSystemParameter();
	}

	m_nRegCtrlDigital = 0;
	m_nRegCtrlDigital |= 1 << 0;

	//    m_nRegCtrlDigital |= 1<<1;//Ble default
	// if(m_nBootMode == 0)
	// {
	// 	m_nRegCtrlDigital |= 1 << 2; //ON/OFF_FX1  default=1
	// 	m_nRegCtrlDigital |= 1 << 3; //ON/OFF_FX2  default=1
	// 	m_nRegCtrlDigital |= 1 << 4; //ON/OFF_FX3  default=1
	// 	m_nRegCtrlDigital |= 1 << 5; //ON/OFF_FX4  default=1
	// }

	m_nRegCtrlDigital |= 1 << 7; //ON/OFF_FT3  default=1

	m_nVoltPowerRefVal = 0;
	m_nCurrPowerRefVal = 0;
	m_nTestStopTick = -1;
	m_nBatCalcCnt = 0;
	m_nBatErrCnt = 0;
	//PNS330只有一个bit31的模拟信号和一个bit30数字信号

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		if(m_nBootMode == 0)
		{
			g_theDeviceSystemParameter->m_nModuleCount_UI = 1;
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[0];

			if(pModule != NULL)
			{
				pModule->m_oModuleAttr.m_nModuleIndex = 16;//bit31模拟信号

				if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H)
				{
					//270V10A
					pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrl_PNS330_H);
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
				{
					//120V单项10A同向20A
					pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrl_PNS330);
				}
				else
				{
					//默认机型配置 120V10A 单项10A同向10A
					pModule->m_oModuleAttr.m_nModulePower = STT_MODULE_UI_PNS330;
					pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrl_PNS330);
				}

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
				pChDrvPos->m_nChDrvPos[8] = 8;
				pChDrvPos->m_nChDrvPos[9] = 9;
				pModule->init_ch_drv_pos();

				if(pModule->m_oModuleAttr.m_nChannelNum > 10)
				{
					pModule->m_oModuleAttr.m_nChannelNum = 10;
				}

				//4U6I
				strcpy(pChDefs->m_oChDef[0].m_pszChId, "U1_1");
				strcpy(pChDefs->m_oChDef[1].m_pszChId, "U1_2");
				strcpy(pChDefs->m_oChDef[2].m_pszChId, "U1_3");
				strcpy(pChDefs->m_oChDef[3].m_pszChId, "U1_4");
				strcpy(pChDefs->m_oChDef[4].m_pszChId, "I1_1");
				strcpy(pChDefs->m_oChDef[5].m_pszChId, "I1_2");
				strcpy(pChDefs->m_oChDef[6].m_pszChId, "I1_3");
				strcpy(pChDefs->m_oChDef[7].m_pszChId, "I1_4");
				strcpy(pChDefs->m_oChDef[8].m_pszChId, "I1_5");
				strcpy(pChDefs->m_oChDef[9].m_pszChId, "I1_6");
				pChDefs->m_oChDef[0].m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDefs->m_oChDef[1].m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDefs->m_oChDef[2].m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDefs->m_oChDef[3].m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDefs->m_oChDef[4].m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDefs->m_oChDef[5].m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDefs->m_oChDef[6].m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDefs->m_oChDef[7].m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDefs->m_oChDef[8].m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDefs->m_oChDef[9].m_nEeType = STT_CH_EETYPE_CURRENT;
			}
		}
	}

	if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
	{
		if(m_nBootMode == 0)
		{
			g_theDeviceSystemParameter->m_nModuleCount_D = 1;
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[0];

			if(pModule != NULL)
			{
				pModule->m_oModuleAttr.m_nModuleIndex = 15;//bit30数字信号
				pModule->m_oModuleAttr.m_nFiberPortNum_LC = 4;
				pModule->m_oModuleAttr.m_nFiberPortNum_STSend = 2;
				pModule->m_oModuleAttr.m_nFiberPortNum_STRecv = 2;
			}

			//打开4个光模块电源
			m_nRegCtrlDigital &= ~(1 << 2);
			m_nRegCtrlDigital &= ~(1 << 3);
			m_nRegCtrlDigital &= ~(1 << 4);
			m_nRegCtrlDigital &= ~(1 << 5);
			SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
		}
	}

	if(m_nBootMode == 0)
	{
		g_theDeviceSystemParameter->m_nModuleCount_U = 0;
		g_theDeviceSystemParameter->m_nModuleCount_I = 0;
		g_theDeviceSystemParameter->m_nModuleCount_WEEK = 0;
		g_theDeviceSystemParameter->m_nModuleCount_FT3 = 0;
		g_theDeviceSystemParameter->m_nModuleCount_S = 0;
	}

	g_theSystemConfig->m_oPeripheral.m_b4G = 1;//默认4G启动
	g_theSystemConfig->m_oPeripheral.m_bBle = 0;
	g_theSystemConfig->m_oPeripheral.m_bNetRj45 = 1;
	g_theSystemConfig->m_oPeripheral.m_bNetWifi = 0;
	g_theSystemConfig->m_oPeripheral.m_nLcdTimes = 0;
	m_nTouchfd = open("/dev/exc7200dev", O_RDWR);
	m_pDegressMsg = (Drv_DegressMsg *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
	qDebug() << "Driver Mmap = " << m_pDegressMsg;
#endif


	InitDApara(m_nCommfd, bHasAdjFile);
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
	SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
	//Uart0
	SetRegisterValue(0xe0000018, 62); //4G
	SetRegisterValue(0xe0000034, 6);
	//便于开机的时候获取一次电池 4G 蓝牙的状态,用于第一次进实验的图标显示
	g_nGetSystemStateTickCnt = 1;
	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nSTModeSet = 1;
	m_oBatInfoRef0.fVolt = 0;
	m_oBatInfoRef0.fCurr = 0;
	m_oBatInfoRef1.fVolt = 0;
	m_oBatInfoRef1.fCurr = 0;

	m_nUIModulePower = UIModulePower_10A;
	for(int i = 0;i<g_theDeviceSystemParameter->m_nModuleCount_UI;i++)
	{
		PSTT_MODULE pModuleUI = g_theDeviceSystemParameter->m_oModules_UI[i];
		if(pModuleUI != NULL)
		{
			if(pModuleUI->m_oModuleAttr.m_nModuleIndex == 16)
			{
				if(pModuleUI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
				{
					m_nUIModulePower = UIModulePower_20A;
					break;
				}
			}
		}
	}
	return m_nCommfd;
}

void CSttDevicePNS330::SetDrvMoudlePara()
{
	Drv_ModulePara oDrv_ModulePara;
	memset(&oDrv_ModulePara, 0, sizeof(Drv_ModulePara));
	oDrv_ModulePara.nAlgCnt = 0;
	memset(&m_oModuleMaxVaildCnt, 0, sizeof(Drv_ModuleMaxVaildCnt));
	int nHarmCnt = 31;

	if(m_nBootMode == 0)
	{
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
			m_oModuleMaxVaildCnt.maxVaildCnt[nIndex] = DIGITAL_CHANNEL_MAX * nHarmCnt * 3;
			oDrv_ModulePara.nAlgCnt++;
		}
	}
	else
	{
		int nModuleIndex;

		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			PSTT_MODULE pModule_U = g_theDeviceSystemParameter->m_oModules_U[nIndex];

			if(pModule_U != NULL)
			{
				if(pModule_U->m_oModuleAttr.m_nErr)
				{
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
				}
				else
				{
					nModuleIndex = pModule_U->m_oModuleAttr.m_nModuleIndex;
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
				}

				m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = CHANNEL_MAX + CHANNEL_MAX * 3 * nHarmCnt;
				oDrv_ModulePara.nAlgCnt++;
			}
		}

		//CURRENT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			PSTT_MODULE pModule_I = g_theDeviceSystemParameter->m_oModules_I[nIndex];

			if(pModule_I != NULL)
			{
				if(pModule_I->m_oModuleAttr.m_nErr)
				{
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
				}
				else
				{
					nModuleIndex = pModule_I->m_oModuleAttr.m_nModuleIndex;
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
				}

				m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = CHANNEL_MAX + CHANNEL_MAX * 3 * nHarmCnt;
				oDrv_ModulePara.nAlgCnt++;
			}
		}

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

			if(pModule_UI != NULL)
			{
				if(pModule_UI->m_oModuleAttr.m_nErr)
				{
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
				}
				else
				{
					nModuleIndex = pModule_UI->m_oModuleAttr.m_nModuleIndex;
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
				}

				if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
						|| pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
						|| pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
				{
					m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = 12 + 12 * 3 * nHarmCnt;
				}
				else
				{
					m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = 6 + 6 * 3 * nHarmCnt;
				}

				oDrv_ModulePara.nAlgCnt++;
			}
		}

		//DIGITAL
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_D; nIndex++)
		{
			PSTT_MODULE pModule_D = g_theDeviceSystemParameter->m_oModules_D[nIndex];

			if(pModule_D != NULL)
			{
				if(pModule_D->m_oModuleAttr.m_nErr)
				{
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
				}
				else
				{
					nModuleIndex = pModule_D->m_oModuleAttr.m_nModuleIndex;
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
				}

				m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = DIGITAL_CHANNEL_MAX * nHarmCnt * 3;
				oDrv_ModulePara.nAlgCnt++;
			}
		}

		//Week
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
		{
			PSTT_MODULE pModule_W = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			if(pModule_W != NULL)
			{
				if(pModule_W->m_oModuleAttr.m_nErr)
				{
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
				}
				else
				{
					nModuleIndex = pModule_W->m_oModuleAttr.m_nModuleIndex;
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
				}

				if(pModule_W->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA48S)
				{
					m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = 48 + 48 * 3 * 2;
				}
				else
				{
					m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = 12 + 12 * 3 * nHarmCnt;
				}

				oDrv_ModulePara.nAlgCnt++;
			}
		}

		//FT3
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_FT3; nIndex++)
		{
			PSTT_MODULE pModule_FT3 = g_theDeviceSystemParameter->m_oModules_FT3[nIndex];

			if(pModule_FT3 != NULL)
			{
				if(pModule_FT3->m_oModuleAttr.m_nErr)
				{
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
				}
				else
				{
					nModuleIndex = pModule_FT3->m_oModuleAttr.m_nModuleIndex;
					oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
				}

				m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = DIGITAL_CHANNEL_MAX * nHarmCnt * 3;
				oDrv_ModulePara.nAlgCnt++;
			}
		}
	}

	//BIO
	oDrv_ModulePara.nBiCnt = 1;
	oDrv_ModulePara.nBiTable[0] = 0x8000;
	oDrv_ModulePara.nBoCnt = 1;
	oDrv_ModulePara.nBoTable[0] = 0x8000;

	if(m_nBootMode == 1)
	{
		CSttDeviceBase::g_pSttDeviceBase->InitSwitchModule();//初始化全局公共变量m_oSwitchModules
		SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

		//BIOEx
		for(int nIndex = 0; nIndex < oSwitchModules.m_nModulesCount; nIndex++)
		{
			int nModuleIndex = oSwitchModules.oSWITCHINFO[nIndex].m_nModulePos;
			oDrv_ModulePara.nBiTable[oDrv_ModulePara.nBiCnt] = ModuleIndexTransToDrv(nModuleIndex);
			oDrv_ModulePara.nBoTable[oDrv_ModulePara.nBoCnt] = ModuleIndexTransToDrv(nModuleIndex);
			oDrv_ModulePara.nBiCnt++;
			oDrv_ModulePara.nBoCnt++;
		}
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x331, 0);
	write(m_nfd, (char *)&oDrv_ModulePara, sizeof(Drv_ModulePara));
	g_oDrvMutex.unlock();
	Sleep(10);
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x356, 0);
	write(m_nfd, (char *)&m_oModuleMaxVaildCnt, sizeof(Drv_ModuleMaxVaildCnt));
	g_oDrvMutex.unlock();
}

void CSttDevicePNS330::InitModulePowerCtrl()
{
	CSttPowerCtrlBase *pCSttPowerCtrlBase = NULL;

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		pCSttPowerCtrlBase = NULL;

		switch(pModule->m_oModuleAttr.m_nModulePower)
		{
			case STT_MODULE_VOLT_V130_130:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV130_PI);
				break;

			case STT_MODULE_VOLT_V270_270:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV270_PI);
				break;

			case STT_MODULE_VOLT_V300_300:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV300_PI);
				break;

			default:
				//PI常用300伏模块
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV300_PI);
				break;
		}

		if(pCSttPowerCtrlBase != NULL)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase = pCSttPowerCtrlBase;
		}
	}

	//CURRENT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		pCSttPowerCtrlBase = NULL;

		switch(pModule->m_oModuleAttr.m_nModulePower)
		{
			case STT_MODULE_CURRENT_C12_5:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlC12_5);
				break;

			case STT_MODULE_CURRENT_C20:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlC20);
				break;

			case STT_MODULE_CURRENT_C32:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlC32);
				break;

			default:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlC20);
				break;
		}

		if(pCSttPowerCtrlBase != NULL)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase = pCSttPowerCtrlBase;
		}
	}

	//UI
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		pCSttPowerCtrlBase = NULL;

		if(pModule->m_oModuleAttr.m_nModuleIndex == 16)
		{
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H)
			{
				//270V10A
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrl_PNS330_H);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
			{
				//120V10A
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrl_PNS330);
			}
			else
			{
				//默认机型配置 120V10A
				pModule->m_oModuleAttr.m_nModulePower = STT_MODULE_UI_PNS330;
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrl_PNS330);
			}

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
			pChDrvPos->m_nChDrvPos[8] = 8;
			pChDrvPos->m_nChDrvPos[9] = 9;
			pModule->init_ch_drv_pos();

			if(pModule->m_oModuleAttr.m_nChannelNum > 10)
			{
				pModule->m_oModuleAttr.m_nChannelNum = 10;
			}

			//4U6I
			strcpy(pChDefs->m_oChDef[0].m_pszChId, "U1_1");
			strcpy(pChDefs->m_oChDef[1].m_pszChId, "U1_2");
			strcpy(pChDefs->m_oChDef[2].m_pszChId, "U1_3");
			strcpy(pChDefs->m_oChDef[3].m_pszChId, "U1_4");
			strcpy(pChDefs->m_oChDef[4].m_pszChId, "I1_1");
			strcpy(pChDefs->m_oChDef[5].m_pszChId, "I1_2");
			strcpy(pChDefs->m_oChDef[6].m_pszChId, "I1_3");
			strcpy(pChDefs->m_oChDef[7].m_pszChId, "I1_4");
			strcpy(pChDefs->m_oChDef[8].m_pszChId, "I1_5");
			strcpy(pChDefs->m_oChDef[9].m_pszChId, "I1_6");
			pChDefs->m_oChDef[0].m_nEeType = STT_CH_EETYPE_VOLTAGE;
			pChDefs->m_oChDef[1].m_nEeType = STT_CH_EETYPE_VOLTAGE;
			pChDefs->m_oChDef[2].m_nEeType = STT_CH_EETYPE_VOLTAGE;
			pChDefs->m_oChDef[3].m_nEeType = STT_CH_EETYPE_VOLTAGE;
			pChDefs->m_oChDef[4].m_nEeType = STT_CH_EETYPE_CURRENT;
			pChDefs->m_oChDef[5].m_nEeType = STT_CH_EETYPE_CURRENT;
			pChDefs->m_oChDef[6].m_nEeType = STT_CH_EETYPE_CURRENT;
			pChDefs->m_oChDef[7].m_nEeType = STT_CH_EETYPE_CURRENT;
			pChDefs->m_oChDef[8].m_nEeType = STT_CH_EETYPE_CURRENT;
			pChDefs->m_oChDef[9].m_nEeType = STT_CH_EETYPE_CURRENT;
		}
		else
		{
			switch(pModule->m_oModuleAttr.m_nModulePower)
			{
				case STT_MODULE_UI_V130_C20:
				{
					pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV130C20_PI);
					pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[0].m_fChACMaxValue = 20;
					pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[1].m_fChACMaxValue = 20;
					pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[2].m_fChACMaxValue = 20;
					pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[3].m_fChACMaxValue = 130;
					pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[4].m_fChACMaxValue = 130;
					pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[5].m_fChACMaxValue = 130;
				}
				break;
			}
		}

		if(pCSttPowerCtrlBase != NULL)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase = pCSttPowerCtrlBase;
		}
	}
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
	float fBat = fV * 0.994;

	if(fBat > 12.5)
	{
		fBat = 12.5;
	}

	int nBatCap;

	if(fBat < 10.47)
	{
		//8
		//                nBatCap = 8.0*fBat/(10.47 - 10.26) - 390.8;
		if(fBat > 10.38)
		{
			nBatCap = 5;
		}
		else
		{
			nBatCap = 0;
		}
	}
	else if(fBat < 10.60)
	{
		//16
		//                nBatCap = 8.0*fBat/(10.60 - 10.47) - 636.0;
		if(fBat > 10.57)
		{
			nBatCap = 15;
		}
		else
		{
			nBatCap = 10;
		}
	}
	else if(fBat < 10.67)
	{
		//24
		//                nBatCap = 8.0*fBat/(10.67 - 10.60) - 1195.4;
		if(fBat > 10.63)
		{
			nBatCap = 25;
		}
		else
		{
			nBatCap = 20;
		}
	}
	else if(fBat < 10.73)
	{
		//32
		//                nBatCap = 8.0*fBat/(10.73 - 10.67) - 1398.6;
		if(fBat > 10.70)
		{
			nBatCap = 30;
		}
		else
		{
			nBatCap = 28;
		}
	}
	else if(fBat < 10.80)
	{
		//40
		//                nBatCap = 8.0*fBat/(10.80 - 10.73) - 1194.2;
		if(fBat > 10.77)
		{
			nBatCap = 35;
		}
		else
		{
			nBatCap = 32;
		}
	}
	else if(fBat < 10.88)
	{
		//48
		//                nBatCap = 8.0*fBat/(10.88 - 10.80) - 1040.0;
		if(fBat > 10.84)
		{
			nBatCap = 40;
		}
		else
		{
			nBatCap = 38;
		}
	}
	else if(fBat < 11.0)
	{
		//56
		//                nBatCap = 8.0*fBat/(11.0 - 10.88) - 677.3;
		if(fBat > 10.98)
		{
			nBatCap = 50;
		}
		else
		{
			nBatCap = 45;
		}
	}
	else if(fBat < 11.2)
	{
		//64
		//                nBatCap = 8.0*fBat/(11.2 - 11.0) - 384;
		if(fBat > 11.10)
		{
			nBatCap = 60;
		}
		else
		{
			nBatCap = 55;
		}
	}
	else if(fBat < 11.4)
	{
		//72
		//                nBatCap = 8.0*fBat/(11.4 - 11.2) - 384;
		if(fBat > 11.30)
		{
			nBatCap = 70;
		}
		else
		{
			nBatCap = 65;
		}
	}
	else if(fBat < 11.95)
	{
		//80
		//                nBatCap = 8.0*fBat/(11.95 - 11.4) - 93.8;
		if(fBat > 11.70)
		{
			nBatCap = 80;
		}
		else
		{
			nBatCap = 75;
		}
	}
	else if(fBat < 12.15)
	{
		//88
		//                nBatCap = 8.0*fBat/(12.15 - 11.95) - 398;
		if(fBat > 12.05)
		{
			nBatCap = 90;
		}
		else
		{
			nBatCap = 85;
		}
	}
	else
	{
		//100
		//                nBatCap = 8.0*fBat/(12.5 - 12.15) - 185.7;
		if(fBat > 12.37)
		{
			nBatCap = 100;
		}
		else
		{
			nBatCap = 95;
		}
	}

	return nBatCap;
}

int nFirstBatCap = -1;
BOOL CSttDevicePNS330::OnTimer(BOOL bExec)
{
	GetVoltCurRtData();

	if(!bExec)
	{
		m_nDeviceOnTimerCount++;

		if(m_nDeviceOnTimerCount * m_nOnTimerMs < m_nDeviceOnTimerMs)
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

	stt_init_stt_device_status();
	g_theSttDeviceStatus->m_nUdc = g_fAuxVolt > 0.001 ? 1 : 0;
#ifdef _PSX_QT_LINUX_
	memset(&m_oSysUtc, 0, sizeof(Drv_SysUtc));
	g_oDrvMutex.lock();
	int nSize = read(m_nCommfd, (char *)&m_oSysUtc, 0x205);
	g_oDrvMutex.unlock();

	if(nSize != sizeof(Drv_SysUtc))
	{
		return FALSE;
	}

	g_theSttDeviceStatus->m_nUtc_s = m_oSysUtc.tm_h; //默认B码与GPS保持一致，统一为0时区
	g_theSttDeviceStatus->m_nUtc_ns = m_oSysUtc.tm_l;
	g_theSttDeviceStatus->m_nUser_s = g_theSttDeviceStatus->m_nUtc_s
									  + g_theSttDeviceStatus->m_nTimeZone * 3600;

	if(m_oSysUtc.tmFlag != 0)
	{
		g_theSttDeviceStatus->m_nSync = m_oSysUtc.tmFlag;
	}

	memset(&m_oSysInfo, 0, sizeof(Drv_SysInfo));
	g_oDrvMutex.lock();
	nSize = read(m_nCommfd, (char *)&m_oSysInfo, 0x204);
	g_oDrvMutex.unlock();

	if(nSize != sizeof(Drv_SysInfo))
	{
		return FALSE;
	}

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
			m_nRegCtrlDigital |= 1 << 6; //ON/OFF_KIO
			SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
			Sleep(50);
		}
	}

	m_nBatCalcCnt++;
	AnalysisDrvSysInfo(m_oSysInfo.stBack[1], 0, STT_MODULE_TYPE_VOLT);
	AnalysisDrvSysInfo(m_oSysInfo.stBack[0], 1, STT_MODULE_TYPE_CURRENT);

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
			//待机态
			if(m_oBatInfoRef0.fVolt < 9.0)
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
				if(m_oBatInfoRef1.fVolt < 9.0)
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

			long nSecond, nNSecond;
			CDateTime::GetDateTime(nSecond, nNSecond);

			if((nSecond - m_nBatLastTime) > 10 || fBatList.count() > 10)
			{
				fBatList.clear();
			}

			m_nBatLastTime = nSecond;
			fBatList.append(m_oBatInfo.fVolt);
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

	BOOL bSetRegCtrlDigital = FALSE;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase == NULL)
	{
		if(m_nBatCalcCnt > 26)
		{
			if((m_nRegCtrlDigital >> 6) & 0x01)
			{
				m_nRegCtrlDigital &= ~(1 << 6); //ON/OFF_KIO
				bSetRegCtrlDigital = TRUE;
				m_nBatCalcCnt = 0;
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
				m_nTestStopTick = -1;

				if((m_nRegCtrlDigital >> 6) & 0x01)
				{
					m_nRegCtrlDigital &= ~(1 << 6); //ON/OFF_KIO
					bSetRegCtrlDigital = TRUE;
					m_nBatCalcCnt = 0;
				}
			}
			else
			{
				if(m_nBatCalcCnt > 26)
				{
					if((m_nRegCtrlDigital >> 6) & 0x01)
					{
						m_nRegCtrlDigital &= ~(1 << 6); //ON/OFF_KIO
						bSetRegCtrlDigital = TRUE;
						m_nBatCalcCnt = 0;
					}
				}
			}
		}
	}

	if(bSetRegCtrlDigital)
	{
		SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
	}

	ResetPeripheralRtData();
	return TRUE;
}

float BatTemp_trans(float fVdc)
{
	//V(mv)=1324.0 - 8.194(T-30) - 0.00262(T-30)^2
	//262T^2 + 803680T +V*10^5 - 156746200 = 0
	float a, b, c, s, x1, x2;
	a = 262;
	b = 803680;
	c = fVdc * 100000 - 156746200;
	s = b * b - 4 * a * c;
	x1 = 0;
	x2 = 0;

	if(s < 0)
	{
		return 0;
	}
	else if(s == 0)
	{
		x1 = -b / (2 * a);
		x2 = x1;
	}
	else
	{
		x1 = (-b + sqrt(s)) / (2 * a);
		x2 = (-b - sqrt(s)) / (2 * a);
	}

	if(x1 > -5 && x1 < 60)
	{
		return x1;
	}
	else if(x2 > -5 && x2 < 60)
	{
		return x2;
	}
	else
	{
		return 0;
	}
}

void CSttDevicePNS330::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack, int nModulePos, int nModuleType)
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
		oModuleStatus.m_fBAT[1] = translateVoltBase(unMax, 19.6);
		//控制电源
		voltdc = (oDrv_FeedBack.dat[4] >> 16) & 0xfff; //BAT_temp1
		fBatTemp = translateVoltBase(voltdc * 1.015357, 10.0);
		//        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("FPGA BAT_temp1 = %d,%f"),voltdc,fBatTemp);
		oModuleStatus.m_fVoltDc[1] = BatTemp_trans(fBatTemp * 1000);
		voltdc =  oDrv_FeedBack.dat[4] & 0xfff; //BAT_temp2
		fBatTemp = translateVoltBase(voltdc * 0.98552, 10.0);
		//        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("FPGA BAT_temp2 = %d,%f"),voltdc,fBatTemp);
		oModuleStatus.m_fVoltDc[0] = BatTemp_trans(fBatTemp * 1000);
	}
	else
	{
		oModuleStatus.m_nWarningVal = oDrv_FeedBack.dat[9];
		unMax = (oDrv_FeedBack.dat[8] >> 16) & 0xfff;
		oModuleStatus.m_fBAT[0] = translateVoltBase(unMax, 14.0);
		//控制电源
		voltdc = (oDrv_FeedBack.dat[4] >> 16) & 0xfff; //BAT_V8.4
		oModuleStatus.m_fVoltDc[1] = translateVoltBase(voltdc, 10) / 7.85 * 8.31;
		voltdc =  oDrv_FeedBack.dat[4] & 0xfff; //BAT_V4.2
		oModuleStatus.m_fVoltDc[0] = translateVoltBase(voltdc, 5) / 4.23 * 4.15;
	}

	//功率电源
	if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		voltdc = (oDrv_FeedBack.dat[1] >> 16) & 0xfff;
		oModuleStatus.m_fVoltDc[2] = translateVoltBase(voltdc, 214.0);
		voltdc =  oDrv_FeedBack.dat[1] & 0xfff;
		oModuleStatus.m_fVoltDc[3] = translateVoltBase(voltdc, 214.0);
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
		long nChanNum = 3;//3I
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule != NULL)
		{
			if(pModule->m_oModuleAttr.m_nChannelNum > 7)
			{
				nChanNum = 6;//6I
			}
		}

		CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

		if(pSttTestBase != NULL && pSttTestBase->GetTestStarting() && g_theSystemConfig->m_nHasAnalog)
		{
			float fPowerVoltMax, fPowerVoltMin;
			float fChannelVoltMax, fChannelVoltMin;
			fPowerVoltMax = oModuleStatus.m_fVoltDc[2];
			fPowerVoltMin = oModuleStatus.m_fVoltDc[3];

			if(fPowerVoltMax > 0 && fPowerVoltMin < 0)
			{
				for(int j = 0; j < 6; j++)
				{
					fChannelVoltMax = oModuleStatus.m_oChannel[j].m_fVoltMax;
					fChannelVoltMin = oModuleStatus.m_oChannel[j].m_fVoltMin;

					if(fChannelVoltMax > fPowerVoltMax * 0.95)
					{
						if(j < nChanNum)
						{
							oModuleStatus.m_oChannel[j].m_bIsOverLoad = 1;//电流开路
							g_theSttDeviceStatus->m_nIBreak = 1;
						}
					}
				}
			}
		}
	}
#endif
}

void CSttDevicePNS330::GetVoltCurRtData()
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase == NULL)
	{
		return;
	}

	GetRtData();
}

void CSttDevicePNS330::SetRegisterValue(unsigned int nAddr, unsigned int nValue)
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, nAddr, nValue);
	g_oDrvMutex.unlock();
}

void CSttDevicePNS330::DAPowerCtrl()
{
	unsigned int nFPGADelay = m_nUIModulePower;//斜率控制
	switch(m_nUIModulePower)
	{
	case UIModulePower_20A:
	{
		nFPGADelay |= 700<<16;
	}
		break;
	case UIModulePower_10A:
	{
		nFPGADelay |= 50<<16;
	}
		break;
	}

	SetRegisterValue(PNS330_RegAddr_FPGACtrl, nFPGADelay);
}

void CSttDevicePNS330::PreStartTestPro()
{
	m_nTestStopTick = -1;
	m_nRegCtrlDigital |= 1 << 6; //ON/OFF_KIO
	SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);

	if(g_theSystemConfig->m_nHasAnalog)
	{
		m_nRegCtrlAnalog |= 1 << 8; //ON/OFF_PA
		m_nRegCtrlAnalog |= 1 << 9; //ON/OFF_VI
		m_nRegCtrlAnalog &= ~(1 << 19); //LED_VOUT
		m_nRegCtrlAnalog |= 1 << 20; //K_VPout
		m_nRegCtrlAnalog |= 1 << 21; //K_IPout
		SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);

		long nPowerMode = STT_CurrentMODULE_POWER_LOW;

		if(m_nBootMode == 0)
		{
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
		}
		else
		{
			for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_UI;i++)
			{
				PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_UI[i];
				if(pModule!=NULL)
				{
					if(pModule->m_oModuleAttr.m_nModuleIndex == 16)
					{
						for(int nIndex=0;nIndex<g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
						{
							tmt_CurModuleGear &oCurModuleGear=g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];
							if(oCurModuleGear.m_nModulePos == 16)
							{
								nPowerMode = oCurModuleGear.m_nIPowerMode;
								break;
							}
						}
						break;
					}
				}
			}
		}

		switch(m_nUIModulePower)
		{
		case UIModulePower_20A:
		{
			Sleep(700);//一档固有时间

			if(nPowerMode > STT_CurrentMODULE_POWER_LOW)
			{
				float nDA = 3.5;
				if(nPowerMode == STT_CurrentMODULE_POWER_HIGH)
				{
					nDA = 6.5;
				}
				float fDelay = nDA*1000/3.5;
				Sleep((long)fDelay);
			}
		}
			break;
		case UIModulePower_10A:
		{
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
			break;
		}
	}
}

void CSttDevicePNS330::SetPeripheral()
{
	tmt_Peripheral *pPeripheral = &g_theSystemConfig->m_oPeripheral;
	//液晶背光 亮度bit7-bit0 [0,100] 配置后由触摸驱动自动维护。背光时间,单位分钟 bit15-bit8 [0,10],0代表一直高亮
	//bit23-bit16 额定最低亮度,bit31-bit24 额定最高亮度
	unsigned int nValue = 70;//亮度百分比

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
	nValue |= 70 << 24;
	g_oDrvMutex.lock();
	ioctl(m_nTouchfd, 0x7000002c, nValue);
	g_oDrvMutex.unlock();

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
		SetRegisterValue(0xe0000018, 124); //57600
	}
	else
	{
		m_nRegCtrlDigital &= ~(1 << 1);
		SetRegisterValue(0xe0000018, 62); //115200
	}

	SetRegisterValue(PNS330_RegAddr_DigitalCtrl, m_nRegCtrlDigital);
	//主板ST口模式设置，330默认RX2是B码
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x102, m_nMainSTMode); //00:None 01:FT3 10:PPS 11:BCode
	g_oDrvMutex.unlock();
}

void CSttDevicePNS330::AfterTestFinishedPro()
{
	//停止实验后重置秒同步配置
	g_oDrvMutex.lock();
	if(g_theSystemConfig->m_bSyncSecond)
	{
		ioctl(m_nfd, 0x110, 1);
	}
	else
	{
		ioctl(m_nfd, 0x110, 0);
	}
	g_oDrvMutex.unlock();

	if(g_theSystemConfig->m_nHasAnalog)
	{
		// m_nRegCtrlAnalog &= ~(1 << 8); //ON/OFF_PA 由FPGA延时15秒后自动关
		// m_nRegCtrlAnalog &= ~(1 << 9); //ON/OFF_VI
		m_nRegCtrlAnalog &= ~(1 << 20); //K_VPout
		m_nRegCtrlAnalog &= ~(1 << 21); //K_IPout
		SetRegisterValue(PNS330_RegAddr_AnalogCtrl, m_nRegCtrlAnalog);
	}

	m_nTestStopTick = 0;
}

void CSttDevicePNS330::SetOutputTime(tmt_ManualTest *pManualTest, tmt_HarmTest *pHarmTest)
{
	if(!g_theSystemConfig->m_nHasAnalog)
	{
		return;
	}

	tmt_channel *pChannel = NULL;
	BOOL bIsManualTest = FALSE;

	if(pManualTest != NULL)
	{
		pChannel = pManualTest->m_oManuParas.m_uiCUR;
		bIsManualTest = TRUE;
	}

	if(pHarmTest != NULL)
	{
		pChannel = pHarmTest->m_oHarmParas.m_uiCUR;
	}

	if(pChannel == NULL)
	{
		return;
	}

	PSTT_MODULE pModule;

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_UI; i++)
	{
		pModule = g_theDeviceSystemParameter->m_oModules_UI[i];

		if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
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
		return;
	}

	float fIMax = 0;
	float fAmp;

	for(int k = 0; k < 10; k++)
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

		fAmp = pChannel[m_nTmtPos].Harm[1].fAmp;

		if(!bIsManualTest)
		{
			for(int i = 2; i <= 31; i++)
			{
				fAmp += pChannel[m_nTmtPos].Harm[i].fAmp;
			}
		}

		if(fAmp > fIMax)
		{
			fIMax = fAmp;
		}
	}

	if(bIsManualTest)
	{
		if(pManualTest->m_oManuParas.m_bDC)
		{
			fIMax = fIMax * 2;
		}
	}

	long nPowerMode = STT_CurrentMODULE_POWER_HIGH;

	for(int nIndex = 0; nIndex < g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum; nIndex++)
	{
		tmt_CurModuleGear &oCurModuleGear = g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];

		if(oCurModuleGear.m_nModulePos == pModule->m_oModuleAttr.m_nModuleIndex)
		{
			nPowerMode = oCurModuleGear.m_nIPowerMode;
			break;
		}
	}

	float fOutPutTime = 0.0;

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
		if(fIMax > 5.001)
		{
			fOutPutTime = 10.0 * 10.0 / fIMax;
		}
		else
		{
			fOutPutTime = 90.0 * 10.0 / fIMax;
		}
	}

	if(bIsManualTest)
	{
		pManualTest->m_oManuParas.m_fOutPutTime = fOutPutTime;
	}
	else
	{
		pHarmTest->m_oHarmParas.m_fOutPutTime = fOutPutTime;
	}
}

