#include "stdafx.h"
#include "EpDevGlobalDefine.h"


static COLORREF g_crEpDevViewBackColor = RGB(255, 255, 255);
static COLORREF g_crEpDevViewForeColor = RGB(0, 0, 0);

void EPD_SetDevViewBackColor(COLORREF cr)
{
	g_crEpDevViewBackColor = cr;
}

COLORREF EPD_GetDevViewBackColor()
{
	return g_crEpDevViewBackColor;
}

void EPD_SetDevViewForeColor(COLORREF cr)
{
	g_crEpDevViewForeColor = cr;
}

COLORREF EPD_GetDevViewForeColor()
{
	return g_crEpDevViewForeColor;
}

