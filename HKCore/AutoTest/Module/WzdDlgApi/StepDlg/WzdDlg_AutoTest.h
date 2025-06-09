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

//人工检验自动确认 状态
enum tagPreTestItemState
{
	Pre_TestItem_Confirm_N = 0,
	Pre_TestItem_Confirm_Y
};
//自动更新结果   状态
enum tagAutoTestResultState
{
	Auto_TestResult_N = 0,
	Auto_TestResult_Y
};

//日志输出的类型 
enum tagLogType
{
	Log_Type_Error = 0,
	Log_Type_Other,
	Log_Type_NULL
};

// WzdDlg_AutoTest 对话框
class CWzdDlg_AutoTest : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzdDlg_AutoTest)

public:
	CWzdDlg_AutoTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWzdDlg_AutoTest();

// 对话框数据
	enum { IDD = IDD_AUTOTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持	
	DECLARE_MESSAGE_MAP()	

	virtual void XUI_InitAdjust();
	virtual BOOL OnInitDialog();
	virtual BOOL DoNext();
public:
	//整体初始化
	virtual void OnInitialUpdate();

public:
	//初始化 装置信息 
	void InitDeviceInfo();
	//初始化 状态文字合图标
	void initWholeState();
	//初始化 按钮 图标
	void initButton();
	//启动   关闭 定时器
	void StarTimer();
	void EndTimer();
	//清空结果界面的 测试结果
	void ClearResult();

	//设置数据
	void setDataInfo(CDvmDataset* pGlobalDatas,CDevice* pDeviceDatas);
	//更新 测试项状态
	//void OnItemStateChanged(CGbItemBase *pItem);

	//整体 测试状态的改变
	void SetAutoTestState(int nState);
	int GetAutoTestState()	{	return m_nAutoTestState;	}
	//设置当前ListBox 内容
	void SetCurrentLog(CString strText,int nFlag = -1);
	//设置网络状态：蓝牙 or 以太网
	//void SetNetState(long nState);

	//按钮状态刷新
	void EnableBtnBooth();
	//Static 刷新问题 
	void UpdateText(CStatic *pStatic);
	long GetPerConfirm()	{	return m_nPreTestItemState;	}

	//测试 功能
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
	//消息响应函数
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//自动测试 开始 停止 结束 系统设置  蓝牙设置
	afx_msg void OnBnClickedStarButton();
	afx_msg void OnBnClickedStopButton();
	afx_msg void OnBnClickedFinishButton();
	afx_msg void OnBnClickedSetButton();
	afx_msg void OnBnClickedBoothButton();
	//Log 
	afx_msg void OnLogDelete();
	afx_msg void OnLogClear();
	//人工检验自动确认
	afx_msg void OnBnClickedPeoAutoConfirmCheck();
	//检验项目结果自动更新
	afx_msg void OnBnClickedTestItemAutoCheck();
	//作业指导书选中 响应
	afx_msg LRESULT OnTestStepChange(WPARAM wP,LPARAM lP);
	//测试不合格项目 定位
	afx_msg LRESULT OnFindFailItem(WPARAM wP,LPARAM lP);

	//更新 测试项状态
	afx_msg LRESULT OnItemStateChanged(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnTestFinished(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnTestStoped(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnTestCreated(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnTestStarted(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnReport(WPARAM wP,LPARAM lP);
	//设置网络状态：蓝牙 or 以太网
	afx_msg LRESULT OnSetNetState(WPARAM wP,LPARAM lP);
	afx_msg LRESULT OnInputData(WPARAM wP,LPARAM lP);


private:
	//全局数据  设置装置信息
	CDvmDataset*			m_pGlobalDataList;
	CDevice*				m_pDeviceDataList;
	//作业指导书  检查项目是
	CItems					m_TestStepDataList;
	//自动测试 整体状态
	int						m_nAutoTestState;
	//蓝牙状态：启用、禁用
	int                     m_nState_BlueTooth;  
	map<int,HICON>			m_mapStateIcon;
	//自动更新结果   
	int						m_nTestResultState;
	//人工检验自动确认
	int						m_nPreTestItemState;
	bool					m_bIsStarTimer;

	 //当前正在测试的项目
	CGbItemBase*            m_pCurTestItem;
	//界面分割
	//CSplitterWnd			m_Spliter;
	CSplitterWnd_Ex			m_Spliter;
	CFrameWnd*				m_pFrame;
	//子界面，显示在4个分割界面中
	CWzd_TestStepDlg		m_dlgTestStep;
	CWzd_CheckItemDlg		m_dlgCheckItem;
	CWzd_FailItemDlg		m_dlgFailItem;
	CWzd_CheckResultDlg		m_dlgCheckResult;

	InputDataDlg*			m_pInputDlg;

	// 分割线
	CStatic					m_LineStatic;
	// 设备的基本信息
	CStatic					m_DeviceInfoStatic;
	// 日志输出窗口
	//CListBox				m_ctrlLogListBox;
	CListBoxEx				m_ctrlLogListBox;
	//CListBoxLog				m_ctrlLogListBox;

	// 确定分割区域的整体大小
	CButton					m_ctrlBtnCutsomWin;
	//CMFCButton					m_ctrlBtnCutsomWin;
	// 检验项目测试状态
	CStatic					m_TestStatic1;
	CStatic					m_TestStatic2;
	// 保护装置通信状态
	CStatic					m_CommStatic1;
	CStatic					m_CommStatic2;
	// 测试仪器状态
	CStatic					m_OutputStatic1;
	CStatic					m_OutputStatic2;
	// 网卡状态
	CStatic					m_TcpStatic1;
	CStatic					m_TcpStatic2;
	// 蓝牙通信状态
	CStatic					m_ToothStatic1;
	CStatic					m_ToothStatic2;

	// 自动测试功能按钮 开始 停止 结束
	//CButton					m_ctrlBtnStarTest;
	//CButton					m_ctrBtnStopTest;
	//CButton					m_CtrlBtnFinishTest;
	//CButton					m_ctrlBtnSet;
	CWzdDlgButton					m_ctrlBtnStarTest;
	CWzdDlgButton					m_ctrlBtnStopTest;
	CWzdDlgButton					m_ctrlBtnFinishTest;
	CWzdDlgButton					m_ctrlBtnSet;
	CWzdDlgButton					m_ctrlBtnBooth;
	// 人工检验自动确认
	CButton							m_ctrlBtnPerConfirm;
	// 检验项目结果自动更新
	CButton							m_ctrlBtnTestResultAuto;
	
	
};
