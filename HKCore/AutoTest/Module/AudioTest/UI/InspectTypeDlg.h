#pragma once
#include "afxwin.h"
#include "../../../AudioTest/resource.h"
#include "AudioDlgBase.h"
#include "ListCtrlEx.h"

// CInspectTypeDlg �Ի���
class CInspectTypeDlg : /*public CDialog,*/public CAudioDlgBase
{
	DECLARE_DYNAMIC(CInspectTypeDlg)
public:
	CInspectTypeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInspectTypeDlg();
	virtual BOOL OnInitDialog();
	enum { IDD = IDD_DIALOG_INSPECTTYPE };

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;
	CStatic m_static;
	//CListCtrl m_ListCtrl_InspectType;
	CListCtrlEx m_ListCtrl_InspectType;
};
