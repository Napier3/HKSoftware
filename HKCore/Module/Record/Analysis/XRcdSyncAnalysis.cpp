// XRcdSyncAnalysis.cpp: implementation of the CXRcdSyncAnalysis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XRcdSyncAnalysis.h"
#include "XRcdAnalysisDrawMngr.h"

#include "../../API/FileApi.h"
#include "../XRecordDrawComtradeDib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CXRcdSyncAnalysis
CXRcdSyncAnalysis::CXRcdSyncAnalysis()
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

CXRcdSyncAnalysis::~CXRcdSyncAnalysis()
{
	
}


void CXRcdSyncAnalysis::CalRising(short *pNewValBuf, long nLen,  long nMaxMagPos,  short vMaxMag)
{
	double dTimeCoef = 1.0 / m_nSampleRate;
	double dMaxVal = vMaxMag * m_pAnalogData->m_dCoefValue;
	m_fValue_50_U = dMaxVal * 0.5;
	short *pEnd = pNewValBuf + nLen;

	m_fTime_50_U = CalRisingPointTime(pNewValBuf, pEnd, abs(m_fValue_50_U));

	CalIChannel(m_nRisingBegin, m_nRisingEnd);

//	WriteRcdAnalysisFile(m_nRisingBegin, m_nRisingEnd, _T("Rising")
//		, m_fTimeRising_10, m_fTimeRising_90, dVal10, dVal90);
}


void CXRcdSyncAnalysis::CalFalling(short *pNewValBuf, long nLen,  long nMaxMagPos, short vMaxMag)
{
	double dTimeCoef = 1.0 / m_nSampleRate;
	double dMaxVal = vMaxMag * m_pAnalogData->m_dCoefValue;
	m_fValue_50_U = dMaxVal * 0.5;
	short *pEnd = pNewValBuf + nLen;

	m_fTime_50_U = CalFallingPointTime(pNewValBuf, pEnd, abs(m_fValue_50_U));

	CalIChannel(m_nFallingBegin, m_nFallingEnd);

}

BOOL CXRcdSyncAnalysis::Analysis(CRcdCalFilterConfig *pRcdCalConfig)
{
	CXRcdCalRespTime::Analysis(pRcdCalConfig);



	return TRUE;
}

BOOL CXRcdSyncAnalysis::CalIChannel(long nBeginPos ,long nEndPos)
{//�����ǵ�һ��ͨ������
	CComtradeAnalogData *pAnalogI = FindAnalog(_T("I"));
	
	if (pAnalogI == NULL)
	{
		return FALSE;
	}

	long nLen = nEndPos - nBeginPos;
	short *pBuf = (short*)m_pAnalogData->GetBuffer();

	CRcdComtradeFile oNewComtradeFile;
	m_pComtradeFile->CopyOwn(&oNewComtradeFile);
	oNewComtradeFile.CreateComtradeFile(2, 0, nLen);
	oNewComtradeFile.SetSamPoints(0, nLen);

	//��һ����ѹͨ��
	CComtradeAnalogData *pNew = oNewComtradeFile.GetAnalogDataByIndex(0);
	m_pAnalogData->CopyOwn(pNew);
	pNew->m_nTotalPoints = nLen;
	unsigned short *pAnalogBuffer = pNew->GetBuffer();
	memcpy(pAnalogBuffer, pBuf+nBeginPos, nLen*sizeof(short));

	//��һ������ͨ��
	pNew = oNewComtradeFile.GetAnalogDataByIndex(1);
	pAnalogI->CopyOwn(pNew);
	pAnalogBuffer = pNew->GetBuffer();
	pBuf = (short*)pAnalogI->GetBuffer();
	pNew->m_nTotalPoints = nLen;
	memcpy(pAnalogBuffer, pBuf+nBeginPos, nLen*sizeof(short));
	pNew->CalMinMaxValue2(0); //���¼��������Сֵ
	
	//�������ͨ����50%��
	CalIChannel(pNew);

	//���沨���ļ�
	CString strFile = m_pComtradeFile->m_strComtradeFile;
	CString strFileName = ParseFileName(m_pComtradeFile->m_strComtradeFile);
	strFile = ChangeFileName(strFile, strFileName + _T("_Sync"));
	oNewComtradeFile.SaveComtradeFile(strFile);

	//����ͼ��
	CString strText;
	CXRecordDrawComtradeDib oComtradeDib;
	CXRcdAnalysisDrawMngr *pDrawMngr = oComtradeDib.GetRcdAnalysisDrawMngr();
	
	//U-50%��
	CXDrawList *pDrawList = pDrawMngr->AddNew(m_pAnalogData->m_strID);
	pDrawList->AddPoint(m_fTime_50_U, m_fValue_50_U);
	strText.Format(_T("%.3f us"), m_fTime_50_U * 1000000);
	pDrawList->AddText(m_fTime_50_U, m_fValue_50_U, 0, 0, strText);

	//I-50%��
	pDrawList = pDrawMngr->AddNew(pNew->m_strID);
	pDrawList->AddPoint(m_fTime_50_I, m_fValue_50_I);
	strText.Format(_T("%.3f us"), m_fTime_50_I * 1000000);
	pDrawList->AddText(m_fTime_50_I, m_fValue_50_I, 0, 0, strText);

	strFile = ChangeFilePostfix(strFile, XRCD_ANALYSIS_DRAW_FILE_POSTFIX);
	pDrawMngr->SaveXmlFile(strFile, CXDrawXmlRWKeys::g_pXmlKeys);

	oComtradeDib.InitByComtrade(&oNewComtradeFile, 800, 600, FALSE);
	oComtradeDib.AdjustRcdAnalysisDrawMngr();
	strFile = ChangeFilePostfix(strFile, _T("bmp"));
	oComtradeDib.ComtradeDib();
	oComtradeDib.WriteBmpFile(strFile);

	strText.Format(_T("%f"), abs(m_fTime_50_I - m_fTime_50_U) * 1000000);
	m_oResults.AddNew2(_T("RcdChSynFile"), _T("RcdChSynFile"), _T(""), _T("string"), GetPathFileNameFromFilePathName(strFile), _T(""));
	m_oResults.AddNew2(_T("ChSynTime"), _T("ChSynTime"), _T("us"), _T("float"), strText, _T(""));

	return TRUE;
}

void CXRcdSyncAnalysis::CalIChannel(CComtradeAnalogData *pAnalogI)
{
	short nMaxAbs = abs(pAnalogI->m_nMaxCal);
	short nMinAbs = abs(pAnalogI->m_nMinCal);
	short *pBuf = (short*)pAnalogI->GetBuffer();
	short *pBufEnd =pBuf + pAnalogI->m_nTotalPoints - 2;

	if (nMaxAbs > nMinAbs)
	{//������� >> 0   ����  0 >> �������
		pAnalogI->CalValue(nMaxAbs, m_fValue_50_I);
		m_fValue_50_I /= 2;

		if (*pBuf > *pBufEnd)
		{//������� >> 0
			m_fTime_50_I = CalFallingPointTime(pAnalogI, abs(m_fValue_50_U));
		}
		else
		{//0 >> �������
			m_fTime_50_I = CalRisingPointTime(pAnalogI, abs(m_fValue_50_U));
		}
	}
	else
	{//������� >> 0   ����  0 >> �������
		pAnalogI->CalValue(nMinAbs, m_fValue_50_I);
		m_fValue_50_I *= -0.5; //ת��Ϊ����

		if (*pBuf > *pBufEnd)
		{//0 >> �������
			m_fTime_50_I = CalRisingPointTime(pAnalogI, abs(m_fValue_50_I));
		}
		else
		{//������� >> 0 
			m_fTime_50_I = CalFallingPointTime(pAnalogI, abs(m_fValue_50_I));
		}
	}
}

