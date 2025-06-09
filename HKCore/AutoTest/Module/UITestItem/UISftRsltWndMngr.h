#pragma once

/*
	����������Safety������Ŀ���¼�������棬����Safety�Ľ��������ʾ��صĽ���
*/

#include "../../../Module/BaseClass/ExBaseList.h"
#include "UISftRsltWndInterface.h"

class CUISftRsltWndMngr : public CExBaseList
{
public:
	CUISftRsltWndMngr();
	virtual ~CUISftRsltWndMngr();

//����
public:
	CWnd* m_pInforWnd;
	CWnd* m_pButtonOK;
	CWnd* m_pParentWnd;

	long m_nInforWndWidth;
	long m_nInforWndHeight;
	long m_nSftWndWidth;

//����
public:
	void CreateRsltEditWnd(CShortDatas* oReport,CWnd* pParentWnd,CRect rcWnd);
	void SetFont(CFont* pFont);
	long GetHeight();
	BOOL IsAllDataEntered();
	void AdjustAllWindows(CWnd* pParentWnd,CWnd* pInforWnd,CWnd* pButtonOK);

private:
	CUISftRsltWndRows m_oUISftRsltWndRows;

	long AdjustAllWindowsToTwoColumns(long nColTotalHeight,long nYBegin,long &nBottom);
	long AdjustAllWindowsOneColumn(long nYBegin,long &nBottom);
	void ShowWindow();
	
	void CalSftRsltWndsSize();//���������size
	void InitUISftRsltWndRows(); //��ȫ��RsltWnd����
	long GetInforTextWndWidthHeight();

	void AdjustOnlyOne(long xPos, long nWidth);
	void AdjustY(long &yPos);
	void AdjustY_InforWnd(long &yPos);
	void AdjustY_MainWnd(long &yPos);
};