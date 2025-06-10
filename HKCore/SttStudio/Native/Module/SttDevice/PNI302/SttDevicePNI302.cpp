#include "SttDevicePNI302.h"
#include "../../Engine/SttServerTestCtrlCntr.h"
#include "../Module/Driver466/IEC61850CfgMngr.h"

CSttDevicePNI302 *CSttDevicePNI302::g_pSttDevicePNI302=NULL;
long CSttDevicePNI302::g_nSttDevicePNI302Ref = 0;

CSttDevicePNI302::CSttDevicePNI302()
{

}

void CSttDevicePNI302::Create()
{
	g_nSttDevicePNI302Ref++;

	if (g_nSttDevicePNI302Ref == 1)
	{
		g_pSttDevicePNI302=new CSttDevicePNI302;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePNI302;
	}
}

void CSttDevicePNI302::Release()
{
	g_nSttDevicePNI302Ref--;

	if (g_nSttDevicePNI302Ref == 0)
	{
		delete g_pSttDevicePNI302;
		g_pSttDevicePNI302 = NULL;
	}
}

int CSttDevicePNI302::InitDevice(BOOL bHasAdjFile)
{
	m_nCommfd=open("/dev/SttDriver_PN466",O_RDWR);
	g_nmaplen = 7782528;
	g_start = (unsigned int *)mmap(NULL, g_nmaplen, PROT_WRITE, MAP_SHARED, m_nCommfd, 0);

	g_theSystemConfig->m_nFiberType=STT_FiberType_2G6M;
	g_theSystemConfig->m_bSyncSecond=TRUE;

	InitDApara(m_nCommfd,bHasAdjFile);
	//FT3及ST光口配置
	SendConfFT3 Ft3;
	memset(&Ft3,0,sizeof(SendConfFT3));
	Ft3.module=1;
	Ft3.baud = 1<<20;
	Ft3.baud |= 1<<21;
	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Ft3CtrlCfg,(char*)&Ft3);

	ioctl(m_nCommfd,0x7000003c,1);//1588

	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		CSttPowerCtrlBase *pCSttPowerCtrlBase=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
			g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase *)(new CSttPowerCtrlV130);
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		CSttPowerCtrlBase *pCSttPowerCtrlBase=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
			g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase *)(new CSttPowerCtrlC20(FALSE));
	}

	return m_nCommfd;
}

void CSttDevicePNI302::SetSystemConfig()
{
	g_theSystemConfig->m_nFiberType=STT_FiberType_2G6M;
	CSttDeviceComm::SetSystemConfig();
	//FT3及ST光口配置
	SendConfFT3 Ft3;
	memset(&Ft3,0,sizeof(SendConfFT3));
	Ft3.module=1;
	Ft3.baud = 1<<20;
	Ft3.baud |= 1<<21;
	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Ft3CtrlCfg,(char*)&Ft3);
}

//////////////////////////////////////////////////
//2020-03-26 zhoulei

//----------Step6U6I-------------
void CSttDevicePNI302::SetStep6U6IStart()
{
	ioctl(m_nCommfd, 0x110, 1);
	ioctl(m_nCommfd,0xA00,1);
	ioctl(m_nCommfd, 0x100, 1);
	Sleep(50);
	ioctl(m_nCommfd, 0x131, 5);
	ioctl(m_nCommfd, 0x103, 1);
}

void CSttDevicePNI302::SetStep6U6IStop()
{
	ioctl(m_nCommfd,0xA00,0);
	ioctl(m_nCommfd, 0x103, 0);
	ioctl(m_nCommfd, 0x131, 0);
	ioctl(m_nCommfd, 0x100, 0);
	ioctl(m_nCommfd, 0x110, 0);
}
//----------Step6U6I-------------

//-----------MUTest-------------
void CSttDevicePNI302::SetRising(int nRising)
{
	ioctl(m_nCommfd, 0x132, nRising);
}

int CSttDevicePNI302::GetPPS()
{
	return ioctl(m_nCommfd,0x503,0);
}
//-----------MUTest-------------

//-----------Iecdetect------------
void CSttDevicePNI302::SetIecdetectStart(tmt_RecordTest *pTmt)
{
	char *pszBuf=stt_test_get_global_buff();
	GooseSubData *pDrv=(GooseSubData *)pszBuf;
	memset(pDrv,0,sizeof(GooseSubData));

	if(pTmt->m_oRecordPara.m_mode==1)
	{
		pDrv->ncount=1;
		pDrv->nPort=4;
		pDrv->gooseSub[0].CRC=pTmt->m_oRecordPara.m_crc;

		ioctl(m_nCommfd, 0x30C, 1);
		write(m_nCommfd, pDrv, sizeof(GooseSubData));
	}
	else
	{
		ioctl(m_nCommfd, 0x130, 0);
		pDrv->nPort=0;
		ioctl(m_nCommfd, 0x30C, 1);
		write(m_nCommfd, pDrv, sizeof(GooseSubData));
		ioctl(m_nCommfd, 0x130, 1);
	}
}

void CSttDevicePNI302::SetIecdetectStop(tmt_RecordTest *pTmt)
{
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
	if(pTmt->m_oRecordPara.m_mode==0)
	{
		ioctl(m_nCommfd, 0x130, 0);
	}
}

void CSttDevicePNI302::ProIecdetectDrvResult()
{
	char *pDrvResults=stt_test_get_result_buff();
	int ret=read(m_nCommfd,pDrvResults,0x260);
	if(ret<24)
		return;
	//05640564 00000005 5f0c8d8e 2e27cd3c aa12 4009 00f7 340e
	//	QString str;
	//	for(int i=0;i<ret;i++)
	//	{
	//		str+=QString("%1").arg(m_pDrvResults[i],2,16,QChar('0'));
	//	}
	//	qDebug()<<"str"<<str;

	int nPacketLen=0;
	long nRealTimeEventCount = 0;
	for(int i=0;i<ret;)
	{
		if(pDrvResults[i]==0x05&&pDrvResults[i+1]==0x64&&pDrvResults[i+2]==0x05&&pDrvResults[i+3]==0x64)
		{
			nPacketLen=0;
			nPacketLen+=pDrvResults[i+4]<<24;
			nPacketLen+=pDrvResults[i+5]<<16;
			nPacketLen+=pDrvResults[i+6]<<8;
			nPacketLen+=pDrvResults[i+7];
			nPacketLen=nPacketLen*4;

			if(nPacketLen!=20)
			{
				i=i+nPacketLen+4;
				continue;
			}

			STT_IEC_DETECT oSttIecDetect;
			oSttIecDetect.nAppid=pDrvResults[i+18]<<8;
			oSttIecDetect.nAppid|=pDrvResults[i+19];
			oSttIecDetect.nCrc=pDrvResults[i+22]<<8;
			oSttIecDetect.nCrc|=pDrvResults[i+23];
			oSttIecDetect.nPort=pDrvResults[i+17]&0x0f;
			oSttIecDetect.nType=(pDrvResults[i+17]>>4)&0x0f;

			stt_add_iec_detect_event(SttResult_Type_IEC_DETECT,oSttIecDetect);
			nRealTimeEventCount++;

			i=i+nPacketLen+4;
		}
		else
			i++;
	}

	if(nRealTimeEventCount>0)
	{
		CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
		pSttTestBase->ReturnRealTimeEvent();
	}
}
//-----------Iecdetect------------

//-----------IEDTest-----------------
void CSttDevicePNI302::SetIEDTestStart_B2G()
{
	ioctl(m_nCommfd,0xA00,1);
	CSttDeviceComm::SetRecordStart();
	ioctl(m_nCommfd,0x103,0xa);
}

void CSttDevicePNI302::SetIEDTestStop_B2G()
{
	SetTestStop();
	ioctl(m_nCommfd, 0x131, 0);
}

void CSttDevicePNI302::tmt_to_drv_iedtest_B2G(tmt_IEDTest *pTmt)
{
	char *pszBuf=stt_test_get_global_buff();
	Drv_SoePara *stBinOut=(Drv_SoePara *)pszBuf;
	memset(stBinOut,0,sizeof(Drv_SoePara));

	stBinOut->nModuleCnt = 1;
	tmt_IEDPara &otmt_IEDPara=pTmt->m_oIEDParas.m_otmt_IEDPara[0];

	SwitchModules oSwitchPara=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	stBinOut->item[0].nModule =1<<(oSwitchPara.oSWITCHINFO[0].m_nModulePos-1);
	stBinOut->item[0].nBinOut[0]=0xffffffff;
	stBinOut->item[0].nBinOut[1]=0xffffffff;
	stBinOut->item[0].nDelayTime=pTmt->m_oIEDParas.m_nFaultPreTime*50000;

	int nBoNum=0;
	for(int nExBo=0;nExBo<oSwitchPara.oSWITCHINFO[0].m_nBoCount;nExBo++)
	{
		int nIndex=0;
		if(nExBo>31)
			nIndex=1;

		switch(pTmt->m_oIEDParas.m_nTestType)
		{
		case SOEMode:
			if(otmt_IEDPara.m_binOut[nExBo+8].nState==1)
			{
				stBinOut->item[0].nType[nIndex]|=1<<nExBo;
				stBinOut->item[0].nBeginTime[nExBo]=nBoNum*pTmt->m_oIEDParas.m_nOutputTime*50000;
				nBoNum++;
			}
			stBinOut->item[0].param[nExBo].nTmHigh=pTmt->m_oIEDParas.m_nBoKeepTime*50000;
			stBinOut->item[0].param[nExBo].nTmLow=pTmt->m_oIEDParas.m_nBoKeepTime*50000;
			stBinOut->item[0].param[nExBo].nflipCnt=2;
			break;
		case RepeatMode:
			if(otmt_IEDPara.m_binOut[nExBo+8].nState==1)
				stBinOut->item[0].nType[nIndex]|=1<<nExBo;
			stBinOut->item[0].param[nExBo].nTmHigh=pTmt->m_oIEDParas.m_nBoKeepTime*50000;
			stBinOut->item[0].param[nExBo].nTmLow=pTmt->m_oIEDParas.m_nBoKeepTime*50000;
			stBinOut->item[0].param[nExBo].nflipCnt=pTmt->m_oIEDParas.m_nRepeatCount;
			break;
		case DelayMode:
			if(otmt_IEDPara.m_binOut[nExBo+8].nState==1)
				stBinOut->item[0].nBinOut[nIndex]&= ~(1<<nExBo);
			break;
		}
	}

	stBinOut->tm_h = 1000000;
	ioctl(m_nCommfd, 0x340, 0);
	write(m_nCommfd, (char*)stBinOut, sizeof(Drv_SoePara));
}

void CSttDevicePNI302::ProIEDTestDrvResult_B2G(tmt_IEDTest *pTmt,tmt_IEDPara *pPrePara)
{
	CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
	char *pDrvResults=stt_test_init_result_buff();
	int nRet = read(m_nCommfd,pDrvResults,0x240);
	if(nRet < 0)
	{
		return;
	}

	Drv_SoeResults oDrvSoeResults;
	int nLen=sizeof(Drv_SoeResults);
	int nSize = nRet/nLen;
	double nTestTime;

	long nRealTimeEventCount = 0;
	SwitchModules oSwitchPara=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	for(int i = 0;i<nSize;i++)
	{
		memcpy(&oDrvSoeResults,pDrvResults+i*nLen,nLen);

		nTestTime=oDrvSoeResults.tm_h+oDrvSoeResults.tm_l*0.000000001;
		if(oDrvSoeResults.nType==1)
		{
			pSttTestBase->m_dTestStartTime=nTestTime;
			pSttTestBase->ReturnTestStateEvent_TestStart(pSttTestBase->m_dTestStartTime, 0, TRUE);
		}
		else if(oDrvSoeResults.nType==3)
		{
			//开出变位
			int nPreVal=0;
			int nCurVal=0;
			STT_TEST_EVENT oEvent;
			oEvent.oTime.dTime=nTestTime;
			oEvent.oTime.dRealTime=nTestTime- pSttTestBase->m_dTestStartTime;
			int nEventIndex=0;

			for(int nIndex=0;nIndex<oSwitchPara.oSWITCHINFO[0].m_nBoCount;nIndex++)
			{
				nPreVal=pPrePara->m_binOut[nIndex+8].nState;
				nCurVal=pTmt->m_oIEDParas.m_otmt_IEDPara[0].m_binOut[nIndex+8].nState;
				if(nPreVal!=nCurVal)
				{
					oEvent.oEventInfo[nEventIndex].nType=SttResult_Type_Bout;
					oEvent.oEventInfo[nEventIndex].nStateIndex=-1;
					oEvent.oEventInfo[nEventIndex].nStepIndex=-1;
					oEvent.oEventInfo[nEventIndex].nChannel=nIndex+9;
					oEvent.oEventInfo[nEventIndex].nValue=nCurVal;
					nEventIndex++;
//					stt_add_test_event(Result_Type_Bout, -1, -1, nIndex+9, nCurVal, nTestTime,nTestTime- pSttTestBase->m_dTestStartTime);
//					nRealTimeEventCount++;
				}
			}

			if(nEventIndex>0)
			{
				oEvent.nEventInfoCnt=nEventIndex;
				stt_add_test_event(oEvent);
				nRealTimeEventCount++;
			}
			memcpy(pPrePara,&pTmt->m_oIEDParas.m_otmt_IEDPara[0],sizeof(tmt_IEDPara));
		}
	}
	if(nRealTimeEventCount>0)
	{
		pSttTestBase->ReturnRealTimeEvent();
	}
}

void CSttDevicePNI302::SetIEDTestStart_G2B()
{
	ioctl(m_nCommfd,0xA00,1);
	ioctl(m_nCommfd, 0x402, 0);
	ioctl(m_nCommfd, 0x103, 0xc);
}

void CSttDevicePNI302::SetIEDTestStop_G2B()
{
	structGSOutMap *stMaps=m_oCIEC61850CfgMngr.stMaps;
	ioctl(m_nCommfd, 0x30E, 1);
	write(m_nCommfd, (char*)stMaps, sizeof(structGSOutMap));
}

void CSttDevicePNI302::tmt_to_drv_iedtest_G2B(tmt_IEDTest *pTmt)
{
	//Iec61850CfgMngr解析GOOSE发布配置时已将开关量模块实际端子与虚端子对应
	//超过实际端子数量的虚端子未被下载至驱动
	//GOOSE订阅的虚端子也与实际端子对应,B2G走的录波通道未订阅虚端子
	CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
	char* pszBuf=stt_test_get_global_buff();
	structGSOutMap *stMaps=m_oCIEC61850CfgMngr.stMaps;
	int nMode=0;
	switch(pTmt->m_oIEDParas.m_nTestType)
	{
	case SOEMode:
	{
		if(!pSttTestBase->GetTestStarting())
		{
			structGSOutMap *pGSOutMap=(structGSOutMap *)pszBuf;
			memcpy(pGSOutMap,stMaps,sizeof(structGSOutMap));
			int nBoCount=0;
			for(int i=0;i<64;i++)
			{
				if(nBoCount>2)
				{
					pGSOutMap->boMd[1].info[i].cnt=0;
					continue;
				}

				if(pGSOutMap->boMd[1].info[i].cnt>0)
				{
					nBoCount++;
				}
			}			

			ioctl(m_nCommfd, 0x30E, 1);
			write(m_nCommfd, (char*)pGSOutMap, sizeof(structGSOutMap));
		}
	}
		nMode=2;
		break;
	case RepeatMode:
		if(!pSttTestBase->GetTestStarting())
		{
			ioctl(m_nCommfd, 0x30E, 1);
			write(m_nCommfd, (char*)stMaps, sizeof(structGSOutMap));
		}
		nMode=1;
		break;
	case DelayMode:
		if(!pSttTestBase->GetTestStarting())
		{
			ioctl(m_nCommfd, 0x30E, 1);
			write(m_nCommfd, (char*)stMaps, sizeof(structGSOutMap));
		}
		nMode=0;
		break;
	}

	if(!pSttTestBase->GetTestStarting())
	{
		ioctl(m_nCommfd, 0x133, nMode);
	}

	Drv_SoePara *stBinOut=(Drv_SoePara *)pszBuf;
	memset(stBinOut,0,sizeof(Drv_SoePara));
	stBinOut->nModuleCnt=5;
	stBinOut->item[1].nDelayTime=pTmt->m_oIEDParas.m_nFaultPreTime*50000;
	int nBoNum=0;
	SwitchModules  oSwitchPara=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	for(int i=0;i<oSwitchPara.oSWITCHINFO[0].m_nBoCount;i++)
	{
		stBinOut->item[1].param[i].nTmHigh=pTmt->m_oIEDParas.m_nBoKeepTime*50000;
		stBinOut->item[1].param[i].nTmLow=pTmt->m_oIEDParas.m_nBoKeepTime*50000;
		stBinOut->item[1].param[i].nflipCnt=pTmt->m_oIEDParas.m_nRepeatCount;

		if(stMaps->boMd[1].info[i].cnt>0)
		{
			stBinOut->item[1].nBeginTime[i]=nBoNum*pTmt->m_oIEDParas.m_nOutputTime*50000;
			nBoNum++;
		}
	}	

	stBinOut->item[1].nBinOut[0]=0xffffffff;
	stBinOut->item[1].nBinOut[1]=0xffffffff;

	if(nMode==0)
	{
		if(oSwitchPara.oSWITCHINFO[0].m_nBoCount<32)
		{
			for(int i=0;i<oSwitchPara.oSWITCHINFO[0].m_nBoCount;i++)
			{
				if(pTmt->m_oIEDParas.m_otmt_IEDPara[0].m_binOut[i+8].nState>0)
				{
					stBinOut->item[1].nBinOut[0]&= ~(1<<i);
				}
			}
		}
		else
		{
			for(int i=0;i<32;i++)
			{
				if(pTmt->m_oIEDParas.m_otmt_IEDPara[0].m_binOut[i+8].nState>0)
				{
					stBinOut->item[1].nBinOut[0]&= ~(1<<i);
				}
			}

			for(int i=32;i<oSwitchPara.oSWITCHINFO[0].m_nBoCount;i++)
			{
				if(pTmt->m_oIEDParas.m_otmt_IEDPara[0].m_binOut[i+8].nState>0)
				{
					stBinOut->item[1].nBinOut[1]&=~(1<<(i-32));
				}
			}
		}
	}

	ioctl(m_nCommfd,0x341,0);
	write(m_nCommfd,(char*)stBinOut,sizeof(Drv_SoePara));
}

void CSttDevicePNI302::ProIEDTestDrvResult_G2B(tmt_IEDTest *pTmt,tmt_IEDPara *pPrePara)
{
	CSttTestBase *pSttTestBase=CSttServerTestCtrlCntr::GetCurrTest();
	char *pDrvResults=stt_test_get_result_buff();

	int nLen=sizeof(Drv_SoeResults);
	int nRet = read(m_nCommfd,pDrvResults,0x240);
	if(nRet < 0)
	{
		return;
	}

	int nSize = nRet/nLen;
	double nTestTime;

	Drv_SoeResults oDrvSoeResults;
	long nRealTimeEventCount = 0;

	SwitchModules oSwitchPara=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	for(int i = 0;i<nSize;i++)
	{
		memcpy(&oDrvSoeResults,pDrvResults+i*nLen,nLen);
		nTestTime=oDrvSoeResults.tm_h+oDrvSoeResults.tm_l*0.000000001;

		m_strCurrBiVal=QString("%1").arg(oDrvSoeResults.item[1].bi[1],32,2,QChar('0'));
		m_strCurrBiVal+=QString("%1").arg(oDrvSoeResults.item[1].bi[0],32,2,QChar('0'));
		m_strCurrBiVal=m_strCurrBiVal.mid(0,oSwitchPara.oSWITCHINFO[0].m_nBiCount);

		switch(oDrvSoeResults.nType)
		{
		case 1:
		{
			m_strPreBiVal=QString("%1").arg((unsigned int)0xffffffff,32,2,QChar('0'));
			m_strPreBiVal+=QString("%1").arg((unsigned int)0xffffffff,32,2,QChar('0'));
			m_strPreBiVal=m_strPreBiVal.mid(0,oSwitchPara.oSWITCHINFO[0].m_nBiCount);
			pSttTestBase->m_dTestStartTime=nTestTime;

			for(int nIndex=0;nIndex<oSwitchPara.oSWITCHINFO[0].m_nBiCount;nIndex++)
			{
				m_oSTTSoeResult.item[1].fChgTime[nIndex]=0.0;
			}

			pSttTestBase->ReturnTestStateEvent_TestStart(pSttTestBase->m_dTestStartTime, 0, TRUE);

			qDebug()<<"TestStart BiVal"<<m_strPreBiVal;
		}
			continue;
		case 3:
		{
			if(pTmt->m_oIEDParas.m_nTestType==DelayMode)
			{
				//开出变位
				int nPreVal=0;
				int nCurVal=0;
				STT_TEST_EVENT oEvent;
				oEvent.oTime.dTime=nTestTime;
				oEvent.oTime.dRealTime=nTestTime- pSttTestBase->m_dTestStartTime;
				int nEventIndex=0;
				for(int nIndex=0;nIndex<oSwitchPara.oSWITCHINFO[0].m_nBoCount;nIndex++)
				{
					nPreVal=pPrePara->m_binOut[nIndex+8].nState;
					nCurVal=pTmt->m_oIEDParas.m_otmt_IEDPara[0].m_binOut[nIndex+8].nState;
					if(nPreVal!=nCurVal)
					{
						oEvent.oEventInfo[nEventIndex].nType=SttResult_Type_Bout;
						oEvent.oEventInfo[nEventIndex].nStateIndex=-1;
						oEvent.oEventInfo[nEventIndex].nStepIndex=-1;
						oEvent.oEventInfo[nEventIndex].nChannel=nIndex+9;
						oEvent.oEventInfo[nEventIndex].nValue=nCurVal;
						nEventIndex++;
//						stt_add_test_event(Result_Type_Bout, -1, -1, nIndex+9, nCurVal, nTestTime,nTestTime- pSttTestBase->m_dTestStartTime);
//						nRealTimeEventCount++;
					}
				}
				if(nEventIndex>0)
				{
					oEvent.nEventInfoCnt=nEventIndex;
					stt_add_test_event(oEvent);
					nRealTimeEventCount++;
				}
				for(int nIndex=0;nIndex<(8+oSwitchPara.oSWITCHINFO[0].m_nBoCount);nIndex++)
				{
					pPrePara->m_binOut[nIndex].nState=pTmt->m_oIEDParas.m_otmt_IEDPara[0].m_binOut[nIndex].nState;
				}
			}
		}
			continue;
		case 4:
			break;
		}

		for(int nIndex=0;nIndex<oSwitchPara.oSWITCHINFO[0].m_nBiCount;nIndex++)
		{
			m_bChgChan[nIndex]=false;
		}

		qDebug()<<"Result  PreBI"<< m_strPreBiVal;
		qDebug()<<"Result CurrBI"<< m_strCurrBiVal;

		if(m_strPreBiVal.compare(m_strCurrBiVal)==0)
			continue;

		GetChgNum(m_strPreBiVal,m_strCurrBiVal,m_bChgChan);

		STT_TEST_EVENT oEvent;
		oEvent.oTime.dTime=nTestTime;
		oEvent.oTime.dRealTime=nTestTime- pSttTestBase->m_dTestStartTime;
		int nEventIndex=0;
		for(int nIndex=0;nIndex<oSwitchPara.oSWITCHINFO[0].m_nBiCount;nIndex++)
		{
			oEvent.oEventInfo[nEventIndex].nType=SttResult_Type_Bin;
			oEvent.oEventInfo[nEventIndex].nStateIndex=-1;
			oEvent.oEventInfo[nEventIndex].nStepIndex=-1;
			oEvent.oEventInfo[nEventIndex].nChannel=nIndex+9;

			if(m_bChgChan[nIndex])
			{
				switch(pTmt->m_oIEDParas.m_nTestType)
				{
				case DelayMode:
				{
					int nCurrBitVal=m_strCurrBiVal.right(nIndex+1).left(1).toInt();
					oEvent.oEventInfo[nEventIndex].nValue=(nCurrBitVal+1)%2;
					nEventIndex++;
//					stt_add_test_event(Result_Type_Bin, -1, -1, nIndex+9, (nCurrBitVal+1)%2, nTestTime,nTestTime- pSttTestBase->m_dTestStartTime);
//					nRealTimeEventCount++;
				}
					break;
				case SOEMode:
				{
					if(m_oSTTSoeResult.item[1].fChgTime[nIndex]<0.01)
					{
						m_oSTTSoeResult.item[1].fChgTime[nIndex]=nTestTime;
						oEvent.oEventInfo[nEventIndex].nValue=1;
						nEventIndex++;
//						stt_add_test_event(Result_Type_Bin, -1, -1, nIndex+9, 1, nTestTime,nTestTime- pSttTestBase->m_dTestStartTime);
//						nRealTimeEventCount++;
					}
					else
					{
						m_oSTTSoeResult.item[1].fBackTime[nIndex]=nTestTime;
						oEvent.oEventInfo[nEventIndex].nValue=0;
						nEventIndex++;
//						stt_add_test_event(Result_Type_Bin, -1, -1, nIndex+9, 0, nTestTime,nTestTime- pSttTestBase->m_dTestStartTime);
//						nRealTimeEventCount++;
					}
				}
					break;
				}
			}
		}

		if(nEventIndex>0)
		{
			oEvent.nEventInfoCnt=nEventIndex;
			stt_add_test_event(oEvent);
			nRealTimeEventCount++;
		}

		m_strPreBiVal=m_strCurrBiVal;
	}

	if(nRealTimeEventCount>0)
		pSttTestBase->ReturnRealTimeEvent();
}

void CSttDevicePNI302::GetChgNum(CString strPreBiVal,CString strCurrBiVal,bool *bChgChan)
{
	CString strPreBitVal;
	CString strCurrBitVal;

	SwitchModules oSwitchPara=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	for(int nIndex=0;nIndex<oSwitchPara.oSWITCHINFO[0].m_nBiCount;nIndex++)
	{
		strPreBitVal=strPreBiVal.right(nIndex+1).left(1);
		strCurrBitVal=strCurrBiVal.right(nIndex+1).left(1);

		if(CString::compare(strPreBitVal,strCurrBitVal)!=0)
			bChgChan[nIndex]=TRUE;
	}
}
//-----------IEDTest-----------------
