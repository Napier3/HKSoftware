// Mr1200AttrDrawBase.cpp: implementation of the CMr1200AttrDrawBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mr1200AttrDrawBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMr1200AttrDrawBase::CMr1200AttrDrawBase()
{
}

CMr1200AttrDrawBase::~CMr1200AttrDrawBase()
{

}

//这里的计算暂时没有测试
BOOL CMr1200AttrDrawBase::CalCurrentDataPos(double dMax,double dMin)
{
	double dMaxTime = dMax;
	double dMinTime = dMin;
	
	if (dMinTime < m_oTimeAxisDraw.m_dOldTimeMin)
	{
		dMinTime = m_oTimeAxisDraw.m_dOldTimeMin;
	}
	
	if (dMaxTime > m_oTimeAxisDraw.m_dOldTimeMax)
	{
		dMaxTime = m_oTimeAxisDraw.m_dOldTimeMax;
	}
	
	//属性理论上工频50Hz
	/////////////计算当前绘图数据的范围,及取数间隔
	double dTimeLength = dMaxTime - dMinTime;
	long nNeedDataLength = (long)(dTimeLength * 50);//计算理论使用数据量
	long nDrawPoints = m_pPointBuffer->GetBufferLength();
	
	long nGap = nNeedDataLength / nDrawPoints ;
	long nRemain = nNeedDataLength % nDrawPoints ;
	long nBufferLen  = m_pRefBuffer->GetBufferLength();
	long nDataLength = m_pRefBuffer->GetDataLength();
	long nFillBeginPos = m_pRefBuffer->GetDataFillBeginPosition();
	
	if (nRemain > 0)
	{
		nGap ++;
	}
	
	if (nGap <1)
	{
		nGap = 1;
	}
	
	if (nGap > 100)
	{
		nGap = 100;
	}
	
	if (nNeedDataLength > nDrawPoints)
	{
		nNeedDataLength = nNeedDataLength / nGap * nGap;//计算实际使用的数据量，小于等于理论值
	}
	
	m_oDrawBufferPos.nGap = nGap;
	long nBegin = (long)(dMinTime * 50);//理论起点
	
	if (nBegin < 0)
	{
		nBegin = 0;
	}
	
	if (nDataLength < nBufferLen)//不循环
	{ 
		if (nBegin >= nBufferLen)
		{
			nBegin -= nBufferLen;
		}
		
		long nEnd   = nBegin + nNeedDataLength ;//理论终点
		
		if (nFillBeginPos >= nEnd) //有足够的数据
		{
			//			m_oDrawBufferPos.nBufLength	   = nNeedDataLength;
			SetDrawDataRange(nBegin,nBegin + nNeedDataLength - 1);
		}
		else //有部分数据
		{
			m_oDrawBufferPos.nBufLength	   = nFillBeginPos - nBegin;
			SetDrawDataRange(nBegin,nFillBeginPos  - 1);
		}
	}
	else//一定使用最新的数据
	{		
		nBegin += nFillBeginPos;
		if (nBegin >= nBufferLen) //说明都在新的区域
		{
			nBegin -= nBufferLen;
			long nEnd   = nBegin + nNeedDataLength ;//理论终点
			
			if (nEnd >= nFillBeginPos)
			{
				nEnd = nFillBeginPos;
			}
			
			//			m_oDrawBufferPos.nBufLength	   = nEnd - nBegin;
			SetDrawDataRange(nBegin,nEnd - 1);
			
		}
		else
		{
			long nEnd   = nBegin + nNeedDataLength ;//理论终点
			
			if (nEnd <= nBufferLen)
			{
				//				m_oDrawBufferPos.nBufLength	   = nEnd - nBegin;
				SetDrawDataRange(nBegin,nEnd - 1);
			} 
			else
			{
				nEnd -= nBufferLen;
				//				m_oDrawBufferPos.nBufLength	   = nNeedDataLength;
				SetDrawDataRange(nBegin,nBufferLen-1,long(0),nEnd-1);
			}
		}
		
	}
	
	CalXPos(nNeedDataLength / nGap);
	
	return TRUE;
}

void CMr1200AttrDrawBase::CalXPos(long nTotalPoints)
{
	double dMaxTime = 0;
	double dMinTime = 0;
	m_oTimeAxisDraw.m_oTimeAxis.GetMinMaxVal(&dMinTime, &dMaxTime, 0);
	double dCoef = 0;
	int nCenterX = 0;
	m_oTimeAxisDraw.m_oTimeAxis.GetAxisInterface(dCoef, nCenterX);
	double dTimePerPoint = (double)(dMaxTime - dMinTime) / nTotalPoints;
	dCoef *= dTimePerPoint;
	
	CPoint* pBuffer = m_pPointBuffer->GetBuffer();
	CPoint* pEnd = pBuffer + nTotalPoints;
	
	long nIndex = (long)(dMinTime * 50);
	
	while (pBuffer < pEnd)
	{
		pBuffer->x = (long)(nIndex * dCoef + nCenterX );
		pBuffer++;
		nIndex++;
	}
}
