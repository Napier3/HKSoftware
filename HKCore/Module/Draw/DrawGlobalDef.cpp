// DrawGlobalDef.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawGlobalDef.h"
#include "..\..\..\Module\API\GloblaDrawFunctions.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HCURSOR g_hMoveCursor = NULL;
CBitmap g_bmpZoom;
namespace MrDraw
{
LOGFONT g_lfDrawPara;
LOGFONT g_lfDrawVariableName;
LOGFONT g_lfDrawVaraibleAxisScale;
long g_nVariableNameLength = VARIABLE_NAME_MIN_LENGTH;

class CDrawGlobalDef
{
private:
	CDrawGlobalDef()
	{
		g_lfDrawVariableName = InitLogFont();
		g_lfDrawVaraibleAxisScale = InitLogFont();
		g_lfDrawPara = InitLogFont();

		g_lfDrawPara.lfHeight = - 10;
		g_lfDrawVariableName.lfHeight = -10;
		g_lfDrawVariableName.lfWeight = 0;

		strcpy(g_lfDrawPara.lfFaceName, "Tahoma");
		strcpy(g_lfDrawVariableName.lfFaceName, "Tahoma");
		strcpy(g_lfDrawVaraibleAxisScale.lfFaceName, "Tahoma");
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