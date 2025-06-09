#include "SttIEDTest.h"
#include "../../SttDevice/drv_define.h"
#include "../../SttDevice/SttDriverOper.h"
#include "../../Engine/SttServerTestCtrlCntr.h"



CString CSttIEDTest::m_strMacroName = "ÖÇÄÜÖÕ¶Ë²âÊÔ";
CString CSttIEDTest::m_strMacroID = ("SttIEDTest");
CString CSttIEDTest::m_strFilePostFix = "stttst";
CString CSttIEDTest::m_strMacroVer ="1.0";

CSttIEDTest::CSttIEDTest()
{
	m_pszResultBuff=stt_test_init_result_buff();
	stBinOut=new structSoe;
	soeResult=new structSoeResult;
	m_ostructGSOutMap=new structGSOutMap;
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_Start=FALSE;
}

CSttIEDTest::~CSttIEDTest()
{
	m_pszResultBuff= NULL;
}


void CSttIEDTest::AfterSetParameter()
{

}

void CSttIEDTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	m_oIEDParas.init();
	stt_xml_serialize(&m_oIEDParas,pXmlSerialize);
}

void CSttIEDTest::StartTest()
{
#ifdef _PSX_QT_LINUX_
	TtmToDrv();
	if(m_oIEDParas.m_nDataMode>1)
	{
		if(!m_Start)
		{
			CSttDriverOper::startDMA();
			CSttDriverOper::setFilter(0);

			if(m_oIEDParas.m_nDataMode==3)
				CSttDriverOper::Start(0xa);

			if(m_oIEDParas.m_nDataMode==2)
				CSttDriverOper::Start(0xc);

			Sleep(1300);
		}

//		CSttDevice::g_pSttDevice->SetTestStop();
//		CSttParas *pParas=CSttServerTestCtrlCntr::GetCurrParas();
//		pParas->AddNewData("TestReturn",0);
		return;
	}

	if(!m_Start)
	{
		m_Start=TRUE;

		CSttDriverOper::startDMA();
		CSttDriverOper::setFilter(0);

		if(m_oIEDParas.m_nDataMode==1)
			CSttDriverOper::Start(0xa);

		if(m_oIEDParas.m_nDataMode==0)
			CSttDriverOper::Start(0xc);

		//CSttDriverOper::setSendAtStop(1);
	}

#endif
}

void CSttIEDTest::Stop()
{	
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
}

void CSttIEDTest::EventProcess()
{
	/***
	if(!m_Start)
		return;

	if(m_oIEDParas.m_nTestType==RepeatMode||m_oIEDParas.m_nDataMode==2||m_oIEDParas.m_nDataMode==3)
		return;

	CSttParas *pParas=CSttServerTestCtrlCntr::GetCurrParas();

	int nLen=sizeof(structSoeResult);
	int nRet = CSttDriverOper::ReadBinaryModule(m_pszResultBuff);
	if(nRet < 0)
	{
		return;
	}

	int nSize = nRet/nLen;

	double nTestTime;

	for(int i = 0;i<nSize;i++)
	{
		memcpy(soeResult,m_pszResultBuff+i*nLen,nLen);

		nTestTime=soeResult->tm_h+soeResult->tm_l*0.000000001;
		qDebug()<<"Result tm"<<CString::number(nTestTime,10,9);
		qDebug()<<"Result Type"<<soeResult->nType;

		m_strCurrBiVal=QString("%1").arg(soeResult->item[1].bi[1],32,2,QChar('0'));
		m_strCurrBiVal+=QString("%1").arg(soeResult->item[1].bi[0],32,2,QChar('0'));

		switch(soeResult->nType)
		{
		case 1:
		{
			pParas->AddNewData("TestStart",0);
			m_strPreBiVal=QString("%1").arg((unsigned int)0xffffffff,32,2,QChar('0'));
			m_strPreBiVal+=m_strPreBiVal;
			if(m_oIEDParas.m_nDataMode==1)
			{
				GooseSubData *ogsesub=CIEC61850CfgMngr::g_pIEC61850CfgMngr->gsesub;
				unsigned int val[2]={0,0};
				for(int nIndex=0;nIndex<ogsesub->ncount;nIndex++)
				{
					GooseSubItem &gooseSub=ogsesub->gooseSub[nIndex];
					for(int nSubIndex=0;nSubIndex<gooseSub.count;nSubIndex++)
					{
						int nBiIndex=gooseSub.val[nSubIndex].index;
						if(nBiIndex<32)
							val[0]|=1<<nBiIndex;
						else
							val[1]|=1<<(nBiIndex-32);
					}
				}

				m_strPreBiVal=QString("%1").arg(val[1],32,2,QChar('0'));
				m_strPreBiVal+=QString("%1").arg(val[0],32,2,QChar('0'));
			}
			m_oSoeResult.fStartTime=nTestTime;
			for(int nIndex=0;nIndex<64;nIndex++)
			{
				m_oSoeResult.item[1].fChgTime[nIndex]=0.0;
			}

			qDebug()<<"TestStart BiVal"<<m_strPreBiVal;
		}
			continue;
		case 3:
		{
			if(m_oIEDParas.m_nTestType==DelayMode)
			{
				m_fDelayBeginTime=nTestTime;
				if(m_oIEDParas.m_nDataMode==0)
					m_fDelayBeginTime+=0.000100;
				//Ó²¼þ²¹³¥
				//				else
				//				{
				//					if(strCurrBitVal==1)
				//						m_fDelayBeginTime+=0.000030;
				//					else
				//						m_fDelayBeginTime+=0.000080;
				//				}
			}

		}
			continue;
		case 4:
			break;
		}

		if(m_oIEDParas.m_nTestType==DelayMode)
		{
			m_fDelayEndTime=nTestTime;
		}

		for(int nIndex=0;nIndex<64;nIndex++)
		{
			m_bChgChan[nIndex]=false;
		}

		qDebug()<<"Result  PreBI"<< m_strPreBiVal;
		qDebug()<<"Result CurrBI"<< m_strCurrBiVal;

		if(m_strPreBiVal.compare(m_strCurrBiVal)==0)
			continue;

		GetChgNum(m_strPreBiVal,m_strCurrBiVal,m_bChgChan);
		double tm;
		for(int nIndex=0;nIndex<64;nIndex++)
		{
			if(m_bChgChan[nIndex])
			{
				CDvmData *pData = pParas->AddNewData("",0);
				pData->m_strID.Format("Bin%03d",nIndex+9-m_oDeviceInfo->switchmodule[0].BoCount);
				if(m_oIEDParas.m_nDataMode==1)
					pData->m_strID.Format("Bin%03d",nIndex+9);

				switch(m_oIEDParas.m_nTestType)
				{
				case DelayMode:
				{
					pData->m_strValue=CString::number(m_fDelayEndTime-m_fDelayBeginTime,10,9);
				}
					break;
				case SOEMode:
				{
					if(m_oSoeResult.item[1].fChgTime[nIndex]<0.00001)
					{
						m_oSoeResult.item[1].fChgTime[nIndex]=nTestTime;
					}
					else
					{
						m_oSoeResult.item[1].fBackTime[nIndex]=nTestTime;
						tm=m_oSoeResult.item[1].fChgTime[nIndex]-m_oSoeResult.fStartTime;
						pData->m_strValue=CString::number(tm,10,9);
						pData->m_strValue+="$";
						tm=m_oSoeResult.item[1].fBackTime[nIndex]-m_oSoeResult.fStartTime;
						pData->m_strValue+=CString::number(tm,10,9);
					}
				}
					break;
				}
			}
		}
		m_strPreBiVal=m_strCurrBiVal;
	}
	***/
}

/***
void CSttIEDTest::GetChgNum(CString strPreBiVal,CString strCurrBiVal,bool *bChgChan)
{
	CString strPreBitVal;
	CString strCurrBitVal;

	if(m_oIEDParas.m_nDataMode==1)
	{
		//TtmToDrv_B2G();

		for(int nIndex=0;nIndex<64;nIndex++)
		{
			strPreBitVal=strPreBiVal.right(nIndex+1).left(1);
			strCurrBitVal=strCurrBiVal.right(nIndex+1).left(1);

			if(m_oIEDParas.m_nTestType==DelayMode&&strCurrBitVal.toInt()==1)
				continue;

			if(CString::compare(strPreBitVal,strCurrBitVal)!=0)
				bChgChan[nIndex]=TRUE;
		}
	}

	if(m_oIEDParas.m_nDataMode==0)
	{
		//TtmToDrv_G2B();
		switch(m_oDeviceInfo->switchmodule[0].BoCount)
		{
		case 0:
			for(int nIndex=0;nIndex<64;nIndex++)
			{
				strPreBitVal=strPreBiVal.right(nIndex+1).left(1);
				strCurrBitVal=strCurrBiVal.right(nIndex+1).left(1);

				if(m_oIEDParas.m_nTestType==DelayMode&&strCurrBitVal.toInt()==1)
					continue;

				if(CString::compare(strPreBitVal,strCurrBitVal)!=0)
					bChgChan[nIndex]=TRUE;
			}
			break;
		case 16:
			for(int nIndex=16;nIndex<64;nIndex++)
			{
				strPreBitVal=strPreBiVal.right(nIndex+1).left(1);
				strCurrBitVal=strCurrBiVal.right(nIndex+1).left(1);

				if(m_oIEDParas.m_nTestType==DelayMode&&strCurrBitVal.toInt()==1)
					continue;

				if(CString::compare(strPreBitVal,strCurrBitVal)!=0)
					bChgChan[nIndex]=TRUE;
			}
			break;
		case 32:
			for(int nIndex=32;nIndex<64;nIndex++)
			{
				strPreBitVal=strPreBiVal.right(nIndex+1).left(1);
				strCurrBitVal=strCurrBiVal.right(nIndex+1).left(1);

				if(m_oIEDParas.m_nTestType==DelayMode&&strCurrBitVal.toInt()==1)
					continue;

				if(CString::compare(strPreBitVal,strCurrBitVal)!=0)
					bChgChan[nIndex]=TRUE;
			}
			break;
		case 48:
			for(int nIndex=48;nIndex<64;nIndex++)
			{
				strPreBitVal=strPreBiVal.right(nIndex+1).left(1);
				strCurrBitVal=strCurrBiVal.right(nIndex+1).left(1);

				if(m_oIEDParas.m_nTestType==DelayMode&&strCurrBitVal.toInt()==1)
					continue;

				if(CString::compare(strPreBitVal,strCurrBitVal)!=0)
					bChgChan[nIndex]=TRUE;
			}
			break;
		}
	}
}
***/

void CSttIEDTest::TtmToDrv()
{
	if(m_oIEDParas.m_nTestType==DelayMode)
		m_fDelayBeginTime=0.0;

	if(m_oIEDParas.m_nDataMode==1||m_oIEDParas.m_nDataMode==3)
//		TtmToDrv_B2G()
		;

	if(m_oIEDParas.m_nDataMode==0||m_oIEDParas.m_nDataMode==2)
//		TtmToDrv_G2B()
		;
}

/***
void CSttIEDTest::TtmToDrv_B2G()
{
	memset(stBinOut,0,sizeof(structSoe));
	stBinOut->nModuleCnt = 1;
	tmt_IEDPara &otmt_IEDPara=m_oIEDParas.m_otmt_IEDPara[0];
	m_nBoNum[0]=0;
	m_nBoNum[1]=0;
	m_nBoNum[2]=0;
	m_nBoNum[3]=0;

	int nBoTotal=0;
	for(int i =0;i<stBinOut->nModuleCnt;i++)
	{
		SwitchModule &oSwitchModule=m_oDeviceInfo->switchmodule[i];
		stBinOut->item[i].nModule = oSwitchModule.pos;
		stBinOut->item[i].nBinOut[0]=0xffffffff;
		stBinOut->item[i].nBinOut[1]=0xffffffff;
		if(m_oIEDParas.m_nDataMode==1)
			stBinOut->item[i].nDelayTime=m_oIEDParas.m_nFaultPreTime*50000;
		nBoTotal+=oSwitchModule.BoCount;
	}

	if(m_oIEDParas.m_nDataMode==1)
	{
		for(int nIndex=0;nIndex<nBoTotal;nIndex++)
		{
			SetBoVal(*stBinOut,nIndex+1,otmt_IEDPara.m_binOut[nIndex+8].nState);
		}
	}

	stBinOut->tm_h = 1000000;

	CSttDriverOper::SetBinaryModule((char*)stBinOut,sizeof(structSoe));
}

void CSttIEDTest::TtmToDrv_G2B()
{
	structGSOutMap *stMaps=CIEC61850CfgMngr::g_pIEC61850CfgMngr->stMaps;
	int nMode=0;
	switch(m_oIEDParas.m_nTestType)
	{
	case SOEMode:
		nMode=2;
		break;
	case RepeatMode:
		nMode=1;
		break;
	case DelayMode:
		nMode=0;
		break;
	}

	if(!m_Start)
	{
		if(nMode==2&&m_oIEDParas.m_nDataMode==0)
		{
			memset(m_ostructGSOutMap,0,sizeof(structGSOutMap));
			memcpy(m_ostructGSOutMap,stMaps,sizeof(structGSOutMap));
			int nBoCount=0;
			for(int i=0;i<32;i++)
			{
				if(nBoCount>2)
				{
					m_ostructGSOutMap->boMd[0].info[0][i].cnt==0;
				}
				else if(m_ostructGSOutMap->boMd[0].info[0][i].cnt>0)
					nBoCount++;
			}

			for(int i=0;i<32;i++)
			{
				if(nBoCount>2)
				{
					m_ostructGSOutMap->boMd[0].info[1][i].cnt==0;
				}
				else if(m_ostructGSOutMap->boMd[0].info[1][i].cnt>0)
					nBoCount++;
			}

			CSttDriverOper::setGooseBoMapData((char*)m_ostructGSOutMap,sizeof(structGSOutMap));
		}
		else
		{
			CSttDriverOper::setGooseBoMapData((char*)stMaps,sizeof(structGSOutMap));
		}

		structModuleParam modulepara;
		memset(&modulepara,0,sizeof(structModuleParam));
		modulepara.nAlgCnt = 1;
		modulepara.nAlgTable[0]=DIGITAL_CHANNEL_MARK;

		modulepara.nbIntCnt = 2;
		modulepara.nbITable[0] = 0x8000;
		modulepara.nbITable[1] = 8;
		modulepara.nBoCnt = 2;
		modulepara.nBoTable[0] = 0x8000;
		modulepara.nBoTable[1] = 8;
		CSttDriverOper::SetModuleInfo((char*)&modulepara,sizeof(structModuleParam));

		CSttDriverOper::IoCtrl(0x133,nMode);

		memset(stBinOut,0,sizeof(structSoe));
		stBinOut->nModuleCnt=5;
		stBinOut->item[0].nDelayTime=m_oIEDParas.m_nFaultPreTime*50000;
		int nBoNum=0;
		for(int i=0;i<32;i++)
		{
			stBinOut->item[0].param[i].nTmHigh=m_oIEDParas.m_nBoKeepTime*50000;
			stBinOut->item[0].param[i].nTmLow=m_oIEDParas.m_nBoKeepTime*50000;
			stBinOut->item[0].param[i].nflipCnt=m_oIEDParas.m_nRepeatCount;

			if(stMaps->boMd[0].info[0][i].cnt>0)
			{
				stBinOut->item[0].nBeginTime[i]=nBoNum*m_oIEDParas.m_nOutputTime*50000;
				nBoNum++;
			}
		}

		for(int i=32;i<64;i++)
		{
			stBinOut->item[0].param[i].nTmHigh=m_oIEDParas.m_nBoKeepTime*50000;
			stBinOut->item[0].param[i].nTmLow=m_oIEDParas.m_nBoKeepTime*50000;
			stBinOut->item[0].param[i].nflipCnt=m_oIEDParas.m_nRepeatCount;

			if(stMaps->boMd[0].info[1][i-32].cnt>0)
			{
				stBinOut->item[0].nBeginTime[i]=nBoNum*m_oIEDParas.m_nOutputTime*50000;
				nBoNum++;
			}
		}
	}

	stBinOut->item[0].nBinOut[0]=0xffffffff;
	stBinOut->item[0].nBinOut[1]=0xffffffff;

	if(nMode==0&&m_oIEDParas.m_nDataMode==0)
	{
		for(int i=0;i<32;i++)
		{
			if(m_oIEDParas.m_otmt_IEDPara[0].m_binOut[i+8].nState>0)
			{
				stBinOut->item[0].nBinOut[0]&= ~(1<<i);
			}
		}

		for(int i=32;i<64;i++)
		{
			if(m_oIEDParas.m_otmt_IEDPara[0].m_binOut[i+8].nState>0)
			{
				stBinOut->item[0].nBinOut[1]&=~(1<<(i-32));
			}
		}
	}

	CSttDriverOper::IoCtrl(0x341,0);
	CSttDriverOper::WriteData((char*)stBinOut,sizeof(structSoe));
}


void CSttIEDTest::SetBoVal(structSoe &oSoe,int nExBo,int nState)//nExBoI=1~256
{
	if(nExBo<=m_oDeviceInfo->switchmodule[0].BoCount)
	{
		SetDrvBoVal(m_oDeviceInfo->switchmodule[0],oSoe.item[0],nExBo,nState);
	}
	else
	{
		nExBo-=m_oDeviceInfo->switchmodule[0].BoCount;
		if(nExBo<=m_oDeviceInfo->switchmodule[1].BoCount)
		{
			SetDrvBoVal(m_oDeviceInfo->switchmodule[1],oSoe.item[1],nExBo,nState);
		}
		else
		{
			nExBo-=m_oDeviceInfo->switchmodule[1].BoCount;
			if(nExBo<=m_oDeviceInfo->switchmodule[2].BoCount)
			{
				SetDrvBoVal(m_oDeviceInfo->switchmodule[2],oSoe.item[2],nExBo,nState);
			}
			else
			{
				nExBo-=m_oDeviceInfo->switchmodule[2].BoCount;
				if(nExBo<=m_oDeviceInfo->switchmodule[3].BoCount)
				{
					SetDrvBoVal(m_oDeviceInfo->switchmodule[3],oSoe.item[3],nExBo,nState);
				}
			}
		}
	}

}

void CSttIEDTest::SetDrvBoVal(SwitchModule &oSwitchModule,structSoeItem &oitem,int nExBo,int nState)
{
	int nBoCount=0;
	int nFlag=0;
	for(int nIndex=0;nIndex<32;nIndex++)
	{
		nFlag=oSwitchModule.channel_G2G1&(1<<nIndex);
		if(nFlag==0)
		{
			nBoCount++;
			if(nExBo==nBoCount)
			{
				switch(m_oIEDParas.m_nTestType)
				{
				case SOEMode:
					if(nState==1)
					{
						int nSwitchModuleIndex=oSwitchModule.group;
						oitem.nType[0]|=1<<(nExBo-1);
						oitem.nBeginTime[nExBo-1]=m_nBoNum[nSwitchModuleIndex]*m_oIEDParas.m_nOutputTime*50000;
						m_nBoNum[nSwitchModuleIndex]++;
					}
					oitem.param[nExBo-1].nTmHigh=m_oIEDParas.m_nBoKeepTime*50000;
					oitem.param[nExBo-1].nTmLow=m_oIEDParas.m_nBoKeepTime*50000;
					oitem.param[nExBo-1].nflipCnt=2;
					break;
				case RepeatMode:
					if(nState==1)
						oitem.nType[0]|=1<<(nExBo-1);
					oitem.param[nExBo-1].nTmHigh=m_oIEDParas.m_nBoKeepTime*50000;
					oitem.param[nExBo-1].nTmLow=m_oIEDParas.m_nBoKeepTime*50000;
					oitem.param[nExBo-1].nflipCnt=m_oIEDParas.m_nRepeatCount;
					break;
				case DelayMode:
					if(nState==1)
						oitem.nBinOut[0]&= ~(1<<(nExBo-1));
					break;
				}
				return;
			}
		}
	}
	nExBo-=nBoCount;
	nBoCount=0;
	for(int nIndex=0;nIndex<32;nIndex++)
	{
		nFlag=oSwitchModule.channel_G4G3&(1<<nIndex);
		if(nFlag==0)
		{
			nBoCount++;
			if(nExBo==nBoCount)
			{
				switch(m_oIEDParas.m_nTestType)
				{
				case SOEMode:
					if(nState==1)
					{
						int nSwitchModuleIndex=oSwitchModule.group;
						oitem.nType[1]|=1<<(nExBo-1);
						oitem.nBeginTime[nExBo+31]=m_nBoNum[nSwitchModuleIndex]*m_oIEDParas.m_nOutputTime*50000;
						m_nBoNum[nSwitchModuleIndex]++;
					}
					oitem.param[nExBo+31].nTmHigh=m_oIEDParas.m_nBoKeepTime*50000;
					oitem.param[nExBo+31].nTmLow=m_oIEDParas.m_nBoKeepTime*50000;
					oitem.param[nExBo+31].nflipCnt=2;
					break;
				case RepeatMode:
					if(nState==1)
						oitem.nType[1]|=1<<(nExBo-1);
					oitem.param[nExBo+31].nTmHigh=m_oIEDParas.m_nBoKeepTime*50000;
					oitem.param[nExBo+31].nTmLow=m_oIEDParas.m_nBoKeepTime*50000;
					oitem.param[nExBo+31].nflipCnt=m_oIEDParas.m_nRepeatCount;
					break;
				case DelayMode:
					if(nState==1)
						oitem.nBinOut[1]&= ~(1<<(nExBo-1));
					break;
				}
				return;
			}
		}
	}
}
***/
