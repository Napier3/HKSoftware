// RecordDrawMngrBase.cpp: implementation of the CRecordDrawMngrBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecordDrawMngrBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// long CRecordDrawMngrBase::g_snWaveDrawAreaGap				= 2;	//15;
// long CRecordDrawMngrBase::g_snBottomRectHeight			= 0;	//15;
// long CRecordDrawMngrBase::g_snTimeandProgressRectHeight	= 0;	//5;

CRecordDrawMngrBase::CRecordDrawMngrBase()
{
	m_pRefBuffer			= NULL;
	SetRecordDataTimeLength(0);
	m_dMinTimeInOneSreen          = 0;
	m_rcTimeandProgress     = CRect(0,0,0,0); 

	m_nMaxGapValue = MAX_DRAWGAP2;
	SetMaxShowOneSreen ( MAX_DRAWGAP2 * AnalyseWnd_MaxDrawlength / m_nSamRateForDraw);

	//绘图点的起始和终止位置
	m_dDrawBeginTime = 0;
	m_dDrawEndTime = 0;
}

CRecordDrawMngrBase::~CRecordDrawMngrBase()
{
}

void CRecordDrawMngrBase::Init()
{
}

void CRecordDrawMngrBase::AdjustChanState()
{	
	if (m_pCurrDrawVariable == NULL) 
	{
		return;
	}

	UINT nClassID = m_pCurrDrawVariable->GetClassID();
	
	if (nClassID == DRAWCLASSID_BINARYVARIABLE) 
	{
		m_pRangeStateAxis->FrozenHead1();
		m_pRangeStateAxis->FrozenHead2();
	}
	else
	{
		m_pRangeStateAxis->FrozenHead1(FALSE);
		m_pRangeStateAxis->FrozenHead2(FALSE);
	}
	
	CRect rcAxis = m_pCurrDrawVariable->m_rcAxis;
	CRect rcRangeStateAxis = CreateRangeVertStateAxisBorder(rcAxis.right, rcAxis.top, rcAxis.bottom);
	m_pRangeStateAxis->SetBorder(rcRangeStateAxis, RANGESTATEAXIS_TYPE_VERT);
}

void CRecordDrawMngrBase::SelectNextChannel(CDrawBase *pChannel)
{	
}

void CRecordDrawMngrBase::SelectPrevChannel(CDrawBase *pChannel)
{

}

void CRecordDrawMngrBase::SelectChannel(CDrawVariable *pVariable)
{
	if (m_pCurrDrawVariable != NULL)
	{
		m_pCurrDrawVariable->SetSelect(FALSE);
	}

	m_pCurrDrawVariable = pVariable;

	if (m_pCurrDrawVariable != NULL)
	{
		m_pCurrDrawVariable->SetSelect(TRUE);
	}
}

void CRecordDrawMngrBase::SelectNextChannel()
{
	if (m_pCurrDrawVariable == NULL)
	{
		m_pCurrDrawVariable = (CDrawVariable*)GetHead();
	}

	if (ReCompositor() == TRUE)//重新排序
	{
		m_pCurrDrawVariable->SetSelect(FALSE);
		m_pCurrDrawVariable = (CDrawVariable*)GetNextByObj(m_pCurrDrawVariable);
		m_pCurrDrawVariable->SetSelect(TRUE);
		m_pRangeStateAxis->AttachDrawObject(m_pCurrDrawVariable);
		AdjustChanState();	
	}
}

void CRecordDrawMngrBase::SelectPrevChannel()
{
	if (m_pCurrDrawVariable == NULL)
	{
		m_pCurrDrawVariable = (CDrawVariable*)GetHead();
	}

	if (ReCompositor() == TRUE)
	{
		m_pCurrDrawVariable->SetSelect(FALSE);
		m_pCurrDrawVariable = (CDrawVariable*)GetPrevByObj(m_pCurrDrawVariable);
		m_pCurrDrawVariable->SetSelect(TRUE);
		m_pRangeStateAxis->AttachDrawObject(m_pCurrDrawVariable);
		AdjustChanState();		
	}
}

void CRecordDrawMngrBase::MoveChanDown()
{
	if (m_pCurrDrawVariable == NULL)
	{
		m_pCurrDrawVariable = (CDrawVariable*)GetHead();
	}

	if (m_pCurrDrawVariable != NULL)//CDrawBaseMngr中需要给m_pCurrDrawVariable赋值
	{
		long nBottom = m_pCurrDrawVariable->m_rcBorder.bottom;
		
		m_pCurrDrawVariable->Move(0 , VER_MOVE_ONCE, TRUE);
// 		if (nBottom + VER_MOVE_ONCE < m_rcWaveDraw.bottom)
// 		{
// 			m_pCurrDrawVariable->Move(0 , VER_MOVE_ONCE);
// 		}
// 		else
// 		{
// 			long nMove = m_rcWaveDraw.bottom - nBottom;
// 			m_pCurrDrawVariable->Move(0 , nMove);
// 		}
		
		AdjustDrawNameRect();
		AdjustChanState();
	}
}

void CRecordDrawMngrBase::MoveChanUp()
{
	if (m_pCurrDrawVariable == NULL)
	{
		m_pCurrDrawVariable = (CDrawVariable*)GetHead();
	}

	if (m_pCurrDrawVariable != NULL)
	{
		long nTop = m_pCurrDrawVariable->m_rcBorder.top;
		
		m_pCurrDrawVariable->Move(0 , 0 - VER_MOVE_ONCE, TRUE);
// 		if (nTop - VER_MOVE_ONCE >= m_rcWaveDraw.top)
// 		{
// 			m_pCurrDrawVariable->Move(0 , 0 - VER_MOVE_ONCE);
// 		}
// 		else
// 		{
// 			long nMove = m_rcWaveDraw.top - nTop;
// 			m_pCurrDrawVariable->Move(0 , nMove);
// 		}
		
		AdjustDrawNameRect();
		AdjustChanState();
	}
}

//获取当前坐标范围之内的有效绘图数据时间
void CRecordDrawMngrBase::InitDrawBeginEndTime()
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

//时间限定范围为0 ~ m_dRecordDataTimeLength
void CRecordDrawMngrBase::MoveLeft()
{
// 	double dMoveOnce = m_oTimeAxisDraw.m_oTimeAxis.GetHorCarryOenGap();
// 	double dMax,dMin;	
// 	double dMaxTime = m_dRecordDataTimeLength;
// 	m_oTimeAxisDraw.GetMaxMinTime(dMax,dMin);
// 	
// 	//设置可以移出的范围
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
//最小时间值设定为0
void CRecordDrawMngrBase::MoveRight()
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

void CRecordDrawMngrBase::ArrowLeft()
{
	if (m_pTimeCursorDraw != NULL)
	{
		m_pTimeCursorDraw->Move(-1,0);			
	}
}

void CRecordDrawMngrBase::ArrowRight()
{
	if (m_pTimeCursorDraw != NULL)
	{
		m_pTimeCursorDraw->Move(1,0);
	}
}

void CRecordDrawMngrBase::ArrowDown()
{
	if (m_pTimeCursorDraw != NULL)
	{
		long nCurrentCursorID = m_pTimeCursorDraw->GetCurrCursorID();
		nCurrentCursorID = !nCurrentCursorID;
		m_pTimeCursorDraw->SetCurrentCursor(nCurrentCursorID);
	}
}

void CRecordDrawMngrBase::ArrowUp()
{
	if (m_pTimeCursorDraw != NULL)
	{
		long nCurrentCursorID = m_pTimeCursorDraw->GetCurrCursorID();
		nCurrentCursorID = !nCurrentCursorID;
		m_pTimeCursorDraw->SetCurrentCursor(nCurrentCursorID);
	}
}


void CRecordDrawMngrBase::ZoomOutTime_GetTimeCenter()
{
	double dTimeMax,dTimeMin, dCursorTime;
	m_oTimeAxisDraw.GetMaxMinTime(dTimeMax,dTimeMin);
	dCursorTime = (dTimeMax + dTimeMin) / 2; //中心压缩

	double dCurrentTimeLength = dTimeMax - dTimeMin;
	double dTimeLength    = dCurrentTimeLength / TIME_ZOOM_RATE;
	double dOffSet = dTimeLength / 2;

	dTimeMax = dCursorTime + dOffSet;
	dTimeMin = dCursorTime - dOffSet;

	//判断dMax-dMin是否小于m_dMinTimeInOneSreen
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

void CRecordDrawMngrBase::ZoomOutTime_GetTimeCursorXA()
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

	//判断dMax-dMin是否小于m_dMinTimeInOneSreen
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

void CRecordDrawMngrBase::ZoomOutTime_GetTimeCursorXAXB()
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
	
	//判断dMax-dMin是否小于m_dMinTimeInOneSreen
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

void CRecordDrawMngrBase::ZoomOutTime(long nMode)
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

void CRecordDrawMngrBase::ZoomInTime(long nMode)
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

void CRecordDrawMngrBase::ZoomInChan()
{
	if (m_pCurrDrawVariable != NULL)
	{
		if (m_pCurrDrawVariable->CanZoomY()) 
		{
			CRect rect = m_pCurrDrawVariable->m_rcBorder;
			long nWidth = rect.Width();
			long nHeight = (long)(rect.Height() * VER_ZOOM_RATE);
			long nChange = (nHeight - rect.Height()) / 2; 
			long nCurrentTop = rect.top;
			long nCurrentBom = rect.bottom;
			long nTop = nCurrentTop - nChange;
			long nBottom = nCurrentBom + nChange;
			long nX = 0;
			
			m_pCurrDrawVariable->ExpandBorder(nX,nChange,nX,nChange); 
// 			if (nTop >= m_rcWaveDraw.top && nBottom <= m_rcWaveDraw.bottom)//如果放大后仍然在波形绘制的区域内
// 			{
// 				m_pCurrDrawVariable->ExpandBorder(nX,nChange,nX,nChange); 
// 			}
// 			else
// 			{
// 				//如何限制超出,如果原来没有超过，那么限制为当前当顶部或底部的最小值
// 				if (nCurrentTop >= m_rcWaveDraw.top && nCurrentBom <= m_rcWaveDraw.bottom) 
// 				{
// 					nChange = min(nCurrentTop - m_rcWaveDraw.top , m_rcWaveDraw.bottom - nCurrentBom );
// 					m_pCurrDrawVariable->ExpandBorder(nX,nChange,nX,nChange); 
// 				}
// 				else
// 				{
// 				}
// 			}
			
			AdjustChanState();
			
		}
	}
}

void CRecordDrawMngrBase::ZoomOutChan()
{
	if (m_pCurrDrawVariable != NULL)
	{
		if (m_pCurrDrawVariable->CanZoomY()) 
		{
			CRect rect = m_pCurrDrawVariable->m_rcBorder;
			long nWidth = rect.Width();
			long nrcHeight = rect.Height();
			
			if (nrcHeight > RANGESTATEAXIS_MIN_LENGTH) //只有当前显示区域大于最小值时才能压缩
			{
				long  nHeight = (long)((double)nrcHeight / VER_ZOOM_RATE);
				long nX = 0;
				
				if (nHeight < RANGESTATEAXIS_MIN_LENGTH) //不能小于最小高度
				{
					nHeight = RANGESTATEAXIS_MIN_LENGTH;
				}
				
				long nChange = 0 - (nrcHeight - nHeight) / 2;
				
				m_pCurrDrawVariable->ExpandBorder(nX,nChange,nX,nChange); 
				AdjustChanState();
				
			}
			
		}
	}
}

void CRecordDrawMngrBase::DrawMainBack(CDC *pDC)
{
	CRect rc = m_rcBorder;
	rc.right = m_rcNameAndRangeAxis.right;
	rc.left = 0;
	rc.top = 0;
	rc.bottom = m_rcTimeAxis.bottom;
	pDC->FillSolidRect(rc, MrDraw::g_crDrawBackColor);
	
	rc = m_rcTimeAxis;
	rc.right++;
	pDC->FillSolidRect(rc, MrDraw::g_crDrawBackColor);
	
	DrawWaveAreaBorder(pDC);
	
	//时间轴
	m_oTimeAxisDraw.Draw(pDC);
	
	//网格绘制
	DrawGrid(pDC);
}

void CRecordDrawMngrBase::DrawMain(CDC *pDC)
{	
	DrawMainBack(pDC);
	
	CDrawVariable *pDraw = NULL;
	POS pos = GetHeadPosition();
	double dCoef = 0;
	double dOffset = 0;
	CRgn rgn;
	
	//绘制通道名称和坐标
	rgn.CreateRectRgn(m_rcNameAndRangeAxis.left, m_rcNameAndRangeAxis.top, m_rcNameAndRangeAxis.right, m_rcTimeAxis.bottom);
	pDC->SelectClipRgn(&rgn);

	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->Draw(pDC, VARIABLE_DRAW_STYLE_NAME | VARIABLE_DRAW_STYLE_AXIS);
	}

	//绘制通道波形
	rgn.DeleteObject();
	rgn.CreateRectRgnIndirect(m_rcWaveDraw);
	pDC->SelectClipRgn(&rgn);
	pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->LogicPointToDevicePoint(dCoef, dOffset, m_oDrawBufferPos);
		pDraw->Draw(pDC, VARIABLE_DRAW_STYLE_CENTER);
		pDraw->Draw(pDC, VARIABLE_DRAW_STYLE_WAVE);
	}

	pDC->SelectClipRgn(NULL);
}

void CRecordDrawMngrBase::DrawWaveAreaBorder(CDC *pDC)
{
	CPen pen1(PS_SOLID, 1, MrDraw::g_crDrawAreaLeftTopFrom);
	CPen pen2(PS_SOLID, 1, MrDraw::g_crDrawAreaRightBottomFrom);
	CPen *pPen = NULL;
	long nIndex = 0;

	pPen = pDC->SelectObject(&pen1);

	for (nIndex=0; nIndex<MrDraw::g_snWaveDrawAreaGap; nIndex++)
	{
		pDC->MoveTo(m_rcWaveDrawEx.left + nIndex, m_rcWaveDrawEx.bottom - nIndex);
		pDC->LineTo(m_rcWaveDrawEx.left + nIndex, m_rcWaveDrawEx.top + nIndex);
		pDC->LineTo(m_rcWaveDrawEx.right - nIndex, m_rcWaveDrawEx.top + nIndex);
	}

	pDC->SelectObject(pPen);
	pen1.DeleteObject();

	pPen = pDC->SelectObject(&pen2);
	
	for (nIndex=0; nIndex<MrDraw::g_snWaveDrawAreaGap; nIndex++)
	{
		pDC->MoveTo(m_rcWaveDrawEx.left + nIndex+1, m_rcWaveDrawEx.bottom - nIndex);
		pDC->LineTo(m_rcWaveDrawEx.right - nIndex, m_rcWaveDrawEx.bottom - nIndex);
		pDC->LineTo(m_rcWaveDrawEx.right - nIndex, m_rcWaveDrawEx.top + nIndex-1);
	}
	
	pDC->SelectObject(pPen);
	pen2.DeleteObject();
	
	pDC->FillSolidRect(m_rcWaveDraw, RGB(0, 0, 0));
}

void CRecordDrawMngrBase::DrawGrid(CDC *pDC)
{
	CPen pen(PS_DOT, 1, MrDraw::g_crAxisGrid);
	CPen *pPen = pDC->SelectObject(&pen);

	CAxisScaleDataList *pScales = &(m_oTimeAxisDraw.m_oTimeAxis.m_listRulerScale);
	POS pos = pScales->GetHeadPosition();
	CAxisScaleData *pScale = NULL;
	UINT nBkMode = pDC->SetBkMode(TRANSPARENT);

	long x, y;

	//垂直刻度
	while (pos != NULL)
	{
		pScale = pScales->GetNext(pos);
		x = pScale->m_ptAxisScale.x;
		
		if (m_rcWaveDraw.left < x && x < m_rcWaveDraw.right )
		{
			pDC->MoveTo(x, m_rcWaveDraw.top);
			pDC->LineTo(x, m_rcWaveDraw.bottom);
		}
	}

	//水平刻度
	long nHeight = m_rcWaveDraw.Height();
	long nCount = nHeight / 50;
	double dGap = nHeight;
	dGap = dGap / nCount;
//	nCount--;
	y = m_rcWaveDraw.top;

	for (long nIndex=1; nIndex<nCount; nIndex++)
	{
		y = (long)(m_rcWaveDraw.top + dGap * nIndex);
		pDC->MoveTo(m_rcWaveDraw.left, y);
		pDC->LineTo(m_rcWaveDraw.right, y);
	}

	pen.DeleteObject();
	pDC->SelectObject(pPen);
	pDC->SetBkMode(nBkMode);
}

void CRecordDrawMngrBase::SetParentWnd(CWnd* pParentWnd)
{
	CDrawBaseMngr::SetParentWnd(pParentWnd);
	m_oDrawSysTime.SetParentWnd(pParentWnd);
}

void CRecordDrawMngrBase::SetBorder(CDC *pDC, const CRect &rect, BOOL bUseClipRect)
{
	CRect rc = rect;
	CreateDrawMemDC(pDC, rc);
	
	long nTop		= rc.top;// + g_snWaveDrawAreaGap;//g_snTimeandProgressRectHeight;
	long nLeft		= rc.left;
	long nRight		= rc.right-1;// - WAVE_BORDER_TO_RIGHT;
	long nBottom	= rc.bottom;// - g_snBottomRectHeight;
	
	m_rcWaveDrawEx.left = nLeft + MrDraw::g_snNameandAxisRectWidth;
	m_rcWaveDrawEx.top = nTop;
	m_rcWaveDrawEx.right = nRight;
	m_rcWaveDrawEx.bottom = nBottom - MrDraw::g_snTimeAxisHeight;
	m_rcWaveDraw = m_rcWaveDrawEx;
	m_rcWaveDraw.DeflateRect(MrDraw::g_snWaveDrawAreaGap, MrDraw::g_snWaveDrawAreaGap);
	m_rcWaveDraw.bottom++;
	m_rcWaveDraw.right++;

	m_rcNameAndRangeAxis = CRect(nLeft , nTop , nLeft + MrDraw::g_snNameandAxisRectWidth , nBottom - MrDraw::g_snTimeAxisHeight);
	m_rcTimeAxis		 = CRect(nLeft + MrDraw::g_snNameandAxisRectWidth ,nBottom - MrDraw::g_snTimeAxisHeight, nRight, nBottom );
	
	if (m_pTimeCursorDraw)
	{
		m_pTimeCursorDraw->SetBorder(m_rcWaveDraw);
	}
	
	m_oTimeAxisDraw.SetBorder(m_rcTimeAxis, TRUE);
}

BOOL CRecordDrawMngrBase::CalCurrentDataPos(double dMax,double dMin)
{
	if (m_pRefBuffer == NULL)
	{
		return FALSE;
	}
	
	double dMaxTime = dMax;
	double dMinTime = dMin;

	/////////////计算当前绘图数据的范围,及取数间隔
	double dTimeLength = dMaxTime - dMinTime;
	double dTimeMaxLength = m_dMaxTimeInOneSreen;
	
	if ( dMaxTime< 0 || dMinTime > dTimeMaxLength) //这个现在用不到，因为不会超出范围
	{
		m_oDrawBufferPos.nBufLength    = 0;
		m_oDrawBufferPos.nBuf1BeginPos = -1;
		m_oDrawBufferPos.nBuf1EndPos   = -1;
		m_oDrawBufferPos.nBuf2EndPos   = -1;
		m_oDrawBufferPos.nBuf2BeginPos = -1;

		return TRUE;
	}
	else
	{
		//计算数据的时间起点和终点，因为数据范围是0~dTimeMaxLength
		dMinTime = max(0,dMin); 
		dMaxTime = min(dMax,dTimeMaxLength);
	}
	
	dTimeLength = dMaxTime - dMinTime;
	
	////////////////////////////
	long nNeedDataLength = (long)(dTimeLength * m_nSamRateForDraw);//计算理论使用数据量
	long nBufferLen  = m_pRefBuffer->GetBufferLength();
	long nDataLength = m_pRefBuffer->GetDataLength();
	long nFillBeginPos = m_pRefBuffer->GetDataFillBeginPosition();
	long nDrawPoints = m_pPointBuffer->GetBufferLength();
	long nGap = nNeedDataLength / nDrawPoints ;
	
	long nRemain = nNeedDataLength % nDrawPoints ;
	
	if (nRemain > 0)
	{
		nGap ++;
	}
	
	if (nGap <1)
	{
		nGap = 1;
	}
	
	if (nGap > m_nMaxGapValue)
	{
		nGap = m_nMaxGapValue;
	}
	
	if (nNeedDataLength > nDrawPoints)
	{
		nNeedDataLength = nNeedDataLength / nGap * nGap;//计算实际使用的数据量，小于等于理论值
	}
	
	m_oDrawBufferPos.nGap = nGap;
	
	long nBegin = (long)(dMinTime * m_nSamRateForDraw);//理论起点>=0

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
		//nBegin += nFillBeginPos; //如果缓存循环， 那么最新点需要从nFillBeginPos开始，fdp add 2010.6.1
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

void CRecordDrawMngrBase::ZoomInTime_GetTimeCursorXA()
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
	
	//判断dMax-dMin是否小于m_dMinTimeInOneSreen
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

void CRecordDrawMngrBase::ZoomInTime_GetTimeCenter()
{
		double dTimeMax,dTimeMin;
		m_oTimeAxisDraw.GetMaxMinTime(dTimeMax,dTimeMin);
		double dCurrentTimeLength = dTimeMax - dTimeMin;
		double dTimeLength    = dCurrentTimeLength * TIME_ZOOM_RATE;
		double dCursorTime = (dTimeMax + dTimeMin) / 2;//中心展开
		dTimeMin = dTimeMin - dTimeLength;
		dTimeMax = dTimeMax + dTimeLength;

		double dRecordMaxTime = m_pRefBuffer->GetDataLength();
		dRecordMaxTime /= g_dwSampleRate;
		
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

void CRecordDrawMngrBase::ZoomInTime_GetTimeCursorXAXB()
{
	//不能有这种放大方式，没法时间相乘
}