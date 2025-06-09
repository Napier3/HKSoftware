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

CString CSttFileMngrTool::GetFolderPath(const CString &strTypeId)
{
	CString strPath;
	POS pos = m_oFileMngr.GetHeadPosition();
	CDvmData *oDvmData = NULL;
	while(pos)
	{
		oDvmData = (CDvmData *)m_oFileMngr.GetNext(pos);	

		if (strTypeId == oDvmData->m_strID)
		{
			IsFolderPath(oDvmData->m_strDefaultValue,strPath);
			break;
		}

	}


	return strPath;

}

BOOL CSttFileMngrTool::IsFolderPath(const CString &strPath,CString &strFilePath)
{
	CString strRootPath,strSystemPath,strCurrFilePath;

// 	if (!_P_GetFullPathEx(strPath,strRootPath))
// 	{
// 		if (strPath == "Workspace_PATH")
// 		{
// 			strRootPath = _P_GetWorkspacePath();
// 		}
// 	}

	strSystemPath = _P_GetSystemPath();
	strCurrFilePath = strSystemPath + strPath;

	if (IsFileExist(strCurrFilePath))
	{
		strRootPath = strCurrFilePath;
	}

	if (!IsFileExist(strRootPath))
	{
		CreateAllDirectories(strCurrFilePath);
		strRootPath = strCurrFilePath;
	}
	strFilePath = strRootPath;

	return FALSE;

}