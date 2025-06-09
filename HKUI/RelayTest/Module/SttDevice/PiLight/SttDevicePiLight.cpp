#include "SttDevicePiLight.h"
#include "../../SttTest/PiLight/tmt_light_test.h"
#include "../../SttTest/PiLight/tmt_light_anglectrl.h"

CSttDevicePiLight *CSttDevicePiLight::g_pSttDevicePiLight=NULL;
long CSttDevicePiLight::g_nSttDeviceRef = 0;

unsigned char nAngleData_4Bytes[4+4];
unsigned char nAngleData_6Bytes[4+6];
unsigned char nAngleData_15Bytes[4+15];

#define TestType_Null		0
#define TestType_AngleCtrl	1
#define TestType_Light		2
#define TestType_GetAngle   3

unsigned int g_nTestType;
CSttDevicePiLight::CSttDevicePiLight()
{

}

CSttDevicePiLight::~CSttDevicePiLight()
{

}

void CSttDevicePiLight::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDevicePiLight=new CSttDevicePiLight;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevicePiLight;
	}
}

void CSttDevicePiLight::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDevicePiLight;
		g_pSttDevicePiLight = NULL;
	}
}

int CSttDevicePiLight::InitDevice(BOOL bHasAdjFile)
{
	m_nCommfd=open("/dev/SttDriver_Pi1000",O_RDWR);
	m_pDegressMsg = (Drv_DegressMsg *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, m_nCommfd, 0);
#ifdef _PSX_QT_LINUX_
	qDebug()<<"Driver Mmap = "<<m_pDegressMsg;
#endif

	InitDApara(m_nCommfd,bHasAdjFile);
	ioctl(m_nCommfd,0x110,0);//关闭秒同步减少报文量
	ioctl(m_nCommfd,0x120,0);//关闭主板开关量模块防抖

	Sleep(500);
	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule==NULL)
			continue;

		CSttPowerCtrlBase *pCSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
		if(pCSttPowerCtrlBase==NULL)
			pModule->m_oModuleAttr.m_pPowerCtrlBase=(CSttPowerCtrlBase*)(new CSttPowerCtrlC20);
	}

	nAngleData_4Bytes[0] = 0;
	nAngleData_4Bytes[1] = 0;
	nAngleData_4Bytes[2] = 0;
	nAngleData_4Bytes[3] = 4;
	nAngleData_4Bytes[4] = 0x55;
	nAngleData_4Bytes[5] = 0x03;
	nAngleData_4Bytes[6] = 0x02;
	nAngleData_4Bytes[7] = 0xAA;

	nAngleData_6Bytes[0] = 0;
	nAngleData_6Bytes[1] = 0;
	nAngleData_6Bytes[2] = 0;
	nAngleData_6Bytes[3] = 6;
	nAngleData_6Bytes[4] = 0x55;
	nAngleData_6Bytes[5] = 0x02;
	nAngleData_6Bytes[9] = 0xAA;

	nAngleData_15Bytes[0] = 0;
	nAngleData_15Bytes[1] = 0;
	nAngleData_15Bytes[2] = 0;
	nAngleData_15Bytes[3] = 15;
	nAngleData_15Bytes[4] = 0x55;
	nAngleData_15Bytes[5] = 0x01;
	nAngleData_15Bytes[18] = 0xAA;

	//开始命令
	ioctl(m_nCommfd,0x358,1);
	nAngleData_4Bytes[5] = 0x03;
	nAngleData_4Bytes[6] = 0x01;
	write(m_nfd,(char*)&nAngleData_4Bytes,8);

	//停止命令
	ioctl(m_nCommfd,0x358,2);
	nAngleData_4Bytes[5] = 0x03;
	nAngleData_4Bytes[6] = 0x00;
	write(m_nfd,(char*)&nAngleData_4Bytes,8);

	//读取命令
	ioctl(m_nCommfd,0x358,6);
	nAngleData_4Bytes[5] = 0x04;
	nAngleData_4Bytes[6] = 0x00;
	write(m_nfd,(char*)&nAngleData_4Bytes,8);

	g_nTestType = TestType_Null;
	return m_nCommfd;
}

void CSttDevicePiLight::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,int nModuleType)
{
    CSttDeviceBase::AnalysisDrvSysInfo(oDrv_FeedBack,nModulePos,nModuleType);
	//466插件暂不考虑以下指标
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

	oModuleStatus.m_nIsVoltHot = 0;//电压过热
	oModuleStatus.m_nIsDCHot = 0;//直流过热
	oModuleStatus.m_nIsVoltWarining = 0;//电压告警
	oModuleStatus.m_nIsMissWarining = 0;//失地告警
}

void CSttDevicePiLight::ProLightDrvResult(BOOL &bTestFinished,STT_TIME &oTestFinishedTime)
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	char *pDrvResults=stt_test_get_drvresult_buff();
	int nret;
	if(g_nTestType == TestType_GetAngle)
	{
		nret = read(m_nfd,pDrvResults,0x261);

		if(nret <= 0)
		{
			return;
		}

		if(pDrvResults[0]== 0x05 && pDrvResults[1]== 0x64 && pDrvResults[2]== 0x05 && pDrvResults[3]== 0x64)
		{
			if(pDrvResults[4]== 0x00 && pDrvResults[5]== 0x00 && pDrvResults[6]== 0x00 && pDrvResults[7]== 0x07)
			{
				if(pDrvResults[8]== 0x55 && pDrvResults[9]== 0x04 && pDrvResults[30]== 0xaa)
				{
					g_oLightGetAngle.m_oLightGetAngleResult.m_nTotalCode = pDrvResults[13];
					g_oLightGetAngle.m_oLightGetAngleResult.m_nTotalCode |= pDrvResults[12]<<8;
					g_oLightGetAngle.m_oLightGetAngleResult.m_nTotalCode |= pDrvResults[11]<<16;
					g_oLightGetAngle.m_oLightGetAngleResult.m_nTotalCode |= pDrvResults[10]<<24;

					g_oLightGetAngle.m_oLightGetAngleResult.m_nRingCnt |= pDrvResults[17];
					g_oLightGetAngle.m_oLightGetAngleResult.m_nRingCnt |= pDrvResults[16]<<8;
					g_oLightGetAngle.m_oLightGetAngleResult.m_nRingCnt |= pDrvResults[15]<<16;
					g_oLightGetAngle.m_oLightGetAngleResult.m_nRingCnt |= pDrvResults[14]<<24;

					g_oLightGetAngle.m_oLightGetAngleResult.m_nRingValue |= pDrvResults[21];
					g_oLightGetAngle.m_oLightGetAngleResult.m_nRingValue |= pDrvResults[20]<<8;
					g_oLightGetAngle.m_oLightGetAngleResult.m_nRingValue |= pDrvResults[19]<<16;
					g_oLightGetAngle.m_oLightGetAngleResult.m_nRingValue |= pDrvResults[18]<<24;

					g_oLightGetAngle.m_oLightGetAngleResult.m_nAngle |= pDrvResults[25];
					g_oLightGetAngle.m_oLightGetAngleResult.m_nAngle |= pDrvResults[24]<<8;
					g_oLightGetAngle.m_oLightGetAngleResult.m_nAngle |= pDrvResults[23]<<16;
					g_oLightGetAngle.m_oLightGetAngleResult.m_nAngle |= pDrvResults[22]<<24;

					g_oLightGetAngle.m_oLightGetAngleResult.m_nReserve |= pDrvResults[29];
					g_oLightGetAngle.m_oLightGetAngleResult.m_nReserve |= pDrvResults[28]<<8;
					g_oLightGetAngle.m_oLightGetAngleResult.m_nReserve |= pDrvResults[27]<<16;
					g_oLightGetAngle.m_oLightGetAngleResult.m_nReserve |= pDrvResults[26]<<24;

					g_nTestType = TestType_Null;
					m_bRdDegRtData=FALSE;
					pSttTestBase->SetTestStarting(FALSE);
					bTestFinished=TRUE;
					oTestFinishedTime.dTime=0;
					oTestFinishedTime.dRealTime=0;
				}
			}
		}
	}
	else
	{
		nret = read(m_nfd,pDrvResults,0x203);

		if(nret <= 0)
		{
			return;
		}

		long nRealTimeEventCount = 0;
		BOOL bCalcBinAct = TRUE;
		for(int i=0;i<nret/m_nDrvResItemLen;i++)
		{
			memcpy(&m_oDrvResItem,pDrvResults+i*m_nDrvResItemLen,m_nDrvResItemLen);
			double dTime=m_oDrvResItem.nSec+m_oDrvResItem.nNanoSec*0.000000001;
			switch(m_oDrvResItem.nType)
			{
			case DrvResult_TestStart:
			{
				m_bRdDegRtData=TRUE;
				pSttTestBase->m_dTestStartTime=dTime;
				m_oStepInfo.dTime=dTime;
				m_oStepInfo.dLastBinTime=-1;
				memcpy(&m_oPreBoStatus,&m_oDrvResItem.nBo,sizeof(DrvComBoStatus));

				if(g_nTestType == TestType_Light)
				{
					ProStartBinEvent(m_oDrvResItem.nBi,nRealTimeEventCount,-1,pSttTestBase->m_nCurStepIndex,dTime);
					ProCommBoutEvent(m_oDrvResItem.nBo,nRealTimeEventCount,-1,
									 pSttTestBase->m_nCurStepIndex,dTime,0);
				}

				pSttTestBase->ReturnTestStateEvent_TestStart(pSttTestBase->m_dTestStartTime, 0, TRUE);

				m_oRampRestCom.init();
			}
				break;
			case DrvResult_TestFinish:
			{
				g_nTestType = TestType_Null;
				m_bRdDegRtData=FALSE;
				pSttTestBase->SetTestStarting(FALSE);
				if(!pSttTestBase->IsRecvStopCmd())
				{
					bTestFinished=TRUE;
					oTestFinishedTime.dTime=dTime;
					oTestFinishedTime.dRealTime=dTime-pSttTestBase->m_dTestStartTime;
				}
			}
				break;
			case DrvResult_BI:
			{
				m_oStepInfo.dLastBinTime=dTime;
				ProCommBinEvent(m_oDrvResItem,nRealTimeEventCount,-1,pSttTestBase->m_nCurStepIndex,
								dTime,dTime-pSttTestBase->m_dTestStartTime,bCalcBinAct);
			}
				break;
			case DrvResult_BI_LogicMatch:
			{
				if(m_oRampRestCom.m_fTripTime > 0)
				{
					//开入延时阶段再来开入不计入动作时间
				}
				else
					m_oRampRestCom.m_fTripTime=
							m_oStepInfo.dLastBinTime-m_oStepInfo.dTime;
			}
				break;
			case DrvResult_Output_Change:
			{
				pSttTestBase->m_dTestStartTime=dTime;
				m_oStepInfo.dTime=dTime;
				m_oStepInfo.dLastBinTime=-1;
				pSttTestBase->ReturnTestStateEvent_TestStart(pSttTestBase->m_dTestStartTime, 0, TRUE);

				ProCommBoutEvent(m_oDrvResItem.nBo,nRealTimeEventCount,-1,
								 pSttTestBase->m_nCurStepIndex,dTime,0,FALSE);
				memcpy(&m_oPreBoStatus,&m_oDrvResItem.nBo,sizeof(DrvComBoStatus));
			}
				break;
			case DrvResult_Light_TimeOut:
				SetTestStop();
				break;
			}
		}

	}
}

void CSttDevicePiLight::Light_current(tmt_channel *pTmt_channel,long *dat,float fAngleDiff)
{
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[0];
	if(pModule==NULL)
		return;

	int nChPos;
	float fAmp=0;

	m_nTmtChanNum=pModule->m_oModuleAttr.m_nChannelNum;
	tmt_ChannelHarm *oTmtHarm;
	float fFreq=0;
	float fAngle=0;
	for(int k=0; k<m_nTmtChanNum; k++)
	{
		m_nTmtPos=pModule->m_nChTmtPos[k];

		//DC
		{
			if(m_nTmtPos<0)
				fAmp=0;
			else
				fAmp=pTmt_channel[m_nTmtPos].Harm[0].fAmp;
			nChPos=pModule->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fAmp,k,0,dat+nChPos);
		}

		if(m_nTmtPos<0)
			continue;

		//BASE
		{
			oTmtHarm=&pTmt_channel[m_nTmtPos].Harm[1];
			fAmp=oTmtHarm->fAmp;
			fAngle=oTmtHarm->fAngle + fAngleDiff;
			fFreq=oTmtHarm->fFreq;

			TransAnalogCurToDrv(fAmp,fAngle,
								fFreq,k,0,dat+CHANNEL_MAX+nChPos*3);
		}

		//Harm
		for(int nHarmIndex=1;nHarmIndex < 31;nHarmIndex++)
		{
			for(int j=2;j < 31;j++)
			{
				if(nHarmIndex == pTmt_channel[m_nTmtPos].Harm[j].nSelectIndex)
				{
					oTmtHarm=&pTmt_channel[m_nTmtPos].Harm[j];
					fAmp=oTmtHarm->fAmp;
					fAngle=oTmtHarm->fAngle + fAngleDiff*nHarmIndex;
					fFreq=oTmtHarm->fFreq;

					TransAnalogCurToDrv(fAmp,fAngle,
										fFreq,k,0,dat+CHANNEL_MAX+nChPos*3+nHarmIndex*3*CHANNEL_MAX);

					break;
				}
			}
		}
	}
}

void CSttDevicePiLight::tmt_to_drv_lightpara(void *pVoidTmt)
{
	ioctl(m_nfd,0x100,1);
	g_nTestType = TestType_Light;
	ioctl(m_nfd,0x143,0);//停用模块内系数补偿功能
	Sleep(100);
	m_bCurTestIsGradient = FALSE;
	tmt_LightTest *pTmt=(tmt_LightTest *)pVoidTmt;

	//光源参数
	nAngleData_15Bytes[6] = pTmt->m_oLightPara.m_nMode &0x01;
	nAngleData_15Bytes[7] = (pTmt->m_oLightPara.m_nTime >> 8) &0xFF;
	nAngleData_15Bytes[8] = pTmt->m_oLightPara.m_nTime &0xFF;
	nAngleData_15Bytes[9] = pTmt->m_oLightPara.m_nType &0x01;

	//紫光
	nAngleData_15Bytes[10] = (pTmt->m_oLightPara.m_nData0 >> 24) &0xFF;
	nAngleData_15Bytes[11] = (pTmt->m_oLightPara.m_nData0 >> 16) &0xFF;
	nAngleData_15Bytes[12] = (pTmt->m_oLightPara.m_nData0 >> 8) &0xFF;
	nAngleData_15Bytes[13] = pTmt->m_oLightPara.m_nData0 &0xFF;

	//白光
	nAngleData_15Bytes[14] = (pTmt->m_oLightPara.m_nData1 >> 24) &0xFF;
	nAngleData_15Bytes[15] = (pTmt->m_oLightPara.m_nData1 >> 16) &0xFF;
	nAngleData_15Bytes[16] = (pTmt->m_oLightPara.m_nData1 >> 8) &0xFF;
	nAngleData_15Bytes[17] = pTmt->m_oLightPara.m_nData1 &0xFF;
	ioctl(m_nCommfd,0x358,4);
	write(m_nfd,(char*)&nAngleData_15Bytes,19);

	//电流参数
	char *pszDrv =stt_test_get_drvparas_buff();
	Drv_CurrentData *pDrv=(Drv_CurrentData *)pszDrv;
	memset(pDrv,0,sizeof(Drv_CurrentData));

	pDrv->nBinStop = pTmt->m_oLightPara.m_nBinStop;
	int nModule = g_theDeviceSystemParameter->m_oModules_I[0]->m_oModuleAttr.m_nModuleIndex;
	pDrv->nModule = 1<<(nModule-1);
	pDrv->oTrip.nBiLogic = pTmt->m_oLightPara.m_nBinLogic;
	pDrv->oTrip.oValid.nModuleCount = 1;
	pDrv->oTrip.oValid.item[0].nModule = 0x8000;
	for (int i=0; i<8; i++)
	{
		pDrv->oTrip.oValid.item[0].nVal1 |= pTmt->m_oLightPara.m_binIn[i].nSelect<<i;
	}
	for (int i=0; i<8; i++)//bo
	{
		pDrv->oBoStatus.item[0].nVal1 += ((!pTmt->m_oLightPara.m_binOut[i].nState)<<i);
	}
	pDrv->nBiCtrl = pTmt->m_oLightPara.m_nUseBi;
	int nDelayTime = pTmt->m_oLightPara.m_fDelayTime;
	nDelayTime = nDelayTime/20;
	float fAngleDiff = (pTmt->m_oLightPara.m_fDelayTime - nDelayTime*20)/20*360;
	if(pTmt->m_oLightPara.m_nDelayType == 0)
	{
		//电流超前
		fAngleDiff = -fAngleDiff;
	}
	Light_current(pTmt->m_oLightPara.m_uiCUR,pDrv->dat,fAngleDiff);

	ioctl(m_nCommfd,0x358,5);
	write(m_nfd,pszDrv,sizeof(Drv_CurrentData));//驱动开始输出零值

	//Current
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[0];
	if(pModule!=NULL)
	{
		CSttPowerCtrlBase *pSttPowerCtrlBase=pModule->m_oModuleAttr.m_pPowerCtrlBase;
		if(pSttPowerCtrlBase!=NULL)
		{
			pSttPowerCtrlBase->SetCurrentDA_State(0);
			m_oDAPara.nvolt[g_theDeviceSystemParameter->m_nModuleCount_U] = pSttPowerCtrlBase->GetModuleDA();
		}
	}
	WriteDApara();

	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	if(!pSttTestBase->GetTestStarting())
	{
		pSttTestBase->SetTestStarting(TRUE);
		Sleep(1000);
		ioctl(m_nCommfd,0x145,1);//开始弧光
	}
}

void CSttDevicePiLight::tmt_to_drv_lightangle(void *pVoidTmt,unsigned int nType)
{
	//0-转动 1-清零  2-读角度
	if(nType == 0)
	{
		g_nTestType = TestType_AngleCtrl;
		m_bCurTestIsGradient = FALSE;
		tmt_LightAngleTest *pTmt=(tmt_LightAngleTest *)pVoidTmt;

		//电机超时时间
		unsigned int nData = 0xFFFF0000;
		nData |= pTmt->m_oLightAnglePara.m_nWaitTime &0xFF;
		ioctl(m_nCommfd,0x358,nData);

		//光源角度控制
		nAngleData_6Bytes[6] = (pTmt->m_oLightAnglePara.m_nAngle >> 8) &0xFF;
		nAngleData_6Bytes[7] = pTmt->m_oLightAnglePara.m_nAngle &0xFF;
		nAngleData_6Bytes[8] = pTmt->m_oLightAnglePara.m_nDirection &0x01;
		ioctl(m_nCommfd,0x358,3);
		write(m_nfd,(char*)&nAngleData_6Bytes,10);
	}
	else if(nType == 1)
	{
		nAngleData_4Bytes[5] = 0x03;
		nAngleData_4Bytes[6] = 0x02;
		ioctl(m_nCommfd,0x358,0);
		write(m_nfd,(char*)&nAngleData_4Bytes,8);//初始化
		Sleep(1000);
		CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
		pSttTestBase->SetTestStarting(FALSE);
		pSttTestBase->ReturnTestStateEvent_TestFinish(0,0,FALSE);
	}
	else
	{
		g_nTestType = TestType_GetAngle;
		ioctl(m_nCommfd,0x145,2);//读取弧光角度
	}
}

void CSttDevicePiLight::SetTestStop(BOOL bIsSysDefaultOutput)
{
	g_nTestType = TestType_Null;
	ioctl(m_nCommfd,0x145,0);//停止弧光
}
