#pragma once
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/GuideBook/Items.h"
#include "ListCtrlEx.h"
// CWzd_TestStepDlg �Ի���
#define  WM_TEST_STEP_CHANG WM_USER+1000

class CWzd_TestStepDlg : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzd_TestStepDlg)

public:
	CWzd_TestStepDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWzd_TestStepDlg();

// �Ի�������
	enum { IDD = IDD_TEST_STEP_DIALOG };
	virtual void XUI_InitAdjust();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	
public:
	//��ʼ�� �б��ֵ
	void InitCheckStepInfo(CItems& stepItems);
	//�������У����²���ֵ ���Ե�״̬ͼ��
	void UpdateCheckStepState(CGbItemBase* pStep);
	CGbItemBase* UpdateCheckStepState2();
protected:
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void OnLvnGetdispinfoCheckStepList(NMHDR *pNMHDR, LRESULT *pResult);
	//��Ϣ��Ӧ����
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMClickCheckStepList(NMHDR *pNMHDR, LRESULT *pResult);

private:
	// ��ҵָ����
	//CListCtrl m_ctrlCheckStepList;
	CListCtrlEx m_ctrlCheckStepList;
	CImageList m_ImageList;
};
