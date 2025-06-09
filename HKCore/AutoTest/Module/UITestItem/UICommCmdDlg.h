#pragma once
#include "sysparagrid.h"

#include "UITestGlobalDefine.h"
#include "CommCmdGrid.h"
// CUICommCmdDlg �Ի���


class CUICommCmdDlg : public CDialog
{
	DECLARE_DYNAMIC(CUICommCmdDlg)

public:
	CUICommCmdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUICommCmdDlg();

// �Ի�������
	//enum { IDD = IDD_DLG_SYSPARAS };

private:
	CCommCmd* m_pTestItemCommCmd;
	CTestControlWnd* m_pWndMsgRcv;
	CString m_strType;

	//����CPU�ļ���
	CExBaseList m_setCpu;

	//��ǰCPU����Ӧ��CSet
	CCpu* m_pCurCpu;
	CExBaseList m_listNodeDatas;

	//��ǰCCommCmd��Ӧ��CDevice
	CDevice* m_pCurDevice;

	//��ʼ��Tabҳ
	void InitTabandCpu();
	
	//�л���ǰCPU
	void ChangeCurCpu(CCpu* pChangeCpu);
	void CreateCommCmdGrid();

public:
	CExBaseList* GetDatas()	{	return &m_listNodeDatas;	}
	void InitTestItem(CCommCmd* pTestItemCommCmd, CTestControlWnd *pWndMsgRcv);
	void FinishTestCmmCmdItem();
	void FinishTestItem();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CCommCmdGrid *m_pGridCmdDatas;
	CTabCtrl	m_tabParaSel;
	CButton m_btnNext;

	CRect rectWin,rectTab,rectGrid,rectBtnNext;

	void InitMacroRect();

	CFont m_font;
	LOGFONT m_lfFont;
	CFont m_fontRsltCtrl;

	afx_msg void OnBnClickedOk();
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnEndEdit(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
