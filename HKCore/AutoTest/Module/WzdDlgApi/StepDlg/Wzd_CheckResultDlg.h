#pragma once
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"

#include "../../../Module/GuideBook/Items.h"
#include "afxwin.h"
#include "ListCtrlEx.h"
#include "../StepCtrl/UIDrawer.h"

// CWzd_CheckResultDlg �Ի���

class CWzd_CheckResultDlg : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzd_CheckResultDlg)

public:
	CWzd_CheckResultDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWzd_CheckResultDlg();

// �Ի�������
	enum { IDD = IDD_CHECK_RESULT_DIALOG };
	virtual void XUI_InitAdjust();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	

public:
	//��ʼ�� �б��ֵ
	void InitCheckResultInfo();
	//��ʼ�� combox�б��ֵ
	void InitCheckBoxInfo();
	//���ñ������
	void SetCheckResultInfo(CReports* pReports);
	void SetCurrentCheckResultInfo(CReport* pReport);
	void ClearResult();

protected:
	//��Ϣ��Ӧ����
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnSelchangeCheckCountCombo();

private:
	// ��Ŀ�������Ϣ
	//CListCtrl m_ctrlItemResutList;
	CListCtrlEx m_ctrlItemResutList;
	//CComboBox m_ctrlCBBChectCount;
	CUIComboBox	m_ctrlCBBChectCount;
	CImageList m_ImageList;

public:
	CStatic m_Static3;
};
