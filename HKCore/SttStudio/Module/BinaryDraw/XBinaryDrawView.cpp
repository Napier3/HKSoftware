//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewIedCfg.cpp  CXScdDrawViewIedCfg


#include "stdafx.h"
#include "XBinaryDrawView.h"


CXBinaryDrawView::CXBinaryDrawView()
{
	m_pBinarysDraw = NULL;
	//初始化属性

	//初始化成员变量
}

CXBinaryDrawView::~CXBinaryDrawView()
{
}

void CXBinaryDrawView::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	if (m_pBinarysDraw == NULL)
	{
		return;
	}

	CXDrawViewBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}

CSize CXBinaryDrawView::Layout(CPoint &ptTopLeft)
{
	vm_draw_init_binary_font();

	if (m_pBinarysDraw == NULL)
	{
		return CSize(m_nWidth, m_nHeight);
	}

	long nBinaryWidth = vm_binary_get_width();
	long nBinaryHeight = vm_binary_get_height();
	long nCols = binary_draw_cal_cols(m_nWidth, nBinaryWidth);

	long nIndex = 0;

	POS pos = m_pBinarysDraw->GetHeadPosition();
	CXBinaryDrawBase *pBinaryDraw = NULL;

	while (pos != NULL)
	{
		pBinaryDraw = (CXBinaryDrawBase *)m_pBinarysDraw->GetNext(pos);
		pBinaryDraw->Layout(ptTopLeft);

		ptTopLeft.x += nBinaryWidth;
		nIndex++;
	
		if (nIndex >= nCols)
		{
			nIndex=0;
			ptTopLeft.y += nBinaryHeight;
			ptTopLeft.x = 0;
		}
	}

	m_nWidth = nCols * nBinaryWidth;
	m_nHeight = ptTopLeft.y + nBinaryHeight;

	m_pBinarysDraw->m_nWidth = m_nWidth;
	m_pBinarysDraw->m_nHeight = m_nHeight;

	return CSize(m_nWidth, ptTopLeft.x + nBinaryHeight);
}

CSize CXBinaryDrawView::CalLayout(CSize &szDraw)
{
	if (m_pBinarysDraw != NULL)
	{
		m_pBinarysDraw->CalLayout(szDraw);
	}

	return szDraw;
}

void CXBinaryDrawView::BinarysDraw(CDC *pDC)
{
	Draw(pDC, 1, CPoint(0, 0), 0xFFFFFFFF);
}
