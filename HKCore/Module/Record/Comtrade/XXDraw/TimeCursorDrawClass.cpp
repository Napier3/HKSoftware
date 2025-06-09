// TimeCursorDrawClass.cpp: implementation of the CTimeCursorDrawClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TimeCursorDrawClass.h"

#include "..\..\API\GloblaDrawFunctions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimeCursorDrawClass::CTimeCursorDrawClass()
{
	m_crViewBK	=RGB(192,192,192);
	m_crArea	=RGB(255,192,192);
	InitIt();

	m_IDC_CURSOR_HAND = 0;
	m_IDC_CURSOR_MOVE = 0;
}

CTimeCursorDrawClass::~CTimeCursorDrawClass()
{
	EndIt();
}
void CTimeCursorDrawClass::InitIt()
{
	m_iActiveTimeLine=1;	//当前活动的时间线缺省为终止时间线
	m_iMoveEndTimeFlag=0;
	m_iCurrDrawTimeLineType=0;//
	m_crBeginLine=RGB(255,0,0);
	m_crEndLine=RGB(0,0,255);
	m_ulBeginLineType=m_ulEndLineType=PS_SOLID;
	m_nLineAreas=0;
	m_pRectLineArea=NULL;

	pParent				=NULL;				//父窗口指针
	m_rectOwnPosition	=CRect(0,0,500,20);
	m_rectTimeBtnArea	=CRect(50,2,450,18);	//时间光标的按钮的位置
	m_rectBeginTimeBtn	=CRect(0,4,0,16);	//起始时间光标按钮位置
	m_rectEndTimeBtn	=CRect(0,4,0,16);	//终止时间光标按钮位置
}
void CTimeCursorDrawClass::EndIt()
{
	if(m_pRectLineArea)delete m_pRectLineArea;m_pRectLineArea=NULL;
}
//同各通道的绘图区域进行绑定
void CTimeCursorDrawClass::SetLineAreaRects(int iAreas,CRect*pRect)
{
	EndIt();
	m_nLineAreas=iAreas;
	if(iAreas<=0)return;
	m_pRectLineArea=new CRect [iAreas];
	for(iAreas=0;iAreas<m_nLineAreas;iAreas++)
		m_pRectLineArea[iAreas]=pRect[iAreas];
	m_rectTimeBtnArea.left=m_pRectLineArea[0].left;
	m_rectTimeBtnArea.right=m_pRectLineArea[0].right;
	m_iBLinePtX=m_rectTimeBtnArea.left;
	m_iELinePtX=m_rectTimeBtnArea.right;
	GetTimeLineButton();
}
void CTimeCursorDrawClass::GetTimeLineButton()
{
	m_rectBeginTimeBtn.left=m_iBLinePtX-8;
	m_rectBeginTimeBtn.right=m_iBLinePtX+9;
	m_rectBeginTimeBtn.top=m_rectTimeBtnArea.top+2;
	m_rectBeginTimeBtn.bottom=m_rectTimeBtnArea.bottom-2;

	m_rectEndTimeBtn.left=m_iELinePtX-8;
	m_rectEndTimeBtn.right=m_iELinePtX+9;
	m_rectEndTimeBtn.top=m_rectTimeBtnArea.top+2;
	m_rectEndTimeBtn.bottom=m_rectTimeBtnArea.bottom-2;
}
void CTimeCursorDrawClass::Typeset(CSize size,long &lDrift)
{
	int iHeight=m_rectOwnPosition.Height();
	m_rectOwnPosition.left=0;
	m_rectOwnPosition.right=size.cx;
	m_rectOwnPosition.top=lDrift;
	lDrift=lDrift+iHeight; 
	m_rectOwnPosition.bottom=lDrift;
}
void CTimeCursorDrawClass::DrawIt(CDC*pDC)
{
	CBrush brush;
	brush.CreateSolidBrush(m_crViewBK);
	pDC->FillRect(m_rectOwnPosition,&brush);
	brush.DeleteObject();
	brush.CreateSolidBrush(m_crArea);
	pDC->FillRect(m_rectTimeBtnArea,&brush);
	brush.DeleteObject();
	Draw3dRectBorder(pDC,m_rectTimeBtnArea,1,RGB(128,128,128),RGB(255,255,255));

	DrawBeginTimeLine(pDC);
	DrawEndTimeLine(pDC);
}
void CTimeCursorDrawClass::DrawBeginTimeLine(CDC*pDC,BOOL b)
{
	if(m_iBLinePtX < m_rectTimeBtnArea.left)return;
	if(m_iBLinePtX > m_rectTimeBtnArea.right)return;

	CPoint pt;
	CPen pen,*pOldPen;
	pen.CreatePen(m_ulBeginLineType,1,m_crBeginLine);
	pOldPen=pDC->SelectObject(&pen);

	int index=0;
	for(index=0;index<m_nLineAreas;index++)
	{
		pDC->MoveTo(m_iBLinePtX,m_pRectLineArea[index].top);
		pDC->LineTo(m_iBLinePtX,m_pRectLineArea[index].bottom);
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	///////////绘制起始时间线的按钮
	CRect rect=m_rectBeginTimeBtn;
	Draw3dRectBorder(pDC,rect,1,RGB(128,128,128),RGB(128,128,128));
	CBrush	brush;
	rect.top+=1;rect.bottom-=0;	rect.left+=1;rect.right-=0;
	brush.CreateSolidBrush(RGB(192,192,192));
	pDC->FillRect(rect,&brush);
	brush.DeleteObject();
	
	rect.top+=2;rect.bottom-=2;	rect.left+=4;rect.right-=4;

	brush.CreateSolidBrush(m_crBeginLine);
	pDC->FillRect(rect,&brush);
	brush.DeleteObject();
}

void  CTimeCursorDrawClass::DrawEndTimeLine(CDC*pDC,BOOL b)
{
	if(m_iELinePtX < m_rectTimeBtnArea.left)return;
	if(m_iELinePtX > m_rectTimeBtnArea.right)return;

	CPoint pt;
	CPen pen,*pOldPen;
	pen.CreatePen(m_ulEndLineType,1,m_crEndLine);
	pOldPen=pDC->SelectObject(&pen);

	int index=0;
	for(index=0;index<m_nLineAreas;index++)
	{
		pDC->MoveTo(m_iELinePtX,m_pRectLineArea[index].top);
		pDC->LineTo(m_iELinePtX,m_pRectLineArea[index].bottom);
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	///////////绘制起始时间线的按钮
	CRect rect=m_rectEndTimeBtn;
	Draw3dRectBorder(pDC,rect,1,RGB(128,128,128),RGB(128,128,128));
	CBrush	brush;
	rect.top+=1;rect.bottom-=0;	rect.left+=1;rect.right-=0;
	brush.CreateSolidBrush(RGB(192,192,192));
	pDC->FillRect(rect,&brush);
	brush.DeleteObject();
	
	rect.top+=2;rect.bottom-=2;	rect.left+=4;rect.right-=4;

	brush.CreateSolidBrush(m_crEndLine);
	pDC->FillRect(rect,&brush);
	brush.DeleteObject();
}
void CTimeCursorDrawClass::EraseBeginTimeLine()			//erase the begin time line
{
	CRect rect=m_rectBeginTimeBtn;
	rect=rect+CRect(2,2,2,2);

	pParent->InvalidateRect(rect,0);

	rect.top=0;
	rect.left=m_iBLinePtX-1;rect.right=m_iBLinePtX+1;
	rect.bottom=m_pRectLineArea[m_nLineAreas-1].bottom;
	pParent->InvalidateRect(rect,0);
}
void CTimeCursorDrawClass::EraseEndTimeLine()			//erase the end time line;
{
	CRect rect=m_rectEndTimeBtn;
	rect=rect+CRect(2,2,2,2);

	pParent->InvalidateRect(rect,0);

	rect.top=0;;
	rect.left=m_iELinePtX-1;rect.right=m_iELinePtX+1;
	rect.bottom=m_pRectLineArea[m_nLineAreas-1].bottom;
	pParent->InvalidateRect(rect,0);
}

BOOL CTimeCursorDrawClass::OnMouseMoveTimeLines(CPoint point,CDC*pDC)
{
	BOOL bInPlace=FALSE;
	for(int index=0;index<m_nLineAreas;index++)
	{
		if(m_pRectLineArea[index].PtInRect(point))
		{
			bInPlace=TRUE;
			break;
		}
	}
	if(!bInPlace)
	{
		if(m_rectBeginTimeBtn.PtInRect(point))bInPlace=TRUE;	//是否位于终止时间按钮内
	}
	if(!bInPlace)
	{
		if(m_rectEndTimeBtn.PtInRect(point))bInPlace=TRUE;	//是否位于起始时间按钮内
	}
	
	int iLen=abs(point.x-m_iELinePtX);
	if(m_iMoveEndTimeFlag==0)
		m_iCurrDrawTimeLineType=0;
	if(m_iMoveEndTimeFlag==0)
	{//没有直线处于被移动状态，
		if(iLen<=4)
		{
			if(bInPlace)
			{
				if(m_rectEndTimeBtn.PtInRect(point) )//|| point.y<m_rectWave.top)
				{
					::SetCursor(AfxGetApp()->LoadCursor(m_IDC_CURSOR_HAND));
				}
				else
				{
					::SetCursor(AfxGetApp()->LoadCursor(m_IDC_CURSOR_MOVE));
				}
				m_iCurrDrawTimeLineType=1;	//endtime
			}
		}
		if(m_iCurrDrawTimeLineType!=1)
		{
			iLen=abs(point.x-m_iBLinePtX);
			if(iLen<=4)
			{
				if(bInPlace)
				{
					if(m_rectBeginTimeBtn.PtInRect(point) )//|| point.y<m_rectWave.top)
						::SetCursor(AfxGetApp()->LoadCursor(m_IDC_CURSOR_HAND));
					else
						::SetCursor(AfxGetApp()->LoadCursor(m_IDC_CURSOR_MOVE));
					m_iCurrDrawTimeLineType=2;	//begin time
				}
			}
		}
	}
	else
	{
		if(m_rectBeginTimeBtn.PtInRect(point) || m_rectEndTimeBtn.PtInRect(point) )// || point.y<m_rectWave.top)
			::SetCursor(AfxGetApp()->LoadCursor(m_IDC_CURSOR_HAND));
		else
			::SetCursor(AfxGetApp()->LoadCursor(m_IDC_CURSOR_MOVE));
		if(m_iCurrDrawTimeLineType==1)
		{
			//搽除原来的时间线
			EraseEndTimeLine();
		}
		else
		{
			////搽除原来的时间线
			EraseBeginTimeLine();
		}
	
		if(m_iCurrDrawTimeLineType==1)
		{
			m_iELinePtX=point.x;
			GetTimeLineButton();
			//DrawEndTimeLine(pDC);
			EraseEndTimeLine();
			m_iActiveTimeLine=1;
		}
		else
		{
			m_iBLinePtX=point.x;
			GetTimeLineButton();
			//DrawBeginTimeLine(pDC);
			EraseBeginTimeLine();
			m_iActiveTimeLine=2;
		}
		//处理鼠标移动的结果的函数在此调用
	}
	if(m_iCurrDrawTimeLineType)
		return TRUE;
	else
		return FALSE;
}
BOOL CTimeCursorDrawClass::OnTimeLineClick(CPoint point,CDC*pDC)
{
	int iLen=abs(point.x-m_iELinePtX);
	HCURSOR hCursor;	
	if(iLen<=4)
	{
		if(m_iCurrDrawTimeLineType)
		{
			m_iMoveEndTimeFlag	= 1;
			if(m_rectEndTimeBtn.PtInRect(point) )//|| point.y<m_rectWave.top)
				hCursor=AfxGetApp()->LoadCursor(m_IDC_CURSOR_HAND);
			else
				hCursor=AfxGetApp()->LoadCursor(m_IDC_CURSOR_MOVE);
			::SetCursor(hCursor);
			return TRUE;
		}
	}
	iLen=abs(point.x-m_iBLinePtX);
	if(iLen<=4)
	{
		if(m_iCurrDrawTimeLineType)
		{
			m_iMoveEndTimeFlag	= 1;
			if(m_rectBeginTimeBtn.PtInRect(point) )//|| point.y<m_rectWave.top)
				hCursor=AfxGetApp()->LoadCursor(m_IDC_CURSOR_HAND);
			else
				hCursor=AfxGetApp()->LoadCursor(m_IDC_CURSOR_MOVE);
			::SetCursor(hCursor);
			return TRUE;
		}
	}
	m_iMoveEndTimeFlag=0;
	return FALSE;
}

BOOL CTimeCursorDrawClass::OnMouseMove(CPoint point,CDC*pDC,CPoint ptScroll)
{
	if(m_nLineAreas<=0)return FALSE;
	if(point.x<m_rectTimeBtnArea.left || point.x>m_rectTimeBtnArea.right)return FALSE;
	return OnMouseMoveTimeLines(point,pDC);
}
BOOL CTimeCursorDrawClass::OnLButtonDown(CPoint point,CDC*pDC)
{
	if(m_nLineAreas<=0)return FALSE;
	return OnTimeLineClick(point,pDC);
}
BOOL CTimeCursorDrawClass::OnLButtonUp(CPoint point,CDC*pDC)
{
	m_iMoveEndTimeFlag=0;
	m_iCurrDrawTimeLineType=0;
	return TRUE;
}
BOOL CTimeCursorDrawClass::IsPointInRestList(CPoint point)
{
	BOOL bTrue=FALSE;
	int index=0;
	for(index=0;index<m_nLineAreas;index++)
	{
		bTrue=m_pRectLineArea[index].PtInRect(point);
		if(bTrue)break;
	}
	return bTrue;
}
CRect CTimeCursorDrawClass::GetMaxRectArea()
{
	CRect rect=CRect(0,0,0,0);
	if(m_nLineAreas<=0)return rect;
	int index=0;
	rect=m_pRectLineArea[index];
	for(index=0;index<m_nLineAreas;index++)
	{
		if(rect.bottom<m_pRectLineArea[index].bottom)
			rect.bottom=m_pRectLineArea[index].bottom;
	}
	return rect;
}