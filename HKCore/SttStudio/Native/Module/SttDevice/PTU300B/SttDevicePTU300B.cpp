#include "SttDevicePTU300B.h"
#include "../../Engine/SttServerTestCtrlCntr.h"
#include "../../SttTest/Common/SttAdjust_ModuleOutput.h"
#include "../Module/PowerCtrl/SttPowerCtrlCom.h"


CSttDevicePTU300B *CSttDevicePTU300B::g_pSttDevicePTU300B=NULL;
long CSttDevicePTU300B::g_nSttDeviceRef = 0;

CSttDevicePTU300B::CSttDevicePTU300B()
{

}

void CSttDevicePTU300B::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDevicePTU300B=new CSttDevicePTU300B;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePTU300B;
	}
}

void CSttDevicePTU300B::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePTU300B;
		g_pSttDevicePTU300B = NULL;
	}
}

int CSttDevicePTU300B::InitDevice()
{
	m_nCommfd=open("/dev/SttDriver_PTU",O_RDWR);
	//	ioctl(m_nCommfd,0x114,0xff0000);//含小信号档位
	//	ioctl(m_nCommfd,0x104,4);//采集档位固定100
	ioctl(m_nCommfd,0x105,0x80);//电压电流档位

	g_nmaplen = 0x70005074 - 0x70004010;
	g_start = (unsigned int *)mmap(NULL, g_nmaplen, PROT_WRITE, MAP_SHARED, m_nCommfd, 0);

	InitDApara(m_nCommfd);

	CSttPowerCtrlBase *pCSttPowerCtrlBase=NULL;
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		pCSttPowerCtrlBase=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
		{
			g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase *)(new CSttPowerCtrlV264(FALSE));
		}
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		pCSttPowerCtrlBase=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
		{
			g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase *)(new CSttPowerCtrlC20(FALSE));
		}
	}

	return m_nCommfd;
}

//manu
void CSttDevicePTU300B::tmt_to_drv_manu(tmt_ManualTest *pTmt)
{
	char *pszBuf=stt_test_get_global_buff();
	structACPara *pstACpara=(structACPara *)pszBuf;
	memset(pstACpara,0,sizeof(structACPara));

	float fSampleFre=0;
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre>0)
		fSampleFre=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	else
		fSampleFre=50;

	pstACpara->sample = 40000/fSampleFre;//每周波800点
	pTmt->m_oManuParas.m_bDC=FALSE;

	//DA
	float fDAValue=0;
	InitDAData();

	int nModuleCount=0;
	//VOLT
	if(g_theDeviceSystemParameter->m_nModuleCount_U>0)
	{
		if(g_theDeviceSystemParameter->m_oModules_U[0]!=NULL)
		{
			pstACpara->waveCount[nModuleCount] = 24;
			pstACpara->stAlg[nModuleCount].module=g_theDeviceSystemParameter->m_oModules_U[0]->m_oModuleAttr.m_nModuleIndex-1;

			tmt_to_drv_manual_volt(pTmt->m_oManuParas.m_uiVOL,pstACpara->stAlg[nModuleCount].dat,1,0,pTmt->m_oManuParas.m_bDC);

			float fAmp;
			for(int k=0;k<CHANNEL_MAX;k++)
			{
				fAmp=fabs(pTmt->m_oManuParas.m_uiVOL[k].Harm[1].fAmp);
				if(fDAValue<fAmp)
					fDAValue=fAmp;
			}

			SetVoltDApara(fDAValue,0);
			nModuleCount++;
		}
	}

	//PTU300B
	//CURRENT
	if(g_theDeviceSystemParameter->m_nModuleCount_I>0)
	{
		float fISum=0;
		float fIMax=0;
		tmt_channel uiCUR[MAX_CURRENT_COUNT];

		BOOL IsMultiCurrentMode=FALSE;
		if(g_theDeviceSystemParameter->m_nModuleCount_I>1)
		{
			for(int i=0;i<CHANNEL_MAX;i++)
			{
				if(pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp>12.5)
				{
					IsMultiCurrentMode=TRUE;
					break;
				}
			}
		}

		if(IsMultiCurrentMode)
		{
			float fTemp;
			for(int i=0;i<CHANNEL_MAX;i++)
			{
				uiCUR[i].Harm[0].fAmp=0;
				uiCUR[i].Harm[1].fAmp=0;
				uiCUR[i].Harm[1].fAngle=pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAngle;
				uiCUR[i].Harm[1].fFreq=pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fFreq;

				if(pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp>12.5)
				{
					fTemp=pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;
					fTemp=fTemp*0.5;
					pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp=fTemp;

					uiCUR[i].Harm[1].fAmp=fTemp;
				}

				if(fIMax<pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp)
					fIMax=pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;

				fISum+=pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;
			}
		}
		else
		{
			for(int i=0;i<CHANNEL_MAX;i++)
			{
				if(fIMax<pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp)
					fIMax=pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;

				fISum+=pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;
			}

			for(int i=0;i<MAX_CURRENT_COUNT;i++)
			{
				uiCUR[i].Harm[0].fAmp=0;
				for(int j=1;j<MAX_HARM_COUNT;j++)
				{
					uiCUR[i].Harm[j].fAmp=0;
					uiCUR[i].Harm[j].fAngle=0;
					uiCUR[i].Harm[j].fFreq=50;
				}
			}

		}

		if(g_theDeviceSystemParameter->m_oModules_I[0]!=NULL)
		{
			pstACpara->stAlg[nModuleCount].module = g_theDeviceSystemParameter->m_oModules_I[0]->m_oModuleAttr.m_nModuleIndex-1;
			pstACpara->waveCount[nModuleCount] = 24;
			tmt_to_drv_manual_current(pTmt->m_oManuParas.m_uiCUR,pstACpara->stAlg[nModuleCount].dat,1,0,pTmt->m_oManuParas.m_bDC);
			nModuleCount++;
		}

		if(g_theDeviceSystemParameter->m_oModules_I[1]!=NULL)
		{
			pstACpara->stAlg[nModuleCount].module = g_theDeviceSystemParameter->m_oModules_I[1]->m_oModuleAttr.m_nModuleIndex-1;
			pstACpara->waveCount[nModuleCount] = 24;
			tmt_to_drv_manual_current(uiCUR,pstACpara->stAlg[nModuleCount].dat,1,1,pTmt->m_oManuParas.m_bDC);
			nModuleCount++;
		}

		if(pTmt->m_oManuParas.m_bDC)
		{
			SetCurrentDApara_DC(fISum,0);
			SetCurrentDApara_DC(fISum,1);
		}
		else
		{
			SetCurrentDApara_AC(fISum,0,fIMax);
			SetCurrentDApara_AC(fISum,1,fIMax);
		}
	}

	pstACpara->moduleCount=nModuleCount;

	int nOverload=pTmt->m_oManuParas.m_fOverloadDelaytime*10000000*5;//DelayOverload
	ioctl(m_nCommfd,0x112,nOverload);

	int nBo=0;
	for (int i=0; i<8; i++)//bo
	{
		nBo += pTmt->m_oManuParas.m_binOut[i].nState<<i;
	}
	ioctl(m_nCommfd,0x107,nBo);

	WriteDApara();

	ioctl(m_nCommfd,0x300,0);
	write(m_nCommfd,pszBuf,sizeof(structACPara));
}

void HarmParaPrePro(tmt_HarmTest *pTmt,tmt_channel *pCurrent1,tmt_channel *pCurrent2)
{
	//以第一个电流模块pCurrent1为主要输出
	BOOL IsMultiCurrentMode=FALSE;
	if(g_theDeviceSystemParameter->m_nModuleCount_I>1)
	{
		for(int i=0;i<CHANNEL_MAX;i++)
		{
			if(pTmt->m_oHarmParas.m_uiCUR[i].Harm[1].fAmp>5)
			{
				IsMultiCurrentMode=TRUE;
				break;
			}
		}
	}

	if(IsMultiCurrentMode)
	{
		float fTemp;
		for(int i=0;i<CHANNEL_MAX;i++)
		{
			pCurrent2[i].Harm[0].fAmp=0;

			BOOL bChannelMulti=FALSE;
			if(pTmt->m_oHarmParas.m_uiCUR[i].Harm[1].fAmp>5)
				bChannelMulti=TRUE;

			for(int j=1;j<MAX_HARM_COUNT;j++)
			{
				pCurrent1[i].Harm[j].fAmp=pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fAmp;
				pCurrent1[i].Harm[j].fAngle=pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fAngle;
				pCurrent1[i].Harm[j].fFreq=pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fFreq;

				pCurrent2[i].Harm[j].fAmp=0;
				pCurrent2[i].Harm[j].fAngle=pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fAngle;
				pCurrent2[i].Harm[j].fFreq=pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fFreq;

				if(bChannelMulti)
				{
					fTemp=pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fAmp;
					fTemp=fTemp*0.5;
					pCurrent1[i].Harm[j].fAmp=fTemp;
					pCurrent2[i].Harm[j].fAmp=fTemp;
				}
			}
		}
	}
	else
	{
		for(int i=0;i<MAX_CURRENT_COUNT;i++)
		{
			pCurrent2[i].Harm[0].fAmp=0;
			for(int j=1;j<MAX_HARM_COUNT;j++)
			{
				pCurrent2[i].Harm[j].fAmp=0;
				pCurrent2[i].Harm[j].fAngle=0;
				pCurrent2[i].Harm[j].fFreq=50;
			}
		}
	}

}

BOOL CSttDevicePTU300B::CheckHarmTestPara(tmt_HarmTest *pTmt)
{
	//1.谐波总含量及加权含量不超限
	//2.波形最大值不超功放最大输出点
	float fVoltChannelMax[MAX_VOLTAGE_COUNT];
	float fCurrentChannelMax[MAX_CURRENT_COUNT];

	int nVoltChannelNum=0;
	int nCurrentChannelNum=0;

	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		nVoltChannelNum+=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_nChannelNum;
	}
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		nCurrentChannelNum+=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_nChannelNum;
		break;
	}

	for(int nChannelIndex=0;nChannelIndex<nVoltChannelNum;nChannelIndex++)
	{
		if(!GetChannelContentOK(pTmt->m_oHarmParas.m_uiVOL[nChannelIndex],STT_MODULE_TYPE_VOLT))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("VoltChannel[%d] ContentOver"),
									   nChannelIndex);
			return FALSE;
		}

		fVoltChannelMax[nChannelIndex]=GetChannelMax(pTmt->m_oHarmParas.m_uiVOL[nChannelIndex],
													 pTmt->m_oHarmParas.m_fBaseFre);

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("VoltChannel[%d] Max=%.3f"),
								   nChannelIndex,fVoltChannelMax[nChannelIndex]);
	}

	tmt_channel uiCUR1[MAX_CURRENT_COUNT];
	tmt_channel uiCUR2[MAX_CURRENT_COUNT];
	HarmParaPrePro(pTmt,uiCUR1,uiCUR2);
	for(int nChannelIndex=0;nChannelIndex<nCurrentChannelNum;nChannelIndex++)
	{
		if(!GetChannelContentOK(uiCUR1[nChannelIndex],STT_MODULE_TYPE_CURRENT))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("CurrentChannel[%d] ContentOver"),
									   nChannelIndex);
			return FALSE;
		}

		fCurrentChannelMax[nChannelIndex]=GetChannelMax(uiCUR1[nChannelIndex],
														pTmt->m_oHarmParas.m_fBaseFre);

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("CurrentChannel[%d] Max=%.3f"),
								   nChannelIndex,fCurrentChannelMax[nChannelIndex]);
	}

	if(nVoltChannelNum>0)
	{
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
		{
			if(g_theDeviceSystemParameter->m_oModules_U[nIndex]==NULL)
				continue;

			if(g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_pPowerCtrlBase==NULL)
				continue;

			if(!CheckModuleChannel(fVoltChannelMax,g_theDeviceSystemParameter->m_oModules_U[nIndex]))
				return FALSE;
		}
	}

	if(nCurrentChannelNum>0)
	{
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
		{
			if(g_theDeviceSystemParameter->m_oModules_I[nIndex]==NULL)
				continue;

			if(g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_pPowerCtrlBase==NULL)
				continue;

			if(!CheckModuleChannel(fCurrentChannelMax,g_theDeviceSystemParameter->m_oModules_I[nIndex]))
				return FALSE;
		}
	}

	return TRUE;
}

//harm
void CSttDevicePTU300B::tmt_to_drv_harm(tmt_HarmTest *pTmt)
{
	char *pszBuf=stt_test_get_global_buff();
	structACPara *pstACpara=(structACPara *)pszBuf;
	memset(pstACpara,0,sizeof(structACPara));

	float fSampleFre=0;
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre>0)
		fSampleFre=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	else
		fSampleFre=50;

	pstACpara->sample = 40000/fSampleFre;//每周波800点

	//DA
	InitDAData();

	int nModuleCount=0;
	//VOLT
	if(g_theDeviceSystemParameter->m_nModuleCount_U>0)
	{
		if(g_theDeviceSystemParameter->m_oModules_U[0]!=NULL)
		{
			pstACpara->waveCount[nModuleCount] = 6+3*6*31;
			pstACpara->stAlg[nModuleCount].module=g_theDeviceSystemParameter->m_oModules_U[0]->m_oModuleAttr.m_nModuleIndex-1;

			tmt_to_drv_manual_volt(pTmt->m_oHarmParas.m_uiVOL,pstACpara->stAlg[nModuleCount].dat,31,0);

			SetVoltDApara(270,0);
			nModuleCount++;
		}
	}

	float fIDAValue;
	int nModuleIndex;
	uchar nByte;
	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		if(g_theDeviceSystemParameter->m_oModules_I[nIndex]==NULL)
			continue;

		fIDAValue=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_pPowerCtrlBase->GetCurrentDA_State();
		nByte = fIDAValue/3.3*255;
		nModuleIndex=nIndex+g_theDeviceSystemParameter->m_nModuleCount_U;
		CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nModuleIndex] |= ((uint)nByte)<<(1*8);
	}

	//CURRENT
	if(g_theDeviceSystemParameter->m_nModuleCount_I>0)
	{
		tmt_channel uiCUR1[MAX_CURRENT_COUNT];
		tmt_channel uiCUR2[MAX_CURRENT_COUNT];

		HarmParaPrePro(pTmt,uiCUR1,uiCUR2);
		if(g_theDeviceSystemParameter->m_oModules_I[0]!=NULL)
		{
			pstACpara->stAlg[nModuleCount].module = g_theDeviceSystemParameter->m_oModules_I[0]->m_oModuleAttr.m_nModuleIndex-1;
			pstACpara->waveCount[nModuleCount] = 6+3*6*31;
			tmt_to_drv_manual_current(uiCUR1,pstACpara->stAlg[nModuleCount].dat,31,0);
			nModuleCount++;
		}

		if(g_theDeviceSystemParameter->m_oModules_I[1]!=NULL)
		{
			pstACpara->stAlg[nModuleCount].module = g_theDeviceSystemParameter->m_oModules_I[1]->m_oModuleAttr.m_nModuleIndex-1;
			pstACpara->waveCount[nModuleCount] = 6+3*6*31;
			tmt_to_drv_manual_current(uiCUR2,pstACpara->stAlg[nModuleCount].dat,31,1);
			nModuleCount++;
		}
	}

	pstACpara->moduleCount=nModuleCount;

	int nBo=0;
	for (int i=0; i<8; i++)//bo
	{
		nBo += pTmt->m_oHarmParas.m_oBinaryConfig.m_binOut[i].nState<<i;
	}
	ioctl(m_nCommfd,0x107,nBo);

	WriteDApara();

	ioctl(m_nCommfd,0x300,0);
	write(m_nCommfd,pszBuf,sizeof(structACPara));
}

//state
void CSttDevicePTU300B::tmt_to_drv_StatePara(tmt_StateTest *pTmt)
{
	int nModuleIndex;
	uchar nByte;
	CSttDeviceBase::g_pSttDeviceBase->InitDAData();
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		if(g_theDeviceSystemParameter->m_oModules_U[nIndex]==NULL)
			continue;

		CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(270,nIndex);
	}

	float fIDAValue;
	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		if(g_theDeviceSystemParameter->m_oModules_I[nIndex]==NULL)
			continue;

		fIDAValue=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_pPowerCtrlBase->GetCurrentDA_State();
		nByte = fIDAValue/3.3*255;
		nModuleIndex=nIndex+g_theDeviceSystemParameter->m_nModuleCount_U;
		CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nModuleIndex] |= ((uint)nByte)<<(1*8);
	}

	tmt_StatePara oTmt_paraState;

	char* pBuff=stt_test_get_global_buff();
	structStateParam *statepara=(structStateParam *)pBuff;
	memset(statepara,0,sizeof(structStateParam));

	if(pTmt->m_oStateParas.m_bRepeat)
		statepara->isLoop = pTmt->m_oStateParas.m_nRepeatNumbers;
	else
		statepara->isLoop = 0;

	int nModuleCnt=0;
	structState state;
	BOOL IsMultiCurrentMode;
	for(int j=0;j<pTmt->m_oStateParas.m_nStateNumbers;j++)
	{
		oTmt_paraState =pTmt->m_oStateParas.m_paraState[j];
		memset(&state,0,sizeof(structState));
		state.state = statepara->stateCount;

		nModuleCnt=0;
		//Volt
		if(g_theDeviceSystemParameter->m_nModuleCount_U>0)
		{
			if(g_theDeviceSystemParameter->m_oModules_U[0]!=NULL)
			{
				state.dat[nModuleCnt].module=g_theDeviceSystemParameter->m_oModules_U[0]->m_oModuleAttr.m_nModuleIndex-1;
				tmt_to_drv_manual_volt(oTmt_paraState.m_uiVOL,state.dat[nModuleCnt].dat,1,0,oTmt_paraState.m_bDC);
				state.dat[nModuleCnt].cnt=24;
				nModuleCnt++;
			}
		}

		//Current
		if(g_theDeviceSystemParameter->m_nModuleCount_I>0)
		{
			tmt_channel uiCUR[MAX_CURRENT_COUNT];

			IsMultiCurrentMode=FALSE;
			if(g_theDeviceSystemParameter->m_nModuleCount_I>1)
			{
				for(int i=0;i<CHANNEL_MAX;i++)
				{
					if(oTmt_paraState.m_uiCUR[i].Harm[1].fAmp>12.5)
					{
						IsMultiCurrentMode=TRUE;
						break;
					}
				}
			}

			if(IsMultiCurrentMode)
			{
				float fTemp;
				for(int i=0;i<CHANNEL_MAX;i++)
				{
					uiCUR[i].Harm[0].fAmp=0;
					uiCUR[i].Harm[1].fAmp=0;
					uiCUR[i].Harm[1].fAngle=oTmt_paraState.m_uiCUR[i].Harm[1].fAngle;
					uiCUR[i].Harm[1].fFreq=oTmt_paraState.m_uiCUR[i].Harm[1].fFreq;

					if(oTmt_paraState.m_uiCUR[i].Harm[1].fAmp>12.5)
					{
						fTemp=oTmt_paraState.m_uiCUR[i].Harm[1].fAmp;
						fTemp=fTemp*0.5;
						oTmt_paraState.m_uiCUR[i].Harm[1].fAmp=fTemp;

						uiCUR[i].Harm[1].fAmp=fTemp;
					}
				}
			}
			else
			{
				for(int i=0;i<MAX_CURRENT_COUNT;i++)
				{
					uiCUR[i].Harm[0].fAmp=0;
					for(int j=1;j<MAX_HARM_COUNT;j++)
					{
						uiCUR[i].Harm[j].fAmp=0;
						uiCUR[i].Harm[j].fAngle=0;
						uiCUR[i].Harm[j].fFreq=50;
					}
				}
			}

			if(g_theDeviceSystemParameter->m_oModules_I[0]!=NULL)
			{
				state.dat[nModuleCnt].module = g_theDeviceSystemParameter->m_oModules_I[0]->m_oModuleAttr.m_nModuleIndex-1;
				state.dat[nModuleCnt].cnt=24;
				tmt_to_drv_manual_current(oTmt_paraState.m_uiCUR,state.dat[nModuleCnt].dat,1,0,oTmt_paraState.m_bDC);
				nModuleCnt++;
			}

			if(g_theDeviceSystemParameter->m_oModules_I[1]!=NULL)
			{
				state.dat[nModuleCnt].module = g_theDeviceSystemParameter->m_oModules_I[1]->m_oModuleAttr.m_nModuleIndex-1;
				state.dat[nModuleCnt].cnt=24;
				tmt_to_drv_manual_current(uiCUR,state.dat[nModuleCnt].dat,1,1,oTmt_paraState.m_bDC);
				nModuleCnt++;
			}
		}

		for (int i=0; i<8; i++)//bo
		{
			state.BO += oTmt_paraState.m_binOut[i].nState<<i;
		}

		switch(oTmt_paraState.m_nTriggerCondition)
		{
		case TMT_MDSTATE_MEARSURETRIGGER:
		{
			state.trip = 0;//手动
		}
			break;
		case TMT_MDSTATE_TIMETRIGGER:
		{
			state.trip = 1;
			structTmTrip	tm;
			tm.mSec = oTmt_paraState.m_fTimeState*1000;
			state.tripData.tm = tm;
		}
			break;
		case TMT_MDSTATE_GPSBTRIGGER:
		{
			structGPSTrip 	gps;
			QDateTime datetime;
			QDate date;
			if(oTmt_paraState.m_tGps.nYear==0&&oTmt_paraState.m_tGps.nMonth==0&&oTmt_paraState.m_tGps.nDay==0)
			{
				int nSecond=g_theSttDeviceStatus->m_nUtc_s;
				datetime=QDateTime::fromTime_t(nSecond);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("Dev Hour=%d,Minute=%d,Second=%d"),
										   datetime.time().hour(),datetime.time().minute(),datetime.time().second());
			}
			else if(date.setYMD(oTmt_paraState.m_tGps.nYear,oTmt_paraState.m_tGps.nMonth,oTmt_paraState.m_tGps.nDay))
			{
				datetime.setDate(date);
			}
			else
				break;

			QTime time;
			if(time.setHMS(oTmt_paraState.m_tGps.nHour,oTmt_paraState.m_tGps.nMinutes,oTmt_paraState.m_tGps.nSeconds))
			{
				datetime.setTime(time);
				state.trip = 2;
				gps.sec = datetime.toTime_t();
				gps.nSec = oTmt_paraState.m_tGps.nMilliSeconds*1000000;
				state.tripData.gps = gps;
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("Year=%d,Month=%d,Day=%d"),
										   datetime.date().year(),datetime.date().month(),datetime.date().day());
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("TestPara Hour=%d,Minute=%d,Second=%d"),
										   datetime.time().hour(),datetime.time().minute(),datetime.time().second());

			}
		}
			break;
		case TMT_MDSTATE_BINTRIGGER:
		{
			state.trip = 3;
			structBITrip bi;
			bi.logic = 1;
			if(oTmt_paraState.m_nBinLogic==TMT_BINLOGIC_AND)
				bi.logic =0;

			for (int i=0; i<8; i++)
			{
				bi.valid |= oTmt_paraState.m_binIn[i].nSelect<<i;
			}

			bi.ref = oTmt_paraState.m_eBinReversal;
			state.tripData.bi = bi;
			state.mdelay = oTmt_paraState.m_fTimeAfterTrigger*1000;
		}
			break;
		}

		statepara->state[statepara->stateCount] = state;
		statepara->stateCount++;
	}

	statepara->moduleCount = nModuleCnt;

	ioctl(m_nCommfd,0x302,0);
	write(m_nCommfd,pBuff,sizeof(structStateParam));
}

/***
void CSttDevicePTU300B::tmt_to_drv_analog_volt(Drv_StateItem *oDrv_StateItem,tmt_StatePara  oTmt_paraState,int nModuleUIndex)
{
	if(g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]==NULL)
		return;

	structACParamItem Voltanal;
	memset(&Voltanal,0,sizeof(structACParamItem));
	Voltanal.DWCount = 24;

	int  nArrayBeginIndex=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_nArrayBeginIndex;
	int nChPos;

	float fAmp;
	long *dat=&Voltanal.nVal[0];
	if(oTmt_paraState.m_bDC)
	{
		for(int k=0; k<CHANNEL_MAX; k++)
		{
			fAmp=oTmt_paraState.m_uiVOL[k+nArrayBeginIndex].Harm[1].fAmp;
			nChPos=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_nChDrvPos[k];

			TransAnalogDCVolToDrv(fabs(fAmp),k,nModuleUIndex,dat+nChPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		for(int k=0; k<CHANNEL_MAX; k++)
		{
			fAmp=oTmt_paraState.m_uiVOL[k+nArrayBeginIndex].Harm[0].fAmp;
			nChPos=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_nChDrvPos[k];
			TransAnalogDCVolToDrv(fabs(fAmp),k,nModuleUIndex,dat+nChPos);

			oTmtHarm=&oTmt_paraState.m_uiVOL[k+nArrayBeginIndex].Harm[1];
			if(oTmtHarm->fFreq<1)
				oTmtHarm->fFreq=1;

			TransAnalogVolToDrv(fabs(oTmtHarm->fAmp),oTmtHarm->fAngle,oTmtHarm->fFreq,k,nModuleUIndex,
								dat+CHANNEL_MAX+nChPos*3);
		}
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleUIndex],&Voltanal,sizeof(structACParamItem));
}

void CSttDevicePTU300B::tmt_to_drv_analog_current(Drv_StateItem *oDrv_StateItem,tmt_StatePara  oTmt_paraState,int nModuleIIndex)
{
	if(g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]==NULL)
		return;

	structACParamItem Curanal;
	memset(&Curanal,0,sizeof(structACParamItem));
	Curanal.DWCount = 24;

	int  nArrayBeginIndex=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_nArrayBeginIndex;
	int nChPos;

	float fAmp;
	long *dat=&Curanal.nVal[0];
	if(oTmt_paraState.m_bDC)
	{
		for(int k=0; k<CHANNEL_MAX; k++)
		{
			fAmp=oTmt_paraState.m_uiCUR[k+nArrayBeginIndex].Harm[1].fAmp;
			nChPos=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		for(int k=0; k<CHANNEL_MAX; k++)
		{
			fAmp=oTmt_paraState.m_uiCUR[k+nArrayBeginIndex].Harm[0].fAmp;
			nChPos=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);
			oTmtHarm=&oTmt_paraState.m_uiCUR[k+nArrayBeginIndex].Harm[1];
			if(oTmtHarm->fFreq<1)
				oTmtHarm->fFreq=1;

			TransAnalogCurToDrv(fabs(oTmtHarm->fAmp),oTmtHarm->fAngle,oTmtHarm->fFreq,k,nModuleIIndex,
								dat+CHANNEL_MAX+nChPos*3);
		}
	}
	memcpy(&oDrv_StateItem->oAcParam.item[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U],
			&Curanal,sizeof(structACParamItem));
}

void  FpgaDirectOper::SetbinarySetting(hqyBinaryInPackage::BinaryinSetting* pSetting)
{
	hqyBinaryInPackage::BinaryInInfo* pInfo = NULL;
	if(pSetting->obinaryinfolist_size() != 10)
	{
		qDebug()<<"binaryIn count is err!";
		return;
	}
	uint nFD1 = 0;
	uint nFD2 = 0;
	long lTemp1 = 0;
	 short nthreadHold = 0;
	 short vthreadhold[10] = {0};
	unsigned long nMode = 0;
	float ftemp;
	for(int i=0;i<pSetting->obinaryinfolist_size();i++)
	{

		pInfo = pSetting->mutable_obinaryinfolist(i);
		float fThreadHold = pInfo->fthreshold();

		hqyBinaryInPackage::BinaryInFD nBDF = getBinaryInFD(fThreadHold) ;

		int nBinaryInType = pInfo->ntype();

		switch(nBinaryInType){
		case hqyBinaryInPackage::BT_EmptyMode:
		{
			nMode |= 1<<i;
			vthreadhold[i] =0x95CE;// 0xB480;0xA300
			int nBDFCode = getBinaryFDCode(hqyBinaryInPackage::BFD_B_10V);
			if(i<8)
			{
				nFD1 |= nBDFCode<<(i*4);
			}
			else
			{
				nFD2 |= nBDFCode<<((i-8)*4);
			}

			//DriverOper::IoCtrl(0x10B,0xB480);

			break;
		}
		case hqyBinaryInPackage::BT_SampleMode:
		{
			int nBDFCode = getBinaryFDCode(nBDF);
			if(i<8)
			{
				nFD1 |= nBDFCode<<(i*4);
			}
			else
			{
				nFD2 |= nBDFCode<<((i-8)*4);
			}


			switch (nBDF)
			{
			case hqyBinaryInPackage::BFD_B_600V:
			{
			   ftemp = (fThreadHold / (505.1*1.2) * 0.9995002 / 2.048)*1.814;
				break;
			}
			case hqyBinaryInPackage::BFD_B_100V:
			{
			   ftemp = (fThreadHold / (505.1*1.2) * 6.7540723 / 2.048)*1.06;
				break;
			}
			case hqyBinaryInPackage::BFD_B_10V:
			{
			   ftemp = (fThreadHold / (505.1*1.2) * 72.2891566 / 2.048)*1.171;
				break;
			}
			case hqyBinaryInPackage::BFD_B_1V:
			{
			   ftemp = (fThreadHold/ (505.1*1.2) * 666.6666667 / 2.048)*0.92;
				break;
			}
			case hqyBinaryInPackage::BFD_B_01V:
			{
				ftemp = (fThreadHold / (505.1*1.2) * 2000 / 2.048);
				break;
			}
			default:
				break;
			}

			lTemp1 = (ftemp * 32767) + 32768;
			nthreadHold = ( short)lTemp1;
			vthreadhold[i] = nthreadHold;
			break;

		}
		default:
			break;
		}

	}

	int i=0;
	unsigned short nth = vthreadhold[i++];
	unsigned short nth2 = vthreadhold[i++];

	unsigned long ns = ((nth<<16)&0xFFFF0000)|(nth2&0xFFFF);

	DriverOper::g_pDriverOper->WriteFPGAData(0x70004068,ns);

	nth = vthreadhold[i++];
	nth2 = vthreadhold[i++];
	ns = ((nth<<16)&0xFFFF0000)|(nth2&0xFFFF);

	DriverOper::g_pDriverOper->WriteFPGAData(0x7000406C,ns);

	nth = vthreadhold[i++];
	nth2 = vthreadhold[i++];
	ns = ((nth<<16)&0xFFFF0000)|(nth2&0xFFFF);

	DriverOper::g_pDriverOper->WriteFPGAData(0x70005068,ns);

	nth = vthreadhold[i++];
	nth2 = vthreadhold[i++];
	ns = ((nth<<16)&0xFFFF0000)|(nth2&0xFFFF);

	DriverOper::g_pDriverOper->WriteFPGAData(0x7000506C,ns);


	nth = vthreadhold[i++];
	nth2 = vthreadhold[i++];
	ns = ((nth<<16)&0xFFFF0000)|(nth2&0xFFFF);

	DriverOper::g_pDriverOper->WriteFPGAData(0x70005070,ns);


	//write fd
	//sample mode
	unsigned long nInputMode = 0;
	if(pSetting->binarymode() == 1) //zhangsen 20180423
		nInputMode = 0x80000000;
	nMode |= nInputMode;
	DriverOper::IoCtrl(0x108,nMode);

	//Sample gear
	DriverOper::IoCtrl(0x109,nFD1);
	DriverOper::IoCtrl(0x10A,nFD2);

	//设置防抖时间
	int nTime = pSetting->bitime();
	logcontrol::g_pLogControl->PrintLogMessage("binaryinput shake time is %d ms",nTime);
	nTime = nTime*1000000/20;
	DriverOper::IoCtrl(0x120,nTime);
}
***/
