#include "stdafx.h"

#include "XFileFindEx.h"
#include "../API/FileApi.h"

#ifdef _PSX_IDE_QT_

#include "QT/XFileFindExImp.h"

#else

#include "VC/XFileFindExImp.h"

#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////
// CXFileFind implementation

CXFileFindEx::CXFileFindEx()
{
	m_pContext = new CXFileFindExImp();
}

CXFileFindEx::~CXFileFindEx()
{
	if (m_pContext != NULL)
	{
		delete m_pContext;
	}
}

void CXFileFindEx::Close()
{
	m_pContext->Close();
}

BOOL CXFileFindEx::FindFile(const CString &strName /* = NULL */,
	DWORD dwUnused /* = 0 */)
{
	return m_pContext->FindFile(strName, dwUnused);
}

BOOL CXFileFindEx::MatchesMask(DWORD dwMask) const
{
	return m_pContext->MatchesMask(dwMask);
}

BOOL CXFileFindEx::GetLastAccessTime(FILETIME* pTimeStamp) const
{
	return m_pContext->GetLastAccessTime(pTimeStamp);
}

BOOL CXFileFindEx::GetLastWriteTime(FILETIME* pTimeStamp) const
{
	return m_pContext->GetLastWriteTime(pTimeStamp);
}

BOOL CXFileFindEx::GetCreationTime(FILETIME* pTimeStamp) const
{
	return m_pContext->GetCreationTime(pTimeStamp);
}

BOOL CXFileFindEx::GetLastAccessTime(CTime& refTime) const
{
	return m_pContext->GetLastAccessTime(refTime);
}

BOOL CXFileFindEx::GetLastWriteTime(CTime& refTime) const
{
	return m_pContext->GetLastWriteTime(refTime);
}

BOOL CXFileFindEx::GetCreationTime(CTime& refTime) const
{
	return m_pContext->GetCreationTime(refTime);
}

BOOL CXFileFindEx::IsDots() const
{
	return m_pContext->IsDots();
}

BOOL CXFileFindEx::FindNextFile()
{
	return m_pContext->FindNextFile();
}

CString CXFileFindEx::GetFileURL() const
{
	return m_pContext->GetFileURL();
}

CString CXFileFindEx::GetRoot() const
{
	return m_pContext->GetRoot();
}

CString CXFileFindEx::GetFilePath() const
{
	return m_pContext->GetFilePath();
}

CString CXFileFindEx::GetFileTitle() const
{
	return m_pContext->GetFileTitle();
}

CString CXFileFindEx::GetFileName() const
{
	return m_pContext->GetFileName();
}

__uint64 CXFileFindEx::GetLength() const
{
	return m_pContext->GetLength();
}

long CXFileFindEx::FindFileCount(const CString &strRoot, const CString &strFileType)
{
	return m_pContext->FindFileCount(strRoot, strFileType);
}


// CFileFind

BOOL CXFileFindEx::IsReadOnly() const
{
	return m_pContext->IsReadOnly();
}

BOOL CXFileFindEx::IsDirectory() const
{
	return m_pContext->IsDirectory();
}

BOOL CXFileFindEx::IsCompressed() const
{
	return m_pContext->IsCompressed();
}

BOOL CXFileFindEx::IsSystem() const
{
	return m_pContext->IsSystem();
}

BOOL CXFileFindEx::IsHidden() const
{
	return m_pContext->IsHidden();
}

BOOL CXFileFindEx::IsTemporary() const
{
	return m_pContext->IsTemporary();
}

BOOL CXFileFindEx::IsNormal() const
{
	return m_pContext->IsNormal();
}

BOOL CXFileFindEx::IsArchived() const
{
	return m_pContext->IsArchived();
}


void CXFileFindEx::ClearFileFilters()
{
    m_pContext->ClearFileFilters();
}

void CXFileFindEx::AddFileFilter(const CString &strFilter)
{
   m_pContext->AddFileFilter(strFilter);
}

