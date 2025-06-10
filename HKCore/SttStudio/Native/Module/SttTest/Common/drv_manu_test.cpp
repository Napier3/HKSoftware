#include "stdafx.h"
#include "drv_manu_test.h"
#include"math.h"
#include"../../SttDevice/SttDeviceBase.h"
#include "../../SttDevice/SttDriverOper.h"
#include "tmt_adjust_sys_parameter.h"


void SetDrvMoudlePara(BOOL bHasAnalog,BOOL bHasDigital)
{
	Drv_ModulePara oDrv_ModulePara;
	memset(&oDrv_ModulePara,0,sizeof(Drv_ModulePara));

	int nModuleIndex=0;

	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		nModuleIndex=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_nModuleIndex;
		if(bHasAnalog)
		{
			oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt]=1<<(nModuleIndex-1);
			oDrv_ModulePara.nAlgCnt++;
		}
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		nModuleIndex=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_nModuleIndex;
		if(bHasAnalog)
		{
			oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt]=1<<(nModuleIndex-1);
			oDrv_ModulePara.nAlgCnt++;
		}
	}

	//DIGITAL
#ifdef _USE_IEC61850_
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_D;nIndex++)
	{
		nModuleIndex=g_theDeviceSystemParameter->m_oModules_D[nIndex]->m_oModuleAttr.m_nModuleIndex;
		if(bHasDigital)
		{
			oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt]=1<<(nModuleIndex-1);
			oDrv_ModulePara.nAlgCnt++;
		}
	}
#endif

	//BIO
	oDrv_ModulePara.nBiCnt=1;
	oDrv_ModulePara.nBiTable[0] = 0x8000;
	oDrv_ModulePara.nBoCnt = 1;
	oDrv_ModulePara.nBoTable[0] = 0x8000;

#ifdef _USE_EXT_SWITCH_
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_S;nIndex++)
	{
		nModuleIndex=g_theDeviceSystemParameter->m_oModules[nIndex].m_oModuleAttr.m_nModuleIndex;
		oDrv_ModulePara.nBiTable[oDrv_ModulePara.nBiCnt]= 1<<(nModuleIndex-1);
		oDrv_ModulePara.nBoTable[oDrv_ModulePara.nBoCnt] = 1<<(nModuleIndex-1);
		oDrv_ModulePara.nBiCnt++;
		oDrv_ModulePara.nBoCnt++;
	}
#endif

	CSttDriverOper::SetModuleInfo((char*)&oDrv_ModulePara,sizeof(Drv_ModulePara));
}

long TranslateACFre(float fFre)
{
	long nH = (long)fFre*65536/400000.0;
	double fH = fFre*65536/400000.0;
	long nL = (fH - nH)*65536;
	long nFre  =((nH<<16)&0xFFFF0000)+nL;
	return nFre;
}

//
//volt
void TransAnalogDCVolToDrv(float fAmp,int nChannel,int nModuleUIndex,long *pDrvData)
{	
	if(g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]==NULL)
		return;

	float fChDcMax=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_oModuleAttr.m_fChDcMax;
	if(fAmp>fChDcMax)
		fAmp=fChDcMax;

	float fVoltMax=stt_adj_get_ac_max(fAmp,nModuleUIndex,STT_MODULE_TYPE_VOLT);
	fVoltMax=fVoltMax*1.414;

	if(fVoltMax<0.001)
		return;

	float fTemperature=0;//getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust=stt_adj_find_channel(STT_MODULE_TYPE_VOLT,nModuleUIndex,nChannel,fTemperature);
	float fCoef=stt_adj_get_ac_u_coef(fAmp,nModuleUIndex,nChannel,fTemperature,0);//幅值系数
	float fZero=pChsAdjust->m_fDcZero;//直流零漂

	fAmp = fAmp*fCoef-fZero;

	long nH = fAmp*32768/fVoltMax;//65536/2=32768
	double fH = fAmp*32768/fVoltMax;
	long nL = (fH - nH)*65536;
	pDrvData[0] = ((nH<<16)&0xFFFF0000)+nL;
}

long TranslateACVoltAmp(float fAmp,int nChannel,int nModuleUIndex,int nHarm)
{
	if(g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]==NULL)
		return 0;

	float fChMax=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_oModuleAttr.m_fChMax;
	if(fAmp>fChMax)
		fAmp=fChMax;

	float fVoltMax=stt_adj_get_ac_max(fAmp,nModuleUIndex,STT_MODULE_TYPE_VOLT);

	if(fVoltMax<0.001)
	{
		return 0;
	}

	float fTemperature=0;//getTemperature();
	PSTT_ADJUST_ITEM pAdjItem=stt_adj_get_ac_u(fAmp,nModuleUIndex,nChannel,fTemperature,nHarm);
	float fCoef=1;//幅值系数
	float fZero=0;//交流零漂
	if(pAdjItem!=NULL)
	{
		fCoef=pAdjItem->m_fCoef;
		fZero=pAdjItem->m_fZero;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);

	fAmp =fAmp*fCoef+fZero;

	long nH = fAmp*65536/fVoltMax;
	double fH = fAmp*65536/fVoltMax;
	long nL = (fH - nH)*65536;

	return ((nH<<16)&0xFFFF0000)+nL;
}

void TransAnalogVolToDrv(float fAmp,float fAng,float fFre,int nChannel,int nModuleUIndex,long *pnDrvData)
{	
	int nHarm=0;
	int m_nEDFre=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	if(m_nEDFre<0.001)
		m_nEDFre=50;
	if(fFre<=m_nEDFre)
	{
		nHarm = 0;
	}
	else
	{
		nHarm  = (fFre+25)/m_nEDFre - 1;
	}

	float fTemperature=0;//getTemperature();
	float faddPh = stt_adj_get_ac_u_angle(50,nModuleUIndex,nChannel,fTemperature);
	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("volt-channel-%d ph=%f"),nChannel,faddPh);
	fAng -= faddPh*(nHarm+1);

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
	float fFreCoef=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_oModuleAttr.m_fFreCoef;
	pnDrvData[1] = TranslateACFre(fFre*fFreCoef);
	pnDrvData[2] = TranslateACVoltAmp(fAmp,nChannel,nModuleUIndex,nHarm+1);
}

void tmt_to_drv_manual_volt(tmt_channel *pTmt_channel,Drv_ManuData *pDrv,int nHarm,int nModuleUIndex,BOOL bIsDc)
{
	if(g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]==NULL)
		return;

	int  nArrayBeginIndex=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_nArrayBeginIndex;
	int nChPos;
	float fAmp=0;

	long *dat=&pDrv->oDrv_HarmParam[nModuleUIndex].dat[0];
	if(bIsDc)
	{
		for(int k=0; k<CHANNEL_MAX; k++)
		{
			fAmp=pTmt_channel[k+nArrayBeginIndex].Harm[1].fAmp;
			nChPos=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_nChDrvPos[k];

			TransAnalogDCVolToDrv(fabs(fAmp),k,nModuleUIndex,dat+nChPos);
		}
		pDrv->oDrv_HarmParam[nModuleUIndex].nDWcnt=24;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		for(int k=0; k<CHANNEL_MAX; k++)
		{
			fAmp=pTmt_channel[k+nArrayBeginIndex].Harm[0].fAmp;
			nChPos=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_nChDrvPos[k];

			TransAnalogDCVolToDrv(fabs(fAmp),k,nModuleUIndex,dat+nChPos);

			for(int m=0;m<nHarm;m++)
			{
				oTmtHarm=&pTmt_channel[k+nArrayBeginIndex].Harm[m+1];
				if(oTmtHarm->fFreq<1)
				{
					oTmtHarm->fFreq=1;
				}

				TransAnalogVolToDrv(fabs(oTmtHarm->fAmp),oTmtHarm->fAngle,oTmtHarm->fFreq,k,nModuleUIndex,
									dat+CHANNEL_MAX+nChPos*3+m*3*CHANNEL_MAX);
			}
		}
		pDrv->oDrv_HarmParam[nModuleUIndex].nDWcnt=6+nHarm*3*CHANNEL_MAX;
	}

}

//
//current
void TransAnalogDCCurToDrv(float fAmp,int nChannel,int nModuleIIndex,long *pDrvData)
{
	if(g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]==NULL)
		return;

	float fChDcMax=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_oModuleAttr.m_fChDcMax;
	if(fAmp>fChDcMax)
		fAmp=fChDcMax;

	float fCurrentMax = stt_adj_get_ac_max(fAmp,nModuleIIndex,STT_MODULE_TYPE_CURRENT);
	if(fCurrentMax<0.001)
		return;

	float fTemperature=0;//getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust=stt_adj_find_channel(STT_MODULE_TYPE_CURRENT,nModuleIIndex,nChannel,fTemperature);
	float fCoef=stt_adj_get_ac_i_coef(fAmp,nModuleIIndex,nChannel,fTemperature,0);//幅值系数
	float fZero=pChsAdjust->m_fDcZero;//直流零漂

	fAmp = -fAmp*fCoef;
	if(fabs(fAmp)>5&&fCurrentMax>5)
	{
		float fMaxRatio = pChsAdjust->m_fLargeCurrentRatio;
		fAmp = fAmp-fAmp*(fAmp-5)*(fAmp-5)*(fMaxRatio-1)/((fCurrentMax - 5)*(fCurrentMax - 5));
	}
	fAmp += fZero;

	long nH = fAmp*32768/(fCurrentMax*1.414);//65536/2=32768
	double fH = fAmp*32768/(fCurrentMax*1.414);
	long nL = (fH - nH)*65536;
	pDrvData[0] = ((nH<<16)&0xFFFF0000)+nL;
}

long  TranslateACCurrentAmp(float fAmp,int nChannel,int nModuleIIndex,int nHarm)
{
	if(g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]==NULL)
		return 0;

	float fChMax=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_oModuleAttr.m_fChMax;
	if(fAmp>fChMax)
		fAmp=fChMax;

	float fCurrentMax = stt_adj_get_ac_max(fAmp,nModuleIIndex,STT_MODULE_TYPE_CURRENT);

	if(fCurrentMax<0.001)
	{
		return 0;
	}

	float fTemperature=0;//getTemperature();
	PSTT_ADJUST_ITEM pAdjItem=stt_adj_get_ac_i(fAmp,nModuleIIndex,nChannel,fTemperature,nHarm);
	PSTT_CHANNEL_ADJUSTS pChsAdjust=stt_adj_find_channel(STT_MODULE_TYPE_CURRENT,nModuleIIndex,nChannel,fTemperature);
	float fCoef=1;//幅值系数
	float fZero=0;//交流零漂
	float fMaxRatio=1.0;
	if(pAdjItem!=NULL)
	{
		fCoef=pAdjItem->m_fCoef;
		fZero=pAdjItem->m_fZero;
	}
	if(pChsAdjust!=NULL)
		fMaxRatio = pChsAdjust->m_fLargeCurrentRatio;

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Current_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);

	fAmp =fAmp*fCoef;

	if(fAmp>5&&fCurrentMax>5)
	{
		fAmp = fAmp-fAmp*(fAmp-5)*(fAmp-5)*(fMaxRatio-1)/((fCurrentMax - 5)*(fCurrentMax - 5));
	}

	fAmp += fZero;

	long nH = fAmp*65536/fCurrentMax;
	double fH = fAmp*65536/fCurrentMax;
	long nL = (fH - nH)*65536;

	return ((nH<<16)&0xFFFF0000)+nL;
}

void TransAnalogCurToDrv(float fAmp,float fAng,float fFre,int nChannel,int nModuleIIndex,long *pnDrvData)
{	
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
	float faddPh = stt_adj_get_ac_i_angle(1,nModuleIIndex,nChannel,fTemperature);//0:DC,1:基波
	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("current-channel-%d ph=%f"),nChannel,faddPh);
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
	pnDrvData[2] = TranslateACCurrentAmp(fAmp,nChannel,nModuleIIndex,nHarm+1);
}

void tmt_to_drv_manual_current(tmt_channel *pTmt_channel,Drv_ManuData *pDrv,int nHarm,int nModuleIIndex,BOOL bIsDc)
{
	if(g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]==NULL)
		return;

	int  nArrayBeginIndex=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_nArrayBeginIndex;
	int nChPos;
	float fAmp=0;

	long *dat=&pDrv->oDrv_HarmParam[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U].dat[0];
	if(bIsDc)
	{
		for(int k=0; k<CHANNEL_MAX; k++)
		{
			fAmp=pTmt_channel[k+nArrayBeginIndex].Harm[1].fAmp;
			nChPos=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);
		}
		pDrv->oDrv_HarmParam[nModuleIIndex+g_theDeviceSystemParameter->m_nModuleCount_U].nDWcnt=24;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		for(int k=0; k<CHANNEL_MAX; k++)
		{
			fAmp=pTmt_channel[k+nArrayBeginIndex].Harm[0].fAmp;
			nChPos=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex]->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fabs(fAmp),k,nModuleIIndex,dat+nChPos);

			for(int m=0;m<nHarm;m++)
			{
				oTmtHarm=&pTmt_channel[k+nArrayBeginIndex].Harm[m+1];
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

void tmt_to_drv_manual_digital(tmt_ManualTest *pTmt,Drv_ManuData *pDrv,int nHarm,int nIndex)
{
	/***
	int nModuleIndex=nIndex+g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleIndex+=g_theDeviceSystemParameter->m_nModuleCount_I;

	for(int m=0; m<nHarm; m++)
	{
		float fFreq=pTmt->m_oManuParas.m_uiVOL[i*3+channel].Harm[m+1].fFreq;
		if(pTmt->m_oManuParas.m_bDC)
		{
			fFreq=0;
		}

		CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolToDrv(pTmt->m_oManuParas.m_uiVOL[i*3+channel].Harm[m+1].fAmp,
				pTmt->m_oManuParas.m_uiVOL[i*3+channel].Harm[m+1].fAngle,
				fFreq, i ,
				pDrv->oDrv_HarmParam[nModuleIndex].dat);

		fFreq=pTmt->m_oManuParas.m_uiCUR[i*3+channel].Harm[m+1].fFreq;
		if(pTmt->m_oManuParas.m_bDC)
		{
			fFreq=0;
		}
		CSttDeviceBase::g_pSttDeviceBase->TransDigitalCurToDrv(pTmt->m_oManuParas.m_uiCUR[i*3+channel].Harm[m+1].fAmp,
				pTmt->m_oManuParas.m_uiCUR[i*3+channel].Harm[m+1].fAngle,
				fFreq, i ,
				pDrv->oDrv_HarmParam[nModuleIndex].dat);
	}
	***/
}

void tmt_to_drv(tmt_ManualTest *pTmt , Drv_ManuData *pDrv, int nHarm)
{
	memset(pDrv,0,sizeof(Drv_ManuData));

	if(pTmt->m_oManuParas.m_bLockChanged)
	{
		//		pDrvBin->nisStop = 1;
		//		pTmt->m_oManuParas.m_bLockChanged = false;
	}

	BOOL bHasAnalog=TRUE;
	BOOL bHasDigital=TRUE;

	if(bHasAnalog)
	{
		//VOLT
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
		{
			tmt_channel *pTmt_channel=&pTmt->m_oManuParas.m_uiVOL[0];
			tmt_to_drv_manual_volt(pTmt_channel,pDrv,nHarm,nIndex,pTmt->m_oManuParas.m_bDC);
		}

		//CURRENT
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
		{
			tmt_channel *pTmt_channel=&pTmt->m_oManuParas.m_uiCUR[0];
			tmt_to_drv_manual_current(pTmt_channel,pDrv,nHarm,nIndex,pTmt->m_oManuParas.m_bDC);
		}


		//DAPara
		float fIsum = 0;
		float fVsum = 0;
		float fIMax = 0;
		CSttDeviceBase::g_pSttDeviceBase->InitDAVolt();
		int nArrayBeginIndex=0;
		float fAmp=0;
		//VOLT
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
		{
			if(g_theDeviceSystemParameter->m_oModules_U[nIndex]!=NULL)
			{
				nArrayBeginIndex=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_nArrayBeginIndex;
				for(int k=0;k<CHANNEL_MAX;k++)
				{
					fAmp=fabs(pTmt->m_oManuParas.m_uiVOL[k+nArrayBeginIndex].Harm[1].fAmp);
					if(fVsum<fAmp)
						fVsum=fAmp;
				}

				if(pTmt->m_oManuParas.m_bDC)
					fVsum/=1.414;

				CSttDeviceBase::g_pSttDeviceBase->setDApara(fVsum,nIndex,STT_MODULE_TYPE_VOLT);
			}
		}

		//Current
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
		{
			if(g_theDeviceSystemParameter->m_oModules_I[nIndex]!=NULL)
			{
				nArrayBeginIndex=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_nArrayBeginIndex;
				for(int k=0;k<CHANNEL_MAX;k++)
				{
					fAmp=fabs(pTmt->m_oManuParas.m_uiCUR[k+nArrayBeginIndex].Harm[1].fAmp);
					fIsum+=fAmp;
					if(fIMax<fAmp)
						fIMax=fAmp;
				}

				if(pTmt->m_oManuParas.m_bDC)
				{
					CSttDeviceBase::g_pSttDeviceBase->setCurrentDCDApara(fIsum,nIndex);
				}
				else
				{
					CSttDeviceBase::g_pSttDeviceBase->setDApara(fIsum,nIndex,STT_MODULE_TYPE_CURRENT,fIMax);
				}
			}
		}

		CSttDeviceBase::g_pSttDeviceBase->setDApara_to_drv();
	}

#ifdef _USE_IEC61850_

	if(bHasDigital)
	{
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_D;nIndex++)
		{
			tmt_to_drv_manual_digital(pTmt,pDrv,nHarm,nIndex);
		}
	}
#endif


	for (int i=0; i<8; i++)//bo
	{
		pDrv->oDrv_BIOParam[0].dat[0] += ((!pTmt->m_oManuParas.m_binOut[i].nState)<<i);
	}
}

void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt)
{
	Drv_ManuData oDrv_ManuData;
	memset(&oDrv_ManuData,0,sizeof(Drv_ManuData));

	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		tmt_channel *pTmt_channel=&pTmt->m_uiVOL[0];
		tmt_to_drv_manual_volt(pTmt_channel,&oDrv_ManuData,31,nIndex);
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		tmt_channel *pTmt_channel=&pTmt->m_uiCUR[0];
		tmt_to_drv_manual_current(pTmt_channel,&oDrv_ManuData,31,nIndex);
	}


	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;
	CSttDeviceBase::g_pSttDeviceBase->InitDAVolt();
	int nArrayBeginIndex=0;
	float fAmp=0;
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		if(g_theDeviceSystemParameter->m_oModules_U[nIndex]!=NULL)
		{
			nArrayBeginIndex=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_nArrayBeginIndex;
			for(int k=0;k<CHANNEL_MAX;k++)
			{
				fAmp=fabs(pTmt->m_uiVOL[k+nArrayBeginIndex].Harm[1].fAmp);
				if(fVsum<fAmp)
					fVsum=fAmp;
			}

			CSttDeviceBase::g_pSttDeviceBase->setDApara(fVsum,nIndex,STT_MODULE_TYPE_VOLT);
		}
	}

	//Current
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		if(g_theDeviceSystemParameter->m_oModules_I[nIndex]!=NULL)
		{
			nArrayBeginIndex=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_nArrayBeginIndex;
			for(int k=0;k<CHANNEL_MAX;k++)
			{
				fAmp=fabs(pTmt->m_uiCUR[k+nArrayBeginIndex].Harm[1].fAmp);
				fIsum+=fAmp;
				if(fIMax<fAmp)
					fIMax=fAmp;
			}

			CSttDeviceBase::g_pSttDeviceBase->setDApara(fIsum,nIndex,STT_MODULE_TYPE_CURRENT,fIMax);
		}
	}

	CSttDeviceBase::g_pSttDeviceBase->setDApara_to_drv();

	for (int i=0; i<8; i++)//bo
	{
		oDrv_ManuData.oDrv_BIOParam[0].dat[0] += ((!pTmt->m_binOut[i].nState)<<i);
	}

	CSttDriverOper::IoCtrl(0x353,0);
	CSttDriverOper::WriteData((char*)&oDrv_ManuData,sizeof(Drv_ManuData));	
}


