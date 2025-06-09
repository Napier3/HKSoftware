// TimeCursorDrawClass.h: interface for the CTimeCursorDrawClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined TIMECURSORDRAWCLASS_H_
#define TIMECURSORDRAWCLASS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\BaseClass\ExBaseObject.h"

//########//定义时间区断线数据类
class CTimeCursorDrawClass : public CExBaseObject  
{
public:
	CWnd	*pParent;			//父窗口指针
	CRect	m_rectOwnPosition;	//光标本身的位置
	CRect	m_rectTimeBtnArea;	//时间光标的按钮的位置
	CRect	m_rectBeginTimeBtn;	//起始时间光标按钮位置
	CRect	m_rectEndTimeBtn;	//终止时间光标按钮位置
	//初始化函数
	void	InitIt();
	void	EndIt();
	//同各通道的绘图区域进行绑定
	void	SetLineAreaRects(int iAreas,CRect*pRect);
	void	GetTimeLineButton();

	void	Typeset(CSize size,long &lDrift);
public:
	int		m_iBLinePtX;		//起始时间坐标数值
	int		m_iELinePtX;		//终止时间坐标数值

	int		m_nLineAreas;		//时间线的绘制区域数
	CRect	*m_pRectLineArea;	//时间线的绘制区域位置

	COLORREF	m_crBeginLine;	//起始时间光标的颜色
	COLORREF	m_crEndLine;	//终止时间光标的颜色
	COLORREF	m_crViewBK;
	COLORREF	m_crArea;
	unsigned long	m_ulBeginLineType;	//起始时间光标的线型
	unsigned long	m_ulEndLineType;	//终止时间光标的线型

	//时间光标的绘图函数
	void  DrawIt(CDC*pDC);
	void  DrawBeginTimeLine(CDC*pDC,BOOL b=FALSE);		//////绘制起始时间的直线
	void  DrawEndTimeLine(CDC*pDC,BOOL b=FALSE);		//////绘制终止直线
	void  EraseBeginTimeLine();			//erase the begin time line
	void  EraseEndTimeLine();			//erase the end time line;

	/////定义鼠标的各种操作标志
	int   m_iMoveEndTimeFlag;			/////当前是否移动终止直线的标志
	int	  m_iCurrDrawTimeLineType;		//现在绘制的是起始时间线还是终止时间线
	int	  m_iActiveTimeLine;			//当前活动的时间线  2：起始时间线；1：终止时间线
	//////定义鼠标的各种操作函数
	BOOL OnMouseMoveTimeLines(CPoint point,CDC*pDC);
	BOOL OnTimeLineClick(CPoint point,CDC*pDC);

	BOOL OnMouseMove(CPoint point,CDC*pDC,CPoint ptScroll=CPoint(0,0));
	BOOL OnLButtonDown(CPoint point,CDC*pDC);
	BOOL OnLButtonUp(CPoint point,CDC*pDC);
	BOOL IsPointInRestList(CPoint point);
	CRect GetMaxRectArea();

public:
	CTimeCursorDrawClass();
	virtual ~CTimeCursorDrawClass();

	void Set_IDC_CURSOR(UINT nHand, UINT nMove)	{	m_IDC_CURSOR_HAND = nHand;	m_IDC_CURSOR_MOVE = nMove;}
protected:
	UINT m_IDC_CURSOR_HAND;
	UINT m_IDC_CURSOR_MOVE;

};

#endif // !defined(TIMECURSORDRAWCLASS_H_)
