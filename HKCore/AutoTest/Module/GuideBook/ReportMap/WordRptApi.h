#pragma once

#include "../../../../Module/Office/mso9.h"
#include "../../../../Module/Office/msword9.h"
#include "../../../../Module/CriticalSection/SynCriticalSection.h"

extern DWORD *g_pdwMaxBkmkIndex;


void wordrpt_RenameRptBkmks(CExBaseList *pList, MSWord::_Application &oWordApp, MSWord::_Document &oDoc);
void wordrpt_InsertWordEdit(MSWord::_Application	&oWordApp, MSWord::_Document &oDocDest, MSWord::_Document &oDocSrc
							, const CString &strDestRptFile, const CString &strSrcRptFile, long nAddRptGroupTitle);
void wordrpt_InsertTitle(MSWord::_Application &oWordApp, MSWord::_Document &oDoc, const CString &strDocFile, const CString &strTitle, long nTitleLevel, BOOL bPasteFormat=NULL);
BOOL  wordrpt_ActiveWindow(MSWord::_Application	&oWordApp, const CString &strTitle);
CString wordrpt_GetWordFileTitle(const CString &strRptFile);
// void wordrpt_InsertWordEdit(MSWord::_Application &oWordApp, MSWord::_Document &oDocDest, MSWord::_Document &oDocSrc
// 							, const CString &strDestRptFile, const CString &strSrcRptFile, long nAddRptGroupTitle);
BOOL wordrpt_Open(MSWord::_Application &oWordApp, MSWord::_Document &oDoc, const CString  &strReportFile);
