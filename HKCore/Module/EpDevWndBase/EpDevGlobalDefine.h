#pragma once

#include "../BaseClass/ExBaseObject.h"

//DevWnd����
#define EPDCLASSID_DEVBASE				(CLASSID_BASECLASS + 0x00400000)
#define EPDCLASSID_DEVBASELIST		(CLASSID_LISTCLASS + 0x00600000)
#define EPDCLASSID_DEVWND				(EPDCLASSID_DEVBASELIST + 0x00500000)
#define EPDCLASSID_DEVPOINT			(EPDCLASSID_DEVBASELIST + 0x00700000)

//���ڼ��
#define EPDWND_GAP_VERT  10
#define EPDWND_GAP_HORZ  20

//���ڵ�չ��״̬
#define EPDES_CLOSE     0
#define EPDES_EXPAND   1

//���ڵ���ʾ������״̬
#define EPDES_HIDE      0
#define EPDES_SHOW   1

//ȫ�ֺ���
//����������
inline void EPD_DrawLinkLine(CPoint ptBegin,CPoint ptEnd,CDC* pDC)
{
	CPoint ptMiddle1((ptBegin.x+ptEnd.x)/2,ptBegin.y);
	CPoint ptMiddle2(ptMiddle1.x,ptEnd.y);
	CPoint ptArray[4] = {ptBegin,ptMiddle1,ptMiddle2,ptEnd};
 
	pDC->PolyBezier(ptArray,4);
}

void EPD_SetDevViewBackColor(COLORREF cr);
COLORREF EPD_GetDevViewBackColor();
void EPD_SetDevViewForeColor(COLORREF cr);
COLORREF EPD_GetDevViewForeColor();


//////////////////////////////////////////////////////////////////////////
//WM_MESSAGE define
#define WM_DEV_WND_SIZE_CHANGED  (WM_USER+1917)   //2011/10/18

