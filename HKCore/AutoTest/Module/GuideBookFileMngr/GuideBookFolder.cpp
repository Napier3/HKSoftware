#include "stdafx.h"
#include "GuideBookFolder.h"

CGuideBookFolder::CGuideBookFolder()
{

}

CGuideBookFolder::~CGuideBookFolder()
{

}
// 
// CExBaseObject* CGuideBookFolder::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	if(strClassID == CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFolderKey)
// 	{
// 		CGuideBookFolder* pFolder = new CGuideBookFolder();
// 		return pFolder;
// 	}
// 	else if(strClassID == CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFileKey)
// 	{
// 		CGuideBookFile* pFile = new CGuideBookFile();
// 		return pFile;
// 	}
// 
// 	return NULL;
// }
// 
// CExBaseObject* CGuideBookFolder::CreateNewChild(long nClassID)
// {
// 	if(nClassID == GB_DEV_GUIDEBOOK_FOLDER)
// 	{
// 		CGuideBookFolder* pFolder = new CGuideBookFolder();
// 		return pFolder;
// 	}
// 	else if(nClassID == GB_DEV_GUIDEBOOK_FILE)
// 	{
// 		CGuideBookFile* pFile = new CGuideBookFile();
// 		return pFile;
// 	}
// 
// 	return NULL;
// }