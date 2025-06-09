#include "stdafx.h"
#include "SttDeviceBase.h"
#include "./Module/PowerCtrl/SttPowerCtrlCom.h"
#include "../SttTest/Common/tmt_test_paras_head.h"
#include "../Engine/SttServerTestCtrlCntr.h"
#include "../Engine/QT/SttTestServerEngine.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../SttTestBase/SttXmlSerialize.h"
#include "SttDeviceStatus.h"

long g_nNeedReportUTC = 1;
long g_nNeedReportRTDATA = 1;
long g_nNeedReportEvents = 1;
long g_nNeedReportDevExcept = 1;
long g_nGetSystemStateTickCnt = 0;
long g_nTmtParaMode = 1;//0-一次值 1-二次值
long g_nEnableDCCurr = 1;//允许电流功放输出直流
long g_nRTDATAMode = 0;//0-完整，1-最简
float g_fAuxVolt = 0;
long g_nLogPrintIsZN = 1;//默认打印中文
CString g_strDrvName = "";
CString g_strAppName = "";

#ifdef _PSX_QT_LINUX_
float sinData[SINCOUNT * 2 + 4];
#include "time.h"
#include "QDebug"
#include "QDir"
#include <sys/ipc.h>
#include <sys/shm.h>
#endif

long nIecReadPos = 0;
long nIec64ReadSizeTotal = 0;
long nIecDetType = 0;
BOOL bIecDetectRun = FALSE;
BOOL bIecRecordRun = FALSE;

IECDetectResult oIECDetectResult;
CRingMemBuf *g_pIecDetectBuf;
CSttDeviceMutex g_oDrvMutex;

pthread_mutex_t g_oTestResultMutex;

CSttDeviceBase *CSttDeviceBase::g_pSttDeviceBase = NULL;

CSttDeviceBase::CSttDeviceBase()
{
	for(int i = 0;i < 10;i++)
	{
		m_oBinSetting.nEType[i] = 1;//默认空接点
		m_nCurnEType[i] = 1;//默认空接点
		for(int j = 0;j < ADJUST_MAX_GEAR_COUNT;j++)
		{
			m_oBinSetting.fCoef[i][j] = 1.0;
			m_oBinSetting.fZero[i][j] = 0.0;
		}
		m_nCurBinaryCode[i] = 0;
		m_nCurBinaryGear[i] = Gear_Null;
	}

	m_nSetAmpPowerCnt = 0;
	g_oDcMeasCfg.m_nDCInGear_I = 0;//默认大档
	m_oDevInputInfo.m_nVerIdx = 0;
	m_oDevInputInfo.m_bMouse = FALSE;
	m_oDevInputInfo.m_strKeyBoard = "";
	m_nSetSysTmCnt = 0;//未设置的状态
	m_nBootMode = 0;//0-基本模式
	m_bTestStarting = FALSE;
	m_nUseIecCfgCRC = 1;//1-使用Iec61850Config下发的CRC
	m_nIsIecMode = 0;//0-IEC配置模式
	m_nMainSTMode = 0b0101;//00-None 01:FT3 10:PPS  11:BCode
	memset(&m_oIecRecvCfg, 0, sizeof(IecRecvCfg));
	m_pIECConfigFt3 = (Drv_IECConfigFt3 *)malloc(sizeof(Drv_IECConfigFt3));
	m_nIECDetectIdx = 0;
	memset(&oIECDetectResult, 0, sizeof(IECDetectResult));
	m_oPowerDAMngr.nUse = 0;
	m_nVoltPowerRefVal = 0;//1.5/3.3*255 会影响待机温度
	m_nCurrPowerRefVal = 30;//1.8/3.3*255
	m_nModuleHotCnt = 0;//模块过热84度信号过滤
	m_nDeviceOnTimerCount = 0;
	m_bDevStaIsInit = FALSE;
	memset(&m_oCurDAPara,0,sizeof(DeviceDAPara));

	m_pReplayModulesBuf = new Drv_BlockPkg[12];//最多12个回放模块
	m_pReplayChsBuf = new float[80 * COMTRADE_REPLAY_PKG_POINTS / 2 + 10];//最多80路回放数据
	m_oManuRtList.clear();
	g_pIecDetectBuf = new CRingMemBuf;
	g_pIecDetectBuf->Create(1024 * 1024 * 2);
	m_pMMapBuf = NULL;

	pthread_mutex_init(&g_oTestResultMutex,NULL);
	pthread_mutex_lock(&g_oTestResultMutex);
	pthread_t nthreadid;
	int nRet = pthread_create(&nthreadid, NULL, ProTestResultThread, (LPVOID)this);
#ifdef _PSX_QT_LINUX_
	if(nRet == 0)
	{
		qDebug() << ">>>>>>Create ProTestResultThread";
	}
#endif
	stt_init_stt_device_status();

	int fd = open("/dev/mem", O_RDWR| O_SYNC, 0655);
	m_pDrvUtcBase = (char*)mmap(0, 4096, PROT_READ, MAP_SHARED, fd, 0x70000000);
	m_pDrvModuleBase = (char*)mmap(0, 8192, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x70000000);
}

CSttDeviceBase::~CSttDeviceBase()
{
	bIecDetectRun = FALSE;
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

	if(m_pDrvUtcBase != NULL)
	{
		munmap(m_pDrvUtcBase,4096);
	}

	if(m_pDrvModuleBase != NULL)
	{
		munmap(m_pDrvModuleBase,8192);
	}

	if(m_pMMapBuf != NULL)
	{
		munmap(m_pMMapBuf,4096);
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
	long nCurrPowerForStop = 70;//默认待机12伏
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
			unsigned char nByte = nCurrPowerForStop;
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
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V130_C20)
			{
#ifdef _MainBoard_PN_
				unsigned char nByte = nCurrPowerForStop;
				m_oDAParaForTestStop.nmodule[nModuleCnt] = ModuleIndexTransToDrv(nModuleIndex);
				m_oDAParaForTestStop.nvolt[nModuleCnt] = nByte;
#endif
			}
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

	long nMngrVer = 0;
	m_shm = NULL;
	m_nShmkey = 2024;
	m_nShareMemoryId = shmget((key_t)m_nShmkey, 4, 0666 | IPC_CREAT);

	if(m_nShareMemoryId == -1)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Requset ShareMemoryId Fail"));
	}

	m_shm = shmat(m_nShareMemoryId, (void *)0, 0);

	if(m_shm == (void *) -1)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Requset ShareMemoryAddr Fail"));
	}
	else
	{
		memcpy(&nMngrVer, m_shm, 4);
	}

	m_strMngrVer.AppendFormat(_T("%d.%d.%d"),
							 (nMngrVer>>16)&0xFF
							 , (nMngrVer>>8)&0xFF
							 , nMngrVer&0xFF);
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strMngrVer,
		   m_strMngrVer.GetString());

	//初始化谐波最大值计算查点正弦
	int nCnt = SINCOUNT * 2 + 2;
    float fVal = 2 * XPI / SINCOUNT;

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
		PSTT_MODULE pModule_I = g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule_I != NULL)
		{
			CSttPowerCtrlBase *pPowerCtrlBase = pModule_I->m_oModuleAttr.m_pPowerCtrlBase;
			if(pPowerCtrlBase != NULL)
			{
				pPowerCtrlBase->SetCurrentDA(0, 0, nIndex);
				m_oDAPara.nvolt[nModuleCnt] = pPowerCtrlBase->GetModuleDA();
			}
		}
		nModuleCnt++;
	}

	//UI
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
	{
		m_oDAPara.nvolt[nModuleCnt] = 0;
		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[nIndex];
		if(pModule_UI != NULL)
		{
			CSttPowerCtrlBase *pPowerCtrlBase = pModule_UI->m_oModuleAttr.m_pPowerCtrlBase;
			if(pPowerCtrlBase != NULL)
			{
				pPowerCtrlBase->SetVoltDA(0, FALSE);
				pPowerCtrlBase->SetCurrentDA_State(nIndex);
				m_oDAPara.nvolt[nModuleCnt] = pPowerCtrlBase->GetModuleDA();
			}
		}
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

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nCommfd, 0x313, 0);
	write(m_nCommfd, &oDevOverLoad, sizeof(DeviceOverLoad));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
}

void CSttDeviceBase::Stt_Xml_Serialize_Channels(CSttXmlSerializeBase *pXmlSerialize)
{
	for(long k = 0; k < g_theSttDeviceStatus->m_nAnalogCount; k++)
	{
		stt_xml_serialize(&g_theSttDeviceStatus->m_oModule[k], k, pXmlSerialize);
	}
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
	//在定时任务中会调用，所以将锁的控制放在调用的地方比较合适
#ifdef _PSX_QT_LINUX_
	if(IsSysDefaultOut)
	{
		ioctl(m_nCommfd, 0x355, 0);
		write(m_nCommfd, (char *)pDAPara, sizeof(DeviceDAPara));
	}
	else
	{
		if(m_nSetAmpPowerCnt < 0xFFFFFFFF)
		{
			m_nSetAmpPowerCnt++;
		}
		ioctl(m_nCommfd, 0x304, 0);
		write(m_nCommfd, (char *)pDAPara, sizeof(DeviceDAPara));
	}
#endif
}

void CSttDeviceBase::WriteDAparaForTestStop()
{
#ifdef _PSX_QT_LINUX_
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nCommfd, 0x305, 0);
	write(m_nCommfd, (char *)&m_oDAParaForTestStop, sizeof(DeviceDAPara));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
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
				fAmp = pModule->m_oModuleAttr.m_fDefChMax;
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

				if(g_nTmtParaMode == 0)
				{
					//界面一次值
					fAmp = fAmp*1000*g_theSystemConfig->GetPTRate(nTmtPos/3);
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
				if(g_nTmtParaMode == 0)
				{
					//界面一次值
					fAmp = fAmp*g_theSystemConfig->GetCTRate(nTmtPos/3);
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
				int nDefChannelNum = pModule->m_oModuleAttr.m_nDefChannelNum;
				if(nDefChannelNum == nTmtChanNum)
				{
					int nPcbChanNum = pModule->m_oModuleAttr.m_nDAChanNum;
					if(nTmtChanNum != nPcbChanNum)
					{
						//单个IO同步控制多块放大电路
						fIMax = fIMax*nTmtChanNum/nPcbChanNum;
					}
				}
				else
				{
					//不匹配的时候，通过m_fChTmtCoef来调整
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
						if(g_nTmtParaMode == 0)
						{
							//界面一次值
							fAmp = fAmp*1000*g_theSystemConfig->GetPTRate(nTmtPos/3);
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
						if(g_nTmtParaMode == 0)
						{
							//界面一次值
							fAmp = fAmp*g_theSystemConfig->GetCTRate(nTmtPos/3);
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

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	WriteDApara(&m_oDAPara);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttDeviceBase::DAValueCalc_CommAsync(tmt_AsyncModules *pAsyncModules, BOOL bDC, int nDirection, float fGradientAmp, float fUdc)
{

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

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	WriteDApara(&m_oDAPara);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttDeviceBase::DAValueCalc_AsyncManu_UpdateParameter()
{
	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;
	int nModuleIndex;
	InitDAData();

	tmt_AsyncModules *pAsyncModuels = &g_pAsyncManualTest->m_oParas.m_oAsyncModuels;
	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		fVsum = 0;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		tmt_AsyncModule *pAnalogModule = NULL;

		for(int i = 0;i < pAsyncModuels->m_nAnalogCount && i < MAX_MODULE_COUNT;i++)
		{
			if(pAsyncModuels->m_oAnalogModules[i].m_nModulePos == pModule->m_oModuleAttr.m_nModuleIndex)
			{
				pAnalogModule = &pAsyncModuels->m_oAnalogModules[i];
				break;
			}
		}

		if(pAnalogModule != NULL)
		{
			if(pAnalogModule->m_nVolChCount > 0)
			{
				if(pAsyncModuels->m_nDc[ASYNC_MODULE_TYPE_ANALOG])
				{
					fVsum = pModule->m_oModuleAttr.m_fDefChDcMax;
				}
				else
				{
					fVsum = pModule->m_oModuleAttr.m_fDefChMax;
				}
			}
		}

		float fUdcMax = 0;
		PSTT_CHANNEL_WAVE_ADJUST pChUdcAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0].m_oChUdcAdj;

		if(pChUdcAdj->m_nGearCount > 0)
		{
			fUdcMax = pChUdcAdj->m_oChGearAdj[pChUdcAdj->m_nGearCount - 1].m_fGearValue;
		}

		SetVoltDApara(fVsum, fUdcMax, nIndex, pAsyncModuels->m_nDc[ASYNC_MODULE_TYPE_ANALOG]);
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

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	WriteDApara(&m_oDAPara);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
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
		oGradientParas.m_nChannel2 = Null;
		oGradientParas.m_nType = pTmt->m_oHarmParas.m_nGradientTpSelect;
		TranGradientChannels(oGradientParas, ChannelVolts, ChannelCurrs,ChannelVolts2, ChannelCurrs2);
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
	tmt_channel oChannel;
	float fPTRate,fCTRate;

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

				fPTRate = 1.0;
				if(g_nTmtParaMode == 0)
				{
					//界面一次值
					for(int i = 0; i < MAX_HARM_COUNT; i++)
					{
						oChannel.Harm[i].fAmp = pTmt->m_oHarmParas.m_uiVOL[nTmtPos].Harm[i].fAmp
								*1000*g_theSystemConfig->GetPTRate(nTmtPos/3);
						oChannel.Harm[i].fAngle = pTmt->m_oHarmParas.m_uiVOL[nTmtPos].Harm[i].fAngle;
						oChannel.Harm[i].fFreq = pTmt->m_oHarmParas.m_uiVOL[nTmtPos].Harm[i].fFreq;
					}
					fPTRate = 1000*g_theSystemConfig->GetPTRate(nTmtPos/3);
				}

				if(!GetChannelContentOK(oChannel, STT_MODULE_TYPE_VOLT,
										nGradientDirection, nHarmIndex, nGradientAmp*fPTRate, pModule->m_oModuleAttr.m_fDefChMax))
				{
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 电压模块[%d]-通道[%d] 谐波含量超约定值"),
											   nIndex, nChanIndex);
					return 3;
				}

				fChannelMax = GetChannelMax(oChannel, pTmt->m_oHarmParas.m_fBaseFre,
											nGradientDirection, nHarmIndex, nGradientAmp*fPTRate);

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

				fCTRate = 1.0;
				if(g_nTmtParaMode == 0)
				{
					//界面一次值
					for(int i = 0; i < MAX_HARM_COUNT; i++)
					{
						oChannel.Harm[i].fAmp = pTmt->m_oHarmParas.m_uiCUR[nTmtPos].Harm[i].fAmp
								*g_theSystemConfig->GetCTRate(nTmtPos/3);
						oChannel.Harm[i].fAngle = pTmt->m_oHarmParas.m_uiCUR[nTmtPos].Harm[i].fAngle;
						oChannel.Harm[i].fFreq = pTmt->m_oHarmParas.m_uiCUR[nTmtPos].Harm[i].fFreq;
					}
					fCTRate = g_theSystemConfig->GetCTRate(nTmtPos/3);
				}
				BOOL bRet;

				if(pModule->m_oModuleAttr.m_fDefChMax < 50)
				{
					bRet = GetChannelContentOK(oChannel, STT_MODULE_TYPE_CURRENT,
											   nGradientDirection, nHarmIndex, nGradientAmp*fCTRate, pModule->m_oModuleAttr.m_fDefChMax);
				}
				else
				{
					bRet = GetChannelContentOK_PF300(oChannel,
													 nGradientDirection, nHarmIndex, nGradientAmp*fCTRate);
				}

				if(!bRet)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 电流模块[%d]-通道[%d] 谐波含量超约定值"),
											   nIndex, nChanIndex);
					return 3;
				}

				fChannelMax = GetChannelMax(oChannel, pTmt->m_oHarmParas.m_fBaseFre,
											nGradientDirection, nHarmIndex, nGradientAmp*fCTRate);

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

void CSttDeviceBase::GetUtcInfo(Drv_SysUtc *pSysUtc)
{
	char *pUtcH = m_pDrvUtcBase + 0x04;
	char *pUtcL = m_pDrvUtcBase + 0x0c;

	memcpy(&pSysUtc->tmFlag,m_pDrvUtcBase,4);
	memcpy(&pSysUtc->tm_h,pUtcH,4);
	memcpy(&pSysUtc->tm_l,pUtcL,4);
}

void CSttDeviceBase::GetModuleInfo(Drv_SysInfo *pSysInfo)
{
	char *pModule_cs = m_pDrvModuleBase + 0x1070;
	char *pModule_addr = m_pDrvModuleBase + 0x106c;
	char *pModule_data = m_pDrvModuleBase + 0x1038;
	unsigned int nPos = 0;

	for(int j = 0; j < g_theDeviceSystemParameter->m_nModuleCount;j++)
	{
		PST_MODULE_ATTR pModuleAttr = &g_theDeviceSystemParameter->m_oModules[j].m_oModuleAttr;
		int nModulePos = pModuleAttr->m_nModuleIndex - 1;

		if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_VOLT
				|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_CURRENT
				|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT
				|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_DIGITAL_0G8M
				|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_DIGITAL_2G6M
				|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_DIGITAL_4G4M)
		{
			//模拟量电源+光功率
			nPos = 0x01 << nModulePos;
			memcpy(pModule_cs,&nPos,4);
			for (int i = 0; i < 11; i++)
			{
				*pModule_addr = i;
				memcpy(&pSysInfo->stBack[nModulePos].dat[i],pModule_data,4);
			}
		}
	}
}

BOOL CSttDeviceBase::OnTimer(BOOL bExec)
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

	if(m_oPowerDAMngr.nUse)
	{
		if(m_oPowerDAMngr.nTickCnt == m_oPowerDAMngr.nTickTotal)
		{
			g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
			WriteDApara(&m_oDAPara);//解决电流模块异响
			g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
			m_oPowerDAMngr.nUse = 0;
		}

		m_oPowerDAMngr.nTickCnt++;
	}

	stt_init_stt_device_status();
	g_theSttDeviceStatus->m_nUdc = g_fAuxVolt > 0.001 ? 1 : 0;
	g_theSttDeviceStatus->m_bPowerAC = 1;
#ifdef _PSX_QT_LINUX_
	memset(&m_oSysUtc, 0, sizeof(Drv_SysUtc));
	GetUtcInfo(&m_oSysUtc);

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
			memset(&m_oSysInfo, 0, sizeof(Drv_SysInfo));
			GetModuleInfo(&m_oSysInfo);

			long nModulePos;
			for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_D; i++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];

				if(pModule == NULL)
				{
					continue;
				}

				nModulePos = pModule->m_oModuleAttr.m_nModuleIndex;
				AnalysisLightPower(m_oSysInfo.stBack[nModulePos - 1], nModulePos);
			}
			return TRUE;
		}
	}

	memset(&m_oSysInfo, 0, sizeof(Drv_SysInfo));
	GetModuleInfo(&m_oSysInfo);

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
	}

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_D; i++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];

		if(pModule == NULL)
		{
			continue;
		}

		nModulePos = pModule->m_oModuleAttr.m_nModuleIndex;
		AnalysisLightPower(m_oSysInfo.stBack[nModulePos - 1], nModulePos);
	}
#endif

	if(g_theSystemConfig->m_nHasAnalog == 0)
	{
		g_theSttDeviceStatus->m_nOverHeat = 0;//模块过热
		g_theSttDeviceStatus->m_nIBreak = 0;//电流开路
		g_theSttDeviceStatus->m_nUShort = 0;//电压短路
	}

	QDir oUsbDir("/mnt/Stt/Usb/1");
	if(oUsbDir.exists())
	{
		g_theSttDeviceStatus->m_bUSB = 1;
	}
	else
	{
		g_theSttDeviceStatus->m_bUSB = 0;
	}

	return TRUE;
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
	else if(nModuleType == STT_MODULE_TYPE_CURRENT)
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
	else if(nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
	{
		for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_UI; i++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[i];

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

	int nChMeasPos[6];
	for(int j = 0; j < 6; j++)
	{
		nChMeasPos[j] = 0;
	}

	if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		for(int j = 0; j < 6; j++)
		{
			oModuleStatus.m_oChannel[j].m_fVoltMax = fmaxarry[j];
			oModuleStatus.m_oChannel[j].m_fVoltMin = fminarry[j];
		}
	}
	else
	{
		for(int j = 0; j < pSTT_MODULE->m_oModuleAttr.m_nChannelNum; j++)
		{
			nChMeasPos[j] = pSTT_MODULE->m_nChMeasPos[j];
		}

		for(int j = 0; j < 6; j++)
		{
			oModuleStatus.m_oChannel[j].m_fVoltMax = fmaxarry[nChMeasPos[j]];
			oModuleStatus.m_oChannel[j].m_fVoltMin = fminarry[nChMeasPos[j]];
		}
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

	if(nModuleType == STT_MODULE_TYPE_CURRENT || nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
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
					if(nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
					{
						nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
					}
					m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
				}
				else
				{
					nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
					if(nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
					{
						nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
					}
					m_oDAPara.nvolt[nModuleIndex] = 0;
				}

				if(g_oDrvMutex.trylock(__FILE__,__FUNCTION__,__LINE__))
				{
					WriteDApara(&m_oDAPara);
					g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
				}

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

	for(int j = 0; j < 6; j++)
	{
		//通道异常或者模块通讯丢失,都会报过载
		//以此标记来停止实验不合适.如果是模块通讯丢失并且测试人员已知晓,可以继续实验.
		oModuleStatus.m_oChannel[j].m_bIsOverLoad = fOverLoad[nChMeasPos[j]]; //过载
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
	else
	{
		float fOutput;
		for(int j = 0; j < 6; j++)
		{
			//电流模块需要额外判断是否开路
			float fChannelVoltMax = fabs(oModuleStatus.m_oChannel[j].m_fVoltMax);
			float fChannelVoltMin = fabs(oModuleStatus.m_oChannel[j].m_fVoltMin);
			float fChannelVolt = (fChannelVoltMax + fChannelVoltMin)/2.0;
			float fPowerVolt = (fPowerVoltMax + fPowerVoltMin)/2.0;

			fOutput = pSTT_MODULE->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_fTotalCurAmp;

			if(fOutput > 0.099)
			{
				if((fChannelVolt < 1.0) || (fChannelVolt < fPowerVolt))
				{
					//电流回路
				}
				else
				{
					//电流开路
					g_theSttDeviceStatus->m_nIBreak = 1;
				}
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
		m_oGradientParas.m_uiVOL[2][chan].Ramp[oGradientParas.m_nType].bSecondChan = FALSE;
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
		m_oGradientParas.m_uiCUR[2][chan].Ramp[oGradientParas.m_nType].bSecondChan = FALSE;
	}

	float fStart2 = oGradientParas.m_fStart2;
	float fEnd2 = oGradientParas.m_fStop2;
	float fStep2 = fabs(oGradientParas.m_fStep2);
	m_oGradientParas.m_nType2 = oGradientParas.m_nType2;
	m_oGradientParas.m_fStep2 = oGradientParas.m_fStep2;
	m_oGradientParas.m_fStart2 = oGradientParas.m_fStart2;
	m_oGradientParas.m_fStop2 = oGradientParas.m_fStop2;

	switch(oGradientParas.m_nType2)
	{
		case GRADIENT_AMP:
			if(fStart2 < fEnd2)
			{
				m_oGradientParas.m_nStepDirection2 = 1;
			}
			else
			{
				m_oGradientParas.m_nStepDirection2 = -1;
			}

			break;

		case GRADIENT_ANG:
			if(fStart2 < fEnd2)
			{
				m_oGradientParas.m_nStepDirection2 = 1;
			}
			else
			{
				m_oGradientParas.m_nStepDirection2 = -1;
			}

			break;

		case GRADIENT_FRE:
			if(fabs(fStart2) < fabs(fEnd2))
			{
				m_oGradientParas.m_nStepDirection2 = 1;
			}
			else
			{
				m_oGradientParas.m_nStepDirection2 = -1;
			}

			break;
	}

	for(int i = 0; i < ChannelVolts2.size(); i++)
	{
		int chan = ChannelVolts2.at(i);

		switch(oGradientParas.m_nType2)
		{
			case GRADIENT_AMP:
				m_oGradientParas.m_uiVOL[2][chan].Harm[nHarmIndex].fAmp = fStart2;
				m_oGradientParas.m_uiVOL[2][chan].Ramp[GRADIENT_AMP].fEnd = fEnd2;
				break;

			case GRADIENT_ANG:
				m_oGradientParas.m_uiVOL[2][chan].Harm[nHarmIndex].fAngle = fStart2;
				m_oGradientParas.m_uiVOL[2][chan].Ramp[GRADIENT_ANG].fEnd = fEnd2;
				break;

			case GRADIENT_FRE:
				float fFreqStart = fabs(fStart2);

				if(fFreqStart < EPSINON)
				{
					fFreqStart = 0.001;
				}

				m_oGradientParas.m_uiVOL[2][chan].Harm[nHarmIndex].fFreq = fFreqStart;
				m_oGradientParas.m_uiVOL[2][chan].Ramp[GRADIENT_FRE].fEnd = fabs(fEnd2);
				break;
		}

		m_oGradientParas.m_uiVOL[2][chan].Ramp[oGradientParas.m_nType2].nIndex = nHarmIndex;
		m_oGradientParas.m_uiVOL[2][chan].Ramp[oGradientParas.m_nType2].fStep = fStep2;
		m_oGradientParas.m_uiVOL[2][chan].Ramp[oGradientParas.m_nType2].bSecondChan = TRUE;
	}

	for(int i = 0; i < ChannelCurrs2.size(); i++)
	{
		int chan = ChannelCurrs2.at(i);

		switch(oGradientParas.m_nType2)
		{
			case GRADIENT_AMP:
				m_oGradientParas.m_uiCUR[2][chan].Harm[nHarmIndex].fAmp = fStart2;
				m_oGradientParas.m_uiCUR[2][chan].Ramp[GRADIENT_AMP].fEnd = fEnd2;
				break;

			case GRADIENT_ANG:
			{
				m_oGradientParas.m_uiCUR[2][chan].Harm[nHarmIndex].fAngle = fStart2;
				m_oGradientParas.m_uiCUR[2][chan].Ramp[GRADIENT_ANG].fEnd = fEnd2;
			}
			break;

			case GRADIENT_FRE:
				float fFreqStart = fabs(fStart2);

				if(fFreqStart < EPSINON)
				{
					fFreqStart = 0.001;
				}

				m_oGradientParas.m_uiCUR[2][chan].Harm[nHarmIndex].fFreq = fFreqStart;
				m_oGradientParas.m_uiCUR[2][chan].Ramp[GRADIENT_FRE].fEnd = fabs(fEnd2);
				break;
		}

		m_oGradientParas.m_uiCUR[2][chan].Ramp[oGradientParas.m_nType2].nIndex = nHarmIndex;
		m_oGradientParas.m_uiCUR[2][chan].Ramp[oGradientParas.m_nType2].fStep = fStep2;
		m_oGradientParas.m_uiCUR[2][chan].Ramp[oGradientParas.m_nType2].bSecondChan = TRUE;
	}
}

void CSttDeviceBase::SetChannelSelect(tmt_GradientParas &oGradientParas)
{
	TranGradientChannels(oGradientParas, ChannelVolts, ChannelCurrs,ChannelVolts2, ChannelCurrs2);
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

void CSttDeviceBase::TranGradientChannels(tmt_GradientParas &oGradientParas, vector<int> &ChannelVolts,
										  vector<int> &ChannelCurrs,vector<int> &ChannelVolts2, vector<int> &ChannelCurrs2)
{
	ChannelVolts.clear();
	ChannelCurrs.clear();
	ChannelVolts2.clear();
	ChannelCurrs2.clear();
	//Ua1 Ub1 Uc1 Ua2 Ub2 Uc2
	//Ia1 Ib1 Ic1 Ia2 Ib2 Ic2
	int nRampChannel = oGradientParas.m_nChannel;
	int nRampChannel2 = oGradientParas.m_nChannel2;

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

				case Null:
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

			switch(nRampChannel2)
			{
				case U1a:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A);
					break;

				case U1b:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case U1c:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case Null:
					break;

				case U1ab:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case U1bc:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case U1ca:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case U1abc:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case U2a:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A2);
					break;

				case U2b:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case U2c:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case U2abc:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I1a:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A);
					break;

				case I1b:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case I1c:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case I1ab:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B);
					break;

				case I1bc:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case I1ca:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case I1abc:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C);
					break;

				case I2a:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A2);
					break;

				case I2b:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case I2c:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I2abc:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case U_All:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I_All:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case Udc:
					break;

				case Uz:
					break;

				case U2ab:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case U2bc:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case U2ca:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I2ab:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B2);
					break;

				case I2bc:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I2ca:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case I1abcAdd:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C);

					if(oGradientParas.m_nType2 == GRADIENT_AMP)
					{
						oGradientParas.m_fStart2 = oGradientParas.m_fStart2 / 3;
						oGradientParas.m_fStop2 = oGradientParas.m_fStop2 / 3;
						oGradientParas.m_fStep2 = oGradientParas.m_fStep2 / 3;
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
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C2);

					if(oGradientParas.m_nType2 == GRADIENT_AMP)
					{
						oGradientParas.m_fStart2 = oGradientParas.m_fStart2 / 3;
						oGradientParas.m_fStop2 = oGradientParas.m_fStop2 / 3;
						oGradientParas.m_fStep2 = oGradientParas.m_fStep2 / 3;
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
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C);

					if(oGradientParas.m_nType2 == GRADIENT_AMP)
					{
						oGradientParas.m_fStart2 = oGradientParas.m_fStart2 / 3;
					}

					break;

				case U2abcAdd:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C2);

					if(oGradientParas.m_nType2 == GRADIENT_AMP)
					{
						oGradientParas.m_fStart2 = oGradientParas.m_fStart2 / 3;
					}

					break;

				case FreAll:
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelVolts2.push_back(TMT_GRADIENT_CHANNEL_C2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C2);
					break;

				case Ia1Ia2Add:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A2);

					if(oGradientParas.m_nType2 == GRADIENT_AMP
							|| oGradientParas.m_nType2 == GRADIENT_ANG)
					{
						oGradientParas.m_fStart2 = oGradientParas.m_fStart2 / 2;
					}

					break;

				case Ib1Ib2Add:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B2);

					if(oGradientParas.m_nType2 == GRADIENT_AMP
							|| oGradientParas.m_nType2 == GRADIENT_ANG)
					{
						oGradientParas.m_fStart2 = oGradientParas.m_fStart2 / 2;
					}

					break;

				case Ic1Ic2Add:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C2);

					if(oGradientParas.m_nType2 == GRADIENT_AMP
							|| oGradientParas.m_nType2 == GRADIENT_ANG)
					{
						oGradientParas.m_fStart2 = oGradientParas.m_fStart2 / 2;
					}

					break;

				case Ia1Ia2Add_Ib1Ib2Add_Ic1Ic2Add:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C2);

					if(oGradientParas.m_nType2 == GRADIENT_AMP
							|| oGradientParas.m_nType2 == GRADIENT_ANG)
					{
						oGradientParas.m_fStart2 = oGradientParas.m_fStart2 / 2;
					}

					break;

				case Ia1Ia2_Ib1Ib2_Ic1Ic2_Add:
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_A2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_B2);
					ChannelCurrs2.push_back(TMT_GRADIENT_CHANNEL_C2);

					if(oGradientParas.m_nType2 == GRADIENT_AMP
							|| oGradientParas.m_nType2 == GRADIENT_ANG)
					{
						oGradientParas.m_fStart2 = oGradientParas.m_fStart2 / 6;
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

void CSttDeviceBase::SetIecDetect(BOOL bEnable, long nIecType)
{
	if(bEnable)
	{
		CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

		if(pSttTestBase != NULL && pSttTestBase->GetTestStarting())
		{
			//实验中，以Iec61850Cfg的订阅为准，不能探测
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[warning] 实验进行中，以IEC配置为准，禁用报文探测功能"));
			return;
		}

		if(m_nIsIecMode == 1 || m_nIsIecMode == 2)
		{
			if(bIecDetectRun)
			{
				bIecDetectRun = FALSE;
				Sleep(120);
			}
			if(g_oSttRcdSendSocket.m_bRunning)
			{
				pthread_mutex_lock(&g_oSttRcdSendMutex);
			}
			g_oSttRcdSendSocket.m_bRunning = FALSE;
			if(bIecRecordRun)
			{
				bIecRecordRun = FALSE;
				Sleep(120);
			}

			g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
			ioctl(m_nCommfd, 0x131, DMA_TYPE_NULL);
			ioctl(m_nCommfd, 0x126, 0);//关闭FPGA DMA缓存
			g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

			Sleep(20);
		}

		m_nIsIecMode = 1;
		g_pIecDetectBuf->Reset();
		nIecReadPos = 0;
		nIec64ReadSizeTotal = 0;

		memset(&oIECDetectResult, 0, sizeof(IECDetectResult));
		m_nIECDetectIdx = 0;
		nIecDetType = nIecType;
		bIecDetectRun = TRUE;
		pthread_t nthreadid;
		int nRet = pthread_create(&nthreadid, NULL, IecHeaderCapThread, (LPVOID)this);
#ifdef _PSX_QT_LINUX_
		if(nRet == 0)
		{
			qDebug() << ">>>>>>Create IecHeaderCapThread";
		}
		nRet = pthread_create(&nthreadid, NULL, ProIecDetectThread, (LPVOID)this);
		if(nRet == 0)
		{
			qDebug() << ">>>>>>Create ProIecDetectThread";
		}
#endif

		memset(&m_oIecRecvCfg, 0, sizeof(IecRecvCfg));

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nCommfd, 0x126, 1);//开启FPGA DMA缓存
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

		Sleep(10);
		m_oIecRecvCfg.nType = nIecType;//0-All,1-SV,2-GOOSE,3-FT3
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nCommfd, 0x30C, 1);
		write(m_nCommfd, &m_oIecRecvCfg, sizeof(IecRecvCfg));
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

		Sleep(10);
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nCommfd, 0x131, DMA_TYPE_PROBE);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}
	else
	{
		bIecDetectRun = FALSE;
		Sleep(120);

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nCommfd, 0x131, DMA_TYPE_NULL);
		ioctl(m_nCommfd, 0x126, 0);//关闭FPGA DMA缓存
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

		m_nIsIecMode = 0;
	}
}

void CSttDeviceBase::SetIecFilter(IECRecordItems *pRecordItems)
{
	if(pRecordItems->bEnable)
	{
		CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

		if(pSttTestBase != NULL && pSttTestBase->GetTestStarting())
		{
			//实验中，以Iec61850Cfg的订阅为准，不下载新的CRC
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[warning] 实验进行中，以IEC配置为准，禁用报文探测功能"));
			return;
		}

		if(m_nIsIecMode == 1 || m_nIsIecMode == 2)
		{
			if(bIecDetectRun)
			{
				bIecDetectRun = FALSE;
				Sleep(120);
			}

			if(g_oSttRcdSendSocket.m_bRunning)
			{
				pthread_mutex_lock(&g_oSttRcdSendMutex);
			}
			g_oSttRcdSendSocket.m_bRunning = FALSE;
			if(bIecRecordRun)
			{
				bIecRecordRun = FALSE;
				Sleep(120);
			}

			g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
			ioctl(m_nCommfd, 0x131, DMA_TYPE_NULL);
			ioctl(m_nCommfd, 0x126, 0);//关闭FPGA DMA缓存
			g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

			Sleep(20);
		}

		m_nIsIecMode = 2;
		CSttDeviceBase::g_pSttDeviceBase->m_nUseIecCfgCRC = 0;

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

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nCommfd, 0x30C, 2);
		write(m_nCommfd, (char *)&m_oIecRecvCfg, sizeof(IecRecvCfg));
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

		if(pRecordItems->nCount6044 > 0)
		{
			Ft3SubDatas oSubDatas;
			memset(&oSubDatas, 0, sizeof(Ft3SubDatas));
			oSubDatas.nModuleCnt = m_pIECConfigFt3->mdCnt;

			for(int i = 0; i < m_pIECConfigFt3->mdCnt; i++)
			{
				if(m_pIECConfigFt3->item[i].nSTRecvBeginIdx > -1)
				{
					oSubDatas.ft3SubData[i].nModule = m_pIECConfigFt3->item[i].module;
				}

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

				if((nBoard >= 0) && (nBoard < 4))
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

			g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
			ioctl(m_nCommfd, 0x310, 0);
			write(m_nCommfd, (char *)&oSubDatas, sizeof(Ft3SubDatas));
			g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
		}

		g_oSttRcdSendSocket.m_bRunning = TRUE;
		pthread_mutex_unlock(&g_oSttRcdSendMutex);
		bIecRecordRun = TRUE;
		pthread_t nthreadid;
		int nRet = pthread_create(&nthreadid, NULL, IecPkgCapThread, (LPVOID)this);
#ifdef _PSX_QT_LINUX_
		if(nRet == 0)
		{
			qDebug() << ">>>>>>Create IecPkgCapThread";
		}
#endif

		g_nRTDATAMode = 1;//简化实时数据报文
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		if(pRecordItems->bHasSmv)
		{
			ioctl(m_nCommfd, 0x126, 1);//开启FPGA DMA缓存
		}
		else
		{
			ioctl(m_nCommfd, 0x126, 0);//关闭FPGA DMA缓存
		}
		ioctl(m_nCommfd, 0x131, DMA_TYPE_RECORD);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}
	else
	{
		CSttDeviceBase::g_pSttDeviceBase->m_nUseIecCfgCRC = 1;

		if(g_oSttRcdSendSocket.m_bRunning)
		{
			pthread_mutex_lock(&g_oSttRcdSendMutex);
		}
		g_oSttRcdSendSocket.m_bRunning = FALSE;
		if(bIecRecordRun)
		{
			bIecRecordRun = FALSE;
			Sleep(120);
		}

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nCommfd, 0x131, DMA_TYPE_NULL);
		ioctl(m_nCommfd, 0x126, 0);//关闭FPGA DMA缓存
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
		m_nIsIecMode = 0;
		Sleep(10);
		g_oSttRcdSendSocket.InitRecordBuf();

		g_nRTDATAMode = 0;
	}
}

void *ProIecDetectThread(LPVOID pParam)
{
	pthread_setname_np(pthread_self(),"IecDetect");

	unsigned char pszPkgBuf[28];
	BOOL bFind = FALSE;
	long nType;
	long nCrc;//控制块CRC
	long nPort;
	long nBaud;
	long nNewBlock;
	int i;
	unsigned int nFT3Recv = 0;

	while(1)
	{
		if(!bIecDetectRun)
		{
			break;
		}

		if(g_pIecDetectBuf->GetDataLen() >= 28)
		{
			g_pIecDetectBuf->ReadBuf((char *)pszPkgBuf, nIecReadPos, nIec64ReadSizeTotal, 4);
			if(pszPkgBuf[0] == 0x05 && pszPkgBuf[1] == 0x64 && pszPkgBuf[2] == 0x05 && pszPkgBuf[3] == 0x64)
			{
				g_pIecDetectBuf->ReadBuf((char *)pszPkgBuf, nIecReadPos, nIec64ReadSizeTotal, 24);
				if(pszPkgBuf[12] == 0xAA)
				{
					nType = pszPkgBuf[13] >> 4;

					if(nIecDetType == 0 || nIecDetType == 3)
					{
						if(nType == 3)
						{
							if(nFT3Recv < 5)
							{
								nFT3Recv++;
								if(nFT3Recv < 5)
								{
									continue;//过滤掉开始探测时的不稳定报文
								}
							}

							//FPGA不支持探测报文长度是奇数的情况
							nPort = pszPkgBuf[13] & 0xF;
							nBaud = pszPkgBuf[15];

							bFind = FALSE;
							for(i = 0; i < oIECDetectResult.nCount; i++)
							{
								if(oIECDetectResult.item[i].bFT3 == TRUE)
								{
									if(nPort == oIECDetectResult.item[i].nPort_FT3
											&& nBaud == oIECDetectResult.item[i].nBaud_FT3)
									{
										bFind = TRUE;
										break;
									}
								}
							}

							if(!bFind)
							{
								nNewBlock = oIECDetectResult.nCount;
								oIECDetectResult.item[nNewBlock].bFT3 = TRUE;
								oIECDetectResult.item[nNewBlock].nPort_FT3 = nPort;
								oIECDetectResult.item[nNewBlock].nBaud_FT3 = nBaud;
								memcpy(oIECDetectResult.item[nNewBlock].sData, pszPkgBuf + 12, 12);
								oIECDetectResult.nCount++;

								if(oIECDetectResult.nCount == 200)
								{
									bIecDetectRun = FALSE;
								}
							}
						}
					}

					if(nIecDetType == 0 || nIecDetType == 1)
					{
						if(nType == 1)
						{
							nCrc = pszPkgBuf[18] << 8 | pszPkgBuf[19];
							bFind = FALSE;
							//sv
							for(i = 0; i < oIECDetectResult.nCount; i++)
							{
								if(oIECDetectResult.item[i].bFT3 == FALSE && nCrc == oIECDetectResult.item[i].nCrc)
								{
									bFind = TRUE;
									break;
								}
							}

							if(!bFind)
							{
								nNewBlock = oIECDetectResult.nCount;
								oIECDetectResult.item[nNewBlock].bFT3 = FALSE;
								oIECDetectResult.item[nNewBlock].nCrc = nCrc;
								memcpy(oIECDetectResult.item[nNewBlock].sData, pszPkgBuf + 12, 12);
								oIECDetectResult.nCount++;

								if(oIECDetectResult.nCount == 200)
								{
									bIecDetectRun = FALSE;
								}
							}
						}
					}

					if(nIecDetType == 0 || nIecDetType == 2)
					{
						if(nType == 2)
						{
							nCrc = pszPkgBuf[18] << 8 | pszPkgBuf[19];
							bFind = FALSE;
							//goose
							for(i = 0; i < oIECDetectResult.nCount; i++)
							{
								if(oIECDetectResult.item[i].bFT3 == FALSE && nCrc == oIECDetectResult.item[i].nCrc)
								{
									bFind = TRUE;
									break;
								}
							}

							if(!bFind)
							{
								nNewBlock = oIECDetectResult.nCount;
								oIECDetectResult.item[nNewBlock].bFT3 = FALSE;
								oIECDetectResult.item[nNewBlock].nCrc = nCrc;
								memcpy(oIECDetectResult.item[nNewBlock].sData, pszPkgBuf + 12, 12);
								oIECDetectResult.nCount++;

								if(oIECDetectResult.nCount == 200)
								{
									bIecDetectRun = FALSE;
								}
							}
						}
					}
				}
			}
		}

		Sleep(10);
	}

	pthread_exit(0);
}

void *IecHeaderCapThread(LPVOID pParam)
{
	pthread_setname_np(pthread_self(),"IecHeaderCap");
	CSttDeviceBase *pSttDeviceBase = (CSttDeviceBase *)pParam;
	long nCount = 0;

	while(1)
	{
		if(pSttDeviceBase->m_pMMapBuf == NULL)
		{
			Sleep(100);
			continue;
		}

		if(!bIecDetectRun)
		{
			break;
		}

		if(pSttDeviceBase->m_pMMapBuf->nRecordSize == 0)
		{
			Sleep(100);
			continue;
		}

		char *pDrvResults = stt_test_get_drvresult_buff();
		int ret = 0;

		if(pSttDeviceBase->m_pMMapBuf->nRecordSize > 300000
				|| nCount > 10)
		{
			nCount = 0;
			g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
			ret = read(pSttDeviceBase->m_nCommfd, pDrvResults, 0x260);
			g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

			if(ret > 0)
			{
				g_pIecDetectBuf->WriteBuf(pDrvResults, ret);
			}
		}
		else
		{
			nCount++;
		}

		Sleep(100);
	}
	pthread_exit(0);
}

void *IecPkgCapThread(LPVOID pParam)
{
	pthread_setname_np(pthread_self(),"IecPkgCap");
	CSttDeviceBase *pSttDeviceBase = (CSttDeviceBase *)pParam;
	long nCount = 0;

	while(1)
	{
		if(pSttDeviceBase->m_pMMapBuf == NULL)
		{
			Sleep(100);
			continue;
		}

		if(!bIecRecordRun)
		{
			break;
		}

		if(pSttDeviceBase->m_pMMapBuf->nRecordSize == 0)
		{
			nCount = 0;
			Sleep(100);
			continue;
		}

		char *pDrvResults = stt_test_get_drvresult_buff();
		int ret = 0;

		if(pSttDeviceBase->m_pMMapBuf->nRecordSize > 2048000
				|| nCount > 10)
		{
			nCount = 0;
			g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
			ret = read(pSttDeviceBase->m_nCommfd, pDrvResults, 0x261);
			g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

			if(ret > 0)
			{
				g_oSttRcdSendSocket.WriteRecordBuf(pDrvResults, ret);
			}
		}
		else
		{
			nCount++;
		}

		Sleep(100);
	}
	pthread_exit(0);
}

void *ProTestResultThread(LPVOID pParam)
{
	pthread_setname_np(pthread_self(),"TestResult");
	CSttDeviceBase *pSttDeviceBase = (CSttDeviceBase *)pParam;

	while(1)
	{
		if(pSttDeviceBase->m_pMMapBuf == NULL)
		{
			Sleep(10);
			continue;
		}

		if(!pSttDeviceBase->m_bTestStarting)
		{
			pthread_mutex_lock(&g_oTestResultMutex);
			pthread_mutex_unlock(&g_oTestResultMutex);
		}

		if(pSttDeviceBase->m_pMMapBuf->nResultSize > 0)
		{
			pSttDeviceBase->ProTestResults();
		}

		Sleep(50);
	}
	pthread_exit(0);
}

void CSttDeviceBase::ProTestResults()
{
	BOOL bIsTestFinish=CSttServerTestCtrlCntr::EventProcess();
	if(bIsTestFinish)
	{
		CSttServerTestCtrlCntr::ProcessTestFinish();
	}
}

BOOL CSttDeviceBase::GetIecPktList()
{
	BOOL bRet = FALSE;
	if(bIecDetectRun)
	{
		bRet = oIECDetectResult.nCount > m_nIECDetectIdx;
	}

	return bRet;
}

BOOL CSttDeviceBase::stt_xml_serialize_iec_rtdatas(CSttXmlSerializeBase *pXmlSerialize)
{
	CString str;
	CString strCRC;
	CString strAPPID;
	CString strType;
	CString strPort;
	CString strBaudRate;
	CString strSampleRate;
	CString strOnePkgLen;

	long nResultCnt = oIECDetectResult.nCount;

	for(int i = m_nIECDetectIdx; i < nResultCnt && i < 200; i++)
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
		}

		str.clear();

		for(int j = 0; j < 12; j++)
		{
			str += CString("%1").arg(oIECDetectResult.item[i].sData[j], 2, 16, QChar('0'));
		}

		pXml->xml_serialize("", XPARA_ID_PkgDetect, "", "string", str);
	}

	m_nIECDetectIdx = nResultCnt;
	return TRUE;
}

/*********IEC**********/

/*********DMA**********/
void CSttDeviceBase::SetDMAType(long nDMAType)
{
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nCommfd, 0x402, nDMAType);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
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

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nCommfd, 0x124, nCurrentCtrlMode);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttDeviceBase::InitAsyncManu()
{
	if(g_pAsyncManualTest == NULL)
	{
		g_pAsyncManualTest = new tmt_AsyncManualTest;
	}

	g_pAsyncManualTest->m_oResult.init();
	g_pAsyncManualTest->m_oParas.m_bBinStop = FALSE;
	g_pAsyncManualTest->m_oParas.m_bAging = FALSE;
	g_pAsyncManualTest->m_oParas.m_bAuto = FALSE;
	g_pAsyncManualTest->m_oParas.m_bLockChanged = FALSE;
	g_pAsyncManualTest->m_oParas.m_fOutPutTime = 0.000001f;
	g_pAsyncManualTest->m_oParas.m_fVolAux = 0;
	g_pAsyncManualTest->m_oParas.m_fCurAux = 0;
	g_pAsyncManualTest->m_oParas.m_nBinLogic = 0;
	g_pAsyncManualTest->m_oParas.m_nGradientModuleTypeSel = 0;

	for(int nIndex = 0;nIndex < ASYNC_MODULE_TYPE_COUNT;nIndex++)
	{
		g_pAsyncManualTest->m_oParas.m_manuGradient[nIndex].init();
	}

	for(int j = 0; j < MAX_BINARYIN_COUNT; j++)
	{
		g_pAsyncManualTest->m_oParas.m_binIn[j].nSelect = 0;
		g_pAsyncManualTest->m_oParas.m_binIn[j].nTrigMode = 0;
	}

	for(int j = 0; j < MAX_BINARYOUT_COUNT; j++)
	{
		g_pAsyncManualTest->m_oParas.m_binOut[j].nState = 0;
		g_pAsyncManualTest->m_oParas.m_binOut[j].nMode = 0;
		g_pAsyncManualTest->m_oParas.m_binOut[j].fTimeTrig = 0;
		g_pAsyncManualTest->m_oParas.m_binOut[j].fHoldTime = 0;
	}

	for(int j = 0; j < g_nBinExCount && j < MAX_ExBINARY_COUNT; j++)
	{
		g_pAsyncManualTest->m_oParas.m_binInEx[j].nSelect = 0;//默认扩增开入不选中
		g_pAsyncManualTest->m_oParas.m_binInEx[j].nTrigMode = 0;
	}

	for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
	{
		g_pAsyncManualTest->m_oParas.m_binOutEx[j].nState = 0;//默认扩增开出全断开
		g_pAsyncManualTest->m_oParas.m_binOutEx[j].nMode = 0;
		g_pAsyncManualTest->m_oParas.m_binOutEx[j].fTimeTrig = 0;
		g_pAsyncManualTest->m_oParas.m_binOutEx[j].fHoldTime = 0;
	}

	for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
	{
		g_pAsyncManualTest->m_oParas.m_oGoosePub[nIndex].init();
	}

	for(int nIndex = 0; nIndex < MAX_MODULES_FT3PUB_COUNT; nIndex++)
	{
		g_pAsyncManualTest->m_oParas.m_oFt3Pub[nIndex].init();
	}

	g_pAsyncManualTest->m_oParas.m_fTimeSet =0;
	g_pAsyncManualTest->m_oParas.m_fUSet=0;
	g_pAsyncManualTest->m_oParas.m_fISet=0;
	g_pAsyncManualTest->m_oParas.m_fAngleSet=0;
	g_pAsyncManualTest->m_oParas.m_fHzSet=0;
	g_pAsyncManualTest->m_oParas.m_fRetCoefSet=0;

	g_pAsyncManualTest->m_oParas.m_fTimeValue_AbsErr = 0.001f;
	g_pAsyncManualTest->m_oParas.m_fTimeValue_RelErr = 0.1f;
	g_pAsyncManualTest->m_oParas.m_nTimeValue_ErrorLogic = 0;
	g_pAsyncManualTest->m_oParas.m_fUActVal_AbsErr = 0.001f;
	g_pAsyncManualTest->m_oParas.m_fUActVal_RelErr = 0.1f;
	g_pAsyncManualTest->m_oParas.m_nUActVal_ErrorLogic = 0;
	g_pAsyncManualTest->m_oParas.m_fIActVal_AbsErr = 0.001f;
	g_pAsyncManualTest->m_oParas.m_fIActVal_RelErr = 0.1f;
	g_pAsyncManualTest->m_oParas.m_nIActVal_ErrorLogic = 0;
	g_pAsyncManualTest->m_oParas.m_fAngleActVal_AbsErr = 0.001f;
	g_pAsyncManualTest->m_oParas.m_fAngleActVal_RelErr = 0.1f;
	g_pAsyncManualTest->m_oParas.m_nAngleActVal_ErrorLogic = 0;
	g_pAsyncManualTest->m_oParas.m_fHzActVal_AbsErr = 0.001f;
	g_pAsyncManualTest->m_oParas.m_fHzActVal_RelErr = 0.1f;
	g_pAsyncManualTest->m_oParas.m_nHzActVal_ErrorLogic = 0;
	g_pAsyncManualTest->m_oParas.m_fRetCoef_AbsErr = 0.001f;
	g_pAsyncManualTest->m_oParas.m_fRetCoef_RelErr = 0.1f;
	g_pAsyncManualTest->m_oParas.m_nRetCoef_ErrorLogic = 0;

	long nAnalogModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U
			+ g_theDeviceSystemParameter->m_nModuleCount_I
			+ g_theDeviceSystemParameter->m_nModuleCount_UI;

	for(int i = 0;i < MAX_MODULE_COUNT && i < nAnalogModuleCnt;i++)
	{
		tmt_AsyncChannel *pVolChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oAnalogModules[i].m_pVolChannel;
		tmt_AsyncChannel *pCurrChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oAnalogModules[i].m_pCurrChannel;
		if(pVolChannel == NULL)
		{
			pVolChannel = new tmt_AsyncChannel[CHANNEL_MAX];
		}
		if(pCurrChannel == NULL)
		{
			pCurrChannel = new tmt_AsyncChannel[CHANNEL_MAX];
		}
		for(int j = 0;j < CHANNEL_MAX;j++)
		{
			pVolChannel[j].init();
			pCurrChannel[j].init();
		}
	}

	long nWeekModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_WEEK;
	for(int i = 0;i < MAX_MODULE_COUNT && i < nWeekModuleCnt;i++)
	{
		tmt_AsyncChannel *pVolChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oWeekModules[i].m_pVolChannel;
		tmt_AsyncChannel *pCurrChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oWeekModules[i].m_pCurrChannel;
		if(pVolChannel == NULL)
		{
			pVolChannel = new tmt_AsyncChannel[48];
		}
		if(pCurrChannel == NULL)
		{
			pCurrChannel = new tmt_AsyncChannel[48];
		}
		for(int j = 0;j < 48;j++)
		{
			pVolChannel[j].init();
			pCurrChannel[j].init();
		}
	}

	long nDigitalModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_D;
	if(nDigitalModuleCnt > 0)
	{
		tmt_AsyncChannel *pVolChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oDigitalModules.m_pVolChannel;
		tmt_AsyncChannel *pCurrChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oDigitalModules.m_pCurrChannel;
		if(pVolChannel == NULL)
		{
			pVolChannel = new tmt_AsyncChannel[18];
		}
		if(pCurrChannel == NULL)
		{
			pCurrChannel = new tmt_AsyncChannel[18];
		}
		for(int j = 0;j < 18;j++)
		{
			pVolChannel[j].init();
			pCurrChannel[j].init();
		}
	}
}

void CSttDeviceBase::FreeAsyncManu()
{
	if(g_pAsyncManualTest != NULL)
	{
		long nAnalogModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U
				+ g_theDeviceSystemParameter->m_nModuleCount_I
				+ g_theDeviceSystemParameter->m_nModuleCount_UI;
		for(int i = 0;i < MAX_MODULE_COUNT && i < nAnalogModuleCnt;i++)
		{
			tmt_AsyncChannel *pVolChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oAnalogModules[i].m_pVolChannel;
			tmt_AsyncChannel *pCurrChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oAnalogModules[i].m_pCurrChannel;
			if(pVolChannel != NULL)
			{
				delete[] pVolChannel;
			}
			if(pCurrChannel != NULL)
			{
				delete[] pCurrChannel;
			}
		}

		long nWeekModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_WEEK;
		for(int i = 0;i < MAX_MODULE_COUNT && i < nWeekModuleCnt;i++)
		{
			tmt_AsyncChannel *pVolChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oWeekModules[i].m_pVolChannel;
			tmt_AsyncChannel *pCurrChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oWeekModules[i].m_pCurrChannel;
			if(pVolChannel != NULL)
			{
				delete[] pVolChannel;
			}
			if(pCurrChannel != NULL)
			{
				delete[] pCurrChannel;
			}
		}

		long nDigitalModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_D;
		if(nDigitalModuleCnt > 0)
		{
			tmt_AsyncChannel *pVolChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oDigitalModules.m_pVolChannel;
			tmt_AsyncChannel *pCurrChannel = g_pAsyncManualTest->m_oParas.m_oAsyncModuels.m_oDigitalModules.m_pCurrChannel;
			if(pVolChannel != NULL)
			{
				delete[] pVolChannel;
			}
			if(pCurrChannel != NULL)
			{
				delete[] pCurrChannel;
			}
		}

		delete g_pAsyncManualTest;
	}
}

void CSttDeviceBase::InitAsyncState()
{
	if(g_pAsyncStateTest == NULL)
	{
		g_pAsyncStateTest = new tmt_AsyncStateTest;
	}

	g_pAsyncStateTest->m_oStateAsyncResults.init(g_nStateCount);
	long nAnalogModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U
			+ g_theDeviceSystemParameter->m_nModuleCount_I
			+ g_theDeviceSystemParameter->m_nModuleCount_UI;
	long nWeekModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_WEEK;
	long nDigitalModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_D;

	for (int i = 0;i < g_nStateCount;i++)
	{
		tmt_AsyncStatePara	*paraState = &g_pAsyncStateTest->m_oStateAsyncParas.m_paraState[i];
		if(paraState == NULL)
		{
			continue;
		}

		paraState->m_bSelected = true;
		paraState->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		paraState->m_fTimeState = 5;
		paraState->m_fTimeAfterTrigger = 0;
		paraState->m_fOutputHoldTime = 0;
		paraState->m_nBinLogic = TMT_BINLOGIC_OR;
		paraState->m_nBinAndSelect = 0;
		paraState->m_nBinOrSelect = 0;
		paraState->m_nBinaryOutType = 0;
		paraState->m_fVolAux = 0;
		paraState->m_nRampTimeGrad = 0;

		//开关量
		for (int j=0;j<MAX_BINARYIN_COUNT;j++)
		{
			paraState->m_binIn[j].nSelect = 0;
			paraState->m_binIn[j].nTrigMode = 0;
		}

		for (int j=0;j<MAX_BINARYOUT_COUNT;j++)
		{
			paraState->m_binOut[j].init();
		}

		for(int j = 0; j < g_nBinExCount && j < MAX_ExBINARY_COUNT; j++)
		{
			paraState->m_binInEx[j].nSelect = 0;//默认扩增开入不选中
			paraState->m_binInEx[j].nTrigMode = 0;
		}

		for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
		{
			paraState->m_binOutEx[j].init();//默认扩增开出全断开
		}

		for(int i = 0;i < MAX_MODULE_COUNT && i < nAnalogModuleCnt;i++)
		{
			tmt_AsyncChannel *pVolChannel = paraState->m_oStateAsyncModule.m_oAnalogModules[i].m_pVolChannel;
			tmt_AsyncChannel *pCurrChannel = paraState->m_oStateAsyncModule.m_oAnalogModules[i].m_pCurrChannel;
			if(pVolChannel == NULL)
			{
				pVolChannel = new tmt_AsyncChannel[CHANNEL_MAX];
			}
			if(pCurrChannel == NULL)
			{
				pCurrChannel = new tmt_AsyncChannel[CHANNEL_MAX];
			}
			for(int j = 0;j < CHANNEL_MAX;j++)
			{
				pVolChannel[j].init();
				pCurrChannel[j].init();
			}
		}

		for(int i = 0;i < MAX_MODULE_COUNT && i < nWeekModuleCnt;i++)
		{
			tmt_AsyncChannel *pVolChannel = paraState->m_oStateAsyncModule.m_oWeekModules[i].m_pVolChannel;
			tmt_AsyncChannel *pCurrChannel = paraState->m_oStateAsyncModule.m_oWeekModules[i].m_pCurrChannel;
			if(pVolChannel == NULL)
			{
				pVolChannel = new tmt_AsyncChannel[48];
			}
			if(pCurrChannel == NULL)
			{
				pCurrChannel = new tmt_AsyncChannel[48];
			}
			for(int j = 0;j < 48;j++)
			{
				pVolChannel[j].init();
				pCurrChannel[j].init();
			}
		}

		if(nDigitalModuleCnt > 0)
		{
			tmt_AsyncChannel *pVolChannel = paraState->m_oStateAsyncModule.m_oDigitalModules.m_pVolChannel;
			tmt_AsyncChannel *pCurrChannel = paraState->m_oStateAsyncModule.m_oDigitalModules.m_pCurrChannel;
			if(pVolChannel == NULL)
			{
				pVolChannel = new tmt_AsyncChannel[18];
			}
			if(pCurrChannel == NULL)
			{
				pCurrChannel = new tmt_AsyncChannel[18];
			}
			for(int j = 0;j < 18;j++)
			{
				pVolChannel[j].init();
				pCurrChannel[j].init();
			}
		}
	}
}

void CSttDeviceBase::FreeAsyncState()
{
	if(g_pAsyncStateTest != NULL)
	{
		long nAnalogModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U
				+ g_theDeviceSystemParameter->m_nModuleCount_I
				+ g_theDeviceSystemParameter->m_nModuleCount_UI;
		long nWeekModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_WEEK;
		long nDigitalModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_D;

		for (int i = 0;i < g_nStateCount;i++)
		{
			tmt_AsyncStatePara	*paraState = &g_pAsyncStateTest->m_oStateAsyncParas.m_paraState[i];
			if(paraState == NULL)
			{
				continue;
			}

			for(int i = 0;i < MAX_MODULE_COUNT && i < nAnalogModuleCnt;i++)
			{
				tmt_AsyncChannel *pVolChannel = paraState->m_oStateAsyncModule.m_oAnalogModules[i].m_pVolChannel;
				tmt_AsyncChannel *pCurrChannel = paraState->m_oStateAsyncModule.m_oAnalogModules[i].m_pCurrChannel;
				if(pVolChannel != NULL)
				{
					delete[] pVolChannel;
				}
				if(pCurrChannel != NULL)
				{
					delete[] pCurrChannel;
				}
			}

			for(int i = 0;i < MAX_MODULE_COUNT && i < nWeekModuleCnt;i++)
			{
				tmt_AsyncChannel *pVolChannel = paraState->m_oStateAsyncModule.m_oWeekModules[i].m_pVolChannel;
				tmt_AsyncChannel *pCurrChannel = paraState->m_oStateAsyncModule.m_oWeekModules[i].m_pCurrChannel;
				if(pVolChannel != NULL)
				{
					delete[] pVolChannel;
				}
				if(pCurrChannel != NULL)
				{
					delete[] pCurrChannel;
				}
			}

			if(nDigitalModuleCnt > 0)
			{
				tmt_AsyncChannel *pVolChannel = paraState->m_oStateAsyncModule.m_oDigitalModules.m_pVolChannel;
				tmt_AsyncChannel *pCurrChannel = paraState->m_oStateAsyncModule.m_oDigitalModules.m_pCurrChannel;
				if(pVolChannel != NULL)
				{
					delete[] pVolChannel;
				}
				if(pCurrChannel != NULL)
				{
					delete[] pCurrChannel;
				}
			}
		}
		delete[] g_pAsyncStateTest->m_oStateAsyncParas.m_paraState;
		delete g_pAsyncStateTest;
	}
}

void CSttDeviceBase::SaveSystemConfig()
{
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("SttTestServer.ini");
	QFile fileini(strXMLPath);

	if(fileini.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
	{
		BOOL bNeedWrite = FALSE;

		//TimeZone
		CDvmData *pDvmData = (CDvmData*)m_oUserSetting.FindByID("TimeZone");
		CString strValue;
		strValue.Format("%d",g_theSystemConfig->m_nTimeZone);

		if(pDvmData == NULL)
		{
			pDvmData = m_oUserSetting.AddNewData("TimeZone",strValue);
			bNeedWrite = TRUE;
		}
		else
		{
			if(strValue != pDvmData->m_strValue)
			{
				pDvmData->m_strValue = strValue;
				bNeedWrite = TRUE;
			}
		}

		if(bNeedWrite)
		{
			CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			CSttXmlSerializeTool oSttXmlSerializeTool;
			oSttXmlSerializeTool.CreateXmlSerializeWrite(&m_oUserSetting);
			CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
			oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
		}

		fileini.close();
	}
}

void CSttDeviceBase::ReadSystemConfig()
{
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("SttTestServer.ini");
	QFile fileini(strXMLPath);

	if(fileini.open(QIODevice::ReadWrite | QIODevice::Text))
	{
		char *pBuf = new char[1024000];
		qint64 nSize = fileini.read(pBuf,1024000);

		CSttXmlSerializeTool oSttXmlSerializeTool;
		if(nSize > 10)
		{
			oSttXmlSerializeTool.CreateXmlSerializeRead(&m_oUserSetting,pBuf,nSize);
		}
		delete[] pBuf;
		fileini.close();
	}
	else
	{
		if(fileini.exists())
		{
			system("/mnt/dosfsck -w -a /dev/mmcblk0p1");
		}
	}
}
