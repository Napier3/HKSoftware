#include "stdafx.h"
#include "PpTemplateFileMngr.h"
#include "PpTemplateFolder.h"
#include "..\..\..\Module\XFileMngrBase\DlgXFileMngr.h"
#include "..\..\..\Module\XLanguage\XLanguageResource.h"
#include "..\..\..\System\Module\XAtsSysSvrGlobalDef.h"

long CPpTemplateFileMngr::g_nPpTemplateFileMngr = 0;
CPpTemplateFileMngr* CPpTemplateFileMngr::g_pPpTemplateFileMngr = NULL;

CPpTemplateFileMngr::CPpTemplateFileMngr(const CString &strPath, BOOL bYun)
{

	SetYunFolder(bYun);
	InitFileMngr(strPath);
}

void CPpTemplateFileMngr::InitFileMngr(const CString &strPath)
{
	if (strPath.GetLength() == 0)
	{
		//参见GuideBookDev的CGbDevItemFileMngr类
		m_strRootPath = (CString)_P_GetSystemPath() + g_strTemplateFolder;
	}
	else
	{
		m_strRootPath = strPath + g_strTemplateFolder;
	}

	m_strID = m_strRootPath;
	CString strTemp;
	strTemp = _P_FOLDER_PATH_SEPARATOR_;
	m_strID.TrimRight(strTemp);
	
	m_strPath = m_strRootPath;
#ifdef NOT_USE_XLANGUAGE
	m_strName = _T("规约模板文件");
#else
	m_strName = g_sLangTxt_PrtcTempFileMagn/*_T("规约模板文件管理")*/;
#endif
	
	DeleteAll();
	SearchFiles(g_strPpFileFilter, g_strPpFileFilter,this->GetRootPath());

	YunSearch();
}

CPpTemplateFileMngr::CPpTemplateFileMngr()
{
	
}

CPpTemplateFileMngr::~CPpTemplateFileMngr()
{

}

CPpTemplateFileMngr* CPpTemplateFileMngr::CreatePpTemplateFileMngr(BOOL bYun, const CString &strPath)
{
	g_nPpTemplateFileMngr ++;

	if(g_nPpTemplateFileMngr == 1)
	{
		g_pPpTemplateFileMngr = new CPpTemplateFileMngr(strPath, bYun);
	}
	
	return g_pPpTemplateFileMngr;
}

CPpTemplateFileMngr* CPpTemplateFileMngr::Create()
{
	g_nPpTemplateFileMngr ++;

	if(g_nPpTemplateFileMngr == 1)
	{
		g_pPpTemplateFileMngr = new CPpTemplateFileMngr();
	}

	return g_pPpTemplateFileMngr;
}

void CPpTemplateFileMngr::Release()
{
	g_nPpTemplateFileMngr --;

	if(g_nPpTemplateFileMngr == 0)
	{
		delete g_pPpTemplateFileMngr;
		g_pPpTemplateFileMngr = NULL;
	}
}

CString pp_GetProtocolPath()
{
	return atssys_GetProtocolPath();
}

CString pp_GetProtocolTemplatePath()
{
	return atssys_GetProtocolTemplatePath();
}

void CPpTemplateFileMngr::InitPpTemplateFileMngr()
{
	g_pPpTemplateFileMngr->InitFileMngr(pp_GetProtocolPath());
}

// 
// long CPpTemplateFileMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 	return 0;
// }
// 
// long CPpTemplateFileMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
// {
// 	return 0;
// }
// 
// CExBaseObject* CPpTemplateFileMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	ASSERT(CFileMngrXMLKeys::g_pFileMngrXMLKeys != NULL);
// 
// 	if(strClassID == CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFolderKey)
// 	{
// 		CPpTemplateFolder* pFolder = new CPpTemplateFolder();
// 		return pFolder;
// 	}
// 	else if(strClassID == CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFileKey)
// 	{
// 		CPpTemplateFile* pFile = new CPpTemplateFile();
// 		return pFile;
// 	}
// 
// 	return NULL;
// }

BOOL pp_GetPpTemplateFile(CWnd *pParent, CString &strPpFile, BOOL bHasFullPath)
{
	CString strPath = pp_GetProtocolPath();

	CPpTemplateFileMngr::InitPpTemplateFileMngr();

	CPpTemplateFileMngr *pFileMngr = CPpTemplateFileMngr::g_pPpTemplateFileMngr;

	CDlgXFileMngr dlg(0, _T("ppxml"),g_sLangTxt_PrtcTempFile/*_T("规约模板文件")*/, pFileMngr,OPEN_FILE_MODE, pParent);

	if(dlg.DoModal() != IDOK)
	{
		return FALSE;
	}

	strPpFile = dlg.GetFileName();

	if (!bHasFullPath)
	{
		strPath.AppendFormat(_T("%s\\"), g_strTemplateFolder);
		strPpFile = strPpFile.Mid(strPath.GetLength());
	}

	return TRUE;
}

