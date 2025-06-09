#pragma once
#include "../../../AudioTest/resource.h"
#include "../../../AudioTest/AudioTest.h"
//#include "../../../AudioTest/EditEx.h"
#include "EditEx.h"
#include "../../../../Module/WndGroupMngr/XUIAutoAdjTool.h"

// CSetConfigDlg 对话框

class CSetConfigDlg : public CDialog,public CXUIAdjItem_Area
{
	DECLARE_DYNAMIC(CSetConfigDlg)

public:
	CSetConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetConfigDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SET_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持	
	virtual void XUI_InitAdjust();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOK();
	afx_msg void OnBnClickedButtonReturn();

private:
	/*CEdit    m_ctrlStarKey;
	CEdit    m_ctrlEndKey;
	CEdit    m_ctrlWakeUpKey;
	CEdit    m_ctrlTime;*/
	CEditEx    m_ctrlStarKey;
	CEditEx    m_ctrlEndKey;
	CEditEx    m_ctrlWakeUpKey;
	CEditEx    m_ctrlTime;
};
