#if !defined(AFX_UIWNDANALYSE_H__BDBAA802_027D_48DB_800A_5DCC44066E64__INCLUDED_)
#define AFX_UIWNDANALYSE_H__BDBAA802_027D_48DB_800A_5DCC44066E64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewAnalyse.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewAnalyse window
#include "../../BaseClass/MemBufferDC.H"
#include "RecordTestDrawBase.h"
#include "../RecordGlobalDefine.h"
#include "ParaSort.h"

#include "../MR1200BaseApp.h"
// #include "../RecordTest/RecordTest.h"
// #include "../Comtrade/ComtradeMngr.h"
#define MIN_PELS 40                     //左键放大的最小范围
#define ZOOMBMP_TO_CURSOR 2

#define RECORDBUFFERTYPE_RECORDBUFFER    0
#define RECORDBUFFERTYPE_MAPFILEBUFFER   1

//分析单通道录波数据
class CViewAnalyse :public CRecordTestDrawBase
{
// Construction
public:
	CViewAnalyse();
	virtual ~CViewAnalyse();

	//CMemBufferDC m_oMemDC;
	//暂时没有用
	//long m_nShowContent;//显示内容，0-实验数据，1-打开文件的数据

	//原设计的目的是可以将不同的通道放在不同的page上
	//CDrawBaseObjectList m_listDrawPages;  
	//CDrawVariablesMngr* m_pCurrentPageVariables;//当前页面的通道
	
	//录波数据的长度
	double m_dOscillographTimeLong;
	MrDraw::DRAWMEMBUFFERPOS m_oOscillographBufferPos;

	BOOL m_bRecordPageChanged;
	double m_dAxisMinTimeBack;
	double m_dAxisMaxTimeBack;

	BOOL m_bWaveAnalyse;
	
// Attributes
public:
// 	//关键字
	long m_nPostSysOptr;
	long m_nPostSysTimer;
	long m_nRecordBufferType;   //录波数据的种类0=RecordBuffer；1=RecordMapFile

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewAnalyse)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual void InitDrawBeginEndTime();
	virtual void InitDrawPoints();		

	//从CDrawMr1200RecordBase继承的函数
	virtual void InitDrawBufferPos();
	virtual void SelectNextChannel();
	virtual void SelectPrevChannel();
	virtual void MoveChanDown();
	virtual void MoveChanUp();
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void ArrowLeft();
	virtual void ArrowRight();
	virtual void ArrowUp();
	virtual void ArrowDown();
	virtual void ZoomInTime(long nMode = 0);
	virtual void ZoomOutTime(long nMode = 0);
	virtual void ZoomInChan();
	virtual void ZoomOutChan();

	//从CUIWindowBase派生的
	virtual void Enable(long nEnable, BOOL bEnableWindow);
	virtual BOOL UICreate(CWnd *pParent);
	virtual long InitAttributes();
	virtual long OnSystemMessage(UINT nSysMsgID, long &nImpCount, long &nRunCount);
	virtual CBaseObject* CreateNewAttributeChild(long nClassID);
	virtual CBaseObject* CreateNewAttributeChild(LPCTSTR pszClassID);
	//virtual long SerializeOwn(CBinarySerializeBuffer &oBinaryBuffer);
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual UINT GetClassID() {        return CMTRDCLASSID_WNDWAVEANALYSE;                               }

	//自身
	//void CreateVariablesFromComtradeFile(int& nAnalogChanAmount, int& nBinaryChanAmount,long nDataPoints);
	void GetSaveDataPos(long nMode,long& nBegin1,long& nLen1,long& nBegin2,long& nLen2);	
//	void SetCurrentShowContent(long nSet)	{	m_nShowContent = nSet;	}//暂时没有用

	//virtual BOOL CalCurrentDataPosEx(MrDraw::DRAWMEMBUFFERPOS &oDrawBufferPos, long nSampleRate, double dMax,double dMin);
	virtual BOOL CalCurrentDataPos(double dMax,double dMin);
	virtual long CalCurrentDataPosEx(double dMax,double dMin
		, CRecordTest *pRecordTest
		, CMemBufferInterface *pRefBuffer
		, MrDraw::DRAWMEMBUFFERPOS &oDrawBufferPos
		, MrDraw::DRAWMEMBUFFERPOS &oOscillographBufferPos);


	virtual void InitFromComtrade();
	virtual void InitFromRecordTest(long nDataLen, long nSamRateForDraw);

	void InitFromRecordTest();
	void CalXPosByTimeAxis(double dMax=-1, double dMin=-1);
	void InitDrawVariablesByRecordTest();
	void CreateMemDC();				//创建绘图缓存
	virtual void InitTimeAxis();  //2022-4-24  lijunqing 初始化时间坐标，可被重载设置个性化
	
	void SetTimeMoveCursor(HCURSOR hCursor) {	m_pTimeCursorDraw->SetMoveCursor(hCursor);	}

	//参数显示，计算
	void CalParaRect();
	void DrawPara(CDC* pDC);
	void InitByBorder();
	void AdjustAllDrawObjectsPos();
	void DrawAnalyse();
	void OnDraw(CDC *pDC);
	
	static UINT  DrawAnalyseThread(LPVOID pParam);
	static UINT  ReadOnlineDataThread(LPVOID pParam);
	static UINT  ReadComtradeFileThread(LPVOID pParam);
	BOOL m_bInDrawAnalyseThread;

protected:
	void XOnMouseMove(UINT nFlags, CPoint point);
	void XOnLButtonDown(UINT nFlags, CPoint point);
	void XOnLButtonUp(UINT nFlags, CPoint point);
	void XOnRButtonDown(UINT nFlags, CPoint point);
	void XOnRButtonUp(UINT nFlags, CPoint point);
// 	afx_msg void OnPaint();
	void XOnLButtonDblClk(UINT nFlags, CPoint point);
	void XOnRButtonDblClk(UINT nFlags, CPoint point);
	void OnSizeEx(UINT nType, int cx, int cy);

	LRESULT XOnInvalidateVertRangeStateAxis(WPARAM wParam, LPARAM lParam);
	LRESULT XOnVariableSizeChanged(WPARAM wParam, LPARAM lParam);
	LRESULT XOnVariablePositionChanged(WPARAM wParam, LPARAM lParam);
	LRESULT XOnVariableSelectChanged(WPARAM wParam, LPARAM lParam);
	LRESULT XOnTimeAxisChanged(WPARAM wParam, LPARAM lParam);
	LRESULT XOnTimeCursorPositionChange(WPARAM wParam, LPARAM lParam);
	LRESULT XOnTimeCursorSelectChange(WPARAM wParam, LPARAM lParam);
	LRESULT XOnSaveComtradeFile(WPARAM wParam, LPARAM lParam);
	LRESULT XOnTimeCursorMessage(WPARAM wParam, LPARAM lParam);
	//LRESULT XOnDrawVariableShowChanged(WPARAM wParam, LPARAM lParam);
	//LRESULT XOnSetVariableAxisRange(WPARAM wParam, LPARAM lParam);
	LRESULT XOnVariableShow(WPARAM wParam, LPARAM lParam);
	LRESULT XOnAnalyseRecordViewMapChanged(WPARAM wParam, LPARAM lParam);
	LRESULT XOnOnlineRecordWriteFinished(WPARAM wParam, LPARAM lParam);
	LRESULT XOnOnlineRecordDataCopy(WPARAM wParam, LPARAM lParam);
	LRESULT XOnDrawSetChanged(WPARAM wParam, LPARAM lParam);

protected:
// 	BOOL m_bByRecordTest;
	BOOL m_bCanChanged;//可以使用鼠标圈定区域放大
	//MR1200SYSANALYSEMNGR m_oDrawVarsOld;//保存原来的录波设置，在退出的时候恢复原来的设置,fdp add 2010.7.7
	void LoadZoomBmp();

	//fdp add 2010.6.4
	long m_nAttrSpyState[MAX_MR1200_CHANNELS][MAX_MR1200_VARIABLE_ATTR_BUFFERS];//保存监视状态的变量
	long m_nVariableSpyState[MAX_MR1200_CHANNELS];
//	void SaveLastSpyState(); //保存监视状态
//	void ReSetSpyState();    //将各个通道及其各个参数的监视状态回到原来的状态
//	void InitBackUpSpyState(); //初始化m_nAttrSpyState和m_nVariableSpyState数组
//	void SetVariableRect();
//	BOOL CalCurrentDataPosByOpenFile(double dMax,double dMin);
//	void CalPara(long nBeginPos);
	virtual void InitCurrDrawPageVariables();//chenling 需要改变m_nTextHeight的高度 改成虚函数
	void AttachCurrentVariable();

	//调整绘制的区域，通道调整的区域只是区域的right的值
	void InitDrawRectByDrawStruct();
	void ReSetBorder(const CRect &rect);
	void ReSetMainRect(const CRect &rect);

	CDrawVariable* FindDrawVariableBySelIndex(long nIndex);
	void InitViewAnalyse();

	//fdp add 2010.7.7
	void InitDrawVarRect();
	void SetBorder();
	
	//关联所有绘图对象的Parent窗口
	void SetAllObjParentWnd();

private:
	BOOL IsUseRecorBuffer()      {    return (m_nRecordBufferType == RECORDBUFFERTYPE_RECORDBUFFER);    }
	BOOL IsUseMapFileBuffer()    {    return (m_nRecordBufferType == RECORDBUFFERTYPE_MAPFILEBUFFER);   }

//////////////////////////////////////////////////////////////////////////
//使用映射文件的相关处理
private:
#define DRAW_HEIGHT   20
#define WAIT_DRAW_POS   10
#define ONLINE_WITE_DRAW_POS   -30
#define CALTHREAD_DRAW_POS   -50

	void MapRecorBuffer(double dBeginTime, double dTimeLong);
	void DrawWait();
	void DrawInWritingState();
	void DrawCalThreadState();
	void DrawRecordDataBufferState(long nTotal, long nIndex);
	void DrawSaveComtradeFileState(long nTotal, long nIndex);
	
	long GetAnalogVariableCount();
	BOOL m_bHasUICreated;

public:
	virtual void SetInRecordProcessThreadState(BOOL bInState = TRUE);
	void FireTimeAxisChangedSysOptr();

	void WaveAnalyse();
	void CalValues();
	BOOL CalValues(long nTimeCursorPos);

	void WriteAttrFile(long nAttrID);
};


extern BOOL g_bWriteAttrFileWhenWaveAnalyse;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UIWNDANALYSE_H__BDBAA802_027D_48DB_800A_5DCC44066E64__INCLUDED_)
