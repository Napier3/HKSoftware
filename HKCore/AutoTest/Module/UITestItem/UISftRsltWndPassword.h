#pragma once

/*
	����������Safety������Ŀ�û���������¼�봰��
*/

#include "UISftRsltWndInterface.h"

//δ���
class CUISftRsltWndPassword : public CStatic
{
public:
	CUISftRsltWndPassword();
	virtual ~CUISftRsltWndPassword();

public:
	CEdit* m_pEditPsw;
	CEdit* m_pEditUserName;

	CUISftRsltWndInterface* m_pResultWndInterface;
	CString m_strUserID;
	long m_nTimerID;
	CString m_strUserName;

	// Operations
public:
	void InitPassWord(const CString &strInterfaceCall, const CString &strUserName, long &nID);
	void AdjustWnd();


	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};