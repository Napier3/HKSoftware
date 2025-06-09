#pragma once
#include "../../../AudioTest/resource.h"
#include "AudioDlgBase.h"
#include "ListCtrlEx.h"
// CDviceTypeDlg 对话框

class CDviceTypeDlg : /*public CDialog ,*/public CAudioDlgBase
{
	DECLARE_DYNAMIC(CDviceTypeDlg)

public:
	CDviceTypeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDviceTypeDlg();
// 对话框数据
	enum { IDD = IDD_DIALOG_DEVICETYPE };
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);  
	//void SetBackPage();
	//void SetNextPage();
	//CString GetDevType();


	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	  // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	CString GetDevID();

public:
	CFont m_font;
	CStatic m_static;

	/*int m_nScollMin;
	int m_nScollMax;
	int m_nPageStep;
	int m_nCurrentPagePos;*/

	//CListCtrl m_ListCtrl_DviceType;
	CListCtrlEx m_ListCtrl_DviceType;
};
