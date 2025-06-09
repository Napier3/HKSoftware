// DrawParas.cpp: implementation of the CDrawParas class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawParas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawParas::CDrawParas()
{
	memset(&m_oParaValue, 0, sizeof(RTCHANNELATTRVALUE));
	memset(&m_oCalPara, 0, sizeof(RTATTRIBUTECALFUNCPARA));

	m_oParaFont.CreateFontIndirect(&MrDraw::g_lfDrawPara);
	m_oCalPara.pRtChAttrVal = &m_oParaValue;
	m_ptBegin.x		= 0;
	m_ptBegin.y		= 0;
	m_nParaPosToCursor	= 0; 
	m_crForeColor          = RGB(124,153,226);

	m_rcPara			= CRect(0,0,0,0);
	m_strUnit			= "";
	m_ptBegin			= CPoint(0,0);
	m_rcClip			= CRect(0,0,0,0);
}

CDrawParas::~CDrawParas()
{
	m_oParaFont.DeleteObject();
}

void CDrawParas::Draw(CDC* pDC)
{
	long Amount = GetCount();
	long nLen = m_oCalPara.nDataLength ;
	
	if (Amount < 1 || nLen < 1)
	{
		return;
	}

	int nMode = pDC->SetBkMode(TRANSPARENT);
	POS pos = GetHeadPosition();
	CDrawPara* pPara = NULL;
	COLORREF cr = pDC->GetTextColor();
	pDC->SetTextColor(RGB(255, 255, 255));

	while (pos != NULL) 
	{
		pPara = (CDrawPara*)GetNext(pos);
		pPara->Draw(pDC);
	}

	pDC->SetTextColor(cr);

#ifndef _PSX_IDE_QT_
	CDC BitmapDC;
	long nTop = m_rcPara.top;
	long nLeft = m_rcPara.left;
	long nWidth = m_rcPara.Width();
	long nHeight = m_rcPara.Height();

	BitmapDC.CreateCompatibleDC(pDC);
	HDC hdc=pDC->GetSafeHdc();
	HDC bitDC=BitmapDC.GetSafeHdc();
	
	CBitmap hBitmap;
	hBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
	CBitmap* bm=BitmapDC.SelectObject(&hBitmap);
	BitmapDC.FillSolidRect(0,0,nWidth,nHeight,m_crForeColor);
	BLENDFUNCTION bf;
	bf.BlendFlags=0;
	bf.AlphaFormat=0;
	bf.BlendOp=AC_SRC_OVER;
	bf.SourceConstantAlpha=128;
	AlphaBlend(hdc,nLeft,nTop,nWidth,nHeight,bitDC,0,0,nWidth,nHeight,bf);
	BitmapDC.SelectObject(bm);
	hBitmap.DeleteObject();
	bm=NULL;
	pDC->SetBkMode(nMode);
#endif
}

void CDrawParas::AddPara(UINT nID)
{
	//链表是一个固定顺序的
	POS pos = GetHeadPosition();
	CDrawPara* pObj = NULL;//(CDrawPara*)GetAt(pos);
	CDrawPara* pNew = NULL;
	
	BOOL bInserted = FALSE;
	POS pPre = NULL;//上一个节点
	
	while(pos != NULL)//遍历链表，是插入，还是已经有的
	{
		pPre = pos;
		pObj = (CDrawPara*)GetNext(pos);
		UINT nParaID = pObj->m_nParaID;
		
		if(nID < nParaID ) 
		{
			pNew = CreateNewPara(nID);
			InsertBefore(pPre,pNew);
			bInserted = TRUE;
			break;	
		}
		else if(nID == nParaID )
		{
			bInserted = TRUE;
			break;	
		}
		else
		{
		}
	}
	
	if (!bInserted)
	{
		pNew = CreateNewPara(nID);
		AddTail(pNew);
	}

	if (pNew != NULL)
	{
		pNew->Init(nID,m_strUnit,&m_oCalPara,&m_oParaFont);
	}
}

void CDrawParas::SetAdjustValue(double dZero,double dCoef)
{
	m_oCalPara.dCeofValue = dCoef;
	m_oCalPara.dZeroValue = dZero;
}

void CDrawParas::DeletePara(UINT nID)
{
	POS pos = GetHeadPosition();
	CDrawPara* pPara = NULL;
	POS pPrePos = NULL;

	while (pos != NULL) 
	{
		pPrePos = pos;
		pPara = (CDrawPara*)GetNext(pos);

		if (pPara->GetParaID() == nID)
		{
			DeleteAt(pos);
		}
	}
}

void CDrawParas::DeleteAllPara()
{
	DeleteAll();
}

void CDrawParas::SetParentWnd(CWnd* pParentWnd)
{
	m_pParentWnd = pParentWnd;

	POS pos = GetHeadPosition();
	CDrawPara* pPara = NULL;
	
	//获得区域宽度和高度
	while (pos != NULL) 
	{
		pPara = (CDrawPara*)GetNext(pos);		
		pPara->SetParentWnd(m_pParentWnd);
	}
}

void CDrawParas::CalParaRect(long nXPos, long nYCenter)
{
	long Amount = GetCount();
	
	if (Amount < 1)
	{
		return;
	}
	
	m_ptBegin.x = nXPos;
	m_ptBegin.y = nYCenter;

	long nTotalHeight = 0;
	long nPerHeight = 0;
	long nPerWidth = 0;
	long nMaxWidth = -1;
	POS pos = GetHeadPosition();
	CDrawPara* pPara = NULL;

	//获得区域宽度和高度
	while (pos != NULL) 
	{
		pPara = (CDrawPara*)GetNext(pos);		
		pPara->GetDrawRectSize(nPerWidth,nPerHeight);
		nTotalHeight += nPerHeight;

		if (nPerWidth > nMaxWidth)
		{
			nMaxWidth = nPerWidth;
		}
	}

	//设置区域位置
	long nLeft = nXPos + Para_to_Cursor;
	long nRight = nLeft + nMaxWidth;
	long nTop = nYCenter - nTotalHeight ;
	long nBom = nYCenter ;

	m_rcPara.top = nTop;
	m_rcPara.bottom = nBom;
	m_rcPara.left = nLeft;
	m_rcPara.right = nRight;
	
	if (nLeft < m_rcClip.left)
	{
		m_rcPara.left = m_rcClip.left;
		m_rcPara.right = m_rcPara.left + nMaxWidth;
	}

	if (nRight > m_rcClip.right)
	{
		m_rcPara.left = nXPos - Para_to_Cursor - nMaxWidth;
		m_rcPara.right = nXPos - Para_to_Cursor;
		m_nParaPosToCursor = 1;
	}

	if (nTop < m_rcClip.top)
	{
		m_rcPara.top = m_rcClip.top;
		m_rcPara.bottom = m_rcClip.top + nTotalHeight;
	}

	if (nBom > m_rcClip.bottom)
	{
		m_rcPara.bottom = m_rcClip.bottom;
		m_rcPara.top = m_rcClip.bottom - nTotalHeight;
	}
	
	//m_rcBorder = m_rcPara;
	SetBorder(m_rcPara);

	SetParaRect(m_rcPara);
}

void CDrawParas::SetClipRect(CRect rect)
{
	m_rcClip = rect;
}

CDrawPara* CDrawParas::CreateNewPara(UINT nID)
{
	CDrawPara* pNew = NULL;
	switch(nID)
	{
	case Para_FreqValue:             
	case Para_EffecValue:             
	case Para_EffecPhase:             
	case Para_PeakValue:             
	case Para_VellayValue:           
	case Para_InstValue:              
	case Para_AverageValue:        
	case Para_Impedance:             
	case Para_ActivePower:            
	case Para_ReactivePower:            
	case Para_ApparentPower:
	case Para_PositiveSequence:
	case Para_NegativeSequence:
	case Para_ZeroSequence:
		{
			pNew = new CDrawPara();
		}
		break;
	case Para_FundValue:             
	case Para_HarmValue2:        
	case Para_HarmValue3:
	case Para_HarmValue4:        
	case Para_HarmValue5:       
	case Para_HarmValue6:       
	case Para_HarmValue7:  			
	case Para_HarmValue8:        
	case Para_HarmValue9:        
	case Para_HarmValue10:        
	case Para_HarmValue11:        
	case Para_HarmValue12:        
	case Para_HarmValue13:        
	case Para_HarmValue14:        
	case Para_HarmValue15:        
	case Para_HarmValue16:        
	case Para_HarmValue17:        
	case Para_HarmValue18:        
	case Para_HarmValue19:        
	case Para_HarmValue20:        
	case Para_HarmValue21:        
	case Para_HarmValue22:        
	case Para_HarmValue23:       
	case Para_HarmValue24:        
	case Para_HarmValue25: 
		{
			pNew = new CDrawMultiPara();
		}
		break;
	default:
		break;
	}

	return pNew;
}

void CDrawParas::SetParaRect(CRect rcPara)
{
	long nParaAmount = GetCount();

	if (nParaAmount < 1)
	{
		return ;
	}
	
	m_rcPara = rcPara;
	long nTop = rcPara.top;
	long nPerHeight = m_rcPara.Height() / nParaAmount;
	long nIndex = 0;

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CDrawPara* pPara = (CDrawPara*)GetNext(pos);
		//pPara->m_rcBorder = m_rcPara;
		//pPara->m_rcBorder.top = nTop + nIndex * nPerHeight;
		//pPara->m_rcBorder.bottom = nTop + (nIndex + 1) * nPerHeight;

		pPara->SetBorder(m_rcPara);
		pPara->m_ptTopLeft.y = nTop + nIndex * nPerHeight;
		pPara->m_nHeight = nPerHeight;//nTop + (nIndex + 1) * nPerHeight;
	}
}

//2022-9-1  lijunqing
void CDrawParas::CalValue()
{
	POS pos = GetHeadPosition();
	CDrawPara* pPara = NULL;

	while (pos != NULL)
	{
		pPara = (CDrawPara*)GetNext(pos);
		pPara->CalValue();
	}
}
