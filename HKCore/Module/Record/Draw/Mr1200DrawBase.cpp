// Mr1200DrawBase.cpp: implementation of the CDrawMr1200Base class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mr1200DrawBase.h"
#include "..\MR1200BaseApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawMr1200Base::CDrawMr1200Base()
{
	m_dHeightRateOnSize = 1;
	m_pCurrDrawObj			= NULL;
	m_pCurrDrawVariable		= NULL;
	m_pPointBuffer			= NULL;

	m_pTimeCursorDraw = new CDrawTimeCursor();
	m_pRangeStateAxis = new CDrawRangeStateAxis();
	m_pRangeStateAxis->SetColor(RGB(0, 0, 255));
	m_crForeColor               = RGB(255, 255, 255);
	m_nMaxGapValue          = MAX_DRAWGAP1;
	m_nSamRateForDraw				= MR1200_SAMPLE_RATE;
	m_pRangeStateAxis->SetMinLength(40);

	m_pRefBuffer = NULL;

	m_rcNameAndRangeAxis = CRect(0,0,0,0);
	m_rcTimeAxis		 = CRect(0,0,0,0);
	m_rcWaveDraw		 = CRect(0,0,0,0);

	m_oTimeAxisDraw.m_oTimeAxis.SetBigSawMinWidth(40);
	m_pRcdComtradeFile = NULL;

	g_crDrawBackColor	= RGB(182,182,182);
	g_crRecordBackColor	= RGB(0,0,0);
	g_crDrawAreaBkColorFrom     = RGB(240, 240, 240);
	g_crDrawAreaBkColorTo       = RGB(255, 255, 255);
	//g_crAxisGrid = RGB(100, 100, 100);
	g_crDrawAreaLeftTopFrom = RGB(90, 90, 90);
	g_crDrawAreaLeftTopTo = RGB(90, 90, 90);
	g_crDrawAreaRightBottomFrom = RGB(210, 210, 210);
	g_crDrawAreaRightBottomTo = RGB(210, 210, 210);
}

CDrawMr1200Base::~CDrawMr1200Base()
{
	if (m_pRangeStateAxis != NULL)
	{
		delete m_pRangeStateAxis;
		m_pRangeStateAxis = NULL;
	}
	
	if (m_pTimeCursorDraw != NULL)
	{
		delete m_pTimeCursorDraw;
		m_pTimeCursorDraw = NULL;
	}	

	if (m_pRecordTest != NULL)
	{
		g_theRecordApp.Delete(m_pRecordTest);
	}

	if (m_pRcdComtradeFile != NULL)
	{
		CRcdComtradeFileMngr::CloseComtradeFile(m_pRcdComtradeFile);
	}

	m_pRecordTest = NULL;
	m_pRcdComtradeFile = NULL;
}

void CDrawMr1200Base::SetVariableMoveCursor(HCURSOR hCursor)
{
	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->SetMoveCursor(hCursor);
	}
}

void CDrawMr1200Base::SetVariableZoomCursor(HCURSOR hCursor)
{
	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->SetZoomCursor(hCursor);
	}
}

void CDrawMr1200Base::SetVariableProhibitCursor(HCURSOR hCursor)
{
	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->SetProhibitCursor(hCursor);
	}
}

void CDrawMr1200Base::SetTimeAxisMoveCursor(HCURSOR hCursor)
{
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetMoveCursor(hCursor);
}

void CDrawMr1200Base::SetTimeAxisZoomCursor(HCURSOR hCursor)
{
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetZoomCursor(hCursor);	
}

void CDrawMr1200Base::SetTimeAxisProhibitCursor(HCURSOR hCursor)
{
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetProhibitCursor(hCursor);	
}

void CDrawMr1200Base::SetParentWnd(CWnd* pParentWnd)
{
	CXDrawElements::SetParentWnd(pParentWnd);

	m_pRangeStateAxis->SetParentWnd(pParentWnd);
	m_pTimeCursorDraw->SetParentWnd(pParentWnd);
	m_oTimeAxisDraw.SetParentWnd(pParentWnd);

	CDrawBase *pDraw = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDraw = (CDrawBase*)GetNext(pos);
		pDraw->SetParentWnd(pParentWnd);
	}
}

void CDrawMr1200Base::AdjustDrawNameRect()
{
	ReCompositor();
	CNameSortMngr oNameSortMngr(this,m_rcNameAndRangeAxis);
}

BOOL CDrawMr1200Base::ReCompositor()
{
	int nAmount = GetCount();
	
	if (nAmount < 1)
	{
		return FALSE;
	}
	else
	{
		POS  pBeginPos = GetHeadPosition();
		POS  pNextPos = pBeginPos;
		POS  pEndPos  = GetTailPosition();
		POS  pPre = pBeginPos;
		POS  pNext = pNextPos;
		long nCenter1 = 0 , nCenter2 = 0 , nTemp = 0;
		
		while(pBeginPos != pEndPos)//重新排序
		{
			pPre = pBeginPos;
			CDrawVariable* pVa = (CDrawVariable*)GetNext(pBeginPos);
			nCenter1 = pVa->m_nYCenter;
			pNextPos = pBeginPos;
			/////////////temp
			CDrawVariable* pTemp = (CDrawVariable*)GetAt(pNextPos);
			//////////////////////////
			while(pNextPos != NULL)
			{
				pNext = pNextPos;
				CDrawVariable* pVb = (CDrawVariable*)GetNext(pNextPos);
				nCenter2 = pVb->m_nYCenter;
				
				if(nCenter1 > nCenter2)
				{
					ChangePosition(pPre,pNext);
					nTemp = nCenter1;
					nCenter1 = nCenter2;
					nCenter2 = nTemp; 
				}				
			}			
		}
	}
	
	return TRUE;
}

BOOL CDrawMr1200Base::InitShowDrawVariables(CXDrawElements &oVariableMngr)
{
	///////////////////////////
	POS pos = oVariableMngr.GetHeadPosition();
	
	while (pos != NULL)
	{
		CDrawVariable* pDrawVariable = (CDrawVariable*)oVariableMngr.GetNext(pos);
		UINT nClassID = pDrawVariable->GetClassID();
		
		if (pDrawVariable->m_nShow > 0)
		{
			AddTail(pDrawVariable);
		}
	}
	
	/////////////////判断是否有当前选中通道
	BOOL bHas = FALSE;
	pos = GetHeadPosition();
	CDrawBase* pDraw = NULL;
	
	while (pos != NULL)
	{
		pDraw = (CDrawBase*)GetNext(pos);
		
		if (pDraw == m_pCurrDrawVariable) 
		{
			bHas = TRUE;
			break;
		}
	}
	
	if (!bHas) 
	{
		pos = GetHeadPosition();
		m_pCurrDrawVariable = (CDrawVariable*)GetAt(pos);
	}

	return bHas;
}

void CDrawMr1200Base::AdjustDrawVariablePosition(BOOL bUseClipRect)
{	
	CDrawBase *pDraw = NULL;

	//遍历查找有多少模拟通道，多少开关通道
	POS pos = GetHeadPosition();
	long nBinaryChans = 0 ;
	long nAnalogChans = 0;
	CRect rcClip = m_rcWaveDraw;
	CRect rcBorder;
	CRect rcAxis;

	while (pos != NULL)
	{
		pDraw = (CDrawBase*)GetNext(pos);
		UINT nClassID = pDraw->GetClassID();

		if (CMTRDCLASSID_ANALOGVARIABLE == nClassID
			|| CMTRDCLASSID_CMPANALOGVARIABLE == nClassID
			|| CMTRDCLASSID_ATTRSPYVARIABLE == nClassID
			|| CMTRDCLASSID_COMPLEXVARIABLE == nClassID)
		{
			nAnalogChans++;
		}
		else if (CMTRDCLASSID_BINARYVARIABLE == nClassID)
		{
			nBinaryChans++;
		}
		else
		{
		}
		
	}
	
	if (nAnalogChans == 0 && nBinaryChans == 0)
	{
		return;
	}
	
	//计算高度
	long nBinaryHeight = nBinaryChans * (RECORDDRAW_BINARY_HEIGHT+RECORDDRAW_OBJECT_GAP);
	long nHeightDraw = m_rcWaveDraw.Height();
	long nAnalogHeight = nHeightDraw - nBinaryHeight;

	double dRatio = nHeightDraw;
	long nChs = nAnalogChans * ANALOG_BINARY_HEIGHT_RATE + nBinaryChans;
	dRatio /= nChs;
	double dAnalogRatio = dRatio * ANALOG_BINARY_HEIGHT_RATE;
	long nMaxHeight = (long)dAnalogRatio;
	double dPos = dAnalogRatio/2;
	nMaxHeight -= 20;
	long nHeight = 0;
	BOOL bFindAxis = FALSE;
	
	pos = GetHeadPosition();
	double dCenter = 0;
	double dHeight = 0;

	//调整模拟量的位置
	while (pos != NULL)
	{
		pDraw = (CDrawBase*)GetNext(pos);
		UINT nClassID = pDraw->GetClassID();
		
		if (CMTRDCLASSID_ANALOGVARIABLE == nClassID
			|| CMTRDCLASSID_CMPANALOGVARIABLE == nClassID
			|| CMTRDCLASSID_ATTRSPYVARIABLE == nClassID
			|| CMTRDCLASSID_COMPLEXVARIABLE == nClassID)
		{
			CDrawAnalogVariable* pAnalog = (CDrawAnalogVariable*)pDraw;
			
			if (bUseClipRect)
			{
				pAnalog->SetClipRect(rcClip);
			}
			
			rcBorder = pAnalog->GetBorder();//m_rcBorder;
			nHeight = rcBorder.Height();

			if (nHeight < nMaxHeight)
			{
				nHeight = nMaxHeight;
			}

			dCenter = dPos / nHeightDraw;
			pAnalog->SaveDrawControl(dCenter);
			dCenter = dCenter * nHeightDraw;
			dHeight = nHeight;
			dHeight /= 2;
			rcBorder.top = DoubleToLong(dCenter - dHeight);
			rcBorder.bottom = rcBorder.top + nHeight;
			rcBorder.top += m_rcWaveDraw.top;
			rcBorder.bottom += m_rcWaveDraw.top;
			
			dPos += dAnalogRatio;

			pAnalog->SetBorder(rcBorder);
			pAnalog->InitAxis(MrDraw::g_snNameandAxisRectWidth);
			
			if (!bFindAxis)
			{
				rcAxis = pAnalog->m_rcAxis;
				bFindAxis = TRUE;
			}
		}
	}
	
	dPos -= dAnalogRatio/2;
	dPos += dRatio/2;

	//开关量
	while (pos != NULL)
	{
		pDraw = (CDrawBase*)GetNext(pos);
		UINT nClassID = pDraw->GetClassID();
		
		if (CMTRDCLASSID_BINARYVARIABLE == nClassID)
		{
			CDrawBinaryVariable* pBinary =(CDrawBinaryVariable*)pDraw;
			
			if (bUseClipRect)
			{
				pBinary->SetClipRect(rcClip);
			}
			
			rcBorder = pBinary->GetBorder();//m_rcBorder;
			nHeight = rcBorder.Height();
			
			dCenter = dPos / nHeightDraw;
			pBinary->SaveDrawControl(dCenter);
			dCenter = dCenter * nHeightDraw;
			dHeight = nHeight;
			dHeight /= 2;
			rcBorder.top = DoubleToLong(dCenter - dHeight);
			rcBorder.bottom = rcBorder.top + nHeight;
			rcBorder.top += m_rcWaveDraw.top;
			rcBorder.bottom += m_rcWaveDraw.top;

			dPos += dRatio;
			pBinary->SetBorder(rcBorder);
			pBinary->InitAxis(MrDraw::g_snNameandAxisRectWidth);
			
			if (!bFindAxis)
			{
				bFindAxis = TRUE;
				rcAxis = pBinary->m_rcAxis;
			}
		}
		else
		{
		}
	}

	//设置裁剪区域
	rcClip = rcAxis;
	rcClip.top = m_ptTopLeft.y;//m_rcBorder.top;
	rcClip.bottom = Bottom();//m_rcBorder.bottom;
	rcClip.right += RANGESTATEAXIS_BLOCK_HEIGHT2 + 1;
	rcClip.left -= RANGESTATEAXIS_BLOCK_HEIGHT2 + 1;
	
	if (bUseClipRect)
	{
		m_pRangeStateAxis->SetClipRect(rcClip);
	}
}

long CDrawMr1200Base::GetTotalPoints()
{
	if (m_pRcdComtradeFile->m_pnDataPoints == NULL) 
	{
		return 0;
	}

	return m_pRcdComtradeFile->m_pnDataPoints[0];
}

long CDrawMr1200Base::GetSampleRate()
{
	return (long)(m_pRcdComtradeFile->m_pdSamRate[0]);
}

void CDrawMr1200Base::SetBorder(const CRect &rect, BOOL bUseClipRect)
{	
	CXDrawElements::SetBorder(rect);

	/////////////////
	long nTop		= rect.top;
	long nLeft		= rect.left;
	long nRight		= rect.right - RECORDDRAW_TOPBOTTOM_GAP;
	long nBottom	= rect.bottom;

	m_rcNameAndRangeAxis = CRect(nLeft , nTop , nLeft + MrDraw::g_snNameandAxisRectWidth , nBottom - MrDraw::g_snTimeAxisHeight);
	
	m_rcTimeAxis		 = CRect(nLeft + MrDraw::g_snNameandAxisRectWidth ,nBottom - MrDraw::g_snTimeAxisHeight, nRight, nBottom );
	m_rcWaveDraw		 = CRect(nLeft + MrDraw::g_snNameandAxisRectWidth ,nTop , nRight, nBottom - MrDraw::g_snTimeAxisHeight);
	m_rcTimeAxis.top -= TIMEAXIS_RANGESTATEAXIS_HEIGHT;
	m_rcWaveDraw.bottom -= TIMEAXIS_RANGESTATEAXIS_HEIGHT;
	
	if (m_pTimeCursorDraw)
	{
		m_pTimeCursorDraw->SetBorder(m_rcWaveDraw);
	}

	m_oTimeAxisDraw.SetBorder(m_rcTimeAxis, TRUE);

	AdjustDrawVariablePosition(bUseClipRect);
}

LONG CDrawMr1200Base::MouseMove(UINT nFlags, CPoint point)
{
	//通道状态坐标，是否被操作
	if (m_pRangeStateAxis->m_pAttachDraw != NULL)
	{
		if (m_pRangeStateAxis->MouseMove(nFlags, point) == DRAW_HAS_OBJECT_SELECTED)
		{
			return DRAW_HAS_OBJECT_SELECTED;
		}
	}
	else
	{
		
	}

	//处理当前选中的对象
	if (m_pCurrDrawObj != NULL)
	{
		if (m_pCurrDrawObj->MouseMove(nFlags, point) == DRAW_HAS_OBJECT_SELECTED)//m_pRangeStateAxis
		{
			if (m_pRangeStateAxis->m_pAttachDraw != NULL)
			{
				m_pRangeStateAxis->MouseMove(point);
			}

			return DRAW_HAS_OBJECT_SELECTED;
		}
	}
	
	//时间坐标轴
	//处理时间坐标轴
	if (m_oTimeAxisDraw.MouseMove(nFlags, point) == DRAW_HAS_OBJECT_SELECTED)
	{
		return DRAW_HAS_OBJECT_SELECTED;
	}
	
	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawMr1200Base::LButtonDown(UINT nFlags, CPoint point) 
{
	//通道状态坐标，是否被操作
	if (m_pRangeStateAxis->m_pAttachDraw != NULL)
	{
		if (m_pRangeStateAxis->LButtonDown(nFlags, point) == DRAW_HAS_OBJECT_SELECTED)
		{
			return DRAW_HAS_OBJECT_SELECTED;
		}
	}
	
	//处理当前选中的对象
	if (m_pCurrDrawObj != NULL)
	{
		if (m_pCurrDrawObj->LButtonDown(nFlags, point) == DRAW_HAS_OBJECT_SELECTED)
		{
			if (m_pRangeStateAxis->m_pAttachDraw != NULL)
			{
				m_pRangeStateAxis->LButtonDown(point);
			}

			return DRAW_HAS_OBJECT_SELECTED;
		}
	}
	else
	{
	}
	
	long nSelect = DRAW_NONE_OBJECT_SELECTED;

	//处理集合对象
	CDrawBase *pDraw = NULL;
	POS pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pDraw = (CDrawBase*)GetNext(pos);
		nSelect = pDraw->LButtonDown(nFlags, point);

		if (DRAW_HAS_OBJECT_SELECTED == nSelect)
		{
			m_pCurrDrawObj = pDraw;
			break;
		}
	}

	//当前选中的是否为通道对象
	if (DRAW_HAS_OBJECT_SELECTED != nSelect)
	{
		if (m_pRangeStateAxis->m_pAttachDraw != NULL)
		{
			m_pCurrDrawObj = NULL;
			m_pRangeStateAxis->DettachVariable();
			
			if (m_pParentWnd != NULL)
			{
				if (::IsWindow(m_pParentWnd->m_hWnd))
				{					
					m_pParentWnd->PostMessage(WM_INVALIDATE_RANGESTATEAXIS, (WPARAM)m_pRangeStateAxis, 0);	
					m_pParentWnd->PostMessage(WM_VARIABLE_SELECT_CHANGED, 0, 0);
				}
			}
		}
	}
	else
	{
		//选中对象是通道
		if (IsDrawVariable(m_pCurrDrawObj))
		{
			AttachRangeStateAxisVariable();
			m_pRangeStateAxis->LButtonDown(nFlags, point);
			
			if (m_pParentWnd != NULL)
			{
				if (::IsWindow(m_pParentWnd->m_hWnd))
				{										
					m_pParentWnd->PostMessage(WM_INVALIDATE_RANGESTATEAXIS, (WPARAM)m_pRangeStateAxis, 0);
					m_pParentWnd->PostMessage(WM_VARIABLE_SELECT_CHANGED, (WPARAM)m_pCurrDrawObj, 0);
				}
			}
	
			if (m_pCurrDrawVariable != NULL)
			{
				m_pCurrDrawVariable->SetSelect(FALSE);
				m_pCurrDrawVariable =(CDrawVariable*)m_pCurrDrawObj;
				m_pCurrDrawVariable->SetSelect(TRUE);

				if (m_pRangeStateAxis->m_pAttachDraw != NULL)
				{
					m_pRangeStateAxis->LButtonDown(point);
				}
			}
		}
		else
		{
		}
	}
	
	//处理时间坐标轴
	if (nSelect != DRAW_HAS_OBJECT_SELECTED)
	{
		nSelect = m_oTimeAxisDraw.LButtonDown(nFlags, point);
	}
	
	if (nSelect == DRAW_NONE_OBJECT_SELECTED)
	{
		nSelect = m_pTimeCursorDraw->LButtonDown(nFlags , point);

		if (nSelect == DRAW_HAS_OBJECT_SELECTED)
		{
			m_pCurrDrawObj = m_pTimeCursorDraw;
		}
	}
	
	return nSelect;
}

LONG CDrawMr1200Base::LButtonDbClick(UINT nFlags, CPoint point) 
{
	//通道状态坐标，是否被操作
	if (m_pRangeStateAxis->m_pAttachDraw != NULL && m_pCurrDrawObj != NULL)
	{
		if (m_pCurrDrawObj->GetShow() == 0)
		{
			m_pCurrDrawObj->SetShow(1);
		}
		else
		{
			m_pCurrDrawObj->SetShow(0);
		}

		if (m_pParentWnd != NULL)
		{
			if (::IsWindow(m_pParentWnd->m_hWnd))
			{					
				m_pParentWnd->PostMessage(WM_VARIABLE_POS_CHANGED, 0, 0);
			}
		}
	}
	
	return DRAW_NONE_OBJECT_SELECTED;
}

void CDrawMr1200Base::AttachRangeStateAxisVariable()
{
	m_pRangeStateAxis->AttachDrawObject(m_pCurrDrawObj);
	CDrawVariable *pVariable = (CDrawVariable*)m_pCurrDrawObj;
	UINT nClassID = pVariable->GetClassID();

	if (nClassID == CMTRDCLASSID_BINARYVARIABLE) 
	{
		m_pRangeStateAxis->FrozenHead1();
		m_pRangeStateAxis->FrozenHead2();
	}
	else
	{
		m_pRangeStateAxis->FrozenHead1(FALSE);
		m_pRangeStateAxis->FrozenHead2(FALSE);
	}

	CRect rcAxis = pVariable->m_rcAxis;
	CRect rcRangeStateAxis = CreateRangeVertStateAxisBorder(rcAxis.right, rcAxis.top, rcAxis.bottom);
	m_pRangeStateAxis->SetBorder(rcRangeStateAxis, RANGESTATEAXIS_TYPE_VERT);
}

LONG CDrawMr1200Base::LButtonUp(UINT nFlags, CPoint point)
{
	//纵向通道状态坐标轴
	if (m_pRangeStateAxis->m_pAttachDraw != NULL)
	{
		if (m_pRangeStateAxis->LButtonUp(nFlags, point) == DRAW_HAS_OBJECT_SELECTED)
		{
			return DRAW_HAS_OBJECT_SELECTED;
		}
	}

	//当前选中的对象
	if (m_pCurrDrawObj != NULL)
	{
		if (DRAW_HAS_OBJECT_SELECTED == m_pCurrDrawObj->LButtonUp(nFlags , point))
		{
			if (m_pRangeStateAxis->m_pAttachDraw != NULL)
			{
				m_pRangeStateAxis->LButtonUp(point);
			}

			if (IsDrawVariable(m_pCurrDrawObj))
			{	
				AttachRangeStateAxisVariable();
			}
			
			return DRAW_HAS_OBJECT_SELECTED;
		}
	}
		
	//时间坐标轴
	if (DRAW_HAS_OBJECT_SELECTED == m_oTimeAxisDraw.LButtonUp(nFlags, point))
	{
		return DRAW_HAS_OBJECT_SELECTED;
	}
	
	//AdjustDrawNameRect();

	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawMr1200Base::RButtonDown(UINT nFlags, CPoint point)
{
	return 0;
}

LONG CDrawMr1200Base::RButtonUp(UINT nFlags, CPoint point)
{
	return 0;
}

void CDrawMr1200Base::Init()
{
}

void CDrawMr1200Base::MoveChannel(CDrawBase *pChannel, double dOffset)
{
}

void CDrawMr1200Base::ZoomChannel(CDrawBase *pChannel, double dRate)
{
}

void CDrawMr1200Base::MoveTimeAxis(double dOffset)
{
}

void CDrawMr1200Base::ZoomTimeAxis(double dRate)
{
}

void CDrawMr1200Base::MoveTimerCursor(double dOffset)
{
}

void CDrawMr1200Base::DrawSubject(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	DrawRangeStateAxis(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	
	m_pTimeCursorDraw->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	m_oTimeAxisDraw.DrawSubject(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}
// 
// void CDrawMr1200Base::Draw(CDC* pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
// {
// 	//时间轴
// 	m_oTimeAxisDraw.Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
// 	
// 	CDrawVariable *pDraw = NULL;
// 	POS pos = GetHeadPosition();
// 	double dCoef = 0;
// 	double dOffset = 0;
// 	//绘制通道
// 	while (pos != NULL)
// 	{
// 		pDraw = (CDrawVariable*)GetNext(pos);
// 		pDraw->LogicPointToDevicePoint(dCoef,dOffset,m_oDrawBufferPos);
// 		pDraw->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
// 	}
// 	
// 	//绘制通道纵向状态坐标
// 	DrawRangeStateAxis(pDC, fZoomRatio, ptOffset, dwDrawFlag);
// 	m_pTimeCursorDraw->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
// }

void CDrawMr1200Base::GetCurrentShowTimeRange(double& dMax, double& dMin)
{
	m_oTimeAxisDraw.GetMaxMinTime(dMax , dMin);
}

void CDrawMr1200Base::SetCurrentShowTimeRange(double dMax, double dMin)
{	
	m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
	CalCurrentDataPos(dMax, dMin);
}

void CDrawMr1200Base::GetTimeRange(double& dMax, double& dMin)
{
	m_oTimeAxisDraw.GetMaxMinTime(dMax , dMin);
	m_oTimeAxisDraw.GetMaxMinTime(dMax , dMin);
}

void CDrawMr1200Base::SetTimeRange(double dMax, double dMin)
{	
	m_oTimeAxisDraw.SetOldMaxMinTime(dMax, dMin);
	m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
}

//这里的计算暂时没有测试
BOOL CDrawMr1200Base::CalCurrentDataPos(double dMax,double dMin)
{
	ASSERT (FALSE);

	return TRUE;
}


void CDrawMr1200Base::CalXPosEx(long nTotalPoints, CMemBuffer_CPoint *pPointBuffer, long nSamRateForDraw, long nGap)
{
	double dMaxTime = 0;
	double dMinTime = 0;
	m_oTimeAxisDraw.m_oTimeAxis.GetMinMaxVal(&dMinTime, &dMaxTime, 0);
	double dCoef = 0;
	int nCenterX = 0;
	m_oTimeAxisDraw.m_oTimeAxis.GetAxisInterface(dCoef, nCenterX);
	double dTimePerPoint = (double)(dMaxTime - dMinTime) / nTotalPoints;
	double dIndex = dMinTime;

	CPoint* pBuffer = pPointBuffer->GetBuffer();
	CPoint* pEnd = pBuffer + nTotalPoints;

	long nIndex = (long)(dMinTime * nSamRateForDraw) / nGap;

	while (pBuffer < pEnd)
	{
		pBuffer->x = (long)(dIndex * dCoef + nCenterX );
		pBuffer++;
		dIndex += dTimePerPoint;
	}

	pPointBuffer->SetCurrUseLength(nTotalPoints);
}

void CDrawMr1200Base::CalXPos(long nTotalPoints)
{
	CalXPosEx(nTotalPoints, m_pPointBuffer, m_nSamRateForDraw, m_oDrawBufferPos.nGap);

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
}

void CDrawMr1200Base::OnTimeAxisPositionchanged()
{
	double dMaxTime = 0;
	double dMinTime = 0;

	m_oTimeAxisDraw.GetMaxMinTime(dMaxTime, dMinTime);
	CalCurrentDataPos(dMaxTime, dMinTime);
}

double CDrawMr1200Base::DecivePointToLogicPointTime(long x)
{
	double dValue = 0;
	m_oTimeAxisDraw.m_oTimeAxis.DevicePointToLogicPoint(x, &dValue);
	return dValue;
}

//////////////////////////////////////////////////////////////////////////
void CDrawMr1200Base::AddAttrsDraw()
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

