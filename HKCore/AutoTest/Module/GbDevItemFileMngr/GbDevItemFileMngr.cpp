#include "stdafx.h"
#include "GbDevItemFileMngr.h"
#include "GbDevItemFolder.h"
#include "GbDevItemFile.h"
#include "..\..\Module\API\FileApi.h"

CGbDevItemFileMngr* CGbDevItemFileMngr::g_pGbDevItemFileMngr = NULL;
long CGbDevItemFileMngr::g_nGbDevItemFileMngrRef = 0;

CGbDevItemFileMngr* CGbDevItemFileMngr::CreateGbDevItemFileMngr()
{
	g_nGbDevItemFileMngrRef ++;

	if(g_nGbDevItemFileMngrRef == 1)
	{
		g_pGbDevItemFileMngr = new CGbDevItemFileMngr();
	}

	return g_pGbDevItemFileMngr;
}

void CGbDevItemFileMngr::Release()
{
	g_nGbDevItemFileMngrRef --;

	if(g_nGbDevItemFileMngrRef == 0)
	{
		delete g_pGbDevItemFileMngr;
		g_pGbDevItemFileMngr = NULL;
	}

}

CGbDevItemFileMngr::CGbDevItemFileMngr()
{
	m_strRootPath = GetGbDevItemFilePath();
	m_strID = m_strRootPath;		//CExBaseObject::GetPath();
	m_strID.TrimRight(_T("\\"));

	if (!::IsFileExist(m_strID))
	{
		::CreateAllDirectories(m_strID);
	}

	m_strPath = m_strRootPath;
	m_strName = g_strGbDevItemSavePath;
}

CGbDevItemFileMngr::~CGbDevItemFileMngr()
{

}
BOOL CGbDevItemFileMngr::SaveXMLFile()
{

	return TRUE;
}

BOOL CGbDevItemFileMngr::OpenXMLFile(const CString &strTypeName, const CString &strTypeID)
{
	m_strName = strTypeName + /*_T("文件管理")*/g_sLangTxt_FileMngr;

	DeleteAll();
	CExBaseList *pList = GEtFilePostfixList();
	pList->DeleteAll();
	CXFileTypes *pXFileTypes = GetXFileTypes();
	pXFileTypes->DeleteAll();
	SearchFiles(strTypeName, strTypeID, this->GetRootPath());

	return TRUE;
}