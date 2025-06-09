//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDevice91.cpp  CCapDevice91


#include "stdafx.h"
#include "CapDevice91.h"

CCapDevice91::CCapDevice91()
{
	//初始化属性
//	m_nPriority = 0;
	m_dwVersion = 1;
//	m_dwAppID = 0;
	m_dwVID = 0;
	m_dwDataSet = 0;
	m_nAsduNum = 1;
	m_dwVersion = 1;
	m_dwLNName = 0;
	m_dwLDName = 0;
	m_dwStateWord = 0;
	m_dwINomPh = 1200;
	m_dwINomNeutral =100;
	m_dwUNomPh = 110;
	m_dwDelayTime = 0;
	m_dwSmpCnt = 0;

	//初始化成员变量

}

CCapDevice91::~CCapDevice91()
{
}

void CCapDevice91::InitDevice(CIecCfgDataBase *pIecCfgData)
{
	m_pIecCfgData = pIecCfgData;

	if(pIecCfgData == NULL)
	{
		return;
	}

	CIecCfg91Data* pCfgData91 = (CIecCfg91Data*)pIecCfgData;

	m_dwAppID = pCfgData91->m_dwAppID;

	m_nType = PROTOCOL_61850_TYPE_91;

	m_strDestAddress = pCfgData91->m_strDestAddress;
	m_strSrcAddress = pCfgData91->m_strSrcAddress;

	m_dwVID = pCfgData91->m_dwVID;
	m_dwVersion = pCfgData91->m_dwVersion;
	m_dwDataSet = pCfgData91->m_dwDataSet;
	m_dwLNName = pCfgData91->m_dwLNName;
	m_dwLDName = pCfgData91->m_dwLDName;
	m_dwINomPh = pCfgData91->m_fINom;
	m_dwINomNeutral = pCfgData91->m_fICenter;
	m_dwUNomPh = pCfgData91->m_fUNom;
	m_dwDelayTime = pCfgData91->m_dwDelayTime;
	m_dwSmpCnt = pCfgData91->m_nSampleRate;
	m_dwStateWord = pCfgData91->m_dwStateWord;

	CCapDeviceBase::InitDevice(pIecCfgData);
}

void CCapDevice91::GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas)
{
	CCapDeviceSmvCh *pSmvCh = NULL;

	for (int nIndex = 0;nIndex<GetCount();nIndex++)
	{
		pSmvCh = (CCapDeviceSmvCh *)GetAtIndex(nIndex);
		pSmvCh->m_wValue = pParseDatas->pDatas[nIndex].dwValue;
		pSmvCh->m_fValue = pSmvCh->m_dwValue * pSmvCh->m_fChRate;
	}
}
