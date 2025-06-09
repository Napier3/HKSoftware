// ViewAnalyse.cpp : implementation file
//

#include "stdafx.h"
#include "ViewAnalyse.h"
// #include "../MRONLINERECORD/MrOnlineRecordEx.h"
#include "../MR1200BaseApp.h"
#include "../../System/TickCount32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define _USE_ANALYSE_

#define TIMER_ID_INIT  32
#define TIMER_ID_INIT_LONG  200

BOOL g_bWriteAttrFileWhenWaveAnalyse = FALSE;

// extern CRecordTest *g_pCurrRecordTest;

CViewAnalyse::CViewAnalyse()
{
	m_bWaveAnalyse = FALSE;
// 	g_theRecordApp.m_pUIWndThread->m_dwAnalyseWndCreate = ::GetTickCount();
// 	g_theRecordApp.m_pUIWndThread->m_nCanDeletePageRef++;

	m_bHasUICreated = FALSE;

	//m_pCurrentPageVariables = NULL;

// 	m_pCursorLeft		= NULL;
// 	m_pCursorRight		= NULL;
// 	m_pSelectNextCursor	= NULL;
// 	m_pSelectPrevCursor	= NULL;
// 	m_pSelChanDown		= NULL;
// 	m_pSelChanUp		= NULL;
// 	m_pMoveChanDown		= NULL;
// 	m_pMoveChanUp		= NULL;
// 	m_pMoveLeft			= NULL;
// 	m_pMoveRight		= NULL;
// 	m_pTimeZoomIn		= NULL;
// 	m_pTimeZoomOut		= NULL;
// 	m_pChanZoomIn		= NULL;
// 	m_pChanZoomOut		= NULL;
// 	m_pLockCursor		= NULL;
// 	m_pNextPage			= NULL;
// 	m_pPrevPage			= NULL;
// 	m_pReFresh			= NULL;
// 	
// 	m_pTimeCursorMove	= NULL;
// 	m_pPageChanged		= NULL;
	//m_nShowContent		= 0;
	m_bCanChanged		= FALSE;

	m_nPostSysOptr		= 0;
	m_nPostSysTimer		= 0;
	//InitBackUpSpyState();
	m_pPointBuffer = NULL;
	InitDrawPoints();
	m_dOscillographTimeLong = 0;
	m_bInDrawAnalyseThread = FALSE;
	
	m_nRecordBufferType = RECORDBUFFERTYPE_RECORDBUFFER;

#ifdef _debug_oneline_recordex
	SetMaxShowOneSreen ( MAX_TIME_IN_ONE_SCREEN );
#endif

	m_dAxisMinTimeBack = 0;
	m_dAxisMaxTimeBack = 0;
	m_bRecordPageChanged = FALSE;
}

CViewAnalyse::~CViewAnalyse()
{
	m_bHasUICreated = FALSE;

	if (m_pPointBuffer != NULL)
	{
		delete m_pPointBuffer;
		m_pPointBuffer = NULL;
	}

	g_wBufferState = 0;
	ClearBuffer();
	
// 	
// //	g_theRecordApp.UnRegisterSysOptrCall(m_nOnSysOptrID, WM_ANALYSE_SETVARIABLEAXISRANGEANDSHOW, this);
// 	g_theRecordApp.UnRegisterSysOptrCall(MR1200_SYSOPTR_ONLINERECORDEX_WRITEFINISHED, WM_ONLINERECORDEX_WRITEFINISHED, this);
// 	g_theRecordApp.UnRegisterSysOptrCall(MR1200_SYSOPTR_ONLINE_RECORD_DATA_COPY, WM_ONLINERECORD_DATA_COPY, this);
// 	g_theRecordApp.UnRegisterSysOptrCall(MR1200_SYSOPTR_DRAWSET_CHANGED, WM_DRAWSET_CHANGED,this);		
// 
// 	//COMTRADE文件保存
// 	g_theRecordApp.UnRegisterSysOptrCall(MR1200_SYSOPTR_SAVE_RECORDFILE, WM_SAVERECORDFILE, this);		

// 	if (g_theRecordApp.IsRecordDataModeComtrade())
// 	{
// 		ClearMR1200SysAnalyseMngr();
// 	}

}
// 
// BEGIN_MESSAGE_MAP(CViewAnalyse, CStatic)
// 	//{{AFX_MSG_MAP(CViewAnalyse)
// 	ON_WM_MOUSEMOVE()
// 	ON_WM_LBUTTONDOWN()
// 	ON_WM_LBUTTONUP()
// 	ON_WM_RBUTTONDOWN()
// 	ON_WM_RBUTTONUP()
// 	ON_WM_PAINT()
// 	ON_WM_LBUTTONDBLCLK()
// 	ON_WM_RBUTTONDBLCLK()
// 	ON_MESSAGE(WM_TIME_CHANGED, OnTimeCursorMessage)
// 	ON_MESSAGE(WM_INVALIDATE_RANGESTATEAXIS, OnInvalidateVertRangeStateAxis)
// 	ON_MESSAGE(WM_VARIABLE_SIZE_CHANGED, OnVariableSizeChanged)
// 	ON_MESSAGE(WM_VARIABLE_POS_CHANGED, OnVariablePositionChanged)
// 	ON_MESSAGE(WM_VARIABLE_SELECT_CHANGED, OnVariableSelectChanged)
// 	ON_MESSAGE(WM_TIMEAXIS_CHANGED, OnTimeAxisChanged)
// 	ON_MESSAGE(WM_TIMECURSOR_POS_CHANGE, OnTimeCursorPositionChange)
// 	ON_MESSAGE(WM_TIMECURSOR_SELECT_CHANGE, OnTimeCursorSelectChange)
// 	ON_MESSAGE(WM_SAVERECORDFILE, OnSaveComtradeFile)
// 	//ON_MESSAGE(WM_ANALYSE_SETVARIABLEAXISRANGEANDSHOW, OnVariableShowAndSetAxisRange)
// 	ON_WM_SIZE()
// 	//}}AFX_MSG_MAP
// 	ON_MESSAGE(WM_ANALYSE_RECORD_VIEWMAP_CHANGED, OnAnalyseRecordViewMapChanged)
// 	ON_MESSAGE(WM_ONLINERECORDEX_WRITEFINISHED, OnOnlineRecordWriteFinished)
// 	ON_MESSAGE(WM_ONLINERECORD_DATA_COPY, OnOnlineRecordDataCopy)
// 	ON_MESSAGE(WM_DRAWSET_CHANGED, OnDrawSetChanged)
// END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CViewAnalyse message handlers
LRESULT CViewAnalyse::XOnDrawSetChanged(WPARAM wParam, LPARAM lParam)
{
	if (wParam == UPDATE_WAVESHOW_VARSHOW)
	{
		XOnVariableShow(wParam, lParam);
	}
	else if (wParam == UPDATE_WAVESHOW_POS_MIDLINE)
	{
		if (lParam == DRAW_WAVEPOS)
		{					
			//自动调整、
			int i = 0;
			AdjustDrawVariablePosition();
		
			//SaveRecordDrawObjectControl();
			m_pRangeStateAxis->AttachDrawObject(m_pCurrDrawVariable);		
			AdjustChanState();
			DrawAnalyse();
		}
		else if(lParam == DRAW_WAVEMIDLINE_SHOW)
		{
			//中心线的显示
			int i = 1;
			DrawAnalyse();
		}
	}
	else
	{
	}

	return 0;
}

LRESULT CViewAnalyse::XOnOnlineRecordDataCopy(WPARAM wParam, LPARAM lParam)
{
/*
	long nTotal = 0;
	long nIndex = 0;

	nTotal = HIWORD(lParam);
	nIndex = LOWORD(lParam);
	DrawRecordDataBufferState(nTotal, nIndex);
	
	if (wParam == SYSOPTRPARA_ONLINERECORDDATACOPY_FINISH)
	{
		

		if (g_theRecordApp.IsRecordDataModeComtrade())
		{
			CMrOnlineRecordEx *pOnlineRecord = CMrOnlineRecordEx::g_pMrOnlineRecordEx;
			m_dMaxTimeInOneSreen = pOnlineRecord->GetSavedRecordTimeLong();
		}
		else
		{

		}

		MapRecorBuffer(0, SM_ONLINE_EX_DATAAREA_PAGE_SIZE);
		InitViewAnalyse();
	}
	else if (wParam == SYSOPTRPARA_ONLINERECORDDATACOPY_COPY
		|| wParam == SYSOPTRPARA_ONLINERECORDDATACOPY_BEGIN)
	{
		DrawRecordDataBufferState(nTotal, nIndex);
	}
	else if (wParam == SYSOPTRPARA_ONLINERECORDDATACOPY_READDATA)
	{//开始读在线录波数据
		DrawRecordDataBufferState(0, 0);
		//
		//g_theRecordApp.ReadOnlineRecordData();
		AfxBeginThread(ReadOnlineDataThread, this);
	}
	else
	{

	}
*/
	
	return 0;
}


LRESULT CViewAnalyse::XOnAnalyseRecordViewMapChanged(WPARAM wParam, LPARAM lParam)
{
/*
	if (!::IsWindow(m_hWnd))
	{
		return 0;
	}
	
	if (wParam == 1)
	{
		return 0;
	}
	
	
	g_theRecordApp.AttachOnlineRecordExBuffer();

	//初始化m_oDrawBufferPos
	InitDrawBufferPos();  

	//根据录波数据缓冲区的数据长度，计算获得当前显示的波形的长度
	//同时设置时间坐标的范围
	InitTimeAxis();
	
	//计算绘图缓冲区CPoint的X位置
	CalXPosByTimeAxis();

	DrawAnalyse();
	CalValues();
	FireTimeAxisChangedSysOptr();
*/

	return 0;
}

LRESULT CViewAnalyse::XOnOnlineRecordWriteFinished(WPARAM wParam, LPARAM lParam)
{
/*
	if (m_bHasUICreated)
	{
		m_pDrawAnalyseThread = AfxBeginThread(DrawAnalyseThread, this);
	}
	else
	{
	}
*/

	return 0;
}

LRESULT CViewAnalyse::XOnVariableShow(WPARAM wParam, LPARAM lParam)
{
/*
	if (m_bInDrawAnalyseThread)
	{	
		return 0;
	}

	PVAR_SHOW_RANGE pVarShow_Range = NULL;
	pVarShow_Range = (PVAR_SHOW_RANGE)lParam;
	ASSERT(pVarShow_Range != NULL);
	CDrawVariable* pVariable = FindDrawVariableBySelIndex(pVarShow_Range->nVariableIndex);

	if (pVariable == NULL)
	{
		return 0;
	}

	pVariable->SetShow(pVarShow_Range->nShowSet);

	AttachCurrentVariable();
	DrawAnalyse();
	*/

	return 0;
}

LRESULT CViewAnalyse::XOnTimeCursorMessage(WPARAM wParam, LPARAM lParam)
{
	if (lParam == 0) 
	{
		ZoomInTime();
	}
	else if (lParam == 1) 
	{
		ZoomOutTime();
	}
	else if (lParam == 2)
	{
		double dMax =0, dMin = 0;
		m_oTimeAxisDraw.GetOldMaxMinTime(dMax,dMin);
		m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
		
		CalValues();
		FireTimeAxisChangedSysOptr();

		DrawAnalyse();
	}
	else
	{
	}
	return 0;
}

void CViewAnalyse::SetInRecordProcessThreadState(BOOL bInState)
{
	m_bInDrawAnalyseThread = bInState;
}

LRESULT CViewAnalyse::XOnSaveComtradeFile(WPARAM wParam, LPARAM lParam)
{
/*
	if (wParam>= 0x0FFFFFFF && lParam >= 0x00FFFFFF)
	{
		AfxBeginThread(SaveComtradeFileThread, (CDrawMr1200RecordBase*)this);
	}
	else
	{
		ULONG nTotal = HIWORD(lParam);
		ULONG nIndex = LOWORD(lParam);

		if (wParam == 0)
		{
			DrawSaveComtradeFileState(nTotal, nIndex);
		}
		else
		{
			DrawMain();
			
		}
	}
	*/
	return 0;
}



LRESULT CViewAnalyse::XOnInvalidateVertRangeStateAxis(WPARAM wParam, LPARAM lParam)
{
	CDrawRangeStateAxis *pAxis = (CDrawRangeStateAxis*)wParam;
	CRect *pClipRect = pAxis->GetClipRect();

	if (pClipRect != NULL)
	{
		m_pParentWnd->InvalidateRect(pClipRect, FALSE);
	}
	else
	{
        CRect rc = pAxis->GetInvalidateRect();
        m_pParentWnd->InvalidateRect(&rc, FALSE);
	}

	return 0;
}


LRESULT CViewAnalyse::XOnVariableSizeChanged(WPARAM wParam, LPARAM lParam)
{
	DrawAnalyse();
	
	return 0;
}

LRESULT CViewAnalyse::XOnVariablePositionChanged(WPARAM wParam, LPARAM lParam)
{
	AdjustDrawNameRect();
	DrawAnalyse();
	SaveRecordDrawObjectControl();

	return 0;
}

LRESULT CViewAnalyse::XOnVariableSelectChanged(WPARAM wParam, LPARAM lParam)
{
	DrawAnalyse();
	
	return 0;
}

LRESULT CViewAnalyse::XOnTimeAxisChanged(WPARAM wParam, LPARAM lParam)
{
	CalXPosByTimeAxis();

	DrawAnalyse();
	
	return 0;
}

//wParam是光标指针
LRESULT CViewAnalyse::XOnTimeCursorPositionChange(WPARAM wParam, LPARAM lParam)
{
	CDrawTimeCursor* pCursor = (CDrawTimeCursor*)wParam;
	
	if (pCursor != NULL)
	{
		CRect rcOld, rcNew;
		pCursor->GetCurrCursorInvalidateRect(rcOld,rcNew);
		
		CalValues();

#ifdef _SHOW_PARA
		CalParaRect();
		CalDrawParasValue();  //2022-9-1  lijunqing

		CParaSortMngr oParaSortMngr(this,m_rcWaveDraw);
		m_pParentWnd->Invalidate(FALSE);
#else
		m_pParentWnd->InvalidateRect(rcNew, FALSE);
		m_pParentWnd->InvalidateRect(rcOld, FALSE);
		rcOld = pCursor->m_rcZoomBmpOld;
		rcNew = pCursor->m_rcZoomBmp;
		m_pParentWnd->InvalidateRect(rcNew, FALSE);
		m_pParentWnd->InvalidateRect(rcOld, FALSE);
#endif		
	}
	
	return 0;
}

LRESULT CViewAnalyse::XOnTimeCursorSelectChange(WPARAM wParam, LPARAM lParam)
{
	CDrawTimeCursor* pCursor = (CDrawTimeCursor*)wParam;
	
	if (pCursor != NULL)
	{
		CRect rcOld, rcNew;
		pCursor->GetInvalidateRect(rcOld,rcNew);

		CalValues();

#ifdef _SHOW_PARA
		CalParaRect();
		CalDrawParasValue();  //2022-9-1  lijunqing
		CParaSortMngr oParaSortMngr(this,m_rcWaveDraw);
#else
		m_pParentWnd->InvalidateRect(rcNew, FALSE);
		m_pParentWnd->InvalidateRect(rcOld, FALSE);
		rcOld = pCursor->m_rcZoomBmpOld;
		rcNew = pCursor->m_rcZoomBmp;
		m_pParentWnd->InvalidateRect(rcNew, FALSE);
		m_pParentWnd->InvalidateRect(rcOld, FALSE);
#endif		
	}
	
	return 0;
}

void CViewAnalyse::CreateMemDC()
{
	CRect rcClient;
	CDC *pDC = m_pParentWnd->GetDC();
	m_pParentWnd->GetClientRect(rcClient);
	CreateDrawMemDC(pDC, rcClient);
	m_pParentWnd->ReleaseDC(pDC);
}

void CViewAnalyse::Enable(long nEnable, BOOL bEnableWindow)
{
	//CUIWindowBase::Enable(nEnable,FALSE);
}

void CViewAnalyse::InitFromRecordTest(long nDataLen, long nSamRateForDraw)
{
	m_nSamRateForDraw = nSamRateForDraw;
	double dMax = 0,dMin =0;
	dMax = nDataLen;
	dMax /=  m_nSamRateForDraw;
	m_pRecordTest->init_RTATTRIBUTECAL_MIN_BUFFER_LEN(m_nSamRateForDraw);

	ClearBuffer();
	SetRecordDataTimeLength(dMax);
	m_dMinTimeInOneSreen = (double)g_dwOscillographMinTime / 1000;
	m_oTimeAxisDraw.SetOldMaxMinTime(m_dRecordDataTimeLength,0);
	SetMaxShowOneSreen(dMax);
	m_oTimeAxisDraw.SetMaxMinTime(m_dMaxTimeInOneSreen,dMin);
	MrDraw::ClearDrawBuffBeginEndPos(&m_oOscillographBufferPos);

	int nAnalogs = 0;
	int nBinarys = 0;
	m_dOscillographTimeLong = dMax;
	//	CreateVariablesFromComtradeFile(nAnalogs,nBinarys,nDataLen);
	InitViewAnalyse();

	// 	if (m_ppRecordBuffer[0] != NULL)
	// 	{
	// 		m_pRefBuffer = m_ppRecordBuffer[0];
	// 	}
	m_pRefBuffer = GetDefaultRefBuffer();

	if (nAnalogs > 0 || nBinarys > 0)//初始化第一个为选中通道
	{
		POS  pos = m_oVariableMngr.GetHeadPosition();
		m_pCurrDrawVariable = (CDrawVariable*)m_oVariableMngr.GetAt(pos);
		m_pCurrDrawVariable->SetSelect(TRUE);
	}

	//初始化MEMDC，初始化CDrawMr1200RecordBase区域
	InitByBorder();

	//初始化当前绘图的变量，包括设置当前选中变量
	InitCurrDrawPageVariables();

	//调整各变量绘图的位置
	CRecordTestDrawBase::AdjustDrawVariablePosition();
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetLockHead(FALSE);
	CalXPosByTimeAxis();
	CalParaRect();
}

void CViewAnalyse::InitFromComtrade()
{	
	if (m_pRcdComtradeFile->m_pnDataPoints == NULL) 
	{
		return;
	}
	
	long nDataLen = m_pRcdComtradeFile->m_pnDataPoints[0];
	long nSamRateForDraw = (long)(m_pRcdComtradeFile->m_pdSamRate[0]);

	InitFromRecordTest(nDataLen, nSamRateForDraw);
}

void CViewAnalyse::InitFromRecordTest()
{
	//保存示波的显示信息,在退出的时候恢复
	//InitDrawRectByDrawStruct();
	//根据RecordTest创建绘图变量
	InitDrawVariablesByRecordTest();

	//初始化m_oDrawBufferPos
	InitDrawBufferPos();  
	
	//初始化MEMDC，初始化CDrawMr1200RecordBase区域
	InitByBorder();

	//初始化当前绘图的变量，包括设置当前选中变量
	InitCurrDrawPageVariables();
	//原来在InitCurrDrawPageVariables函数内部，现在改到外部
	//调整各变量绘图的位置
	CRecordTestDrawBase::SetParentWnd(m_pParentWnd);
//	CDrawMr1200RecordBase::AdjustDrawVariablePosition();
	m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState.SetLockHead(FALSE);

	//根据结构体设置的通道位置调整通道位置
	InitDrawVarRect();
	//根据录波数据缓冲区的数据长度，计算获得当前显示的波形的长度
	//同时设置时间坐标的范围
	InitTimeAxis();
	
	//计算绘图缓冲区CPoint的X位置
	CalXPosByTimeAxis();
	
//#ifdef _USE_ANALYSE_
	//计算参数显示区域
	CalParaRect();
//#endif

}

void CViewAnalyse::InitDrawBufferPos()
{
	CMemBufferInterface* pRecordBuffer = GetDefaultRefBuffer();//m_ppRecordBuffer[0];
	
	ASSERT (pRecordBuffer != NULL);

	m_pRefBuffer = pRecordBuffer;
	MrDraw::InitDrawBuffPos(&m_oDrawBufferPos);
	m_nSamRateForDraw = m_pRecordTest->g_nSampleRate;

	DWORD dwDataLength = m_pRefBuffer->GetDataLength();
	m_dOscillographTimeLong = dwDataLength;
	m_dOscillographTimeLong /= m_pRecordTest->g_nSampleRate;

	//初始化整个录波数据的有效波形数据
	DWORD dwBufLen = m_pRefBuffer->GetBufferLength();
	DWORD dwFillPos = m_pRefBuffer->GetDataFillBeginPosition();

	MrDraw::ClearDrawBuffBeginEndPos(&m_oOscillographBufferPos);

	if (dwDataLength == 0)
	{
	}
	else if (dwBufLen > dwDataLength)
	{
		m_oOscillographBufferPos.nBuf1BeginPos = 0;
		m_oOscillographBufferPos.nBuf1EndPos   = dwFillPos-1;
		m_oOscillographBufferPos.nBuf2BeginPos = -1;
		m_oOscillographBufferPos.nBuf2EndPos = -1;
	}
	else
	{
		if (dwFillPos == dwBufLen)
		{
			m_oOscillographBufferPos.nBuf1BeginPos = 0;
			m_oOscillographBufferPos.nBuf1EndPos   = dwFillPos-1;
		}
		else if (dwFillPos == 0)
		{
			m_oOscillographBufferPos.nBuf1BeginPos = 0;
			m_oOscillographBufferPos.nBuf1EndPos   = dwBufLen-1;
		}
		else
		{
			m_oOscillographBufferPos.nBuf1BeginPos = dwFillPos;
			m_oOscillographBufferPos.nBuf1EndPos   = dwBufLen-1;
			m_oOscillographBufferPos.nBuf2BeginPos = 0;
			m_oOscillographBufferPos.nBuf2EndPos = dwFillPos - 1;
		}
	}

	m_oOscillographBufferPos.nGap = 1;
	m_oOscillographBufferPos.nBufLength = m_pRefBuffer->GetBufferLength();
}

//获取当前坐标范围之内的有效绘图数据时间
void CViewAnalyse::InitDrawBeginEndTime()
{
	m_oTimeAxisDraw.GetMaxMinTime(m_dDrawEndTime, m_dDrawBeginTime);
	
	if (m_dOscillographTimeLong <= m_dDrawEndTime)
	{
		m_dDrawEndTime = m_dOscillographTimeLong;
	}
	
	if (m_dOscillographTimeLong <= m_dDrawBeginTime)
	{
		m_dDrawBeginTime = m_dOscillographTimeLong;
	}
	
	if (m_dDrawBeginTime < 0.00000001)
	{
		m_dDrawBeginTime = 0;
	}
	
	if (m_dDrawEndTime < 0.00000001)
	{
		m_dDrawEndTime = 0;
	}
}

//数据规则：最早的数据表示时间为0，最新的一个数据为最大时间m_dOscillographTimeLong
BOOL CViewAnalyse::CalCurrentDataPos(double dMax,double dMin)
{
// 	if (m_pRefBuffer == NULL)
// 	{
// 		return FALSE;
// 	}
// 	
// 	//校验时间区段的范围
// 	if (m_dOscillographTimeLong <= dMax)
// 	{
// 		dMax = m_dOscillographTimeLong;
// 	}
// 	if (m_dOscillographTimeLong <= dMin)
// 	{
// 		dMin = m_dOscillographTimeLong;
// 	}
// 
// 	double dMaxTime = dMax;
// 	double dMinTime = dMin;
// 
// 	if (dMin >= dMax)
// 	{
// 		dMaxTime = dMin;
// 		dMinTime = dMax;
// 	}
// 
// 	long dwBeginIndex = dMinTime * m_pRecordTest->g_nSampleRate;
// 	long dwEndIndex = dMaxTime * m_pRecordTest->g_nSampleRate;
// 	long dwMaxOneScreen = m_dMaxTimeInOneSreen * m_pRecordTest->g_nSampleRate;
// 	long dwLength = dwEndIndex - dwBeginIndex;
// 	long nGap = 1;
// 
// 	//如果需要绘制的波形长度超过当前最大的绘制点数
// 	//则计算绘图的的等间隔点数
// 	while (TRUE)
// 	{
// 		if (dwLength > AnalyseWnd_MaxDrawlength)
// 		{
// 			nGap = dwLength / AnalyseWnd_MaxDrawlength;
// 			
// 			if (dwLength - nGap * AnalyseWnd_MaxDrawlength > 0)
// 			{
// 				nGap++;
// 			}
// 		}
// 
// 		//间隔太大，缩短绘图时间，重新计算，重新计算时，将最大时间缩小到原来的0.8倍
// 		if (nGap > MAX_DRAWGAP2)
// 		{
// 			dMaxTime *= 0.9;
// 			dwEndIndex = dMaxTime * m_pRecordTest->g_nSampleRate;
// 			dwLength = dwEndIndex - dwBeginIndex;
// 		}
// 		else
// 		{//计算出来的间隔满足要求，退出计算
// 			break;
// 		}
// 	}
// 
// 	if (nGap > 1)
// 	{//当间隔大于1时，计算dwEndIndex，避免访问越界
// 		dwEndIndex -= nGap;
// 		dwLength = dwEndIndex - dwBeginIndex;
// 	}
// 
// 	//////////////////////////////////////////////////////////////////////////
// 	//计算当前绘图的位置
// 	MrDraw::InitDrawBuffPos(&m_oDrawBufferPos, nGap, m_pRefBuffer->GetDataLength());
// 
// 	long dwBuffer1Length = m_oOscillographBufferPos.nBuf1EndPos - m_oOscillographBufferPos.nBuf1BeginPos ;
// 	long dwBuffer2Length = m_oOscillographBufferPos.nBuf2EndPos - m_oOscillographBufferPos.nBuf2BeginPos ;
// 
// 	if (m_oOscillographBufferPos.nBuf2BeginPos < 0)
// 	{
// 		dwBuffer2Length = -1;
// 	}
// 
// 	//根据m_oOscillographBufferPos的区段获取此次绘图的数据区段
// 	if (dwBuffer1Length >= dwBeginIndex)
// 	{//开始位置dwBeginIndex在第一段数据区中
// 		m_oDrawBufferPos.nBuf1BeginPos = m_oOscillographBufferPos.nBuf1BeginPos + dwBeginIndex;
// 
// 		if (dwBuffer1Length >= dwEndIndex)
// 		{//dwEndIndex在第一段数据区中
// 			m_oDrawBufferPos.nBuf1EndPos = m_oOscillographBufferPos.nBuf1BeginPos + dwEndIndex;
// 		}
// 		else////dwEndIndex在第二段数据区中
// 		{
// 			m_oDrawBufferPos.nBuf1EndPos = m_oOscillographBufferPos.nBuf1EndPos;
// 
// 			//第二段数据，从第二段起始位置开始，终止位置为总的数据长度减去第一段数据的长度
// 			m_oDrawBufferPos.nBuf2BeginPos = m_oOscillographBufferPos.nBuf2BeginPos;
// 			m_oDrawBufferPos.nBuf2EndPos   = dwLength - (m_oDrawBufferPos.nBuf1EndPos - m_oDrawBufferPos.nBuf1BeginPos);
// 		}
// 	}
// 	else
// 	{//开始位置dwBeginIndex在第二段数据区中
// 		m_oDrawBufferPos.nBuf1BeginPos = dwBeginIndex - dwBuffer1Length;
// 		m_oDrawBufferPos.nBuf1EndPos   = dwEndIndex - dwBuffer1Length;
// 	}
// 
// 
// 	DWORD dwB = ::GetTickCount();
// 
// 	long nUsePoints = dwLength / nGap;
// 	long nRemainPoints = dwLength % nGap;
// 
// 	if (nRemainPoints > 0)
// 	{
// 		nUsePoints++;
// 	}

	long nUsePoints = CalCurrentDataPosEx(dMax, dMin, m_pRecordTest, m_pRefBuffer
		, m_oDrawBufferPos, m_oOscillographBufferPos);

	CalXPos(nUsePoints);

	return TRUE;
}

long CViewAnalyse::CalCurrentDataPosEx(double dMax,double dMin
									   , CRecordTest *pRecordTest
									   , CMemBufferInterface *pRefBuffer
									   , MrDraw::DRAWMEMBUFFERPOS &oDrawBufferPos
									   , MrDraw::DRAWMEMBUFFERPOS &oOscillographBufferPos)
{
	if (pRefBuffer == NULL)
	{
		return 0;
	}
	
	//校验时间区段的范围
	if (m_dOscillographTimeLong <= dMax)
	{
		dMax = m_dOscillographTimeLong;
	}
	if (m_dOscillographTimeLong <= dMin)
	{
		dMin = m_dOscillographTimeLong;
	}

	double dMaxTime = dMax;
	double dMinTime = dMin;

	if (dMin >= dMax)
	{
		dMaxTime = dMin;
		dMinTime = dMax;
	}

	long dwBeginIndex = dMinTime * pRecordTest->g_nSampleRate;
	long dwEndIndex = dMaxTime * pRecordTest->g_nSampleRate;
	long dwMaxOneScreen = m_dMaxTimeInOneSreen * pRecordTest->g_nSampleRate;
	long dwLength = dwEndIndex - dwBeginIndex;
	long nGap = 1;

	//如果需要绘制的波形长度超过当前最大的绘制点数
	//则计算绘图的的等间隔点数
	while (TRUE)
	{
		if (dwLength > AnalyseWnd_MaxDrawlength)
		{
			nGap = dwLength / AnalyseWnd_MaxDrawlength;
			
			if (dwLength - nGap * AnalyseWnd_MaxDrawlength > 0)
			{
				nGap++;
			}
		}

		//间隔太大，缩短绘图时间，重新计算，重新计算时，将最大时间缩小到原来的0.8倍
		if (nGap > MAX_DRAWGAP2)
		{
			dMaxTime *= 0.9;
			dwEndIndex = dMaxTime * pRecordTest->g_nSampleRate;
			dwLength = dwEndIndex - dwBeginIndex;
		}
		else
		{//计算出来的间隔满足要求，退出计算
			break;
		}
	}

	if (nGap > 1)
	{//当间隔大于1时，计算dwEndIndex，避免访问越界
		dwEndIndex -= nGap;
		dwLength = dwEndIndex - dwBeginIndex;
	}

	//////////////////////////////////////////////////////////////////////////
	//计算当前绘图的位置
	MrDraw::InitDrawBuffPos(&oDrawBufferPos, nGap, pRefBuffer->GetDataLength());

	long dwBuffer1Length = oOscillographBufferPos.nBuf1EndPos - oOscillographBufferPos.nBuf1BeginPos ;
	long dwBuffer2Length = oOscillographBufferPos.nBuf2EndPos - oOscillographBufferPos.nBuf2BeginPos ;

	if (oOscillographBufferPos.nBuf2BeginPos < 0)
	{
		dwBuffer2Length = -1;
	}

	//根据oOscillographBufferPos的区段获取此次绘图的数据区段
	if (dwBuffer1Length >= dwBeginIndex)
	{//开始位置dwBeginIndex在第一段数据区中
		oDrawBufferPos.nBuf1BeginPos = oOscillographBufferPos.nBuf1BeginPos + dwBeginIndex;

		if (dwBuffer1Length >= dwEndIndex)
		{//dwEndIndex在第一段数据区中
			oDrawBufferPos.nBuf1EndPos = oOscillographBufferPos.nBuf1BeginPos + dwEndIndex;
		}
		else////dwEndIndex在第二段数据区中
		{
			oDrawBufferPos.nBuf1EndPos = oOscillographBufferPos.nBuf1EndPos;

			//第二段数据，从第二段起始位置开始，终止位置为总的数据长度减去第一段数据的长度
			oDrawBufferPos.nBuf2BeginPos = oOscillographBufferPos.nBuf2BeginPos;
			oDrawBufferPos.nBuf2EndPos   = dwLength - (oDrawBufferPos.nBuf1EndPos - oDrawBufferPos.nBuf1BeginPos);
		}
	}
	else
	{//开始位置dwBeginIndex在第二段数据区中
		oDrawBufferPos.nBuf1BeginPos = dwBeginIndex - dwBuffer1Length;
		oDrawBufferPos.nBuf1EndPos   = dwEndIndex - dwBuffer1Length;
	}


	DWORD dwB = ::GetTickCount();

	long nUsePoints = dwLength / nGap;
	long nRemainPoints = dwLength % nGap;

	if (nRemainPoints > 0)
	{
		nUsePoints++;
	}

	return nUsePoints;
}


void CViewAnalyse::SelectNextChannel()
{
// 	CDrawMr1200RecordBase::SelectNextChannel();
// 	DrawMain();
	m_pParentWnd->Invalidate(FALSE);
}

void CViewAnalyse::SelectPrevChannel()
{
// 	CDrawMr1200RecordBase::SelectPrevChannel();
// 	DrawMain();
	m_pParentWnd->Invalidate(FALSE);
}

void CViewAnalyse::MoveChanDown()
{
	CRecordTestDrawBase::MoveChanDown();

#ifdef _SHOW_PARA
	CalParaRect();
	CParaSortMngr oParaSortMngr(this,m_rcWaveDraw);
#endif

	m_pParentWnd->Invalidate(FALSE);
}

void CViewAnalyse::MoveChanUp()
{
	CRecordTestDrawBase::MoveChanUp();
#ifdef _SHOW_PARA
	CalParaRect();
	CParaSortMngr oParaSortMngr(this,m_rcWaveDraw);
#endif
	
	DrawAnalyse();
	m_pParentWnd->Invalidate(FALSE);
}

void CViewAnalyse::MoveLeft()
{
	double dMin, dMax;
	m_oTimeAxisDraw.GetMaxMinTime(dMax, dMin);
	
	double dReadTimeLong = 0;
	double dRecordDataReadBeginTime = 0;

	dReadTimeLong = m_pRefBuffer->GetDataLength() ;
	dReadTimeLong /= m_nSamRateForDraw;

	BOOL bMove = FALSE;
	double dRecordTimeLength = 0;

	//当前时间的最大值大于等于录波的最大时间GetMaxRecordTimeLong
	if (dMax >= dReadTimeLong)
	{//当前的时间大于一次性读取的时间
		if (dMax + dRecordDataReadBeginTime >= dRecordTimeLength)//g_theRecordApp.m_dRecordDataReadBeginTime
		{//当前最大时间+读取的起始时间 》 当前录波数据时间长度，移动
			bMove = TRUE;
		}
		else 
		{//波形数据翻页
			bMove = FALSE;
		}
	}
	else
	{
		bMove = TRUE;
	}

	if (bMove)
	{
		CRecordTestDrawBase::MoveLeft();
		
#ifdef _SHOW_PARA
		CalParaRect();
		CParaSortMngr oParaSortMngr(this,m_rcWaveDraw);
#endif
		
		m_oTimeAxisDraw.GetMaxMinTime(dMax, dMin);
		CalCurrentDataPos(dMax, dMin);
		DrawAnalyse();
		CalValues();
		FireTimeAxisChangedSysOptr();
	}
	else
	{//波形数据翻页，记录当前的录波数据时间
		double dMoveOnce = m_oTimeAxisDraw.m_oTimeAxis.GetHorCarryOenGap();
		m_dAxisMinTimeBack = dMin + dRecordDataReadBeginTime + dMoveOnce;//g_theRecordApp.m_dRecordDataReadBeginTime
		m_dAxisMaxTimeBack = dMax + dRecordDataReadBeginTime + dMoveOnce;//g_theRecordApp.m_dRecordDataReadBeginTime
	//	double dSavedRecordTimeLong = p->GetSavedRecordTimeLong();

		double dSavedRecordTimeLong = 0;
		
		if (m_dAxisMaxTimeBack > dSavedRecordTimeLong)
		{
			dMoveOnce = m_dAxisMaxTimeBack-dSavedRecordTimeLong;
			m_dAxisMinTimeBack -= dMoveOnce;
			m_dAxisMaxTimeBack -= dMoveOnce;
		}

		m_bRecordPageChanged = TRUE;
		ASSERT(FALSE);
		//g_theRecordApp.m_pMrOnlineThreadEx->NextPage(m_dAxisMinTimeBack, m_dAxisMaxTimeBack);

		//缓冲区改变，关联缓冲区，初始化参数数据的计算		//if (g_theRecordApp.IsRecordDataModeOnlineRecord())
	}
}

void CViewAnalyse::MoveRight()
{
	double dMin, dMax;
	m_oTimeAxisDraw.GetMaxMinTime(dMax, dMin);
	
	BOOL bMove = TRUE;
	double dRecordDataReadBeginTime = 0;

	if (dMin <= 0.00001)
	{
		if (dRecordDataReadBeginTime <= 0.0000001)//g_theRecordApp.m_dRecordDataReadBeginTime
		{
			bMove = TRUE;
		}
		else
		{
			bMove = FALSE;
		}
	}
	else
	{
		bMove = TRUE;
	}

	if (!bMove)
	{
		//波形数据翻页，记录当前的录波数据时间
		double dMoveOnce = m_oTimeAxisDraw.m_oTimeAxis.GetHorCarryOenGap();
		m_dAxisMinTimeBack = dMin + dRecordDataReadBeginTime - dMoveOnce;//g_theRecordApp.m_dRecordDataReadBeginTime
		m_dAxisMaxTimeBack = dMax + dRecordDataReadBeginTime - dMoveOnce;//g_theRecordApp.m_dRecordDataReadBeginTime
		double dSavedRecordTimeLong = 0;
		
		if (m_dAxisMinTimeBack < 0)
		{
			m_dAxisMaxTimeBack -= m_dAxisMinTimeBack;
			m_dAxisMinTimeBack = 0;
		}
		
		m_bRecordPageChanged = TRUE;

		ASSERT (FALSE);
		
// 		if (g_theRecordApp.m_pMrOnlineThreadEx != NULL)
// 		{
// 			g_theRecordApp.m_pMrOnlineThreadEx->PrevPage(m_dAxisMinTimeBack, m_dAxisMaxTimeBack);
// 		}
	}
	else
	{
		CRecordTestDrawBase::MoveRight();
		
#ifdef _SHOW_PARA
		CalParaRect();
		CParaSortMngr oParaSortMngr(this,m_rcWaveDraw);
#endif

		double dMin, dMax;
		m_oTimeAxisDraw.GetMaxMinTime(dMax, dMin);
		CalCurrentDataPos(dMax, dMin);
		DrawAnalyse();
		CalValues();
		FireTimeAxisChangedSysOptr();
	}
}

void CViewAnalyse::ArrowRight()
{
	CRecordTestDrawBase::ArrowRight();
}

void CViewAnalyse::ArrowLeft()
{
	CRecordTestDrawBase::ArrowLeft();
}

void CViewAnalyse::ArrowUp()
{
	CRecordTestDrawBase::ArrowUp();
}

void CViewAnalyse::ArrowDown()
{
	CRecordTestDrawBase::ArrowDown();
}

void CViewAnalyse::ZoomInTime(long nMode)
{
	CRecordTestDrawBase::ZoomInTime(nMode);

#ifdef _SHOW_PARA
	CalParaRect();
	CParaSortMngr oParaSortMngr(this,m_rcWaveDraw);
#endif

	DrawAnalyse();
	FireTimeAxisChangedSysOptr();
}

void CViewAnalyse::ZoomOutTime(long nMode)
{
	CRecordTestDrawBase::ZoomOutTime(nMode);

#ifdef _SHOW_PARA
	CalParaRect();
	CParaSortMngr oParaSortMngr(this,m_rcWaveDraw);
#endif

	FireTimeAxisChangedSysOptr();
	DrawAnalyse();
}

void CViewAnalyse::ZoomInChan()
{
	CRecordTestDrawBase::ZoomInChan();
	m_pParentWnd->Invalidate(FALSE);
}

void CViewAnalyse::ZoomOutChan()
{
	CRecordTestDrawBase::ZoomOutChan();
}

void CViewAnalyse::XOnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bInDrawAnalyseThread)
	{
		return;
	}
	
	CXRecordDrawBase::MouseMove(nFlags,point);

	//CStatic::OnMouseMove(nFlags, point);
}

void CViewAnalyse::XOnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bInDrawAnalyseThread)
	{
		return;
	}
	
	LONG nState = CXRecordDrawBase::LButtonDown(nFlags,point) ;

	if (nState == DRAW_NONE_OBJECT_SELECTED) 
	{
		if (m_rcWaveDraw.PtInRect(point))
		{
			m_bCanChanged = TRUE;
			g_ptOrigin = point;
		}
	}

	//CStatic::OnLButtonDown(nFlags, point);
}

void CViewAnalyse::XOnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bInDrawAnalyseThread)
	{
		return;
	}
	
	// TODO: Add your message handler code here and/or call default
	LONG nState = CXRecordDrawBase::LButtonUp(nFlags,point) ;

/*
	if (nState == DRAW_NONE_OBJECT_SELECTED && m_bCanChanged == TRUE) 
	{
		m_bCanChanged = FALSE;
		g_ptCurrent = point;
		long nMin = min(g_ptCurrent.x,g_ptOrigin.x);
		long nMax = max(g_ptCurrent.x,g_ptOrigin.x);
		long nMoved = nMax - nMin;
		double dMin = 0,dMax = 0;
		
		if (nMoved >= MIN_PELS) 
		{
			m_oTimeAxisDraw.DevicePointToLogicPoint(nMin,&dMin);
			m_oTimeAxisDraw.DevicePointToLogicPoint(nMax,&dMax);
			m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
			
#ifdef _SHOW_PARA
			CalParaRect();
			CParaSortMngr oParaSortMngr(this,m_rcWaveDraw);
#endif			
			DrawAnalyse();
		}
		else
		{		
#ifdef _SHOW_PARA
			CalParaRect();
			CParaSortMngr oParaSortMngr(this,m_rcWaveDraw);
			
#endif		
		}
	}
*/

	//CStatic::OnLButtonUp(nFlags, point);
}


void CViewAnalyse::XOnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CXRecordDrawBase::RButtonDown(nFlags,point) ;

	//CStatic::OnRButtonDown(nFlags, point);
}

void CViewAnalyse::XOnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CXRecordDrawBase::RButtonUp(nFlags,point) ;

	//CStatic::OnRButtonUp(nFlags, point);
}

BOOL CViewAnalyse::UICreate(CWnd *pParent)
{
/*
	if (m_nPostSysOptr > 0)
	{
		g_theRecordApp.RegisterSysOptr(m_nPostSysOptr);
	}

	//录波数据映射关系改变
	g_theRecordApp.RegisterSysOptr(MR1200_SYSOPTR_RECORDMAP_CHANGED);
	g_theRecordApp.RegisterSysOptrCall(MR1200_SYSOPTR_RECORDMAP_CHANGED, WM_ANALYSE_RECORD_VIEWMAP_CHANGED, this);

	//在线录波存储完成消息
	g_theRecordApp.RegisterSysOptr(MR1200_SYSOPTR_ONLINERECORDEX_WRITEFINISHED);
	g_theRecordApp.RegisterSysOptrCall(MR1200_SYSOPTR_ONLINERECORDEX_WRITEFINISHED, WM_ONLINERECORDEX_WRITEFINISHED, this);

	//在线录波数据拷贝过程消息
	g_theRecordApp.RegisterSysOptr(MR1200_SYSOPTR_ONLINE_RECORD_DATA_COPY);
	g_theRecordApp.RegisterSysOptrCall(MR1200_SYSOPTR_ONLINE_RECORD_DATA_COPY, WM_ONLINERECORD_DATA_COPY, this);

	//通道显示设置操作
	g_theRecordApp.RegisterSysOptrCall(MR1200_SYSOPTR_DRAWSET_CHANGED, WM_DRAWSET_CHANGED,this);		

	//COMTRADE文件保存
	g_theRecordApp.RegisterSysOptrCall(MR1200_SYSOPTR_SAVE_RECORDFILE, WM_SAVERECORDFILE, this);		
*/

	//时间光标移动
	//g_theRecordApp.RegisterSysOptr(MR1200_SYSOPTR_ANALYSE_TIMERCURRSOR_MOVE);
	//已经在MR1200BaseApp.cpp(165)注册
	
	CreateMemDC();

	DrawCalThreadState();

/*
	ASSERT (g_theRecordApp.m_pMrOnlineThreadEx != NULL);

	if (g_theRecordApp.m_pMrOnlineThreadEx != NULL)
	{
		if (g_theRecordApp.IsRecordDataModeOscillograph())
		{
			InitByBorder();
			DrawMain();
			DrawRecordDataBufferState(0,0);

			m_bHasUICreated = TRUE;

			//如果录波数据处理完毕，则
			if (g_theRecordApp.m_pMrOnlineThreadEx->IsWriteRecordDataFinished())
			{
				m_pDrawAnalyseThread = AfxBeginThread(DrawAnalyseThread, this);
			}
		}
		else if (g_theRecordApp.IsRecordDataModeOnlineRecord())
		{
			g_theRecordApp.InitCopyRecordDataFromOnlineToAnalyse();
		}
		else if (g_theRecordApp.IsRecordDataModeComtrade())
		{
			AfxBeginThread(ReadComtradeFileThread, this);
		}
		else
		{
		}
	}
*/
	if (g_theRecordApp.IsRecordDataModeOscillograph())
	{
// 		InitByBorder();
// 		DrawMain();
// 		DrawRecordDataBufferState(0,0);
// 
// 		m_bHasUICreated = TRUE;
// 
// 		//如果录波数据处理完毕，则
// 		if (g_theRecordApp.m_pMrOnlineThreadEx->IsWriteRecordDataFinished())
// 		{
// 			m_pDrawAnalyseThread = AfxBeginThread(DrawAnalyseThread, this);
// 		}
	}
	else if (g_theRecordApp.IsRecordDataModeOnlineRecord())
	{
// 		g_theRecordApp.InitCopyRecordDataFromOnlineToAnalyse();
	}
	else if (g_theRecordApp.IsRecordDataModeComtrade())
	{
		//AfxBeginThread(ReadComtradeFileThread, this);
	}
	else
	{
	}

	//保存监视状态
//	SaveLastSpyState();
	g_wBufferState = 1;

	return TRUE;
}

void CViewAnalyse::DrawWait()
{

}

void CViewAnalyse::DrawCalThreadState()
{
/*
	if (g_theRecordApp.m_pRecordTestCalThread != NULL)
	{
		if (!g_theRecordApp.m_pRecordTestCalThread->m_bIsInCalState)
		{
			return;
		}
	}

	CDC *pDC = m_oDrawMemDC.GetDC();
	CRect rc(0, 0, m_nWidth, m_nHeight);
	
	LOGFONT lf = InitLogFont();
	lf.lfHeight = 16;
	lf.lfWeight = 600;
	
	CRect rcClient;
	GetClientRect(&rcClient);
	long nHeight = rcClient.Height();
	long nPos = nHeight / 2 - CALTHREAD_DRAW_POS;
	
	rcClient.top = nPos;
	rcClient.bottom = nPos + DRAW_HEIGHT;

	CString str;
	str = "处理参数计算.............";

	
	long nMode = pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(str, rcClient, DT_CENTER | DT_VCENTER);
	pDC->SetBkMode(nMode);
*/
}

void CViewAnalyse::InitDrawPoints()
{
	if (m_pPointBuffer == NULL)
	{
		m_pPointBuffer = new CMemBuffer_CPoint();
		m_pPointBuffer->SetBufferLength(AnalyseWnd_MaxDrawlength);
		CPoint *pPoint = m_pPointBuffer->GetBuffer();
	}
}

long CViewAnalyse::GetAnalogVariableCount()
{
	POS pos = m_oVariableMngr.GetHeadPosition();
	CDrawVariable* pDrawVariable = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pDrawVariable = (CDrawVariable*)m_oVariableMngr.GetNext(pos);

		if (pDrawVariable->GetClassID() == CMTRDCLASSID_ANALOGVARIABLE
			||  pDrawVariable->GetClassID() == CMTRDCLASSID_CMPANALOGVARIABLE			)
		{
			nCount++;
		}
	}

	return nCount;
}

//
void CViewAnalyse::InitDrawVariablesByRecordTest()
{
	ClearBuffer();

	if (m_pRecordTest == NULL)
	{
		return;
	}

	int nAnalogChanAmount = 0;
	int nBinaryChanAmount = 0;
	CreateDrawVariableByRecordTest(nAnalogChanAmount, nBinaryChanAmount);
	
// 	if (m_ppRecordBuffer[0] != NULL)
// 	{
// 		m_pRefBuffer = m_ppRecordBuffer[0];			
// 	}
	m_pRefBuffer = GetDefaultRefBuffer();	
	
	//初始化第一个为选中通道
	if (nAnalogChanAmount > 0 || nBinaryChanAmount > 0)
	{
		POS  pos = m_oVariableMngr.GetHeadPosition();
		
		m_pCurrDrawVariable = (CDrawVariable*)m_oVariableMngr.GetAt(pos);
		m_pCurrDrawVariable->SetSelect(TRUE);
	}
	
// 	//初始化当前绘图的变量，包括设置当前选中变量
// 	InitCurrDrawPageVariables();
// 	
// 	//根据录波数据缓冲区的数据长度，计算获得当前显示的波形的长度
// 	//同时设置时间坐标的范围
// 	InitTimeAxis();
// 	
// 	CalXPosByTimeAxis();
// 	
// 	CalParaRect();
}


//初始化当前绘制页面的绘图对象
void CViewAnalyse::InitCurrDrawPageVariables()
{
	RemoveAll();
	
	///////////////////////////
	POS pos = m_oVariableMngr.GetHeadPosition();
	
	while (pos != NULL)
	{
		CDrawVariable* pDrawVariable = (CDrawVariable*)m_oVariableMngr.GetNext(pos);

		if (pDrawVariable->GetUse() == 1 && pDrawVariable->GetShow() == 1)
		{
			AddTail(pDrawVariable);
		}
		else
		{
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
	
	if (!bHas && m_pCurrDrawVariable != NULL) 
	{
		pos = GetHeadPosition();
		m_pCurrDrawVariable->SetSelect(FALSE);
		if (pos == NULL)
		{
			m_pCurrDrawVariable->SetSelect(FALSE);
			m_pCurrDrawVariable = NULL;
		} 
		else
		{
			m_pCurrDrawVariable = (CDrawVariable*)GetAt(pos);
			if (m_pCurrDrawVariable != NULL)
			{
				m_pCurrDrawVariable->SetSelect(TRUE);
				AdjustChanState();
			}
		}
	}
	
	//根据改变过的绘图变量的位置，重新排序
	ReCompositor();
}

//根据录波数据缓冲区的数据长度，计算获得当前显示的波形的长度
//同时设置时间坐标的范围
void CViewAnalyse::InitTimeAxis()
{
	m_nSamRateForDraw = m_pRecordTest->g_nSampleRate;

	if (m_pRefBuffer == NULL)
	{
		return ;
	}

	double dMax = 0;
	double dMin = 0;
	long nDataLen = m_pRefBuffer->GetDataLength();
	dMax = nDataLen;
	dMax /=  m_nSamRateForDraw;
	
	if (m_dMaxTimeInOneSreen > dMax) 
	{
		m_dMaxTimeInOneSreen = dMax;
	}

	m_dMaxTimeInOneSreen = dMax;
	SetRecordDataTimeLength(dMax);
	m_dMinTimeInOneSreen = (double)g_dwOscillographMinTime / 1000;
	m_oTimeAxisDraw.SetOldMaxMinTime(m_dRecordDataTimeLength,0);

	if (m_dMaxTimeInOneSreen > dMax) 
	{
		m_oTimeAxisDraw.SetMaxMinTime(dMax,0);
	}
	else
	{
		m_oTimeAxisDraw.SetMaxMinTime(m_dMaxTimeInOneSreen,0);
	}

	if (IsUseMapFileBuffer())
	{
		m_oTimeAxisDraw.m_oTimeAxis.SetScaleOffset(g_theRecordApp.m_dRecordDataReadBeginTime);

		if (m_bRecordPageChanged)
		{
			double d1 = m_dAxisMinTimeBack - g_theRecordApp.m_dRecordDataReadBeginTime;
			double d2 = m_dAxisMaxTimeBack - g_theRecordApp.m_dRecordDataReadBeginTime;
			m_bRecordPageChanged = FALSE;
			double dCoefLeft = d1 / dMax;
			double dCoefRight = d2 / dMax;
			m_oTimeAxisDraw.SetAxisRange(dCoefLeft, dCoefRight);
			m_oTimeAxisDraw.SetMaxMinTime(d2, d1);
		}
	}
}


long CViewAnalyse::InitAttributes()
{
// 	m_pCursorLeft	    = FindByMsgImpID(g_pszKeyMoveCursorLeft);
// 	m_pCursorRight	    = FindByMsgImpID(g_pszKeyMoveCursorRight);
// 	m_pSelectNextCursor = FindByMsgImpID(g_pszKeySelectPrevTimeCursor);
// 	m_pSelectPrevCursor	= FindByMsgImpID(g_pszKeySelectNextTimeCursor);
// 	m_pSelChanDown	    = FindByMsgImpID(g_pszKeySelChDown);
// 	m_pSelChanUp		= FindByMsgImpID(g_pszKeySelChUp);
// 	m_pMoveChanDown		= FindByMsgImpID(g_pszKeyMoveChanDown);
// 	m_pMoveChanUp		= FindByMsgImpID(g_pszKeyMoveChanUp);
// 	m_pMoveLeft			= FindByMsgImpID(g_pszKeyMoveChanLeft);
// 	m_pMoveRight		= FindByMsgImpID(g_pszKeyMoveChanRight);
// 	m_pTimeZoomIn		= FindByMsgImpID(g_pszKeyZoomInTime);
// 	m_pTimeZoomOut		= FindByMsgImpID(g_pszKeyZoomOutTime);
// 	m_pChanZoomIn		= FindByMsgImpID(g_pszKeyZoomInChan);
// 	m_pChanZoomOut		= FindByMsgImpID(g_pszKeyZoomOutChan);
// 	m_pNextPage			= FindByMsgImpID(g_pszKeyNextPage);
// 	m_pPrevPage			= FindByMsgImpID(g_pszKeyPrevPage);
// 	m_pLockCursor		= FindByMsgImpID(g_pszKeyLockCursor);		
// 	m_pReFresh			= FindByMsgImpID(g_pszKeyReFresh);
// 
// 	m_pTimeCursorMove	= m_pEvents->FindByMsgImpID(g_pszKeyCursorMove);
// 	m_pPageChanged		= m_pEvents->FindByMsgImpID(g_pszKeyPageChanged);

	return 0;
}

long CViewAnalyse::OnSystemMessage(UINT nSysMsgID, long &nImpCount, long &nRunCount)
{
/*
	if (m_bInDrawAnalyseThread)
	{
		return 0;
	}

	if (!IsEnable())
	{
		return 0;
	}

	if (m_pSysMsgMaps != NULL)
	{
		CMessageImp *pSysMsgImp = FindBySysMsgID(nSysMsgID);
		
		if (pSysMsgImp != NULL)
		{
			if (pSysMsgImp == m_pCursorLeft) 
			{
				ArrowLeft();
			}
			else if(pSysMsgImp == m_pCursorRight)
			{
				ArrowRight();
			}
			else if (pSysMsgImp == m_pSelectPrevCursor)
			{
				ArrowUp();
			}
			else if (pSysMsgImp == m_pSelectNextCursor)
			{
				ArrowDown();
			}
			else if (pSysMsgImp == m_pSelChanDown) 
			{
				SelectNextChannel();
			}
			else if (pSysMsgImp == m_pSelChanUp)
			{
				SelectPrevChannel();
			}
			else if (pSysMsgImp == m_pMoveChanDown)
			{
				MoveChanDown();
			}
			else if (pSysMsgImp == m_pMoveChanUp)
			{
				MoveChanUp();
			}
			else if (pSysMsgImp == m_pMoveLeft)
			{
				MoveLeft();
			}
			else if (pSysMsgImp == m_pMoveRight)
			{
				MoveRight();
			}
			else if (pSysMsgImp == m_pChanZoomIn)
			{
				ZoomInChan();
			}
			else if (pSysMsgImp == m_pChanZoomOut)
			{	
				ZoomOutChan();
			}
			else if (pSysMsgImp == m_pTimeZoomIn)
			{
				ZoomInTime(2);
			}
			else if (pSysMsgImp == m_pTimeZoomOut)
			{
				ZoomOutTime(2);
			}
			else
			{
			}
		}
	}	
	*/
	return 0;
}

CBaseObject* CViewAnalyse::CreateNewAttributeChild(long nClassID)
{
	return NULL;
}

CBaseObject* CViewAnalyse::CreateNewAttributeChild(LPCTSTR pszClassID)
{
	CBaseObject *pNew = NULL;

// 	if (_stricmp(pszClassID, g_pszKeyFontTitle) == 0)
// 	{
// 		//暂时用不到
// 	}
// 	else if (_stricmp(pszClassID, CUIBaseAxises::g_pszKeyAxis) == 0)
// 	{
// 		//暂时用不到
// 	}
// 	else
// 	{
// 		pNew = CUIWindowBase::CreateNewAttributeChild(pszClassID);
// 	}
	
	return pNew;
}

// long CViewAnalyse::SerializeOwn(CBinarySerializeBuffer &oBinaryBuffer)
// {
// 	return 0;
// }

void CViewAnalyse::CalParaRect()
{
#ifdef _SHOW_PARA
	long nPos = m_pTimeCursorDraw->GetCurrentCursorPosition();
	POS  pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		CDrawVariable* pVariable = (CDrawVariable*)GetNext(pos);
		
		if (pVariable->GetClassID() == CMTRDCLASSID_ANALOGVARIABLE
			|| pVariable->GetClassID() == CMTRDCLASSID_CMPANALOGVARIABLE) 
		{
			CDrawAnalogVariable* pAnalog = (CDrawAnalogVariable*)pVariable;

			//2022-9-1  lijunqing
			pAnalog->GetTimeCursorPos(nPos, m_pRecordTest->MR1200_DFT_CAL_LEN);
			//pAnalog->GetTimeCursorPos(nPos, RT_FREQUENCY_CAL_LEN + RT_FREQUENCY_CAL_LEN_ADD*2);
		}
	}
#endif
}

void CViewAnalyse::DrawPara(CDC* pDC)
{
#ifdef _SHOW_PARA
	POS  pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		CDrawVariable* pVariable = (CDrawVariable*)GetNext(pos);

		if (pVariable->GetShow() == 0)
		{
			continue;
		}
		
		if (pVariable->GetClassID() == CMTRDCLASSID_ANALOGVARIABLE
			|| pVariable->GetClassID() == CMTRDCLASSID_CMPANALOGVARIABLE) 
		{
			CDrawAnalogVariable* pAnalog = (CDrawAnalogVariable*)pVariable;
			pAnalog->m_oParas.Draw(pDC);
		}
	}
#endif
}

void CViewAnalyse::CalXPosByTimeAxis(double dMax, double dMin)
{
	if (dMax < 0 && dMin < 0)
	{
		double dMax2,dMin2;
		m_oTimeAxisDraw.GetMaxMinTime(dMax2,dMin2);
		CalCurrentDataPos(dMax2,dMin2);
	}
	else
	{
	CalCurrentDataPos(dMax,dMin);
	}
}

void CViewAnalyse::XOnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (m_bInDrawAnalyseThread)
	{
		return;
	}
	
// 	if (m_pTimeCursorDraw != NULL)
// 	{
// 		m_pTimeCursorDraw->SetCurrentCursor(USETIMECURSORA);
// 	}

	LONG nState = CXRecordDrawBase::LButtonDbClick(nFlags,point) ;
}

void CViewAnalyse::XOnRButtonDblClk(UINT nFlags, CPoint point) 
{
	if (m_bInDrawAnalyseThread)
	{
		return;
	}
	
	if (m_pTimeCursorDraw != NULL)
	{
		m_pTimeCursorDraw->SetCurrentCursor(USETIMECURSORB);
	}

	//CStatic::XOnRButtonDblClk(nFlags, point);
}

// void CViewAnalyse::SaveLastSpyState()
// {
// 	
// 	
// 	if (m_pRecordTest == NULL)
// 	{
// 		return;
// 	}
// 	
// 	CRtVariables *pVariables = m_pRecordTest->m_pVariables;
// 	
// 	if (pVariables == NULL)
// 	{
// 		return;
// 	}
// 
// 	long nVarIndex = 0;
// 	long nAttrIndex = 0;
// 	POS  posAttr = NULL;
// 
// 	POS  pos = pVariables->GetHeadPosition();
// 
// 	while(pos != NULL)
// 	{
// 		CRtVariable *pVariable = (CRtVariable*)pVariables->GetNext(pos);
// 		if (pVariable != NULL)
// 		{
// 			UINT nClassID = pVariable->GetClassID();
// 			if ((nClassID == RTCLASSID_BINARYVARIABLE) || (nClassID == RTCLASSID_SINGLEVARIABLE))
// 			{
// 		//		m_nVariableSpyState[nVarIndex] = pVariable->m_nSpyState;
// 				CRtDataAttributes* pAttrs = pVariable->m_pDataAttrs;
// 				
// 				posAttr = pAttrs->GetHeadPosition();
// 				nAttrIndex = 0;
// 				
// 				while(posAttr != NULL)
// 				{
// 					CRtDataAttribute* pAttr = (CRtDataAttribute*)pAttrs->GetNext(posAttr);
// 					if (pAttr != NULL)
// 					{
// 						m_nAttrSpyState[nVarIndex][nAttrIndex] = pAttr->GetSpyState();
// 						CString str;
// 						str.Format("");
// 						nAttrIndex++;
// 					}
// 				}
// 
// 				nVarIndex++;
// 			}
// 		}
// 	}
// 
// 	//重新关联计算的相关信息
// 	g_wBufferState = 1;
// 	//pVariables->InitDataAttributeCalFunc();
// }

// void CViewAnalyse::ReSetSpyState()
// {
// 	
// 	
// 	if (m_pRecordTest == NULL)
// 	{
// 		return;
// 	}
// 	
// 	CRtVariables *pVariables = m_pRecordTest->m_pVariables;
// 	
// 	if (pVariables == NULL)
// 	{
// 		return;
// 	}
// 	
// 	long nVarIndex = 0;
// 	long nAttrIndex = 0;
// 	POS  posAttr = NULL;
// 	POS  pos = pVariables->GetHeadPosition();
// 	
// 	while(pos != NULL)
// 	{
// 		CRtVariable *pVariable = (CRtVariable*)pVariables->GetNext(pos);
// 		UINT nClassID = pVariable->GetClassID();
// 
// 		if ((nClassID == RTCLASSID_BINARYVARIABLE) || (nClassID == RTCLASSID_SINGLEVARIABLE))
// 		{
// 	//		pVariable->m_nSpyState = m_nVariableSpyState[nVarIndex];
// 			
// 			CRtDataAttributes* pAttrs = pVariable->m_pDataAttrs;
// 			posAttr = pAttrs->GetHeadPosition();
// 			nAttrIndex = 0;
// 			
// 			while(posAttr != NULL)
// 			{
// 				CRtDataAttribute* pAttr = (CRtDataAttribute*)pAttrs->GetNext(posAttr);
// 				pAttr->SetSpyState(m_nAttrSpyState[nVarIndex][nAttrIndex]);
// // 				CString str;
// // 				str.Format("%s %d",pAttr->m_strID,pAttr->GetSpyState());
// // 				AfxMessageBox(str);
// 				nAttrIndex++;
// 			}
// 
// 			nVarIndex++;
// 		}
// 	}
// 
// 	//重新关联计算的相关信息
// 	g_wBufferState = 0;
// 	//pVariables->InitDataAttributeCalFunc();
// 
// 	InitBackUpSpyState();
// }

// void CViewAnalyse::InitBackUpSpyState()
// {
// 	memset(m_nAttrSpyState, 0, MAX_MR1200_CHANNELS*MAX_MR1200_VARIABLE_ATTR_BUFFERS*sizeof(long));
// 	memset(m_nVariableSpyState, 0, MAX_MR1200_CHANNELS*sizeof(long));
// }

//根据时间光标的位置获取参数计算的起始位置

void CViewAnalyse::WaveAnalyse()
{
	if (m_bWaveAnalyse)
	{
		return;
	}

	m_bWaveAnalyse = TRUE;
	RECORD_CAL_LEN_PARA oCalLenPara;
	m_pRecordTest->Get_RECORD_CAL_LEN_PARA(&oCalLenPara);
	long nPos = 0;
	CRtVariables *pRtVariables= m_pRecordTest->m_pVariables;
	
#ifdef _CAL_USE_REF_VARIABLE_
	long nPoints = pRtVariables->GetRefBufDataLen();
#else
	long nPoints = -1;  //2020-12-19  lijunqing 10000 ==>> -1
#endif
	long nCmpIndex = 0;
	long nRecordTestIndex = 0;
	DWORD dwSampleRate = m_pRecordTest->g_nSampleRate;
	BOOL bAddDataToBuffer = g_bAddDataToBuffer;
	g_bAddDataToBuffer = TRUE;

	CTickCount32 oTick;
	pRtVariables->CalValuesFnom_Quick(&oCalLenPara, nPos, dwSampleRate, FALSE, FALSE);
	DWORD dwAttrCalUsePoints = rcd_CalCyclePoints(dwSampleRate, 50);//, g_bCarry_For_AttrCalUsePoints);
	pRtVariables->CalFaultValues(0, nPoints, dwAttrCalUsePoints);

#ifdef DEBUG
	//m_pRecordTest->CalValues_PeakVellay(0, nPoints-1);
#endif

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Cal Values use %d ms"), oTick.GetTickCountLong());

	if (g_bWriteAttrFileWhenWaveAnalyse)
	{
		WriteAttrFile(SingleVariableAttrID_EffecValue);
		WriteAttrFile(SingleVariableAttrID_FundValue);
		WriteAttrFile(SingleVariableAttrID_DeltaFundValue);
		WriteAttrFile(SingleVariableAttrID_FundPhase);
	}

	g_bAddDataToBuffer = bAddDataToBuffer;

	//更新图形
	AddAttrsDraw();

	DrawAnalyse();
}

void CViewAnalyse::WriteAttrFile(long nAttrID)
{
#ifndef _PSX_IDE_QT_
	CRtVariables *pRtVariables= m_pRecordTest->m_pVariables;
	CString strFile;
	strFile = _P_GetDBPath();
	strFile.AppendFormat(_T("Cal_%d.txt"), nAttrID);
	CFile oFile;
	BOOL b = oFile.Open(strFile, CFile::modeCreate | CFile::modeWrite);

	if (b)
	{
		POS pos = pRtVariables->GetHeadPosition();
		CRtVariable *pVariable = NULL;

		while (pos != NULL)
		{
			pVariable = (CRtVariable *)pRtVariables->GetNext(pos);
			CRtDataAttribute *pAttr = (CRtDataAttribute*)pVariable->m_pDataAttrs->GetAt(nAttrID);

			if (pAttr == NULL)
			{
				continue;
			}

			if (pAttr->GetUse() == 0)
			{
				continue;
			}

			float *pfBuff = pAttr->m_pAttrBuffer->GetBuffer_float();
			long nLen = pAttr->m_pAttrBuffer->GetBufferLength();
			long nIndex = 0;
			CString strText;

			strText.Format(_T("%s:%s\r\n"), pVariable->m_strName, pAttr->m_strID);
			oFile.Write(strText, strText.GetLength());

			for (nIndex=0; nIndex<nLen; nIndex++)
			{
				strText.Format(_T("%f\r\n"), *pfBuff);
				oFile.Write(strText, strText.GetLength());
				pfBuff++;
			}
			strText = _T("\r\n\r\n");
			oFile.Write(strText, strText.GetLength());
		}

		oFile.Close();
	}
#endif
}

void CViewAnalyse::CalValues()
{
	BOOL bAddDataToBuffer = g_bAddDataToBuffer;
	g_bAddDataToBuffer = FALSE;

	long nPos = m_pTimeCursorDraw->GetCurrentCursorPosition();
	CalValues(nPos);

	g_bAddDataToBuffer = bAddDataToBuffer;
}


BOOL CViewAnalyse::CalValues(long nTimeCursorPos)
{
//	return FALSE;
	CRecordTest* pRecordTest = m_pRecordTest;

	if (pRecordTest == NULL)
	{
		return FALSE;
	}

	CRtVariables* pVariables = pRecordTest->m_pVariables;
	
	if (pVariables == NULL)
	{
		return FALSE;
	}

	if (m_pRefBuffer == NULL)
	{
		return FALSE;
	}

	long nCalBegin = GetCalAttrBeginPos(nTimeCursorPos);

	if (nCalBegin < 0)
	{
		return FALSE;
	}

	RECORD_CAL_LEN_PARA oCalLenPara;
	m_pRecordTest->Get_RECORD_CAL_LEN_PARA(&oCalLenPara);
	BOOL bRet = pVariables->CalValues(&oCalLenPara, nCalBegin, m_pRecordTest->g_nSampleRate, FALSE, TRUE);

	if (bRet)
	{
		FireTimeAxisChangedSysOptr();
	}

	return bRet;
}

void CViewAnalyse::FireTimeAxisChangedSysOptr()
{
// 	if (!::IsWindow(m_hWnd))
// 	{
// 		return;
// 	}
// 	
// 	CMrOnlineRecordEx *p = CMrOnlineRecordEx::g_pMrOnlineRecordEx;
// 	
// 	if (p != NULL)
// 	{
// 		CDrawMr1200RecordBase::FireTimeAxisChangedSysOptr(g_theRecordApp.m_dRecordDataReadBeginTime);
// 	}
// 	else
// 	{
// 		CDrawMr1200RecordBase::FireTimeAxisChangedSysOptr(0);
// 	}
}

void CViewAnalyse::DrawAnalyse()
{
	if (m_pParentWnd == NULL)
	{
		return;
	}

	//绘制图形
 	DrawMain(1, CPoint(0, 0), 0xFFFFFFFF);
	m_pParentWnd->Invalidate(FALSE);
}

void CViewAnalyse::OnDraw(CDC *pDC)
{
	if (m_oDrawMemDC->GetBitmap() != NULL)
	{
		m_oDrawMemDC->Draw(pDC);
	}

	CXRecordDrawBase::DrawSubject(pDC, 1, CPoint(0, 0));

	DrawPara(pDC);
}

void CViewAnalyse::DrawInWritingState()
{
// 	CDC *pDC = m_oDrawMemDC.GetDC();
// 	CRect rc(0, 0, m_nWidth, m_nHeight);
// 	
// 	LOGFONT lf = InitLogFont();
// 	lf.lfHeight = 16;
// 	lf.lfWeight = 600;
// 	
// 	CRect rcClient;
// 	GetClientRect(&rcClient);
// 	long nHeight = rcClient.Height();
// 	long nPos = nHeight / 2 - ONLINE_WITE_DRAW_POS;
// 	
// 	rcClient.top = nPos;
// 	rcClient.bottom = nPos + DRAW_HEIGHT;
// 	
// 	CString str;
// 	str = "处理录波数据.............";
// 	
// 	long nMode = pDC->SetBkMode(TRANSPARENT);
// 	pDC->DrawText(str, rcClient, DT_CENTER | DT_VCENTER);
// 	pDC->SetBkMode(nMode);
}

void CViewAnalyse::DrawRecordDataBufferState(long nTotal, long nIndex)
{
	CDC *pDC = m_oDrawMemDC.GetDC();
	CRect rc(0, 0, m_nWidth, m_nHeight);
	
	LOGFONT lf = InitLogFont();
	lf.lfHeight = 16;
	lf.lfWeight = 400;
	
	CRect rcClient;
	m_pParentWnd->GetClientRect(&rcClient);
	long nHeight = rcClient.Height();
	long nPos = nHeight / 2 - ONLINE_WITE_DRAW_POS;
	
	rcClient.top = nPos;
	rcClient.bottom = nPos + DRAW_HEIGHT + DRAW_HEIGHT;
	
	CString str;
	if (nTotal <= 0)
	{
		str = _T("AnalyseCopyOnlineRecord2");//GetLanguageStringByID(gs_strLanguage_msAnalyseCopyOnlineRecord2);
	}
	else
	{
		double dCoef = nIndex;
		dCoef /= nTotal;
		CString strFormat = _T("AnalyseCopyOnlineRecord");//GetLanguageStringByID(gs_strLanguage_msAnalyseCopyOnlineRecord);
		str.Format(strFormat, dCoef*100);
	}

	rcClient.left = 80;
	rcClient.right -= 40;
	pDC->Rectangle(rcClient);
	COLORREF cr = pDC->SetTextColor(RGB(255, 0, 0));
	long nMode = pDC->SetBkMode(TRANSPARENT);
	rcClient.top += DRAW_HEIGHT/2;
	rcClient.bottom -= DRAW_HEIGHT/2;
	pDC->DrawText(str, rcClient, DT_CENTER | DT_VCENTER);
	pDC->SetBkMode(nMode);
	pDC->SetTextColor(cr);
	
	m_pParentWnd->Invalidate(FALSE);
}

void CViewAnalyse::DrawSaveComtradeFileState(long nTotal, long nIndex)
{
// 	CDC *pDC = m_oDrawMemDC.GetDC();
// 	CRect rc(0, 0, m_nWidth, m_nHeight);
// 	
// 	CRect rcClient;
// 	GetClientRect(&rcClient);
// 	long nHeight = rcClient.Height();
// 	long nPos = nHeight / 2 - ONLINE_WITE_DRAW_POS;
// 	
// 	rcClient.top = nPos;
// 	rcClient.bottom = nPos + DRAW_HEIGHT + DRAW_HEIGHT;
// 	rcClient.left = 80;
// 	rcClient.right -= 40;
// 
// 	CDrawMr1200RecordBase::DrawSaveComtradeFileState(pDC, rcClient, nTotal, nIndex);
// 
// 	
}

UINT  CViewAnalyse::ReadComtradeFileThread(LPVOID pParam)
{
	CViewAnalyse *pWnd = (CViewAnalyse*)pParam;
	
	pWnd->m_bInDrawAnalyseThread = TRUE;
	g_theRecordApp.SetCanFireSysMessage(FALSE);
	g_theRecordApp.ReadComtradeFile();
	g_theRecordApp.SetCanFireSysMessage(TRUE);
	pWnd->m_bInDrawAnalyseThread = FALSE;
	return 0;
}

UINT CViewAnalyse::ReadOnlineDataThread(LPVOID pParam)
{
// 	CViewAnalyse *pWnd = (CViewAnalyse*)pParam;
// 	
// 	pWnd->m_bInDrawAnalyseThread = TRUE;
// 	g_theRecordApp.SetCanFireSysMessage(FALSE);
// 	g_theRecordApp.ReadOnlineRecordData();
// 	g_theRecordApp.SetCanFireSysMessage(TRUE);
// 	pWnd->m_bInDrawAnalyseThread = FALSE;
	return 0;
}

UINT  CViewAnalyse::DrawAnalyseThread(LPVOID pParam)
{
/*
	
	g_theRecordApp.m_pUIWndThread->m_nCanDeletePageRef++;

	static long g_nDrawAnalyseThreadRef;
	if (g_nDrawAnalyseThreadRef > 0)
	{
		g_theRecordApp.m_pUIWndThread->m_nCanDeletePageRef--;
		return 0;
	}

	g_nDrawAnalyseThreadRef++;
	CViewAnalyse *pWnd = (CViewAnalyse*)pParam;
	
	pWnd->m_bInDrawAnalyseThread = TRUE;
	
	//等待在线录波线程存储完毕全部的数据
	if (pWnd->IsUseMapFileBuffer())
	{
		ASSERT (g_theRecordApp.m_pMrOnlineThreadEx != NULL);
		
		if (g_theRecordApp.IsRecordDataModeOnlineRecord())
		{
			g_theRecordApp.InitCopyRecordDataFromOnlineToAnalyse();
		}
		else
		{
			//初始映射数据
			pWnd->MapRecorBuffer(0, SM_ONLINE_EX_DATAAREA_PAGE_SIZE);
			pWnd->InitViewAnalyse();
		}		
	}
	
	pWnd->m_bInDrawAnalyseThread = FALSE;

	g_nDrawAnalyseThreadRef--;
	pWnd->m_pDrawAnalyseThread = NULL;

	g_theRecordApp.m_pUIWndThread->m_nCanDeletePageRef--;
*/

	return 0;
}

void CViewAnalyse::InitViewAnalyse()
{
	if (m_pRecordTest != NULL)
	{
		InitFromRecordTest();
		//CalValues();
	}
	else
	{
	}
	
	m_pTimeCursorDraw->SetMoveCursor(g_hMoveCursor);
	//DrawAnalyse();
	CalValues();
	m_pParentWnd->Invalidate(FALSE);
}

//创建MemDC，设置绘图区域
void CViewAnalyse::InitByBorder()
{
	CRect rc;
	m_pParentWnd->GetClientRect(&rc);
	
	CDC *pDC = m_pParentWnd->GetDC();
	CRecordTestDrawBase::SetBorder(pDC, rc);
	m_pParentWnd->ReleaseDC(pDC);

	if (m_pTimeCursorDraw)
	{
		m_pTimeCursorDraw->SetBorder(m_rcWaveDraw);
	}
}

void CViewAnalyse::AdjustAllDrawObjectsPos()
{
	InitCurrDrawPageVariables();
}

void CViewAnalyse::SetAllObjParentWnd()
{
	CRecordTestDrawBase::SetParentWnd(m_pParentWnd);
	
	if (m_pRangeStateAxis != NULL)
	{
		m_pRangeStateAxis->SetParentWnd(m_pParentWnd);
	}
	
	if (m_pTimeCursorDraw != NULL)
	{
		m_pTimeCursorDraw->SetParentWnd(m_pParentWnd);
	}
	
	m_oTimeAxisDraw.SetParentWnd(m_pParentWnd);
	
	POS  pos = m_oVariableMngr.GetHeadPosition();
	
	while(pos != NULL)
	{
		CDrawVariable* pDrawVar = (CDrawVariable*)m_oVariableMngr.GetNext(pos);
		pDrawVar->SetParentWnd(m_pParentWnd);
	}
}


void CViewAnalyse::OnSizeEx(UINT nType, int cx, int cy) 
{
	if (m_pParentWnd == NULL)
	{
		return;
	}

	if (cy > 400)
	{
		m_dHeightRateOnSize = m_nHeight;
		m_dHeightRateOnSize = cy / m_dHeightRateOnSize;
	}

	long nXa, nXb;
	m_pTimeCursorDraw->GetTwoCursorPosition(nXa, nXb);
	double dTimeA, dTimeB;
	m_oTimeAxisDraw.DevicePointToLogicPoint(nXa, &dTimeA);
	m_oTimeAxisDraw.DevicePointToLogicPoint(nXb, &dTimeB);

	InitByBorder();

	//计算当前的绘图范围
	double dMax,dMin;
	double dOldMax,dOldMin;
	m_oTimeAxisDraw.GetOldMaxMinTime(dOldMax,dOldMin);	
	m_oTimeAxisDraw.GetMaxMinTime(dMax,dMin);
	m_oTimeAxisDraw.SetOldMaxMinTime(dOldMax,dOldMin);
	m_oTimeAxisDraw.SetMaxMinTime(dMax,dMin);
	CalXPosByTimeAxis();

	//调整各个通道的绘图区域
	InitDrawVarRect();
	m_oTimeAxisDraw.LogicPointToDevicePoint(dTimeA, &nXa);
	m_oTimeAxisDraw.LogicPointToDevicePoint(dTimeB, &nXb);
	m_pTimeCursorDraw->SetCursorPosition(nXa, USETIMECURSORA);
	m_pTimeCursorDraw->SetCursorPosition(nXb, USETIMECURSORB);
	CalValues();
	FireTimeAxisChangedSysOptr();
	DrawAnalyse();
}

void CViewAnalyse::SetBorder()
{
	CreateMemDC();
	
	InitByBorder();
}


void CViewAnalyse::ReSetBorder(const CRect &rect)
{
	CXDrawElements::SetBorder(rect);
	long nTop		= rect.top;
	long nLeft		= rect.left;
	long nRight		= rect.right;
	long nBottom	= rect.bottom;
	m_rcTimeandProgress  = CRect(nLeft , nTop , nRight , nTop + MrDraw::g_snTimeandProgressRectHeight);
	CRect rcMain = CRect(nLeft , nTop + MrDraw::g_snTimeandProgressRectHeight, nRight , nBottom - MrDraw::g_snBottomRectHeight);
	long nWidth = m_oDrawSysTime.m_nDrawWidth;
	CRect rcTime = CRect(nRight - nWidth , nTop , nRight , nTop + MrDraw::g_snTimeandProgressRectHeight);
	m_oDrawSysTime.SetBorder(rcTime);
	
	/////////////////
	ReSetMainRect(rcMain);
	
}

void CViewAnalyse::ReSetMainRect(const CRect &rect)
{
	CXDrawElements::SetBorder(rect);
	
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
	
	//设置各个通道的Border，因为只是改变右侧，所以改变Right的值
	POS  pos = m_oVariableMngr.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawVariable* pDraw = (CDrawVariable*)m_oVariableMngr.GetNext(pos);
		pDraw->SetBorderRight(nRight);
		pDraw->SetClipRect(m_rcWaveDraw);
	}
}

void CViewAnalyse::AttachCurrentVariable()
{
	InitCurrDrawPageVariables();
	m_pRangeStateAxis->AttachDrawObject(m_pCurrDrawVariable);		
	AdjustChanState();
}

CDrawVariable* CViewAnalyse::FindDrawVariableBySelIndex(long nIndex)
{
	CDrawVariable* pDraw = NULL;
	CDrawVariable* pFind = NULL;
	long nUseVars = 0;
	POS  pos = m_oVariableMngr.GetHeadPosition();
	
	while (pos != NULL)
	{
		pDraw = (CDrawVariable*)m_oVariableMngr.GetNext(pos);
		
		if (pDraw->GetUse() == 1)
		{
			if (nIndex == nUseVars)
			{
				pFind = pDraw;
				break;
			} 
			else
			{
				nUseVars++;
			}			
		} 
		else
		{
		}
	}
	
	return pFind;
}

void CViewAnalyse::InitDrawVarRect()
{
	InitRecordDrawObjectPosByControl();
	SetAllObjParentWnd();
}

//////////////////////////////////////////////////////////////////////////
//使用映射文件的相关处理
void CViewAnalyse::MapRecorBuffer(double dBeginTime, double dTimeLong)
{
/*
	m_pCurrDrawObj = NULL;

	CMrOnlineRecordEx *pMrOnlineRecordEx = CMrOnlineRecordEx::g_pMrOnlineRecordEx;
	ASSERT (pMrOnlineRecordEx != NULL);
	pMrOnlineRecordEx->ViewOnlineFileMap(dBeginTime, dTimeLong);

	//缓冲区改变，关联缓冲区，初始化参数数据的计算
	

	//if (g_theRecordApp.IsRecordDataModeOnlineRecord() || g_theRecordApp.IsRecordDataModeComtrade())
	{
		g_theRecordApp.AttachOnlineRecordExBuffer();
	}

	g_theRecordApp.FireSysOptrMsg(MR1200_SYSOPTR_RECORDMAP_CHANGED, 1, 1);
*/
}

