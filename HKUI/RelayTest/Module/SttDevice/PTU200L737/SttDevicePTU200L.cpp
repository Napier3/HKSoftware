#include "SttDevicePTU200L.h"
#include "../../Engine/SttServerTestCtrlCntr.h"
#include "../Module/Week/SttDevice_Week.h"

CSttDevicePTU200L *CSttDevicePTU200L::g_pSttDevicePTU200L = NULL;
long CSttDevicePTU200L::g_nSttDeviceRef = 0;

CSttDevicePTU200L::CSttDevicePTU200L()
{
	//主板ST口模式设置，L336D默认RX1是B码
	//00-None 01:FT3 10:PPS  11:BCode
	m_nMainSTMode = 0b1011;
}

CSttDevicePTU200L::~CSttDevicePTU200L()
{
}

void CSttDevicePTU200L::Create()
{
	g_nSttDeviceRef++;

	if(g_nSttDeviceRef == 1)
	{
		g_pSttDevicePTU200L = new CSttDevicePTU200L;
		g_pSttDeviceBase = (CSttDeviceBase *)g_pSttDevicePTU200L;
	}
}

void CSttDevicePTU200L::Release()
{
	g_nSttDeviceRef--;

	if(g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePTU200L;
		g_pSttDevicePTU200L = NULL;
	}
}

void CSttDevicePTU200L::InitModulePowerCtrl()
{
	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		if(pModule->m_oModuleAttr.m_nModuleIndex == 2)
		{
			pModule->m_oModuleAttr.m_nModulePower = STT_MODULE_VOLT_V270_270;
			pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV270_PTU200L);
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

		if(pModule->m_oModuleAttr.m_nModuleIndex == 3)
		{
			pModule->m_oModuleAttr.m_nModulePower = STT_MODULE_CURRENT_C12_5;
			pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlC12_5);
		}
	}

	//WEEK
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		if(pModule->m_oModuleAttr.m_nModuleIndex == 16)
		{
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D_ECTEVT)
			{
				g_nL336DWeekType = pModule->m_oModuleAttr.m_nModulePower;//主板小信号
			}
		}
	}
}

int CSttDevicePTU200L::InitDevice(BOOL bHasAdjFile)
{
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_D; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		if(pModule->m_oModuleAttr.m_nModuleIndex == 1)
		{
			pModule->m_oModuleAttr.m_nFiberPortNum_LC = 0;
			pModule->m_oModuleAttr.m_nFiberPortNum_STSend = 2;
			pModule->m_oModuleAttr.m_nFiberPortNum_STRecv = 0;
		}
	}

	m_nCurrPowerRefVal = 178;//2.3/3.3*255
	m_nCommfd = open("/dev/SttDriver_PN466", O_RDWR);
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	g_nStateCount = read(m_nCommfd,NULL,0x201);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nStateCount = g_nStateCount;
	InitBuff();
	m_nTouchfd = open("/dev/exc7200dev", O_RDWR);
	m_pMMapBuf = (Drv_MMapBuf *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
	qDebug() << "Driver Mmap = " << m_pMMapBuf;
	InitDApara(m_nCommfd, bHasAdjFile);

	long nFT3Idx = m_pIECConfigFt3->mdCnt;
	m_pIECConfigFt3->item[nFT3Idx].moduletype = STT_MODULE_TYPE_DIGITAL_2G6M;
	m_pIECConfigFt3->item[nFT3Idx].module = 0x8000;//可以和小信号公用位置片选
	m_pIECConfigFt3->item[nFT3Idx].nSTSendBeginIdx = -1;
	m_pIECConfigFt3->item[nFT3Idx].nSTSendEndIdx = -1;
	m_pIECConfigFt3->item[nFT3Idx].nSTRecvBeginIdx = 0;
	m_pIECConfigFt3->item[nFT3Idx].nSTRecvEndIdx = 1;
	m_pIECConfigFt3->mdCnt += 1;

	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nSTModeSet = 2;
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	g_nDrvMainSTMode = ioctl(m_nCommfd, 0x506, 0);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	return m_nCommfd;
}

long CSttDevicePTU200L::TransAuxDcVolt(float fUdc)
{
	long nValue = 0;
	//输出辅助直流,不区分模块,统一值
	float fUdcMin, fCoef, fZero;
	fUdcMin = 0.0001;//关断值
	fCoef = 1.0f;
	fZero = 0.0f;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[0];

	if(pModule != NULL)
	{
		PSTT_CHANNEL_WAVE_ADJUST pChUdcAdj =
			&pModule->m_oModuleAdjust.m_oTempAdjust[0].m_oChUdcAdj;
		int nGearCnt = pChUdcAdj->m_nGearCount;

		for(int j = 0; j < nGearCnt; j++)
		{
			if(fUdc < pChUdcAdj->m_oChGearAdj[j].m_fGearValue + EPSINON)
			{
				fCoef = pChUdcAdj->m_oChGearAdj[j].m_oAdjItem.m_fCoef;
				fZero = pChUdcAdj->m_oChGearAdj[j].m_oAdjItem.m_fZero;
				break;
			}
		}

		for(int j = 0; j < nGearCnt; j++)
		{
			if(pChUdcAdj->m_oChGearAdj[j].m_oAdjItem.m_fCoef < 0.01)
			{
				fUdcMin = pChUdcAdj->m_oChGearAdj[j].m_fGearValue;
				break;
			}
		}
	}

	long nEnable = 0;
	long nDA = 0;

	if(fUdc < fUdcMin)
	{
		nEnable = 0;//关闭
	}
	else
	{
		nEnable = 1;//打开

		if(fUdc > 299.999)
		{
			fUdc = 299.999;
		}

		fUdc = fUdc * fCoef + fZero;
		float fValue = 0;

		if(fUdcMin < 1.0)
		{
			//未正确配置低档，默认110伏硬件
			fValue = fUdc * 0.014778 - 1.3854;
		}
		else if(fUdcMin < 13.0)
		{
			fValue = fUdc * 0.010739 - 0.02984;//12伏公式
		}
		else
		{
			fValue = fUdc * 0.014778 - 1.3854;//110伏公式
		}

		fValue = fValue / 3.3;

		if(fValue > 0.999999)
		{
			fValue = 0.999999;
		}
		else if(fValue < 0.000001)
		{
			fValue = 0.0;
		}

		nDA = 0xFFF * fValue;
	}

	nValue = nEnable << 24;
	nValue |= nDA << 12;
	return nValue;
}

void CSttDevicePTU200L::SetAuxDcVolt(float fUdc)
{
	if(g_theDeviceSystemParameter->m_nModuleCount_U == 0)
	{
		return;
	}

	long nValue = TransAuxDcVolt(fUdc);
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[0];

	if(pModule != NULL)
	{
		long nModuleIndex = pModule->m_oModuleAttr.m_nModuleIndex;
		nValue |= ModuleIndexTransToDrv(nModuleIndex);

		g_fAuxVolt = fUdc;
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(m_nfd, 0x10f, nValue);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}
}

void CSttDevicePTU200L::GetVoltCurRtData()
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase == NULL)
	{
		return;
	}

	GetRtData();
}

void CSttDevicePTU200L::PreStartTestPro()
{
	if(g_theSystemConfig->m_nHasAnalog)
	{
		Sleep(100);//电源打开到端口继电器之间延时
	}
}

void CSttDevicePTU200L::DAValueCalc_Comm(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt, BOOL bDC,
									   int nDirection, int nGradientHarm, float fGradientAmp, float fUdc)
{
	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;
	int nModuleIndex;
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

		if(pModule->m_oModuleAttr.m_nModuleIndex == 2)
		{
			unsigned char nCode = (oDAPara.nvolt[nIndex] >> 8) & 0xFF;

			if(nCode < m_nVoltPowerRefVal)
			{
				oDAPara.nvolt[nIndex] = m_oDAPara.nvolt[nIndex] & 0xFF;
				oDAPara.nvolt[nIndex] |= m_nVoltPowerRefVal << 8;
			}
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

			nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
			nModuleIndex += nIndex;

			if(bDC)
			{
				if(pModule->m_oModuleAttr.m_nModuleIndex == 3)
				{
					unsigned char nByte = 0.9 / 3.3 * 255;
					m_oDAPara.nvolt[nModuleIndex] = ((unsigned int)nByte) << (1 * 8);
				}
				else
				{
					SetCurrentDApara_DC(fIsum,nIndex);
				}
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
				oDAPara.nvolt[nModuleIndex] = m_oDAPara.nvolt[nModuleIndex];

				if(pModule->m_oModuleAttr.m_nModuleIndex == 3)
				{
					unsigned char nCode = (oDAPara.nvolt[nModuleIndex] >> 8) & 0xFF;

					if(nCode < m_nCurrPowerRefVal)
					{
						oDAPara.nvolt[nModuleIndex] = m_oDAPara.nvolt[nModuleIndex] & 0xFF;
						oDAPara.nvolt[nModuleIndex] |= m_nCurrPowerRefVal << 8;
					}

					if(fIMax < 1)
					{
						m_oDAPara.nvolt[nModuleIndex] = oDAPara.nvolt[nModuleIndex];
					}
				}
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
				oDAPara.nvolt[nModuleIndex] = m_oDAPara.nvolt[nModuleIndex];

				if(pModule->m_oModuleAttr.m_nModuleIndex == 3)
				{
					unsigned char nCode = (oDAPara.nvolt[nModuleIndex] >> 8) & 0xFF;
					if(nCode < m_nCurrPowerRefVal)
					{
						oDAPara.nvolt[nModuleIndex] = m_oDAPara.nvolt[nModuleIndex] & 0xFF;
						oDAPara.nvolt[nModuleIndex] |= m_nCurrPowerRefVal << 8;
					}

					nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

					for(int k = 0; k < nTmtChanNum; k++)
					{
						nTmtPos = pModule->m_nChTmtPos[k];

						if(nTmtPos < 0)
						{
							continue;
						}

						fAmp = fabs(pCurrent[nTmtPos].Harm[1].fAmp);
						if(g_nTmtParaMode == 0)
						{
							//界面一次值
							fAmp = fAmp*g_theSystemConfig->GetCTRate(nTmtPos/3);
						}

						if(fIMax < fAmp)
						{
							fIMax = fAmp;
						}
					}

					if(fIMax < 1)
					{
						m_oDAPara.nvolt[nModuleIndex] = oDAPara.nvolt[nModuleIndex];
					}
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

void CSttDevicePTU200L::DAValueCalc_Manu_UpdateParameter(BOOL bDC)
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

			if(pModule->m_oModuleAttr.m_nModuleIndex == 3)
			{
				if(bDC)
				{
					unsigned char nByte = 0.9 / 3.3 * 255;
					m_oDAPara.nvolt[nModuleIndex] = ((unsigned int)nByte) << (1 * 8);
				}
				else
				{
					m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
					long nDAvolt = m_oDAPara.nvolt[nModuleIndex];
					unsigned char nCode = (nDAvolt >> 8) & 0xFF;

					if(nCode < m_nCurrPowerRefVal)
					{
						m_oDAPara.nvolt[nModuleIndex] = nDAvolt & 0xFF;
						m_oDAPara.nvolt[nModuleIndex] |= m_nCurrPowerRefVal << 8;
					}
				}
			}
			else
			{
				m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
			}
		}
	}

	WriteDApara(&m_oDAPara);
}

void CSttDevicePTU200L::ProStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_StatePara  &oTmt_FirstState)
{
	DeviceDAPara *pDevBaseDAPara = &CSttDeviceBase::g_pSttDeviceBase->m_oDAPara;
	DeviceDAPara *pDAParaForState2 = &CSttDeviceBase::g_pSttDeviceBase->m_oDAParaForState2;
	int nModuleIndex;
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

		if(pModule->m_oModuleAttr.m_nModuleIndex == 2)
		{
			unsigned char nCode = (pDAPara->nvolt[nIndex] >> 8) & 0xFF;
			unsigned char nRef = CSttDeviceBase::g_pSttDeviceBase->m_nVoltPowerRefVal;

			if(nCode < nRef)
			{
				pDAPara->nvolt[nIndex] = pDevBaseDAPara->nvolt[nIndex] & 0xFF;
				pDAPara->nvolt[nIndex] |= nRef << 8;
			}
		}
	}

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
			nModuleIndex = nIndex + g_theDeviceSystemParameter->m_nModuleCount_U;
			pDevBaseDAPara->nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
			pDAPara->nvolt[nModuleIndex] = pDevBaseDAPara->nvolt[nModuleIndex];
			pDAParaForState2->nvolt[nModuleIndex] = pDevBaseDAPara->nvolt[nModuleIndex];

			if(pModule->m_oModuleAttr.m_nModuleIndex == 3)
			{
				unsigned char nCode = (pDAPara->nvolt[nModuleIndex] >> 8) & 0xFF;
				unsigned char nRef = CSttDeviceBase::g_pSttDeviceBase->m_nCurrPowerRefVal;

				if(nCode < nRef)
				{
					pDAPara->nvolt[nModuleIndex] = pDevBaseDAPara->nvolt[nModuleIndex] & 0xFF;
					pDAPara->nvolt[nModuleIndex] |= nRef << 8;
				}

				long nChanNum = pModule->m_oModuleAttr.m_nChannelNum;
				float fIMax_ForDa = 0;
				for(int j = 0; j < nChanNum; j++)
				{
					long nTmtPos = pModule->m_nChTmtPos[j];
					float fChanValue = oTmt_FirstState.m_uiCUR[nTmtPos].Harm[1].fAmp;
					fChanValue = fChanValue * pModule->m_fChTmtCoef[j];
					if(fChanValue > fIMax_ForDa)
					{
						fIMax_ForDa = fChanValue;
					}
				}

				if(fIMax_ForDa < 1)
				{
					pDevBaseDAPara->nvolt[nModuleIndex] = pDAPara->nvolt[nModuleIndex];
				}
			}
		}
	}
}

void CSttDevicePTU200L::SetPeripheral()
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
	ioctl(m_nfd, 0x102, m_nMainSTMode); //00-None 01:FT3 10:PPS 11:BCode
	g_nDrvMainSTMode = m_nMainSTMode;
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

BOOL CSttDevicePTU200L::SetOutputTime(tmt_channel *pChannel, BOOL bDc, float &fOutPutTime)
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
	fOutPutTime = 0.0f;//初始化为不限时
	float fCTRate = 1.0;

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_I; i++)
	{
		pModule = g_theDeviceSystemParameter->m_oModules_I[i];

		if(pModule == NULL)
		{
			continue;
		}

		if(pModule->m_oModuleAttr.m_nModuleIndex != 3)
		{
			continue;//只统计位置3的电流模块
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

		if(nPowerMode == STT_CurrentMODULE_POWER_HIGH)
		{
			fOutPutTime = 0.4 * 20 * 20.0 / fIMax;
		}
		else
		{
			fOutPutTime = 20 * 20.0 / fIMax;
		}
	}

	return TRUE;
}
