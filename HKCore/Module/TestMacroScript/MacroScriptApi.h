#pragma once


#include "TestMacroScriptMngr.h"

CShortData* TMS_FindData(CTestMacro *pMacro, const CString &strID);
BOOL TMS_CanAddScptData(CTestMacroScript *pScript, CExBaseObject *pData);

CTmScptData* TMS_AddScptData(CTestMacroScript *pScript, CExBaseObject *pData);
CTmScptCmd* TMS_AddScptCmd(CTmScptData *pScptData, CExBaseObject *pData, const CString &strAttrID);
CTmScptCmd* TMS_AddScptCmd(CTmScptValue *pScptValue, CExBaseObject *pData, const CString &strAttrID);

BOOL TMS_DeleteScptCmd(CTmScptValue *pScptValue, CTmScptCmd *pScptCmd);
BOOL TMS_DeleteScptCmd(CTmScptData *pScptData, CTmScptCmd *pScptCmd);

BOOL TMS_DeleteScptCmd(CTmScptValue *pScptValue, const CString &strDataID, const CString &strAttrID);
BOOL TMS_DeleteScptCmd(CTmScptData *pScptData, const CString &strDataID, const CString &strAttrID);

BOOL TMS_Import(CTestMacroScript *pScript, CExBaseList *pList);

void TMS_InsertChildrenToListBox(CTestMacroScript *pScript, CListBox *pListBox, CTestMacro *pMacro);
long TMS_InsertToListBox(CTmScptData *pScptData, CListBox *pListBox, CTestMacro *pMacro);