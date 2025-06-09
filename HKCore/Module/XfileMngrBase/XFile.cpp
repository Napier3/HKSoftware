#include "stdafx.h"
#include "XFile.h"
#include "XFileMngr.h"

#include "../XLanguage/XLanguageResource.h"
#ifdef _PSX_QT_LINUX_
#include "../API/StringConvertApi.h"
#include <QTextCodec>
#endif

#ifndef _PSX_IDE_QT_
#include <windows.h>
#elif defined(_PSX_IDE_QT_) && !defined(_USE_NO_GUI_)
#include "../OSInterface/QT/XMessageBox.h"
#endif

#ifdef _PSX_IDE_QT_
#include <QFileInfo>
#include <QDateTime>
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXFileOptr *g_pXFileOptr = NULL;

BOOL XCopyFile(const CString &strSrcFile, const CString &strDestFile, BOOL bFailIfExists)
{
	if (g_pXFileOptr == NULL)
	{
		::X_CopyFile(strSrcFile, strDestFile, bFailIfExists);
	}
	else
	{
		g_pXFileOptr->XCopyFile(strSrcFile, strDestFile, bFailIfExists);
	}

	return TRUE;
}

BOOL xfile_XCopyFile(const CString &strFile, const CString &strFolder, BOOL bFailIfExists)
{
	CString strDestFile = strFolder;
	strDestFile += GetPathFileNameFromFilePathName(strFile);

	if (strDestFile != strFile)
	{
		::X_CopyFile(strFile, strDestFile, FALSE);
		return TRUE;
	}

	return FALSE;
}

#ifdef  _PSX_IDE_QT_
void QDateTimeToSystemTime(QDateTime& dateTime,SYSTEMTIME& sysTime)
{
//	CLogPrint::LogString(XLOGLEVEL_RESULT,_T("QDateTimeToSystemTime"));
	QDate date = dateTime.date();
	QTime time = dateTime.time();

	sysTime.wYear = date.year();
	sysTime.wMonth = date.month();
	sysTime.wDay = date.day();
	sysTime.wHour = time.hour();
	sysTime.wMinute = time.minute();
	sysTime.wSecond = time.second();
	sysTime.wMilliseconds = time.msec();
}
#endif

CXFile::CXFile()
{
	m_nSelected = 0;
	m_bIsOpen = FALSE;
	m_bIsYun = FALSE;

	m_nYunSize = 0;
	ZeroMemory(&m_tmYun, sizeof(m_tmYun));
	m_pYunFile = NULL;
}

CXFile::~CXFile()
{
	if (m_pYunFile != NULL)
	{
		delete m_pYunFile;
		m_pYunFile = NULL;
	}
}

BOOL CXFile::CopyTo(const CString &strPath)
{
	CString strSrcFile = GetRelativePath(TRUE);
	CString strDestFile = strPath + m_strName;

	return X_CopyFile(strSrcFile, strDestFile, FALSE);
}

BOOL CXFile::DeleteFile()
{
	if(m_bIsOpen)
	{		//如果文件已被打开
		return FALSE;	
	}

	CXFileMngr *pXFileMngr = xfile_GetXFileMngr(this);//(CXFileMngr*)GetAncestor(CLASSID_XFILEMNGR);

	if (pXFileMngr == NULL)
	{
		pXFileMngr = GetXFileMngr();//
	}

	if (pXFileMngr != NULL)
	{
		return pXFileMngr->XDeleteXFile(this);
	}
	else
	{
		return 0;
	}
	
	//CString strPath = GetRelativePath(TRUE);
	//BOOL bFlag =  ::DeleteFile(strPath);

	//return bFlag;
}

BOOL CXFile::GetFilePostfix(CString &strPostfix, BOOL bHasDot)
{
	BOOL bFlag = IsFileExist();
	
	if(bFlag || m_bIsYun)
	{
		int nIndex = m_strName.ReverseFind('.');

		if (bHasDot)
		{
			strPostfix = m_strName.Right(m_strName.GetLength()- nIndex);
		}
		else
		{
			strPostfix = m_strName.Right(m_strName.GetLength()- nIndex-1);
		}
	}

	return TRUE;
}

BOOL CXFile::RenameFile(const CString& strNewName)
{
	if(m_bIsOpen)
	{
		return FALSE;
	}

	if(strNewName == m_strName)
	{
		return TRUE;
	}

	CString strOldName = m_strName;
	CString strFromName = GetRelativePath(TRUE);	

	m_strName = strNewName;
	m_strID = strNewName;
	CString strToName = GetRelativePath(TRUE);
#ifndef _PSX_IDE_QT_
	CFile::Rename(strFromName, strToName);
#else
	char* pstrFromName,*pstrToName;
	CString_to_char(strFromName, &pstrFromName);
	CString_to_char(strToName, &pstrToName);
	rename(pstrFromName, pstrToName);
	delete pstrFromName;
	delete pstrToName;
#endif
	if (IsFileExist())
	{
		return TRUE;
	}
	else
	{
		m_strName = strOldName;
		m_strID = strOldName;
		return FALSE;
	}
}

BOOL  CXFile::GetModifyTime(CString& strModifyTime)
{
	CString strFile = GetTotalFileName();
	return xfile_GetModifyTime(strFile, strModifyTime);
}

BOOL  CXFile::GetModifyTime(SYSTEMTIME &tm)
{
	CString strFile = GetTotalFileName();
	return xfile_GetModifyTime(strFile, tm);
}

BOOL CXFile::GetFileSize(CString& strFileSize)
{ 
	return xfile_GetFileSize(GetTotalFileName(), strFileSize);
}

// #ifdef _PSX_QT_LINUX_
// long CXFile::GetFileSize(BOOL bUseUtf8Code)
// {
// 	if (bUseUtf8Code)
// 	{
// 		QTextCodec *codec = QTextCodec::codecForName("utf-8");
// 		QTextCodec::setCodecForLocale(codec);
// 		QTextCodec::setCodecForCStrings(codec);
// 		QTextCodec::setCodecForTr(codec);
// 	}
// 
// 	long nRet = GetFileSize();
// 
// 	if (bUseUtf8Code)
// 	{
// 		QTextCodec *codec = QTextCodec::codecForName("GBK");
// 		QTextCodec::setCodecForLocale(codec);
// 		QTextCodec::setCodecForCStrings(codec);
// 		QTextCodec::setCodecForTr(codec);	
// 	}
// 
// 	return nRet;
// }
// #endif

long CXFile::GetFileSize()
{
	CString strFileSize;
	strFileSize = GetTotalFileName();//20220926 zhouhj 直接通道返回值传递参数有风险,改为临时变量

#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strFileSize,&pOldTextCodec);
#endif
	long nRet =  xfile_GetFileSize(strFileSize);

#ifdef _PSX_QT_LINUX_
	ResetLocalCodec(pOldTextCodec);
#endif
	return nRet;
}

BOOL  CXFile::GetModifyTime_Yun(CString& strModifyTime)
{
	//2016-12-3 lijq
	strModifyTime.Format(_T("%4d-%02d-%02d %02d:%02d")
		,m_tmYun.wYear,m_tmYun.wMonth,m_tmYun.wDay,m_tmYun.wHour
		,m_tmYun.wMinute);

	return TRUE;
}

BOOL CXFile::GetFileSize_Yun(CString& strFileSize)
{  
	//2016-12-3 lijq
	strFileSize.Format(_T("%.2f"),m_nYunSize/1024.0f);
	return TRUE;
}

long CXFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nSelected);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileType);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileName);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nSelected);
		BinarySerializeRead(oBinaryBuffer, m_strFileType);
		BinarySerializeRead(oBinaryBuffer, m_strFileName);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nSelected);
		BinarySerializeWrite(oBinaryBuffer, m_strFileType);
		BinarySerializeWrite(oBinaryBuffer, m_strFileName);
	}
	return 0;
}

BOOL CXFile::CopyOwn(CBaseObject* pDest)
{
	CExBaseObject::CopyOwn(pDest);

	CXFile *p = (CXFile*)pDest;

	p->m_nSelected = m_nSelected;
	p->m_strFileType = m_strFileType;
	p->m_strFileName = m_strFileName;
	p->m_bIsOpen = m_bIsOpen;

	return TRUE;
}

CBaseObject* CXFile::Clone()
{
	CXFile *pNew = new CXFile();
	Copy(pNew);
	return pNew;
}

BOOL CXFile::IsFileExist()
{
	CString strFileName = GetRelativePath(TRUE);
	return ::IsFileExist(strFileName);
}

CString CXFile::GetRelativePath(BOOL bAddRoot)
{
	CString strPath;

	if (bAddRoot)
	{
		CXFolder *pFolder = (CXFolder*)GetParent();
		strPath = pFolder->GetFolderPath(TRUE) + m_strName;
	}
	else
	{
		CExBaseObject *pRoot = NULL;
		CExBaseObject *pParent = NULL;

		pParent = (CExBaseObject*)GetParent();
		strPath = m_strName;

		while (pParent != NULL)
		{
			pRoot = (CExBaseObject*)pParent->GetParent();

			if (pRoot == NULL)
			{
				break;
			}

			strPath = pParent->m_strName + _P_FOLDER_PATH_SEPARATOR_ + strPath;

			pParent = pRoot;
		}
	}

	return strPath;
}

CString CXFile::GetFolderPath(BOOL bAddRoot)
{
	CString strPath;

	if (bAddRoot)
	{
		CXFolder *pFolder = (CXFolder*)GetParent();
		strPath = pFolder->GetFolderPath(TRUE);
	}
	else
	{
		CExBaseObject *pRoot = NULL;
		CExBaseObject *pParent = NULL;

		pParent = (CExBaseObject*)GetParent();

		while (pParent != NULL)
		{
			pRoot = (CExBaseObject*)pParent->GetParent();

			if (pRoot == NULL)
			{
				break;
			}

			strPath = pParent->m_strName + _P_FOLDER_PATH_SEPARATOR_ + strPath;

			pParent = pRoot;
		}
	}

	return strPath;
}

CString CXFile::GetTotalFileName()
{
	return GetRelativePath(TRUE);
}

CXFileMngr* CXFile::GetXFileMngr()
{
	//return (CXFileMngr*)GetAncestor(CLASSID_XFILEMNGR);
	return xfile_GetXFileMngr(this);
}

CDataGroup* CXFile::XFolderToDataGroup()
{
	long nDepth = GetDepth();
	if (nDepth == 0)
	{
		return NULL;
	}

	CDataGroup* pPathGroup = new CDataGroup;
	ASSERT(pPathGroup != NULL);

	CXFolder* pFolder = (CXFolder*)GetParent();
	pPathGroup->m_strName = pFolder->m_strName;
	CDataGroup* pYunFolder = pYunFolder = pFolder->GetYunFolder();
	if (pYunFolder != NULL)
	{
		pPathGroup->m_strID = pYunFolder->m_strID;
	}

	CXFolder* pRootFolder = (CXFolder*)GetAncestorByDepth(nDepth);
	ASSERT(pRootFolder != NULL);

	return pFolder->ParentToDataGroup(pPathGroup, pRootFolder);
}

CDataGroup* CXFile::GetLeafDataGroup(CDataGroup *pPathGroup)
{
	ASSERT(pPathGroup != NULL);

	CDataGroup *pGroup = pPathGroup;

	UINT nClassID;
	CExBaseObject *p = NULL;
	POS pos = pPathGroup->GetHeadPosition();

	while (pos != NULL)
	{
		p = pPathGroup->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			pGroup = GetLeafDataGroup((CDataGroup *)p);
		}
	}
	
	return pGroup;
}

BOOL xfile_CheckFileName(const CString &strFileName, CWnd *pWnd)
{
	CString strInfor;

	if (!CheckFileName(strFileName, strInfor))
	{
		CString strMsg;
#ifdef NOT_USE_XLANGUAGE
        strMsg.Format(_T("文件名【%s】包含【%s】等非法字符"), strFileName.GetString(), strInfor.GetString());
#else
        strMsg.Format(g_sLangTxt_FileNameInclude/*_T("文件名【%s】包含【%s】等非法字符")*/, strFileName.GetString(), strInfor.GetString());
#endif

		if (pWnd != NULL)
		{
#ifdef NOT_USE_XLANGUAGE
#ifndef _PSX_IDE_QT_
			pWnd->MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONEXCLAMATION);
#elif defined(_PSX_IDE_QT_) && !defined(_USE_NO_GUI_)
			CXMessageBox::information(NULL, _T("提示"), strMsg);
#endif
#else
#ifndef _PSX_IDE_QT_
			pWnd->MessageBox(strMsg, g_sLangTxt_Message/*_T("提示")*/, MB_OK | MB_ICONEXCLAMATION);
#elif defined(_PSX_IDE_QT_) && !defined(_USE_NO_GUI_)
			CXMessageBox::information(NULL, g_sLangTxt_Message, strMsg);
#endif
#endif
		}
		else
		{
#ifndef _PSX_IDE_QT_
			AfxMessageBox(strMsg, MB_OK | MB_ICONEXCLAMATION);
#elif defined(_PSX_IDE_QT_) && !defined(_USE_NO_GUI_)
			CXMessageBox::information(NULL, _T("提示"), strMsg);
#endif
		}

		return FALSE;
	}
	else
	{
		return TRUE;
	}
}



BOOL xfile_GetFileSize(const CString &strFile, CString& strFileSize)
{ 
#ifndef _PSX_IDE_QT_
	WIN32_FIND_DATA fileInfo; 
#else
	QFileInfo fileInfo(strFile.toUtf8());
#endif

	HANDLE hFind; 
	double fileSize; 
#ifndef _PSX_IDE_QT_
	hFind = FindFirstFile(strFile ,&fileInfo); 

	if(hFind != INVALID_HANDLE_VALUE) 
	{
		fileSize = fileInfo.nFileSizeLow; 
		strFileSize.Format(_T("%.2f"),fileSize/1024);
		FindClose(hFind);

		return TRUE;
	}
	else
	{
		strFileSize = _T("----");
	}

	FindClose(hFind); 
#else
	fileSize = fileInfo.size();
    fileSize /= 1024;
    strFileSize.Format(_T("%.2lf"),fileSize/*fileSize/1024*/);
#endif

	return FALSE;
}

DWORD xfile_GetFileSize(const CString &strFile)
{
#ifndef _PSX_IDE_QT_
	WIN32_FIND_DATA fileInfo; 
#else
#ifdef _PSX_QT_LINUX_//在linux下需要进行编码转换,采用utf8编码处理
	QFileInfo fileInfo(strFile);

	if (!fileInfo.exists())
	{
		CString strUtf8String;

		if (gbk_to_utf8(strFile,strUtf8String)>0)
		{
			fileInfo.setFile(strUtf8String);
		} 
		else
		{

			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("xfile_GetFileSize[%s][%s]."),strFile.GetString(),strUtf8String.GetString());
		}
	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("xfile_GetFileSize[%s]."),strFile.GetString());
// 	}
#else
	QFileInfo fileInfo(strFile);
#endif

#endif

	HANDLE hFind; 
	DWORD fileSize = 0; 

#ifndef _PSX_IDE_QT_
	hFind = FindFirstFile(strFile ,&fileInfo); 

	if(hFind != INVALID_HANDLE_VALUE) 
	{
		fileSize = fileInfo.nFileSizeLow; 
	}

	FindClose(hFind); 
#else
	fileSize = fileInfo.size();
#endif

	return fileSize;
}

BOOL xfile_GetFileInfo(const CString &strFile, DWORD &dwSize, SYSTEMTIME &dtTime)
{
#ifndef _PSX_IDE_QT_
	WIN32_FIND_DATA fileInfo; 
	HANDLE hFind; 

	hFind = FindFirstFile(strFile ,&fileInfo); 

	if(hFind != INVALID_HANDLE_VALUE) 
	{
		dwSize = fileInfo.nFileSizeLow; 
		FileTimeToSystemTime(&fileInfo.ftLastWriteTime, &dtTime);
	}

	FindClose(hFind); 

	return (hFind != INVALID_HANDLE_VALUE);
#else
	QFileInfo fileInfo(strFile);
	if (!fileInfo.exists())
	{
		return FALSE;
	}
	dwSize = fileInfo.size();

	QDateTime dateTime = fileInfo.lastModified();
	QDateTimeToSystemTime(dateTime,dtTime);

	return TRUE;
#endif
}


BOOL  xfile_GetModifyTime(const CString &strFile, CString& strModifyTime)
{
	SYSTEMTIME systime;
	BOOL bFlag = xfile_GetModifyTime(strFile, systime);

	if (bFlag)
	{
		strModifyTime.Format(_T("%4d-%02d-%02d %02d:%02d")
			,systime.wYear,systime.wMonth,systime.wDay,systime.wHour
			,systime.wMinute);
	}
	else
	{
		strModifyTime = _T("----");
	}

	return bFlag;
}

BOOL  xfile_GetModifyTime(const CString &strFile, SYSTEMTIME &tmModifyTime)
{
#ifndef _PSX_IDE_QT_
	HANDLE hFile;
	WIN32_FIND_DATA wfd;
	FILETIME localtime;
	memset(&wfd,0,sizeof(wfd));
	hFile = FindFirstFile(strFile,&wfd);

	if( hFile != INVALID_HANDLE_VALUE)
	{
		FileTimeToLocalFileTime(&wfd.ftLastWriteTime,&localtime);
		FileTimeToSystemTime(&localtime,&tmModifyTime);
		FindClose(hFile);
		return TRUE;
	}

	FindClose(hFile);
#else

#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strFile,&pOldTextCodec);
#endif
    QFileInfo fileInfo(strFile);
//    if (!QFile::exists(strFile))
    if (!fileInfo.exists())
    {
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
		ResetLocalCodec(pOldTextCodec);
#endif
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("file not exists(%s). "),strFile.GetString());
		return FALSE;
	}


	QDateTime dateTime = fileInfo.lastModified();
	QDateTimeToSystemTime(dateTime,tmModifyTime);

#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
	ResetLocalCodec(pOldTextCodec);
#endif
#endif
	return TRUE;
}


UINT xfile_GetImageIndex(CExBaseObject* pObj)
{
	UINT nClassID = pObj->GetClassID();

	if (g_pXFileOptr != NULL)
	{
		nClassID = g_pXFileOptr->GetImgIndex(pObj);

		if (nClassID != 0xFFFFFFFF)
		{
			return nClassID;
		}
	}

	nClassID = pObj->GetClassID();

	switch (nClassID)
	{
	case CLASSID_XFILE:
		if (((CXFile*)pObj)->IsYunFile())
		{
			nClassID = 8;
		}
		else
		{
			nClassID = 2;
		}
		break;
	case CLASSID_XFOLDER:
		if (((CXFolder*)pObj)->IsYunFolder())
		{
			nClassID = 6;
		}
		else
		{
			nClassID = 0;
		}
		break;
	case CLASSID_XFILEMNGR:
		nClassID = 0;
		break;
	default:
		nClassID = 0;
		break;
	}

	return nClassID;
}

BOOL xfile_IsYunFile(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();

	switch (nClassID)
	{
	case CLASSID_XFILE:
		return ((CXFile*)pObj)->IsYunFile();

	case CLASSID_XFOLDER:
		return ((CXFolder*)pObj)->IsYunFolder();

	default:
		break;
	}

	return FALSE;
}

#ifndef _PSX_IDE_QT_
BOOL xfile_LoadFileMngrBmp(CBmpImageList *pBmpImageList, const CString &strBmpFile, long nCount, COLORREF crMask)
{
	CString strFile;

	if (::IsFileExist(strBmpFile))
	{
		strFile = strBmpFile;
	}
	else
	{
		strFile = _P_GetCommonResourcePath();
		strFile += _T("FileMngrBmp.bmp");
	}

	return pBmpImageList->LoadBmpFile(strFile, nCount, crMask);
}
#endif

CString xfile_GetYunFileVersion(CXFile *pXFile)
{
	ASSERT (pXFile != NULL);

	if (pXFile->m_pYunFile != NULL)
	{
		return pXFile->m_pYunFile->m_strValue;
	}
	else
	{
		return _T("");
	}
}

