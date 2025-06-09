#include "stdafx.h"
#include "SttDeviceBase.h"
#include "./Module/PowerCtrl/SttPowerCtrlCom.h"
#include "../SttTest/Common/tmt_test_paras_head.h"
#include "../Engine/SttServerTestCtrlCntr.h"
#include "../Engine/QT/SttTestServerEngine.h"


long g_nNeedReportUTC = 1;
long g_nNeedReportRTDATA = 1;
long g_nNeedReportEvents = 1;
long g_nNeedReportDevExcept = 1;
long g_nGetSystemStateTickCnt = 0;
float g_fAuxVolt = 0;

#ifdef _PSX_QT_LINUX_
float sinData[SINCOUNT * 2 + 4];
#include "time.h"
#include "QDebug"
#include "QDir"
#endif

long nIecReadPos = 0;
long nIec64ReadSizeTotal = 0;
BOOL bIecThreadRun = FALSE;
BOOL bExitIecDetectThread = FALSE;
IECDetectResult oIECDetectResult;
CRingMemBuf *g_pIecDetectBuf;
QMutex g_oDrvMutex;

CSttDeviceBase *CSttDeviceBase::g_pSttDeviceBase = NULL;

CSttDeviceBase::CSttDeviceBase()
{
	m_nBootMode = 0;//0-基本模式
	m_nIecPkgFormat = 1;//1-完整报文
	m_nUseIecCfgCRC = 1;//1-使用Iec61850Config下发的CRC
	m_nIsIecMode = 0;//0-非IEC模式
	m_nMainSTMode = 0b0101;//00-None 01:FT3 10:PPS  11:BCode
	memset(&m_oIecRecvCfg, 0, sizeof(IecRecvCfg));
	m_pIECConfigFt3 = (Drv_IECConfigFt3 *)malloc(sizeof(Drv_IECConfigFt3));
	m_nIECDetectIdx = 0;
	memset(&oIECDetectResult, 0, sizeof(IECDetectResult));
	m_oPowerDAMngr.nUse = 0;
	m_nVoltPowerRefVal = 0;//1.5/3.3*255 会影响待机温度
	m_nCurrPowerRefVal = 30;//1.8/3.3*255
	m_nModuleHotCnt = 0;//模块过热84度信号过滤
	m_nOnTimerMs = 50;//50ms典型值
	m_nDeviceOnTimerMs = 1000;
	m_nDeviceOnTimerCount = 0;
	m_bDevStaIsInit = FALSE;

	for(int nIndex = 0; nIndex < MAX_CURRENT_COUNT; nIndex++)
	{
		m_oCurrAmp[nIndex] = 0;
	}

	m_pReplayModulesBuf = new Drv_BlockPkg[12];//最多12个回放模块
	m_pReplayChsBuf = new float[80 * COMTRADE_REPLAY_PKG_POINTS / 2 + 10];//最多80路回放数据
	m_oManuRtList.clear();
	g_pIecDetectBuf = new CRingMemBuf;
	g_pIecDetectBuf->Create(1024 * 1024 * 2);
	pthread_t nthreadid;
	int nRet = pthread_create(&nthreadid, NULL, ProIecDetectThread, (LPVOID)this);
#ifdef _PSX_QT_LINUX_

	if(nRet == 0)
	{
		qDebug() << ">>>>>>Create ProIecDetectThread";
	}

#endif
	stt_init_stt_device_status();
}

CSttDeviceBase::~CSttDeviceBase()
{
	bExitIecDetectThread = TRUE;
	Sleep(1000);
	free(m_pIECConfigFt3);

	if(m_pReplayChsBuf != NULL)
	{
		delete m_pReplayChsBuf;
		m_pReplayChsBuf = NULL;
	}

	if(m_pReplayModulesBuf != NULL)
	{
		delete m_pReplayModulesBuf;
		m_pReplayModulesBuf = NULL;
	}

	if(g_pIecDetectBuf != NULL)
	{
		delete g_pIecDetectBuf;
		g_pIecDetectBuf = NULL;
	}
}

void CSttDeviceBase::InitModulePowerCtrl()
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
#ifdef _MainBoard_PI_

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
#elif _MainBoard_PTU_

			case STT_MODULE_VOLT_V270_270:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV270_PTU(FALSE));
				break;

			case STT_MODULE_VOLT_V270_380:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV270_PTU(TRUE));
				break;

			case STT_MODULE_VOLT_V300_300:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV300_PTU(FALSE));
				break;

			case STT_MODULE_VOLT_V300_440:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV300_PTU(TRUE));
				break;
#elif _MainBoard_PN_

			case STT_MODULE_VOLT_V130_130:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV130_PN);
				break;

			case STT_MODULE_VOLT_V248_248:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV248_PN);
				break;

			case STT_MODULE_VOLT_V270_270:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV270_PN);
				break;

			case STT_MODULE_VOLT_V300_300:
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV300_PN);
				break;

			default:
				//PN常用130伏模块
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV130_PN);
				break;
#else
				//一些非常规的插件模块,由各自工程的派生类去创建对应的硬件
#endif
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
#if (defined(_MainBoard_PI_)||defined(_MainBoard_PTU_)||defined(_MainBoard_PN_))

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
#else
				//一些非常规的插件模块,由各自工程的派生类去创建对应的硬件
#endif
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

		switch(pModule->m_oModuleAttr.m_nModulePower)
		{
			case STT_MODULE_UI_V130_C20:
			{
#ifdef _MainBoard_PI_
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV130C20_PI);
				pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[0].m_fChACMaxValue = 20;
				pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[1].m_fChACMaxValue = 20;
				pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[2].m_fChACMaxValue = 20;
				pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[3].m_fChACMaxValue = 130;
				pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[4].m_fChACMaxValue = 130;
				pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[5].m_fChACMaxValue = 130;
#endif
#ifdef _MainBoard_PN_
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV130C20_PN);
#endif
			}
			break;

			case STT_MODULE_UI_V310_C60:
#ifdef _MainBoard_PN_
				pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV310C60_PN);
#endif
				break;

			case STT_MODULE_UI_PFC6A:
				break;

			case STT_MODULE_UI_PIA0103:
				break;
		}

		if(pCSttPowerCtrlBase != NULL)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase = pCSttPowerCtrlBase;
		}
	}
}

void CSttDeviceBase::InitSwitchModule()
{
	m_oSwitchModules.m_nModulesBiCount = 0;
	m_oSwitchModules.m_nModulesBoCount = 0;
	m_oSwitchModules.m_nModulesCount = 0;

	for(int nModulePos = 1; nModulePos < 12; nModulePos++)
	{
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount; nIndex++)
		{
			PSTT_MODULE pModule = &g_theDeviceSystemParameter->m_oModules[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_SWITCH
					|| pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
			{
				if(nModulePos == pModule->m_oModuleAttr.m_nModuleIndex)
				{
					long nSIndex = m_oSwitchModules.m_nModulesCount;
					if(nSIndex == (BIO_MODULE_MAX - 1))
					{
						CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("程序可控的开关量模块总数%d个，实际配置了%d个，插件位置高的无效"),
												   BIO_MODULE_MAX - 1, g_theDeviceSystemParameter->m_nModuleCount_S +
												   g_theDeviceSystemParameter->m_nModuleCount_ADMU);
						continue;
					}

					m_oSwitchModules.oSWITCHINFO[nSIndex].m_nModulePos = nModulePos;

					for(int j = 0; j < 8; j++)
					{
						switch(j)
						{
						case 0:
							for(int i = 0;i < 8;i++)
							{
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = FALSE;
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = FALSE;
							}
							break;
						case 1:
							for(int i = 8;i < 16;i++)
							{
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = FALSE;
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = FALSE;
							}
							break;
						case 2:
							for(int i = 16;i < 24;i++)
							{
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = FALSE;
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = FALSE;
							}
							break;
						case 3:
							for(int i = 24;i < 32;i++)
							{
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = FALSE;
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = FALSE;
							}
							break;
						case 4:
							for(int i = 32;i < 40;i++)
							{
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = FALSE;
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = FALSE;
							}
							break;
						case 5:
							for(int i = 40;i < 48;i++)
							{
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = FALSE;
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = FALSE;
							}
							break;
						case 6:
							for(int i = 48;i < 56;i++)
							{
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = FALSE;
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = FALSE;
							}
							break;
						case 7:
							for(int i = 56;i < 64;i++)
							{
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = FALSE;
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = FALSE;
							}
							break;
						}
					}

					if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_SWITCH)
					{
						for(int j = 0; j < 8; j++)
						{
							if(pModule->m_oModuleAttr.m_nSwitchIn[j] < 0)
							{
								continue;
							}

							switch(pModule->m_oModuleAttr.m_nSwitchIn[j])
							{
							case 0:
								switch(j)
								{
								case 0:
									for(int i = 0;i < 8;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = TRUE;
									}
									break;
								case 1:
									for(int i = 8;i < 16;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = TRUE;
									}
									break;
								case 2:
									for(int i = 16;i < 24;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = TRUE;
									}
									break;
								case 3:
									for(int i = 24;i < 32;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = TRUE;
									}
									break;
								case 4:
									for(int i = 32;i < 40;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = TRUE;
									}
									break;
								case 5:
									for(int i = 40;i < 48;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = TRUE;
									}
									break;
								case 6:
									for(int i = 48;i < 56;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = TRUE;
									}
									break;
								case 7:
									for(int i = 56;i < 64;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = TRUE;
									}
									break;
								}
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_nBoCount += 8;
								break;
							case 1:
								switch(j)
								{
								case 0:
									for(int i = 0;i < 8;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = TRUE;
									}
									break;
								case 1:
									for(int i = 8;i < 16;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = TRUE;
									}
									break;
								case 2:
									for(int i = 16;i < 24;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = TRUE;
									}
									break;
								case 3:
									for(int i = 24;i < 32;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = TRUE;
									}
									break;
								case 4:
									for(int i = 32;i < 40;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = TRUE;
									}
									break;
								case 5:
									for(int i = 40;i < 48;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = TRUE;
									}
									break;
								case 6:
									for(int i = 48;i < 56;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = TRUE;
									}
									break;
								case 7:
									for(int i = 56;i < 64;i++)
									{
										m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = TRUE;
									}
									break;
								}
								m_oSwitchModules.oSWITCHINFO[nSIndex].m_nBiCount += 8;
								break;
							}
						}
					}
					else
					{
						//ADMU,固定8开出，4开入
						for(int i = 0;i < 8;i++)
						{
							m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBoPos[i] = TRUE;
						}
						m_oSwitchModules.oSWITCHINFO[nSIndex].m_nBoCount += 8;

						for(int i = 8;i < 12;i++)
						{
							m_oSwitchModules.oSWITCHINFO[nSIndex].m_bBiPos[i] = TRUE;
						}
						m_oSwitchModules.oSWITCHINFO[nSIndex].m_nBiCount += 4;
					}

					m_oSwitchModules.m_nModulesBiCount += m_oSwitchModules.oSWITCHINFO[nSIndex].m_nBiCount;
					m_oSwitchModules.m_nModulesBoCount += m_oSwitchModules.oSWITCHINFO[nSIndex].m_nBoCount;
					m_oSwitchModules.m_nModulesCount++;
				}
			}
		}
	}

	if(m_oSwitchModules.m_nModulesBiCount > MAX_ExBINARY_COUNT)
	{
		m_oSwitchModules.m_nModulesBiCount = MAX_ExBINARY_COUNT;
	}

	if(m_oSwitchModules.m_nModulesBoCount > MAX_ExBINARY_COUNT)
	{
		m_oSwitchModules.m_nModulesBoCount = MAX_ExBINARY_COUNT;
	}

	g_nBinExCount = m_oSwitchModules.m_nModulesBiCount;
	g_nBoutExCount = m_oSwitchModules.m_nModulesBoCount;
}

void GetCompileTime(struct tm *lpCompileTime)
{
	char Mmm[3];
	sscanf(__DATE__, "%3s %d %d", Mmm,
		   &lpCompileTime->tm_mday, &lpCompileTime->tm_year);

	if(strcmp(Mmm, "Jan") == 0)
	{
		lpCompileTime->tm_mon = 1;
	}
	else if(strcmp(Mmm, "Feb") == 0)
	{
		lpCompileTime->tm_mon = 2;
	}
	else if(strcmp(Mmm, "Mar") == 0)
	{
		lpCompileTime->tm_mon = 3;
	}
	else if(strcmp(Mmm, "Apr") == 0)
	{
		lpCompileTime->tm_mon = 4;
	}
	else if(strcmp(Mmm, "May") == 0)
	{
		lpCompileTime->tm_mon = 5;
	}
	else if(strcmp(Mmm, "Jun") == 0)
	{
		lpCompileTime->tm_mon = 6;
	}
	else if(strcmp(Mmm, "Jul") == 0)
	{
		lpCompileTime->tm_mon = 7;
	}
	else if(strcmp(Mmm, "Aug") == 0)
	{
		lpCompileTime->tm_mon = 8;
	}
	else if(strcmp(Mmm, "Sep") == 0)
	{
		lpCompileTime->tm_mon = 9;
	}
	else if(strcmp(Mmm, "Oct") == 0)
	{
		lpCompileTime->tm_mon = 10;
	}
	else if(strcmp(Mmm, "Nov") == 0)
	{
		lpCompileTime->tm_mon = 11;
	}
	else if(strcmp(Mmm, "Dec") == 0)
	{
		lpCompileTime->tm_mon = 12;
	}

	sscanf(__TIME__, "%d:%d:%d", &lpCompileTime->tm_hour,
		   &lpCompileTime->tm_min, &lpCompileTime->tm_sec);
}

void CSttDeviceBase::InitDASetting()
{
#ifdef _PSX_QT_LINUX_

	for(int i = 0; i < ADJUST_MAX_MODULE_COUNT; i++)
	{
		m_oDAPara.nmodule[i] = 0;
		m_oDAPara.nvolt[i] = 0;
		m_oDAParaForTestStop.nmodule[i] = 0;
		m_oDAParaForTestStop.nvolt[i] = 0;
	}

	int nModuleCnt = 0;
	int nModuleIndex = 0;

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			m_oDAPara.nmodule[nModuleCnt] = 0;
		}
		else
		{
			nModuleIndex = pModule->m_oModuleAttr.m_nModuleIndex;
			m_oDAPara.nmodule[nModuleCnt] = ModuleIndexTransToDrv(nModuleIndex);
			m_oDAParaForTestStop.nmodule[nModuleCnt] = ModuleIndexTransToDrv(nModuleIndex);
			unsigned char nByte = m_nVoltPowerRefVal;
			m_oDAParaForTestStop.nvolt[nModuleCnt] = nByte;
			m_oDAParaForTestStop.nvolt[nModuleCnt] |= ((unsigned int)nByte) << (1 * 8);
		}

		nModuleCnt++;
	}

	//CURRENT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule == NULL)
		{
			m_oDAPara.nmodule[nModuleCnt] = 0;
		}
		else
		{
			nModuleIndex = pModule->m_oModuleAttr.m_nModuleIndex;
			m_oDAPara.nmodule[nModuleCnt] = ModuleIndexTransToDrv(nModuleIndex);
			m_oDAParaForTestStop.nmodule[nModuleCnt] = ModuleIndexTransToDrv(nModuleIndex);
			unsigned char nByte = m_nCurrPowerRefVal;
			m_oDAParaForTestStop.nvolt[nModuleCnt] = ((unsigned int)nByte) << (1 * 8);
		}

		nModuleCnt++;
	}

	//UI
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

		if(pModule == NULL)
		{
			m_oDAPara.nmodule[nModuleCnt] = 0;
		}
		else
		{
			nModuleIndex = pModule->m_oModuleAttr.m_nModuleIndex;
			m_oDAPara.nmodule[nModuleCnt] = ModuleIndexTransToDrv(nModuleIndex);
		}

		nModuleCnt++;
	}

	InitModulePowerCtrl();
	WriteDAparaForTestStop();
	//APP版本根据工程编译时间自动生成,编译前需要保证虚拟机的系统时间误差不超1小时
	struct tm *pCompileTime = new tm;
	GetCompileTime(pCompileTime);
	//版本信息格式 "年.月.日-时"
	m_strAppVer.AppendFormat(_T("%d.%d.%d -%d:%d"),
							 pCompileTime->tm_year
							 , pCompileTime->tm_mon
							 , pCompileTime->tm_mday
							 , pCompileTime->tm_hour
							 , pCompileTime->tm_min);
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strAppVer,
		   m_strAppVer.GetString());
	delete pCompileTime;
	//初始化谐波最大值计算查点正弦
	int nCnt = SINCOUNT * 2 + 2;
	float fVal = 2 * pi / SINCOUNT;

	for(int i = 0; i < nCnt; i++)
	{
		sinData[i] = sin(i * fVal);
	}

#endif
}

void CSttDeviceBase::InitDAData()
{
	int nModuleCnt = 0;

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		m_oDAPara.nvolt[nModuleCnt] = 0;
		nModuleCnt++;
	}

	//CURRENT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		m_oDAPara.nvolt[nModuleCnt] = 0;
		nModuleCnt++;
	}

	//UI
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
	{
		m_oDAPara.nvolt[nModuleCnt] = 0;
		nModuleCnt++;
	}
}

void CSttDeviceBase::SetOverLoadTime_PTU(int nTime_ms)
{
	//int nTime_ms=2;
	DeviceOverLoad oDevOverLoad;
	oDevOverLoad.nCnt = 2;
	int nModuleIndex = 2;
	oDevOverLoad.nmodule[0] = ModuleIndexTransToDrv(nModuleIndex);
	oDevOverLoad.nmodule[1] = oDevOverLoad.nmodule[0];
	oDevOverLoad.nOverLoad[0] = nTime_ms * 1000000 / 20;
	oDevOverLoad.nOverLoad[1] = oDevOverLoad.nOverLoad[0];
#ifdef _PSX_QT_LINUX_
	g_oDrvMutex.lock();
	ioctl(m_nCommfd, 0x313, 0);
	write(m_nCommfd, &oDevOverLoad, sizeof(DeviceOverLoad));
	g_oDrvMutex.unlock();
#endif
}

void CSttDeviceBase::SetVoltDApara(float fVMax, float fUdc, int nModuleIndex, BOOL bIsDC)
{
#ifdef _PSX_QT_LINUX_
	PSTT_MODULE oModule_U = g_theDeviceSystemParameter->m_oModules_U[nModuleIndex];

	if(oModule_U == NULL)
	{
		return;
	}

	CSttPowerCtrlBase *pSttPowerCtrlBase = oModule_U->m_oModuleAttr.m_pPowerCtrlBase;

	if(pSttPowerCtrlBase != NULL)
	{
		pSttPowerCtrlBase->SetVoltDA(fVMax, bIsDC);
		pSttPowerCtrlBase->SetVoltDA_DC_300V(fUdc);
		m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
	}

#endif
}

void CSttDeviceBase::SetCurrentDApara_AC(float fSum, int nModuleIndex, float fImax)
{
#ifdef _PSX_QT_LINUX_
	PSTT_MODULE oModule_I = g_theDeviceSystemParameter->m_oModules_I[nModuleIndex];

	if(oModule_I == NULL)
	{
		return;
	}

	CSttPowerCtrlBase *pSttPowerCtrlBase = oModule_I->m_oModuleAttr.m_pPowerCtrlBase;

	if(pSttPowerCtrlBase != NULL)
	{
		pSttPowerCtrlBase->SetCurrentDA(fSum, fImax, nModuleIndex);
		nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
		m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
	}

#endif
}

void CSttDeviceBase::SetCurrentDApara_DC(float fSum, int nModuleIndex)
{
#ifdef _PSX_QT_LINUX_
	PSTT_MODULE oModule_I = g_theDeviceSystemParameter->m_oModules_I[nModuleIndex];

	if(oModule_I == NULL)
	{
		return;
	}

	CSttPowerCtrlBase *pSttPowerCtrlBase = oModule_I->m_oModuleAttr.m_pPowerCtrlBase;

	if(pSttPowerCtrlBase != NULL)
	{
		pSttPowerCtrlBase->SetCurrentDA(fSum, 0, nModuleIndex, TRUE);
		nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
		m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
	}

#endif
}

void CSttDeviceBase::WriteDApara(DeviceDAPara *pDAPara, BOOL IsSysDefaultOut)
{
#ifdef _PSX_QT_LINUX_
	g_oDrvMutex.lock();
	if(IsSysDefaultOut)
	{
		ioctl(m_nCommfd, 0x355, 0);
		write(m_nCommfd, (char *)pDAPara, sizeof(DeviceDAPara));
	}
	else
	{
		ioctl(m_nCommfd, 0x304, 0);
		write(m_nCommfd, (char *)pDAPara, sizeof(DeviceDAPara));
	}
	g_oDrvMutex.unlock();
#endif
}

void CSttDeviceBase::WriteDAparaForTestStop()
{
#ifdef _PSX_QT_LINUX_
	g_oDrvMutex.lock();
	ioctl(m_nCommfd, 0x305, 0);
	write(m_nCommfd, (char *)&m_oDAParaForTestStop, sizeof(DeviceDAPara));
	g_oDrvMutex.unlock();
#endif
}

void CSttDeviceBase::DAValue_PN_3U3I(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt, BOOL bDC,
									 int nDirection, int nGradientHarm, float fGradientAmp, float fUdc)
{
	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		float fVoltMax_3U3I = 0;
		float fVoltMax_6U = 0;
		float fAmp;
		long nTmtChanNum, nTmtPos;
		BOOL bChanIsGradient;
		PSTT_MODULE pModule_6U = NULL;
		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule_UI != NULL)
		{
			//V130C20的3U3I模块的电压部分需要借用位置2电压模块的电源
			if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V130_C20)
			{
				CSttPowerCtrlBase *pSttPowerCtrlBase = pModule_UI->m_oModuleAttr.m_pPowerCtrlBase;

				if(pSttPowerCtrlBase != NULL)
				{
					nTmtChanNum = pModule_UI->m_oModuleAttr.m_nChannelNum;

					//volt
					for(int k = 0; k < nTmtChanNum; k++)
					{
						nTmtPos = pModule_UI->m_nChTmtPos[k];

						if(nTmtPos < 0)
						{
							continue;
						}

						if(pModule_UI->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
						{
							if(nHarmCnt > 1)
							{
								fAmp = pModule_UI->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_fChACMaxValue;
							}
							else
							{
								bChanIsGradient = CheckChannelIsGradient(nTmtPos);

								if(nDirection != 0 && bChanIsGradient)
								{
									fAmp = fGradientAmp;
								}
								else
								{
									fAmp = fabs(pVolt[nTmtPos].Harm[1].fAmp);
								}
							}

							if(fVoltMax_3U3I < fabs(fAmp))
							{
								fVoltMax_3U3I = fabs(fAmp);
							}
						}
					}

					if(g_theDeviceSystemParameter->m_nModuleCount_U > 0)
					{
						pModule_6U = g_theDeviceSystemParameter->m_oModules_U[0];

						if(pModule_6U != NULL)
						{
							nTmtChanNum = pModule_6U->m_oModuleAttr.m_nChannelNum;

							for(int k = 0; k < nTmtChanNum; k++)
							{
								nTmtPos = pModule_6U->m_nChTmtPos[k];

								if(nTmtPos < 0)
								{
									continue;
								}

								if(nHarmCnt > 1)
								{
									fAmp = pModule_6U->m_oModuleAttr.m_fChMax;
								}
								else
								{
									bChanIsGradient = CheckChannelIsGradient(nTmtPos);

									if(nDirection != 0 && bChanIsGradient)
									{
										fAmp = fGradientAmp;
									}
									else
									{
										fAmp = fabs(pVolt[nTmtPos].Harm[1].fAmp);
									}
								}

								if(fVoltMax_6U < fabs(fAmp))
								{
									fVoltMax_6U = fabs(fAmp);
								}
							}
						}
					}

					if(pModule_UI != NULL && pModule_6U != NULL)
					{
						if(fVoltMax_3U3I > fVoltMax_6U)
						{
							if(nHarmCnt > 1)
							{
								SetVoltDApara(fVoltMax_3U3I, fUdc, 0, FALSE);
							}
							else
							{
								SetVoltDApara(fVoltMax_3U3I, fUdc, 0, bDC);
							}
						}
					}
				}
			}
			else if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V310_C60)
			{
				long nCurModuleIndex = -1;

				if(g_theDeviceSystemParameter->m_nModuleCount_U > 0)
				{
					nCurModuleIndex += 1;
				}

				if(g_theDeviceSystemParameter->m_nModuleCount_I > 0)
				{
					nCurModuleIndex += 1;
				}

				if(nCurModuleIndex >= 0)
				{
					m_oDAPara.nvolt[nCurModuleIndex + 1] = (m_oDAPara.nvolt[nCurModuleIndex] >> 8) & 0xFF;
				}
			}
		}
	}
}

void CSttDeviceBase::DAValueCalc_Comm(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt, BOOL bDC,
									  int nDirection, int nGradientHarm, float fGradientAmp, float fUdc)
{
	DAPowerCtrl();
	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;
	int nModuleIndex;
	float fAmp;
	InitDAData();
	BOOL bChanIsGradient = FALSE;
	int nTmtChanNum;
	int nTmtPos;

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		fVsum = 0;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nTmtPos = pModule->m_nChTmtPos[k];

			if(nTmtPos < 0)
			{
				continue;
			}

			if(nHarmCnt > 1)
			{
				fAmp = pModule->m_oModuleAttr.m_fChMax;
			}
			else
			{
				bChanIsGradient = CheckChannelIsGradient(nTmtPos);

				if(nDirection != 0 && bChanIsGradient)
				{
					fAmp = fGradientAmp;
				}
				else
				{
					fAmp = fabs(pVolt[nTmtPos].Harm[1].fAmp);
				}
			}

			if(fVsum < fabs(fAmp))
			{
				fVsum = fabs(fAmp);
			}
		}

		if(nHarmCnt > 1)
		{
			SetVoltDApara(fVsum, fUdc, nIndex, FALSE);
		}
		else
		{
			SetVoltDApara(fVsum, fUdc, nIndex, bDC);
		}
	}

	//Current
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		fIsum = 0;
		fIMax = 0;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		if(nHarmCnt == 1)
		{
			nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			for(int k = 0; k < nTmtChanNum; k++)
			{
				nTmtPos = pModule->m_nChTmtPos[k];

				if(nTmtPos < 0)
				{
					continue;
				}

				bChanIsGradient = CheckChannelIsGradient(nTmtPos, FALSE);

				if((nDirection != 0) && bChanIsGradient)
				{
					fAmp = fGradientAmp;
				}
				else
				{
					fAmp = fabs(pCurrent[nTmtPos].Harm[1].fAmp);
				}

				fAmp = fAmp * pModule->m_fChTmtCoef[k];
				fIsum += fabs(fAmp);

				if(fIMax < fabs(fAmp))
				{
					fIMax = fabs(fAmp);
				}
			}

			if(bDC)
			{
				SetCurrentDApara_DC(fIsum, nIndex);
			}
			else
			{
				switch(pModule->m_oModuleAttr.m_nChMergeMode)
				{
					case STT_CURRENT_ChMergeMode_1Ch_Fixed:
						if(pModule->m_oModuleAttr.m_nChannelNum == 1)
						{
							//6合1模块
							fIMax = fIMax/6.0;
						}
						break;
					case STT_CURRENT_ChMergeMode_3Ch_Fixed:
						if(pModule->m_oModuleAttr.m_nChannelNum == 3)
						{
							//6合3模块
							fIMax = fIMax/2.0;
						}
						break;
				}

				SetCurrentDApara_AC(fIsum, nIndex, fIMax);
			}
		}
		else
		{
			CSttPowerCtrlBase *pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

			if(pSttPowerCtrlBase != NULL)
			{
				pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
				nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
				nModuleIndex += nIndex;
				m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
			}
		}
	}

	//UI
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
	{
		fIsum = 0;
		fVsum = 0;
		fIMax = 0;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		CSttPowerCtrlBase *pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

		if(pSttPowerCtrlBase != NULL)
		{
			nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			//volt
			for(int k = 0; k < nTmtChanNum; k++)
			{
				nTmtPos = pModule->m_nChTmtPos[k];

				if(nTmtPos < 0)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					if(nHarmCnt > 1)
					{
						fAmp = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_fChACMaxValue;
					}
					else
					{
						bChanIsGradient = CheckChannelIsGradient(nTmtPos);

						if(nDirection != 0 && bChanIsGradient)
						{
							fAmp = fGradientAmp;
						}
						else
						{
							fAmp = fabs(pVolt[nTmtPos].Harm[1].fAmp);
						}
					}

					if(fVsum < fabs(fAmp))
					{
						fVsum = fabs(fAmp);
					}
				}
			}

			pSttPowerCtrlBase->SetVoltDA(fVsum, bDC);

			//current
			if(nHarmCnt == 1)
			{
				for(int k = 0; k < nTmtChanNum; k++)
				{
					nTmtPos = pModule->m_nChTmtPos[k];

					if(nTmtPos < 0)
					{
						continue;
					}

					if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_CURRENT)
					{
						bChanIsGradient = CheckChannelIsGradient(nTmtPos, FALSE);

						if((nDirection != 0) && bChanIsGradient)
						{
							fAmp = fGradientAmp;
						}
						else
						{
							fAmp = fabs(pCurrent[nTmtPos].Harm[1].fAmp);
						}

						fIsum += fabs(fAmp);

						if(fIMax < fabs(fAmp))
						{
							fIMax = fabs(fAmp);
						}
					}
				}

				pSttPowerCtrlBase->SetCurrentDA(fIsum, fIMax, nIndex, bDC);
			}
			else
			{
				pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
			}

			nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
			nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
			nModuleIndex += nIndex;
			m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
		}
	}

#ifdef _MainBoard_PN_
	DAValue_PN_3U3I(pVolt, pCurrent, nHarmCnt, bDC, nDirection, nGradientHarm, fGradientAmp, fUdc);
#endif
	WriteDApara(&m_oDAPara);
}

void CSttDeviceBase::DAValueCalc_Manu_UpdateParameter(BOOL bDC)
{
	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;
	int nModuleIndex;
	InitDAData();
	int nTmtChanNum;
	int nTmtPos;

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		fVsum = 0;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nTmtPos = pModule->m_nChTmtPos[k];

			if(nTmtPos < 0)
			{
				continue;
			}

			if(bDC)
			{
				fVsum = pModule->m_oModuleAttr.m_fDefChDcMax;
			}
			else
			{
				fVsum = pModule->m_oModuleAttr.m_fDefChMax;
			}
		}

		float fUdcMax = 0;
		PSTT_CHANNEL_WAVE_ADJUST pChUdcAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0].m_oChUdcAdj;

		if(pChUdcAdj->m_nGearCount > 0)
		{
			fUdcMax = pChUdcAdj->m_oChGearAdj[pChUdcAdj->m_nGearCount - 1].m_fGearValue;
		}

		SetVoltDApara(fVsum, fUdcMax, nIndex, bDC);
	}

	//Current
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		fIsum = 0;
		fIMax = 0;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		CSttPowerCtrlBase *pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

		if(pSttPowerCtrlBase != NULL)
		{
			pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
			nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
			nModuleIndex += nIndex;
			m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
		}
	}

	//UI
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
	{
		fIsum = 0;
		fVsum = 0;
		fIMax = 0;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		CSttPowerCtrlBase *pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

		if(pSttPowerCtrlBase != NULL)
		{
			pSttPowerCtrlBase->SetVoltDA_State();
			pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
			nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
			nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
			nModuleIndex += nIndex;
			m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
		}
	}

#ifdef _MainBoard_PN_

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule_UI != NULL)
		{
			if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V310_C60)
			{
				long nCurModuleIndex = -1;

				if(g_theDeviceSystemParameter->m_nModuleCount_U > 0)
				{
					nCurModuleIndex += 1;
				}

				if(g_theDeviceSystemParameter->m_nModuleCount_I > 0)
				{
					nCurModuleIndex += 1;
				}

				if(nCurModuleIndex >= 0)
				{
					m_oDAPara.nvolt[nCurModuleIndex + 1] = (m_oDAPara.nvolt[nCurModuleIndex] >> 8) & 0xFF;
				}
			}
		}
	}

#endif
	WriteDApara(&m_oDAPara);
}

//谐波总含量及加权含量不超限
BOOL CSttDeviceBase::GetChannelContentOK(tmt_channel &oChannel, int nModuleType, int nDirection, int nHarmIndex, float fGradientAmp, float fChMax)
{
	float HarmContentSet = 1;
	float fAmpBase = oChannel.Harm[1].fAmp;

	if(nDirection != 0 && nHarmIndex == 1)
	{
		//基波递变
		fAmpBase = fGradientAmp;
	}

	if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		if(fChMax < 144)
		{
			if(fAmpBase < 57.75)
			{
				return TRUE;
			}
			else
			{
				//谐波总含量,10*4%=40% (PTU200L送检标准)
				//谐波总含量,8%+6%+4%+2%+1.5%+1%+8%+6%+4%+2%+1.5%+8%=52% (PTU国网验证中心标准)
				//谐波加权含量,(2+3+5+7+9+11+13+15+17+21)*4%=103*4%=412% (PTU200L送检标准)
				//谐波加权含量,2*8%+3*6%+4*4%+5*2%+6*1.5%+7*1%+8*8%+9*6%+10*4%+11*2%+12*1.5%+13*8%=378% (PTU国网验证中心标准)
				HarmContentSet = 40.1;
			}
		}
		else if(fChMax < 271)
		{
			if(fAmpBase < 150.1)
			{
				return TRUE;
			}
			else
			{
				HarmContentSet = 40.1;
			}
		}
		else if(fChMax < 348)
		{
			if(fAmpBase < 220.1)
			{
				return TRUE;
			}
			else
			{
				HarmContentSet = 20.1;
			}
		}
		else
		{
			return FALSE;
		}

		/***
		if(fAmpBase<60)
		{
			//谐波总含量 2%+3%+4%+5%+6%+7%+8%+9%+10%+11%+12%+13%=90%
			//谐波加权含量,2*2%+3*3%+4*4%+5*5%+6*6%+7*7%+8*8%+9*9%+10*10%+11*11%+12*12%+13*13%=818%
			HarmContentSet1=90.5;
			HarmContentSet2=818.5;
		}
		else if(fAmpBase<=100.1)
		{
			//谐波总含量,10*4%=40% (PTU200L送检标准)
			//谐波总含量,8%+6%+4%+2%+1.5%+1%+8%+6%+4%+2%+1.5%+8%=52% (PTU国网验证中心标准)

			//谐波加权含量,(2+3+5+7+9+11+13+15+17+21)*4%=103*4%=412% (PTU200L送检标准)
			//谐波加权含量,2*8%+3*6%+4*4%+5*2%+6*1.5%+7*1%+8*8%+9*6%+10*4%+11*2%+12*1.5%+13*8%=378% (PTU国网验证中心标准)

			HarmContentSet1=52.5;
			HarmContentSet2=412.5;
		}
		else if(fAmpBase<=220.1)
		{
			//谐波总含量,10%
			//谐波加权含量 21*10%=210%
			HarmContentSet1=10.5;
			HarmContentSet2=210.5;
		}
		else
		{
			//谐波总含量,2%
			//谐波加权含量 30*2%=60%
			HarmContentSet1=2.5;
			HarmContentSet2=60.5;
		}
		***/
	}
	else if(nModuleType == STT_MODULE_TYPE_CURRENT)
	{
		if(fChMax < 15)
		{
			//12.5A
			//基波额定5A的谐波实验目前不需要特别限制谐波含量
			if(fAmpBase < 5.1)
			{
				return TRUE;
			}
			else
			{
				HarmContentSet = 40.1;
			}
		}
		else if(fChMax < 25)
		{
			//20A
			//基波额定5A的谐波实验目前不需要特别限制谐波含量
			if(fAmpBase < 10.1)
			{
				return TRUE;
			}
			else
			{
				HarmContentSet = 40.1;
			}
		}
		else if(fChMax < 50)
		{
			//40A
			if(fAmpBase < 20.1)
			{
				return TRUE;
			}
			else
			{
				HarmContentSet = 40.1;
			}
		}
		else
		{
			return FALSE;
		}
	}

	float fSum = 0;
	float nContent = 0;
	float fAmp = 0;

	for(int i = 2; i < MAX_HARM_COUNT; i++)
	{
		fAmp = oChannel.Harm[i].fAmp;

		if(nDirection != 0 && nHarmIndex == i)
		{
			fAmp = fGradientAmp;
		}

		fSum += fAmp;
	}

	nContent = fSum * 100 / fAmpBase; //谐波总含量
	BOOL bRet = nContent < HarmContentSet;

	if(!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 限制条件:谐波总含量小于[%.1f]%"), HarmContentSet);
	}

	return bRet;
}

BOOL CSttDeviceBase::GetChannelContentOK_PF300(tmt_channel &oChannel, int nDirection, int nHarmIndex, float fGradientAmp)
{
	return TRUE;
	float HarmContentSet1 = 1;
	float HarmContentSet2 = 1;
	float fAmpBase = oChannel.Harm[1].fAmp;

	if(nDirection != 0 && nHarmIndex == 1)
	{
		//基波递变
		fAmpBase = fGradientAmp;
	}

	if(fAmpBase < EPSINON)
	{
		fAmpBase = EPSINON;
	}
	else
	{
		HarmContentSet1 = 20.0;
		HarmContentSet2 = 40.0;
	}

	float fSum1 = 0;
	float fSum2 = 0;
	float nContent1 = 0;
	float nContent2 = 0;
	float fAmp = 0;

	for(int i = 2; i < MAX_HARM_COUNT; i++)
	{
		fAmp = oChannel.Harm[i].fAmp;

		if(nDirection != 0 && nHarmIndex == i)
		{
			fAmp = fGradientAmp;
		}

		fSum1 += fAmp;
		fSum2 += fAmp * i;
	}

	nContent1 = fSum1 * 100 / fAmpBase; //谐波总含量
	nContent2 = fSum2 * 100 / fAmpBase; //谐波加权含量
	BOOL bRet = (nContent1 < HarmContentSet1) && (nContent2 < HarmContentSet2);

	if(!bRet)
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 限制条件:谐波总含量小于[%.1f]%,谐波加权含量小于[%.1f]%"),
								   HarmContentSet1, HarmContentSet2);

	return bRet;
}

float CSttDeviceBase::GetChannelMax(tmt_channel &oChannel, float fBaseHz, int nDirection, int nHarmIndex, float fGradientAmp)
{
	float fChannelMax = 0;
#ifdef _PSX_QT_LINUX_
	//点赋值,经MR1200录波验证,计算结果基本接近,计算耗时可忽略
	float XWVector[MAX_HARM_COUNT - 1];
	float fXS[MAX_HARM_COUNT - 1];
	float fW[MAX_HARM_COUNT - 1];
	long nSincount = SINCOUNT;
	float fxxs = 0.02 * fBaseHz * SINCOUNT / CIRCLECOUNT;
	float fAngle = 0;
	float fAmp = 0;
	float fv, fV2;

	for(int i = 1; i < MAX_HARM_COUNT; i++)
	{
		fAngle = oChannel.Harm[i].fAngle;

		while(fAngle < 0)
		{
			fAngle += 360;
		}

		while(fAngle >= 360)
		{
			fAngle -= 360;
		}

		XWVector[i - 1] = fAngle * SINCOUNT / 360.0;
		fXS[i - 1] = fxxs * i;
		fW[i - 1] = 0;
	}

	for(int j = 0; j < CHANLEPOINT; j++)
	{
		fv = 0;
		int nIndex = 0;

		for(int i = 1; i < MAX_HARM_COUNT; i++)
		{
			fAmp = oChannel.Harm[i].fAmp;

			if(nDirection != 0)
			{
				if(i == nHarmIndex)
				{
					fAmp = fGradientAmp;
				}
			}

			fv += fAmp * sinData[(unsigned long)(fW[nIndex] + XWVector[nIndex])];
			nIndex++;
		}

		fV2 = (double)G2 * fv  + oChannel.Harm[0].fAmp;

		for(int i = 0; i < MAX_HARM_COUNT - 1; i++)
		{
			fW[i] += fXS[i];

			if(fW[i] > nSincount)
			{
				fW[i] -= nSincount;
			}
		}

		fV2 = fabs(fV2);

		if(fChannelMax < fV2)
		{
			fChannelMax = fV2;
		}
	}

#endif
	return fChannelMax;
}

//各通道波形最大值不超功放最大输出点
BOOL CSttDeviceBase::CheckModuleChannel(float fChanneMax, int nChannel, PSTT_MODULE pModule)
{
	float fMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChACMaxValue * G2;

	if(fChanneMax > fMax)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ModuleChannel Max=%.3f"),
								   fMax);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

int CSttDeviceBase::CheckHarmTestPara(tmt_HarmTest *pTmt)
{
	//0-正常 1-模块配置异常无法判断最大输出能力  2-谐波总幅值超硬件能力  3-谐波含量过大
	ChannelVolts.clear();
	ChannelCurrs.clear();
	int nDirection = 0;
	int nHarmIndex = pTmt->m_oHarmParas.m_oHarmGradient.nHarmIndex;
	float nGradientAmp = 0;

	//仅检查幅值递变
	if(pTmt->m_oHarmParas.m_bAuto && pTmt->m_oHarmParas.m_nGradientTpSelect == GRADIENT_AMP)
	{
		tmt_GradientParas oGradientParas;
		oGradientParas.m_nTestMode = GradientTest_Base;
		oGradientParas.m_nChannel = pTmt->m_oHarmParas.m_nGradientChSelect;
		oGradientParas.m_nType = pTmt->m_oHarmParas.m_nGradientTpSelect;
		TranGradientChannels(oGradientParas, ChannelVolts, ChannelCurrs);
		nDirection = 1;
		nGradientAmp = pTmt->m_oHarmParas.m_oHarmGradient.fEnd;

		if(pTmt->m_oHarmParas.m_oHarmGradient.fStart > pTmt->m_oHarmParas.m_oHarmGradient.fEnd)
		{
			nDirection = -1;
			nGradientAmp = pTmt->m_oHarmParas.m_oHarmGradient.fStart;
		}
	}

	//1.谐波总含量及加权含量不超限
	//2.波形最大值不超功放最大输出点
	float fChannelMax;
	int nTmtPos;
	int nGradientDirection;

	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		if(pModule->m_oModuleAttr.m_pPowerCtrlBase == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Volt[%d]  PowerCtrlBase==NULL"),
									   nIndex);
			return 1;
		}

		for(int nChanIndex = 0; nChanIndex < pModule->m_oModuleAttr.m_nChannelNum; nChanIndex++)
		{
			nTmtPos = pModule->m_nChTmtPos[nChanIndex];

			if(nTmtPos >= 0)
			{
				nGradientDirection = 0;

				for(int i = 0; i < ChannelVolts.size(); i++)
				{
					if(nTmtPos == ChannelVolts.at(i))
					{
						nGradientDirection = nDirection;
						break;
					}
				}

				tmt_channel &oChannel = pTmt->m_oHarmParas.m_uiVOL[nTmtPos];

				if(!GetChannelContentOK(oChannel, STT_MODULE_TYPE_VOLT,
										nGradientDirection, nHarmIndex, nGradientAmp, pModule->m_oModuleAttr.m_fChMax))
				{
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 电压模块[%d]-通道[%d] 谐波含量超约定值"),
											   nIndex, nChanIndex);
					return 3;
				}

				fChannelMax = GetChannelMax(oChannel, pTmt->m_oHarmParas.m_fBaseFre,
											nGradientDirection, nHarmIndex, nGradientAmp);

				if(!CheckModuleChannel(fChannelMax, nChanIndex, pModule))
				{
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Volt[%d]Channel[%d] Max=%.3f"),
											   nIndex, nChanIndex, fChannelMax);
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 电压模块[%d]-通道[%d] 输出最大值超设计"),
											   nIndex, nChanIndex);
					return 2;
				}
			}
		}
	}

	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		if(pModule->m_oModuleAttr.m_pPowerCtrlBase == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Current[%d]  PowerCtrlBase==NULL"),
									   nIndex);
			return 1;
		}

		for(int nChanIndex = 0; nChanIndex < pModule->m_oModuleAttr.m_nChannelNum; nChanIndex++)
		{
			nTmtPos = pModule->m_nChTmtPos[nChanIndex];

			if(nTmtPos >= 0)
			{
				nGradientDirection = 0;

				for(int i = 0; i < ChannelCurrs.size(); i++)
				{
					if(nTmtPos == ChannelCurrs.at(i))
					{
						nGradientDirection = nDirection;
						break;
					}
				}

				tmt_channel &oChannel = pTmt->m_oHarmParas.m_uiCUR[nTmtPos];
				BOOL bRet;

				if(pModule->m_oModuleAttr.m_fChMax < 50)
				{
					bRet = GetChannelContentOK(oChannel, STT_MODULE_TYPE_CURRENT,
											   nGradientDirection, nHarmIndex, nGradientAmp, pModule->m_oModuleAttr.m_fChMax);
				}
				else
				{
					bRet = GetChannelContentOK_PF300(oChannel,
													 nGradientDirection, nHarmIndex, nGradientAmp);
				}

				if(!bRet)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 电流模块[%d]-通道[%d] 谐波含量超约定值"),
											   nIndex, nChanIndex);
					return 3;
				}

				fChannelMax = GetChannelMax(oChannel, pTmt->m_oHarmParas.m_fBaseFre,
											nGradientDirection, nHarmIndex, nGradientAmp);

				if(!CheckModuleChannel(fChannelMax, nChanIndex, pModule))
				{
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Current[%d]Channel[%d] Max=%.3f"),
											   nIndex, nChanIndex, fChannelMax);
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 电流模块[%d]-通道[%d] 输出最大值超设计"),
											   nIndex, nChanIndex);
					return 2;
				}
			}
		}
	}

	return 0;
}

#define HARM_POINT 80
float CSttDeviceBase::CalWaveMaxValue(float *pfAmp, float *pfAng, float *pfFre, int nChanNum, BOOL bIsDc)
{
	//最多算6项
	float XWVector[6][HARM_POINT];
	float fXS[6][HARM_POINT];
	float fW[6][HARM_POINT];
	float fValue[CHANLEPOINT];
	long nSincount = SINCOUNT;
	float fxxs = 0.02 * 50 * SINCOUNT / CIRCLECOUNT;
	float f1 = 0, f2 = 0; //定义正负半轴瞬时值
	float fMax = 0;

	if(bIsDc)
	{
		for(int nChan = 0; nChan < nChanNum && nChan < 6; nChan++)
		{
			if(pfAmp[nChan] > 0)
			{
				f1 += pfAmp[nChan];
			}
			else
			{
				f2 += pfAmp[nChan];
			}
		}

		fMax = f1;

		if(f1 < fabs(f2))
		{
			fMax = fabs(f2);
		}

		return fMax;
	}

	for(int i = 0; i < nChanNum && i < 6; i++)
	{
		while(pfAng[i] < 0)
		{
			pfAng[i] += 360;
		}

		while(pfAng[i] >= 360)
		{
			pfAng[i] -= 360;
		}

		for(int j = 0; j < HARM_POINT; j++)
		{
			XWVector[i][j] = pfAng[i] * SINCOUNT / 360.0;
			fXS[i][j] = fxxs * (j + 1);
			fW[i][j] = 0;
		}
	}

	for(int j = 0; j < CHANLEPOINT; j++)
	{
		f1 = f2 = 0;

		for(int i = 0; i < nChanNum && i < 6; i++)
		{
			int nIndex = pfFre[i] / 50.0 - 1;

			if(nIndex < 0)
			{
				nIndex = 0;
			}

			if(nIndex > HARM_POINT - 1)
			{
				nIndex = HARM_POINT - 1;
			}

			float fV2 = pfAmp[i] * sinData[(unsigned long)(fW[i][nIndex] + XWVector[i][nIndex])] * (double)1.4142135623731;

			if(fV2 > 0)
			{
				f1 += fV2;
			}
			else
			{
				f2 += fV2;
			}
		}

		if(f1 > fabs(f2))
		{
			fValue[j] = f1;
		}
		else
		{
			fValue[j] = fabs(f2);
		}

		for(int i = 0; i < nChanNum && i < 6; i++)
		{
			for(int k = 0; k < HARM_POINT; k++)
			{
				fW[i][k] += fXS[i][k];

				if(fW[i][k] > nSincount)
				{
					fW[i][k] -= nSincount;
				}
			}
		}
	}

	for(int j = 0; j < CHANLEPOINT; j++)
	{
		if(fValue[j] > fMax)
		{
			fMax = fValue[j];
		}
	}

	return fMax;
}

BOOL CSttDeviceBase::CheckCurrLoadIsSafe(tmt_channel *pChannel, BOOL bIsDc)
{
	long nChannelNum;
	long nTmtPos;
	float fTmtCoef;
	float fChMax;
	PSTT_MODULE pModule;

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
			float fAmp = pChannel[nTmtPos].Harm[1].fAmp;
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

		if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
				||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
				||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
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

				STT_MODULE_CH_DEF &oChDef = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel];

				if(oChDef.m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					fAmp[nCnt] = pChannel[nTmtPos].Harm[1].fAmp;
					fAng[nCnt] = pChannel[nTmtPos].Harm[1].fAngle;
					fFre[nCnt] = pChannel[nTmtPos].Harm[1].fFreq;
					nCnt++;
				}
			}

			float fMaxPoint = CalWaveMaxValue(fAmp, fAng, fFre, nCnt, bIsDc);

			if(bIsDc)
			{
				fChMax = 15.0;
			}
			else
			{
				if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
				{
					fChMax = 28.286;
				}
				else
				{
					fChMax = 14.143;
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

					float fAmp = pChannel[nTmtPos].Harm[1].fAmp;

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

BOOL CSttDeviceBase::CheckCurrLoadIsSafe_moduleoutput(tmt_channel *pChannel, BOOL bIsDc, PSTT_MODULE pModule)
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
		if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
				||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
				||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
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
			}
			else
			{
				if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
				{
					fChMax = 28.286;
				}
				else
				{
					fChMax = 14.143;
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

void CSttDeviceBase::MeasDev_Init()
{
	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount; i++)
	{
		STT_MODULE &oModule = g_theDeviceSystemParameter->m_oModules[i];

		if(oModule.m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_MEAS_VOLT
				|| oModule.m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_MEAS_CURRENT)
		{
			MEAS_MODULE &oMeasModule = g_MeasDevice->oModules[g_MeasDevice->nModuleCnt];
			oMeasModule.nModulePos = oModule.m_oModuleAttr.m_nModuleIndex;
			oMeasModule.nModuleType = oModule.m_oModuleAttr.m_nModuleType;
			oMeasModule.nChanCount = oModule.m_oModuleAttr.m_nChannelNum;

			if(oMeasModule.nChanCount > 6)
			{
				oMeasModule.nChanCount = 6;
			}

			for(int nChannel = 0; nChannel < oMeasModule.nChanCount; nChannel++)
			{
				oMeasModule.oChannels[nChannel].nHarmCount = 32;
				oMeasModule.oChannels[nChannel].init();
			}

			g_MeasDevice->nModuleCnt++;
		}
	}
}

BOOL CSttDeviceBase::OnTimer(BOOL bExec)
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

	if(m_oPowerDAMngr.nUse)
	{
		if(m_oPowerDAMngr.nTickCnt == m_oPowerDAMngr.nTickTotal)
		{
			WriteDApara(&m_oDAPara);//解决电流模块异响
			m_oPowerDAMngr.nUse = 0;
		}

		m_oPowerDAMngr.nTickCnt++;
	}

	stt_init_stt_device_status();
	g_theSttDeviceStatus->m_nUdc = g_fAuxVolt > 0.001 ? 1 : 0;
	g_theSttDeviceStatus->m_bPowerAC = 1;
#ifdef _PSX_QT_LINUX_
	memset(&m_oSysUtc, 0, sizeof(Drv_SysUtc));
	g_oDrvMutex.lock();
	int nSize = read(m_nCommfd, (char *)&m_oSysUtc, 0x205);
	g_oDrvMutex.unlock();

	if(nSize != sizeof(Drv_SysUtc))
	{
		return FALSE;
	}

	if(m_oSysUtc.tmFlag != 0)
	{
		g_theSttDeviceStatus->m_nSync = m_oSysUtc.tmFlag;
	}

	g_theSttDeviceStatus->m_nUtc_s = m_oSysUtc.tm_h;
	g_theSttDeviceStatus->m_nUtc_ns = m_oSysUtc.tm_l;
	g_theSttDeviceStatus->m_nUser_s = g_theSttDeviceStatus->m_nUtc_s
									  + g_theSttDeviceStatus->m_nTimeZone * 3600;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase != NULL && pSttTestBase->GetTestStarting())
	{
		if(g_theSystemConfig->m_nHasAnalog == 0)
		{
			return TRUE;
		}
	}

	memset(&m_oSysInfo, 0, sizeof(Drv_SysInfo));
	g_oDrvMutex.lock();
	nSize = read(m_nCommfd, (char *)&m_oSysInfo, 0x204);
	g_oDrvMutex.unlock();

	if(nSize != sizeof(Drv_SysInfo))
	{
		return FALSE;
	}

	PST_MODULE_ATTR pModuleAttr;
	int nModulePos = 0;

	for(int nModuleIndex = 0; nModuleIndex < g_theDeviceSystemParameter->m_nModuleCount; nModuleIndex++)
	{
		pModuleAttr = &g_theDeviceSystemParameter->m_oModules[nModuleIndex].m_oModuleAttr;
		nModulePos = pModuleAttr->m_nModuleIndex;

		if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_VOLT || pModuleAttr->m_nModuleType == STT_MODULE_TYPE_CURRENT)
		{
			AnalysisDrvSysInfo(m_oSysInfo.stBack[nModulePos - 1], nModulePos, pModuleAttr->m_nModuleType);
		}
		else
		{
			for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_D; i++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];

				if(pModule == NULL)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_nModuleIndex == nModulePos)
				{
					AnalysisLightPower(m_oSysInfo.stBack[nModulePos - 1], nModulePos);
					break;
				}
			}
		}
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

	return TRUE;
}

void CSttDeviceBase::SetCurrAmp_Monitor(long nIndex, float fAmp)
{
	if(nIndex < MAX_CURRENT_COUNT && nIndex > -1)
	{
		if(g_theSystemConfig->m_nHasAnalog != 0)
		{
			m_oCurrAmp[nIndex] = fAmp;
		}
		else
		{
			m_oCurrAmp[nIndex] = 0;
		}
	}
}

void CSttDeviceBase::AnalysisLightPower(Drv_FeedBack &oDrv_FeedBack, int nModulePos)
{
	long nItemIndex = 0;

	for(unsigned int i = 0; i < g_theSttDeviceStatus->m_nAnalogCount; i++)
	{
		if(g_theSttDeviceStatus->m_oModule[i].m_nModulePos == nModulePos)
		{
			nItemIndex = i;
			break;
		}
	}

	g_theSttDeviceStatus->m_oModule[nItemIndex].m_fLCPortPower[0] = translateLightPower(oDrv_FeedBack.dat[0] & 0xFFFF);
	g_theSttDeviceStatus->m_oModule[nItemIndex].m_fLCPortPower[1] = translateLightPower((oDrv_FeedBack.dat[0] >> 16) & 0xFFFF);
	g_theSttDeviceStatus->m_oModule[nItemIndex].m_fLCPortPower[2] = translateLightPower(oDrv_FeedBack.dat[1] & 0xFFFF);
	g_theSttDeviceStatus->m_oModule[nItemIndex].m_fLCPortPower[3] = translateLightPower((oDrv_FeedBack.dat[1] >> 16) & 0xFFFF);
	g_theSttDeviceStatus->m_oModule[nItemIndex].m_fLCPortPower[4] = translateLightPower(oDrv_FeedBack.dat[2] & 0xFFFF);
	g_theSttDeviceStatus->m_oModule[nItemIndex].m_fLCPortPower[5] = translateLightPower((oDrv_FeedBack.dat[2] >> 16) & 0xFFFF);
	g_theSttDeviceStatus->m_oModule[nItemIndex].m_fLCPortPower[6] = translateLightPower(oDrv_FeedBack.dat[3] & 0xFFFF);
	g_theSttDeviceStatus->m_oModule[nItemIndex].m_fLCPortPower[7] = translateLightPower((oDrv_FeedBack.dat[3] >> 16) & 0xFFFF);
}

void CSttDeviceBase::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack, int nModulePos, int nModuleType)
{
#ifdef _PSX_QT_LINUX_
	PSTT_MODULE pSTT_MODULE = NULL;
	int nModuleIndex = 0;

	if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_U; i++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[i];

			if(pModule == NULL)
			{
				continue;
			}

			if(pModule->m_oModuleAttr.m_nModuleIndex == nModulePos)
			{
				pSTT_MODULE = pModule;
				break;
			}
		}
	}
	else
	{
		for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_I; i++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[i];

			if(pModule == NULL)
			{
				continue;
			}

			if(pModule->m_oModuleAttr.m_nModuleIndex == nModulePos)
			{
				pSTT_MODULE = pModule;
				nModuleIndex = i;
				break;
			}
		}
	}

	if(pSTT_MODULE == NULL)
	{
		return;
	}

	int nItemIndex = 0;

	for(unsigned int i = 0; i < g_theSttDeviceStatus->m_nAnalogCount; i++)
	{
		if(g_theSttDeviceStatus->m_oModule[i].m_nModulePos == nModulePos)
		{
			nItemIndex = i;
			break;
		}
	}

	STT_MODULE_STATUS &oModuleStatus = g_theSttDeviceStatus->m_oModule[nItemIndex];

	if(oModuleStatus.m_nDisable != 0 || oModuleStatus.m_nNeedMonitor == 0)
	{
		return;
	}

	unsigned short unmin, unMax;
	float fmin, fmax;
	float fminarry[6] = {0, 0, 0, 0, 0, 0};
	float fmaxarry[6] = {0, 0, 0, 0, 0, 0};

	for(int j = 0; j < 6; j++)
	{
		unmin = oDrv_FeedBack.dat[j] & 0xfff;
		unMax = (oDrv_FeedBack.dat[j] >> 16) & 0xfff;

		if(nModuleType == STT_MODULE_TYPE_VOLT)
		{
			fmin = translateVolt(unmin);
			fmax = translateVolt(unMax);
		}
		else
		{
			fmin = translateCurrentVolt(unmin);
			fmax = translateCurrentVolt(unMax);
		}

		fminarry[j] = fmin; //最小电压
		fmaxarry[j] = fmax; //最大电压
	}

	int nChMeasPos = 0;

	for(int j = 0; j < 6; j++)
	{
		for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount; i++)
		{
			if(g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleIndex == nModulePos)
			{
				nChMeasPos = g_theDeviceSystemParameter->m_oModules[i].m_nChMeasPos[j];
				break;
			}
		}

		oModuleStatus.m_oChannel[j].m_fVoltMax = fmaxarry[nChMeasPos];
		oModuleStatus.m_oChannel[j].m_fVoltMin = fminarry[nChMeasPos];
	}

	unsigned short voltdc = 0;

	if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		voltdc = (oDrv_FeedBack.dat[6] >> 16) & 0xfff; //电源电压
		oModuleStatus.m_fVoltDc[0] = translateVoltBase(voltdc, 15 * 1.07);
		voltdc =  oDrv_FeedBack.dat[6] & 0xfff;
		oModuleStatus.m_fVoltDc[1] = translateVoltBase(voltdc, 15 * 1.07);
		voltdc = (oDrv_FeedBack.dat[7] >> 16) & 0xfff;
		oModuleStatus.m_fVoltDc[2] = translateVoltBase(voltdc, 200 * 2.2);
		voltdc =  oDrv_FeedBack.dat[7] & 0xfff;
		oModuleStatus.m_fVoltDc[3] = translateVoltBase(voltdc, 200 * 2.2);
	}
	else
	{
		voltdc = (oDrv_FeedBack.dat[6] >> 16) & 0xfff; //电源电压
		oModuleStatus.m_fVoltDc[0] = translateVoltBase(voltdc, 28);
		voltdc =  oDrv_FeedBack.dat[6] & 0xfff;
		oModuleStatus.m_fVoltDc[1] = translateVoltBase(voltdc, 28);
		voltdc = (oDrv_FeedBack.dat[7] >> 16) & 0xfff;
		oModuleStatus.m_fVoltDc[2] = translateVoltBase(voltdc, 25 * 1.1);
		voltdc =  oDrv_FeedBack.dat[7] & 0xfff;
		oModuleStatus.m_fVoltDc[3] = translateVoltBase(voltdc, 25 * 1.1);
	}

	unsigned short tempMax = 0;
	// long temp = (oDrv_FeedBack.dat[9] >> 16) & 0xfff;
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
	temp  = temp * 0.0625;
	oModuleStatus.m_nTemp[2] = temp;

	if(temp > 0 && tempMax < temp)
	{
		tempMax = temp;
	}

	if(nModuleType == STT_MODULE_TYPE_CURRENT)
	{
		if(tempMax >= 0 && tempMax < 100)
		{
			if(tempMax > 75)
			{
				for(int nCurModule = 0; nCurModule < g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum; nCurModule++)
				{
					tmt_CurModuleGear &oCurModuleGear = g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nCurModule];

					if(oCurModuleGear.m_nModulePos == pSTT_MODULE->m_oModuleAttr.m_nModuleIndex)
					{
						oCurModuleGear.m_nIPowerMode = STT_CurrentMODULE_POWER_LOW;
						break;
					}
				}

				CSttPowerCtrlBase *pSttPowerCtrlBase = pSTT_MODULE->m_oModuleAttr.m_pPowerCtrlBase;

				if(pSttPowerCtrlBase != NULL)
				{
					pSttPowerCtrlBase->SetCurrentDA_State(nModuleIndex);
					nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
					m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
				}
				else
				{
					nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
					m_oDAPara.nvolt[nModuleIndex] = 0;
				}

				WriteDApara(&m_oDAPara);
				g_theSttDeviceStatus->m_nOverHeat = 1;
			}

			if(tempMax > 84)
			{
				if(m_nModuleHotCnt > 5)
				{
					//电流模块高温停止实验
					g_theSttDeviceStatus->m_bNeedStop = TRUE;
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("ModulePos=%d,MaxTemperature > 84"), nModulePos);
				}

				m_nModuleHotCnt++;
			}
			else
			{
				m_nModuleHotCnt = 0;
			}
		}
		else
		{
			m_nModuleHotCnt = 0;
		}
	}

	unsigned short nH = (~oDrv_FeedBack.dat[10]) & 0x1;
	oModuleStatus.m_nIsVoltHot = nH; //电压过热
	float fPowerVoltMax = fabs(oModuleStatus.m_fVoltDc[2]);
	float fPowerVoltMin = fabs(oModuleStatus.m_fVoltDc[3]);
	float fOverLoad[6] = {0, 0, 0, 0, 0, 0};

	for(int j = 1; j < 7; j++)
	{
		fOverLoad[j - 1] = (~(oDrv_FeedBack.dat[10] >> j)) & 0x1;
	}

	BOOL bCalCurrOverload = FALSE;
	for(int j = 0; j < 6; j++)
	{
		for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount; i++)
		{
			if(g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleIndex == nModulePos)
			{
				nChMeasPos = g_theDeviceSystemParameter->m_oModules[i].m_nChMeasPos[j];
				break;
			}
		}

		//通道异常或者模块通讯丢失,都会报过载
		//以此标记来停止实验不合适.如果是模块通讯丢失并且测试人员已知晓,可以继续实验.
		oModuleStatus.m_oChannel[j].m_bIsOverLoad = fOverLoad[nChMeasPos]; //过载
		CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

		if(nModuleType == STT_MODULE_TYPE_CURRENT)
		{
			if(pSttTestBase != NULL && pSttTestBase->GetTestStarting() && g_theSystemConfig->m_nHasAnalog)
			{
				if(pSttTestBase->m_strID == STT_MACRO_ID_ManualTest)
				{
					float fAmp = m_oCurrAmp[j];
					if(fAmp > 0.9)
					{
						bCalCurrOverload = TRUE;
					}
				}
			}
		}
	}

	if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		long nChanSize = pSTT_MODULE->m_oModuleAttr.m_nChannelNum;
		for(int j = 0; j < nChanSize; j++)
		{
			if(oModuleStatus.m_oChannel[j].m_bIsOverLoad)
			{
				g_theSttDeviceStatus->m_nUShort = 1;
				break;
			}
		}
	}

	if(bCalCurrOverload)
	{
		for(int j = 0; j < 6; j++)
		{
			//电流模块需要额外判断是否开路
			float fChannelVoltMax = oModuleStatus.m_oChannel[j].m_fVoltMax;
			float fChannelVoltMin = oModuleStatus.m_oChannel[j].m_fVoltMin;
			if(fChannelVoltMax > 0.000001 && fChannelVoltMin < 0)
			{
				//软件判断前提是满足fChannelVoltMax > 0,fChannelVoltMin < 0
				fChannelVoltMax = fabs(oModuleStatus.m_oChannel[j].m_fVoltMax);
				fChannelVoltMin = fabs(oModuleStatus.m_oChannel[j].m_fVoltMin);

				if(fChannelVoltMax < fPowerVoltMax && fChannelVoltMin < fPowerVoltMin)
				{
					//电流回路
				}
				else
				{
					//电流开路
					g_theSttDeviceStatus->m_nIBreak = 1;
				}
			}
			else
			{
				//通道输出大于1A时采集最大最小电压才可信
				//通道实际输出幅值较小,无法判断是否开路
			}
		}
	}
	nH = (~(oDrv_FeedBack.dat[10] >> 7)) & 0x1;
	oModuleStatus.m_nIsDCHot = nH; //直流过热

	if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		nH = (~(oDrv_FeedBack.dat[10] >> 8)) & 0x1;
		oModuleStatus.m_nIsVoltWarining = nH; //电压告警
	}

	nH = (~(oDrv_FeedBack.dat[10] >> 9)) & 0x1;
	oModuleStatus.m_nIsMissWarining = nH; //丢失告警
#endif
}


#include "../SttTest/Common/tmt_gradient_test.h"
void CSttDeviceBase::CalStepValue_Gradient(tmt_GradientParas &oGradientParas, int nHarmIndex)
{
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("递变谐波次数%d"), nHarmIndex);
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("递变始值%.3f"), oGradientParas.m_fStart);
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("递变终值%.3f"), oGradientParas.m_fStop);
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("递变步长%.3f"), oGradientParas.m_fStep);
	m_oGradientParas.m_nStepHarm = nHarmIndex;
	m_oGradientParas.m_fStep = oGradientParas.m_fStep;
	m_oGradientParas.m_fStart = oGradientParas.m_fStart;
	m_oGradientParas.m_fStop = oGradientParas.m_fStop;
	m_oGradientParas.m_nType = oGradientParas.m_nType;
	m_oGradientParas.m_nTestMode = oGradientParas.m_nTestMode;
	float fStart = oGradientParas.m_fStart;
	float fEnd = oGradientParas.m_fStop;
	float fStep = fabs(oGradientParas.m_fStep);

	switch(oGradientParas.m_nType)
	{
		case GRADIENT_AMP:
			if(fStart < fEnd)
			{
				m_oGradientParas.m_nStepDirection = 1;
			}
			else
			{
				m_oGradientParas.m_nStepDirection = -1;
			}

			break;

		case GRADIENT_ANG:
			if(fStart < fEnd)
			{
				m_oGradientParas.m_nStepDirection = 1;
			}
			else
			{
				m_oGradientParas.m_nStepDirection = -1;
			}

			break;

		case GRADIENT_FRE:
			if(fabs(fStart) < fabs(fEnd))
			{
				m_oGradientParas.m_nStepDirection = 1;
			}
			else
			{
				m_oGradientParas.m_nStepDirection = -1;
			}

			break;
	}

	for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
	{
		m_oGradientParas.m_uiVOL[2][i].Ramp[0].nIndex = -1;
		m_oGradientParas.m_uiVOL[2][i].Ramp[1].nIndex = -1;
		m_oGradientParas.m_uiVOL[2][i].Ramp[2].nIndex = -1;
	}

	for(int i = 0; i < MAX_CURRENT_COUNT; i++)
	{
		m_oGradientParas.m_uiCUR[2][i].Ramp[0].nIndex = -1;
		m_oGradientParas.m_uiCUR[2][i].Ramp[1].nIndex = -1;
		m_oGradientParas.m_uiCUR[2][i].Ramp[2].nIndex = -1;
	}

	for(int i = 0; i < ChannelVolts.size(); i++)
	{
		int chan = ChannelVolts.at(i);

		switch(oGradientParas.m_nType)
		{
			case GRADIENT_AMP:
				m_oGradientParas.m_uiVOL[2][chan].Harm[nHarmIndex].fAmp = fStart;
				m_oGradientParas.m_uiVOL[2][chan].Ramp[GRADIENT_AMP].fEnd = fEnd;
				break;

			case GRADIENT_ANG:
				m_oGradientParas.m_uiVOL[2][chan].Harm[nHarmIndex].fAngle = fStart;
				m_oGradientParas.m_uiVOL[2][chan].Ramp[GRADIENT_ANG].fEnd = fEnd;
				break;

			case GRADIENT_FRE:
				float fFreqStart = fabs(fStart);

				if(fFreqStart < EPSINON)
				{
					fFreqStart = 0.001;
				}

				m_oGradientParas.m_uiVOL[2][chan].Harm[nHarmIndex].fFreq = fFreqStart;
				m_oGradientParas.m_uiVOL[2][chan].Ramp[GRADIENT_FRE].fEnd = fabs(fEnd);
				break;
		}

		m_oGradientParas.m_uiVOL[2][chan].Ramp[oGradientParas.m_nType].nIndex = nHarmIndex;
		m_oGradientParas.m_uiVOL[2][chan].Ramp[oGradientParas.m_nType].fStep = fStep;
	}

	for(int i = 0; i < ChannelCurrs.size(); i++)
	{
		int chan = ChannelCurrs.at(i);

		switch(oGradientParas.m_nType)
		{
			case GRADIENT_AMP:
				m_oGradientParas.m_uiCUR[2][chan].Harm[nHarmIndex].fAmp = fStart;
				m_oGradientParas.m_uiCUR[2][chan].Ramp[GRADIENT_AMP].fEnd = fEnd;
				break;

			case GRADIENT_ANG:
			{
				m_oGradientParas.m_uiCUR[2][chan].Harm[nHarmIndex].fAngle = fStart;
				m_oGradientParas.m_uiCUR[2][chan].Ramp[GRADIENT_ANG].fEnd = fEnd;
			}
			break;

			case GRADIENT_FRE:
				float fFreqStart = fabs(fStart);

				if(fFreqStart < EPSINON)
				{
					fFreqStart = 0.001;
				}

				m_oGradientParas.m_uiCUR[2][chan].Harm[nHarmIndex].fFreq = fFreqStart;
				m_oGradientParas.m_uiCUR[2][chan].Ramp[GRADIENT_FRE].fEnd = fabs(fEnd);
				break;
		}

		m_oGradientParas.m_uiCUR[2][chan].Ramp[oGradientParas.m_nType].nIndex = nHarmIndex;
		m_oGradientParas.m_uiCUR[2][chan].Ramp[oGradientParas.m_nType].fStep = fStep;
	}
}

void CSttDeviceBase::SetChannelSelect(tmt_GradientParas &oGradientParas)
{
	TranGradientChannels(oGradientParas, ChannelVolts, ChannelCurrs);
}

void CSttDeviceBase::InitParaBeforeGradient(tmt_GradientParas &oGradientParas)
{
	m_oGradientParas.m_fPrepareTime = oGradientParas.m_fPrepareTime;//用于RTDADA第一包数据判断
	m_oGradientParas.m_fPreFaultTime = oGradientParas.m_fPreFaultTime;

	if(oGradientParas.m_nSttTestMode == GradientTest_Base_1
			||oGradientParas.m_nSttTestMode == GradientTest_URamp
			||oGradientParas.m_nSttTestMode == GradientTest_IRamp)
	{
		//变化前、故障前、故障态都由上位机直接指定
		for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
		{
			if(i < GRADIENT_CHAN_COUNT)
			{
				for(int j = 0; j < 3; j++)
				{
					m_oGradientParas.m_uiVOL[j][i].Harm[0].fAmp =
						oGradientParas.m_uiVOL[j][i].Harm[0].fAmp;
					m_oGradientParas.m_uiVOL[j][i].Harm[1].fAmp =
						oGradientParas.m_uiVOL[j][i].Harm[1].fAmp;
					m_oGradientParas.m_uiVOL[j][i].Harm[1].fFreq =
						oGradientParas.m_uiVOL[j][i].Harm[1].fFreq;
					m_oGradientParas.m_uiVOL[j][i].Harm[1].fAngle =
						oGradientParas.m_uiVOL[j][i].Harm[1].fAngle;
				}
			}
		}

		for(int i = 0; i < MAX_CURRENT_COUNT; i++)
		{
			if(i < GRADIENT_CHAN_COUNT)
			{
				for(int j = 0; j < 3; j++)
				{
					m_oGradientParas.m_uiCUR[j][i].Harm[0].fAmp =
						oGradientParas.m_uiCUR[j][i].Harm[0].fAmp;
					m_oGradientParas.m_uiCUR[j][i].Harm[1].fAmp =
						oGradientParas.m_uiCUR[j][i].Harm[1].fAmp;
					m_oGradientParas.m_uiCUR[j][i].Harm[1].fFreq =
						oGradientParas.m_uiCUR[j][i].Harm[1].fFreq;
					m_oGradientParas.m_uiCUR[j][i].Harm[1].fAngle =
						oGradientParas.m_uiCUR[j][i].Harm[1].fAngle;
				}
			}
		}

		return;
	}

	//6U6I软件资源
	float fAngleVoltage[6] = {0, -120.0, 120.0, 0, -120.0, 120.0};//20220719 zhouhj 增加电压电流相序设置功能
	float fAngleCurrent[6] = {0, -120.0, 120.0, 0, -120.0, 120.0};

	if(oGradientParas.m_nPhaseSet[0] == 1) //电压相序负序
	{
		fAngleVoltage[1] = 120.0f;
		fAngleVoltage[2] = -120.0f;
		fAngleVoltage[4] = 120.0f;
		fAngleVoltage[5] = -120.0f;
	}
	else if(oGradientParas.m_nPhaseSet[0] == 2) //电压相序零序
	{
		fAngleVoltage[1] = 0.0f;
		fAngleVoltage[2] = 0.0f;
		fAngleVoltage[4] = 0.0f;
		fAngleVoltage[5] = 0.0f;
	}

	if(oGradientParas.m_nPhaseSet[1] == 1) //电流相序负序
	{
		fAngleCurrent[1] = 120.0f;
		fAngleCurrent[2] = -120.0f;
		fAngleCurrent[4] = 120.0f;
		fAngleCurrent[5] = -120.0f;
	}
	else if(oGradientParas.m_nPhaseSet[1] == 2) //电流相序零序
	{
		fAngleCurrent[1] = 0.0f;
		fAngleCurrent[2] = 0.0f;
		fAngleCurrent[4] = 0.0f;
		fAngleCurrent[5] = 0.0f;
	}

	for(int i = 3; i < 6; i++)
	{
		fAngleVoltage[i] = fAngleVoltage[i] - oGradientParas.m_fDiffIAngle;
		fAngleCurrent[i] = fAngleCurrent[i] - oGradientParas.m_fDiffIAngle;
	}

	//变化前,额定
	for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
	{
		if(i < GRADIENT_CHAN_COUNT)
		{
			m_oGradientParas.m_uiVOL[0][i].Harm[0].fAmp = 0;
			m_oGradientParas.m_uiVOL[0][i].Harm[1].fAmp = oGradientParas.m_fEDU;
			m_oGradientParas.m_uiVOL[0][i].Harm[1].fFreq = oGradientParas.m_fEDFreq;
			m_oGradientParas.m_uiVOL[0][i].Harm[1].fAngle = fAngleVoltage[i];
		}
		else
		{
			m_oGradientParas.m_uiVOL[0][i].Harm[0].fAmp = 0;
			m_oGradientParas.m_uiVOL[0][i].Harm[1].fAmp = 0;
		}
	}

	for(int i = 0; i < MAX_CURRENT_COUNT; i++)
	{
		if(i < GRADIENT_CHAN_COUNT)
		{
			m_oGradientParas.m_uiCUR[0][i].Harm[0].fAmp = 0;
			m_oGradientParas.m_uiCUR[0][i].Harm[1].fAmp = oGradientParas.m_fEDI;
			m_oGradientParas.m_uiCUR[0][i].Harm[1].fFreq = oGradientParas.m_fEDFreq;
			m_oGradientParas.m_uiCUR[0][i].Harm[1].fAngle = fAngleCurrent[i] - oGradientParas.m_fEDUaIaAngle;
		}
		else
		{
			m_oGradientParas.m_uiCUR[0][i].Harm[0].fAmp = 0;
			m_oGradientParas.m_uiCUR[0][i].Harm[1].fAmp = 0;
		}
	}

	//故障前
	for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
	{
		if(i < GRADIENT_CHAN_COUNT)
		{
			m_oGradientParas.m_uiVOL[1][i].Harm[0].fAmp = 0;
			m_oGradientParas.m_uiVOL[1][i].Harm[1].fAmp = (i < 3) ? oGradientParas.m_fG1Volt : oGradientParas.m_fG2Volt;
			m_oGradientParas.m_uiVOL[1][i].Harm[1].fFreq = oGradientParas.m_fHz;
			m_oGradientParas.m_uiVOL[1][i].Harm[1].fAngle = fAngleVoltage[i];
		}
		else
		{
			m_oGradientParas.m_uiVOL[1][i].Harm[0].fAmp = 0;
			m_oGradientParas.m_uiVOL[1][i].Harm[1].fAmp = 0;
		}
	}

	for(int i = 0; i < MAX_CURRENT_COUNT; i++)
	{
		if(i < GRADIENT_CHAN_COUNT)
		{
			m_oGradientParas.m_uiCUR[1][i].Harm[0].fAmp = 0;
			m_oGradientParas.m_uiCUR[1][i].Harm[1].fAmp = (i < 3) ? oGradientParas.m_fG1Current : oGradientParas.m_fG2Current;
			m_oGradientParas.m_uiCUR[1][i].Harm[1].fFreq = oGradientParas.m_fHz;
			m_oGradientParas.m_uiCUR[1][i].Harm[1].fAngle = fAngleCurrent[i] - oGradientParas.m_fEDUaIaAngle;
		}
		else
		{
			m_oGradientParas.m_uiCUR[1][i].Harm[0].fAmp = 0;
			m_oGradientParas.m_uiCUR[1][i].Harm[1].fAmp = 0;
		}
	}

	//故障态参数
	if(oGradientParas.m_nSttTestMode == GradientTest_Base)
	{
		for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
		{
			if(i < GRADIENT_CHAN_COUNT)
			{
				m_oGradientParas.m_uiVOL[2][i].Harm[0].fAmp = m_oGradientParas.m_uiVOL[1][i].Harm[0].fAmp;
				m_oGradientParas.m_uiVOL[2][i].Harm[1].fAmp = m_oGradientParas.m_uiVOL[1][i].Harm[1].fAmp;
				m_oGradientParas.m_uiVOL[2][i].Harm[1].fFreq = m_oGradientParas.m_uiVOL[1][i].Harm[1].fFreq;
				m_oGradientParas.m_uiVOL[2][i].Harm[1].fAngle = m_oGradientParas.m_uiVOL[1][i].Harm[1].fAngle;
			}
			else
			{
				m_oGradientParas.m_uiVOL[2][i].Harm[0].fAmp = 0;
				m_oGradientParas.m_uiVOL[2][i].Harm[1].fAmp = 0;
			}
		}

		for(int i = 0; i < MAX_CURRENT_COUNT; i++)
		{
			if(i < GRADIENT_CHAN_COUNT)
			{
				m_oGradientParas.m_uiCUR[2][i].Harm[0].fAmp = m_oGradientParas.m_uiCUR[1][i].Harm[0].fAmp;
				m_oGradientParas.m_uiCUR[2][i].Harm[1].fAmp = m_oGradientParas.m_uiCUR[1][i].Harm[1].fAmp;
				m_oGradientParas.m_uiCUR[2][i].Harm[1].fFreq = m_oGradientParas.m_uiCUR[1][i].Harm[1].fFreq;
				m_oGradientParas.m_uiCUR[2][i].Harm[1].fAngle = m_oGradientParas.m_uiCUR[1][i].Harm[1].fAngle;
			}
			else
			{
				m_oGradientParas.m_uiCUR[2][i].Harm[0].fAmp = 0;
				m_oGradientParas.m_uiCUR[2][i].Harm[1].fAmp = 0;
			}
		}
	}
	else
	{
		for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
		{
			if(i < GRADIENT_CHAN_COUNT)
			{
				m_oGradientParas.m_uiVOL[2][i].Harm[0].fAmp = oGradientParas.m_uiVOL[2][i].Harm[0].fAmp;
				m_oGradientParas.m_uiVOL[2][i].Harm[1].fAmp = oGradientParas.m_uiVOL[2][i].Harm[1].fAmp;
				m_oGradientParas.m_uiVOL[2][i].Harm[1].fFreq = oGradientParas.m_uiVOL[2][i].Harm[1].fFreq;
				m_oGradientParas.m_uiVOL[2][i].Harm[1].fAngle = oGradientParas.m_uiVOL[2][i].Harm[1].fAngle;
			}
			else
			{
				m_oGradientParas.m_uiVOL[2][i].Harm[0].fAmp = 0;
				m_oGradientParas.m_uiVOL[2][i].Harm[1].fAmp = 0;
			}
		}

		for(int i = 0; i < MAX_CURRENT_COUNT; i++)
		{
			if(i < GRADIENT_CHAN_COUNT)
			{
				m_oGradientParas.m_uiCUR[2][i].Harm[0].fAmp = oGradientParas.m_uiCUR[2][i].Harm[0].fAmp;
				m_oGradientParas.m_uiCUR[2][i].Harm[1].fAmp = oGradientParas.m_uiCUR[2][i].Harm[1].fAmp;
				m_oGradientParas.m_uiCUR[2][i].Harm[1].fFreq = oGradientParas.m_uiCUR[2][i].Harm[1].fFreq;
				m_oGradientParas.m_uiCUR[2][i].Harm[1].fAngle = oGradientParas.m_uiCUR[2][i].Harm[1].fAngle;
			}
			else
			{
				m_oGradientParas.m_uiCUR[2][i].Harm[0].fAmp = 0;
				m_oGradientParas.m_uiCUR[2][i].Harm[1].fAmp = 0;
			}
		}
	}
}

void CSttDeviceBase::TranGradientChannels(tmt_GradientParas &oGradientParas, vector<int> &ChannelVolts, vector<int> &ChannelCurrs)
{
	ChannelVolts.clear();
	ChannelCurrs.clear();
	//Ua1 Ub1 Uc1 Ua2 Ub2 Uc2
	//Ia1 Ib1 Ic1 Ia2 Ib2 Ic2
	int nRampChannel = oGradientParas.m_nChannel;

	switch(oGradientParas.m_nSttTestMode)
	{
		case GradientTest_Base:
		case GradientTest_Base_1:
		{
			switch(nRampChannel)
			{
				case U1a:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					break;

				case U1b:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case U1c:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case U1ab:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case U1bc:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case U1ca:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case U1abc:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case U2a:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					break;

				case U2b:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case U2c:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case U2abc:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I1a:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					break;

				case I1b:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case I1c:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case I1ab:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case I1bc:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case I1ca:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case I1abc:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case I2a:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					break;

				case I2b:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case I2c:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I2abc:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case U_All:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I_All:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case Udc:
					break;

				case Uz:
					break;

				case U2ab:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case U2bc:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case U2ca:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I2ab:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case I2bc:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I2ca:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I1abcAdd:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);

					if(oGradientParas.m_nType == GRADIENT_AMP)
					{
						oGradientParas.m_fStart = oGradientParas.m_fStart / 3;
						oGradientParas.m_fStop = oGradientParas.m_fStop / 3;
						oGradientParas.m_fStep = oGradientParas.m_fStep / 3;
						//故障前
						float fAngle = m_oGradientParas.m_uiCUR[1][0].Harm[1].fAngle;
						m_oGradientParas.m_uiCUR[1][1].Harm[1].fAngle = fAngle;
						m_oGradientParas.m_uiCUR[1][2].Harm[1].fAngle = fAngle;
						//故障态
						m_oGradientParas.m_uiCUR[2][0].Harm[1].fAngle = fAngle;
						m_oGradientParas.m_uiCUR[2][1].Harm[1].fAngle = fAngle;
						m_oGradientParas.m_uiCUR[2][2].Harm[1].fAngle = fAngle;
					}

					break;

				case I2abcAdd:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);

					if(oGradientParas.m_nType == GRADIENT_AMP)
					{
						oGradientParas.m_fStart = oGradientParas.m_fStart / 3;
						oGradientParas.m_fStop = oGradientParas.m_fStop / 3;
						oGradientParas.m_fStep = oGradientParas.m_fStep / 3;
						//故障前
						float fAngle = m_oGradientParas.m_uiCUR[1][3].Harm[1].fAngle;
						m_oGradientParas.m_uiCUR[1][4].Harm[1].fAngle = fAngle;
						m_oGradientParas.m_uiCUR[1][5].Harm[1].fAngle = fAngle;
						//故障态
						m_oGradientParas.m_uiCUR[2][3].Harm[1].fAngle = fAngle;
						m_oGradientParas.m_uiCUR[2][4].Harm[1].fAngle = fAngle;
						m_oGradientParas.m_uiCUR[2][5].Harm[1].fAngle = fAngle;
					}

					break;

				case U1abcAdd:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);

					if(oGradientParas.m_nType == GRADIENT_AMP)
					{
						oGradientParas.m_fStart = oGradientParas.m_fStart / 3;
					}

					break;

				case U2abcAdd:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);

					if(oGradientParas.m_nType == GRADIENT_AMP)
					{
						oGradientParas.m_fStart = oGradientParas.m_fStart / 3;
					}

					break;

				case FreAll:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case Ia1Ia2Add:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);

					if(oGradientParas.m_nType == GRADIENT_AMP
							|| oGradientParas.m_nType == GRADIENT_ANG)
					{
						oGradientParas.m_fStart = oGradientParas.m_fStart / 2;
					}

					break;

				case Ib1Ib2Add:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);

					if(oGradientParas.m_nType == GRADIENT_AMP
							|| oGradientParas.m_nType == GRADIENT_ANG)
					{
						oGradientParas.m_fStart = oGradientParas.m_fStart / 2;
					}

					break;

				case Ic1Ic2Add:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);

					if(oGradientParas.m_nType == GRADIENT_AMP
							|| oGradientParas.m_nType == GRADIENT_ANG)
					{
						oGradientParas.m_fStart = oGradientParas.m_fStart / 2;
					}

					break;

				case Ia1Ia2Add_Ib1Ib2Add_Ic1Ic2Add:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);

					if(oGradientParas.m_nType == GRADIENT_AMP
							|| oGradientParas.m_nType == GRADIENT_ANG)
					{
						oGradientParas.m_fStart = oGradientParas.m_fStart / 2;
					}

					break;

				case Ia1Ia2_Ib1Ib2_Ic1Ic2_Add:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);

					if(oGradientParas.m_nType == GRADIENT_AMP
							|| oGradientParas.m_nType == GRADIENT_ANG)
					{
						oGradientParas.m_fStart = oGradientParas.m_fStart / 6;
					}

					break;
			}
		}
		break;

		case GradientTest_URamp:
		{
			switch(nRampChannel)
			{
				case a1:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					break;

				case b1:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case c1:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case a2:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					break;

				case b2:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case c2:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case ab1:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case bc1:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case ca1:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					break;

				case ab2:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case bc2:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case ca2:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					break;

				case abc1:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case abc2:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case abc12:
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;
			}
		}
		break;

		case GradientTest_IRamp:
		{
			switch(nRampChannel)
			{
				case a1:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					break;

				case b1:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case c1:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case a2:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					break;

				case b2:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case c2:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case ab1:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case bc1:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case ca1:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					break;

				case ab2:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case bc2:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case ca2:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					break;

				case abc1:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case abc2:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case abc12:
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;
			}
		}
		break;
	}
}
/*********SttGradientTest**********/

/*********IEC**********/
#ifdef _PSX_QT_LINUX_
#include "Module/Driver466/IEC_GlobalDefine.h"
#endif

void CSttDeviceBase::SetIecDetect(BOOL bEnable)
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase != NULL && pSttTestBase->GetTestStarting())
	{
		//实验中，以Iec61850Cfg的订阅为准，不能探测
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[warning] 实验进行中，以IEC配置为准，禁用报文探测功能"));
		return;
	}

	if(bEnable)
	{
		m_nIsIecMode = 1;
		m_nIecPkgFormat = 0;

		g_pIecDetectBuf->Init();
		nIecReadPos = 0;
		nIec64ReadSizeTotal = 0;
		memset(&oIECDetectResult, 0, sizeof(IECDetectResult));
		m_nIECDetectIdx = 0;

		for(int i = 0;i < 2;i++)
		{
			unsigned char nMainSTMode = (m_nMainSTMode >> (i*2))&0x3;
			long nCount = oIECDetectResult.nCount;
			if(nMainSTMode != 1)
			{
				oIECDetectResult.item[nCount].bFT3 = TRUE;
				oIECDetectResult.item[nCount].nSTMode = nMainSTMode;
				oIECDetectResult.item[nCount].nPort_FT3 = i;
				oIECDetectResult.item[nCount].nBaud_FT3 = 0;
			}

			oIECDetectResult.nCount++;
		}

		bIecThreadRun = TRUE;
		memset(&m_oIecRecvCfg, 0, sizeof(IecRecvCfg));		

		g_oDrvMutex.lock();
		ioctl(m_nCommfd, 0x126, 1);//开启FPGA DMA缓存
		g_oDrvMutex.unlock();
		Sleep(10);
		m_oIecRecvCfg.nType = 0;
		g_oDrvMutex.lock();
		ioctl(m_nCommfd, 0x30C, 1);
		write(m_nCommfd, &m_oIecRecvCfg, sizeof(IecRecvCfg));
		g_oDrvMutex.unlock();
		Sleep(10);
		g_oDrvMutex.lock();
		ioctl(m_nCommfd, 0x131, DMA_TYPE_PROBE);
		g_oDrvMutex.unlock();
	}
	else
	{		
		bIecThreadRun = FALSE;
		g_oDrvMutex.lock();
		ioctl(m_nCommfd, 0x131, DMA_TYPE_NULL);
		ioctl(m_nCommfd, 0x126, 0);//关闭FPGA DMA缓存
		g_oDrvMutex.unlock();
		Sleep(20);
		m_nIecPkgFormat = 1;
		m_nIsIecMode = 0;
	}
}

void CSttDeviceBase::SetIecFilter(IECRecordItems *pRecordItems)
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase != NULL && pSttTestBase->GetTestStarting())
	{
		//实验中，以Iec61850Cfg的订阅为准，不下载新的CRC
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[warning] 实验进行中，以IEC配置为准，禁用报文探测功能"));
		return;
	}

	if(pRecordItems->bEnable)
	{
		m_nIsIecMode = 1;
		CSttDeviceBase::g_pSttDeviceBase->m_nUseIecCfgCRC = 0;

		m_nIecPkgFormat = 1;
		memset(&m_oIecRecvCfg, 0, sizeof(IecRecvCfg));
		m_oIecRecvCfg.nType = 4;
		m_oIecRecvCfg.ncount = 0;

		for(int i = 0; i < pRecordItems->nCount61850; i++)
		{
			if(pRecordItems->item61850[i].nFilterVal > 0)
			{
				m_oIecRecvCfg.oIecSub[m_oIecRecvCfg.ncount].CRC =
					pRecordItems->item61850[i].nFilterVal;
				m_oIecRecvCfg.ncount++;
			}
		}

		g_oDrvMutex.lock();
		ioctl(m_nCommfd, 0x30C, 2);
		write(m_nCommfd, (char *)&m_oIecRecvCfg, sizeof(IecRecvCfg));
		g_oDrvMutex.unlock();

		if(pRecordItems->nCount6044 > 0)
		{
			Ft3SubDatas oSubDatas;
			memset(&oSubDatas, 0, sizeof(Ft3SubDatas));
			oSubDatas.nModuleCnt = m_pIECConfigFt3->mdCnt;

			for(int i = 0; i < m_pIECConfigFt3->mdCnt; i++)
			{
				oSubDatas.ft3SubData[i].nModule = m_pIECConfigFt3->item[i].module;
				oSubDatas.ft3SubData[i].nOffset = m_pIECConfigFt3->item[i].nSTRecvBeginIdx;
			}

			for(int i = 0; i < pRecordItems->nCount6044; i++)
			{
				IECRecordItem_6044 oItem_6044 = pRecordItems->item6044[i];
				int nBoard = -1;

				for(int j = 0; j < m_pIECConfigFt3->mdCnt; j++)
				{
					if(oItem_6044.nPort >= m_pIECConfigFt3->item[j].nSTRecvBeginIdx
							&& oItem_6044.nPort <= m_pIECConfigFt3->item[j].nSTRecvEndIdx)
					{
						nBoard = j;
						break;
					}
				}

				if(nBoard >= 0)
				{
					Ft3SubData *pft3sub = &oSubDatas.ft3SubData[nBoard];
					int nBlockIdx = pft3sub->nCnt;
					pft3sub->ft3Item[nBlockIdx].nPort =
							oItem_6044.nPort - m_pIECConfigFt3->item[nBoard].nSTRecvBeginIdx;
					pft3sub->ft3Item[nBlockIdx].npacketLen = oItem_6044.nPkgLen;
					pft3sub->ft3Item[nBlockIdx].nbaud = oItem_6044.nBaudRate;//自适应时，要留出18个字节逻辑时间给FPGA
					pft3sub->ft3Item[nBlockIdx].nMapCnt = 0;
					pft3sub->nCnt++;
				}
			}

			g_oDrvMutex.lock();
			ioctl(m_nCommfd, 0x310, 0);
			write(m_nCommfd, (char *)&oSubDatas, sizeof(Ft3SubDatas));
			g_oDrvMutex.unlock();
		}

		g_oDrvMutex.lock();
		if(pRecordItems->bHasSmv)
		{
			ioctl(m_nCommfd, 0x126, 1);//开启FPGA DMA缓存
		}
		else
		{
			ioctl(m_nCommfd, 0x126, 0);//关闭FPGA DMA缓存
		}
		ioctl(m_nCommfd, 0x131, DMA_TYPE_RECORD);
		g_oDrvMutex.unlock();
	}
	else
	{
		CSttDeviceBase::g_pSttDeviceBase->m_nUseIecCfgCRC = 1;
		g_oDrvMutex.lock();
		ioctl(m_nCommfd, 0x131, DMA_TYPE_NULL);
		ioctl(m_nCommfd, 0x126, 0);//关闭FPGA DMA缓存
		g_oDrvMutex.unlock();
		m_nIsIecMode = 0;
	}
}


void *ProIecDetectThread(LPVOID pParam)
{
	unsigned char pszBuf[28];
	long nCrc;//控制块CRC
	long nPort;
	long nBaud;
	int i;

	while(1)
	{
		if(bExitIecDetectThread)
		{
			break;
		}

		if(!bIecThreadRun)
		{
			Sleep(200);
			continue;
		}

		if(g_pIecDetectBuf->GetDataLen() >= 28)
		{
			g_pIecDetectBuf->ReadBuf((char *)pszBuf, nIecReadPos, nIec64ReadSizeTotal, 4);

			if(pszBuf[0] == 0x05 && pszBuf[1] == 0x64 && pszBuf[2] == 0x05 && pszBuf[3] == 0x64)
			{
				g_pIecDetectBuf->ReadBuf((char *)pszBuf, nIecReadPos, nIec64ReadSizeTotal, 24);

				if((pszBuf[13] >> 4) == 3)
				{
					//FPGA不支持探测报文长度是奇数的情况
					nPort = pszBuf[13] & 0xF;
					nBaud = pszBuf[15];

					for(i = 0; i < oIECDetectResult.nCount; i++)
					{
						if(oIECDetectResult.item[i].bFT3 == TRUE)
						{
							if(nPort == oIECDetectResult.item[i].nPort_FT3
									&& nBaud == oIECDetectResult.item[i].nBaud_FT3)
							{
								break;
							}
						}
					}

					if(i == oIECDetectResult.nCount)
					{
						oIECDetectResult.item[i].bFT3 = TRUE;
						oIECDetectResult.item[i].nSTMode = 0b01;
						oIECDetectResult.item[i].nPort_FT3 = nPort;
						oIECDetectResult.item[i].nBaud_FT3 = nBaud;
						memcpy(oIECDetectResult.item[i].sData, pszBuf + 12, 12);
						oIECDetectResult.nCount++;

						if(oIECDetectResult.nCount == 200)
						{
							bIecThreadRun = FALSE;
						}
					}
				}
				else
				{
					nCrc = pszBuf[18] << 8 | pszBuf[19];

					for(i = 0; i < oIECDetectResult.nCount; i++)
					{
						if(oIECDetectResult.item[i].bFT3 == FALSE && nCrc == oIECDetectResult.item[i].nCrc)
						{
							break;
						}
					}

					if(i == oIECDetectResult.nCount)
					{
						oIECDetectResult.item[i].bFT3 = FALSE;
						oIECDetectResult.item[i].nCrc = nCrc;
						memcpy(oIECDetectResult.item[i].sData, pszBuf + 12, 12);
						oIECDetectResult.nCount++;

						if(oIECDetectResult.nCount == 200)
						{
							bIecThreadRun = FALSE;
						}
					}
				}
			}
		}
		else
		{
			Sleep(20);
		}
	}

	pthread_exit(0);
}

void CSttDeviceBase::EventProcessEx()
{
	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();

	if(pCurrTest != NULL && pCurrTest->m_bUpdateFPGA)
	{
		return;
	}

	char *pDrvResults = stt_test_get_drvresult_buff();
	int ret;
	CString str, strFt3;

	if(m_nIecPkgFormat == 0)
	{
		g_oDrvMutex.lock();
		ret = read(m_nCommfd, pDrvResults, 0x260);
		g_oDrvMutex.unlock();

		if(ret > 0)
		{
			g_pIecDetectBuf->WriteBuf(pDrvResults, ret);
//            QFile file("/mnt/Stt/log/Data0");
//            if(file.open(QIODevice::WriteOnly))
//            {
//                file.write(pDrvResults, ret);
//                file.flush();
//                file.close();
//                system("sync");
//            }
		}
	}
	else
	{
		g_oDrvMutex.lock();
		ret = read(m_nCommfd, pDrvResults, 0x261);
		g_oDrvMutex.unlock();

		if(ret > 0)
		{
			g_oSttRcdSendSocket.WriteRecordBuf(pDrvResults, ret);
//            QFile file("/mnt/Stt/log/Data1");
//            if(file.open(QIODevice::WriteOnly))
//            {
//                file.write(pDrvResults, ret);
//                file.flush();
//                file.close();
//                system("sync");
//            }
			//FT3
			BOOL bPrint = FALSE;

			if(g_theDeviceSystemParameter->m_nModuleCount_FT3 > 0
					|| g_theDeviceSystemParameter->m_nModuleCount_ADMU > 0)
			{
				bPrint = TRUE;
			}

			if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
			{
				if(g_theSystemConfig->m_nIecFormat == STT_IEC_FORMAT_60044_8DC
						|| g_theSystemConfig->m_nIecFormat == STT_IEC_FORMAT_60044_8)
				{
					bPrint = TRUE;
				}
			}

			if(bPrint)
			{
				str.clear();

				for(int i = 0; i < 1000; i++)
				{
					if(pDrvResults[i] == 0x05 && pDrvResults[i + 1] == 0x64
							&& pDrvResults[i + 2] == 0x05 && pDrvResults[i + 3] == 0x64 && pDrvResults[i + 17] >> 4 == 0x03)
					{
						long nPort = pDrvResults[i + 17] & 0xF;
						str += CString("光口[%1] ").arg(nPort + 1);
						strFt3.clear();
						long nLen = pDrvResults[i + 21];
						i += 28;

						for(int j = 0; j < nLen; j++)
						{
							strFt3 += CString("%1").arg(pDrvResults[i + j], 2, 16, QChar('0'));
						}

						if(nPort < 4)
						{
							strFt3.insert(strFt3.length() - 4, " ");
							//只支持光口1-4格式化
							long nChanSize = m_oFT3DbgChansInfo.oFT3ChanInfo[nPort].nCount - 1;

							for(int j = nChanSize; j >= 0; j--)
							{
								long nChanLen1 = m_oFT3DbgChansInfo.oFT3ChanInfo[nPort].nChanLen1[j];
								long nChanLen2 = m_oFT3DbgChansInfo.oFT3ChanInfo[nPort].nChanLen2[j];
								long nIdx = strFt3.indexOf(" ", 0);

								if(nChanLen2 > 0)
								{
									nIdx = nIdx - nChanLen2 * 2;
									strFt3.insert(nIdx, " ");
									nIdx = nIdx - 4;
									strFt3.insert(nIdx, " ");
								}
								else
								{
									BOOL bCRC = m_oFT3DbgChansInfo.oFT3ChanInfo[nPort].bContainCRC[j];

									if(bCRC)
									{
										nIdx = nIdx - 4;
										strFt3.insert(nIdx, " ");
									}
								}

								strFt3.insert(nIdx - nChanLen1 * 2, " ");
							}
						}

						str += strFt3;
						break;
					}
				}

				if(str.length() > 0)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s"), str.GetString());
				}
			}
		}
	}
}

BOOL CSttDeviceBase::GetIecPktList()
{
	if(oIECDetectResult.nCount > m_nIECDetectIdx)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CSttDeviceBase::stt_xml_serialize_iec_rtdatas(CSttXmlSerializeBase *pXmlSerialize)
{
	CString str;
	CString strCRC;
	CString strAPPID;
	CString strType;
	CString strPort;
	CString strBaudRate;
	CString strSampleRate;
	CString strOnePkgLen;
	CString strSTMode;
	long nResultCnt = oIECDetectResult.nCount;

	for(int i = m_nIECDetectIdx; i < nResultCnt; i++)
	{
		CSttXmlSerializeBase *pXml = pXmlSerialize->xml_serialize("", XPARA_ID_IEC_CB, XPARA_ID_IEC_CB, stt_ParaGroupKey());
		unsigned char bType = (oIECDetectResult.item[i].sData[1] >> 4);

		if(bType == 1)
		{
			strType = XPARA_ID_TYPE_SMV92;
		}
		else if(bType == 2)
		{
			strType = XPARA_ID_TYPE_GOOSE;
		}
		else
		{
			strType = XPARA_ID_TYPE_FT3;
			unsigned char bBaudRate = oIECDetectResult.item[i].sData[3];

			switch(bBaudRate)
			{
				case 0:
					strBaudRate = "2.5";
					break;

				case 1:
					strBaudRate = "5";
					break;

				case 2:
					strBaudRate = "10";
					break;

				default:
					strBaudRate = "20";
			}

			unsigned int nSample = oIECDetectResult.item[i].sData[6] << 8;
			nSample += oIECDetectResult.item[i].sData[7];
			if(nSample > 0)
			{
				nSample = 200000 / nSample;
				nSample = nSample * 100;
			}
			strSampleRate = CString::number(nSample);
			unsigned int nOnePkgLen = oIECDetectResult.item[i].sData[4] << 8;
			nOnePkgLen += oIECDetectResult.item[i].sData[5];
			strOnePkgLen = CString::number(nOnePkgLen);
		}

		pXml->xml_serialize("", XPARA_ID_Type, "", "string", strType);		

		if(bType == 1 || bType == 2)
		{
			strPort = CString::number(oIECDetectResult.item[i].sData[1] & 0xF);
			pXml->xml_serialize("", XPARA_ID_Port, "", "string", strPort);
			strAPPID = CString("%1").arg(oIECDetectResult.item[i].sData[2], 2, 16, QChar('0'));
			strAPPID += CString("%1").arg(oIECDetectResult.item[i].sData[3], 2, 16, QChar('0'));
			strCRC = CString("%1").arg(oIECDetectResult.item[i].sData[6], 2, 16, QChar('0'));
			strCRC += CString("%1").arg(oIECDetectResult.item[i].sData[7], 2, 16, QChar('0'));
			str = "0x";
			str += strAPPID;
			pXml->xml_serialize("", XPARA_ID_APPID, "", "string", str);
			str = "0x";
			str += strCRC;
			pXml->xml_serialize("", XPARA_ID_CRC, "", "string", str);
			int nCnt = oIECDetectResult.item[i].sData[10] * 256 + oIECDetectResult.item[i].sData[11];

			if(strType == XPARA_ID_TYPE_SMV92)
			{
				nCnt = nCnt / 8;
			}

			str = CString::number(nCnt);
			pXml->xml_serialize("", XPARA_ID_ChCount, "", "string", str);
		}
		else
		{
			pXml->xml_serialize("", XPARA_ID_Port, "", "string", oIECDetectResult.item[i].nPort_FT3);
			pXml->xml_serialize("", XPARA_ID_BaudRate, "", "string", strBaudRate);
			pXml->xml_serialize("", XPARA_ID_SampleRate, "", "string", strSampleRate);
			pXml->xml_serialize("", XPARA_ID_OnePkgLen, "", "string", strOnePkgLen);
			switch(oIECDetectResult.item[i].nSTMode)
			{
			case 0:
				strSTMode = "None";
				break;
			case 1:
				strSTMode = "FT3";
				break;
			case 2:
				strSTMode = "PPS";
				break;
			case 3:
				strSTMode = "BCode";
				break;
			}

			pXml->xml_serialize("", XPARA_ID_STMode, "", "string", strSTMode);
		}

		str.clear();

		for(int j = 0; j < 12; j++)
		{
			str += CString("%1").arg(oIECDetectResult.item[i].sData[j], 2, 16, QChar('0'));
		}

		pXml->xml_serialize("", XPARA_ID_PkgDetect, "", "string", str);

		if(bType == 1 || bType == 2)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("Crc=%s"), strCRC.GetString());
		}
	}

	m_nIECDetectIdx = nResultCnt;
}

/*********IEC**********/

/*********DMA**********/
void CSttDeviceBase::SetDMAType(long nDMAType)
{	
	g_oDrvMutex.lock();
	ioctl(m_nCommfd, 0x402, nDMAType);
	g_oDrvMutex.unlock();
}
/*********DMA**********/

void CSttDeviceBase::SetCurMergeConfig()
{
	int nCurrentCtrlMode = 1; //电流模块2组3路独立控制
//m_nMergeCurTerminal==3只有PN466支持
#ifdef _MainBoard_PI_

	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		if(g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex].m_nMergeCurTerminal == 0)
		{
			continue;
		}

		if(g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex].m_nMergeCurTerminal == 1)
		{
			//固定Ia出
			continue;
		}

		switch(g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex].m_nLargeCurOutTerm)
		{
			case STT_LARGE_CUR_OUT_TERM_B:
				break;

			case STT_LARGE_CUR_OUT_TERM_C:
				break;

			default:
				//默认Ia出
				//STT_LARGE_CUR_OUT_TERM_A
				break;
		}
	}

#else

	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		if(g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex].m_nMergeCurTerminal == 3)
		{
			//PN466 电流出3路只能全局设定,不能分模块单独设定.FPGA主板时序限制
			nCurrentCtrlMode = 0; //电流模块2组3路并联控制
			break;
		}
	}

#endif

	g_oDrvMutex.lock();
	ioctl(m_nCommfd, 0x124, nCurrentCtrlMode);
	g_oDrvMutex.unlock();
}
