// Mr1200DrawBase.h: interface for the CDrawMr1200Base class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MR1200DRAWBASE_H__64430395_E132_4498_8453_FF07ECA0AEB7__INCLUDED_)
#define AFX_MR1200DRAWBASE_H__64430395_E132_4498_8453_FF07ECA0AEB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBinaryVariable.h"
#include "DrawAnalogVariable.h"
#include "DrawTimeAxis.h"
#include "DrawTimeCursor.h"
//#include "DrawBinaryVariableGroup.h"
#include "DrawAttrSpy.h"
#include "DrawAnalogComplexVariable.h"
#include "NameSort.h"
#include "DrawGlobalDef.h"

#include "..\..\BaseClass\MemBufferDC.H"

#include "..\..\XDrawBase\XDrawViewBase.h"

#include "..\Comtrade\ComtradeMngr.h"
#include "..\RecordTest\RecordTest.h"

//说明，m_listChild中有的只是通道对象
#define MAX_DRAWGAP1 100   //示波窗的等间隔取数的Gap
#define MAX_DRAWGAP2 200   //其它等间隔取数的Gap
#define AnalyseWnd_MaxDrawlength 60000 //定义分析窗每屏最大绘制的长度，最大十分钟

class CDrawMr1200Base : public CXDrawViewBase  
{
public:
	CDrawMr1200Base();
	virtual ~CDrawMr1200Base();

public:
	CDrawBase       *m_pCurrDrawObj;        //当前选中的绘图对象
	CDrawVariable   *m_pCurrDrawVariable;   //当前通道对象
	CDrawTimeCursor *m_pTimeCursorDraw;     //时间光标
	CDrawTimeAxis   m_oTimeAxisDraw;        //时间轴	
	CDrawRangeStateAxis *m_pRangeStateAxis; //时间轴区域

	//缓冲区管理
	CMemBuffer_CPoint* m_pPointBuffer;//CPoint
	CMemBufferInterface* m_pRefBuffer;
	//CMemBuffer_Float*  m_pfAttrBuffer;
	MrDraw::DRAWMEMBUFFERPOS m_oDrawBufferPos;
	//区域设置
	CRect m_rcNameAndRangeAxis;
	CRect m_rcTimeAxis;
	CRect m_rcWaveDraw;

	long m_nMaxGapValue;
	UINT m_nSamRateForDraw;//采样率

	CRcdComtradeFile *m_pRcdComtradeFile;
	CRecordTest *m_pRecordTest;
	double m_dHeightRateOnSize;

public:
	virtual long GetTotalPoints();
	virtual long GetSampleRate();

	//继承的方法
	virtual void SetBorder(const CRect &rect, BOOL bUseClipRect=TRUE);
	virtual void SetParentWnd(CWnd* pParentWnd);
	
	virtual LONG MouseMove(UINT nFlags, CPoint point);
	virtual LONG LButtonDown(UINT nFlags, CPoint point); 
	virtual LONG LButtonDbClick(UINT nFlags, CPoint point); 
	virtual LONG LButtonUp(UINT nFlags, CPoint point);
	virtual LONG RButtonDown(UINT nFlags, CPoint point);
	virtual LONG RButtonUp(UINT nFlags, CPoint point);
	//virtual void Draw(CDC* pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag);
	virtual void Init();
	virtual UINT GetClassID()			{	return 0;	}
	virtual void SetCurrentShowTimeRange(double dMax, double dMin);
	virtual void GetCurrentShowTimeRange(double& dMax, double& dMin);
	virtual void SetTimeRange(double dMax, double dMin);
	virtual void GetTimeRange(double& dMax, double& dMin);

	//自身的方法
	void MoveChannel(CDrawBase *pChannel, double dOffset);
	void ZoomChannel(CDrawBase *pChannel, double dRate);
	void MoveTimeAxis(double dOffset =0);
	void ZoomTimeAxis(double dRate);
	void MoveTimerCursor(double dOffset);
	virtual BOOL CalCurrentDataPos(double dMax, double dMin);
	virtual void CalXPos(long nTotalPoints);
	virtual void CalXPosEx(long nTotalPoints, CMemBuffer_CPoint *pPointBuffer, long nSamRateForDraw, long nGap);
	void AdjustDrawVariablePosition(BOOL bUseClipRect = TRUE);

	void OnTimeAxisPositionchanged();
	double DecivePointToLogicPointTime(long x);

	void AdjustDrawNameRect();
	BOOL ReCompositor();
	
	BOOL InitShowDrawVariables(CXDrawElements &oVariableMngr);

    void SetDrawDataRange(long nBeginPos1,long nEndPos1,long nBeginPos2 = -1,long nEndPos2 = -1)
	{
		m_oDrawBufferPos.nBuf1BeginPos  = nBeginPos1;
		m_oDrawBufferPos.nBuf1EndPos	= nEndPos1;
		m_oDrawBufferPos.nBuf2BeginPos  = nBeginPos2;
		m_oDrawBufferPos.nBuf2EndPos	= nEndPos2;

		if (nBeginPos2 >= 0)
		{
			m_oDrawBufferPos.nBufLength = nEndPos1 - nBeginPos1 + nEndPos2 - nBeginPos2 + 2;
		} 
		else
		{
			m_oDrawBufferPos.nBufLength = nEndPos1 - nBeginPos1 + 1;
		}
	}

public:
	void FreeAll()
	{
		DeleteAll();
		m_pCurrDrawObj = NULL;
		m_pCurrDrawVariable = NULL;
		m_pRefBuffer = NULL;
		m_pRangeStateAxis->DettachVariable();
	}

	void SetVariableMoveCursor(HCURSOR hCursor);
	void SetVariableZoomCursor(HCURSOR hCursor);
	void SetVariableProhibitCursor(HCURSOR hCursor);
	void SetTimeAxisMoveCursor(HCURSOR hCursor);
	void SetTimeAxisZoomCursor(HCURSOR hCursor);
	void SetTimeAxisProhibitCursor(HCURSOR hCursor);
	CDrawRangeStateAxis* GetChannelRangeStateAxis()       {    return m_pRangeStateAxis;                               }
	CDrawRangeStateAxis* GetTimeAxisRangeStateAxis()      {    return &(m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState);   }

	virtual void DrawSubject(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

protected:
	void AttachRangeStateAxisVariable();
	long DoubleToLong(double dVal)
	{
		long nVal = (long)dVal;

		if (dVal - nVal >= 0.5)
		{
			nVal++;
		}

		return nVal;
	}

	void DrawRangeStateAxis(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF)
	{
		CRgn rgn;
		CRect rcRgn = m_rcWaveDraw;
		rcRgn.left = 0;
		rgn.CreateRectRgnIndirect(rcRgn);
		pDC->SelectClipRgn(&rgn);
		m_pRangeStateAxis->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
		pDC->SelectClipRgn(NULL);
		rgn.DeleteObject();
	}

//////////////////////////////////////////////////////////////////////////
//综合属性绘图
public:
	void AddAttrsDraw();

protected:
	COLORREF g_crRecordBackColor;//	= RGB(182,182,182);
	COLORREF g_crDrawBackColor;//	= RGB(182,182,182);
	COLORREF g_crDrawAreaBkColorFrom;//     = RGB(240, 240, 240);
	COLORREF g_crDrawAreaBkColorTo;//       = RGB(255, 255, 255);
	//COLORREF g_crAxisGrid;// = RGB(100, 100, 100);
	COLORREF g_crDrawAreaLeftTopFrom;// = RGB(90, 90, 90);
	COLORREF g_crDrawAreaLeftTopTo;// = RGB(90, 90, 90);
	COLORREF g_crDrawAreaRightBottomFrom;// = RGB(210, 210, 210);
	COLORREF g_crDrawAreaRightBottomTo;// = RGB(210, 210, 210);
};

#endif // !defined(AFX_MR1200DRAWBASE_H__64430395_E132_4498_8453_FF07ECA0AEB7__INCLUDED_)
