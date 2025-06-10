// Mr1200RecordDrawBase.h: interface for the CDrawMr1200RecordBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MR1200RECORDDRAWBASE_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_)
#define AFX_MR1200RECORDDRAWBASE_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XRecordDrawBase.h"
#include "../RecordTest/RecordTest.h"
#include "../Draw/DrawSysTime.h"

//2023-7-22  lijunqing 从CXRecordDrawBase移动过来
#include "../Comtrade/ComtradeMngr.h"

#define VER_MOVE_ONCE 1  //通道垂直一次移动5个像素
#define TIME_MOVE_ONCE 1 //时间轴一次移动一格时间
#define TIME_ZOOM_RATE 2 //时间放大比率，缩小是其倒数
#define VER_ZOOM_RATE 1.5 //通道放大比率
#define OUT_RANGE 5.0 //采集卡的输出最值

/*
录波通道管理，m_oVariableMngr管理了所有的录波通道，此对象实现
1、通道的分页管理
2、录波的示波部分
3、管理了RecordTest
*/

class CRecordTestDrawBase : public CXRecordDrawBase  
{
public:
	CRecordTestDrawBase();
	virtual ~CRecordTestDrawBase();

public:
	CMemBufferInterface* m_ppRecordBuffer[MAX_MR1200_CHANNELS];

	CRect m_rcTimeandProgress;
	CExBaseList  m_oVariableMngr;    //通道管理  
	double m_dRecordDataTimeLength;    //当前录波数据的总的时间长度，单位为s
	double m_dMinTimeInOneSreen;       //当前屏幕能够显示的最小时间长度 ,单位为秒
	double m_dMaxTimeInOneSreen;       //当前屏幕能够显示的最大时间长度 ,单位为秒
	CDrawSysTime m_oDrawSysTime;       //系统时间绘制
	//CRect m_rcWaveDrawEx;              //波形绘图区域的扩展

	//绘图波形数据点的起始和终止位置
	double m_dDrawBeginTime;
	double m_dDrawEndTime;

	//2023-7-22  lijunqing 从CXRecordDrawBase移动过来
	CRcdComtradeFile *m_pRcdComtradeFile;
	CRecordTest *m_pRecordTest;

public:
	virtual long GetTotalPoints();
	virtual long GetSampleRate();

	//综合属性绘图
	void AddAttrsDraw();
	
	//得到计算的起点位置
	long GetCalAttrBeginPos(long nTimeCursorPos);

	virtual void InitDrawBeginEndTime();
	virtual void SetRecordDataTimeLength(double dTime) {     m_dRecordDataTimeLength = dTime;   }

	//继承的方法
	UINT GetClassID()	{	return 0;	}
	virtual void Init();
	//virtual void SetBorder(CDC *pDC, const CRect &rect, BOOL bUseClipRect=TRUE);
	virtual void SetParentWnd(CWnd* pParentWnd);
	virtual BOOL CalCurrentDataPos(double dMax,double dMin);
	//自身的方法
	virtual void SetMaxShowOneSreen(double dMaxShowOneSreen){		m_dMaxTimeInOneSreen	= dMaxShowOneSreen;	}
	void SelectNextChannel(CDrawBase *pChannel);
	void SelectPrevChannel(CDrawBase *pChannel);
	void AdjustChanState(); 
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

// 	virtual void DrawMainBack(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
// 	virtual void DrawMain(double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
// 	virtual void DrawMain_Wave(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);


	virtual void ZoomOutTime_GetTimeCenter();//以波形窗口中心进行缩放
	virtual void ZoomOutTime_GetTimeCursorXA();//以主光标进行缩放
	virtual void ZoomOutTime_GetTimeCursorXAXB();//缩放两个光标之间的波形
	virtual void ZoomInTime_GetTimeCursorXA();//以主光标进行放大
	virtual void ZoomInTime_GetTimeCenter();//以波形窗口中心进行放大
	virtual void ZoomInTime_GetTimeCursorXAXB();//放大两个光标之间的波形

	virtual void SaveRecordDrawObjectControl();
	virtual void InitRecordDrawObjectPosByControl();

// protected:
// 	void DrawWaveAreaBorder(CDC *pDC);
// 	void DrawGrid(CDC *pDC);
// 	void DrawMainEx(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void AdjustAxisRange();

public:
	//COMTRADEFILE保存
	static UINT  SaveComtradeFileThread(LPVOID pParam);
	virtual void SetInRecordProcessThreadState(BOOL bInState);
	virtual void GetComtradeSaveDataPos(long nMode,long& nBegin1,long& nLen1,long& nBegin2,long& nLen2);
	virtual void DrawSaveComtradeFileState(CDC *pDC, CRect rcBorder, long nTotal, long nIndex);
	virtual void InitComtradeChannels(CRcdComtradeFile *pComtradeFile);

protected:
// 	double m_dDeltaT;
// 	double m_dTa;
// 	double m_dTb;

	virtual void FireTimeAxisChangedSysOptr(double dTOffset);
	CDrawVariable* GetNextVariable(CDrawVariable *pCurr);
	CDrawVariable* GetPrevVariable(CDrawVariable *pCurr);

public:
	CMemBufferInterface* GetDefaultRefBuffer();
	void ClearBuffer();


	void CreateDrawVariableByRecordTest(int& nAnalogChanAmount, int& nBinaryChanAmount);

	virtual void AddBinaryDrawVariable(CExBaseObject* pVaraible, long &nCurrentChans);
	virtual CDrawAnalogVariable* AddAnalogDrawVariable(CExBaseObject* pVaraible, long nCurrentChans,  long nChIndex);
	virtual CDrawAnalogVariable* NewAnalogVariable();
	virtual void InitAnalogDrawVariable(CRtSingleVariable* pSingle, long &nCurrentChans, CDrawAnalogVariable *pAnalog, BOOL bNew);

};

extern double g_dCursorTime[3];

#endif // !defined(AFX_MR1200RECORDDRAWBASE_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_)
