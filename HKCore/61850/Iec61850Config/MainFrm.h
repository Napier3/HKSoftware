// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "OutputWnd.h"
#include "..\..\Module\XfileMngrBase\XFileDockablePane.h"
#include "IecfgDeviceDockablePane.h"
#include "..\Module\IecCfgTool\IecCfgTool.h"
#include "..\..\Module\MfcCtrlEx\TrayIcon.h"


class CMainFrame : public CMDIFrameWndEx, public CXFileOptrMsgRcvWnd
{
	DECLARE_DYNAMIC(CMainFrame)

public:
	virtual BOOL XCopyFile(const CString &strSrcFile, const CString &strDestFile, BOOL bFailIfExists);
	virtual DWORD XOpenXFile(CXFile *pFile);
	virtual DWORD XDeleteXFile(CXFile *pFile);
	virtual DWORD XDeleteXFolder(CXFolder *pFolder);
	virtual DWORD XEditXFile(CXFile *pFile, const CString &strDestName);
	virtual DWORD XCanEditXFolder(CXFolder *pFolder);
	virtual UINT GetImgIndex(CExBaseObject *pObj);

	virtual DWORD OpenIecfgFile(const CString &strIecfgFile,BOOL bAutoGenerate);
	virtual DWORD XDownLoad(CExBaseObject *pXFileObj);
	virtual DWORD XUpload(CExBaseObject *pXFileObj);


public:
	CMainFrame();

// 属性
public:
	CXFolder* GetCurrXFolder();

// 操作
public:
	void ShowIecCfgFileTitleToStatusBar(const CString &strFile);
	void ShowIecCfgFileTitleToStatusBar(CIecCfgFile *pIecfgFile);
	void ShowIecfgFileDevice(CIecCfgFile *pIecfgFile);
	void ShowIecfgFileDevice(CIecCfgFileDevice *pIecfgFileDevice);

	void IntRibbonByDispMode();
	void CloseAllIecfgDeviceFrame(){m_wndIecfgDevicePane.OnIecfgDeviceClose();}//zhouhj 20201210  在新建或新打开一个“*.iecfg”文件前，需将已经打开的子对象的文档视图关闭

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutputWnd        m_wndOutput;

	CXFileDockablePane m_wndXFilePane;
	CXFileDockablePane m_wndDeviceXFilePane;
	CIecfgDeviceDockablePane m_wndIecfgDevicePane;
	CTrayIcon m_TrayIcon;

// 生成的消息映射函数
protected:
	afx_msg LRESULT OnElectricTestMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetDispMode(WPARAM wPara,LPARAM lPara);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	void InitNormalRibbon();
	void InitPN466Ribbon();
	void InitAT02DRibbon();//周宏军  20200610 增加AT02D相关按钮
	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
// 	afx_msg void OnFileSave();
// 	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
// 	afx_msg void OnFileSaveAs();
// 	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnViewIeccfgFilePane();
	afx_msg void OnUpdateViewIeccfgFilePane(CCmdUI *pCmdUI);
	afx_msg void OnViewIeccfgDeviceFilePane();
	afx_msg void OnUpdateViewIeccfgDeviceFilePane(CCmdUI *pCmdUI);
	afx_msg void OnViewModelUseHarm();
	afx_msg void OnUpdateViewModelUseHarm(CCmdUI *pCmdUI);
	afx_msg void OnVerifyVolCurChannel();
	afx_msg void OnUpdateVerifyVolCurChannel(CCmdUI *pCmdUI);
	afx_msg void OnViewLinkGout();
	afx_msg void OnUpdateViewLinkGout(CCmdUI *pCmdUI);
	afx_msg void OnViewAutoOpenLast();
	afx_msg void OnUpdateViewAutoOpenLast(CCmdUI *pCmdUI);
	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI *pCmdUI);
	afx_msg void OnFileImport();
	afx_msg void OnFileImportAT02D();//周宏军 20200616  增加AT02配置
	afx_msg void OnViewIeccfgDevicePane();
	afx_msg void OnUpdateViewIeccfgDevicePane(CCmdUI *pCmdUI);
	LRESULT OnXAtsSvrClientMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTrayNotification(WPARAM wParam,LPARAM lParam);
	afx_msg void OnAppExit();
};


