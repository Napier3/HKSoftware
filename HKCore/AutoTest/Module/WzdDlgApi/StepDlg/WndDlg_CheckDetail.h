#pragma once
#include "../../../iSmartTestWzd/Resource.h"

// CWndDlg_CheckDetail �Ի���

class CWndDlg_CheckDetail : public CDialog
{
	DECLARE_DYNAMIC(CWndDlg_CheckDetail)

public:
	CWndDlg_CheckDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWndDlg_CheckDetail();

// �Ի�������
	enum { IDD = IDD_CHECK_DETAIL_INFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
