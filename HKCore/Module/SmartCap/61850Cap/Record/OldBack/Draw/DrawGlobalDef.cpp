// DrawGlobalDef.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawGlobalDef.h"
#include "..\..\..\..\..\Module\API\GloblaDrawFunctions.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
HCURSOR g_hMoveCursor = NULL;
CBitmap g_bmpZoom;
namespace MrDraw
{
	LOGFONT g_lfDrawPara;
	LOGFONT g_lfDrawVariableName;
	LOGFONT g_lfDrawVariableSelectName;
	LOGFONT g_lfDrawVaraibleAxisScale;
	long g_nVariableNameLength = VARIABLE_NAME_MIN_LENGTH;
	
	long g_snTimeAxisHeight				= 33;//25;
	long g_snNameandAxisRectWidth		= 65;
	long g_snWaveDrawAreaGap			= 2;	//15;
	long g_snBottomRectHeight			= 0;	//15;
	long g_snTimeandProgressRectHeight	= 0;	//5;
	
	
	COLORREF g_crDrawBackColor	= RGB(182,182,182);
	COLORREF g_crDrawAreaBkColorFrom     = RGB(240, 240, 240);
	COLORREF g_crDrawAreaBkColorTo       = RGB(255, 255, 255);
	COLORREF g_crAxisGrid = RGB(100, 100, 100);
	COLORREF g_crDrawAreaLeftTopFrom = RGB(90, 90, 90);
	COLORREF g_crDrawAreaLeftTopTo = RGB(90, 90, 90);
	COLORREF g_crDrawAreaRightBottomFrom = RGB(210, 210, 210);
	COLORREF g_crDrawAreaRightBottomTo = RGB(210, 210, 210);

	class CDrawGlobalDef
	{
	private:
		CDrawGlobalDef()
		{
			g_lfDrawVariableName = InitLogFont();
			g_lfDrawVariableSelectName = InitLogFont();
			g_lfDrawVaraibleAxisScale = InitLogFont();
			g_lfDrawPara = InitLogFont();
			
			g_lfDrawPara.lfHeight = - 12;
			g_lfDrawVariableName.lfHeight = -10;
			g_lfDrawVariableName.lfWeight = 0;
			g_lfDrawVariableSelectName.lfHeight = -10;
			g_lfDrawVariableSelectName.lfWeight = FW_BOLD;
			
#ifdef _UNICODE
			wcscpy(g_lfDrawPara.lfFaceName, _T("Tahoma"));
			wcscpy(g_lfDrawVariableName.lfFaceName, _T("Tahoma"));
			wcscpy(g_lfDrawVariableSelectName.lfFaceName, _T("Tahoma"));
			wcscpy(g_lfDrawVaraibleAxisScale.lfFaceName, _T("Tahoma"));
#else
			strcpy(g_lfDrawPara.lfFaceName, _T("Tahoma"));
			strcpy(g_lfDrawVariableName.lfFaceName, _T("Tahoma"));
			strcpy(g_lfDrawVariableSelectName.lfFaceName, _T("Tahoma"));
			strcpy(g_lfDrawVaraibleAxisScale.lfFaceName, _T("Tahoma"));
#endif
			
			
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

}
