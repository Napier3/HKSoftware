// XRecordDrawBase.cpp: implementation of the CXRecordDrawBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XRecordDrawBase.h"
// #include "../MR1200BaseApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL g_bInWriteBmpFileState = FALSE;

BOOL CXRecordDrawBase::g_bDibDrawUseChannelColor = FALSE;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXRecordDrawBase::CXRecordDrawBase()
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
	m_nSamRateForDraw				= 100000;//MR1200_SAMPLE_RATE;  //2020-06-22 lijunqing
	m_pRangeStateAxis->SetMinLength(40);

	m_pRefBuffer = NULL;

	m_rcNameAndRangeAxis = CRect(0,0,0,0);
	m_rcTimeAxis		 = CRect(0,0,0,0);
	m_rcWaveDraw		 = CRect(0,0,0,0);

	m_oTimeAxisDraw.m_oTimeAxis.SetBigSawMinWidth(40);
	//m_pRcdComtradeFile = NULL;

	g_crDrawBackColor	= RGB(182,182,182);
	g_crRecordBackColor	= RGB(0,0,0);
	g_crDrawAreaBkColorFrom     = RGB(240, 240, 240);
	g_crDrawAreaBkColorTo       = RGB(255, 255, 255);
	//g_crAxisGrid = RGB(100, 100, 100);
	g_crDrawAreaLeftTopFrom = RGB(90, 90, 90);
	g_crDrawAreaLeftTopTo = RGB(90, 90, 90);
	g_crDrawAreaRightBottomFrom = RGB(210, 210, 210);
	g_crDrawAreaRightBottomTo = RGB(210, 210, 210);

	m_pRecordDrawObjcontrol = NULL;
}

CXRecordDrawBase::~CXRecordDrawBase()
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

// 	if (m_pRecordTest != NULL)
// 	{
// 		g_theRecordApp.Delete(m_pRecordTest);
// 	}

/*//2023-7-22  lijunqing 移动到子类中
	if (m_pRcdComtradeFile != NULL)
	{
		CRcdComtradeFileMngr::CloseComtradeFile(m_pRcdComtradeFile);
	}

	m_pRcdComtradeFile = NULL;
*/

	if (m_pPointBuffer != NULL)
	{
		delete m_pPointBuffer;
		m_pPointBuffer = NULL;
	}
}

void CXRecordDrawBase::ClearSelect()
{
	m_pCurrDrawObj = NULL;
	m_pCurrDrawVariable = NULL;

	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->DettachVariable();
	}
}

void CXRecordDrawBase::SetVariableMoveCursor(HCURSOR hCursor)
{
	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->SetMoveCursor(hCursor);
	}
}

void CXRecordDrawBase::SetVariableZoomCursor(HCURSOR hCursor)
{
	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->SetZoomCursor(hCursor);
	}
}

void CXRecordDrawBase::SetVariableProhibitCursor(HCURSOR hCursor)
{
	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->SetProhibitCursor(hCursor);
	}
}

void CXRecordDrawBase::SetTimeAxisMoveCursor(HCURSOR hCursor)
{
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetMoveCursor(hCursor);
}

void CXRecordDrawBase::SetTimeAxisZoomCursor(HCURSOR hCursor)
{
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetZoomCursor(hCursor);	
}

void CXRecordDrawBase::SetTimeAxisProhibitCursor(HCURSOR hCursor)
{
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetProhibitCursor(hCursor);	
}

void CXRecordDrawBase::SetParentWnd(CWnd* pParentWnd)
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

void CXRecordDrawBase::AdjustDrawNameRect()
{
	ReCompositor();
//	CNameSortMngr oNameSortMngr(this,m_rcNameAndRangeAxis);
}

BOOL CXRecordDrawBase::ReCompositor()
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

BOOL CXRecordDrawBase::InitShowDrawVariables(CXDrawElements &oVariableMngr)
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

void CXRecordDrawBase::AdjustDrawVariablePosition(BOOL bUseClipRect)
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
			rcBorder.right = m_rcWaveDraw.right;
			
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

long CXRecordDrawBase::GetTotalPoints()
{
		return 0;
// 	if (m_pRcdComtradeFile->m_pnDataPoints == NULL) 
// 	{
// 		return 0;
// 	}
// 
// 	return m_pRcdComtradeFile->m_pnDataPoints[0];
}

long CXRecordDrawBase::GetSampleRate()
{
	return 0;
	//return (long)(m_pRcdComtradeFile->m_pdSamRate[0]);
}

void CXRecordDrawBase::InitDrawPoints(long nPoints)
{
	if (m_pPointBuffer == NULL)
	{
		m_pPointBuffer = new CMemBuffer_CPoint();
	}

	m_pPointBuffer->SetBufferLength(nPoints);
	CPoint *pPoint = m_pPointBuffer->GetBuffer();
}


void CXRecordDrawBase::InitRecordDrawObjectPosByControl()
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
	POS  pos = GetHeadPosition();
	double dDrawVariableHeight = 0;
	double dCenter = 0;
	double dDrawHeight = 0;

	while (pos != NULL)
	{
		CDrawVariable* pDrawVar = (CDrawVariable*)GetNext(pos);
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

	//设置m_pRangeStateAxis的裁剪区域
	CRect rectRange = m_rcWaveDraw;	
	CDrawVariable *pFirst = (CDrawVariable *)GetHead();

	if (pFirst == NULL)
	{
		return;
	}

	rectRange.right = pFirst->m_rcAxis.right + RANGESTATEAXIS_BLOCK_WIDTH / 2;
	rectRange.left = pFirst->m_rcAxis.left;
	m_pRangeStateAxis->SetClipRect(rectRange);
}

void CXRecordDrawBase::SetBorder(const CRect &rect, BOOL bUseClipRect)
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

LONG CXRecordDrawBase::MouseMove(UINT nFlags, CPoint point)
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

LONG CXRecordDrawBase::LButtonDown(UINT nFlags, CPoint point) 
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
				//if (::IsWindow(m_pParentWnd->m_hWnd))
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
				//if (::IsWindow(m_pParentWnd->m_hWnd))
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

LONG CXRecordDrawBase::LButtonDbClick(UINT nFlags, CPoint point) 
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
			//if (::IsWindow(m_pParentWnd->m_hWnd))
			{					
				m_pParentWnd->PostMessage(WM_VARIABLE_POS_CHANGED, 0, 0);
			}
		}
	}
	
	return DRAW_NONE_OBJECT_SELECTED;
}

void CXRecordDrawBase::AttachRangeStateAxisVariable()
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

LONG CXRecordDrawBase::LButtonUp(UINT nFlags, CPoint point)
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

LONG CXRecordDrawBase::RButtonDown(UINT nFlags, CPoint point)
{
	return 0;
}

LONG CXRecordDrawBase::RButtonUp(UINT nFlags, CPoint point)
{
	return 0;
}

void CXRecordDrawBase::Init()
{
}

void CXRecordDrawBase::MoveChannel(CDrawBase *pChannel, double dOffset)
{
}

void CXRecordDrawBase::ZoomChannel(CDrawBase *pChannel, double dRate)
{
}

void CXRecordDrawBase::MoveTimeAxis(double dOffset)
{
}

void CXRecordDrawBase::ZoomTimeAxis(double dRate)
{
}

void CXRecordDrawBase::MoveTimerCursor(double dOffset)
{
}

void CXRecordDrawBase::DrawSubject(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	DrawRangeStateAxis(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	
	m_pTimeCursorDraw->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	m_oTimeAxisDraw.DrawSubject(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}
// 
// void CXRecordDrawBase::Draw(CDC* pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
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

void CXRecordDrawBase::GetCurrentShowTimeRange(double& dMax, double& dMin)
{
	m_oTimeAxisDraw.GetMaxMinTime(dMax , dMin);
}

void CXRecordDrawBase::SetCurrentShowTimeRange(double dMax, double dMin)
{	
	m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
	CalCurrentDataPos(dMax, dMin);
}

void CXRecordDrawBase::GetTimeRange(double& dMax, double& dMin)
{
	m_oTimeAxisDraw.GetMaxMinTime(dMax , dMin);
	m_oTimeAxisDraw.GetMaxMinTime(dMax , dMin);
}

void CXRecordDrawBase::SetTimeRange(double dMax, double dMin)
{	
	m_oTimeAxisDraw.SetOldMaxMinTime(dMax, dMin);
	m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
}

//这里的计算暂时没有测试
BOOL CXRecordDrawBase::CalCurrentDataPos(double dMax,double dMin)
{
	ASSERT (FALSE);

	return TRUE;
}

BOOL CXRecordDrawBase::CalScrollDrawDataPos(double dMax,double dMin)
{
	if (m_pRefBuffer == NULL)
	{
		return FALSE;
	}

	double dMaxTime = dMax;
	double dMinTime = dMin;

	double dTimeLength = dMaxTime - dMinTime;
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

	if (nDataLength < nBufferLen)//不循环
	{ 		
		if (nFillBeginPos >= nNeedDataLength) //有足够的数据
		{
			m_oDrawBufferPos.nBuf1BeginPos = nFillBeginPos - nNeedDataLength;//起点是最小值点对应的位置
			m_oDrawBufferPos.nBufLength	   = nNeedDataLength;
			m_oDrawBufferPos.nBuf1EndPos   = nFillBeginPos - 1;
			m_oDrawBufferPos.nBuf2EndPos   = -1;
			m_oDrawBufferPos.nBuf2BeginPos = -1;
		}
		else //有部分数据
		{
			m_oDrawBufferPos.nBuf1BeginPos = 0;//起点是最小值点对应的位置
			m_oDrawBufferPos.nBufLength	   = nFillBeginPos ;
			m_oDrawBufferPos.nBuf1EndPos   = nFillBeginPos  - 1;
			m_oDrawBufferPos.nBuf2EndPos   = -1;
			m_oDrawBufferPos.nBuf2BeginPos = -1;
		}
	}
	else//一定使用最新的数据
	{
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

void CXRecordDrawBase::CalXPosEx(long nTotalPoints, CMemBuffer_CPoint *pPointBuffer, long nSamRateForDraw, long nGap)
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

void CXRecordDrawBase::CalXPos(long nTotalPoints)
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

void CXRecordDrawBase::OnTimeAxisPositionchanged()
{
	double dMaxTime = 0;
	double dMinTime = 0;

	m_oTimeAxisDraw.GetMaxMinTime(dMaxTime, dMinTime);
	CalCurrentDataPos(dMaxTime, dMinTime);
}

double CXRecordDrawBase::DecivePointToLogicPointTime(long x)
{
	double dValue = 0;
	m_oTimeAxisDraw.m_oTimeAxis.DevicePointToLogicPoint(x, &dValue);
	return dValue;
}


void CXRecordDrawBase::SetBorder(CDC *pDC, const CRect &rect, BOOL bUseClipRect)
{
	SetBorder(rect);
	CRect rc = rect;
	CreateDrawMemDC(pDC, rc);

	long nTop		= rc.top;
	long nLeft		= rc.left;
	long nRight		= rc.right-1;
	long nBottom	= rc.bottom;

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

void CXRecordDrawBase::DrawMainBack(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CRect rc = GetBorder();//m_rcBorder;
	rc.right = m_rcNameAndRangeAxis.right;
	rc.left = 0;
	rc.top = 0;
	rc.bottom = m_rcTimeAxis.bottom;
	pDC->FillSolidRect(rc, g_crDrawBackColor);

	rc = m_rcTimeAxis;
	rc.right++;
	pDC->FillSolidRect(rc, g_crDrawBackColor);

	DrawWaveAreaBorder(pDC);

	//时间轴
	m_oTimeAxisDraw.Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);

	//网格绘制
	DrawGrid(pDC);
}


void CXRecordDrawBase::DrawMain(double fZoomRatio,const CPoint &ptOffset, BOOL bShowMidLine, DWORD dwDrawFlag)
{	
	CDC *pDC = m_oDrawMemDC.GetDC();
	DrawMainEx(pDC, fZoomRatio, ptOffset, bShowMidLine, dwDrawFlag);
}


void CXRecordDrawBase::DrawMain_Wave(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CDrawVariable *pDraw = NULL;
	POS pos = GetHeadPosition();
	double dCoef = 0;
	double dOffset = 0;

	pos = GetHeadPosition();
	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->LogicPointToDevicePoint(dCoef, dOffset, m_oDrawBufferPos);
		pDraw->Draw(pDC, fZoomRatio, ptOffset, VARIABLE_DRAW_STYLE_WAVE);
		pDraw->DrawAttrs(pDC, fZoomRatio, ptOffset, dwDrawFlag, m_oDrawBufferPos);
	}
}


void CXRecordDrawBase::DrawMainEx(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, BOOL bShowMidLine, DWORD dwDrawFlag)
{
	DrawMainBack(pDC, fZoomRatio, ptOffset, dwDrawFlag);

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
		pDraw->Draw(pDC, fZoomRatio, ptOffset, VARIABLE_DRAW_STYLE_NAME | VARIABLE_DRAW_STYLE_AXIS);
	}

	//绘制通道波形
	rgn.DeleteObject();
	rgn.CreateRectRgnIndirect(m_rcWaveDraw);
	pDC->SelectClipRgn(&rgn);
	pos = GetHeadPosition();

	//绘制零线
	pos = GetHeadPosition();

	if (bShowMidLine)
	{
		while (pos != NULL)
		{
			pDraw = (CDrawVariable*)GetNext(pos);
			pDraw->Draw(pDC, fZoomRatio, ptOffset, VARIABLE_DRAW_STYLE_CENTER);
		}
	}

	DrawMain_Wave(pDC, fZoomRatio, ptOffset, dwDrawFlag);

	pDC->SelectClipRgn(NULL);

	rgn.DeleteObject();
}


void CXRecordDrawBase::DrawElements(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, BOOL bShowMidLine, DWORD dwDrawFlag)
{
	CDrawVariable *pDraw = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->DrawElements(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	}
}

void CXRecordDrawBase::DrawGrid(CDC *pDC)
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

	for (long nIndex=1; nIndex<nCount+1; nIndex++)
	{
		y = (long)(m_rcWaveDraw.top + 50 * nIndex);
		pDC->MoveTo(m_rcWaveDraw.left, y);
		pDC->LineTo(m_rcWaveDraw.right, y);
	}

	pen.DeleteObject();
	pDC->SelectObject(pPen);
	pDC->SetBkMode(nBkMode);
}

void CXRecordDrawBase::DrawWaveAreaBorder(CDC *pDC)
{
	CPen pen1(PS_SOLID, 1, g_crDrawAreaLeftTopFrom);
	CPen pen2(PS_SOLID, 1, g_crDrawAreaRightBottomFrom);
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

	pDC->FillSolidRect(m_rcWaveDraw, g_crRecordBackColor);
}

//////////////////////////////////////////////////////////////////////
// void CXRecordDrawBase::AddAttrsDraw()
// {
// 	POS pos = GetHeadPosition();
// 	CDrawVariable *pVariable = NULL;
// 	CRtVariables *pRtVariables = m_pRecordTest->m_pVariables;
// 	CRtVariable  *pRtVariable = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pVariable = (CDrawVariable *)GetNext(pos);
// 		pRtVariable = (CRtVariable *)pRtVariables->FindByName(pVariable->m_strName);
// 
// 		if (pRtVariable == NULL)
// 		{
// 			continue;
// 		}
// 
// 		ASSERT (pRtVariable == pVariable->m_pXDrawDataRef);
// 		pVariable->AddAttrsDraw(pRtVariable);
// 	}
// }
// 

#ifndef _PSX_IDE_QT_
void CXRecordDrawBase::DibDraw(CDibDraw &oDibDraw, DWORD dwDrawFlag)
{
	if (g_bDibDrawUseChannelColor)
	{
		g_bInWriteBmpFileState = FALSE;
	}
	else
	{
		g_bInWriteBmpFileState = TRUE;
	}

	CDC oDC;
	HDC hdc = NULL;

	COLORREF crRecordBackColor = g_crRecordBackColor;
	COLORREF crDrawBackColor = g_crDrawBackColor;
	COLORREF crDrawAreaBkColorTo = g_crDrawAreaBkColorTo;
	COLORREF crDrawAreaBkColorFrom = g_crDrawAreaBkColorFrom;
	long nSelectFlag[MAX_MR1200_CHANNELS];
	ZeroMemory(nSelectFlag, sizeof(long)*MAX_MR1200_CHANNELS);
	long nIndex = 0;

	POS pos = GetHeadPosition();
	CDrawVariable *pVar = NULL;

	while (pos != NULL)
	{
		pVar = (CDrawVariable *)GetNext(pos);
		nSelectFlag[nIndex] = pVar->GetSelect();
		pVar->SetSelect(TRUE);
		nIndex++;
	}

	g_crRecordBackColor = RGB(255, 255, 255);
	g_crDrawBackColor =RGB(255, 255, 255);
	g_crDrawAreaBkColorTo = RGB(255, 255, 255);
	g_crDrawAreaBkColorTo = RGB(255, 255, 255);

	g_crRecordBackColor = RGB(255, 255, 255);
	oDibDraw.CreateDraw(m_nWidth, m_nHeight);
	hdc = oDibDraw.GetDrawDC();
	oDC.Attach(hdc);
	DrawMainEx(&oDC, 1, CPoint(0,0), TRUE, dwDrawFlag);
	DrawElements(&oDC, 1, CPoint(0,0), TRUE, dwDrawFlag);	//2021-1-17  lijunqing
	oDC.Detach();

	g_crRecordBackColor = crRecordBackColor;
	g_crDrawBackColor =crDrawBackColor;
	g_crDrawAreaBkColorTo = crDrawAreaBkColorTo;
	g_crDrawAreaBkColorTo = crDrawAreaBkColorFrom;

	g_bInWriteBmpFileState = FALSE;

	pos = GetHeadPosition();
	nIndex = 0;

	while (pos != NULL)
	{
		pVar = (CDrawVariable *)GetNext(pos);
		nSelectFlag[nIndex] = pVar->GetSelect();
		pVar->SetSelect(nSelectFlag[nIndex] );
		nIndex++;
	}
}


void CXRecordDrawBase::WriteToBmpFile(const CString &strFile)
{
	CDibDraw oDibDraw;
	DibDraw(oDibDraw);

	oDibDraw.WriteToFile(strFile);
	oDibDraw.FreeDraw();
}

void CXRecordDrawBase::CopyToClipboard()
{
	CDibDraw oDibDraw;
	DibDraw(oDibDraw);

	oDibDraw.CopyToClipboard(m_pParentWnd->m_hWnd);
	oDibDraw.FreeDraw();
}
#endif

void CXRecordDrawBase::AttatchAxisX()
{
	AttatchAxisX(&m_oTimeAxisDraw.m_oTimeAxis);
}

void CXRecordDrawBase::AttatchAxisX(CRulerAxis *pAxis)
{
	CDrawVariable *pDraw = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->AttatchAxisX(pAxis);
	}
}

#ifdef _SHOW_PARA
//2022-9-1  lijunqing
void CXRecordDrawBase::CalDrawParasValue()
{
	CDrawVariable *pDraw = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)GetNext(pos);
		pDraw->CalValue();
	}
}

#endif
