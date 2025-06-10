#include "stdafx.h"
#include "SttQueryAtsFileTool.h"

#include "../../../Module/XfileMngrBase/XFileFindEx.h"
#include "../../../Protocol/Module/Engine/PpGlobalDefine.h"
#include "../../../AutoTest/Module/TCtrlCntrDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttQueryAtsFileTool::CSttQueryAtsFileTool()
{
	
}

CSttQueryAtsFileTool::~CSttQueryAtsFileTool()
{

}

void CSttQueryAtsFileTool::QueryAtsFile(CSttAtsCmd &oAtsCmd, CSttSysState &oSysState)
{
    CString strLibPath, strTemplatePath, strWorkspacePath;
    strTemplatePath = _P_GetTemplatePath();
    strLibPath = _P_GetLibraryPath();
    strWorkspacePath = _P_GetWorkspacePath();
    CString strNotHas, strEmpty;
    strNotHas = _T("_CmmCfg");

    CSttParas *pSttParas = oAtsCmd.GetSttParas();
    CSttParas *pRetParas = oSysState.GetSttParas();

    QueryFiles(strTemplatePath, XPARA_ID_GBXMLFILE, g_strGbTemplateExeFileFilter, pSttParas, pRetParas, strEmpty);
    QueryFiles(strTemplatePath, XPARA_ID_PPXMLFILE, g_strPpFileFilter, pSttParas, pRetParas, strEmpty);
    QueryFiles(strWorkspacePath, XPARA_ID_GBRPTFILE, g_strGuideBookBinaryPostfix, pSttParas, pRetParas, strEmpty);
    QueryFiles(strLibPath, XPARA_ID_DVMFILE, "xml", pSttParas, pRetParas, strNotHas);
}

void CSttQueryAtsFileTool::QueryFiles(const CString &strPath, const CString &strFilesID, const CString &strFilter, CSttParas *pSttParas, CSttParas *pRetParas, const CString &strNotHas)
{
    long nQuery = 0;
    pSttParas->GetDataValue(strFilesID, nQuery);

    if (nQuery == 0)
    {
        return;
    }

    //2022-3-23 lijunqing
    pRetParas->SearchFiles(strPath, 1, 1, strFilter);
/*
    CXFileFindEx oFind;
    CString strTemp = strFilter;

    if (strTemp.GetAt(1) != '.')
    {
        strTemp.Format(_T("*.%s"), strFilter.GetString());
    }

    oFind.AddFileFilter(strTemp);
    oFind.FindFile(strPath);
    CDataGroup *pGroup = pRetParas->AddNewGroup(strFilesID, strFilesID, "");
    CString strFile;

    while (oFind.FindNextFile())
    {
        strFile = oFind.GetFileName();

        if (strNotHas.GetLength() > 0)
        {//不能包含的文本
            if (strFile.Find(strNotHas) >= 0)
            {
                continue;
            }
        }
        pGroup->AddNewData(strFile, strFile, _T("string"), strFile);
    }
    */
}
