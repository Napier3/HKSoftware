#pragma once
#include "../../../iSmartTestWzd/Resource.h"

// CWzdDlg_Advise �Ի���

class CWzdDlg_Advise : public CDialog
{
	DECLARE_DYNAMIC(CWzdDlg_Advise)

public:
	CWzdDlg_Advise(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWzdDlg_Advise();

// �Ի�������
	enum { IDD = IDD_ADVISE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
