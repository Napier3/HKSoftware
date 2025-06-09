#pragma once

/*
	功能描述：
*/

class CUISftRsltWndInterface;

class CUISftRsltWndEdit : public CEdit
{
public:
	CUISftRsltWndEdit(const CString& strType);
	virtual ~CUISftRsltWndEdit();

public:
	CUISftRsltWndInterface* m_pResultWndInterface;
	CString m_strType;		//number 或者string，为number时要对用户输入的数据进行限制

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChange();
	afx_msg void OnEnKillfocus();
};