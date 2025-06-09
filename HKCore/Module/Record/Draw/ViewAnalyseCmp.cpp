// ViewAnalyseCmp.cpp : implementation file
//

#include "stdafx.h"
#include "ViewAnalyseCmp.h"
#include "..\MR1200BaseApp.h"
#include "DrawAnalogVariableCmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CViewAnalyseCmp::CViewAnalyseCmp()
{
	m_bCmpDrawUseCmbMode = TRUE;
	m_pPointBufferCmp = NULL;
	m_nBeginPos1 = 0;
	m_nEndPos1 = 0;
	m_nBeginPos2 = 0;
	m_nEndPos2 = 0;

	m_pRcdComtradeFile1 = NULL;
	m_pRecordTest1 = NULL;
	m_pRefBuffer1 = NULL;

	m_pPointBufferCmp = new CMemBuffer_CPoint();
	m_pPointBufferCmp->SetBufferLength(AnalyseWnd_MaxDrawlength);
	CPoint *pPoint = m_pPointBufferCmp->GetBuffer();
	//g_crDrawBackColor = RGB(255, 255, 255);
}

CViewAnalyseCmp::~CViewAnalyseCmp()
{
	m_pRecordTest = NULL;
	m_pRcdComtradeFile = NULL;
	m_pRcdComtradeFile1 = NULL;
	m_pRecordTest1 = NULL;
	m_pRefBuffer1 = NULL;

	if (m_pPointBufferCmp != NULL)
	{
		delete m_pPointBufferCmp;
		m_pPointBufferCmp = NULL;
	}
}

void CViewAnalyseCmp::InitFromComtrade()
{
	m_nSamRateForDraw1 = m_pRecordTest1->g_nSampleRate;

	CViewAnalyse::InitFromComtrade();
}

void CViewAnalyseCmp::InitDrawBufferPos()
{
	CMemBufferInterface* pRecordBuffer = GetDefaultRefBuffer();//m_ppRecordBuffer[0];

	ASSERT (pRecordBuffer != NULL);

	m_pRefBuffer = pRecordBuffer;
	MrDraw::InitDrawBuffPos(&m_oDrawBufferPos);
	m_nSamRateForDraw = m_pRecordTest->g_nSampleRate;

	//��ʼ������¼�����ݵ���Ч��������
	DWORD dwBufLen = m_pRefBuffer->GetBufferLength();
	DWORD dwFillPos = m_pRefBuffer->GetDataFillBeginPosition();

	MrDraw::ClearDrawBuffBeginEndPos(&m_oOscillographBufferPos);

	m_oOscillographBufferPos.nBuf1BeginPos = m_nBeginPos2;
	m_oOscillographBufferPos.nBuf1EndPos   = m_nEndPos2;
	m_oOscillographBufferPos.nBuf2BeginPos = 0;
	m_oOscillographBufferPos.nBuf2EndPos = - 1;
	m_oOscillographBufferPos.nGap = 1;
	m_oOscillographBufferPos.nBufLength = m_pRefBuffer->GetBufferLength();

	DWORD dwDataLength = m_nEndPos2 - m_nBeginPos2;
	m_dOscillographTimeLong = dwDataLength;
	m_dOscillographTimeLong /= m_pRecordTest->g_nSampleRate;

	//�ԱȲ��ε�λ��
	MrDraw::ClearDrawBuffBeginEndPos(&m_oOscillographBufferPosCmp);
	m_oOscillographBufferPosCmp.nBuf1BeginPos = m_nBeginPos1;
	m_oOscillographBufferPosCmp.nBuf1EndPos   = m_nEndPos1;
	m_oOscillographBufferPosCmp.nBufLength   = m_nEndPos1;
	m_oOscillographBufferPosCmp.nGap = 1;
}

void CViewAnalyseCmp::InitDrawPoints()
{
	CViewAnalyse::InitDrawPoints();

	if (m_pPointBufferCmp == NULL)
	{
		m_pPointBufferCmp = new CMemBuffer_CPoint();
		m_pPointBufferCmp->SetBufferLength(AnalyseWnd_MaxDrawlength);
		CPoint *pPoint = m_pPointBufferCmp->GetBuffer();
	}
}


CDrawAnalogVariable* CViewAnalyseCmp::AddAnalogDrawVariable(CExBaseObject* pVar, long nCurrentChans, long nChIndex)
{
	CRtSingleVariable *pVariable1 = (CRtSingleVariable*)g_theRecordApp.FindCmpVariable1(pVar);

	if (pVariable1 == NULL)
	{
		return NULL;
	}

	CDrawAnalogVariable* pAnalog  = CViewAnalyse::AddAnalogDrawVariable(pVar, nCurrentChans, nChIndex);
	CDrawAnalogVariable *pDrawCmp = NULL;
	double dRange = pAnalog->GetRange();

	if (m_bCmpDrawUseCmbMode)
	{
		CDrawAnalogVariableCmp *pAnalogCmp = (CDrawAnalogVariableCmp*)pAnalog;
	
		//�����ıȽ�ͨ������
		pDrawCmp = &pAnalogCmp->m_oCmpAnalogDraw;
		InitAnalogDrawVariable(pVariable1, nCurrentChans, pDrawCmp, FALSE);
		pDrawCmp->AttachAxis(pAnalogCmp->m_pRulerAxis);
	}
	else
	{
		pDrawCmp = new CDrawAnalogVariable();
		InitAnalogDrawVariable(pVariable1, nCurrentChans, pDrawCmp, TRUE);
	}

	dRange = max(dRange, pDrawCmp->GetRange());
	pAnalog->SetRange(dRange);
	pDrawCmp->SetRange(dRange);
	pAnalog->SetShow(1);
	pAnalog->SetUse(1);
	pDrawCmp->m_pptAttachDrawBuffer = m_pPointBufferCmp;//������ͼ����
// 	pAnalog->m_crForeColor = RGB(0, 0, 0);
// 	pDrawCmp->m_crForeColor = RGB(0, 0, 0);
	pDrawCmp->m_nLineStyle = PS_DOT;
	//pDrawCmp->m_crForeColor = ~pAnalog->m_crForeColor;
	//pDrawCmp->m_crForeColor = pDrawCmp->m_crForeColor & 0x00FFFFFF;

	if (m_pRefBuffer1 == NULL)
	{
		m_pRefBuffer1 = pDrawCmp->m_pnAttachBuffer;
	}

	return pAnalog;
}

CDrawAnalogVariable* CViewAnalyseCmp::NewAnalogVariable()
{
	CDrawAnalogVariable* pAnalog = NULL;
	
	if (m_bCmpDrawUseCmbMode)
	{
		pAnalog = new CDrawAnalogVariableCmp();
	}
	else
	{
		pAnalog = new CDrawAnalogVariable();
	}

	return pAnalog;
}


void CViewAnalyseCmp::DrawMain_Wave(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CRecordTestDrawBase::DrawMain_Wave(pDC, fZoomRatio, ptOffset, dwDrawFlag);

	CDrawVariable *pDraw = NULL;
	POS pos = GetHeadPosition();
	double dCoef = 0;
	double dOffset = 40;

	pos = GetHeadPosition();
	CDrawAnalogVariableCmp *pDrawCmp = NULL;
	CDrawAnalogVariable *pAnalogDraw = NULL;

	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);

		if (pDraw->GetClassID() != CMTRDCLASSID_CMPANALOGVARIABLE)
		{
			continue;
		}

		pDrawCmp = (CDrawAnalogVariableCmp *)pDraw;
		pAnalogDraw = &pDrawCmp->m_oCmpAnalogDraw;
		pAnalogDraw->LogicPointToDevicePoint(dCoef, dOffset, m_oDrawBufferPosCmp);
		pAnalogDraw->Draw(pDC, fZoomRatio, ptOffset, VARIABLE_DRAW_STYLE_WAVE);
		pAnalogDraw->DrawAttrs(pDC, fZoomRatio, ptOffset, dwDrawFlag, m_oDrawBufferPosCmp);
	}
}
// 
// void CViewAnalyseCmp::CalXPos(long nTotalPoints)
// {
// 	CXRecordDrawBase::CalXPos(nTotalPoints);
// 
// 	CalXPosEx(nTotalPoints, m_pPointBuffer, m_nSamRateForDraw, m_oDrawBufferPos.nGap);
// 
// 	double dMaxTime = 0;
// 	double dMinTime = 0;
// 	m_oTimeAxisDraw.m_oTimeAxis.GetMinMaxVal(&dMinTime, &dMaxTime, 0);
// 	double dCoef = 0;
// 	int nCenterX = 0;
// 	m_oTimeAxisDraw.m_oTimeAxis.GetAxisInterface(dCoef, nCenterX);
// 	double dTimePerPoint = (double)(dMaxTime - dMinTime) / nTotalPoints;
// 	//dCoef *= dTimePerPoint;
// 	double dIndex = dMinTime;
// 
// 	CPoint* pBuffer = m_pPointBuffer->GetBuffer();
// 	CPoint* pEnd = pBuffer + nTotalPoints;
// 
// 	long nIndex = (long)(dMinTime * m_nSamRateForDraw) / m_oDrawBufferPos.nGap;
// 
// 	while (pBuffer < pEnd)
// 	{
// 		pBuffer->x = (long)(dIndex * dCoef + nCenterX );
// 		pBuffer++;
// 		dIndex += dTimePerPoint;
// 	}
// 
// 	m_pPointBuffer->SetCurrUseLength(nTotalPoints);
// }

//���ݹ�����������ݱ�ʾʱ��Ϊ0�����µ�һ������Ϊ���ʱ��m_dOscillographTimeLong
BOOL CViewAnalyseCmp::CalCurrentDataPos(double dMax,double dMin)
{
	CViewAnalyse::CalCurrentDataPos(dMax, dMin);

	//�ȱȼ���ȽϵĲ��ε�λ��
	//m_oDrawBufferPosCmp
	long nUsePoints = CalCurrentDataPosEx(dMax, dMin, m_pRecordTest1, m_pRefBuffer1
		, m_oDrawBufferPosCmp, m_oOscillographBufferPosCmp);

	CalXPosEx(nUsePoints, m_pPointBufferCmp, m_nSamRateForDraw, m_oDrawBufferPosCmp.nGap);

	return TRUE;
}
