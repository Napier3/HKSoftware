// XRecordDrawBase.h: interface for the CXRecordDrawBase class.
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

#include "../../BaseClass/MemBufferDC.H"

#include "../../XDrawBase/XDrawViewBase.h"

//2023-7-22  lijunqing 移动到子类中
//#include "../Comtrade/ComtradeMngr.h"

//说明，m_listChild中有的只是通道对象
#define MAX_DRAWGAP1 100   //示波窗的等间隔取数的Gap
#define MAX_DRAWGAP2 200   //其它等间隔取数的Gap
#define AnalyseWnd_MaxDrawlength 120000 //定义分析窗每屏最大绘制的长度，最大十分钟

/*
子对象为绘图通道，即当前绘图页面，绘制当前页面的通道波形
*/
class CXRecordDrawBase : public CXDrawViewBase  
{
public:
	CXRecordDrawBase();
	virtual ~CXRecordDrawBase();

	static BOOL g_bDibDrawUseChannelColor;
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

	//2023-7-22  lijunqing 移动到子类中
	//CRcdComtradeFile *m_pRcdComtradeFile;
	PRECORDDRAWOBJECTCONTROL m_pRecordDrawObjcontrol;
	double m_dHeightRateOnSize;

public:
	virtual void InitRecordDrawObjectPosByControl();
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
	virtual BOOL CalScrollDrawDataPos(double dMax,double dMin);//滚动显示时的Buffer位置
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
	void ClearSelect();

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
//#ifndef _PSX_QT_LINUX_//20230112 zhouhj 显示波形图左侧垂直调整按钮
		CRgn rgn;
		CRect rcRgn = m_rcWaveDraw;
		rcRgn.left = 0;
		rgn.CreateRectRgnIndirect(rcRgn);
		pDC->SelectClipRgn(&rgn);
		m_pRangeStateAxis->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
		pDC->SelectClipRgn(NULL);
		rgn.DeleteObject();
//#endif
	}

public:
// 	CRect m_rcTimeandProgress;
// 	CExBaseList  m_oVariableMngr;    //通道管理  
// 	double m_dRecordDataTimeLength;    //当前录波数据的总的时间长度，单位为s
// 	double m_dMinTimeInOneSreen;       //当前屏幕能够显示的最小时间长度 ,单位为秒
// 	double m_dMaxTimeInOneSreen;       //当前屏幕能够显示的最大时间长度 ,单位为秒
// 	CDrawSysTime m_oDrawSysTime;       //系统时间绘制
	CRect m_rcWaveDrawEx;              //波形绘图区域的扩展

public:
	virtual void InitDrawPoints(long nPoints);		
	virtual void SetBorder(CDC *pDC, const CRect &rect, BOOL bUseClipRect=TRUE);

	virtual void DrawMainBack(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void DrawMain(double fZoomRatio,const CPoint &ptOffset, BOOL bShowMidLine, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void DrawMain_Wave(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

protected:
	void DrawWaveAreaBorder(CDC *pDC);
	void DrawGrid(CDC *pDC);
	void DrawMainEx(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, BOOL bShowMidLine, DWORD dwDrawFlag=0xFFFFFFFF);
	void DrawElements(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, BOOL bShowMidLine, DWORD dwDrawFlag=0xFFFFFFFF);

//////////////////////////////////////////////////////////////////////////
//综合属性绘图
// public:
// 	void AddAttrsDraw();

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

public:
#ifndef _PSX_IDE_QT_
	virtual void WriteToBmpFile(const CString &strFile);
	virtual void CopyToClipboard();
#endif

protected:
#ifndef _PSX_IDE_QT_
	void DibDraw(CDibDraw &oDibDraw, DWORD dwDrawFlag=0xFFFFFFFF);
#endif

	//2021-1-16  lijunqing
	void AttatchAxisX();
	void AttatchAxisX(CRulerAxis *pAxis);


#ifdef _SHOW_PARA
	//2022-9-1  lijunqing
	void CalDrawParasValue();
#endif

};

#endif // !defined(AFX_MR1200DRAWBASE_H__64430395_E132_4498_8453_FF07ECA0AEB7__INCLUDED_)
