#pragma once

/*
	����������
*/

class CUISftRsltWndInterface;

class CUISftRsltWndEdit : public CEdit
{
public:
	CUISftRsltWndEdit(const CString& strType);
	virtual ~CUISftRsltWndEdit();

public:
	CUISftRsltWndInterface* m_pResultWndInterface;
	CString m_strType;		//number ����string��ΪnumberʱҪ���û���������ݽ�������

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChange();
	afx_msg void OnEnKillfocus();
};