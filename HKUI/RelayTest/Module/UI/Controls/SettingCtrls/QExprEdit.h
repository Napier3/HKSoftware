#pragma once

#include <QObject>
#include <QTextEdit>
#include <QKeyEvent>

#include "../../../../../Module/Expression/ExprParse.h"

class QExprEdit : public QTextEdit
{
	Q_OBJECT
public:
	explicit QExprEdit(QWidget *parent = 0);
	~QExprEdit();

protected:
	static BOOL g_bIsInProcessing;
	static CString g_strExprEditCopyString;

private:
	BOOL IsCharOptr(TCHAR chChar);
	BOOL IsCharDigit(TCHAR chChar);

	BOOL CheckChar(TCHAR chChar, int nPos);
	void OnCharPrintchar(UINT nChar);
	void OnCharBackspace(UINT nChar);
	void OnCharDelete(UINT nChar);
	void GetGroupBounds(int &nBegin, int &nEnd, int nStartPos = 0, BOOL bForward = TRUE);
	BOOL DoUpdate(int nPos);

	void getPosition(int &nBegin, int &nEnd);
	void setPosition(int nBegin, int nEnd);

	// Attributes
private:
	CString m_strExprScript;  //���ʽ�Ľű�����

	CExprTextUnitList m_oExprTextUnitList;

	bool m_bPressCONTROL;
	bool m_bPressSHIFT;

	// Implementation
public:
	void SetExprVariableFind(CExprVariableFind *pVariableFind)	{ m_oExprTextUnitList.SetExprVariableFind(pVariableFind); }

	void SetExprScript(const CString &strScript);		//����ԭ���ʽ
	void SetExprScriptText(const CString &strScriptText);

	void GetExprScript(CString& rstrString) const;			//��ȡ���ʽ
	void GetWindowShowText(CString& rstrString) const;		//��ȡ���ʽ��ʾ����

	void InsertText(const CString &strID, const CString &strName);
	void InsertFunc(const CString &strFunc);

	bool eventFilter(QObject *obj, QEvent *event);

	void UpdateCursor();

protected:

	virtual void mousePressEvent(QMouseEvent *event);
	void OnLButtonUp();

	int GetSelExprTextUnits(CExprTextUnitList &oList);

};

extern CExBaseList* g_pDvmDevice_AttachSetting;			//ģ��
