// DrawGlobalDef.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DRAWGLOBALDEF_H__)
#define _DRAWGLOBALDEF_H__

#include "../../XDrawBase/XDrawElements.h"
#include "../../API/GloblaDrawFunctions.h"
// #include "..\RecordSysMsgDef.h"
// #include "..\RecordGlobalDefine.h"

extern HCURSOR g_hMoveCursor;
// extern CBitmap g_bmpZoom;
extern 	BOOL g_bInWriteBmpFileState;

namespace MrDraw
{	
#define VARIABLE_NAME_MIN_LENGTH			40
#define VARIABLE_MIN_DEFAULT_HEIGHT			50
#define DRAW_HAS_OBJECT_SELECTED            1
#define DRAW_NONE_OBJECT_SELECTED           0
	
#define AXIS_SCALE_MIN_VALUE   0.000000001

#define ANALOG_DRAW_MODE_LINE         0
#define ANALOG_DRAW_MODE_CROSSA     1   ////	+ 
#define ANALOG_DRAW_MODE_CROSSX     2  ////	x

// #define WM_RECORD_TIMER_DRAW                (WM_USER + 89)
// #define WM_DRAW								(WM_USER + 90)
// #define WM_INVALIDATE_RANGESTATEAXIS        (WM_USER + 91)
// #define WM_VARIABLE_SIZE_CHANGED		    (WM_USER + 92)
// #define WM_VARIABLE_POS_CHANGED				(WM_USER + 93)
// #define WM_VARIABLE_SELECT_CHANGED			(WM_USER + 94)
// #define WM_TIMEAXIS_CHANGED					(WM_USER + 95)
// #define WM_TIMECURSOR_POS_CHANGE			(WM_USER + 96)
// #define WM_TIMECURSOR_SELECT_CHANGE			(WM_USER + 97)
// #define WM_TIME_CHANGED						(WM_USER + 98)

	extern long g_snTimeAxisHeight;			//= 33;//25;
	extern long g_snNameandAxisRectWidth;		//= 50;
	extern long g_snWaveDrawAreaGap;				//= 2;	//15;
	extern long g_snBottomRectHeight;			//= 0;	//15;
	extern long g_snTimeandProgressRectHeight;	//= 0;	//5;

	//模拟量绘图模式
	extern DWORD g_dwAnalogDrawMode;

	//绘图时的显示波形的数据范围
	typedef struct  
	{
		long nBufLength;
		long nBuf1BeginPos;
		long nBuf1EndPos;
		long nBuf2BeginPos;
		long nBuf2EndPos;
		long nGap;
	}DRAWMEMBUFFERPOS, *PDRAWMEMBUFFERPOS;
		
	extern LOGFONT g_lfDrawVariableName;
	extern LOGFONT g_lfDrawVariableSelectName;
	extern LOGFONT g_lfDrawVaraibleAxisScale;
	extern LOGFONT g_lfDrawPara;
	extern long g_nVariableNameLength;
	
	inline BOOL PointInRect(const CPoint &pt, const CRect &rcRect)
	{
		return (rcRect.left <= pt.x && pt.x <= rcRect.right
			&& rcRect.top <= pt.y && pt.y <= rcRect.bottom);
	}

	inline BOOL PointInRect(const CPoint &pt, const CPoint &ptTopLeft, long nWidth, long nHeight)
	{
		return (ptTopLeft.x <= pt.x && pt.x <= ptTopLeft.x + nWidth
			&& ptTopLeft.y <= pt.y && pt.y <= ptTopLeft.y + nHeight);
	}

	inline BOOL PointInRect(const CRect &rcRect, const CPoint &pt)
	{
		return (rcRect.left <= pt.x && pt.x <= rcRect.right
			&& rcRect.top <= pt.y && pt.y <= rcRect.bottom);
	}

	//波形绘制窗口的颜色设置
// 	extern COLORREF g_crDrawBackColor;
// 	extern COLORREF g_crDrawAreaBkColorFrom;
// 	extern COLORREF g_crDrawAreaBkColorTo;
 	extern COLORREF g_crAxisGrid;
// 	extern COLORREF g_crDrawAreaLeftTopFrom;
// 	extern COLORREF g_crDrawAreaLeftTopTo;
// 	extern COLORREF g_crDrawAreaRightBottomFrom;
// 	extern COLORREF g_crDrawAreaRightBottomTo;

	double GetFloatCarryValue(double dValue);	//获取浮点数的进位数字
	double GetFloatCarryValue2(double dValue);
	double GetIECAxisScaleValueZoomIn(double dValue, double &dMinScaleVal);    //获取IEC标准的坐标轴的刻度值
	double GetIECAxisScaleValueZoomOut(double dValue, double &dMinScaleVal);    //获取IEC标准的坐标轴的刻度值
	inline double GetIECAxisScaleValue(double dValue, double &dMinScaleVal) {return GetIECAxisScaleValueZoomIn(dValue, dMinScaleVal);}

	inline void ValidateGap(long &nGap, long nMaxGap)
	{
		if (nGap <= 0)
		{
			nGap = 1;
		}

		if (nGap > nMaxGap)
		{
			nGap = nMaxGap;
		}
	}

	inline long CalGap(long nBufPoints, long nNeedPoints, long nMaxGap)
	{
		ASSERT( nBufPoints != 0);
		long nGap = nBufPoints / nNeedPoints;
		long nRemain = nBufPoints % nNeedPoints;
		
		if(nRemain > 0)
		{
			nGap++;
		}
		
		ValidateGap(nGap, nMaxGap);
		
		return nGap;
	}

	inline void InitDrawBuffPos(PDRAWMEMBUFFERPOS pDrawBufPos)
	{
		pDrawBufPos->nGap = 1;
		pDrawBufPos->nBufLength = 0;
		pDrawBufPos->nBuf1BeginPos = -1;
		pDrawBufPos->nBuf1EndPos   = -1;
		pDrawBufPos->nBuf2BeginPos = -1;
		pDrawBufPos->nBuf2EndPos   = -1;
	}
	inline void InitDrawBuffPos(PDRAWMEMBUFFERPOS pDrawBufPos, long nGap, long nBufLength)
	{
		pDrawBufPos->nGap = nGap;
		pDrawBufPos->nBufLength = nBufLength;
		pDrawBufPos->nBuf1BeginPos = -1;
		pDrawBufPos->nBuf1EndPos   = -1;
		pDrawBufPos->nBuf2BeginPos = -1;
		pDrawBufPos->nBuf2EndPos   = -1;
	}
	inline void ClearDrawBuffBeginEndPos(PDRAWMEMBUFFERPOS pDrawBufPos)
	{
// 		pDrawBufPos->nGap = 1;
// 		pDrawBufPos->nBufLength = 0;
		pDrawBufPos->nBuf1BeginPos = -1;
		pDrawBufPos->nBuf1EndPos   = -1;
		pDrawBufPos->nBuf2BeginPos = -1;
		pDrawBufPos->nBuf2EndPos   = -1;
	}

}


#endif // !defined(_DRAWGLOBALDEF_H__)
