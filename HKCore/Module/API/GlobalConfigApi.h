// GlobalConfigApi.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GLOBALCONFIGAPI_H__)
#define _GLOBALCONFIGAPI_H__

#include "GlobalApi.h"

const char* _P_GetInstallPath();	//软件的安装路径
const char* _P_GetHexPath();        //Hex路径
const char* _P_GetConfigPath();		//软件配置文件路径
const char* _P_GetBinPath();		//软件运行文件路径
const char* _P_GetResourcePath();	//软件资源文件路径
const char* _P_GetReportPath();		//软件报告文件路径
const char* _P_GetLibraryPath();	//软件库文件路径
const char* _P_GetSystemPath();		//软件软件系统文件路径
const char* _P_GetSystemSoftName();	//软件名称
const char* _P_GetSoftRegKey();		//软件对应注册表的关键字
const char* _P_GetLanguagePath(BOOL bCommon=FALSE);	//多语言资源路径
const char* _P_GetDBPath();			//获得数据库文件
const char* _P_GetTemplatePath();			//模板文件
const char* _P_GetCommonPath();			
const char* _P_GetCommonBinPath();		
const char* _P_GetCommonConfigPath();		
const char* _P_GetCommonLibraryPath();		
const char* _P_GetCommonResourcePath();		
const char* _P_GetWorkspacePath();	
const char* _P_GetMoudleFileName();

void    _P_GetWorkspacePath(const CString &strUser, CString &strPath);	
CString _P_GetWorkspacePath(const CString &strUser);	

void _P_InitSystemPath();

void _P_InitSystemPath(CString strPath);
void _P_SetSystemPath(const char* strPath);
void _P_InitSystemConfigPath();
CString _P_GetConfigFilePath(const CString &strFileName);
CString _P_GetConfigFilePath(const CString &strMacroTypeID, const CString &strFileName);

CString _P_GetXPath(const CString &strXPathName);

//////////////////////////////////////////////////////////////////////////
//路径变量
static const CString g_strInstallPathVar        = _T("INSTALL_PATH");
static const CString g_strConfigPathVar        = _T("CONFIG_PATH");
static const CString g_strResourcePathVar    = _T("RESOURCE_PATH");
static const CString g_strLibraryPathVar       = _T("LIBRARY_PATH");
static const CString g_strTemplatePathVar   = _T("TEMPLATE_PATH");
static const CString g_strDBPathVar            = _T("DB_PATH");
static const CString g_strBinPathVar            = _T("BIN_PATH");
static const CString g_strSystemPathVar            = _T("SYS_PATH");

CString _P_GetFullPath(const CString &strPathVar);
BOOL _P_GetFullPathEx(const CString &strPathVar, CString &strRetPath);
CString _P_GetCompany();
void _P_ReplaceSystemPath(const CString &strFrom, const CString &strTo, CString &strDestFile);
BOOL _P_ValidateSystemPath(const CString &strCurrSysPath, CString &strDestFile);
void _P_ReplaceSystemPath(CString &strDestFile);

extern const char *g_pszKeyCompany;//		= "Power-Sky";
extern const char *g_pszKeyRegInstall;//  = "InstallPath";
extern const char *g_pszKeyConfig;//		= "Config";
extern const char *g_pszKeyHex;//			= "Hex";
extern const char *g_pszKeyBin;//			= "Bin";
extern const char *g_pszKeyRespurce;//	= "Resource";
extern const char *g_pszKeyReport;//		= "Report";
extern const char *g_pszKeyLibrary;//		= "Library";
extern const char *g_pszKeyTemplate;//	= "Template";
extern const char *g_pszKeySystem;//		= "System";
extern const char *g_pszKeyPlugin;//		= "Plugin";
extern const char *g_pszKeyLanguage;//	= "Language";
extern const char *g_pszKeyDB;//			= "DB";
extern const char *g_pszKeyCommon;//		= "Common";
extern const char *g_pszKeyWorkspace;//	= "Workspace";

#endif // !defined(_GLOBALCONFIGAPI_H__)
