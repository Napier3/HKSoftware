#pragma once

#include "PpScriptMethodsInfo.h"
// CScriptMethodsComboBox

class CScriptMethodsComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CScriptMethodsComboBox)

public:
	CScriptMethodsComboBox();
	virtual ~CScriptMethodsComboBox();

public:
	CEdit* m_pEdit;
	void InitComboBox(DWORD dwFlag);
	void AddStringEx();
	CString GetFuncText(BOOL bHasParaList);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();

public:
	afx_msg void OnCbnSelchange();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


