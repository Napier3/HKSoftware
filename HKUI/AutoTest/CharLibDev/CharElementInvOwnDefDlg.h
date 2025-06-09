#pragma once

#include "CharElmentBaseDlg.h"
#include "InvOwnDefGrid.h"
#include "../Module/Characteristic/CharElementPoint.h"
#include "afxwin.h"

// CCharElementInvOwnDefDlg 对话框

class CCharElementInvOwnDefDlg : public CDialog , public CCharElmentBaseDlg, public CExBaseListGridOptrInterface
{
	DECLARE_DYNAMIC(CCharElementInvOwnDefDlg)

public:
	CCharElementInvOwnDefDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCharElementInvOwnDefDlg();

	virtual void CreateDlg(CWnd *pParent) ; 
	virtual void GetData(); 
	virtual void ShowData(); 	
	virtual BOOL IsEnable();

// 对话框数据
	enum { IDD = IDD_DIALOG_INV_OWNDEF };

public:
	CInvOwnDefGrid m_gridInvOwnDef;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	virtual void OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);

public:
	virtual BOOL OnInitDialog();
	void EnableButtons();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strXMAX;
	CString m_strTMAX;
	CCharElementPoints m_oPoints; //测试点集合

	CButton m_btnInvOwnDefDel;
	CButton m_btnInvOwnDefDelAll;
	CButton m_btnInvOwnDefAddPrev;
	CButton m_btnInvOwnDefAddAfter;

public:
	afx_msg void OnBnClickedInvowndefAddpoint();
	afx_msg void OnBnClickedInvowndefDelpoint();
	afx_msg void OnBnClickedInvowndefDelallpoint();
	afx_msg void OnBnClickedInvowndefAddpointhead();
	afx_msg void OnBnClickedInvowndefAddpointprev();
	afx_msg void OnBnClickedInvowndefAddpointafter();
};
