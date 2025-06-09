// Mr1200RecordDrawBase.cpp: implementation of the CDrawMr1200RecordBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecordTestDrawBase.h"
#include "../Comtrade/ComtradeMngr.h"
#include "../MR1200BaseApp.h"

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

CRecordTestDrawBase::CRecordTestDrawBase()
{
	m_pRcdComtradeFile = NULL;
	m_pRefBuffer			= NULL;
	SetRecordDataTimeLength(0);
	m_dMinTimeInOneSreen          = 0;
	m_rcTimeandProgress     = CRect(0,0,0,0); 

	m_nMaxGapValue = MAX_DRAWGAP2;
	SetMaxShowOneSreen ( MAX_DRAWGAP2 * AnalyseWnd_MaxDrawlength / m_nSamRateForDraw);

	//绘图点的起始和终止位置
	m_dDrawBeginTime = 0;
	m_dDrawEndTime = 0;

	MrDraw::InitDrawBuffPos(&m_oDrawBufferPos);
	
	g_dCursorTime[0] = 0;
	g_dCursorTime[1] = 0;
	g_dCursorTime[2] = 0;

	m_pRecordTest = NULL;

	for(long nIndex = 0; nIndex < MAX_MR1200_CHANNELS; nIndex++)
	{
		m_ppRecordBuffer[nIndex] = NULL;
	}

}

CRecordTestDrawBase::~CRecordTestDrawBase()
{
	if (m_pRecordTest != NULL)
	{
		g_theRecordApp.Delete(m_pRecordTest);
	}

	m_pRecordTest = NULL;

	//2023-7-22  lijunqing 从CXRecordDrawBase移动过来
	if (m_pRcdComtradeFile != NULL)
	{
		CRcdComtradeFileMngr::CloseComtradeFile(m_pRcdComtradeFile);
	}

	m_pRcdComtradeFile = NULL;

}


CMemBufferInterface* CRecordTestDrawBase::GetDefaultRefBuffer()
{
	long nIndex = 0;

	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRecordBuffer[nIndex] != NULL)
		{
			return m_ppRecordBuffer[nIndex];
		}
	}

	return NULL;
}

void CRecordTestDrawBase::ClearBuffer()
{
	for(long nIndex = 0 ; nIndex < MAX_MR1200_CHANNELS; nIndex ++)
	{
		m_ppRecordBuffer[nIndex]   = NULL;
	}

	RemoveAll();
	m_oVariableMngr.DeleteAll();

}

void CRecordTestDrawBase::Init()
{
}

void CRecordTestDrawBase::AdjustChanState()
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

void CRecordTestDrawBase::SelectNextChannel(CDrawBase *pChannel)
{	
}

void CRecordTestDrawBase::SelectPrevChannel(CDrawBase *pChannel)
{

}

void CRecordTestDrawBase::SelectNextChannel()
{
	if (m_pCurrDrawVariable == NULL)
	{
		m_pCurrDrawVariable = (CDrawVariable*)GetHead();
	}

	if (ReCompositor() == TRUE)//重新排序
	{
		m_pCurrDrawVariable->SetSelect(FALSE);
		m_pCurrDrawVariable = (CDrawVariable*)GetNextVariable(m_pCurrDrawVariable);
		m_pCurrDrawVariable->SetSelect(TRUE);
		m_pRangeStateAxis->AttachDrawObject(m_pCurrDrawVariable);
		AdjustChanState();	
	}
}

void CRecordTestDrawBase::SelectPrevChannel()
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

void CRecordTestDrawBase::MoveChanDown()
{
	if (m_pCurrDrawVariable == NULL)
	{
		m_pCurrDrawVariable = (CDrawVariable*)GetHead();
	}

	if (m_pCurrDrawVariable != NULL)//CXRecordDrawBase中需要给m_pCurrDrawVariable赋值
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

void CRecordTestDrawBase::MoveChanUp()
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

//获取当前坐标范围之内的有效绘图数据时间
void CRecordTestDrawBase::InitDrawBeginEndTime()
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
void CRecordTestDrawBase::MoveLeft()
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
void CRecordTestDrawBase::MoveRight()
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

void CRecordTestDrawBase::ArrowLeft()
{
	if (m_pTimeCursorDraw != NULL)
	{
		m_pTimeCursorDraw->Move(-1,0);			
	}
}

void CRecordTestDrawBase::ArrowRight()
{
	if (m_pTimeCursorDraw != NULL)
	{
		m_pTimeCursorDraw->Move(1,0);
	}
}

void CRecordTestDrawBase::ArrowDown()
{
	if (m_pTimeCursorDraw != NULL)
	{
		long nCurrentCursorID = m_pTimeCursorDraw->GetCurrCursorID();
		nCurrentCursorID = !nCurrentCursorID;
		m_pTimeCursorDraw->SetCurrentCursor(nCurrentCursorID);
	}
}

void CRecordTestDrawBase::ArrowUp()
{
	if (m_pTimeCursorDraw != NULL)
	{
		long nCurrentCursorID = m_pTimeCursorDraw->GetCurrCursorID();
		nCurrentCursorID = !nCurrentCursorID;
		m_pTimeCursorDraw->SetCurrentCursor(nCurrentCursorID);
	}
}


void CRecordTestDrawBase::ZoomOutTime_GetTimeCenter()
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

void CRecordTestDrawBase::ZoomOutTime_GetTimeCursorXA()
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

void CRecordTestDrawBase::ZoomOutTime_GetTimeCursorXAXB()
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

void CRecordTestDrawBase::ZoomOutTime(long nMode)
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

void CRecordTestDrawBase::ZoomInTime(long nMode)
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

void CRecordTestDrawBase::ZoomInChan()
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
	m_pCurrDrawVariable->Zoom(2);
	AdjustChanState();
	
	SaveRecordDrawObjectControl();
}

void CRecordTestDrawBase::ZoomOutChan()
{
// 	CRect rect = m_pCurrDrawVariable->m_rcBorder;
// 	long nWidth = rect.Width();
// 	long nrcHeight = rect.Height();
// 	
// 	if (nrcHeight > RECORDDRAW_ANALOG_MINHEIGHT) //只有当前显示区域大于最小值时才能压缩
// 	{
// 		long  nHeight = (long)((double)nrcHeight / VER_ZOOM_RATE);
// 		long nX = 0;
// 		
// 		if (nHeight < RECORDDRAW_ANALOG_MINHEIGHT) //不能小于最小高度
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

// 	if (nrcHeight > RANGESTATEAXIS_MIN_LENGTH) //只有当前显示区域大于最小值时才能压缩
// 	{
// 		long  nHeight = (long)((double)nrcHeight / VER_ZOOM_RATE);
// 		long nX = 0;
// 		
// 		if (nHeight < RANGESTATEAXIS_MIN_LENGTH) //不能小于最小高度
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
// 	//时间轴
// 	m_oTimeAxisDraw.Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
// 	
// 	//网格绘制
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
// 	//绘制通道名称和坐标
// 	rgn.CreateRectRgn(m_rcNameAndRangeAxis.left, m_rcNameAndRangeAxis.top, m_rcNameAndRangeAxis.right, m_rcTimeAxis.bottom);
// 	pDC->SelectClipRgn(&rgn);
// 
// 	while (pos != NULL)
// 	{
// 		pDraw = (CDrawVariable*)GetNext(pos);
// 		pDraw->Draw(pDC, fZoomRatio, ptOffset, VARIABLE_DRAW_STYLE_NAME | VARIABLE_DRAW_STYLE_AXIS);
// 	}
// 
// 	//绘制通道波形
// 	rgn.DeleteObject();
// 	rgn.CreateRectRgnIndirect(m_rcWaveDraw);
// 	pDC->SelectClipRgn(&rgn);
// 	pos = GetHeadPosition();
// 
// 	//绘制零线
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
// 	//垂直刻度
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
// 	//水平刻度
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

void CRecordTestDrawBase::SetParentWnd(CWnd* pParentWnd)
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

BOOL CRecordTestDrawBase::CalCurrentDataPos(double dMax,double dMin)
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
		MrDraw::InitDrawBuffPos(&m_oDrawBufferPos);
		return TRUE;
	}
	else
	{
		//计算数据的时间起点和终点，因为数据范围是0~dTimeMaxLength
        dMinTime = max(0.0,dMin);
		dMaxTime = min(dMax,dTimeMaxLength);
	}
	
	dTimeLength = dMaxTime - dMinTime;
	
	////////////////////////////
	long nNeedDataLength = (long)(dTimeLength * m_nSamRateForDraw);//计算理论使用数据量
	long nBufferLen  = m_pRefBuffer->GetBufferLength();
	long nDataLength = m_pRefBuffer->GetDataLength();
	long nFillBeginPos = m_pRefBuffer->GetDataFillBeginPosition();
	long nDrawPoints = m_pPointBuffer->GetBufferLength();

	long nGap = MrDraw::CalGap(nNeedDataLength, nDrawPoints, m_nMaxGapValue);
	
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

			SetDrawDataRange(nBegin,nEnd - 1);

		}
		else
		{
			long nEnd   = nBegin + nNeedDataLength ;//理论终点

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

void CRecordTestDrawBase::ZoomInTime_GetTimeCursorXA()
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

void CRecordTestDrawBase::ZoomInTime_GetTimeCenter()
{
		double dTimeMax,dTimeMin;
		m_oTimeAxisDraw.GetMaxMinTime(dTimeMax,dTimeMin);
		double dCurrentTimeLength = dTimeMax - dTimeMin;
		double dTimeLength    = dCurrentTimeLength * TIME_ZOOM_RATE;
		double dCursorTime = (dTimeMax + dTimeMin) / 2;//中心展开
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

void CRecordTestDrawBase::ZoomInTime_GetTimeCursorXAXB()
{
	//不能有这种放大方式，没法时间相乘
}


long CRecordTestDrawBase::GetTotalPoints()
{
	if (m_pRcdComtradeFile->m_pnDataPoints == NULL) 
	{
		return 0;
	}

	return m_pRcdComtradeFile->m_pnDataPoints[0];
}

long CRecordTestDrawBase::GetSampleRate()
{
	return (long)(m_pRcdComtradeFile->m_pdSamRate[0]);
}

void CRecordTestDrawBase::AddAttrsDraw()
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

long CRecordTestDrawBase::GetCalAttrBeginPos(long nTimeCursorPos)
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

void CRecordTestDrawBase::SaveRecordDrawObjectControl()
{
	CDrawVariable *pDraw = NULL;
	POS pos = m_oVariableMngr.GetHeadPosition();
	
	
	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->SaveDrawControl();
	}
}

void CRecordTestDrawBase::InitRecordDrawObjectPosByControl()
{
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
		ASSERT (m_pRecordDrawObjcontrol != NULL);

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
		dDrawVariableHeight /= 2;
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

	//设置m_pRangeStateAxis的裁剪区域
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

void CRecordTestDrawBase::AdjustAxisRange()
{
	ASSERT (m_pRecordDrawObjcontrol != NULL);
	ASSERT (m_pRecordDrawObjcontrol == m_pRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl);
	
	PRECORDDRAWOBJECTCONTROL p = m_pRecordDrawObjcontrol;
	long nIndex = 0;
	POS pos = m_oVariableMngr.GetHeadPosition();
	CDrawVariable *pVariable = NULL;

	while (pos != NULL)
	{
		pVariable = (CDrawVariable *)m_oVariableMngr.GetNext(pos);

		if (pVariable->GetClassID() == CMTRDCLASSID_ANALOGVARIABLE)
		{
			((CDrawAnalogVariable*)pVariable)->SetRange(p->dRange);
		}

		p++;
	}
}

void CRecordTestDrawBase::InitComtradeChannels(CRcdComtradeFile *pComtradeFile)
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

UINT  CRecordTestDrawBase::SaveComtradeFileThread(LPVOID pParam)
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
// 	//获得文件路径，不加后缀名	
// 	CString strFilePath = pFile->strFilePath;
// 	strFilePath += pFile->strFileName;
// 	//获得文件保存范围
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
// 	if (nSaveMode == 0)//全部保存
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

void CRecordTestDrawBase::SetInRecordProcessThreadState(BOOL bInState = TRUE)
{

}

void CRecordTestDrawBase::GetComtradeSaveDataPos(long nMode,long& nBegin1,long& nLen1,long& nBegin2,long& nLen2)
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
// 			if (nDataLength == nBufferLen)//循环
// 			{
// 				if(nCalBegin >= nBufferLen)//计算的数据在新的一端
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
// 					if(nCalEnd <= nBufferLen)//都在数据旧的一端
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
// 		if (nDataLength == nBufferLen)//循环
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

void CRecordTestDrawBase::DrawSaveComtradeFileState(CDC *pDC, CRect rcBorder, long nTotal, long nIndex)
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

void CRecordTestDrawBase::FireTimeAxisChangedSysOptr(double dTOffset)
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

CDrawVariable* CRecordTestDrawBase::GetNextVariable(CDrawVariable *pCurr)
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


CDrawVariable* CRecordTestDrawBase::GetPrevVariable(CDrawVariable *pCurr)
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

//////////////////////////////////////////////////////////////////////////
//
void CRecordTestDrawBase::CreateDrawVariableByRecordTest(int& nAnalogChanAmount, int& nBinaryChanAmount)
{
	CExBaseList *pVariables = m_pRecordTest->m_pVariables;
	nAnalogChanAmount = 0;
	nBinaryChanAmount = 0;

	long nAmount = pVariables->GetCount();
	long nIndex = 0;

	int nCenter = VARIABLE_MIN_DEFAULT_HEIGHT / 2;
	int j =0 ;
	long nCurrentChans = 0;

	for(nIndex = 0 ; nIndex < nAmount ; nIndex ++)
	{
		CRtVariable* pVariable = (CRtVariable*)pVariables->GetAt(nIndex);
		UINT nClassID = pVariable->GetClassID();

		if (pVariable->GetVariableUseState() != 1)
		{
			continue;
		}

		if(nClassID == RTCLASSID_BINARYVARIABLE)//开关通道
		{
			AddBinaryDrawVariable(pVariable, nCurrentChans);
			nBinaryChanAmount++;
		}
		else if (nClassID == RTCLASSID_SINGLEVARIABLE) //单信号通道
		{
			if (NULL == AddAnalogDrawVariable(pVariable, nCurrentChans, nAnalogChanAmount))
			{
				continue;
			}

			nAnalogChanAmount++;
		}
		else 
		{
		}

		nCurrentChans++;
	}
}

void CRecordTestDrawBase::AddBinaryDrawVariable(CExBaseObject* pVar, long &nCurrentChans)
{
	ASSERT (m_pRecordDrawObjcontrol != NULL);
	PRECORDDRAWOBJECTCONTROL pSetVar = &(m_pRecordDrawObjcontrol[nCurrentChans]); //fdp add 2010.7.7

	CDrawVariable* pDrawVariable = NULL;
	CMemBufferInterface* pRecordBuffer = NULL;
	CRtVariable* pVariable = (CRtVariable*)pVar;
	CRtMemBufferChannel *pChannelBuffer = pVariable->m_pChannelBuffer;
	CRtBinaryVariable* pBinary = (CRtBinaryVariable*)pVariable;

	if (pChannelBuffer != NULL)
	{
		pRecordBuffer = pChannelBuffer->GetRecordMemBuffer();
	}
	else
	{
		pRecordBuffer = pVariable->m_pAttachRecordBuffer;
	}

	// 	if (IsUseMapFileBuffer())
	// 	{
	// 		if (pRecordBuffer == NULL)
	// 		{
	// 			long nChIndex = GetAnalogVariableCount();
	// 			nChIndex += pBinary->m_nIndex / 16;
	// 			pRecordBuffer = CMrOnlineRecordEx::g_pMrOnlineRecordEx->GetChBuffer(nChIndex);
	// 		}
	// 		else
	// 		{
	// 			pRecordBuffer = CMrOnlineRecordEx::FindRecordBufferByID(pRecordBuffer->m_strBufferID);
	// 		}
	// 
	// 	}

	ASSERT (pRecordBuffer != NULL);

	if (pRecordBuffer == NULL)
	{
		return;
	}

	pDrawVariable = new CDrawBinaryVariable();//创建开关量绘图对象
	CDrawBinaryVariable* pDrawBinary = (CDrawBinaryVariable*)pDrawVariable;	

	pDrawBinary->m_crForeColor = pBinary->m_crColor; 
	pDrawBinary->m_strName = pBinary->m_strName;//开关量名称
	pDrawBinary->m_pptAttachDrawBuffer = m_pPointBuffer;//关联绘图缓存
	pDrawBinary->m_nChanIndex = pBinary->m_nIndex;//索引				
	m_ppRecordBuffer[nCurrentChans] = pRecordBuffer;   
	pDrawBinary->m_pnAttachBuffer = pRecordBuffer;//初始化数据缓存	
	pDrawBinary->SetUse(pBinary->m_nVariableUse);
	pDrawBinary->m_nShow = pSetVar->nShow;
	pDrawBinary->SetParentWnd(m_pParentWnd);
	m_oVariableMngr.AddTail(pDrawVariable);
	pDrawBinary->SetSelect(FALSE);

	pDrawBinary->SetAttachStruct(pSetVar);//fdp add 2010.7.7
}

CDrawAnalogVariable* CRecordTestDrawBase::AddAnalogDrawVariable(CExBaseObject* pVar, long nCurrentChans, long nChIndex)
{
	CRtSingleVariable* pSingle = (CRtSingleVariable*)pVar;

	CDrawAnalogVariable* pAnalog = NewAnalogVariable();
	InitAnalogDrawVariable(pSingle, nCurrentChans, pAnalog, TRUE);

	return pAnalog;
}

CDrawAnalogVariable* CRecordTestDrawBase::NewAnalogVariable()
{
	CDrawAnalogVariable* pAnalog = new CDrawAnalogVariable();
	return pAnalog;
}

void CRecordTestDrawBase::InitAnalogDrawVariable(CRtSingleVariable* pSingle, long &nCurrentChans, CDrawAnalogVariable *pAnalog, BOOL bNew)
{
	CMemBufferInterface* pRecordBuffer = NULL;

	if (pSingle->m_pChannelBuffer != NULL)
	{
		pRecordBuffer = pSingle->m_pChannelBuffer->GetRecordMemBuffer();
	}
	else
	{
		pRecordBuffer = pSingle->m_pAttachRecordBuffer;
	}

	ASSERT (pRecordBuffer != NULL);

	pAnalog->m_strPhaseID = pSingle->m_strPhaseID;
	pAnalog->m_strUnit = pSingle->m_strUnit;
	pAnalog->m_pXDrawDataRef = pSingle;

	//各个通道添加单位
	if (pSingle->m_nType == RTVARIABLE_TYPE_U) 
	{
		pAnalog->SetUnit("V");
	}
	else if(pSingle->m_nType ==RTVARIABLE_TYPE_I)
	{
		pAnalog->SetUnit("A");
	}
	else
	{
	}

#ifdef _SHOW_PARA			
	//temp，添加一个参数
	pAnalog->AddPara(Para_FundValue);
#endif

	CRecordTest *pRecordTest = (CRecordTest*)pSingle->GetAncestor(RTCLASSID_RECORDTEST);
	double *pdCoef = NULL,  *pdZero = NULL;
	long nChIndex = pRecordTest->FindCoefAndZero(pSingle, &pdCoef, &pdZero);

	ASSERT (m_pRecordDrawObjcontrol != NULL);
	PRECORDDRAWOBJECTCONTROL pSetVar = &(m_pRecordDrawObjcontrol[nChIndex]);//fdp add 2010.7.7
	pAnalog->m_nShow = pSetVar->nShow;
	pAnalog->SetRange(pSetVar->dRange);	
	pAnalog->SetUse(pSingle->m_nVariableUse);
	pAnalog->m_crForeColor = pSingle->m_crColor;
	pAnalog->m_pptAttachDrawBuffer = m_pPointBuffer;//关联绘图缓存
	pAnalog->SetAdjustValue(pdZero, pdCoef);
	pAnalog->m_strName = pSingle->m_strName;//模拟量名称
	pAnalog->m_strID = pSingle->m_strID;

	pAnalog->m_pnAttachBuffer = pRecordBuffer;//初始化数据缓存

	pAnalog->SetParentWnd(m_pParentWnd);
	pAnalog->SetSelect(FALSE);

	if (bNew)
	{
		m_ppRecordBuffer[nChIndex] = pRecordBuffer;
		m_oVariableMngr.AddTail(pAnalog);
	}

	pAnalog->SetAttachStruct(pSetVar);//fdp add 2010.7.7
}
