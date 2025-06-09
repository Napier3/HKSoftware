// ComtradeAnalogData.cpp: implementation of the CComtradeAnalogData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComtradeAnalogData.h"

#include "../Algorithm/AlgorithmAPI.h"
#include "ComtradeMngr.h"
#include "../../API/MathApi.h"
#include "../../API/GlobalConfigApi.h"
#include "../../OSInterface/OSInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComtradeAnalogData::CComtradeAnalogData()
{
	m_strUnit		  = "V";
	m_dCoefValue	  = 0;	
	m_dZeroValue	  = 0;
	m_dTimeSkew		  = 0;	
	m_nMin			  = -32767;		
	m_nMax			  = 32767;		
	m_dPrimaryValue	  = 1;		
	m_dSecondaryValue = 1;
	m_cPSType		  =	'S';
	m_nMinCal = 0;
	m_nMaxCal = 0;
	m_dBeginAng_SpecialSmpRate = 0;
	m_bInPhase_SpecialSmpRate = 1;
	m_dCoefValueBK = 1.0f;
	m_dZeroValueBK = 0.0f;
}

CComtradeAnalogData::~CComtradeAnalogData()
{
	
}

double CComtradeAnalogData::GetRange()
{
	double dRange = 0;
	
// 	if (m_dSecondaryValue > 0.0001)
// 	{
// 		if (m_dSecondaryValue < 0.00001)
// 		{
// 			dRange = m_dPrimaryValue;
// 		}
// 		else
// 		{
// 			dRange = m_dPrimaryValue / m_dSecondaryValue;
// 		}
// 	}

	if (dRange <= 0.0001)
	{
		double dMin = m_nMinCal * m_dCoefValue + m_dZeroValue;
		double dMax = m_nMaxCal * m_dCoefValue + m_dZeroValue;
		dMax = fabs(dMax);
		dMin = fabs(dMin);

		dRange = max(dMin, dMax);
	}

	return dRange;
}

void CComtradeAnalogData::CalMinMaxValue(long nPoints)
{
	CalMinMaxValue2(nPoints);

	double dRange = GetRange();
	double dCoefCal = dRange / 30000.0;

	if (dCoefCal < 0.001)
	{
		dCoefCal = 0.001;
	}

	if (dCoefCal > fabs(m_dCoefValue))
	{
		return;
	}

	AdjustZeroValue(nPoints, dCoefCal);

	CalMinMaxValue2(nPoints);
}

void CComtradeAnalogData::CalMinMaxValue2(long nPoints)
{
	if (nPoints <= 0)
	{//2021-2-18  lijunqing
		nPoints = m_nTotalPoints;
	}

	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	long nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;

	if (pComtradeFile != NULL)
	{
		nDataFileType = pComtradeFile->m_nDataFileType;
	}

	m_nMaxCal = -32767;
	m_nMinCal = 32767;

	if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
	{
		short* pEnd = (short*)m_pnAttachBuffer + nPoints;
		short* pCurr = (short*)m_pnAttachBuffer;

		while (pCurr < pEnd)
		{
			if (m_nMinCal > *pCurr)
			{
				m_nMinCal = *pCurr;
			}

			if (m_nMaxCal < *pCurr)
			{
				m_nMaxCal = *pCurr;
			}

			pCurr++;
		}
	} 
	else
	{
		int* pEnd = ((int*)m_pnAttachBuffer) + nPoints;
		int* pCurr = (int*)m_pnAttachBuffer;

		while (pCurr < pEnd)
		{
			if (m_nMinCal > *pCurr)
			{
				m_nMinCal = *pCurr;
			}

			if (m_nMaxCal < *pCurr)
			{
				m_nMaxCal = *pCurr;
			}

			pCurr++;
		}
	}
}

double CComtradeAnalogData::GetUnitRadio()
{
	CString strCurUnit = m_strUnit;
	strCurUnit.MakeLower();

	if ((strCurUnit == _T("v"))||(strCurUnit == _T("a")))
	{
		return 1;
	}
	else if ((strCurUnit == _T("kv"))||(strCurUnit == _T("ka")))//kV��kA
	{
		return 1000;
	}
	else if ((strCurUnit == _T("mv"))||(strCurUnit == _T("ma")))//mA��mV
	{
		return 0.001;
	}
	else
	{
		return 1;
	}
}

BOOL CComtradeAnalogData::IsChU0()
{
	CString strID;
	strID = m_strID;
	strID.MakeUpper();

	if (strID.Find("U0") != -1)
	{
		return TRUE;
	}

	if (strID.Find("UZ") != -1)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CComtradeAnalogData::IsChI0()
{
	CString strID;
	strID = m_strID;
	strID.MakeUpper();

	if (strID.Find("I0") != -1)
	{
		return TRUE;
	}

	if (strID.Find("IZ") != -1)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CComtradeAnalogData::GetMaxMinValue(long nPtBeginIndex, long nPointNum, double &dMaxValue, double &dMinValue)
{
	long nMaxCount = nPtBeginIndex + nPointNum;

	if (nMaxCount > GetMemBuffer_UShortNum())
	{
		return FALSE;
	}

	double dValue = 0.0f;

	for (int nIndex = nPtBeginIndex; nIndex < nMaxCount;nIndex++)
	{
		dValue = GetUShortPointValueDouble(nIndex);

		if (dValue>dMaxValue)
		{
			dMaxValue = dValue;
		}

		if (dValue<dMinValue)
		{
			dMinValue = dValue;
		}
	}

	return TRUE;
}

void CComtradeAnalogData::UpdateCoef_SpecialSmpRate(double dMaxValue)
{
	dMaxValue *= SQRT2;
//	double dMin = m_nMinCal * m_dCoefValue + m_dZeroValue;
	double dTmpValue = dMaxValue - m_dZeroValue;
	double dTmpValue2 = dTmpValue / m_dCoefValue;

	if (dTmpValue2>32767)
	{
		AdjustCoefValue(m_nTotalPoints, m_dCoefValue*SQRT2);
	}
}

long CComtradeAnalogData::GetChCurrVolIndex()
{
	long nChIndex = 0;

	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();

	if (pComtradeFile == NULL)
	{
		return nChIndex;
	}

	BOOL bIsAnalogU = IsAnalogU();
	long nFindIndex = 0;
	CComtradeAnalogData *pComtradeAnalogData = NULL;
	CExBaseList* pAnalogs = pComtradeFile->GetAnalogs();
	POS pos = pAnalogs->GetHeadPosition();

	while(pos)
	{
		pComtradeAnalogData = (CComtradeAnalogData*)pAnalogs->GetNext(pos);

		if (bIsAnalogU != pComtradeAnalogData->IsAnalogU())
		{
			continue;
		}

		nFindIndex++;

		if (pComtradeAnalogData == this)
		{
			nChIndex = nFindIndex;
			break;
		}
	}

	return nChIndex;
}

long CComtradeAnalogData::GetValues_Double(double *pdFftCalPoint,long nPointNum,long nBeginPos)
{
	if (nBeginPos>= m_nTotalPoints)
	{
		return 0;
	}

	long nCurrLenth = nPointNum;

	if ((m_nTotalPoints-nBeginPos)<nPointNum)
	{
		nCurrLenth = m_nTotalPoints-nBeginPos;
	}

	long *pnAttachBufferValue = (long *)m_pnAttachBuffer;

	for (int nIndex = 0;nIndex<nCurrLenth;nIndex++)
	{
		pdFftCalPoint[nIndex] = GetUShortPointValueDouble(nBeginPos + nIndex);//m_dCoefValue*(long)pnAttachBufferValue[]+m_dZeroValue;
	}

	return nCurrLenth;
}

double CComtradeAnalogData::GetUShortPointValueDouble(long nPointIndex)
{
	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	long nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;

	if (pComtradeFile != NULL)
	{
		nDataFileType = pComtradeFile->m_nDataFileType;
	}

	ASSERT(m_pnAttachBuffer);
	double dValue = 0.0f;

	if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
	{
		dValue = m_dCoefValue*(short)m_pnAttachBuffer[nPointIndex]+m_dZeroValue;
	} 
	else
	{
		int *pnAttachBufferValue = (int *)m_pnAttachBuffer;
		dValue = m_dCoefValue*(int)pnAttachBufferValue[nPointIndex]+m_dZeroValue;
	}
//	ASSERT(dValue<200);
	return dValue;
}

void CComtradeAnalogData::AdjustZeroValue(long nPoints, double dCoefCal)
{
	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	long nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;

	if (pComtradeFile != NULL)
	{
		nDataFileType = pComtradeFile->m_nDataFileType;
	}

	m_dZeroValueBK = m_dZeroValue;
	m_dCoefValueBK = m_dCoefValue;
	double dValue = 0;

	if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
	{
		short* pEnd = (short*)m_pnAttachBuffer + nPoints;
		short* pCurr = (short*)m_pnAttachBuffer;

		while (pCurr < pEnd)
		{
			dValue = ((short)*pCurr) * m_dCoefValue + m_dZeroValue;
			dValue = dValue / dCoefCal;
			*((short*)pCurr) = (short)dValue;

			if (dValue - *((short*)pCurr) > 0.5)  //zhouhj 20200916 ���Ǿ��ȿ���
			{
				*((short*)pCurr) += 1;
			}
			else if (dValue - *((short*)pCurr) < -0.5)
			{
				*((short*)pCurr) -= 1;
			}

			pCurr++;
		}
	} 
	else
	{
		int *pnAttachBufferValue = (int *)m_pnAttachBuffer;
		int* pEnd = pnAttachBufferValue + nPoints;
		int* pCurr = pnAttachBufferValue;

		while (pCurr < pEnd)
		{
			dValue = ((int)*pCurr) * m_dCoefValue + m_dZeroValue;
			dValue = dValue / dCoefCal;
			*(pCurr) = (int)dValue;

			if (dValue - *pCurr > 0.5)  //zhouhj 20200916 ���Ǿ��ȿ���
			{
				*pCurr += 1;
			}
			else if (dValue - *pCurr < -0.5)
			{
				*pCurr -= 1;
			}

			pCurr++;
		}
	}

	m_dZeroValue = 0;
	m_dCoefValue = dCoefCal;
}

void CComtradeAnalogData::AdjustCoefValue(long nPoints, double dNewCoefCal)
{
	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	long nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;

	if (pComtradeFile != NULL)
	{
		nDataFileType = pComtradeFile->m_nDataFileType;
	}

	m_dZeroValueBK = m_dZeroValue;
	m_dCoefValueBK = m_dCoefValue;
	double dValue = 0;

	if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
	{
		short* pEnd = (short*)m_pnAttachBuffer + nPoints;
		short* pCurr = (short*)m_pnAttachBuffer;

		while (pCurr < pEnd)
		{
			dValue = ((short)*pCurr) * m_dCoefValue;
			dValue = dValue / dNewCoefCal;
			*((short*)pCurr) = (short)dValue;

			if (dValue - *((short*)pCurr) > 0.5)  //zhouhj 20200916 ���Ǿ��ȿ���
			{
				*((short*)pCurr) += 1;
			}
			else if (dValue - *((short*)pCurr) < -0.5)
			{
				*((short*)pCurr) -= 1;
			}

			pCurr++;
		}
	} 
	else
	{
		int *pnAttachBufferValue = (int *)m_pnAttachBuffer;
		int* pEnd = pnAttachBufferValue + nPoints;
		int* pCurr = pnAttachBufferValue;

		while (pCurr < pEnd)
		{
			dValue = (*pCurr) * m_dCoefValue;
			dValue = dValue / dNewCoefCal;
			*pCurr = (int)dValue;

			if (dValue - *pCurr > 0.5)  //zhouhj 20200916 ���Ǿ��ȿ���
			{
				*pCurr += 1;
			}
			else if (dValue - *pCurr < -0.5)
			{
				*pCurr -= 1;
			}

			pCurr++;
		}
	}

	m_dCoefValue = dNewCoefCal;
}

// BOOL CComtradeAnalogData::DealWithStartWave(const double &dSmpRate,const double &dCurFreq,const long &nCycleNum)
// {
// 	return TRUE;
// }

BOOL CComtradeAnalogData::Copy_AddSlowlyRising(float fSmpRate,long nAddRisingPoints,long nAddStartSteadyPoints,CComtradeDataBase *pDstData,BOOL bDealStartCircle)
{
	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	long nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;

	if (pComtradeFile != NULL)
	{
		nDataFileType = pComtradeFile->m_nDataFileType;
	}

	int *pnAttachBufferValue = (int *)m_pnAttachBuffer;
	CComtradeAnalogData *pDstAnalogData = (CComtradeAnalogData*)pDstData;
	CopyOwn(pDstData);
	double dAmp = 0,dAng = 0 ,dDcValue = 0;
	long nStartPointIndex = 2*(fSmpRate/50);//��ʼ�ܲ��ĵ�ţ��ĵ�֮ǰ�ĵ�ɾ��

	if (!bDealStartCircle)//���������ʼ�����ܲ����ݣ��򽫿�ʼ������Ϊ0
	{
		nStartPointIndex = 0;
	}

	GetWaveCircleAmpAng(nStartPointIndex,fSmpRate,50,dAmp,dAng,dDcValue);//��ȡ����һ�������λ����Чֵ
	double dSecondTotalAng = 2*_PI*50;//ÿ���ӵ�����λֵ
	double dTotalTime = (nAddRisingPoints+nAddStartSteadyPoints+nStartPointIndex)/fSmpRate;
	double dGapTime = 1/fSmpRate;
	double dTmp1 = 0,dTmp2 = 0;
	long nRisingSineWaveNum = (50*nAddRisingPoints/fSmpRate+1);//��Ҫ�������ܲ���
	double dSepValue = dAmp/nRisingSineWaveNum;
	double dCurValue = dSepValue;
	long nTotalPoints = nAddRisingPoints+nAddStartSteadyPoints+nStartPointIndex;
	double dOldAngle = 0;

	for (int nIndex = 0;nIndex<nTotalPoints;nIndex++)//��������������ǰ��Ҫ��ӵĵ�ֵ
	{
	
		dTmp1 = dAng - (dTotalTime-dGapTime*nIndex)*dSecondTotalAng;//��ȡ��ǰ�����λֵ

		while(dTmp1 <0)//����λֵ����Ϊ����
		{
			dTmp1 += 2*_PI;
		}

		while(dTmp1 > 2*_PI)//����λֵ����Ϊ����
		{
			dTmp1 -= 2*_PI;
		}

		if (dOldAngle>dTmp1)//�����һ�νǶȴ��ڱ��εĽǶȣ���˵������һ���ܲ��ˣ����ֵ����
		{
			dCurValue += dSepValue;
		}

		if (dCurValue >= dAmp)//�����ǰ�ܲ�����Чֵ����ԭʼ���ε�һ���ܲ�����Чֵ����ʹ�õ�һ���ܲ�����Чֵ����Ϊ����Чֵ�ǻ��������ģ������ϲ�Ӧ�ô��ڵ�һ���ܲ���Чֵ
		{
			dCurValue = dAmp;
		}

		dOldAngle = dTmp1;
		dTmp2 = SQRT2*dCurValue*sin(dTmp1) + dDcValue;

		if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
		{
			pDstAnalogData->m_pnAttachBuffer[nIndex] = DoubleToUShortPointValue((dTmp2-m_dZeroValue)/m_dCoefValue);
		} 
		else
		{
			
			pnAttachBufferValue[nIndex] = static_cast<int>(DoubleToLongPointValue((dTmp2-m_dZeroValue)/m_dCoefValue));
		}
		

// 		if ((dTmp2>0)&&(pDstAnalogData->m_pnAttachBuffer[nIndex]>32767))
// 		{
// 			pDstAnalogData->m_pnAttachBuffer[nIndex] = 32767;
// 		}
	}

	if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
	{
		for (long nPtIndex = nStartPointIndex;nPtIndex<m_nTotalPoints;nPtIndex++)
		{
			pDstAnalogData->m_pnAttachBuffer[nAddRisingPoints + nAddStartSteadyPoints + nPtIndex] = m_pnAttachBuffer[nPtIndex];
		}
	} 
	else
	{
		for (long nPtIndex = nStartPointIndex;nPtIndex<m_nTotalPoints;nPtIndex++)
		{
			pnAttachBufferValue[nAddRisingPoints + nAddStartSteadyPoints + nPtIndex] = pnAttachBufferValue[nPtIndex];
		}
	}

	pDstAnalogData->m_nTotalPoints = m_nTotalPoints + nAddRisingPoints + nAddStartSteadyPoints;
	return TRUE;
}

BOOL CComtradeAnalogData::SetSteadySineWave(float fSmpRate,long nStartPointIndex,long nSetSteadyPoints)
{
	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	long nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;

	if (pComtradeFile != NULL)
	{
		nDataFileType = pComtradeFile->m_nDataFileType;
	}

	int *pnAttachBufferValue = (int *)m_pnAttachBuffer;
	double dAmp = 0,dAng = 0 ,dDcValue = 0;
	GetWaveCircleAmpAng(nStartPointIndex,fSmpRate,50,dAmp,dAng,dDcValue);//��ȡ����һ�������λ����Чֵ
	double dSecondTotalAng = 2*_PI*50;//ÿ���ӵ�����λֵ
	double dGapTime = 1/fSmpRate;
	double dTmp1 = 0,dTmp2 = 0;

	for (int nIndex = 0;nIndex<nSetSteadyPoints;nIndex++)//��������������ǰ��Ҫ��ӵĵ�ֵ
	{
		dTmp1 = (dGapTime*nIndex)*dSecondTotalAng;//��ȡ��ǰ�����λֵ

		while(dTmp1 <0)//����λֵ����Ϊ����
		{
			dTmp1 += 2*_PI;
		}

		while(dTmp1 > 2*_PI)//����λֵ����Ϊ����
		{
			dTmp1 -= 2*_PI;
		}

		dTmp2 = SQRT2*dAmp*sin(dTmp1) + dDcValue;

		if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
		{
			m_pnAttachBuffer[nStartPointIndex+nIndex] = DoubleToUShortPointValue((dTmp2-m_dZeroValue)/m_dCoefValue);
		} 
		else
		{
			pnAttachBufferValue[nStartPointIndex+nIndex] = static_cast<int>(DoubleToLongPointValue((dTmp2-m_dZeroValue)/m_dCoefValue));
		}
	}

	return TRUE;
}

long CComtradeAnalogData::InsertBySampleRate(float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount,double dDstSmpRate,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime)
{
	if (pDstData->GetClassID() != CMTRDCLASSID_ANALOG)
	{
		return 0;
	}

	CComtradeAnalogData *pDstAnalogData = (CComtradeAnalogData*)pDstData;
	CopyOwn(pDstData);

	BOOL bIsFirstSmpRate = TRUE;// ��ֹ��һ��������,��������Ϊ0�����
	long nSrcBeginPoint = 0;
	long nSrcEndPoint = 0;
	long nDstBeginPoint = 0;
	double dSrcBeginPointTime = 0;
//	double dDstBeginPointTime = 0;
	double dSrcGap = 0;
	double dDstGap = 1/dDstSmpRate;
	double dCurFreq = 50.0f;
	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();

	if (pComtradeFile != NULL)
	{
		dCurFreq = pComtradeFile->m_dFreq;
	}

	for (int nRateIndex = 0;nRateIndex<nSrcSamAmount;nRateIndex++)
	{
		if (pnSrcDataPoints[nRateIndex]<=0)//������������,��������Ϊ0�Ĳ�����
		{
			continue;
		}

		dSrcGap = 1/pdSrcSamRate[nRateIndex];

		if (bIsFirstSmpRate)
		{
			nSrcBeginPoint = 0;
			nSrcEndPoint = (pnSrcDataPoints[nRateIndex]-1);//��һ����Ч������,ȥ����һ����
//			InsertBySampleRate(nSrcBeginPoint,nSrcEndPoint ,nDstBeginPoint,dSrcBeginPointTime,dSrcGap,dDstGap,pDstData);
			bIsFirstSmpRate = FALSE;
		} 
		else
		{
			nSrcEndPoint += pnSrcDataPoints[nRateIndex];
		}

		if ((fabs(dCurFreq*2-pdSrcSamRate[nRateIndex])<0.0001)||(fabs(dCurFreq-pdSrcSamRate[nRateIndex])<0.0001))//����2����Ƶ�Ĳ�����,���仹ԭΪ���Ҳ�
		{
			double dCurPointAng = GetCurPointAng(pdSrcSamRate,pnSrcDataPoints,nSrcSamAmount,dCurFreq,nSrcBeginPoint);
			m_dBeginAng_SpecialSmpRate = dCurPointAng;
			InsertBySampleRate_SteadyState(dCurPointAng,dCurFreq,nSrcBeginPoint,nSrcEndPoint ,nDstBeginPoint,dSrcBeginPointTime,dSrcGap,dDstGap,pDstData,dDstBeginOffsetTime);
		} 
		else
		{
			InsertBySampleRate(nSrcBeginPoint,nSrcEndPoint ,nDstBeginPoint,dSrcBeginPointTime,dSrcGap,dDstGap,pDstData,dDstBeginOffsetTime);
		}

		nSrcBeginPoint = nSrcEndPoint;
	}

	pDstData->m_nTotalPoints = nDstBeginPoint;
	return nDstBeginPoint;
}

long CComtradeAnalogData::InsertBySampleRate_DoubleBuff(CMemBuffer_Double &oDoubleBuff,float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount,double dDstSmpRate,const double &dDstBeginOffsetTime)
{
	BOOL bIsFirstSmpRate = TRUE;// ��ֹ��һ��������,��������Ϊ0�����
	long nSrcBeginPoint = 0;
	long nSrcEndPoint = 0;
	long nDstBeginPoint = 0;
	double dSrcBeginPointTime = 0;
	double dSrcGap = 0;
	double dDstGap = 1/dDstSmpRate;
	double dCurFreq = 50.0f;
	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	double *pdDoubleBuff = oDoubleBuff.GetBuffer();

	if (pComtradeFile != NULL)
	{
		dCurFreq = pComtradeFile->m_dFreq;
	}

	for (int nRateIndex = 0;nRateIndex<nSrcSamAmount;nRateIndex++)
	{
		if (pnSrcDataPoints[nRateIndex]<=0)//������������,��������Ϊ0�Ĳ�����
		{
			continue;
		}

		dSrcGap = 1/pdSrcSamRate[nRateIndex];

		if (bIsFirstSmpRate)
		{
			nSrcBeginPoint = 0;
			nSrcEndPoint = (pnSrcDataPoints[nRateIndex]-1);//��һ����Ч������,ȥ����һ����
			bIsFirstSmpRate = FALSE;
		} 
		else
		{
			nSrcEndPoint += pnSrcDataPoints[nRateIndex];
		}

		if ((fabs(dCurFreq*2-pdSrcSamRate[nRateIndex])<0.0001)||(fabs(dCurFreq-pdSrcSamRate[nRateIndex])<0.0001))//����2����Ƶ�Ĳ�����,���仹ԭΪ���Ҳ�
		{
			double dCurPointAng = GetCurPointAng(pdSrcSamRate,pnSrcDataPoints,nSrcSamAmount,dCurFreq,nSrcBeginPoint);
			m_dBeginAng_SpecialSmpRate = dCurPointAng;
			InsertBySampleRate_SteadyState_Double(&pdDoubleBuff,dCurPointAng,dCurFreq,nSrcBeginPoint,nSrcEndPoint ,nDstBeginPoint,dSrcBeginPointTime,dSrcGap,dDstGap,dDstBeginOffsetTime);
		} 
		else
		{
			InsertBySampleRate_Double(&pdDoubleBuff,nSrcBeginPoint,nSrcEndPoint ,nDstBeginPoint,dSrcBeginPointTime,dSrcGap,dDstGap,dDstBeginOffsetTime);
		}

		nSrcBeginPoint = nSrcEndPoint;
	}

	ASSERT(oDoubleBuff.GetBufferLength()>= nDstBeginPoint);
	oDoubleBuff.SetDataLength(nDstBeginPoint);
	return nDstBeginPoint;
}

double CComtradeAnalogData::GetCurPointAng(float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount,const double &dCurFreq,const long &nCurPointIndex)
{
	double dCurSampRate = 0;
	double dCurTotalPointNum = 0;

	for (int nIndex = 0;nIndex<nSrcSamAmount;nIndex++)
	{
		if (pnSrcDataPoints[nIndex] <=0)
		{
			continue;
		}

		dCurTotalPointNum += pnSrcDataPoints[nIndex];

		if (dCurTotalPointNum>= nCurPointIndex)
		{
			dCurSampRate = pdSrcSamRate[nIndex];
			break;
		}
	}

	double dCurPointAng = 0;
	long nCalTotalPoints = dCurSampRate/dCurFreq + 2;//ʹ��һ���ܲ����2���������ֵ����Сֵ
	long nBeginPointIndex = nCurPointIndex-nCalTotalPoints;

	if (nBeginPointIndex<0)
	{
		dCurPointAng = m_dBeginAng_SpecialSmpRate;
		
		if (!m_bInPhase_SpecialSmpRate)
		{
			dCurPointAng += _PI;
		}

		return dCurPointAng;
	}

	double dMaxValue = 0,dMinValue = 0 ,dCurValue = 0,dCalPointValue = GetUShortPointValueDouble(nCurPointIndex);
	long nMaxPointIndex = 0,nMinPointIndex = 0;

	for (long nPointIndex = nBeginPointIndex;nPointIndex<=nCurPointIndex;nPointIndex++)
	{
		dCurValue = GetUShortPointValueDouble(nPointIndex); /*m_dCoefValue*(short)m_pnAttachBuffer[nPointIndex]+m_dZeroValue*/;

		if (dCurValue>dMaxValue)
		{
			dMaxValue = dCurValue;
			nMaxPointIndex = nPointIndex;
		}

		if (dCurValue<dMinValue)
		{
			dMinValue = dCurValue;
			nMinPointIndex = nPointIndex;
		}
	}

	double dTmp1 = max(dMaxValue,fabs(dMinValue));
	double dTmp2 = 0.000f;

	if (dTmp1>0.000001f)
	{
		dTmp2 = dCalPointValue/dTmp1;
	}

	dCurPointAng = acos(dTmp2);

	if (nMaxPointIndex<nMinPointIndex)//�����ǰ������Сֵ�ȽϽ�,��Ƕ�ȡ��
	{
		dCurPointAng = -dCurPointAng;
	} 

	dCurPointAng += _PI/2;//����Ϊ���Ҳ��Ƕ�
	return dCurPointAng;
}

BOOL CComtradeAnalogData::GetWaveCircleAmpAng(const long &nStartPointIndex,const double &dSmpRate,const double &dCurFreq,double &dAmp,double &dCurPointAng ,double &dDC_Value)
{
	long nCalTotalPoints = nStartPointIndex + dSmpRate/dCurFreq +5;//ʹ��һ���ܲ����2���������ֵ����Сֵ
	double dMaxValue = 0,dMinValue = 0 ,dCurValue = 0,dCalPointValue = GetUShortPointValueDouble(nStartPointIndex);
	long nMaxPointIndex = nStartPointIndex,nMinPointIndex = nStartPointIndex;
	dMaxValue = dCalPointValue;
	dMinValue = dMaxValue;

	for (long nPointIndex = nStartPointIndex;nPointIndex<nCalTotalPoints;nPointIndex++)
	{
		dCurValue = GetUShortPointValueDouble(nPointIndex); /*m_dCoefValue*(short)m_pnAttachBuffer[nPointIndex]+m_dZeroValue*/;

		if (dCurValue>dMaxValue)
		{
			dMaxValue = dCurValue;
			nMaxPointIndex = nPointIndex;
		}

		if (dCurValue<dMinValue)
		{
			dMinValue = dCurValue;
			nMinPointIndex = nPointIndex;
		}
	}

	dAmp = (dMaxValue - dMinValue)/2.828;
	dDC_Value = dMaxValue - ((dMaxValue - dMinValue)/2);//���ֵ��ȥ�����ֵ��ȥ��Сֵ��һ�룩

	if (fabs(dAmp)<0.00001)//����Чֵ�ӽ�0������ǰֵΪ0���������Ƕ�
	{
		dCurPointAng = 0;
		return TRUE;
	}

	double dTmp = 2*(dCalPointValue-dDC_Value)/(dMaxValue - dMinValue);
	dCurPointAng = acos(dTmp);

	if (nMaxPointIndex<nMinPointIndex)//�����ǰ������Сֵ�ȽϽ�,��Ƕ�ȡ��
	{
		dCurPointAng = -dCurPointAng;
	} 

	dCurPointAng += _PI/2;//����Ϊ���Ҳ��Ƕ�
	return TRUE;
}

void CComtradeAnalogData::InsertNormalCyclePoints(double dVolValue,double dCurrentValue,double dSmpRate,double dFreq,
												  long nInsertPoints,long nDataFileType)
{
	CMemBuffer_UShort* pShortBuffer = GetMemBuffer_UShort();

	if(!pShortBuffer)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰͨ�����ݻ���Ϊ��,�޷����в�ֵ����"));
		return;
	}

	unsigned short* pBuffer = pShortBuffer->GetBuffer();
	long nBufferSize = pShortBuffer->GetBufferLength();

	if((nBufferSize <= 0)||(pBuffer == NULL))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰͨ�����ݻ��泤��Ϊ0,�޷����в�ֵ����"));
		return;
	}

	double dMaxValue = 0.0f;
	double dNewAmp = 0,dAmp = 0,dAng = 0 ,dDcValue = 0;
	long nAfterBufferSize = nBufferSize + nInsertPoints;

	if (IsAnalogU())
	{
		dNewAmp = dVolValue;
	}
	else
	{
		dNewAmp = dCurrentValue;
	}

	dMaxValue = dNewAmp*SQRT2;
	double dCurrPointValue = (dMaxValue-m_dZeroValue)/m_dCoefValue;

	if ((dCurrPointValue)>32767)
	{
		double dNewCoef = 1.1* m_dCoefValue * dCurrPointValue/32767;
		AdjustCoefValue(m_nTotalPoints,dNewCoef);
	}

	// ������������ѡ����ʵĻ������ͷ����С
	if (nDataFileType == COMTRADE_DATAFILE_TYPE_ASCII && IsAnalogData())
	{
		nBufferSize /=2;//COMTRADE_DATAFILE_TYPE_ASCIIģʽ2���޷��Ŷ����ͱ�ʶ1��ͨ������
		nAfterBufferSize = nBufferSize + nInsertPoints;

		// ����long���͵�����
		int* pOldBuffer = new int[nBufferSize]; 
		memset(pOldBuffer, 0, nBufferSize * sizeof(int));
		memcpy(pOldBuffer, pBuffer, nBufferSize * sizeof(int));

		AllocBuffer(nAfterBufferSize *2); // �������Ļ�����
		int* pBufferLong = (int*)pShortBuffer->GetBuffer();

		// ���²�������
// 		memset(pBufferLong , 0, nInsertPoints * sizeof(long));
		memcpy(pBufferLong + nInsertPoints, pOldBuffer, nBufferSize * sizeof(int));
		delete[] pOldBuffer;
	}
 	else
 	{
 		nAfterBufferSize = nBufferSize + nInsertPoints;
 
 		// ����unsigned short���͵�����
 		unsigned short* pOldBuffer = new unsigned short[nBufferSize];
 		memset(pOldBuffer, 0, nBufferSize * sizeof(unsigned short));
 		memcpy(pOldBuffer, pBuffer, nBufferSize * sizeof(unsigned short));
 
 		AllocBuffer(nAfterBufferSize);
 		pBuffer = pShortBuffer->GetBuffer();
 
 		//���²�������
//		memcpy(pBuffer, pOldBuffer, nInsertPoints * sizeof(unsigned short));
 		memcpy(pBuffer + nInsertPoints, pOldBuffer, nBufferSize * sizeof(unsigned short));
 		delete[] pOldBuffer;
 	}

	m_nTotalPoints = nAfterBufferSize; // ���µ���


	int *pnAttachBufferValue = (int *)m_pnAttachBuffer;
	GetWaveCircleAmpAng(nInsertPoints,dSmpRate,dFreq,dAmp,dAng,dDcValue);//��ȡ����һ�������λ����Чֵ
	double dSecondTotalAng = 2*_PI*dFreq;//ÿ���ӵ�����λֵ
	double dGapTime = 1/dSmpRate;
	double dTmp1 = 0,dTmp2 = 0;

	dAng -= (nInsertPoints*dGapTime*dSecondTotalAng);//���볣ֵ̬��ĳ�ʼ��λ

	for (int nIndex = 0;nIndex<nInsertPoints;nIndex++)//��������������ǰ��Ҫ��ӵĵ�ֵ
	{
		dTmp1 = dAng + (dGapTime*nIndex)*dSecondTotalAng;//��ȡ��ǰ�����λֵ

		while(dTmp1 <0)//����λֵ����Ϊ����
		{
			dTmp1 += 2*_PI;
		}

		while(dTmp1 > 2*_PI)//����λֵ����Ϊ����
		{
			dTmp1 -= 2*_PI;
		}

		dTmp2 = SQRT2*dNewAmp*sin(dTmp1) /*+ dDcValue*/;

		if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
		{
			m_pnAttachBuffer[nIndex] = DoubleToUShortPointValue((dTmp2-m_dZeroValue)/m_dCoefValue);
		} 
		else
		{
			pnAttachBufferValue[nIndex] = static_cast<int>(DoubleToLongPointValue((dTmp2-m_dZeroValue)/m_dCoefValue));
		}
	}
}

BOOL CheckDataValueValid(unsigned short* pnAttachBuffer,long nDstCurPointIndex)//���ڲ�����ת������ֵ��,�����⴦��
{
	if (nDstCurPointIndex<=0)
	{
		return TRUE;
	}

	short nValue1 = pnAttachBuffer[nDstCurPointIndex-1];
	short nValue2 = pnAttachBuffer[nDstCurPointIndex];

// 	if ((nValue1 == 32586) && (nValue2 == 32705))
// 	{
// 		nValue1++;
// 		nValue1--;
// 	}

	if ((nValue1>=32766)&&(nValue2<=-32766))
	{
		return FALSE;
	}

	if ((nValue1<=-32766)&&(nValue2>=32766))
	{
		return FALSE;
	}

	if (abs(nValue1-nValue2)>60000)//20220427 zhouhj �����ֵͻȻ�е���Сֵʱ,��������Ч
	{
		return FALSE;
	}

	return TRUE;
}

long CComtradeAnalogData::InsertBySampleRate(const long &nSrcBeginPoint,const long &nSrcEndPoint ,long &nDstBeginPoint,
							double &dSrcBeginPointTime,const double &dSrcGap,const double &dDstGap,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime)
{
	if (pDstData->GetClassID() != CMTRDCLASSID_ANALOG)
	{
		return 0;
	}

	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	long nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;

	if (pComtradeFile != NULL)
	{
		nDataFileType = pComtradeFile->m_nDataFileType;
	}

	CComtradeAnalogData *pDstAnalogData = (CComtradeAnalogData*)pDstData;
	double dPointX[USE_LAGRANGE_MAX_POINT_NUM];
	double dPointY[USE_LAGRANGE_MAX_POINT_NUM];
	double dDstPointX,dDstPointY;
	double dSrcEndTime = 0;
	long nPointNum = 0;
	long nCurSrcPointIndex = 0;
	long nIndex = 0;
	long nDstCurPointIndex = nDstBeginPoint;//��ֵ�ز�������λ��
	double dTmp = 0;
	long nTmp = 0;
	int *pnAttachBufferValue = (int *)m_pnAttachBuffer;
	int *pnDstAttachBufferValue = (int *)pDstAnalogData->m_pnAttachBuffer;

	for (nCurSrcPointIndex = nSrcBeginPoint;nCurSrcPointIndex<nSrcEndPoint;nCurSrcPointIndex += (nPointNum-1))//��Դ¼����ǰ�������µĵ�,���б����ز���,���������㷨������������
	{
		if ((nCurSrcPointIndex+USE_LAGRANGE_MAX_POINT_NUM-1)>nSrcEndPoint)//���ڵ�ǰ��������������������������⴦��
		{
			if ((nSrcEndPoint-USE_LAGRANGE_MAX_POINT_NUM-1)>=nSrcBeginPoint)//��������һ������ǰ�Ƶ����������õ�������������,�ڸò����ʷ�Χ��
			{
				nCurSrcPointIndex = (nSrcEndPoint-USE_LAGRANGE_MAX_POINT_NUM+1);
				nPointNum = USE_LAGRANGE_MAX_POINT_NUM;
			} 
			else//����,�ӵ�ǰ��������,��һ�������㿪ʼ,�м�������ü���������ز���
			{
				nCurSrcPointIndex = nSrcBeginPoint;
				nPointNum = (nSrcEndPoint-nCurSrcPointIndex+1);
			}

		}
		else
		{
			nPointNum = USE_LAGRANGE_MAX_POINT_NUM;
		}

		for (nIndex = 0;nIndex<nPointNum;nIndex++)
		{
			dPointX[nIndex] = (dSrcBeginPointTime+(nCurSrcPointIndex-nSrcBeginPoint+nIndex)*dSrcGap);//ȡԴ����ͨ��ʱ���������ϵĵ�
			nTmp = GetAttachBuffer_long(nDataFileType,nCurSrcPointIndex+nIndex);
			dPointY[nIndex] = (nTmp*m_dCoefValue+m_dZeroValue);//ȡԴ������ǰʱ���²�����ֵ
		}

		dSrcEndTime = dPointX[nPointNum-1];//��ȡ���������õ���Դ����ͨ������ʱ��
		dDstPointX = nDstCurPointIndex*dDstGap + dDstBeginOffsetTime;//��ȡĿ�����ͨ����ǰ���ʱ������ֵ

		while(dDstPointX<dSrcEndTime)
		{
			dDstPointY = LagrangeAlg(dPointX,dPointY,nPointNum,dDstPointX);
//			ASSERT(dDstPointY<170);

			if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
			{
				pDstAnalogData->m_pnAttachBuffer[nDstCurPointIndex] = DoubleToUShortPointValue((dDstPointY-pDstAnalogData->m_dZeroValue)/pDstAnalogData->m_dCoefValue);

				if (!CheckDataValueValid(pDstAnalogData->m_pnAttachBuffer,nDstCurPointIndex))//zhouhj 20210807 ��鵱ǰֵ�Ƿ�Խ��,���Խ��,��������ǰһ��ֵ��ͬ
				{
					pDstAnalogData->m_pnAttachBuffer[nDstCurPointIndex] = pDstAnalogData->m_pnAttachBuffer[nDstCurPointIndex-1];
				}
			} 
			else
			{
				pnDstAttachBufferValue[nDstCurPointIndex] = static_cast<int>(DoubleToLongPointValue((dDstPointY-pDstAnalogData->m_dZeroValue)/pDstAnalogData->m_dCoefValue));
			}

			nDstCurPointIndex++;
			dDstPointX += dDstGap;
		}

		if ((fabs(dDstPointX-dSrcEndTime)<0.0000001)&&(dDstPointX>=dSrcEndTime))//�������ز���ǰ�غϵĵ�,ֱ�Ӹ�ֵ
		{
			if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
			{
				pDstAnalogData->m_pnAttachBuffer[nDstCurPointIndex] = m_pnAttachBuffer[nCurSrcPointIndex+nPointNum-1];
			} 
			else
			{
				pnDstAttachBufferValue[nDstCurPointIndex] = static_cast<int>(pnAttachBufferValue[nCurSrcPointIndex+nPointNum-1]);
			}

			nDstCurPointIndex++;
			dDstPointX += dDstGap;
		}
	}

	nDstBeginPoint = nDstCurPointIndex;
	dSrcBeginPointTime += (nSrcEndPoint-nSrcBeginPoint)*dSrcGap;
	return nDstBeginPoint;
}

long CComtradeAnalogData::GetAttachBuffer_long(long nDataFileType,long nIndex)
{
	long nValue = 0;
	int *pnAttachBufferValue = (int *)m_pnAttachBuffer;

	if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
	{
		nValue = (short)m_pnAttachBuffer[nIndex];
	} 
	else
	{
		nValue = pnAttachBufferValue[nIndex];
	}

	return nValue;
}

long CComtradeAnalogData::InsertBySampleRate_SteadyState(const double &dBeginPointAng,const double &dCurFreq ,const long &nSrcBeginPoint,const long &nSrcEndPoint ,long &nDstBeginPoint,
												 double &dSrcBeginPointTime,const double &dSrcGap,const double &dDstGap,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime)
{
	if (pDstData->GetClassID() != CMTRDCLASSID_ANALOG)
	{
		return 0;
	}

	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	long nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;

	if (pComtradeFile != NULL)
	{
		nDataFileType = pComtradeFile->m_nDataFileType;
	}

	CComtradeAnalogData *pDstAnalogData = (CComtradeAnalogData*)pDstData;
	long nCurSrcPointIndex = 0;
	long nDstCurPointIndex = nDstBeginPoint;//��ֵ�ز�������λ��
	double dSrcBeginTime = 0;
	double dSrcEndTime = 0;
	double dDstCurTime = 0;
	double dTmp1 = 0 ,dTmp2 = 0,dCurPointValue = 0;
	double dSecondTotalAng = 2*_PI*dCurFreq;
	dDstCurTime = nDstCurPointIndex*dDstGap + dDstBeginOffsetTime;//�����Ŀ��������������ʼ���ʱ�䣬�ټ���offsetʱ��
	int *pnDstAttachBufferValue = (int *)pDstAnalogData->m_pnAttachBuffer;

	for (nCurSrcPointIndex = nSrcBeginPoint;nCurSrcPointIndex<nSrcEndPoint;nCurSrcPointIndex++)
	{
		dSrcBeginTime = dSrcBeginPointTime + (nCurSrcPointIndex-nSrcBeginPoint)*dSrcGap;
		dSrcEndTime = dSrcBeginTime + dSrcGap;

		while(dDstCurTime<dSrcEndTime)
		{
			dCurPointValue = GetUShortPointValueDouble(nCurSrcPointIndex+1)/*m_dCoefValue*((short)m_pnAttachBuffer[nCurSrcPointIndex+1])+m_dZeroValue*/;
			dTmp1 = (dDstCurTime-dSrcBeginPointTime)*dSecondTotalAng + dBeginPointAng;

			while(dTmp1 <0)
			{
				dTmp1 += 2*_PI;
			}

			dTmp2 = SQRT2*dCurPointValue*sin(dTmp1);

			if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
			{
				pDstAnalogData->m_pnAttachBuffer[nDstCurPointIndex] = DoubleToUShortPointValue((dTmp2-m_dZeroValue)/m_dCoefValue);
			} 
			else
			{
				pnDstAttachBufferValue[nDstCurPointIndex] = static_cast<int>(DoubleToLongPointValue((dTmp2-m_dZeroValue)/m_dCoefValue));
			}

			nDstCurPointIndex++;
			dDstCurTime += dDstGap;
		}
	}

	nDstBeginPoint = nDstCurPointIndex;
	dSrcBeginPointTime += (nSrcEndPoint-nSrcBeginPoint)*dSrcGap;
	return nDstBeginPoint;
}

long CComtradeAnalogData::InsertBySampleRate_Double(double **ppdDoubleBuff,const long &nSrcBeginPoint,const long &nSrcEndPoint ,long &nDstBeginPoint,
											 double &dSrcBeginPointTime,const double &dSrcGap,const double &dDstGap,const double &dDstBeginOffsetTime)
{
	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	long nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;

	if (pComtradeFile != NULL)
	{
		nDataFileType = pComtradeFile->m_nDataFileType;
	}

	double dPointX[USE_LAGRANGE_MAX_POINT_NUM];
	double dPointY[USE_LAGRANGE_MAX_POINT_NUM];
	double dDstPointX,dDstPointY;
	double dSrcEndTime = 0;
	long nPointNum = 0;
	long nCurSrcPointIndex = 0;
	long nIndex = 0;
	long nDstCurPointIndex = nDstBeginPoint;//��ֵ�ز�������λ��
	double dTmp = 0;
	long nTmp = 0;

	for (nCurSrcPointIndex = nSrcBeginPoint;nCurSrcPointIndex<nSrcEndPoint;nCurSrcPointIndex += (nPointNum-1))//��Դ¼����ǰ�������µĵ�,���б����ز���,���������㷨������������
	{
		if ((nCurSrcPointIndex+USE_LAGRANGE_MAX_POINT_NUM-1)>nSrcEndPoint)//���ڵ�ǰ��������������������������⴦��
		{
			if ((nSrcEndPoint-USE_LAGRANGE_MAX_POINT_NUM-1)>=nSrcBeginPoint)//��������һ������ǰ�Ƶ����������õ�������������,�ڸò����ʷ�Χ��
			{
				nCurSrcPointIndex = (nSrcEndPoint-USE_LAGRANGE_MAX_POINT_NUM+1);
				nPointNum = USE_LAGRANGE_MAX_POINT_NUM;
			} 
			else//����,�ӵ�ǰ��������,��һ�������㿪ʼ,�м�������ü���������ز���
			{
				nCurSrcPointIndex = nSrcBeginPoint;
				nPointNum = (nSrcEndPoint-nCurSrcPointIndex+1);
			}
		}
		else
		{
			nPointNum = USE_LAGRANGE_MAX_POINT_NUM;
		}

		for (nIndex = 0;nIndex<nPointNum;nIndex++)
		{
			dPointX[nIndex] = (dSrcBeginPointTime+(nCurSrcPointIndex-nSrcBeginPoint+nIndex)*dSrcGap);//ȡԴ����ͨ��ʱ���������ϵĵ�
			nTmp = GetAttachBuffer_long(nDataFileType,nCurSrcPointIndex+nIndex);
			dPointY[nIndex] = (nTmp*m_dCoefValue+m_dZeroValue);//ȡԴ������ǰʱ���²�����ֵ
		}

		dSrcEndTime = dPointX[nPointNum-1];//��ȡ���������õ���Դ����ͨ������ʱ��
		dDstPointX = nDstCurPointIndex*dDstGap + dDstBeginOffsetTime;//��ȡĿ�����ͨ����ǰ���ʱ������ֵ

		while(dDstPointX<dSrcEndTime)
		{
			dDstPointY = LagrangeAlg(dPointX,dPointY,nPointNum,dDstPointX);
			//			ASSERT(dDstPointY<170);
			(*ppdDoubleBuff)[nDstCurPointIndex] = dDstPointY;
			nDstCurPointIndex++;
			dDstPointX += dDstGap;
		}

		if ((fabs(dDstPointX-dSrcEndTime)<0.0000001)&&(dDstPointX>=dSrcEndTime))//�������ز���ǰ�غϵĵ�,ֱ�Ӹ�ֵ
		{
			(*ppdDoubleBuff)[nDstCurPointIndex] = (m_dCoefValue*GetAttachBuffer_long(nDataFileType,nCurSrcPointIndex+nPointNum-1))+m_dZeroValue;
			nDstCurPointIndex++;
			dDstPointX += dDstGap;
		}
	}

	nDstBeginPoint = nDstCurPointIndex;
	dSrcBeginPointTime += (nSrcEndPoint-nSrcBeginPoint)*dSrcGap;
	return nDstBeginPoint;
}

long CComtradeAnalogData::InsertBySampleRate_SteadyState_Double(double **ppdDoubleBuff,const double &dBeginPointAng,const double &dCurFreq ,const long &nSrcBeginPoint,const long &nSrcEndPoint ,long &nDstBeginPoint,
														 double &dSrcBeginPointTime,const double &dSrcGap,const double &dDstGap,const double &dDstBeginOffsetTime)
{
	long nCurSrcPointIndex = 0;
	long nDstCurPointIndex = nDstBeginPoint;//��ֵ�ز�������λ��
	double dSrcBeginTime = 0;
	double dSrcEndTime = 0;
	double dDstCurTime = 0;
	double dTmp1 = 0 ,dTmp2 = 0,dCurPointValue = 0;
	double dSecondTotalAng = 2*_PI*dCurFreq;
	dDstCurTime = nDstCurPointIndex*dDstGap + dDstBeginOffsetTime;//�����Ŀ��������������ʼ���ʱ�䣬�ټ���offsetʱ��

	for (nCurSrcPointIndex = nSrcBeginPoint;nCurSrcPointIndex<nSrcEndPoint;nCurSrcPointIndex++)
	{
		dSrcBeginTime = dSrcBeginPointTime + (nCurSrcPointIndex-nSrcBeginPoint)*dSrcGap;
		dSrcEndTime = dSrcBeginTime + dSrcGap;

		while(dDstCurTime<dSrcEndTime)
		{
			dCurPointValue = GetUShortPointValueDouble(nCurSrcPointIndex+1)/*m_dCoefValue*((short)m_pnAttachBuffer[nCurSrcPointIndex+1])+m_dZeroValue*/;
			dTmp1 = (dDstCurTime-dSrcBeginPointTime)*dSecondTotalAng + dBeginPointAng;

			while(dTmp1 <0)
			{
				dTmp1 += 2*_PI;
			}

			dTmp2 = SQRT2*dCurPointValue*sin(dTmp1);
			(*ppdDoubleBuff)[nDstCurPointIndex] = m_dZeroValue;
			nDstCurPointIndex++;
			dDstCurTime += dDstGap;
		}
	}

	nDstBeginPoint = nDstCurPointIndex;
	dSrcBeginPointTime += (nSrcEndPoint-nSrcBeginPoint)*dSrcGap;
	return nDstBeginPoint;
}

void CComtradeAnalogData::SaveChanInfo(CString& strInfor)
{
#ifdef _PSX_IDE_QT_
	strInfor = QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13")
		.arg(m_nChannelIndex)
		.arg(m_strName)
		.arg(m_strPhaseID)
		.arg(m_strCcbm)
		.arg(m_strUnit)
		.arg(m_dCoefValue, 0, 'f', 8)
		.arg(m_dZeroValue, 0, 'f',8)
		.arg(m_dTimeSkew, 0, 'f', 1)
		.arg(m_nMin)
		.arg(m_nMax)
		.arg(m_dPrimaryValue, 0, 'f', 10)
		.arg(m_dSecondaryValue, 0, 'f', 10)
		.arg(m_cPSType);

#else
    strInfor.Format(_T("%d,%s,%s,%s,%s,%.10f,%.10f,%.1f,%ld,%ld,%.10f,%.10f,%c"),
        m_nChannelIndex,m_strName,m_strPhaseID,m_strCcbm,
        m_strUnit,m_dCoefValue,m_dZeroValue,m_dTimeSkew,
        m_nMin,m_nMax,m_dPrimaryValue,m_dSecondaryValue,m_cPSType);
#endif
}

void CComtradeAnalogData::InitBuffer_Circle(long nDataFileType,long nTotalPoints)
{
	if (nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
	{
		CComtradeDataBase::InitBuffer_Circle(nDataFileType,nTotalPoints);
	} 
	else
	{
		unsigned short uTmp = 0,uTmp2 = 0;

		if ((m_pnAttachBuffer != NULL)&&((m_nTotalPoints)>0)&&((2*m_nTotalPoints)<=GetMemBuffer_UShortNum()))
		{
			uTmp = m_pnAttachBuffer[2*m_nTotalPoints-2];
			uTmp2 = m_pnAttachBuffer[2*m_nTotalPoints-1];
		}

		if (GetMemBuffer_UShortNum()<(2*nTotalPoints))
		{
			AllocBuffer(nTotalPoints*2);
		}

		if ((m_pnAttachBuffer != NULL)&&(nTotalPoints>0))
		{
			m_pnAttachBuffer[0] = uTmp;
			m_pnAttachBuffer[1] = uTmp2;
		}
	}
}

void CComtradeAnalogData::GetChanInfor(CString* pstrParse,long nOffSet)
{
	m_nChannelIndex		= CString_To_long(pstrParse[0]);
	m_strName			= pstrParse[1];
	m_strPhaseID		= pstrParse[2];
	m_strCcbm			= pstrParse[3];
	m_strUnit			= pstrParse[4];
	m_dCoefValue		= CString_To_double(pstrParse[5]);
	m_dZeroValue		= CString_To_double(pstrParse[6]);
	m_dTimeSkew			= CString_To_double(pstrParse[7]);
	m_nMin				= CString_To_long(pstrParse[8]);
	m_nMax				= CString_To_long(pstrParse[9]);
	m_dPrimaryValue     = CString_To_double(pstrParse[10]);
	m_dSecondaryValue   = CString_To_double(pstrParse[11]);
	m_strPSType         = pstrParse[12];

	m_strID = m_strName;
// 	if (pstrParse[12].GetLength() > 0)
// 	{
// 		m_cPSType           = pstrParse[12].GetAt(0);
// 	}

}


//������ͨ����ʾ�����ĺ���
void CComtradeAnalogData::GetCountBeforeBind(int*ipBind)
{
	//0���Ƿ�ֻ��ʾʹ�õ�ͨ������
	//1����ѹͨ���ĸ���
	//2������ͨ���ĸ���
	CString strUnit=m_strUnit;
	strUnit.MakeUpper();

	if(ipBind[0]==1)
	{
		if(m_bUsed)
		{
			if(strUnit=="KV" || strUnit=="V")
				ipBind[1]=ipBind[1]+1;
			if(strUnit=="KA" || strUnit=="A")
				ipBind[2]=ipBind[2]+1;
		}
	}
	else
	{
		if(strUnit=="KV" || strUnit=="V")
			ipBind[1]=ipBind[1]+1;
		if(strUnit=="KA" || strUnit=="A")
			ipBind[2]=ipBind[2]+1;
	}
}

//��ͬ��һ����ʾʱ����ø�ͨ����ID��
void CComtradeAnalogData::GetCHIndexBeforeBind(int*ipVoltage,int*ipCurrent,BOOL bUse)
{
	CString strUnit=m_strUnit;
	strUnit.MakeUpper();

	if(bUse)
	{
		if(m_bUsed)
		{
			if(strUnit=="KV" || strUnit=="V")
			{
				ipVoltage[ipVoltage[0]]=m_nChannelIndex;
				ipVoltage[0]=ipVoltage[0]+1;
			}
			if(strUnit=="KA" || strUnit=="A")
			{
				ipCurrent[ipCurrent[0]]=m_nChannelIndex;
				ipCurrent[0]=ipCurrent[0]+1;
			}
		}
	}
	else
	{
		if(strUnit=="KV" || strUnit=="V")
		{
			ipVoltage[ipVoltage[0]]=m_nChannelIndex;
			ipVoltage[0]=ipVoltage[0]+1;
		}
		if(strUnit=="KA" || strUnit=="A")
		{
			ipCurrent[ipCurrent[0]]=m_nChannelIndex;
			ipCurrent[0]=ipCurrent[0]+1;
		}
	}
}

//���ͨ���Ĳ����������Сֵ
void CComtradeAnalogData::GetCHSampMaxMiVal(float &fMaxVal,float &fMinVal)
{
// 	double fMax = ;
// 	if(m_fMaxVal>fMaxVal)
// 		fMaxVal=m_fMaxVal;
// 
// 	if(m_fMinVal<fMinVal)
// 		fMinVal=m_fMinVal;
}

//////////////////////////////////////////////////////////////////////////
void CComtradeAnalogData::InitCalValueBuffer()
{
	long nIndex = 0;

	for (nIndex=0; nIndex<ANALOG_CAL_VALUE_MAX_COUNT; nIndex++)
	{
		m_ppfCalValue[nIndex] = NULL;
	}
}

void CComtradeAnalogData::FreeCalValueBuffer()
{
	long nIndex = 0;

	for (nIndex=0; nIndex<ANALOG_CAL_VALUE_MAX_COUNT; nIndex++)
	{
		if (m_ppfCalValue[nIndex] != NULL)
		{
			delete m_ppfCalValue[nIndex];
			m_ppfCalValue[nIndex] = NULL;
		}
	}
}

void CComtradeAnalogData::FreeCalValueBuffer(long nIndex)
{
	if (m_ppfCalValue[nIndex] != NULL)
	{
		delete m_ppfCalValue[nIndex];
		m_ppfCalValue[nIndex] = NULL;
	}
}


BOOL CComtradeAnalogData::AllocCalValueBuffer(long nIndex, long nPoints)
{
	if (m_ppfCalValue[nIndex] != NULL)
	{
		delete m_ppfCalValue[nIndex];
		m_ppfCalValue[nIndex] = NULL;
	}

	m_ppfCalValue[nIndex] = new float [nPoints];

	if (m_ppfCalValue[nIndex] != NULL)
	{
		ZeroMemory(m_ppfCalValue[nIndex], sizeof(float) * nPoints);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

float* CComtradeAnalogData::GetCalValueBuffer(long nIndex)
{
	return m_ppfCalValue[nIndex];
}

long CComtradeAnalogData::XmlReadOwn( CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys )
{
	CComtradeDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strCoefaKey, oNode, m_dCoefValue);
	xml_GetAttibuteValue(pXmlKeys->m_strCoefbKey, oNode, m_dZeroValue);
	xml_GetAttibuteValue(pXmlKeys->m_strSkewtimeKey, oNode, m_dTimeSkew);
	xml_GetAttibuteValue(pXmlKeys->m_strMinKey, oNode, m_nMin);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxKey, oNode, m_nMax);
	xml_GetAttibuteValue(pXmlKeys->m_strPrimaryKey, oNode, m_dPrimaryValue);
	xml_GetAttibuteValue(pXmlKeys->m_strSecondaryKey, oNode, m_dSecondaryValue);
	xml_GetAttibuteValue(pXmlKeys->m_strPsKey, oNode, m_strPSType);

//	xml_GetCDATA(oNode, m_strDataFile);
	return 0;
}

long CComtradeAnalogData::XmlWriteOwn( CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys )
{
	CComtradeDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strCoefaKey, oElement, m_dCoefValue);
	xml_SetAttributeValue(pXmlKeys->m_strCoefbKey, oElement, m_dZeroValue);
	xml_SetAttributeValue(pXmlKeys->m_strSkewtimeKey, oElement, m_dTimeSkew);
	xml_SetAttributeValue(pXmlKeys->m_strMinKey, oElement, m_nMin);
	xml_SetAttributeValue(pXmlKeys->m_strMaxKey, oElement, m_nMax);
	xml_SetAttributeValue(pXmlKeys->m_strPrimaryKey, oElement, m_dPrimaryValue);
	xml_SetAttributeValue(pXmlKeys->m_strSecondaryKey, oElement, m_dSecondaryValue);
	xml_SetAttributeValue(pXmlKeys->m_strPsKey, oElement, m_strPSType);

//	xml_SetCDATA(oXMLDoc, oElement, (char *)m_pnAttachBuffer, m_nTotalPt);
	return 0;
}

CExBaseObject* CComtradeAnalogData::CreateNewChild( const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys )
{
	CExBaseObject *pNew  = NULL;
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CComtradeAnalogData::CreateNewChild( long nClassID/*, BOOL &bAddToTail*/ )
{
	CExBaseObject *pNew  = NULL;
	return pNew;
}

BOOL CComtradeAnalogData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CComtradeDataBase::CopyOwn(pDest);
	CComtradeAnalogData *p = (CComtradeAnalogData*)pDest;
	p->m_strUnit = m_strUnit;
	p->m_dCoefValue = m_dCoefValue;
	p->m_dCoefValueBK = m_dCoefValueBK;
	p->m_dZeroValue = m_dZeroValue;
	p->m_dZeroValueBK = m_dZeroValueBK;
	p->m_dTimeSkew = m_dTimeSkew;
	p->m_nMin = m_nMin;
	p->m_nMax = m_nMax;
	p->m_dPrimaryValue = m_dPrimaryValue;
	p->m_dSecondaryValue = m_dSecondaryValue;
	p->m_cPSType = m_cPSType;
	p->m_strPSType = m_strPSType;
	p->m_nMinCal = m_nMinCal;
	p->m_nMaxCal = m_nMaxCal;
	return TRUE;
}


long CComtradeAnalogData::GetCoefVal()
{
	if ((m_strUnit == _T("kA")) || (m_strUnit == _T("kV")))
	{
		return 1000;
	}

	return 1;
}
void CComtradeAnalogData::WriteAnalogDatas(const CString &strFileHeadName)
{
	CRcdComtradeFile *pComtradeFile = (CRcdComtradeFile*)GetParent();
	long nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;

	if (pComtradeFile != NULL)
	{
		nDataFileType = pComtradeFile->m_nDataFileType;
	}

	CString strFile;
	strFile = _P_GetLibraryPath();
	SYSTEMTIME tm;
	::GetLocalTime(&tm);

	strFile.AppendFormat(_T("%s-%s(%s)-%04d.%02d.%02d_%02d-%02d-%02d-%03d.txt"),strFileHeadName.GetString(), m_strCcbm.GetString(),m_strPhaseID.GetString() ,
		tm.wYear,tm.wMonth,tm.wDay, tm.wHour, tm.wMinute, tm.wSecond ,tm.wMilliseconds);
	CFile oFile;

	if (! oFile.Open(strFile, CFile::modeCreate | CFile::modeWrite))
	{
		return;
	}

	long nTmpValue = 0;
	CString strTmp;

	for (long nIndex = 0;nIndex<m_nTotalPoints;nIndex++)
	{
		nTmpValue = GetAttachBuffer_long(nDataFileType,nIndex);
		strTmp.Format(_T("%ld\r\n"),nTmpValue);
		oFile.Write(strTmp.GetString(), strTmp.GetLength());
	}


	oFile.Close();
}

//2021-1-18  lijunqing
BOOL CComtradeAnalogData::IsAnalogU()
{
	//return ((m_strUnit.Find(_T("V")) >= 0) || (m_strUnit.Find(_T("v")) >= 0));
	if (m_strUnit.Find(_T("V")) >= 0)
	{
		return TRUE;
	}

	if (m_strUnit.Find(_T("v")) >= 0)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CComtradeAnalogData::IsAnalogI()
{
	//return ((m_strUnit.Find(_T("A")) >= 0) || (m_strUnit.Find(_T("a")) >= 0));
	if (m_strUnit.Find(_T("A")) >= 0)
	{
		return TRUE;
	}

	if (m_strUnit.Find(_T("a")) >= 0)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CComtradeAnalogData::MatchType(const CString &strType)
{
	if (strType.CompareNoCase(m_strUnit) == 0)
	{//��λ��ͬ��������k��m�ȿ�ͷ��������������������Ҫ
		return TRUE;
	}

	if (m_strID.GetLength() == 0)
	{
		return FALSE;
	}

	CString strTemp = m_strID.Left(1);

	if (strType.CompareNoCase(strTemp) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

