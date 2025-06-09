//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangItem.h  CXLangItem

#pragma once


class CXLangRibbonButton : public CMFCRibbonButton
{
public:
	CXLangRibbonButton();
	CXLangRibbonButton(UINT nID, LPCTSTR lpszText, int nSmallImageIndex = -1, int nLargeImageIndex = -1, BOOL bAlwaysShowDescription = FALSE);
	CXLangRibbonButton(UINT nID, LPCTSTR lpszText, HICON hIcon, BOOL bAlwaysShowDescription = FALSE, HICON hIconSmall = NULL, BOOL bAutoDestroyIcon = FALSE, BOOL bAlphaBlendIcon = FALSE);
	CXLangRibbonButton(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText, int nSmallImageIndex = -1, int nLargeImageIndex = -1, BOOL bAlwaysShowDescription = FALSE);
	CXLangRibbonButton(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText, HICON hIcon, BOOL bAlwaysShowDescription = FALSE, HICON hIconSmall = NULL, BOOL bAutoDestroyIcon = FALSE, BOOL bAlphaBlendIcon = FALSE);

	virtual ~CXLangRibbonButton();

//重载函数
public:
	virtual void UpdateTooltipInfo();


//私有成员变量
private:
	CString m_strToolTipTxt;

//私有成员变量访问方法
public:
};

class CXLangRibbonCheckBox : public CMFCRibbonCheckBox//, CXLangRibbonButton
{
public:
	CXLangRibbonCheckBox();
	CXLangRibbonCheckBox(UINT nID, LPCTSTR lpszText);
	CXLangRibbonCheckBox(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText);
	virtual ~CXLangRibbonCheckBox();

	//重载函数
public:
	virtual void UpdateTooltipInfo();


	//私有成员变量
private:
	CString m_strToolTipTxt;

	//私有成员变量访问方法
public:
};

class CXLangRibbonMainPanelButton : public CMFCRibbonMainPanelButton//, CXLangRibbonMainPanelButton
{
public:
	CXLangRibbonMainPanelButton();
	CXLangRibbonMainPanelButton(UINT nID, LPCTSTR lpszText, int nSmallImageIndex);
	CXLangRibbonMainPanelButton(UINT nID, LPCTSTR lpszText, HICON hIcon);
	CXLangRibbonMainPanelButton(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText, int nSmallImageIndex);
	CXLangRibbonMainPanelButton(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText, HICON hIcon);
	virtual ~CXLangRibbonMainPanelButton();

	//重载函数
public:
	virtual void UpdateTooltipInfo();


	//私有成员变量
private:
	CString m_strToolTipTxt;

	//私有成员变量访问方法
public:
};