#pragma once
#include "../../../AudioTest/resource.h"
//#include "../../Module/WndGroupMngr/XUIAutoAdjTool.h"
#include "AudioDlgBase.h"
#include "ListCtrlEx.h"
// CProtocolTypeDlg �Ի���

class CProtocolTypeDlg : /*public CDialog,*/public CAudioDlgBase
{
	DECLARE_DYNAMIC(CProtocolTypeDlg)

public:
	CProtocolTypeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProtocolTypeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROTOCOLTYPE };
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	DECLARE_MESSAGE_MAP()

public:
	CFont m_font;
	CStatic m_static;
	//CListCtrl m_ListCtrl_ProtocolType;
	CListCtrlEx m_ListCtrl_ProtocolType;
};
