
// TestGridVs2008Dlg.h : ͷ�ļ�
//

#pragma once

#include "MyGridctrl.h"

// CTestGridVs2008Dlg �Ի���
class CTestGridVs2008Dlg : public CDialog
{
// ����
public:
	CTestGridVs2008Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	CMyGridCtrl m_gridex;
	void CreateGrid();

// �Ի�������
	enum { IDD = IDD_TESTGRIDVS2008_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
