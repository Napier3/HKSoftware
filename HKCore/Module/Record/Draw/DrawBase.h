// DrawBase.h: interface for the CDrawBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWBASE_H__A1E0DCBD_9551_4697_A07D_BFD21061BA07__INCLUDED_)
#define AFX_DRAWBASE_H__A1E0DCBD_9551_4697_A07D_BFD21061BA07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawGlobalDef.h"
#include "../RecordGlobalDefine.h"
#include "../RecordSysMsgDef.h"

class CDrawBase  : public CXDrawElements
{
public:
	CDrawBase();
	virtual ~CDrawBase();

	UINT m_nLineStyle;

#ifndef _XDRAW_USE_EXTERN_ATTR_
	long  m_nEnable;
	long  m_nShow;
	BOOL m_bSelect;
	long m_nUse;
#endif

#ifndef _XDRAW_USE_EXTERN_ATTR_
	virtual void SetSelect(BOOL bSelect = TRUE)   {    m_bSelect = bSelect;         }
	virtual BOOL GetSelect()                      {    return m_bSelect;            }
	virtual long GetShow()						  {	   return m_nShow;				}
	virtual void SetShow(long nShow)			  {	   m_nShow = nShow;				}
	virtual void SetUse(long nUse)		{	m_nUse = nUse;	}
	virtual long GetUse()				{	return m_nUse;	}	
#endif

//·½·¨
public:
	virtual void LogicPointToDevicePoint(double dCoefY, double dOffsetY, MrDraw::DRAWMEMBUFFERPOS &oBufPos);
	virtual LONG MouseMove(UINT nFlags, CPoint &point);
	virtual LONG LButtonDown(UINT nFlags, CPoint &point);
	virtual LONG LButtonUp(UINT nFlags, CPoint &point);
	virtual LONG RButtonDown(UINT nFlags, CPoint &point);
	virtual LONG RButtonUp(UINT nFlags, CPoint &point);
	virtual BOOL PointInRgn(CPoint &pt) {	return FALSE;	}
	
public:
	void PostDrawObjectPosChangedMsg()
	{
		if (m_pParentWnd != NULL)
		{
			{			
				m_pParentWnd->PostMessage(WM_VARIABLE_POS_CHANGED, 0, 0);
			}
		}
	}
};

#endif // !defined(AFX_DRAWBASE_H__A1E0DCBD_9551_4697_A07D_BFD21061BA07__INCLUDED_)
