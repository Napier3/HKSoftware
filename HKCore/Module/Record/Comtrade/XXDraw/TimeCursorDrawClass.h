// TimeCursorDrawClass.h: interface for the CTimeCursorDrawClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined TIMECURSORDRAWCLASS_H_
#define TIMECURSORDRAWCLASS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\BaseClass\ExBaseObject.h"

//########//����ʱ��������������
class CTimeCursorDrawClass : public CExBaseObject  
{
public:
	CWnd	*pParent;			//������ָ��
	CRect	m_rectOwnPosition;	//��걾���λ��
	CRect	m_rectTimeBtnArea;	//ʱ����İ�ť��λ��
	CRect	m_rectBeginTimeBtn;	//��ʼʱ���갴ťλ��
	CRect	m_rectEndTimeBtn;	//��ֹʱ���갴ťλ��
	//��ʼ������
	void	InitIt();
	void	EndIt();
	//ͬ��ͨ���Ļ�ͼ������а�
	void	SetLineAreaRects(int iAreas,CRect*pRect);
	void	GetTimeLineButton();

	void	Typeset(CSize size,long &lDrift);
public:
	int		m_iBLinePtX;		//��ʼʱ��������ֵ
	int		m_iELinePtX;		//��ֹʱ��������ֵ

	int		m_nLineAreas;		//ʱ���ߵĻ���������
	CRect	*m_pRectLineArea;	//ʱ���ߵĻ�������λ��

	COLORREF	m_crBeginLine;	//��ʼʱ�������ɫ
	COLORREF	m_crEndLine;	//��ֹʱ�������ɫ
	COLORREF	m_crViewBK;
	COLORREF	m_crArea;
	unsigned long	m_ulBeginLineType;	//��ʼʱ���������
	unsigned long	m_ulEndLineType;	//��ֹʱ���������

	//ʱ����Ļ�ͼ����
	void  DrawIt(CDC*pDC);
	void  DrawBeginTimeLine(CDC*pDC,BOOL b=FALSE);		//////������ʼʱ���ֱ��
	void  DrawEndTimeLine(CDC*pDC,BOOL b=FALSE);		//////������ֱֹ��
	void  EraseBeginTimeLine();			//erase the begin time line
	void  EraseEndTimeLine();			//erase the end time line;

	/////�������ĸ��ֲ�����־
	int   m_iMoveEndTimeFlag;			/////��ǰ�Ƿ��ƶ���ֱֹ�ߵı�־
	int	  m_iCurrDrawTimeLineType;		//���ڻ��Ƶ�����ʼʱ���߻�����ֹʱ����
	int	  m_iActiveTimeLine;			//��ǰ���ʱ����  2����ʼʱ���ߣ�1����ֹʱ����
	//////�������ĸ��ֲ�������
	BOOL OnMouseMoveTimeLines(CPoint point,CDC*pDC);
	BOOL OnTimeLineClick(CPoint point,CDC*pDC);

	BOOL OnMouseMove(CPoint point,CDC*pDC,CPoint ptScroll=CPoint(0,0));
	BOOL OnLButtonDown(CPoint point,CDC*pDC);
	BOOL OnLButtonUp(CPoint point,CDC*pDC);
	BOOL IsPointInRestList(CPoint point);
	CRect GetMaxRectArea();

public:
	CTimeCursorDrawClass();
	virtual ~CTimeCursorDrawClass();

	void Set_IDC_CURSOR(UINT nHand, UINT nMove)	{	m_IDC_CURSOR_HAND = nHand;	m_IDC_CURSOR_MOVE = nMove;}
protected:
	UINT m_IDC_CURSOR_HAND;
	UINT m_IDC_CURSOR_MOVE;

};

#endif // !defined(TIMECURSORDRAWCLASS_H_)
