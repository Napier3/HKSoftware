#include "stdafx.h"
#include "GbDevItemFolder.h"
#include "GbDevItemFile.h"
#include "GbDevItemFileMngr.h"

CGbDevItemFolder::CGbDevItemFolder()
{
	m_strName = _T("GbDevItemFolder");
	m_strPath = _T("");
}

CGbDevItemFolder::~CGbDevItemFolder()
{

}
// 
// CExBaseObject* CGbDevItemFolder::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	if(strClassID == CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFolderKey)
// 	{
// 		CGbDevItemFolder* pFolder = new CGbDevItemFolder();
// 		return pFolder;
// 	}
// 	else if(strClassID == CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFileKey)
// 	{
// 		CGbDevItemFile* pFile = new CGbDevItemFile();
// 		return pFile;
// 	}
// 
// 	return NULL;
// }
// 
// CExBaseObject* CGbDevItemFolder::CreateNewChild(long nClassID)
// {
// 	if(nClassID == GB_DEV_ITEM_FOLDER)
// 	{
// 		CGbDevItemFolder* pFolder = new CGbDevItemFolder();
// 		return pFolder;
// 	}
// 	else if(nClassID == GB_DEV_ITEM_FILE)
// 	{
// 		CGbDevItemFile* pFile = new CGbDevItemFile();
// 		return pFile;
// 	}
// 	return NULL;
// }