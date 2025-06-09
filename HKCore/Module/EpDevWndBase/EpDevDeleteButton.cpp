// EpDevDeleteButton.cpp : 实现文件
//

#include "stdafx.h"
#include "EpDevDeleteButton.h"
#include "EpDevWnd.h"


// CEpDevDeleteButton

IMPLEMENT_DYNAMIC(CEpDevDeleteButton, CButton)

CEpDevDeleteButton::CEpDevDeleteButton()
{

}

CEpDevDeleteButton::~CEpDevDeleteButton()
{
}


BEGIN_MESSAGE_MAP(CEpDevDeleteButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CEpDevDeleteButton::OnBnClicked)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CEpDevDeleteButton 消息处理程序


void CEpDevDeleteButton::OnBnClicked()
{
	
}

void CEpDevDeleteButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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

int CEpDevDeleteButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pWindow = this;

	return 0;
}
