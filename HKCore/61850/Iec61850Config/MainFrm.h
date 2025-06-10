// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.h : CMainFrame ��Ľӿ�
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

// ����
public:
	CXFolder* GetCurrXFolder();

// ����
public:
	void ShowIecCfgFileTitleToStatusBar(const CString &strFile);
	void ShowIecCfgFileTitleToStatusBar(CIecCfgFile *pIecfgFile);
	void ShowIecfgFileDevice(CIecCfgFile *pIecfgFile);
	void ShowIecfgFileDevice(CIecCfgFileDevice *pIecfgFileDevice);

	void IntRibbonByDispMode();
	void CloseAllIecfgDeviceFrame(){m_wndIecfgDevicePane.OnIecfgDeviceClose();}//zhouhj 20201210  ���½����´�һ����*.iecfg���ļ�ǰ���轫�Ѿ��򿪵��Ӷ�����ĵ���ͼ�ر�

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutputWnd        m_wndOutput;

	CXFileDockablePane m_wndXFilePane;
	CXFileDockablePane m_wndDeviceXFilePane;
	CIecfgDeviceDockablePane m_wndIecfgDevicePane;
	CTrayIcon m_TrayIcon;

// ���ɵ���Ϣӳ�亯��
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
	void InitAT02DRibbon();//�ܺ��  20200610 ����AT02D��ذ�ť
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
	afx_msg void OnFileImportAT02D();//�ܺ�� 20200616  ����AT02����
	afx_msg void OnViewIeccfgDevicePane();
	afx_msg void OnUpdateViewIeccfgDevicePane(CCmdUI *pCmdUI);
	LRESULT OnXAtsSvrClientMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTrayNotification(WPARAM wParam,LPARAM lParam);
	afx_msg void OnAppExit();
};


