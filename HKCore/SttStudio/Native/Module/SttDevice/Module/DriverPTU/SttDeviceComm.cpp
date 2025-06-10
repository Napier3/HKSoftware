#include "SttDeviceComm.h"
#include "../../../Engine/SttServerTestCtrlCntr.h"
#include "../../../SttTest/Common/Adjust/SttAdjust_ModuleOutput.h"
#include "../PowerCtrl/SttPowerCtrlCom.h"

CSttDeviceComm::CSttDeviceComm()
{

}

CSttDeviceComm::~CSttDeviceComm()
{

}

void CSttDeviceComm::GetBoardInfo()
{
	if(g_theSttDeviceStatus==NULL)
		g_theSttDeviceStatus=new STT_DEVICE_STATUS;

	memset(g_theSttDeviceStatus,0,sizeof(STT_DEVICE_STATUS));
	memset(&m_oBoardinfo,0,sizeof(Drv_BoardVersion));//version:0-10有效

	read(m_nfd,(char*)&m_oBoardinfo,0x209);

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("MainBoardInfo[%08x] Ver=%s"),m_oBoardinfo.version[0],TransVersion(m_oBoardinfo.version[0]).GetString());
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("DriverInfo[%08x]    Ver=%s"),m_oBoardinfo.version[9],TransVersion(m_oBoardinfo.version[9]).GetString());

	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strFPGAVer,TransVersion(m_oBoardinfo.version[0]).GetString());
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDriverVer,TransVersion(m_oBoardinfo.version[9]).GetString());
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strAppName,APP_NAME);
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDriverName,DRV_NAME);

	PSTT_MODULE oModule;
	for(int nModuleUIndex=0;nModuleUIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nModuleUIndex++)
	{
		oModule=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];
		g_theSttDeviceStatus->m_oModule[g_theSttDeviceStatus->m_nAnalogCount].m_nModulePos=oModule->m_oModuleAttr.m_nModuleIndex;
		g_theSttDeviceStatus->m_oModule[g_theSttDeviceStatus->m_nAnalogCount].m_nModuleType=STT_MODULE_TYPE_VOLT;
		g_theSttDeviceStatus->m_nAnalogCount++;
	}

	for(int nModuleIIndex=0;nModuleIIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nModuleIIndex++)
	{
		oModule=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
		g_theSttDeviceStatus->m_oModule[g_theSttDeviceStatus->m_nAnalogCount].m_nModulePos=oModule->m_oModuleAttr.m_nModuleIndex;
		g_theSttDeviceStatus->m_oModule[g_theSttDeviceStatus->m_nAnalogCount].m_nModuleType=STT_MODULE_TYPE_CURRENT;
		g_theSttDeviceStatus->m_nAnalogCount++;
	}

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
			break;
		case 0xaa:
			strBoardType="Current    ";
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

		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount;nIndex++)
		{
			if(i==g_theDeviceSystemParameter->m_oModules[nIndex].m_oModuleAttr.m_nModuleIndex)
			{
				strcpy(g_theDeviceSystemParameter->m_oModules[nIndex].m_oModuleAttr.m_strFPGAVer,TransVersion(m_oBoardinfo.version[i]).GetString());
				break;
			}
		}

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Position=%d Type=%s Ver=%s BoardInfo[%08x]"),i,strBoardType.GetString(),TransVersion(m_oBoardinfo.version[i]).GetString(), m_oBoardinfo.version[i]);
	}
}

//moduleoutput
void CSttDeviceComm::tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
{
	int nBo=~g_theSttAdjustTool.m_nSwitchCtrl;
	ioctl(m_nfd,0x107,nBo);

	tmt_channel    m_oTmt_channel[MAX_VOLTAGE_COUNT];
	for(int nIndex=0;nIndex<MAX_VOLTAGE_COUNT;nIndex++)
	{
		m_oTmt_channel[nIndex].init();
	}
	float fAmp=0;
	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;
	char *pszBuf=stt_test_get_drvparas_buff();
	DrvManuPara *pstACpara=(DrvManuPara *)pszBuf;
	memset(pstACpara,0,sizeof(DrvManuPara));

	float fSampleFre=0;
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre>0)
		fSampleFre=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	else
		fSampleFre=50;

	pstACpara->sample = 40000/fSampleFre;//每周波800点
	pstACpara->moduleCount=0;
	BOOL bDc=FALSE;
	if(pTmt->m_nFreqIndex==0)
		bDc=TRUE;

	CSttDeviceBase::g_pSttDeviceBase->InitDAData();
	PSTT_MODULE pSTT_MODULE;
	if(pTmt->m_nModuleType==STT_MODULE_TYPE_VOLT)
	{
		//VOLT
		if(g_theDeviceSystemParameter->m_oModules_U[pTmt->m_nModuleIndex]!=NULL)
		{
			pSTT_MODULE=g_theDeviceSystemParameter->m_oModules_U[pTmt->m_nModuleIndex];
			pstACpara->module[pstACpara->moduleCount].nmodule=pSTT_MODULE->m_oModuleAttr.m_nModuleIndex-1;
			pstACpara->module[pstACpara->moduleCount].nCnt=24;

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

			Manual_Volt(m_oTmt_channel,pstACpara->module[pstACpara->moduleCount].dat,
					1,pTmt->m_nModuleIndex,bDc);
			pstACpara->moduleCount++;

			if(bDc)
				fVsum/=1.414;
			CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(fVsum,pTmt->m_nModuleIndex);
		}
	}
	else if(pTmt->m_nModuleType==STT_MODULE_TYPE_CURRENT)
	{
		if(g_theDeviceSystemParameter->m_oModules_U[0]!=NULL)
		{
			pSTT_MODULE=g_theDeviceSystemParameter->m_oModules_U[0];
			pstACpara->module[pstACpara->moduleCount].nmodule=pSTT_MODULE->m_oModuleAttr.m_nModuleIndex-1;
			pstACpara->module[pstACpara->moduleCount].nCnt=24;

			//以第一个电压模块UA为相位基准
			//RD33 UAUBUC统一接到测试仪UA,UA'
			m_oTmt_channel[0].Harm[1].fAmp=50;
			m_oTmt_channel[0].Harm[1].fAngle=0;
			m_oTmt_channel[0].Harm[1].fFreq=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

			Manual_Volt(m_oTmt_channel,pstACpara->module[pstACpara->moduleCount].dat,1,0);
			pstACpara->moduleCount++;

			CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(50,0);
		}

		for(int nIndex=0;nIndex<MAX_VOLTAGE_COUNT;nIndex++)
		{
			m_oTmt_channel[nIndex].init();
		}
		//CURRENT
		if(g_theDeviceSystemParameter->m_oModules_I[pTmt->m_nModuleIndex]!=NULL)
		{
			pSTT_MODULE=g_theDeviceSystemParameter->m_oModules_I[pTmt->m_nModuleIndex];
			pstACpara->module[pstACpara->moduleCount].nmodule=pSTT_MODULE->m_oModuleAttr.m_nModuleIndex-1;

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

			Manual_Current(m_oTmt_channel,pstACpara->module[pstACpara->moduleCount].dat,1,pTmt->m_nModuleIndex,bDc);
			pstACpara->module[pstACpara->moduleCount].nCnt=24;
			pstACpara->moduleCount++;

			if(bDc)
			{
				CSttDeviceBase::g_pSttDeviceBase->SetCurrentDApara_DC(fIsum,pTmt->m_nModuleIndex);
			}
			else
			{
				CSttDeviceBase::g_pSttDeviceBase->SetCurrentDApara_AC(fIsum,pTmt->m_nModuleIndex,fIMax);
			}
		}
	}

	CSttDeviceBase::g_pSttDeviceBase->WriteDApara();
	ioctl(m_nfd,0x300,0);
	write(m_nfd,pszBuf,sizeof(DrvManuPara));
}

//manu
void CSttDeviceComm::tmt_to_drv_manu(tmt_ManualTest *pTmt)
{
	char *pszBuf=stt_test_get_drvparas_buff();
	DrvManuPara *pstACpara=(DrvManuPara *)pszBuf;
	memset(pstACpara,0,sizeof(DrvManuPara));

	float fSampleFre=0;
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre>0)
		fSampleFre=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	else
		fSampleFre=50;

	pstACpara->sample = 40000/fSampleFre;//每周波800点
	pTmt->m_oManuParas.m_bDC=FALSE;

	pstACpara->moduleCount=g_theDeviceSystemParameter->m_nModuleCount_U;
	pstACpara->moduleCount+=g_theDeviceSystemParameter->m_nModuleCount_I;

	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
		if(pModule==NULL)
			continue;

		Manual_Volt(pTmt->m_oManuParas.m_uiVOL,pstACpara->module[nIndex].dat,
					1,0,pTmt->m_oManuParas.m_bDC);
		pstACpara->module[nIndex].nmodule =pModule->m_oModuleAttr.m_nModuleIndex-1;
		pstACpara->module[nIndex].nCnt = 24;
	}

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule==NULL)
			continue;

		Manual_Current(pTmt->m_oManuParas.m_uiCUR,pstACpara->module[nIndex].dat,
					   1,nIndex,pTmt->m_oManuParas.m_bDC);
	}

	int nOverload=g_theSystemConfig->m_fOverLoadDelay*10000000*5;//DelayOverload
	ioctl(m_nfd,0x112,nOverload);

	int nBo=0;
	for (int i=0; i<8; i++)//bo
	{
		nBo += pTmt->m_oManuParas.m_binOut[i].nState<<i;
	}
	ioctl(m_nfd,0x107,nBo);

	if(g_theSystemConfig->m_nHasAnalog!=0)
	{
		CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Comm(pTmt->m_oManuParas.m_uiVOL,
														   pTmt->m_oManuParas.m_uiCUR,1,pTmt->m_oManuParas.m_bDC,0,0,0);
	}
	ioctl(m_nfd,0x300,0);
	write(m_nfd,pszBuf,sizeof(DrvManuPara));
}

void CSttDeviceComm::tmt_to_drv_harm(tmt_HarmTest *pTmt)
{

}

void CSttDeviceComm::tmt_to_drv_StatePara(tmt_StateTest *pTmt)
{
	tmt_StatePara *pTmt_paraState;
	int nModuleIndex;
	unsigned char nByte;
	int nTmtPos;
	float fVMax=0;
	CSttDeviceBase::g_pSttDeviceBase->InitDAData();

	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
		if(pModule==NULL)
			continue;

		float fVMaxState=0;
		float fAmp=0;
		for(int nStateIndex=0;nStateIndex<pTmt->m_oStateParas.m_nStateNumbers;nStateIndex++)
		{
			fVMaxState=0;
			pTmt_paraState=&pTmt->m_oStateParas.m_paraState[nStateIndex];
			for(int k=0;k<pModule->m_oModuleAttr.m_nChannelNum;k++)
			{
				nTmtPos=pModule->m_nChTmtPos[k];
				if(nTmtPos<0)
					continue;

				fAmp=fabs(pTmt_paraState->m_uiVOL[nTmtPos].Harm[1].fAmp);
				if(fVMaxState<fAmp)
					fVMaxState=fAmp;
			}

			if(pTmt_paraState->m_bDC)
				fVMaxState/=1.414;

			if(fVMax<fVMaxState)
				fVMax=fVMaxState;
		}

		CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(fVMax,nIndex);
	}

	float fIDAValue;
	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule==NULL)
			continue;

		CSttPowerCtrlBase *pPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;
		if(pPowerCtrlBase==NULL)
			continue;

		pPowerCtrlBase->SetCurrentDA_State(nIndex);
		nModuleIndex=nIndex+g_theDeviceSystemParameter->m_nModuleCount_U;
		CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nModuleIndex] |= pPowerCtrlBase->GetModuleDA();
	}

	char* pBuff=stt_test_get_drvparas_buff();
	DrvStatePara *statepara=(DrvStatePara *)pBuff;
	memset(statepara,0,sizeof(DrvStatePara));
	statepara->isLoop = pTmt->m_oStateParas.m_nRepeatNumbers;

	int nOffSet=0;
	DrvStateItem state;

	for(int j=0;j<pTmt->m_oStateParas.m_nStateNumbers;j++)
	{
		pTmt_paraState =&pTmt->m_oStateParas.m_paraState[j];
		memset(&state,0,sizeof(DrvStateItem));
		state.state = statepara->stateCount;

		//Volt
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
		{
			PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
			if(pModule==NULL)
				continue;

			state.module[nIndex].nmodule=pModule->m_oModuleAttr.m_nModuleIndex-1;
			Manual_Volt(pTmt_paraState->m_uiVOL,state.module[nIndex].dat,1,0,pTmt_paraState->m_bDC);
			state.module[nIndex].cnt=24;
		}
		nOffSet=g_theDeviceSystemParameter->m_nModuleCount_U;

		//Current
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
		{
			PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
			if(pModule==NULL)
				continue;

			state.module[nIndex+nOffSet].nmodule = pModule->m_oModuleAttr.m_nModuleIndex-1;
			state.module[nIndex+nOffSet].cnt=24;
			Manual_Current(pTmt_paraState->m_uiCUR,state.module[nIndex+nOffSet].dat,1,0,pTmt_paraState->m_bDC);
		}

		//Week
		for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_WEEK;nIndex++)
		{

		}

		for (int i=0; i<8; i++)//bo
		{
			state.BO += pTmt_paraState->m_binOut[i].nState<<i;
		}

		switch(pTmt_paraState->m_nTriggerCondition)
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
			tm.mSec = pTmt_paraState->m_fTimeState*1000;
			state.tripData.tm = tm;
		}
			break;
		case TMT_MDSTATE_GPSBTRIGGER:
		{
			structGPSTrip 	gps;
			QDateTime datetime;
			QDate date;
			if(pTmt_paraState->m_tGps.nYear==0&&pTmt_paraState->m_tGps.nMonth==0
					&&pTmt_paraState->m_tGps.nDay==0)
			{
				int nSecond=g_theSttDeviceStatus->m_nUtc_s;
				datetime=QDateTime::fromTime_t(nSecond);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("Dev Hour=%d,Minute=%d,Second=%d"),
										   datetime.time().hour(),datetime.time().minute(),datetime.time().second());
			}
			else if(date.setYMD(pTmt_paraState->m_tGps.nYear,pTmt_paraState->m_tGps.nMonth,
								pTmt_paraState->m_tGps.nDay))
			{
				datetime.setDate(date);
			}
			else
				break;

			QTime time;
			if(time.setHMS(pTmt_paraState->m_tGps.nHour,pTmt_paraState->m_tGps.nMinutes,
						   pTmt_paraState->m_tGps.nSeconds))
			{
				datetime.setTime(time);
				state.trip = 2;
				gps.sec = datetime.toTime_t();
				gps.nSec = pTmt_paraState->m_tGps.nMilliSeconds*1000000;
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
			if(pTmt_paraState->m_nBinLogic==TMT_BINLOGIC_AND)
				bi.logic =0;

			for (int i=0; i<8; i++)
			{
				bi.valid |= pTmt_paraState->m_binIn[i].nSelect<<i;
			}

			bi.ref = pTmt_paraState->m_eBinReversal;
			state.tripData.bi = bi;
			state.mdelay = pTmt_paraState->m_fTimeAfterTrigger*1000;
		}
			break;
		}

		memcpy(&statepara->item[statepara->stateCount],&state,sizeof(DrvStateItem));
		statepara->stateCount++;
	}

	statepara->moduleCount = g_theDeviceSystemParameter->m_nModuleCount_U;
	statepara->moduleCount += g_theDeviceSystemParameter->m_nModuleCount_I;
	statepara->moduleCount += g_theDeviceSystemParameter->m_nModuleCount_WEEK;

	ioctl(m_nfd,0x302,0);
	write(m_nfd,pBuff,sizeof(DrvStatePara));
}

void CSttDeviceComm::tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt)
{
	char *pszBuf=stt_test_get_drvparas_buff();
	DrvManuPara *pstACpara=(DrvManuPara *)pszBuf;
	memset(pstACpara,0,sizeof(DrvManuPara));

	float fSampleFre=0;
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre>0)
		fSampleFre=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	else
		fSampleFre=50;

	pstACpara->sample = 40000/fSampleFre;//每周波800点

	//DA
	float fDAValue=0;
	CSttDeviceBase::g_pSttDeviceBase->InitDAData();
	int nOffSet=0;
	int nTmtPos;
	float fIsum = 0;
	float fIMax = 0;
	//VOLT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nIndex];
		if(pModule==NULL)
			continue;

		Manual_Volt(pTmt->m_uiVOL,pstACpara->module[nIndex].dat,31,0);
		pstACpara->module[nIndex].nmodule=pModule->m_oModuleAttr.m_nModuleIndex-1;
		pstACpara->module[nIndex].nCnt=6+6*3*31;

		fDAValue=0;
		for(int k=0;k<pModule->m_oModuleAttr.m_nChannelNum;k++)
		{
			nTmtPos=pModule->m_nChTmtPos[k];
			if(nTmtPos<0)
				continue;

			if(fDAValue<fabs(pTmt->m_uiVOL[nTmtPos].Harm[1].fAmp))
				fDAValue=fabs(pTmt->m_uiVOL[nTmtPos].Harm[1].fAmp);
		}

		CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(fDAValue,nIndex);
	}
	nOffSet=g_theDeviceSystemParameter->m_nModuleCount_U;

	//CURRENT
	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nIndex];
		if(pModule==NULL)
			continue;

		Manual_Current(pTmt->m_uiCUR,pstACpara->module[nIndex+nOffSet].dat,31,nIndex);
		pstACpara->module[nIndex+nOffSet].nmodule=pModule->m_oModuleAttr.m_nModuleIndex-1;
		pstACpara->module[nIndex+nOffSet].nCnt=6+6*3*31;

		fIsum = 0;
		fIMax = 0;
		for(int k=0;k<pModule->m_oModuleAttr.m_nChannelNum;k++)
		{
			nTmtPos=pModule->m_nChTmtPos[k];
			if(nTmtPos<0)
				continue;

			fDAValue=fabs(pTmt->m_uiCUR[nTmtPos].Harm[1].fAmp);
			fIsum+=fDAValue;
			if(fIMax<fDAValue)
				fIMax=fDAValue;
		}

		CSttDeviceBase::g_pSttDeviceBase->SetCurrentDApara_AC(fIsum,nIndex,fIMax);
	}

	pstACpara->moduleCount=g_theDeviceSystemParameter->m_nModuleCount_U;
	pstACpara->moduleCount+=g_theDeviceSystemParameter->m_nModuleCount_I;

	CSttDeviceBase::g_pSttDeviceBase->WriteDApara(TRUE);

	ioctl(m_nfd,0x308,0);
	write(m_nfd,pszBuf,sizeof(DrvManuPara));
}

void CSttDeviceComm::ProManuDrvResult()
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	char *pBuf=stt_test_get_drvresult_buff();
	int nret = read(m_nfd,pBuf,0x01);

	if(nret <=0)
	{
		return;
	}

	DrvResult* pResult= (DrvResult*)(pBuf);
	int nBiChang=0;
	int nBiValue=0;
	long nRealTimeEventCount = 0;

	for(int i=0;i<pResult->cnt;i++)
	{
		DrvResultItem oItem = pResult->result[i];
		double dTime=oItem.sec+oItem.nSec*0.000000001;

		switch(oItem.type)
		{
		case PTU_Result_Type_TestStart:
			pSttTestBase->m_dTestStartTime=dTime;
			pSttTestBase->ReturnTestStateEvent_TestStart(pSttTestBase->m_dTestStartTime, 0, TRUE);

			m_oPreBiStatus=oItem.biValue;
			for(int nChanIndex=0;nChanIndex<8;nChanIndex++)
			{
				nBiValue=oItem.biValue>>nChanIndex;
				nBiValue=nBiValue&0x1;
				nBiValue=(nBiValue==0?1:0);
				//				stt_add_test_event(SttResult_Type_Bin, -1, -1, nChanIndex+1, nBiValue, dTime, dTime-pSttTestBase->m_dTestStartTime);
				nRealTimeEventCount++;
			}

			break;
		case PTU_Result_Type_TestFinish:
			if(!pSttTestBase->IsRecvStopCmd())
				pSttTestBase->ReturnTestStateEvent_TestFinish(dTime, dTime-pSttTestBase->m_dTestStartTime, TRUE);
			pSttTestBase->SetTestStarting(FALSE);
			break;
		case PTU_Result_Type_StateChange:
			pSttTestBase->m_dTestStartTime=dTime;
			pSttTestBase->ReturnTestStateEvent_TestStart(pSttTestBase->m_dTestStartTime, 0, TRUE);
			break;
		case PTU_Result_Type_DI_CHANGE:
			for(int nChanIndex=0;nChanIndex<8;nChanIndex++)
			{
				nBiChang=m_oPreBiStatus>>nChanIndex;
				nBiChang=nBiChang&0x1;

				nBiValue=oItem.biValue>>nChanIndex;
				nBiValue=nBiValue&0x1;

				if(nBiChang==nBiValue)
					continue;

				nBiValue=(nBiValue==0?1:0);
				//				stt_add_test_event(SttResult_Type_Bin, -1, -1, nChanIndex+1, nBiValue, dTime, dTime-pSttTestBase->m_dTestStartTime);
				nRealTimeEventCount++;
			}
			m_oPreBiStatus=oItem.biValue;
			break;
		}
	}

	if (nRealTimeEventCount > 0)
	{
		pSttTestBase->ReturnRealTimeEvent();
	}
}

//			if(m_bSysOutPutRunning)//供电模式下，切换回正常档位
//			{
//				int nTap = 0;
//				int nItap;
//				if(g_theSystemConfig->m_bIout_ChansMergeOne)
//				{
//					nItap = 0;
//				}
//				else
//					nItap = 128;
//				nTap |= nItap;
//				if(nTap!=m_nTestTap)
//				{
//					ioctl(m_nfd,0x105,nTap);
//					Sleep(50);
//					m_nTestTap=nTap;
//				}

//				ioctl(m_nfd, 0x136, 1);//开始供电
//			}

void CSttDeviceComm::ProStateDrvResult()
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	char *pBuf=stt_test_get_drvresult_buff();
	int nret = read(m_nfd,pBuf,0x01);

	if(nret <=0)
	{
		return;
	}

	DrvResult* pResult= (DrvResult*)(pBuf);
	int nBiChang=0;
	int nBiValue=0;
	long nRealTimeEventCount = 0;

	for(int i=0;i<pResult->cnt;i++)
	{
		DrvResultItem oItem = pResult->result[i];
		double dTime=oItem.sec+oItem.nSec*0.000000001;

		switch(oItem.type)
		{
		case PTU_Result_Type_TestStart:
			pSttTestBase->m_dTestStartTime=dTime;
			pSttTestBase->ReturnTestStateEvent_TestStart(pSttTestBase->m_dTestStartTime, 0, TRUE);

			//			stt_add_test_event(SttResult_Type_StateChange, pSttTestBase->m_nCurStateIndex, -1, -1, 0, dTime, dTime-pSttTestBase->m_dTestStartTime);
			nRealTimeEventCount++;

			m_oPreBiStatus=oItem.biValue;
			for(int nChanIndex=0;nChanIndex<8;nChanIndex++)
			{
				nBiValue=oItem.biValue>>nChanIndex;
				nBiValue=nBiValue&0x1;
				nBiValue=(nBiValue==0?1:0);
				//				stt_add_test_event(SttResult_Type_Bin, -1, -1, nChanIndex+1, nBiValue, dTime, dTime-pSttTestBase->m_dTestStartTime);
				nRealTimeEventCount++;
			}

			break;
		case PTU_Result_Type_TestFinish:
			if(!pSttTestBase->IsRecvStopCmd())
				pSttTestBase->ReturnTestStateEvent_TestFinish(dTime, dTime-pSttTestBase->m_dTestStartTime, TRUE);
			pSttTestBase->SetTestStarting(FALSE);
			break;
		case PTU_Result_Type_StateChange:
		{
			pSttTestBase->m_nCurStateIndex=oItem.step;
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("nCurStateIndex=%d"), m_nCurStateIndex);
			//			stt_add_test_event(Result_Type_StateChange, pSttTestBase->m_nCurStateIndex, -1, -1, 0,
			//							   dTime, dTime-pSttTestBase->m_dTestStartTime);
			nRealTimeEventCount++;
		}
			break;
		case PTU_Result_Type_DI_CHANGE:
			for(int nChanIndex=0;nChanIndex<8;nChanIndex++)
			{
				nBiChang=m_oPreBiStatus>>nChanIndex;
				nBiChang=nBiChang&0x1;

				nBiValue=oItem.biValue>>nChanIndex;
				nBiValue=nBiValue&0x1;

				if(nBiChang==nBiValue)
					continue;

				nBiValue=(nBiValue==0?1:0);
				//				stt_add_test_event(Result_Type_Bin, -1, -1, nChanIndex+1, nBiValue, dTime, dTime-pSttTestBase->m_dTestStartTime);
				nRealTimeEventCount++;
			}
			m_oPreBiStatus=oItem.biValue;
			break;
		}
	}

	if (nRealTimeEventCount > 0)
	{
		pSttTestBase->ReturnRealTimeEvent();
	}
}

void CSttDeviceComm::SetManualBI(char* pszBuff,int nLen)
{
	ioctl(m_nfd,0x302,0);
	write(m_nfd,pszBuff,nLen);
}

void CSttDeviceComm::SetStateTriger()
{
	ioctl(m_nfd,0x400,0);
}

//bit31-bit1 <<===>>KZ16-KZ1继电器
//
//bit4-bit1 升压器控制 1:启动 0:关闭
//bit7-bit5 直流电压档位控制 1:选中 0:不选中
//bit5 [0-0.12]  bit6 [0.12-1.2] bit7[12-]  都不选 [1.2-12]
//bit8 1:6I输出 0:Is输出
//bit9 直流电流档位控制 1:小于1.2  0:大于1.2
//bit16-bit13 大电流输出端子IA IB IC IZ 多选一切换控制 1:选中 0:不选中 同时bit8选Is输出
//
void CSttDeviceComm::SetTestTap(int nTestTap)
{
	ioctl(m_nfd, 0x136, 0);//停止供电
	ioctl(m_nfd,0x105,nTestTap);
	Sleep(50);
	m_nTestTap=nTestTap;
}

void CSttDeviceComm::SetTestStart(int nTestType)
{
	ioctl(m_nfd,0xA00,1);
	ioctl(m_nfd, 0x402, 0);
	ioctl(m_nfd, 0x100, 1);
	Sleep(50);
	switch(nTestType)
	{
	case ManualTest:
		ioctl(m_nfd, 0x103, 1);
		break;
	case StateTest:
		ioctl(m_nfd, 0x103, 2);//启动状态序列测试
		break;
	case SystemDefaultOutput:
		ioctl(m_nfd, 0x113, 1);
		break;
	}
}

void CSttDeviceComm::SetTestStop(BOOL bIsSysDefaultOutput)
{
	if(bIsSysDefaultOutput)
	{
		ioctl(m_nfd, 0x113, 0);
	}
	else
	{
		ioctl(m_nfd,0xA00,0);
		ioctl(m_nfd, 0x103, 0);
	}
}

void CSttDeviceComm::SetSystemConfig()
{
	//防抖时间
	int nTime=g_theSystemConfig->m_fStabTime*10000;//ms
	ioctl(m_nfd,0x111,nTime);
}

void CSttDeviceComm::InitDApara(int fd)
{
	if(g_theDeviceSystemParameter->m_nModuleCount_U>PTU_MAX_MODULE_COUNT)
	{
		g_theDeviceSystemParameter->m_nModuleCount_U=PTU_MAX_MODULE_COUNT;
		g_theDeviceSystemParameter->m_nModuleCount_I=0;
		g_theDeviceSystemParameter->m_nModuleCount_WEEK=0;
	}
	else
	{
		if(g_theDeviceSystemParameter->m_nModuleCount_I>=
				PTU_MAX_MODULE_COUNT-g_theDeviceSystemParameter->m_nModuleCount_U)
		{
			g_theDeviceSystemParameter->m_nModuleCount_I=
					PTU_MAX_MODULE_COUNT-g_theDeviceSystemParameter->m_nModuleCount_U;
			g_theDeviceSystemParameter->m_nModuleCount_WEEK=0;
		}
		else
		{
			if(g_theDeviceSystemParameter->m_nModuleCount_WEEK>1)
				g_theDeviceSystemParameter->m_nModuleCount_WEEK=1;//PTU机箱只有一个位置可以插小信号
		}
	}

	g_theDeviceSystemParameter->m_nModuleCount_D=0;
	g_theDeviceSystemParameter->m_nModuleCount_FT3=0;
	g_theDeviceSystemParameter->m_nModuleCount_S=0;
	g_theDeviceSystemParameter->m_nModuleCount_UI=0;

	Sleep(100);//等待驱动初始化完成
	m_nfd=fd;
	ioctl(m_nfd, 0x110,5);//电流模块1的通道调整
	m_bSysOutPutRunning=FALSE;
	m_nTestTap=-1;
	SetSystemConfig();

	//开入模式
	ioctl(m_nfd,0x108,0);
	ioctl(m_nfd,0x109,0xffffffff);
	ioctl(m_nfd,0x10a,0xff);

	//防抖时间
	int nTime = 2;//ms
	nTime = nTime*10000;
	ioctl(m_nfd,0x111,nTime);

	unsigned int nYear,nMonth,nDay;
	CSttDeviceBase::g_pSttDeviceBase->InitDASetting(nYear,nMonth,nDay);

	GetBoardInfo();
}

/***
void CSttDeviceComm::AnalysisDrvSysInfo(DeviceParaState oDeviceParaState,BOOL bIsVolt)
{
	if(bIsVolt)
		CLogPrint::LogString(XLOGLEVEL_TRACE,_T("Volt"));
	else
		CLogPrint::LogString(XLOGLEVEL_TRACE,_T("Current"));

	for(int i=0;i<6;i++)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("i=%d,volt=%d"),
								   i,oDeviceParaState.nvolt[i]);
	}

	int nModuleType=STT_MODULE_TYPE_VOLT;
	if(!bIsVolt)
		nModuleType=STT_MODULE_TYPE_CURRENT;

	int nItemIndex=0;
	for(unsigned int i=0;i<g_theSttDeviceStatus->m_nAnalogCount;i++)
	{
		if(g_theSttDeviceStatus->m_oModule[i].m_nModuleType==nModuleType)
		{
			nItemIndex=i;
			break;
		}
	}
	STT_MODULE_STATUS &oModuleStatus=g_theSttDeviceStatus->m_oModule[nItemIndex];

	for(int i=0;i<6;i++)
	{
		oModuleStatus.m_oChannel[i].m_bIsOverLoad=oDeviceParaState.nvolt[5]&(1<<(i+1));//过载
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("i=%d,OverLoad=%d"),
								   i,oModuleStatus.m_oChannel[i].m_bIsOverLoad);
	}
	oModuleStatus.m_nIsVoltHot=oDeviceParaState.nvolt[5]&0x1;//电压过热
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("VoltHot=%d"),
							   oModuleStatus.m_nIsVoltHot);

	oModuleStatus.m_oChannel[0].m_fVoltMax=(oDeviceParaState.nvolt[0]&0xFFF00000)>>20;
	oModuleStatus.m_oChannel[1].m_fVoltMax=(oDeviceParaState.nvolt[0]&0xFFF00)>>8;
	oModuleStatus.m_oChannel[2].m_fVoltMax=(oDeviceParaState.nvolt[1]&0xFFF00000)>>20;
	oModuleStatus.m_oChannel[3].m_fVoltMax=(oDeviceParaState.nvolt[1]&0xFFF00)>>8;
	oModuleStatus.m_oChannel[4].m_fVoltMax=(oDeviceParaState.nvolt[2]&0xFFF00000)>>20;
	oModuleStatus.m_oChannel[5].m_fVoltMax=(oDeviceParaState.nvolt[2]&0xFFF00)>>8;

	oModuleStatus.m_oChannel[0].m_fVoltMin=oModuleStatus.m_oChannel[0].m_fVoltMax;
	oModuleStatus.m_oChannel[1].m_fVoltMin=oModuleStatus.m_oChannel[1].m_fVoltMax;
	oModuleStatus.m_oChannel[2].m_fVoltMin=oModuleStatus.m_oChannel[2].m_fVoltMax;
	oModuleStatus.m_oChannel[3].m_fVoltMin=oModuleStatus.m_oChannel[3].m_fVoltMax;
	oModuleStatus.m_oChannel[4].m_fVoltMin=oModuleStatus.m_oChannel[4].m_fVoltMax;
	oModuleStatus.m_oChannel[5].m_fVoltMin=oModuleStatus.m_oChannel[5].m_fVoltMax;

	for(int i=0;i<6;i++)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ChannelVolt[i]=%d"),
								   i,oModuleStatus.m_oChannel[i].m_fVoltMin);
	}

	oModuleStatus.m_fVoltDc[0]=(oDeviceParaState.nvolt[3]&0xFFF00000)>>20;
	oModuleStatus.m_fVoltDc[1]=(oDeviceParaState.nvolt[3]&0xFFF00)>>8;
	oModuleStatus.m_fVoltDc[2]=(oDeviceParaState.nvolt[4]&0xFFF00000)>>20;
	oModuleStatus.m_fVoltDc[3]=(oDeviceParaState.nvolt[4]&0xFFF00)>>8;

	for(int i=0;i<4;i++)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("VoltDc[i]=%d"),
								   i,oModuleStatus.m_fVoltDc[i]);
	}
	if(oModuleStatus.m_nIsVoltHot)
		g_theSttDeviceStatus->m_bNeedStop=TRUE;
}
***/


void CSttDeviceComm::SetBISetting()
{

}

long CSttDeviceComm::TranslateACFre(float fFre)
{
	long nH = (long)fFre*65536/400000.0;
	double fH = fFre*65536/400000.0;
	long nL = (fH - nH)*65536;
	long nFre  =((nH<<16)&0xFFFF0000)+nL;
	return nFre;
}

//volt
void CSttDeviceComm::TransAnalogDCVolToDrv(float fAmp,int nChannel,int nModuleUIndex,long *pDrvData)
{
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];
	if(pModule==NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	float fChMax=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_oModuleAttr.m_fChMax;
	float fChDcMax=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_oModuleAttr.m_fChDcMax;
	if(fChMax>0&&fChDcMax>0)
	{

	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	float fVoltMax=stt_adj_get_ac_max_GearVal(nChannel,pModule,0);
	if(fVoltMax>0&&fVoltMax<=fChDcMax)
	{
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

	float fTemperature = 0;//getTemperature();
	float fCoef = 1;
	float fZero = 0;
	PSTT_CHANNEL_ADJUSTS pChsAdjust=stt_adj_find_channel(pModule,nChannel,fTemperature);
	if(pChsAdjust!=NULL)
		fZero=pChsAdjust->m_fDcZero;//直流零漂
	PSTT_ADJUST_ITEM pAdjItem = stt_adj_get_ac(fabs(fAmp),pModule,nChannel,fTemperature,0);
	if(pChsAdjust!=NULL)
		fCoef = pAdjItem->m_fCoef;//幅值系数

	fAmp = fAmp*fCoef-fZero;

	fChMax=fChMax*1.414;
	if(fabs(fAmp)>EPSINON)
	{
		long nH = fAmp*32768/fChMax;//65536/2=32768
		double fH = fAmp*32768/fChMax;
		long nL = (fH - nH)*65536;
		pDrvData[0] = ((nH<<16)&0xFFFF0000)+nL;
	}
	else
	{
		pDrvData[0] = 0;
	}
}

long CSttDeviceComm::TranslateACVoltAmp(float fAmp,int nChannel,int nModuleUIndex,int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];
	if(pModule==NULL)
		return 0;

	CSttPowerCtrlBase *pSttPowerCtrlBase=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_oModuleAttr.m_pPowerCtrlBase;
	if(pSttPowerCtrlBase==NULL)
		return 0;

	BOOL bVoltUse440V=FALSE;
	float fVoltMax=0;
	fVoltMax=stt_adj_get_ac_max_GearVal(nChannel,pModule,nHarm);
	if(fVoltMax>0)
	{

	}
	else
		return 0;

	if(nHarm>1)
	{
		//无升压功能
		if(fAmp>pSttPowerCtrlBase->m_fMaxVal)
			fAmp=pSttPowerCtrlBase->m_fMaxVal;
	}
	else
	{
		if(pSttPowerCtrlBase->m_bVolt_440V)
		{
			if(fAmp>pSttPowerCtrlBase->m_fMaxVal)
				bVoltUse440V=TRUE;

			if(fAmp>fVoltMax)
				fAmp=fVoltMax;
		}
		else
		{
			//无升压功能
			if(fAmp>pSttPowerCtrlBase->m_fMaxVal)
				fAmp=pSttPowerCtrlBase->m_fMaxVal;
		}
	}

	float fChMax=0;
	float fTemperature=0;//getTemperature();
	PSTT_ADJUST_ITEM pAdjItem;
	float fCoef=1;//幅值系数
	float fZero=0;//交流零漂

	if(bVoltUse440V)
	{
		fChMax=pSttPowerCtrlBase->m_fMaxVal2;

		pAdjItem=stt_adj_get_ac(pSttPowerCtrlBase->m_fMaxVal,pModule,nChannel,fTemperature);
		if(pAdjItem!=NULL)
		{
			fCoef=pAdjItem->m_fCoef;
		}

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f"),nChannel,fCoef);
		fAmp =fAmp*fCoef;

		fCoef=1;
		pAdjItem=stt_adj_get_ac(pSttPowerCtrlBase->m_fMaxVal2,pModule,nChannel,fTemperature);
		if(pAdjItem!=NULL)
		{
			fCoef=pAdjItem->m_fCoef;
		}

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("VoltUse440V Volt_channel-%d  Coef=%f"),nChannel,fCoef);
		fAmp =fAmp*fCoef;
	}
	else
	{
		fChMax=pSttPowerCtrlBase->m_fMaxVal;

		pAdjItem=stt_adj_get_ac(fAmp,pModule,nChannel,fTemperature,nHarm);
		if(pAdjItem!=NULL)
		{
			fCoef=pAdjItem->m_fCoef;
		}

		//		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);
		fAmp =fAmp*fCoef;
	}

	fChMax=fChMax*1.2;

	if(fAmp>0)
	{
		long nH = fAmp*65536/fChMax;
		double fH = fAmp*65536/fChMax;
		long nL = (fH - nH)*65536;

		return ((nH<<16)&0xFFFF0000)+nL;
	}
	else
		return 0;
}

void CSttDeviceComm::TransAnalogVolToDrv(float fAmp,float fAng,float fFre,int nChannel,int nModuleUIndex,long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];
	if(pModule==NULL)
		return;

	int nHarm=0;
	int m_nEDFre=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	if(m_nEDFre<0.001)
		m_nEDFre=50;

	if(fFre<EPSINON)
	{
		//AC通道出DC
		pnDrvData[0] = 0;
		pnDrvData[1] = 0;
		TransAnalogDCVolToDrv(fAmp,nChannel,nModuleUIndex,&pnDrvData[2]);
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
	float faddPh = 0;
	PSTT_ADJUST_ITEM pAdjItem = stt_adj_get_ac(fAmp,pModule,nChannel,fTemperature);
	if(pAdjItem!=NULL)
		faddPh = pAdjItem->m_fAngle;
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

//current
void CSttDeviceComm::TransAnalogDCCurToDrv(float fAmp,int nChannel,int nModuleIIndex,long *pDrvData)
{
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
	if(pModule==NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	float fChMax=pModule->m_oModuleAttr.m_fChMax;
	float fChDcMax=pModule->m_oModuleAttr.m_fChDcMax;
	if(fChMax>0&&fChDcMax>0)
	{

	}
	else
		return;

	float fCurrentMax=stt_adj_get_ac_max_GearVal(nChannel,pModule,0);
	if(fCurrentMax>0&&fCurrentMax<=fChDcMax)
	{
		if(fabs(fAmp)>fCurrentMax)
		{
			if(fAmp>0)
				fAmp=fCurrentMax;
			else
				fAmp=fCurrentMax*(-1);
		}
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}
	/*************确定合适的fAmp值************/


	float fTemperature = 0;//getTemperature();
	float fCoef = 1;
	float fZero = 0;
	float fMaxRatio = 1;

	PSTT_CHANNEL_ADJUSTS pChsAdjust=stt_adj_find_channel(pModule,nChannel,fTemperature);
	if(pChsAdjust!=NULL)
	{
		fZero=pChsAdjust->m_fDcZero;//直流零漂
		fMaxRatio = pChsAdjust->m_fLargeCurrentRatio;
	}

	PSTT_ADJUST_ITEM pAdjItem = stt_adj_get_ac(fabs(fAmp),pModule,nChannel,fTemperature,0);//幅值系数
	if(pAdjItem!=NULL)
		fCoef = pAdjItem->m_fCoef;

	fAmp = -fAmp*fCoef;
	if(fabs(fAmp)>5&&fCurrentMax>5)
	{
		fAmp = fAmp-fAmp*(fAmp-5)*(fAmp-5)*(fMaxRatio-1)/((fCurrentMax - 5)*(fCurrentMax - 5));
	}
	fAmp += fZero;

	fChMax=fChMax*1.414;
	if(fabs(fAmp)>EPSINON)
	{
		long nH = fAmp*32768/fChMax;//65536/2=32768
		double fH = fAmp*32768/fChMax;
		long nL = (fH - nH)*65536;
		pDrvData[0] = ((nH<<16)&0xFFFF0000)+nL;
	}
	else
	{
		pDrvData[0] = 0;
	}
}

long CSttDeviceComm::TranslateACCurrentAmp(float fAmp,int nChannel,int nModuleIIndex,int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
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
	//fCurrentMax限制fAmp的最大值
	float fCurrentMax=stt_adj_get_ac_max_GearVal(nChannel,pModule,nHarm);
	if(fCurrentMax>0&&fCurrentMax<=fChMax)
	{
		if(fAmp>fCurrentMax)
			fAmp=fCurrentMax;
	}
	else
	{
		return 0;
	}
	/*************确定合适的fAmp值************/

	float fTemperature = 0;//getTemperature();
	float fCoef = 1;//幅值系数
	//	float fZero=0;//交流零漂
	float fMaxRatio = 1.0;
	PSTT_ADJUST_ITEM pAdjItem=stt_adj_get_ac(fAmp,pModule,nChannel,fTemperature,nHarm);
	if(pAdjItem!=NULL)
	{
		fCoef=pAdjItem->m_fCoef;
		//		fZero=pAdjItem->m_fZero;
	}
	PSTT_CHANNEL_ADJUSTS pChsAdjust=stt_adj_find_channel(pModule,nChannel,fTemperature);
	if(pChsAdjust!=NULL)
		fMaxRatio = pChsAdjust->m_fLargeCurrentRatio;

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Current_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);

	fAmp =fAmp*fCoef;

	if(fAmp>5&&fChMax>5)
	{
		fAmp = fAmp-fAmp*(fAmp-5)*(fAmp-5)*(fMaxRatio-1)/((fChMax - 5)*(fChMax - 5));
	}

	if(fAmp>0)
	{
		fChMax=fChMax*1.2;
		long nH = fAmp*65536/fChMax;
		double fH = fAmp*65536/fChMax;
		long nL = (fH - nH)*65536;

		return ((nH<<16)&0xFFFF0000)+nL;
	}
	else
		return 0;
}

void CSttDeviceComm::TransAnalogCurToDrv(float fAmp,float fAng,float fFre,int nChannel,int nModuleIIndex,long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
	if(pModule==NULL)
		return;

	int nHarm=0;
	int m_nEDFre=g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	if(m_nEDFre<EPSINON)
		m_nEDFre=50;

	if(fFre<EPSINON)
	{
		//AC通道出DC
		pnDrvData[0] = 0;
		pnDrvData[1] = 0;
		TransAnalogDCCurToDrv(fAmp,nChannel,nModuleIIndex,&pnDrvData[2]);
		return;
	}
	fAmp=fabs(fAmp);

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
	if(pAdjItem!=NULL)
		faddPh = pAdjItem->m_fAngle;
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

//PTU100 PTU200
//if(g_theSystemConfig->m_bIout_ChansMergeOne)
//{
//	float fTemp=pTmt->m_oManuParas.m_uiCUR[0].Harm[1].fAmp;
//	for(int i=0;i<CHANNEL_MAX;i++)
//	{
//		pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp=fTemp/6;
//	}
//}


void CSttDeviceComm::Manual_Volt(tmt_channel *pTmt_channel,long *pDrvData,int nHarm,
								 long nModuleUIndex,BOOL bIsDc,BOOL bIsModuleOutput)
{
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];
	if(pModule==NULL)
		return;

	int nChPos;
	float fAmp=0;
	int nTmtChanNum=pModule->m_oModuleAttr.m_nChannelNum;
	int nTmtPos;
	if(bIsDc)
	{
		for(int k=0; k<nTmtChanNum; k++)
		{
			nTmtPos=k;
			if(!bIsModuleOutput)
			{
				nTmtPos=pModule->m_nChTmtPos[k];
			}
			if(nTmtPos<0)
				fAmp=0;
			else
				fAmp=pTmt_channel[nTmtPos].Harm[1].fAmp;
			nChPos=pModule->m_nChDrvPos[k];

			TransAnalogDCVolToDrv(fAmp,k,nModuleUIndex,pDrvData+nChPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq=0;
		float fAngle=0;
		for(int k=0; k<nTmtChanNum; k++)
		{
			nTmtPos=k;
			if(!bIsModuleOutput)
			{
				nTmtPos=pModule->m_nChTmtPos[k];
			}
			if(nTmtPos<0)
				fAmp=0;
			else
				fAmp=pTmt_channel[nTmtPos].Harm[0].fAmp;
			nChPos=pModule->m_nChDrvPos[k];

			TransAnalogDCVolToDrv(fAmp,k,nModuleUIndex,pDrvData+nChPos);

			for(int m=0;m<nHarm;m++)
			{
				if(nTmtPos<0)
				{
					fAmp=0;
					fFreq=50;
				}
				else
				{
					oTmtHarm=&pTmt_channel[nTmtPos].Harm[m+1];
					fAmp=oTmtHarm->fAmp;
					fAngle=oTmtHarm->fAngle;
					fFreq=oTmtHarm->fFreq;
				}

				TransAnalogVolToDrv(fAmp,fAngle,fFreq,k,nModuleUIndex,
									pDrvData+CHANNEL_MAX+nChPos*3+m*3*CHANNEL_MAX);
			}
		}
	}
}

void CSttDeviceComm::Manual_Current(tmt_channel *pTmt_channel,long *pDrvData,int nHarm,
									long nModuleIIndex,BOOL bIsDc,BOOL bIsModuleOutput)
{
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];
	if(pModule==NULL)
		return;

	float fAmp;
	int nChPos;
	int nTmtChanNum=pModule->m_oModuleAttr.m_nChannelNum;
	int nTmtPos;
	if(bIsDc)
	{
		for(int k=0; k<nTmtChanNum; k++)
		{
			nTmtPos=k;
			if(!bIsModuleOutput)
			{
				nTmtPos=pModule->m_nChTmtPos[k];
			}
			if(nTmtPos<0)
				fAmp=0;
			else
				fAmp=pTmt_channel[nTmtPos].Harm[1].fAmp;
			nChPos=pModule->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fAmp,k,nModuleIIndex,pDrvData+nChPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq=0;
		float fAngle=0;
		for(int k=0; k<nTmtChanNum; k++)
		{
			nTmtPos=k;
			if(!bIsModuleOutput)
			{
				nTmtPos=pModule->m_nChTmtPos[k];
			}
			if(nTmtPos<0)
				fAmp=0;
			else
				fAmp=pTmt_channel[nTmtPos].Harm[0].fAmp;
			nChPos=pModule->m_nChDrvPos[k];

			TransAnalogDCCurToDrv(fAmp,k,nModuleIIndex,pDrvData+nChPos);

			for(int m=0;m<nHarm;m++)
			{
				if(nTmtPos<0)
				{
					fAmp=0;
					fFreq=50;
				}
				else
				{
					oTmtHarm=&pTmt_channel[nTmtPos].Harm[m+1];
					fAmp=oTmtHarm->fAmp;
					fAngle=oTmtHarm->fAngle;
					fFreq=oTmtHarm->fFreq;
				}

				TransAnalogCurToDrv(fAmp,fAngle,fFreq,k,nModuleIIndex,
									pDrvData+CHANNEL_MAX+nChPos*3+m*3*CHANNEL_MAX);
			}
		}
	}
}

/***
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
