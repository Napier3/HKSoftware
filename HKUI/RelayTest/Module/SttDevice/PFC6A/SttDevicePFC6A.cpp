#include "SttDevicePFC6A.h"
#include "../../Engine/SttServerTestCtrlCntr.h"
#include "../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>	//SIGIO
#include<sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>

CSttDevicePFC6A *CSttDevicePFC6A::g_pSttDevicePFC6A=NULL;
long CSttDevicePFC6A::g_nSttDeviceRef = 0;

CSttDevicePFC6A::CSttDevicePFC6A()
{

}

void CSttDevicePFC6A::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDevicePFC6A=new CSttDevicePFC6A;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePFC6A;
	}
}

void CSttDevicePFC6A::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePFC6A;
		g_pSttDevicePFC6A = NULL;
	}
}

int CSttDevicePFC6A::InitDevice(BOOL bHasAdjFile)
{
	m_nCommfd=open("/dev/SttDriver_Pi1000",O_RDWR);
	m_pDegressMsg = (Drv_DegressMsg *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
	qDebug()<<"Driver Mmap = "<<m_pDegressMsg;
#endif

	g_theSystemConfig->m_bSyncSecond=TRUE;//考虑PFC-6A IA 和PI1000 UA 相角同步
	g_theSystemConfig->m_nHasDigital=0;

	InitDApara(m_nCommfd,bHasAdjFile);

	CSttPowerCtrlBase *pCSttPowerCtrlBase=NULL;
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
		pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase=
					(CSttPowerCtrlBase *)(new CSttPowerCtrlV300_PI);
		}
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
		if(pModule->m_oModuleAttr.m_fChMax<50)
		{
			if(pCSttPowerCtrlBase==NULL)
			{
				pModule->m_oModuleAttr.m_pPowerCtrlBase=
						(CSttPowerCtrlBase *)(new CSttPowerCtrlC20);				
			}

			if(pModule->m_oModuleAttr.m_fChMax < 25)
			{
				pModule->m_oModuleAttr.m_pPowerCtrlBase->m_fMaxVal = 20;//20A
			}
			else
			{
				pModule->m_oModuleAttr.m_pPowerCtrlBase->m_fMaxVal = 40;//40A
			}

		}
		else
		{
			pModule->m_oModuleAttr.m_pPowerCtrlBase->m_fMaxVal = 300;//PF300
		}
	}

	return m_nCommfd;
}

//manu
void CSttDevicePFC6A::tmt_to_drv_manu(tmt_ManualTest *pTmt,BOOL bIsStartTest)
{
	char *pszDrv=stt_test_get_drvparas_buff();
	Drv_ManuData *pDrv=(Drv_ManuData *)pszDrv;
	memset(pDrv,0,sizeof(Drv_ManuData));

	float fIsum = 0;
	float fAmp=0;
	float fIMax = 0;
	long nTmtPos;

	InitDAData();
	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule==NULL)
			continue;

		fIsum = 0;
		fIMax = 0;
		for(int k=0;k<pModule->m_oModuleAttr.m_nChannelNum;k++)
		{
			nTmtPos=pModule->m_nChTmtPos[k];
			if(nTmtPos < 0)
				continue;

			fAmp = pTmt->m_oManuParas.m_uiCUR[nTmtPos].Harm[1].fAmp;
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("I[%d]Chan[%d] = %.6f"),nIndex+1,k,fAmp);

			if(pModule->m_oModuleAttr.m_fChMax<50)
			{
				fIsum+=fAmp;
				if(fIMax<fAmp)
					fIMax=fAmp;
			}
		}
		if(pModule->m_oModuleAttr.m_fChMax<50)
			SetCurrentDApara_AC(fIsum,nIndex,fIMax);
	}

	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		Manual_volt(pTmt->m_oManuParas.m_uiVOL,pszDrv,1,nIndex,pTmt->m_oManuParas.m_bDC);
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule==NULL)
			continue;

		if(pModule->m_oModuleAttr.m_fChMax<50)
			Manual_Current_PFC6A(pTmt->m_oManuParas.m_uiCUR,pszDrv,1,nIndex,pTmt->m_oManuParas.m_bDC);
		else
			Manual_Current_1000A(pTmt->m_oManuParas.m_uiCUR,pszDrv,1,nIndex,pTmt->m_oManuParas.m_bDC);
	}

	//DAPara
	float fVsum = 0;
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		if(g_theDeviceSystemParameter->m_oModules_U[nIndex]!=NULL)
		{
			m_nTmtChanNum=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_nChannelNum;
			for(int k=0;k<m_nTmtChanNum;k++)
			{
				m_nTmtPos=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_nChTmtPos[k];
				if(m_nTmtPos<0)
					continue;

				fAmp=fabs(pTmt->m_oManuParas.m_uiVOL[m_nTmtPos].Harm[1].fAmp);
				if(fVsum<fAmp)
					fVsum=fAmp;
			}

			if(pTmt->m_oManuParas.m_bDC)
				fVsum/=1.414;

			SetVoltDApara(fVsum,nIndex);
		}
	}

	WriteDApara();

	for (int i=0; i<8; i++)//bo
	{
		pDrv->oDrvComBoSta.item[0].nVal1 += ((!pTmt->m_oManuParas.m_binOut[i].nState)<<i);
	}

	ioctl(m_nCommfd,0x300,0);
	write(m_nCommfd,pszDrv,sizeof(Drv_ManuData));
}

void CSttDevicePFC6A::Manual_Current_PFC6A(tmt_channel *pTmt_channel,char *pszDrv,int nHarm,int nModuleIIndex,BOOL bIsDc,BOOL bIsModuleOutPut)
{
	Drv_ManuData *pDrv=(Drv_ManuData *)pszDrv;
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
	if(pModule==NULL)
		return;

	int nChPos;
	float fAmp=0;
	long nTmtPos;

	long *dat=&pDrv->oDrv_HarmParam[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U].dat[0];
	if(bIsDc)
	{
		for(int k=0; k<pModule->m_oModuleAttr.m_nChannelNum; k++)
		{
			if(bIsModuleOutPut)
			{
				nTmtPos = k;
			}
			else
			{
				nTmtPos=pModule->m_nChTmtPos[k];
				if(nTmtPos < 0)
					continue;
			}

			fAmp=pTmt_channel[nTmtPos].Harm[1].fAmp;
			nChPos=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);
		}
		pDrv->oDrv_HarmParam[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U].nDWcnt=24;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		for(int k=0; k<pModule->m_oModuleAttr.m_nChannelNum; k++)
		{
			if(bIsModuleOutPut)
			{
				nTmtPos = k;
			}
			else
			{
				nTmtPos=pModule->m_nChTmtPos[k];
				if(nTmtPos < 0)
					continue;
			}

			fAmp=pTmt_channel[nTmtPos].Harm[0].fAmp;
			nChPos=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);

			for(int m=0;m<nHarm;m++)
			{
				oTmtHarm=&pTmt_channel[nTmtPos].Harm[m+1];
				if(oTmtHarm->fFreq<1)
				{
					oTmtHarm->fFreq=1;
				}

				TransAnalogCurToDrv(fabs(oTmtHarm->fAmp),oTmtHarm->fAngle,oTmtHarm->fFreq,k,nModuleIIndex,
									dat+CHANNEL_MAX+nChPos*3+m*3*CHANNEL_MAX);
			}
		}
		pDrv->oDrv_HarmParam[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U].nDWcnt=6+nHarm*3*CHANNEL_MAX;
	}
}

void CSttDevicePFC6A::Manual_Current_1000A(tmt_channel *pTmt_channel,char *pszDrv,int nHarm,int nModuleIIndex,BOOL bIsDc,BOOL bIsModuleOutPut)
{
	//IA IB IC
	Drv_ManuData *pDrv=(Drv_ManuData *)pszDrv;
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
	if(pModule==NULL)
		return;

	int nChPos;
	float fAmp=0;
	int nRetTap = 0;
	long nTmtPos;

	long *dat=&pDrv->oDrv_HarmParam[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U].dat[0];
	if(bIsDc)
	{
		for(int k=0; k<3; k++)
		{
			fAmp=pTmt_channel[k].Harm[1].fAmp;
			nChPos=k+3;

			//			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);
		}
		pDrv->oDrv_HarmParam[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U].nDWcnt=24;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		for(int k=0; k<3; k++)
		{
			if(bIsModuleOutPut)
			{
				nTmtPos = k;
			}
			else
			{
				nTmtPos=pModule->m_nChTmtPos[k];
			}

			if(nTmtPos < 0)
			{
				fAmp=0;
			}
			else
				fAmp=pTmt_channel[nTmtPos].Harm[0].fAmp;

			nChPos=k+3;

			//			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);

			for(int m=0;m<nHarm;m++)
			{
				if(nTmtPos < 0)
				{
					oTmtHarm->fAmp=0;
				}
				else
					oTmtHarm=&pTmt_channel[nTmtPos].Harm[m+1];

				if(oTmtHarm->fAmp < 0.001)
				{
					if(m ==0 )
						oTmtHarm->fFreq= 50;
					else
					{
						oTmtHarm->fFreq= 50*(1+m);
					}
				}

				TransAnalogCurToDrv_1000A(fabs(oTmtHarm->fAmp),oTmtHarm->fAngle,oTmtHarm->fFreq,k,nModuleIIndex,
										  dat+CHANNEL_MAX+nChPos*3+m*3*CHANNEL_MAX);
			}
			//0-200 200-400 400-1000
			int nHGearID=stt_adj_get_ac_HGearID(pTmt_channel[nTmtPos].Harm[1].fAmp,pModule);
			nHGearID++;
			nRetTap |= (nHGearID<<k*2);
		}
		pDrv->oDrv_HarmParam[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U].nDWcnt=6+nHarm*3*CHANNEL_MAX;
	}

	ioctl(m_nCommfd,0x70006014,nRetTap);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("nRetTap=%d"),nRetTap);
	Sleep(1500);
}

void CSttDevicePFC6A::TransAnalogCurToDrv_1000A(float fAmp,float fAng,float fFre,int nChannel,int nModuleIIndex,long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
	if(pModule==NULL)
		return;

	int nHarm=0;
	int m_nEDFre=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	if(m_nEDFre<0.001)
		m_nEDFre=50;

	if(fFre<=m_nEDFre)
	{
		nHarm = 0;//0:基波
	}
	else
	{
		nHarm  = (fFre+25)/m_nEDFre - 1;
	}

	float fTemperature=0;//getTemperature();
	float faddPh = 0;
	PSTT_ADJUST_ITEM pAdjItem = stt_adj_get_ac(fAmp,pModule,nChannel,fTemperature);//0:DC,1:基波
	if(pAdjItem!=NULL&&nHarm == 0)
		faddPh = pAdjItem->m_fAngle;
	fAng -= faddPh*(nHarm+1);
	fAng+=180;

	while((fAng>360)||(fAng<0))
	{
		if(fAng>360)
		{
			fAng-=360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng*65536/360;
	nPh = nPh<<16;

	pnDrvData[0] = nPh;
	pnDrvData[1] = TranslateACFre(fFre);
	pnDrvData[2] = TranslateACCurrentAmp_1000A(fAmp,nChannel,nModuleIIndex,nHarm+1);
}

long CSttDevicePFC6A::TranslateACCurrentAmp_1000A(float fAmp,int nChannel,int nModuleIIndex,int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
	if(pModule==NULL)
		return 0;

	float fChMax=pModule->m_oModuleAttr.m_fChMax;
	if(fAmp>fChMax)
		fAmp=fChMax;

	float fCurrentMax=0;

	//0-200,200-400,400-1000
	fCurrentMax = stt_adj_get_ac_max(fAmp,pModule);
	fCurrentMax=fCurrentMax*1.414;

	if(fCurrentMax<0.001)
	{
		return 0;
	}

	float fTemperature=0;//getTemperature();
	float fCoef=1;//幅值系数
	float fZero=0;//交流零漂

	PSTT_ADJUST_ITEM pAdjItem=stt_adj_get_ac(fAmp,pModule,nChannel,fTemperature,1);//只取基波系数
	if(pAdjItem!=NULL)
	{
		fCoef=pAdjItem->m_fCoef;
		fZero=pAdjItem->m_fZero;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Current_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);

	//保证PF300等大功率放大器过零点
	if(fAmp > EPSINON)
	{
		fAmp =fAmp*fCoef;
		fAmp += fZero;
	}
	if(fAmp < EPSINON)
		fAmp=0;

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("PFC-6A Ichannel[%d].Harm[%d].famp=%.3f"),nChannel,fAmp,nHarm);

	long nH = fAmp*65536/fCurrentMax;
	double fH = fAmp*65536/fCurrentMax;
	long nL = (fH - nH)*65536;

	return ((nH<<16)&0xFFFF0000)+nL;
}

//moduleoutput
void CSttDevicePFC6A::tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
{
	char *pszDrv =stt_test_get_drvparas_buff();
	Drv_ManuData *pDrvManuData=(Drv_ManuData *)pszDrv;
	tmt_channel    m_oTmt_channel[MAX_VOLTAGE_COUNT];
	for(int nIndex=0;nIndex<MAX_VOLTAGE_COUNT;nIndex++)
	{
		m_oTmt_channel[nIndex].init();
	}
	memset(pDrvManuData,0,sizeof(Drv_ManuData));

	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;

	float fAmp=0;
	BOOL bDc=FALSE;

	if(pTmt->m_nFreqIndex==0)
		bDc=TRUE;

	pDrvManuData->oDrvComBoSta.item[0].nVal1=g_theSttAdjustTool.m_nSwitchCtrl;


	InitDAData();
	if(pTmt->m_nModuleType==STT_MODULE_TYPE_VOLT)
	{
		//VOLT
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
		{
			PSTT_MODULE oModule_U=g_theDeviceSystemParameter->m_oModules_U[nIndex];
			if(oModule_U!=NULL)
			{
				if(oModule_U->m_oModuleAttr.m_nModuleIndex==pTmt->m_nModuleIndex)
				{
					for(int nChannel=0;nChannel<CHANNEL_MAX;nChannel++)
					{
						m_oTmt_channel[nChannel].Harm[1].fAmp=
								pTmt->m_oChannels[nChannel].m_oVector.m_fMag;
						m_oTmt_channel[nChannel].Harm[1].fAngle=
								pTmt->m_oChannels[nChannel].m_oVector.m_fAngle;
						m_oTmt_channel[nChannel].Harm[1].fFreq=
								pTmt->m_nFreqIndex*g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

						fAmp=fabs(m_oTmt_channel[nChannel].Harm[1].fAmp);
						if(fVsum<fAmp)
							fVsum=fAmp;
					}

					Manual_volt(m_oTmt_channel,pszDrv,1,nIndex,bDc,TRUE);
					SetVoltDApara(fVsum,nIndex,bDc);
					break;
				}
			}
		}
	}
	else if(pTmt->m_nModuleType==STT_MODULE_TYPE_CURRENT)
	{
		if(g_theDeviceSystemParameter->m_oModules_U[0]!=NULL)
		{
			//RD33 UAUBUC统一接到测试仪UA
			m_oTmt_channel[0].Harm[1].fAmp=50;
			m_oTmt_channel[0].Harm[1].fAngle=0;
			m_oTmt_channel[0].Harm[1].fFreq=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

			Manual_volt(m_oTmt_channel,pszDrv,1,0);
			SetVoltDApara(50,0);
		}

		for(int nIndex=0;nIndex<MAX_VOLTAGE_COUNT;nIndex++)
		{
			m_oTmt_channel[nIndex].init();
		}
		//CURRENT
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
		{
			PSTT_MODULE oModule_I=g_theDeviceSystemParameter->m_oModules_I[nIndex];
			if(oModule_I!=NULL)
			{
				if(oModule_I->m_oModuleAttr.m_nModuleIndex==pTmt->m_nModuleIndex)
				{
					for(int nChannel=0;nChannel<CHANNEL_MAX;nChannel++)
					{
						m_oTmt_channel[nChannel].Harm[1].fAmp=
								pTmt->m_oChannels[nChannel].m_oVector.m_fMag;
						m_oTmt_channel[nChannel].Harm[1].fAngle=
								pTmt->m_oChannels[nChannel].m_oVector.m_fAngle;
						m_oTmt_channel[nChannel].Harm[1].fFreq=
								pTmt->m_nFreqIndex*g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

						fAmp=fabs(m_oTmt_channel[nChannel].Harm[1].fAmp);
						fIsum+=fAmp;
						if(fIMax<fAmp)
							fIMax=fAmp;
					}

					float fModuleMax=oModule_I->m_oModuleAttr.m_fChMax;

					if(fModuleMax>50)
						Manual_Current_1000A(m_oTmt_channel,pszDrv,1,nIndex,bDc,TRUE);
					else
					{
						Manual_Current_PFC6A(m_oTmt_channel,pszDrv,1,nIndex,bDc,TRUE);

						if(bDc)
						{
							SetCurrentDApara_DC(fIsum,nIndex);
						}
						else
						{
							SetCurrentDApara_AC(fIsum,nIndex,fIMax);
						}
					}
					break;
				}
			}
		}
	}

	WriteDApara();

	ioctl(m_nCommfd,0x300,0);
	write(m_nCommfd,pszDrv,sizeof(Drv_ManuData));
}

void CSttDevicePFC6A::tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt)
{
	char *pszDrv =stt_test_get_drvparas_buff();
	Drv_ManuData *pDrvManuData=(Drv_ManuData *)pszDrv;
	memset(pDrvManuData,0,sizeof(Drv_ManuData));

	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		Manual_volt(pTmt->m_uiVOL,pszDrv,31,nIndex);
	}

	tmt_channel uiCUR[MAX_CURRENT_COUNT];
	for(int i=0;i<MAX_CURRENT_COUNT;i++)
	{
		uiCUR[i].Harm[0].fAmp=0;
		for(int j=1;j<MAX_HARM_COUNT;j++)
		{
			uiCUR[i].Harm[j].fAmp=0;
			uiCUR[i].Harm[j].fAngle=0;
			uiCUR[i].Harm[j].fFreq=50*j;
		}
	}
	float fModuleMax;
	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		fModuleMax=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_fChMax;
		if(fModuleMax<50)
		{
			Manual_Current_PFC6A(uiCUR,pszDrv,31,nIndex,FALSE);
		}
		else
		{
			Manual_Current_1000A(uiCUR,pszDrv,31,nIndex,FALSE);
		}
	}

	//DAPara
	float fVsum = 0;
	InitDAData();
	float fAmp=0;
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		if(g_theDeviceSystemParameter->m_oModules_U[nIndex]!=NULL)
		{
			m_nTmtChanNum=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_nChannelNum;
			for(int k=0;k<m_nTmtChanNum;k++)
			{
				m_nTmtPos=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_nChTmtPos[k];
				if(m_nTmtPos<0)
					continue;

				fAmp=fabs(pTmt->m_uiVOL[m_nTmtPos].Harm[1].fAmp);
				if(fVsum<fAmp)
					fVsum=fAmp;
			}

			SetVoltDApara(fVsum,nIndex);
		}
	}

	WriteDApara(TRUE);

	ioctl(m_nCommfd,0x353,0);
	write(m_nCommfd,pszDrv,sizeof(Drv_ManuData));
}

//harm
void CSttDevicePFC6A::tmt_to_drv_harm(tmt_HarmTest *pTmt,BOOL bIsStartTest)
{
	char *pszDrv =stt_test_get_drvparas_buff();
	Drv_ManuData *pDrv=(Drv_ManuData *)pszDrv;
	memset(pDrv,0,sizeof(Drv_ManuData));

	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		Manual_volt(pTmt->m_oHarmParas.m_uiVOL,pszDrv,31,nIndex);
	}

	float fIsum = 0;
	float fIMax=0;
	float fAmp=0;

	//DAPara
	float fVsum = 0;
	InitDAData();

	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		if(g_theDeviceSystemParameter->m_oModules_U[nIndex]!=NULL)
		{
			m_nTmtChanNum=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_nChannelNum;
			for(int k=0;k<m_nTmtChanNum;k++)
			{
				fAmp = 0;
				for(int nHarmIndex=0;nHarmIndex<32;nHarmIndex++)
				{
					fAmp+=pTmt->m_oHarmParas.m_uiVOL[k].Harm[nHarmIndex].fAmp;
				}

				if(fVsum<fAmp)
					fVsum=fAmp;
			}

			SetVoltDApara(fVsum,nIndex);
		}
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule==NULL)
			continue;

		if(pModule->m_oModuleAttr.m_fChMax<50)
			Manual_Current_PFC6A(pTmt->m_oHarmParas.m_uiCUR,pszDrv,31,nIndex,FALSE);
		else
			Manual_Current_1000A(pTmt->m_oHarmParas.m_uiCUR,pszDrv,20,nIndex,FALSE);//PF300频率最大1kHz
	}

	long nTmtPos;
	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule==NULL)
			continue;

		fIsum = 0;
		fIMax = 0;
		for(int k=0;k<pModule->m_oModuleAttr.m_nChannelNum;k++)
		{
			nTmtPos=pModule->m_nChTmtPos[k];
			if(nTmtPos < 0)
				continue;

			fAmp = pTmt->m_oHarmParas.m_uiCUR[nTmtPos].Harm[1].fAmp;
			for(int nHarm =2 ;nHarm < 32;nHarm++)
			{
				fAmp += pTmt->m_oHarmParas.m_uiCUR[nTmtPos].Harm[nHarm].fAmp;
			}
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("I[%d]Chan[%d]HarmAmp = %.6f"),nIndex+1,k,fAmp);

			if(pModule->m_oModuleAttr.m_fChMax<50)
			{
				fIsum+=fAmp;
				if(fIMax<fAmp)
					fIMax=fAmp;
			}
		}
		if(pModule->m_oModuleAttr.m_fChMax<50)
			SetCurrentDApara_AC(fIsum,nIndex,fIMax);
	}


	WriteDApara();

	for (int i=0; i<8; i++)//bo
	{
		pDrv->oDrvComBoSta.item[0].nVal1 += ((!pTmt->m_oHarmParas.m_oBinaryConfig.m_binOut[i].nState)<<i);
	}

	ioctl(m_nCommfd,0x300,0);
	write(m_nCommfd,pszDrv,sizeof(Drv_ManuData));
}

//state
void CSttDevicePFC6A::tmt_to_drv_StateItem(tmt_StateParas *pTmt)
{
	char *pBuf=stt_test_get_drvparas_buff();
	int nLen=0;
	Drv_StateItem oDrv_StateItem;
	int nDrvSize=sizeof(Drv_StateItem);

	float fIsum = 0;
	float fIMax = 0;
	float fIsumMax = 0;
	float fAmp=0;

	InitDAData();
	tmt_StatePara  oTmt_paraState;
	for(int nStateIndex=0;nStateIndex<pTmt->m_nStateNumbers;nStateIndex++)
	{
		oTmt_paraState=pTmt->m_paraState[nStateIndex];
		fIsum=0;
		for(int k=0;k<MAX_CURRENT_COUNT;k++)
		{
			fAmp=fabs(oTmt_paraState.m_uiCUR[k].Harm[1].fAmp);
			fIsum+=fAmp;

			if(fIMax<fAmp)
				fIMax=fAmp;
		}

		if(fIsumMax<fIsum)
			fIsumMax=fIsum;
	}

	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule==NULL)
			continue;

		if(pModule->m_oModuleAttr.m_fChMax<50)
			SetCurrentDApara_AC(fIsumMax,nIndex,fIMax);
		else
		{
			int nRetTap=0;
			float fMax;
			int nHGearID;
			long nTmtPos;
			for(int k=0;k<3;k++)
			{
				nTmtPos=pModule->m_nChTmtPos[k];
				fMax=0;
				if(nTmtPos > -1)
				{
					for(int nStateIndex=0;nStateIndex<pTmt->m_nStateNumbers;nStateIndex++)
					{
						oTmt_paraState=pTmt->m_paraState[nStateIndex];
						fAmp = oTmt_paraState.m_uiCUR[nTmtPos].Harm[1].fAmp;
						if(fMax<fAmp)
							fMax=fAmp;
					}
				}

				//0-200 200-400 400-1000
				nHGearID=stt_adj_get_ac_HGearID(fMax,pModule);
				nHGearID++;
				nRetTap |= (nHGearID<<k*2);
			}
			ioctl(m_nCommfd,0x70006014,nRetTap);
			Sleep(1500);
		}
	}

	for(int nStateIndex=0;nStateIndex<pTmt->m_nStateNumbers;nStateIndex++)
	{
		oTmt_paraState=pTmt->m_paraState[nStateIndex];
		memset(&oDrv_StateItem,0,nDrvSize);

		oDrv_StateItem.oStBo.nTripMode=2;
		for (int i=0; i<8; i++)//bo
		{
			oDrv_StateItem.oStBo.boValue.item[0].nVal1 += ((!oTmt_paraState.m_binOut[i].nState)<<i);
		}

		//VOLT
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
		{
			if(g_theDeviceSystemParameter->m_oModules_U[nIndex]==NULL)
				continue;

			State_volt(&oDrv_StateItem,oTmt_paraState,nIndex);
		}

		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
		{
			PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
			if(pModule==NULL)
				continue;

			if(pModule->m_oModuleAttr.m_fChMax<50)
				State_Current_PFC6A(&oDrv_StateItem,oTmt_paraState,nIndex);
			else
				State_Current_1000A(&oDrv_StateItem,oTmt_paraState,nIndex);
		}

		setTriger(oTmt_paraState,&oDrv_StateItem,nStateIndex);

		memcpy(pBuf+nDrvSize*nStateIndex,&oDrv_StateItem,nDrvSize);
		nLen+=nDrvSize;
	}

	//DAPara
	float fVsum = 0;
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
		if(pModule==NULL)
			continue;

		for(int nStateIndex=0;nStateIndex<pTmt->m_nStateNumbers;nStateIndex++)
		{
			oTmt_paraState=pTmt->m_paraState[nStateIndex];
			m_nTmtChanNum=pModule->m_oModuleAttr.m_nChannelNum;
			for(int k=0;k<m_nTmtChanNum;k++)
			{
				m_nTmtPos=pModule->m_nChTmtPos[k];
				if(m_nTmtPos<0)
					continue;

				fAmp=fabs(oTmt_paraState.m_uiVOL[m_nTmtPos].Harm[1].fAmp);
				if(fVsum<fAmp)
					fVsum=fAmp;
			}
		}
		SetVoltDApara(fVsum,nIndex);
	}

	WriteDApara();

	ioctl(m_nCommfd,0x301,1);
	write(m_nCommfd,pBuf,nLen);
}

void CSttDevicePFC6A::State_Current_PFC6A(Drv_StateItem *oDrv_StateItem,tmt_StatePara  oTmt_paraState,int nModuleIIndex)
{
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
	if(pModule==NULL)
		return;

	structACParamItem Curanal;
	memset(&Curanal,0,sizeof(structACParamItem));
	Curanal.DWCount = 24;

	int nChPos;
	float fAmp;
	long nTmtPos;
	long *dat=&Curanal.nVal[0];
	m_nTmtChanNum=pModule->m_oModuleAttr.m_nChannelNum;
	if(oTmt_paraState.m_bDC)
	{
		for(int k=0; k<m_nTmtChanNum; k++)
		{
			nTmtPos=pModule->m_nChTmtPos[k];
			if(nTmtPos < 0)
				continue;

			fAmp=oTmt_paraState.m_uiCUR[nTmtPos].Harm[1].fAmp;
			nChPos=pModule->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		for(int k=0; k<m_nTmtChanNum; k++)
		{
			nTmtPos=pModule->m_nChTmtPos[k];
			if(nTmtPos < 0)
				continue;

			fAmp=oTmt_paraState.m_uiCUR[nTmtPos].Harm[0].fAmp;
			nChPos=pModule->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);
			oTmtHarm=&oTmt_paraState.m_uiCUR[nTmtPos].Harm[1];
			if(oTmtHarm->fFreq<1)
				oTmtHarm->fFreq=1;

			TransAnalogCurToDrv(fabs(oTmtHarm->fAmp),oTmtHarm->fAngle,oTmtHarm->fFreq,k,nModuleIIndex,
								dat+CHANNEL_MAX+nChPos*3);
		}
	}
	memcpy(&oDrv_StateItem->oAcParam.item[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U],
			&Curanal,sizeof(structACParamItem));
}

void CSttDevicePFC6A::State_Current_1000A(Drv_StateItem *oDrv_StateItem,tmt_StatePara  oTmt_paraState,int nModuleIIndex)
{
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
	if(pModule==NULL)
		return;

	structACParamItem Curanal;
	memset(&Curanal,0,sizeof(structACParamItem));
	Curanal.DWCount = 24;

	int nChPos;
	float fAmp;
	long nTmtPos;
	long *dat=&Curanal.nVal[0];
	if(oTmt_paraState.m_bDC)
	{
		for(int k=0; k<3; k++)
		{
			nTmtPos=pModule->m_nChTmtPos[k];
			if(nTmtPos < 0)
			{
				fAmp=0;
			}
			else
				fAmp=oTmt_paraState.m_uiCUR[nTmtPos].Harm[1].fAmp;
			nChPos=k+3;

			//			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		for(int k=0; k<3; k++)
		{
			nTmtPos=pModule->m_nChTmtPos[k];
			if(nTmtPos < 0)
			{
				fAmp=0;
			}
			else
				fAmp=oTmt_paraState.m_uiCUR[nTmtPos].Harm[0].fAmp;
			nChPos=k+3;

			//			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);
			if(nTmtPos < 0)
			{
				oTmtHarm->fAmp=0;
				oTmtHarm->fFreq=50;
			}
			else
				oTmtHarm=&oTmt_paraState.m_uiCUR[nTmtPos].Harm[1];

			if(oTmtHarm->fFreq<1)
				oTmtHarm->fFreq=1;

			TransAnalogCurToDrv_1000A(fabs(oTmtHarm->fAmp),oTmtHarm->fAngle,oTmtHarm->fFreq,k,nModuleIIndex,
									  dat+CHANNEL_MAX+nChPos*3);
		}
	}
	memcpy(&oDrv_StateItem->oAcParam.item[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U],
			&Curanal,sizeof(structACParamItem));
}

void CSttDevicePFC6A::SetDrvMoudlePara()
{
	Drv_ModulePara oDrv_ModulePara;
	memset(&oDrv_ModulePara,0,sizeof(Drv_ModulePara));

	memset(&m_oModuleMaxVaildCnt,0,sizeof(Drv_ModuleMaxVaildCnt));
	int nModuleIndex=0;
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		PSTT_MODULE oModule_U=g_theDeviceSystemParameter->m_oModules_U[nIndex];
		nModuleIndex=oModule_U->m_oModuleAttr.m_nModuleIndex;
		oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt]=1<<(nModuleIndex-1);
		m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt]=6+6*3*31;
		oDrv_ModulePara.nAlgCnt++;
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE oModule_I=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		nModuleIndex=oModule_I->m_oModuleAttr.m_nModuleIndex;
		oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt]=1<<(nModuleIndex-1);
		m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt]=6+6*3*31;
		oDrv_ModulePara.nAlgCnt++;
	}

	//BIO
	oDrv_ModulePara.nBiCnt=1;
	oDrv_ModulePara.nBiTable[0] = 0x8000;
	oDrv_ModulePara.nBoCnt = 1;
	oDrv_ModulePara.nBoTable[0] = 0x8000;

	ioctl(m_nCommfd, 0x331, 0);
	write(m_nCommfd, (char*)&oDrv_ModulePara,sizeof(Drv_ModulePara));

	ioctl(m_nCommfd, 0x356, 0);
	write(m_nCommfd, (char*)&m_oModuleMaxVaildCnt,sizeof(Drv_ModuleMaxVaildCnt));
}

void CSttDevicePFC6A::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,int nModuleType)
{
#ifdef _PSX_QT_LINUX_
	PSTT_MODULE pSTT_MODULE=NULL;
	int nModuleIndex=0;
    if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		for(int i=0;i<g_theDeviceSystemParameter->m_nModuleCount_U;i++)
		{
			PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[i];
			if(pModule==NULL)
				continue;

			if(pModule->m_oModuleAttr.m_nModuleIndex==nModulePos)
			{
				pSTT_MODULE=pModule;
				break;
			}
		}
	}
	else
	{
		for(int i=0;i<g_theDeviceSystemParameter->m_nModuleCount_I;i++)
		{
			PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[i];
			if(pModule==NULL)
				continue;

			if(pModule->m_oModuleAttr.m_nModuleIndex==nModulePos)
			{
				if(pModule->m_oModuleAttr.m_fChMax>50)
				{
                    int nItemIndex=0;
                    for(unsigned int m=0;m<g_theSttDeviceStatus->m_nAnalogCount;m++)
                    {
                        if(g_theSttDeviceStatus->m_oModule[m].m_nModulePos==nModulePos)
                        {
                            nItemIndex=m;
                            break;
                        }
                    }

                    for(int j=0;j<6;j++)
                    {                        
                        STT_MODULE_STATUS &oModuleStatus=g_theSttDeviceStatus->m_oModule[nItemIndex];
                        oModuleStatus.m_oChannel[j].m_bIsOverLoad=0;//过载
                    }
					return;
				}
				pSTT_MODULE=pModule;
				nModuleIndex=i;
				break;
			}
		}
	}

	if(pSTT_MODULE==NULL)
		return;

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
	if(oModuleStatus.m_nDisable!=0||oModuleStatus.m_nNeedMonitor==0)
		return;

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

	int nChDrvPos=0;
	for(int j=0;j<6;j++)
	{
		for(int i=0;i<g_theDeviceSystemParameter->m_nModuleCount;i++)
		{
			if(g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_MEAS_CURRENT
					||g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_MEAS_VOLT)
				continue;

			if(g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleIndex==nModulePos)
			{
				nChDrvPos =	g_theDeviceSystemParameter->m_oModules[i].m_nChDrvPos[j];
				break;
			}
		}

		oModuleStatus.m_oChannel[j].m_fVoltMax=fmaxarry[nChDrvPos];
		oModuleStatus.m_oChannel[j].m_fVoltMin=fminarry[nChDrvPos];
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
	unsigned short temp = (oDrv_FeedBack.dat[9]>>16)&0xfff;
	temp  = temp*0.0625;
	oModuleStatus.m_nTemp[0]=temp;
	if(tempMax<temp)
		tempMax = temp;

	temp = (oDrv_FeedBack.dat[9])&0xfff;
	temp  = temp*0.0625;
	oModuleStatus.m_nTemp[1]=temp;
	if(tempMax<temp)
		tempMax = temp;

	temp = (oDrv_FeedBack.dat[10]>>16)&0xfff;
	temp  = temp*0.0625;
	oModuleStatus.m_nTemp[2]=temp;
	if(tempMax<temp)
		tempMax = temp;

    if(nModuleType == STT_MODULE_TYPE_CURRENT)
	{
		if(tempMax>75)
		{
			for(int nCurModule=0;nCurModule<g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum;nCurModule++)
			{
				tmt_CurModuleGear &oCurModuleGear=g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nCurModule];
				if(oCurModuleGear.m_nModulePos==pSTT_MODULE->m_oModuleAttr.m_nModuleIndex)
				{
					oCurModuleGear.m_nIPowerMode=STT_CurrentMODULE_POWER_LOW;
					break;
				}
			}

			CSttPowerCtrlBase *pSttPowerCtrlBase=pSTT_MODULE->m_oModuleAttr.m_pPowerCtrlBase;
			if(pSttPowerCtrlBase!=NULL)
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
			WriteDApara();
		}

		if(tempMax>84)
		{
			//电流模块高温停止实验
			g_theSttDeviceStatus->m_bNeedStop=TRUE;
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ModulePos=%d,MaxTemperature>84"),nModulePos);
		}
	}

	unsigned short nH = (~oDrv_FeedBack.dat[10])&0x1;
	oModuleStatus.m_nIsVoltHot=nH;//电压过热

	for(int j=1;j<7;j++)
	{
		//通道异常或者模块通讯丢失,都会报过载
		//以此标记来停止实验不合适.如果是模块通讯丢失并且测试人员已知晓,可以继续实验.
		nH = (~(oDrv_FeedBack.dat[10]>>j))&0x1;
		oModuleStatus.m_oChannel[j-1].m_bIsOverLoad=nH;//过载
	}

	nH = (~(oDrv_FeedBack.dat[10]>>7))&0x1;
	oModuleStatus.m_nIsDCHot=nH;//直流过热

    if(nModuleType == STT_MODULE_TYPE_VOLT)
	{
		nH = (~(oDrv_FeedBack.dat[10]>>8))&0x1;
		oModuleStatus.m_nIsVoltWarining=nH;//电压告警
	}

	nH = (~(oDrv_FeedBack.dat[10]>>9))&0x1;
	oModuleStatus.m_nIsMissWarining=nH;//忽略告警

	//466插件暂不考虑以下指标
	oModuleStatus.m_nIsVoltHot = 0;//电压过热
	oModuleStatus.m_nIsDCHot = 0;//直流过热
	oModuleStatus.m_nIsVoltWarining = 0;//电压告警
	oModuleStatus.m_nIsMissWarining = 0;//失地告警

#endif
}
