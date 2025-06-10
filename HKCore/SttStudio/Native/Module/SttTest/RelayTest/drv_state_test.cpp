#include "stdafx.h"
#include "drv_state_test.h"
#include"math.h"
#include"../../SttDevice/RelayTest/SttDevice.h"
#include "../../SttDevice/SttDeviceBase.h"
#include "Iec61850Config.h"
#include "IEC61850CfgMngr.h"

QVector<int> ChannelVolts,ChannelCurrs;

void tmt_to_drv_analog(tmt_StatePara &oTmtState,drv_acanalogpara &acAnalog)
{
	acAnalog.oModuledata[0].nModule = VOL_CHANNEL_MARK;
	acAnalog.oModuledata[1].nModule = CUR_CHANNEL_MARK;

	for (int i=0; i<CHANNEL_MAX; i++)
	{
		if(oTmtState.m_bDC)
		{
			CSttDeviceBase::g_pSttDeviceBase->TransAnalogDCVolToDrv(oTmtState.m_uiVOL[i].Harm[1].fAmp,i ,acAnalog.oModuledata[0].nData);
			CSttDeviceBase::g_pSttDeviceBase->TransAnalogDCCurToDrv(oTmtState.m_uiCUR[i].Harm[1].fAmp, i ,acAnalog.oModuledata[1].nData);
		}
		else
		{
			CSttDeviceBase::g_pSttDeviceBase->TransAnalogVolToDrv(oTmtState.m_uiVOL[i].Harm[1].fAmp,
					oTmtState.m_uiVOL[i].Harm[1].fAngle,
					oTmtState.m_uiVOL[i].Harm[1].fFreq, i ,
					acAnalog.oModuledata[0].nData);

			CSttDeviceBase::g_pSttDeviceBase->TransAnalogCurToDrv(oTmtState.m_uiCUR[i].Harm[1].fAmp,
					oTmtState.m_uiCUR[i].Harm[1].fAngle,
					oTmtState.m_uiCUR[i].Harm[1].fFreq, i ,
					acAnalog.oModuledata[1].nData);
		}
	}
}

void tmt_to_drv_digital(tmt_StatePara &oTmtState,drv_sindataitem &oSinDataItem)
{
	oSinDataItem.module = DIGITAL_CHANNEL_MARK;

	int nChannelA_drv_Index_Volt,nChannelA_drv_Index_Curr;
	for(int i=0; i<MAX_DIGITAL_GROUP_NUM; i++)
	{
		if(oTmtState.m_bDC)
		{
			oTmtState.m_uiVOL[i*3+CHANNEL_A].Harm[1].fFreq = 0;
			oTmtState.m_uiVOL[i*3+CHANNEL_B].Harm[1].fFreq = 0;
			oTmtState.m_uiVOL[i*3+CHANNEL_C].Harm[1].fFreq = 0;
			oTmtState.m_uiCUR[i*3+CHANNEL_A].Harm[1].fFreq = 0;
			oTmtState.m_uiCUR[i*3+CHANNEL_B].Harm[1].fFreq = 0;
			oTmtState.m_uiCUR[i*3+CHANNEL_C].Harm[1].fFreq = 0;
		}

		//bool ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(i,nChannelA_drv_Index_Volt,VOLT);
		//ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(i,nChannelA_drv_Index_Curr,CURRENT);

		nChannelA_drv_Index_Volt=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(i,VOLT,Ang);
		nChannelA_drv_Index_Curr=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(i,CURRENT,Ang);
		for(int channel=0;channel<3;channel++)//A B C
		{
			CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolToDrv(oTmtState.m_uiVOL[i*3+channel].Harm[1].fAmp,
					oTmtState.m_uiVOL[i*3+channel].Harm[1].fAngle,
					oTmtState.m_uiVOL[i*3+channel].Harm[1].fFreq, i ,
					&oSinDataItem.dat[nChannelA_drv_Index_Volt+channel*3]);

			CSttDeviceBase::g_pSttDeviceBase->TransDigitalCurToDrv(oTmtState.m_uiCUR[i*3+channel].Harm[1].fAmp,
					oTmtState.m_uiCUR[i*3+channel].Harm[1].fAngle,
					oTmtState.m_uiCUR[i*3+channel].Harm[1].fFreq, i ,
					&oSinDataItem.dat[nChannelA_drv_Index_Curr+channel*3]);
		}
	}
}

void tmt_to_drv_rmp_channel_analog(tmt_StatePara &oTmtState ,QVector<int> uChannelNum,drv_state &oDrvState,int nType)
{	
	float fChangeValue = oTmtState.m_sttGradient.fEnd - oTmtState.m_sttGradient.fStart;
	float fStep = fabs(oTmtState.m_sttGradient.fStep);
	unsigned int uChangeCount = fabs(fChangeValue/fStep);

	if(oTmtState.m_sttGradient.fEnd < oTmtState.m_sttGradient.fStart)
	{
		fStep = -fStep;
	}

	int Drvchannel=0;

	for(int i=0;i<uChannelNum.size();i++)
	{
		int channel=uChannelNum.at(i);
		int nTemp = channel/CHANNEL_MAX;
		oDrvState.stChange[nTemp].nIsChange=1;
		if(!(fabs(fChangeValue/fStep)-uChangeCount < 0.0000001))//两者不等，则增加一次递变次数
			uChangeCount++;
		oDrvState.stChange[nTemp].nChangeCount=uChangeCount;

		float fTemp = fChangeValue-fStep*(uChangeCount-1);

		switch(nType)
		{
		case VOLT:
		{
			oDrvState.stChange[nTemp].nModule=CSttDevice::g_pSttDevice->getModuleNum(VOLT,nTemp);

			//Drvchannel=CSttDevice::g_pSttDevice->GetChannelIndex_Drv_Amp(channel,VOLT);
			Drvchannel=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(channel,VOLT,Amp);
			oDrvState.stChange[nTemp].nChangeValue[Drvchannel] = CSttDeviceBase::g_pSttDeviceBase->TranslateACVoltAmp(fStep,channel);

			int nDvDt  = CSttDeviceBase::g_pSttDeviceBase->TranslateACVoltAmp(fTemp,channel);
			oDrvState.stChange[nTemp].nLastChangeValue[Drvchannel] = nDvDt;
		}
			break;
		case CURRENT:
		{
			oDrvState.stChange[nTemp].nModule=CSttDevice::g_pSttDevice->getModuleNum(CURRENT,nTemp);

			//Drvchannel=CSttDevice::g_pSttDevice->GetChannelIndex_Drv_Amp(channel,CURRENT);
			Drvchannel=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(channel,CURRENT,Amp);
			oDrvState.stChange[nTemp].nChangeValue[Drvchannel] = CSttDeviceBase::g_pSttDeviceBase->TranslateACCurrentAmp(fStep,channel);
		}
			break;
		}
	}
}

void tmt_to_drv_rmp_channel_digital(tmt_StatePara &oTmtState ,QVector<int> uChannelNum,drv_digitalchange &oDrvChange,int nType)
{
	if(uChannelNum.count()==0)
		return;

	float fChangeValue = oTmtState.m_sttGradient.fEnd - oTmtState.m_sttGradient.fStart;
	float fStep = oTmtState.m_sttGradient.fStep;
	float uChangeCount = fabs(fChangeValue)/fStep;
	oDrvChange.nChangeCount = uChangeCount;

	if(!((uChangeCount - (int)uChangeCount ) < 0.0000001))
		oDrvChange.nChangeCount+=1; //有余数，需要有额外的一步去递变到终止值

	if(oTmtState.m_sttGradient.fEnd < oTmtState.m_sttGradient.fStart)
	{
		fStep = -fStep;
	}

	float fTemp = fChangeValue-fStep*(oDrvChange.nChangeCount-1);

	for(int i=0;i<uChannelNum.count();i++)
	{
		int chanid=uChannelNum.at(i);
		long nGroupIndex = chanid/3;
		int channel_Type=chanid%3;//A B C
		int DrvChannel=0;
		switch(nType)
		{
		case VOLT:
		{
			//CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(nGroupIndex,DrvChannel,VOLT);
			DrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(nGroupIndex,VOLT,Amp);
			oDrvChange.nChangeValue[3*channel_Type+DrvChannel] = CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolAmp(fStep,nGroupIndex,false);
			oDrvChange.nLastChangeValue[3*channel_Type+DrvChannel] = CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolAmp(fTemp,nGroupIndex,false);
			oTmtState.m_uiVOL[chanid].Harm[1].fAmp=oTmtState.m_sttGradient.fStart;
		}
			break;
		case CURRENT:
		{
			//CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(nGroupIndex,DrvChannel,CURRENT);
			DrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(nGroupIndex,CURRENT,Amp);
			oDrvChange.nChangeValue[3*channel_Type+DrvChannel] = CSttDeviceBase::g_pSttDeviceBase->TransDigitalCurAmp(fStep,nGroupIndex,false);
			oDrvChange.nLastChangeValue[3*channel_Type+DrvChannel] = CSttDeviceBase::g_pSttDeviceBase->TransDigitalCurAmp(fTemp,nGroupIndex,false);
			oTmtState.m_uiCUR[chanid].Harm[1].fAmp=oTmtState.m_sttGradient.fStart;
		}
			break;
		}
	}
}

void setDvDt(tmt_StatePara &pState,drv_state &oState,QVector<int> vChanel)
{
	float fBeginV,fEndV;
	float fDvdt;

	bool bDC =pState.m_bDC;
	tmt_StateGradient *pGadient =&pState.m_sttGradient;

	fBeginV = pGadient->fStart;
	fEndV = pGadient->fEnd;
	fDvdt = pGadient->fdvdt;

	if(fabs(fDvdt)<0.00001)
	{
		return;
	}

	oState.stChange[0].nIsChange = 1;
	oState.stChange[0].nModule = CSttDevice::g_pSttDevice->getModuleNum(VOLT,0); //zhangsen 20180822
	long nDvDt = 0;
	if(vChanel.size()>0)
	{
		if(bDC)
		{
			//CSttDevice::g_pSttDevice->TranslateUValueToLongDC(fDvdt/1000,nDvDt,vChanel.at(0));
			CSttDevice::g_pSttDevice->TransAnalogDCCurToDrv(fDvdt/1000,vChanel.at(0),&nDvDt);
		}
		else
		{
			nDvDt  = CSttDeviceBase::g_pSttDeviceBase->TranslateACVoltAmp(fDvdt/1000,vChanel.at(0));
		}
	}
	double fdvdtRU = CSttDevice::g_pSttDevice->getAnalogVoltMax(vChanel.at(0))/65536.0/65536.0;
	long nTimegap = 1;
	int nCount;
	if(nDvDt==0)
	{
		nDvDt = 1;
		nTimegap = fdvdtRU*1000.0/fDvdt;
		nCount =  fabs(fEndV - fBeginV)/(nDvDt*fdvdtRU);
	}
	else
	{
		nTimegap = 1;
		nCount = fabs(fEndV - fBeginV)*1000.0/fDvdt+1;
	}

	oState.stChange[0].nChangeCount = nCount;
	if(fEndV<fBeginV)
	{
		nDvDt = -nDvDt;
	}

	int Drvchannel=0;
	for(int i=0;i<vChanel.size();i++)
	{
		if(bDC)
		{
			Drvchannel=CSttDevice::g_pSttDevice->GetVoltChannelMap(vChanel.at(i));
			oState.stChange[0].nChangeValue[Drvchannel] = nDvDt;
		}
		else
		{
			//Drvchannel=CSttDevice::g_pSttDevice->GetChannelIndex_Drv_Amp(vChanel.at(i),VOLT);
			Drvchannel=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(vChanel.at(i),VOLT,Amp);
			oState.stChange[0].nChangeValue[Drvchannel] = nDvDt;
		}
	}
	oState.nChangemSec = nTimegap;
}

BOOL tmt_to_drv_rmp_analog(tmt_StatePara &oTmtState,drv_state &oDrvState)
{
	switch (oTmtState.m_nRampType)
	{
	case STATE_RAMP_TYPE_SLIP_VAL:
	{
		setDvDt(oTmtState,oDrvState,ChannelVolts);
	}
		break;
	case STATE_RAMP_TYPE_SLIP_FRE:
	{
		oDrvState.stChange[0].nIsChange = 1;
		oDrvState.stChange[1].nIsChange = 1;

		oDrvState.stChange[0].nModule = VOL_CHANNEL_MARK;//按位设置
		oDrvState.stChange[1].nModule = CUR_CHANNEL_MARK;//按位设置
		oDrvState.nChangemSec = 1;//递变时间分度设置为1
		oDrvState.stChange[0].ndfcount = fabs((oTmtState.m_sttGradient.fEnd - oTmtState.m_sttGradient.fStart)*1000*1.0737/oTmtState.m_sttGradient.fdfdt);
		oDrvState.stChange[1].ndfcount = oDrvState.stChange[0].ndfcount;
		long nRmpValue = 0;
		nRmpValue = CSttDeviceBase::g_pSttDeviceBase->TranslateACFre(oTmtState.m_sttGradient.fdfdt/1000);//1.073741824 = (2的30次方除以10的9次方)
		//            nRmpValue = fabs(oTmtState.m_sttGradient.fdfdt)*m_pDeviceParas->m_fFreCof_Std/(1000*1.073741824);//1.073741824 = (2的30次方除以10的9次方)

		if(oTmtState.m_sttGradient.fStart>oTmtState.m_sttGradient.fEnd)
			nRmpValue *= -1;

		for(int i=0;i<ChannelVolts.size();i++)
		{
			int drv_chan=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(ChannelVolts.at(i),VOLT,Fre);
			oDrvState.stChange[0].nChangeValue[drv_chan]=nRmpValue;
		}

		for(int i=0;i<ChannelCurrs.size();i++)
		{
			int drv_chan=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(ChannelCurrs.at(i),CURRENT,Fre);
			oDrvState.stChange[1].nChangeValue[drv_chan]=nRmpValue;
		}
	}
		break;
	case STATE_RAMP_TYPE_NORMAL:
	{
		oDrvState.nChangemSec = oTmtState.m_sttGradient.fStepTime*1000;//递变每步的时间
		tmt_to_drv_rmp_channel_analog(oTmtState,ChannelVolts,oDrvState,VOLT);
		tmt_to_drv_rmp_channel_analog(oTmtState,ChannelCurrs,oDrvState,CURRENT);
	}
		break;
	}

	return TRUE;
}

BOOL tmt_to_drv_rmp_digital(tmt_StatePara &oTmtState,drv_state &oDrvState)
{
	int nDrvChannel=0;
//	int channelvolt_group0=0,channelvolt_group1=0;
//	int channelcurr_group0=0,channelcurr_group1=0;
//	CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(0,channelvolt_group0,VOLT);
//	CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(1,channelvolt_group1,VOLT);
//	CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(0,channelcurr_group0,CURRENT);
//	CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(1,channelcurr_group1,CURRENT);

	oDrvState.stDigitalChange[0].nIsChange = 1;
	oDrvState.stDigitalChange[0].nModule = DIGITAL_CHANNEL_MARK;//按位设置
	oDrvState.nChangemSec = 1;//递变时间分度设置为1

	switch (oTmtState.m_nRampType)
	{
	case STATE_RAMP_TYPE_SLIP_VAL:
	{
		oDrvState.stDigitalChange[0].nChangeCount = fabs(oTmtState.m_sttGradient.fEnd - oTmtState.m_sttGradient.fStart)*1000.0f/oTmtState.m_sttGradient.fdvdt;
		float fRmpValue =0;
		fRmpValue =  (oTmtState.m_sttGradient.fdvdt)*0.001f;

		if(oTmtState.m_sttGradient.fStart>oTmtState.m_sttGradient.fEnd)
			fRmpValue *= -1;

		int nDrvValue=0;

		for(int i=0;i<ChannelVolts.size();i++)
		{
			int chan=ChannelVolts.at(i);
			int group=chan/3;
			int chan_type=chan%3;
			switch(group)
			{
			case 0:
				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(0,VOLT,Amp);
				nDrvValue=CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolAmp(fRmpValue,0,false);
				break;
			case 1:
				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(1,VOLT,Amp);
				nDrvValue=CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolAmp(fRmpValue,1,false);
				break;
			}
			oDrvState.stDigitalChange[0].nChangeValue[chan_type*3+nDrvChannel]=nDrvValue;
			oTmtState.m_uiVOL[chan].Harm[1].fAmp=oTmtState.m_sttGradient.fStart;
		}
	}
		break;
	case STATE_RAMP_TYPE_SLIP_FRE:
	{
		oDrvState.stDigitalChange[0].ndfcount = fabs(oTmtState.m_sttGradient.fEnd - oTmtState.m_sttGradient.fStart)*1000/oTmtState.m_sttGradient.fdfdt;
		long nRmpValue = 0;
		nRmpValue = CSttDeviceBase::g_pSttDeviceBase->TranslateDigitalFre(oTmtState.m_sttGradient.fdfdt/1000);//1.073741824 = (2的30次方除以10的9次方)
		//            nRmpValue = fabs(oTmtState.m_sttGradient.fdfdt)*m_pDeviceParas->m_fFreCof_Std/(1000*1.073741824);//1.073741824 = (2的30次方除以10的9次方)

		if(oTmtState.m_sttGradient.fStart>oTmtState.m_sttGradient.fEnd)
			nRmpValue *= -1;

		for(int i=0;i<ChannelVolts.size();i++)
		{
			int chan=ChannelVolts.at(i);
			int group=chan/3;
			int chan_type=chan%3;
			switch(group)
			{
			case 0:
				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(0,VOLT,Fre);
				break;
			case 1:
				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(1,VOLT,Fre);
				break;
			}
			oDrvState.stDigitalChange[0].nChangeValue[chan_type*3+nDrvChannel]=nRmpValue;
			oTmtState.m_uiVOL[chan].Harm[1].fFreq=oTmtState.m_sttGradient.fStart;
		}

		for(int i=0;i<ChannelCurrs.size();i++)
		{
			int chan=ChannelCurrs.at(i);
			int group=chan/3;
			int chan_type=chan%3;
			switch(group)
			{
			case 0:
				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(0,CURRENT,Fre);
				break;
			case 1:
				nDrvChannel=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(1,CURRENT,Fre);
				break;
			}
			oDrvState.stDigitalChange[0].nChangeValue[chan_type*3+nDrvChannel]=nRmpValue;
			oTmtState.m_uiCUR[chan].Harm[1].fFreq=oTmtState.m_sttGradient.fStart;
		}
	}
		break;
	case STATE_RAMP_TYPE_NORMAL:
	{
		oDrvState.nChangemSec = oTmtState.m_sttGradient.fStepTime*1000;//递变每步的时间
		tmt_to_drv_rmp_channel_digital(oTmtState,ChannelVolts,oDrvState.stDigitalChange[0],VOLT);
		tmt_to_drv_rmp_channel_digital(oTmtState,ChannelCurrs,oDrvState.stDigitalChange[0],CURRENT);
	}
		break;
	}

	return TRUE;
}

void tmt_to_drv(tmt_StateParas &oStateParas,int nIndex,drv_state &oDrvState)
{
	memset(&oDrvState,0,sizeof(drv_state));
	tmt_StatePara oTmtState=oStateParas.m_paraState[nIndex];
	oDrvState.nReversal = oTmtState.m_eBinReversal;

	unsigned int nLogicValid = 0;

	for (int i=0; i<8; i++)
	{
		nLogicValid |= ((oTmtState.m_binIn[i].nSelect?1:0)<<i);
	}

	if(oTmtState.m_nBinLogic)//And
	{
		oDrvState.nAndValid = nLogicValid;
		oDrvState.nOrValid = 0;
	}
	else//Or
	{
		oDrvState.nAndValid  = 0;
		oDrvState.nOrValid = nLogicValid;
	}

	//oDrvState.gpsSec = oTmtState.m_tGps.Year + oTmtState.m_tGps;
	oDrvState.nGpsnSec = oTmtState.m_tGps.nMilliSeconds*1000000;//纳秒值转换
	oDrvState.nTimemSec = oTmtState.m_fTimeState*1000;
	oDrvState.nDelay = oTmtState.m_fTimeAfterTrigger*1000;
	oDrvState.nDelay = oTmtState.m_fTimeAfterTrigger*1000;

	oDrvState.oBo.nBoValue = 0;

	//设置递变
	if(oTmtState.m_nRampType != STATE_RAMP_TYPE_NULL)
	{
		CSttDevice::GetTMTChannels(oTmtState.m_sttGradient.iVar,ChannelVolts,ChannelCurrs);
		tmt_to_drv_rmp_analog(oTmtState,oDrvState);
		tmt_to_drv_rmp_digital(oTmtState,oDrvState);
	}

	//设置模拟量值
	tmt_to_drv_analog(oTmtState,oDrvState.acAnalog);
	//设置数字量值
	tmt_to_drv_digital(oTmtState,oDrvState.Digital.oModuledata[0]);

	//设置开出量

	for (long i = 0;i<10;i++)
	{
		oDrvState.oBo.nBoValue += ((!oTmtState.m_binOut[i].nState)*(1<<i));

		if (oTmtState.m_binOut[i].nMode)
		{
			oDrvState.oBo.ntrigerMode = 1;
		}

		if (oTmtState.m_binOut[i].fTimeTrig>0)
		{
			oDrvState.oBo.ntimeDelay = oTmtState.m_binOut[i].fTimeTrig*1000;
		}

		if (oTmtState.m_binOut[i].fHoldTime>0)
		{
			oDrvState.oBo.nHoldTime = oTmtState.m_binOut[i].fHoldTime*1000;
		}
	}

	//设置触发条件
	switch(oTmtState.m_nTriggerCondition)
	{
	case TMT_MDSTATE_TIMETRIGGER:
		oDrvState.nTirpType[1] = oDrvState.nStateNum+1;
		break;
	case TMT_MDSTATE_TIMEBINTRIGGER:
	{
		oDrvState.nTirpType[1] = oDrvState.nStateNum+1;

		if (oTmtState.m_nBinLogic)
		{
			oDrvState.nTirpType[3] = oDrvState.nStateNum+1;
		}
		else
		{
			oDrvState.nTirpType[4] = oDrvState.nStateNum+1;
		}
	}
		break;
	case TMT_MDSTATE_BINTRIGGER:
	{
		if (oTmtState.m_nBinLogic)
		{
			oDrvState.nTirpType[3] = oDrvState.nStateNum+1;
		}
		else
		{
			oDrvState.nTirpType[4] = oDrvState.nStateNum+1;
		}
	}
		break;
	case TMT_MDSTATE_MEARSURETRIGGER:
		oDrvState.nTirpType[0] = oDrvState.nStateNum+1;
		break;
	case TMT_MDSTATE_GPSBTRIGGER:
		oDrvState.nTirpType[2] = oDrvState.nStateNum+1;
		break;
	}

	//goosechange
	if(nIndex>0)
		CIEC61850CfgMngr::g_pIEC61850CfgMngr->SetGooseValue(oStateParas,nIndex,&oDrvState);
}

void tmt_to_drv(tmt_StateTest *pTmt ,drv_state_test *pDrv)
{
	pDrv->nModuleCount = 2;//模拟模块总数
	pDrv->nStateModuleCount = 1;//数字模块总数
	pDrv->nDcmodule=0;//直流模块总数
	pDrv->nStateCount  = pTmt->m_oStateParas.m_nStateNumbers;//状态数
	pDrv->nSequence = pTmt->m_oStateParas.m_bSequence;//是否位顺序状态序列
	pDrv->nloop = pTmt->m_oStateParas.m_bRepeat;//是否循环
	pDrv->nReverRefence = pTmt->m_oStateParas.m_nBinTripRef;//0：开入量以第一态为参考
	//1：以上一态为参考
	pDrv->noriginal = 0;//goose开入初始值
	for (int nIndex = 0;nIndex<pTmt->m_oStateParas.m_nStateNumbers;nIndex++)
	{
		pDrv->stState[nIndex].nStateNum = nIndex;
		tmt_to_drv(pTmt->m_oStateParas,nIndex,pDrv->stState[nIndex]);
	}
}


