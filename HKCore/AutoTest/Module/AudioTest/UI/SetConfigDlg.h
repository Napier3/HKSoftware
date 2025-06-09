#pragma once
#include "../../../AudioTest/resource.h"
#include "../../../AudioTest/AudioTest.h"
//#include "../../../AudioTest/EditEx.h"
#include "EditEx.h"
#include "../../../../Module/WndGroupMngr/XUIAutoAdjTool.h"

// CSetConfigDlg �Ի���

class CSetConfigDlg : public CDialog,public CXUIAdjItem_Area
{
	DECLARE_DYNAMIC(CSetConfigDlg)

public:
	CSetConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetConfigDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��	
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
