#pragma once
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"
#include <afxwin.h>
#include <afxcmn.h>
#include <afxext.h>
#include <stdio.h>
#include <map>
#include <list>

#include "../../../Module/GuideBook/DataSet.h"
#include "../../../Module/GuideBook/Items.h"
#include "../../../Module/GuideBook/Device.h"
#include "../../../../Module/DataMngr/DvmDataset.h"
#include "../StepCtrl/WzdDlgButton.h"

#include "Wzd_CheckItemDlg.h"
#include "Wzd_CheckResultDlg.h"
#include "Wzd_FailItemDlg.h"
#include "Wzd_TestStepDlg.h"
#include "./Wzd_ConfigSetDlg.h"
#include "SplitterWndEx.h"
#include "InputDataDlg.h"
#include "ListBoxEx.h"
#define XIDC_SET_GRID   2380

#define  WM_TEST_STATE_CHANGE WM_USER+1010
#define  WM_TEST_STATE_STAR WM_USER+1011
#define  WM_TEST_STATE_STOP WM_USER+1012
#define  WM_TEST_STATE_FINISH WM_USER+1013
#define  WM_TEST_STATE_CREATE WM_USER+1014
#define  WM_TEST_STATE_REPORT WM_USER+1015
#define  WM_TEST_STATE_BOOTH WM_USER+1016
#define  WM_TEST_ONINPUTDATA WM_USER+1017

#define  TimeEvent_State   7

enum tagAutoTestState
{
	AUTOTEST_NULL = 0,
	AUTOTEST_CREATE,
	AUTOTEST_START,
	AUTOTEST_STOP,
	AUTOTEST_FINISH,
	AUTOTEST_CLOSE
};

//�˹������Զ�ȷ�� ״̬
enum tagPreTestItemState
{
	Pre_TestItem_Confirm_N = 0,
	Pre_TestItem_Confirm_Y
};
//�Զ����½��   ״̬
enum tagAutoTestResultState
{
	Auto_TestResult_N = 0,
	Auto_TestResult_Y
};

//��־��������� 
enum tagLogType
{
	Log_Type_Error = 0,
	Log_Type_Other,
	Log_Type_NULL
};

// WzdDlg_AutoTest �Ի���
class CWzdDlg_AutoTest : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzdDlg_AutoTest)

public:
	CWzdDlg_AutoTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWzdDlg_AutoTest();

// �Ի�������
	enum { IDD = IDD_AUTOTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��	
	DECLARE_MESSAGE_MAP()	

	virtual void XUI_InitAdjust();
	virtual BOOL OnInitDialog();
	virtual BOOL DoNext();
public:
	//�����ʼ��
	virtual void OnInitialUpdate();

public:
	//��ʼ�� װ����Ϣ 
	void InitDeviceInfo();
	//��ʼ�� ״̬���ֺ�ͼ��
	void initWholeState();
	//��ʼ�� ��ť ͼ��
	void initButton();
	//����   �ر� ��ʱ��
	void StarTimer();
	void EndTimer();
	//��ս������� ���Խ��
	void ClearResult();

	//��������
	void setDataInfo(CDvmDataset* pGlobalDatas,CDevice* pDeviceDatas);
	//���� ������״̬
	//void OnItemStateChanged(CGbItemBase *pItem);

	//���� ����״̬�ĸı�
	void SetAutoTestState(int nState);
	int GetAutoTestState()	{	return m_nAutoTestState;	}
	//���õ�ǰListBox ����
	void SetCurrentLog(CString strText,int nFlag = -1);
	//��������״̬������ or ��̫��
	//void SetNetState(long nState);

	//��ť״̬ˢ��
	void EnableBtnBooth();
	//Static ˢ������ 
	void UpdateText(CStatic *pStatic);
	long GetPerConfirm()	{	return m_nPreTestItemState;	}

	//���� ����
	//void OnTestFinished();
	//void OnTestStoped();
	void OnTestAppEvent(const CString& strEvent);
	void OnEngineEvent(const CString& strEvent);
	//void OnTestCreated();
	void OnOpenGbrptFileFailed();
	void OnTestProcess(CExBaseList* pSttParas);
	void OnReTestFinished(CExBaseList* pSttParas);
	//void OnTestStarted();
	//void OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs);
	//void OnReport(CGbItemBase *pItem);

	void ClearInputDlg();

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//��Ϣ��Ӧ����
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//�Զ����� ��ʼ ֹͣ ���� ϵͳ����  ��������
	afx_msg void OnBnClickedStarButton();
	afx_msg void OnBnClickedStopButton();
	afx_msg void OnBnClickedFinishButton();
	afx_msg void OnBnClickedSetButton();
	afx_msg void OnBnClickedBoothButton();
	//Log 
	afx_msg void OnLogDelete();
	afx_msg void OnLogClear();
	//�˹������Զ�ȷ��
	afx_msg void OnBnClickedPeoAutoConfirmCheck();
	//������Ŀ����Զ�����
	afx_msg void OnBnClickedTestItemAutoCheck();
	//��ҵָ����ѡ�� ��Ӧ
	afx_msg LRESULT OnTestStepChange(WPARAM wP,LPARAM lP);
	//���Բ��ϸ���Ŀ ��λ
	afx_msg LRESULT OnFindFailItem(WPARAM wP,LPARAM lP);

	//���� ������״̬
	afx_msg LRESULT OnItemStateChanged(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnTestFinished(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnTestStoped(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnTestCreated(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnTestStarted(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnReport(WPARAM wP,LPARAM lP);
	//��������״̬������ or ��̫��
	afx_msg LRESULT OnSetNetState(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnInputData(WPARAM wP,LPARAM lP);


private:
	//ȫ������  ����װ����Ϣ
	CDvmDataset*			m_pGlobalDataList;
	CDevice*				m_pDeviceDataList;
	//��ҵָ����  �����Ŀ��
	CItems					m_TestStepDataList;
	//�Զ����� ����״̬
	int						m_nAutoTestState;
	//����״̬�����á�����
	int                     m_nState_BlueTooth;  
	map<int,HICON>			m_mapStateIcon;
	//�Զ����½��   
	int						m_nTestResultState;
	//�˹������Զ�ȷ��
	int						m_nPreTestItemState;
	bool					m_bIsStarTimer;

	 //��ǰ���ڲ��Ե���Ŀ
	CGbItemBase*            m_pCurTestItem;
	//����ָ�
	//CSplitterWnd			m_Spliter;
	CSplitterWnd_Ex			m_Spliter;
	CFrameWnd*				m_pFrame;
	//�ӽ��棬��ʾ��4���ָ������
	CWzd_TestStepDlg		m_dlgTestStep;
	CWzd_CheckItemDlg		m_dlgCheckItem;
	CWzd_FailItemDlg		m_dlgFailItem;
	CWzd_CheckResultDlg		m_dlgCheckResult;

	InputDataDlg*			m_pInputDlg;

	// �ָ���
	CStatic					m_LineStatic;
	// �豸�Ļ�����Ϣ
	CStatic					m_DeviceInfoStatic;
	// ��־�������
	//CListBox				m_ctrlLogListBox;
	CListBoxEx				m_ctrlLogListBox;
	//CListBoxLog				m_ctrlLogListBox;

	// ȷ���ָ�����������С
	CButton					m_ctrlBtnCutsomWin;
	//CMFCButton					m_ctrlBtnCutsomWin;
	// ������Ŀ����״̬
	CStatic					m_TestStatic1;
	CStatic					m_TestStatic2;
	// ����װ��ͨ��״̬
	CStatic					m_CommStatic1;
	CStatic					m_CommStatic2;
	// ��������״̬
	CStatic					m_OutputStatic1;
	CStatic					m_OutputStatic2;
	// ����״̬
	CStatic					m_TcpStatic1;
	CStatic					m_TcpStatic2;
	// ����ͨ��״̬
	CStatic					m_ToothStatic1;
	CStatic					m_ToothStatic2;

	// �Զ����Թ��ܰ�ť ��ʼ ֹͣ ����
	//CButton					m_ctrlBtnStarTest;
	//CButton					m_ctrBtnStopTest;
	//CButton					m_CtrlBtnFinishTest;
	//CButton					m_ctrlBtnSet;
	CWzdDlgButton					m_ctrlBtnStarTest;
	CWzdDlgButton					m_ctrlBtnStopTest;
	CWzdDlgButton					m_ctrlBtnFinishTest;
	CWzdDlgButton					m_ctrlBtnSet;
	CWzdDlgButton					m_ctrlBtnBooth;
	// �˹������Զ�ȷ��
	CButton							m_ctrlBtnPerConfirm;
	// ������Ŀ����Զ�����
	CButton							m_ctrlBtnTestResultAuto;
	
	
};
