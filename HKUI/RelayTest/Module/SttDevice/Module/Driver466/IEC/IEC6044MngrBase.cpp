#include "IEC6044MngrBase.h"
#include "OSInterface.h"
#include "../../../../SttTest/Common/SttSystemConfig.h"

CIEC6044MngrBase::CIEC6044MngrBase()
{
	Init();
}

CIEC6044MngrBase::~CIEC6044MngrBase()
{
}

void CIEC6044MngrBase::Init()
{
	m_nSample = 4000;
	m_nBaudRate = 0;//2.5,5,10,20
	m_nSendSampleLen = 0;
	m_nVoltDrvCnt = 0;
	m_nCurrDrvCnt = 0;

	for(int i = 0; i < 36; i++)
	{
		m_nVoltDrvPos[36] = 0;
		m_nCurrDrvPos[36] = 0;
	}

	InitChanelMap();
	InitFT3ChanelType();
	data_6044.clear();
	data_6044Sub.clear();
}

void CIEC6044MngrBase::InitSampleLen(long nSampleDataLen)
{
	QMap<QString, FT3MapPointer>::iterator mi;

	for(mi = m_Ft3ChannelType.begin(); mi != m_Ft3ChannelType.end(); mi++)
	{
		FT3MapPointer map = mi.value();
		map.nSampleLen = nSampleDataLen;
		mi.value() = map;
	}
}

void CIEC6044MngrBase::Create6044ComTmtStruct(CIecCfg6044CommonData *pIecData)
{
	if(pIecData->m_nUseFlag == 0 || m_strSendProtocolID != pIecData->m_strProtocolID)
	{
		return;
	}

	m_nBaudRate = pIecData->m_nBaudRate;
	m_nSample = pIecData->m_nSampleRate;
	m_nSendSampleLen = pIecData->m_nSmpDataLen;

	tmt_ft3_6044 otmt_6044;
	otmt_6044.port = pIecData->m_nFiberIndex;
	otmt_6044.m_nChanNum = pIecData->m_nChannelNum;
	otmt_6044.m_nDelayTimeValue = pIecData->m_nDelayTime;
	otmt_6044.m_nSampleType = pIecData->m_nSmpCntType + 1;//界面传的是Combox的Index
	otmt_6044.m_nSampleDataLen  = pIecData->m_nSmpDataLen;
	InitSampleLen(otmt_6044.m_nSampleDataLen);

	for(int nChan = 0; nChan < otmt_6044.m_nChanNum; nChan++)
	{
		CIecCfg6044CommonCh *pCIecCfg6044ComCh = (CIecCfg6044CommonCh *)pIecData->m_pCfgChs->GetAtIndex(nChan);
		FT3ChanInfo  oChanInfo;
		oChanInfo.nLen = pCIecCfg6044ComCh->m_nChLenth;
		oChanInfo.strMap = pCIecCfg6044ComCh->m_strAppChID;
		oChanInfo.nFirstValue = pCIecCfg6044ComCh->m_nValue;

		if(g_theSystemConfig->m_nIecFormat == STT_IEC_FORMAT_60044_8
				&& pCIecCfg6044ComCh->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure)
		{
			oChanInfo.strMap += "M";
		}

		otmt_6044.m_oChanList.append(oChanInfo);

		if(oChanInfo.strMap.contains("t-delay"))
		{
			BOOL bFindUI = FALSE;
			BOOL bOk;
			long nDelayGroup;

			for(int i = 0; i < otmt_6044.m_nChanNum; i++)
			{
				CIecCfg6044CommonCh *pCIecCfg6044ComCh2 = (CIecCfg6044CommonCh *)pIecData->m_pCfgChs->GetAtIndex(i);
				QString chanstrUI = pCIecCfg6044ComCh2->m_strAppChID;

				if(chanstrUI.contains("U") || chanstrUI.contains("I"))
				{
					nDelayGroup = chanstrUI.right(1).toInt(&bOk, 10);

					if(bOk && nDelayGroup > 0)
					{
						bFindUI = TRUE;
					}

					break;
				}
			}

			if(bFindUI)
			{
				if(nDelayGroup <= MAX_DIGITAL_GROUP_NUM)
				{
					if(m_nDelayTime[nDelayGroup - 1] == 0)
					{
						m_nDelayTime[nDelayGroup - 1] = otmt_6044.m_nDelayTimeValue;
					}
				}
			}
		}
	}

	data_6044.append(otmt_6044);
}

void CIEC6044MngrBase::InsertCRCFlag_Standard(QByteArray &oPackage)
{
	int n = 0;
	QByteArray oPackage2;
	oPackage2.clear();
	oPackage2.append(oPackage.at(0));
	oPackage2.append(oPackage.at(1));

	for(int i = 2; i < oPackage.size(); i++)
	{
		if(n == 16)
		{
			//块之间CRC
			oPackage2.append(0xab);//取0xABBA,便于识别，最终数值由FPGA自动替换
			oPackage2.append(0xba);
			n = 0;
		}

		n++;
		oPackage2.append(oPackage.at(i));
	}

	if(m_oEncoderInfo.nSmpcntPos >= 2)
	{
		long nSmpcntPos = m_oEncoderInfo.nSmpcntPos - 2;
		long nBlocks = nSmpcntPos / 16;

		if(nSmpcntPos % 16 == 0)
		{
			nBlocks -= 1;//正好整除的时候，只需补到前一个块
		}

		m_oEncoderInfo.nSmpcntPos += nBlocks * 2;
	}

	if(m_bACDataBegin)
	{
		long nACDataPos = m_oEncoderInfo.nACDataPos - 2;
		long nBlocks = nACDataPos / 16;

		if(nACDataPos % 16 == 0)
		{
			nBlocks -= 1;//正好整除的时候，只需补到前一个块
		}

		m_oEncoderInfo.nACDataPos += nBlocks * 2;
		long nDataCnt = 0;

		for(int i = m_oEncoderInfo.nACDataPos; i < oPackage2.size(); i++)
		{
			if(nDataCnt > m_oEncoderInfo.nACDataLen)
			{
				break;
			}

			if(oPackage2.at(i - 1) == 0xab && oPackage2.at(i) == 0xba)
			{
				m_oEncoderInfo.nACDataLen += 2;
			}

			nDataCnt++;
		}
	}

	//尾部CRC
	oPackage2.append(0xab);
	oPackage2.append(0xba);
	oPackage.clear();
	oPackage.swap(oPackage2);
}

void CIEC6044MngrBase::EnCoderHeader(tmt_ft3_6044 otmt_6044, QByteArray &m_oPackage)
{
	QByteArray oar;
	unsigned short nLen = m_oPackage.size();
	oar.push_back((nLen >> 8) & 0xFF);
	oar.push_back((nLen & 0xFF));
	//nACDataPos
	oar.push_back((m_oEncoderInfo.nACDataPos >> 8) & 0xFF);
	oar.push_back((m_oEncoderInfo.nACDataPos & 0xFF));
	//nACDataLen
	oar.push_back((m_oEncoderInfo.nACDataLen >> 8) & 0xFF);
	oar.push_back((m_oEncoderInfo.nACDataLen & 0xFF));
	//nSmpcntPos
	oar.push_back((m_oEncoderInfo.nSmpcntPos >> 8) & 0xFF);
	oar.push_back((m_oEncoderInfo.nSmpcntPos & 0xFF));
	oar.push_back(m_oEncoderInfo.nSmpcntType & 0xFF);
	oar.push_back(otmt_6044.m_nSampleDataLen & 0xFF);
	oar.push_back((char)0x00);
	oar.push_back((char)0x00);
	m_oPackage.prepend(oar);
}
