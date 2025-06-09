// GlobalConfigApi_VC.cpp
//
//////////////////////////////////////////////////////////////////////

#include "../GlobalConfigApi.h"
#include "../FileApi.h"
#include <QCoreApplication>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const char *g_pszPath_Dlimiter = "/";
extern char* g_pszMoudleFileName;	//程序文件名称
BOOL _P_access(CString &strPath);

void _P_CompleteModuleName(CString &strPath)
{
    CString strBin;
    strBin.Format(_T("%sBin%s*.*"), strPath.GetString(), g_pszPath_Dlimiter);
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
}

CString _P_CompletePath(CString &strPath)
{
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

	return strPath;
}

void _P_InitSystemPath()
{
	CString strPath = qApp->applicationFilePath();
	
    _P_InitSystemPath(strPath);
}
