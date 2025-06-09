//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VMDrawIed.cpp  CSttIecGsDrawIed


#include "stdafx.h"
#include "SttIecGsBinaryDraw.h"
#include "../../../../Module/API/GloblaDrawFunctions.h"
//#include "../../UI/SttTestCntrFrameBase.h"

//////////////////////////////////////////////////////////////////////////
//CSttIecGsBinarysDraw
CSttIecGsBinaryDraw::CSttIecGsBinaryDraw()
{
	//初始化属性
	m_pDatas = NULL;

	//初始化成员变量
}

CSttIecGsBinaryDraw::~CSttIecGsBinaryDraw()
{
}

void CSttIecGsBinaryDraw::CreateBinaryDraw(long nIndex, EPCAPPARSEDATAS *pDatas)
{
	m_nBinaryIndex = nIndex;
	m_pDatas = pDatas;
}

long CSttIecGsBinaryDraw::GetBinaryBitVal()
{
	
	//return vm_GetBinaryBitVal(m_pBinaryBufRef, m_nBytePos, m_nBitPos);

	return 0;
}

void CSttIecGsBinaryDraw::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CRect rc_IedName;
	vm_draw_get_binary_rect(m_ptTopLeft, rc_IedName);
	// 	rc_IedName.left = m_ptTopLeft.x + XBINARY_DRAW_GAP_HOR;
	// 	rc_IedName.top =  m_ptTopLeft.y + XBINARY_DRAW_GAP_HOR;
	// 	rc_IedName.right = rc_IedName.left + XBINARY_DRAW_WIDTH;
	// 	rc_IedName.bottom = rc_IedName.top + XBINARY_DRAW_HEIGHT;

	CPen pen;

	if (IsPicked())
	{
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	}
	else
	{
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	}

	CPen *pOldPen = pDC->SelectObject(&pen);
	CBrush brush;
	PEPCAPPARSEDATA pData = &m_pDatas->pDatas[m_nBinaryIndex];

	switch(pData->wChType)
	{
	case 0x83:   //单点
		if (pData->dwValue == 0)//20220611 为0值分位
		{
			brush.CreateSolidBrush(BINARY_OPEN_COLOR);
		}
		else
		{
			brush.CreateSolidBrush(BINARY_CLOSE_COLOR);
		}
		break;
	case 0x84://双点
		if ((pData->dwValue&0xFF) == 0x00)
		{
			brush.CreateSolidBrush(BINARY_COLOR_0X84_0);
		}
		else if ((pData->dwValue&0xFF) == 0x40)
		{
			brush.CreateSolidBrush(BINARY_COLOR_0X84_1);
		}
		else if ((pData->dwValue&0xFF) == 0x80)
		{
			brush.CreateSolidBrush(BINARY_COLOR_0X84_2);
		}
		else
		{
			brush.CreateSolidBrush(BINARY_COLOR_0X84_3);
		}
		break;
	default:
		brush.CreateSolidBrush(BINARY_NOT_BINARY_COLOR);

		break;
	}

// 	if ((pData->wChType == 0x83)||(pData->wChType == 0x84))
// 	{
// 		CString strLog;
// 		strLog.Format("wChType:%d;dwValue:%d(ChIndex=%ld).", pData->wChType, pData->dwValue,m_nBinaryIndex);
// 		g_theTestCntrFrame->m_pResultWidget->LogString(0, strLog);
// 	}

	CBrush *pOldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(rc_IedName);
	CString strName;
	vm_draw_get_binary_name(strName, m_nBinaryIndex);

	CRect rc_IedName_Text = rc_IedName;
	rc_IedName_Text.DeflateRect(1, 1, 1, 1);
	CmDrawTextRect(pDC, strName, m_crForeColor, rc_IedName_Text, m_crBkColor, g_fontXBinaryDraw, TRANSPARENT,DT_VCENTER|DT_CENTER,0);

/*
	strName.Format(_T("%d"), m_nBinaryIndex / 32 + 1);
	rc_IedName_Text.right = rc_IedName_Text.left + rc_IedName_Text.Width() / 2;
	LOGFONT font = g_fontXBinaryDraw;
	vm_draw_get_card_font(font);
	CmDrawTextRect(pDC, strName, g_crCardIndexDraw, rc_IedName_Text, m_crBkColor, font, TRANSPARENT,DT_LEFT|DT_TOP,0);
*/

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

//////////////////////////////////////////////////////////////////////////
//CSttIecGsBinarysDraw
CSttIecGsBinarysDraw::CSttIecGsBinarysDraw()
{
	//初始化属性
	m_pDatas = NULL;
	m_nBinaryCount = 0;   //开关量数目

	//初始化成员变量
}

CSttIecGsBinarysDraw::~CSttIecGsBinarysDraw()
{
}

void CSttIecGsBinarysDraw::CreateBinarysDraw(long nCount, EPCAPPARSEDATAS *pDatas, CWnd *pMsgRcvWnd)
{
	m_pDatas = pDatas;
	CSttIecGsBinaryDraw *pNew = NULL;
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pNew = new CSttIecGsBinaryDraw();
		AddNewChild(pNew);
		pNew->CreateBinaryDraw(nIndex, pDatas);
		pNew->m_pParentWnd = pMsgRcvWnd;
	}
}
