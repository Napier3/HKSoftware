#include "SttDevicel336D.h"
#include "../../Engine/SttServerTestCtrlCntr.h"

CSttDeviceL336D *CSttDeviceL336D::g_pSttDeviceL336D = NULL;
long CSttDeviceL336D::g_nSttDeviceRef = 0;

CSttDeviceL336D::CSttDeviceL336D()
{
	//主板ST口模式设置，L336D默认RX1是B码
	//00-None 01:FT3 10:PPS  11:BCode
	m_nMainSTMode = 0b1011;
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
	m_nCurrPowerRefVal = 178;//2.3/3.3*255
	m_nCommfd = open("/dev/SttDriver_PN466", O_RDWR);
	g_nStateCount = read(m_nCommfd,NULL,0x201);
	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nStateCount = g_nStateCount;
	InitBuff();
	m_pDegressMsg = (Drv_DegressMsg *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
	qDebug() << "Driver Mmap = " << m_pDegressMsg;
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

		if(pCSttPowerCtrlBase == NULL)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlV130_PN);
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

		if(pCSttPowerCtrlBase == NULL)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase = (CSttPowerCtrlBase *)(new CSttPowerCtrlC12_5);
		}

		pModule->m_oModuleAttr.m_nChMergeMode = 2;//6I并3I，需要手动外部并线
	}

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
			pModule->m_oModuleAttr.m_nFiberPortNum_STRecv = 2;
		}
	}

	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nSTModeSet = 1;
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
			}

			if(pChUdcAdj->m_oChGearAdj[j].m_oAdjItem.m_fCoef < 0.01)
			{
				fUdcMin = pChUdcAdj->m_oChGearAdj[j].m_fGearValue;
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

		float fValue = (fUdc * fCoef + fZero) * 0.014778 - 1.3854;
		fValue = fValue / 3.3;

		if(fValue > 0.999999)
		{
			fValue = 0.999999;
		}

		nDA = 0xFFF * fValue;
	}

	nValue = nEnable << 24;
	nValue += nDA << 12;
	return nValue;
}

void CSttDeviceL336D::SetAuxDcVolt(float fUdc)
{
	if(g_theDeviceSystemParameter->m_nModuleCount_U == 0)
	{
		return;
	}

	long nValue = TransAuxDcVolt(fUdc);
	BOOL bAuxDcOutput = FALSE;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[0];

	if(pModule != NULL)
	{
		long nModuleIndex = pModule->m_oModuleAttr.m_nModuleIndex;
		nValue |= ModuleIndexTransToDrv(nModuleIndex);
		CSttPowerCtrlBase *pPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

		if(pPowerCtrlBase != NULL)
		{
			pPowerCtrlBase->SetVoltDA_State();
			m_oDAPara.nvolt[0] = pPowerCtrlBase->GetModuleDA();
			bAuxDcOutput = TRUE;
		}
	}

	if(bAuxDcOutput)
	{
		//CURRENT
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[0];

		if(pModule != NULL)
		{
			m_oDAPara.nmodule[1] =
				ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
			unsigned char nByte = m_nCurrPowerRefVal;
			m_oDAPara.nvolt[1] = ((unsigned int)nByte) << (1 * 8);
		}

		WriteDApara(&m_oDAPara);
		ioctl(m_nfd, 0x10f, nValue);
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

		oDAPara.nvolt[nIndex] = m_oDAPara.nvolt[nIndex];
		unsigned char nCode = (oDAPara.nvolt[nIndex] >> 8) & 0xFF;

		if(nCode < m_nVoltPowerRefVal)
		{
			oDAPara.nvolt[nIndex] = m_oDAPara.nvolt[nIndex] & 0xFF;
			oDAPara.nvolt[nIndex] |= m_nVoltPowerRefVal << 8;
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
				//                SetCurrentDApara_DC(fIsum,nIndex);
				unsigned char nByte = 0.7 / 3.3 * 255;
				m_oDAPara.nvolt[nModuleIndex] = ((unsigned int)nByte) << (1 * 8);
			}
			else
			{
				SetCurrentDApara_AC(fIsum, nIndex, fIMax);
				oDAPara.nvolt[nModuleIndex] = m_oDAPara.nvolt[nModuleIndex];
				unsigned char nCode = (oDAPara.nvolt[nModuleIndex] >> 8) & 0xFF;
//                if(fIMax < 1)
//                {
//                    if(nCode < m_nCurrPowerRefVal)
//                    {
//                        oDAPara.nvolt[nModuleIndex] = m_oDAPara.nvolt[nModuleIndex]&0xFF;
//                        oDAPara.nvolt[nModuleIndex] |= m_nCurrPowerRefVal<<8;

//                        m_oDAPara.nvolt[nModuleIndex] = oDAPara.nvolt[nModuleIndex];
//                    }
//                }

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
				fVsum = pModule->m_oModuleAttr.m_fChDcMax;
			}
			else
			{
				fVsum = pModule->m_oModuleAttr.m_fChMax;
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

			if(bDC)
			{
				unsigned char nByte = 0.7 / 3.3 * 255;
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
	}

	WriteDApara(&m_oDAPara);
}

void CSttDeviceL336D::ProStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_StatePara  &oTmt_FirstState)
{
	float fIMax_ForDa = 0;

	for(int j = 0; j < 6; j++)
	{
		if(oTmt_FirstState.m_uiCUR[j].Harm[1].fAmp > fIMax_ForDa)
		{
			fIMax_ForDa = oTmt_FirstState.m_uiCUR[j].Harm[1].fAmp;
		}
	}

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

		CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(pModule->m_oModuleAttr.m_fChMax, fAuxMax, nIndex, FALSE);
		pDAPara->nvolt[nIndex] = pDevBaseDAPara->nvolt[nIndex];
		pDAParaForState2->nvolt[nIndex] = pDevBaseDAPara->nvolt[nIndex];
		unsigned char nCode = (pDAPara->nvolt[nIndex] >> 8) & 0xFF;
		unsigned char nRef = CSttDeviceBase::g_pSttDeviceBase->m_nVoltPowerRefVal;

		if(nCode < nRef)
		{
			pDAPara->nvolt[nIndex] = pDevBaseDAPara->nvolt[nIndex] & 0xFF;
			pDAPara->nvolt[nIndex] |= nRef << 8;
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
			unsigned char nCode = (pDAPara->nvolt[nModuleIndex] >> 8) & 0xFF;
			unsigned char nRef = CSttDeviceBase::g_pSttDeviceBase->m_nCurrPowerRefVal;

			if(nCode < nRef)
			{
				pDAPara->nvolt[nModuleIndex] = pDevBaseDAPara->nvolt[nModuleIndex] & 0xFF;
				pDAPara->nvolt[nModuleIndex] |= nRef << 8;
			}

			if(fIMax_ForDa < 1)
			{
				pDevBaseDAPara->nvolt[nModuleIndex] = pDAPara->nvolt[nModuleIndex];
			}
		}
	}
}

void CSttDeviceL336D::SetPeripheral()
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
	ioctl(m_nTouchfd, 0x7000002c, nValue);
	m_nMainSTMode |= 0x3;//固定1口是B码
	ioctl(m_nfd, 0x102, m_nMainSTMode); //00-None 01:FT3 10:PPS 11:BCode
}
