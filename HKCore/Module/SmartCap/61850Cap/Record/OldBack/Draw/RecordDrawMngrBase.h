// RecordDrawMngrBase.h: interface for the CRecordDrawMngrBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RecordDrawMngrBase_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_)
#define AFX_RecordDrawMngrBase_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBaseMngr.h"
#include "DrawSysTime.h"
#include "ParaSort.h"
#define VER_MOVE_ONCE 1  //通道垂直一次移动5个像素
#define TIME_MOVE_ONCE 1 //时间轴一次移动一格时间
#define TIME_ZOOM_RATE 2 //时间放大比率，缩小是其倒数
#define VER_ZOOM_RATE 1.5 //通道放大比率
#define OUT_RANGE 5.0 //采集卡的输出最值

class CRecordDrawMngrBase : public CDrawBaseMngr  
{
public:
	CRecordDrawMngrBase();
	virtual ~CRecordDrawMngrBase();

public:
	CRect m_rcTimeandProgress;
	CDrawVariablesMngr  m_oVariableMngr;    //通道管理  
// 	static long g_snWaveDrawAreaGap;
// 	static long g_snBottomRectHeight;
// 	static long g_snTimeandProgressRectHeight;
	double m_dRecordDataTimeLength;    //当前录波数据的总的时间长度，单位为s
	double m_dMinTimeInOneSreen;       //当前屏幕能够显示的最小时间长度 ,单位为秒
	double m_dMaxTimeInOneSreen;       //当前屏幕能够显示的最大时间长度 ,单位为秒
	CDrawSysTime m_oDrawSysTime;       //系统时间绘制
	CRect m_rcWaveDrawEx;              //波形绘图区域的扩展

	//绘图波形数据点的起始和终止位置
	double m_dDrawBeginTime;
	double m_dDrawEndTime;

public:
	virtual void InitDrawBeginEndTime();
	void SetRecordDataTimeLength(double dTime) {     m_dRecordDataTimeLength = dTime;   }

	//继承的方法
	UINT GetClassID()	{	return 0;	}
	virtual void Init();
	virtual void SetBorder(CDC *pDC, const CRect &rect, BOOL bUseClipRect=TRUE);
	virtual void SetParentWnd(CWnd* pParentWnd);
	virtual BOOL CalCurrentDataPos(double dMax,double dMin);
	//自身的方法
	void SetMaxShowOneSreen(double dMaxShowOneSreen){		m_dMaxTimeInOneSreen	= dMaxShowOneSreen;	}
	void SelectNextChannel(CDrawBase *pChannel);
	void SelectPrevChannel(CDrawBase *pChannel);
	void AdjustChanState(); 
	void SelectChannel(CDrawVariable *pVariable);

	//按键消息
	virtual void SelectNextChannel();
	virtual void SelectPrevChannel();
	virtual void MoveChanDown();
	virtual void MoveChanUp();
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void ArrowLeft();
	virtual void ArrowRight();
	virtual void ArrowDown();
	virtual void ArrowUp();
	virtual void ZoomInTime(long nMode = 0);//nMode = 0表示以波形窗口中心进行缩放，nMode = 1表示缩放两个光标之间的波形，nMode = 2表示以主光标进行缩放
	virtual void ZoomOutTime(long nMode = 0);//nMode = 0表示以波形窗口中心进行缩放，nMode = 1表示缩放两个光标之间的波形，nMode = 2表示以主光标进行缩放
	virtual void ZoomInChan();
	virtual void ZoomOutChan();

	virtual void DrawMainBack(CDC *pDC);
	virtual void DrawMain(CDC *pDC);


	virtual void ZoomOutTime_GetTimeCenter();//以波形窗口中心进行缩放
	virtual void ZoomOutTime_GetTimeCursorXA();//以主光标进行缩放
	virtual void ZoomOutTime_GetTimeCursorXAXB();//缩放两个光标之间的波形
	virtual void ZoomInTime_GetTimeCursorXA();//以主光标进行放大
	virtual void ZoomInTime_GetTimeCenter();//以波形窗口中心进行放大
	virtual void ZoomInTime_GetTimeCursorXAXB();//放大两个光标之间的波形

protected:
	void DrawWaveAreaBorder(CDC *pDC);
	void DrawGrid(CDC *pDC);
};

#endif // !defined(AFX_RecordDrawMngrBase_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_)
