#include "stdafx.h"
#include "PpTemplateFolder.h"

CPpTemplateFolder::CPpTemplateFolder()
{

}

CPpTemplateFolder::~CPpTemplateFolder()
{

}
// 
// CExBaseObject* CPpTemplateFolder::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
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