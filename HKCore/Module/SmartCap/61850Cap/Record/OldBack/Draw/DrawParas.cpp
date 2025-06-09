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
	 m_oParaFont.CreateFontIndirect(&MrDraw::g_lfDrawPara);
	 m_oCalPara.pRtChAttrVal = &m_oParaValue;
	 m_ptBegin.x		= 0;
	 m_ptBegin.y		= 0;
	 m_nParaPosToCursor	= 0; 
	 m_crColor          = RGB(124,153,226);
	 
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
// 	long nLen = m_oCalPara.nDataLength ;
	
	if (Amount < 1 /*|| nLen < 1*/)
	{
		return;
	}

	int nMode = pDC->SetBkMode(TRANSPARENT);
	POS pos = GetHeadPosition();
	CDrawPara* pPara = NULL;

	COLORREF crText = pDC->SetTextColor(RGB(255, 255, 255));
	CPen Pen(PS_SOLID,1,RGB(255, 255, 255));
	CPen* pOldPen = pDC->SelectObject(&Pen);

	while (pos != NULL) 
	{
		pPara = (CDrawPara*)GetNext(pos);
		pPara->Draw(pDC);
	}

	pDC->SetTextColor(crText);
	pDC->SelectObject(pOldPen);
	pOldPen  = NULL;
	Pen.DeleteObject();

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
	BitmapDC.FillSolidRect(0,0,nWidth,nHeight,m_crColor);
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
}

void CDrawParas::AddPara(UINT nID)
{
	CDrawPara* pNew = NULL;
	pNew = CreateNewPara(nID);
	pNew->Init(nID,m_strUnit,&m_oCalPara,&m_oParaFont);
	AddTail(pNew);
	//链表是一个固定顺序的
// 	POS pos = GetHeadPosition();
// 	CDrawPara* pObj = (CDrawPara*)GetAt(pos);
// 	CDrawPara* pNew = NULL;
// 	
// 	BOOL bInserted = FALSE;
// 	POS pPre = NULL;//上一个节点
// 	
// 	while(pos != NULL)//遍历链表，是插入，还是已经有的
// 	{
// 		pPre = pos;
// 		pObj = (CDrawPara*)GetNext(pos);
// 		UINT nParaID = pObj->m_nParaID;
// 		
// 		if(nID < nParaID ) 
// 		{
// 			pNew = CreateNewPara(nID);
// 			InsertBefore(pPre,pNew);
// 			bInserted = TRUE;
// 			break;	
// 		}
// 		else if(nID == nParaID )
// 		{
// 			bInserted = TRUE;
// 			break;	
// 		}
// 		else
// 		{
// 		}
// 	}
// 	
// 	if (!bInserted)
// 	{
// 		pNew = CreateNewPara(nID);
// 		AddTail(pNew);
// 	}
// 
// 	if (pNew != NULL)
// 	{
// 		pNew->Init(nID,m_strUnit,&m_oCalPara,&m_oParaFont);
// 	}
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
// 	long nTop = nYCenter - nTotalHeight ;
// 	long nBom = nYCenter ;

// 	m_rcPara.top = nTop;
// 	m_rcPara.bottom = nBom;
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

// 	if (nTop < m_rcClip.top)
// 	{
// 		m_rcPara.top = m_rcClip.top;
// 		m_rcPara.bottom = m_rcClip.top + nTotalHeight;
// 	}
// 
// 	if (nBom > m_rcClip.bottom)
// 	{
// 		m_rcPara.bottom = m_rcClip.bottom;
// 		m_rcPara.top = m_rcClip.bottom - nTotalHeight;
// 	}
	
	m_rcBorder = m_rcPara;

	SetParaRect(m_rcPara);
}

void CDrawParas::SetClipRect(CRect rect)
{
	m_rcClip = rect;
}

CDrawPara* CDrawParas::CreateNewPara(UINT nID)
{
	CDrawPara* pNew = NULL;
	pNew = new CDrawMultiPara();
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
		pPara->m_rcBorder = m_rcPara;
		pPara->m_rcBorder.top = nTop + nIndex * nPerHeight;
		pPara->m_rcBorder.bottom = nTop + (nIndex + 1) * nPerHeight;
	}
}
