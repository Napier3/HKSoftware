
#pragma once

#define _DISP_MODE_NORMAL                             0
#define _DISP_MODE_AT02D                              1
#define _DISP_MODE_PNI302                             2
#define _DISP_MODE_PN466                              3

// CTestEngine 命令目标

class CTestEngine : public CCmdTarget
{
	DECLARE_DYNCREATE(CTestEngine)

public:
	CTestEngine();
	virtual ~CTestEngine();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CTestEngine)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	enum 
	{
		dispidCommConfig = 12L,
		dispidSetDispMode = 11L,
		dispidExportAt02dFiles = 10L,
		dispidExitEngine = 9L,
		dispidCloseIecfgFile = 8L,
		dispidSaveIecfgFile = 7L,
		dispidEditIecfgFile = 6L,
		dispidNewIecfgFile = 5L,
		dispidSetDestPath = 4L,
		dispidOpenTscdFile = 3L,
		dispidOpenSCDFile = 2L,
		dispidSetWndMsg = 1L,
	};

	LONG SetWndMsg(ULONG hMainWnd, ULONG nMsgID);
	//ULONG NewCfgFile(LPCTSTR strTscdFilePath, LPCTSTR strIEDName, LPCTSTR strSavePath);
	//ULONG EditCfgFile(LPCTSTR strCfgFilePath);
	LONG OpenSCDFile(LPCTSTR strScdFilePath);
	LONG OpenTscdFile(LPCTSTR strTscdFilePath);
	LONG SetDestPath(LPCTSTR strDestPath);
	LONG NewIecfgFile(LPCTSTR strIedName,LPCTSTR strSrcIecfgFile);
	LONG EditIecfgFile(LPCTSTR strIecfgFile);
	LONG SaveIecfgFile(LPCTSTR strIecfgFile);
	LONG CloseIecfgFile(LPCTSTR strIecfgFile);
	ULONG ExitEngine(void);

public:
	
protected:
	LONG ExportAt02dFiles(LPCTSTR strDesIecfgPath, LPCTSTR strCbXml);
	void SetDispMode(LONG nMode);
	LONG CommConfig(LPCTSTR strCmmConfig);
};

BOOL PostMsg_TestEngineFinish(const CString &strEngineIecfgPath);

extern char g_szEngineIecfgPath[500];
extern char g_szEngineSCLPath[500];
extern HWND g_hEngineMsgWnd; 
extern ULONG g_nEngineMSG_ID;
extern ULONG g_nEngineDispMode;//zhouhj 用于区分调用类型，比如AT02D、PNI302、正常测试仪模式
extern BOOL g_bSendTestFinished;//zhouhj 20211018 是否给外部发送结束消息
