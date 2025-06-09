#include "stdafx.h"
#include "WzdDlgComboBox.h"

IMPLEMENT_DYNAMIC(CWzdDlgComboBox, CComboBox)

CWzdDlgComboBox::CWzdDlgComboBox()
{
	m_crBorder = RGB(102, 209, 255);
}

CWzdDlgComboBox::~CWzdDlgComboBox()
{
}


void CWzdDlgComboBox::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	//ModifyStyle(0, CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS);
	CComboBox::PreSubclassWindow();
}

int CWzdDlgComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	int iComp = 0;
	ASSERT(lpCompareItemStruct->CtlType == ODT_COMBOBOX);
	LPCTSTR lpszText1 = (LPCTSTR) lpCompareItemStruct->itemData1;
	ASSERT(lpszText1 != NULL);
	LPCTSTR lpszText2 = (LPCTSTR) lpCompareItemStruct->itemData2;
	ASSERT(lpszText2 != NULL);

	if (NULL != lpszText1 && NULL != lpszText2)
	{
		iComp = _tcscmp(lpszText2, lpszText1);    
	}

	return iComp;
}

void CWzdDlgComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{

}

BEGIN_MESSAGE_MAP(CWzdDlgComboBox, CComboBox)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CWzdDlgComboBox::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CWzdDlgComboBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC* pDC = &dc;
	//绘制客户区
	CDC dMemDC;
	dMemDC.CreateCompatibleDC(pDC);
	dMemDC.SetMapMode(pDC->GetMapMode());

	CBitmap mNewBmp;
	CRect rc;
	GetClientRect(&rc);

	//画整个客户区域
 	mNewBmp.CreateCompatibleBitmap(pDC, rc.right - rc.left, rc.bottom - rc.top);
 	CBitmap* pOldBmp = dMemDC.SelectObject(&mNewBmp);
 	CPen pen(PS_SOLID,1,RGB(200,200,200));
 	CPen *pOldPen = dMemDC.SelectObject(&pen);
 	CBrush bkBrush;
 	bkBrush.CreateSolidBrush(m_crBorder);
 	dMemDC.SelectObject(&bkBrush);
 	dMemDC.Rectangle(rc);

	//画右边的三角形按钮
	CRect rcEnd(rc);
	rcEnd.left = rc.right - 20;
	CBrush bkBrushRect;
	bkBrushRect.CreateSolidBrush(m_crBorder);
	dMemDC.SelectObject(&bkBrushRect);
	dMemDC.Rectangle(rcEnd);
	//画三角形
	CRgn rgn;
	CPoint ptAngle[3];
	int angleSideWidth = 8;//三角形边长
	//第一个点的坐标
	ptAngle[0].x = rcEnd.left+rcEnd.Width()/2-angleSideWidth/2;
	ptAngle[0].y = rcEnd.top+rcEnd.Height()/2-2;
	//第二个点的坐标
	ptAngle[1].x = ptAngle[0].x + angleSideWidth;
	ptAngle[1].y = ptAngle[0].y;
	//第三个点的坐标
	ptAngle[2].x = rcEnd.left+rcEnd.Width()/2;
	ptAngle[2].y = ptAngle[0].y + 5;
	CBrush brushAngle;
	rgn.CreatePolygonRgn(ptAngle, 3, ALTERNATE); //创建区域  
	brushAngle.CreateSolidBrush(RGB(255,255,255)); //创建画刷
	dMemDC.FillRgn(&rgn, &brushAngle); //填充区域
	pDC->BitBlt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, &dMemDC,
		rc.left ,rc.top, SRCCOPY);

	//画选择时Label中的字符串
	CString strText;
	GetWindowText(strText);
	CRect rcText(rc);
	rcText.right = rc.right - 20;
 	rcText.top += 2;
 	rcText.bottom -= 2;
 	rcText.left += 2;
	CFont* pFont = GetParent()->GetFont();
	pDC->SelectObject(pFont);
	pDC->FillSolidRect(rcText, RGB(255,255,255));
	rcText.top += 2;
	rcText.left += 2;
	pDC->DrawText(strText, rcText, DT_VCENTER | DT_LEFT);

	//恢复
	dMemDC.SelectObject(pOldBmp);
	dMemDC.SelectObject(pOldPen);
	pOldPen->DeleteObject();
	pOldBmp->DeleteObject();
	dMemDC.DeleteDC();
	bkBrush.DeleteObject();
	bkBrushRect.DeleteObject();
	brushAngle.DeleteObject();

}