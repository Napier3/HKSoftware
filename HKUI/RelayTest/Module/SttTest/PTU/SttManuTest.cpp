#include "stdafx.h"
#include"SttManuTest.h"
#include "../../SttDevice/SttDeviceBase.h"
#include "../../SttDevice/PTU/SttDriverOper.h"
#include "../../SttDevice/PTU/SttDevice.h"
#include "QDebug"
#include "../../Engine/SttTestServerBase.h"

CString CSttManuTest::m_strMacroName = "电压电流试验";
CString CSttManuTest::m_strMacroID = ("SttManuTest");
CString CSttManuTest::m_strFilePostFix = "sttuit";
//#include<QtDebug>

CSttManuTest::CSttManuTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	Init();
}

void CSttManuTest::Init()
{
	m_vchannel[0] = 3;
	m_vchannel[1] = 2;
	m_vchannel[2] = 0;
	m_vchannel[3] = 1;

	m_ichannel[0] = 5;
	m_ichannel[1] = 4;
	m_ichannel[2] = 7;
	m_ichannel[3] = 6;

	m_nOverload = 0;
	tmt_ManualTest::init();
	CSttTestBase::Init();
	//	m_uStartTimeS = 0;
	//	m_uStartTimeNS = 0;
	//	memset(m_oDrvResults,0,sizeof(structRampResult)*100);
	m_Start=false;
}

long CSttManuTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return true;
}

CSttManuTest::~CSttManuTest(void)
{
}


double CSttManuTest::GetTestTimeLong()
{
	float fTime;

	//	fTime = m_oManuParas.m_fOutPutTime;
	//	fTime += TIME_ONLINE_DELAY;

	return fTime;
}

long CSttManuTest::CalReport(UINT nState)
{

	return 0;
}

long CSttManuTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttManuTest::StartTest()
{
	if(!m_Start)
	{
		m_Start=true;
		//		start();
		CSttTestBase::StartTest();
		CSttDriverOper::Start(1);
	}
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttManuTest::DataDownload Finished");
}


void CSttManuTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oManuParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		//m_bPause=true;
		AfterSetParameter();
		//m_bPause=false;
	}

}

void CSttManuTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(m_binOut,pXmlSerialize);
}

void CSttManuTest::UpdateParameter()
{

}

/***
void CSttManuTest::calcMeasTap()
{	
	m_channelTemp=m_manual;
	for(int i=0;i<4;i++)
	{
		if(m_manual.vChannel[i].famptitude <=20)
			m_nVtap[i] = 0xf;
		else if(m_manual.vChannel[i].famptitude>20 && m_manual.vChannel[i].famptitude <=57.7)
			m_nVtap[i] = 0x7;
		else if(m_manual.vChannel[i].famptitude>57.7 && m_manual.vChannel[i].famptitude <=100)
			m_nVtap[i] = 0xb;
		else if(m_manual.vChannel[i].famptitude>100 && m_manual.vChannel[i].famptitude <=220)
			m_nVtap[i] = 0xd;
		else if(m_manual.vChannel[i].famptitude>220)
			m_nVtap[i] = 0xe;
	}
	for(int i=0;i<4;i++)
	{
		if(m_manual.iChannel[i].famptitude <=0.2)
			m_nITap[i] = 0xf;
		else if(m_manual.iChannel[i].famptitude>0.2 && m_manual.iChannel[i].famptitude <=0.5)
			m_nITap[i] = 0x7;
		else if(m_manual.iChannel[i].famptitude>0.5 && m_manual.iChannel[i].famptitude <=1)
			m_nITap[i] = 0xb;
		else if(m_manual.iChannel[i].famptitude>1 && m_manual.iChannel[i].famptitude <=5)
			m_nITap[i] = 0xe;
		else if(m_manual.iChannel[i].famptitude>5)
			m_nITap[i] = 0xc;
	}
	int nType[2] = {0,0};
	nType[0] |= m_nITap[0]<<20;
	nType[0] |= m_nITap[1]<<16;
	nType[0] |= m_nITap[2]<<28;
	nType[0] |= m_nITap[3]<<24;
	nType[0] |= m_nVtap[0]<<12;
	nType[0] |= m_nVtap[1]<<8;
	nType[0] |= m_nVtap[2]<<0;
	nType[0] |= m_nVtap[3]<<4;

	structACinSet pSet;
	pSet.acInMode = 0;
	pSet.acInStall1 = nType[0];
	pSet.acInStall2 = nType[1];

	CSttDriverOper::setAnalogMeas((char*)&pSet,sizeof(structACinSet));
}
***/

void CSttManuTest::setTap()
{	
	int nTap = 0;
	int nUtap = 0;

	for(int i=0;i<4;i++)
	{
		if(m_oManuParas.m_uiVOL[i].Harm[1].fAmp > 300)
			nUtap |= 1<<i;
	}
	int nItap = 128;
//	if(d_Data->sendzeroafterstop())  大电流模式
//    {
//       nItap = 0;
//    }

	int nDCTap=0;

	long nTemp = m_oManuParas.m_fVolAux*1000000;
	if(nTemp<=120000)
	{
		nDCTap =1<<4;
	}
	else if(nTemp<=1200000 && nTemp>120000)
	{
		nDCTap=1<<5;
	}
	else if(nTemp<=12000000 && nTemp>1200000)
	{

	}
	else if(nTemp>12000000)
	{
		nDCTap=1<<6;
	}


	int nCDCTap =0;
	float fCurrent = m_oManuParas.m_fCurAux;
	if(fCurrent<1.2)
	{
		nCDCTap = 1<<8;
	}
	nTap |= nCDCTap;

	nTap |= nUtap;
	nTap |= nItap;
	nTap |= nDCTap;

	CSttDriverOper::setOutPutTap(nTap);
}

void CSttManuTest::AfterSetParameter()
{	
	memset(&m_oDrvManuPara,0,sizeof(Drv_ManuPara));
	m_oDrvManuPara.moduleCount = 2;
	Drv_ManuAnalogPara Voltanal,Curanal;
	memset(&Voltanal,0,sizeof(Drv_ManuAnalogPara));
	Voltanal.module = 0;
	memset(&Curanal,0,sizeof(Drv_ManuAnalogPara));
	Curanal.module = 1;

	float fre=m_oManuParas.m_uiVOL[0].Harm[1].fFreq;

	for(int i=0;i<4;i++)
	{
		if(m_oManuParas.m_uiVOL[i].Harm[1].fAmp>300)
			m_oManuParas.m_uiVOL[i].Harm[1].fAmp=300;

		if(m_oManuParas.m_uiCUR[i].Harm[1].fAmp>20)
			m_oManuParas.m_uiCUR[i].Harm[1].fAmp=20;

		CSttDevice::g_pSttDevice->TranslateACVoltBuffer(m_oManuParas.m_uiVOL[i].Harm[1].fAmp
				,m_oManuParas.m_uiVOL[i].Harm[1].fAngle,m_oManuParas.m_uiVOL[i].Harm[1].fFreq,
				i,Voltanal.dat+6);

		CSttDevice::g_pSttDevice->TranslateACCurrentBuffer(m_oManuParas.m_uiCUR[i].Harm[1].fAmp
				,m_oManuParas.m_uiCUR[i].Harm[1].fAngle,m_oManuParas.m_uiCUR[i].Harm[1].fFreq,
				i,Curanal.dat+6);

		//CSttDevice::g_pSttDevice->TranslateACVoltBufferDC(m_oManuParas.m_uiVOL[i].Harm[1].fAmp,i,Voltanal.nDc);
		//CSttDevice::g_pSttDevice->TranslateACCurrentBufferDC(m_oManuParas.m_uiCUR[i].Harm[1].fAmp,i,Curanal.nDc);
		CSttDevice::g_pSttDevice->TranslateACVoltBufferDC(m_oManuParas.m_uiVOL[i].Harm[1].fAmp,i,Voltanal.dat);
		CSttDevice::g_pSttDevice->TranslateACCurrentBufferDC(m_oManuParas.m_uiCUR[i].Harm[1].fAmp,i,Curanal.dat);

		fre=qMin(fre,m_oManuParas.m_uiVOL[i].Harm[1].fFreq);
		fre=qMin(fre,m_oManuParas.m_uiCUR[i].Harm[1].fFreq);
	}

	//CSttDevice::g_pSttDevice->TranslateDCCurrent(m_oManuParas.m_fCurAux,Voltanal.nDc);
	CSttDevice::g_pSttDevice->TranslateDCCurrent(m_oManuParas.m_fCurAux,Voltanal.dat);
	CSttDevice::g_pSttDevice->TRanslateDcVolt(m_oManuParas.m_fVolAux);

	if(fre==0)
		fre=50;

	m_oDrvManuPara.sample = 40000/fre;

	CSttDriverOper::setMeasTap(4);
	CSttDriverOper::setDelayOverload(m_oManuParas.m_fOverloadDelaytime*10000000*5);
	int nBo=0;
	for (int i=0; i<8; i++)//bo
	{
		nBo += ((m_oManuParas.m_binOut[i].nState)<<i);
	}
	CSttDriverOper::setOutPutStatue(nBo);

	setTap();
	float fDAValue[3]  ={0,0,300};//电源功率
	for(int i =0;i<4;i++)
	{
		if(m_oManuParas.m_uiVOL[i].Harm[1].fAmp > fDAValue[0] )
			fDAValue[0] = m_oManuParas.m_uiVOL[i].Harm[1].fAmp;		
	}
	fDAValue[0] = fDAValue[0]+fDAValue[0]*0.1;
	if(fDAValue[0] > 300.0)
		fDAValue[0] = 300.0;

	fDAValue[1] =CSttDevice::g_pSttDevice->getCurrentDa();
	CSttDevice::g_pSttDevice->SetDeviceInnerParaSet(fDAValue);
	//	calcMeasTap();

	m_oDrvManuPara.stAlg[0] = Voltanal;
	m_oDrvManuPara.waveCount[0] = 6+3*6*1;
	m_oDrvManuPara.stAlg[1] = Curanal;
	m_oDrvManuPara.waveCount[1] = 6+3*6*1;
	CSttDriverOper::setManualAcAnalogPara((char*)&m_oDrvManuPara,sizeof(Drv_ManuPara));
}

void CSttManuTest::EventProcess()
{
	int nret = CSttDriverOper::readManualResult((char*)&m_oDrvResult,sizeof(Drv_Result));
	if(nret <28)
	{
		return;
	}
	qDebug()<<"the nRet size is"<<nret;

	for(int i=0;i<m_oDrvResult.nCount;i++)
	{
		//		for(int nIndex=0;nIndex<32;nIndex++)
		//		{
		//			m_pPTU_SingleResult->Bin[nIndex]=pResult->result[i].biValue&(1<<nIndex);
		//			//1=open,0=close
		//		}
		qDebug()<<"type "<<m_oDrvResult.stResult[i].type;
		double currtime=m_oDrvResult.stResult[i].nSec+m_oDrvResult.stResult[i].nNanoSec*0.000000001;
		//AddEventBuf(m_oDrvResult.stResult[i].type,m_oDrvResult.stResult[i].step,m_oDrvResult.stResult[i].biValue,currtime);
	}
}

/***
void CSttManuTest::setChannelData(manualdata* pdata)
{
	drv_manu_test *pstACpara = new drv_manu_test;
	pstACpara->moduleCount =2;

	for(int i=0;i<4;i++)
	{
		if(pdata->vChannel[i].ffre>0)
			pstACpara->sample = 40000/pdata->vChannel[i].ffre;
	}
	for(int i=0;i<8;i++)
	{
		m_fMeasValue[i]=pdata->fMeasValue[i];
	}

	structAnalogPara Voltanal;
	memset(&Voltanal,0,sizeof(structAnalogPara));

	if(m_oManuParas.m_bDC)
	{
		CSttDevice::g_pSttDevice->TranslateACVoltBufferDC(*pdata,Voltanal.nDc);
	}
	else
	{
		CSttDevice::g_pSttDevice->TranslateACVoltBuffer(*pdata,Voltanal.dat);
	}


#ifdef PTU200
	if(d_Data->oacpara().oacanlogpara().fcurrentdc_size()>0)
		FpgaDirectOper::g_FpgsDirectOper->TranslateDCCurrent(d_Data->oacpara().oacanlogpara().fcurrentdc(0),Voltanal.nDc);
#endif

	Voltanal.module = 0;
	pstACpara->stAlg[0] = Voltanal;
	pstACpara->waveCount[0] = 1;

	structAnalogPara Curranal;
	memset(&Curranal,0,sizeof(structAnalogPara));

	if(m_oManuParas.m_bDC)
	{
		CSttDevice::g_pSttDevice->TranslateACCurrentBufferDC(*pdata,Curranal.nDc);
	}
	else
	{
		CSttDevice::g_pSttDevice->TranslateACCurrentBuffer(*pdata,Curranal.dat);
	}

	Curranal.module = 1;
	pstACpara->stAlg[1] = Curranal;
	pstACpara->waveCount[1] = 1;

	setTap();
	CSttDriverOper::setManualAcAnalogPara((char*)pstACpara,sizeof(drv_manu_test));

	delete pstACpara;
}
***/

/***
void CSttManuTest::run()
{
	while (m_bTestRunning)
	{
		msleep(1000);
		if(m_bPause)
			continue;
		calcNewData();
		CLogPrint::LogString(XLOGLEVEL_TRACE,CString("Ua=").arg(m_fMeasValue[0]));
		CLogPrint::LogString(XLOGLEVEL_TRACE,CString("Ub=").arg(m_fMeasValue[1]));
		CLogPrint::LogString(XLOGLEVEL_TRACE,CString("Uc=").arg(m_fMeasValue[2]));
		CLogPrint::LogString(XLOGLEVEL_TRACE,CString("Uz=").arg(m_fMeasValue[3]));

		CLogPrint::LogString(XLOGLEVEL_TRACE,CString("Ia=").arg(m_fMeasValue[4]));
		CLogPrint::LogString(XLOGLEVEL_TRACE,CString("Ib=").arg(m_fMeasValue[5]));
		CLogPrint::LogString(XLOGLEVEL_TRACE,CString("Ic=").arg(m_fMeasValue[6]));
		CLogPrint::LogString(XLOGLEVEL_TRACE,CString("I0=").arg(m_fMeasValue[7]));

		CLogPrint::LogString(XLOGLEVEL_TRACE," ");
		CLogPrint::LogString(XLOGLEVEL_TRACE," ");
	}
}
***/

void CSttManuTest::Stop()
{
	m_Start=false;
	//	msleep(1000);

	if(CSttDeviceBase::g_pSttDeviceBase->IsStartTest_UserParameter())
	{
		CSttDeviceBase::g_pSttDeviceBase->StartTest_UserParameter();
	}
	else
		CSttDeviceBase::g_pSttDeviceBase->CloseDevice();
}

/***
void CSttManuTest::calcNewData()
{
	structSmp *stSmp;
	int nLen = sizeof(structSmp);
	char* pbuff = new char[nLen];
	manualdata *channel = new manualdata;
	int nReady[4] ={0,0,0,0};

	CSttDriverOper::readMeasdata(pbuff,0x02);
	stSmp = (structSmp*)pbuff;
	msleep(100);
	for(int i=0;i<4;i++)
	{
		float nCode=0;
		if(m_nVtap[i] == 0xf)
		{
			nCode =  qSqrt((stSmp->rms[m_vchannel[i]][0]*qPow(2,32)+stSmp->rms[m_vchannel[i]][1])/800);
			float fMeasValue = (float)nCode/32767*2.048*505.1/27.6;
			float fdiffValue = m_manual.vChannel[i].famptitude -fMeasValue;
			channel->fMeasValue[i] = fMeasValue*CSttDevice::g_pSttDevice->m_fVampMeas[i][4];
			channel->vChannel[i].famptitude = m_manual.vChannel[i].famptitude;
		}
		else if(m_nVtap[i] == 0x7)
		{
			nCode =  qSqrt((stSmp->rms[m_vchannel[i]][0]*qPow(2,32)+stSmp->rms[m_vchannel[i]][1])/800);
			float fMeasValue = (float)nCode/32767*2.048*505.1/9.71831;
			float fdiffValue = m_manual.vChannel[i].famptitude -fMeasValue;
			channel->fMeasValue[i] = fMeasValue*CSttDevice::g_pSttDevice->m_fVampMeas[i][3];
			channel->vChannel[i].famptitude = m_manual.vChannel[i].famptitude;
		}
		else if(m_nVtap[i] == 0xb)
		{
			nCode =  qSqrt((stSmp->rms[m_vchannel[i]][0]*qPow(2,32)+stSmp->rms[m_vchannel[i]][1])/800);
			float fMeasValue = (float)nCode/32767*2.048*505.1/5.89742;
			float fdiffValue = m_manual.vChannel[i].famptitude -fMeasValue;
			channel->fMeasValue[i] = fMeasValue*CSttDevice::g_pSttDevice->m_fVampMeas[i][2];
			channel->vChannel[i].famptitude = m_manual.vChannel[i].famptitude;
		}
		else if(m_nVtap[i] == 0xd)
		{
			nCode =  qSqrt((stSmp->rms[m_vchannel[i]][0]*qPow(2,32)+stSmp->rms[m_vchannel[i]][1])/800);
			float fMeasValue = (float)nCode/32767*2.048*505.1/2.70588;
			float fdiffValue = m_manual.vChannel[i].famptitude -fMeasValue;
			channel->fMeasValue[i] = fMeasValue*CSttDevice::g_pSttDevice->m_fVampMeas[i][1];
			channel->vChannel[i].famptitude = m_manual.vChannel[i].famptitude;
		}
		else if(m_nVtap[i] == 0xe)
		{
			if(m_manual.vChannel[i].famptitude > 300)
			{
				int fre = 40000/m_manual.vChannel[i].ffre;

				nCode =  qSqrt((stSmp->rms[m_vchannel[i]][0]*qPow(2,32)+stSmp->rms[m_vchannel[i]][1])/fre);
				qDebug()<<"nocde"<<nCode;
				float fMeasValue= (float)nCode/32767*2.048*505.1/0.9995002*CSttDevice::g_pSttDevice->m_fVampMeas[i][0];

				if(fMeasValue<200)
					return;

				qDebug()<<"the bcxs"<<CSttDevice::g_pSttDevice->m_fVampMeas[i][0];
				float fdiffValue = m_manual.vChannel[i].famptitude -fMeasValue;
				channel->fMeasValue[i] = fMeasValue;
				float pPre = fdiffValue/m_manual.vChannel[i].famptitude;
				qDebug()<<"the fmeasvalue is"<<fMeasValue<<"the pre is"<<pPre;

				if(pPre<=0.3 && pPre>=-0.3 && qAbs(pPre)>0.0001)
				{
					channel->vChannel[i].famptitude = m_channelTemp.vChannel[i].famptitude+fdiffValue;
					m_channelTemp.vChannel[i].famptitude = channel->vChannel[i].famptitude;
				}
				else if(pPre>0.45 || pPre<-0.45)
				{
					m_nOverload=1;
					Stop();
				}
				else
				{
					channel->vChannel[i].famptitude = m_channelTemp.vChannel[i].famptitude;
					nReady[i] = 1;
				}

				qDebug()<<"the famptitude is"<<channel->vChannel[i].famptitude;
			}
			else
			{
				nCode =  qSqrt((stSmp->rms[m_vchannel[i]][0]*qPow(2,32)+stSmp->rms[m_vchannel[i]][1])/800);
				float fMeasValue = (float)nCode/32767*2.048*505.1/0.9995002*CSttDevice::g_pSttDevice->m_fVampMeas[i][0];
				channel->fMeasValue[i] = fMeasValue;
				channel->vChannel[i].famptitude = m_manual.vChannel[i].famptitude;
			}

		}

		if(m_nITap[i] == 0xf)
		{
			nCode =  qSqrt((stSmp->rms[m_ichannel[i]][0]*qPow(2,32)+stSmp->rms[m_ichannel[i]][1])/800);
			float fMeasValue = (float)nCode/32767*2.048*51/285;
			float fdiffValue = m_manual.iChannel[i].famptitude -fMeasValue;
			channel->fMeasValue[i+4] = fMeasValue*CSttDevice::g_pSttDevice->m_fIampMeas[i][4];
			channel->iChannel[i].famptitude = m_manual.iChannel[i].famptitude;
		}
		if(m_nITap[i] == 0x7)
		{
			nCode =  qSqrt((stSmp->rms[m_ichannel[i]][0]*qPow(2,32)+stSmp->rms[m_ichannel[i]][1])/800);
			float fMeasValue = (float)nCode/32767*2.048*51/116.591767;
			float fdiffValue = m_manual.iChannel[i].famptitude -fMeasValue;
			channel->fMeasValue[i+4] = fMeasValue*CSttDevice::g_pSttDevice->m_fIampMeas[i][3];
			channel->iChannel[i].famptitude = m_manual.iChannel[i].famptitude;
		}
		else if(m_nITap[i] == 0xb)
		{
			nCode =  qSqrt((stSmp->rms[m_ichannel[i]][0]*qPow(2,32)+stSmp->rms[m_ichannel[i]][1])/800);
			float fMeasValue = (float)nCode/32767*2.048*51/59.1356;
			float fdiffValue = m_manual.iChannel[i].famptitude -fMeasValue;
			channel->fMeasValue[i+4] = fMeasValue*CSttDevice::g_pSttDevice->m_fIampMeas[i][2];
			channel->iChannel[i].famptitude = m_manual.iChannel[i].famptitude;
		}
		else if(m_nITap[i] == 0xe)
		{
			nCode =  qSqrt((stSmp->rms[m_ichannel[i]][0]*qPow(2,32)+stSmp->rms[m_ichannel[i]][1])/800);
			float fMeasValue = (float)nCode/32767*2.048*51/11.7948;
			float fdiffValue = m_manual.iChannel[i].famptitude -fMeasValue;
			channel->fMeasValue[i+4] = fMeasValue*CSttDevice::g_pSttDevice->m_fIampMeas[i][1];
			channel->iChannel[i].famptitude = m_manual.iChannel[i].famptitude;
		}
		else if(m_nITap[i] == 0xc)
		{
			nCode =  qSqrt((stSmp->rms[m_ichannel[i]][0]*qPow(2,32)+stSmp->rms[m_ichannel[i]][1])/800);
			float fMeasValue = (float)nCode/32767*2.048*51/6.7540723;
			float fdiffValue = m_manual.iChannel[i].famptitude -fMeasValue;
			channel->fMeasValue[i+4] = fMeasValue*CSttDevice::g_pSttDevice->m_fIampMeas[i][0];
			channel->iChannel[i].famptitude = m_manual.iChannel[i].famptitude;
		}
	}
	for(int i =0;i<4;i++)
	{
		channel->iChannel[i].fphase = m_manual.iChannel[i].fphase;
		channel->iChannel[i].ffre = m_manual.iChannel[i].ffre;
		channel->vChannel[i].fphase = m_manual.vChannel[i].fphase;
		channel->vChannel[i].ffre = m_manual.vChannel[i].ffre;
	}

	setChannelData(channel);
	if(nReady[0] == 1&&nReady[1] == 1&&nReady[2] == 1&&nReady[3] == 1)
	{

	}
	delete []pbuff;
	delete channel;
	channel = NULL;
}
***/
