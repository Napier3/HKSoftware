// DrawGlobalDef.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawGlobalDef.h"
#include "../../../Module/API/GloblaDrawFunctions.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
HCURSOR g_hMoveCursor = NULL;

long RANGESTATEAXIS_BLOCK_WIDTH  =   15;
long RANGESTATEAXIS_BLOCK_WIDTHGAP = 7;
long RANGESTATEAXIS_BLOCK_HEIGHT1 =  7;
long RANGESTATEAXIS_BLOCK_HEIGHT2 =  7;

long RANGESTATEAXIS_MIN_LENGTH  =    14; //4+ 2+ 4


// CBitmap g_bmpZoom;
namespace MrDraw
{
	LOGFONT g_lfDrawPara;
	LOGFONT g_lfDrawVariableName;
	LOGFONT g_lfDrawVariableSelectName;
	LOGFONT g_lfDrawVaraibleAxisScale;
	long g_nVariableNameLength = VARIABLE_NAME_MIN_LENGTH;
	
	long g_snTimeAxisHeight				= 26 + RANGESTATEAXIS_BLOCK_WIDTH;//25;
	long g_snNameandAxisRectWidth		= 50;
	long g_snWaveDrawAreaGap			= 2;	//15;
	long g_snBottomRectHeight			= 0;	//15;
	long g_snTimeandProgressRectHeight	= 0;	//5;
	
	DWORD g_dwAnalogDrawMode = ANALOG_DRAW_MODE_LINE;
	
// 	COLORREF g_crDrawBackColor	= RGB(182,182,182);
// 	COLORREF g_crDrawAreaBkColorFrom     = RGB(240, 240, 240);
// 	COLORREF g_crDrawAreaBkColorTo       = RGB(255, 255, 255);
 	COLORREF g_crAxisGrid = RGB(100, 100, 100);
// 	COLORREF g_crDrawAreaLeftTopFrom = RGB(90, 90, 90);
// 	COLORREF g_crDrawAreaLeftTopTo = RGB(90, 90, 90);
// 	COLORREF g_crDrawAreaRightBottomFrom = RGB(210, 210, 210);
// 	COLORREF g_crDrawAreaRightBottomTo = RGB(210, 210, 210);
	
	class CDrawGlobalDef
	{
	private:
		CDrawGlobalDef()
		{
			g_lfDrawVariableName = InitLogFont();
			g_lfDrawVariableSelectName = InitLogFont();
			g_lfDrawVaraibleAxisScale = InitLogFont();
			g_lfDrawPara = InitLogFont();
			
			g_lfDrawPara.lfHeight = - 10;
			g_lfDrawVariableName.lfHeight = -10;
			g_lfDrawVariableName.lfWeight = 0;
			g_lfDrawVariableSelectName.lfHeight = -12;
            g_lfDrawVariableSelectName.lfWeight = 700;
			
// 			strcpy(g_lfDrawPara.lfFaceName, "Tahoma");
// 			strcpy(g_lfDrawVariableName.lfFaceName, "Tahoma");
// 			strcpy(g_lfDrawVariableSelectName.lfFaceName, "Tahoma");
// 			strcpy(g_lfDrawVaraibleAxisScale.lfFaceName, "Tahoma");
			
			
		}
		
		virtual ~CDrawGlobalDef()
		{
		}
		
	public:
		static CDrawGlobalDef *g_pDrawGlobalDef;
		static long g_nDrawGlobalDefRefCount;
		
		static CDrawGlobalDef* CreateDrawGlobalDef()
		{
			g_nDrawGlobalDefRefCount++;
			
			if (g_nDrawGlobalDefRefCount == 1)
			{
				g_pDrawGlobalDef = new CDrawGlobalDef();
			}
			
			return g_pDrawGlobalDef;
		}
		
		static void Release()
		{
			g_nDrawGlobalDefRefCount--;
			
			if (g_nDrawGlobalDefRefCount == 0)
			{
				delete g_pDrawGlobalDef;
				g_pDrawGlobalDef = NULL;
			}
		}
		
	};
	
	CDrawGlobalDef* CDrawGlobalDef::g_pDrawGlobalDef = NULL;
	long CDrawGlobalDef::g_nDrawGlobalDefRefCount    = 0;
	
	class CDrawGlobalDefCreator
	{
	public:
		CDrawGlobalDef *m_pDrawGlobalDef;
		
		CDrawGlobalDefCreator()
		{
			m_pDrawGlobalDef = CDrawGlobalDef::CreateDrawGlobalDef();
		}
		
		virtual ~CDrawGlobalDefCreator()
		{
			m_pDrawGlobalDef->Release();
		}
	};
	
	CDrawGlobalDefCreator g_oDrawGlobalDefCreator;
	
	//获取浮点数的进位数字
	double GetFloatCarryValue(double dValue)
	{
		double fStep = AXIS_SCALE_MIN_VALUE;
		double fStep1=fStep*10;
		
		for (int i=1;;i++)
		{
			if( (dValue >=fStep ) && (dValue < fStep1) ) 
			{
				break;
			}
			
			fStep=fStep1;
			fStep1*=10;
		}

		return fStep;
	}
	double GetFloatCarryValue2(double dValue)
	{
		if (dValue <= 0.0001)
		{
			dValue = 0.001;
			return dValue;
		}

		double fStep = AXIS_SCALE_MIN_VALUE;
		double fStep1=fStep*10;
		
		for (int i=1;;i++)
		{
			if( (dValue >=fStep ) && (dValue < fStep1) ) 
			{
				break;
			}
			
			fStep=fStep1;
			fStep1*=10;
		}
		
		double dCal = fStep;

		while (TRUE)
		{
			if (dValue < dCal)
			{
				return dCal;
			}

			dCal += fStep;
		}
		
		return fStep1;
	}

	//获取IEC标准的坐标轴的刻度值
	double GetIECAxisScaleValueZoomIn(double dValue, double &dMinScaleVal)
	{
		if(dValue <= AXIS_SCALE_MIN_VALUE)
		{
			dMinScaleVal = dValue;
			return dValue;
		}

		double fCarry = GetFloatCarryValue(dValue);///进位数值
		int iSet[4] = {1, 2, 5, 10};
		double fMin = 0;
		double fMax = 0;
		
		for (int i=0; i<3; i++)
		{
			fMin = fCarry * iSet[i];
			fMax = iSet[i+1] * fCarry;
			
			if ((dValue >= fMin) && (dValue < fMax) )
			{
				dMinScaleVal = fMin;
				
				return fMax;
			}
		}
		
		return fMax;
	}

	double GetIECAxisScaleValueZoomOut(double dValue, double &dMinScaleVal)
	{
		if(dValue <= AXIS_SCALE_MIN_VALUE)
		{
			dMinScaleVal = dValue;
			return dValue;
		}

		double fCarry = GetFloatCarryValue(dValue);///进位数值
		int iSet[4] = {1, 2, 5, 10};
		double fMin = 0;
		double fMax = 0;
		
		for (int i=0; i<3; i++)
		{
			fMin = fCarry * iSet[i];
			fMax = iSet[i+1] * fCarry;
			
			if ((dValue >= fMin) && (dValue < fMax) )
			{
				if (dValue == fMin)
				{
					dMinScaleVal = fMin;
					return fMax;
				}
				else
				{
					dMinScaleVal = fMax;
					return fMax;
				}
			}
		}
		
		return fMax;
	}
}
