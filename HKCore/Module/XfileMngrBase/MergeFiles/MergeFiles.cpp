#include "stdafx.h"

#include "MergeFiles.h"
#include "..\..\Module\API\FileApi.h"
#include "..\XFileFindEx.h"

////////////////////////////////////////////////////////////////////////////
// CXMergeFiles implementation

CMergeFiles::CMergeFiles()
{
	m_strEndIF = _T("#endif");
}

CMergeFiles::~CMergeFiles()
{
	
}

BOOL CMergeFiles::MergeFiles(const CString &strSrcPath, const CString &strDestFile)
{
	if (!m_oFileDest.Open(strDestFile, CFile::modeCreate | CFile::modeWrite))
	{
		return FALSE;
	}

	CString strTextFile;
	strTextFile = ChangeFilePostfix(strDestFile, _T("txt"));

	if (!m_oFileTxt.Open(strTextFile, CFile::modeCreate | CFile::modeWrite))
	{
		return FALSE;
	}

	MergeFiles(strSrcPath);

	m_oFileDest.Close();
	m_oFileTxt.Close();

	return TRUE;
}

void CMergeFiles::MergeFiles(const CString &strSrcPath)
{
	CXFileFindEx finder;
	CString strPath = strSrcPath;
	CString strFinder;
	CString strHeader;
	CString strText;
	CString strEndIF;
	
	if (strPath.Right(1) == _T("\\"))
	{
		strFinder = strPath + _T("*.*");
	}
	else
	{
		strFinder.Format(_T("%s\\*.*"), strPath);
	}

	BOOL bIsFinded = finder.FindFile(strFinder);

	while(bIsFinded)
	{
		bIsFinded = (BOOL)finder.FindNextFile();

		if( !finder.IsDots())
		{
			if(finder.IsDirectory())
			{
				strPath = finder.GetFileName();
				MergeFiles(strPath);
			}
			else
			{
				CFile oFile;
				strPath = finder.GetFilePath();
				
				if (!oFile.Open(strPath, CFile::modeRead))
				{
					continue;
				}

				long nLen = oFile.GetLength();
				char *pBuffer = new char[nLen + 10];
				oFile.Read(pBuffer, nLen);

				strHeader = finder.GetFileName();
				strHeader.Replace(_T("."), _T("_"));
				strHeader = _T("_") + strHeader + _T("_\r\n");

				strText = _T("#ifdef ") + strHeader;
				m_oFileDest.Write(strText, strText.GetLength());

				m_oFileDest.Write(pBuffer, nLen);
				m_oFileDest.Write("\r\n", 2);

				strEndIF.Format(_T("#endif      //%s\r\n\r\n\r\n"), strHeader);
				m_oFileDest.Write(strEndIF, strEndIF.GetLength());

				oFile.Close();
				delete pBuffer;

				strText = _T("#define ") + strHeader;
				m_oFileTxt.Write(strText, strText.GetLength());
			}
		}
	}

	finder.Close();
}


