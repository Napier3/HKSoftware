// XRcdCalRespTime.cpp: implementation of the CXRcdCalRespTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XRcdCalRespTime.h"
#include "XRcdAnalysisDrawMngr.h"

#include "../../API/FileApi.h"
#include "../XRecordDrawComtradeDib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CXRcdCalRespConfig::CXRcdCalRespConfig()
{
	m_fChValue = 50;
	m_strChID = _T("Ia");
}

CXRcdCalRespConfig::~CXRcdCalRespConfig()
{

}


//////////////////////////////////////////////////////////////////////////
//CXRcdCalRespTime
CXRcdCalRespTime::CXRcdCalRespTime()
{
	m_nHasRising = m_nHasFaling = 0; //�Ƿ��������غ��½���

	//�����ؽ��
	m_fTimeRising_10 = m_fTimeRising_90 = 0; //10%��90%��ʱ��λ��
	m_nRisingBegin = m_nRisingEnd = -1;  //�����ؿ�ʼ������
	m_fPeakVal = 0;    //��ֵ

	//�½��ؽ��
	m_fTimeFalling_10 = m_fTimeFalling_90 = 0; //10%��90%��ʱ��λ��
	m_nFallingBegin = m_nFallingEnd = -1;  //�½��ؿ�ʼ������
	m_fValleyVal = 0;    //��ֵ

}

CXRcdCalRespTime::~CXRcdCalRespTime()
{
	
}

CComtradeAnalogData* CXRcdCalRespTime::FindAnalog(const CString &strChID)
{
	CComtradeAnalogData *pFind = NULL;
	pFind = (CComtradeAnalogData*)m_pComtradeFile->FindAnalogDataByChID(strChID);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = (CComtradeAnalogData*)m_pComtradeFile->FindAnalogDataByChType(strChID);

	return pFind;
}

BOOL CXRcdCalRespTime::InitCurrAnalogData()
{
	CXRcdCalRespConfig *pRcdRespConfig = (CXRcdCalRespConfig*)m_pRespConfig;
	m_pAnalogData = (CComtradeAnalogData*)m_pComtradeFile->FindAnalogDataByChID(pRcdRespConfig->m_strChID);

	if (m_pAnalogData == NULL)
	{
		m_pAnalogData = m_pComtradeFile->GetAnalogDataByChIndex(1);

		if (m_pAnalogData == NULL)
		{
			return  FALSE;
		}
	}

	return TRUE;
}

void CXRcdCalRespTime::InitAnalysisParas()
{
	CXRcdCalRespConfig *pRcdRespConfig = (CXRcdCalRespConfig*)m_pRespConfig;
	m_nTotalPoints = m_pComtradeFile->GetTotalPoints();
	double dSampleRate = m_pComtradeFile->GetSampleRate(0);
	m_nCalPoints = dSampleRate / 200;  //�ķ�֮һ�ܲ������ڲ��ҷ��ֵ��ǰ������
	m_nFilterPoints = m_nCalPoints / 10; //
	m_nFilterPoints = min(m_nFilterPoints, 5);  //��Ӧʱ��һ��Ϊ100us���൱��ʮ���㣬����ȡ5����������Delta����
	m_nSampleRate = (long)dSampleRate;

	if (pRcdRespConfig->m_fChValue >= 0.5)
	{
		m_nDeltaValue = pRcdRespConfig->m_fChValue / m_pAnalogData->m_dCoefValue;
	}
	else
	{
		m_nDeltaValue = max(abs(m_pAnalogData->m_nMaxCal), abs(m_pAnalogData->m_nMinCal));
	}

	m_nDeltaValue /= 5;   //�����ͻ���������ڼ��������غ��½���

	if (m_nFilterPoints < 5)
	{
		m_nFilterPoints = 5;
	}
}

BOOL CXRcdCalRespTime::Analysis(CRcdCalFilterConfig *pRcdCalConfig)
{
	m_pRespConfig = pRcdCalConfig;
	
	if (!InitCurrAnalogData())
	{
		return FALSE;
	}

	InitAnalysisParas();

	RT_MEM_BUFFER_DATA_POS oMemDataPos;
	oMemDataPos.nDataLength = m_nTotalPoints;
	oMemDataPos.nBufferLength = m_nTotalPoints;
	oMemDataPos.nBuffer1Len = m_nTotalPoints;
	oMemDataPos.nBuffer1Pos = 0;
	oMemDataPos.nBuffer2Len = -1;
	oMemDataPos.nBuffer2Pos = -1;

	CXRcdCalFilter_Short  oCalFilter;

	long k = m_nFilterPoints;
	long nLastPoint = m_nTotalPoints - m_nFilterPoints;
	oCalFilter.SetDeltaDoor(m_nDeltaValue);  //�����ͻ���������ڼ��������غ��½���
	oCalFilter.ConfigRcdCal(m_nSampleRate, m_nFilterPoints, m_nFilterPoints);
	oCalFilter.SetPeakVallyOffsetPoints(m_nCalPoints); //���ҷ��ֵ�õ���ƫ����
	unsigned short *pBuf = m_pAnalogData->GetBuffer();
	unsigned short *pPos = pBuf + m_nFilterPoints+1;

	AnalysisRespRising(oMemDataPos, oCalFilter);
	AnalysisRespFalling(oMemDataPos, oCalFilter);

	return TRUE;
}

//���ݵ�ǰֵ������������
double CXRcdCalRespTime::CalRisingPointTime(short *pBuf, short *pBufEnd, double dValue, double dCoef, double dZero)
{
	double dCurr, dNext;
	short *p = pBuf;
	dCurr = *p * dCoef - dZero;
	p++;
	double dTimeCoef = 1.0 / m_nSampleRate;
	double dTimeOffset = 0;

	while (p < pBufEnd)
	{
		dNext = *p * dCoef - dZero;

		if (dCurr <= dValue && dValue < dNext)
		{//  dCurr <= dValue <= dNext  ���ԣ�(dValue - dCurr) / (dNext - dCurr)
			dTimeOffset += dTimeCoef * (dValue - dCurr) / (dNext - dCurr);
			break;
		}
		else
		{
			dTimeOffset += dTimeCoef;
		}

		dCurr = dNext;
		p++;
	}

	return dTimeOffset;
}

double CXRcdCalRespTime::CalRisingPointTime(short *pBuf, short *pBufEnd, double dValue)
{
	return CalRisingPointTime(pBuf, pBufEnd, dValue, m_pAnalogData->m_dCoefValue, m_pAnalogData->m_dZeroValue);
}

double CXRcdCalRespTime::CalRisingPointTime(CComtradeAnalogData *pAnalog, double dValue)
{
	short *pBuf = (short*)pAnalog->GetBuffer();
	short *pNewValBuf = pBuf;
	short *pBufEnd = pBuf + pAnalog->m_nTotalPoints;

	ValidAndCreateBuffer(pAnalog, pNewValBuf, pBufEnd);

	double dRet = CalRisingPointTime(pNewValBuf, pBufEnd, dValue, pAnalog->m_dCoefValue, pAnalog->m_dZeroValue);

	if (pNewValBuf != pBuf)
	{
		delete pNewValBuf;
	}

	return dRet;
}

//�½���ʱ�����
double CXRcdCalRespTime::CalFallingPointTime(short *pBuf, short *pBufEnd, double dValue, double dCoef, double dZero)
{
	double dCurr, dNext;
	short *p = pBuf;
	dCurr = *p * dCoef - dZero;
	p++;
	double dTimeCoef = 1.0 / m_nSampleRate;
	double dTimeOffset = 0;

	while (p < pBufEnd)
	{
		dNext = *p * dCoef - dZero;

		if (dCurr >= dValue && dValue > dNext)
		{//  dCurr >= dValue >= dNext  ���ԣ�(dCurr - dValue) / (dCurr - dNext)
			dTimeOffset += dTimeCoef * (dCurr - dValue) / (dCurr - dNext);
			break;
		}
		else
		{
			dTimeOffset += dTimeCoef;
		}

		dCurr = dNext;
		p++;
	}

	return dTimeOffset;
}

double CXRcdCalRespTime::CalFallingPointTime(short *pBuf, short *pBufEnd, double dValue)
{
	return CalFallingPointTime(pBuf, pBufEnd, dValue, m_pAnalogData->m_dCoefValue, m_pAnalogData->m_dZeroValue);
}

short* CXRcdCalRespTime::ValidAndCreateBuffer(CComtradeAnalogData *pAnalog, short* &pNewValBuf, short* &pBufEnd)
{
	short *pBuf = (short*)pAnalog->GetBuffer();
	pNewValBuf = pBuf;
	pBufEnd = pBuf + pAnalog->m_nTotalPoints;

	if (pAnalog->m_nMinCal < 0 && (abs(pAnalog->m_nMinCal) > abs(pAnalog->m_nMaxCal)))
	{//0 >> valley   valley >> 0
		long nLen = pAnalog->m_nTotalPoints;
		pNewValBuf = new short [nLen+2];
		short *p = pNewValBuf;
		pBufEnd = pNewValBuf + nLen;

		memcpy(pNewValBuf, pBuf, nLen*sizeof(short));

		while (p < pBufEnd)
		{
			*p = -*p;
			p++;
		}
	}

	return pNewValBuf;
}

double CXRcdCalRespTime::CalFallingPointTime(CComtradeAnalogData *pAnalog, double dValue)
{
	short *pBuf = (short*)pAnalog->GetBuffer();
	short *pNewValBuf = pBuf;
	short *pBufEnd = pBuf + pAnalog->m_nTotalPoints;

	ValidAndCreateBuffer(pAnalog, pNewValBuf, pBufEnd);

	double dRet = CalFallingPointTime(pNewValBuf, pBufEnd, dValue, pAnalog->m_dCoefValue, pAnalog->m_dZeroValue);

	if (pNewValBuf != pBuf)
	{
		delete pNewValBuf;
	}

	return dRet;
}


//������ʱ���������
void CXRcdCalRespTime::CalRising(long nBeginPos, long nEndPos,  long nMaxMagPos, short vMaxMag)
{
	//�����������Ч�Դ���
	m_nRisingBegin = nBeginPos;
	m_nRisingEnd = nEndPos;
	m_nRisingBegin = max(m_nRisingBegin, 0);
	m_nRisingEnd = min(m_nRisingEnd, m_nTotalPoints);

	//���·��仺���������ڼ��㣬ͬʱ���Ե���Ϊ�µ�COMTRADE�ļ�
	long nLen = m_nRisingEnd - m_nRisingBegin;
	short *pNewValBuf = new short [nLen+2];
	short *pBuf = (short*)m_pAnalogData->GetBuffer();
	short *p = pNewValBuf;
	short *pEnd = pNewValBuf + nLen;

	memcpy(pNewValBuf, pBuf+m_nRisingBegin, nLen*sizeof(short));

	if (vMaxMag < 0)
	{//����Ǹ����ܲ�����ת��Ϊ�����������
		while (p < pEnd)
		{
			*p = -*p;
			p++;
		}
	}

	CalRising(pNewValBuf, nLen, nMaxMagPos, vMaxMag);

	delete pNewValBuf;
}

void CXRcdCalRespTime::CalRising(short *pNewValBuf, long nLen,  long nMaxMagPos,  short vMaxMag)
{
	double dTimeCoef = 1.0 / m_nSampleRate;
	double dMaxVal = vMaxMag * m_pAnalogData->m_dCoefValue;
	double dVal10 = dMaxVal * 0.1;
	double dVal90 = dMaxVal * 0.9;
	short *pEnd = pNewValBuf + nLen;

	if (vMaxMag < 0)
	{
		dMaxVal = - dMaxVal;
	}

	//m_fTimeRising_0 = dTimeCoef * (nPos - m_nRisingBegin);
	m_fTimeRising_10 = CalRisingPointTime(pNewValBuf, pEnd, abs(dVal10));
	m_fTimeRising_90 = CalRisingPointTime(pNewValBuf, pEnd, abs(dVal90));
	//m_fTimeRising_100 = dTimeCoef * (nMaxMagPos - nBeginPos);

	WriteRcdAnalysisFile(m_nRisingBegin, m_nRisingEnd, _T("Rising")
		, m_fTimeRising_10, m_fTimeRising_90, dVal10, dVal90);
}

void CXRcdCalRespTime::WriteRcdAnalysisFile(long nBeginPos, long nEndPos, const CString &strNameAppend
											, double fTime10, double fTime90, double fVal10, double fVal90)
{
	long nLen = nEndPos - nBeginPos;
	short *pBuf = (short*)m_pAnalogData->GetBuffer();

	CRcdComtradeFile oNewComtradeFile;
	m_pComtradeFile->CopyOwn(&oNewComtradeFile);
	oNewComtradeFile.CreateComtradeFile(1, 0, nLen);
	oNewComtradeFile.SetSamPoints(0, nLen);
	CComtradeAnalogData *pNew = oNewComtradeFile.GetAnalogDataByIndex(0);
	m_pAnalogData->CopyOwn(pNew);
	unsigned short *pAnalogBuffer = pNew->GetBuffer();
	memcpy(pAnalogBuffer, pBuf+nBeginPos, nLen*sizeof(short));
	CString strFile = m_pComtradeFile->m_strComtradeFile;
	CString strName, strPostFix;
	ParseFileNameAndPostfix(strFile, strName, strPostFix);
	strFile.Format(_T("%s_%s.%s"), strName, strNameAppend, strPostFix);

	oNewComtradeFile.SaveComtradeFile(strFile);

	CString strText;
	CXRecordDrawComtradeDib oComtradeDib;
	CXRcdAnalysisDrawMngr *pDrawMngr = oComtradeDib.GetRcdAnalysisDrawMngr();
	CXDrawList *pDrawList = pDrawMngr->AddNew(pNew->m_strID);
	pDrawMngr->m_strID = strFile;

	//��ӵ㣬ȱʡΪʮ�ֵ�
	CXDrawPoint *pPoint = new CXDrawPoint();
	pDrawList->AddPoint(fTime10, fVal10);
	strText.Format(_T("%.3f us"), fTime10 * 1000000);
	pDrawList->AddText(fTime10, fVal10, 0, 0, strText);

	pPoint = new CXDrawPoint();
	pDrawList->AddPoint(fTime90, fVal90);
	strText.Format(_T("%.3f us"), fTime90 * 1000000);
	pDrawList->AddText(fTime90, fVal90, 0, 0, strText);

	strFile = ChangeFilePostfix(strFile, XRCD_ANALYSIS_DRAW_FILE_POSTFIX);
	pDrawMngr->SaveXmlFile(strFile, CXDrawXmlRWKeys::g_pXmlKeys);

	//DWORD dwAnalogDrawMode = MrDraw::g_dwAnalogDrawMode;
	//MrDraw::g_dwAnalogDrawMode = ANALOG_DRAW_MODE_CROSSX;

	oComtradeDib.InitByComtrade(&oNewComtradeFile, 800, 600, FALSE);
	oComtradeDib.AdjustRcdAnalysisDrawMngr();
	strFile = ChangeFilePostfix(strFile, _T("bmp"));
	oComtradeDib.ComtradeDib();
	oComtradeDib.WriteBmpFile(strFile);
	//MrDraw::g_dwAnalogDrawMode = dwAnalogDrawMode;

	strText.Format(_T("%f"), abs(fTime90 - fTime10) * 1000000);
	CString strID;
	strID.Format(_T("Rcd%sFile"), strNameAppend);
	m_oResults.AddNew2(strID,strID, _T(""), _T("string"), GetPathFileNameFromFilePathName(strFile), _T(""));
	strID.Format(_T("Rcd%sTime"), strNameAppend);
	m_oResults.AddNew2(strID, strID, _T("us"), _T("float"), strText, _T(""));

}

//�½���ʱ�����
void CXRcdCalRespTime::CalFalling(long nBeginPos, long nEndPos,  long nMaxMagPos, short vMaxMag)
{
	//�����������Ч�Դ���
	m_nFallingBegin = nBeginPos;
	m_nFallingEnd = nEndPos;
	m_nFallingBegin = max(m_nFallingBegin, 0);
	m_nFallingEnd = min(m_nFallingEnd, m_nTotalPoints);

	//���·��仺���������ڼ��㣬ͬʱ���Ե���Ϊ�µ�COMTRADE�ļ�
	long nLen = m_nFallingEnd - m_nFallingBegin;
	short *pNewValBuf = new short [nLen+2];
	short *pBuf = (short*)m_pAnalogData->GetBuffer();
	short *pEnd = pNewValBuf + nLen;
	short *p = pNewValBuf;

	memcpy(pNewValBuf, pBuf+m_nFallingBegin, nLen*sizeof(short));

	if (vMaxMag < 0)
	{//����Ǹ����ܲ�����ת��Ϊ�����������
		while (p < pEnd)
		{
			*p = -*p;
			p++;
		}
	}

	CalFalling(pNewValBuf, nLen, nMaxMagPos, vMaxMag);

	delete pNewValBuf;
}

void CXRcdCalRespTime::CalFalling(short *pNewValBuf, long nLen,  long nMaxMagPos, short vMaxMag)
{
	double dTimeCoef = 1.0 / m_nSampleRate;
	double dMaxVal = vMaxMag * m_pAnalogData->m_dCoefValue;
	double dVal10 = dMaxVal * 0.1;
	double dVal90 = dMaxVal * 0.9;
	short *pEnd = pNewValBuf + nLen;

	if (vMaxMag < 0)
	{
		dMaxVal = - dMaxVal;
	}

	//m_fTimeFalling_0 = dTimeCoef * (nPos - m_nFallingBegin);
	m_fTimeFalling_10 = CalFallingPointTime(pNewValBuf, pEnd, dMaxVal * 0.1);
	m_fTimeFalling_90 = CalFallingPointTime(pNewValBuf, pEnd, dMaxVal * 0.9);
	//m_fTimeFalling_100 = dTimeCoef * (nMaxMagPos - nBeginPos);

	WriteRcdAnalysisFile(m_nFallingBegin, m_nFallingEnd, _T("Falling")
		, m_fTimeFalling_10, m_fTimeFalling_90, dVal10, dVal90);

}

BOOL CXRcdCalRespTime::AnalysisRespRising(RT_MEM_BUFFER_DATA_POS &oMemDataPos, CXRcdCalFilter_Short  &oCalFilter)
{
	//�ҵ�������
	long nPos = FindRising(oMemDataPos, oCalFilter);

	if (nPos < 0)
	{
		return FALSE;
	}

	unsigned short *pBuf = m_pAnalogData->GetBuffer();

	if (oCalFilter.IsNextPositive(pBuf + nPos))
	{//����ĵ�Ϊ��ֵ����ʾ��0ͻ�䵽�������
		short vPeak = 0;
		long nPeakPos = nPos;
		
		if (oCalFilter.FindPeak_Next(pBuf+nPos, nPeakPos, vPeak))
		{//���ҷ�ֵλ�ã���������Ϊ��ͻ��λ��-���˵���  ~  ��ֵλ��+���˵���
			CalRising(nPos-m_nFilterPoints, nPeakPos+m_nFilterPoints, nPeakPos, vPeak);
			return TRUE;
		}
		
		return FALSE;
	}

	if (oCalFilter.IsNextNegative(pBuf+nPos))
	{//����ĵ�Ϊ��ֵ����ʾ�������ͻ�䵽0
		short vValley = 0;
		long nValleyPos = nPos;

		if (oCalFilter.FindValley_Prev(pBuf+nPos, nValleyPos, vValley))
		{//������ҹ�ֵλ��
			long nEndPos = nPos + 4*m_nFilterPoints;

			//���������ֵ��λ�ã����ҷ�Χ�� �ܲ�/20
			//��ֵ��Delta������ֵ/25��������Խ��е�������ȷ����Ե�1/50����1/100
			oCalFilter.FindZero_Next(pBuf+nPos, pBuf + nPos + m_nCalPoints/5, m_nDeltaValue/5, nEndPos);

			//�������䣺��ֵλ��-m_nFilterPoints�� ��ֵλ��+m_nFilterPoints
			CalFalling(nValleyPos-m_nFilterPoints, nEndPos+m_nFilterPoints, nValleyPos, vValley);
			return TRUE;
		}

		return FALSE;
	}

	return FALSE;
}

BOOL CXRcdCalRespTime::AnalysisRespFalling(RT_MEM_BUFFER_DATA_POS &oMemDataPos, CXRcdCalFilter_Short  &oCalFilter)
{
	//�����½���
	long nPos = FindFalling(oMemDataPos, oCalFilter);

	if (nPos < 0)
	{
		return FALSE;
	}

	unsigned short *pBuf = m_pAnalogData->GetBuffer();

	if (oCalFilter.IsNextPositive(pBuf + nPos))
	{//����ĵ�Ϊ��ֵ����ʾ���������ͻ�䵽0
		short vPeak = 0;
		long nPeakPos = nPos;

		if (oCalFilter.FindPeak_Next(pBuf+nPos, nPeakPos, vPeak))
		{//��ǰ���ҷ�ֵ
			long nEndPos = nPos + 4*m_nFilterPoints;

			//��ǰ������ֵλ��
			oCalFilter.FindZero_Next(pBuf+nPos, pBuf + nPos + m_nCalPoints/5, m_nDeltaValue/5, nEndPos);

			//�������䣺��ֵλ��-m_nFilterPoints�� ��ֵλ��+m_nFilterPoints
			CalFalling(nPeakPos-m_nFilterPoints, nEndPos+m_nFilterPoints, nPeakPos, vPeak);
			return TRUE;
		}

		return FALSE;
	}

	if (oCalFilter.IsNextNegative(pBuf+nPos))
	{//����ĵ�Ϊ��ֵ����ʾ��0ͻ�䵽�������
		short vValley = 0;
		long nValleyPos = nPos;

		if (oCalFilter.FindValley_Next(pBuf+nPos, nValleyPos, vValley))
		{//��ǰ���ҹ�ֵλ��
			long nEndPos = nValleyPos - 6*m_nFilterPoints;

			//��ǰ������ֵλ��
			oCalFilter.FindZero_Prev(pBuf+nValleyPos, pBuf + nEndPos, m_nDeltaValue/20, nEndPos);
			nEndPos = min(nEndPos, nPos - m_nFilterPoints); //��ֵλ�ã���ͻ��λ�ã�ȥ��С��ֵ

			//�������䣺��ֵλ��-m_nFilterPoints�� ��ֵλ��+m_nFilterPoints
			CalRising(nEndPos-m_nFilterPoints, nValleyPos+m_nFilterPoints, nValleyPos, vValley);
			return TRUE;
		}

		return FALSE;
	}

	return FALSE;
}

//����ͻ��Delta���������������ص�λ��
long CXRcdCalRespTime::FindRising(RT_MEM_BUFFER_DATA_POS &oMemDataPos, CXRcdCalFilter_Short  &oCalFilter)
{
	long k = m_nFilterPoints;
	long nLastPoint = m_nTotalPoints - m_nFilterPoints;
	unsigned short *pBuf = m_pAnalogData->GetBuffer();
	unsigned short *pPos = pBuf + m_nFilterPoints;
	long nPos = -1;
	m_nHasRising = 0;
	oCalFilter.ConfigRcdCal(pBuf, &oMemDataPos);

	for (k=m_nFilterPoints; k<nLastPoint; k++)
	{
		oCalFilter.RcdCal(pPos);

		if (oCalFilter.IsRising())
		{
			m_nHasRising = 1;
			break;
		}

		pPos++;
	}

// 	if (m_nHasRising == 1)
// 	{
// 		nPos = oCalFilter.FindZeroRising(pPos - m_nFilterPoints);
// 
// 		if (nPos < 0)
// 		{
// 			m_nHasRising = 0;
// 		}
// 	}
	if (m_nHasRising == 1)
	{
		nPos = pPos - pBuf;
	
		if (nPos < 0)
		{
			ASSERT (FALSE);
			nPos = 0;
		}
	}

	return nPos;
}

long CXRcdCalRespTime::FindFalling(RT_MEM_BUFFER_DATA_POS &oMemDataPos, CXRcdCalFilter_Short  &oCalFilter)
{
	long k = m_nFilterPoints;
	long nLastPoint = m_nTotalPoints - m_nFilterPoints;
	unsigned short *pBuf = m_pAnalogData->GetBuffer();
	unsigned short *pPos = pBuf + m_nFilterPoints;
	long nPos = -1;
	oCalFilter.ConfigRcdCal(pBuf, &oMemDataPos);

	for (k=m_nFilterPoints; k<nLastPoint; k++)
	{
		oCalFilter.RcdCal(pPos);

		if (oCalFilter.IsFalling())
		{
			m_nHasFaling = 1;
			break;
		}

		pPos++;
	}

// 	if (m_nHasFaling == 1)
// 	{
// 		nPos = oCalFilter.FindZeroFalling(pPos - m_nFilterPoints);
// 
// 		if (nPos < 0)
// 		{
// 			m_nHasFaling = 0;
// 		}
// 	}

	if (m_nHasFaling == 1)
	{
		nPos = pPos - pBuf;

		if (nPos < 0)
		{
			ASSERT (FALSE);
			nPos = 0;
		}
	}

	return nPos;
}

