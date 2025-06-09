#include "stdafx.h"
#include "CapDeviceRecord.h"

#include "../../../API/MathApi.h"
#include "../../../Record/RecordTest/CalFunctions.h"
#include "../../../../RelayTest/Module/SttGlobalDef.h"
#include "CapDeviceMngr.h"
#include "CapDeviceRcdCh.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCapDeviceRecord::CCapDeviceRecord()
{
	//初始化属性
	m_nChannelNum = BINARY_CHANNEL_MAX;
	m_nModulePos = 0;
	for (int i = 0;i < BINARY_CHANNEL_MAX;i++)
	{
		m_nChannelData[i] = 0;
	}
}

CCapDeviceRecord::~CCapDeviceRecord()
{
}

void CCapDeviceRecord::InitDevice(CIecCfgDataBase *pIecCfgData)
{
	CCapDeviceBase::InitDevice(pIecCfgData);
}

void CCapDeviceRecord::AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead,long nBufferLenth)
{
	long nChNum = GetCount();
	long nCurrBytePos = 0, nHasCrcLenth = 0;
	if (m_nChannelNum >= 64)
	{
		m_nChannelNum = 64;
	}
	long nMeasGear = 0;//不同档位计算系数不一样
	long nChIndex = 0;
	DWORD dwChValue = 0;
	float fValue;
	POS pos = GetHeadPosition();
	CCapDeviceRcdCh *pRcdCh = NULL;
	while (pos)
	{
		pRcdCh = (CCapDeviceRcdCh*)GetNext(pos);
		nMeasGear = pRcdCh->m_nMeasGear;
		dwChValue = GetByteChValue(pBuferHead, nCurrBytePos, nHasCrcLenth, 4);
		if (dwChValue >= 0x80000000)
		{
			dwChValue -= 0x80000000;
			dwChValue = dwChValue >> 16;
			fValue = dwChValue / 32767.0;
		}
		else
		{
			dwChValue = 0xFFFF0000 - dwChValue;
			dwChValue -= 0x80000000;
			dwChValue = dwChValue >> 16;
			fValue = dwChValue / 32767.0;
			fValue = 0 - fValue;
		}
		switch (nMeasGear)
		{
			case 4:
			{
				fValue = fValue / 2000.0;
			}
			break;
			case 3:
			{
				fValue = fValue / 380.5668;
			}
			break;
			case 2:
			{
				fValue = fValue / 54.4105;
			}
			break;
			case 1:
			{
		fValue = fValue / 5.982;
			}
			break;
			case 0:
			{
				fValue = fValue / (0.9995002 * 1.07);
			}
			break;
		}
		fValue = fValue*(505.1 * 2.048);
		pDatas->pDatas[nChIndex].dwValue = fValue / pRcdCh->m_fChRate;
		pRcdCh->m_dwValue = dwChValue;
		pRcdCh->m_fValue = fValue;
		nChIndex++;
	}
	pDatas->dwDatas = nChNum;
}

long CCapDeviceRecord::GetByteChValue(BYTE* pBuferHead,long &nCurrPos,long &nHasCrcLenth,long nChLenth)
{
	if ((nChLenth>4) ||(nChLenth<=0))
	{
		nCurrPos += nChLenth;
		return 0;
	}

	BYTE *pCurr = &pBuferHead[nCurrPos];
	BYTE *pEnd = pCurr + nChLenth;
	DWORD val = 0;

	while (pCurr < pEnd)
	{
		val = val << 8;
		val += *pCurr;
		pCurr++;
		nCurrPos++;
	}

	return val;
}

void CCapDeviceRecord::ClearAnalysisResultErrors()
{

}
