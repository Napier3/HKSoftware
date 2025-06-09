// DrawRangeStateAxis.h: interface for the CDrawRangeStateAxis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DRAWRANGESTATEAXIS_H__)
#define _DRAWRANGESTATEAXIS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "DrawVariable.h"
#include "DrawBase.h"

#define RANGESTATEAXIS_TYPE_HORZ       0
#define RANGESTATEAXIS_TYPE_VERT       1

extern long RANGESTATEAXIS_BLOCK_WIDTH;//     15
extern long  RANGESTATEAXIS_BLOCK_WIDTHGAP;//  7
extern long  RANGESTATEAXIS_BLOCK_HEIGHT1;//   7
extern long  RANGESTATEAXIS_BLOCK_HEIGHT2;//   7

extern long RANGESTATEAXIS_MIN_LENGTH;//      14 //4+ 2+ 4
#define RANGESTATEAXIS_MIN_LENGTHMAX   200

#define RANGESTATEAXIS_DIR_LEFT       0
#define RANGESTATEAXIS_DIR_RIGHT      1
#define RANGESTATEAXIS_DIR_UP         2
#define RANGESTATEAXIS_DIR_DOWN       3

#define RANGESTATEAXIS_NONE           0
#define RANGESTATEAXIS_MOVE           1
#define RANGESTATEAXIS_ZOOM           2

#define RANGESTATEAXIS_BLOCK_NONE     0
#define RANGESTATEAXIS_BLOCK_HEAD1    1
#define RANGESTATEAXIS_BLOCK_CENTER   2
#define RANGESTATEAXIS_BLOCK_HEAD2    3

CRect CreateRangeStateAxisBorder(const CRect &rcRect, UINT nDir);
CRect CreateRangeVertStateAxisBorder(long nCenterX, long nYBegin, long yEnd);
CRect CreateRangeHorzStateAxisBorder(long nCenterY, long nXBegin, long nXEnd);

class CDrawRangeStateAxis : public CDrawBase  
{
public:
	CXDrawElement *m_pAttachDraw;

public:
	virtual void SetBorder(const CRect &rcBorder);
	virtual void SetBorder(const CRect &rcBorder, UINT nType);
	virtual void ExpandBorder(long &l, long &t, long &r, long &b);
	void SetRangeStateAxisType(UINT nType = RANGESTATEAXIS_TYPE_VERT);
	virtual UINT GetClassID()       {    return CMTRDCLASSID_RANGESTATEAXIS;    }

	virtual LONG MouseMove(UINT nFlags, CPoint &point);
	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
	virtual LONG MouseMove(CPoint &point);
	virtual LONG LButtonDown(CPoint &point);
	virtual LONG LButtonUp(CPoint &point);
	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) ;
	virtual void Move(long nHor = 0, long nVer = 0) ;

	//virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

	void AttachDrawObject(CXDrawElement *pVariable);
	void DettachVariable()                           {    m_pAttachDraw = NULL;         }

	void SetMoveCursor(HCURSOR hCursor)              {    m_hMoveCursor = hCursor;      }
	void SetZoomCursor(HCURSOR hCursor)              {    m_hZoomCursor = hCursor;      }
	void SetProhibitCursor(HCURSOR hCursor)          {    m_hProhitiCursor = hCursor;   }

	void DrawRangeStateAxis(CDC *pDC);//, const CRect rcHead1, const CRect rcHead2, const CRect rcCenter, long nType, COLORREF crColor);

public:
	CDrawRangeStateAxis();
	virtual ~CDrawRangeStateAxis();

	void SetClipRect(const CRect &rcClip);
	BOOL IsInClipRect(CRect &rcBlockHead1, CRect &rcBlockHead2);
	void ClipRect(CRect &rcBlockHead1, CRect &rcBlockHead2, CRect &rcBlockCenter);
	BOOL IsInClipRect();
	CPoint GetPointCenter()                {     return m_ptBlockCenter;                     }
	void GetRangeStateAxisRange(long &nBegin, long &nEnd);
	void SetLockHead(BOOL bLockHead)       {     m_bLockHead = bLockHead;  AdjustLockHead(); }
	void SetMinLength(long nMinPength);
	void FrozenHead1(BOOL bFrozen = TRUE)  {   m_bFrozenHead1 = bFrozen; AdjustLockHead();   }
	void FrozenHead2(BOOL bFrozen = TRUE)  {   m_bFrozenHead2 = bFrozen; AdjustLockHead();   }
	void FrozenCenter(BOOL bFrozen = TRUE) {   m_bFrozenCenter = bFrozen; AdjustLockHead();  }
	CRect* GetClipRect()                   {   return m_pClipRect;                           }
	CRect GetInvalidateRect();
	
	void GetBlockHeadPos(long &nHead1Pos, long &nHead2Pos)        {   nHead1Pos = m_ptBlockHead1.x;    nHead2Pos = m_ptBlockHead2.x;     }
	void GetBlockHeadOriginPos(long &nHead1Pos, long &nHead2Pos)  {   nHead1Pos = m_ptOldBlockHead1.x; nHead2Pos = m_ptOldBlockHead2.x;  }
	void AdjustRangeStateAxisByCoef(double dLeftCoef,double dRightCoef);//根据外部重新绘制滑块
	
private:
	void AdjustBlcockHead();
	void AdjustRangeStateAxis();
	void BeforeExpand(long &x, long &y);
	void ModifyBlock();
	void ModifyBlock_Move(long &x, long &y);
	void ModifyBlock_Zoom(long &x, long &y);
	void ModifyBlock_ZoomClip(long &x, long &y);
	void ModifyBlock_MinRect();
	void ModifyBorder();
	void ModifyBorder_Move(long &x, long &y);
	void ModifyBorder_ZoomClipByMinLength(long &x, long &y, long &x2, long &y2);
	void ModifyBorder_Zoom(long &x, long &y);
	void BackPosition();
	void RestorePosition();

	void InitBlockRect();
	void Offset(long &x, long &y);
	
	void DrawBlock(CDC *pDC, CBrush &brush, CBrush &brushFronzen, CRect &rcBlock, BOOL bFrozen);
	void AdjustLockHead()	{  if (m_bFrozenHead1 || m_bFrozenHead2)  {  m_bLockHead = FALSE; /*m_bFrozenCenter = TRUE;*/ }  }

private:
	HCURSOR m_hArrowCursor;
	UINT  m_nStateAxisOptrState;
	
	HCURSOR m_hMoveCursor;
	HCURSOR m_hZoomCursor;
	HCURSOR m_hProhitiCursor;

	CRect m_rcBlockHead1;
	CRect m_rcBlockHead2;
	CRect m_rcBlockCenter;

	CPoint m_ptBlockHead1;
	CPoint m_ptBlockHead2;
	CPoint m_ptBlockCenter;
	CPoint m_ptOldBlockHead1;
	CPoint m_ptOldBlockHead2;
	CPoint m_ptOldBlockCenter;
	CPoint m_ptOriginBlockHead1;
	CPoint m_ptOriginBlockHead2;
	
	long m_nActiveState;
	UINT m_nRangeStateAxisType;
	UINT  m_nBlockID;
	CRect *m_pClipRect;           //坐标移动区域
	BOOL  m_bLockHead;            //是否锁定两个头区块
	long  m_nMinLength;
	BOOL  m_bFrozenHead1;         //冻结Head、Center，冻结之后就不能操作
	BOOL  m_bFrozenHead2;
	BOOL  m_bFrozenCenter;

	COLORREF m_crFrozenColor;
	BOOL m_bSetCapture;
};


#endif // !defined(_DRAWRANGESTATEAXIS_H__)
