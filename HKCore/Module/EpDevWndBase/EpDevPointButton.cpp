// D:\WorkLiJQ\Source\Module\EpDevWndBase\EpDevPointButton.cpp : 实现文件
//

#include "stdafx.h"
#include "EpDevPointButton.h"
#include "EpDevWnd.h"


// CEpDevPointButton

IMPLEMENT_DYNAMIC(CEpDevPointButton, CButton)

CEpDevPointButton::CEpDevPointButton()
{
}

CEpDevPointButton::~CEpDevPointButton()
{
}


BEGIN_MESSAGE_MAP(CEpDevPointButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CEpDevPointButton::OnBnClicked)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CEpDevPointButton 消息处理程序


long CEpDevPointButton::Expand(long nExpand)
{
	nExpand = CEpDevPoint::Expand(nExpand);
	Invalidate();
	return nExpand;
}

void CEpDevPointButton::SetExpand(long nExpand/* =EPDES_EXPAND */)
{
	Invalidate();
	BeginWaitCursor();
	Expand(nExpand);
	CWnd* pWnd = CWnd::GetParent()->GetParent();
	pWnd->SendMessage(WM_DEV_WND_SIZE_CHANGED, (WPARAM)this, (LPARAM)nExpand);
	EndWaitCursor();
}

CPoint CEpDevPointButton::GetConnectPoint()
{
	CRect rect;
	GetWindowRect(&rect);
	CWnd* pParent = CWnd::GetParent()->GetParent();
	pParent->ScreenToClient(rect);

	CPoint ptRet(0,0);
	ptRet.x = rect.right + 3;
	ptRet.y = rect.top + rect.Height()/2;

	return ptRet;
}

void CEpDevPointButton::Show(UINT nShow)
{
	CEpDevWnd* pDevWnd = (CEpDevWnd*)CEpDevBase::GetParent();
	ASSERT(pDevWnd != NULL);
	
	if(pDevWnd == NULL)
	{
		return;
	}
	
	//如果自身是展开的且父窗口也是展开的
	if(m_bExpand && pDevWnd->IsExpand())
	{
		ShowChildren(nShow);
	}
	else
	{
		ShowChildren(EPDES_HIDE);
	}
}

void CEpDevPointButton::OnBnClicked()
{
	m_bExpand = !m_bExpand;
	SetExpand(m_bExpand);
}

void CEpDevPointButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC); 

	CRect rect;
	GetClientRect(&rect);
	pDC->Rectangle(rect);

	CPoint pt1,pt2,pt3,pt4;
	pt1 = CPoint(rect.left+2,rect.CenterPoint().y);
	pt2 = CPoint(rect.right-2,rect.CenterPoint().y);
	pt3 = CPoint(rect.CenterPoint().x,rect.top+2);
	pt4 = CPoint(rect.CenterPoint().x,rect.bottom-2);

	pDC->MoveTo(pt1);
	pDC->LineTo(pt2);

	if(m_bExpand)
	{
		//画减号
	}
	else
	{
		//画加号
		pDC->MoveTo(pt3);
		pDC->LineTo(pt4);
	}
}

int CEpDevPointButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pWindow = this;

	return 0;
}
