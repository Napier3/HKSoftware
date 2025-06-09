#include "stdafx.h"

#include "XFileFindExImp.h"
#include "../../API/FileApi.h"

#ifdef _PSX_QT_LINUX_
#include "../../API/StringConvertApi.h"
#include "../../API/StringApi.h"
#endif

/*
QString FindFile( QString &strFilePath,  QString &strNameFilters)
{
 if (strFilePath.isEmpty() || strNameFilters.isEmpty())
 {
  return QString();
 }

 QDir dir;
    QStringList filters;

    filters << strNameFilters;
    dir.setPath(strFilePath);
    dir.setNameFilters(filters);
    QDirIterator iter(dir,QDirIterator::Subdirectories);

    while (iter.hasNext())
    {
        iter.next();
        QFileInfo info=iter.fileInfo();
        if (info.isFile())
  {
   return info.absoluteFilePath().replace('/', '\\');
        }
    }

 return QString();
}
*/
////////////////////////////////////////////////////////////////////////////
// CXFileFind implementation

CXFileFindExImp::CXFileFindExImp()
{
    m_pIter = NULL;
}

CXFileFindExImp::~CXFileFindExImp()
{
	Close();
}

void CXFileFindExImp::Close()
{
    if (m_pIter != NULL)
    {
        delete m_pIter;
        m_pIter = NULL;
    }
}

BOOL CXFileFindExImp::FindFile(const CString &strName /* = NULL */,
	DWORD dwUnused /* = 0 */)
{
    Close();

    if (strName.GetLength() >= X_MAX_PATH)
	{
		return FALSE;		
	}
	
    m_oDir.setPath(strName);

    if (m_strFilters.size() > 0)
    {
        m_oDir.setNameFilters(m_strFilters);
    }

    m_pIter = new QDirIterator (m_oDir/*, QDirIterator::Subdirectories*/);//20220702 zhouhj �˴���������Ŀ¼,����ģʽ��,�ȱ�����ǰĿ¼,������ɺ�,�ٱ�������Ŀ¼
	m_strRoot = GetPathFromFilePathName(strName);

    return m_pIter->hasNext();
}

BOOL CXFileFindExImp::MatchesMask(DWORD dwMask)
{
    return FALSE;
}

BOOL CXFileFindExImp::GetLastAccessTime(FILETIME* pTimeStamp)
{
    if(m_pIter == NULL)
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    QDateTime tm = info.lastRead();

#ifndef _PSX_QT_LINUX_
	qint64 n64Value = tm.toMSecsSinceEpoch();
	pTimeStamp->dwLowDateTime = (DWORD) n64Value;
	pTimeStamp->dwHighDateTime = (DWORD)(n64Value>> 32);
#else
	*pTimeStamp = tm.toMSecsSinceEpoch();
#endif

    return TRUE;
}

BOOL CXFileFindExImp::GetLastWriteTime(FILETIME* pTimeStamp)
{
    if(m_pIter == NULL)
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    QDateTime tm = info.lastModified();
#ifndef _PSX_QT_LINUX_
	qint64 n64Value = tm.toMSecsSinceEpoch();
	pTimeStamp->dwLowDateTime = (DWORD) n64Value;
	pTimeStamp->dwHighDateTime = (DWORD)(n64Value >> 32);
#else
	*pTimeStamp = tm.toMSecsSinceEpoch();
#endif

    return TRUE;
}

BOOL CXFileFindExImp::GetCreationTime(FILETIME* pTimeStamp)
{
    if(m_pIter == NULL)
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    QDateTime tm = info.created();
#ifndef _PSX_QT_LINUX_
	qint64 n64Value = tm.toMSecsSinceEpoch();
	pTimeStamp->dwLowDateTime = (DWORD) n64Value;
	pTimeStamp->dwHighDateTime = (DWORD)(n64Value >> 32);
#else
	*pTimeStamp = tm.toMSecsSinceEpoch();
#endif

    return TRUE;
}

BOOL CXFileFindExImp::GetLastAccessTime(CTime& refTime)
{
    if(m_pIter == NULL)
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    QDateTime tm = info.lastRead();
    refTime = tm;

    return TRUE;
}

BOOL CXFileFindExImp::GetLastWriteTime(CTime& refTime)
{
    if(m_pIter == NULL)
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    QDateTime tm = info.lastModified();
    refTime = tm;

    return TRUE;
}

BOOL CXFileFindExImp::GetCreationTime(CTime& refTime)
{
    if(m_pIter == NULL)
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    QDateTime tm = info.created();
    refTime = tm;

    return TRUE;
}

BOOL CXFileFindExImp::IsDots()
{
    if(m_pIter == NULL)
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
	BOOL bIsDots = info.isRoot();

	if (!bIsDots)//20220702 zhouhj �˴���Ȼ��Ҫ����
	{
		CString strResult;
		strResult = info.fileName();

		if ((strResult == ".")||(strResult == ".."))
		{
			bIsDots = TRUE;
		}
	}

    return bIsDots;
}

BOOL CXFileFindExImp::FindNextFile()
{
    if(m_pIter == NULL)
    {
        return FALSE;
    }

	m_pIter->next();//20220704 zhouhj ����next��,��ȡ��Ӧ���ļ�

   if (m_pIter->hasNext())
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

CString CXFileFindExImp::GetFileURL()
{
    CString strResult("file://");

    if(m_pIter != NULL)
    {
        strResult += GetFilePath();
    }
	
	return strResult;
}

CString CXFileFindExImp::GetRoot()
{
    return m_strRoot;
}

CString CXFileFindExImp::GetFilePath()
{
	CString strResult = m_strRoot;

    if(m_pIter != NULL)
    {
        QFileInfo info=m_pIter->fileInfo();
        strResult = info.filePath();
    }

	return strResult;
}

CString CXFileFindExImp::GetFileTitle()
{
    CString strResult = m_strRoot;

    if(m_pIter != NULL)
    {
        QFileInfo info=m_pIter->fileInfo();
        strResult = info.baseName();
    }

    return strResult;
}

CString CXFileFindExImp::GetFileName()
{
    CString strResult = m_strRoot;

    if(m_pIter != NULL)
    {
        QFileInfo info=m_pIter->fileInfo();
        strResult = info.fileName();
//		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("CXFileFindExImp::GetFileName[%s]"),strResult.GetString());
		//20230512 zhouhj ����Ҫ�ڴ�ת��
// #ifdef _PSX_QT_LINUX_//��linux����Ҫ���б���ת��,����utf8���봦��
// 		CString strGbkString;
// 
// 		if (utf8_to_gbk(strResult,strGbkString)>0)
// 		{
// 			strResult = strGbkString;
// 		}
// #endif
    }

    return strResult;
}

__uint64 CXFileFindExImp::GetLength()
{
    __uint64 nLen = 0;

    if(m_pIter != NULL)
    {
        QFileInfo info=m_pIter->fileInfo();
        nLen = info.size();
    }

    return nLen;
}

long CXFileFindExImp::FindFileCount(const CString &strRoot, const CString &strFileType)
{
	CString strPath;

	if (strRoot.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
	{
        strPath.Format(_T("%s*.%s"), strRoot.GetString(), strFileType.GetString());
	}
	else
	{
        strPath.Format(_T("%s\\*.%s"), strRoot.GetString(), strFileType.GetString());
	}

	BOOL b = FindFile(strPath);
	long nCount = 0;

	while (b)
	{
		b = FindNextFile();//zhouhj 20220704 �ĺ�������Ϊ��ȡ����ǰ�ļ�,��ȡ�����һ���ļ��Ƿ�����÷���ֵ��ʶ

		if( !IsDots() )
		{ 
			if(IsDirectory()) 
			{ 
			}
			else 
			{ 
				nCount++;
			} 
		} 
	}

	return nCount;
}


BOOL CXFileFindExImp::IsReadOnly()
{
    if(m_pIter == NULL)//20220702 zhouhj Ӧ�ж�Ϊ�շ���
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    return !( info.isWritable());
}

BOOL CXFileFindExImp::IsDirectory()
{
    if(m_pIter == NULL)//20220702 zhouhj Ӧ�ж�Ϊ�շ���
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    return info.isDir();
}

BOOL CXFileFindExImp::IsCompressed()
{
    if(m_pIter == NULL)//20220702 zhouhj Ӧ�ж�Ϊ�շ���
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    return info.isBundle();
}

BOOL CXFileFindExImp::IsSystem()
{
    if(m_pIter == NULL)//20220702 zhouhj Ӧ�ж�Ϊ�շ���
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    return info.isAbsolute();
}

BOOL CXFileFindExImp::IsHidden()
{
    if(m_pIter == NULL)//20220702 zhouhj Ӧ�ж�Ϊ�շ���
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    return info.isHidden();
}

BOOL CXFileFindExImp::IsTemporary()
{
    if(m_pIter == NULL)//20220702 zhouhj Ӧ�ж�Ϊ�շ���
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    return info.isRelative();
}

BOOL CXFileFindExImp::IsNormal()
{
    if(m_pIter == NULL)
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    return info.isAbsolute();
}

BOOL CXFileFindExImp::IsArchived()
{
    if(m_pIter == NULL)//20220702 zhouhj Ӧ�ж�Ϊ�շ���
    {
        return FALSE;
    }

    QFileInfo info=m_pIter->fileInfo();
    return info.isFile();
}

void CXFileFindExImp::ClearFileFilters()
{
    m_strFilters.clear();
}

void CXFileFindExImp::AddFileFilter(const CString &strFilter)
{
    m_strFilters.append(strFilter);
}
