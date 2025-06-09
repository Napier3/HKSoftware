#include "SttFileMngrTool.h"
#include "../../../../../Module/DataMngr/DvmData.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../Module/API/FileApi.h"
#include "../../../../../Module/DataMngr/DataMngrGlobal.h"


CSttFileMngrTool g_oFileMngrTool;

CSttFileMngrTool::CSttFileMngrTool()
{
	

}

CSttFileMngrTool::~CSttFileMngrTool()
{
	
}

BOOL CSttFileMngrTool::OpenConfigFile(CString strFilePath)
{
	if (strFilePath.IsEmpty())
	{
		strFilePath = _P_GetConfigPath();
		strFilePath += _T("SttFileTypeMngr.xml");
	}

	m_oFileMngr.DeleteAll();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oFileMngr.OpenXmlFile(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	return FALSE;

}

CString CSttFileMngrTool::GetFolderPath_STD(const CString &strTypeId)
{
	CExBaseObject *pCurrObj = m_oFileMngr.FindByID(strTypeId);

	if (pCurrObj == NULL)
	{
		return _T("");
	}

	if (pCurrObj->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return _T("");
	}

	CDvmData *pDvmData = (CDvmData*)pCurrObj;
	CString strPath;
	strPath = _P_GetSystemPath();
	strPath += pDvmData->m_strDefaultValue;
	CreateAllDirectories(strPath);
	return strPath;
}

// BOOL CSttFileMngrTool::IsFolderPath(const CString &strPath,CString &strFilePath)
// {
// 	CString strRootPath,strSystemPath,strCurrFilePath;
// 
// 	strSystemPath = _P_GetSystemPath();
// 	strCurrFilePath = strSystemPath + strPath;
// 
// 	if (IsFileExist(strCurrFilePath))
// 	{
// 		strRootPath = strCurrFilePath;
// 	}
// 
// 	if (!IsFileExist(strRootPath))
// 	{
// 		CreateAllDirectories(strCurrFilePath);
// 		strRootPath = strCurrFilePath;
// 	}
// 	strFilePath = strRootPath;
// 
// 	return FALSE;
//}