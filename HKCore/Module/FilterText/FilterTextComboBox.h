#pragma once

#include "..\BaseClass\ExBaseListComboBox.h"
#include "FilterTextMngr.h"
#define  WM_FILTERTEXT_END_EDIT  (WM_USER + 800)
#include "..\API\FileApi.h"

//
// #define WM_DELETE_FILTER_TEXT   (WM_USER + 1413)
// 
// class CFilterTextListBox : public CListBox
// {
// 	DECLARE_DYNAMIC(CFilterTextListBox)
// 
// public:
// 	CFilterTextListBox();
// 	virtual ~CFilterTextListBox();
// 	CComboBox *m_pCmoboBox;
// 
// 
// protected:
// 	DECLARE_MESSAGE_MAP()
// public:
// 	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
// };
// 
// 
// class CFilterTexEdit : public CEdit
// {
// 	DECLARE_DYNAMIC(CFilterTexEdit)
// public:
// 	CFilterTexEdit();
// 	virtual ~CFilterTexEdit();
// 
// 	int m_nCurrPosBegin, m_nCurrPosEnd;
// 	void SetSelText(const CString &strText);
// 
// protected:
// 	DECLARE_MESSAGE_MAP()
// 
// public:
// 	afx_msg void OnEnKillfocus();
// };

class CFilterTextComboBox : public CExBaseListComboBox
{
public:
	CFilterTextComboBox();
	virtual ~CFilterTextComboBox();

	virtual long AddObj(CExBaseObject *pObj);
	virtual long InsertObj(long nIndex, CExBaseObject *pObj);

public:
	void InitFilterText(CFilterTextMngr *pFilterTextMngr);
	void SaveFilterText();
	BOOL GetFilterText(CString &strFilterText);
	CFilterText* GetFilterText(BOOL bBringToTop=FALSE);
	void SelectFilterText(CFilterText *pText);

//	CEdit* GetEdit()	{	return &m_Edit;	}
	CFilterText* AddFilterText(const CString &strFilterText);

	virtual void AddFilterText(CFilterText *pText);
	virtual void OnRbtnDelete();
	BOOL GetCurrSelFilterText(CString &strFilterText);

	void SetPrevfixText(const CString &strText)	{	m_strPrevfixText = strText;	m_strPrevfixText.MakeLower();	}

protected:
	CString m_strPrevFilterText;
// 	CFilterTexEdit    m_Edit;
// 	CFilterTextListBox    m_ListBox;
	CFilterTextMngr *g_pFilterTextMngr;
	CString m_strPrevfixText;

	virtual void GetAddString(CString &strText);
	virtual CString GetAddString2(const CString &strText);
// public:
// 	DECLARE_MESSAGE_MAP()
// 	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd *pWnd, UINT nCtlColor);
// 	afx_msg void OnDestroy();


};


