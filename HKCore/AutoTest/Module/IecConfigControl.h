#pragma once
#include "IecConfigInterface.h"

#define WM_IEC_CONFIG_MSG_ID  (WM_USER+0X5093)

class CIecConfigControl
{
public:
	CIecConfigControl(void);
	virtual ~CIecConfigControl(void);

	Iec61850Config::CTestEngine m_oTestEngine;

public:
	BOOL CreateTestEngine();
	LONG SetWndMsg(ULONG hMainWnd);
	BOOL OpenTscdFile(const CString &strTsdFilePath);
	BOOL OpenSCDFile(const CString &strScdFilePath);
	BOOL NewIecfgFile(const CString &strIEDName);
	BOOL GenerNewIecfgFile(const CString &strIEDName,const CString &strSrcIecfgFile);
	BOOL EditIecfgFile(const CString &strIecfgPath);
	BOOL SaveIecfgFile(const CString &strIecfgPath);
	BOOL SetDestPath(const CString &strIecfgPath);
	ULONG ExitEngine(void);
	void ExitTest();
};
