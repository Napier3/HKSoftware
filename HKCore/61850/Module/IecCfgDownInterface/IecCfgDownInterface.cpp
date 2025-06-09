// DownIecCfgFileInterface.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IecCfgDownInterface.h"
#include "..\..\..\Module\BaseClass\RegKeyEdit.h"
#include "..\..\..\Module\API\FileApi.h"


typedef LONG (__cdecl *IECFG_DOWNCFGFILE)(char *pszIecCfgFile);

IECFG_DOWNCFGFILE   dll_iecfg_DownCfgFile = NULL;

HINSTANCE g_hIecCfgFileDownLib = NULL;

CRegKeyEdit g_regKeyEdit;
CString		m_strWorkFolder;
CString		m_strDllPath;

BOOL HasLoadDownIecCfgFileLib()
{
	return (g_hIecCfgFileDownLib != NULL);
}

void ReleaseDownIecCfgFileLib()
{
	if (g_hIecCfgFileDownLib != NULL)
	{
		FreeLibrary(g_hIecCfgFileDownLib);
		g_hIecCfgFileDownLib = NULL;
	}
}


BOOL LoadDownIecCfgFileLib(const CString &strLibName)
{
	ReleaseDownIecCfgFileLib();

	if (GetWorkFolderFromReg()<0)	//获取工作路径
	{
		return FALSE;
	}
	
	if (!GetDllPath(strLibName))	//获取Dll路径
	{
		return FALSE;
	}

	BOOL bSucc = TRUE;
	g_hIecCfgFileDownLib = LoadLibrary(m_strDllPath);

	if(g_hIecCfgFileDownLib != NULL)
	{
		dll_iecfg_DownCfgFile = (IECFG_DOWNCFGFILE)GetProcAddress(g_hIecCfgFileDownLib, "DownCfgFile");
	}
	else
	{
		bSucc = FALSE;
	}	

	return bSucc;
}

long iecfg_DownCfgFile(char *pszIecCfgFile)
{
	if (dll_iecfg_DownCfgFile == NULL)
	{
		return 0;
	}

	dll_iecfg_DownCfgFile(pszIecCfgFile);

	return 1;
}


long iecfg_DownCfgFile(const CString &strIecCfgFile)
{
	char pszFilePath[MAX_PATH];
	CString_to_char(strIecCfgFile, pszFilePath, MAX_PATH);

	return iecfg_DownCfgFile(pszFilePath);
}

long GetWorkFolderFromReg()
{
	BOOL bSelectFolder = TRUE;
	TCHAR tchFolder[MAX_PATH];
	ULONG lPathLen = MAX_PATH;
	LONG lRes = g_regKeyEdit.OpenEx_User(_T("Software\\IEC61850Config"));
	ZeroMemory(tchFolder,MAX_PATH);

	if (lRes != ERROR_SUCCESS)
	{
		lRes = g_regKeyEdit.CreateEx_User(_T("Software\\IEC61850Config"));
	}

	if (lRes == ERROR_SUCCESS)
	{
		lRes = g_regKeyEdit.QueryStringValue(_T("WorkFolder_PW"),tchFolder,&lPathLen);

		if (lRes == ERROR_SUCCESS)
		{
			m_strWorkFolder = tchFolder;
			if (IsFileExist(m_strWorkFolder+_T("\\CFG\\PWA.CFG")))	//路径存在、合理
			{
				bSelectFolder = FALSE;
			}
		}
	}

	if (bSelectFolder)
	{
		TCHAR pszBuffer[MAX_PATH];
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("PowerTest工作目录无效，请重新选择！"));

		if (!FGetDirectory(NULL, pszBuffer, _T("请选择PowerTest工作路径")))
		{
			return -1;
		}

		CString strPath = pszBuffer;
		lRes = g_regKeyEdit.SetStringValue(_T("WorkFolder_PW"),strPath);
	}

	return lRes;
}

BOOL GetDllPath(const CString &strLibName)
{
	BOOL	bRes = TRUE;
	m_strDllPath = m_strWorkFolder+_T("\\")+strLibName;

	if ( !IsFileExist(m_strDllPath) )
	{
		m_strDllPath = _P_GetBinPath() + strLibName;

		if ( !IsFileExist(m_strDllPath) )
		{
			bRes = FALSE;
		}
	}

	if (!bRes)
	{
		CLogPrint::LogString( XLOGLEVEL_TRACE, _T("未找到IEC61850下载配置模块没有定义！") );
	}

	return bRes;
}