#include "SttDevice.h"

CSttDevice *CSttDevice::g_pSttDevice=NULL;
long CSttDevice::g_nSttDeviceRef = 0;
ConverStruct ts;

CSttDevice::CSttDevice(QObject *parent) : QObject(parent)
{
	m_nSampPoints=4000;
	m_pSysInfo=new Drv_SysInfo;
	g_theSttDeviceStatus=new STT_DEVICE_STATUS;
}

void CSttDevice::Create(int fd)
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDevice=new CSttDevice;
		CSttDriverOper::Create(fd);
		g_pSttDevice->InitDevice();
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevice;
	}
}

void CSttDevice::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDevice;
		g_pSttDevice = NULL;
	}
}

void CSttDevice::InitDevice()
{
	QDateTime time = QDateTime::fromString("2020-09-14 00:00:00", "yyyy-MM-dd hh:mm:ss");
	setBCodeTime(time);
	InitDApara();

	//stopDCout
	CSttDriverOper::IoCtrl(0x330,0);

	CSttDriverOper::setSendAtStop(0);
	CSttDriverOper::setPollingsyncsecond(0);//关闭秒同步
	CSttDriverOper::setfiberports(0xff);//0G8M

#ifdef _AT02D_
	CSttDriverOper::setfiberports(0xfc);//2G6M
#endif

	CSttDriverOper::IoCtrl(0x7000003c,1);//开启1588对时

	CSttDriverOper::IoCtrl(0x70004068,0x80008000);
	CSttDriverOper::IoCtrl(0x7000406c,0x80008000);
	CSttDriverOper::IoCtrl(0x70005068,0x80008000);
	CSttDriverOper::IoCtrl(0x7000506c,0x80008000);
	CSttDriverOper::IoCtrl(0x70005070,0x80008000);

	//开入模式
	CSttDriverOper::IoCtrl(0x108,0);
	CSttDriverOper::IoCtrl(0x109,0xffffffff);
	CSttDriverOper::IoCtrl(0x10a,0xff);

	int nBoutDefValue=0;
	for(int nIndex=0;nIndex<8;nIndex++)
	{
		nBoutDefValue+=(!g_theDeviceSystemParameter->m_oBoutTurnOnValue.m_nBout[nIndex])<<nIndex;
	}
	CSttDriverOper::SetBinaryOutTurnOnVaule(nBoutDefValue);
	CSttDriverOper::SetBinaryOut(0xff);
	//防抖时间
	int nTime = 2;//ms
	nTime = nTime*1000000/20;
	CSttDriverOper::IoCtrl(0x120,nTime);

	CSttDriverOper::SetCurrent_Multiple(1);

	memset(g_theSttDeviceStatus,0,sizeof(STT_DEVICE_STATUS));
	memset(&m_oBoardinfo,0,sizeof(Drv_BoardVersion));
	CSttDriverOper::readFlashData((char*)&m_oBoardinfo,0,0);

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("MainBoardInfo[%08x] Ver=%s"),m_oBoardinfo.version[0],TransVersion(m_oBoardinfo.version[0]).GetString());
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("DriverInfo[%08x]    Ver=%s"),m_oBoardinfo.version[9],TransVersion(m_oBoardinfo.version[9]).GetString());

	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strFPGAVer,TransVersion(m_oBoardinfo.version[0]).GetString());
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDriverVer,TransVersion(m_oBoardinfo.version[9]).GetString());

	CString strBoardType;
	for(int i =1;i<9;i++)
	{
		switch(m_oBoardinfo.version[i]>>24)
		{
		case 0xc0:
			strBoardType="Digital-0G ";
			break;
		case 0xc2:
			strBoardType="Digital-2G ";
			break;
		case 0xc4:
			strBoardType="Digital-4G ";
			break;
		case 0x55:
			strBoardType="Volt       ";
			g_theSttDeviceStatus->m_oModule[g_theSttDeviceStatus->m_nAnalogCount].m_nModuleIndex=i;
			g_theSttDeviceStatus->m_oModule[g_theSttDeviceStatus->m_nAnalogCount].m_nModuleType=STT_MODULE_TYPE_VOLT;
			g_theSttDeviceStatus->m_nAnalogCount++;

			for(int nUIndex=0;nUIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nUIndex++)
			{
				if(i==g_theDeviceSystemParameter->m_oModules_U[nUIndex]->m_oModuleAttr.m_nModuleIndex)
				{
					strcpy(g_theDeviceSystemParameter->m_oModules_U[nUIndex]->m_oModuleAttr.m_strFPGAVer,TransVersion(m_oBoardinfo.version[i]).GetString());
					break;
				}
			}
			break;
		case 0xaa:
			strBoardType="Current    ";
			g_theSttDeviceStatus->m_oModule[g_theSttDeviceStatus->m_nAnalogCount].m_nModuleIndex=i;
			g_theSttDeviceStatus->m_oModule[g_theSttDeviceStatus->m_nAnalogCount].m_nModuleType=STT_MODULE_TYPE_CURRENT;
			g_theSttDeviceStatus->m_nAnalogCount++;

			for(int nIIndex=0;nIIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIIndex++)
			{
				if(i==g_theDeviceSystemParameter->m_oModules_I[nIIndex]->m_oModuleAttr.m_nModuleIndex)
				{
					strcpy(g_theDeviceSystemParameter->m_oModules_I[nIIndex]->m_oModuleAttr.m_strFPGAVer,TransVersion(m_oBoardinfo.version[i]).GetString());
					break;
				}
			}
			break;
		case 0xd:
			strBoardType="FT3        ";
			break;
		case 0x99:
			strBoardType="Switch     ";
			break;
		case 0x66:
			strBoardType="DcCurrent  ";
			break;
		default:
			if(m_oBoardinfo.version[i]==0)
				continue;
			strBoardType="unknow     ";
			break;
		}

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Position=%d Type=%s Ver=%s BoardInfo[%08x]"),i,strBoardType.GetString(),TransVersion(m_oBoardinfo.version[i]).GetString(), m_oBoardinfo.version[i]);
	}
}

CString CSttDevice::TransVersion(unsigned int nVal)
{
	CString strBoardVer=CString::number((nVal>>16)&0xff);
	strBoardVer.push_back(".");
	strBoardVer+=CString::number((nVal>>8)&0xff);
	strBoardVer.push_back(".");
	strBoardVer+=CString::number(nVal&0xff);
	return strBoardVer;
}
void CSttDevice::setBCodeTime(QDateTime tm)
{
	uint nYear = tm.date().year();
	uint nMonth = tm.date().month();
	uint nday = tm.date().day();
	uint nhour =tm.time().hour();
	uint nmin = tm.time().minute();
	uint nsecond = tm.time().second();

	uint nY  = 0;
	nY = (nYear/10%10)<<4 | (nYear%10);
	uint nMd = 0;
	uint n2m = 28;

	if(nYear%4==0){
		n2m = 29;
	}
	switch (nMonth) {
	case 1:
		nMd = 0;
		break;
	case 2:
		nMd = 31;
		break;
	case 3:
		nMd = 31+ n2m;
		break;
	case 4:
		nMd = 31+n2m+31;
		break;
	case 5:
		nMd = 31+n2m+31+30;
		break;
	case 6:
		nMd = 31+n2m+31+30+31;
		break;
	case 7:
		nMd = 31+n2m+31+30+31+30;
		break;
	case 8:
		nMd = 31+n2m+31+30+31+30+31;
		break;
	case 9:
		nMd = 31+n2m+31+30+31+30+31+31;
		break;
	case 10:
		nMd = 31+n2m+31+30+31+30+31+31+30;
		break;
	case 11:
		nMd = 31+n2m+31+30+31+30+31+31+30+31;
		break;
	case 12:
		nMd = 31+n2m+31+30+31+30+31+31+30+31+30;
		break;
	default:
		break;
	}
	nMd += nday;
	uint nd = 0;
	nd |= (nMd/100%10)<<28 ;
	nd |= (nMd/10%10)<<24 ;
	nd |= (nMd%10)<<20;

	nd = nd | (nhour/10%10)<<18 ;
	nd =nd | (nhour%10)<<14;
	nd = nd | (nmin/10%10)<<11;
	nd = nd| (nmin%10)<<7;
	nd = nd | (nsecond/10%10)<<4 ;
	nd = nd | (nsecond%10);


	uint data[2] = {0,0};
	data[0] = nY;
	data[1] = nd;

	CSttDriverOper::IoCtrl(0x351,0);
	CSttDriverOper::WriteData((char*)data,8);
}


//////////////////////////////////////////////////
//2020-03-26 zhoulei

void CSttDevice::SetTestStart(int nTestType)
{
	CSttDriverOper::startDMA();
	CSttDriverOper::setFilter(0);
	CSttDriverOper::IoCtrl(0x100,1);
	Sleep(50);
	switch(nTestType)
	{
	case GradientTest:
		CSttDriverOper::Start(7);
		break;
	case ManualTest:
		CSttDriverOper::Start(1);
		break;
	case StateTest:
		CSttDriverOper::Start(2);//启动状态序列测试
		break;
	case AbnoramlTest:
		CSttDriverOper::Start(9);//启动异常模拟
		break;
	case ShakeTest:
		CSttDriverOper::Start(8);//启动振荡测试
		break;
	case ReplayTest:
        CSttDriverOper::Start(0x0D);//启动故障回放
		break;
	}

}

void CSttDevice::SetTestStop()
{
	CSttDriverOper::stopDMA();
	CSttDriverOper::Stop();
}

void CSttDevice::SetRecordStart()
{
	CSttDriverOper::StartRecord();
}

void CSttDevice::SetRecordStop()
{
	CSttDriverOper::stopDMA();
	CSttDriverOper::StopRecord();
}

void CSttDevice::SetTestPara(int nTestType,char *pszBuff,int nLen)
{
	switch(nTestType)
	{
	case StateTest:
		CSttDriverOper::setStatePara(pszBuff,nLen);
		break;
	case GradientTest:
		CSttDriverOper::setRampPara(pszBuff,nLen);
		break;
	case ManualTest:
		CSttDriverOper::setManualAcAnalogPara(pszBuff,nLen);
		break;
	case AbnoramlTest:
		CSttDriverOper::setabnStatePara(pszBuff,nLen);
		break;
	case IECDataCfg:
		CSttDriverOper::setConfigIECCoderData(pszBuff,nLen);
		break;
	case SvCtrlCfg:
		CSttDriverOper::set_optical_port(pszBuff,nLen,1);
		break;
	case GseCtrlCfg:
		CSttDriverOper::set_optical_port(pszBuff,nLen,2);
		break;
	case FiberCtrlCfg:
		CSttDriverOper::set_optical_port(pszBuff,nLen,0);
		break;
	case ShakeTest:
		CSttDriverOper::setSwingingPara(pszBuff,nLen);
		break;
	case ReplayTestCfg:
        CSttDriverOper::setLtRelayConfData(pszBuff,nLen);
		break;
	case ReplayTestData:
		CSttDriverOper::setRelayData(pszBuff,nLen);
		break;
	case Record:
		CSttDriverOper::setGooseSubData(pszBuff,nLen);
		break;
	}
}

void CSttDevice::SetManualBI(char* pszBuff,int nLen)
{
	CSttDriverOper::setManualBISetting(pszBuff,nLen);
}

void CSttDevice::SetStateTriger()
{
	CSttDriverOper::setStateTrigerManual();
}

int CSttDevice::GetTestResult(ResultType eType,char *pszBuff)
{
	switch(eType)
	{
	case GradientResult:
		return CSttDriverOper::readRampResult(pszBuff);
	case StateResult:
		return CSttDriverOper::readStateResult(pszBuff);
	case RecordResult:
		return CSttDriverOper::readRecordResult(pszBuff);
	default:
		return 0;
	}
}

int CSttDevice::GetReplayIrp()
{
	return CSttDriverOper::readReplayIrp();
}

BOOL CSttDevice::TransDigitalVolToDrv(float fAmp,float fAng,float fFre,int nGroupIndex,unsigned int *pnDrvData,int ndigmoduleindex)
{
	/***
	float fPh=fAng;
	bool bDC = false;

	if(m_oDevSysParas.m_nOutputMode==2)
		fPh = fAng+getDigitalPhRatio(ndigmoduleindex);

	float fGroupAdd = m_nDelayTime[nGroupIndex]/250.0*4.5;

	fPh -= fGroupAdd;

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

	if(fabs(fFre)<0.0001)
	{
		bDC = true;
		fPh = 90;
		if(fAmp<0)
		{
			fPh = 270;
			fAmp =qAbs(fAmp);
		}
	}
	else
	{
		bDC = false;
	}
	long  nPh=fPh*MaxNum/360;
	nPh = nPh<<16;

	pnDrvData[0] = nPh;
	pnDrvData[1] = TranslateDigitalFre(fFre);
	pnDrvData[2] = TransDigitalVolAmp(fAmp,nGroupIndex,bDC);
	***/
	return true;
}

int CSttDevice::TransDigitalVolAmp(float fValue,int nGroup,bool bDC)
{
	if(nGroup>=MAX_DIGITAL_GROUP_NUM)
	{
		return 0;
	}

	float fsqr2 = 1;

	if(!bDC)
	{
		fsqr2 = 1.414;
	}

	return 0;
//	return fValue* m_oDevSysParas.PkgModePTRate(nGroup) * fsqr2 * 100 * 2;
}

BOOL CSttDevice::TransDigitalCurToDrv(float fAmp,float fAng,float fFre,int nGroupIndex,unsigned int *pnDrvData,int ndigmoduleindex)
{
	/***
	float fPh=fAng;
	bool bDC = false;

	if(m_oDevSysParas.m_nOutputMode==2)
		fPh = fAng+getDigitalPhRatio(ndigmoduleindex);

	float fGroupAdd = m_nDelayTime[nGroupIndex]/250.0*4.5;

	fPh -= fGroupAdd;

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

	if(fabs(fFre)<= 0.0001)
	{
		bDC = true;
		fAng = 90;

		if(fAmp<0)
		{
			fAng = 270;
			fAmp =fabs(fAmp);
		}
	}

	long  nPh = fAng*MaxNum/360;
	nPh = nPh<<16;

	pnDrvData[0] = nPh;
	pnDrvData[1] = TranslateDigitalFre(fFre);
	pnDrvData[2] = TransDigitalCurAmp(fAmp,nGroupIndex,bDC);
	***/
	return true;
}

int CSttDevice::TransDigitalCurAmp(float fValue,int nGroup,bool bDC)
{
	if(nGroup>=MAX_DIGITAL_GROUP_NUM)
	{
		return 0;
	}

	float fsqr2 = 1;

	if(!bDC)
	{
		fsqr2 = 1.414;
	}

	return 0;
//	return fValue* (m_oDevSysParas.PkgModeCTRate(nGroup)) * fsqr2 * 1000 * 2;
}

long CSttDevice::TranslateDigitalFre(float fFre)
{
	if(m_nSampPoints<=0)
		m_nSampPoints = 4000;

	long nH = (long)fFre*MaxNum/m_nSampPoints;
	double fH = fFre*MaxNum/m_nSampPoints;
	long nL = (fH - nH)*65536;
	long nFre  =((nH<<16)&0xFFFF0000)+nL;
	return nFre;
}

float CSttDevice::getDigitalPhRatio(int nIndex)
{
	float fXSPh = 0;
	//	for(int index=0;index<DIGITAL_MODULE_MAX;index++)
	//	{
	//		if(nIndex==m_oDeviceInfo->digitalmodule[index].group)
	//		{
	//			fXSPh=m_oDeviceInfo->digitalmodule[index].fdigitaldelay;
	//			break;
	//		}
	//	}

	return fXSPh;
}

void CSttDevice::GetTMTChannels(int nRampChannel,QVector<int> &ChannelVolts,QVector<int> &ChannelCurrs)
{
	ChannelVolts.clear();
	ChannelCurrs.clear();

	switch(nRampChannel)
	{
	case GRADIENT_UA:
		ChannelVolts.append(TMT_UA_POS);
		break;
	case GRADIENT_UB:
		ChannelVolts.append(TMT_UB_POS);
		break;
	case GRADIENT_UC:
		ChannelVolts.append(TMT_UC_POS);
		break;
	case GRADIENT_UABC:
	{
		ChannelVolts.append(TMT_UA_POS);
		ChannelVolts.append(TMT_UB_POS);
		ChannelVolts.append(TMT_UC_POS);
	}
		break;
	case GRADIENT_UA2:
		ChannelVolts.append(TMT_UA2_POS);
		break;
	case GRADIENT_UB2:
		ChannelVolts.append(TMT_UB2_POS);
		break;
	case GRADIENT_UC2:
		ChannelVolts.append(TMT_UC2_POS);
		break;
	case GRADIENT_UABC2:
	{
		ChannelVolts.append(TMT_UA2_POS);
		ChannelVolts.append(TMT_UB2_POS);
		ChannelVolts.append(TMT_UC2_POS);
	}
		break;
	case GRADIENT_UABC_UABC2:
	{
		ChannelVolts.append(TMT_UA_POS);
		ChannelVolts.append(TMT_UB_POS);
		ChannelVolts.append(TMT_UC_POS);

		ChannelVolts.append(TMT_UA2_POS);
		ChannelVolts.append(TMT_UB2_POS);
		ChannelVolts.append(TMT_UC2_POS);
	}
		break;
	case GRADIENT_IA:
		ChannelCurrs.append(TMT_IA_POS);
		break;
	case GRADIENT_IB:
		ChannelCurrs.append(TMT_IB_POS);
		break;
	case GRADIENT_IC:
		ChannelCurrs.append(TMT_IC_POS);
		break;
	case GRADIENT_IABC:
	{
		ChannelCurrs.append(TMT_IA_POS);
		ChannelCurrs.append(TMT_IB_POS);
		ChannelCurrs.append(TMT_IC_POS);
	}
		break;
	case GRADIENT_IA2:
		ChannelCurrs.append(TMT_IA2_POS);
		break;
	case GRADIENT_IB2:
		ChannelCurrs.append(TMT_IB2_POS);
		break;
	case GRADIENT_IC2:
		ChannelCurrs.append(TMT_IC2_POS);
		break;
	case GRADIENT_IABC2:
	{
		ChannelCurrs.append(TMT_IA2_POS);
		ChannelCurrs.append(TMT_IB2_POS);
		ChannelCurrs.append(TMT_IC2_POS);
	}
		break;
	case GRADIENT_IABC_IABC2:
	{
		ChannelCurrs.append(TMT_IA_POS);
		ChannelCurrs.append(TMT_IB_POS);
		ChannelCurrs.append(TMT_IC_POS);

		ChannelCurrs.append(TMT_IA2_POS);
		ChannelCurrs.append(TMT_IB2_POS);
		ChannelCurrs.append(TMT_IC2_POS);
	}
		break;
	case GRADIENT_UABC_IABC_1:
	{
		ChannelVolts.append(TMT_UA_POS);
		ChannelVolts.append(TMT_UB_POS);
		ChannelVolts.append(TMT_UC_POS);

		ChannelCurrs.append(TMT_IA_POS);
		ChannelCurrs.append(TMT_IB_POS);
		ChannelCurrs.append(TMT_IC_POS);
	}
		break;
	case GRADIENT_UABC_IABC_2:
	{
		ChannelVolts.append(TMT_UA2_POS);
		ChannelVolts.append(TMT_UB2_POS);
		ChannelVolts.append(TMT_UC2_POS);

		ChannelCurrs.append(TMT_IA2_POS);
		ChannelCurrs.append(TMT_IB2_POS);
		ChannelCurrs.append(TMT_IC2_POS);
	}
		break;
	}
}

int CSttDevice::GetDrvChannel_Digital(int Group,int nModuleType,ValueType eType)
{
	/***
	if(Group>MAX_DIGITAL_GROUP_NUM)
		return -1;

	int nVolChannelA_Index=0;
	int nCurChannelA_Index=0;

	switch(Group)
	{
	case 0://U1I1
		nVolChannelA_Index=0;
		nCurChannelA_Index=13*3;
		break;
	case 1://U2I2
		nVolChannelA_Index=4*3;
		nCurChannelA_Index=16*3;
		break;
	case 2://U3I3
		nVolChannelA_Index=7*3;
		nCurChannelA_Index=19*3;
		break;
	case 3://U4I4
		nVolChannelA_Index=10*3;
		nCurChannelA_Index=22*3;
		break;
	case 4://U5I5
		nVolChannelA_Index=25*3;
		nCurChannelA_Index=31*3;
		break;
	case 5://U6I6
		nVolChannelA_Index=28*3;
		nCurChannelA_Index=34*3;
		break;
	}

	int chan=0;
	switch(nModuleType)
	{
	case VOLT:
		chan=nVolChannelA_Index;
		break;
	case CURRENT:
		chan=nCurChannelA_Index;
		break;
	default:
		return -1;
	}

	switch(eType)
	{
	case Amp:
		chan+=DrvPos_Amp;
		break;
	case Ang:
		chan+=DrvPos_Ang;
		break;
	case Fre:
		chan+=DrvPos_Fre;
		break;
	}

	return chan;
	***/
	return 0;
}


void CSttDevice::SetGooseSub(char* pszBuff,int nLen)
{
	CSttDriverOper::setGooseSubData(pszBuff,nLen);
}

void CSttDevice::SetCurrentPowerMode(int nMode,float fSetChIMax,int nModuleIndex,float fSetVolt)
{
	m_nCurrentPowerMode=nMode;
	if(m_nCurrentPowerMode==STT_CurrentMODULE_POWER_OTHER)
	{
		float fModuleCurrentMax = g_theDeviceSystemParameter->m_oModules_I[nModuleIndex]->m_oModuleAttr.m_fChMax;
		nModuleIndex+=g_theDeviceSystemParameter->m_nModuleCount_U;

		float fVolt=0;
		if(fModuleCurrentMax<15)
		{
			fVolt=0.6;
			if(fSetVolt>=0.6&&fSetVolt<=7.5)
	{
				fVolt=fSetVolt;
	}

			if(fSetChIMax>12.5)
				fSetChIMax=12.5;

			fVolt=fVolt*1.414+fSetChIMax*0.1-1.1;
			fVolt/=3.88;
		}
		else if(fModuleCurrentMax<25)
		{
			if(fSetChIMax<22)
	{
				fVolt=fVolt*1.414+20*0.1-2.8;
				fVolt/=6.6;
			}
			else
			{
				fVolt=fVolt*1.414+32*0.1-1.1;
				fVolt/=3.88;
			}
	}

		uchar nByte = fVolt/3.3*255;
		oDAPara.nvolt[nModuleIndex] |= ((uint)nByte)<<(1*8);

		CSttDriverOper::setDeviceDaPara((char*)&oDAPara,sizeof(DeviceDAPara));
	}
}

void CSttDevice::InitDApara()
{
	m_nCurrentPowerMode=STT_CurrentMODULE_POWER_LOW;
	memset(&oDAPara,0,sizeof(DeviceDAPara));
	int nModuleCnt=0;
	int nModuleIndex=0;
	float fDefault;
	uchar nByte=0;
	//VOLT
	fDefault=3;
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		nModuleIndex=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_oModuleAttr.m_nModuleIndex;
		oDAPara.nmodule[nModuleCnt]=1<<(nModuleIndex-1);
		for(int j=0;j<4;j++)
		{
			nByte = fDefault/3.3*255;
			oDAPara.nvolt[nModuleCnt] |= ((uint)nByte)<<(j*8);
		}
		nModuleCnt++;
	}

	//CURRENT
	fDefault=0.3;
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		nModuleIndex=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_oModuleAttr.m_nModuleIndex;
		oDAPara.nmodule[nModuleCnt]=1<<(nModuleIndex-1);
		for(int j=0;j<4;j++)
		{
			nByte = fDefault/3.3*255;
			oDAPara.nvolt[nModuleCnt] |= ((uint)nByte)<<(j*8);
		}
		nModuleCnt++;
	}

	CSttDriverOper::setDeviceDaPara((char*)&oDAPara,sizeof(DeviceDAPara));
}

void CSttDevice::setDApara(float fSum,int nModuleIndex,int nModuleType,float fImax)
{
	if(nModuleType==STT_MODULE_TYPE_VOLT)
	{
		float fValue=0;
		float fModuleVoltMax = g_theDeviceSystemParameter->m_oModules_U[nModuleIndex]->m_oModuleAttr.m_fChMax;
		if(fModuleVoltMax<150)
		{
			if(fSum<63||fSum>fModuleVoltMax)
			{
				fSum = 63;//模块典型值
			}
			fValue = (fSum*1.414-89)/32.0;
		}
		else if(fModuleVoltMax<260&&fModuleVoltMax>200)
		{
			if(fSum<115||fSum>fModuleVoltMax)
			{
				fSum = 115;//模块典型值
			}
			fValue = (fSum*1.414+20)/162;
		}
		else
		{//fModuleVoltMax 260~300
			if(fSum<115||fSum>fModuleVoltMax)
			{
				fSum = 115;//模块典型值
			}
			fValue = (fSum*1.414-163)/82.0;
		}

		uchar nByte = fValue/3.3*255;
		oDAPara.nvolt[nModuleIndex] |= ((uint)nByte)<<(1*8);
	}
	else if(nModuleType==STT_MODULE_TYPE_CURRENT)
	{
		if(m_nCurrentPowerMode==STT_CurrentMODULE_POWER_OTHER)
			return;

		float fModuleCurrentMax = g_theDeviceSystemParameter->m_oModules_I[nModuleIndex]->m_oModuleAttr.m_fChMax;
		nModuleIndex+=g_theDeviceSystemParameter->m_nModuleCount_U;
		float fvolt=0.3;//STT_CurrentMODULE_POWER_LOW
		if(fModuleCurrentMax<15)
		{
			fvolt=0.7;
			switch(m_nCurrentPowerMode)
			{
			case STT_CurrentMODULE_POWER_MIDDLE:
				fvolt=1.5;
				break;
			case STT_CurrentMODULE_POWER_HIGH:
				fvolt=3.3;
				break;
			default:
				return;
			}
		}
		else if(fModuleCurrentMax<25)
		{
			fvolt=0.3;
			switch(m_nCurrentPowerMode)
			{
			case STT_CurrentMODULE_POWER_MIDDLE:
			{
				if(fSum<=80)
				{
					fvolt=1.3;
				}
				else if(fSum<=100)
				{
					fvolt=1.1;
				}
				else
				{
					fvolt=1;
				}
			}
				break;
			case STT_CurrentMODULE_POWER_HIGH:
			{
				float fDa1 =3.3;
				float fDa2 = 0;

				if(fSum<=50)
				{

				}
				else if(fSum<=60)
				{
					fDa1 = 2.8;
				}
				else if(fSum<=70)
				{
					fDa1 = 2.4;
				}
				else if(fSum<=80)
				{
					fDa1 = 2;
				}
				else if(fSum<=90)
				{
					fDa1 = 1.7;
				}
				else if(fSum<=100)
				{
					fDa1 = 1.4;
				}
				else if(fSum<=110)
				{
					fDa1 = 1.2;
				}
				else
				{
					fDa1 = 1.1;
				}

				fvolt=fDa1;
				if(fImax>15)
				{
					fDa2 = 3.3*15/fImax*0.9;
					if(fDa1>fDa2)
						fvolt=fDa2;
				}
			}
				break;
			default:
				return;
			}
		}


		uchar nByte = fvolt/3.3*255;
		oDAPara.nvolt[nModuleIndex] |= ((uint)nByte)<<(1*8);
	}

	CSttDriverOper::setDeviceDaPara((char*)&oDAPara,sizeof(DeviceDAPara));
}

void CSttDevice::setCurrentDCDApara(float fSum,int nModuleIndex)
{
	nModuleIndex+=g_theDeviceSystemParameter->m_nModuleCount_U;
	float fvolt=0.3;//STT_CurrentMODULE_POWER_LOW
	switch(m_nCurrentPowerMode)
	{
	case STT_CurrentMODULE_POWER_MIDDLE:
	{
		if(fSum<=30)
		{
			fvolt=1.3;
		}
		else if(fSum<=45)
		{
			fvolt=1;
		}
		else
		{
			fvolt=0.6;
		}
	}
		break;
	case STT_CurrentMODULE_POWER_HIGH:
	{
		if(fSum<=30)
		{
			fvolt=1.3;
		}
		else if(fSum<=45)
		{
			fvolt=1;
		}
		else
		{
			fvolt=0.6;
		}
	}
		break;
	}
	uchar nByte = fvolt/3.3*255;
	oDAPara.nvolt[nModuleIndex] |= ((uint)nByte)<<(1*8);
}

float translateVoltBase(unsigned short nValue,float fXS)
{
	short nv = nValue - 2048;

	float fv = (float)nv*fXS/2048.0;
	return fv;
}

float translateCurrentVolt(unsigned short nValue)
{
	short nv = nValue - 2048;

	float fv = (float)nv*25.0*1.13/2048.0;
	return fv;
}

float translateVolt(unsigned short nValue)
{
	short nv = nValue - 2048;

	float fv = (float)nv*200*1.25/2048.0;
	return fv;
}

void CSttDevice::AnalysisDrvSysInfo(Drv_FeedBack &oDrv_FeedBack,int nModulePos,BOOL IsVolt)
{
	int nItemIndex=0;
	for(unsigned int i=0;i<g_theSttDeviceStatus->m_nAnalogCount;i++)
	{
		if(g_theSttDeviceStatus->m_oModule[i].m_nModuleIndex==nModulePos)
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
			InitDApara();
		}

		if(tempMax>84)
		{
			g_theSttDeviceStatus->m_bNeedStop=TRUE;
		}
	}

	unsigned short nH = (~oDrv_FeedBack.dat[10])&0x1;
	oModuleStatus.m_nIsVoltHot=nH;//电压过热

	for(int j=1;j<7;j++)
	{
		nH = (~(oDrv_FeedBack.dat[10]>>j))&0x1;
		oModuleStatus.m_oChannel[j-1].m_bIsOverLoad=nH;//过载
	}

	nH = (~(oDrv_FeedBack.dat[10]>>7))&0x1;
	oModuleStatus.m_nIsDCHot=nH;//直流过热

	nH = (~(oDrv_FeedBack.dat[10]>>8))&0x1;
	oModuleStatus.m_nIsVoltWarining=nH;//电压告警

	nH = (~(oDrv_FeedBack.dat[10]>>9))&0x1;
	oModuleStatus.m_nIsMissWarining=nH;//忽略告警
}

void CSttDevice::OnTimer()
{
	memset(m_pSysInfo,0,sizeof(Drv_SysInfo));
	int nSize=CSttDriverOper::readDeviceInnerPara((char*)m_pSysInfo);
	if(nSize>sizeof(Drv_SysInfo))
	{
		return;
	}

	g_theSttDeviceStatus->m_bNeedStop=FALSE;
	g_theSttDeviceStatus->m_nSync=0;
	if(m_pSysInfo->tmFlag != 0)
		g_theSttDeviceStatus->m_nSync=1;

	g_theSttDeviceStatus->m_nUtc_s=m_pSysInfo->tm_h;
	g_theSttDeviceStatus->m_nUtc_ns=m_pSysInfo->tm_l;

	for(int nModuleIndex=0;nModuleIndex<8;nModuleIndex++)
	{
		Drv_FeedBack oFeedBack = m_pSysInfo->stBack[nModuleIndex];
		int nType = m_oBoardinfo.version[nModuleIndex+1]>>24;
		switch(nType)
		{
		case 0x55:
			AnalysisDrvSysInfo(oFeedBack,nModuleIndex+1,TRUE);
			break;
		case 0xaa:
			AnalysisDrvSysInfo(oFeedBack,nModuleIndex+1);
			break;
		}
	}
}
