// DrawBaseMngr.cpp: implementation of the CDrawBaseMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawBaseMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawBaseMngr::CDrawBaseMngr()
{
	m_pCurrDrawObj			= NULL;
	m_pCurrDrawVariable		= NULL;
	m_pPointBuffer			= NULL;

	m_pTimeCursorDraw = new CDrawTimeCursor();
	m_pRangeStateAxis = new CDrawRangeStateAxis();
	m_pRangeStateAxis->SetColor(RGB(0, 0, 255));
	m_crColor               = RGB(255, 255, 255);
	m_nMaxGapValue          = MAX_DRAWGAP1;
	m_nSamRateForDraw				= STRECORD_SAMPLE_RATE;
	m_pRangeStateAxis->SetMinLength(40);

	m_pRefBuffer = NULL;

	m_rcNameAndRangeAxis = CRect(0,0,0,0);
	m_rcTimeAxis		 = CRect(0,0,0,0);
	m_rcWaveDraw		 = CRect(0,0,0,0);

	m_oTimeAxisDraw.m_oTimeAxis.SetBigSawMinWidth(40);
}

CDrawBaseMngr::~CDrawBaseMngr()
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
}

void CDrawBaseMngr::SetVariableMoveCursor(HCURSOR hCursor)
{
	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->SetMoveCursor(hCursor);
	}
}

void CDrawBaseMngr::SetVariableZoomCursor(HCURSOR hCursor)
{
	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->SetZoomCursor(hCursor);
	}
}

void CDrawBaseMngr::SetVariableProhibitCursor(HCURSOR hCursor)
{
	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->SetProhibitCursor(hCursor);
	}
}

void CDrawBaseMngr::SetTimeAxisMoveCursor(HCURSOR hCursor)
{
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetMoveCursor(hCursor);
}

void CDrawBaseMngr::SetTimeAxisZoomCursor(HCURSOR hCursor)
{
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetZoomCursor(hCursor);	
}

void CDrawBaseMngr::SetTimeAxisProhibitCursor(HCURSOR hCursor)
{
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetProhibitCursor(hCursor);	
}

void CDrawBaseMngr::SetParentWnd(CWnd* pParentWnd)
{
	CDrawBase::SetParentWnd(pParentWnd);

	m_pRangeStateAxis->SetParentWnd(pParentWnd);
	m_pTimeCursorDraw->SetParentWnd(pParentWnd);
	m_oTimeAxisDraw.SetParentWnd(pParentWnd);

	CDrawBase *pDraw = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDraw = GetNext(pos);
		pDraw->SetParentWnd(pParentWnd);
	}
}

void CDrawBaseMngr::AdjustDrawNameRect()
{
	ReCompositor();
	CNameSortMngr oNameSortMngr(this,m_rcNameAndRangeAxis);
}

BOOL CDrawBaseMngr::ReCompositor()
{
	int nAmount = GetCount();
	
	if (nAmount < 1)
	{
		return FALSE;
	}
	else
	{
		long nBeginPos = 0;
		long nEndPos = GetCount() - 1;
		long nNextPos = 0;
		long nCenter1 = 0 , nCenter2 = 0 , nTemp = 0;
	
		while(nBeginPos < nEndPos)//重新排序
		{
			CDrawVariable* pVa = (CDrawVariable*)GetAtIndex(nBeginPos);
			nCenter1 = pVa->m_nYCenter;
			nNextPos = nBeginPos+1;

			while(nNextPos <= nEndPos)
			{
				CDrawVariable* pVb = (CDrawVariable*)GetAtIndex(nNextPos);
				nCenter2 = pVb->m_nYCenter;

				if(nCenter1 > nCenter2)
				{
					ChangePosition(nBeginPos,nNextPos);
					nTemp = nCenter1;
					nCenter1 = nCenter2;
					nCenter2 = nTemp; 
				}

				nNextPos++;
			}	

			nBeginPos++;
		}

	}
	
	return TRUE;
}

BOOL CDrawBaseMngr::ReCompositorEx()
{
	int nAmount = GetCount();
	
	if (nAmount < 1)
	{
		return FALSE;
	}
	else
	{
		long nBeginPos = 0;
		long nEndPos = GetCount() - 1;
		long nNextPos = 0;
		
		long nCenter1 = 0 , nCenter2 = 0 , nTemp = 0;

		while(nBeginPos < nEndPos)//重新排序
		{
			CDrawVariable* pVa = (CDrawVariable*)GetAtIndex(nBeginPos);
			nCenter1 = pVa->m_nYCenter;
			nNextPos = nBeginPos+1;

			while(nNextPos <= nEndPos)
			{
				CDrawVariable* pVb = (CDrawVariable*)GetAtIndex(nNextPos);
				nCenter2 = pVb->m_nYCenter;

				if(nCenter1 > nCenter2)
				{
					ChangePosition(nBeginPos,nNextPos);
					nTemp = nCenter1;
					nCenter1 = nCenter2;
					nCenter2 = nTemp; 
				}

				nNextPos++;
			}	

			nBeginPos++;
		}

	}
	
	return TRUE;
}

BOOL CDrawBaseMngr::InitShowDrawVariables(CDrawVariablesMngr &oVariableMngr)
{
	RemoveAll();
	
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
		pDraw = GetNext(pos);
		
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

void CDrawBaseMngr::AdjustDrawVariablePosition(BOOL bUseClipRect)
{	
	CDrawBase *pDraw = NULL;

	//遍历查找有多少模拟通道，多少开关通道
	POS pos = GetHeadPosition();
	long nBinaryChans = 0 ;
	long nAnalogChans = 0;

	while (pos != NULL)
	{
		pDraw = GetNext(pos);
		UINT nClassID = pDraw->GetClassID();

		if (DRAWCLASSID_ANALOGVARIABLE == nClassID || DRAWCLASSID_ATTRSPYVARIABLE == nClassID || DRAWCLASSID_COMPLEXVARIABLE == nClassID)
		{
			nAnalogChans++;
		}
		else if (DRAWCLASSID_BINARYVARIABLE == nClassID)
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
	
	//计算开关量高度
	///////////////
	CRect rcBinary = m_rcBorder;
	rcBinary.right -= WAVE_BORDER_TO_RIGHT;
	long nBinaryHeight = BINARY_BORDER_HEIGHT + 2 * BINARY_AXIS_GAP;
	long nBinaryGap =  1; //
	rcBinary.top	 = m_rcWaveDraw.bottom - BINRAR_TO_BOTTOM - nBinaryHeight;
	rcBinary.bottom = m_rcWaveDraw.bottom - BINRAR_TO_BOTTOM;
	long nBinarysHeight = nBinaryChans * (nBinaryHeight + nBinaryGap);

	//计算模拟量的高度
	CRect rcBorder = m_rcBorder;
	rcBorder.right -= WAVE_BORDER_TO_RIGHT;
	long nHeight = 60;

	if (nAnalogChans >0 )
	{
		nHeight = (m_rcWaveDraw.Height() - nBinarysHeight ) / nAnalogChans - ANALOG_GAP;
		
		if (nHeight < RANGESTATEAXIS_MIN_LENGTH) 
		{
			nHeight = RANGESTATEAXIS_MIN_LENGTH;
		}
				
		rcBorder.bottom = rcBorder.top + nHeight;
	}
	

	//重新设置显示区域
	pos = GetHeadPosition();
	CRect rcAxis = m_rcBorder;
	BOOL bFindAxis = FALSE;
	CRect rcClip = m_rcWaveDraw;
	rcClip.left = m_rcBorder.left;
	while (pos != NULL)
	{
		pDraw = GetNext(pos);
		UINT nClassID = pDraw->GetClassID();

		if (DRAWCLASSID_ANALOGVARIABLE == nClassID || DRAWCLASSID_ATTRSPYVARIABLE == nClassID || DRAWCLASSID_COMPLEXVARIABLE == nClassID)
		{
			CDrawAnalogVariable* pAnalog = (CDrawAnalogVariable*)pDraw;

			if (bUseClipRect)
			{
				pAnalog->SetClipRect(rcClip);
			}

			pAnalog->SetBorder(rcBorder);
			rcBorder.OffsetRect(0, nHeight+ANALOG_GAP);
			pAnalog->InitAxis(MrDraw::g_snNameandAxisRectWidth);

			if (!bFindAxis)
			{
				rcAxis = pAnalog->m_rcAxis;
			}

			bFindAxis = TRUE;
		}
		else if (DRAWCLASSID_BINARYVARIABLE == nClassID)
		{
			CDrawBinaryVariable* pBinary =(CDrawBinaryVariable*)pDraw;
			
			if (bUseClipRect)
			{
				pBinary->SetClipRect(rcClip);
			}

			pBinary->SetBorder(rcBinary);
			rcBinary.OffsetRect(0, 0 - nBinaryGap - nBinaryHeight);
			pBinary->InitAxis(MrDraw::g_snNameandAxisRectWidth);
					
			if (!bFindAxis)
			{
				rcAxis = pBinary->m_rcAxis;
			}

			bFindAxis = TRUE;
		}
		else
		{
		}

	}

	//设置裁剪区域
	rcClip = rcAxis;
	rcClip.top = m_rcBorder.top;
	rcClip.bottom = m_rcBorder.bottom;
	rcClip.right += RANGESTATEAXIS_BLOCK_HEIGHT2 + 1;
	rcClip.left -= RANGESTATEAXIS_BLOCK_HEIGHT2 + 1;
	
	if (bUseClipRect)
	{
		m_pRangeStateAxis->SetClipRect(rcClip);
	}
}

void CDrawBaseMngr::SetBorder(const CRect &rect, BOOL bUseClipRect)
{	
	CDrawBase::SetBorder(rect);

	/////////////////
	long nTop		= rect.top;
	long nLeft		= rect.left;
	long nRight		= rect.right - WAVE_BORDER_TO_RIGHT;
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


void CDrawBaseMngr::CreateDrawMemDC(CDC *pDC, const CRect &rcClient)
{
	m_oDrawMemDC.Create(pDC, rcClient);
	//m_oDrawMemDC.FillSolidRect(m_crColor);
		
	if (m_oDrawMemDC.GetDC() == NULL)
	{
	}	
}

LONG CDrawBaseMngr::MouseMove(UINT nFlags, CPoint point)
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

LONG CDrawBaseMngr::LButtonDown(UINT nFlags, CPoint point) 
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
		pDraw = GetNext(pos);
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

void CDrawBaseMngr::AttachRangeStateAxisVariable()
{
	m_pRangeStateAxis->AttachDrawObject(m_pCurrDrawObj);
	CDrawVariable *pVariable = (CDrawVariable*)m_pCurrDrawObj;
	UINT nClassID = pVariable->GetClassID();

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

	CRect rcAxis = pVariable->m_rcAxis;
	CRect rcRangeStateAxis = CreateRangeVertStateAxisBorder(rcAxis.right, rcAxis.top, rcAxis.bottom);
	m_pRangeStateAxis->SetBorder(rcRangeStateAxis, RANGESTATEAXIS_TYPE_VERT);
}

LONG CDrawBaseMngr::LButtonUp(UINT nFlags, CPoint point)
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

			AdjustDrawNameRect();
			
			return DRAW_HAS_OBJECT_SELECTED;
		}
	}
	
	//时间坐标轴
	if (DRAW_HAS_OBJECT_SELECTED == m_oTimeAxisDraw.LButtonUp(nFlags, point))
	{
		return DRAW_HAS_OBJECT_SELECTED;
	}
	
	AdjustDrawNameRect();

	return DRAW_NONE_OBJECT_SELECTED;
}

LONG CDrawBaseMngr::RButtonDown(UINT nFlags, CPoint point)
{
	return 0;
}

LONG CDrawBaseMngr::RButtonUp(UINT nFlags, CPoint point)
{
	return 0;
}

void CDrawBaseMngr::Init()
{
}

void CDrawBaseMngr::MoveChannel(CDrawBase *pChannel, double dOffset)
{
}

void CDrawBaseMngr::ZoomChannel(CDrawBase *pChannel, double dRate)
{
}

void CDrawBaseMngr::MoveTimeAxis(double dOffset)
{
}

void CDrawBaseMngr::ZoomTimeAxis(double dRate)
{
}

void CDrawBaseMngr::MoveTimerCursor(double dOffset)
{
}

void CDrawBaseMngr::DrawMain(CDC *pDC)
{	
	m_oTimeAxisDraw.Draw(pDC);//时间轴
	
	CDrawVariable *pDraw = NULL;
	POS pos = GetHeadPosition();
	double dCoef = 0;
	double dOffset = 0;
	
	//绘制通道
	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->LogicPointToDevicePoint(dCoef,dOffset,m_oDrawBufferPos);
		pDraw->Draw(pDC);
	}
}

void CDrawBaseMngr::DrawSubject(CDC *pDC)
{
	//绘制通道纵向状态坐标
	m_pRangeStateAxis->Draw(pDC);
	m_pTimeCursorDraw->Draw(pDC);
	m_oTimeAxisDraw.DrawSubject(pDC);
}


CDrawVariable* CDrawBaseMngr::FindVariable(CMemBuffer_Long *pBuffer)
{
	POS pos = GetHeadPosition();
	CDrawVariable *pVariable = NULL;
	CDrawVariable *pFind = NULL;

	while (pos != NULL)
	{
		pVariable = (CDrawVariable *)GetNext(pos);

		if (pVariable->m_pnAttachBuffer == pBuffer)
		{
			pFind = pVariable;
			break;
		}
	}

	return pFind;
}

void CDrawBaseMngr::AddVariableByIndex(CDrawVariable *pVariable)
{
	POS pos = GetHeadPosition();
	POS posCurr = NULL;
	POS posFind = NULL;
	CDrawVariable *p = NULL;

	while (pos != NULL)
	{
		posCurr = pos;
		p = (CDrawVariable *)GetNext(pos);

		if (p->m_nVariableIndex > pVariable->m_nVariableIndex)
		{
			posFind = posCurr;
			break;
		}
	}

	if (posFind == NULL)
	{
		AddTail(pVariable);
	}
	else
	{
		InsertBefore(posFind, pVariable);
	}
}

void CDrawBaseMngr::InitParaRectByNameRect()
{
	POS pos = GetHeadPosition();
	CDrawVariable *p = NULL;

	while (pos != NULL)
	{
		p = (CDrawVariable *)GetNext(pos);
		p->m_oParas.m_rcPara.top = p->m_rcName.top;
		p->m_oParas.m_rcPara.bottom = p->m_rcName.bottom;
	}

}

void CDrawBaseMngr::Draw(CDC* pDC)
{
	//时间轴
	m_oTimeAxisDraw.Draw(pDC);
	
	CDrawVariable *pDraw = NULL;
	POS pos = GetHeadPosition();
	double dCoef = 0;
	double dOffset = 0;
	//绘制通道
	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->LogicPointToDevicePoint(dCoef,dOffset,m_oDrawBufferPos);
		pDraw->Draw(pDC);
	}
	
	//绘制通道纵向状态坐标
	m_pRangeStateAxis->Draw(pDC);
	m_pTimeCursorDraw->Draw(pDC);
}

void CDrawBaseMngr::GetCurrentShowTimeRange(double& dMax, double& dMin)
{
	m_oTimeAxisDraw.GetMaxMinTime(dMax , dMin);
}

void CDrawBaseMngr::SetCurrentShowTimeRange(double dMax, double dMin)
{	
	m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
	CalCurrentDataPos(dMax, dMin);
}

void CDrawBaseMngr::GetTimeRange(double& dMax, double& dMin)
{
	m_oTimeAxisDraw.GetMaxMinTime(dMax , dMin);
	m_oTimeAxisDraw.GetMaxMinTime(dMax , dMin);
}

void CDrawBaseMngr::SetTimeRange(double dMax, double dMin)
{	
	m_oTimeAxisDraw.SetOldMaxMinTime(dMax, dMin);
	m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
}

//这里的计算暂时没有测试
BOOL CDrawBaseMngr::CalCurrentDataPos(double dMax,double dMin)
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

	/////////////计算当前绘图数据的范围,及取数间隔
	double dTimeLength = dMaxTime - dMinTime;
	long nNeedDataLength = (long)(dTimeLength * m_nSamRateForDraw);//计算理论使用数据量
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
	
	if (nGap > m_nMaxGapValue)
	{
		nGap = m_nMaxGapValue;
	}
	
	if (nNeedDataLength > nDrawPoints)
	{
		nNeedDataLength = nNeedDataLength / nGap * nGap;//计算实际使用的数据量，小于等于理论值
	}

	m_oDrawBufferPos.nGap = nGap;
	long nBegin = (long)(dMinTime * m_nSamRateForDraw);//理论起点
	long nEnd   = nBegin + nNeedDataLength ;//理论终点
	
	if (nDataLength < nBufferLen)
	{
		if (nFillBeginPos >= nEnd) //有足够的数据
		{
			m_oDrawBufferPos.nBuf1BeginPos = nBegin;//起点是最小值点对应的位置
			m_oDrawBufferPos.nBufLength	   = nNeedDataLength;
			m_oDrawBufferPos.nBuf1EndPos   = nBegin + nNeedDataLength - 1;
			m_oDrawBufferPos.nBuf2EndPos   = -1;
			m_oDrawBufferPos.nBuf2BeginPos = -1;
		}
		else //有部分数据
		{
			m_oDrawBufferPos.nBuf1BeginPos = nBegin;//起点是最小值点对应的位置
			m_oDrawBufferPos.nBufLength	   = nFillBeginPos - nBegin;
			m_oDrawBufferPos.nBuf1EndPos   = nFillBeginPos  - 1;
			m_oDrawBufferPos.nBuf2EndPos   = -1;
			m_oDrawBufferPos.nBuf2BeginPos = -1;
		}
	}
	else
	{
//		nBegin += nFillBeginPos;//理论起点
//		nEnd   = nBegin + nNeedDataLength ;//理论终点
//
		if (nFillBeginPos < nNeedDataLength)//当前数据小于需要的长度
		{
			m_oDrawBufferPos.nBufLength    = nNeedDataLength ;
			m_oDrawBufferPos.nBuf1BeginPos = nBufferLen - nNeedDataLength + nFillBeginPos ;
			m_oDrawBufferPos.nBuf1EndPos   = nBufferLen - 1;
			m_oDrawBufferPos.nBuf2EndPos   = nFillBeginPos - 1;
			m_oDrawBufferPos.nBuf2BeginPos = 0;
		}
		else
		{
			m_oDrawBufferPos.nBufLength	   = nNeedDataLength;
			m_oDrawBufferPos.nBuf1BeginPos = nFillBeginPos - nNeedDataLength ;
			m_oDrawBufferPos.nBuf1EndPos   = nFillBeginPos - 1;
			m_oDrawBufferPos.nBuf2EndPos   = -1;
			m_oDrawBufferPos.nBuf2BeginPos = -1;
		}
	}
	
	CalXPos(nNeedDataLength / nGap);

	return TRUE;
}

void CDrawBaseMngr::CalXPos(long nTotalPoints)
{
// 	double dMaxTime = 0;
// 	double dMinTime = 0;
// 	m_oTimeAxisDraw.m_oTimeAxis.GetMinMaxVal(&dMinTime, &dMaxTime, 0);
// 	double dCoef = 0;
// 	int nCenterX = 0;
// 	m_oTimeAxisDraw.m_oTimeAxis.GetAxisInterface(dCoef, nCenterX);
// 	double dTimePerPoint = (double)(dMaxTime - dMinTime) / nTotalPoints;
// 	dCoef *= dTimePerPoint;
// 
// 	CPoint* pBuffer = m_pPointBuffer->GetBuffer();
// 	CPoint* pEnd = pBuffer + nTotalPoints;
// 	
// 	long nIndex = (long)(dMinTime * m_nSamRateForDraw) / m_oDrawBufferPos.nGap;
// 
// 	while (pBuffer < pEnd)
// 	{
// 		pBuffer->x = (long)(nIndex * dCoef + nCenterX );
// 		pBuffer++;
// 		nIndex++;
// 	}
	

	double dMaxTime = 0;
	double dMinTime = 0;
	m_oTimeAxisDraw.m_oTimeAxis.GetMinMaxVal(&dMinTime, &dMaxTime, 0);
	double dCoef = 0;
	int nCenterX = 0;
	m_oTimeAxisDraw.m_oTimeAxis.GetAxisInterface(dCoef, nCenterX);
	double dTimePerPoint = (double)(dMaxTime - dMinTime) / nTotalPoints;
	//dCoef *= dTimePerPoint;
	double dIndex = dMinTime;
	
	CPoint* pBuffer = m_pPointBuffer->GetBuffer();
	CPoint* pEnd = pBuffer + nTotalPoints;
	
	long nIndex = (long)(dMinTime * m_nSamRateForDraw) / m_oDrawBufferPos.nGap;
	
	while (pBuffer < pEnd)
	{
		pBuffer->x = (long)(dIndex * dCoef + nCenterX );
		pBuffer++;
		dIndex += dTimePerPoint;
	}
}

void CDrawBaseMngr::OnTimeAxisPositionchanged()
{
	double dMaxTime = 0;
	double dMinTime = 0;

	m_oTimeAxisDraw.GetMaxMinTime(dMaxTime, dMinTime);
	CalCurrentDataPos(dMaxTime, dMinTime);
}

double CDrawBaseMngr::DecivePointToLogicPointTime(long x)
{
	double dValue = 0;
	m_oTimeAxisDraw.m_oTimeAxis.DevicePointToLogicPoint(x, &dValue);
	return dValue;
}
