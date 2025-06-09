#include "stdafx.h"
#include "CFile_QT.h"
//#include "../../API/StringApi.h"

#include "CString_QT.h"
#include <QDataStream>

bool CopyFileW(
    const CString &strExistingFileName,
    const CString &strNewFileName,
    BOOL bFailIfExists
    )
{
    bool bRet = QFile::copy(strExistingFileName, strNewFileName);
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
                system("sync");
#endif
     return bRet;
}

bool DeleteFileW(const CString &strFileName)
{
    bool bRet = QFile::remove(strFileName);
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
                system("sync");
#endif
    return bRet;
}

UINT CFile::Read(void* lpBuf, unsigned int nCount)
{
	return (UINT)QFile::read((char *)lpBuf,nCount);
}

void CFile::Write(const void* lpBuf, unsigned int nCount)
{
	//add by yyj at 20200429 begin
	void* pChar = const_cast<void*>(lpBuf);
	const char*p = static_cast<const char*>(pChar);
	write(p,nCount);
	//add by yyj at 20200429 end
}

BOOL CFile::Open(const CString &strFileName, UINT nOpenFlags)
{
	//add by yyj at 20200429 begin
	setFileName(strFileName);

// 	QIODevice::OpenMode nOpenMode = QIODevice::ReadOnly;
// 
// 	if(nOpenFlags&modeWrite)
// 		nOpenMode |= QIODevice::WriteOnly;
// 	if(nOpenFlags&modeReadWrite)
// 		nOpenMode |= QIODevice::ReadWrite;
// 	if(nOpenFlags&modeNoTruncate)
// 		nOpenMode |= QIODevice::Append;
// 	if(nOpenFlags&typeText)
// 		nOpenMode |= QIODevice::Text;

	if(QFile::open((QIODevice::OpenMode)nOpenFlags))
	{
		return TRUE;
	}
	//add by yyj at 20200429 end

	return FALSE;
}

void CFile::Close()
{
	if (handle() != (int)INVALID_HANDLE_VALUE)
	{
		close();
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
        ::system("sync");
#endif
	}	
}

BOOL CFile::Flush()
{
	if (handle() != (int)INVALID_HANDLE_VALUE)
	{
		flush();
	}

    return TRUE;
}

long CFile::SeekToEnd()
{
	QFile::seek(QFile::size());
	return 1;
}

void CFile::SeekToBegin()
{
	QFile::seek(0);
}

int CFile::GetLength()
{
	return QFile::size();
}

CString CFile::GetFileName()
{
	return QFile::fileName();
}

#ifdef _PSX_QT_LINUX_
void InitLocalCodec_BeforeReadWrite(const CString &strPath,QTextCodec **ppOldTextCodec)
{
	*ppOldTextCodec = QTextCodec::codecForLocale();
	QTextCodec *pSetCodec = NULL;

//yzj 2024.1.31 周磊统一usb拓展空间的编码格式为utf8
// 	if (strPath.Find(_T("/Usb/sda")) == -1)
// 	{
//		pSetCodec = QTextCodec::codecForName("utf-8");
// 	}
// 	else
// 	{
// 		pSetCodec = QTextCodec::codecForName("GBK");
// 	}
	pSetCodec = QTextCodec::codecForName("utf-8");

	if (pSetCodec != (*ppOldTextCodec))
	{
#ifdef _USE_IN_IED_QT5
		QTextCodec::setCodecForLocale(pSetCodec);
#else
		QTextCodec::setCodecForLocale(pSetCodec);
		QTextCodec::setCodecForCStrings(pSetCodec);
		QTextCodec::setCodecForTr(pSetCodec);
#endif
	}
	else
	{
		*ppOldTextCodec = NULL;
	}
}
#endif