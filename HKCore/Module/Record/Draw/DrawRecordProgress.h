// DrawRecordProgress.h: interface for the CDrawRecordProgress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DrawRecordProgress_H__)
#define _DrawRecordProgress_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBase.h"
#define SPACE_TO_BORDER 2

//现在没有用到
class CDrawRecordProgress : public CDrawBase  
{
public:
	__int64 m_n64DataLength;
	__int64 m_n64CurrDataPos;
	long  m_nOldPos;//上次绘图位置
	long m_nProgressRectWidth;
	COLORREF m_crBackColor;
public:
	virtual void Draw(CDC* pDC);
	virtual void SetBorder(const CRect &rect) ; 

	void SetLength(__int64 n64Length);
	void SetCurrPos(__int64 n64Pos);
	void StepIt(CDC* pDC);
public:
	CDrawRecordProgress();
	virtual ~CDrawRecordProgress();
};

#endif // !defined(_DrawProgress_H__)
