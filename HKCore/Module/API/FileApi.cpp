#include "stdafx.h"
#include "FileApi.h"
#include "GlobalConfigApi.h"


#ifndef _PSX_IDE_QT_
#include "VC/FileApi_VC.cpp"
#else
#include "QT/FileApi_QT.cpp"
#endif

//从文件的全名称路径中获取文件的路径信息
CString GetPathFromFilePathName(const CString &strFilePath, char ch)
{
	long nPos1 = strFilePath.ReverseFind('\\');
	long nPos2 = strFilePath.ReverseFind('/');
	long nPos = 0;
	nPos = max(nPos1, nPos2);
	
	CString strTemp;

	if (nPos == 0)
	{
		return strTemp;
	}

	strTemp = strFilePath.Left(nPos+1);

	return strTemp;
}

CString GetPathFromFilePathName(const char *pszFilePath, char ch)
{
	char *pszBuff = NULL;
	char *pTemp = NULL;
	char *pPos = NULL;
	CString strTemp=_T("");

	long lLen = strlen(pszFilePath);
	pszBuff = new char [lLen+1];
	strcpy(pszBuff,pszFilePath);
	pTemp = pszBuff + lLen - 1;

	while(pTemp != pszBuff)
	{
		if((*pTemp == '/') || (*pTemp == '\\'))
		{
			pPos = pTemp;
			break;
		}
		pTemp--;
	}

	pTemp = pPos;
	if (pTemp == NULL)
	{
		strTemp = _T("C:\\");
	}
	else
	{
		ch = *pTemp;
		*pTemp = 0;
        strTemp.Format(_T("%s%c"), pszBuff, ch);
	}

	delete []pszBuff;
	return strTemp;	
}


CString GetLastFolderNameFromPathName(const CString &strFilePath)
{
	CString strTemp = strFilePath;

	while(TRUE)
	{
		CString strRight = strTemp.Right(1);
		if ((strRight == _T("\\")) || (strRight == _T("/")))
		{
			strTemp = strTemp.Left(strTemp.GetLength() - 1);
		}
		else
		{
			break;
		}
	}

	long nPos = strTemp.ReverseFind('\\');
	if (nPos < 0)
	{
		nPos = strTemp.ReverseFind('/');
	}

	if (nPos < 0)
	{
		return _T("");
	}

	strTemp = strTemp.Mid(nPos+1);
	return strTemp;
}


CString GetPathFileNameFromFilePathName(const CString &strFilePath, char ch)
{
	long nPos1 = strFilePath.ReverseFind('\\');
	long nPos2 = strFilePath.ReverseFind('/');
	long nPos = 0;
	nPos = max(nPos1, nPos2);

	if (nPos <= 0)
	{
		return _T("");
		//return strFilePath;
	}

	CString strTemp;
	strTemp = strFilePath.Mid(nPos+1);

	return strTemp;
}

CString GetFileNameFromFilePath(const CString &strFilePath, char ch)
{
	long nPos1 = strFilePath.ReverseFind('\\');
	long nPos2 = strFilePath.ReverseFind('/');
	long nPos = 0;
	nPos = max(nPos1, nPos2);

	if (nPos <= 0)
	{
		return strFilePath;
	}

	CString strTemp;
	strTemp = strFilePath.Mid(nPos+1);

	return strTemp;
}

CString GetFileTitleFromFilePath(const CString &strFilePath, char ch)
{
	long nPos1 = strFilePath.ReverseFind('\\');
	long nPos2 = strFilePath.ReverseFind('/');
	long nPos = 0;
	nPos = max(nPos1, nPos2);

	if (nPos > 0)
	{//包含文件路径，例如：d:/A.txt
		nPos +=1;
	}
	else
	{//2022-9-4  lijunqing 兼容没有文件路径的情况，例如：A.txt
		nPos = 0;
	}

	nPos2 = strFilePath.ReverseFind('.');

	CString strTitle = strFilePath.Mid(nPos, nPos2 - nPos);
	return strTitle;
}

CString ChangeFilePostfix(const CString &strFile, const CString &strPostfix)
{
	CString strDestFile = strFile;

	long nPos = strDestFile.ReverseFind('.');
	long nPos2 = strDestFile.ReverseFind('/');//2023.7.12 zhouhj 防止文件夹名称中包含'.'
	long nPos3 = strDestFile.ReverseFind('\\');

	if (nPos2 < nPos3)
	{
		nPos2 = nPos3;
	}

	if ((nPos > 0)&&(nPos2<nPos))
	{
		strDestFile = strDestFile.Left(nPos + 1);
	}
	else
	{
		strDestFile += _T(".");
	}

	strDestFile += strPostfix;

	return strDestFile;
}

CString ChangeFileName(const CString &strFile, const CString &strFileName)
{
	CString strDestPath, strName, strPostFix;
	strPostFix = ParseFilePostfix(strFile);
	strDestPath = GetPathFromFilePathName(strFile);
    //strDestPath.AppendFormat(_T("%s.%s"), strFileName, strPostFix);
    strDestPath += strFileName;
    strDestPath += _T(".");
    strDestPath += strPostFix;

	return strDestPath;
}

//解析文件的名字和后缀名称
void ParseFileNameAndPostfix(const CString &strFileName, CString &strName, CString &strPostfix)
{
	long nPos = strFileName.ReverseFind('.');

	if (nPos >= 0)
	{
		strName = strFileName.Left(nPos);
		strPostfix = strFileName.Mid(nPos+1);
	}
	else
	{
		strName = strFileName;
		strPostfix = _T("");
	}
}

CString ParseFilePostfix(const CString &strFileName)
{
	long nPos = strFileName.ReverseFind('.');

	if (nPos >= 0)
	{
		return strFileName.Mid(nPos+1);
	}
	else
	{
		return _T("");
	}
}


CString ParseFileName(const CString &strFileName)
{
	CString strFile;
	strFile = GetPathFileNameFromFilePathName(strFileName);

	if (strFile.GetLength() == 0)
	{
		strFile = strFileName;
	}

	long nPos = strFile.ReverseFind('.');

	if (nPos >= 0)
	{
		return strFile.Left(nPos);
	}
	else
	{
		return strFile;
	}
}


BOOL CheckFileName(const CString &strFileName, CString &strInfor)
{
    strInfor = _T("");
    char ch[] = {'\\', '/', ':', '*', '?', '\"', '<', '>', '|' };
    BOOL bTrue = TRUE;

    long nIndex=0;

    for (nIndex=0; nIndex<9; nIndex++)
    {
        char c = ch[nIndex];

        if (strFileName.Find(c) >= 0)
        {
            bTrue = FALSE;
            strInfor.AppendFormat(_T("%c "), ch[nIndex]);
        }
    }

	return bTrue;
}

void MakeFileNameValidate(CString &strFileName)
{
	CString strPath;
	strPath = _P_FOLDER_PATH_SEPARATOR_;
    strFileName.Replace(strPath, _T("-"));
	strFileName.Replace(_T("/"), _T("-"));
	strFileName.Replace(_T(":"), _T("-"));
	strFileName.Replace(_T("*"), _T("-"));
	strFileName.Replace(_T("?"), _T("-"));
	strFileName.Replace(_T("<"), _T("-"));
	strFileName.Replace(_T(">"), _T("-"));
	strFileName.Replace(_T("|"), _T("-"));
	strFileName.Replace(_T("\""), _T("-"));
}

void ValidatePath(CString &strPath)
{
	CString strRight = strPath.Right(1);

    if (strRight == _P_FOLDER_PATH_SEPARATOR_)
	{
		return;
	}

	if (strRight == _T("/"))
	{
		return;
	}

    strPath += _P_FOLDER_PATH_SEPARATOR_;
}

#include <stdio.h>

BOOL IsFileExist2(const CString &strFile)
{
	return IsFileExist(strFile);
// 	CFileStatus fts;
// 	return CFile::GetStatus(strFile, fts);
}


//2021-1-2  lijunqing
void path_CheckSeparater(CString &strPath)
{
	if (strPath.GetLength() == 0)
	{
		return;
	}

	CString strRight = strPath.Right(1);

	if (strRight != _P_FOLDER_PATH_SEPARATOR_ && strRight != _T("/"))
	{
		strPath += _P_FOLDER_PATH_SEPARATOR_;
	}
}
