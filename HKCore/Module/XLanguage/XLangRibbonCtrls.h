//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
	virtual void UpdateTooltipInfo();


//˽�г�Ա����
private:
	CString m_strToolTipTxt;

//˽�г�Ա�������ʷ���
public:
};

class CXLangRibbonCheckBox : public CMFCRibbonCheckBox//, CXLangRibbonButton
{
public:
	CXLangRibbonCheckBox();
	CXLangRibbonCheckBox(UINT nID, LPCTSTR lpszText);
	CXLangRibbonCheckBox(UINT nID, LPCTSTR lpszText, LPCTSTR lpszTipText);
	virtual ~CXLangRibbonCheckBox();

	//���غ���
public:
	virtual void UpdateTooltipInfo();


	//˽�г�Ա����
private:
	CString m_strToolTipTxt;

	//˽�г�Ա�������ʷ���
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

	//���غ���
public:
	virtual void UpdateTooltipInfo();


	//˽�г�Ա����
private:
	CString m_strToolTipTxt;

	//˽�г�Ա�������ʷ���
public:
};