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

// Iec61850Config.h : Iec61850Config 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#include "..\Module\IecCfgTool\IecCfgTool.h"
#include "..\..\AutoTest\Module\Interface\MacroTestEngine.h"
#include "..\Module\SCL\SclIecCfgDatas.h"
#include "..\..\Module\MfcCtrlEx\XSplashWndBase.h"
#include "XLanguageResourceIec_61850Cfg.h"
#include "..\Module\XLanguageResourceIec.h"
#include "..\..\Module\XLanguage\XLangWndAdjust.h"
#include "..\..\Module\XLanguage\XLangRibbonCtrls.h"
//电气量测试消息，通过接口指定给底层测试功能测试
#define	WM_ELECTRIC_TEST	(WM_USER+1000)

#define WM_ON_SETTING_DISP_MODE  (WM_USER+1201)

// CIec61850ConfigApp:
// 有关此类的实现，请参阅 Iec61850Config.cpp
//

#define IECCFG_CTRL_GAP   2

class CIecConfigFrame;

class CIec61850ConfigApp : public CWinAppEx
{
public:
	CIec61850ConfigApp();

	CIecCfgFile* OpenIecCfgFileEx(const CString &strFile,BOOL bAutoGenerate);
	CIecCfgFile* AutoGeneNewIecfgFile(const CString &strSrcIecfgFile,CString strNewIecfgFile);
	void ShowIecCfgFileTitleToStatusBar(const CString &strFile);
	void ShowIecCfgFileTitleToStatusBar(CIecCfgFile *pIecfgFile);
	void UpdateIecCfgFilesComboBox();
	CIecConfigFrame* CreateNewIecCfgFrame(CIecCfgDatasMngr *pIecCfgDatasMngr);
	CIecConfigFrame* CreateNewIecCfgFrame_FirstIecCfgDatasMngr(CIecCfgFileDevice *pIecfileDevice);
	
	void CloseIecfgFrame(CExBaseObject *pIecCfgDatasMngr, BOOL bDelete);
	void UpdateIecfgFileTitle(CExBaseObject *pIecCfgDatasMngr);
	void SaveIecfg(CExBaseObject *pIecfg);

	BOOL SaveIecfgFile(CIecCfgFile *pIecCfgFile, CDocument *pDoc,BOOL bIsAT02D_CFG = FALSE);//周宏军 20200616  增加AT02配置
	BOOL SaveAsIecfgFile(CIecCfgFile *pIecCfgFile, CDocument *pDoc,BOOL bIsAT02D_CFG = FALSE);
	BOOL SaveIecfgFile(const CString &strIecfgFile);

	void CreateNewSclFrame(const CString &strTscdFile, const CString &strIedId);

	void OnFileNewDevice(CIecCfgFileDevice *pIecfileDevice);

public:
	CSclIed *m_pCurrSelSclIed;
	CMDIChildWndEx *m_pSclFileFrame;

	BOOL IsCfgInStationTest()	{	return m_bIsCfgInStationTest;	}
	void SetCfgInStationTest(BOOL b=TRUE)	{	m_bIsCfgInStationTest = b;	}
	void OpenTscdFile(const CString &strTscdFile);
	void CloseSclFileFrame();//zhouhj 20200807
	void SetDispMode(long nDispMode);//zhouhj 20200902  用于PNI302调用设置界面

private:
	BOOL m_bIsCfgInStationTest;

private:
	BOOL InitTemplate();
	void OpenDocTemplate(CMultiDocTemplate *pDocTemplate, CView **pView, CMDIChildWndEx **pFrame);
	void OpenAllFrame();
	CIecConfigFrame* CreateNewIecCfgFrame(CIecCfgFile *pIecCfgFile);
	void CreateNewIecCfgDeviceFrame(CIecCfgFile *pIecCfgFile);
	void OpenLastFiles();
	void CreateNewSclFrame(CSclFile *pSclFile);
	void CreateNewStateFrame();

	CMultiDocTemplate *m_pIecConfigDocTemplate;
	CMultiDocTemplate *m_pSclFileDocTemplate;
	CMultiDocTemplate *m_pStateDocTemplate;

	CMDIChildWndEx *m_pStateToolFrame;
//MacroTest
protected:
	MacroTest::IMacroTestEngine GetMacroTestEngine(const CString &strProgID);
	void ReleaseMacroTestEngine();
	void PostFinishMsg_ExternExc(CIecCfgFile *pIecCfgFile);//zhouhj 在外部通过COM接口调用时，修改完配置文件后，或新建保存配置文件后，给外部程序发送消息

	MacroTest::IMacroTestEngine m_pMacroTestEngine;
	MacroTest::IMacroTest m_oMacroTest;
	BOOL m_bIsNowTesting;

	void UseIeccfgfile();
	void DownIecCfgFile();
	void TestStateTool();
	void CreateMacroTestInterface(const CString &strProgID);

	BOOL ExportDeviceModelFile_AT02D(const CString &strFilePath);

	CString GetCurrEditIecCfgFile();
	BOOL IsIn_EReport_Path();
public:
	BOOL IsNowTesting();
	BOOL OpenSclFile(const CString &strScdFilePath);
	long ExportPNI302IecfgFile(const CString &strDesIecfgPath,const CString &strCbXml);

private:
	BOOL m_bIsRunAutomaition;  //程序处于自动化运行状态

// 重写
public:
	virtual BOOL InitInstance();
	BOOL IsRunAutomaition()		{		return m_bIsRunAutomaition;		}
	COleTemplateServer m_server;

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	afx_msg void OnSendConfig();
	afx_msg void OnUpdateSendConfig(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAT02D();//周宏军 20200616  增加AT02配置
	afx_msg void OnUpdateFileSaveAT02D(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAsAT02D();
	afx_msg void OnUpdateFileSaveAsAT02D(CCmdUI *pCmdUI);

	afx_msg void OnExportDevModel();
	afx_msg void OnUpdateExportDevModel(CCmdUI *pCmdUI);

	LRESULT OnElectricTestMsg(WPARAM wPara,LPARAM lPara);

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnFileNew();
	afx_msg void OnFileNew_AT02D();


	afx_msg void OnFileNewDevice();
	afx_msg void OnUpdateFileNewDevice(CCmdUI *pCmdUI);
	afx_msg void OnFileNewDeviceAT02D();
	afx_msg void OnUpdateFileNewDeviceAT02D(CCmdUI *pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenScl();
	afx_msg void OnFileOpenSclHis();
	afx_msg void OnFileOpenSclAT02D();
	afx_msg void OnFileOpenSclHisAT02D();
	virtual int ExitInstance();
	afx_msg void OnFileUseIeccfgfile();
	afx_msg void OnUpdateFileUseIeccfgfile(CCmdUI *pCmdUI);
	afx_msg void OnFileStateTool();
	afx_msg void OnUpdateFileStateTool(CCmdUI *pCmdUI);
	afx_msg void OnFileStateStarttest();
	afx_msg void OnUpdateFileStateStarttest(CCmdUI *pCmdUI);
	afx_msg void OnFileStateStoptest();
	afx_msg void OnUpdateFileStateStoptest(CCmdUI *pCmdUI);
	afx_msg void OnViewIeccfgUsedin();
	afx_msg void OnUpdateViewIeccfgUsedin(CCmdUI *pCmdUI);
	afx_msg void OnViewChPath();
	afx_msg void OnUpdateViewChPath(CCmdUI *pCmdUI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CIec61850ConfigApp theApp;

