// DrawSysTime.h: interface for the CDrawSysTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DRAWSYSTIME_H__)
#define _DRAWSYSTIME_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawGlobalDef.h"
#include "../RecordSysMsgDef.h"
#include "../RecordGlobalDefine.h"

//û���õ�,ԭ����Ŀ������ʾ��ǰʱ��,����ʹ����һ��UI����CUIWndTimeʵ��
class CDrawSysTime  
{
public:
	CRect m_rcTime;
	RTTIME m_oTime;
	COLORREF m_crColor;
	long m_nDrawWidth;
	CWnd* m_pParentWnd;
public:
	void GetSysTime(RTTIME& oTime);
	void Draw(CDC* pDC);
	virtual void SetParentWnd(CWnd* pParentWnd)	  {	   m_pParentWnd = pParentWnd;	}
	virtual void SetBorder(const CRect &rect)     {    m_rcTime = rect;           }
public:
	CDrawSysTime();
	virtual ~CDrawSysTime();
};

#endif // !defined(_DRAWSYSTIME_H__)
