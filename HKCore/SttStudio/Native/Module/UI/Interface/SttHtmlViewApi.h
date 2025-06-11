#pragma once

#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../Config/MacroTestUI/SttMacroTestUI_TestMacroUIs.h"

CString stt_ui_GetHtmlFile(const CString &strHtmlFileName);
char* stt_ui_OpenHtmlFile_GetChar(const CString &strHtmlFileName);//zhouhj 2023.9.26 修改函数名,改函数的返回值需要单独delete,与其它同名函数作区分
bool stt_ui_OpenHtmlFile(const CString &strHtmlFileName, CString &strCurrRptFileData);
bool stt_ui_OpenHtmlHeadFile(const CString &strHtmlFileName, CString &strCurrRptFileData);//20240510 suyang 增加对获取到报告头

CString stt_ui_GetParasFile(const CString &strFileName);
CString stt_ui_GetParasAiFile(const CString &strFileName);  //2023-2-7  lijunqing
BOOL stt_ui_OpenParasFile(const CString &strFileName, CDataGroup *pParas);
BOOL stt_ui_SaveParasFile(const CString &strFileName, CDataGroup *pParas, long nXmlRWType = _PUGI_XML_TYPE_);

CString stt_ui_GetTestTemplateFile(const CString &strMacroUI);

CString stt_ui_GetDebugFile(const CString &strFileName);
BOOL stt_ui_OpenDebugFile(const CString &strFileName, char **ppszText);
BOOL stt_ui_OpenDebugFile(const CString &strFileName, CString &strText);
