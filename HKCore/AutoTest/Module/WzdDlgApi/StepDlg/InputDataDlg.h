#pragma once
#include "../StepCtrl/UIDrawer.h"
#include "../../../iSmartTestWzd/Resource.h"
#include <vector>

// InputDataDlg �Ի���

class InputDataDlg : public CUIDialog
{
	DECLARE_DYNAMIC(InputDataDlg)

public:
	InputDataDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InputDataDlg();

// �Ի�������
	enum { IDD = IDD_INPUTDATADLG };

private:
	long m_nListID;
	long m_nEditID;
	CWnd* m_pLastCtrl;
	CExBaseList* m_pDatas;
	CExBaseList* m_pMsgs;
	CExBaseList* m_pItem;
	std::vector<CWnd*> m_vecCtrls;
	std::vector<CWnd*> m_vecStatics;

	CUIButton m_btnOK;

	void FitSize(CStatic* pTxt, CRect& rc, const CString& strText);
	void InitMsgBox(CExBaseList* pMsgs);
	void InitListBox(CExBaseList* pDatas);
	void InitEditBox(CExBaseList* pDatas);
	void DoOK();

public:
	void InitDlg(CExBaseList* pDatas, CExBaseList* pMsgs, CExBaseList *pItem);
	void KillTimer();
	void StartTimer();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
};
