// XAtsSysSvrClient.h
//

#pragma once
#include "SysSvrApp.h"

#include "../../Module/API/SingleAppMutexApi.h"

#define WM_XATSSYSCLIENT   (WM_USER + 1439)
#include "XAtsSysSvrGlobalDef.h"

class CXAtsSysSvrClient
{
protected:
	CXAtsSysSvrClient();
	virtual ~CXAtsSysSvrClient();

	static long g_nXAtsSysSvrClientRef;

public:
	static CXAtsSysSvrClient* g_pXAtsSysSvrClient;
	static CXAtsSysSvrClient* Create();
	static void Release();

	static BOOL RegisterModule(const CString &strName, const CString &strID, unsigned long nMsgWnd, unsigned long nMsgThreadID, unsigned long nMsgID);
	static HWND GetModuleMainWnd(const CString &strID);

	static BOOL UnRegisterModule(const CString &strID);
	static BOOL UnRegisterModule();

	//是否可以打开程序模块
	static BOOL CanOpenExeModule(const CString &strExeModule);

	//打开程序模块，strPara为相关的文件。即打开程序成功后，向新打开的程序发送strPara消息
	static BOOL OpenExeModule(const CString &strExeModule, const CString &strPara);

	//打开自动测试程序，传入的参数分别为模板文件、报告文件、数据模型文件；如果只有报告文件，则直接打开已经存在的报告
	static BOOL OpenAutoTest_XTestDB(const CString &strGbrptFile, const CString &strDeviceAttr);
	static BOOL OpenAutoTest_XTestDB();
	static BOOL OpenAutoTest(const CString &strGbxmlFile, const CString &strGbrptFile, const CString &strPpTemplateFile, const CString &strDvmFile, const CString &strIecfgFile);
	static BOOL OpenAutoTest(const CString &strGbxmlFile, const CString &strGbrptFile, const CString &strPpTemplateFile, const CStringArray &astrDvmFile, const CString &strIecfgFile);

	//打开测试仪配置程序，传入的参数分别为配置文件、整站SCD数据文件
	static BOOL OpenIec61850Config(const CString &strIecfgFile, const CString &strTscdFile, const CString &strOptr);

	//打开模型映射程序，传入的参数分别为映射文件、源文件、目标文件
	static BOOL OpenDvmMap(const CString &strDvmMapFile, const CString &strDvmSrcFile, const CString &strDvmDestFile);

	//打开模型测试程序，传入的参数分别为源文件、目标文件
	static BOOL OpenDvmTest(const CString &strDvmSrcFile, const CString &strDvmDestFile);

	//打开SCL测试程序，传入的参数分别为源文件、目标文件
	static BOOL OpenSclFileTest(const CString &strSclFile, const CString &strSclDestFile);

	//从系统管理模块取得编号为nMsgIndex的系统消息；消息对象保存在oSysMsg中
	static void GetSysMsg(LONG nMsgIndex, AtsSysSvr::CSysMsg &oSysMsg);

	//删除编号为nMsgIndex的系统消息
	static void DeleteSysMsg(LONG nMsgIndex);
	static void PostTestStateMsgTo(const CString &strDestModuleID, const CString &strState, const CString &strFile);

	//向模块添加参数，例如测试模板编辑软件打开一个模板文件，则添加一个参数文件
	static void AddModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);
	static void AddModulePara(const CString &strParaID, const CString &strParaValue);

	//删除模块参数，例如测试模板编辑软件关闭一个模板文件，则删除一个参数文件
	static void DeleteModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);
	static void DeleteModulePara(const CString &strParaID, const CString &strParaValue);

	//模块参数是否存在，例如测试模板编辑软件打开一个模板文件之前，需要判断报告模板编辑软件是否已经打开此文件
	static BOOL IsModuleParaExist(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);
	static BOOL IsModuleParaExist(const CString &strParaID, const CString &strParaValue);

	//标志
	static void WriteFlag(const CString &strFlagID, const CString &strValue);
	static CString GetFlag(const CString &strFlagID);

	//获取测试项目参数  lijq 2020-02-03
	static BOOL GbGetItemPara(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule);
	static BOOL GbSetItemPara(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, const CString &strItemXml, BOOL bOpenModule);
	static BOOL AtsTestItem(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule);
	static BOOL AtsViewItemReport(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule);

protected:
	AtsSysSvr::CSysSvrApp m_oSysSvrApp;
	CString m_strModuleID;

	BOOL _RegisterModule(const CString &strName, const CString &strID, unsigned long nMsgWnd, unsigned long nMsgThreadID, unsigned long nMsgID);
	HWND _GetModuleMainWnd(const CString &strID);
	BOOL _UnRegisterModule(const CString &strID);
	BOOL _UnRegisterModule();
	BOOL _CanOpenExeModule(const CString &strExeModule); 
	BOOL _OpenExeModule(const CString &strExeModule, const CString &strPara);  

	//打开程序模块，nSysMsgIndex为系统消息ID。即打开程序成功后，向新打开的程序发送nSysMsgIndex消息
	BOOL _OpenExeModuleEx(const CString &strExeModule, LONG nSysMsgIndex);

	void _GetSysMsg(LONG nMsgIndex, AtsSysSvr::CSysMsg &oSysMsg);
	void _DeleteSysMsg(LONG nMsgIndex);
	BOOL _OpenAutoTest_XTestDB(const CString &strGbrptFile, const CString &strDeviceAttr);
	BOOL _OpenAutoTest_XTestDB();
	BOOL _OpenAutoTest(const CString &strGbxmlFile, const CString &strGbrptFile, const CString &strPpTemplateFile, const CString &strDvmFile, const CString &strIecfgFile);
	BOOL _OpenAutoTest(const CString &strGbxmlFile, const CString &strGbrptFile, const CString &strPpTemplateFile, const CStringArray &astrDvmFile, const CString &strIecfgFile);
	BOOL _OpenIec61850Config(const CString &strIecfgFile, const CString &strTscdFile, const CString &strOptr);
	BOOL _OpenDvmMap(const CString &strDvmMapFile, const CString &strDvmSrcFile, const CString &strDvmDestFile);
	BOOL _OpenDvmTest(const CString &strDvmSrcFile, const CString &strDvmDestFile);
	BOOL _OpenSclFileTest(const CString &strSclFile, const CString &strSclDestFile);

	//像模块发送消息
	void _PostTestStateMsgTo(const CString &strDestModuleID, const CString &strState, const CString &strFile);

	//向模块添加参数，例如测试模板编辑软件打开一个模板文件，则添加一个参数文件
	void _AddModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);

	//删除模块参数，例如测试模板编辑软件关闭一个模板文件，则删除一个参数文件
	void _DeleteModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);

	//模块参数是否存在，例如测试模板编辑软件打开一个模板文件之前，需要判断报告模板编辑软件是否已经打开此文件
	BOOL _IsModuleParaExist(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);

	//标志
	void _WriteFlag(const CString &strFlagID, const CString &strValue);
	CString _GetFlag(const CString &strFlagID);

	//获取测试项目参数  lijq 2020-02-03
	BOOL _GbGetItemPara(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule);
	BOOL _GbSetItemPara(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, const CString &strItemXml, BOOL bOpenModule);
	BOOL _AtsTestItem(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule);
	BOOL _AtsViewItemReport(const CString &strExeModule, const CString &strGbXml, const CString &strItemPath, BOOL bOpenModule);

	BOOL _CreateSysSvrApp();
};

CString atssys_GetSysName(const CString &strSysName);
CString atssys_GetSysName(const CString &strSysName, const CString &strExeName);
CString atssys_GetTestState(const CString &strState, COLORREF &crBack);
CString atssys_GetTestState(const CString &strState);

BOOL atssys_CreateSingleAppMutex(const CString &pszMutexName, const CString &strModuleID);
