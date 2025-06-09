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

	//�Ƿ���Դ򿪳���ģ��
	static BOOL CanOpenExeModule(const CString &strExeModule);

	//�򿪳���ģ�飬strParaΪ��ص��ļ������򿪳���ɹ������´򿪵ĳ�����strPara��Ϣ
	static BOOL OpenExeModule(const CString &strExeModule, const CString &strPara);

	//���Զ����Գ��򣬴���Ĳ����ֱ�Ϊģ���ļ��������ļ�������ģ���ļ������ֻ�б����ļ�����ֱ�Ӵ��Ѿ����ڵı���
	static BOOL OpenAutoTest_XTestDB(const CString &strGbrptFile, const CString &strDeviceAttr);
	static BOOL OpenAutoTest_XTestDB();
	static BOOL OpenAutoTest(const CString &strGbxmlFile, const CString &strGbrptFile, const CString &strPpTemplateFile, const CString &strDvmFile, const CString &strIecfgFile);
	static BOOL OpenAutoTest(const CString &strGbxmlFile, const CString &strGbrptFile, const CString &strPpTemplateFile, const CStringArray &astrDvmFile, const CString &strIecfgFile);

	//�򿪲��������ó��򣬴���Ĳ����ֱ�Ϊ�����ļ�����վSCD�����ļ�
	static BOOL OpenIec61850Config(const CString &strIecfgFile, const CString &strTscdFile, const CString &strOptr);

	//��ģ��ӳ����򣬴���Ĳ����ֱ�Ϊӳ���ļ���Դ�ļ���Ŀ���ļ�
	static BOOL OpenDvmMap(const CString &strDvmMapFile, const CString &strDvmSrcFile, const CString &strDvmDestFile);

	//��ģ�Ͳ��Գ��򣬴���Ĳ����ֱ�ΪԴ�ļ���Ŀ���ļ�
	static BOOL OpenDvmTest(const CString &strDvmSrcFile, const CString &strDvmDestFile);

	//��SCL���Գ��򣬴���Ĳ����ֱ�ΪԴ�ļ���Ŀ���ļ�
	static BOOL OpenSclFileTest(const CString &strSclFile, const CString &strSclDestFile);

	//��ϵͳ����ģ��ȡ�ñ��ΪnMsgIndex��ϵͳ��Ϣ����Ϣ���󱣴���oSysMsg��
	static void GetSysMsg(LONG nMsgIndex, AtsSysSvr::CSysMsg &oSysMsg);

	//ɾ�����ΪnMsgIndex��ϵͳ��Ϣ
	static void DeleteSysMsg(LONG nMsgIndex);
	static void PostTestStateMsgTo(const CString &strDestModuleID, const CString &strState, const CString &strFile);

	//��ģ����Ӳ������������ģ��༭�����һ��ģ���ļ��������һ�������ļ�
	static void AddModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);
	static void AddModulePara(const CString &strParaID, const CString &strParaValue);

	//ɾ��ģ��������������ģ��༭����ر�һ��ģ���ļ�����ɾ��һ�������ļ�
	static void DeleteModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);
	static void DeleteModulePara(const CString &strParaID, const CString &strParaValue);

	//ģ������Ƿ���ڣ��������ģ��༭�����һ��ģ���ļ�֮ǰ����Ҫ�жϱ���ģ��༭����Ƿ��Ѿ��򿪴��ļ�
	static BOOL IsModuleParaExist(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);
	static BOOL IsModuleParaExist(const CString &strParaID, const CString &strParaValue);

	//��־
	static void WriteFlag(const CString &strFlagID, const CString &strValue);
	static CString GetFlag(const CString &strFlagID);

	//��ȡ������Ŀ����  lijq 2020-02-03
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

	//�򿪳���ģ�飬nSysMsgIndexΪϵͳ��ϢID�����򿪳���ɹ������´򿪵ĳ�����nSysMsgIndex��Ϣ
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

	//��ģ�鷢����Ϣ
	void _PostTestStateMsgTo(const CString &strDestModuleID, const CString &strState, const CString &strFile);

	//��ģ����Ӳ������������ģ��༭�����һ��ģ���ļ��������һ�������ļ�
	void _AddModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);

	//ɾ��ģ��������������ģ��༭����ر�һ��ģ���ļ�����ɾ��һ�������ļ�
	void _DeleteModulePara(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);

	//ģ������Ƿ���ڣ��������ģ��༭�����һ��ģ���ļ�֮ǰ����Ҫ�жϱ���ģ��༭����Ƿ��Ѿ��򿪴��ļ�
	BOOL _IsModuleParaExist(const CString &strExeModule, const CString &strParaID, const CString &strParaValue);

	//��־
	void _WriteFlag(const CString &strFlagID, const CString &strValue);
	CString _GetFlag(const CString &strFlagID);

	//��ȡ������Ŀ����  lijq 2020-02-03
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
