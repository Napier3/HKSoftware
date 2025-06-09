// DrawBase.h: interface for the CDrawBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWBASE_H__A1E0DCBD_9551_4697_A07D_BFD21061BA07__INCLUDED_)
#define AFX_DRAWBASE_H__A1E0DCBD_9551_4697_A07D_BFD21061BA07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawGlobalDef.h"


class CDrawBase  
{
//属性
public:
	//静态属性
	static CPoint g_ptOrigin;
	static CPoint g_ptCurrent;
	static BOOL   g_bLButtonDown;

	//普通属性
	CRect m_rcBorder;
	COLORREF m_crColor;
	BOOL m_bSelect;
	long m_nShow;
	CString m_strName;
	CString m_strID;
	CWnd *m_pParentWnd;//如果需要给父窗口发消息时使用
	CDrawBase *m_pParent;

//方法
public:
	virtual CDrawBase* GetParent()                {    return m_pParent;			}
	virtual void SetParent(CDrawBase* pParent)    {    m_pParent = pParent;			}
	virtual void SetParentWnd(CWnd* pParentWnd)	  {	   m_pParentWnd = pParentWnd;	}
	virtual void SetSelect(BOOL bSelect = TRUE)   {    m_bSelect = bSelect;         }
	virtual BOOL GetSelect()                      {    return m_bSelect;            }
	void SetColor(COLORREF cr)                    {    m_crColor = cr;              }
	COLORREF GetColor()                           {    return m_crColor;            }
	
	virtual void SetBorder(const CRect &rect)     {    m_rcBorder = rect;           }
	virtual CRect GetBorder()                     {    return m_rcBorder;           }
	virtual void ExpandBorder(long &l, long &t, long &r, long &b);
	virtual UINT GetClassID()							{    return DRAWCLASSID_BASEOBJECT;			}
	virtual BOOL CanZoomY()								{    return FALSE;							}
	virtual BOOL CanZoomX()								{    return FALSE;							}
	virtual void Move(long nHor = 0, long nVer = 0)		{    m_rcBorder.OffsetRect(nHor, nVer);		} 
	virtual void Zoom(double dRate) ;
	virtual void Draw(CDC *pDC) ;
	virtual void LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos);
	virtual LONG MouseMove(UINT nFlags, CPoint &point);
	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) {	return FALSE;	}

public:
	CDrawBase();
	virtual ~CDrawBase();
};

#endif // !defined(AFX_DRAWBASE_H__A1E0DCBD_9551_4697_A07D_BFD21061BA07__INCLUDED_)
