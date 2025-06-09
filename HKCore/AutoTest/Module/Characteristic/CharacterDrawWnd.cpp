// CharacterDrawWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "CharacterDrawWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCharacterDrawWnd

IMPLEMENT_DYNAMIC(CCharacterDrawWnd, CStatic)

CCharacterDrawWnd::CCharacterDrawWnd()
{
	m_pCharacterDrawView = NULL;
}

CCharacterDrawWnd::~CCharacterDrawWnd()
{
	if (m_pCharacterDrawView != NULL)
	{
		delete m_pCharacterDrawView;
		m_pCharacterDrawView = NULL;
	}
}


BEGIN_MESSAGE_MAP(CCharacterDrawWnd, CStatic)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CCharacterDrawWnd 消息处理程序



void CCharacterDrawWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	if (m_pCharacterDrawView != NULL)
	{
		if (m_pCharacterDrawView->HasDefChar())
		{
			m_pCharacterDrawView->Draw(&dc, 1, CPoint(0, 0));
			return;
		}
	}
	
	CRect rcClient;
	GetClientRect(&rcClient);
	dc.Rectangle(rcClient);	
}

void CCharacterDrawWnd::CreateCharacterDrawView()
{
	if (m_pCharacterDrawView == NULL)
	{
		m_pCharacterDrawView = new CCharacterDrawView();
	}

	m_pCharacterDrawView->UI_SetActiveElement(NULL);
}

BOOL CCharacterDrawWnd::HasCharDrawCreated(CCharacteristic *pCharTemp)
{
	if (m_pCharacterDrawView == NULL)
	{
		return FALSE;
	}

	return (m_pCharacterDrawView->HasDefChar(pCharTemp));
}

void CCharacterDrawWnd::InitCharacterDrawView(CCharacteristic *pCharTemp, BOOL bViewTestLines, BOOL bCalCharTemp)
{
// 	if (pCharTemp != NULL)
// 	{
// 		if (bCalCharTemp)
// 		{
// 			pCharTemp->CalCharElement(NULL);
// 		}
// 	}

	//创建m_pCharacterDrawView
	CreateCharacterDrawView();

	//XCreateElement：创建整个特性曲线的绘图对象，创建坐标系和绘图数据
	m_pCharacterDrawView->XCreateElement(pCharTemp, this, bViewTestLines, bCalCharTemp);

	CRect rcClient;
	GetClientRect(&rcClient);
	CDC *pDC = GetDC();
	m_pCharacterDrawView->SetBorder(rcClient, pDC);
	ReleaseDC(pDC);

	Invalidate(FALSE);
}


void CCharacterDrawWnd::InitCharacterDrawView(CCharacteristics *pChars, BOOL bViewTestLines, BOOL bCalCharTemp)
{
	CreateCharacterDrawView();
	m_pCharacterDrawView->XCreateElement(pChars, this, bViewTestLines, bCalCharTemp);

	CRect rcClient;
	GetClientRect(&rcClient);
	CDC *pDC = GetDC();
	m_pCharacterDrawView->SetBorder(rcClient, pDC);
	ReleaseDC(pDC);

	Invalidate(FALSE);
}

void CCharacterDrawWnd::SetActiveElement(CCharElement *pElement, BOOL bRedraw)
{
	if (m_pCharacterDrawView == NULL)
	{
		return;
	}

	if (pElement == NULL)
	{
		m_pCharacterDrawView->UI_SetActiveElement(NULL);
	}
	else
	{
		m_pCharacterDrawView->UI_SetActiveElement((CXDrawElement*)pElement->m_pDataRef);
	}

	if (bRedraw)
	{
		Invalidate(FALSE);
	}
}

void CCharacterDrawWnd::UpdateCurrTestPoint(double dX, double dY)
{
	m_pCharacterDrawView->UpdateCurrTestPoint(dX, dY);
	Invalidate(FALSE);
}

void CCharacterDrawWnd::FreeCurrTestPoint()
{
	m_pCharacterDrawView->FreeCurrTestPoint();
}

void CCharacterDrawWnd::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	if (!::IsWindow(m_hWnd))
	{
		return;
	}

	if (m_pCharacterDrawView == NULL)
	{
		return;
	}

	CRect rcBorder = m_pCharacterDrawView->GetBorder();

	if (rcBorder.Height() == cy && rcBorder.Width() == cx)
	{
		return;
	}

	CRect rcClient;
	GetClientRect(&rcClient);
	CDC *pDC = GetDC();
	m_pCharacterDrawView->SetBorder(rcClient, pDC);
	ReleaseDC(pDC);

	Invalidate(FALSE);
}
