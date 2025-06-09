#pragma once

#include "..\BaseClass\ExBaseList.h"
// CExprEdit

class CExprVariableFind
{
public:
	CExprVariableFind();
	virtual ~CExprVariableFind();

	virtual CExBaseObject* FindVariableByID(const CString &strID);
	virtual CExBaseObject* FindVariableByName(const CString &strName);
	virtual void OnExprScriptChanged(const CString &strExprScript);
};

class CExprTextUnit
{
public:
	CExprTextUnit()							{						};
	CExprTextUnit(TCHAR chChar)				{	SetTChar(chChar);	};
	CExprTextUnit(const CString &strText)	{	SetString(strText);	};
	virtual ~CExprTextUnit(){};

public:
	BOOL IsNumber();
	BOOL IsVariable();
	BOOL IsOptr();
	BOOL IsFunc();

	BOOL InsertChar(TCHAR chChar, int nPos);
	CString GetString();
	BOOL AppendChar(TCHAR chChar);

private:
	void SetTChar(TCHAR chChar);
	void SetString(const CString &strText);

public:
	CString m_strUnitScpt;   //脚本-变量、符号、函数、数字
	CString m_strUnitText;   //文本-显示的文本
};

class CExprTextUnitList : public CTLinkList<CExprTextUnit>
{
public:
	CExprTextUnitList()				{	m_pExprVariableFind = NULL;		}
	virtual ~CExprTextUnitList()	{									}
	CExprVariableFind *m_pExprVariableFind;

public:
	void SetExprVariableFind(CExprVariableFind *pVariableFind)		{	m_pExprVariableFind = pVariableFind;	}
	CExprTextUnit* GetExprTextUnit(int nBeginPos, int nEndPos);
	int GetExprTextUnits(int nBeginPos, int nEndPos, CExprTextUnitList &oList);
	void GetExprTextUnitsPos(CExprTextUnitList &oList, int &nBeginPos, int &nEndPos);
	void GetExprTextUnitPos(CExprTextUnit *pExprTextUnit, int &nBeginPos, int &nEndPos);
	CExprTextUnit* FindPrevExprTextUnit(CExprTextUnit *pExprTextUnit);
	CExprTextUnit* FindNextExprTextUnit(CExprTextUnit *pExprTextUnit);

	void SetExprScript(const CString &strExprScript);
	void GetExprScript(CString &strExprScript) const;
	CString GetExprScript();

	void GetExprScriptText(CString &strExprScript) const;
	CString GetExprScriptText();

	// 		void InsertText(int nBeginPos, int nEndPos, const CString &strText);
	// 		BOOL CanInsertText(int nBeginPos, int nEndPos, const CString &strText);
	// 		BOOL CanInsertChar(int nPos);

	// 		BOOL CanDelete(CExprTextUnitList &oList);
	// 		BOOL Delete(CExprTextUnitList &oList);
	// 		BOOL CanDelete(CExprTextUnit &pTextUnit);
	BOOL DeleteExprTextUnit(CExprTextUnit *pTextUnit);
	void InitStringUnit(CExprTextUnit *pUnit);


protected:
	CExprTextUnit* NewTextUnit(TCHAR chChar);
	CExprTextUnit* NewTextUnit(const CString &strText);
	BOOL IsIntersect(int nBegin, int nEnd, int nBeginRef, int nEndRef);

};


class CExprEdit : public CEdit
{
	DECLARE_DYNAMIC(CExprEdit)

protected:
	

	static BOOL g_bIsInProcessing;
	static CString g_strExprEditCopyString;

public:
	CExprEdit();
	virtual ~CExprEdit();


	// Implementation
public:
	void SetExprVariableFind(CExprVariableFind *pVariableFind)	{	m_oExprTextUnitList.SetExprVariableFind(pVariableFind);	 }
	void SetExprScript(const CString &strScriptText);
	void GetWindowText(CString& rstrString) const;
	void InsertText(const CString &strText);
	void InsertFunc(const CString &strFunc);

protected:
	int GetWindowText(_Out_z_cap_post_count_(nMaxCount, return + 1) LPTSTR lpszStringBuf, _In_ int nMaxCount) const;
	void SetWindowText(LPCTSTR lpszString);

	int GetSelExprTextUnits(CExprTextUnitList &oList);

private:
	BOOL IsCharOptr(TCHAR chChar);
	BOOL IsCharDigit(TCHAR chChar);

	BOOL CheckChar(TCHAR chChar, int nPos);
	void OnCharPrintchar(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnCharBackspace(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnCharDelete(UINT nChar, UINT nRepCnt, UINT nFlags);
	void GetGroupBounds(int &nBegin, int &nEnd, int nStartPos=0, BOOL bForward=TRUE);
	BOOL DoUpdate(int nPos);

	// Attributes
private:
	CString m_strExprScript;  //表达式的脚本部分

	CExprTextUnitList m_oExprTextUnitList;

protected:
	//{{AFX_MSG(CMFCMaskedEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocusR();
	afx_msg LRESULT OnCut(WPARAM, LPARAM);
	afx_msg LRESULT OnClear(WPARAM, LPARAM);
	afx_msg LRESULT OnPaste(WPARAM, LPARAM);
	afx_msg LRESULT OnSetText(WPARAM, LPARAM);
	afx_msg LRESULT OnGetText(WPARAM, LPARAM);
	afx_msg LRESULT OnGetTextLength(WPARAM, LPARAM);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnCopy();
	afx_msg void OnPaste();

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

BOOL Expr_IsStringFunc(const CString &strText);
