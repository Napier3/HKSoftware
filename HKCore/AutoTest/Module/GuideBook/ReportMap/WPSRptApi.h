#pragma once

#include "../../../../Module/Office/KSO.h"
#include "../../../../Module/Office/WPS.h"
#include "../../../../Module/CriticalSection/SynCriticalSection.h"

extern DWORD *g_pdwMaxBkmkIndex;

void wpsrpt_RenameRptBkmks(CExBaseList *pList, WPS::_Application &oWPSApp, WPS::_Document &oDoc);
void wpsrpt_InsertWPSEdit(WPS::_Application	&oWPSApp, WPS::_Document &oDocDest, WPS::_Document &oDocSrc
							, const CString &strDestRptFile, const CString &strSrcRptFile, long nAddRptGroupTitle);
void wpsrpt_InsertTitle(WPS::_Application &oWPSApp, WPS::_Document &oDoc, const CString &strDocFile, const CString &strTitle, long nTitleLevel);
BOOL  wpsrpt_ActiveWindow(WPS::_Application	&oWPSApp, const CString &strTitle);
CString wpsrpt_GetWPSFileTitle(const CString &strRptFile);

BOOL wpsrpt_Open(WPS::_Application &oWPSApp, WPS::_Document &oDoc, const CString  &strReportFile);
