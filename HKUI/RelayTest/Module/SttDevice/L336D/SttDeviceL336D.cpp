#include "SttDeviceL336D.h"
#include "../../Engine/SttServerTestCtrlCntr.h"
#include "../Module/Week/SttDevice_Week.h"
#include "../SttDeviceStatus.h"
#include "../../SttTest/Common/SttSystemDefaultOutput.h"
#include "QDir"

CSttDeviceL336D *CSttDeviceL336D::g_pSttDeviceL336D = NULL;
long CSttDeviceL336D::g_nSttDeviceRef = 0;

QList<float> fBatList;

CSttDeviceL336D::CSttDeviceL336D()
{
	//主板ST口模式设置，L336D默认RX1是B码
	//00-None 01:FT3 10:PPS  11:BCode
	m_nMainSTMode = 0b1011;
	m_oBat485Info.bHasBat = FALSE;
}

CSttDeviceL336D::~CSttDeviceL336D()
{
}

void CSttDeviceL336D::Create()
{
	g_nSttDeviceRef++;

	if(g_nSttDeviceRef == 1)
	{
		g_pSttDeviceL336D = new CSttDeviceL336D;
		g_pSttDeviceBase = (CSttDeviceBase *)g_pSttDeviceL336D;
	}
}

void CSttDeviceL336D::Release()
{
	g_nSttDeviceRef--;

	if(g_nSttDeviceRef == 0)
	{
		delete g_pSttDeviceL336D;
		g_pSttDeviceL336D = NULL;
	}
}

int CSttDeviceL336D::InitDevice(BOOL bHasAdjFile)
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
			pModule->m_oModuleAttr.m_nFiberPortNum_LC = 8;
			pModule->m_oModuleAttr.m_nFiberPortNum_STSend = 6;
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

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		CSttPowerCtrlBase *pCSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

		if(pModule->m_oModuleAttr.m_nModuleIndex == 2)
		{
			if(pCSttPowerCtrlBase == NULL)
			{
				pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV130_PN);
			}
			else
			{
				switch(pModule->m_oModuleAttr.m_nModulePower)
				{
				case STT_MODULE_VOLT_V300_300:
					pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV270_PTU200L);
					break;
				default:
					pCSttPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV130_PN);
				}
			}
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

		CSttPowerCtrlBase *pCSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

		if(pCSttPowerCtrlBase == NULL && pModule->m_oModuleAttr.m_nModuleIndex == 3)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlC12_5);
		}

		if(pModule->m_oModuleAttr.m_nModuleIndex == 3)
		{
			pModule->m_oModuleAttr.m_nChMergeMode = STT_CURRENT_ChMergeMode_3Ch;//6I并3I，需要手动外部并线
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[0].m_nChMeasPos = 3;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[1].m_nChMeasPos = 2;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[2].m_nChMeasPos = 0;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[3].m_nChMeasPos = 1;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[4].m_nChMeasPos = 4;
			pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[5].m_nChMeasPos = 5;
			pModule->m_nChMeasPos[0] = 3;
			pModule->m_nChMeasPos[1] = 2;
			pModule->m_nChMeasPos[2] = 0;
			pModule->m_nChMeasPos[3] = 1;
			pModule->m_nChMeasPos[4] = 4;
			pModule->m_nChMeasPos[5] = 5;
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

	long nFT3Idx = m_pIECConfigFt3->mdCnt;
	m_pIECConfigFt3->item[nFT3Idx].moduletype = STT_MODULE_TYPE_DIGITAL_2G6M;
	m_pIECConfigFt3->item[nFT3Idx].module = 0x8000;
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

long CSttDeviceL336D::TransAuxDcVolt(float fUdc)
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

void CSttDeviceL336D::SetAuxDcVolt(float fUdc)
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

void CSttDeviceL336D::GetVoltCurRtData()
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase == NULL)
	{
		return;
	}

	GetRtData();
}

void CSttDeviceL336D::PreStartTestPro()
{
	if(g_theSystemConfig->m_nHasAnalog)
	{
		Sleep(100);//电源打开到端口继电器之间延时
	}
}

void CSttDeviceL336D::DAValueCalc_Comm(tmt_channel *pVolt, tmt_channel *pCurrent, int nHarmCnt, BOOL bDC,
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
					if(m_oBat485Info.bHasBat)
					{
						//L336D-2
						nByte = 1.5 / 3.3 * 255;
						CSttPowerCtrlBase *pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;
						if(pSttPowerCtrlBase != NULL)
						{
							float fVset = 0;
							int nPowerMode = STT_CurrentMODULE_POWER_LOW;
							pSttPowerCtrlBase->GetCurrentPowerMode(nIndex,nPowerMode,fVset);

							if(nPowerMode == STT_CurrentMODULE_POWER_LOW)
							{
								nByte = 0.7 / 3.3 * 255;
							}
						}
					}
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

void CSttDeviceL336D::DAValueCalc_Manu_UpdateParameter(BOOL bDC)
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
					if(m_oBat485Info.bHasBat)
					{
						//L336D-2
						nByte = 1.5 / 3.3 * 255;
						CSttPowerCtrlBase *pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;
						if(pSttPowerCtrlBase != NULL)
						{
							float fVset = 0;
							int nPowerMode = STT_CurrentMODULE_POWER_LOW;
							pSttPowerCtrlBase->GetCurrentPowerMode(nIndex,nPowerMode,fVset);

							if(nPowerMode == STT_CurrentMODULE_POWER_LOW)
							{
								nByte = 0.7 / 3.3 * 255;
							}
						}
					}

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

void CSttDeviceL336D::ProStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_StatePara  &oTmt_FirstState)
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
					pDevBaseDAPara->nvolt[nModuleIndex] = pDAPara->nvolt[nModuleIndex];
				}
			}
		}
	}
}

void CSttDeviceL336D::SetPeripheral()
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

BOOL CSttDeviceL336D::IsBatPower()
{
	BOOL bBatPower = FALSE;

	if(m_oBat485Info.bHasBat)
	{
		if(g_theSttDeviceStatus->m_nBatErr == 0 && g_theSttDeviceStatus->m_bPowerAC == 0)
		{
			bBatPower = TRUE;
		}
	}

	return bBatPower;
}

BOOL CSttDeviceL336D::SetOutputTime(tmt_channel *pChannel, BOOL bDc, float &fOutPutTime)
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
	float fCTRate = 1;

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

		BOOL bBatPower = IsBatPower();

		if(bBatPower)
		{
			//电池版
			if(bDc)
			{
				if(fIMax < 10.001)
				{
					fOutPutTime = 120.0;
					continue;
				}

				fOutPutTime = 0.4 * 20 * 10.0 / fIMax;
			}
			else
			{
				if(fIMax < 5.001)
				{
					fOutPutTime = 300.0;
					continue;
				}
				if(fIMax < 10.001)
				{
					fOutPutTime = 120.0;
					continue;
				}

				fOutPutTime = 0.4 * 20 * 20.0 / fIMax;
			}
		}
		else
		{
			if(bDc)
			{
				if(fIMax < 5.001)
				{
					continue;//小于5A，不限时
				}

				fOutPutTime = 0.4 * 20 * 10.0 / fIMax;
			}
			else
			{
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
		}
	}

	return TRUE;
}

BOOL CSttDeviceL336D::CheckCurrLoadIsSafe(tmt_channel *pChannel, BOOL bIsDc)
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

		if(pModule->m_oModuleAttr.m_nModuleIndex == 3)
		{
			//位置3电流模块
			BOOL bBatPower = IsBatPower();

			if(bBatPower)
			{
				//电池供电
				//直流并联小于30A，交流并联小于50A				

				float fTotal = 0.0;
				float fAng2[6],fAmp2[6];

				for(int j = 0; j < 6; j++)
				{
					fAmp2[j] = 0.0;
					fAng2[j] = 0.0;
				}

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

					fAmp2[j] = fAmp;
					fAng2[j] = pChannel[nTmtPos].Harm[1].fAngle;
					fTotal += fAmp;
				}

				if(bIsDc)
				{
					if(fTotal > 30.001)
					{
						return FALSE;
					}
				}
				else
				{
					if(fTotal > 60.001)
					{
						return FALSE;
					}

					//交流同向并联
					fTotal = fAmp2[0];
					for(int j = 1; j < nChannelNum; j++)
					{
						if(fabs(fAng2[j] - fAng2[0]) < 0.001)
						{
							fTotal += fAmp2[j];
						}
					}

					if(fTotal > 50.001)
					{
						return FALSE;
					}
				}
			}
			else
			{
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
		}
		else
		{
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
	}

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_UI; i++)
	{
		pModule = g_theDeviceSystemParameter->m_oModules_UI[i];

		if(pModule == NULL)
		{
			continue;
		}

		nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;

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

	return TRUE;
}

BOOL CSttDeviceL336D::CheckCurrLoadIsSafe_moduleoutput(tmt_channel *pChannel, BOOL bIsDc, PSTT_MODULE pModule)
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

		if(pModule->m_oModuleAttr.m_nModuleIndex == 3)
		{
			//位置3电流模块
			BOOL bBatPower = IsBatPower();

			if(bBatPower)
			{
				//电池供电
				//直流并联小于30A，交流并联小于50A				

				float fTotal = 0.0;
				float fAng2[6],fAmp2[6];
				for(int j = 0; j < 6; j++)
				{
					fAmp2[j] = 0.0;
					fAng2[j] = 0.0;
				}

				for(int j = 0; j < nChannelNum; j++)
				{
					float fAmp = pChannel[j].Harm[1].fAmp;

					if(fAmp > (fChMax + EPSINON))
					{
						return FALSE;
					}

					fAmp2[j] = fAmp;
					fAng2[j] = pChannel[j].Harm[1].fAngle;
					fTotal += fAmp;
				}

				if(bIsDc)
				{
					if(fTotal > 30.001)
					{
						return FALSE;
					}
				}
				else
				{
					if(fTotal > 60.001)
					{
						return FALSE;
					}

					//交流同向并联
					fTotal = fAmp2[0];
					for(int j = 1; j < nChannelNum; j++)
					{
						if(fabs(fAng2[j] - fAng2[0]) < 0.001)
						{
							fTotal += fAmp2[j];
						}
					}

					if(fTotal > 50.001)
					{
						return FALSE;
					}
				}
			}
			else
			{
				for(int j = 0; j < nChannelNum; j++)
				{
					float fAmp = pChannel[j].Harm[1].fAmp;

					if(fAmp > (fChMax + EPSINON))
					{
						return FALSE;
					}
				}
			}
		}
		else
		{
			for(int j = 0; j < nChannelNum; j++)
			{
				float fAmp = pChannel[j].Harm[1].fAmp;

				if(fAmp > (fChMax + EPSINON))
				{
					return FALSE;
				}
			}
		}
	}
	else if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
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

	return TRUE;
}

float BatCap_trans(float fV)
{
	float fBat = fV/2.0;

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

BOOL CSttDeviceL336D::IsLargeCurrentOutput()
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase != NULL && pSttTestBase->GetTestStarting() && g_theSystemConfig->m_nHasAnalog)
	{
		for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_I;i++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[i];
			if(pModule != NULL)
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

void CSttDeviceL336D::GetModuleInfo(Drv_SysInfo *pSysInfo)
{
	CSttDeviceBase::GetModuleInfo(pSysInfo);

	if(!m_oBat485Info.bHasBat)
	{
		return;
	}

	BOOL bFind485 = FALSE;
	char *pModule_cs = m_pDrvModuleBase + 0x1070;
	char *pModule_addr = m_pDrvModuleBase + 0x106c;
	char *pModule_data = m_pDrvModuleBase + 0x1038;
	unsigned int nPos = 0;

	nPos = 0x01 << 4;
	memcpy(pModule_cs,&nPos,4);
	unsigned char pszBat[40];
	memset(pszBat,0,40);
	unsigned int nDat;
	for (int i = 0; i < 10; i++)
	{
		*pModule_addr = i;
		memcpy(&nDat,pModule_data,4);
		pszBat[i*4] = (nDat>>24)&0xFF;
		pszBat[i*4 + 1] = (nDat>>16)&0xFF;
		pszBat[i*4 + 2] = (nDat>>8)&0xFF;
		pszBat[i*4 + 3] = nDat&0xFF;
	}

	if(pszBat[4] == 0x42 && pszBat[5] == 0x44)
	{
		CString strDat = "";
		for (int i = 0; i <= 36; i++)
		{
			strDat += CString::number(pszBat[i],16);
			strDat += " ";
		}

		unsigned char pCRC = 0;
		for(int i = 0;i < pszBat[7];i++)
		{
			pCRC ^= pszBat[i + 4];
		}

		if(pszBat[pszBat[7] + 4] == pCRC)
		{
			// CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("BAT485 Dat = %s BCC_ok"),strDat.GetString());
			if(pszBat[8] == 2 && pszBat[9] == 1)
			{
				memcpy(&m_oBat485Info.fV1,pszBat + 12,4);
				memcpy(&m_oBat485Info.fV2,pszBat + 16,4);
				memcpy(&m_oBat485Info.fI1,pszBat + 20,4);
				memcpy(&m_oBat485Info.fI2,pszBat + 24,4);
				memcpy(&m_oBat485Info.fT1,pszBat + 28,4);
				memcpy(&m_oBat485Info.fT2,pszBat + 32,4);
				bFind485 = TRUE;
			}
		}
	}

	if(!bFind485)
	{
		g_theSttDeviceStatus->m_bPowerAC = 0;
		g_theSttDeviceStatus->m_nBatErr = 1;
		return;
	}

	if((m_oBat485Info.fV1 < 3.0) || (m_oBat485Info.fV1 > 9.0))
	{
		g_theSttDeviceStatus->m_bPowerAC = 0;
		g_theSttDeviceStatus->m_nBatErr = 1;
		return;
	}
	if((m_oBat485Info.fV2 < 3.0) || (m_oBat485Info.fV2 > 9.0))
	{
		g_theSttDeviceStatus->m_bPowerAC = 0;
		g_theSttDeviceStatus->m_nBatErr = 1;
		return;
	}

	g_theSttDeviceStatus->m_nBatErr = 0;
	if((m_oBat485Info.fI1 > 1.0) && (m_oBat485Info.fI2 > 1.0))
	{
		//电池供电
		g_theSttDeviceStatus->m_bPowerAC = 0;
	}
	else
	{
		g_theSttDeviceStatus->m_bPowerAC = 1;
	}

	if(IsLargeCurrentOutput())
	{
		//大电流输出下不更新电量
		return;
	}

	float fMin = m_oBat485Info.fV1;
	if(fMin > m_oBat485Info.fV2)
	{
		fMin = m_oBat485Info.fV2;
	}

	//计算电量，8.4伏电池
	m_oBatInfo.fVolt = fMin;

	fBatList.append(m_oBatInfo.fVolt);
	if(fBatList.count() > 3)
	{
		float fMax = 0;
		float fMin = 9.0;
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
}

BOOL CSttDeviceL336D::OnTimer(BOOL bExec)
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

void CSttDeviceL336D::Stt_Xml_Serialize_Channels(CSttXmlSerializeBase *pXmlSerialize)
{
	for(long k = 0; k < g_theSttDeviceStatus->m_nAnalogCount; k++)
	{
		stt_xml_serialize(&g_theSttDeviceStatus->m_oModule[k], k, pXmlSerialize);
	}

	if(!m_oBat485Info.bHasBat)
	{
		return;
	}

	CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize("模块", "Module", 4, "Module", stt_ParaGroupKey());

	if(pXmlModule == NULL)
	{
		return;
	}

	pXmlModule->xml_serialize("电池电压正", "BAT_V1", "", "float", m_oBat485Info.fV1);
	pXmlModule->xml_serialize("电池电压负", "BAT_V2", "", "float", m_oBat485Info.fV2);
	pXmlModule->xml_serialize("电池电流正", "BAT_I1", "", "float", m_oBat485Info.fI1);
	pXmlModule->xml_serialize("电池电流负", "BAT_I2", "", "float", m_oBat485Info.fI2);
	pXmlModule->xml_serialize("电池组温度1", "BAT_Temp1", "deg", "float", m_oBat485Info.fT1);
	pXmlModule->xml_serialize("电池组温度2", "BAT_Temp2", "deg", "float", m_oBat485Info.fT2);
}
