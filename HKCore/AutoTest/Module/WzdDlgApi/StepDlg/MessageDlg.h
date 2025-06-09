#pragma once

#include "../StepCtrl/UIDrawer.h"
#include "../../../iSmartTestWzd/Resource.h"

// MessageDlg 对话框

class MessageDlg : public CUIDialog
{
	DECLARE_DYNAMIC(MessageDlg)

private:
	CUIButton m_btnOK;
	CUIButton m_btnOK2;
	CUIButton m_btnCancel;
	CUIButton m_btnIcon;
	CStatic m_txtText;

	CString m_strText;
	CString m_strTitle;

public:
	enum tagMode{
		YES,
		YESANDNO,
		ERRYES,
		ERRYESANDNO
	}m_nMode;

	MessageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MessageDlg();

// 对话框数据
	enum { IDD = IDD_MESSAGEBOX };

	static INT_PTR MessageBox(CString strTitle, CString strText, tagMode nMode = YESANDNO);

protected:
	void SetMessage(CString strTitle, CString strText, tagMode nMode = YESANDNO);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
