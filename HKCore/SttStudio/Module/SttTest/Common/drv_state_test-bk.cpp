#include "stdafx.h"
#include "drv_state_test.h"
#include"math.h"
#include"../../SttDevice/SttDeviceBase.h"
#include "../../SttDevice/SttDeviceBase.h"
#include "Iec61850Config.h"
#include "IEC61850CfgMngr.h"

QVector<int> ChannelVolts,ChannelCurrs;


//void tmt_to_drv_rmp_channel_analog(tmt_StatePara &oTmtState ,QVector<int> uChannelNum,drv_state &oDrvState,int nType)
//{
//	float fChangeValue = oTmtState.m_sttGradient.fEnd - oTmtState.m_sttGradient.fStart;
//	float fStep = fabs(oTmtState.m_sttGradient.fStep);
//	unsigned int uChangeCount = fabs(fChangeValue/fStep);

//	if(oTmtState.m_sttGradient.fEnd < oTmtState.m_sttGradient.fStart)
//	{
//		fStep = -fStep;
//	}

//	int Drvchannel=0;

//	for(int i=0;i<uChannelNum.size();i++)
//	{
//		int channel=uChannelNum.at(i);
//		int nTemp = channel/CHANNEL_MAX;
//		oDrvState.stChange[nTemp].nIsChange=1;
//		if(!(fabs(fChangeValue/fStep)-uChangeCount < 0.0000001))//两者不等，则增加一次递变次数
//			uChangeCount++;
//		oDrvState.stChange[nTemp].nChangeCount=uChangeCount;

//		float fTemp = fChangeValue-fStep*(uChangeCount-1);

//		switch(nType)
//		{
//		case VOLT:
//		{
//			oDrvState.stChange[nTemp].nModule=CSttDevice::g_pSttDevice->getModuleNum(VOLT,nTemp);

//			//Drvchannel=CSttDevice::g_pSttDevice->GetChannelIndex_Drv_Amp(channel,VOLT);
//			Drvchannel=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(channel,VOLT,Amp);
//			oDrvState.stChange[nTemp].nChangeValue[Drvchannel] = CSttDeviceBase::g_pSttDeviceBase->TranslateACVoltAmp(fStep,channel);

//			int nDvDt  = CSttDeviceBase::g_pSttDeviceBase->TranslateACVoltAmp(fTemp,channel);
//			oDrvState.stChange[nTemp].nLastChangeValue[Drvchannel] = nDvDt;
//		}
//			break;
//		case CURRENT:
//		{
//			oDrvState.stChange[nTemp].nModule=CSttDevice::g_pSttDevice->getModuleNum(CURRENT,nTemp);

//			//Drvchannel=CSttDevice::g_pSttDevice->GetChannelIndex_Drv_Amp(channel,CURRENT);
//			Drvchannel=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(channel,CURRENT,Amp);
//			oDrvState.stChange[nTemp].nChangeValue[Drvchannel] = CSttDeviceBase::g_pSttDeviceBase->TranslateACCurrentAmp(fStep,channel);
//		}
//			break;
//		}
//	}
//}

//void tmt_to_drv_rmp_channel_digital(tmt_StatePara &oTmtState ,QVector<int> uChannelNum,drv_digitalchange &oDrvChange,int nType)
//{
//	if(uChannelNum.count()==0)
//		return;

//	float fChangeValue = oTmtState.m_sttGradient.fEnd - oTmtState.m_sttGradient.fStart;
//	float fStep = oTmtState.m_sttGradient.fStep;
//	float uChangeCount = fabs(fChangeValue)/fStep;
//	oDrvChange.nChangeCount = uChangeCount;

//	if(!((uChangeCount - (int)uChangeCount ) < 0.0000001))
//		oDrvChange.nChangeCount+=1; //有余数，需要有额外的一步去递变到终止值

//	if(oTmtState.m_sttGradient.fEnd < oTmtState.m_sttGradient.fStart)
//	{
//		fStep = -fStep;
//	}

//	float fTemp = fChangeValue-fStep*(oDrvChange.nChangeCount-1);

//	for(int i=0;i<uChannelNum.count();i++)
//	{
//		int chanid=uChannelNum.at(i);
//		long nGroupIndex = chanid/3;
//		int channel_Type=chanid%3;//A B C
//		int DrvChannel=0;
//		switch(nType)
//		{
//		case VOLT:
//		{
//			//CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(nGroupIndex,DrvChannel,VOLT);
//			DrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(nGroupIndex,VOLT,Amp);
//			oDrvChange.nChangeValue[3*channel_Type+DrvChannel] = CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolAmp(fStep,nGroupIndex,false);
//			oDrvChange.nLastChangeValue[3*channel_Type+DrvChannel] = CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolAmp(fTemp,nGroupIndex,false);
//			oTmtState.m_uiVOL[chanid].Harm[1].fAmp=oTmtState.m_sttGradient.fStart;
//		}
//			break;
//		case CURRENT:
//		{
//			//CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(nGroupIndex,DrvChannel,CURRENT);
//			DrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(nGroupIndex,CURRENT,Amp);
//			oDrvChange.nChangeValue[3*channel_Type+DrvChannel] = CSttDeviceBase::g_pSttDeviceBase->TransDigitalCurAmp(fStep,nGroupIndex,false);
//			oDrvChange.nLastChangeValue[3*channel_Type+DrvChannel] = CSttDeviceBase::g_pSttDeviceBase->TransDigitalCurAmp(fTemp,nGroupIndex,false);
//			oTmtState.m_uiCUR[chanid].Harm[1].fAmp=oTmtState.m_sttGradient.fStart;
//		}
//			break;
//		}
//	}
//}

//void setDvDt(tmt_StatePara &pState,drv_state &oState,QVector<int> vChanel)
//{
//	float fBeginV,fEndV;
//	float fDvdt;

//	bool bDC =pState.m_bDC;
//	tmt_StateGradient *pGadient =&pState.m_sttGradient;

//	fBeginV = pGadient->fStart;
//	fEndV = pGadient->fEnd;
//	fDvdt = pGadient->fdvdt;

//	if(fabs(fDvdt)<0.00001)
//	{
//		return;
//	}

//	oState.stChange[0].nIsChange = 1;
//	oState.stChange[0].nModule = CSttDevice::g_pSttDevice->getModuleNum(VOLT,0); //zhangsen 20180822
//	long nDvDt = 0;
//	if(vChanel.size()>0)
//	{
//		if(bDC)
//		{
//			//CSttDevice::g_pSttDevice->TranslateUValueToLongDC(fDvdt/1000,nDvDt,vChanel.at(0));
//			CSttDevice::g_pSttDevice->TransAnalogDCCurToDrv(fDvdt/1000,vChanel.at(0),&nDvDt);
//		}
//		else
//		{
//			nDvDt  = CSttDeviceBase::g_pSttDeviceBase->TranslateACVoltAmp(fDvdt/1000,vChanel.at(0));
//		}
//	}
//	double fdvdtRU = CSttDevice::g_pSttDevice->getAnalogVoltMax(vChanel.at(0))/65536.0/65536.0;
//	long nTimegap = 1;
//	int nCount;
//	if(nDvDt==0)
//	{
//		nDvDt = 1;
//		nTimegap = fdvdtRU*1000.0/fDvdt;
//		nCount =  fabs(fEndV - fBeginV)/(nDvDt*fdvdtRU);
//	}
//	else
//	{
//		nTimegap = 1;
//		nCount = fabs(fEndV - fBeginV)*1000.0/fDvdt+1;
//	}

//	oState.stChange[0].nChangeCount = nCount;
//	if(fEndV<fBeginV)
//	{
//		nDvDt = -nDvDt;
//	}

//	int Drvchannel=0;
//	for(int i=0;i<vChanel.size();i++)
//	{
//		if(bDC)
//		{
//			Drvchannel=CSttDevice::g_pSttDevice->GetVoltChannelMap(vChanel.at(i));
//			oState.stChange[0].nChangeValue[Drvchannel] = nDvDt;
//		}
//		else
//		{
//			//Drvchannel=CSttDevice::g_pSttDevice->GetChannelIndex_Drv_Amp(vChanel.at(i),VOLT);
//			Drvchannel=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(vChanel.at(i),VOLT,Amp);
//			oState.stChange[0].nChangeValue[Drvchannel] = nDvDt;
//		}
//	}
//	oState.nChangemSec = nTimegap;
//}


//BOOL tmt_to_drv_rmp_digital(tmt_StatePara &oTmtState,drv_state &oDrvState)
//{
//	int nDrvChannel=0;
//	//	int channelvolt_group0=0,channelvolt_group1=0;
//	//	int channelcurr_group0=0,channelcurr_group1=0;
//	//	CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(0,channelvolt_group0,VOLT);
//	//	CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(1,channelvolt_group1,VOLT);
//	//	CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(0,channelcurr_group0,CURRENT);
//	//	CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(1,channelcurr_group1,CURRENT);

//	oDrvState.stDigitalChange[0].nIsChange = 1;
//	oDrvState.stDigitalChange[0].nModule = DIGITAL_CHANNEL_MARK;//按位设置
//	oDrvState.nChangemSec = 1;//递变时间分度设置为1

//	switch (oTmtState.m_nRampType)
//	{
//	case STATE_RAMP_TYPE_SLIP_VAL:
//	{
//		oDrvState.stDigitalChange[0].nChangeCount = fabs(oTmtState.m_sttGradient.fEnd - oTmtState.m_sttGradient.fStart)*1000.0f/oTmtState.m_sttGradient.fdvdt;
//		float fRmpValue =0;
//		fRmpValue =  (oTmtState.m_sttGradient.fdvdt)*0.001f;

//		if(oTmtState.m_sttGradient.fStart>oTmtState.m_sttGradient.fEnd)
//			fRmpValue *= -1;

//		int nDrvValue=0;

//		for(int i=0;i<ChannelVolts.size();i++)
//		{
//			int chan=ChannelVolts.at(i);
//			int group=chan/3;
//			int chan_type=chan%3;
//			switch(group)
//			{
//			case 0:
//				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(0,VOLT,Amp);
//				nDrvValue=CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolAmp(fRmpValue,0,false);
//				break;
//			case 1:
//				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(1,VOLT,Amp);
//				nDrvValue=CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolAmp(fRmpValue,1,false);
//				break;
//			}
//			oDrvState.stDigitalChange[0].nChangeValue[chan_type*3+nDrvChannel]=nDrvValue;
//			oTmtState.m_uiVOL[chan].Harm[1].fAmp=oTmtState.m_sttGradient.fStart;
//		}
//	}
//		break;
//	case STATE_RAMP_TYPE_SLIP_FRE:
//	{
//		oDrvState.stDigitalChange[0].ndfcount = fabs(oTmtState.m_sttGradient.fEnd - oTmtState.m_sttGradient.fStart)*1000/oTmtState.m_sttGradient.fdfdt;
//		long nRmpValue = 0;
//		nRmpValue = CSttDeviceBase::g_pSttDeviceBase->TranslateDigitalFre(oTmtState.m_sttGradient.fdfdt/1000);//1.073741824 = (2的30次方除以10的9次方)
//		//            nRmpValue = fabs(oTmtState.m_sttGradient.fdfdt)*m_pDeviceParas->m_fFreCof_Std/(1000*1.073741824);//1.073741824 = (2的30次方除以10的9次方)

//		if(oTmtState.m_sttGradient.fStart>oTmtState.m_sttGradient.fEnd)
//			nRmpValue *= -1;

//		for(int i=0;i<ChannelVolts.size();i++)
//		{
//			int chan=ChannelVolts.at(i);
//			int group=chan/3;
//			int chan_type=chan%3;
//			switch(group)
//			{
//			case 0:
//				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(0,VOLT,Fre);
//				break;
//			case 1:
//				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(1,VOLT,Fre);
//				break;
//			}
//			oDrvState.stDigitalChange[0].nChangeValue[chan_type*3+nDrvChannel]=nRmpValue;
//			oTmtState.m_uiVOL[chan].Harm[1].fFreq=oTmtState.m_sttGradient.fStart;
//		}

//		for(int i=0;i<ChannelCurrs.size();i++)
//		{
//			int chan=ChannelCurrs.at(i);
//			int group=chan/3;
//			int chan_type=chan%3;
//			switch(group)
//			{
//			case 0:
//				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(0,CURRENT,Fre);
//				break;
//			case 1:
//				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(1,CURRENT,Fre);
//				break;
//			}
//			oDrvState.stDigitalChange[0].nChangeValue[chan_type*3+nDrvChannel]=nRmpValue;
//			oTmtState.m_uiCUR[chan].Harm[1].fFreq=oTmtState.m_sttGradient.fStart;
//		}
//	}
//		break;
//	case STATE_RAMP_TYPE_NORMAL:
//	{
//		oDrvState.nChangemSec = oTmtState.m_sttGradient.fStepTime*1000;//递变每步的时间
//		tmt_to_drv_rmp_channel_digital(oTmtState,ChannelVolts,oDrvState.stDigitalChange[0],VOLT);
//		tmt_to_drv_rmp_channel_digital(oTmtState,ChannelCurrs,oDrvState.stDigitalChange[0],CURRENT);
//	}
//		break;
//	}

//	return TRUE;
//}

//void tmt_to_drv(tmt_StateParas &oStateParas,int nIndex,drv_state &oDrvState)
//{
//	memset(&oDrvState,0,sizeof(drv_state));
//	tmt_StatePara oTmtState=oStateParas.m_paraState[nIndex];
//	oDrvState.nReversal = oTmtState.m_eBinReversal;

//	unsigned int nLogicValid = 0;

//	for (int i=0; i<8; i++)
//	{
//		nLogicValid |= ((oTmtState.m_binIn[i].nSelect?1:0)<<i);
//	}

//	if(oTmtState.m_nBinLogic)//And
//	{
//		oDrvState.nAndValid = nLogicValid;
//		oDrvState.nOrValid = 0;
//	}
//	else//Or
//	{
//		oDrvState.nAndValid  = 0;
//		oDrvState.nOrValid = nLogicValid;
//	}

//	//oDrvState.gpsSec = oTmtState.m_tGps.Year + oTmtState.m_tGps;
//	oDrvState.nGpsnSec = oTmtState.m_tGps.nMilliSeconds*1000000;//纳秒值转换
//	oDrvState.nTimemSec = oTmtState.m_fTimeState*1000;
//	oDrvState.nDelay = oTmtState.m_fTimeAfterTrigger*1000;
//	oDrvState.nDelay = oTmtState.m_fTimeAfterTrigger*1000;

//	oDrvState.oBo.nBoValue = 0;

//	//设置递变
//	if(oTmtState.m_nRampType != STATE_RAMP_TYPE_NULL)
//	{
//		CSttDevice::GetTMTChannels(oTmtState.m_sttGradient.iVar,ChannelVolts,ChannelCurrs);
//		tmt_to_drv_rmp_analog(oTmtState,oDrvState);
//#ifdef _USE_IEC61850_
//		tmt_to_drv_rmp_digital(oTmtState,oDrvState);
//#endif
//	}

//	//设置模拟量值
//	tmt_to_drv_analog(oTmtState,oDrvState.acAnalog);

//#ifdef _USE_IEC61850_
//	//设置数字量值
//	tmt_to_drv_digital(oTmtState,oDrvState.Digital.oModuledata[0]);
//#endif

//	//设置开出量

//	for (long i = 0;i<10;i++)
//	{
//		oDrvState.oBo.nBoValue += ((!oTmtState.m_binOut[i].nState)*(1<<i));

//		if (oTmtState.m_binOut[i].nMode)
//		{
//			oDrvState.oBo.ntrigerMode = 1;
//		}

//		if (oTmtState.m_binOut[i].fTimeTrig>0)
//		{
//			oDrvState.oBo.ntimeDelay = oTmtState.m_binOut[i].fTimeTrig*1000;
//		}

//		if (oTmtState.m_binOut[i].fHoldTime>0)
//		{
//			oDrvState.oBo.nHoldTime = oTmtState.m_binOut[i].fHoldTime*1000;
//		}
//	}

//	//设置触发条件
//	switch(oTmtState.m_nTriggerCondition)
//	{
//	case TMT_MDSTATE_TIMETRIGGER:
//		oDrvState.nTirpType[1] = oDrvState.nStateNum+1;
//		break;
//	case TMT_MDSTATE_TIMEBINTRIGGER:
//	{
//		oDrvState.nTirpType[1] = oDrvState.nStateNum+1;

//		if (oTmtState.m_nBinLogic)
//		{
//			oDrvState.nTirpType[3] = oDrvState.nStateNum+1;
//		}
//		else
//		{
//			oDrvState.nTirpType[4] = oDrvState.nStateNum+1;
//		}
//	}
//		break;
//	case TMT_MDSTATE_BINTRIGGER:
//	{
//		if (oTmtState.m_nBinLogic)
//		{
//			oDrvState.nTirpType[3] = oDrvState.nStateNum+1;
//		}
//		else
//		{
//			oDrvState.nTirpType[4] = oDrvState.nStateNum+1;
//		}
//	}
//		break;
//	case TMT_MDSTATE_MEARSURETRIGGER:
//		oDrvState.nTirpType[0] = oDrvState.nStateNum+1;
//		break;
//	case TMT_MDSTATE_GPSBTRIGGER:
//		oDrvState.nTirpType[2] = oDrvState.nStateNum+1;
//		break;
//	}

//#ifdef _USE_IEC61850_
//	//goosechange
//	if(nIndex>0)
//		CIEC61850CfgMngr::g_pIEC61850CfgMngr->SetGooseValue(oStateParas,nIndex,&oDrvState);
//#endif
//}

////
////2020-10-06
void tmt_to_drv_StatePara(tmt_StateTest *pTmt, Drv_StatePara *pDrv)
{
	pDrv->nStateCount = pTmt->m_oStateParas.m_nStateNumbers;//*pTmt->m_oStateParas.m_nRepeatNumbers
	pDrv->nIsLoop = 0;
	pDrv->nbiRef = pTmt->m_oStateParas.m_nBinTripRef;
	Drv_BIStatus gooseInit;
	memset(&gooseInit,0,sizeof(Drv_BIStatus));
	pDrv->oGooseInit = gooseInit;
}

void setTriger(tmt_StatePara  oTmt_paraState,Drv_StateItem *oDrv_StateItem,int nIndex)
{
	oDrv_StateItem->nStateNum = nIndex;

	switch(oTmt_paraState.m_nTriggerCondition)
	{
	case TMT_MDSTATE_MEARSURETRIGGER://手动触发
	{
		oDrv_StateItem->nTirpType = State_Trig_Manual;
		break;
	}
	case TMT_MDSTATE_TIMETRIGGER://时间触发
	{
		oDrv_StateItem->nTirpType = State_Trig_TimeDelay;

		oDrv_StateItem->oTm.oTime.nMsec =oTmt_paraState.m_fTimeState*1000;
		break;
	}
	case TMT_MDSTATE_BINTRIGGER:
	{
		oDrv_StateItem->nTirpType = State_Trig_Bin;
		oDrv_StateItem->obiTrip.nBiLogic =0;
		if(oTmt_paraState.m_nBinLogic==TMT_BINLOGIC_AND)
			oDrv_StateItem->obiTrip.nBiLogic =1;

		oDrv_StateItem->obiTrip.nBiRef  = oTmt_paraState.m_eBinReversal;
		oDrv_StateItem->oTm.oTime.nDelay = oTmt_paraState.m_fTimeAfterTrigger*1000;

		oDrv_StateItem->obiTrip.oValid.item[0].nVal1 = 0;
		oDrv_StateItem->obiTrip.oValid.item[0].nModule = 0x8000;
		oDrv_StateItem->obiTrip.oValid.nModuleCount = 1;

		for (int i=0; i<8; i++)
		{
			oDrv_StateItem->obiTrip.oValid.item[0].nVal1 |= oTmt_paraState.m_binIn[i].nSelect<<i;
		}


		//		if(pState->nexbivalide1()>0)
		//		{
		//			oDrv_StateItem.obiTrip.oValid.nModuleCount = 2;
		//			//      oState.obiTrip.oValid.item[1].nVal1 = 1;
		//			oDrv_StateItem.obiTrip.oValid.item[1].nVal1 = pState->nexbivalide1();
		//			oDrv_StateItem.obiTrip.oValid.item[1].nVal2 = pState->nexbivalide2();
		//			oDrv_StateItem.obiTrip.oValid.item[1].nModule = 8;
		//		}

		break;
	}
	case TMT_MDSTATE_GPSBTRIGGER://GPS触发
	{
		oDrv_StateItem->nTirpType = State_Trig_GPS;
		QDateTime datetime;
		QDate date;
		date.setYMD(oTmt_paraState.m_tGps.nYear,oTmt_paraState.m_tGps.nMonth,oTmt_paraState.m_tGps.nDay);
		datetime.setDate(date);
		QTime time;
		time.setHMS(oTmt_paraState.m_tGps.nHour,oTmt_paraState.m_tGps.nMinutes,oTmt_paraState.m_tGps.nSeconds);
		datetime.setTime(time);
		oDrv_StateItem->oTm.oGps.nNsec = oTmt_paraState.m_tGps.nMilliSeconds*1000000;//纳秒值转换
		oDrv_StateItem->oTm.oGps.nSec = datetime.toTime_t();
		break;
	}
	case TMT_MDSTATE_TIMEBINTRIGGER:
	{
		oDrv_StateItem->nTirpType = State_Trig_Bin_TimeDelay;
		oDrv_StateItem->obiTrip.nBiLogic =0;
		if(oTmt_paraState.m_nBinLogic==TMT_BINLOGIC_AND)
			oDrv_StateItem->obiTrip.nBiLogic =1;

		oDrv_StateItem->obiTrip.nBiRef  =oTmt_paraState.m_eBinReversal;
		oDrv_StateItem->oTm.oTime.nMsec =oTmt_paraState.m_fTimeState*1000;
		oDrv_StateItem->oTm.oTime.nDelay = oTmt_paraState.m_fTimeAfterTrigger*1000;

		oDrv_StateItem->obiTrip.oValid.item[0].nVal1 = 0;
		oDrv_StateItem->obiTrip.oValid.item[0].nModule = 0x8000;
		oDrv_StateItem->obiTrip.oValid.nModuleCount = 1;

		for (int i=0; i<32; i++)
		{
			oDrv_StateItem->obiTrip.oValid.item[0].nVal1 |= oTmt_paraState.m_binIn[i].nSelect<<i;
		}
		//		if(pState->nexbivalide1()>0)
		//		{
		//			oDrv_StateItem.obiTrip.oValid.nModuleCount = 2;
		//			oDrv_StateItem.obiTrip.oValid.item[1].nVal1 = pState->nexbivalide1();
		//			oDrv_StateItem.obiTrip.oValid.item[1].nVal2 = pState->nexbivalide2();
		//			oDrv_StateItem.obiTrip.oValid.item[1].nModule = 8;
		//		}
		break;
	}
	default:
		break;
	}
}

void tmt_to_drv_analog_volt(Drv_StateItem *oDrv_StateItem,tmt_StatePara  oTmt_paraState,int nModuleUIndex)
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

void tmt_to_drv_analog_current(Drv_StateItem *oDrv_StateItem,tmt_StatePara  oTmt_paraState,int nModuleIIndex)
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

//void setDvDt_analog_singlemodule(structChangeNew &oChange,float fBeginV,float fEndV,float fDvdt,long &nTimegap,int nModuleUIndex,BOOL bDC)
//{
//	int nChPos=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_nChDrvPos[k];
//	oChange.nIsChange = 1;

//	long nDvDt = 0;
//	if(vChanel.size()>0)
//	{
//		if(bDC)
//		{
//			TranslateUValueToLongDC(fDvdt/1000,nDvDt,vChanel.at(0));
//		}
//		else
//		{
//			nDvDt  = TranslateACVoltAmp(fDvdt/1000,vChanel.at(0));
//		}
//	}
//	double fdvdtRU = Device::g_Device->getAnalogVoltMax()/65536.0/65536.0;

//	int nCount;
//	if(nDvDt==0)
//	{
//		nDvDt = 1;
//		nTimegap = fdvdtRU*1000.0/fDvdt;
//		nCount =  fabs(fEndV - fBeginV)/(nDvDt*fdvdtRU);
//	}
//	else
//	{
//		nTimegap = 1;
//		nCount = fabs(fEndV - fBeginV)*1000.0/fDvdt+1;
//	}

//	oChange.nAmpCount = nCount;
//	if(fEndV<fBeginV)
//	{
//		nDvDt = -nDvDt;
//	}

//	for(int i=0;i<ChannelVolts.size();i++)
//	{
//		nChPos=g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex]->m_nChDrvPos[ChannelVolts.at(i)];
//		if(bDC)
//		{
//			oChange.changeVal[nChPos] = nDvDt;
//		}
//		else
//		{
//			oChange.changeVal[nChPos*3+CHANNEL_MAX+2] = nDvDt;
//		}
//	}
//	oChange.nDWCount = 6+18;
//}

//void setDvDt_analog(tmt_StatePara oTmt_paraState,Drv_StateItem &oDrv_StateItem)
//{
//	tmt_StateGradient &oStateGradient=oTmt_paraState.m_sttGradient;

//	float fBeginV = oStateGradient.fStart;
//	float fEndV = oStateGradient.fEnd;
//	float fDvdt = oStateGradient.fdvdt;

//	if(fabs(fDvdt)<0.00001)
//	{
//		return;
//	}

//	long nTimegap = 1;
//	//VOLT
//	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
//	{
//		setDvDt_analog_singlemodule(oDrv_StateItem.oStChange[nIndex],fBeginV,fEndV,fDvdt,nTimegap,nIndex,oTmt_paraState.m_bDC);
//	}

//	oDrv_StateItem.nChangemSec = nTimegap;
//}

//void setDFDt_analog(tmt_StatePara oTmt_paraState,Drv_StateItem &oDrv_StateItem,QVector<int> vChanel,QVector<int> iChanel)
//{
//	float fBeginFre,fEndFre;
//	float fDfdt;
//	float fDfdtTime;

//	StatePara::GradientPara* pGadient =  pState->mutable_oanagradientpara();
//	ogradient.bDfDt = true;
//	fBeginFre = pGadient->fstarthz();
//	fEndFre = pGadient->fendhz();
//	fDfdt = pGadient->fdfdt();

//	if(fabs(fDfdt<0.0001))
//	{
//		return;
//	}

//	fDfdtTime = fabs(fEndFre - fBeginFre)/fDfdt;


//	stChange.nIsChange = 1;


//	QVector<int> vChanel;
//	int nVoltorCur=0;
//	FpgaDirectOper::g_FpgsDirectOper->getCurrentVChanelAndType(pGadient->ivar(),vChanel,nVoltorCur);
//	ogradient.vChangel= vChanel;


//	float fTemp = fDfdt/1000.0;
//	int nCount;

//	long nDfDt = Device::g_Device->TranslateACFre(fDfdt/1000.0);
//	double fdfdtRU = 400000.0/65535.0/65535;
//	long nTimegap = 1;
//	if(nDfDt==0)
//	{
//		nDfDt = 1;
//		nTimegap = fdfdtRU*1000.0/fDfdt;
//		nCount =  fabs(fEndFre - fBeginFre)/(nDfDt*fdfdtRU);
//		ogradient.fdfstep = nDfDt*fdfdtRU;
//	}
//	else
//	{
//		nCount =  Device::g_Device->TranslateACFre(fabs(fEndFre - fBeginFre))/nDfDt;
//		ogradient.fdfstep = fDfdt/1000.0;
//	}


//	stChange.nFreCount = nCount;

//	ogradient.fFreBegin = fBeginFre;
//	ogradient.fFreEnd = fEndFre;
//	if(fEndFre<fBeginFre)
//	{
//		nDfDt = -nDfDt;
//	}
//	//qDebug()<<"vchanelsize"<<vChanel.size();
//	for(int i=0;i<vChanel.size();i++)
//	{
//		stChange.changeVal[g_nVChannel[vChanel.at(i)]*3+CHANNEL_MAX+1] = nDfDt;
//		if(vChanel.at(i)<pAcPara->analogvoltchangelvalue_size())
//		{
//			pAcPara->mutable_analogvoltchangelvalue(vChanel.at(i))->set_ffre(fBeginFre);
//		}
//	}
//	stChange.nDWCount = 6+18;

//	oState.nChangemSec = 1/*nTimegap*/;



//	for(int i=0;i<ChannelVolts.size();i++)
//	{
//		int drv_chan=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(ChannelVolts.at(i),VOLT,Fre);
//		oDrvState.stChange[0].nChangeValue[drv_chan]=nRmpValue;
//	}

//	for(int i=0;i<ChannelCurrs.size();i++)
//	{
//		int drv_chan=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(ChannelCurrs.at(i),CURRENT,Fre);
//		oDrvState.stChange[1].nChangeValue[drv_chan]=nRmpValue;
//	}
//}

//void setComGradient_analog(tmt_StatePara oTmt_paraState,Drv_StateItem &oDrv_StateItem,QVector<int> vChanel,QVector<int> iChanel)
//{
//	bool bDC = pState->bdc();
//	StatePara::GradientPara* pGadient =  pState->mutable_oanagradientpara();

//	ogradient.bcomgradient = true;
//	oState.nChangemSec = pGadient->fsteptime()*1000;
//	float fBegin = pGadient->fstart();
//	float fEnd = pGadient->fend();
//	float fStep  = pGadient->fstep();

//	stChange.nIsChange = 1;
//	if(fabs(fStep)<0.0001)
//		return;

//	stChange.nAmpCount = fabs(fEnd - fBegin)/fabs(fStep);
//	float fRemainder = (fEnd - fBegin)/fStep;
//	bool bEnd = true;
//	if(fabs(fRemainder - (int)fRemainder ) < 0.0000001)
//		bEnd = false;
//	else
//		stChange.nAmpCount+=1; //有余数，需要有额外的一步去递变到终止值
//	ogradient.fstep = fStep;
//	ogradient.fVBegin = fBegin;
//	ogradient.fVend = fEnd;
//	QVector<int> vChanel;
//	int nVoltorCur=0;
//	FpgaDirectOper::g_FpgsDirectOper->getCurrentVChanelAndType(pGadient->ivar(),vChanel,nVoltorCur);
//	ogradient.vChangel= vChanel;
//	long nDiDt =0;
//	stChange.nDWCount = 6+18;
//	if(nVoltorCur == 0)
//	{
//		ogradient.bvolt = false;
//		for(int i=0;i<vChanel.size();i++)
//		{
//			if(bDC)
//			{
//				Device::g_Device->TranslateIValueToLongDC(fStep,nDiDt,vChanel.at(i));
//				if(fEnd< fBegin)
//				{
//					nDiDt = -nDiDt;
//				}
//				stChange.changeVal[g_nIChannel[vChanel.at(i)]] = nDiDt;
//			}
//			else
//			{
//				nDiDt  = Device::g_Device->TranslateACCurrentAmp(fStep,vChanel.at(i));
//				if(fEnd< fBegin)
//				{
//					nDiDt = -nDiDt;
//				}
//				stChange.changeVal[g_nIChannel[vChanel.at(i)]*3+CHANNEL_MAX+2] = nDiDt;
//			}


//			if(vChanel.at(i)<pAcPara->analogcurrentchanelvalue_size())
//			{
//				pAcPara->mutable_analogcurrentchanelvalue(vChanel.at(i))->set_famptitude(fBegin);
//			}

//		}
//		float fdiff;
//		if(fEnd>fBegin)
//			fdiff = fEnd-fBegin;
//		else
//			fdiff = fBegin- fEnd;
//		float fTemp = fdiff-fStep*(stChange.nAmpCount-1);
//		qDebug()<<"the sdfsdfsdfsdfsdfsf"<<fTemp;
//		for(int i=0;i<vChanel.size();i++)
//		{
//			if(bDC)
//			{
//				Device::g_Device->TranslateIValueToLongDC(fTemp,nDiDt,vChanel.at(i));
//				if(fEnd< fBegin)
//				{
//					nDiDt = -nDiDt;
//				}
//				stChange.lastVal[g_nIChannel[vChanel.at(i)]] = nDiDt;
//			}
//			else
//			{
//				nDiDt  = Device::g_Device->TranslateACCurrentAmp(fTemp,vChanel.at(i));
//				if(fEnd< fBegin)
//				{
//					nDiDt = -nDiDt;
//				}
//				stChange.lastVal[g_nIChannel[vChanel.at(i)]*3+CHANNEL_MAX+2] = nDiDt;
//			}
//		}
//	}
//	else
//	{
//		ogradient.bvolt = true;
//		long nDvDt = 0;
//		for(int i=0;i<vChanel.size();i++)
//		{
//			if(bDC)
//			{
//				Device::g_Device->TranslateUValueToLongDC(fStep,nDvDt,vChanel.at(i));
//				if(fEnd< fBegin)
//				{
//					nDvDt = -nDvDt;
//				}
//				stChange.changeVal[g_nVChannel[vChanel.at(i)]] = nDvDt;
//			}
//			else
//			{
//				nDvDt  = Device::g_Device->TranslateACVoltAmp(fStep,vChanel.at(i));
//				if(fEnd< fBegin)
//				{
//					nDvDt = -nDvDt;
//				}
//				stChange.changeVal[g_nVChannel[vChanel.at(i)]*3+CHANNEL_MAX+2] = nDvDt;
//			}

//			pAcPara->mutable_analogvoltchangelvalue(vChanel.at(i))->set_famptitude(fBegin);
//		}
//		float fdiff;
//		if(fEnd>fBegin)
//			fdiff = fEnd-fBegin;
//		else
//			fdiff = fBegin- fEnd;
//		float fTemp = fdiff-fStep*(stChange.nAmpCount-1);
//		qDebug()<<"the sdfsdfsdfsdfsdfsf"<<fTemp;
//		for(int i=0;i<vChanel.size();i++)
//		{
//			if(bDC)
//			{
//				Device::g_Device->TranslateUValueToLongDC(fTemp,nDvDt,vChanel.at(i));
//				if(fEnd< fBegin)
//				{
//					nDvDt = -nDvDt;
//				}
//				stChange.lastVal[g_nVChannel[vChanel.at(i)]] = nDvDt;
//			}
//			else
//			{
//				nDvDt  = Device::g_Device->TranslateACVoltAmp(fTemp,vChanel.at(i));
//				if(fEnd< fBegin)
//				{
//					nDvDt = -nDvDt;
//				}
//				stChange.lastVal[g_nVChannel[vChanel.at(i)]*3+CHANNEL_MAX+2] = nDvDt;
//			}
//		}
//	}
//	if(nVoltorCur == 0)
//	{
//		oState.oStChange[1] = stChange;
//	}
//	else
//	{
//		oState.oStChange[0] = stChange;
//	}
//}

void tmt_to_drv_StateItem(tmt_StateTest *pTmt,Drv_StateItem *pDrv_StateItem, char *pBuf,int &nBufLen)
{
	int nDrvSize=sizeof(Drv_StateItem);
	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;

	int nArrayBeginIndex=0;
	float fAmp=0;

	for(int nStateIndex=0;nStateIndex<pTmt->m_oStateParas.m_nStateNumbers;nStateIndex++)
	{
		tmt_StatePara  oTmt_paraState=pTmt->m_oStateParas.m_paraState[nStateIndex];
		memset(pDrv_StateItem,0,nDrvSize);

		for (int i=0; i<8; i++)//bo
		{
			pDrv_StateItem->oStBo.boStatus.item[0].nVal1 += ((!oTmt_paraState.m_binOut[i].nState)<<i);
		}

#ifdef _USE_EXT_SWITCH_
		//		oDrv_StateItem.oStBo.boStatus.item[0].nVal1 = pState->nbovalide();
		//		oDrv_StateItem.oStBo.boStatus.item[1].nVal1 = 0;
		//		oDrv_StateItem.oStBo.boStatus.item[1].nVal2 = pState->nexbovalide1();
		//		oDrv_StateItem.oStBo.boStatus.item[2].nVal1 = 0;
		//		oDrv_StateItem.oStBo.boStatus.item[2].nVal2 = pState->nexbovalide2();
#endif

		//oDrv_StateItem.oStBo.nHoldDelay = oTmt_paraState.m_binOut[0].fHoldTime*1000;

		BOOL bHasAnalog=TRUE;
		BOOL bHasDigital=TRUE;

		if(bHasAnalog)
		{
			CSttDeviceBase::g_pSttDeviceBase->InitDAVolt();
			//VOLT
			for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U;nIndex++)
			{
				if(g_theDeviceSystemParameter->m_oModules_U[nIndex]==NULL)
					continue;

				tmt_to_drv_analog_volt(pDrv_StateItem,oTmt_paraState,nIndex);

				nArrayBeginIndex=g_theDeviceSystemParameter->m_oModules_U[nIndex]->m_nArrayBeginIndex;
				for(int k=0;k<CHANNEL_MAX;k++)
				{
					fAmp=fabs(oTmt_paraState.m_uiVOL[k+nArrayBeginIndex].Harm[1].fAmp);
					if(fVsum<fAmp)
						fVsum=fAmp;
				}

				if(oTmt_paraState.m_bDC)
					fVsum/=1.414;

				CSttDeviceBase::g_pSttDeviceBase->setDApara(fVsum,nIndex,STT_MODULE_TYPE_VOLT);
			}

			//CURRENT
			for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I;nIndex++)
			{
				if(g_theDeviceSystemParameter->m_oModules_I[nIndex]==NULL)
					continue;

				tmt_to_drv_analog_current(pDrv_StateItem,oTmt_paraState,nIndex);

				nArrayBeginIndex=g_theDeviceSystemParameter->m_oModules_I[nIndex]->m_nArrayBeginIndex;
				for(int k=0;k<CHANNEL_MAX;k++)
				{
					fAmp=fabs(oTmt_paraState.m_uiCUR[k+nArrayBeginIndex].Harm[1].fAmp);
					fIsum+=fAmp;
					if(fIMax<fAmp)
						fIMax=fAmp;
				}

				if(oTmt_paraState.m_bDC)
				{
					CSttDeviceBase::g_pSttDeviceBase->setCurrentDCDApara(fIsum,nIndex);
				}
				else
				{
					CSttDeviceBase::g_pSttDeviceBase->setDApara(fIsum,nIndex,STT_MODULE_TYPE_CURRENT,fIMax);
				}
			}

			CSttDeviceBase::g_pSttDeviceBase->setDApara_to_drv();
		}

#ifdef _USE_IEC61850_
		if(bHasDigital)
		{

		}
#endif

		if(oTmt_paraState.m_nRampType!=STATE_RAMP_TYPE_NULL)
		{
//			CSttDevice::GetTMTChannels(oTmt_paraState.m_sttGradient.iVar,ChannelVolts,ChannelCurrs);

			switch (oTmt_paraState.m_nRampType)
			{
			case STATE_RAMP_TYPE_SLIP_VAL:
			{
				//setDvDt_analog(oTmt_paraState,oDrv_StateItem);
			}
				break;
			case STATE_RAMP_TYPE_SLIP_FRE:
			{
				if(oTmt_paraState.m_bDC)
					break;

				//setDFDt_analog(oTmt_paraState,oDrv_StateItem);
			}
				break;
			case STATE_RAMP_TYPE_NORMAL:
			{
				//setComGradient_analog(oTmt_paraState,oDrv_StateItem);
			}
				break;
			}
		}


		setTriger(oTmt_paraState,pDrv_StateItem,nStateIndex);

#ifdef _USE_IEC61850_
		setGSChangeItem(state,pState);
#endif

		qDebug()<<"the state"<<pDrv_StateItem->nTirpType;
		memcpy(pBuf+nDrvSize*nStateIndex,pDrv_StateItem,nDrvSize);
		nBufLen+=nDrvSize;
	}
}

