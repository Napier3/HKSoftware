// GlobalConfigApi.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlobalConfigApi.h"
#include "FileApi.h"

#ifndef _PSX_IDE_QT_
#include "VC/GlobalConfigApi_VC.cpp"
#else
#include "QT/GlobalConfigApi_QT.cpp"
#endif


const char *g_pszKeyCompany		= "Power-Sky";
const char *g_pszKeyRegInstall  = "InstallPath";
const char *g_pszKeyConfig		= "Config";
const char *g_pszKeyHex			= "Hex";
const char *g_pszKeyBin			= "Bin";
const char *g_pszKeyRespurce	= "Resource";
const char *g_pszKeyReport		= "Report";
const char *g_pszKeyLibrary		= "Library";
const char *g_pszKeyTemplate	= "Template";
const char *g_pszKeySystem		= "System";
const char *g_pszKeyPlugin		= "Plugin";
const char *g_pszKeyLanguage	= "Language";
const char *g_pszKeyDB			= "DB";
const char *g_pszKeyCommon		= "Common";
const char *g_pszKeyWorkspace	= "Workspace";

char* g_pszSystemPath	= NULL;	//软件软件系统文件路径
char* g_pszSoftwareName = NULL;	//软件项目工程的名称
char* g_pszInstallPath	= NULL;	//软件的安装路径
char* g_pszConfigPath	= NULL;	//配置文件的路径
char* g_pszHexPath		= NULL;	//DSP文件的路径
char* g_pszBinPath		= NULL;	//软件运行文件路径
char* g_pszResourcePath = NULL;	//软件资源文件路径
char* g_pszReportPath	= NULL;	//软件报告文件路径
char* g_pszLanguagePath = NULL;	//多语言资源路径路径
char* g_pszLibraryPath	= NULL;	//软件库文件路径
char* g_pszPluginPath	= NULL;	//软件插件路径
char* g_pszSoftRegKey	= NULL;	//软件库文件路径
char* g_pszDBPath		= NULL;	//数据库文件路径
char* g_pszTemplatePath		= NULL;	//数据库文件路径
char* g_pszCommonPath		= NULL;	//数据库文件路径
char* g_pszCommonConfigPath		= NULL;	//数据库文件路径
char* g_pszCommonLibraryPath		= NULL;	//数据库文件路径
char* g_pszCommonBinPath		= NULL;	//数据库文件路径
char* g_pszCommonResourcePath		= NULL;	
char* g_pszCommonLanguagePath = NULL;	//多语言资源路径路径
char* g_pszWorkspace		= NULL;	//工作区路径
char* g_pszMoudleFileName		= NULL;	//程序文件名称

void InitGlobalConfig();
void EndGlobalConfig();

void InitGlobalConfig()
{
	if (g_pszDBPath == NULL)
	{
		g_pszDBPath = new char [MAX_PATH];
		memset(g_pszDBPath,0,MAX_PATH);
	}

	if (g_pszInstallPath == NULL)
	{
		g_pszInstallPath = new char [MAX_PATH];
		memset(g_pszInstallPath,0,MAX_PATH);
	}

	if (g_pszSoftwareName == NULL)
	{
		g_pszSoftwareName = new char [MAX_PATH];
		memset(g_pszSoftwareName,0,MAX_PATH);
	}

	if (g_pszConfigPath == NULL)
	{
		g_pszConfigPath = new char [MAX_PATH];
		memset(g_pszConfigPath,0,MAX_PATH);
	}
	
	if (g_pszHexPath == NULL)
	{
		g_pszHexPath = new char [MAX_PATH];
		memset(g_pszHexPath,0,MAX_PATH);
	}

	if (g_pszBinPath == NULL)
	{
		g_pszBinPath = new char [MAX_PATH];
		memset(g_pszBinPath,0,MAX_PATH);
	}
	
	if (g_pszResourcePath == NULL)
	{
		g_pszResourcePath = new char [MAX_PATH];
		memset(g_pszResourcePath,0,MAX_PATH);
	}
	
	if (g_pszReportPath == NULL)
	{
		g_pszReportPath = new char [MAX_PATH];
		memset(g_pszReportPath,0,MAX_PATH);
	}
	
	if (g_pszLanguagePath == NULL)
	{
		g_pszLanguagePath = new char [MAX_PATH];
		memset(g_pszLanguagePath,0,MAX_PATH);
	}

	if (g_pszLibraryPath == NULL)
	{
		g_pszLibraryPath = new char [MAX_PATH];
		memset(g_pszLibraryPath,0,MAX_PATH);
	}
	
	if (g_pszSystemPath == NULL)
	{
		g_pszSystemPath = new char [MAX_PATH];
		memset(g_pszSystemPath,0,MAX_PATH);
	}
	
	if (g_pszPluginPath == NULL)
	{
		g_pszPluginPath = new char [MAX_PATH];
		memset(g_pszPluginPath,0,MAX_PATH);
	}
	
	if (g_pszSoftRegKey == NULL)
	{
		g_pszSoftRegKey = new char [MAX_PATH];
		memset(g_pszSoftRegKey,0,MAX_PATH);
	}

	if (g_pszTemplatePath == NULL)
	{
		g_pszTemplatePath = new char [MAX_PATH];
		memset(g_pszTemplatePath,0,MAX_PATH);
	}

	if (g_pszCommonPath == NULL)
	{
		g_pszCommonPath = new char [MAX_PATH];
		memset(g_pszCommonPath,0,MAX_PATH);
	}

	if (g_pszCommonBinPath == NULL)
	{
		g_pszCommonBinPath = new char [MAX_PATH];
		memset(g_pszCommonBinPath,0,MAX_PATH);
	}

	if (g_pszCommonResourcePath == NULL)
	{
		g_pszCommonResourcePath = new char [MAX_PATH];
		memset(g_pszCommonResourcePath,0,MAX_PATH);
	}

	if (g_pszCommonLanguagePath == NULL)
	{
		g_pszCommonLanguagePath = new char [MAX_PATH];
		memset(g_pszCommonLanguagePath,0,MAX_PATH);
	}

	if (g_pszCommonConfigPath == NULL)
	{
		g_pszCommonConfigPath = new char [MAX_PATH];
		memset(g_pszCommonConfigPath,0,MAX_PATH);
	}

	if (g_pszCommonLibraryPath == NULL)
	{
		g_pszCommonLibraryPath = new char [MAX_PATH];
		memset(g_pszCommonLibraryPath,0,MAX_PATH);
	}

	if (g_pszWorkspace == NULL)
	{
		g_pszWorkspace = new char [MAX_PATH];
		memset(g_pszWorkspace,0,MAX_PATH);
	}

	if (g_pszMoudleFileName == NULL)
	{
		g_pszMoudleFileName = new char [MAX_PATH];
		memset(g_pszMoudleFileName,0,MAX_PATH);
	}
}

void EndGlobalConfig()
{
	if (g_pszDBPath != NULL)
	{
		delete g_pszDBPath;
		g_pszDBPath = NULL;
	}

	if (g_pszInstallPath != NULL)
	{
		delete g_pszInstallPath;
		g_pszInstallPath = NULL;
	}

	if (g_pszConfigPath != NULL)
	{
		delete g_pszConfigPath;
		g_pszConfigPath = NULL;
	}

	if (g_pszHexPath != NULL)
	{
		delete g_pszHexPath;
		g_pszHexPath = NULL;
	}

	if (g_pszBinPath != NULL)
	{
		delete g_pszBinPath;
		g_pszBinPath = NULL;
	}

	if (g_pszResourcePath != NULL)
	{
		delete g_pszResourcePath;
		g_pszResourcePath = NULL;
	}

	if (g_pszReportPath != NULL)
	{
		delete g_pszReportPath;
		g_pszReportPath = NULL;
	}

	if (g_pszLanguagePath != NULL)
	{
		delete g_pszLanguagePath;
		g_pszLanguagePath = NULL;
	}
	
	if (g_pszLibraryPath != NULL)
	{
		delete g_pszLibraryPath;
		g_pszLibraryPath = NULL;
	}

	if (g_pszSoftRegKey != NULL)
	{
		delete g_pszSoftRegKey;
		g_pszSoftRegKey = NULL;
	}

	if (g_pszSystemPath != NULL)
	{
		delete g_pszSystemPath;
		g_pszSystemPath = NULL;
	}

	if (g_pszSoftwareName != NULL)
	{
		delete g_pszSoftwareName;
		g_pszSoftwareName = NULL;
	}

	if (g_pszPluginPath != NULL)
	{
		delete g_pszPluginPath;
		g_pszPluginPath = NULL;
	}

	if (g_pszTemplatePath != NULL)
	{
		delete g_pszTemplatePath;
		g_pszTemplatePath = NULL;
	}

	if (g_pszCommonPath != NULL)
	{
		delete g_pszCommonPath;
		g_pszCommonPath = NULL;
	}

	if (g_pszCommonBinPath != NULL)
	{
		delete g_pszCommonBinPath;
		g_pszCommonBinPath = NULL;
	}

	if (g_pszCommonResourcePath != NULL)
	{
		delete g_pszCommonResourcePath;
		g_pszCommonResourcePath = NULL;
	}

	if (g_pszCommonLanguagePath != NULL)
	{
		delete g_pszCommonLanguagePath;
		g_pszCommonLanguagePath = NULL;
	}

	if (g_pszCommonConfigPath != NULL)
	{
		delete g_pszCommonConfigPath;
		g_pszCommonConfigPath = NULL;
	}

	if (g_pszCommonLibraryPath != NULL)
	{
		delete g_pszCommonLibraryPath;
		g_pszCommonLibraryPath = NULL;
	}

	if (g_pszWorkspace != NULL)
	{
		delete g_pszWorkspace;
		g_pszWorkspace = NULL;
	}

	if (g_pszMoudleFileName != NULL)
	{
		delete g_pszMoudleFileName;
		g_pszMoudleFileName = NULL;
	}
}

CString _P_GetXPath(const CString &strXPathName)
{
	CString strPath;
	strPath = g_pszSystemPath;
    strPath.AppendFormat(_T("%s%s"), strXPathName.GetString(), g_pszPath_Dlimiter);
	return strPath;
}

const char* _P_GetDBPath()
{
	return g_pszDBPath;
}

//软件的安装路径
const char* _P_GetInstallPath()
{
	return g_pszInstallPath;
}

//软件配置文件路径
const char* _P_GetConfigPath()
{
	return  g_pszConfigPath;
}

//软件配置文件路径
const char* _P_GetHexPath()
{
	return  g_pszHexPath;
}

//软件运行文件路径
const char* _P_GetBinPath()
{
	return  g_pszBinPath;
}


//软件资源文件路径
const char* _P_GetResourcePath()
{
	return  g_pszResourcePath;
}


//软件报告文件路径
const char* _P_GetReportPath()
{
	return  g_pszReportPath;
}

//软件报告文件路径
const char* _P_GetLanguagePath(BOOL bCommon)
{
	if (bCommon)
	{
		return g_pszCommonLanguagePath;
	}
	else
	{
		return  g_pszLanguagePath;
	}
}

//软件库文件路径
const char* _P_GetLibraryPath()
{
	return  g_pszLibraryPath;
}

//软件软件系统文件路径
const char* _P_GetSystemPath()
{
	return  g_pszSystemPath;
}

//软件名称
const char* _P_GetSystemSoftName()
{
	return g_pszSoftwareName;
}

//软件对应注册表的关键字
const char* _P_GetSoftRegKey()
{
	return g_pszSoftRegKey;
}

const char* _P_GetTemplatePath()
{
	return g_pszTemplatePath;
}

const char* _P_GetCommonPath()
{
	return g_pszCommonPath;
}

const char* _P_GetCommonBinPath()
{
	return g_pszCommonBinPath;
}

const char* _P_GetCommonResourcePath()
{
	return g_pszCommonResourcePath;
}

const char* _P_GetWorkspacePath()
{
	return g_pszWorkspace;
}

const char* _P_GetMoudleFileName()
{
	return g_pszMoudleFileName;
}

void _P_GetWorkspacePath(const CString &strUser, CString &strPath)
{
	strPath = g_pszWorkspace;

	if (strUser.GetLength() > 0)
	{
        strPath.AppendFormat(_T("%s%s"), strUser.GetString(), g_pszPath_Dlimiter);
	}
}

CString _P_GetWorkspacePath(const CString &strUser)
{
	CString strPath;
	_P_GetWorkspacePath(strUser, strPath);

	return strPath;
}

const char* _P_GetCommonConfigPath()
{
	return g_pszCommonConfigPath;
}

const char* _P_GetCommonLibraryPath()
{
	return g_pszCommonLibraryPath;
}


BOOL _P_access(CString &strPath)
{
	return IsFileExist(strPath);
	// 	char *pszPath = NULL;
	// 	CString_to_char(strPath, &pszPath);
	// 
	// 	BOOL bRet = access(pszPath, 0);
	// 	delete pszPath;

// 	CFileFind find;
// 	CString strTemp;
// 	strTemp = strPath + _T("*.*");
// 	BOOL bFind = find.FindFile(strTemp);
// 	return bFind;
}
// 
// void _P_CompleteModuleName(CString &strPath)
// {
// #ifndef _PSX_IDE_QT_
//     CString strBin;
//     strBin.Format(_T("%sBin%s*.*"), strPath.GetString(), g_pszPath_Dlimiter);
// 
// #ifdef UNICODE
// 	CFileFind find; 
// #else
// 	CXFileFindEx find; 
// #endif
// 
// 	BOOL bFind = find.FindFile(strBin);
// 	CString strFile, strTemp;
// 	CString strModuleName;
// 	strModuleName = g_pszMoudleFileName;
// 	long nPos = strModuleName.Find('~');
// 	strModuleName = strModuleName.Left(nPos);
// 	strModuleName.MakeLower();
// 
// 	while (bFind)
// 	{
// 		bFind = find.FindNextFile();
// 		strFile = find.GetFileName();
// 
// 		if (find.IsDots())
// 		{
// 			continue;
// 		}
// 
// 		if (find.IsDirectory())
// 		{
// 			continue;
// 		}
// 
// 		strTemp = strFile;
// 		strTemp.MakeLower();
// 
// 		if (strTemp.Right(4) == _T(".exe"))
// 		{
// 			if (strModuleName == strTemp.Left(nPos))
// 			{
// 				strModuleName = strFile.Left(strFile.GetLength() - 4);
// 				CString_to_char(strModuleName, g_pszMoudleFileName);
// 				break;
// 			}
// 		}
// 	}
// #endif
// }
// 
// CString _P_CompletePath(CString &strPath)
// {
// #ifndef _PSX_IDE_QT_
//     strPath.MakeLower();
// 	CString strFullPath = strPath;
// 	CString strPrefix;
// 	CString strPrevFolder, strLasFolder, strTemp, strFind;
// 
// 	while (TRUE)
// 	{
// 		long nPos = strFullPath.Find(_T("~"));
// 
// 		if (nPos > 0)
// 		{
// 			strTemp = strFullPath.Left(nPos);
//             long nPos2 = strTemp.ReverseFind(*g_pszPath_Dlimiter);
// 			strPrevFolder = strTemp.Left(nPos2 + 1); //~之前的路径
// 			strTemp = strPrevFolder + _T("*.*");
// 			strPrefix = strFullPath.Mid(nPos2+1, nPos - nPos2-1);//   \与~之间的文字
//             long nPos3 = strFullPath.Find(*g_pszPath_Dlimiter, nPos + 1);
// 
// 			if (nPos3 > 0)
// 			{
// 				strLasFolder = strFullPath.Mid(nPos3); //~之后的路径
// 			}
// 
// #ifdef UNICODE
// 			CFileFind find; 
// #else
// 			CXFileFindEx find; 
// #endif
// 
// 			BOOL bFind = find.FindFile(strTemp);
// 
// 			while (bFind)
// 			{
// 				bFind = find.FindNextFile();
// 				strFind = find.GetFileName();
// 
// 				if (find.IsDots())
// 				{
// 					continue;
// 				}
// 
// 				if (!find.IsDirectory())
// 				{
// 					continue;
// 				}
// 
// 				strFind.MakeLower();
// 
// 				if (strFind.Left(strPrefix.GetLength()) == strPrefix)
// 				{
// 					strFullPath = strPrevFolder + strFind + strLasFolder;
// 
// 					//只判断一次，存在缺陷
// 					if (_P_access(strFullPath))
// 					{
// 						if ( strFullPath.Find(_T("~")) < 0)
// 						{
// 							return strFullPath;
// 						}
// 						else
// 						{
// 							break;
// 						}
// 					}
// 				}
// 
// 			}
// 		}
// 		else
// 		{
// 			break;
// 		}
// 	}
// #endif
// 	return strPath;
// }

void _P_InitSystemPath(CString strPath)
{
    long nPos = strPath.ReverseFind(*g_pszPath_Dlimiter);
    if (nPos < 0)
    {
        return;
    }

    CString str;
    char pszPath[MAX_PATH];

    //模块名称
    str = strPath.Mid(nPos + 1);
    CString_to_char(str, pszPath);
    strcpy(g_pszMoudleFileName, pszPath);

    char *pTemp = g_pszMoudleFileName;

    while (*pTemp != 0)
    {
        if (*pTemp == '.')
        {
            *pTemp = 0;
            break;
        }

        pTemp++;
    }

    //系统路径
    strPath = strPath.Left(nPos);
    nPos = strPath.ReverseFind(*g_pszPath_Dlimiter);
    if (nPos < 0)
    {
        return;
    }

    strPath = strPath.Left(nPos+1);
    //strPath.Replace(_T("m Files"), _T("~1")); //Test......

    if (strPath.Find(_T("~")) > 0)
    {
        str = _P_CompletePath(strPath);
        CString_to_char(str, pszPath);

        if (strchr(g_pszMoudleFileName, '~') != NULL)
        {
            _P_CompleteModuleName(str);
        }
    }
    else
    {
#ifdef _PSX_IDE_QT_
		long nLen = 0;
        CString_to_char(strPath, pszPath, nLen);
#else
		CString_to_char(strPath, pszPath);
#endif
    }

    _P_SetSystemPath(pszPath);
}

void _P_SetSystemPath(const char* strPath)
{
    long nLen = strlen(strPath);
	strcpy(g_pszSystemPath, strPath);

    if (strPath[nLen - 1] != *g_pszPath_Dlimiter)
	{
        strcat(g_pszSystemPath, g_pszPath_Dlimiter);
		nLen++;
	}
	else
	{
	}

	//g_pszSoftwareName
	long nPos = nLen-2;

    while( (g_pszSystemPath[nPos] != *g_pszPath_Dlimiter) && (nPos > 0) )
	{
		nPos--;
	}

	char *pTemp = g_pszSoftwareName;
	nPos++;

	while (nPos < nLen - 1)
	{
		*pTemp = g_pszSystemPath[nPos];
		pTemp++;
		nPos++;
	}

	*pTemp = 0;

	strcpy(g_pszInstallPath, g_pszSystemPath);//软件的安装路径
    sprintf(g_pszConfigPath,"%s%s%s",g_pszSystemPath,g_pszKeyConfig, g_pszPath_Dlimiter);//配置文件的路径
    sprintf(g_pszHexPath,"%s%s%s",g_pszSystemPath,g_pszKeyHex, g_pszPath_Dlimiter);//配置文件的路径
    sprintf(g_pszBinPath,"%s%s%s",g_pszSystemPath,g_pszKeyBin, g_pszPath_Dlimiter);//软件运行文件路径
    sprintf(g_pszResourcePath,"%s%s%s",g_pszSystemPath,g_pszKeyRespurce, g_pszPath_Dlimiter);//软件资源文件路径
    sprintf(g_pszReportPath,"%s%s%s",g_pszSystemPath,g_pszKeyReport, g_pszPath_Dlimiter);//软件报告文件路径
    sprintf(g_pszLibraryPath,"%s%s%s",g_pszSystemPath,g_pszKeyLibrary, g_pszPath_Dlimiter);//软件库文件路径
    sprintf(g_pszSoftRegKey,"Software%s%s%s%s",g_pszPath_Dlimiter, g_pszKeyCompany, g_pszPath_Dlimiter, g_pszSoftwareName);//注册表路径
    sprintf(g_pszPluginPath,"%s%s%s",g_pszSystemPath,g_pszKeyPlugin, g_pszPath_Dlimiter);//软件插件路径
    sprintf(g_pszLanguagePath,"%s%s%s",g_pszSystemPath, g_pszKeyLanguage, g_pszPath_Dlimiter);//多语言资源路径
    sprintf(g_pszDBPath,"%s%s%s",g_pszSystemPath, g_pszKeyDB, g_pszPath_Dlimiter);//多语言资源路径
    sprintf(g_pszTemplatePath,"%s%s%s",g_pszSystemPath, g_pszKeyTemplate, g_pszPath_Dlimiter);//模板路径


	nLen = strlen(g_pszInstallPath);
	pTemp = g_pszInstallPath+nLen-1;

	while (pTemp > g_pszInstallPath)
	{
        if (*(pTemp-1) == *g_pszPath_Dlimiter)
		{
			*pTemp = 0;
			break;
		}
		pTemp--;
	}

    sprintf(g_pszCommonPath,"%s%s%s",g_pszInstallPath, g_pszKeyCommon, g_pszPath_Dlimiter);
    sprintf(g_pszCommonBinPath,"%s%s%s",g_pszCommonPath, g_pszKeyBin, g_pszPath_Dlimiter);
    sprintf(g_pszCommonResourcePath,"%s%s%s",g_pszCommonPath, g_pszKeyRespurce, g_pszPath_Dlimiter);
    sprintf(g_pszCommonLanguagePath,"%s%s%s",g_pszCommonPath, g_pszKeyLanguage, g_pszPath_Dlimiter);
    sprintf(g_pszCommonConfigPath,"%s%s%s",g_pszCommonPath, g_pszKeyConfig, g_pszPath_Dlimiter);
    sprintf(g_pszCommonLibraryPath,"%s%s%s",g_pszCommonPath, g_pszKeyLibrary, g_pszPath_Dlimiter);

    sprintf(g_pszWorkspace,"%s%s%s",g_pszSystemPath, g_pszKeyWorkspace, g_pszPath_Dlimiter);
}

CString _P_GetConfigFilePath(const CString &strFileName)
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strFileName;
	return strPath;
}

CString _P_GetConfigFilePath(const CString &strMacroTypeID, const CString &strFileName)
{
	CString strPath;
	strPath = _P_GetConfigPath();
    strPath.AppendFormat(_T("%s%s%s"), strMacroTypeID.GetString(), g_pszPath_Dlimiter, strFileName.GetString());
	return strPath;
}

class _CPGlobalConfig
{
public:
	_CPGlobalConfig()
	{
		InitGlobalConfig();
	}
	virtual ~_CPGlobalConfig()
	{
		EndGlobalConfig();
	}
};
_CPGlobalConfig g_GlobalConfig;

BOOL _P_GetFullPathEx(const CString &strPathVar, CString &strRetPath)
{
	CString strRootPath;

	if (strPathVar.Left(g_strInstallPathVar.GetLength()) == g_strInstallPathVar)
	{
		strRootPath =  _P_GetInstallPath();
		strRootPath += strPathVar.Mid(g_strInstallPathVar.GetLength()+1);
	}
	else if (strPathVar.Left(g_strConfigPathVar.GetLength()) == g_strConfigPathVar)
	{
		strRootPath =  _P_GetConfigPath();
		strRootPath += strPathVar.Mid(g_strConfigPathVar.GetLength()+1);
	}
	else if (strPathVar.Left(g_strResourcePathVar.GetLength()) == g_strResourcePathVar)
	{
		strRootPath =  _P_GetResourcePath();
		strRootPath += strPathVar.Mid(g_strResourcePathVar.GetLength()+1);
	}
	else if (strPathVar.Left(g_strLibraryPathVar.GetLength()) == g_strLibraryPathVar)
	{
		strRootPath =  _P_GetLibraryPath();
		strRootPath += strPathVar.Mid(g_strLibraryPathVar.GetLength()+1);
	}
	else if (strPathVar.Left(g_strTemplatePathVar.GetLength()) == g_strTemplatePathVar)
	{
		strRootPath =  _P_GetTemplatePath();
		strRootPath += strPathVar.Mid(g_strTemplatePathVar.GetLength()+1);
	}
	else if (strPathVar.Left(g_strDBPathVar.GetLength()) == g_strDBPathVar)
	{
		strRootPath =  _P_GetDBPath();
		strRootPath += strPathVar.Mid(g_strDBPathVar.GetLength()+1);
	}
	else if (strPathVar.Left(g_strBinPathVar.GetLength()) == g_strBinPathVar)
	{
		strRootPath =  _P_GetBinPath();
		strRootPath += strPathVar.Mid(g_strBinPathVar.GetLength()+1);
	}
	else if (strPathVar.Left(g_strSystemPathVar.GetLength()) == g_strSystemPathVar)
	{
		strRootPath =  _P_GetSystemPath();
		strRootPath += strPathVar.Mid(g_strSystemPathVar.GetLength()+1);
	}
	else
	{
		return FALSE;
	}

	strRetPath = strRootPath;

	return TRUE;
}

CString _P_GetFullPath(const CString &strPathVar)
{
	CString strRootPath;
	
	if (_P_GetFullPathEx(strPathVar, strRootPath))
	{
		return strRootPath;
	}
	else
	{
		return strPathVar;
	}
}

CString _P_GetCompany()
{
	return CString (g_pszKeyCompany);
}

BOOL _P_ValidateSystemPath(const CString &strCurrSysPath, CString &strDestFile)
{
	CString str1 = strCurrSysPath;
	CString str2 = strDestFile;

	str1.MakeLower();
	str2.MakeLower();

	if (str2.Left(str1.GetLength()) == str1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void _P_ReplaceSystemPath(const CString &strFrom, const CString &strTo, CString &strDestFile)
{
	if (strDestFile.GetLength() < strFrom.GetLength())
	{
		return;
	}

	CString strTemp = strDestFile.Mid(strFrom.GetLength());
	strTemp = strTo + strTemp;
	strDestFile = strTemp;
}

CString _P_GetSysPathFromFile(const CString &strFile)
{
	CString strSystemPath = strFile;
	strSystemPath.MakeLower();
	CString strSoft;
	strSoft = g_pszSoftwareName;
	strSoft.MakeLower();

	long nPos = strSystemPath.Find(strSoft);

	if (nPos > 0)
	{
		strSystemPath = strSystemPath.Left(nPos);
	}
	else
	{
		ASSERT (FALSE);
	}
	
	return strSystemPath;
}

void _P_ReplaceSystemPath(CString &strDestFile)
{
	CString strFrom = _P_GetSysPathFromFile(strDestFile);
	CString strTo;
	strTo = _P_GetInstallPath();

	_P_ReplaceSystemPath(strFrom, strTo, strDestFile);
}