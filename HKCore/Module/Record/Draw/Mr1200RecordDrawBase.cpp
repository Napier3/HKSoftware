// Mr1200RecordDrawBase.cpp: implementation of the CDrawMr1200RecordBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mr1200RecordDrawBase.h"
#include "..\Comtrade\ComtradeMngr.h"
#include "..\MR1200BaseApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// long CDrawMr1200RecordBase::g_snWaveDrawAreaGap				= 2;	//15;
// long CDrawMr1200RecordBase::g_snBottomRectHeight			= 0;	//15;
// long CDrawMr1200RecordBase::g_snTimeandProgressRectHeight	= 0;	//5;
double g_dCursorTime[3];

CDrawMr1200RecordBase::CDrawMr1200RecordBase()
{
	m_pRefBuffer			= NULL;
	SetRecordDataTimeLength(0);
	m_dMinTimeInOneSreen          = 0;
	m_rcTimeandProgress     = CRect(0,0,0,0); 

	m_nMaxGapValue = MAX_DRAWGAP2;
	SetMaxShowOneSreen ( MAX_DRAWGAP2 * AnalyseWnd_MaxDrawlength / m_nSamRateForDraw);

	//��ͼ�����ʼ����ֹλ��
	m_dDrawBeginTime = 0;
	m_dDrawEndTime = 0;

	MrDraw::InitDrawBuffPos(&m_oDrawBufferPos);
	
	g_dCursorTime[0] = 0;
	g_dCursorTime[1] = 0;
	g_dCursorTime[2] = 0;

	m_pRecordTest = NULL;
}

CDrawMr1200RecordBase::~CDrawMr1200RecordBase()
{
	if (m_pRecordTest != NULL)
	{
		g_theRecordApp.Delete(m_pRecordTest);
	}

	m_pRecordTest = NULL;

}

void CDrawMr1200RecordBase::Init()
{
}

void CDrawMr1200RecordBase::AdjustChanState()
{	
	if (m_pCurrDrawVariable == NULL) 
	{
		return;
	}

	UINT nClassID = m_pCurrDrawVariable->GetClassID();
	
	if (nClassID == CMTRDCLASSID_BINARYVARIABLE) 
	{
		m_pRangeStateAxis->FrozenHead1();
		m_pRangeStateAxis->FrozenHead2();
	}
	else
	{
		m_pRangeStateAxis->FrozenHead1();
		m_pRangeStateAxis->FrozenHead2();
	}
	
	CRect rcAxis = m_pCurrDrawVariable->m_rcAxis;
	CRect rcRangeStateAxis = CreateRangeVertStateAxisBorder(rcAxis.right, rcAxis.top, rcAxis.bottom);
	m_pRangeStateAxis->SetBorder(rcRangeStateAxis, RANGESTATEAXIS_TYPE_VERT);
}

void CDrawMr1200RecordBase::SelectNextChannel(CDrawBase *pChannel)
{	
}

void CDrawMr1200RecordBase::SelectPrevChannel(CDrawBase *pChannel)
{

}

void CDrawMr1200RecordBase::SelectNextChannel()
{
	if (m_pCurrDrawVariable == NULL)
	{
		m_pCurrDrawVariable = (CDrawVariable*)GetHead();
	}

	if (ReCompositor() == TRUE)//��������
	{
		m_pCurrDrawVariable->SetSelect(FALSE);
		m_pCurrDrawVariable = (CDrawVariable*)GetNextVariable(m_pCurrDrawVariable);
		m_pCurrDrawVariable->SetSelect(TRUE);
		m_pRangeStateAxis->AttachDrawObject(m_pCurrDrawVariable);
		AdjustChanState();	
	}
}

void CDrawMr1200RecordBase::SelectPrevChannel()
{
	if (m_pCurrDrawVariable == NULL)
	{
		m_pCurrDrawVariable = (CDrawVariable*)GetHead();
	}

	if (ReCompositor() == TRUE)
	{
		m_pCurrDrawVariable->SetSelect(FALSE);
		m_pCurrDrawVariable = (CDrawVariable*)GetPrevVariable(m_pCurrDrawVariable);
		m_pCurrDrawVariable->SetSelect(TRUE);
		m_pRangeStateAxis->AttachDrawObject(m_pCurrDrawVariable);
		AdjustChanState();		
	}
}

void CDrawMr1200RecordBase::MoveChanDown()
{
	if (m_pCurrDrawVariable == NULL)
	{
		m_pCurrDrawVariable = (CDrawVariable*)GetHead();
	}

	if (m_pCurrDrawVariable != NULL)//CXRecordDrawBase����Ҫ��m_pCurrDrawVariable��ֵ
	{
		//long nBottom = m_pCurrDrawVariable->m_rcBorder.bottom;
		long nBottom = m_pCurrDrawVariable->m_nYCenter;
	
		//m_pCurrDrawVariable->Move(0 , VER_MOVE_ONCE, TRUE);

 		if (nBottom + VER_MOVE_ONCE < m_rcWaveDraw.bottom)
 		{
			m_pCurrDrawVariable->Move(0 , VER_MOVE_ONCE, TRUE);
 		}
 		else
 		{
 			long nMove = m_rcWaveDraw.bottom - nBottom;
 			m_pCurrDrawVariable->Move(0 , nMove);
 		}
		
		AdjustDrawNameRect();
		AdjustChanState();
	}

	SaveRecordDrawObjectControl();
}

void CDrawMr1200RecordBase::MoveChanUp()
{
	if (m_pCurrDrawVariable == NULL)
	{
		m_pCurrDrawVariable = (CDrawVariable*)GetHead();
	}

	if (m_pCurrDrawVariable != NULL)
	{
		//long nTop = m_pCurrDrawVariable->m_rcBorder.top;
		long nTop = m_pCurrDrawVariable->m_nYCenter;
		
		//m_pCurrDrawVariable->Move(0 , 0 - VER_MOVE_ONCE, TRUE);
		if (nTop - VER_MOVE_ONCE >= m_rcWaveDraw.top)
 		{
		m_pCurrDrawVariable->Move(0 , 0 - VER_MOVE_ONCE, TRUE);
 		}
 		else
 		{
 			long nMove = m_rcWaveDraw.top - nTop;
 			m_pCurrDrawVariable->Move(0 , nMove);
 		}
		
		AdjustDrawNameRect();
		AdjustChanState();
	}

	SaveRecordDrawObjectControl();
}

//��ȡ��ǰ���귶Χ֮�ڵ���Ч��ͼ����ʱ��
void CDrawMr1200RecordBase::InitDrawBeginEndTime()
{
	m_oTimeAxisDraw.GetMaxMinTime(m_dDrawEndTime, m_dDrawBeginTime);

	if (m_dMaxTimeInOneSreen <= m_dDrawEndTime)
	{
		m_dDrawEndTime = m_dMaxTimeInOneSreen;
	}

	if (m_dMaxTimeInOneSreen <= m_dDrawBeginTime)
	{
		m_dDrawBeginTime = m_dMaxTimeInOneSreen;
	}

	if (m_dDrawBeginTime < 0.00000001)
	{
		m_dDrawBeginTime = 0;
	}
	
	if (m_dDrawEndTime < 0.00000001)
	{
		m_dDrawEndTime = 0;
	}
}

//ʱ���޶���ΧΪ0 ~ m_dRecordDataTimeLength
void CDrawMr1200RecordBase::MoveLeft()
{
// 	double dMoveOnce = m_oTimeAxisDraw.m_oTimeAxis.GetHorCarryOenGap();
// 	double dMax,dMin;	
// 	double dMaxTime = m_dRecordDataTimeLength;
// 	m_oTimeAxisDraw.GetMaxMinTime(dMax,dMin);
// 	
// 	//���ÿ����Ƴ��ķ�Χ
// 	double dOutGap = (dMax - dMin) / 4;
// 	double dOutMaxTime = dMaxTime + dOutGap;
// 	
// 	if (dMax + dMoveOnce < dOutMaxTime)
// 	{
// 		dMax += dMoveOnce;
// 		dMin += dMoveOnce;
// 	}
// 	else
// 	{
// 		dMin = dOutMaxTime - dMax + dMin;
// 		dMax = dOutMaxTime;
// 	}
	double dMoveOnce = m_oTimeAxisDraw.m_oTimeAxis.GetHorCarryOenGap();
	double dMax,dMin;	
	double dMaxTime = m_dRecordDataTimeLength;
	m_oTimeAxisDraw.GetMaxMinTime(dMax,dMin);
	
	if (dMax + dMoveOnce < dMaxTime)
	{
		dMax += dMoveOnce;
		dMin += dMoveOnce;
	}
	else
	{
		dMin = dMaxTime - dMax + dMin;
		dMax = dMaxTime;
	}

	m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
}
//��Сʱ��ֵ�趨Ϊ0
void CDrawMr1200RecordBase::MoveRight()
{
	double dMoveOnce = m_oTimeAxisDraw.m_oTimeAxis.GetHorCarryOenGap();
	double dMax,dMin;	
	m_oTimeAxisDraw.GetMaxMinTime(dMax,dMin);
	
	if (dMin > dMoveOnce)
	{
		dMin -= dMoveOnce;
		dMax -= dMoveOnce;
	}
	else
	{
		dMax -= dMin ;
		dMin = 0;
	}
	
	m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
}

void CDrawMr1200RecordBase::ArrowLeft()
{
	if (m_pTimeCursorDraw != NULL)
	{
		m_pTimeCursorDraw->Move(-1,0);			
	}
}

void CDrawMr1200RecordBase::ArrowRight()
{
	if (m_pTimeCursorDraw != NULL)
	{
		m_pTimeCursorDraw->Move(1,0);
	}
}

void CDrawMr1200RecordBase::ArrowDown()
{
	if (m_pTimeCursorDraw != NULL)
	{
		long nCurrentCursorID = m_pTimeCursorDraw->GetCurrCursorID();
		nCurrentCursorID = !nCurrentCursorID;
		m_pTimeCursorDraw->SetCurrentCursor(nCurrentCursorID);
	}
}

void CDrawMr1200RecordBase::ArrowUp()
{
	if (m_pTimeCursorDraw != NULL)
	{
		long nCurrentCursorID = m_pTimeCursorDraw->GetCurrCursorID();
		nCurrentCursorID = !nCurrentCursorID;
		m_pTimeCursorDraw->SetCurrentCursor(nCurrentCursorID);
	}
}


void CDrawMr1200RecordBase::ZoomOutTime_GetTimeCenter()
{
	double dTimeMax,dTimeMin, dCursorTime;
	m_oTimeAxisDraw.GetMaxMinTime(dTimeMax,dTimeMin);
	dCursorTime = (dTimeMax + dTimeMin) / 2; //����ѹ��

	double dCurrentTimeLength = dTimeMax - dTimeMin;
	double dTimeLength    = dCurrentTimeLength / TIME_ZOOM_RATE;
	double dOffSet = dTimeLength / 2;

	dTimeMax = dCursorTime + dOffSet;
	dTimeMin = dCursorTime - dOffSet;

	//�ж�dMax-dMin�Ƿ�С��m_dMinTimeInOneSreen
	if (dTimeMax - dTimeMin < m_dMinTimeInOneSreen)
	{
		return;
	}

	if (dTimeMax - m_dMaxTimeInOneSreen >= 0.00001)
	{
		dTimeMax = m_dMaxTimeInOneSreen;
	}
	
	if (dTimeMin <= 0.000001)
	{
		dTimeMin = 0;
	}
	
	m_oTimeAxisDraw.SetMaxMinTime(dTimeMax,dTimeMin);
	CalCurrentDataPos(dTimeMax, dTimeMin);
}

void CDrawMr1200RecordBase::ZoomOutTime_GetTimeCursorXA()
{
	double dTimeMax,dTimeMin;
	m_oTimeAxisDraw.GetMaxMinTime(dTimeMax,dTimeMin);
	double dTime = 0;
	long nX = m_pTimeCursorDraw->GetCurrentCursorPosition();
	m_oTimeAxisDraw.DevicePointToLogicPoint(nX, &dTime);

	double dLeftCurrTimeLength = dTime - dTimeMin;
	double dRightCurrTimeLength = dTimeMax - dTime;
	double dOffset = dLeftCurrTimeLength / TIME_ZOOM_RATE;
	dTimeMin = dTime - dOffset;
	dOffset = dRightCurrTimeLength / TIME_ZOOM_RATE;
	dTimeMax = dTime + dOffset;

	//�ж�dMax-dMin�Ƿ�С��m_dMinTimeInOneSreen
	if (dTimeMax - dTimeMin < m_dMinTimeInOneSreen)
	{
		return;
	}

	if (dTimeMax - m_dMaxTimeInOneSreen >= 0.00001)
	{
		dTimeMax = m_dMaxTimeInOneSreen;
	}

	if (dTimeMin <= 0.000001)
	{
		dTimeMin = 0;
	}

	m_oTimeAxisDraw.SetMaxMinTime(dTimeMax,dTimeMin);
	CalCurrentDataPos(dTimeMax, dTimeMin);
}

void CDrawMr1200RecordBase::ZoomOutTime_GetTimeCursorXAXB()
{
	double dTemp;
	double dTimeMax,dTimeMin;
	long nTimeCursorXA = 0, nTimeCursorXB = 0;
	m_pTimeCursorDraw->GetTwoCursorPosition(nTimeCursorXA, nTimeCursorXB);
	m_oTimeAxisDraw.DevicePointToLogicPoint(nTimeCursorXA, &dTimeMin);
	m_oTimeAxisDraw.DevicePointToLogicPoint(nTimeCursorXB, &dTimeMax);
	
	if (dTimeMin > dTimeMax)
	{
		dTemp = dTimeMax;
		dTimeMax = dTimeMin;
		dTimeMin = dTemp;
	}
	
	//�ж�dMax-dMin�Ƿ�С��m_dMinTimeInOneSreen
	if (dTimeMax - dTimeMin < m_dMinTimeInOneSreen)
	{
		return;
	}

	if (dTimeMax - m_dMaxTimeInOneSreen >= 0.00001)
	{
		dTimeMax = m_dMaxTimeInOneSreen;
	}
	
	if (dTimeMin <= 0.000001)
	{
		dTimeMin = 0;
	}

	m_oTimeAxisDraw.SetMaxMinTime(dTimeMax,dTimeMin);
	CalCurrentDataPos(dTimeMax, dTimeMin);
}

void CDrawMr1200RecordBase::ZoomOutTime(long nMode)
{
	if (m_pTimeCursorDraw ==NULL)
	{
	}
	else
	{	
		switch(nMode)
		{
		case 0:
			{
				ZoomOutTime_GetTimeCenter();
			}
			break;
		case 1:
			{
				ZoomOutTime_GetTimeCursorXAXB();
			}
			break;
		case 2:
			{
				ZoomOutTime_GetTimeCursorXA();
			}
			break;
		default:
			break;
		}
	}
}

void CDrawMr1200RecordBase::ZoomInTime(long nMode)
{
	if (m_pTimeCursorDraw ==NULL)
	{
	}
	else
	{
		switch(nMode)
		{
		case 0:
			{
				ZoomInTime_GetTimeCenter();
			}
			break;
		case 1:
			{
				ZoomInTime_GetTimeCursorXAXB();
			}
			break;
		case 2:
			{
				ZoomInTime_GetTimeCursorXA();
			}
			break;
		default:
			break;
		}
	}
}

void CDrawMr1200RecordBase::ZoomInChan()
{
	if (m_pCurrDrawVariable == NULL)
	{
		return;
	}
	
	if (!m_pCurrDrawVariable->CanZoomY()) 
	{
		return;
	}
	
// 	CRect rect = m_pCurrDrawVariable->m_rcBorder;
// 	long nWidth = rect.Width();
// 	long nHeight = (long)(rect.Height() * VER_ZOOM_RATE);
// 	long nChange = (nHeight - rect.Height()) / 2; 
// 	long nCurrentTop = rect.top;
// 	long nCurrentBom = rect.bottom;
// 	long nTop = nCurrentTop - nChange;
// 	long nBottom = nCurrentBom + nChange;
// 	long nX = 0;
//	
//	m_pCurrDrawVariable->ExpandBorder(nX,nChange,nX,nChange); 
// 			if (nTop >= m_rcWaveDraw.top && nBottom <= m_rcWaveDraw.bottom)//����Ŵ����Ȼ�ڲ��λ��Ƶ�������
// 			{
// 				m_pCurrDrawVariable->ExpandBorder(nX,nChange,nX,nChange); 
// 			}
// 			else
// 			{
// 				//������Ƴ���,���ԭ��û�г�������ô����Ϊ��ǰ��������ײ�����Сֵ
// 				if (nCurrentTop >= m_rcWaveDraw.top && nCurrentBom <= m_rcWaveDraw.bottom) 
// 				{
// 					nChange = min(nCurrentTop - m_rcWaveDraw.top , m_rcWaveDraw.bottom - nCurrentBom );
// 					m_pCurrDrawVariable->ExpandBorder(nX,nChange,nX,nChange); 
// 				}
// 				else
// 				{
// 				}
// 			}
	m_pCurrDrawVariable->Zoom(2);
	AdjustChanState();
	
	SaveRecordDrawObjectControl();
}

void CDrawMr1200RecordBase::ZoomOutChan()
{
// 	CRect rect = m_pCurrDrawVariable->m_rcBorder;
// 	long nWidth = rect.Width();
// 	long nrcHeight = rect.Height();
// 	
// 	if (nrcHeight > RECORDDRAW_ANALOG_MINHEIGHT) //ֻ�е�ǰ��ʾ���������Сֵʱ����ѹ��
// 	{
// 		long  nHeight = (long)((double)nrcHeight / VER_ZOOM_RATE);
// 		long nX = 0;
// 		
// 		if (nHeight < RECORDDRAW_ANALOG_MINHEIGHT) //����С����С�߶�
// 		{
// 			nHeight = RECORDDRAW_ANALOG_MINHEIGHT;
// 		}
// 		
// 		long nChange = 0 - (nrcHeight - nHeight) / 2;
// 		
// 		m_pCurrDrawVariable->ExpandBorder(nX,nChange,nX,nChange); 
// 		AdjustChanState();
// 		
// 	}

// 	if (nrcHeight > RANGESTATEAXIS_MIN_LENGTH) //ֻ�е�ǰ��ʾ���������Сֵʱ����ѹ��
// 	{
// 		long  nHeight = (long)((double)nrcHeight / VER_ZOOM_RATE);
// 		long nX = 0;
// 		
// 		if (nHeight < RANGESTATEAXIS_MIN_LENGTH) //����С����С�߶�
// 		{
// 			nHeight = RANGESTATEAXIS_MIN_LENGTH;
// 		}
// 		
// 		long nChange = 0 - (nrcHeight - nHeight) / 2;
// 		
// 		m_pCurrDrawVariable->ExpandBorder(nX,nChange,nX,nChange); 
// 		AdjustChanState();
// 		
// 	}

	m_pCurrDrawVariable->Zoom(0.5);
	AdjustChanState();
	
	SaveRecordDrawObjectControl();
}
// 
// void CDrawMr1200RecordBase::DrawMainBack(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
// {
// 	CRect rc = GetBorder();//m_rcBorder;
// 	rc.right = m_rcNameAndRangeAxis.right;
// 	rc.left = 0;
// 	rc.top = 0;
// 	rc.bottom = m_rcTimeAxis.bottom;
// 	pDC->FillSolidRect(rc, g_crDrawBackColor);
// 	
// 	rc = m_rcTimeAxis;
// 	rc.right++;
// 	pDC->FillSolidRect(rc, g_crDrawBackColor);
// 	
// 	DrawWaveAreaBorder(pDC);
// 	
// 	//ʱ����
// 	m_oTimeAxisDraw.Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
// 	
// 	//�������
// 	DrawGrid(pDC);
// }
// 
// void CDrawMr1200RecordBase::DrawMainEx(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
// {
// 	DrawMainBack(pDC, fZoomRatio, ptOffset, dwDrawFlag);
// 
// 	CDrawVariable *pDraw = NULL;
// 	POS pos = GetHeadPosition();
// 	double dCoef = 0;
// 	double dOffset = 0;
// 	CRgn rgn;
// 
// 	//����ͨ�����ƺ�����
// 	rgn.CreateRectRgn(m_rcNameAndRangeAxis.left, m_rcNameAndRangeAxis.top, m_rcNameAndRangeAxis.right, m_rcTimeAxis.bottom);
// 	pDC->SelectClipRgn(&rgn);
// 
// 	while (pos != NULL)
// 	{
// 		pDraw = (CDrawVariable*)GetNext(pos);
// 		pDraw->Draw(pDC, fZoomRatio, ptOffset, VARIABLE_DRAW_STYLE_NAME | VARIABLE_DRAW_STYLE_AXIS);
// 	}
// 
// 	//����ͨ������
// 	rgn.DeleteObject();
// 	rgn.CreateRectRgnIndirect(m_rcWaveDraw);
// 	pDC->SelectClipRgn(&rgn);
// 	pos = GetHeadPosition();
// 
// 	//��������
// 	pos = GetHeadPosition();
// 
// 	if (m_pRecordTest->m_oMR1200SysAnalyseMngr.bShowMidLine)
// 	{
// 		while (pos != NULL)
// 		{
// 			pDraw = (CDrawVariable*)GetNext(pos);
// 			pDraw->Draw(pDC, fZoomRatio, ptOffset, VARIABLE_DRAW_STYLE_CENTER);
// 		}
// 	}
// 
// 	DrawMain_Wave(pDC, fZoomRatio, ptOffset, dwDrawFlag);
// 
// 	pDC->SelectClipRgn(NULL);
// 
// 	rgn.DeleteObject();
// }
// 
// void CDrawMr1200RecordBase::DrawMain(double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
// {	
// 	CDC *pDC = m_oDrawMemDC.GetDC();
// 	DrawMainEx(pDC, fZoomRatio, ptOffset, dwDrawFlag);
// }
// 
// void CDrawMr1200RecordBase::DrawMain_Wave(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
// {
// 	CDrawVariable *pDraw = NULL;
// 	POS pos = GetHeadPosition();
// 	double dCoef = 0;
// 	double dOffset = 0;
// 
// 	pos = GetHeadPosition();
// 	while (pos != NULL)
// 	{
// 		pDraw = (CDrawVariable*)GetNext(pos);
// 		pDraw->LogicPointToDevicePoint(dCoef, dOffset, m_oDrawBufferPos);
// 		pDraw->Draw(pDC, fZoomRatio, ptOffset, VARIABLE_DRAW_STYLE_WAVE);
// 		pDraw->DrawAttrs(pDC, fZoomRatio, ptOffset, dwDrawFlag, m_oDrawBufferPos);
// 	}
// }
// 
// void CDrawMr1200RecordBase::DrawWaveAreaBorder(CDC *pDC)
// {
// 	CPen pen1(PS_SOLID, 1, g_crDrawAreaLeftTopFrom);
// 	CPen pen2(PS_SOLID, 1, g_crDrawAreaRightBottomFrom);
// 	CPen *pPen = NULL;
// 	long nIndex = 0;
// 
// 	pPen = pDC->SelectObject(&pen1);
// 
// 	for (nIndex=0; nIndex<MrDraw::g_snWaveDrawAreaGap; nIndex++)
// 	{
// 		pDC->MoveTo(m_rcWaveDrawEx.left + nIndex, m_rcWaveDrawEx.bottom - nIndex);
// 		pDC->LineTo(m_rcWaveDrawEx.left + nIndex, m_rcWaveDrawEx.top + nIndex);
// 		pDC->LineTo(m_rcWaveDrawEx.right - nIndex, m_rcWaveDrawEx.top + nIndex);
// 	}
// 
// 	pDC->SelectObject(pPen);
// 	pen1.DeleteObject();
// 
// 	pPen = pDC->SelectObject(&pen2);
// 	
// 	for (nIndex=0; nIndex<MrDraw::g_snWaveDrawAreaGap; nIndex++)
// 	{
// 		pDC->MoveTo(m_rcWaveDrawEx.left + nIndex+1, m_rcWaveDrawEx.bottom - nIndex);
// 		pDC->LineTo(m_rcWaveDrawEx.right - nIndex, m_rcWaveDrawEx.bottom - nIndex);
// 		pDC->LineTo(m_rcWaveDrawEx.right - nIndex, m_rcWaveDrawEx.top + nIndex-1);
// 	}
// 	
// 	pDC->SelectObject(pPen);
// 	pen2.DeleteObject();
// 	
// 	pDC->FillSolidRect(m_rcWaveDraw, g_crRecordBackColor);
// }
// 
// void CDrawMr1200RecordBase::DrawGrid(CDC *pDC)
// {
// 	CPen pen(PS_DOT, 1, MrDraw::g_crAxisGrid);
// 	CPen *pPen = pDC->SelectObject(&pen);
// 
// 	CAxisScaleDataList *pScales = &(m_oTimeAxisDraw.m_oTimeAxis.m_listRulerScale);
// 	POS pos = pScales->GetHeadPosition();
// 	CAxisScaleData *pScale = NULL;
// 	UINT nBkMode = pDC->SetBkMode(TRANSPARENT);
// 
// 	long x, y;
// 
// 	//��ֱ�̶�
// 	while (pos != NULL)
// 	{
// 		pScale = pScales->GetNext(pos);
// 		x = pScale->m_ptAxisScale.x;
// 		
// 		if (m_rcWaveDraw.left < x && x < m_rcWaveDraw.right )
// 		{
// 			pDC->MoveTo(x, m_rcWaveDraw.top);
// 			pDC->LineTo(x, m_rcWaveDraw.bottom);
// 		}
// 	}
// 
// 	//ˮƽ�̶�
// 	long nHeight = m_rcWaveDraw.Height();
// 	long nCount = nHeight / 50;
// 	double dGap = nHeight;
// 	dGap = dGap / nCount;
// //	nCount--;
// 	y = m_rcWaveDraw.top;
// 
// 	for (long nIndex=1; nIndex<nCount+1; nIndex++)
// 	{
// 		y = (long)(m_rcWaveDraw.top + 50 * nIndex);
// 		pDC->MoveTo(m_rcWaveDraw.left, y);
// 		pDC->LineTo(m_rcWaveDraw.right, y);
// 	}
// 
// 	pen.DeleteObject();
// 	pDC->SelectObject(pPen);
// 	pDC->SetBkMode(nBkMode);
// }

void CDrawMr1200RecordBase::SetParentWnd(CWnd* pParentWnd)
{
	CXRecordDrawBase::SetParentWnd(pParentWnd);
	m_oDrawSysTime.SetParentWnd(pParentWnd);
}
// 
// void CDrawMr1200RecordBase::SetBorder(CDC *pDC, const CRect &rect, BOOL bUseClipRect)
// {
// 	CXDrawElements::SetBorder(rect);
// 	CRect rc = rect;
// 	CreateDrawMemDC(pDC, rc);
// 	
// 	long nTop		= rc.top;
// 	long nLeft		= rc.left;
// 	long nRight		= rc.right-1;
// 	long nBottom	= rc.bottom;
// 	
// 	m_rcWaveDrawEx.left = nLeft + MrDraw::g_snNameandAxisRectWidth;
// 	m_rcWaveDrawEx.top = nTop;
// 	m_rcWaveDrawEx.right = nRight;
// 	m_rcWaveDrawEx.bottom = nBottom - MrDraw::g_snTimeAxisHeight;
// 	m_rcWaveDraw = m_rcWaveDrawEx;
// 	m_rcWaveDraw.DeflateRect(MrDraw::g_snWaveDrawAreaGap, MrDraw::g_snWaveDrawAreaGap);
// 	m_rcWaveDraw.bottom++;
// 	m_rcWaveDraw.right++;
// 
// 	m_rcNameAndRangeAxis = CRect(nLeft , nTop , nLeft + MrDraw::g_snNameandAxisRectWidth , nBottom - MrDraw::g_snTimeAxisHeight);
// 	m_rcTimeAxis		 = CRect(nLeft + MrDraw::g_snNameandAxisRectWidth ,nBottom - MrDraw::g_snTimeAxisHeight, nRight, nBottom );
// 	
// 	if (m_pTimeCursorDraw)
// 	{
// 		m_pTimeCursorDraw->SetBorder(m_rcWaveDraw);
// 	}
// 	
// 	m_oTimeAxisDraw.SetBorder(m_rcTimeAxis, TRUE);
// }

BOOL CDrawMr1200RecordBase::CalCurrentDataPos(double dMax,double dMin)
{
	if (m_pRefBuffer == NULL)
	{
		return FALSE;
	}
	
	double dMaxTime = dMax;
	double dMinTime = dMin;

	/////////////���㵱ǰ��ͼ���ݵķ�Χ,��ȡ�����
	double dTimeLength = dMaxTime - dMinTime;
	double dTimeMaxLength = m_dMaxTimeInOneSreen;
	
	if ( dMaxTime< 0 || dMinTime > dTimeMaxLength) //��������ò�������Ϊ���ᳬ����Χ
	{
		MrDraw::InitDrawBuffPos(&m_oDrawBufferPos);
		return TRUE;
	}
	else
	{
		//�������ݵ�ʱ�������յ㣬��Ϊ���ݷ�Χ��0~dTimeMaxLength
		dMinTime = max(0,dMin); 
		dMaxTime = min(dMax,dTimeMaxLength);
	}
	
	dTimeLength = dMaxTime - dMinTime;
	
	////////////////////////////
	long nNeedDataLength = (long)(dTimeLength * m_nSamRateForDraw);//��������ʹ��������
	long nBufferLen  = m_pRefBuffer->GetBufferLength();
	long nDataLength = m_pRefBuffer->GetDataLength();
	long nFillBeginPos = m_pRefBuffer->GetDataFillBeginPosition();
	long nDrawPoints = m_pPointBuffer->GetBufferLength();

	long nGap = MrDraw::CalGap(nNeedDataLength, nDrawPoints, m_nMaxGapValue);
	
	if (nNeedDataLength > nDrawPoints)
	{
		nNeedDataLength = nNeedDataLength / nGap * nGap;//����ʵ��ʹ�õ���������С�ڵ�������ֵ
	}
	
	m_oDrawBufferPos.nGap = nGap;
	
	long nBegin = (long)(dMinTime * m_nSamRateForDraw);//�������>=0

	if (nBegin < 0)
	{
		nBegin = 0;
	}

	if (nDataLength < nBufferLen)//��ѭ��
	{ 
		if (nBegin >= nBufferLen)
		{
			nBegin -= nBufferLen;
		}
		
		long nEnd   = nBegin + nNeedDataLength ;//�����յ�

		if (nFillBeginPos >= nEnd) //���㹻������
		{
			SetDrawDataRange(nBegin,nBegin + nNeedDataLength - 1);
		}
		else //�в�������
		{
			m_oDrawBufferPos.nBufLength	   = nFillBeginPos - nBegin;
			SetDrawDataRange(nBegin,nFillBeginPos  - 1);
		}
	}
	else//һ��ʹ�����µ�����
	{		
		//nBegin += nFillBeginPos; //�������ѭ���� ��ô���µ���Ҫ��nFillBeginPos��ʼ��fdp add 2010.6.1
		if (nBegin >= nBufferLen) //˵�������µ�����
		{
			nBegin -= nBufferLen;
			long nEnd   = nBegin + nNeedDataLength ;//�����յ�

			if (nEnd >= nFillBeginPos)
			{
				nEnd = nFillBeginPos;
			}

			SetDrawDataRange(nBegin,nEnd - 1);

		}
		else
		{
			long nEnd   = nBegin + nNeedDataLength ;//�����յ�

			if (nEnd <= nBufferLen)
			{
				SetDrawDataRange(nBegin,nEnd - 1);
			} 
			else
			{
				nEnd -= nBufferLen;
				SetDrawDataRange(nBegin,nBufferLen-1,long(0),nEnd-1);
			}
		}
		
	}

	CalXPos(nNeedDataLength / nGap);

	return TRUE;
}

void CDrawMr1200RecordBase::ZoomInTime_GetTimeCursorXA()
{
	double dTimeMax,dTimeMin;
	m_oTimeAxisDraw.GetMaxMinTime(dTimeMax,dTimeMin);
	double dTime = 0;
	long nX = m_pTimeCursorDraw->GetCurrentCursorPosition();
	m_oTimeAxisDraw.DevicePointToLogicPoint(nX, &dTime);
	
	double dLeftCurrTimeLength = dTime - dTimeMin;
	double dRightCurrTimeLength = dTimeMax - dTime;
	double dOffset = dLeftCurrTimeLength * TIME_ZOOM_RATE;
	dTimeMin = dTime - dOffset;
	dOffset = dRightCurrTimeLength * TIME_ZOOM_RATE;
	dTimeMax = dTime + dOffset;
	
	//�ж�dMax-dMin�Ƿ�С��m_dMinTimeInOneSreen
	if (dTimeMax - dTimeMin < m_dMinTimeInOneSreen)
	{
		return;
	}
	
	if (dTimeMax - m_dMaxTimeInOneSreen >= 0.00001)
	{
		dTimeMax = m_dMaxTimeInOneSreen;
	}
	
	if (dTimeMin <= 0.000001)
	{
		dTimeMin = 0;
	}
	
	m_oTimeAxisDraw.SetMaxMinTime(dTimeMax,dTimeMin);
	CalCurrentDataPos(dTimeMax, dTimeMin);
}

void CDrawMr1200RecordBase::ZoomInTime_GetTimeCenter()
{
		double dTimeMax,dTimeMin;
		m_oTimeAxisDraw.GetMaxMinTime(dTimeMax,dTimeMin);
		double dCurrentTimeLength = dTimeMax - dTimeMin;
		double dTimeLength    = dCurrentTimeLength * TIME_ZOOM_RATE;
		double dCursorTime = (dTimeMax + dTimeMin) / 2;//����չ��
		dTimeMin = dTimeMin - dTimeLength;
		dTimeMax = dTimeMax + dTimeLength;

		double dRecordMaxTime = m_pRefBuffer->GetDataLength();
		dRecordMaxTime /= m_pRecordTest->g_nSampleRate;
		
		if (dTimeMax - m_dMaxTimeInOneSreen >= 0.00001)
		{
			dTimeMax = m_dMaxTimeInOneSreen;
		}
	
		if (dTimeMax - dRecordMaxTime >= 0.00001)
		{
			dTimeMax = dRecordMaxTime;
		}
		
		if (dTimeMin <= 0.000001)
		{
			dTimeMin = 0;
		}
		
		m_oTimeAxisDraw.SetMaxMinTime(dTimeMax,dTimeMin);
		CalCurrentDataPos(dTimeMax,dTimeMin);
}

void CDrawMr1200RecordBase::ZoomInTime_GetTimeCursorXAXB()
{
	//���������ַŴ�ʽ��û��ʱ�����
}

void CDrawMr1200RecordBase::AddAttrsDraw()
{
	POS pos = GetHeadPosition();
	CDrawVariable *pVariable = NULL;
	CRtVariables *pRtVariables = m_pRecordTest->m_pVariables;
	CRtVariable  *pRtVariable = NULL;

	while (pos != NULL)
	{
		pVariable = (CDrawVariable *)GetNext(pos);
		pRtVariable = (CRtVariable *)pRtVariables->FindByName(pVariable->m_strName);

		if (pRtVariable == NULL)
		{
			continue;
		}

		ASSERT (pRtVariable == pVariable->m_pXDrawDataRef);
		pVariable->AddAttrsDraw(pRtVariable);
	}
}

long CDrawMr1200RecordBase::GetCalAttrBeginPos(long nTimeCursorPos)
{
	long nCalBegin = 0;

	long nPoints = m_pPointBuffer->GetCurrUseLength();
	long nWidth  = m_rcWaveDraw.Width();
	long nLeft   = m_rcWaveDraw.left;
	
	long nLeftPos = (nTimeCursorPos - nLeft) * nPoints / nWidth;
	long nGap = m_oDrawBufferPos.nGap;
	
	long nBeginPos1 = m_oDrawBufferPos.nBuf1BeginPos;
	
	long nBufferLen = m_pRefBuffer->GetBufferLength();
	long nDataLen   = m_pRefBuffer->GetDataLength();
	long nFillBegin = m_pRefBuffer->GetDataFillBeginPosition();
	
	nCalBegin = nBeginPos1 + nGap * nLeftPos;
	
	if (nCalBegin < 0)
	{
		return -1;
	}
	
	if (nBufferLen > nDataLen)
	{
	} 
	else
	{
		if (nCalBegin > nBufferLen)
		{
			nCalBegin -= nBufferLen;
		}
	}

	return nCalBegin;
}

void CDrawMr1200RecordBase::SaveRecordDrawObjectControl()
{
	CDrawVariable *pDraw = NULL;
	POS pos = m_oVariableMngr.GetHeadPosition();
	
	
	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->SaveDrawControl();
	}
}

void CDrawMr1200RecordBase::InitRecordDrawObjectPosByControl()
{
	ASSERT (m_pRecordDrawObjcontrol != NULL);
	double dHeightRateOnSize = m_dHeightRateOnSize;
	long nHeight = m_rcWaveDraw.Height();
	long nLeft = m_ptTopLeft.x;
	long nRight = m_rcWaveDraw.right;
	long nTop = 0;
	long nBom = 0;
	PRECORDDRAWOBJECTCONTROL pDrawControl = NULL;
	long nIndex = 0;
	POS  pos = m_oVariableMngr.GetHeadPosition();
	double dDrawVariableHeight = 0;
	double dCenter = 0;
	double dDrawHeight = 0;

	while (pos != NULL)
	{
		CDrawVariable* pDrawVar = (CDrawVariable*)m_oVariableMngr.GetNext(pos);
		pDrawControl = pDrawVar->m_pDrawStruct;

		if (pDrawControl == NULL)
		{
			pDrawVar->SetAttachStruct(&m_pRecordDrawObjcontrol[nIndex]);
		}

		if (pDrawVar->m_nHeight == 0)
		{
			if (pDrawVar->GetClassID() == CMTRDCLASSID_BINARYVARIABLE)
			{
				dDrawHeight = RECORDDRAW_BINARY_HEIGHT;
			}
			else
			{
				dDrawHeight = RECORDDRAW_ANALOG_MINHEIGHT;
			}
		}
		else
		{
			dDrawHeight = pDrawVar->m_nHeight;//pDrawVar->m_nHeight;
			dDrawHeight *= dHeightRateOnSize;
		}

		dDrawVariableHeight = (pDrawControl->dRange / pDrawControl->dRangeGrid) * dDrawHeight;
		dCenter = pDrawControl->dCenter * nHeight;
		nTop = DoubleToLong(dCenter - dDrawVariableHeight);
		nBom = DoubleToLong(dCenter + dDrawVariableHeight);
		
		CRect rc(nLeft , nTop , nRight , nBom);
		rc.top += m_rcWaveDraw.top;
		rc.bottom += m_rcWaveDraw.top;
		pDrawVar->SetClipRect(m_rcWaveDraw);
		pDrawVar->SetBorder(rc);		
		nIndex++;
	}
	
	m_dHeightRateOnSize = 1;

	//����m_pRangeStateAxis�Ĳü�����
	CRect rectRange = m_rcWaveDraw;	
	CDrawVariable *pFirst = (CDrawVariable *)m_oVariableMngr.GetHead();
	
	if (pFirst == NULL)
	{
		return;
	}
	
	rectRange.right = pFirst->m_rcAxis.right + RANGESTATEAXIS_BLOCK_WIDTH / 2;
	rectRange.left = pFirst->m_rcAxis.left;
	m_pRangeStateAxis->SetClipRect(rectRange);
}

void CDrawMr1200RecordBase::InitComtradeChannels(CRcdComtradeFile *pComtradeFile)
{
// 	POS  pos = m_oVariableMngr.GetHeadPosition();
// 	long nIndex = 0;
// 	
// 	while (pos != NULL)
// 	{
// 		CDrawVariable* pDrawVariable = (CDrawVariable*)m_oVariableMngr.GetNext(pos);
// 		
// 		if (pDrawVariable->GetUse() == 1)
// 		{
// 			UINT nClassID = pDrawVariable->GetClassID();
// 			CMemBuffer_UShort* pBuffer = pDrawVariable->m_pnAttachBuffer;
// 			
// 			if (nClassID == CMTRDCLASSID_ANALOGVARIABLE) 
// 			{
// 				CDrawAnalogVariable* pAnalog = (CDrawAnalogVariable*) pDrawVariable;
// 				CComtradeAnalogData* pNew = new CComtradeAnalogData();
// 				pNew->m_pnAttachBuffer = pBuffer->GetBuffer();
// 				pComtradeFile->AddTail(pNew);
// 				pNew->m_strName = pAnalog->m_strName;
// 				pNew->m_strUnit = pAnalog->m_strUnit;
// 				pNew->m_strPhaseID = pAnalog->m_strPhaseID;
// 				pNew->m_dCoefValue = *pAnalog->m_dCoefValue;
// 				pNew->m_dZeroValue = *pAnalog->m_dZeroValue;
// 				nIndex++;
// 				double dRange = pAnalog->GetRange();
// 				pNew->m_dSecondaryValue = OUT_RANGE / dRange;
// 				pNew->m_nChannelIndex = nIndex;
// 			}
// 			else if (nClassID == CMTRDCLASSID_BINARYVARIABLE) 
// 			{
// 				CDrawBinaryVariable* pBinary = (CDrawBinaryVariable*)pDrawVariable;
// 				CComtradeBinaryData* pNew = new CComtradeBinaryData();
// 				pNew->m_pnAttachBuffer = pBuffer->GetBuffer();
// 				pComtradeFile->AddTail(pNew);
// 				nIndex++;
// 				pNew->m_strName = pBinary->m_strName;
// 				pNew->m_nChannelIndex = nIndex;
// 				pNew->m_nDataIndex = pBinary->m_nChanIndex;
// 			}
// 			else
// 			{
// 			}
// 		}
// 	}
}

UINT  CDrawMr1200RecordBase::SaveComtradeFileThread(LPVOID pParam)
{
// 	CDrawMr1200RecordBase *pWnd = (CDrawMr1200RecordBase*)pParam;
// 	
// 	ASSERT (g_theRecordApp.m_pRecordTest != NULL);
// 	pWnd->SetInRecordProcessThreadState(TRUE);
// 	g_theRecordApp.SetCanFireSysMessage(FALSE);
// 	
// 	CComtradeMngr* pComtradeMngr = CComtradeMngr::CreateCComtradeMngr();
// 	COMTRADEFILE *pFile = &(pComtradeMngr->m_oComtradeFile);
// 	
// 	//����ļ�·�������Ӻ�׺��	
// 	CString strFilePath = pFile->strFilePath;
// 	strFilePath += pFile->strFileName;
// 	//����ļ����淶Χ
// 	long nSaveMode = pFile->nFileSaveMode;
// 	long nBegin1,nBegin2,nLen1,nLen2;
// 	pWnd->GetComtradeSaveDataPos(nSaveMode,nBegin1,nLen1,nBegin2,nLen2);
// 	
// 	long nIndex = 0;
// 	pComtradeMngr->Init();
// 	pComtradeMngr->GetSaveTimeRange(nBegin1,nLen1,nBegin2,nLen2);
// 	pComtradeMngr->m_nSamAmount = 1;
// 	pComtradeMngr->m_pdSamRate = new double[1];
// 	pComtradeMngr->m_pdSamRate[0] = pWnd->m_nSamRateForDraw;
// 	pComtradeMngr->m_dFreq = 50;
// 	pComtradeMngr->m_pnDataPoints = new long[1];
// 	
// 	pComtradeMngr->m_nBufferLen = pWnd->m_pRefBuffer->GetBufferLength();
// 	if (nSaveMode == 0)//ȫ������
// 	{
// 		pComtradeMngr->m_pnDataPoints[0] = pWnd->m_pRefBuffer->GetDataLength();
// 	}
// 	else
// 	{
// 	}
// 	
// 	pWnd->InitComtradeChannels();
// 	
// 	memcpy(&(pComtradeMngr->m_oFirstPointTime),&g_oFirstDataTime,sizeof(RTTIME));
// 
// 	memcpy(&(pComtradeMngr->m_oTrigPointTime),&g_oStartupTime,sizeof(RTTIME));
// 	
// 	pComtradeMngr->SaveComtradeFile(strFilePath);
// 	CComtradeMngr::Release();
// 	
// 	g_theRecordApp.SetCanFireSysMessage(TRUE);
// 	pWnd->SetInRecordProcessThreadState(FALSE);
	
	return 0;
}

void CDrawMr1200RecordBase::SetInRecordProcessThreadState(BOOL bInState = TRUE)
{

}

void CDrawMr1200RecordBase::GetComtradeSaveDataPos(long nMode,long& nBegin1,long& nLen1,long& nBegin2,long& nLen2)
{
// 	nBegin1 = -1;
// 	nLen1   = -1;
// 	nLen2   = -1;
// 	nBegin2 = -1;
// 
// 	long nXA,nXB;
// 
// 	if (m_pRefBuffer == NULL)
// 	{
// 		return;
// 	}
// 
// 	long nDataLength = m_pRefBuffer->GetDataLength();
// 	long nDataFillBegin = m_pRefBuffer->GetDataFillBeginPosition();
// 	long nBufferLen    = m_pRefBuffer->GetBufferLength();
// 		
// 	if (nDataFillBegin == nBufferLen)
// 	{
// 		nDataFillBegin = 0;
// 	}
// 
// 	if (nMode == COMTRADEFILE_SAVE_MODE_CURSOR)
// 	{
// 		if (m_pTimeCursorDraw != NULL)
// 		{
// 			m_pTimeCursorDraw->GetTwoCursorPosition(nXA,nXB);
// 
// 			if (nXA == nXB)
// 			{
// 				return;
// 			}
// 			
// 			long nBufBeginPos1 = m_oDrawBufferPos.nBuf1BeginPos;
// 			long nBufBeginPos2 = m_oDrawBufferPos.nBuf2BeginPos;
// 			long nBufEndPos1   = m_oDrawBufferPos.nBuf1EndPos;
// 			long nBufEndPos2   = m_oDrawBufferPos.nBuf2EndPos;
// 			long nGap		   = m_oDrawBufferPos.nGap;
// 			long nMax = max(nXA,nXB);
// 			long nMin = min(nXA,nXB);
// 			long nWidth = m_rcWaveDraw.Width();
// 			long nPoints = m_pPointBuffer->GetCurrUseLength();
// 			long nLeft = (nMin - m_rcWaveDraw.left) * nPoints / nWidth;
// 			long nRight = (nMax - m_rcWaveDraw.left) * nPoints / nWidth;
// 			long nCalBegin  = nBufBeginPos1 + nLeft * nGap;
// 			long nCalEnd    = nBufBeginPos1 + nRight * nGap;
// 					
// 			if (nDataLength == nBufferLen)//ѭ��
// 			{
// 				if(nCalBegin >= nBufferLen)//������������µ�һ��
// 				{
// 					nCalBegin -= nBufferLen;
// 					nCalEnd   -= nBufferLen;
// 					
// 					if (nCalBegin > nDataFillBegin)
// 					{
// 						nBegin2 = -1;
// 						nLen2   = -1;
// 						nBegin1 = -1;
// 						nLen1   = -1;
// 						return;
// 					}
// 
// 					if(nCalEnd > nDataFillBegin)
// 					{ 
// 						nCalEnd = nDataFillBegin;
// 					}
// 					
// 					nBegin2 = -1;
// 					nLen2   = -1;
// 					nBegin1 = nCalBegin;
// 					nLen1   = nCalEnd - nCalBegin;
// 				}
// 				else
// 				{
// 					if(nCalEnd <= nBufferLen)//�������ݾɵ�һ��
// 					{
// 						nBegin2 = -1;
// 						nLen2   = -1;
// 						nBegin1 = nCalBegin;
// 						nLen1   = nCalEnd - nCalBegin;			
// 					}
// 					else
// 					{
// 						nCalEnd -= nBufferLen;
// 
// 						if (nCalEnd > nDataFillBegin)
// 						{
// 							nCalEnd = nDataFillBegin;
// 						}
// 
// 						nBegin2 = 0;
// 						nLen2   = nCalEnd;
// 						nLen1   = nBufferLen - nCalBegin;
// 						nBegin1 = nCalBegin;
// 					}
// 				}
// 			}
// 			else
// 			{
// 				if (nCalEnd < 0 || nCalBegin > nDataFillBegin) 
// 				{
// 					nBegin2 = -1;
// 					nLen2   = -1;
// 					nBegin1 = -1;
// 					nLen1   = -1;
// 				}
// 				else
// 				{
// 					nBegin2 = -1;
// 					nLen2   = -1;
// 					nBegin1 = nCalBegin;
// 					nLen1   = nCalEnd - nCalBegin;
// 				}
// 
// 			}
// 		}
// 		else
// 		{
// 			return;
// 		}		
// 	}
// 	else
// 	{
// 		if (nDataLength == nBufferLen)//ѭ��
// 		{
// 			nBegin2 = 0;
// 			nLen2   = nDataFillBegin;
// 			nLen1   = nDataLength - nDataFillBegin;
// 			nBegin1 = nDataFillBegin;
// 		}
// 		else
// 		{
// 			nBegin2 = -1;
// 			nLen2   = -1;
// 			nBegin1 = 0;
// 			nLen1   = nDataFillBegin;
// 		}
// 	}
}

void CDrawMr1200RecordBase::DrawSaveComtradeFileState(CDC *pDC, CRect rcBorder, long nTotal, long nIndex)
{
// 	LOGFONT lf = InitLogFont();
// 	lf.lfHeight = 16;
// 	lf.lfWeight = 400;
// 	
// 	CString str;
// 	double dCoef = nIndex;
// 	dCoef /= nTotal;
// 	CString strFormat = GetLanguageStringByID(gs_strLanguage_msSaveComtradeFile);
// 	CComtradeMngr* pComtradeMngr = CComtradeMngr::CreateCComtradeMngr();
// 	str.Format(strFormat, pComtradeMngr->m_oComtradeFile.strFileName, dCoef*100);
// 	pComtradeMngr->Release();
// 	
// 	pDC->Rectangle(rcBorder);
// 	COLORREF cr = pDC->SetTextColor(RGB(255, 0, 0));
// 	long nMode = pDC->SetBkMode(TRANSPARENT);
// 	rcBorder.top += DRAW_HEIGHT/2;
// 	rcBorder.bottom -= DRAW_HEIGHT/2;
// 	pDC->DrawText(str, rcBorder, DT_CENTER | DT_VCENTER);
// 	pDC->SetBkMode(nMode);
// 	pDC->SetTextColor(cr);
}

void CDrawMr1200RecordBase::FireTimeAxisChangedSysOptr(double dTOffset)
{
// 	long nXa, nXb;
// 	m_pTimeCursorDraw->GetTwoCursorPosition(nXa, nXb);
// 	long nCurr = m_pTimeCursorDraw->GetCurrentCursorPosition();
// 	
// 	if (nCurr == nXb)
// 	{
// 		nXb = nXa;
// 		nXa = nCurr;
// 	}
// 
// 	m_oTimeAxisDraw.DevicePointToLogicPoint(nXa, &g_dCursorTime[1]);
// 	m_oTimeAxisDraw.DevicePointToLogicPoint(nXb, &g_dCursorTime[2]);
// 	__int64 n64Time = g_dCursorTime[1] * g_dwSampleRate;
// 	g_dCursorTime[1] = n64Time;
// 	g_dCursorTime[1] /= g_dwSampleRate;
// 
// 	n64Time = g_dCursorTime[2] * g_dwSampleRate;
// 	g_dCursorTime[2] = n64Time;
// 	g_dCursorTime[2] /= g_dwSampleRate;
// 
// 	g_dCursorTime[0] = fabs(g_dCursorTime[1] - g_dCursorTime[2]);
// 	g_dCursorTime[1] += dTOffset;
// 	g_dCursorTime[2] += dTOffset;
// 	g_theRecordApp.FireSysOptrMsg(MR1200_SYSOPTR_ANALYSE_TIMERCURRSOR_MOVE ,SIT_DELTAT | SIT_T1TIME | SIT_T2TIME, (LPARAM)(g_dCursorTime));
}

CDrawVariable* CDrawMr1200RecordBase::GetNextVariable(CDrawVariable *pCurr)
{
	POS pos = Find(pCurr);
	CDrawVariable *pFind = NULL;

	if (pos == NULL)
	{
		pos = GetHeadPosition();
	}
	else
	{
		GetNext(pos);
	}

	if (pos == NULL)
	{
		pos = GetHeadPosition();
	}

	pFind = (CDrawVariable *)GetAt(pos);

	return pFind;
}


CDrawVariable* CDrawMr1200RecordBase::GetPrevVariable(CDrawVariable *pCurr)
{
	POS pos = Find(pCurr);
	CDrawVariable *pFind = NULL;

	if (pos == NULL)
	{
		pos = GetTailPosition();
	}
	else
	{
		GetPrev(pos);
	}

	if (pos == NULL)
	{
		pos = GetTailPosition();
	}

	pFind = (CDrawVariable *)GetAt(pos);

	return pFind;
}
