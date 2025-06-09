#pragma once

/*
	功能描述：Safety测试项目结果录入管理界面，根据Safety的结果定义显示相关的界面
*/

#include "../../../Module/BaseClass/ExBaseList.h"
#include "UISftRsltWndInterface.h"

class CUISftRsltWndMngr : public CExBaseList
{
public:
	CUISftRsltWndMngr();
	virtual ~CUISftRsltWndMngr();

//属性
public:
	CWnd* m_pInforWnd;
	CWnd* m_pButtonOK;
	CWnd* m_pParentWnd;

	long m_nInforWndWidth;
	long m_nInforWndHeight;
	long m_nSftWndWidth;

//方法
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
	
	void CalSftRsltWndsSize();//计算各窗口size
	void InitUISftRsltWndRows(); //将全部RsltWnd分列
	long GetInforTextWndWidthHeight();

	void AdjustOnlyOne(long xPos, long nWidth);
	void AdjustY(long &yPos);
	void AdjustY_InforWnd(long &yPos);
	void AdjustY_MainWnd(long &yPos);
};