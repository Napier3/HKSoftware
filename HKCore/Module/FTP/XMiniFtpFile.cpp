#include "StdAfx.h"
#include "XMiniFtpFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CXMiniFtpFile::CXMiniFtpFile()
{


}

CXMiniFtpFile::~CXMiniFtpFile()
{

}

CXMiniFtpFileMngr::CXMiniFtpFileMngr()
{
	m_pMainWnd = NULL;
}

CXMiniFtpFileMngr::~CXMiniFtpFileMngr()
{

}

void CXMiniFtpFileMngr::AttachMainWnd(CWnd *pMainWnd)
{
	m_pMainWnd = pMainWnd;
}

CXMiniFtpFile* CXMiniFtpFileMngr::AddFile(const CString &strFile)
{
	CXMiniFtpFile *pFile = (CXMiniFtpFile*)FindByID(strFile);

	if (pFile == NULL)
	{
		CXMiniFtpFile *pFile = new CXMiniFtpFile();
		pFile->m_strID = strFile;
		pFile->m_strName = strFile;
		AddTail(pFile);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strFile);

		if (m_pMainWnd != NULL)
		{
			m_pMainWnd->PostMessage(WM_RECEIVE_FILE, (WPARAM)pFile, (LPARAM)pFile);
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("文件已经存在"), strFile);
	}

	return pFile;
}
