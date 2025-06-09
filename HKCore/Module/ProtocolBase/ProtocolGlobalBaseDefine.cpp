// ProtocolGlobalBaseDefine.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProtocolGlobalBaseDefine.h"
#include "EpCycleMemBufferMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


inline void Ep_GetCycleMemBuffer(CEpCycleMemBuffer *pBuffer, PEPBUFFERPOS pBufPos)
{
	Ep_InitEpBufferPos(pBufPos);
	pBufPos->dwBufferLen = pBuffer->GetDataLength();
	pBufPos->pBuffer = pBuffer->GetBuffer();
	pBufPos->nIndex = pBuffer->m_nCurrPos;
}

void Ep_TIME64_to_TIME64EX(EPTIME64 &tmSrc, EPTIME64EX &tmDest)
{
	WORD nTemp = 0;
	WORD nValue=0;

	//year=D63-D52
	nValue = tmSrc.tm[7];
	nValue = nValue << 4;
	nTemp = tmSrc.tm[6] >> 4;
	tmDest.wYear = nValue + nTemp;

	//month=D51-D48
	tmDest.wMonth = tmSrc.tm[6] & 0x0F;

	//day==D47-D43
	tmDest.wDay = tmSrc.tm[5] >> 3;

	//hour=D42-D38
	tmDest.wHour = ( (tmSrc.tm[5] & 0x07) << 2 ) + (tmSrc.tm[4] >> 6);

	//MINUTE=D37-D32
	tmDest.wMinute = (tmSrc.tm[4] & 0x3F);

	DWORD dwValue = *((DWORD*)(&tmSrc.tm[0]));

	//wMicrosecond
	tmDest.wMicrosecond = dwValue % 1000;

	//wMilliseconds
	dwValue -= tmDest.wMicrosecond;
	dwValue /= 1000;
	tmDest.wMilliseconds = dwValue % 1000;

	//second
	dwValue -= tmDest.wMilliseconds;
	dwValue /= 1000;
	tmDest.wSecond = dwValue % 100;
}

void Ep_TIME64EX_to_TIME64(EPTIME64EX &tmSrc, EPTIME64 &tmDest)
{
	tmDest.n64Time = 0;

	DWORD dValue=tmSrc.wMicrosecond + (tmSrc.wMilliseconds + tmSrc.wSecond*1000)*1000;
	*((DWORD*) &(tmDest.tm[0]) ) = dValue;

	//year=D63-D56  D55-D52
	WORD nValue = tmSrc.wYear;
	tmDest.tm[7] = (BYTE)(nValue >> 4);
	tmDest.tm[6] = (nValue & 0x0F) << 4;

	//month=D51-D48
	tmDest.tm[6] |= (tmSrc.wMonth & 0x0F);

	//day==D47-D43
	tmDest.tm[5] = tmSrc.wDay <<  3;

	//hour=D42-D38
	tmDest.tm[5] |= (tmSrc.wHour >> 2) & 0x07;
	tmDest.tm[4] = (tmSrc.wHour & 0x03) << 6;
	tmDest.tm[4] |= (tmSrc.wMinute & 0x3F);
}

void Ep_GetLocalTm_TIME64EX(EPTIME64EX &tmDest)
{
	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);
	Ep_SYSTEMTIME_to_TIME64EX(tmSys, tmDest);
}

void Ep_TIME64EX_to_SYSTEMTIME(EPTIME64EX &tmSrc, SYSTEMTIME &tmDest)
{
	tmDest.wYear = tmSrc.wYear;
	tmDest.wMonth = tmSrc.wMonth;
	tmDest.wDay = tmSrc.wDay;
	tmDest.wHour = tmSrc.wHour;
	tmDest.wMinute = tmSrc.wMinute;
	tmDest.wSecond = tmSrc.wSecond;
	tmDest.wMilliseconds = tmSrc.wMilliseconds;
}

void Ep_SYSTEMTIME_to_TIME64EX(SYSTEMTIME &tmSrc, EPTIME64EX &tmDest)
{
	tmDest.wYear = tmSrc.wYear;
	tmDest.wMonth = tmSrc.wMonth;
	tmDest.wDay = tmSrc.wDay;
	tmDest.wHour = tmSrc.wHour;
	tmDest.wMinute = tmSrc.wMinute;
	tmDest.wSecond = tmSrc.wSecond;
	tmDest.wMilliseconds = tmSrc.wMilliseconds;
	tmDest.wMicrosecond = 0;
}


//////////////////////////////////////////////////////////////////////////
void CEpDeviceDatas::AddName(const CString &strName, long nID)
{
	m_astrName.Add(strName);
	m_adwIndex.Add(nID);
}

void CEpDeviceDatas::RemoveName(long nIndex)
{
	m_astrName.RemoveAt(nIndex);
	m_adwIndex.RemoveAt(nIndex);
}

CString CEpDeviceDatas::GetName(long nID)
{
	long nIndex = 0;
	long nCount = m_adwIndex.GetCount();

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		if (nID == m_adwIndex.GetAt(nIndex))
		{
			return m_astrName.GetAt(nIndex);
		}
	}

	return _T("---");
}

void CEpDeviceDatas::SortDesc()
{
}

void CEpDeviceDatas::SortInc()
{
	long nCount = GetCount();

	if (nCount == 0)
	{
		return;
	}

	DWORD *pdwBuffer = new DWORD[nCount];
	GetAllDataAddr(pdwBuffer);
	
	QuickSort(pdwBuffer, 0, nCount - 1);
	RemoveAll();
	
	for (long nInex=0; nInex<nCount; nInex++)
	{
		AddTail((CEpY4Data*)pdwBuffer[nInex]);
	}

	delete pdwBuffer;
}


void CEpDeviceDatas::QuickSort(DWORD *pdwBuffer, long nLeft, long nRight)
{
	int i,j; 
	CEpY4Data *middle = NULL; 
	i = nLeft; 
	j = nRight; 

	middle = (CEpY4Data*)pdwBuffer[(nLeft+nRight)/2]; //求中间值 

	if (middle == NULL)
	{
		return;
	}

	do
	{ 
		while(( *((CEpY4Data*)pdwBuffer[i]) < *middle) && (i<nRight))//从左扫描大于中值的数 
		{
			i++;   
		}

		while(( *((CEpY4Data*)pdwBuffer[j]) > *middle) && (j>nLeft))//从右扫描大于中值的数 
		{
			j--;
		}

		if(i<=j)//找到了一对值 
		{ 
			//交换 
			DWORD dwVal = pdwBuffer[i]; 
			pdwBuffer[i] = pdwBuffer[j]; 
			pdwBuffer[j] = dwVal; 
			i++; 
			j--; 
		} 
	}while(i<=j);//如果两边扫描的下标交错，就停止（完成一次） 

	//当左边部分有值(nLeft<j)，递归左半边 
	if(nLeft<j) 
	{
		QuickSort(pdwBuffer,nLeft,j); 
	}

	//当右边部分有值(nRight>i)，递归右半边 
	if(nRight>i) 
	{
		QuickSort(pdwBuffer,i,nRight); 
	}
}

//////////////////////////////////////////////////////////////////////////
void CEpDeviceDatasMngr::AddDeviceData(CEpY4Data *pData,WORD nDeviceDataType, EPTIME64 &tm)
{
	CEpDeviceDatas *pDatas = FindByItemIndex(pData->m_nDataAddr);

	if (nDeviceDataType == EP_DEVICE_DATA_YC)
	{
		pData->m_tm = tm;
	}
	else
	{
		if (pData->m_tm.n64Time == 0)
		{
			pData->m_tm = tm;
		}
	}

	if (pDatas != NULL)
	{
		pDatas->AddTail(pData);
	}
	else
	{
		pDatas = new CEpDeviceDatas();
		pDatas->m_nDeviceDataType = nDeviceDataType;
		AddTail(pDatas);
		pDatas->AddTail(pData);
		pDatas->m_nItemIndex = pData->m_nDataAddr;
	}
}

void CEpDeviceDatasMngr::AddData(EPTIME64 &tm, DWORD nProtocol, DWORD nDataAddr, float fValue)
{
	CEpDeviceDatas *pDatas = FindByItemIndex(nDataAddr);
	CEpY4Data *pData = new CEpY4Data();
	pData->m_fValue = fValue;
	pData->m_nDataAddr = nDataAddr;
	pData->m_tm = tm;

	if (pDatas != NULL)
	{
		pDatas->AddTail(pData);
	}
	else
	{
		pDatas = new CEpDeviceDatas();
		pDatas->m_nDeviceDataType = Ep_GetProtocol_ProtoType_Type(nProtocol);
		AddTail(pDatas);
		pDatas->AddTail(pData);
		pDatas->m_nItemIndex = pData->m_nDataAddr;
	}
}

void CEpDeviceDatasMngr::AddDeviceDatas(BYTE *pBuffer, long nLength, EPTIME64 &tm)
{
	long nCount = *((long*)pBuffer);
	long nIndex = 0;
	BYTE *pTemp = pBuffer;
	pTemp += sizeof(long);

	WORD nDataType = *((WORD*)pBuffer);
	pTemp +=  sizeof(WORD);

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		CEpY4Data *pDate = new CEpY4Data();
		long nLen = pDate->ReadFromBuffer(pTemp);
		pTemp += nLen;

		AddDeviceData(pDate, nDataType, tm);
	}
}

void CEpDeviceDatasMngr::AddDeviceDatas(CEpDeviceDatas *pDatas, EPTIME64 &tm)
{
	POS pos = pDatas->GetHeadPosition();
	CEpY4Data *pData = NULL;

	while (pos != NULL)
	{
		pData = pDatas->GetNext(pos);
		AddDeviceData(pData, pDatas->m_nDeviceDataType, tm);
	}

	pDatas->RemoveAll();
}

