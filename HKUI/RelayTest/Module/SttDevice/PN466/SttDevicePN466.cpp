#include "SttDevicePN466.h"

CSttDevicePN466 *CSttDevicePN466::g_pSttDevicePN466=NULL;
long CSttDevicePN466::g_nSttDeviceRef = 0;

CSttDevicePN466::CSttDevicePN466()
{

}

CSttDevicePN466::~CSttDevicePN466()
{
	if(g_pFpgaUart != NULL)
	{
		delete g_pFpgaUart;
	}
	FreeAsyncManu();
	FreeAsyncState();
}

void CSttDevicePN466::Create()
{
    g_nSttDeviceRef++;

    if (g_nSttDeviceRef == 1)
    {
        g_pSttDevicePN466=new CSttDevicePN466;
        g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePN466;
    }
}

void CSttDevicePN466::Release()
{
    g_nSttDeviceRef--;

    if (g_nSttDeviceRef == 0)
    {
        delete g_pSttDevicePN466;
        g_pSttDevicePN466 = NULL;
    }
}

int CSttDevicePN466::InitDevice(BOOL bHasAdjFile)
{
	if(g_theDeviceSystemParameter->m_nModuleCount_ADMU > 0)
		g_pFpgaUart = new CFpgaUart;

	m_nCurrPowerRefVal = 178;//按20伏参考去控制电源
    m_nCommfd=open("/dev/SttDriver_PN466",O_RDWR);
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	g_nStateCount = read(m_nCommfd,NULL,0x201);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nStateCount = g_nStateCount;

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(m_nCommfd, 0x14D, 0);//设置直流测量电流档位
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	InitBuff();
	m_pMMapBuf = (Drv_MMapBuf *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
	qDebug()<<"Driver Mmap = "<<m_pMMapBuf;
#endif
    InitDApara(m_nCommfd,bHasAdjFile);
	InitAsyncManu();
	InitAsyncState();

    //VOLT
    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
    {
        PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
        if(pModule==NULL)
            continue;

        CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
        if(pCSttPowerCtrlBase==NULL)
        {
            pModule->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase*)(new CSttPowerCtrlV130_PN);
        }
    }

    //CURRENT
    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
    {
        PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
        if(pModule==NULL)
            continue;

        CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase == NULL && pModule->m_oModuleAttr.m_nModuleIndex == 3)
		{
            pModule->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase*)(new CSttPowerCtrlC20);
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[0].m_nChMeasPos = 3;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[1].m_nChMeasPos = 0;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[2].m_nChMeasPos = 4;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[3].m_nChMeasPos = 2;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[4].m_nChMeasPos = 5;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[5].m_nChMeasPos = 1;
			pModule->m_nChMeasPos[0] = 3;
			pModule->m_nChMeasPos[1] = 0;
			pModule->m_nChMeasPos[2] = 4;
			pModule->m_nChMeasPos[3] = 2;
			pModule->m_nChMeasPos[4] = 5;
			pModule->m_nChMeasPos[5] = 1;
		}

		if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_CURRENT_C20)
		{
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[0].m_nChMeasPos = 3;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[1].m_nChMeasPos = 0;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[2].m_nChMeasPos = 4;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[3].m_nChMeasPos = 2;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[4].m_nChMeasPos = 5;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[5].m_nChMeasPos = 1;
			pModule->m_nChMeasPos[0] = 3;
			pModule->m_nChMeasPos[1] = 0;
			pModule->m_nChMeasPos[2] = 4;
			pModule->m_nChMeasPos[3] = 2;
			pModule->m_nChMeasPos[4] = 5;
			pModule->m_nChMeasPos[5] = 1;
		}
    }

	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinVoltMeas)
	{
		for(int i = 0;i < g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinCount && i < 10;i++)
		{
			PSTT_BIN_ADJUST pBinAdj = &g_theDeviceSystemParameter->m_oBinAdj[i];
			for(int j = 0;j < pBinAdj->m_nGearCount && j < ADJUST_MAX_GEAR_COUNT;j++)
			{
				m_oBinSetting.fCoef[i][j] = pBinAdj->m_oBinGearAdj[j].m_oAdjItem.m_fCoef;
				m_oBinSetting.fZero[i][j] = pBinAdj->m_oBinGearAdj[j].m_oAdjItem.m_fZero;
			}
		}
	}

    return m_nCommfd;
}

void CSttDevicePN466::SetSystemLocalTime(CString strTime_t)
{
	if(m_nSetSysTmCnt > 0)
		return;

	unsigned int nTime_t = strTime_t.toUInt();
	short nYear,nMon,nDay,nHour,nMin,nSec;
	TransTimer_t(nTime_t,nYear,nMon,nDay,nHour,nMin,nSec);

	int nSize = 0;
	int nFlag = -1;
	
	Drv_SysUtc oSysUtc;
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	nSize = read(m_nCommfd, (char *)&oSysUtc, 0x205);
	nFlag = oSysUtc.tmFlag;
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	if(nSize == sizeof(Drv_SysUtc))
	{
		if(nFlag == 0)
		{
			setBCodeTime(nYear, nMon, nDay, nHour, nMin, nSec);//传入的是0时区时间
			m_nSetSysTmCnt++;
		}
	}
}

void CSttDevicePN466::GetVoltCurRtData()
{
    CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
    if(pSttTestBase == NULL)
        return;

    GetRtData();
}

void CSttDevicePN466::PreStartTestPro()
{
	if(g_theSystemConfig->m_nHasAnalog)
	{
		Sleep(100);//电源打开到端口继电器之间延时
	}
}

BOOL CSttDevicePN466::SetOutputTime(tmt_channel *pChannel, BOOL bDc, float &fOutPutTime)
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
	float fOutPutTimeMin = 100.0;
	float fCTRate = 1.0;

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_I; i++)
	{
		pModule = g_theDeviceSystemParameter->m_oModules_I[i];

		if(pModule == NULL)
		{
			continue;
		}

		float fIMax = 0;
		float fAmp;
		float fChTmtCoef;
		long nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;

		for(int k = 0; k < nChannelNum; k++)
		{
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

		if(fIMax < 10.001)
		{
			continue;//小于10A，不限时
		}

		fOutPutTime = 0;
		if(nPowerMode == STT_CurrentMODULE_POWER_HIGH)
		{
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_CURRENT_C20)
			{
				fOutPutTime = 0.4 * 20 * 20.0 / fIMax;
			}
			else
			{
				//32A模块
				fOutPutTime = 0.4 * 20 * 30.0 / fIMax;
			}
		}
		else
		{
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_CURRENT_C20)
			{
				fOutPutTime = 20 * 20.0 / fIMax;
			}
			else
			{
				//32A模块
				fOutPutTime = 20 * 30.0 / fIMax;
			}
		}

		if(fOutPutTime < fOutPutTimeMin)
		{
			fOutPutTimeMin = fOutPutTime;
		}
	}

	if(fOutPutTimeMin > 99.0)
		fOutPutTimeMin = 0;//不限时

	fOutPutTime = fOutPutTimeMin;
	return TRUE;
}

void CSttDevicePN466::GetBinAndDC()
{
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinVoltMeas)
	{
		char *pModule_cs = m_pDrvModuleBase + 0x1070;
		char *pModule_addr = m_pDrvModuleBase + 0x106c;
		char *pModule_data = m_pDrvModuleBase + 0x1038;

		*pModule_cs = 0x01 << 4;
		Sleep(1);

		for (int i = 0; i < 10; i++)
		{
			*pModule_addr = i;
			Sleep(1);
			memcpy(&CSttDeviceBase::g_pSttDeviceBase->m_nCurBinaryCode[i],pModule_data,4);
		}
	}

	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nDCMeas)
	{
		char *pReadIn_I = m_pDrvModuleBase + 0x1008;
		char *pReadIn_V = m_pDrvModuleBase + 0x1010;

		unsigned int nCode = 0;
		memcpy(&nCode,pReadIn_I,4);
		nCode = nCode &0xFFFFFF;
		CSttDeviceBase::g_pSttDeviceBase->m_nReadInCode_I = nCode;
		memcpy(&nCode,pReadIn_V,4);
		nCode = nCode &0xFFFFFF;
		CSttDeviceBase::g_pSttDeviceBase->m_nReadInCode_V = nCode;
	}
}

void CSttDevicePN466::GetModuleInfo(Drv_SysInfo *pSysInfo)
{
	CSttDeviceBase::GetModuleInfo(pSysInfo);

	if(m_nSetAmpPowerCnt == 0)
	{
		unsigned int nData = 0;
		BOOL bUse[2];
		bUse[0] = bUse[1] = FALSE;

		//再判断位置3电源硬件是否支持
		nData = (pSysInfo->stBack[2].dat[6] >> 16) & 0xfff;
		float fVoltDc = translateVoltBase(nData, 28);
		if(fVoltDc > 10.0)
		{
			nData = pSysInfo->stBack[2].dat[6] & 0xfff;
			fVoltDc = translateVoltBase(nData, 28);
			if(fVoltDc < -10.0)
			{
				//满足正负控制电源
				nData = (pSysInfo->stBack[2].dat[7] >> 16) & 0xfff;
				fVoltDc = translateVoltBase(nData, 25 * 1.1);
				if(fVoltDc < 1.0)
				{
					bUse[0] = TRUE;
				}
			}
		}

		//再判断位置4电源硬件是否支持
		nData = (pSysInfo->stBack[3].dat[6] >> 16) & 0xfff;
		fVoltDc = translateVoltBase(nData, 28);
		if(fVoltDc > 10.0)
		{
			nData = pSysInfo->stBack[3].dat[6] & 0xfff;
			fVoltDc = translateVoltBase(nData, 28);
			if(fVoltDc < -10.0)
			{
				//满足正负控制电源
				nData = (pSysInfo->stBack[3].dat[7] >> 16) & 0xfff;
				fVoltDc = translateVoltBase(nData, 25 * 1.1);
				if(fVoltDc < 1.0)
				{
					bUse[1] = TRUE;
				}
			}
		}

		long nCurrPowerForStop = 178;//20伏待机
		int nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U;
		int nModuleIndex;

		//CURRENT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

			if(pModule != NULL)
			{
				nModuleIndex = pModule->m_oModuleAttr.m_nModuleIndex;
				if(nModuleIndex == 3 || nModuleIndex == 4)
				{
					if(bUse[nModuleIndex - 3])
					{
						unsigned char nByte = nCurrPowerForStop;
						m_oDAParaForTestStop.nvolt[nModuleCnt] = ((unsigned int)nByte) << (1 * 8);
					}
				}
			}

			nModuleCnt++;
		}

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

			if(pModule != NULL)
			{
				nModuleIndex = pModule->m_oModuleAttr.m_nModuleIndex;
				if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V130_C20)
				{
					if(nModuleIndex == 4)
					{
						if(bUse[1])
						{
							unsigned char nByte = nCurrPowerForStop;
							m_oDAParaForTestStop.nvolt[nModuleCnt] = nByte;
						}
					}
				}
			}

			nModuleCnt++;
		}

		WriteDAparaForTestStop();
	}
}

BOOL CSttDevicePN466::OnTimer(BOOL bExec)
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
			GetBinAndDC();

			//纯数字实验进行中
			g_theSttDeviceStatus->m_nOverHeat = 0;//模块过热
			g_theSttDeviceStatus->m_nIBreak = 0;//电流开路
			g_theSttDeviceStatus->m_nUShort = 0;//电压短路

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

		if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_VOLT
				|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_CURRENT
				|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
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
		//实验停止中
		g_theSttDeviceStatus->m_nOverHeat = 0;//模块过热
		g_theSttDeviceStatus->m_nIBreak = 0;//电流开路
		g_theSttDeviceStatus->m_nUShort = 0;//电压短路
	}
	GetBinAndDC();

	return TRUE;
}

void CSttDevicePN466::ProStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_StatePara  &oTmt_FirstState)
{
	DeviceDAPara *pDevBaseDAPara = &CSttDeviceBase::g_pSttDeviceBase->m_oDAPara;
	DeviceDAPara *pDAParaForState2 = &CSttDeviceBase::g_pSttDeviceBase->m_oDAParaForState2;
	int nModuleIndex = 0;
	memcpy(pDAPara, pDevBaseDAPara, sizeof(DeviceDAPara));
	memcpy(pDAParaForState2, pDevBaseDAPara, sizeof(DeviceDAPara));

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(pModule->m_oModuleAttr.m_fDefChMax, fAuxMax, nIndex, FALSE);
		pDAPara->nvolt[nIndex] = pDevBaseDAPara->nvolt[nIndex];
		pDAParaForState2->nvolt[nIndex] = pDevBaseDAPara->nvolt[nIndex];
	}

	nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
	CSttPowerCtrlBase *pSttPowerCtrlBase = NULL;

	//CURRENT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

		if(pSttPowerCtrlBase != NULL)
		{
			pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
			pDevBaseDAPara->nvolt[nModuleIndex + nIndex] = pSttPowerCtrlBase->GetModuleDA();
			pDAPara->nvolt[nModuleIndex + nIndex] = pDevBaseDAPara->nvolt[nModuleIndex + nIndex];
			pDAParaForState2->nvolt[nModuleIndex + nIndex] = pDevBaseDAPara->nvolt[nModuleIndex + nIndex];

			unsigned char nCode = (pDAPara->nvolt[nModuleIndex + nIndex] >> 8) & 0xFF;
			unsigned char nRef = CSttDeviceBase::g_pSttDeviceBase->m_nCurrPowerRefVal;

			if(nCode < nRef)
			{
				pDAPara->nvolt[nModuleIndex + nIndex] = pDevBaseDAPara->nvolt[nModuleIndex + nIndex] & 0xFF;
				pDAPara->nvolt[nModuleIndex + nIndex] |= nRef << 8;
			}

			long nChanNum = pModule->m_oModuleAttr.m_nChannelNum;
			float fIMax_ForDa = 0;
			for(int j = 0; j < nChanNum; j++)
			{
				long nTmtPos = pModule->m_nChTmtPos[j];
				float fChanValue = oTmt_FirstState.m_uiCUR[nTmtPos].Harm[1].fAmp;
				if(g_nTmtParaMode == 0)
				{
					//界面一次值
					fChanValue = fChanValue*g_theSystemConfig->GetCTRate(nTmtPos/3);
				}
				fChanValue = fChanValue * pModule->m_fChTmtCoef[j];
				if(fChanValue > fIMax_ForDa)
				{
					fIMax_ForDa = fChanValue;
				}
			}

			if(fIMax_ForDa < 1)
			{
				pDevBaseDAPara->nvolt[nModuleIndex + nIndex] = pDAPara->nvolt[nModuleIndex + nIndex];
			}
		}
	}

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule_UI != NULL)
		{
			pSttPowerCtrlBase = pModule_UI->m_oModuleAttr.m_pPowerCtrlBase;

			if(pSttPowerCtrlBase != NULL)
			{
				nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
				nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
				pSttPowerCtrlBase->SetVoltDA_State();
				pSttPowerCtrlBase->SetCurrentDA_State(0);
				pDevBaseDAPara->nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
				pDAPara->nvolt[nModuleIndex] = pDevBaseDAPara->nvolt[nModuleIndex];
				pDAParaForState2->nvolt[nModuleIndex] = pDevBaseDAPara->nvolt[nModuleIndex];
			}

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
					pDAPara->nvolt[nCurModuleIndex + 1] =
						(pDAPara->nvolt[nCurModuleIndex] >> 8) & 0xFF;
					pDAParaForState2->nvolt[nCurModuleIndex + 1] =
						(pDAParaForState2->nvolt[nCurModuleIndex] >> 8) & 0xFF;
				}
			}
		}
	}
}

void CSttDevicePN466::ProAsyncStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_AsyncStatePara  &oTmt_FirstState)
{
	DeviceDAPara *pDevBaseDAPara = &CSttDeviceBase::g_pSttDeviceBase->m_oDAPara;
	DeviceDAPara *pDAParaForState2 = &CSttDeviceBase::g_pSttDeviceBase->m_oDAParaForState2;
	int nModuleIndex = 0;
	memcpy(pDAPara, pDevBaseDAPara, sizeof(DeviceDAPara));
	memcpy(pDAParaForState2, pDevBaseDAPara, sizeof(DeviceDAPara));

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(pModule->m_oModuleAttr.m_fDefChMax, fAuxMax, nIndex, FALSE);
		pDAPara->nvolt[nIndex] = pDevBaseDAPara->nvolt[nIndex];
		pDAParaForState2->nvolt[nIndex] = pDevBaseDAPara->nvolt[nIndex];
	}

	nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
	CSttPowerCtrlBase *pSttPowerCtrlBase = NULL;

	//CURRENT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

		if(pSttPowerCtrlBase != NULL)
		{
			pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
			pDevBaseDAPara->nvolt[nModuleIndex + nIndex] = pSttPowerCtrlBase->GetModuleDA();
			pDAPara->nvolt[nModuleIndex + nIndex] = pDevBaseDAPara->nvolt[nModuleIndex + nIndex];
			pDAParaForState2->nvolt[nModuleIndex + nIndex] = pDevBaseDAPara->nvolt[nModuleIndex + nIndex];
		}
	}

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule_UI != NULL)
		{
			pSttPowerCtrlBase = pModule_UI->m_oModuleAttr.m_pPowerCtrlBase;

			if(pSttPowerCtrlBase != NULL)
			{
				nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
				nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
				pSttPowerCtrlBase->SetVoltDA_State();
				pSttPowerCtrlBase->SetCurrentDA_State(0);
				pDevBaseDAPara->nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
				pDAPara->nvolt[nModuleIndex] = pDevBaseDAPara->nvolt[nModuleIndex];
				pDAParaForState2->nvolt[nModuleIndex] = pDevBaseDAPara->nvolt[nModuleIndex];
			}

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
					pDAPara->nvolt[nCurModuleIndex + 1] =
						(pDAPara->nvolt[nCurModuleIndex] >> 8) & 0xFF;
					pDAParaForState2->nvolt[nCurModuleIndex + 1] =
						(pDAParaForState2->nvolt[nCurModuleIndex] >> 8) & 0xFF;
				}
			}
		}
	}
}

void CSttDevicePN466::DAValueCalc_Comm(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt, BOOL bDC,
									  int nDirection, int nGradientHarm, float fGradientAmp, float fUdc)
{
	DAPowerCtrl();
	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;
	int nModuleIndex = 0;
	float fAmp;
	InitDAData();
	DeviceDAPara oDAPara;
	memcpy(&oDAPara, &m_oDAPara, sizeof(DeviceDAPara));
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

		oDAPara.nvolt[nIndex] = m_oDAPara.nvolt[nIndex];
	}

	nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
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
				oDAPara.nvolt[nModuleIndex + nIndex] = m_oDAPara.nvolt[nModuleIndex + nIndex];

				unsigned char nCode = (oDAPara.nvolt[nModuleIndex + nIndex] >> 8) & 0xFF;

				if(nCode < m_nCurrPowerRefVal)
				{
					oDAPara.nvolt[nModuleIndex + nIndex] = m_oDAPara.nvolt[nModuleIndex + nIndex] & 0xFF;
					oDAPara.nvolt[nModuleIndex + nIndex] |= m_nCurrPowerRefVal << 8;
				}

				if(fIMax < 1)
				{
					m_oDAPara.nvolt[nModuleIndex + nIndex] = oDAPara.nvolt[nModuleIndex + nIndex];
				}
			}
		}
		else
		{
			CSttPowerCtrlBase *pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

			if(pSttPowerCtrlBase != NULL)
			{
				pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
				m_oDAPara.nvolt[nModuleIndex + nIndex] = pSttPowerCtrlBase->GetModuleDA();
				oDAPara.nvolt[nModuleIndex + nIndex] = m_oDAPara.nvolt[nModuleIndex + nIndex];

				unsigned char nCode = (oDAPara.nvolt[nModuleIndex + nIndex] >> 8) & 0xFF;
				if(nCode < m_nCurrPowerRefVal)
				{
					oDAPara.nvolt[nModuleIndex + nIndex] = m_oDAPara.nvolt[nModuleIndex + nIndex] & 0xFF;
					oDAPara.nvolt[nModuleIndex + nIndex] |= m_nCurrPowerRefVal << 8;
				}
			}
		}
	}

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		DAValue_PN_3U3I(pVolt, pCurrent, &oDAPara, nHarmCnt, bDC, nDirection, nGradientHarm, fGradientAmp, fUdc);

		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];
		if(pModule_UI != NULL)
		{
			if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V130_C20)
			{
				//VOLT
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[0];
				if(pModule != NULL)
				{
					oDAPara.nvolt[0] = m_oDAPara.nvolt[0];
				}
			}
		}
	}

	if(bDC)
	{
		WriteDApara(&m_oDAPara);
	}
	else
	{
		WriteDApara(&oDAPara);
	}
}

void CSttDevicePN466::DAValueCalc_Manu_UpdateParameter(BOOL bDC)
{
	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;
	int nModuleIndex = 0;
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

	nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
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
			m_oDAPara.nvolt[nModuleIndex + nIndex] = pSttPowerCtrlBase->GetModuleDA();

			long nDAvolt = m_oDAPara.nvolt[nModuleIndex + nIndex];
			unsigned char nCode = (nDAvolt >> 8) & 0xFF;

			if(nCode < m_nCurrPowerRefVal)
			{
				m_oDAPara.nvolt[nModuleIndex + nIndex] = nDAvolt & 0xFF;
				m_oDAPara.nvolt[nModuleIndex + nIndex] |= m_nCurrPowerRefVal << 8;
			}
		}
	}

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule_UI != NULL)
		{
			if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V130_C20)
			{
				CSttPowerCtrlBase *pSttPowerCtrlBase = pModule_UI->m_oModuleAttr.m_pPowerCtrlBase;

				if(pSttPowerCtrlBase != NULL)
				{
					pSttPowerCtrlBase->SetVoltDA_State();
					pSttPowerCtrlBase->SetCurrentDA_State(0);
					nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
					nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
					m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
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

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	WriteDApara(&m_oDAPara);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttDevicePN466::DAValueCalc_AsyncManu_UpdateParameter()
{
	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;
	int nModuleIndex = 0;
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

	nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
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
			m_oDAPara.nvolt[nModuleIndex + nIndex] = pSttPowerCtrlBase->GetModuleDA();
		}
	}

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule_UI != NULL)
		{
			CSttPowerCtrlBase *pSttPowerCtrlBase = pModule_UI->m_oModuleAttr.m_pPowerCtrlBase;

			if(pSttPowerCtrlBase != NULL)
			{
				pSttPowerCtrlBase->SetVoltDA_State();
				pSttPowerCtrlBase->SetCurrentDA_State(0);
				nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
				nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
				m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
			}

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

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	WriteDApara(&m_oDAPara);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttDevicePN466::DAValue_PN_3U3I(tmt_channel *pVolt, tmt_channel *pCurrent, DeviceDAPara *pDAPara, int nHarmCnt, BOOL bDC,
									 int nDirection, int nGradientHarm, float fGradientAmp, float fUdc)
{
	float fVoltMax_3U3I = 0;
	float fVoltMax_6U = 0;
	float fAmp;
	long nTmtChanNum, nTmtPos;
	BOOL bChanIsGradient;
	PSTT_MODULE pModule_6U = NULL;
	PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];
	long nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;

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
							if(g_nTmtParaMode == 0)
							{
								//界面一次值
								fAmp = fAmp*1000*g_theSystemConfig->GetPTRate(nTmtPos/3);
							}
						}

						if(fVoltMax_3U3I < fabs(fAmp))
						{
							fVoltMax_3U3I = fabs(fAmp);
						}
					}
				}

				//current
				if(nHarmCnt == 1)
				{
					float fIsum = 0;
					float fIMax = 0;
					for(int k = 0; k < nTmtChanNum; k++)
					{
						nTmtPos = pModule_UI->m_nChTmtPos[k];

						if(nTmtPos < 0)
						{
							continue;
						}

						if(pModule_UI->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_CURRENT)
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

					if(bDC)
					{
						pSttPowerCtrlBase->SetCurrentDA(fIsum, fIMax, 0, TRUE);
						m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
					}
					else
					{
						pSttPowerCtrlBase->SetCurrentDA(fIsum, fIMax, 0, FALSE);
						m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
						pDAPara->nvolt[nModuleIndex] = m_oDAPara.nvolt[nModuleIndex];

						unsigned char nCode = pDAPara->nvolt[nModuleIndex] & 0xFF;

						if(nCode < m_nCurrPowerRefVal)
						{
							pDAPara->nvolt[nModuleIndex] = m_nCurrPowerRefVal;
						}

						if(fIMax < 1)
						{
							m_oDAPara.nvolt[nModuleIndex] = pDAPara->nvolt[nModuleIndex];
						}
					}
				}
				else
				{
					pSttPowerCtrlBase->SetCurrentDA_State(0);
					m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
					pDAPara->nvolt[nModuleIndex] = m_oDAPara.nvolt[nModuleIndex];

					unsigned char nCode = pDAPara->nvolt[nModuleIndex] & 0xFF;
					if(nCode < m_nCurrPowerRefVal)
					{
						pDAPara->nvolt[nModuleIndex] = m_nCurrPowerRefVal;
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
								fAmp = pModule_6U->m_oModuleAttr.m_fDefChMax;
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
				pDAPara->nvolt[nCurModuleIndex + 1] = m_oDAPara.nvolt[nCurModuleIndex + 1];
			}
		}
	}
}
