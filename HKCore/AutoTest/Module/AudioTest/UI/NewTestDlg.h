#pragma once
#include "afxcmn.h"
#include "../UI/MainDlg.h"
#include "../UI/DviceTypeDlg.h"
#include "../UI/InspectTypeDlg.h"
#include "../UI/ProtocolTypeDlg.h"
#include "../UI/TestTemplateDlg.h"
#include "../UI/DeviceIPInspect.h"
#include "../../../AudioTest/resource.h"
#include "../../../AudioTest/AudioTest.h"
#include "ListCtrlEx.h"
#include "../../../../Module/WndGroupMngr/XUIAutoAdjTool.h"
#include "afxwin.h"
#include <map>
#include "AudioDlgBase.h"
using namespace std;
// CNewTest �Ի���

class CNewTestDlg : /*public CDialog,*/ public CAudioDlgBase,public CXUIAdjItem_Area 
{
	DECLARE_DYNAMIC(CNewTestDlg)

public:
	CNewTestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewTestDlg();
	enum { IDD = IDD_DIALOG_NEWTEST };
	virtual void XUI_InitAdjust();
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV ֧��
	virtual bool DealAnswer(CString strResult);

protected:
	HICON m_hIcon;
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnBack();
	afx_msg void OnBnClickedBtnReturn();
	afx_msg void OnBnClickedBtnBackpage();
	afx_msg void OnBnClickedBtnNextpage();
	afx_msg void OnNMDblclkListOperateSteps(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListoperatesteps(NMHDR *pNMHDR, LRESULT *pResult);

	//afx_msg void OnNMCustomdrawList2(NMHDR *pNMHDR, LRESULT *pResult);

	CString GetResultAnswer(int nDlgType);
	// 1 ��һ����  2 ��һ����,  -1 ��ȡ��ǰ
	int SetCurrentIndex(int nBtnFlag = -1);
	void SetCurrentDlg(int nCurrentIndex,int nLastIndex);
	int ShowKeyTipBox(CString strResult = "");
	void ConfirmResultAnswer(int nConfirmFlg);


	CString GetPath();
	CString GetCurrentResultAnswer();

public:
	CDialog				m_AreaSet;
	CFont				m_font;
	CStatic				m_static;
	//CListCtrl			m_ListOperateSteps;
	CListCtrlEx			m_ListOperateSteps;
	
	CInspectTypeDlg		m_dlgInspectType;
	CDviceTypeDlg		m_dlgDeviceType;
	CProtocolTypeDlg	m_dlgPotocolType;
	CTestTemplateDlg	m_dlgTestTemplate;
	CDeviceIPInspect	m_dlgDeviceIPInspect;
	map<int,CDialog*>   m_mapDlg;
	CDialog*		    m_pCurrentDlg;


	CString strCheckType;
	//0 IPƴʧ�� 1 IPƴ�ɹ�  2 ȷ����ʼ����  3 û�п�ʼ����
	//int					m_nReturnFlag;
};
//extern CNewTestDlg* g_pNewTestDlg;
