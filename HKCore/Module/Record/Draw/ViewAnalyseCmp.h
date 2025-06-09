#if !defined(_ViewAnalyseCmp_h__)
#define _ViewAnalyseCmp_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewAnalyseCmp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewAnalyseCmpCmp window
#include "ViewAnalyse.h"
#include "..\Compare\RecordCompareTool.h"

//分析单通道录波数据
class CViewAnalyseCmp :public CViewAnalyse
{
// Construction
public:
	CViewAnalyseCmp();
	virtual ~CViewAnalyseCmp();

	BOOL m_bCmpDrawUseCmbMode;
// Attributes
public:
	CMemBuffer_CPoint* m_pPointBufferCmp;//CPoint

	CRcdComtradeFile *m_pRcdComtradeFile1;
	CRecordTest *m_pRecordTest1;
	CMemBufferInterface* m_pRefBuffer1;
	long m_nSamRateForDraw1;

	long m_nBeginPos1, m_nEndPos1;
	long m_nBeginPos2, m_nEndPos2;
	MrDraw::DRAWMEMBUFFERPOS m_oDrawBufferPosCmp;
	MrDraw::DRAWMEMBUFFERPOS m_oOscillographBufferPosCmp;

// Operations
public:
	virtual void InitFromComtrade();
	virtual void InitDrawBufferPos();
	virtual void InitDrawPoints();		
	virtual BOOL CalCurrentDataPos(double dMax,double dMin);
	virtual CDrawAnalogVariable* AddAnalogDrawVariable(CExBaseObject* pVaraible, long nCurrentChans,  long nChIndex);
	virtual CDrawAnalogVariable* NewAnalogVariable();
	virtual void DrawMain_Wave(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
//	virtual void CalXPos(long nTotalPoints);

// Implementation
public:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ViewAnalyseCmp_h__)
