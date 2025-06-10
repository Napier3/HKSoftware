#include "SttDevicePTU200L.h"
#include "../Module/PowerCtrl/Volt/PTU200L/SttPowerCtrl_V270_PTU200L.h"
#include "../Module/PowerCtrl/Current/PTU200L/SttPowerCtrl_C12_5_PTU200L.h"

CSttDevicePTU200L *CSttDevicePTU200L::g_pSttDevicePTU200L=NULL;
long CSttDevicePTU200L::g_nSttDeviceRef = 0;

CSttDevicePTU200L::CSttDevicePTU200L()
{

}

CSttDevicePTU200L::~CSttDevicePTU200L()
{

}

void CSttDevicePTU200L::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDevicePTU200L=new CSttDevicePTU200L;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePTU200L;
	}
}

void CSttDevicePTU200L::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePTU200L;
		g_pSttDevicePTU200L = NULL;
	}
}

int CSttDevicePTU200L::InitDevice(BOOL bHasAdjFile)
{
	m_nCurrPowerRefVal = 178;//2.3/3.3*255
	m_nCommfd=open("/dev/SttDriver_PTU200L",O_RDWR);
	g_nStateCount = read(m_nCommfd,NULL,0x201);
	g_theDeviceSystemParameter->m_oDeviceAttrs.m_nStateCount = g_nStateCount;
	InitBuff();
    m_pDegressMsg = (Drv_DegressMsg *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
    qDebug()<<"Driver Mmap = "<<m_pDegressMsg;
#endif

    g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum = 1;
    g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[0].m_nModulePos = 3;
	g_theSystemConfig->m_nHasDigital=0;
	InitDApara(m_nCommfd,bHasAdjFile);

	return m_nCommfd;
}

void CSttDevicePTU200L::InitModulePowerCtrl()
{
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
		CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase=
					(CSttPowerCtrlBase*)(new CSttPowerCtrlV270_PTU200L);
		}
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase=
					(CSttPowerCtrlBase*)(new CSttPowerCtrlC12_5_PTU200L);
		}
	}
}

//////////////////////////////////////////////////

void CSttDevicePTU200L::SetPtValue(unsigned int nValue)
{
	ioctl(m_nCommfd,0x135,nValue);
}

int nVoltChMeasPos[6]={0,1,2,3,4,5};
int nCurrChMeasPos[6]={0,1,2,3,4,5};

void CSttDevicePTU200L::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,int nModuleType)
{
	int nItemIndex=0;
	for(unsigned int i=0;i<g_theSttDeviceStatus->m_nAnalogCount;i++)
	{
		if(g_theSttDeviceStatus->m_oModule[i].m_nModulePos==nModulePos)
		{
			nItemIndex=i;
			break;
		}
	}
	STT_MODULE_STATUS &oModuleStatus=g_theSttDeviceStatus->m_oModule[nItemIndex];

	unsigned short unmin,unMax;
	float fmin,fmax;
	float fminarry[6]={0,0,0,0,0,0};
	float fmaxarry[6]={0,0,0,0,0,0};

	for(int j=0;j<6;j++)
	{
		unmin = oDrv_FeedBack.dat[j]&0xfff;
		unMax = (oDrv_FeedBack.dat[j]>>16)&0xfff;

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

		fminarry[j]=fmin;//最小电压
		fmaxarry[j]=fmax;//最大电压
	}

	for(int j=0;j<6;j++)
	{
		if(nModulePos == 2)
		{
			oModuleStatus.m_oChannel[j].m_fVoltMax=fmaxarry[nVoltChMeasPos[j]];
			oModuleStatus.m_oChannel[j].m_fVoltMin=fminarry[nVoltChMeasPos[j]];
		}
		else
		{
			oModuleStatus.m_oChannel[j].m_fVoltMax=fmaxarry[nCurrChMeasPos[j]];
			oModuleStatus.m_oChannel[j].m_fVoltMin=fminarry[nCurrChMeasPos[j]];
		}
	}

	unsigned short voltdc=0;
    if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		voltdc = (oDrv_FeedBack.dat[6]>>16)&0xfff;//电源电压
		oModuleStatus.m_fVoltDc[0]=translateVoltBase(voltdc,15*1.07);
		voltdc =  oDrv_FeedBack.dat[6]&0xfff;
		oModuleStatus.m_fVoltDc[1]=translateVoltBase(voltdc,15*1.07);

		voltdc = (oDrv_FeedBack.dat[7]>>16)&0xfff;
		oModuleStatus.m_fVoltDc[2]=translateVoltBase(voltdc,200*2.2);
		voltdc =  oDrv_FeedBack.dat[7]&0xfff;
		oModuleStatus.m_fVoltDc[3]=translateVoltBase(voltdc,200*2.2);
	}
	else
	{
		voltdc = (oDrv_FeedBack.dat[6]>>16)&0xfff;//电源电压
		oModuleStatus.m_fVoltDc[0]=translateVoltBase(voltdc,28);
		voltdc =  oDrv_FeedBack.dat[6]&0xfff;
		oModuleStatus.m_fVoltDc[1]=translateVoltBase(voltdc,28);

		voltdc = (oDrv_FeedBack.dat[7]>>16)&0xfff;
		oModuleStatus.m_fVoltDc[2]=translateVoltBase(voltdc,25*1.1);
		voltdc =  oDrv_FeedBack.dat[7]&0xfff;
		oModuleStatus.m_fVoltDc[3]=translateVoltBase(voltdc,25*1.1);
	}

	unsigned short tempMax = 0;
	int temp = oDrv_FeedBack.dat[9]&0xffff0000;
	temp = temp>>16;
	temp  = temp*0.0625;
	oModuleStatus.m_nTemp[0]=temp;
	if(temp > 0 && tempMax < temp)
	{
		tempMax = temp;
	}

	temp = oDrv_FeedBack.dat[9]<<16;
	temp = temp>>16;
	temp  = temp*0.0625;
	oModuleStatus.m_nTemp[1]=temp;
	if(temp > 0 && tempMax < temp)
	{
		tempMax = temp;
	}

	temp = oDrv_FeedBack.dat[10]&0xffff0000;
	temp = temp>>16;
	temp  = temp*0.0625;
	oModuleStatus.m_nTemp[2]=temp;
	if(temp > 0 && tempMax < temp)
	{
		tempMax = temp;
	}

    if(nModuleType == STT_MODULE_TYPE_CURRENT)
	{
		if(tempMax >= 0 && tempMax < 100)
		{
			if(tempMax>75)
			{
				g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[0].m_nIPowerMode=STT_CurrentMODULE_POWER_LOW;
				SetSystemConfig();
				CSttDeviceBase::g_pSttDeviceBase->InitDAData();
				CSttDeviceBase::g_pSttDeviceBase->WriteDApara(&m_oDAPara);
			}

			if(tempMax>84)
			{
				if(m_nModuleHotCnt > 5)
				{
					g_theSttDeviceStatus->m_bNeedStop=TRUE;
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("ModulePos=%d,MaxTemperature > 84"),nModulePos);
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
	float fOverLoad[6] = {0, 0, 0, 0, 0, 0};
	for(int j = 1; j < 7; j++)
	{
		fOverLoad[j - 1] = (~(oDrv_FeedBack.dat[10] >> j)) & 0x1;
	}
	unsigned int nChMeasPos;
	for(int j = 0; j < 6; j++)
	{
		if(nModuleType == STT_MODULE_TYPE_VOLT)
		{
			nChMeasPos = nVoltChMeasPos[j];
		}
		else
		{
			nChMeasPos = nCurrChMeasPos[j];
		}
		oModuleStatus.m_oChannel[j].m_bIsOverLoad = fOverLoad[nChMeasPos]; //过载
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

void CSttDevicePTU200L::ProStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_StatePara  &oTmt_FirstState)
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
