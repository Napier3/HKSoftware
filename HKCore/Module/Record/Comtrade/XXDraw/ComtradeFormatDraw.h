// ComtradeFormatDraw.h: interface for the CComtradeFormatDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined COMTRADEFORMATDRAW_H_
#define COMTRADEFORMATDRAW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ComtradeAnalogDraw.h"
#include "ComtradeBinaryDraw.h"
#include "..\ComtradeMngr.h"
#include "..\..\MemBuffer\TMemBuffer.h"

#include "..\..\XDrawBase\XDrawViewBase.h"

#define ANALOG_DRAW_MODE_GROUP   0
#define ANALOG_DRAW_MODE_SIGLE    1

class CComtradeFormatDraw : public CXDrawViewBase  
{
public:
	CComtradeFormatDraw();
	virtual ~CComtradeFormatDraw();

protected:
	CComtradeMngr	*m_pCmtrdInterface;	//同绘图类绑定的接口数据
	CMemBuffer_CPoint	*m_pMemBuf_Point;		//绘图的点的数据缓冲区空间，公用时间坐标轴

	int		m_iTitleMaxLen;						////所有通道标题的最大长度
	CMemBuffer_float	*m_pTimeDataBuff;

public:
	//下面的三个成员变量为绘图的标志
	BOOL	m_bShowTagBar;			//信息标签
	BOOL	m_bShowUsedOnly;		//是否只显示使用的模拟通道
	int		m_nAnalogDrawMode;		//模拟通道的绘图模式 0：同类模拟量一起绘制；1：每个模拟量一个图形

// 	CPDBaseObjectList listDrawElement;	//绘图图元的链表

protected://注册绘图类
	void	RegisterComtradeDrawClass();
	void	UnRegisterComtradeDrawClass();

public:
	CComtradeDrawBaseClass*GetComtradeDrawClassByName(CString strType);
	BOOL IsAnalogDrawModeSingle()	{	return m_nAnalogDrawMode == ANALOG_DRAW_MODE_SIGLE;	}
	BOOL IsAnalogDrawModeGroup()	{	return m_nAnalogDrawMode == ANALOG_DRAW_MODE_GROUP;	}

public:
	void	InitIt();
	void	EndIt();

	//################################################################
	//将绘图接口数据指针同绘图类绑定
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);
	//void	BindComtradeInterface(CComtradeMngr*pInterface);

	//根据三个绘图标志生成绘图图元链表
	void	InitDrawListByFlags(CDC*pDC);

protected:
	void XCreateElement_Group(CWnd *pParentWnd);
	void XCreateElement_Single(CWnd *pParentWnd);
	void XCreateElement_Binary(CWnd *pParentWnd);

private:
	//根据绘图的标志设置通道的单位、恢复通道原来的单位
	void	MakeCHUnitTheSame(CComtradeDrawBaseClass*pElement);
	void	ResumeCHUnit(CComtradeDrawBaseClass*pElement);
	//再将所有的通道都与绘图图元绑定之后，必须设置坐标的刻度范围
	void	SetElementAxisRange();
	//下面是绘图模式改变的接口函数
	
protected:
	void	GetCHTitleMaxLength();						//获得各通道标题的最大长度
	void	TypeSetAllElement(CSize size,long &lDrift);	//对绘图元列表进行排版
	void	TypeSetAllElementAgain(CSize size,long &lDrift);	//重新排版
	void	InitCHTitlePosAfterTypeset();						//排版后对通道数据的标题位置进行初始化
	void	InitDrawElementAxis();				//初始化坐标系
public:
	//初始化绘图的接口函数
	void	InitDrawElement(CSize size,long &lDrift);	//传入绘图区域的大小，设置各绘图图元的位置
public:
	//绘图接口函数
	void	DrawTheGraph(CDC*pDC);			//总的绘图函数
	void	DrawTheGraphCurve(CDC*pDC);
	void	DrawComtrade(CDC*pDC);			//绘制绘图图元中的图形
private:
	int		m_iBeginIndex,m_iEndIndex;		//绘图的起始、终止点
	void	SetDrawBeginEndIndex(int iBeginIndex,int iEndIndex);
	void	DrawTheComtradeCurve(CComtradeDrawBaseClass*pElement,int iActiveCHIndex=-1);

//###################################################################
//图形操作的通用函数
private:
	void SetElementAxisXRange();
	void FindBeginEndIndex(float fBT,float fET);
	void HalfSearchIndex(float fTime,int &iTimeIndex);
	void GetElementAxisUnit(float &fAxisUnit);
public:
	int  FindTimeIndex(float fTime);
//定义图形的操作函数，图形的放大、缩小，移动
public:
	void OnCmtrdGrphOP_Zoomout();		//图形放大
	void OnCmtrdGrphOP_Resume();		//图形复原
	void OnCmtrdGrphOP_Zoomin();		//图形的缩小
	void OnCmtrdGrphOP_Moveleft();		//相左移动
	void OnCmtrdGrphOP_Moveright();		//向右移动

	void OnCmtrdGrphOP_RangeZoomout(int iXL,int iXR);	//图形区域放大
	void OnCmtrdGrphOP_RangeZoomout(float fTime1,float fTime2);	//图形区域放大

	void GetTimeByCursorPos(int iXL,int iXR,float &fTime1,float &fTime2);
	void GetXPosByTimeVal(float fTime1,int &iXPos);
//定义其他的对外接口函数
public:
	//获得所有图元的绘图的矩形的位置
	CRect* GetAllElementRectPos();
	int  GetTotalElement();

	//定义鼠标选中活动的图元中的通道名称的相关成员和函数
private:
	CComtradeDrawBaseClass*	m_pNowActElement;

public:
	BOOL	OnLButtonDown(CPoint point);
	BOOL	OnLButtonDown(CPoint point,CDC*pDC);
	BOOL	OnLButtonDown(CPoint point,CWnd*pParent);
	CComtradeDrawBaseClass*GetNowActiveElement(CPoint point);
	CComtradeDrawBaseClass*GetNowActiveElement();
	int		GetNowActCHIndex();
	void	SetNowActiveElement(CComtradeDrawBaseClass*pElement);
};

#endif // !defined(COMTRADEFORMATDRAW_H_)
