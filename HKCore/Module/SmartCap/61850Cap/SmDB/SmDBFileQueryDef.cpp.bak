//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmFileDBGlobal.cpp

#include "stdafx.h"
#include "SmFileDBQueryDef.h"

CString Ep_GetCapDataText(CEpY4Data *pDeviceData, long nDataType)
{

	CString strText;

	if (nDataType == EP_DEVICE_DATA_YX)
	{
		if(pDeviceData->m_fValue < 0.1)
		{
			strText = _T("分");
		}
		else
		{
			strText = _T("合");
		}
	}
	else if (nDataType == EP_DEVICE_DATA_YC || nDataType == EP_DEVICE_DATA_YT)
	{
		strText.Format(_T("%.4f"), pDeviceData->m_fValue);
	}
	else if (nDataType == EP_DEVICE_DATA_TSYN)
	{
		strText.Format(_T("%.4f"), pDeviceData->m_fValue);
	}
	else
	{
		strText.Format(_T("%.4f"), pDeviceData->m_fValue);
	}

	return strText;
}


void CEpQueryEpCapDbBufferIndex::SortInc()
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
		AddTail((CEpCapDbBufferIndex*)pdwBuffer[nInex]);
	}

	delete pdwBuffer;
}

void CEpQueryEpCapDbBufferIndex::QuickSort(DWORD *pdwBuffer, long nLeft, long nRight)
{
	int i,j; 
	CEpCapDbBufferIndex *middle = NULL; 
	i = nLeft; 
	j = nRight; 

	middle = (CEpCapDbBufferIndex*)pdwBuffer[(nLeft+nRight)/2]; //求中间值 

	do
	{ 
		while(( *((CEpCapDbBufferIndex*)pdwBuffer[i]) < *middle) && (i<nRight))//从左扫描大于中值的数 
		{
			i++;   
		}

		while(( *((CEpCapDbBufferIndex*)pdwBuffer[j]) > *middle) && (j>nLeft))//从右扫描大于中值的数 
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
