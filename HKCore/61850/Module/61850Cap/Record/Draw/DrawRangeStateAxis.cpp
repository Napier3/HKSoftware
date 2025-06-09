// DrawRangeStateAxis.cpp: implementation of the CDrawRangeStateAxis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawRangeStateAxis.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawRangeStateAxis::CDrawRangeStateAxis()
{
	m_pAttachDraw	= NULL;
	m_nActiveState = 0;
	m_nRangeStateAxisType = RANGESTATEAXIS_TYPE_VERT;
	m_rcBlockHead1 = CRect(0,0,0,0);
	m_rcBlockHead2 = CRect(0,0,0,0);
	m_rcBlockCenter = CRect(0,0,0,0);
	BackPosition();
	m_nStateAxisOptrState = RANGESTATEAXIS_NONE;
	m_hArrowCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hMoveCursor = m_hArrowCursor;
	m_hZoomCursor = m_hArrowCursor;
	m_hProhitiCursor = m_hArrowCursor;
	m_nBlockID = RANGESTATEAXIS_BLOCK_NONE;
	m_pClipRect = NULL;
	m_bLockHead = TRUE;
	m_nMinLength = RANGESTATEAXIS_MIN_LENGTH;
	m_bFrozenHead1 = FALSE;
	m_bFrozenHead2 = FALSE;
	m_bFrozenCenter = FALSE;
	m_crFrozenColor = RGB(240, 240, 240);
	m_bSetCapture = FALSE;

	m_ptBlockHead1		 = CPoint(0,0);
	m_ptBlockHead2		 = CPoint(0,0);
	m_ptBlockCenter		 = CPoint(0,0);
	m_ptOldBlockHead1	 = CPoint(0,0);  
	m_ptOldBlockHead2	 = CPoint(0,0);
	m_ptOldBlockCenter	 = CPoint(0,0);
	m_ptOriginBlockHead1 = CPoint(0,0);
	m_ptOriginBlockHead2 = CPoint(0,0);
}

void CDrawRangeStateAxis::BackPosition()
{
	m_ptOldBlockHead1     = m_ptBlockHead1;
	m_ptOldBlockHead2     = m_ptBlockHead2;
	m_ptOldBlockCenter    = m_ptBlockCenter;
}

void CDrawRangeStateAxis::RestorePosition()
{
	m_ptBlockHead1    = m_ptOldBlockHead1;
	m_ptBlockHead2    = m_ptOldBlockHead2;
	m_ptBlockCenter   = m_ptOldBlockCenter;	
}

CDrawRangeStateAxis::~CDrawRangeStateAxis()
{
	if (m_pClipRect != NULL)
	{
		delete m_pClipRect;
		m_pClipRect = NULL;
	}
}

void CDrawRangeStateAxis::SetClipRect(const CRect &rcClip)
{
	if (m_pClipRect == NULL)
	{
		m_pClipRect = new CRect();
	}

	*m_pClipRect = rcClip;
}

void CDrawRangeStateAxis::SetBorder(const CRect &rcBorder)
{
	CDrawBase::SetBorder(rcBorder);
	AdjustRangeStateAxis();	
	m_ptOriginBlockHead1 = m_ptBlockHead1;
	m_ptOriginBlockHead2 = m_ptBlockHead2;
}

void CDrawRangeStateAxis::SetBorder(const CRect &rcBorder, UINT nType)
{
	CDrawBase::SetBorder(rcBorder);
	ASSERT(nType == RANGESTATEAXIS_TYPE_HORZ || nType == RANGESTATEAXIS_TYPE_VERT);
	m_nRangeStateAxisType = nType;
	AdjustRangeStateAxis();
	m_ptOriginBlockHead1 = m_ptBlockHead1;
	m_ptOriginBlockHead2 = m_ptBlockHead2;
}

void CDrawRangeStateAxis::ExpandBorder(long &l, long &t, long &r, long &b)
{
	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_VERT)
	{
		l = 0;
		r = 0;
	}
	else
	{
		t = 0;
		b = 0;
	}

	CDrawBase::ExpandBorder(l, t, r, b);	
	AdjustRangeStateAxis();
}

void CDrawRangeStateAxis::SetRangeStateAxisType(UINT nType)
{
	ASSERT(nType == RANGESTATEAXIS_TYPE_HORZ || nType == RANGESTATEAXIS_TYPE_VERT);
	
	m_nRangeStateAxisType = nType;
	AdjustRangeStateAxis();
}

void CDrawRangeStateAxis::Offset(long &x, long &y)
{
	m_ptBlockHead1.Offset(x, y);
	m_ptBlockHead2.Offset(x, y);
	m_ptBlockCenter.Offset(x, y);
}

void CDrawRangeStateAxis::ModifyBlock_Move(long &x, long &y)
{
	//更改位置
	RestorePosition();
	Offset(x, y);
	
	if (m_pClipRect != NULL)
	{//有限制的区域
		if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
		{//水平坐标
			if (m_ptBlockHead1.x < m_pClipRect->left)
			{//超出左边范围，移动到限制区域最左边
				x = m_pClipRect->left - m_ptOldBlockHead1.x;
			}
			
			if (m_ptBlockHead2.x > m_pClipRect->right)
			{//超出右边范围，移到限制区域最右边
				x = m_pClipRect->right - m_ptOldBlockHead2.x;
			}
		}
		else
		{//纵向座标
			if (m_ptBlockHead1.y < m_pClipRect->top)
			{//超出上边范围，移动到限制区域最上边
				y = m_pClipRect->top - m_ptOldBlockHead1.y;
			}
			
			if (m_ptBlockHead2.y > m_pClipRect->bottom)
			{//超出下边范围，移动到限制区域最下边
				y = m_pClipRect->bottom - m_ptOldBlockHead2.y;
			}
		}
	}
	
	//更改位置
	RestorePosition();
	Offset(x, y);
	InitBlockRect();
}

void CDrawRangeStateAxis::ModifyBlock_ZoomClip(long &x, long &y)
{
	if (m_pClipRect == NULL)
	{
		return;
	}
	
	long x1=x, y1=y;
	long x2=x, y2=y;

	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		if (m_nBlockID == RANGESTATEAXIS_BLOCK_HEAD1)
		{
			if (m_ptBlockHead1.x < m_pClipRect->left)
			{//正向移出
				x1 = m_pClipRect->left - m_ptOldBlockHead1.x;
			}
			
			if (m_ptBlockHead1.x > m_pClipRect->right)
			{//反向移出
				x1 = m_pClipRect->right - m_ptOldBlockHead1.x;
			}
			
			if (m_ptBlockHead2.x < m_pClipRect->left)
			{//正向移出
				x2 = m_ptOldBlockHead2.x - m_pClipRect->left;
			}
			
			if (m_ptBlockHead2.x > m_pClipRect->right)
			{//反向移出
				x2 = m_ptOldBlockHead2.x - m_pClipRect->right;
			}
		}
		else
		{
			if (m_ptBlockHead1.x < m_pClipRect->left)
			{//正向移出
				x1 = m_ptOldBlockHead1.x - m_pClipRect->left;
			}
			
			if (m_ptBlockHead1.x > m_pClipRect->right)
			{//反向移出
				x1 = m_ptOldBlockHead1.x - m_pClipRect->right;
			}
			
			if (m_ptBlockHead2.x < m_pClipRect->left)
			{//正向移出
				x2 = m_pClipRect->left - m_ptOldBlockHead2.x;
			}
			
			if (m_ptBlockHead2.x > m_pClipRect->right)
			{//反向移出
				x2 = m_pClipRect->right - m_ptOldBlockHead2.x;
			}
		}
	}
	else
	{
		if (m_nBlockID == RANGESTATEAXIS_BLOCK_HEAD1)
		{
			if (m_ptBlockHead1.y < m_pClipRect->top)
			{//正向移出
				y1 = m_pClipRect->top - m_ptOldBlockHead1.y;
			}
			
			if (m_ptBlockHead1.y > m_pClipRect->bottom)
			{//反向移出
				y1 = m_pClipRect->bottom - m_ptOldBlockHead1.y;
			}

			if (m_ptBlockHead2.y < m_pClipRect->top)
			{//正向移出
				y2 = m_ptOldBlockHead2.y - m_pClipRect->top;
			}
			
			if (m_ptBlockHead2.y > m_pClipRect->bottom)
			{//反向移出
				y2 = m_ptOldBlockHead2.y - m_pClipRect->bottom;
			}
		}
		else
		{
			if (m_ptBlockHead1.y < m_pClipRect->top)
			{//正向移出
				y1 = m_ptOldBlockHead1.y - m_pClipRect->top;
			}
			
			if (m_ptBlockHead1.y > m_pClipRect->bottom)
			{//反向移出
				y1 = m_ptOldBlockHead1.y - m_pClipRect->bottom;
			}

			if (m_ptBlockHead2.y < m_pClipRect->top)
			{//正向移出
				y2 = m_pClipRect->top - m_ptOldBlockHead2.y;
			}
			
			if (m_ptBlockHead2.y > m_pClipRect->bottom)
			{//反向移出
				y2 = m_pClipRect->bottom - m_ptOldBlockHead2.y;
			}
		}
	}

	if (abs(x1) > abs(x2))
	{
		x = x2;
	}
	else
	{
		x = x1;
	}

	if (abs(y1) > abs(y2))
	{
		y = y2;
	}
	else
	{
		y = y1;
	}
}

void CDrawRangeStateAxis::ModifyBorder_Move(long &x, long &y)
{
	ModifyBlock_Move(x, y);
	Move(x, y);

	if (m_pAttachDraw != NULL)
	{
		m_pAttachDraw->Move(x, y);	
	}
}

void CDrawRangeStateAxis::ModifyBorder_Zoom(long &x, long &y)
{
	ModifyBlock_Zoom(x, y);

	long x2 = x;
	long y2 = y;

	if (m_nBlockID == RANGESTATEAXIS_BLOCK_HEAD1)
	{
		x = -x;
		y = -y;
		x2 = x;
		y2 = y;

		if (!m_bLockHead)
		{
			x2 = 0;
			y2 = 0;
		}
		
		ModifyBorder_ZoomClipByMinLength(x, y, x2, y2);
		AdjustBlcockHead();
		
		x = m_ptOldBlockHead1.x - m_ptBlockHead1.x;
		x2 = m_ptBlockHead2.x - m_ptOldBlockHead2.x;
		y = m_ptOldBlockHead1.y - m_ptBlockHead1.y;
		y2 = m_ptBlockHead2.y - m_ptOldBlockHead2.y;

		
		if (m_pAttachDraw != NULL)
		{
			m_pAttachDraw->ExpandBorder(x, y, x2, y2);
		}
	}
	else//RANGESTATEAXIS_BLOCK_HEAD2
	{
		x2 = x;
		y2 = y;
		
		if (!m_bLockHead)
		{
			x = 0;
			y = 0;
		}
		
		ModifyBorder_ZoomClipByMinLength(x, y, x2, y2);
		AdjustBlcockHead();

		x = m_ptOldBlockHead1.x - m_ptBlockHead1.x;
		x2 = m_ptBlockHead2.x - m_ptOldBlockHead2.x;
		y = m_ptOldBlockHead1.y - m_ptBlockHead1.y;
		y2 = m_ptBlockHead2.y - m_ptOldBlockHead2.y;
		
		if (m_pAttachDraw != NULL)
		{
			m_pAttachDraw->ExpandBorder(x, y, x2, y2);
		}
	}
}

void CDrawRangeStateAxis::AdjustBlcockHead()
{
	long nTemp = 0;

	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_VERT)
	{
		if (m_ptBlockHead1.y > m_ptBlockHead2.y)
		{
			nTemp = m_ptBlockHead1.y;
			m_ptBlockHead1.y = m_ptBlockHead2.y;
			m_ptBlockHead2.y = nTemp;
			m_ptBlockCenter.y = (m_ptBlockHead1.y + m_ptBlockHead2.y) / 2;
		}
	}
	else
	{
		if (m_ptBlockHead1.x > m_ptBlockHead2.x)
		{
			nTemp = m_ptBlockHead1.x;
			m_ptBlockHead1.x = m_ptBlockHead2.x;
			m_ptBlockHead2.x = nTemp;
			m_ptBlockCenter.x = (m_ptBlockHead1.x + m_ptBlockHead2.x) / 2;
		}
	}
	
	long nLen = m_nMinLength / 2;

	if (m_bLockHead)
	{
		if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
		{//水平标尺
			if (abs(m_ptBlockHead1.x - m_ptBlockHead2.x) < m_nMinLength)
			{
				//锁定Head，从中心位置往两边扩展
				m_ptBlockHead1.x = m_ptBlockCenter.x - nLen;
				m_ptBlockHead2.x = m_ptBlockCenter.x + nLen;
			}
		}
		else
		{//垂直标尺
			if (abs(m_ptBlockHead1.y - m_ptBlockHead2.y) < m_nMinLength)
			{
				//锁定Head，从中心位置往两边扩展
				m_ptBlockHead1.y = m_ptBlockCenter.y - nLen;
				m_ptBlockHead2.y = m_ptBlockCenter.y + nLen;
			}
		}
	}
	else
	{
		if (m_nBlockID == RANGESTATEAXIS_BLOCK_HEAD1)
		{//move head1
			if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
			{//水平标尺
				//小于最小长度
				if (abs(m_ptBlockHead1.x - m_ptBlockHead2.x) < m_nMinLength)
				{
					m_ptBlockHead1.x  = m_ptBlockHead2.x - m_nMinLength;
				}
			}
			else
			{//垂直标尺
				if (abs(m_ptBlockHead1.y - m_ptBlockHead2.y) < m_nMinLength)
				{
					m_ptBlockHead1.y  = m_ptBlockHead2.y - m_nMinLength;
				}
			}
		}
		else
		{//move head2
			if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
			{//水平标尺
				//小于最小长度
				if (abs(m_ptBlockHead1.x - m_ptBlockHead2.x) < m_nMinLength)
				{
					m_ptBlockHead2.x  = m_ptBlockHead1.x + m_nMinLength;
				}
			}
			else
			{//垂直标尺
				if (abs(m_ptBlockHead1.y - m_ptBlockHead2.y) < m_nMinLength)
				{
					m_ptBlockHead2.y  = m_ptBlockHead1.y + m_nMinLength;
				}
			}
		}
	}

	m_ptBlockCenter.y = (m_ptBlockHead1.y + m_ptBlockHead2.y) / 2;
	m_ptBlockCenter.x = (m_ptBlockHead1.x + m_ptBlockHead2.x) / 2;
				
	InitBlockRect();
}

void CDrawRangeStateAxis::ModifyBlock_MinRect()
{
	if (m_pClipRect == NULL)
	{
		return;
	}

	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		if (m_rcBorder.Width() < RANGESTATEAXIS_MIN_LENGTH)
		{
			if (m_rcBorder.left == m_pClipRect->left)
			{
				m_rcBorder.right = m_rcBorder.left + RANGESTATEAXIS_MIN_LENGTH;
			}
			
			if (m_rcBorder.right == m_pClipRect->right)
			{
				m_rcBorder.left = m_rcBorder.right - RANGESTATEAXIS_MIN_LENGTH;
			}
		}
	}
	else
	{
		if (m_rcBorder.Height() < RANGESTATEAXIS_MIN_LENGTH)
		{
			if (m_rcBorder.top == m_pClipRect->top)
			{
				m_rcBorder.bottom = m_rcBorder.top + RANGESTATEAXIS_MIN_LENGTH;
			}
			
			if (m_rcBorder.bottom == m_pClipRect->bottom)
			{
				m_rcBorder.top = m_rcBorder.bottom - RANGESTATEAXIS_MIN_LENGTH;
			}
		}
	}
}


void CDrawRangeStateAxis::ModifyBlock_Zoom(long &x, long &y)
{
	RestorePosition();
	
	if (m_nBlockID == RANGESTATEAXIS_BLOCK_HEAD1)
	{
		m_ptBlockHead1.Offset(x, y);

		if (m_bLockHead)
		{
			m_ptBlockHead2.Offset(-x, -y);
		}

		ModifyBlock_ZoomClip(x, y);
	}
	else
	{
		if (m_bLockHead)
		{
			m_ptBlockHead1.Offset(-x, -y);
		}

		m_ptBlockHead2.Offset(x, y);

		ModifyBlock_ZoomClip(x, y);
	}

	//更改位置
	RestorePosition();

	if (m_nBlockID == RANGESTATEAXIS_BLOCK_HEAD1)
	{
		m_ptBlockHead1.Offset(x, y);

		if (m_bLockHead)
		{
			m_ptBlockHead2.Offset(-x, -y);
		}
	}
	else
	{
		if (m_bLockHead)
		{
			m_ptBlockHead1.Offset(-x, -y);
		}
		
		m_ptBlockHead2.Offset(x, y);
	}
	
	if (!m_bLockHead)
	{
		m_ptBlockCenter.x = (m_ptBlockHead1.x + m_ptBlockHead2.x) / 2;
		m_ptBlockCenter.y = (m_ptBlockHead1.y + m_ptBlockHead2.y) / 2;		
	}

	InitBlockRect();
}

void CDrawRangeStateAxis::ModifyBorder_ZoomClipByMinLength(long &x, long &y, long &x2, long &y2)
{
	CPoint pt1, pt2;
	long nLen = 0;

	if (m_bLockHead)
	{
		if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
		{//水平标尺
			if (abs(m_ptBlockHead1.x - m_ptBlockHead2.x) < m_nMinLength)
			{
				//锁定Head，从中心位置往两边扩展
				nLen = m_nMinLength / 2;
				x  = m_ptOldBlockHead1.x - (m_ptOldBlockCenter.x - nLen);
				x2 = (m_ptOldBlockCenter.x + m_nMinLength - nLen) - m_ptOldBlockHead2.x;
			}
		}
		else
		{//垂直标尺
			if (abs(m_ptBlockHead1.y - m_ptBlockHead2.y) < m_nMinLength)
			{
				//锁定Head，从中心位置往两边扩展
				nLen = m_nMinLength / 2;
				y  = m_ptOldBlockHead1.y - (m_ptOldBlockCenter.y - nLen);
				y2 = (m_ptOldBlockCenter.y + m_nMinLength - nLen) - m_ptOldBlockHead2.y;
			}
		}
	}
	else
	{
		if (m_nBlockID == RANGESTATEAXIS_BLOCK_HEAD1)
		{//move head1
			if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
			{//水平标尺
				//小于最小长度
				if (abs(m_ptBlockHead1.x - m_ptBlockHead2.x) < m_nMinLength)
				{
					if (m_ptBlockHead1.x < m_ptBlockHead2.x)
					{//####### OK #######
						//移动Head1，Head1在Head2左边，从Head2往左边计算
						x  = m_nMinLength + m_ptOldBlockHead1.x - m_ptBlockHead2.x;
					}
					else//####### OK #######
					{//移动Head1，Head1在Head2右边，从Head1往左边计算
						//固定Head1，移动Head2，即从Head1往左边计算
						x2  = m_ptBlockHead1.x - m_nMinLength - m_ptOldBlockHead2.x;
					}
				}
			}
			else
			{//垂直标尺
				if (abs(m_ptBlockHead1.y - m_ptBlockHead2.y) < m_nMinLength)
				{
					if (m_ptBlockHead1.y < m_ptBlockHead2.y)
					{//####### OK #######
						//移动Head1，Head1在Head2左边，从Head2往左边计算
						y  = m_nMinLength + m_ptOldBlockHead1.y - m_ptBlockHead2.y;
					}
					else//####### OK #######
					{//移动Head1，Head1在Head2右边，从Head1往左边计算
						//固定Head1，移动Head2，即从Head1往左边计算
						y2  = m_ptBlockHead1.y - m_nMinLength - m_ptOldBlockHead2.y;
					}
				}
			}
		}
		else
		{//move head2
			if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
			{//水平标尺
				//小于最小长度
				if (abs(m_ptBlockHead1.x - m_ptBlockHead2.x) < m_nMinLength)
				{
					if (m_ptBlockHead1.x < m_ptBlockHead2.x)
					{//ok
						//移动Head2，Head2在Head1右边，从Head1往右边计算
						x2  = m_ptBlockHead1.x + m_nMinLength - m_ptOldBlockHead2.x;
					}
					else
					{//移动Head1，Head1在Head2右边，从Head1往左边计算
						//固定Head2，移动Head1：即从Head2往右边计算Head1
						x  = m_ptOldBlockHead1.x - (m_ptBlockHead2.x + m_nMinLength);
					}
				}
			}
			else
			{//垂直标尺
				if (abs(m_ptBlockHead1.y - m_ptBlockHead2.y) < m_nMinLength)
				{
					if (m_ptBlockHead1.y < m_ptBlockHead2.y)
					{//ok
						//移动Head2，Head2在Head1右边，从Head1往右边计算
						y2  = m_ptBlockHead1.y + m_nMinLength - m_ptOldBlockHead2.y;
					}
					else
					{//移动Head1，Head1在Head2右边，从Head1往左边计算
						//固定Head2，移动Head1：即从Head2往右边计算Head1
						y  = m_ptOldBlockHead1.y - (m_ptBlockHead2.y + m_nMinLength);
					}
				}
			}
		}
	}
}

void CDrawRangeStateAxis::ModifyBlock()
{
	long x = g_ptCurrent.x - g_ptOrigin.x;
	long y = g_ptCurrent.y - g_ptOrigin.y;

	//根据种类限定变换
	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		y = 0;
	}
	else
	{
		x = 0;
	}
	
	if (m_nStateAxisOptrState == RANGESTATEAXIS_MOVE)
	{//移动
		ModifyBlock_Move(x, y);
	}
	else if (m_nStateAxisOptrState == RANGESTATEAXIS_ZOOM)
	{
		ModifyBlock_Zoom(x, y);
	}
	else
	{
		
	}
}

void CDrawRangeStateAxis::ModifyBorder()
{
	long x = g_ptCurrent.x - g_ptOrigin.x;
	long y = g_ptCurrent.y - g_ptOrigin.y;

	//根据种类限定变换
	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		y = 0;
	}
	else
	{
		x = 0;
	}
	
	if (m_nStateAxisOptrState == RANGESTATEAXIS_MOVE)
	{
		ModifyBorder_Move(x, y);
	}
	else if (m_nStateAxisOptrState == RANGESTATEAXIS_ZOOM)
	{
		ModifyBorder_Zoom(x, y);
	}
	else
	{
		
	}

	BackPosition();
}

LONG CDrawRangeStateAxis::MouseMove(CPoint &point)
{
	if (m_nStateAxisOptrState != RANGESTATEAXIS_MOVE)
	{
		return DRAW_NONE_OBJECT_SELECTED;
	}

	g_ptCurrent = point;
	
	ModifyBlock();
	
	if (m_pParentWnd != NULL)
	{
		if (::IsWindow(m_pParentWnd->m_hWnd))
		{				
			m_pParentWnd->PostMessage(WM_INVALIDATE_RANGESTATEAXIS, (WPARAM)this, (WPARAM)this);
		}
	}

	return DRAW_HAS_OBJECT_SELECTED;
}


LONG CDrawRangeStateAxis::LButtonDown(CPoint &point)
{
	m_nStateAxisOptrState = RANGESTATEAXIS_MOVE;
	BackPosition();
	g_ptCurrent = point;
	g_ptOrigin = point;
	g_ptOrigin = point;

	return DRAW_HAS_OBJECT_SELECTED;
}

LONG CDrawRangeStateAxis::LButtonUp(CPoint &point)
{
	m_nStateAxisOptrState = RANGESTATEAXIS_NONE;
	g_bLButtonDown = FALSE;
	ModifyBorder();

	return 0;
}


LONG CDrawRangeStateAxis::MouseMove(UINT nFlags, CPoint &point)
{
	LONG nReturn = DRAW_NONE_OBJECT_SELECTED;

	if (g_bLButtonDown && m_nStateAxisOptrState != RANGESTATEAXIS_NONE)
	{
		g_ptCurrent = point;

		if (m_nStateAxisOptrState == RANGESTATEAXIS_MOVE)
		{
			nReturn = DRAW_HAS_OBJECT_SELECTED;
			::SetCursor(m_hMoveCursor);
		}
		else if (m_nStateAxisOptrState == RANGESTATEAXIS_ZOOM)
		{
			nReturn = DRAW_HAS_OBJECT_SELECTED;
			::SetCursor(m_hZoomCursor);
		}
		else
		{
			::SetCursor(m_hProhitiCursor);
		}
		
		ModifyBlock();

		if (m_pParentWnd != NULL)
		{
			if (::IsWindow(m_pParentWnd->m_hWnd))
			{				
				m_pParentWnd->PostMessage(WM_INVALIDATE_RANGESTATEAXIS, (WPARAM)this, (WPARAM)this);
			}
		}
	}
	else
	{
		if (MrDraw::PointInRect(point, m_rcBlockHead1) )
		{
			if (!m_bFrozenHead1)
			{
				nReturn = DRAW_HAS_OBJECT_SELECTED;
				::SetCursor(m_hZoomCursor);
			}
		}
		else if ( MrDraw::PointInRect(point, m_rcBlockHead2) )
		{
			if (!m_bFrozenHead2)
			{
				nReturn = DRAW_HAS_OBJECT_SELECTED;
				::SetCursor(m_hZoomCursor);
			}
		}
		else if (MrDraw::PointInRect(point, m_rcBlockCenter))//m_rcBlockCenter.PtInRect(point))
		{
			if (!m_bFrozenCenter)
			{
				nReturn = DRAW_HAS_OBJECT_SELECTED;
				::SetCursor(m_hMoveCursor);
			}
		}
		else
		{
		}
	}

	if (nReturn == DRAW_NONE_OBJECT_SELECTED)
	{
		::SetCursor(m_hArrowCursor);		
	}
	
	return nReturn;
}

LONG CDrawRangeStateAxis::LButtonDown(UINT nFlags, CPoint &point)
{
	BackPosition();
	g_bLButtonDown = TRUE;

	if (m_pAttachDraw == NULL)
	{
		return DRAW_NONE_OBJECT_SELECTED;
	}

	m_nBlockID = RANGESTATEAXIS_BLOCK_NONE;
	
	if (MrDraw::PointInRect(point, m_rcBlockCenter))
	{
		if (!m_bFrozenCenter)
		{
			m_nBlockID = RANGESTATEAXIS_BLOCK_CENTER;
		}
	}
	else if (MrDraw::PointInRect(point, m_rcBlockHead1))
	{
		if (!m_bFrozenHead1)
		{
			m_nBlockID = RANGESTATEAXIS_BLOCK_HEAD1;
		}
	}
	else if (MrDraw::PointInRect(point, m_rcBlockHead2))
	{
		if (!m_bFrozenHead2)
		{
			m_nBlockID = RANGESTATEAXIS_BLOCK_HEAD2;
		}
	}
	else
	{
		m_nBlockID = RANGESTATEAXIS_BLOCK_NONE;
		if (!MrDraw::PointInRect(point, m_rcBorder))
		{
			return DRAW_NONE_OBJECT_SELECTED;
		}
	}

	if (m_nBlockID == RANGESTATEAXIS_BLOCK_HEAD1 || m_nBlockID == RANGESTATEAXIS_BLOCK_HEAD2)
	{
		g_ptCurrent = point;
		g_ptOrigin = point;
		m_nStateAxisOptrState = RANGESTATEAXIS_ZOOM;
		::SetCursor(m_hZoomCursor);
		g_ptOrigin = point;
	}
	else if (m_nBlockID == RANGESTATEAXIS_BLOCK_CENTER)
	{
		g_ptCurrent = point;
		g_ptOrigin = point;
		m_nStateAxisOptrState = RANGESTATEAXIS_MOVE;
		::SetCursor(m_hMoveCursor);
		g_ptOrigin = point;
	}
	else
	{
		::SetCursor(m_hArrowCursor);
		m_nStateAxisOptrState = RANGESTATEAXIS_NONE;
	}
	
	//限制鼠标移动区域
	if (m_nStateAxisOptrState != RANGESTATEAXIS_NONE)
	{
		if (m_pClipRect != NULL && m_pParentWnd != NULL)
		{
			CRect rcClip = *m_pClipRect;
			SetCapture(m_pParentWnd->m_hWnd);
			m_pParentWnd->ClientToScreen(&rcClip);
			::ClipCursor(&rcClip);
			m_bSetCapture = TRUE;
		}
	}

	return DRAW_HAS_OBJECT_SELECTED;
}

LONG CDrawRangeStateAxis::LButtonUp(UINT nFlags, CPoint &point)
{
	g_bLButtonDown = FALSE;

	if (m_pAttachDraw == NULL)
	{
		if (m_bSetCapture)
		{
			::ClipCursor(NULL);
			ReleaseCapture();
			m_bSetCapture = FALSE;
		}
		
		return DRAW_NONE_OBJECT_SELECTED;
	}

	if (m_nStateAxisOptrState == RANGESTATEAXIS_NONE)
	{
		if (m_bSetCapture)
		{
			::ClipCursor(NULL);
			ReleaseCapture();
			m_bSetCapture = FALSE;
		}

		return DRAW_NONE_OBJECT_SELECTED;
	}

	if (m_nStateAxisOptrState == RANGESTATEAXIS_MOVE)
	{
		ModifyBorder();
		::SetCursor(m_hMoveCursor);
	}
	else if (m_nStateAxisOptrState == RANGESTATEAXIS_ZOOM)
	{
		ModifyBorder();
		::SetCursor(m_hZoomCursor);
	}
	else
	{
	}

	//限制鼠标移动区域
	if (m_nStateAxisOptrState != RANGESTATEAXIS_NONE)
	{
		if (m_pClipRect != NULL && m_pParentWnd != NULL)
		{
			::ClipCursor(NULL);
			ReleaseCapture();
			m_bSetCapture = FALSE;
		}
	}
	
	if (m_bSetCapture)
	{
		::ClipCursor(NULL);
		ReleaseCapture();
		m_bSetCapture = FALSE;
	}
	
	m_nStateAxisOptrState = RANGESTATEAXIS_NONE;

	return 0;
}

LONG CDrawRangeStateAxis::RButtonDown(UINT nFlags, CPoint &point)
{
	return 0;
}

LONG CDrawRangeStateAxis::RButtonUp(UINT nFlags, CPoint &point)
{	
	return 0;
}

BOOL CDrawRangeStateAxis::PointInRgn(CPoint &pt) 
{
	return TRUE;
}

BOOL CDrawRangeStateAxis::IsInClipRect()
{
	if (m_pClipRect == NULL)
	{
		return TRUE;
	}

	if (! MrDraw::PointInRect(*m_pClipRect,m_rcBorder.TopLeft()))
	{
		return FALSE;
	}
	
	if (! MrDraw::PointInRect(*m_pClipRect, m_rcBorder.BottomRight()))
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CDrawRangeStateAxis::IsInClipRect(CRect &rcBlockHead1, CRect &rcBlockHead2)
{
	if (m_pClipRect == NULL)
	{
		return TRUE;
	}

	if (! MrDraw::PointInRect(*m_pClipRect,rcBlockHead1.TopLeft()))
	{
		return FALSE;
	}

	if (! MrDraw::PointInRect(*m_pClipRect, rcBlockHead1.BottomRight()))
	{
		return FALSE;
	}

	if (! MrDraw::PointInRect(*m_pClipRect,rcBlockHead2.TopLeft()))
	{
		return FALSE;
	}

	if (! MrDraw::PointInRect(*m_pClipRect, rcBlockHead2.BottomRight()))
	{
		return FALSE;
	}

	return TRUE;
}

void CDrawRangeStateAxis::ClipRect(CRect &rcBlockHead1, CRect &rcBlockHead2, CRect &rcBlockCenter)
{
	if (m_pClipRect == NULL)
	{
		return;
	}
	
	long nOffset = 0;
	long nOffset2 = 0;

	CPoint ptCenterHead1 = rcBlockHead1.CenterPoint();
	CPoint ptCenterHead2 = rcBlockHead2.CenterPoint();

	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		if (ptCenterHead1.x < ptCenterHead2.x)
		{
			if (ptCenterHead1.x < m_pClipRect->left)
			{
				nOffset = m_pClipRect->left - ptCenterHead1.x;
			}
			
			if (ptCenterHead2.x > m_pClipRect->right)
			{
				nOffset2 = ptCenterHead2.x - m_pClipRect->right;
			}
			
			nOffset = max(nOffset, nOffset2);
			rcBlockHead1.OffsetRect(nOffset, 0);
			rcBlockHead2.OffsetRect(-nOffset, 0);
		}
		else
		{
			if (ptCenterHead1.x > m_pClipRect->right)
			{
				nOffset = ptCenterHead1.x - m_pClipRect->right;
			}
			
			if (ptCenterHead2.x < m_pClipRect->left)
			{
				nOffset2 = m_pClipRect->left - ptCenterHead2.x;
			}
			
			nOffset = max(nOffset, nOffset2);
			rcBlockHead2.OffsetRect(nOffset, 0);
			rcBlockHead1.OffsetRect(-nOffset, 0);
		}		
	}
	else
	{
		if (ptCenterHead1.y < ptCenterHead2.y)
		{
			if (ptCenterHead1.y < m_pClipRect->top)
			{
				nOffset = m_pClipRect->top - ptCenterHead1.y;
			}

			if (ptCenterHead2.y > m_pClipRect->bottom)
			{
				nOffset2 = ptCenterHead2.y - m_pClipRect->bottom;
			}
	
			nOffset = max(nOffset, nOffset2);
			rcBlockHead1.OffsetRect(0, nOffset);
			rcBlockHead2.OffsetRect(0, -nOffset);
		}
		else
		{
			if (ptCenterHead1.y > m_pClipRect->bottom)
			{
				nOffset = ptCenterHead1.y - m_pClipRect->bottom;
			}
			
			if (ptCenterHead2.y < m_pClipRect->top)
			{
				nOffset2 = m_pClipRect->top - ptCenterHead2.y;
			}

			nOffset = max(nOffset, nOffset2);
			rcBlockHead2.OffsetRect(0, nOffset);
			rcBlockHead1.OffsetRect(0, -nOffset);
		}
	}
}

void CDrawRangeStateAxis::GetRangeStateAxisRange(long &nBegin, long &nEnd)
{
	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		nBegin = m_ptBlockHead1.x;
		nEnd = m_ptBlockHead2.x;
	}
	else
	{
		nBegin = m_ptBlockHead1.y;
		nEnd = m_ptBlockHead2.y;
	}
}

void CDrawRangeStateAxis::Draw(CDC *pDC, ULONG nDrawStyle) 
{
	if (m_pAttachDraw == NULL)
	{
		return;
	}

	DrawRangeStateAxis(pDC);//, m_rcBlockHead1, m_rcBlockHead2, m_rcBlockCenter, m_nRangeStateAxisType, m_crColor);
}

void CDrawRangeStateAxis::DrawRangeStateAxis(CDC *pDC)//, const CRect rcHead1, const CRect rcHead2, const CRect rcCenter, long nType, COLORREF crColor)
{
	ASSERT(m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ || m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_VERT);
	
	CBrush brush(m_crColor);
	CBrush brushFrozen(m_crFrozenColor);
	CBrush *pOldBrush = pDC->SelectObject(&brush);
	CBrush *pTemp = NULL;
	CPen pen(PS_SOLID, 1, m_crColor);
	CPen *pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(m_ptBlockHead1);
	pDC->LineTo(m_ptBlockHead2);

	DrawBlock(pDC, brushFrozen, m_rcBlockHead1, m_bFrozenHead1);
	DrawBlock(pDC, brushFrozen, m_rcBlockHead2, m_bFrozenHead2);
	DrawBlock(pDC, brushFrozen, m_rcBlockCenter, m_bFrozenCenter);
	
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	pOldBrush = NULL;
	pOldPen   = NULL;
}

void CDrawRangeStateAxis::DrawBlock(CDC *pDC, CBrush &brushFronzen, const CRect &rcBlock, BOOL bFrozen)
{
	CBrush *pOldBrush = NULL;

	if (bFrozen)
	{
		pOldBrush = pDC->SelectObject(&brushFronzen);
	}
	
	pDC->Rectangle(rcBlock);
	
	if (bFrozen)
	{
		pDC->SelectObject(pOldBrush);
	}

	pOldBrush = NULL;
}

void CDrawRangeStateAxis::Move(long nHor , long nVer ) 
{
	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		nVer = 0;
	}
	else
	{
		nHor = 0;
	}
		
	BackPosition();
	InitBlockRect();
}

void CDrawRangeStateAxis::InitBlockRect()
{
	long nCenter = 0;
	
	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		m_rcBlockHead1.top = m_ptBlockHead1.y - RANGESTATEAXIS_BLOCK_HEIGHT1;
		m_rcBlockHead1.bottom = m_ptBlockHead1.y + RANGESTATEAXIS_BLOCK_HEIGHT1+1;
		m_rcBlockHead1.left = m_ptBlockHead1.x - RANGESTATEAXIS_BLOCK_HEIGHT2;
		m_rcBlockHead1.right = m_ptBlockHead1.x + RANGESTATEAXIS_BLOCK_HEIGHT2;

		m_rcBlockHead2.top = m_ptBlockHead2.y - RANGESTATEAXIS_BLOCK_HEIGHT1;
		m_rcBlockHead2.bottom = m_ptBlockHead2.y + RANGESTATEAXIS_BLOCK_HEIGHT1+1;
		m_rcBlockHead2.left = m_ptBlockHead2.x - RANGESTATEAXIS_BLOCK_HEIGHT2 - 1;
		m_rcBlockHead2.right = m_ptBlockHead2.x + RANGESTATEAXIS_BLOCK_HEIGHT2;
		
		m_rcBlockCenter.top = m_ptBlockCenter.y - RANGESTATEAXIS_BLOCK_HEIGHT1;
		m_rcBlockCenter.bottom = m_ptBlockCenter.y + RANGESTATEAXIS_BLOCK_HEIGHT1+1;
		m_rcBlockCenter.left = m_ptBlockCenter.x - RANGESTATEAXIS_BLOCK_HEIGHT2;
		m_rcBlockCenter.right = m_ptBlockCenter.x + RANGESTATEAXIS_BLOCK_HEIGHT2;
	}
	else
	{
		m_rcBlockHead1.top = m_ptBlockHead1.y - RANGESTATEAXIS_BLOCK_HEIGHT2;
		m_rcBlockHead1.bottom = m_ptBlockHead1.y + RANGESTATEAXIS_BLOCK_HEIGHT2;
		m_rcBlockHead1.left = m_ptBlockHead1.x - RANGESTATEAXIS_BLOCK_HEIGHT1;
		m_rcBlockHead1.right = m_ptBlockHead1.x + RANGESTATEAXIS_BLOCK_HEIGHT1+1;
		
		m_rcBlockHead2.top = m_ptBlockHead2.y - RANGESTATEAXIS_BLOCK_HEIGHT2;
		m_rcBlockHead2.bottom = m_ptBlockHead2.y + RANGESTATEAXIS_BLOCK_HEIGHT1;
		m_rcBlockHead2.left = m_ptBlockHead2.x - RANGESTATEAXIS_BLOCK_HEIGHT1;
		m_rcBlockHead2.right = m_ptBlockHead2.x + RANGESTATEAXIS_BLOCK_HEIGHT1+1;
		
		m_rcBlockCenter.top = m_ptBlockCenter.y - RANGESTATEAXIS_BLOCK_HEIGHT2;
		m_rcBlockCenter.bottom = m_ptBlockCenter.y + RANGESTATEAXIS_BLOCK_HEIGHT2;
		m_rcBlockCenter.left = m_ptBlockCenter.x - RANGESTATEAXIS_BLOCK_HEIGHT1;
		m_rcBlockCenter.right = m_ptBlockCenter.x + RANGESTATEAXIS_BLOCK_HEIGHT1+1;
	}
}

void CDrawRangeStateAxis::AdjustRangeStateAxis()
{
	long nCenter = 0;

	CPoint ptCenter = m_rcBorder.CenterPoint();
	
	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		m_ptBlockHead1.x = m_rcBorder.left;
		m_ptBlockHead1.y = ptCenter.y;

		m_ptBlockHead2.x = m_rcBorder.right;
		m_ptBlockHead2.y = ptCenter.y;
		
		m_ptBlockCenter.x = ptCenter.x;
		m_ptBlockCenter.y = ptCenter.y;
	}
	else
	{
		m_ptBlockHead1.x = ptCenter.x;
		m_ptBlockHead1.y = m_rcBorder.top;
		
		m_ptBlockHead2.x = ptCenter.x;
		m_ptBlockHead2.y = m_rcBorder.bottom;
		
		m_ptBlockCenter.x = ptCenter.x;
		m_ptBlockCenter.y = ptCenter.y;
	}

	InitBlockRect();
}


void CDrawRangeStateAxis::SetMinLength(long nMinLength)
{
	m_nMinLength = nMinLength;

	if (m_nMinLength < RANGESTATEAXIS_MIN_LENGTH)
	{
		m_nMinLength = RANGESTATEAXIS_MIN_LENGTH;
	}

	if (m_nMinLength > RANGESTATEAXIS_MIN_LENGTHMAX)
	{
		m_nMinLength = RANGESTATEAXIS_MIN_LENGTHMAX;
	}
}

void CDrawRangeStateAxis::AdjustRangeStateAxisByCoef(double dLeftCoef,double dRightCoef)
{
	long nWidth = 0;

	if (dLeftCoef < 0)
	{
		dLeftCoef = 0;
	}

	if (dLeftCoef > 1)
	{
		dLeftCoef = 1;
	}
	
	if (dRightCoef < 0)
	{
		dRightCoef = 0;
	}
	
	if (dRightCoef > 1)
	{
		dRightCoef = 1;
	}
	
	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		nWidth = m_ptOriginBlockHead2.x - m_ptOriginBlockHead1.x;
	}
	else
	{
		nWidth = m_ptOriginBlockHead2.y - m_ptOriginBlockHead2.y;
	}

	long nOffSet1 = (long)(dLeftCoef * nWidth);
	long nOffSet2 = (long)(dRightCoef * nWidth);

	if (m_nRangeStateAxisType == RANGESTATEAXIS_TYPE_HORZ)
	{
		m_ptBlockHead1.x = m_ptOriginBlockHead1.x + nOffSet1;
		m_ptBlockHead2.x = m_ptOriginBlockHead1.x + nOffSet2;
		m_ptBlockCenter.x = (m_ptBlockHead2.x + m_ptBlockHead1.x) / 2;
	}
	else
	{
		m_ptOldBlockHead1.y = m_ptOriginBlockHead1.y + nOffSet1;
		m_ptOldBlockHead2.y = m_ptOriginBlockHead1.y + nOffSet2;
		m_ptBlockCenter.y = (m_ptBlockHead2.y + m_ptBlockHead1.y) / 2;
	}
	
	InitBlockRect();
}


CRect CDrawRangeStateAxis::GetInvalidateRect()
{
	CRect rc;
	rc.left = min(m_rcBlockHead1.left ,m_rcBlockHead2.left);
	rc.right = max(m_rcBlockHead1.right ,m_rcBlockHead2.right);
	rc.top = min(m_rcBlockHead1.top ,m_rcBlockHead2.top);
	rc.bottom = max(m_rcBlockHead1.bottom ,m_rcBlockHead2.bottom);


	rc.left = min(rc.left ,m_rcBorder.left);
	rc.right = max(rc.right ,m_rcBorder.right);
	rc.top = min(rc.top ,m_rcBorder.top);
	rc.bottom = max(rc.bottom ,m_rcBorder.bottom);

	rc.InflateRect(RANGESTATEAXIS_BLOCK_WIDTH,RANGESTATEAXIS_BLOCK_WIDTH);
	return rc;
}


CRect CreateRangeStateAxisBorder(const CRect &rcRect, UINT nDir)
{
	CRect rcBorder = rcRect;

	switch(nDir)
	{
	case RANGESTATEAXIS_DIR_LEFT:
		rcBorder.right = rcBorder.left + RANGESTATEAXIS_BLOCK_WIDTH;
		break;
	case RANGESTATEAXIS_DIR_RIGHT:
		rcBorder.left = rcBorder.right - RANGESTATEAXIS_BLOCK_WIDTH;
		break;
	case RANGESTATEAXIS_DIR_UP:
		rcBorder.bottom = rcBorder.top + RANGESTATEAXIS_BLOCK_WIDTH;
		break;
	case RANGESTATEAXIS_DIR_DOWN:
		rcBorder.top = rcBorder.bottom - RANGESTATEAXIS_BLOCK_WIDTH;
		break;
	default:
		rcBorder.right = rcBorder.left + RANGESTATEAXIS_BLOCK_WIDTH;
		break;
	}
	
	return rcBorder;
}

CRect CreateRangeVertStateAxisBorder(long nCenterX, long nYBegin, long yEnd)
{
	CRect rcBorder;
	nCenterX -= 1;
	rcBorder.left = nCenterX - RANGESTATEAXIS_BLOCK_WIDTHGAP;
	rcBorder.right = nCenterX + RANGESTATEAXIS_BLOCK_WIDTHGAP+1;
	rcBorder.top = nYBegin;
	rcBorder.bottom = yEnd+1;

	return rcBorder;
}


CRect CreateRangeHorzStateAxisBorder(long nCenterY, long nXBegin, long nXEnd)
{
	CRect rcBorder;
	nCenterY -= 1;
	rcBorder.top = nCenterY - RANGESTATEAXIS_BLOCK_WIDTHGAP;
	rcBorder.bottom = nCenterY + RANGESTATEAXIS_BLOCK_WIDTHGAP+1;
	rcBorder.left = nXBegin;
	rcBorder.right = nXEnd;
	
	return rcBorder;
}
