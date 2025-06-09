#include "IEC6044MngrBase.h"
#include "OSInterface.h"

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
	if(pIecData->m_nUseFlag == 0)
	{
		return;
	}

	m_nBaudRate = pIecData->m_nBaudRate;
	m_nSample = pIecData->m_nSampleRate;
	tmt_ft3_6044 otmt_6044;
	otmt_6044.port = pIecData->m_nFiberIndex;
	otmt_6044.m_nChanNum = pIecData->m_nChannelNum;
	otmt_6044.m_nDelayTimeValue = pIecData->m_nDelayTime;
	otmt_6044.m_nSampleType = pIecData->m_nSmpCntType + 1;//界面传的是Combox的Index
	otmt_6044.m_nSampleDataLen  = pIecData->m_nSmpDataLen;
	InitSampleLen(otmt_6044.m_nSampleDataLen);
	QString strChType;

	for(int nChan = 0; nChan < otmt_6044.m_nChanNum; nChan++)
	{
		CIecCfg6044CommonCh *pCIecCfg6044ComCh = (CIecCfg6044CommonCh *)pIecData->m_pCfgChs->GetAtIndex(nChan);
		FT3ChanInfo  oChanInfo;
		oChanInfo.nLen = pCIecCfg6044ComCh->m_nChLenth;
		oChanInfo.strMap = pCIecCfg6044ComCh->m_strAppChID;
		oChanInfo.nFirstValue = pCIecCfg6044ComCh->m_nValue;
		strChType = pCIecCfg6044ComCh->m_strChType;
		otmt_6044.m_oChanList.append(oChanInfo);
	}

	data_6044.append(otmt_6044);
}

//FPGA不支持接收报文长度是奇数的情况
void CIEC6044MngrBase::Create6044ComSubTmtStruct(CIecCfg6044CommonInData *pIecData)
{
	if(pIecData->m_nUseFlag == 0)
	{
		return;
	}

	tmt_ft3_6044 otmt_6044;
	otmt_6044.port = pIecData->m_nFiberIndex;
	otmt_6044.m_nChanNum = pIecData->m_nChannelNum;
	otmt_6044.m_nBaudValSub = pIecData->m_nBaudRate;
	otmt_6044.m_nSampleValSub = pIecData->m_nSampleRate;
	QString strDevChID;
	int n = 0;
	int nOffset = 2;//0564

	for(int nChan = 0; nChan < otmt_6044.m_nChanNum; nChan++)
	{
		CIecCfg6044CommonChIn *pCIecCfg6044ComCh = (CIecCfg6044CommonChIn *)pIecData->m_pCfgChs->GetAtIndex(nChan);
		FT3ChanInfo  oChanInfo;
		oChanInfo.nLen = pCIecCfg6044ComCh->m_nChLenth;
		oChanInfo.nFirstValue = nChan + 1;//按通道顺序编号，便于查看
		strDevChID = pCIecCfg6044ComCh->m_strDevChID;
		oChanInfo.nValidBitSub = 0;
		memset(oChanInfo.nBiIdxSub, 0, 16 * 4); //初始化
		oChanInfo.nChanPos1 = nOffset;

		if((n + oChanInfo.nLen) > 16)
		{
			oChanInfo.nChanLen1 = 16 - n;
			oChanInfo.nChanLen2 = oChanInfo.nLen - oChanInfo.nChanLen1;
			oChanInfo.nChanPos2 = oChanInfo.nChanPos1 + oChanInfo.nChanLen1 + 2;
		}
		else
		{
			oChanInfo.nChanLen1 = oChanInfo.nLen;
			oChanInfo.nChanLen2 = 0;
			oChanInfo.nChanPos2 = 0;
		}

		if(pCIecCfg6044ComCh->m_strChType == "StateValue"
				|| (pCIecCfg6044ComCh->m_strChType == "Other" && pCIecCfg6044ComCh->m_strAppChID == "Other"))
		{
			QList<QString> oDevChList = strDevChID.split(";");

			if(oDevChList.count() > 0)
			{
				QString strBitIdx, strBinIdx;
				long nBitIdx, nBinIdx;

				for(int nDevChIdx = 0; nDevChIdx < oDevChList.count(); nDevChIdx++)
				{
					QString strDevCh = oDevChList.at(nDevChIdx);

					if(strDevCh.contains("="))
					{
						strBitIdx = strDevCh.split("=")[0];
						strBitIdx = strBitIdx.replace("bit", "");
						nBitIdx = strBitIdx.toInt();
						strBinIdx = strDevCh.split("=")[1];
						strBinIdx = strBinIdx.replace("bin", "");
						nBinIdx = strBinIdx.toInt();

						if(nBitIdx < 16)
						{
							if(nBinIdx > 0 && nBinIdx <= 8)
							{
								oChanInfo.nBiIdxSub[nBitIdx] = nBinIdx;//1~8
								oChanInfo.nValidBitSub |= 1 << nBitIdx; //0~15
							}
						}
					}
				}
			}
		}

		oChanInfo.strMap = "Other";
		otmt_6044.m_oChanList.append(oChanInfo);
		nOffset += oChanInfo.nLen;

		if((n + oChanInfo.nLen) >= 16)
		{
			nOffset += 2;//CRC
			n = oChanInfo.nChanLen2;
		}
		else
		{
			n += oChanInfo.nLen;
		}
	}

	QByteArray ba;
	Create6044ComByteArray(otmt_6044, ba);
//    qDebug()<<"SubBlock"<<ba.right(ba.size() - 12).toHex();
	otmt_6044.m_nTotalSizeSub = ba.size() - 12;//下载的报文头12字节
	data_6044Sub.append(otmt_6044);
}

//FPGA不支持发送报文长度是奇数的情况
void CIEC6044MngrBase::Create6044ComByteArray(tmt_ft3_6044 otmt_6044, QByteArray &m_oPackage)
{
	m_oPackage.clear();
	BOOL bFindDataPos = FALSE;
	m_oEncoderInfo.nACDataLen = 0;
	m_oEncoderInfo.nACDataPos = 0;
	m_oEncoderInfo.nSmpcntPos = 0;
	m_oEncoderInfo.nSmpcntType = otmt_6044.m_nSampleType;
	m_oEncoderInfo.nACDataEnd = 0;
	m_bACDataBegin = FALSE;
	BOOL bFindEnd = FALSE;
	long nFirstValue;
	m_oPackage.push_back(0x05);
	m_oPackage.push_back(0x64);

	for(int i = 0; i < otmt_6044.m_nChanNum; i++)
	{
		FT3ChanInfo  oChanInfo = otmt_6044.m_oChanList.at(i);
		nFirstValue = oChanInfo.nFirstValue;
		QString strMap = oChanInfo.strMap;

		if(strMap.compare("Other") == 0 ||
				strMap.compare("BOOLEAN") == 0 ||
				strMap.compare("Dbpos") == 0 ||
				strMap.compare("zero") == 0)
		{
			if(m_bACDataBegin && !bFindEnd)
			{
				bFindEnd = true;
				m_oEncoderInfo.nACDataEnd = m_oPackage.size();
			}

			if(oChanInfo.nLen == 1)
			{
				m_oPackage.push_back((unsigned char)(nFirstValue & 0xFF));
			}
			else  if(oChanInfo.nLen == 2)
			{
				m_oPackage.push_back((nFirstValue >> 8) & 0xFF);
				m_oPackage.push_back((nFirstValue & 0xFF));
			}
			else if(oChanInfo.nLen == 3)
			{
				m_oPackage.push_back((nFirstValue >> 16) & 0xFF);
				m_oPackage.push_back((nFirstValue >> 8) & 0xFF);
				m_oPackage.push_back((nFirstValue & 0xFF));
			}
			else if(oChanInfo.nLen == 4)
			{
				m_oPackage.push_back((nFirstValue >> 24) & 0xFF);
				m_oPackage.push_back((nFirstValue >> 16) & 0xFF);
				m_oPackage.push_back((nFirstValue >> 8) & 0xFF);
				m_oPackage.push_back((nFirstValue & 0xFF));
			}
		}
		else if(strMap.compare("SmpCnt") == 0)
		{
			if(m_bACDataBegin && !bFindEnd)
			{
				bFindEnd = true;
				m_oEncoderInfo.nACDataEnd = m_oPackage.size();
			}

			//cnt
			m_oEncoderInfo.nSmpcntPos = m_oPackage.size() + 1;

			if(oChanInfo.nLen == 1)
			{
				m_oPackage.push_back((char) 0x0);
			}
			else
			{
				m_oPackage.push_back((char) 0x0);
				m_oPackage.push_back((char) 0x0);
			}
		}
		else if(strMap.compare("t-delay") == 0)
		{
			if(m_bACDataBegin && !bFindEnd)
			{
				bFindEnd = true;
				m_oEncoderInfo.nACDataEnd = m_oPackage.size();
			}

			//delay
			if(oChanInfo.nLen == 1)
			{
				m_oPackage.push_back((unsigned char)(otmt_6044.m_nDelayTimeValue & 0xFF));
			}
			else
			{
				m_oPackage.push_back((otmt_6044.m_nDelayTimeValue >> 8) & 0xFF);
				m_oPackage.push_back((otmt_6044.m_nDelayTimeValue & 0xFF));
			}
		}
		else
		{
			long nMap = m_ChanMapID[strMap];

			if(nMap < 1)
			{
				CString strInfo = strMap;
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] IEC6044 MapID = %s"), strInfo.GetString());
			}

			//U,I
			m_bACDataBegin = true;

			if(!bFindEnd)
			{
				m_oEncoderInfo.nACDataLen += oChanInfo.nLen;
			}

			if(!bFindDataPos)
			{
				bFindDataPos = true;
				m_oEncoderInfo.nACDataPos = m_oPackage.size() + 1;
			}

			if(oChanInfo.nLen == 1)
			{
				m_oPackage.push_back((unsigned char)(nMap));
			}
			else
			{
				for(int i = 0; i < oChanInfo.nLen; i++)
				{
					m_oPackage.push_back((unsigned char)(nMap));
				}
			}
		}
	}

	int n = 0;
	QByteArray oPackage2;
	oPackage2.clear();
	oPackage2.append(m_oPackage.at(0));
	oPackage2.append(m_oPackage.at(1));

	for(int i = 2; i < m_oPackage.size(); i++)
	{
		if(n == 16)
		{
			//块之间CRC
			oPackage2.append(0xab);//取0xABBA,便于识别，最终数值由FPGA自动替换
			oPackage2.append(0xba);
			n = 0;
		}

		n++;
		oPackage2.append(m_oPackage.at(i));
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
	m_oPackage.clear();
	m_oPackage.swap(oPackage2);
	EnCoderHeader(otmt_6044, m_oPackage);
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
