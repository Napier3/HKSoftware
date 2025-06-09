// KeyHookBaseDialog.h: interface for the CKeyHookBaseDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYHOOKBASEDIALOG_H__3D9F5B21_8A53_44A0_9557_DA783F8B665E__INCLUDED_)
#define AFX_KEYHOOKBASEDIALOG_H__3D9F5B21_8A53_44A0_9557_DA783F8B665E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKeyHookBaseDialog : public CDialog  
{
public:
	CKeyHookBaseDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual ~CKeyHookBaseDialog();

	void ShowDialog();
	void HideDialog();
	virtual BOOL OnKeyHook(UINT nKey) = 0;
};

#endif // !defined(AFX_KEYHOOKBASEDIALOG_H__3D9F5B21_8A53_44A0_9557_DA783F8B665E__INCLUDED_)
