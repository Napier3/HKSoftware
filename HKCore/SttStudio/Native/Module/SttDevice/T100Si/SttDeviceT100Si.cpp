#include "SttDeviceT100Si.h"

const long VoltDrvPos_T100Si[6]={1,0,5,4,3,2};
const long CurrentDrvPos_T100Si[6]={5,4,1,0,3,2};

CSttDeviceT100Si *CSttDeviceT100Si::g_pSttDeviceT100Si=NULL;
long CSttDeviceT100Si::g_nSttDeviceRef = 0;

CSttDeviceT100Si::CSttDeviceT100Si()
{

}

CSttDeviceT100Si::~CSttDeviceT100Si()
{

}

void CSttDeviceT100Si::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDeviceT100Si=new CSttDeviceT100Si;
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDeviceT100Si;
	}
}

void CSttDeviceT100Si::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDeviceT100Si;
		g_pSttDeviceT100Si = NULL;
	}
}

int CSttDeviceT100Si::InitDevice(BOOL bHasAdjFile)
{
	m_nCommfd=open("/dev/SttDriver_T100Si",O_RDWR);
	g_nmaplen = 7782528;
	g_start = (unsigned int *)mmap(NULL, g_nmaplen, PROT_WRITE, MAP_SHARED, m_nCommfd, 0);

	g_theSystemConfig->m_nHasDigital=0;
	InitDApara(m_nCommfd,bHasAdjFile);

	return m_nCommfd;
}

//////////////////////////////////////////////////

void CSttDeviceT100Si::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,BOOL IsVolt)
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

		if(IsVolt)
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
	if(IsVolt)
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

	if(!IsVolt)
	{
		if(tempMax>75)
		{
			g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[0].m_nIPowerMode=STT_CurrentMODULE_POWER_LOW;
			SetSystemConfig();
			CSttDeviceBase::g_pSttDeviceBase->InitDAData();
			CSttDeviceBase::g_pSttDeviceBase->WriteDApara();
		}

		if(tempMax>84)
		{
			g_theSttDeviceStatus->m_bNeedStop=TRUE;
		}
	}

	//PTU200L FPGA 未完善以下标识功能
	oModuleStatus.m_nIsVoltHot=0;
	oModuleStatus.m_nIsDCHot=0;
	oModuleStatus.m_nIsVoltWarining=0;
	oModuleStatus.m_nIsMissWarining=0;
	for(int j=1;j<7;j++)
	{
		oModuleStatus.m_oChannel[j-1].m_bIsOverLoad=0;//过载
	}
}

void CSttDeviceT100Si::tmt_to_drv_manu(tmt_ManualTest *pTmt,BOOL bIsStartTest)
{
	for(int i=0;i<8;i++)
	{
		m_oCurBout.m_binOut[i].nState=pTmt->m_oManuParas.m_binOut[i].nState;
	}

	char *pszDrv=stt_test_get_global_buff();
	if(pTmt->m_oManuParas.m_bAuto)
	{
		CSttDeviceBase::g_pSttDeviceBase->m_bCurTestIsGradient=TRUE;
		tmt_GradientParas oGradientParas;
		oGradientParas.m_nSttTestMode = GradientTest_Base;
		oGradientParas.m_nTestMode = pTmt->m_oManuParas.m_manuGradient.nMode;
		oGradientParas.m_nType = pTmt->m_oManuParas.m_nGradientTpSelect;
		oGradientParas.m_nChannel = pTmt->m_oManuParas.m_nGradientChSelect;
		oGradientParas.m_fStart = pTmt->m_oManuParas.m_manuGradient.fStart;
		oGradientParas.m_fStop = pTmt->m_oManuParas.m_manuGradient.fEnd;
		oGradientParas.m_fStep = pTmt->m_oManuParas.m_manuGradient.fStep;
		oGradientParas.m_fStepTime = pTmt->m_oManuParas.m_manuGradient.fStepTime;
		oGradientParas.m_nBinLogic = pTmt->m_oManuParas.m_nBinLogic;
		for(int nBiIndex=0;nBiIndex<MAX_BINARYIN_COUNT;nBiIndex++)
		{
			memcpy(&oGradientParas.m_binIn[nBiIndex],
				   &pTmt->m_oManuParas.m_binIn[nBiIndex],sizeof(tmt_BinaryIn));
			memcpy(&oGradientParas.m_binOut[0][nBiIndex],
					&pTmt->m_oManuParas.m_binOut[nBiIndex],sizeof(tmt_BinaryOut));
			memcpy(&oGradientParas.m_binOut[1][nBiIndex],
					&pTmt->m_oManuParas.m_binOut[nBiIndex],sizeof(tmt_BinaryOut));
		}

		for(int i=0;i<MAX_VOLTAGE_COUNT;i++)
		{
			oGradientParas.m_uiVOL[0][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAmp;
			oGradientParas.m_uiVOL[0][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAngle;
			oGradientParas.m_uiVOL[0][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fFreq;

			oGradientParas.m_uiVOL[1][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAmp;
			oGradientParas.m_uiVOL[1][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAngle;
			oGradientParas.m_uiVOL[1][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fFreq;

			oGradientParas.m_uiVOL[2][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAmp;
			oGradientParas.m_uiVOL[2][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAngle;
			oGradientParas.m_uiVOL[2][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fFreq;
		}
		for(int i=0;i<MAX_CURRENT_COUNT;i++)
		{
			oGradientParas.m_uiCUR[0][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;
			oGradientParas.m_uiCUR[0][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAngle;
			oGradientParas.m_uiCUR[0][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fFreq;

			oGradientParas.m_uiCUR[1][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;
			oGradientParas.m_uiCUR[1][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAngle;
			oGradientParas.m_uiCUR[1][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fFreq;

			oGradientParas.m_uiCUR[2][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;
			oGradientParas.m_uiCUR[2][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAngle;
			oGradientParas.m_uiCUR[2][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fFreq;
		}

		memcpy(&m_oGradientParas,&oGradientParas,sizeof(tmt_GradientParas));

		if(pTmt->m_oManuParas.m_bDC)
		{
			Gradient_Manu_Harm(pszDrv,oGradientParas,0,0);
		}
		else
		{
			Gradient_Manu_Harm(pszDrv,oGradientParas);
		}

		int nDirection=0;
		float fGradientAmp;
		if(oGradientParas.m_nType==GRADIENT_AMP)
		{
			if(oGradientParas.m_fStart > oGradientParas.m_fStop)
			{
				nDirection=-1;
				fGradientAmp=oGradientParas.m_fStart;
			}
			else
			{
				nDirection=1;
				fGradientAmp=oGradientParas.m_fStop;
			}
		}
		CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Comm(pTmt->m_oManuParas.m_uiVOL,
														   pTmt->m_oManuParas.m_uiCUR,1,pTmt->m_oManuParas.m_bDC,nDirection,1,fGradientAmp);
		return;
	}

	Drv_ManuData *pDrv=(Drv_ManuData *)pszDrv;
	memset(pDrv,0,sizeof(Drv_ManuData));

	Drv_ManuBin oBiSetting;
	memset(&oBiSetting,0,sizeof(Drv_ManuBin));
	oBiSetting.nBinIsStop = false;

	if(pTmt->m_oManuParas.m_bBinStop)
	{
		oBiSetting.nBinIsStop = true;//开入停止
	}
	oBiSetting.nMdelay = pTmt->m_oManuParas.m_manuGradient.fTrigDelay*1000;

	SetTestCommBi(oBiSetting.oTrip,pTmt->m_oManuParas.m_nBinLogic,
				  pTmt->m_oManuParas.m_binIn,pTmt->m_oManuParas.m_binInEx);

	SetManualBI((char*)&oBiSetting,sizeof(Drv_ManuBin));

	Manual_volt_current(pTmt->m_oManuParas.m_uiVOL,pszDrv,1,pTmt->m_oManuParas.m_bDC);

	SetTestCommBo(pDrv->oDrvComBoSta,pTmt->m_oManuParas.m_binOut,pTmt->m_oManuParas.m_binOutEx);

//	if(g_theSystemConfig->m_nHasAnalog!=0)
//	{
//		CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Comm(pTmt->m_oManuParas.m_uiVOL,
//														   pTmt->m_oManuParas.m_uiCUR,1,pTmt->m_oManuParas.m_bDC,0,0,0);
//	}
	ioctl(m_nfd,0x300,0);
	write(m_nfd,pszDrv,sizeof(Drv_ManuData));
}

void CSttDeviceT100Si::GetBoardInfo(BOOL bHasAdjFile)
{
	if(g_theSttDeviceStatus==NULL)
		g_theSttDeviceStatus=new STT_DEVICE_STATUS;

	memset(g_theSttDeviceStatus,0,sizeof(STT_DEVICE_STATUS));
	memset(&m_oBoardinfo,0,sizeof(Drv_BoardVersion));

	read(m_nfd,(char*)&m_oBoardinfo,0x209);

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("MainBoardInfo[%08x] Ver=%s"),
							   m_oBoardinfo.version[0],TransVersion(m_oBoardinfo.version[0]).GetString());
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("DriverInfo[%08x]    Ver=%s"),
							   m_oBoardinfo.version[13],TransVersion(m_oBoardinfo.version[13]).GetString());

	if(!bHasAdjFile)
	{
		//根据硬件实际情况创建最简的系数文件信息
		g_theDeviceSystemParameter->m_nModuleCount=0;
		g_theDeviceSystemParameter->m_nModuleCount_U=0;
		g_theDeviceSystemParameter->m_nModuleCount_I=0;
		g_theDeviceSystemParameter->m_nModuleCount_D=0;
		g_theDeviceSystemParameter->m_nModuleCount_FT3=0;
		g_theDeviceSystemParameter->m_nModuleCount_S=0;
		g_theDeviceSystemParameter->m_nModuleCount_WEEK=0;
		g_theDeviceSystemParameter->m_nModuleCount_UI=0;

		//根据硬件实际情况创建最简的系数文件信息
		g_theDeviceSystemParameter->m_nModuleCount = 1;
		g_theDeviceSystemParameter->m_nModuleCount_UI=1;
		g_theDeviceSystemParameter->m_oModules[0].m_oModuleAttr.m_nModuleType=STT_MODULE_TYPE_VOLT_CURRENT;
		g_theDeviceSystemParameter->m_oModules[0].m_oModuleAttr.m_nModuleIndex=1;
		g_theDeviceSystemParameter->m_oModules[0].m_oModuleAttr.m_nDisable=0;
	}

	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strFPGAVer,
		   TransVersion(m_oBoardinfo.version[0]).GetString());
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDriverVer,
		   TransVersion(m_oBoardinfo.version[13]).GetString());
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strAppName,APP_NAME);
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDriverName,DRV_NAME);

	CSttDeviceBase::g_pSttDeviceBase->m_bDevStaIsInit=TRUE;
}


void CSttDeviceT100Si::TransAnalogDCToDrv(float fAmp,int nChannel,long *pDrvData)
{
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_UI[0];
	if(pModule==NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fChMax=pModule->m_oModuleAttr.m_fChMax;
	float fChDcMax=pModule->m_oModuleAttr.m_fChDcMax;
	if(fChMax>0&&fChDcMax>0)
	{

	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	float fVoltMax=stt_adj_get_ac_max_GearVal(nChannel,0,STT_MODULE_TYPE_VOLT,0);
	if(fVoltMax>0)
	{
		fVoltMax=qMin(fVoltMax,fChDcMax);
		if(fabs(fAmp)>fVoltMax)
		{
			if(fAmp>0)
				fAmp=fVoltMax;
			else
				fAmp=fVoltMax*(-1);
		}
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}
	/*************确定合适的fAmp值************/


	/*************fAmp值补偿************/
	float fTemperature=0;//getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust=stt_adj_find_channel(STT_MODULE_TYPE_VOLT,0,nChannel,fTemperature);
	float fCoef=stt_adj_get_ac_u_coef(fabs(fAmp),0,nChannel,fTemperature,0);//幅值系数
	float fZero=pChsAdjust->m_fDcZero;//直流零漂

	fAmp = fAmp*fCoef-fZero;
	/*************fAmp值补偿************/


	/*************fAmp值转FPGA参数************/
	fChMax=fChMax*1.414;
	if(fabs(fAmp)>EPSINON)
	{
		long nH = fAmp*32768/fChMax;//65536/2=32768
		double fH = fAmp*32768/fChMax;
		long nL = (fH - nH)*65536;
		pDrvData[0] = ((nH<<16)&0xFFFF0000)+nL;//补偿效果依赖于硬件的输出分辨率
	}
	else
	{
		pDrvData[0] = 0;
	}
	/*************fAmp值转FPGA参数************/
}

long CSttDeviceT100Si::TranslateACAmp(float fAmp,int nChannel,int nHarm)
{
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_UI[0];
	if(pModule==NULL)
		return 0;

	//fChMax算幅值做分母
	float fChMax=pModule->m_oModuleAttr.m_fChMax;
	if(fChMax>0)
	{

	}
	else
		return 0;

	/*************确定合适的fAmp值************/
	//fVoltMax限制fAmp的最大值
	float fVoltMax=stt_adj_get_ac_max_GearVal(nChannel,0,STT_MODULE_TYPE_VOLT,nHarm);
	if(fVoltMax>0)
	{
		fVoltMax=qMin(fVoltMax,fChMax);
		if(fAmp>fVoltMax)
			fAmp=fVoltMax;
	}
	else
	{
		return 0;
	}
	/*************确定合适的fAmp值************/


	/*************fAmp值补偿************/
	float fTemperature=0;//getTemperature();
	PSTT_ADJUST_ITEM pAdjItem=stt_adj_get_ac_u(fAmp,0,nChannel,fTemperature,nHarm);
	float fCoef=1;//幅值系数
	float fZero=0;//交流零漂
	if(pAdjItem!=NULL)
	{
		fCoef=pAdjItem->m_fCoef;
		fZero=pAdjItem->m_fZero;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);

	fAmp =fAmp*fCoef+fZero;
	/*************fAmp值补偿************/

	/*************fAmp值转FPGA参数************/
	if(fAmp>0)
	{
		if(fAmp<fChMax)
		{
			long nH = fAmp*65536/fChMax;
			double fH = fAmp*65536/fChMax;
			long nL = (fH - nH)*65536;

			return ((nH<<16)&0xFFFF0000)+nL;
		}
		else
		{
			return 0xFFFFFFFF;
		}
	}
	else
		return 0;
	/*************fAmp值转FPGA参数************/
}

void CSttDeviceT100Si::TransAnalogToDrv(float fAmp,float fAng,float fFre,int nChannel,
										 long *pnDrvData)
{
	int nHarm=0;
	int m_nEDFre=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	if(m_nEDFre<EPSINON)
		m_nEDFre=50;

	if(fFre<EPSINON)
	{
		//AC通道出DC
		pnDrvData[0] = 0;
		pnDrvData[1] = 0;
		TransAnalogDCToDrv(fAmp,nChannel,&pnDrvData[2]);
		return;
	}
	fAmp=fabs(fAmp);

	if(fFre<=m_nEDFre)
	{
		nHarm = 0;
	}
	else
	{
		nHarm  = (fFre+25)/m_nEDFre - 1;
	}

	float fTemperature=0;//getTemperature();
	float faddPh = stt_adj_get_ac_u_angle(50,0,nChannel,fTemperature);
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
	float fFreCoef=1;
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_UI[0];
	if(pModule!=NULL)
	{
		fFreCoef=pModule->m_oModuleAttr.m_fFreCoef;
	}
	pnDrvData[1] = TranslateACFre(fFre*fFreCoef);
	pnDrvData[2] = TranslateACAmp(fAmp,nChannel,nHarm+1);
}

void CSttDeviceT100Si::Manual_volt_current(tmt_channel *pTmt_channel,char *pszDrv,int nHarm,
								 BOOL bIsDc,BOOL bIsModuleOutput)
{
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_UI[0];
	if(pModule==NULL)
		return;

	Drv_ManuData *pDrv=(Drv_ManuData *)pszDrv;
	int nChPos;
	float fAmp=0;

	long *dat=&pDrv->oDrv_HarmParam[0].dat[0];
	m_nTmtChanNum=pModule->m_oModuleAttr.m_nChannelNum;
	if(bIsDc)
	{
		for(int k=0; k<m_nTmtChanNum; k++)
		{
			m_nTmtPos=k;
			if(!bIsModuleOutput)
			{
				m_nTmtPos=pModule->m_nChTmtPos[k];
			}
			if(m_nTmtPos<0)
				fAmp=0;
			else
				fAmp=pTmt_channel[m_nTmtPos].Harm[1].fAmp;
			nChPos=pModule->m_nChDrvPos[k];

//			TransAnalogDCVolToDrv(fAmp,k,nModuleUIndex,dat+nChPos);
		}
		pDrv->oDrv_HarmParam[0].nDWcnt=24;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq=0;
		float fAngle=0;
		for(int k=0; k<m_nTmtChanNum; k++)
		{
			m_nTmtPos=k;
			if(!bIsModuleOutput)
			{
				m_nTmtPos=pModule->m_nChTmtPos[k];
			}
			if(m_nTmtPos<0)
				fAmp=0;
			else
				fAmp=pTmt_channel[m_nTmtPos].Harm[0].fAmp;
			nChPos=pModule->m_nChDrvPos[k];

//			TransAnalogDCVolToDrv(fAmp,k,nModuleUIndex,dat+nChPos);

			for(int m=0;m<nHarm;m++)
			{
				if(m_nTmtPos<0)
				{
					fAmp=0;
					fFreq=50;
				}
				else
				{
					oTmtHarm=&pTmt_channel[m_nTmtPos].Harm[m+1];
					fAmp=oTmtHarm->fAmp;
					fAngle=oTmtHarm->fAngle;
					fFreq=oTmtHarm->fFreq;
				}

//				TransAnalogVolToDrv(fAmp,fAngle,
//									fFreq,k,nModuleUIndex,dat+CHANNEL_MAX+nChPos*3+m*3*CHANNEL_MAX);
			}
		}
		pDrv->oDrv_HarmParam[0].nDWcnt=6+nHarm*3*CHANNEL_MAX;
	}

}
