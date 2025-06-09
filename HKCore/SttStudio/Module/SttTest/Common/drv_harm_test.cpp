#include "stdafx.h"
#include "drv_harm_test.h"
#include"math.h"
#include"../../SttDevice/SttDeviceBase.h"

void tmt_to_drv(tmt_HarmTest *pTmt , Drv_ManuData *pDrv)
{
	memset(pDrv,0,sizeof(Drv_ManuData));

	if(pTmt->m_oHarmParas.m_bLock)
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
			tmt_channel *pTmt_channel=&pTmt->m_oHarmParas.m_uiVOL[0];
			tmt_to_drv_manual_volt(pTmt_channel,pDrv,MAX_HARM_COUNT-1,nIndex);
		}

		//CURRENT
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
		{
			tmt_channel *pTmt_channel=&pTmt->m_oHarmParas.m_uiCUR[0];
			tmt_to_drv_manual_current(pTmt_channel,pDrv,MAX_HARM_COUNT-1,nIndex);
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
					for(int nHarmIndex=0;nHarmIndex<MAX_HARM_COUNT;nHarmIndex++)
					{
						fAmp+=pTmt->m_oHarmParas.m_uiVOL[k+nArrayBeginIndex].Harm[nHarmIndex].fAmp;
					}

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
					for(int nHarmIndex=0;nHarmIndex<MAX_HARM_COUNT;nHarmIndex++)
					{
						fAmp+=pTmt->m_oHarmParas.m_uiCUR[k+nArrayBeginIndex].Harm[nHarmIndex].fAmp;
					}

					fIsum+=fAmp;
					if(fIMax<fAmp)
						fIMax=fAmp;
				}
				CSttDeviceBase::g_pSttDeviceBase->setDApara(fIsum,nIndex,STT_MODULE_TYPE_CURRENT,fIMax);
			}
		}

		CSttDeviceBase::g_pSttDeviceBase->setDApara_to_drv();
	}

	for (int i=0; i<8; i++)//bo
	{
		pDrv->oDrv_BIOParam[0].dat[0] += ((!pTmt->m_oHarmParas.m_oBinaryConfig.m_binOut[i].nState)<<i);
	}
}





