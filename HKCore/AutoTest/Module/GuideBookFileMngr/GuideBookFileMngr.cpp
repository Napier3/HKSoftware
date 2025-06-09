#include "stdafx.h"
#include "GuideBookFileMngr.h"

CGuideBookFileMngr* CGuideBookFileMngr::g_pGuideBookFileMngr = NULL;
long CGuideBookFileMngr::g_nGuideBookFileMngr = 0;


CGuideBookFileMngr* CGuideBookFileMngr::CreateGuideBookFileMngr(BOOL bYun, BOOL bUseAts)
{
	g_nGuideBookFileMngr ++;

	if(g_nGuideBookFileMngr == 1)
	{
		g_pGuideBookFileMngr = new CGuideBookFileMngr(bUseAts);
	}

	if (bYun)
	{
		g_pGuideBookFileMngr->SetYunFolder(bYun);
	}

	return g_pGuideBookFileMngr;
}

void CGuideBookFileMngr::Release()
{
	g_nGuideBookFileMngr --;

	if(g_nGuideBookFileMngr == 0)
	{
		delete g_pGuideBookFileMngr;
		g_pGuideBookFileMngr = NULL;
	}
}

void CGuideBookFileMngr::InitGuideBookFileMngr(const CString &strGbFileType, BOOL bYun)
{
	ASSERT (g_pGuideBookFileMngr != NULL);

	g_pGuideBookFileMngr->OpenXMLFile(strGbFileType, _T(""), bYun);
}

CGuideBookFileMngr::CGuideBookFileMngr(BOOL bUseAts)
{
	m_strRootPath = GetGbDevTemplatePath(bUseAts);
	m_strID = m_strRootPath;		//CExBaseObject::GetPath();
	m_strID.TrimRight(_P_FOLDER_PATH_SEPARATOR_);

	m_strPath = m_strRootPath;
	m_strName = g_strGuideBookMngr;
}	

CGuideBookFileMngr::~CGuideBookFileMngr()
{

}

BOOL CGuideBookFileMngr::SaveXMLFile()
{
	return TRUE;
}

void CGuideBookFileMngr::AddGbFileType(const CString &strFileType)
{
	m_strName = Gb_GetGuideBookFileDes(strFileType);
	CXFileType *pXFileType = AddFileType(m_strName, strFileType, _T(""), _T(""));
	pXFileType->AddNewPostfix(m_strName, strFileType);
	pXFileType->AddNewPostfix(g_strGbDocFileFilter, g_strGbDocFileFilter);
}

BOOL CGuideBookFileMngr::OpenXMLFile(const CString &strFileType, BOOL bYun)
{
	SetYunFolder(bYun);
	m_strName = Gb_GetGuideBookFileDes(strFileType);

	DeleteAll();

#ifdef GB_USE_XFILEMNGRBASE
	CXFileTypes *pXFileTypes = GetXFileTypes();
	pXFileTypes->DeleteAll();
	AddGbFileType(strFileType);

	SetOnllySearchMainTypeFile(TRUE);
	InitByXFileTypes();
	SetLibraryPath(this->GetRootPath());
#else
	TraverseFolder(this,, strFileType/*,g_strGbFilePostfixDes*/);
#endif

	return TRUE;
}

BOOL CGuideBookFileMngr::OpenXMLFile(const CString &strFileType, const CString &strFileType2, BOOL bYun)
{
	SetYunFolder(bYun);
	m_strName = Gb_GetGuideBookFileDes(strFileType);

	DeleteAll();

#ifdef GB_USE_XFILEMNGRBASE
	CXFileTypes *pXFileTypes = GetXFileTypes();
	pXFileTypes->DeleteAll();
	AddGbFileType(strFileType);
	
	if (strFileType2.GetLength() > 0)
	{
		AddGbFileType(strFileType2);
	}	

	SetOnllySearchMainTypeFile(TRUE);
	InitByXFileTypes();
	SetLibraryPath(this->GetRootPath());
#else
	TraverseFolder(this,, strFileType/*,g_strGbFilePostfixDes*/);
#endif

	return TRUE;
}
