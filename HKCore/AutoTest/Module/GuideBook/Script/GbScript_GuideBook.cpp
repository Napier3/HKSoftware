#include "stdafx.h"
#include "GbScript_GuideBook.h"
#include "../GbItemBase.h"
#include "../Device.h"
#include "../GuideBook.h"
#include "../MacroTest.h"

#include "../../../../Module/GpsPcTime/GpsPcTime.h"
#include "../../../../Module/MemBuffer/EquationBuffer.h"

#ifndef GUIDEBOOK_DEV_MODE
#include "../../TestControl/TestControlBase.h"
#endif

#include "../../XLanguageResourceAts.h"

#include "../../../../Module/DataMngr/DatasetValid/DsvChoice.h"
#include "../../../../Module/API/MathApi.h"
#include "../../TCtrlCntrConfig.h"

#ifndef _PSX_QT_LINUX_
#include "../../FactoryBatchTestMngr.h"
#endif

#include "../../../../Module/Record/Draw/DrawGlobalDef.h"

#ifndef GUIDEBOOK_DEV_MODE
#include "../../TestControl/SmartTestBaseApp.h"
#endif
#include "../../../../Module/System/TickCount32.h"

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif

extern char g_pLuaReturnString[MAX_PATH];

extern long g_nLog_TestControl_Msg;

#ifndef GUIDEBOOK_DEV_MODE
CTestControlBase* GBS_GetTestControl2(CTScriptSingleVM *pXvm)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	return pTestControl;
#else
	return NULL;
#endif

}
#endif


CDataObj* GBS_GetDsDataObj(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();

	if (pTestControl->GetParent() == NULL)
	{
		return pTestControl->GBS_GetDsDataObj(pItem, nDeviceIndex, pszID);
	}
	else
	{
        CTestControlBase *pMany = (CTestControlBase*)pTestControl->GetParent();
		return pMany->GBS_GetDsDataObj(pItem, nDeviceIndex, pszID);
	}
#else
	CDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return NULL;
	}

	CString strID ;
	strID = pszID;

	CDataObj *pData = pDevice->FindDataObjByID(strID, nDeviceIndex);
	return pData;
#endif

	// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	// 	//CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectDataObj(CString(pszID));
	// 	CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->FindDataObjByID(CString(pszID), nDeviceIndex);
	// 	double dValue = 1;
	// 
	// 	if (pData != NULL)
	// 	{
	// 		dValue = _wtof(pData->m_strValue);
	// 	}
	// 	else
	// 	{
	// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"dsData id(%s) not exist", (CString)pszID);
	// // 
	// // 		CString strErrorInfo;
	// // 		CString strID(pszID);
	// // 		strErrorInfo.Format( L"Set id(%s) not exist", strID);
	// // 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
	// // 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	// 	}
	// 
	// 	return dValue;
}

CReport* GBS_GetItemReport(CTScriptSingleVM *pXvm)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CReport *pReport = pItem->GetCurrReport();

	if (pReport == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,  g_sLangTxt_NoDataReport.GetString() /*L"没有报告数据"*/);
		return NULL;
	}

	return pReport;
}

CDvmDataset* GBS_GetItemReportDataEx(CTScriptSingleVM *pXvm)
{
	CReport *pReport = GBS_GetItemReport(pXvm);

	if (pReport == NULL)
	{
		return NULL;
	}

	if (pReport->m_pRptDvmDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,  g_sLangTxt_NoDataReport.GetString() /*L"没有报告数据"*/);
		return NULL;
	}

	return pReport->m_pRptDvmDataset;
}

CValues* GBS_GetItemReportValues(CTScriptSingleVM *pXvm)
{
	CReport *pReport = GBS_GetItemReport(pXvm);

	if (pReport == NULL)
	{
		return NULL;
	}

	if (pReport->m_pValues == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,  g_sLangTxt_NoDataReport.GetString() /*L"没有报告数据"*/);
		return NULL;
	}

	return pReport->m_pValues;
}

CGbItemBase* GBS_SelectGbItem(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);

	CGbItemBase *pSelectGbItem = NULL;
	CGbItemBaseList oListDest;
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	long nCount = oListDest.GetCount();
	double dValue = 0;

	if (nCount > 1 || nCount == 0)
	{
		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format( _T("Path(%s) select %d items"), strPath.GetString(), nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
	}
	else
	{
		pSelectGbItem = (CGbItemBase*)oListDest.GetHead();
	}

	oListDest.RemoveAll();

	return pSelectGbItem;
}

// 跳转到制定的项目开始执行测试
// pszItemPath为Item的路径
void GBS_GotoItem(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);

// 	CGbItemBaseList oListDest;
// 	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
// 	POS pos = oListDest.GetHeadPosition();
// 	long nCount = oListDest.GetCount();
// 	double dValue = 0;
// 
// 	if (nCount > 1 || nCount == 0)
// 	{
// 		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"Path(%s) select %d items, gotoItem failed", (CString)pszItemPath, nCount);
// 
// 		CString strErrorInfo;
// 		CString strPath(pszItemPath);
// 		strErrorInfo.Format( _T("Path(%s) select %d items"), strPath, nCount);
// 		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		//lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		//throw luabind::error(g_pGuideBookLua);		//抛出异常信息
// 	}
// 	else
// 	{
// #ifndef GUIDEBOOK_DEV_MODE
// 		CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
// 		ASSERT (pItem != NULL);
// 
// 		CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
// 		ASSERT (pGuideBook != NULL);
// 
// 		CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
// 		CGbItemBase *pGotoItem = (CGbItemBase*)oListDest.GetHead();
// 		pTestControl->GotoItem(pGotoItem);
// #endif
// 	}
// 
// 	oListDest.RemoveAll();

	CGbItemBase *pGotoItem = GBS_SelectGbItem(pXvm, pszItemPath);

	if (pGotoItem != NULL)
	{
#ifndef GUIDEBOOK_DEV_MODE
// 		CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
// 		ASSERT (pItem != NULL);
// 
// 		CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
// 		ASSERT (pGuideBook != NULL);
// 
// 		CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
        CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);

		if (pTestControl != NULL)
		{
			pTestControl->GotoItem(pGotoItem);
		}
#endif
	}
}

void GBS_GotoItemEx(CTScriptSingleVM *pXvm, const char* pszItemPath, long nRslt, long nAndOr)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBase *pGotoItem = GBS_SelectGbItem(pXvm, pszItemPath);

	if (pGotoItem != NULL)
	{
#ifndef GUIDEBOOK_DEV_MODE
        CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);
		CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

		if (pTestControl != NULL)
		{
			pTestControl->GBS_GotoItemEx(pItem, pGotoItem, pszItemPath, nRslt, nAndOr);
		}
#endif
	}
}

void GBS_FireTestNextMsg(CTScriptSingleVM *pXvm)
{
}

void GBS_BreakLoop(CTScriptSingleVM *pXvm, long nLevel)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	
	if (nLevel == 0)
	{
		pItem->m_nBreakLoopState = 1;
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		return;
	}

	CGbItemBase *pItemParent = (CGbItemBase*)pItem->GetParent();
	UINT nClassID = pItemParent->GetClassID();
	
	//父项目，MacroTest、Safety、SysParaEdit
	if ((nClassID == GBCLASSID_MACROTEST) || (nClassID == GBCLASSID_SAFETY) || (nClassID == GBCLASSID_SYSPARAEDIT))
	{
		pItem->m_nBreakLoopState = 1;
		pItemParent->m_nBreakLoopState = 1;
	}
}


void GBS_MtExcuteCmd(CTScriptSingleVM *pXvm, const char *pszCmd, const char *pCmdPara)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	pTestControl->GBS_MtExcuteCmd(pszCmd, pCmdPara);
#endif
}

void GBS_MtRegistPpDataMsg(CTScriptSingleVM *pXvm, const char *pszDvmDataPath)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	pTestControl->GBS_MtRegistPpDataMsg(pszDvmDataPath);
#endif
}

void GBS_MtUnRegistPpDataMsg(CTScriptSingleVM *pXvm, const char *pszDvmDataPath)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	pTestControl->GBS_MtUnRegistPpDataMsg(pszDvmDataPath);
#endif
}


void GBS_MtRegistCmdMsg(CTScriptSingleVM *pXvm, const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	pTestControl->GBS_MtRegistCmdMsg(pszCmdID, nCmdState, nCmdWParam, nCmdLParam);
#endif
}

void GBS_MtUnRegistCmdMsg(CTScriptSingleVM *pXvm, const char *pszCmdID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	pTestControl->GBS_MtUnRegistCmdMsg(pszCmdID);
#endif
}


void GBS_MtRegistPpDataMsgRange(CTScriptSingleVM *pXvm, const char *pszDvmDataPath, double dMin, double dMax)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	pTestControl->GBS_MtRegistPpDataMsgRange(pszDvmDataPath, dMin, dMax);
#endif
}


void GBS_BreakItems(CTScriptSingleVM *pXvm, long nLevel)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();

	if (nLevel < 0)
	{
		nLevel = 0;
	}

	pTestControl->m_nBreakItemsLevel = nLevel;
#endif
}

void GBS_SetUploadRptFile(CTScriptSingleVM *pXvm, const char *pszFileName)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	pGuideBook->m_strAotuSaveReportFileName = pszFileName;

#ifdef GUIDEBOOK_DEV_MODE
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("设置保存文件的名称："), CString(pszFileName));
#endif
}

//数据集访问
double GBS_GetDsDataValue(CTScriptSingleVM *pXvm, const char* pszID)
{
	return GBS_GetDsDataValueEx(pXvm, -1, pszID);
// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
// 	//CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectDataObj(CString(pszID));
// 	CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->FindDataObjByID(CString(pszID), -1);
// 	double dValue = 1;
// 
// 	if (pData != NULL)
// 	{
// 		dValue = _wtof(pData->m_strValue);
// 	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"dsData id(%s) not exist", (CString)pszID);
// // 
// // 		CString strErrorInfo;
// // 		CString strID(pszID);
// // 		strErrorInfo.Format( L"Set id(%s) not exist", strID);
// // 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// // 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
// 	}
// 
// 	return dValue;
}

double GBS_GetDsDataAttr(CTScriptSingleVM *pXvm, const char* pszID, const char *pszAttrID)
{
	CString strAttrID, strValue;
	strAttrID = pszAttrID;

	CDataObj *pDataObj = GBS_GetDsDataObj(pXvm, -1, pszID);

	if (pDataObj != NULL)
	{
		pDataObj->GetValueByID(strAttrID, strValue);
#ifdef _UNICODE
		return _wtof(strValue);
#else
        return atof(strValue.GetString());
#endif
	}
	else
	{
		return 0;
	}
}

const char* GBS_GetDsDataAttrStr(CTScriptSingleVM *pXvm, const char* pszID, const char *pszAttrID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	CString strAttrID, strValue;
	strAttrID = pszAttrID;

	CDataObj *pDataObj = GBS_GetDsDataObj(pXvm, -1, pszID);

	if (pDataObj != NULL)
	{
		pDataObj->GetValueByID(strAttrID, strValue);
		CString_to_char(strValue, g_pLuaReturnString);
	}
	else
	{
		g_pLuaReturnString[0] = 0;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "dsData id(%s) not exist", pszID);
	}

	return g_pLuaReturnString;
}

void GBS_SetDsDataValue(CTScriptSingleVM *pXvm, const char* pszID, double dVal)
{
	GBS_SetDsDataValueEx(pXvm, -1, pszID, dVal);
// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
// 	//CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectDataObj(CString(pszID));
// 	CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->FindDataObjByID(CString(pszID), -1);
// 
// 	if (pData != NULL)
// 	{
// 		pData->m_strValue.Format(_T("%f"), dVal);
// 	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"dsData id(%s) not exist", (CString)pszID);
// 
// // 		CString strErrorInfo;
// // 		CString strID(pszID);
// // 		strErrorInfo.Format( L"Set id(%s) not exist", strID);
// // 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// // 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
// 	}
}
const char* GBS_GetDsDataValueStr(CTScriptSingleVM *pXvm, const char* pszID)
{
	return GBS_GetDsDataValueStrEx(pXvm, -1, pszID);
// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
// 	//CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectDataObj(CString(pszID));
// 	CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->FindDataObjByID(CString(pszID), -1);
// 
// 	if (pData != NULL)
// 	{
// 		CString_to_char(pData->m_strValue, g_pLuaReturnString);
// 	}
// 	else
// 	{
// 		g_pLuaReturnString[0] = 0;
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"dsData id(%s) not exist", (CString)pszID);
// 	}
// 
// 	return g_pLuaReturnString;
}
void GBS_SetDsDataValueStr(CTScriptSingleVM *pXvm, const char* pszID, const char* pszVal)
{
	GBS_SetDsDataValueStrEx(pXvm, -1, pszID, pszVal);
// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
// 	//CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectDataObj(CString(pszID));
// 	CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->FindDataObjByID(CString(pszID), -1);
// 
// 	if (pData != NULL)
// 	{
// 		pData->m_strValue = pszVal;
// 	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"dsData id(%s) not exist", (CString)pszID);
// 	}
}

//数据集访问
double GBS_GetDsDataValueEx(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();

	if (pTestControl->GetParent() == NULL)
	{
		return pTestControl->GBS_GetDsDataValueEx(pItem, nDeviceIndex, pszID);
	}
	else
	{
        CTestControlBase *pMany = (CTestControlBase*)pTestControl->GetParent();
		return pMany->GBS_GetDsDataValueEx(pItem, nDeviceIndex, pszID);
	}
#else
	CDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return 0;
	}

	CString strID ;
	strID = pszID;

	CDataObj *pData = pDevice->FindDataObjByID(strID, nDeviceIndex);
	double dValue = 1;

	if (pData != NULL)
	{
		if (pData->GetClassID() == GBCLASSID_DATAOBJ)
		{
#ifdef _UNICODE
			dValue = _wtof(pData->m_strValue);
#else
			dValue = atof(pData->m_strValue);
#endif
		}
		else if (pData->GetClassID() == GBCLASSID_DATAOBJ_VALUE)
		{
			CDataObjValue *pValue = (CDataObjValue *)pData;

#ifdef _UNICODE
			dValue = _wtof(pValue->m_strValue);
#else
			dValue = atof(pValue->m_strValue);
#endif
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("dsData id(%s) not exist"), (CString)pszID);
	}

	return dValue;
#endif

// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
// 	//CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectDataObj(CString(pszID));
// 	CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->FindDataObjByID(CString(pszID), nDeviceIndex);
// 	double dValue = 1;
// 
// 	if (pData != NULL)
// 	{
// 		dValue = _wtof(pData->m_strValue);
// 	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"dsData id(%s) not exist", (CString)pszID);
// // 
// // 		CString strErrorInfo;
// // 		CString strID(pszID);
// // 		strErrorInfo.Format( L"Set id(%s) not exist", strID);
// // 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// // 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
// 	}
// 
// 	return dValue;
}

void GBS_SetDsDataValueEx(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszID, double dVal)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	//CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectDataObj(CString(pszID));
	CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->FindDataObjByID(CString(pszID), nDeviceIndex);

	if (pData != NULL)
	{
		pData->m_strValue.Format(_T("%f"), dVal);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "dsData id(%s) not exist", pszID);

// 		CString strErrorInfo;
// 		CString strID(pszID);
// 		strErrorInfo.Format( L"Set id(%s) not exist", strID);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
}
const char* GBS_GetDsDataValueStrEx(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	//CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectDataObj(CString(pszID));
	CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->FindDataObjByID(CString(pszID), nDeviceIndex);

	if (pData != NULL)
	{
		CString_to_char(pData->m_strValue, g_pLuaReturnString);
	}
	else
	{
		g_pLuaReturnString[0] = 0;
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "dsData id(%s) not exist", pszID);
	}

	return g_pLuaReturnString;
}
void GBS_SetDsDataValueStrEx(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszID, const char* pszVal)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	//CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectDataObj(CString(pszID));
	CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->FindDataObjByID(CString(pszID),nDeviceIndex);

	if (pData != NULL)
	{
		pData->m_strValue = pszVal;
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "dsData id(%s) not exist", pszID);
	}
}


long GBS_CalAinError(CTScriptSingleVM *pXvm, double dAbsCal, double dRelCal, double dAbsErr, double dRelErr)
{
// 	BOOL bAbsRsltJdg = TRUE;
// 	BOOL bRelRsltJdg = TRUE;
// 	long nRsltJdg = 0;
// 
// 	if (dAbsErr > 0)
// 	{
// 		if (dAbsCal > dAbsErr)
// 		{
// 			bAbsRsltJdg = FALSE;
// 		}
// 
// 	}
// 
// 	if (dRelErr > 0)
// 	{
// 		if (dRelCal > dRelErr)
// 		{
// 			bRelRsltJdg = FALSE;
// 		}
// 	}
// 
// 	if (bAbsRsltJdg && bRelRsltJdg)
// 	{
// 		nRsltJdg = 1;
// 	}
// 	else
// 	{
// 		nRsltJdg = 0;
// 	}

	return math_CalIsInError(dAbsCal, dRelCal, dAbsErr, dRelErr);;
}


long GBS_CalAinError(CTScriptSingleVM *pXvm, double dAbsCal, double dRelCal, double dAbsErr, double dRelErr, CValue *pDataRst)
{
	long nRsltJdg = GBS_CalAinError(pXvm, dAbsCal, dRelCal, dAbsErr, dRelErr);

	if (nRsltJdg == 1)
	{
		if (pDataRst != NULL)
		{
			pDataRst->m_strValue = /*g_strResultDescValueCorrect*/g_sLangTxt_Qualified;
		}
	}
	else
	{
		if (pDataRst != NULL)
		{
			pDataRst->m_strValue = /*g_strResultDescValueIncorrect*/	g_sLangTxt_Unqualified;
		}
	}

	return nRsltJdg;
}

void GBS_CalAinError(CTScriptSingleVM *pXvm, double dValue, double dRefValue, double &dAbsCal, double &dRelCal, BOOL bIsAngle)
{
// 	dAbsCal = dValue - dRefValue;
// 
// 	if (bIsAngle)
// 	{
// 		dAbsCal = dAbsCal - ( ((long)(dAbsCal / 360))*360);
// 	}
// 
// 	dRelCal = fabs(dAbsCal);
// 
// 	if (!bIsAngle)
// 	{
// 		if (dRefValue > 0.0001)
// 		{
// 			dRelCal /= dRefValue;
// 		}
// 	}
	math_CalError(dValue, dRefValue, dAbsCal, dRelCal, bIsAngle);
}

CReport* GBS_GetReport(CTScriptSingleVM *pXvm, CGbItemBase *pItem, long nIndex)
{
#ifdef GUIDEBOOK_DEV_MODE
	return pItem->GetReport(nIndex);
#else

	CGbItemBase *pCurrItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
    CTestControlBase *pTestControl = (CTestControlBase*)pItem->GetAncestor(GBCLASSID_TESTCONTROL);

	if (pItem == pCurrItem)
	{
		return pTestControl->GetReport(pItem, nIndex);
	}
	else
	{
        if (!g_theSmartTestBaseApp->IsSaveRptToDB())
		{
			return pTestControl->GetReport(pItem, nIndex);
		}
		else
		{
			CGuideBook *pGuideBook = (CGuideBook*)pCurrItem->GetAncestor(GBCLASSID_GUIDEBOOK);
            CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
			return pTestControl->GBS_GetReport(pItem, nIndex);
		}
	}

#endif
}

void GBS_AddDataErrorToRpt_Rslt_Ex(CTScriptSingleVM *pXvm, CValues *pValues, const CString &strValueID, long nRslt)
{
	if (g_bAddDataErrorValueToRpt)
	{
		Gb_AddDataErrorToRpt_Rslt(pValues, strValueID, nRslt);
	}
}

long GBS_CalAinError(CTScriptSingleVM *pXvm, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaError3.GetString() /*_T("CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	
	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_ErrFctnTest.GetString() /*L"CalAinErr函数只用用于测试量值测试项目"*/);
		return 1;
	}

	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd     *pCmd = pCommCmd->GetCmd();
	CString strID;
	strID = pszAinID;
	long nRsltJdg = 0;

#ifdef GUIDEBOOK_DEV_MODE
	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CExBaseObject *pSel = pDevice->FindDvmDataObj(strID);

	if (pSel == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CalAinErr函数数据【%s】不存在"), strID);
		return 0;		
	}

	return 1;
#else

	CReport *pReport = GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);
	CValues *pValues = pReport->GetValues();
	CValue *pData = (CValue *)pValues->FindByID(strID);

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ErrFctnUnExist.GetString() /*L"CalAinErr函数数据【%s】不存在"*/, strID.GetString());
		return 0;		
	}

	CValue *pDataAbs = (CValue*)pValues->FindByID(g_strAinExand_Abs + strID);
	CValue *pDataRel = (CValue*)pValues->FindByID(g_strAinExand_Rel + strID);
	CValue *pDataRst = (CValue*)pValues->FindByID(g_strAinExand_Rst + strID);

	double dValue = CString_To_double(pData->m_strValue);
	double dValErrAbs = dValue - dRefVal;
	BOOL bIsAngle = FALSE;

	//是否角度
	if (pData->m_strID.Find(_T("ang$f")) > 0)
	{
		bIsAngle = TRUE;
	}

	if (bIsAngle)
	{
		MakeAngleTo360(dValue);
		MakeAngleTo360(dRefVal);
		dValErrAbs = dValue - dRefVal;
		MakeAngleTo360(dValErrAbs);
		//dValErrAbs = dValErrAbs - ( ((long)(dValErrAbs / 360))*360);
	}

	if (pDataAbs != NULL)
	{
		pDataAbs->m_strValue.Format(_T("%f"), dValErrAbs);
	}

	dValErrAbs = (dValErrAbs);
	double dValErrRel = dValErrAbs;
	double dValErrRelTemp = dValErrAbs;

	//if (dValErrAbs >= 0.000001)
	if (!bIsAngle)
	{
		if (fabs(dRefVal) > 0.0001)
		{
			dValErrRel /= dRefVal;
			dValErrRelTemp = dValErrRel;// * 100;
		}
	}

	nRsltJdg = GBS_CalAinError(pXvm, dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRelTemp);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d")
			, dValue,dRefVal, dValErrAbs, dValErrRelTemp, dAbsErr, dRelErr, nRsltJdg);
	}

	GBS_AddDataErrorToRpt_Rslt_Ex(pXvm, pValues, strID, nRsltJdg);
	//2019-1-2   将数据调整到顶部，方便查阅
	pValues->BringToHead(pDataRst);
	pValues->BringToHead(pDataRel);
	pValues->BringToHead(pDataAbs);
	pValues->BringToHead(pData);

#endif

	return nRsltJdg;
}

long GBS_CalAinErrorEx(CTScriptSingleVM *pXvm, double dRate, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaError3.GetString() /*_T("CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	
	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_ErrFctnTest.GetString() /*L"CalAinErr函数只用用于测试量值测试项目"*/);
		return 1;
	}

	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd     *pCmd = pCommCmd->GetCmd();
	CString strID;
	strID = pszAinID;
	long nRsltJdg = 0;

#ifdef GUIDEBOOK_DEV_MODE
	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CExBaseObject *pSel = pDevice->FindDvmDataObj(strID);

	if (pSel == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CalAinErr函数数据【%s】不存在"), strID);
		return 0;		
	}

	return 1;
#else

	CReport *pReport = GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);
	CValues *pValues = pReport->GetValues();
	CValue *pData = (CValue *)pValues->FindByID(strID);

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ErrFctnUnExist.GetString() /*L"CalAinErr函数数据【%s】不存在"*/, strID.GetString());
		return 0;		
	}

	CValue *pDataAbs = (CValue*)pValues->FindByID(g_strAinExand_Abs + strID);
	CValue *pDataRel = (CValue*)pValues->FindByID(g_strAinExand_Rel + strID);
	CValue *pDataRst = (CValue*)pValues->FindByID(g_strAinExand_Rst + strID);

	double dValue = CString_To_double(pData->m_strValue);
	dValue *= dRate;

	double dValErrAbs = dValue - dRefVal;
	BOOL bIsAngle = FALSE;
	pData->m_strValue.Format(_T("%f"), dValue);

	//是否角度
	if (pData->m_strID.Find(_T("ang$f")) > 0)
	{
		bIsAngle = TRUE;
	}

	if (bIsAngle)
	{
		MakeAngleTo360(dValErrAbs);
		//dValErrAbs = dValErrAbs - ( ((long)(dValErrAbs / 360))*360);
	}

	if (pDataAbs != NULL)
	{
		pDataAbs->m_strValue.Format(_T("%f"), dValErrAbs);
	}

	dValErrAbs = (dValErrAbs);
	double dValErrRel = dValErrAbs;
	double dValErrRelTemp = dValErrAbs;

	if (!bIsAngle)
	{
		if (fabs(dRefVal) > 0.0001)
		{
			dValErrRel /= dRefVal;
			dValErrRelTemp = dValErrRel;// * 100;
		}
	}

	nRsltJdg = GBS_CalAinError(pXvm, dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRelTemp);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d")
			, dValue,dRefVal, dValErrAbs, dValErrRelTemp, dAbsErr, dRelErr, nRsltJdg);
	}

	GBS_AddDataErrorToRpt_Rslt_Ex(pXvm, pValues, strID, nRsltJdg);
#endif

	return nRsltJdg;
}

long GBS_CalAinErrorNom(CTScriptSingleVM *pXvm, double dRate, const char *pszAinID, double dRefVal, double dNom, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaError3.GetString() /*_T("CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	
	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_ErrFctnTest.GetString() /*L"CalAinErr函数只用用于测试量值测试项目"*/);
		return 1;
	}

	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd     *pCmd = pCommCmd->GetCmd();
	CString strID;
	strID = pszAinID;
	long nRsltJdg = 0;

#ifdef GUIDEBOOK_DEV_MODE
	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CExBaseObject *pSel = pDevice->FindDvmDataObj(strID);

	if (pSel == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CalAinErr函数数据【%s】不存在"), strID);
		return 0;		
	}

	return 1;
#else

	CReport *pReport = GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);
	CValues *pValues = pReport->GetValues();
	CValue *pData = (CValue *)pValues->FindByID(strID);

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_ErrFctnUnExist.GetString() /*L"CalAinErr函数数据【%s】不存在"*/, strID.GetString());
		return 0;		
	}

	CValue *pDataAbs = (CValue*)pValues->FindByID(g_strAinExand_Abs + strID);
	CValue *pDataRel = (CValue*)pValues->FindByID(g_strAinExand_Rel + strID);
	CValue *pDataRst = (CValue*)pValues->FindByID(g_strAinExand_Rst + strID);

	double dValue = CString_To_double(pData->m_strValue);
	dValue *= dRate;

	double dValErrAbs = dValue - dRefVal;
	BOOL bIsAngle = FALSE;
	pData->m_strValue.Format(_T("%f"), dValue);

	//是否角度
	if (pData->m_strID.Find(_T("ang$f")) > 0)
	{
		bIsAngle = TRUE;
	}

	if (bIsAngle)
	{
		MakeAngleTo360(dValErrAbs);
		//dValErrAbs = dValErrAbs - ( ((long)(dValErrAbs / 360))*360);
	}

	if (pDataAbs != NULL)
	{
		pDataAbs->m_strValue.Format(_T("%f"), dValErrAbs);
	}

	dValErrAbs = (dValErrAbs);
	double dValErrRel = dValErrAbs;
	double dValErrRelTemp = dValErrAbs;

	if (!bIsAngle)
	{
		if (fabs(dNom) > 0.0001)
		{
			dValErrRel /= dNom;
			dValErrRelTemp = dValErrRel;// * 100;
		}
	}

	nRsltJdg = GBS_CalAinError(pXvm, dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRelTemp);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f , NOM=%.5f, AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d")
			, dValue,dRefVal,dNom, dValErrAbs, dValErrRelTemp, dAbsErr, dRelErr, nRsltJdg);
	}

	GBS_AddDataErrorToRpt_Rslt_Ex(pXvm, pValues, strID, nRsltJdg);
#endif

	return nRsltJdg;
}

long GBS_CalAinStdError(CTScriptSingleVM *pXvm, double dRate, const char *pszAinID,double dRefVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaError4.GetString() /*_T("CalAinStdError函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_StdErrorFctnTest.GetString() /*L"CalAinStdError函数只用用于测试量值测试项目"*/);
		return 1;
	}

	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd     *pCmd = pCommCmd->GetCmd();
	CString strID;
	strID = pszAinID;
	long nRsltJdg = 0;

#ifdef GUIDEBOOK_DEV_MODE
	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CExBaseObject *pSel = pDevice->FindDvmDataObj(strID);

	if (pSel == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CalAinStdError函数数据【%s】不存在"), strID);
		return 0;		
	}

	return 1;
#else

    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);
	CValues *pValues = NULL;
	double dValue = 0;
	CValue *pData = NULL;
	CReport *pReport = NULL;

	if (!pTestControl->CanRunCommCmdFinalResultScript(pCommCmd))
	{
		pReport = GBS_GetReport(pXvm, pCommCmd, -1); //pCommCmd->GetReport(-1);
		pValues = pReport->GetValues();
		pData = (CValue *)pValues->FindByID(strID);

		if (pData != NULL)
		{
			dValue = CString_To_double(pData->m_strValue);
			dValue *= dRate;
			pData->m_strValue.Format(_T("%f"), dValue);
		}

		return 1;
	}

	CReports *pReports = pItem->GetReports();
	CExBaseList oReports;
	pReports->GetReportsForCalEx(oReports);

	long nReports = oReports.GetCount();

	if (nReports < 5)
	{
		oReports.RemoveAll();
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_StdErrorFctnUnExistData.GetString() /*L"CalAinStdError函数数据【%d】不存在不够"*/, nReports);
		return 0;
	}

	double *pdValue = new double[nReports];
	POS pos = oReports.GetHeadPosition();
	long nValueCount = 0;

	while (pos != NULL)
	{
		pReport = (CReport*)oReports.GetNext(pos);
		pValues = pReport->GetValues();
		pData = (CValue *)pValues->FindByID(strID);

		if (pData != NULL)
		{
			pdValue[nValueCount] = CString_To_double(pData->m_strValue);
			nValueCount++;
		}
	}

	oReports.RemoveAll();

	if (nValueCount < 5)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_StdErrorFctnUnExistData.GetString() /*L"CalAinStdError函数数据【%d】不存在不够"*/, nValueCount);
		return 0;		
	}

	long nIndex = 0;
	double dValAvg = 0;
	double dValStdCal = 0;
	dValue = 0;

	//计算平均值
	for (nIndex=0; nIndex<nValueCount; nIndex++)
	{
		dValAvg += pdValue[nIndex];
	}

	dValAvg /= (nValueCount);

	//计算标准差
	for (nIndex=0; nIndex<nValueCount; nIndex++)
	{
		dValue = pdValue[nIndex] - dValAvg;
		dValStdCal += dValue * dValue;
	}

	dValStdCal = dValStdCal / (nValueCount);
	dValStdCal = pow(dValStdCal, 0.5);

	//计算误差
	pReport = GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);
	pValues = pReport->GetValues();
	CValue *pDataAbs = (CValue*)pValues->FindByID(g_strAinExand_Abs + strID);
	CValue *pDataRel = (CValue*)pValues->FindByID(g_strAinExand_Rel + strID);
	CValue *pDataRst = (CValue*)pValues->FindByID(g_strAinExand_Rst + strID);

	double dValErrAbs = dValStdCal;
	BOOL bIsAngle = FALSE;

	//是否角度
	if (pData->m_strID.Find(_T("ang$f")) > 0)
	{
		bIsAngle = TRUE;
	}

	if (bIsAngle)
	{
		MakeAngleTo360(dValErrAbs);
		//dValErrAbs = dValErrAbs - ( ((long)(dValErrAbs / 360))*360);
	}

	if (pDataAbs != NULL)
	{
		pDataAbs->m_strValue.Format(_T("%f"), dValErrAbs);
	}

	dValErrAbs = (dValErrAbs);
	double dValErrRel = dValErrAbs;

	if (!bIsAngle)
	{
		if (fabs(dRefVal) > 0.0001)
		{
			dValErrRel /= dRefVal;
		}
	}

	nRsltJdg = GBS_CalAinError(pXvm, dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRel);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f  nRsltJdg=%d")
			, dValStdCal,dRefVal, dValErrAbs, dValErrRel, dAbsErr, dRelErr, nRsltJdg);
	}

	GBS_AddDataErrorToRpt_Rslt_Ex(pXvm, pValues, strID, nRsltJdg);
#endif

	return nRsltJdg;
}



long GBS_FlterCalError(CTScriptSingleVM *pXvm, const CString &strValID, const char* pszAbsErrID, const char *pszRelErrID
					   , CExBaseList &oList, CValue **ppAbsData, CValue **ppRelData)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FlterFctnTest.GetString() /*L"FlterCalErrorMax函数只用用于测试量值测试项目"*/);
		return 1;
	}

	CString strID;
	CCommCmd *pCommCmd = (CCommCmd*)pItem;

#ifdef GUIDEBOOK_DEV_MODE
	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CExBaseObject *pSel = pDevice->FindDvmDataObj(strID);

	if (pSel == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("FlterCalErrorMax函数数据【%s】不存在"), strValID);
		return 0;		
	}

	CShortDatas* oTags = pCommCmd->GetRptDataEx();

	if (*pszAbsErrID != 0)
	{
		strID = pszAbsErrID;

		if (oTags->FindByID(strID) == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("FlterCalErrorMax函数绝对误差数据【%s】不存在"), strID);
			return 0;	
		}
	}

	if (*pszRelErrID != 0)
	{
		strID = pszRelErrID;

		if (oTags->FindByID(strID) == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("FlterCalErrorMax函数相对误差数据【%s】不存在"), strID);
			return 0;	
		}
	}

	return 1;
#else

	CReport *pReport = GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);
	pReport->m_pRptDvmDataset->QueryByID(strValID, oList);
	CValues *pValues = pReport->GetValues();

	if (*pszAbsErrID != 0)
	{
		strID = pszAbsErrID;
		*ppAbsData = (CValue *)pValues->FindByID(strID);
	}

	if (*pszRelErrID != 0)
	{
		strID = pszRelErrID;
		*ppRelData = (CValue *)pValues->FindByID(strID);
	}

	return 1;
#endif
}

long GBS_FlterCalError(CTScriptSingleVM *pXvm, double dValue, double dRefVal, double dAbsErr, double dRelErr, CValue *pAbsData, CValue *pRelData,BOOL bIsAngle)
{
	double dAbsCal = 0, dRelCal = 0;

	//计算误差
	GBS_CalAinError(pXvm, dValue, dRefVal, dAbsCal, dRelCal, bIsAngle);
	
	//误差判断
	long nRslt = GBS_CalAinError(pXvm, dAbsCal, dRelCal, dAbsErr, dRelErr);
	
	//记录误差值
	if (pAbsData != NULL)
	{
		pAbsData->m_strValue.Format(_T("%f"), dAbsCal);
	}

	if (pRelData != NULL)
	{
		pRelData->m_strValue.Format(_T("%f"), dRelCal);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d")
			, dValue, dRefVal, dAbsCal, dRelCal, dAbsErr, dRelErr, nRslt);
	}

	return nRslt;
}

long GBS_FlterCalErrorMax(CTScriptSingleVM *pXvm, const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_ParaError3.GetString() /*_T("CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FlterFctnTest.GetString() /*L"FlterCalErrorMax函数只用用于测试量值测试项目"*/);
		return 0;
	}

	CString strID;
	CExBaseList oList;
	CValue *pAbsData = NULL;
	CValue *pRelData = NULL;

	strID = pszValID;

	//获得所有的数据对象
	GBS_FlterCalError(pXvm, strID, pszAbsErrID, pszRelErrID, oList, &pAbsData, &pRelData);

#ifdef GUIDEBOOK_DEV_MODE

	return 1;

#else

	if (oList.GetCount() == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ErrFctnUnExist.GetString() /*L"CalAinErr函数数据【%s】不存在"*/, strID.GetString());
		return 0;	
	}

	double dValue = -10000000.0;
	double dTemp = 0;
	POS pos = oList.GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = oList.GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			dTemp = CString_To_double(((CDvmData*)p)->m_strValue);

			if (dValue < dTemp)
			{
				dValue = dTemp;
			}
		}
		else if (p->GetClassID() == DVMCLASSID_CDVMVALUE)
		{
			dTemp = CString_To_double(((CDvmValue*)p)->m_strValue);

			if (dValue < dTemp)
			{
				dValue = dTemp;
			}
		}
	}

	oList.RemoveAll();

	//进行误差判断
	return GBS_FlterCalError(pXvm, dValue, dRefVal, dAbsErr, dRelErr, pAbsData, pRelData, (strID.Find(_T("ang$f")) > 0));

#endif
}


long GBS_FlterCalErrorMin(CTScriptSingleVM *pXvm, const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaError3.GetString() /*_T("CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FlterFctnTest.GetString() /*L"FlterCalErrorMax函数只用用于测试量值测试项目"*/);
		return 0;
	}

	CString strID;
	CExBaseList oList;
	CValue *pAbsData = NULL;
	CValue *pRelData = NULL;

	strID = pszValID;
	GBS_FlterCalError(pXvm, strID, pszAbsErrID, pszRelErrID, oList, &pAbsData, &pRelData);

#ifdef GUIDEBOOK_DEV_MODE

	return 1;

#else

	if (oList.GetCount() == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ErrFctnUnExist.GetString() /*L"CalAinErr函数数据【%s】不存在"*/, strID.GetString());
		return 0;	
	}

	double dValue = 10000000.0;//CString_To_double(pData->m_strValue);
	double dTemp = 0;
	POS pos = oList.GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = oList.GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			dTemp = CString_To_double(((CDvmData*)p)->m_strValue);

			if (dValue > dTemp)
			{
				dValue = dTemp;
			}
		}
		else if (p->GetClassID() == DVMCLASSID_CDVMVALUE)
		{
			dTemp = CString_To_double(((CDvmValue*)p)->m_strValue);

			if (dValue > dTemp)
			{
				dValue = dTemp;
			}
		}
	}

	oList.RemoveAll();

	//进行误差判断
	return GBS_FlterCalError(pXvm, dValue, dRefVal, dAbsErr, dRelErr, pAbsData, pRelData, (strID.Find(_T("ang$f")) > 0));

#endif
}

long GBS_CalAinError2(CTScriptSingleVM *pXvm, const char *pszAinID, const char *pszAinBaseID, double dStdVal, double dAbsErr, double dRelErr)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	
	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_ErrFctnTest.GetString() /*L"CalAinErr函数只用用于测试量值测试项目"*/);
		return 1;
	}

	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd     *pCmd = pCommCmd->GetCmd();
	CString strID, strIDBase;
	strID = pszAinID;
	strIDBase = pszAinBaseID;
	long nRsltJdg = 0;

#ifdef GUIDEBOOK_DEV_MODE
	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CExBaseObject *pSel = pDevice->FindDvmDataObj(strID);

	if (pSel == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CalAinErr函数数据【%s】不存在"), strID);
		return 0;		
	}

	pSel = pDevice->FindDvmDataObj(strIDBase);

	if (pSel == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CalAinErr函数数据【%s】不存在"), strIDBase);
		return 0;		
	}

	return 1;
#else

	CReport *pReport = GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);
	CValues *pValues = pReport->GetValues();
	CValue *pData = (CValue *)pValues->FindByID(strID);
	CValue *pRefData = (CValue *)pValues->FindByID(strIDBase);

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ErrFctnUnExist.GetString() /*L"CalAinErr函数数据【%s】不存在"*/, strID.GetString());
		return 0;		
	}

	if (pRefData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ErrFctnUnExist.GetString() /*L"CalAinErr函数数据【%s】不存在"*/, strIDBase.GetString());
		return 0;		
	}

	CValue *pDataAbs = (CValue*)pValues->FindByID(g_strAinExand_Abs + strID);
	CValue *pDataRel = (CValue*)pValues->FindByID(g_strAinExand_Rel + strID);
	CValue *pDataRst = (CValue*)pValues->FindByID(g_strAinExand_Rst + strID);

	double dValue = CString_To_double(pData->m_strValue);
	double dValueRef = CString_To_double(pRefData->m_strValue);
	double dCalRate = dValue;
	double dValErrAbs = 0;
	BOOL bIsAngle = FALSE;

	if (dValueRef >= 0.0001)
	{
		dCalRate = dValue / dValueRef;
	}

	//计算的比例
	pData->m_strValue.Format(_T("%f"), dCalRate);

	//绝对误差
	dValErrAbs = dCalRate - dStdVal;

	if (pDataAbs != NULL)
	{
		pDataAbs->m_strValue.Format(_T("%f"), dValErrAbs);
	}

	dValErrAbs = (dValErrAbs);
	double dValErrRel = dValErrAbs;
	double dValErrRelTemp = dValErrAbs;

	if (fabs(dStdVal) > 0.0001)
	{
		dValErrRel /= dStdVal;
		dValErrRelTemp = dValErrRel;// * 100;
	}

// 	if (dValErrAbs < dAbsErr || dValErrRel < dRelErr)
// 	{
// 		nRsltJdg = 1;
// 
// 		if (pDataRst != NULL)
// 		{
// 			pDataRst->m_strValue = g_strResultDescValueCorrect;
// 		}
// 	}
// 	else
// 	{
// 		if (pDataRst != NULL)
// 		{
// 			pDataRst->m_strValue = g_strResultDescValueIncorrect	;
// 		}
// 
// 		nRsltJdg = 0;
// 	}

	nRsltJdg = GBS_CalAinError(pXvm, dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRelTemp);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  ,Rate=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d")
		, dValue,dValueRef, dStdVal, dValErrAbs, dValErrRelTemp, dAbsErr, dRelErr, nRsltJdg);

	GBS_AddDataErrorToRpt_Rslt_Ex(pXvm, pValues, strID, nRsltJdg);
#endif

	return nRsltJdg;
}

long GBS_CalAinStdError2(CTScriptSingleVM *pXvm, const char *pszAinID, const char *pszAinBaseID, double dStdVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaError4.GetString() /*_T("CalAinStdError函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_StdErrorFctnTest.GetString() /*L"CalAinStdError函数只用用于测试量值测试项目"*/);
		return 1;
	}

	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd     *pCmd = pCommCmd->GetCmd();
	CString strID, strIDBase;
	strID = pszAinID;
	strIDBase = pszAinBaseID; 
	long nRsltJdg = 0;

#ifdef GUIDEBOOK_DEV_MODE
	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CExBaseObject *pSel = pDevice->FindDvmDataObj(strID);

	if (pSel == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CalAinStdError函数数据【%s】不存在"), strID);
		return 0;		
	}

	return 1;
#else

    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);
	CReports *pReports = pItem->GetReports();
	CReport *pReport = NULL;
	CValues *pValues = NULL;
	double dRate = 1;
	double dValue = 0;
	CValue *pData = NULL;
	pData = NULL;
	long nValueCount = 0;
	CValue *pRefData = NULL;

	if (!pTestControl->CanRunCommCmdFinalResultScript(pCommCmd))
	{
		pReport = GBS_GetReport(pXvm, pCommCmd, -1); //pCommCmd->GetReport(-1);
		pValues = pReport->GetValues();
		pData = (CValue *)pValues->FindByID(strID);
		pRefData = (CValue *)pValues->FindByID(strIDBase);
	
		if (pData != NULL && pRefData != NULL)
		{
			dValue = CString_To_double(pData->m_strValue);
			dRate = CString_To_double(pRefData->m_strValue);

			if (g_nLog_TestControl_Msg == 1)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Value=%f   StdRefVal=%f"), dValue, dRate);
			}
	
			dValue /= dRate;
			pData->m_strValue.Format(_T("%f"), dValue);
		}

		return 1;
	}

	CExBaseList oReports;
	pReports->GetReportsForCalEx(oReports);

	long nReports = oReports.GetCount();

	if (nReports < 2)
	{
		oReports.RemoveAll();
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_StdErrorFctnUnExistData.GetString() /*L"CalAinStdError函数数据【%s】不存在不够"*/);
		return 0;
	}

	double *pdValue = new double[nReports];
	POS pos = oReports.GetHeadPosition();

	while (pos != NULL)
	{
		pReport = (CReport*)oReports.GetNext(pos);
		pValues = pReport->GetValues();
		pData = (CValue *)pValues->FindByID(strID);

		if (pData != NULL)
		{
			pdValue[nValueCount] = CString_To_double(pData->m_strValue);
			nValueCount++;
		}
	}

	oReports.RemoveAll();

	if (nValueCount < 2)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_StdErrorFctnUnExistData.GetString() /*L"CalAinStdError函数数据【%s】不存在不够"*/);
		return 0;		
	}

	long nIndex = 0;
	double dValAvg = 0;
	double dValStdCal = 0;
	dValue = 0;

	//计算平均值
	for (nIndex=0; nIndex<nValueCount; nIndex++)
	{
		dValAvg += pdValue[nIndex];
	}

	dValAvg /= nValueCount;

	//计算标准差
	for (nIndex=0; nIndex<nValueCount; nIndex++)
	{
		dValue = pdValue[nIndex] - dValAvg;
		dValStdCal += dValue * dValue;
	}

	dValStdCal = dValStdCal / nValueCount;
	dValStdCal = pow(dValStdCal, 0.5);

	//计算误差
	pReport = GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);
	pValues = pReport->GetValues();

	CValue *pDataAbs = (CValue*)pValues->FindByID(g_strAinExand_Abs + strID);
	CValue *pDataRel = (CValue*)pValues->FindByID(g_strAinExand_Rel + strID);
	CValue *pDataRst = (CValue*)pValues->FindByID(g_strAinExand_Rst + strID);

	double dValErrAbs = dValStdCal;
	BOOL bIsAngle = FALSE;

	if (pDataAbs != NULL)
	{
		pDataAbs->m_strValue.Format(_T("%f"), dValErrAbs);
	}

	dValErrAbs = (dValErrAbs);
	double dValErrRel = dValErrAbs / dStdVal;

	nRsltJdg = GBS_CalAinError(pXvm, dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRel);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d" )
			, dValStdCal,dStdVal, dValErrAbs, dValErrRel, dAbsErr, dRelErr, nRsltJdg);
	}

	GBS_AddDataErrorToRpt_Rslt_Ex(pXvm, pValues, strID, nRsltJdg);
#endif

	return nRsltJdg;
}

double GBS_CalVariation(CTScriptSingleVM *pXvm, double dValue, double dTheoreticalVal, double dBaseValue, double dRate)
{
	return ((dTheoreticalVal - dValue) / dBaseValue) * dRate;
}

long GBS_CalVariationErr(CTScriptSingleVM *pXvm, double dValue, double dTheoreticalVal, double dBaseValue, double dRate, double dRelErr)
{
	if (dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaError5.GetString() /*_T("CalVariationEror函数:误差限[%f]都小于0，参数错误！")*/, dRelErr);
		return 1;
	}

	double dVarVal = GBS_CalVariation(pXvm, dValue, dTheoreticalVal, dBaseValue, dRate);
	long nRsltJdg = 0;

	dVarVal = fabs(dVarVal);

	if (dVarVal > dRelErr)
	{
		nRsltJdg = 0;
	}
	else
	{
		nRsltJdg = 1;
	}

	return nRsltJdg;
}

long GBS_CalVariationErrEx(CTScriptSingleVM *pXvm, const char *pszAinID, const char *pszTheoreticalID, const char *pszBaseValueID, const char *pszRsltID, const char *pszRelErr, double dRate)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_VariationFctnTest.GetString() /*L"CalVariationErrorEx函数只用用于测量值测试项目"*/);
		return 1;
	}

	CMacroTest *pMacroTest = (CMacroTest*)pItem->GetParent();

	if (pMacroTest->GetClassID() != GBCLASSID_MACROTEST)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_VariationFctnItem.GetString() /*L"CalVariationErrorEx函数所在的项目的父项目不是电气量项目"*/);
		return 1;
	}

	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);
	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd     *pCmd = pCommCmd->GetCmd();
	CString strID, strTheoreticalID, strRsltID, strBaseValID;
	strID = pszAinID;
	strTheoreticalID = pszTheoreticalID;
	strRsltID = pszRsltID;
	strBaseValID = pszBaseValueID;
	long nRsltJdg = 0;

	double dRelErr = 0;

	if (IsStringNumber(pszRelErr))
	{
		dRelErr = atof(pszRelErr);
	}
	else
	{
		CString strErrID;
		strErrID = pszRelErr;
		CDataObj *pError = (CDataObj*)pDevice->m_pSysParas->FindByID(strErrID);

		if (pError == NULL)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_FctnVariousUnExist.GetString() /*_T("CalVariationErrorEx函数:误差限变量[%s]不存在！")*/, strErrID.GetString());
			return 1;
		}

		dRelErr = CString_To_double(pError->m_strValue);
	}

	
	if (dRelErr <= 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaError5.GetString() /*_T("CalVariationErrorEx函数:误差限[%f]小于0，参数错误！")*/, dRelErr);
		return 1;
	}

#ifdef GUIDEBOOK_DEV_MODE
	CExBaseObject *pSel = pDevice->FindDvmDataObj(strID);

	if (pSel == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CalVariationErrorEx函数数据【%s】不存在"), strID);
		return 0;		
	}

	CDataObj *pDataBaseVal = (CDataObj*)pDevice->m_pSysParas->FindByID(strBaseValID);
	
	if (pDataBaseVal == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CalVariationErrorEx函数基准值【%s】不存在"), strBaseValID);
		return 0;		
	}

	return 1;
#else

	CReport *pReport = GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);
	CValues *pValues = pReport->GetValues();
	CReport *pReport2 = GBS_GetReport(pXvm, pMacroTest, -1); //pMacroTest->GetReport(-1);
	CValues *pValues2 = pReport2->GetValues();

	CValue *pData    = (CValue*)pValues->FindByID(strID);
	CValue *pTheoreticalData = (CValue*)pValues2->FindByID(strTheoreticalID);
	CValue *pDataRst = (CValue*)pValues->FindByID(strRsltID);

	if (pDataRst == NULL)
	{
		pDataRst = (CValue*)pValues2->FindByID(strRsltID);
	}

	CDataObj *pDataBaseVal = (CDataObj*)pDevice->m_pSysParas->FindByID(strBaseValID);

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,  g_sLangTxt_VariationFctnUnExist3.GetString() /*L"CalVariationErrorEx函数数据【实测值】【%s】不存在"*/, strID.GetString());
		return 0;		
	}

	if (pTheoreticalData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_VariationFctnUnExist4.GetString() /*L"CalVariationErrorEx函数数据【理论值】【%s】不存在"*/, strTheoreticalID.GetString());
		return 0;		
	}

	if (pDataBaseVal == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_VariationFctnUnExist5.GetString() /*L"CalVariationErrorEx函数：测试参数基准值【%s】不存在"*/, strBaseValID.GetString());
		return 0;		
	}

	if (pDataRst == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_VariationFctnUnExist6.GetString() /*L"CalVariationErrorEx函数数据【结果变量】【%s】不存在"*/, strRsltID.GetString());
	}

	double dValue = CString_To_double(pData->m_strValue);
	double dTheoreticalValue = CString_To_double(pTheoreticalData->m_strValue);
	double dBaseValue = CString_To_double(pDataBaseVal->m_strValue);

	double dCalVarVal = GBS_CalVariation(pXvm, dValue, dTheoreticalValue, dBaseValue, dRate);
	
	//计算的比例
	if (pDataRst != NULL)
	{
		pDataRst->m_strValue.Format(_T("%f"), dCalVarVal);
	}

	//结果判断
	if (fabs(dCalVarVal) > dRelErr)
	{
		nRsltJdg = 0;
	}
	else
	{
		nRsltJdg = 1;
	}

	if (g_nLog_TestControl_Msg == 1)
	{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ResultJude.GetString() /*_T("实测值=%.5f  ,理论值=%.5f  ,基准值=%.5f  变差=%.5f 误差限=%.5f  结果判断=%d")*/
		, dValue, dTheoreticalValue, dBaseValue, dCalVarVal, dRelErr, nRsltJdg);
	}

#endif

	return nRsltJdg;
}


// 获取定值数据
// pszID：数据的ID
double GBS_GetSetValue(CTScriptSingleVM *pXvm, const char* pszID)
{
// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
// 	CSet *pSet = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectSet(CString(pszID));
// 	double dValue = 1;
// 
// 	if (pSet != NULL)
// 	{
// 		dValue = _wtof(pSet->m_strValue);
// 	}
// 	else
// 	{
// 		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"Set id(%s) not exist", (CString)pszID);
// 
// 		CString strErrorInfo;
// 		CString strID(pszID);
// 		strErrorInfo.Format( L"Set id(%s) not exist", strID);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
// 	}
// 
// 	return dValue;
	return GBS_GetDsDataValue(pXvm, pszID);
}

void GBS_SetSetValue(CTScriptSingleVM *pXvm, const char* pszID, double dVal)
{
// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
// 	CSet *pSet = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectSet(CString(pszID));
// 	double dValue = 1;
// 
// 	if (pSet != NULL)
// 	{
// 		pSet->m_strValue.Format(_T("%f"), dVal);
// 	}
// 	else
// 	{
// 		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"Set id(%s) not exist", (CString)pszID);
// 
// 		CString strErrorInfo;
// 		CString strID(pszID);
// 		strErrorInfo.Format( L"Set id(%s) not exist", strID);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
// 	}
	GBS_SetDsDataValue(pXvm, pszID, dVal);
}

// 获取定值数据
// pszID：数据的ID
// double GBS_GetSoftswitchValue(const char* pszID)
// {
// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
// 	CSet *pSet = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectSoftSwitch(CString(pszID));
// 	double dValue = 1;
// 
// 	if (pSet != NULL)
// 	{
// 		dValue = _wtof(pSet->m_strValue);
// 	}
// 	else
// 	{
// 		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"Set id(%s) not exist", (CString)pszID);
// 
// 		CString strErrorInfo;
// 		CString strID(pszID);
// 		strErrorInfo.Format( L"Set id(%s) not exist", strID);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
// 	}
// 
// 	return dValue;
// }
// 
// void GBS_SetSoftswitchValue(const char* pszID, double dVal)
// {
// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
// 	CSet *pSet = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectSoftSwitch(CString(pszID));
// 	double dValue = 1;
// 
// 	if (pSet != NULL)
// 	{
// 		pSet->m_strValue.Format(_T("%f"), dVal);
// 	}
// 	else
// 	{
// 		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"Set id(%s) not exist", (CString)pszID);
// 
// 		CString strErrorInfo;
// 		CString strID(pszID);
// 		strErrorInfo.Format( L"Set id(%s) not exist", strID);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
// 	}
// }

// 获取系统参数数据数据
// pszID：数据的ID
double GBS_GetSysParaValue(CTScriptSingleVM *pXvm, const char* pszID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas != NULL);
	CDataObj  *pData = (CDataObj*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas->FindByID(CString(pszID));
	double dValue = 1;

	if (pData == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SysPara id(%s) not exist"), (CString)pszID);

		CString strErrorInfo;
		CString strID(pszID);
        strErrorInfo.Format( _T("SysPara id(%s) not exist"), strID.GetString());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
		//lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
		//throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
#ifdef _UNICODE
		dValue = _wtof(pData->m_strValue);
#else
        dValue = atof(pData->m_strValue.GetString());
#endif
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("GetSysParaValue([%s] [%.f]")
//		, CString(pszID), dValue);

	return dValue;
}

void GBS_SetSysParaValue(CTScriptSingleVM *pXvm, const char* pszID, double dValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas != NULL);
	CDataObj  *pData = (CDataObj*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas->FindByID(CString(pszID));

	if (pData == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SysPara id(%s) not exist"), (CString)pszID);

		CString strErrorInfo;
		CString strID(pszID);
        strErrorInfo.Format( _T("SysPara id(%s) not exist"), strID.GetString());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
		//lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
		//throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		CString strVal;
		strVal.Format(_T("%f"), dValue);

#ifndef GUIDEBOOK_DEV_MODE
		pData->m_strValue = strVal;
#endif	

	}
}

// 获取测试参数数据
// pszID：数据的ID
double GBS_GetTestParaValue(CTScriptSingleVM *pXvm, const char* pszID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CDevice *pDevice = pGuideBook->GetDevice();
	ASSERT (pDevice != NULL);

	if (pDevice == NULL)
	{
		return 0;
	}

	CDataObj  *pData = (CDataObj*)pDevice->m_pSysParas->FindByID(CString(pszID));
	double dValue = 1;

	if (pData == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SysPara id(%s) not exist"), (CString)pszID);

		CString strErrorInfo;
		CString strID(pszID);
        strErrorInfo.Format(_T("SysPara id(%s) not exist"), strID.GetString());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
#ifdef _UNICODE
		dValue = _wtof(pData->m_strValue);
#else
        dValue = atof(pData->m_strValue.GetString());
#endif
	}

	return dValue;
}

const char* GBS_GetTestParaStr(CTScriptSingleVM *pXvm, const char* pszID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas != NULL);
	CDataObj  *pData = (CDataObj*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas->FindByID(CString(pszID));
	double dValue = 1;

	if (pData == NULL)
	{
		g_pLuaReturnString[0] = 0;
	}
	else
	{
		CString_to_char(pData->m_strValue, g_pLuaReturnString);
	}

	return g_pLuaReturnString;
}


// 设置测试参数数据
// pszID：数据的ID
void GBS_SetTestParaValue(CTScriptSingleVM *pXvm, const char* pszID, double dValue)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CDevice *pDevice = pGuideBook->GetDevice();
	ASSERT (pDevice != NULL);

	if (pDevice == NULL)
	{
		return;
	}

	CDataObj  *pData = (CDataObj*)pDevice->m_pSysParas->FindByID(CString(pszID));

	if (pData == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SysPara id(%s) not exist"), (CString)pszID);

		CString strErrorInfo;
		CString strID(pszID);
        strErrorInfo.Format(_T("SysPara id(%s) not exist"), strID.GetString());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		pData->m_strValue.Format(_T("%f"), dValue);
	}
}

void GBS_SetTestParaStr(CTScriptSingleVM *pXvm, const char* pszID, const char *pszValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas != NULL);
	CDataObj  *pData = (CDataObj*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas->FindByID(CString(pszID));

	if (pData == NULL)
	{
		CString strErrorInfo;
		CString strID(pszID);
        strErrorInfo.Format(_T("SysPara id(%s) not exist"), strID.GetString());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		pData->m_strValue = pszValue;
	}
}

//设置满足条件的项目的Show属性
//pszItemPath为Item的路径
void GBS_SetItemShow(CTScriptSingleVM *pXvm, const char* pszItemPath, long nShow)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);

		if (nShow != pItem->m_nShow)
		{
			pItem->SetShow(nShow);
			
			//发送项目显示改变消息 #########
			
			//显示函数调用信息
			if (g_nLog_TestControl_Msg == 1)
			{
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Item(%s) SHOW=%d"), pItem->m_strID.GetString(), nShow);
			}
		}
	}

	oListDest.RemoveAll();
}


// 获取满足条件的项目的Show属性
// pszItemPath为Item的路径
long GBS_GetItemShow(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();
	long nShow = 0;

	if (nCount > 1)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), pszItemPath, nCount);
		//显示消息，路径检索的项目不唯一

		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format( _T("Path(%s) select %d items"), strPath.GetString(), nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else if (nCount == 0)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);
		//显示消息：路径指定的项目不存在

		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format( _T("Path(%s) select %d items"), strPath.GetString(), nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
		nShow = pItem->GetShow();
	}
	
	oListDest.RemoveAll();
	return nShow;
}

// 设置满足条件的项目的Enable属性
// pszItemPath为Item的路径
void GBS_SetItemEnable(CTScriptSingleVM *pXvm, const char* pszItemPath, long nEnable)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);

		if (nEnable != pItem->m_nEnable)
		{
			pItem->SetEnable(nEnable);

			//发送项目Enable改变消息 #########

			//显示函数调用信息
			if (g_nLog_TestControl_Msg == 1)
			{
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Item(%s) ENABLE=%d"), pItem->m_strID.GetString(), nEnable);
			}
		}
	}

	oListDest.RemoveAll();
}

// 获取满足条件的项目的Enable属性
// pszItemPath为Item的路径
long GBS_GetItemEnable(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();
	long nEnable = 0;

	if (nCount > 1)
	{
		//显示消息，路径检索的项目不唯一
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format(_T("Path(%s) select %d items"), strPath.GetString(), nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else if (nCount == 0)
	{
		//显示消息：路径指定的项目不存在
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format(_T("Path(%s) select %d items"), strPath.GetString(), nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
		nEnable = pItem->GetEnable();
	}

	oListDest.RemoveAll();
	return nEnable;
}

void GBS_SetItemSelect(CTScriptSingleVM *pXvm, const char* pszItemPath, long nSelect)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);

		Gb_SetTestItemSelectedState(pItem, nSelect);
// 		if (nEnable != pItem->m_nEnable)
// 		{
// 			pItem->SetEnable(nEnable);
// 
// 			//发送项目Enable改变消息 #########
// 
// 			//显示函数调用信息
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"Item(%s) ENABLE=%d", (CString)pItem->m_strID, nEnable);
// 		}
	}

	oListDest.RemoveAll();
}

long GBS_GetItemSelect(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();
	long nSelect = 0;

	if (nCount > 1)
	{
		//显示消息，路径检索的项目不唯一
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format(_T("Path(%s) select %d items"), strPath.GetString(), nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else if (nCount == 0)
	{
		//显示消息：路径指定的项目不存在
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format(_T("Path(%s) select %d items"), strPath.GetString(), nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
		nSelect = pItem->GetSelect();
	}

	oListDest.RemoveAll();
	return nSelect;
}

// 设置满足条件的项目的Name属性
// pszItemPath为Item的路径
void GBS_SetItemName(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszName)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	CString strName = CString(pszName);

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);

		pItem->m_strName = strName;

		//发送项目Name改变消息 #########

		//显示函数调用信息
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Item(%s) name=[%s]"), pItem->m_strID.GetString(), pItem->m_strName.GetString());
	}

	oListDest.RemoveAll();
}

// 获取满足条件的项目的Name属性
// pszItemPath为Item的路径
const char* GBS_GetItemName(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();
	long nEnable = 0;
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer[0] = 0;

	if (nCount > 1)
	{
		//显示消息，路径检索的项目不唯一
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

		CString strErrorInfo;
		CString strPath(pszItemPath);
		strErrorInfo.Format(_T("Path(%s) select %d items"), pszItemPath, nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else if (nCount == 0)
	{
		//显示消息：路径指定的项目不存在
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format(_T("Path(%s) select %d items"), strPath.GetString(), nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
		CString_to_char(pItem->m_strName, _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer);
		nEnable = pItem->GetEnable();
	}

	oListDest.RemoveAll();
	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
}

// 设置满足条件的项目的结果判断
// pszItemPath为Item的路径
void GBS_SetRsltJdg(CTScriptSingleVM *pXvm, CGbItemBase *pItem, long nResult)
{
	CReport *pReport = GBS_GetReport(pXvm, pItem, -1);
	pItem->SetRsltJdg(pReport, nResult);
}

void GBS_SetItemResultJudge(CTScriptSingleVM *pXvm, const char* pszItemPath, long nResult)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);

		GBS_SetRsltJdg(pXvm, pItem, nResult);//pItem->SetRsltJdg(nResult);
		//发送项目显示改变消息 #########
		//显示函数调用信息
	}

	oListDest.RemoveAll();
}

long GBS_GetItemResultJudge(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();
	long nResult = 0;

	if (nCount > 1)
	{
		//显示消息，路径检索的项目不唯一
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

		CString strErrorInfo;
		CString strPath;
		strPath = pszItemPath;
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), strPath.GetString(), nCount);
		//lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
		//throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else if (nCount == 0)
	{
		//显示消息：路径指定的项目不存在
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

		CString strErrorInfo;
		CString strPath;
		strPath = pszItemPath;
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), strPath.GetString(), nCount);
		//lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
		//throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
		nResult = pItem->GetRsltJdg();

		if (pItem->GetState() == TEST_STATE_INLEGIBLE)
		{
			nResult = 0;
		}
	}

	oListDest.RemoveAll();
	return nResult;
}




// 设置满足条件的项目的数据的值
// pszItemPath为Item的路径
void GBS_SetItemParaValue(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	CString strVal;
	strVal.Format(_T("%f"), dValue);
	CString strValID(pszValID);
	CString bstrVal(strVal);

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);
		//pItem->SetItemParaValue(strValID, bstrVal);
		if (!pItem->SetItemParaValue(strValID, bstrVal, TRUE))
		{
			//ID不存在
			oListDest.RemoveAll();
			CString strErrorInfo;
			CString strPath(pszItemPath);
			CString strID(pszValID);
            strErrorInfo.Format( g_sLangTxt_SetItemIDUnExist.GetString() /*L"SetItemParaValue ID不存在,Path(%s) ID(%s) items"*/, strPath.GetString(), strID.GetString());
			CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 			lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 			throw luabind::error(g_pGuideBookLua);		//抛出异常信息
		}
	}

	oListDest.RemoveAll();
}

void GBS_SetItemParaValueStr(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, const char *pszValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	CString strVal(pszValue);
	CString strValID(pszValID);

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);

		if (!pItem->SetItemParaValue(strValID, strVal, TRUE))
		{
			//ID不存在
			oListDest.RemoveAll();
			CString strErrorInfo;
			CString strPath(pszItemPath);
			CString strID(pszValID);
            strErrorInfo.Format( g_sLangTxt_SetItemIDUnExist.GetString() /*L"SetItemParaValue ID不存在,Path(%s) ID(%s) items"*/, strPath.GetString(), strID.GetString());
			CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 			lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 			throw luabind::error(g_pGuideBookLua);		//抛出异常信息
		}
	}

	oListDest.RemoveAll();
}

double GBS_GetItemParaValueEx(CTScriptSingleVM *pXvm, CGbItemBase *pItem, const char* pszValID)
{
#ifdef GUIDEBOOK_DEV_MODE

		return pItem->GetItemParaValue(pszValID);

#else

	return pItem->GetItemParaValue(pszValID);

/*
	CGbItemBase *pCurrItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	if (pItem == pCurrItem)
	{
		return pItem->GetItemParaValue(pszValID);
	}
	else
	{
        if (!g_theSmartTestBaseApp->IsSaveRptToDB())
		{
			return pItem->GetItemParaValue(pszValID);
		}
		else
		{
			CGuideBook *pGuideBook = (CGuideBook*)pCurrItem->GetAncestor(GBCLASSID_GUIDEBOOK);
            CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
			return pTestControl->GBS_GetItemParaValueEx(pItem, pszValID);
		}
	}
*/

#endif
}

double GBS_GetItemParaValue(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();
	double dValue = 0;

	if (nCount > 1)
	{
		//显示消息，路径检索的项目不唯一
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format(_T("Path(%s) select %d items"), strPath.GetString(), nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息

	}
	else if (nCount == 0)
	{
		//显示消息：路径指定的项目不存在
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format(_T("Path(%s) select %d items"), strPath.GetString(), nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		 //2019-4-16  多装置测试，报告数据保存到本地数据库，结果判断时要取得其他项目的报告，因此改进此功能
		pItem = (CGbItemBase*)oListDest.GetHead();
		dValue = GBS_GetItemParaValueEx(pXvm, pItem, pszValID);//pItem->GetItemParaValue(pszValID); 
	}

	oListDest.RemoveAll();
	return dValue;
}

const char* GBS_GetItemParaString(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();
	double dValue = 0;

	if (nCount > 1)
	{
		//显示消息，路径检索的项目不唯一
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);

// 		CString strErrorInfo;
// 		CString strPath(pszItemPath);
// 		strErrorInfo.Format(_T("Path(%s) select %d items"), strPath, nCount);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
		g_pLuaReturnString[0] = 0;
	}
	else if (nCount == 0)
	{
		//显示消息：路径指定的项目不存在
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), (CString)pszItemPath, nCount);
		g_pLuaReturnString[0] = 0;

// 		CString strErrorInfo;
// 		CString strPath(pszItemPath);
// 		strErrorInfo.Format(_T("Path(%s) select %d items"), strPath, nCount);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		//2019-4-16  多装置测试，报告数据保存到本地数据库，结果判断时要取得其他项目的报告，因此改进此功能
		pItem = (CGbItemBase*)oListDest.GetHead();
		dValue = GBS_GetItemParaValueEx(pXvm, pItem, pszValID);//pItem->GetItemParaValue(pszValID); 
		sprintf(g_pLuaReturnString, "%f", dValue);
	}

	oListDest.RemoveAll();
	return g_pLuaReturnString;
}

void GBS_GetItemTestTime_Mode(CTScriptSingleVM *pXvm, const char* pszItemPath, CString &strTime, long nMode)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();

	if (nCount == 1)
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
		CReport *pReport = GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);

		if (pReport != NULL)
		{
			strTime = pReport->GetTestTime(nMode);
		}
	}

	if (strTime.GetLength() == 0)
	{
		GetCurrSystemtimeString(strTime);
		g_pLuaReturnString[0] = 0;
	}

	oListDest.RemoveAll();
}

const char* GBS_GetItemTestTime(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	CString strTime;
	
	GBS_GetItemTestTime_Mode(pXvm, pszItemPath, strTime, 0);

	CString_to_char(strTime, g_pLuaReturnString);
	return g_pLuaReturnString;
}

const char* GBS_GetItemTestBeginTime(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	CString strTime;

	GBS_GetItemTestTime_Mode(pXvm, pszItemPath, strTime, 1);

	CString_to_char(strTime, g_pLuaReturnString);
	return g_pLuaReturnString;
}

const char* GBS_GetItemTestEndTime(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	CString strTime;

	GBS_GetItemTestTime_Mode(pXvm, pszItemPath, strTime, 2);

	CString_to_char(strTime, g_pLuaReturnString);
	return g_pLuaReturnString;
}

//通讯命令的参数脚本函数  2019-3-19
void GBS_ClearCommCmdParas(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	CCommCmd *pCommCmd = NULL;

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);

		if (pItem->GetClassID() != GBCLASSID_COMMCMD)
		{
			continue;
		}

		((CCommCmd *)pItem)->ClearCommCmdParas();
	}

	oListDest.RemoveAll();
}

void GBS_AddCommCmdParaValue_String(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, const CString &strValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	CString strValID(pszValID);
	CCommCmd *pCommCmd = NULL;

	if (pos == NULL)
	{
		CString strPath(pszItemPath);
		CString strErrorInfo;
        strErrorInfo.Format( g_sLangTxt_SetItemIDUnExist.GetString() /*L"SetItemParaValue ID不存在,Path(%s) ID(%s) items"*/, strPath.GetString(), strValID.GetString());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
	}

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);

		if (pItem->GetClassID() != GBCLASSID_COMMCMD)
		{
			continue;
		}

		pCommCmd = (CCommCmd *)pItem;

		pCommCmd->AddCommCmdParaValue(strValID, strValue);
	}

	oListDest.RemoveAll();
}

void GBS_AddCommCmdParaValue(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dValue)
{
	CString strValue;
	strValue.Format(_T("%f"), dValue);
	GBS_AddCommCmdParaValue_String(pXvm, pszItemPath, pszValID, strValue);
}

void GBS_AddCommCmdParaValue_Long(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	GBS_AddCommCmdParaValue_String(pXvm, pszItemPath, pszValID, strValue);
}

void GBS_AddCommCmdParaValue_String(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, const char *pszValue)
{
	CString strValue;
	strValue = pszValue;
	GBS_AddCommCmdParaValue_String(pXvm, pszItemPath, pszValID, strValue);
}

void GBS_AddRptMapData(CTScriptSingleVM *pXvm, const char* pszValID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CString strID;
	strID = pszValID;
	CReportMap *pMap = pItem->GetReportMap();
	CExBaseObject* pObj = pMap->FindRptData(strID, 0);

	if (pObj == NULL)
	{
		pObj = pMap->AddNewData(_T(""), strID, _T("3"), 0);
	}
}

BOOL GBS_SetItemReportValue(CTScriptSingleVM *pXvm, CGbItemBase *pItem, const CString &strValueID, const CString &strValue)
{
	CReport *pReport = GBS_GetReport(pXvm, pItem, -1);

    if(pReport == NULL)
        return FALSE;

	return pReport->SetValue(strValueID, strValue);
}

//报告数据
void GBS_SetItemReportValue(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("SetReportValue([%s] [%s] [%.f]")
//		, CString(pszItemPath), CString(pszValID), dValue);

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	CString strVal;
	strVal.Format(_T("%f"), dValue);
	CString strValID(pszValID);
	CString bstrVal(strVal);

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);
	
		//if (!pItem->SetItemReportValue(strValID, bstrVal))
		if (!GBS_SetItemReportValue(pXvm, pItem, strValID, bstrVal))
		{
			//ID不存在
			oListDest.RemoveAll();

#ifdef GUIDEBOOK_DEV_MODE
			CString strErrorInfo;
			CString strPath(pszItemPath);
			CString strID(pszValID);
			strErrorInfo.Format( g_sLangTxt_SetItemIDUnExist2.GetString() /*L"SetReportValue ID不存在,Path(%s) ID(%s) items"*/, strPath, strID);
			CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
#endif
// 			lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 			throw luabind::error(g_pGuideBookLua);	
		}
	}

	oListDest.RemoveAll();
}

void GBS_SetItemReportValueString(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, const char* pszValString)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	CString strVal;
	strVal = pszValString;
	CString strValID(pszValID);
	CString bstrVal(strVal);

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);

		//if (!pItem->SetItemReportValue(strValID, bstrVal))
		if (!GBS_SetItemReportValue(pXvm, pItem, strValID, bstrVal))
		{
			//ID不存在
			oListDest.RemoveAll();
#ifdef GUIDEBOOK_DEV_MODE
			CString strErrorInfo;
			CString strPath(pszItemPath);
			CString strID(pszValID);
			strErrorInfo.Format( g_sLangTxt_SetItemIDUnExist2.GetString() /*L"SetReportValue ID不存在,Path(%s) ID(%s) items"*/, strPath, strID);
			CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
#endif
// 			lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 			throw luabind::error(g_pGuideBookLua);	
		}
	}

	oListDest.RemoveAll();
}

CGbItemBase* GBS_GetItem(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();
	double dValue = 0;

	if (nCount > 1)
	{
		//显示消息，路径检索的项目不唯一
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_PathItem.GetString()/*"路径检索的项目不唯一,Path(%s) select %d items"*/, pszItemPath, nCount);
//		CLogPrint::LogString(XLOGLEVEL_TRACE, CString(pszErrorInfo));
// 		lua_pushstring(g_pGuideBookLua,pszErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else if (nCount == 0)
	{
		//char pszErrorInfo[MAX_PATH];
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_PathItem2.GetString() /*"路径指定的项目不存在,Path(%s) select %d items"*/, pszItemPath, nCount);
		//CLogPrint::LogString(XLOGLEVEL_TRACE, CString(pszErrorInfo));
// 		lua_pushstring(g_pGuideBookLua, pszErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
	}

	oListDest.RemoveAll();

	return pItem;
}

double GBS_GetItemReportValue(CTScriptSingleVM *pXvm, CGbItemBase *pItem, const char* pszValID)
{
	CReport *pReport = GBS_GetReport(pXvm, pItem, -1);

	if (pReport == NULL)
	{
		return 0;
	}

	double dValue = 0;
	CString strValID;
	strValID = pszValID;
	pReport->GetReportValue(strValID, dValue);

	return dValue;
}

char* GBS_GetItemReportValue(CTScriptSingleVM *pXvm, CGbItemBase *pItem, const char* pszValID, char *pszValue, long nIndex)
{
	CReport *pReport = GBS_GetReport(pXvm, pItem, nIndex);

	if (pReport == NULL)
	{
		*pszValue = 0;
		return pszValue;
	}

	CString strValID;
	strValID = pszValID;
	pReport->GetReportValue(strValID, pszValue);

	return pszValue;
}

double GBS_GetItemReportValue(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID)
{
	CGbItemBase *pItem = GBS_GetItem(pXvm, pszItemPath);
	double dValue = 0;

	if (pItem != NULL)
	{
		//dValue = pItem->GetItemReportValue(pszValID);
		dValue = GBS_GetItemReportValue(pXvm, pItem, pszValID);
	}
// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
// 	CGbItemBaseList oListDest;
// 
// 	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
// 	POS pos = oListDest.GetHeadPosition();
// 	long nCount = oListDest.GetCount();
// 
// 	if (nCount > 1)
// 	{
// 		//显示消息，路径检索的项目不唯一
// 		CString strErrorInfo;
// 		CString strPath(pszItemPath);
// 		strErrorInfo.Format( L"路径检索的项目不唯一,Path(%s) select %d items", strPath, nCount);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
// 	}
// 	else if (nCount == 0)
// 	{
// 		//显示消息：路径指定的项目不存在
// 		CString strErrorInfo;
// 		CString strPath(pszItemPath);
// 		strErrorInfo.Format( L"路径指定的项目不存在,Path(%s) select %d items", strPath, nCount);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
// 	}
// 	else
// 	{
// 		pItem = (CGbItemBase*)oListDest.GetHead();
// 		dValue = pItem->GetItemReportValue(pszValID);
// 	}
// 
// 	oListDest.RemoveAll();

// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("GetReportValue([%s] [%s] [%.f]")
// 		, CString(pszItemPath), CString(pszValID), dValue);

	return dValue;
}

long GBS_GetItemReportValueLong(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID)
{
	double dValue = GBS_GetItemReportValue(pXvm, pszItemPath, pszValID);
	long nValue = (long)dValue;
	return nValue;
}


const char* GBS_GetItemReportValueString(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID)
{
	CGbItemBase *pItem = GBS_GetItem(pXvm, pszItemPath);

	if (pItem != NULL)
	{
		//pItem->GetItemReportValue(pszValID, g_pLuaReturnString);
		GBS_GetItemReportValue(pXvm, pItem, pszValID, g_pLuaReturnString, -1);
	}
	else
	{
		g_pLuaReturnString[0] = 0;
	}

	return g_pLuaReturnString;
}

double GBS_GetItemReportValueEx(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, long nIndex)
{
	GBS_GetItemReportValueStringEx(pXvm, pszItemPath, pszValID, nIndex);

	if (g_pLuaReturnString[0] == 0)
	{
		return 0;
	}
	else
	{
		return atof(g_pLuaReturnString);
	}
}

long GBS_GetItemReportValueLongEx(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, long nIndex)
{
	GBS_GetItemReportValueStringEx(pXvm, pszItemPath, pszValID, nIndex);

	if (g_pLuaReturnString[0] == 0)
	{
		return 0;
	}
	else
	{
		return atol(g_pLuaReturnString);
	}
}

const char* GBS_GetItemReportValueStringEx(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, long nIndex)
{
	CGbItemBase *pItem = GBS_GetItem(pXvm, pszItemPath);

	if (pItem != NULL)
	{
		//pItem->GetItemReportValue(pszValID, g_pLuaReturnString, nIndex);
		GBS_GetItemReportValue(pXvm, pItem, pszValID, g_pLuaReturnString, nIndex);
	}
	else
	{
		g_pLuaReturnString[0] = 0;
	}

	return g_pLuaReturnString;
}

long GBS_GetItemReportCount(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	CGbItemBase *pItem = GBS_GetItem(pXvm, pszItemPath);

	if (pItem != NULL)
	{
		CReports *pReports = pItem->GetReports();
		return pReports->GetCount();
	}
	else
	{
		return 0;
	}
}

void GBS_ClearReports(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	CGbItemBase *pItem = GBS_GetItem(pXvm, pszItemPath);

	if (pItem == NULL)
	{
		return;
	}

	if (pItem->GetClassID() == GBCLASSID_ITEMS)
	{
		Gb_EmptyReportDatas(pItem);
	}
	else
	{
		pItem->ClearReport(FALSE);
	}
}

void GBS_CalRptValMax(CTScriptSingleVM *pXvm, CExBaseList *pList, const CString &strValID, double &dMax)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = pList->GetNext(pos);
		nClassID = pItem->GetClassID();

		if ((nClassID & GBCLASSID_ITEMSBASE) == GBCLASSID_ITEMSBASE)
		{
			CItems *pItems = (CItems*)pItem;
			GBS_CalRptValMax(pXvm, pItems, strValID, dMax);
		}
		else if ((nClassID & GBCLASSID_ITEMBASE) == GBCLASSID_ITEMBASE)
		{
			CGbItemBase *pItemBase = (CGbItemBase*)pItem;
			pItemBase->CalRptValMax(strValID, dMax);
		}
	}
}


double GBS_CalRptValMax(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dDefVal)
{
	CGbItemBase *pItem = GBS_GetItem(pXvm, pszItemPath);

	if (pItem == NULL)
	{
		return dDefVal;
	}

	CString strValID;
	strValID = pszValID;
	double dMax = dDefVal;

	if (pItem->GetClassID() == GBCLASSID_ITEMS)
	{
		GBS_CalRptValMax(pXvm, pItem, strValID, dMax);
	}
	else
	{
		pItem->CalRptValMax(strValID, dMax);
	}

	return dMax;
}


void GBS_CalRptValMin(CTScriptSingleVM *pXvm, CExBaseList *pList, const CString &strValID, double &dMin)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = pList->GetNext(pos);
		nClassID = pItem->GetClassID();

		if ((nClassID & GBCLASSID_ITEMSBASE) == GBCLASSID_ITEMSBASE)
		{
			CItems *pItems = (CItems*)pItem;
			GBS_CalRptValMin(pXvm, pItems, strValID, dMin);
		}
		else if ((nClassID & GBCLASSID_ITEMBASE) == GBCLASSID_ITEMBASE)
		{
			CGbItemBase *pItemBase = (CGbItemBase*)pItem;
			pItemBase->CalRptValMin(strValID, dMin);
		}
	}
}

double GBS_CalRptValMin(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dDefVal)
{
	CGbItemBase *pItem = GBS_GetItem(pXvm, pszItemPath);

	if (pItem == NULL)
	{
		return dDefVal;
	}

	CString strValID;
	strValID = pszValID;
	double dMin = dDefVal;

	if (pItem->GetClassID() == GBCLASSID_ITEMS)
	{
		GBS_CalRptValMin(pXvm, pItem, strValID, dMin);
	}
	else
	{
		pItem->CalRptValMin(strValID, dMin);
	}

	return dMin;
}


void GBS_CalRptValAvg(CTScriptSingleVM *pXvm, CExBaseList *pList, const CString &strValID, double &dValue, long &nCount)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = pList->GetNext(pos);
		nClassID = pItem->GetClassID();

		if ((nClassID & GBCLASSID_ITEMSBASE) == GBCLASSID_ITEMSBASE)
		{
			CItems *pItems = (CItems*)pItem;
			GBS_CalRptValAvg(pXvm, pItems, strValID, dValue, nCount);
		}
		else if ((nClassID & GBCLASSID_ITEMBASE) == GBCLASSID_ITEMBASE)
		{
			CGbItemBase *pItemBase = (CGbItemBase*)pItem;
			pItemBase->CalRptValSum(strValID, dValue, nCount);
		}
	}
}

double GBS_CalRptValAvg(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dDefVal)
{
	CGbItemBase *pItem = GBS_GetItem(pXvm, pszItemPath);

	if (pItem == NULL)
	{
		return dDefVal;
	}

	CString strValID;
	strValID = pszValID;
	double dValue = 0;
	long nCount = 0;

	if (pItem->GetClassID() == GBCLASSID_ITEMS)
	{
		GBS_CalRptValAvg(pXvm, pItem, strValID, dValue, nCount);
	}
	else
	{
		pItem->CalRptValSum(strValID, dValue, nCount);
	}

	if (nCount == 0)
	{
		return dDefVal;
	}
	else
	{
		return dValue / nCount;
	}
}


//获取满足条件的报告数据的个数
long GBS_LGetItemReportDataCount(CTScriptSingleVM *pXvm, const char* pszItemPath, const char *pszDataID, long nDataValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();
	long nDataCount = 0;

	if (nCount > 1)
	{
		//显示消息，路径检索的项目不唯一
		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format( g_sLangTxt_PathItem.GetString() /*L"路径检索的项目不唯一,Path(%s) select %d items"*/, strPath.GetString(), nCount);
	}
	else if (nCount == 0)
	{
		//显示消息：路径指定的项目不存在
		CString strErrorInfo;
		CString strPath(pszItemPath);
        strErrorInfo.Format( g_sLangTxt_PathItem2.GetString() /*L"路径指定的项目不存在,Path(%s) select %d items"*/, strPath.GetString(), nCount);
	}
	else
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
		nDataCount = pItem->LGetItemReportDataCount(CString(pszDataID), nDataValue);
	}

	oListDest.RemoveAll();
	return nDataCount;
}

double GBS_GetItemReportExValue(CTScriptSingleVM *pXvm, long nIndex, const char* pszValID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;
	double dValue = 0;

	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	dValue = pItem->GetItemReportExValue(nIndex, pszValID);
	
	return dValue;
}


BOOL GBS_GetItemReportExValue(CTScriptSingleVM *pXvm, const char* pszDataID, const char* pszValID, CString &strValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	return pItem->GetItemReportExValue(pszDataID, pszValID, strValue);
}


double GBS_GetItemReportExValue_D(CTScriptSingleVM *pXvm, const char* pszDataID, const char* pszValID)
{
	double dValue = 0;
	CString strValue;

	if (GBS_GetItemReportExValue(pXvm, pszDataID, pszValID, strValue))
	{
#ifdef _UNICODE
		dValue = _wtof(strValue);
#else
        dValue = atof(strValue.GetString());
#endif
	}

	return dValue;
}

long   GBS_GetItemReportExValue_L(CTScriptSingleVM *pXvm, const char* pszDataID, const char* pszValID)
{
	long nValue = 0;
	CString strValue;

	if (GBS_GetItemReportExValue(pXvm, pszDataID, pszValID, strValue))
	{
#ifdef _UNICODE
		nValue = _wtol(strValue);
#else
        nValue = atol(strValue.GetString());
#endif
	}

	return nValue;
}

char*  GBS_GetItemReportExValue_S(CTScriptSingleVM *pXvm, const char* pszDataID, const char* pszValID)
{
	CString strValue;
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer[0] = 0;

	if (GBS_GetItemReportExValue(pXvm, pszDataID, pszValID, strValue))
	{
		CString_to_char(strValue, _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer);
	}

	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
}

char* GBS_GetFileInReportEx(CTScriptSingleVM *pXvm, const char *pszFilePostfix, long nFileIndex)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CReport *pReport = pItem->GetReport(-1);
	g_pLuaReturnString[0] = 0;

	if (pReport == NULL)
	{
		return g_pLuaReturnString;
	}

	POS pos = pReport->m_pRptDvmDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CString strCurr, strFilePostfix;
	strFilePostfix = pszFilePostfix;
	strFilePostfix.MakeLower();
	long nCount = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)pReport->m_pRptDvmDataset->GetNext(pos);

		if (pData->m_strName.GetLength() > 0)
		{
			strCurr = ParseFilePostfix(pData->m_strName);
			strCurr.MakeLower();

			if (strCurr == strFilePostfix)
			{
				if (nCount == nFileIndex)
				{
					CString_to_char(pData->m_strName, g_pLuaReturnString);
					break;
				}

				nCount++;
			}
		}
		else if (pData->m_strID.GetLength() > 0)
		{
			strCurr = ParseFilePostfix(pData->m_strID);
			strCurr.MakeLower();

			if (strCurr == strFilePostfix)
			{
				if (nCount == nFileIndex)
				{
					CString_to_char(pData->m_strName, g_pLuaReturnString);
					break;
				}

				nCount++;
			}
		}
	}

	return g_pLuaReturnString;
}

long GBS_GetFileNumInReportEx(CTScriptSingleVM *pXvm, const char *pszFilePostfix)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CReport *pReport = pItem->GetReport(-1);
	g_pLuaReturnString[0] = 0;

	if (pReport == NULL)
	{
		return 0;
	}

	POS pos = pReport->m_pRptDvmDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CString strCurr, strFilePostfix;
	strFilePostfix = pszFilePostfix;
	strFilePostfix.MakeLower();
	long nCount = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)pReport->m_pRptDvmDataset->GetNext(pos);

		if (pData->m_strName.GetLength() > 0)
		{
			strCurr = ParseFilePostfix(pData->m_strName);
			strCurr.MakeLower();

			if (strCurr == strFilePostfix)
			{
				nCount++;
			}
		}
		else if (pData->m_strID.GetLength() > 0)
		{
			strCurr = ParseFilePostfix(pData->m_strID);
			strCurr.MakeLower();

			if (strCurr == strFilePostfix)
			{
				nCount++;
			}
		}
	}

	return nCount;
}

long GBS_GetItemReportExCount(CTScriptSingleVM *pXvm)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;
	long nCount = 0;

	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	return pItem->GetItemReportExCount();
}


long GBS_GetItemReportExDataCountByID(CTScriptSingleVM *pXvm, const char* pszDataAttrID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CReport *pReport = (CReport*)GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);

	int nDataCount = 0;
	CString strValueID(pszDataAttrID);
	CDvmDataset *pRptDataEx = pReport->m_pRptDvmDataset;
	POS pos = pRptDataEx->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData* oTags = (CDvmData*)pRptDataEx->GetNext(pos);
		//CTag* oTag = oTags->FindByTagIDIcmp(_T("id"));

		//if (oTag != NULL)
		{
			if (oTags->m_strID == strValueID)
			{
				nDataCount++;
			}
		}
	}

	return nDataCount;
}

long GBS_GetItemReportDataIndexByIDIndex(CTScriptSingleVM *pXvm, const char* pszDataAttrID,long nIndex)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CReport *pReport = (CReport*)GBS_GetReport(pXvm, pItem, -1); //pItem->GetReport(-1);

	BOOL bFind = FALSE;
	int nRePortIndex = 0;//报告Index
	int nDataIndex = 0;//数据Index
	int nDataCount = 0;
	int nCount = pReport->m_pRptDvmDataset->GetCount();
	CString strValueID(pszDataAttrID);
	CDvmDataset *pRptDataEx = pReport->m_pRptDvmDataset;
	POS pos = pRptDataEx->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData* oTags = (CDvmData*)pRptDataEx->GetNext(pos);
		//CTag* oTag = oTags->FindByTagIDIcmp(_T("id"));

		//if (oTag != NULL)
		{
			if (oTags->m_strID == strValueID)
			{
				if(nDataIndex == nIndex)
				{
					bFind = TRUE;
					break;
				}

				nDataIndex ++;
			}
		}

		nRePortIndex++;
	}

	if (bFind)
	{
		return nRePortIndex;
	}
	else
	{
		return -1;
	}

}


long GBS_CalTimeGapStr_Span(const char* pszTime1, const char* pszTime2, CGpsPcTimeSpan &ts)
{
	CString strTime1, strTime2;
	CGpsPcTime tm1, tm2;

	strTime1 = pszTime1;
	strTime2 = pszTime2;
	tm1.FromString(strTime1);
	tm2.FromString(strTime2);

	if (tm1 > tm2)
	{
		ts = tm1 - tm2;
	}
	else
	{
		ts = tm2 - tm1;
	}

	return 0;
}


long GBS_CalTimeGapStr(CTScriptSingleVM *pXvm, const char* pszTime1, const char* pszTime2)
{
	CGpsPcTimeSpan ts;
	GBS_CalTimeGapStr_Span(pszTime1, pszTime2, ts);
	long nGap = ts.GetTotalMilliseconds();
	return nGap;
}

long GBS_CalTimeGapStr_us(CTScriptSingleVM *pXvm, const char* pszTime1, const char* pszTime2)
{
	CGpsPcTimeSpan ts;
	GBS_CalTimeGapStr_Span(pszTime1, pszTime2, ts);
	long nGap = ts.GetTotalMicroseconds();

	return nGap;
}

long GBS_CalItemReportTimeGap(CTScriptSingleVM *pXvm, long nItem1Index, long nItem2Index, const char* pszValID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_CalCall.GetString() /*L"CalTmGap只能在通讯命令项目中被调用"*/);
		return -1;
	}

	CReport *pReport = pItem->GetCurrReport();

	if (pReport == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	if (pReport->m_pRptDvmDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	CDvmData* oRpt1 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem1Index);
	CDvmData* oRpt2 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem2Index);

	if (oRpt1 == NULL || oRpt2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	CDvmValue* oData1 = (CDvmValue*)oRpt1->FindByID(CString(pszValID));
	CDvmValue* oData2 = (CDvmValue*)oRpt2->FindByID(CString(pszValID));

	if (oData1 == NULL || oData2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	CGpsPcTime tm1, tm2;
	tm1.FromString(oData1->m_strValue);
	tm2.FromString(oData2->m_strValue);

	CGpsPcTimeSpan ts;
	
	if (tm1 > tm2)
	{
		ts = tm1 - tm2;
	}
	else
	{
		ts = tm2 - tm1;
	}

	return ts.GetTotalMilliseconds();
}

long GBS_CalItemReportTimeGapEx(CTScriptSingleVM *pXvm, long nItem1Index, long nItem2Index, const char* pszValID1, const char *pszValID2)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_CalCall.GetString() /*L"CalTmGap只能在通讯命令项目中被调用"*/);
		return -1;
	}

	CReport *pReport = pItem->GetCurrReport();

	if (pReport == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	if (pReport->m_pRptDvmDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	CDvmData* oRpt1 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem1Index);
	CDvmData* oRpt2 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem2Index);

	if (oRpt1 == NULL || oRpt2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	CDvmValue* oData1 = (CDvmValue*)oRpt1->FindByID(CString(pszValID1));
	CDvmValue* oData2 = (CDvmValue*)oRpt2->FindByID(CString(pszValID2));

	if (oData1 == NULL || oData2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	CGpsPcTime tm1, tm2;
	tm1.FromString(oData1->m_strValue);
	tm2.FromString(oData2->m_strValue);
	long nFlag = 1;

	CGpsPcTimeSpan ts;

	if (tm1 > tm2)
	{
		ts = tm1 - tm2;
	}
	else
	{
		ts = tm2 - tm1;
		nFlag = -1;
	}

	long nMs = ts.GetTotalMilliseconds();
	nMs *= nFlag;
	return nMs;
}

long GBS_CalItemReportTimeGapEx2(CTScriptSingleVM *pXvm, long nItem1Index, long nItem2Index, long nValIndex1, long nValIndex2)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_CalCall.GetString() /*L"CalTmGap只能在通讯命令项目中被调用"*/);
		return 0;
	}

	CReport *pReport = pItem->GetCurrReport();

	if (pReport == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return 0;
	}

	if (pReport->m_pRptDvmDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return 0;
	}

	CDvmData* oRpt1 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem1Index);
	CDvmData* oRpt2 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem2Index);

	if (oRpt1 == NULL || oRpt2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return 0;
	}

	CDvmValue* oData1 = (CDvmValue*)oRpt1->GetAtIndex(nValIndex1);
	CDvmValue* oData2 = (CDvmValue*)oRpt2->GetAtIndex(nValIndex2);

	if (oData1 == NULL || oData2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NoDataReport2.GetString() /*L"CalTmGap:没有报告数据"*/);
		return 0;
	}

	CGpsPcTime tm1, tm2;
	tm1.FromString(oData1->m_strValue);
	tm2.FromString(oData2->m_strValue);
	long nFlag = 1;

	CGpsPcTimeSpan ts;

	if (tm1 > tm2)
	{
		ts = tm1 - tm2;
	}
	else
	{
		ts = tm2 - tm1;
		nFlag = -1;
	}

	long nMs = ts.GetTotalMilliseconds();
	nMs *= nFlag;
	return nMs;
}

//报告过滤
void GBS_FilterInit(LPVOID pData)
{
	CTScriptSingleVM *pXvm = (CTScriptSingleVM *)pData;
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CDvmDataset* pReportEx = GBS_GetItemReportDataEx(pXvm);

	if (pReportEx != NULL)
	{
		pList->RemoveAll();
		pList->Append(pReportEx);
	}
}

long GBS_FilterReportExEqualValueL(CTScriptSingleVM *pXvm, const char* pszDataAttrID, long nAttrValue)
{
	char pszAttrValue[20];
	sprintf(pszAttrValue, "%d", nAttrValue);
	return GBS_FilterReportExEqualValueStr(pXvm, pszDataAttrID, pszAttrValue);
}

//新增CDvmDatasetGroup之后，g_pGbScriptGlobalDefine->m_oListRptExFilter的子对象就不一定是CDvmData了，故此修改
//shaolei 2021-12-04
long GBS_FilterReportExEqualValueStr(CTScriptSingleVM *pXvm, const char* pszDataAttrID, const char* pszValue)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CExBaseList oListDest;
	CDvmData *pData = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	//CTag *pAttr = NULL;
	CString strTagID(pszDataAttrID);
	CString strValue(pszValue);
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pList->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			pData = (CDvmData *)pObj;

		if (pData->HasValueEx(strTagID, strValue))
		{
			oListDest.AddTail(pData);
				continue;
	 		}
			//判断子对象是否有strTagID == strValue的，若有，返回子对象
			CDvmValue *pValue = pData->HasValueEx_Child(strTagID, strValue);

			if(pValue != NULL)
			{
				CDvmData *pNew = new CDvmData();
				pNew->m_strValue = pValue->m_strValue;
				pNew->m_strDataType = pValue->m_strDataType;
				pNew->m_strID = pValue->m_strID;
				pNew->m_strName = pValue->m_strName;
				oListDest.AddTail(pNew);
			}
		}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup*)pObj;
			pDatasetGroup->FilterDataExEqualValueStr(oListDest, strTagID, strValue);
		}
	}

// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pList->GetNext(pos);
// 		//pAttr = pData->FindByTagID(strTagID);
// 
// 		//if (pAttr != NULL)
// 		if (pData->HasValueEx(strTagID, strValue))
// 			{
// 				oListDest.AddTail(pData);
// // 			if (pAttr->m_strValue == strValue)
// // 			{
// // 				oListDest.AddTail(pData);
// // 			}
// 		}
// 			}

	if (g_nLog_TestControl_Msg == 1)
	{
		CString strMsg;
        strMsg.Format(_T("Filter(%s # %s) %d=>%d"), strTagID.GetString(), strValue.GetString(), pList->GetCount(), oListDest.GetCount());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
	}

	pList->RemoveAll();
	pList->Append(oListDest);
	oListDest.RemoveAll();
	return pList->GetCount();
}

long GBS_FilterReportExHasValueStr(CTScriptSingleVM *pXvm, const char* pszDataAttrID, const char* pszValue)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CExBaseList oListDest;
	CDvmData *pData = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	//CTag *pAttr = NULL;
	CString strTagID(pszDataAttrID);
	CString strValue(pszValue);
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pList->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			pData = (CDvmData *)pObj;

		if (pData->HasValueHasStr(strTagID, strValue))
		{
			oListDest.AddTail(pData);
				continue;
			}
			//判断子对象是否有strTagID 包含 strValue的，若有，返回子对象
			CDvmValue *pValue = pData->HasValueHasStr_Child(strTagID, strValue);

			if(pValue != NULL)
			{
				CDvmData *pNew = new CDvmData();
				pNew->m_strValue = pValue->m_strValue;
				pNew->m_strDataType = pValue->m_strDataType;
				pNew->m_strID = pValue->m_strID;
				pNew->m_strName = pValue->m_strName;
				oListDest.AddTail(pNew);
			}
		}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup*)pObj;
			pDatasetGroup->FilterDataExHasValueStr(oListDest, strTagID, strValue);
		}
	}

// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData*)pList->GetNext(pos);
// 		//pAttr = pData->FindByTagID(strTagID);
// 
// 		//if (pAttr != NULL)
// 		if (pData->HasValueHasStr(strTagID, strValue))
// 			{
// 				oListDest.AddTail(pData);
// // 			if (pAttr->m_strValue.Find(strValue) >= 0)
// // 			{
// // 				oListDest.AddTail(pData);
// // 			}
// 		}
// 			}

	if (g_nLog_TestControl_Msg == 1)
	{
		CString strMsg;
        strMsg.Format(_T("Filter(%s # %s) %d=>%d"), strTagID.GetString(), strValue.GetString(), pList->GetCount(), oListDest.GetCount());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
	}

	pList->RemoveAll();
	pList->Append(oListDest);
	oListDest.RemoveAll();
	return pList->GetCount();
}

long GBS_FilterReportExHasNoValueStr(CTScriptSingleVM *pXvm, const char* pszDataAttrID, const char* pszValue)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CExBaseList oListDest;
	CDvmData *pData = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	//CTag *pAttr = NULL;
	CString strTagID(pszDataAttrID);
	CString strValue(pszValue);
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pList->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			pData = (CDvmData *)pObj;

		if (pData->HasValueHasNoStr(strTagID, strValue))
		{
			oListDest.AddTail(pData);
				continue;
			}
			//判断子对象是否有strTagID 包含 strValue的，若有，返回子对象
			CDvmValue *pValue = pData->HasValueHasNoStr_Child(strTagID, strValue);

			if(pValue != NULL)
			{
				CDvmData *pNew = new CDvmData();
				pNew->m_strValue = pValue->m_strValue;
				pNew->m_strDataType = pValue->m_strDataType;
				pNew->m_strID = pValue->m_strID;
				pNew->m_strName = pValue->m_strName;
				oListDest.AddTail(pNew);
			}
		}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup*)pObj;
			pDatasetGroup->FilterDataExHasNoValueStr(oListDest, strTagID, strValue);
		}
	}

// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData*)pList->GetNext(pos);
// 		//pAttr = pData->FindByTagID(strTagID);
// 
// 		//if (pAttr != NULL)
// 		if (pData->HasValueHasNoStr(strTagID, strValue))
// 			{
// 				oListDest.AddTail(pData);
// // 			if (pAttr->m_strValue.Find(strValue) < 0)
// // 			{
// // 				oListDest.AddTail(pData);
// // 			}
// 		}
// 			}

	if (g_nLog_TestControl_Msg == 1)
	{
		CString strMsg;
        strMsg.Format(_T("Filter(%s # %s) %d=>%d"), strTagID.GetString(), strValue.GetString(), pList->GetCount(), oListDest.GetCount());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
	}

	pList->RemoveAll();
	pList->Append(oListDest);
	oListDest.RemoveAll();
	return pList->GetCount();
}

void GBS_FilterCombineReportEx(CTScriptSingleVM *pXvm, const char* pszDataAttrID, const char* pszRptDataID, const char* pszSeparator)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CValues *pValues = GBS_GetItemReportValues(pXvm);

	if (pValues == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_NullDataReport.GetString() /*_T("FilterCombineReportEx函数：报告数据为空")*/);
		return;
	}

	CDvmData *pData = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	//CTag *pAttr = NULL;
	CString strTagID(pszDataAttrID);
	CString strValues;
	CString strValue;
	CString strSeparator(pszSeparator);
	POS pos = pList->GetHeadPosition();
	strSeparator.Trim();

	if (strSeparator.GetLength() == 0)
	{
		strSeparator = _T(";");
	}

	while (pos != NULL)
	{
		pObj = pList->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			pData = (CDvmData *)pObj;

		if (pData->GetValueByID(strTagID, strValue))
		{
            strValues.AppendFormat(_T("%s%s"), strValue.GetString(), strSeparator.GetString());
		}
	}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup*)pObj;
			pDatasetGroup->FilterCombineDataEx(strValues, strTagID, strSeparator);
		}
	}

// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData*)pList->GetNext(pos);
// 		//pAttr = pData->FindByTagID(strTagID);
// 
// 		//if (pAttr != NULL)
// 		if (pData->GetValueByID(strTagID, strValue))
// 		{
//             strValues.AppendFormat(_T("%s%s"), strValue.GetString(), strSeparator.GetString());
// 		}
// 	}

	CString strDataID(pszRptDataID);
	CValue *pValue = (CValue*)pValues->FindByID(strDataID);

	if (g_nLog_TestControl_Msg == 1)
	{
		CString strMsg;
        strMsg.Format(_T("FilterComb( %d ) (%s)"), pList->GetCount(), strValues.GetString());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
	}

	if (pValue != NULL)
	{
		pValue->m_strValue = strValues;
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_DataReportID.GetString() /*_T("不存在ID为\"%s\"的报告数据")*/, strDataID.GetString());
	}
}

CEquationBuffer g_oEquationBuffer;

BOOL GBS_FilterRptExQueryData(CTScriptSingleVM *pXvm, CDvmData *pData)
{
	POS pos = g_oEquationBuffer.GetHeadPosition();
	CEquationKey *pKey = NULL;
	BOOL bTrue = TRUE;
	//CTag *pTag = NULL;
	CString strValue;

	while (pos != NULL)
	{
		pKey = (CEquationKey*)g_oEquationBuffer.GetNext(pos);
		//pTag = pData->FindByTagID(pKey->GetKeyName());
		strValue = pKey->GetKeyValue();

		//if (pTag == NULL)
		if (pData->HasValueHasStr(pKey->GetKeyName(), pKey->GetKeyValue()))
		{
		}
		else
		{
			bTrue = FALSE;
			break;
		}

// 		if (pTag->m_strValue.Find( pKey->GetKeyValue() ) < 0)
// 		{
// 			bTrue = FALSE;
// 			break;
// 		}
	}

	return bTrue;
}

void GBS_FilterRptExQueryDataGroup(CTScriptSingleVM *pXvm, CDvmDatasetGroup *pDatasetGroup, CExBaseList &oDestList)
{
	POS pos = pDatasetGroup->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pDatasetGroup->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;

			if (GBS_FilterRptExQueryData(pXvm, pData))
			{
				oDestList.AddTail(pData);
			}
		}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pGroup = (CDvmDatasetGroup *)pObj;
			GBS_FilterRptExQueryDataGroup(pXvm, pDatasetGroup, oDestList);
		}
	}
}

long GBS_FilterRptExQuery(CTScriptSingleVM *pXvm, const char* pszQuery)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;

	if (strlen(pszQuery) < 3)
	{
		GBS_FilterInit(pXvm);
		return pList->GetCount();
	}

	g_oEquationBuffer.DeleteAll();
	long nEnd = strlen(pszQuery);
	const char *pEnd = pszQuery + nEnd;
	g_oEquationBuffer.InitBuffer(pszQuery, pEnd);

	CDvmData *pData = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	POS pos = pList->GetHeadPosition();
	long nIndex = 0, nIndexFind = 0;
	CExBaseList oList;

	while (pos != NULL)
	{
		pObj = pList->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
	 		pData = (CDvmData *)pObj;
	 
		if (GBS_FilterRptExQueryData(pXvm, pData))
		{
			oList.AddTail(pData);
		}
	}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup *)pObj;
			GBS_FilterRptExQueryDataGroup(pXvm, pDatasetGroup, oList);
		}
	}

// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pList->GetNext(pos);
// 
// 		if (GBS_FilterRptExQueryData(pXvm, pData))
// 		{
// 			oList.AddTail(pData);
// 		}
// 	}

	pList->RemoveAll();
	pList->Append(oList);
	oList.RemoveAll();

	return pList->GetCount();
}

long GBS_FilterRptExGetCount(CTScriptSingleVM *pXvm)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	return pList->GetCount();
}

long GBS_FilterRptExGetLong(CTScriptSingleVM *pXvm, long nIndex, const char* pszDataAttrID)
{
	char *pValue = GBS_FilterRptExGetString(pXvm, nIndex, pszDataAttrID);

	return atol(pValue);
}

char* GBS_FilterRptExGetString(CTScriptSingleVM *pXvm, long nIndex, const char* pszDataAttrID)
{
	if (g_nLog_TestControl_Msg == 1)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "FilterRptExGetString(%d, %s)", nIndex, pszDataAttrID);
	}

	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CDvmData *pData = NULL;
	strcpy(g_pLuaReturnString, "");
	pData = (CDvmData*)pList->GetAtIndex(nIndex);
	BOOL bFind = FALSE;
	CString strValue;

	if (pData != NULL)
	{
		if (IsStringNumber(pszDataAttrID))
		{
			long nValIndex = atol(pszDataAttrID);
			CDvmValue *pValue = (CDvmValue*)pData->GetAtIndex(nValIndex);

			if (pValue != NULL)
			{
				CString_to_char(pValue->m_strValue, g_pLuaReturnString);
				bFind = TRUE;
			}
		}
		else
		{
			if (pData->GetValueByID(CString(pszDataAttrID), strValue))
			{
				CString_to_char(strValue, g_pLuaReturnString);
				bFind = TRUE;
			}
		}
	}

	return g_pLuaReturnString;
}

double GBS_FilterRptExGetDouble(CTScriptSingleVM *pXvm, long nIndex, const char* pszDataAttrID)
{
	char *pValue = GBS_FilterRptExGetString(pXvm, nIndex, pszDataAttrID);

	return atof(pValue);
}

long GBS_FilterRptExGetValCount(CTScriptSingleVM *pXvm, long nDataIndex)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CDvmData *pData = NULL;
	pData = (CDvmData*)pList->GetAtIndex(nDataIndex);

	if (pData != NULL)
	{
		return pData->GetCount();
	}
	else
	{
		return 0;
	}
}


long GBS_FilterRptExGetValLong(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValIndex)
{
	char *pValue = GBS_FilterRptExGetString(pXvm, nDataIndex, pszValIndex);

	return atol(pValue);
}

CDvmValue* GBS_FilterRptExGetDvmValue(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValIndex)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CDvmData *pData = NULL;
	pData = (CDvmData*)pList->GetAtIndex(nDataIndex);
	CDvmValue *pDvmValue = NULL;

	if (pData != NULL)
	{
		if (IsStringNumber(pszValIndex))
		{
			long nValIndex = atol(pszValIndex);
			pDvmValue = (CDvmValue *)pData->GetAtIndex(nValIndex);
		}
		else
		{
			CString strValID;
			strValID = pszValIndex;
			pDvmValue = (CDvmValue *)pData->FindByID(strValID);
		}
	}

	return pDvmValue;
}

char* GBS_FilterRptExGetValString(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValIndex)
{
	CDvmValue *pDvmValue = GBS_FilterRptExGetDvmValue(pXvm, nDataIndex, pszValIndex);
	g_pLuaReturnString[0] = '0';
	g_pLuaReturnString[1] = 0;
	g_pLuaReturnString[2] = 0;
	CString strValue;

	if (!pDvmValue)
	{
	}
	else
	{
		CString_to_char(pDvmValue->m_strValue, g_pLuaReturnString);
	}

	return g_pLuaReturnString;
}

double GBS_FilterRptExGetValDouble(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValIndex)
{
	char *pValue = GBS_FilterRptExGetString(pXvm, nDataIndex, pszValIndex);

	return atof(pValue);
}

long GBS_FilterRptExCalValError(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValIndex, double dRefVal, double dAbsErr, double dRelErr)
{
	CDvmValue *pDvmValue = GBS_FilterRptExGetDvmValue(pXvm, nDataIndex, pszValIndex);

	if (pDvmValue == NULL)
	{
		return 0;
	}

#ifdef _UNICODE
	double dValue = _wtof(pDvmValue->m_strValue);
#else
    double dValue = atof(pDvmValue->m_strValue.GetString());
#endif
	double dValErrAbs = fabs(dValue - dRefVal);
	double dValErrRel = dValErrAbs;

	if (fabs(dRefVal) > 0.0001)
	{
		dValErrRel /= dRefVal;
	}

	return (dValErrAbs < dAbsErr || dValErrRel < dRelErr);
}

long GBS_FilterRptExCalValErrorEx(CTScriptSingleVM *pXvm, const char *pszDataID, const char *pszValID, double dRefVal, double dAbsErr, double dRelErr)
{
	CDvmDataset* pReportEx = GBS_GetItemReportDataEx(pXvm);
	CDvmValue *pValue = NULL;
	CDvmValue *p = NULL;
	CString strDataID, strValueID;
	strDataID = pszDataID;
	strValueID = pszValID;

	CDvmData *pDataFind = (CDvmData*)pReportEx->FindByID(strDataID);

	if (pDataFind == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DataUnExist2.GetString() /*_T("数据【%s】不存在")*/, strDataID.GetString());
		return 0;
	}

	pValue = (CDvmValue *)pDataFind->FindByID(strValueID);

	if (pValue == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DataUnExist3.GetString() /*_T("数据值【%s】不存在")*/, strValueID.GetString());
		return 0;
	}

	double dValue = CString_To_double(pValue->m_strValue);
	double dAbsCal, dRelCal;

	math_CalError(dValue, dRefVal, dAbsCal, dRelCal,FALSE);

	long nRsltJdg = math_CalIsInError(dAbsCal, dRelCal, dAbsErr, dRelErr);

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  ,AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d")
			, dValue, dRefVal, dAbsCal, dRelCal, dAbsErr, dRelErr, nRsltJdg);
	}

	return nRsltJdg;
}

CDvmData* Gbs_FilterRptExQueryMaxErr(CTScriptSingleVM *pXvm, CExBaseList &listDatas, const CString &strAttrID, double dStand, long nWriteDs, double &dValue, CValues *pReportValues)
{
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;
	POS pos = listDatas.GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmValue *pValueFind = NULL;
	double dErrorMax = 0;
	double dError = 0;
	double dTemp = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)listDatas.GetNext(pos);
		pValue = pData->FindValueByID(strAttrID);

		if (pValue == NULL)
		{
			continue;
		}

		dTemp = CString_To_double(pValue->m_strValue);
		dError = fabs(dTemp - dStand);

		if (dError >= dErrorMax)
		{
			dValue = dTemp;
			pFind = pData;
			dErrorMax = dError;
			pValueFind = pValue;
		}
	}

	if (pFind == NULL)
	{
		return pFind;
	}
	
	if (nWriteDs != 0)
	{
		CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
		CDevice *pDevice = (CDevice *)pItem->GetAncestor(GBCLASSID_DEVICE);
		ASSERT (pDevice != NULL);
		CDataObj *pDataDm = pDevice->FindDataObjByID(pFind->m_strID, -1);
		
		if (pDataDm != NULL)
		{
			CDataObjValue *pValueDm = pDataDm->FindValue(strAttrID);

			if (pValueDm != NULL)
			{
				ASSERT (pValueFind != NULL);
				pValueDm->m_strValue = pValueFind->m_strValue;
			}
		}
	}

	//if (pReportValues->FindByID(pFind->m_strID) == NULL)
	{
		Gb_AddToRptValues(pFind, pReportValues, strAttrID);
	}
	
// 	ASSERT (pValueFind != NULL);
// 	CValue *pReportValue = (CValue*)pReportValues->FindByID(pValueFind->m_strID);
// 
// 	if (pReportValue == NULL)
// 	{
// 		Gb_AddToRptValues(pValueFind, pReportValues, strAttrID);
// 	}
// 	else
// 	{
// 		pReportValue->m_strValue  = pValueFind->m_strValue;
// 	}

	return pFind;
}

CDvmData* Gbs_FilterRptExQueryMaxErr(CTScriptSingleVM *pXvm, CExBaseList &listDatas, const CString &strAttrID1, const CString &strAttrID2, const CString &strOptr, double dStand, long nWriteDs, double &dValue, CValues *pReportValues)
{
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;
	POS pos = listDatas.GetHeadPosition();
	CDvmValue *pValue1 = NULL, *pValue2 = NULL;
	CDvmValue *pValueFind = NULL;
	double dErrorMax = 0;
	double dError = 0;
	double dTemp1 = 0, dTemp2 = 0, dTemp=0;

	while (pos != NULL)
	{
		pData = (CDvmData *)listDatas.GetNext(pos);
		pValue1 = pData->FindValueByID(strAttrID1);
		pValue2 = pData->FindValueByID(strAttrID2);

		if (pValue1 == NULL || pValue2 == NULL)
		{
			continue;
		}

		dTemp1 = CString_To_double(pValue1->m_strValue);
		dTemp2 = CString_To_double(pValue2->m_strValue);
		dTemp = dTemp1 / dTemp2;

		//在此暂时不判断符号，缺省为“除”
		//if (strOptr == _T(""))
		dError = fabs(dTemp - dStand);

		if (dError >= dErrorMax)
		{
			dValue = dTemp;
			pFind = pData;
			dErrorMax = dError;
			pValueFind = pValue1;
		}
	}

	if (pFind == NULL)
	{
		return pFind;
	}

	if (nWriteDs != 0)
	{
		CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
		CDevice *pDevice = (CDevice *)pItem->GetAncestor(GBCLASSID_DEVICE);
		ASSERT (pDevice != NULL);
		CDataObj *pDataDm = pDevice->FindDataObjByID(pFind->m_strID, -1);

		if (pDataDm != NULL)
		{
			CDataObjValue *pValueDm = pDataDm->FindValue(strAttrID1);

			if (pValueDm != NULL)
			{
				pValueDm->m_strValue = pValue1->m_strValue;
			}

			pValueDm = pDataDm->FindValue(strAttrID2);

			if (pValueDm != NULL)
			{
				pValueDm->m_strValue = pValue2->m_strValue;
			}
		}
	}

	//if (pReportValues->FindByID(pFind->m_strID) == NULL)
	{
		Gb_AddToRptValues(pFind, pReportValues, strAttrID1);
		Gb_AddToRptValues(pFind, pReportValues, strAttrID2);
	}

// 	ASSERT (pValueFind != NULL);
// 	CValue *pReportValue = (CValue*)pReportValues->FindByID(pValueFind->m_strID);
// 
// 	if (pReportValue == NULL)
// 	{
// 		Gb_AddToRptValues(pValueFind, pReportValues);
// 	}
// 	else
// 	{
// 		pReportValue->m_strValue  = pValueFind->m_strValue;
// 	}

	return pFind;
}

CDvmData* Gbs_FilterRptExQueryMaxErr(CTScriptSingleVM *pXvm, CExBaseList &listDatas, double dStand, long nWriteDs, double &dValue, CValues *pReportValues)
{
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;
	POS pos = listDatas.GetHeadPosition();
	double dErrorMax = 0;
	double dError = 0;
	double dTemp = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)listDatas.GetNext(pos);
		dTemp = CString_To_double(pData->m_strValue);
		dError = fabs(dTemp - dStand);

		if (dError >= dErrorMax)
		{
			dValue = dTemp;
			pFind = pData;
			dErrorMax = dError;
		}
	}

	if (pFind == NULL)
	{
		return pFind;
	}
	
	if (nWriteDs != 0)
	{
		CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
		CDevice *pDevice = (CDevice *)pItem->GetAncestor(GBCLASSID_DEVICE);
		ASSERT (pDevice != NULL);
		CDataObj *pDataDm = pDevice->FindDataObjByID(pFind->m_strID, -1);

		if (pDataDm != NULL)
		{
			pDataDm->m_strValue = pFind->m_strValue;
		}
	}

	CValue *pReportValue = (CValue*)pReportValues->FindByID(pFind->m_strID) ;

	if (pReportValue == NULL)
	{
		Gb_AddToRptValues(pFind, pReportValues);
	}
	else
	{
		pReportValue->m_strValue = pFind->m_strValue;
	}

	return pFind;
}


void Gbs_FilterRptExQueryByDataID(CTScriptSingleVM *pXvm, const char *pszDataID, long nMaxCount, CExBaseList &listDatas)
{
#ifdef GUIDEBOOK_DEV_MODE
#else
	CReport *pReport = GBS_GetItemReport(pXvm);
	CDvmDataset* pReportEx = pReport->m_pRptDvmDataset;
	CValues *pValues = pReport->m_pValues;
	POS pos = pReportEx->GetTailPosition();
	CDvmData *pData = NULL;
	long nIndex = 0;
	CString strDataID;
	strDataID = pszDataID;
	long nFilterSoeQueryAll = CTCtrlCntrConfig::GetFilterSoeQueryAll();

	if (nMaxCount <= 0)
	{
		nMaxCount = 6;
	}

	//根据数据ID检索出所需要的数据
	while (pos != NULL)
	{
		pData = (CDvmData *)pReportEx->GetPrev(pos);

		if (pData->m_strID == strDataID)
		{
			pData->m_dwReserved = RPTEX_QUERY_FLAG_VAL;
			nIndex++;

			if (nIndex > nMaxCount)
			{
				if (nFilterSoeQueryAll == 0)
				{
					break;
				}
			}
			else
			{
				listDatas.AddTail(pData);
			}
		}
	}
#endif
}

double Gbs_FilterRptExQueryUseErr(CTScriptSingleVM *pXvm, const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs)
{
	CExBaseList listDatas;
	Gbs_FilterRptExQueryByDataID(pXvm, pszDataID, nMaxCount, listDatas);

	CReport *pReport = GBS_GetItemReport(pXvm);
 	CValues *pValues = pReport->m_pValues;
 	CDvmData *pData = NULL;
	CString strAttrID, strDataID;
	strAttrID = pszAttrID;
	strDataID = pszDataID;
	double dDataValue  = -9999999;
	CDvmValue *pValueFind = NULL;

	if (strAttrID.GetLength() > 0)
	{
		pData = Gbs_FilterRptExQueryMaxErr(pXvm, listDatas, strAttrID, dStand, nWriteDs, dDataValue, pValues);
	}
	else
	{
		pData = Gbs_FilterRptExQueryMaxErr(pXvm, listDatas, dStand, nWriteDs, dDataValue, pValues);
	}

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Report Query(DataID=[%s] AttrID=[%s] error"), strDataID.GetString(), strAttrID.GetString());
	}

	listDatas.RemoveAll();

	return dDataValue;
}

double Gbs_FilterRptExQueryUseErrEx(CTScriptSingleVM *pXvm, const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs)
{
	CExBaseList listDatas;
	Gbs_FilterRptExQueryByDataID(pXvm, pszDataID, nMaxCount, listDatas);

	CReport *pReport = GBS_GetItemReport(pXvm);
	CValues *pValues = pReport->m_pValues;
	CDvmData *pData = NULL;
	CString strAttrID1, strAttrID2, strDataID, strOptr;
	strAttrID1 = pszAttrID1;
	strAttrID2 = pszAttrID2;
	strDataID = pszDataID;
	strOptr = pszOptr;
	double dDataValue  = -9999999;
	CDvmValue *pValueFind = NULL;

	if (strAttrID1.GetLength() > 0 && strAttrID2.GetLength() > 0)
	{
		pData = Gbs_FilterRptExQueryMaxErr(pXvm, listDatas, strAttrID1, strAttrID2, strOptr, dStand, nWriteDs, dDataValue, pValues);
	}
	else
	{
		pData = Gbs_FilterRptExQueryMaxErr(pXvm, listDatas, dStand, nWriteDs, dDataValue, pValues);
	}

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Report Query(DataID=[%s] AttrID1=[%s]  AttrID2=[%s] error"), strDataID.GetString(), strAttrID1.GetString(), strAttrID2.GetString());
	}

	listDatas.RemoveAll();

	return dDataValue;
}

//////////////////////////////////////////////////////////////////////////
//Avg
CDvmData* Gbs_FilterRptExQueryAvg(CTScriptSingleVM *pXvm, CExBaseList &listDatas, const CString &strAttrID, CDvmData &oDestData, double &dValue, CValues *pReportValues)
{
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;
	POS pos = listDatas.GetHeadPosition();
	CDvmValue *pValue = NULL;
	CDvmValue *pValueFind = NULL;
	double dCalSum = 0;
	double dError = 0;
	double dTemp = 0;
	long nCount = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)listDatas.GetNext(pos);
		pValue = pData->FindValueByID(strAttrID);

		if (pValue == NULL)
		{
			continue;
		}

		nCount++;
		pFind = pData;
		dTemp = CString_To_double(pValue->m_strValue);
		dCalSum += dTemp;
	}

	if (pFind == NULL)
	{
		return pFind;
	}

	if (nCount > 0)
	{
		dCalSum /= nCount;
	}

	dValue = dCalSum;

	pFind->Copy(&oDestData);
	CString strValue;
	strValue.Format(_T("%f"), dValue);
	oDestData.SetAttr(strAttrID, strValue);
	Gb_AddToRptValues(&oDestData, pReportValues, strAttrID);

	return &oDestData;
}

CDvmData* Gbs_FilterRptExQueryAvg(CTScriptSingleVM *pXvm, CExBaseList &listDatas, const CString &strAttrID1, const CString &strAttrID2, const CString &strOptr, CDvmData &oDestData, double &dValue, CValues *pReportValues)
{
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;
	POS pos = listDatas.GetHeadPosition();
	CDvmValue *pValue1 = NULL, *pValue2 = NULL;
	CDvmValue *pValueFind = NULL;
	double dCalSum = 0, dCalSum1 = 0, dCalSum2 = 0;
	double dError = 0;
	double dTemp1 = 0, dTemp2 = 0, dTemp=0;
	long nCount = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)listDatas.GetNext(pos);
		pValue1 = pData->FindValueByID(strAttrID1);
		pValue2 = pData->FindValueByID(strAttrID2);

		if (pValue1 == NULL || pValue2 == NULL)
		{
			continue;
		}

		nCount++;
		dTemp1 = CString_To_double(pValue1->m_strValue);
		dTemp2 = CString_To_double(pValue2->m_strValue);

		if (math_IsEqual(dTemp2, 0) )
		{
			dTemp = 0;
		}
		else
		{
			dTemp = dTemp1 / dTemp2;
		}

		//在此暂时不判断符号，缺省为“除”
		//if (strOptr == _T(""))
		dCalSum += dTemp;
		dCalSum1 += dTemp1;
		dCalSum2 += dTemp2;
		pFind = pData;
	}

	if (pFind == NULL)
	{
		return pFind;
	}

	if (nCount > 0)
	{
		dCalSum1 /= nCount;
		dCalSum2 /= nCount;
		dCalSum /= nCount;
	}

	dValue = dCalSum;
	pFind->Copy(&oDestData);
	CString strValue;
	strValue.Format(_T("%f"), dCalSum1);
	oDestData.SetAttr(strAttrID1, strValue);
	strValue.Format(_T("%f"), dCalSum2);
	oDestData.SetAttr(strAttrID2, strValue);

	Gb_AddToRptValues(&oDestData, pReportValues, strAttrID1);
	Gb_AddToRptValues(&oDestData, pReportValues, strAttrID2);

	return &oDestData;
}

CDvmData* Gbs_FilterRptExQueryAvg(CTScriptSingleVM *pXvm, CExBaseList &listDatas, CDvmData &oDestData, double &dValue, CValues *pReportValues)
{
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;
	POS pos = listDatas.GetHeadPosition();
	double dCalSunm = 0;
	long nCount = 0;
	double dError = 0;
	double dTemp = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)listDatas.GetNext(pos);
		dTemp = CString_To_double(pData->m_strValue);
		dCalSunm += dTemp;
		pFind = pData;
		nCount++;
	}

	if (pFind == NULL)
	{
		return pFind;
	}

	dCalSunm /= nCount;
	CString strValue;
	strValue.Format(_T("%f"), dCalSunm);
	CValue *pReportValue = (CValue*)pReportValues->FindByID(pFind->m_strID);
	pFind->Copy(&oDestData);
	oDestData.m_strValue = strValue;

	if (pReportValue == NULL)
	{
		Gb_AddToRptValues(&oDestData, pReportValues);
	}
	else
	{
		pReportValue->m_strValue = strValue;
	}

	return &oDestData;
}

double Gbs_FilterRptExQueryUseAvg(CTScriptSingleVM *pXvm, const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs)
{
	CExBaseList listDatas;
	Gbs_FilterRptExQueryByDataID(pXvm, pszDataID, nMaxCount, listDatas);

	CReport *pReport = GBS_GetItemReport(pXvm);
	CValues *pValues = pReport->m_pValues;
	CDvmData *pData = NULL;
	CString strAttrID, strDataID;
	strAttrID = pszAttrID;
	strDataID = pszDataID;
	double dDataValue  = -9999999;
	CDvmValue *pValueFind = NULL;
	CDvmData oDestData;

	if (strAttrID.GetLength() > 0)
	{
		pData = Gbs_FilterRptExQueryAvg(pXvm, listDatas, strAttrID, oDestData, dDataValue, pValues);
	}
	else
	{
		pData = Gbs_FilterRptExQueryAvg(pXvm, listDatas, oDestData, dDataValue, pValues);
	}

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Report Query(DataID=[%s] AttrID=[%s] error"), strDataID.GetString(), strAttrID.GetString());
	}

	listDatas.RemoveAll();

	return dDataValue;
}

double Gbs_FilterRptExQueryUseAvgEx(CTScriptSingleVM *pXvm, const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs)
{
	CExBaseList listDatas;
	Gbs_FilterRptExQueryByDataID(pXvm, pszDataID, nMaxCount, listDatas);

	CReport *pReport = GBS_GetItemReport(pXvm);
	CValues *pValues = pReport->m_pValues;
	CDvmData *pData = NULL;
	CString strAttrID1, strAttrID2, strDataID, strOptr;
	strAttrID1 = pszAttrID1;
	strAttrID2 = pszAttrID2;
	strDataID = pszDataID;
	strOptr = pszOptr;
	double dDataValue  = -9999999;
	CDvmValue *pValueFind = NULL;
	CDvmData oDestData;

	if (strAttrID1.GetLength() > 0 && strAttrID2.GetLength() > 0)
	{
		pData = Gbs_FilterRptExQueryAvg(pXvm, listDatas, strAttrID1, strAttrID2, strOptr, oDestData, dDataValue, pValues);
	}
	else
	{
		pData = Gbs_FilterRptExQueryAvg(pXvm, listDatas, oDestData, dDataValue, pValues);
	}

	if (pData == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Report Query(DataID=[%s] AttrID1=[%s]  AttrID2=[%s] error"), strDataID.GetString(), strAttrID1.GetString(), strAttrID2.GetString());
	}

	listDatas.RemoveAll();

	return dDataValue;
}

long Gbs_FilterRptExQueryClearNotUse(CTScriptSingleVM *pXvm)
{
	CDvmDataset* pReportEx = GBS_GetItemReportDataEx(pXvm);
	return pReportEx->ClearByReserved(RPTEX_QUERY_FLAG_VAL);
// 	CExBaseList listDatas;
// 	POS pos = pReportEx->GetHeadPosition();
// 	POS posPrev = NULL;
// 	CDvmData *pData = NULL;
// 	long nDelCount = 0;
// 
// 	while (pos != NULL)
// 	{
// 		posPrev = pos;
// 		pData = (CDvmData *)pReportEx->GetNext(pos);
// 
// 		if (pData->m_dwReserved != RPTEX_QUERY_FLAG_VAL)
// 		{
// 			pReportEx->DeleteAt(posPrev);
// 			nDelCount++;
// 		}
// 	}
// 
// 	return nDelCount;
}

//########################################################################
/////////////报告处理函数/////////////////////////////////////////////////
//########################################################################
//选择某个项目
long GBS_SSelectItem(CTScriptSingleVM *pXvm, const char *pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);

	if (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem(pszItemPath) == NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//普通报告处理函数******************************************************


//获得当前选择的项目的报告的个数
long GBS_SGetItemReportCount(CTScriptSingleVM *pXvm)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pCurrSelectGbItem;

	if (pItem == NULL)
	{
		return 0;
	}

	CReports *pReports = pItem->GetReports();

	if (pReports == NULL)
	{
		return 0;
	}

	return pReports->GetCount();
}

//选择项目的报告对象
long GBS_SSelectItemReport(CTScriptSingleVM *pXvm, long nReportIndex)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);

	if (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItemReport(nReportIndex) == NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


//获得项目的指定的报告的数据：浮点数
double GBS_SGetItemReportValue(CTScriptSingleVM *pXvm, const char* pszValID)
{
	CReport *pReport = (CReport*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pCurrSelectReport;

	if (pReport == NULL)
	{
		return 0;
	}

	double dValue = 0;
	pReport->GetReportValue(CString(pszValID), dValue);

	return dValue;
}

//获得项目的指定的报告的数据：整数
long GBS_SGetItemReportValueLong(CTScriptSingleVM *pXvm, const char* pszValID)
{
	CReport *pReport = (CReport*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pCurrSelectReport;

	if (pReport == NULL)
	{
		return 0;
	}

	long nValue = 0;
	pReport->GetReportValue(CString(pszValID), nValue);

	return nValue;
}

//获得项目的指定的报告的数据：整数
const char* GBS_SGetItemReportValueString(CTScriptSingleVM *pXvm, const char* pszValID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);

	CReport *pReport = (CReport*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pCurrSelectReport;

	if (pReport == NULL)
	{
		return 0;
	}

	long nValue = 0;
	pReport->GetReportValue(CString(pszValID), _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer);

	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
}

//获得项目的指定的报告的数据个数
long GBS_SGetItemReportValueCount(CTScriptSingleVM *pXvm)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);

	CReport *pReport = (CReport*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pCurrSelectReport;

	if (pReport == NULL)
	{
		return 0;
	}

	if (pReport->m_pValues == NULL)
	{
		return 0;
	}

	return pReport->m_pValues->GetCount();
}

void GBS_SGetItemReportValue(CTScriptSingleVM *pXvm, CValue* &pValue, long nDataIndex)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);

	pValue = NULL;
	CReport *pReport = (CReport*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pCurrSelectReport;

	if (pReport == NULL)
	{
		return;
	}

	if (pReport->m_pValues == NULL)
	{
		return ;
	}

	pValue = (CValue*)pReport->m_pValues->GetAtIndex(nDataIndex);
}

double GBS_SGetItemReportValue2(CTScriptSingleVM *pXvm, long nDataIndex)
{
	CValue *pValue = NULL;

	GBS_SGetItemReportValue(pXvm, pValue, nDataIndex);

	if (pValue == NULL)
	{
		return 0;
	}

#ifdef _UNICODE
    double dValue = _wtof(pValue->m_strValue);
#else
    double dValue = atof(pValue->m_strValue.GetString());
#endif

	return dValue;
}

long GBS_SGetItemReportValueLong2(CTScriptSingleVM *pXvm, long nDataIndex)
{
	CValue *pValue = NULL;

	GBS_SGetItemReportValue(pXvm, pValue, nDataIndex);

	if (pValue == NULL)
	{
		return 0;
	}

#ifdef _UNICODE
    long nValue = _wtol(pValue->m_strValue);
#else
    long nValue = atol(pValue->m_strValue.GetString());
#endif

	return nValue;
}

const char* GBS_SGetItemReportValueString2(CTScriptSingleVM *pXvm, long nDataIndex)
{
	CValue *pValue = NULL;

	GBS_SGetItemReportValue(pXvm, pValue, nDataIndex);

	if (pValue == NULL)
	{
		return 0;
	}

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer[0] = 0;
    CString_to_char(pValue->m_strValue, _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer);

	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
}

//扩展报告处理函数******************************************************

//获得项目的指定的报告的数据个数
long GBS_SGetItemReportExDataCount(CTScriptSingleVM *pXvm)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);

	CReport *pReport = (CReport*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pCurrSelectReport;

	if (pReport == NULL)
	{
		return 0;
	}

	if (pReport->m_pRptDvmDataset == NULL)
	{
		return 0;
	}

	return pReport->m_pRptDvmDataset->GetCount();
}


void GBS_SGetItemReportExValue(CTScriptSingleVM *pXvm, CDvmValue* &oTag, long nDataIndex, const char* pszValID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);

	oTag = NULL;
	CReport *pReport = (CReport*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pCurrSelectReport;

	if (pReport == NULL)
	{
		return;
	}

	if (pReport->m_pRptDvmDataset == NULL)
	{
		return ;
	}

	CDvmData* oTags = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nDataIndex);

	if (oTags == NULL)
	{
		return;
	}

	oTag = (CDvmValue*)oTags->FindByID(CString(pszValID));
}

//获得项目的指定的报告的数据：浮点数
double GBS_SGetItemReportExDataValue(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValID)
{
	CDvmValue* oTag = NULL;
	GBS_SGetItemReportExValue(pXvm, oTag, nDataIndex, pszValID);

	if (oTag == NULL)
	{
		return 0;
	}

#ifdef _UNICODE
	return _wtof(oTag->m_strValue);
#else
    return atof(oTag->m_strValue.GetString());
#endif
}

//获得项目的指定的报告的数据：整数
long GBS_SGetItemReportExDataValueLong(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValID)
{
	CDvmValue* oTag = NULL;
	GBS_SGetItemReportExValue(pXvm, oTag, nDataIndex, pszValID);

	if (oTag == NULL)
	{
		return 0;
	}

#ifdef _UNICODE
	return _wtol(oTag->m_strValue);
#else
    return atol(oTag->m_strValue.GetString());
#endif
}

//获得项目的指定的报告的数据：整数
const char* GBS_SGetItemReportExDataValueString(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValID)
{
	CDvmValue* oTag = NULL;
	GBS_SGetItemReportExValue(pXvm, oTag, nDataIndex, pszValID);

	if (oTag == NULL)
	{
		return 0;
	}

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer[0] = 0;
	CString_to_char(oTag->m_strValue, _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer);
	
	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
}
// 
// //获得项目的指定的报告的数据：浮点数
// double GBS_SFindItemReportExDataValue(const char* pszValID)
// {
// 	return 0;
// }
// 
// //获得项目的指定的报告的数据：整数
// long GBS_SFindItemReportExDataValueLong(const char* pszValID)
// {
// 	return 0;
// }
// 
// //获得项目的指定的报告的数据：整数
// const char* GBS_SFindItemReportExDataValueString(const char* pszValID)
// {
// 	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
// }


//////////////////////////////////////////////////////////////////////////
//数据集判断函数功能
//获得项目的指定的报告的数据个数
void GBS_RptExDsSelect(CTScriptSingleVM *pXvm, const char *pszPath, CExBaseList &oList)
{
	CDvmDataset *pDataset = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;//GBS_GetItemReportDataEx();

	if (pDataset == NULL)
	{
		return;
	}

	CString strPath;
	strPath = pszPath;
	pDataset->SelectDatas(strPath, oList, _T("$"));
}

long GBS_RptExDsGetCount(CTScriptSingleVM *pXvm, const char* pszPath)
{
	CExBaseList oList;
	GBS_RptExDsSelect(pXvm, pszPath, oList);

	long nCount = oList.GetCount();
	oList.RemoveAll();

	return nCount;
}

//获得项目的指定的报告的数据：浮点数
double GBS_RptExDsGetValueD(CTScriptSingleVM *pXvm, const char* pszPath, long nIndex)
{
	const char *pszValue = GBS_RptExDsGetValueStr(pXvm, pszPath, nIndex);
	return atof(pszValue);
}

//获得项目的指定的报告的数据：整数
long GBS_RptExDsGetValueL(CTScriptSingleVM *pXvm, const char* pszPath, long nIndex)
{
	const char *pszValue = GBS_RptExDsGetValueStr(pXvm, pszPath, nIndex);
	return atol(pszValue);
}

//获得项目的指定的报告的数据：整数
const char* GBS_RptExDsGetValueStr(CTScriptSingleVM *pXvm, const char* pszPath, long nIndex)
{
	CExBaseList oList;
	GBS_RptExDsSelect(pXvm, pszPath, oList);

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer[0] = '0';
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer[1] = 0;

	if (oList.GetCount() == 0)
	{
		return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
	}

	CExBaseObject *pObj = oList.GetAtIndex(nIndex);
	double dValue = 0;

	if (pObj == NULL)
	{
		oList.RemoveAll();
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_DataPathUn.GetString() /*_T("数据路径【%s】检索出的数据【%d】不存在")*/,pszPath, nIndex );
		return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
	}

	if (pObj->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		CString_to_char(((CDvmData*)pObj)->m_strValue, _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer);
	}
	else if (pObj->GetClassID() == DVMCLASSID_CDVMVALUE)
	{
		CString_to_char(((CDvmValue*)pObj)->m_strValue, _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer);
	}

	oList.RemoveAll();

	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
}

//数据验证
void GBS_RptExDsValidClear(CTScriptSingleVM *pXvm)
{
	CDsvSequence *pDvmSequence = _CGbScriptGlobalDefine::GetDsvSequence();
	pDvmSequence->DeleteAll();
}

void GBS_RptExDsValidAddElement(CTScriptSingleVM *pXvm, const char* pszText, long nOption, long nUnbound)
{
	CDsvSequence *pDvmSequence = _CGbScriptGlobalDefine::GetDsvSequence();
	pDvmSequence->AddElement(CString(pszText), nOption, nUnbound);
}

void GBS_RptExDsValidAddElementChoice(CTScriptSingleVM *pXvm, const char* pszText, long nOption, long nUnbound)
{
	CDsvChoice *pDsvChoice = NULL;
	CDsvSequence *pDsvSequence = _CGbScriptGlobalDefine::GetDsvSequence();

	pDsvChoice = (CDsvChoice *)pDsvSequence->GetTail();

	if (pDsvChoice != NULL)
	{
		if (pDsvChoice->GetClassID() != DVMCLASSID_CDSVCHOICE)
		{
			pDsvChoice = NULL;
		}
	}

	if (pDsvChoice == NULL)
	{
		pDsvChoice = pDsvChoice->AddChoice(nOption, nUnbound);
	}

	pDsvChoice->AddElement(CString(pszText), nOption, nUnbound);
}

long GBS_RptExDsValid(CTScriptSingleVM *pXvm, long nValidateHead)
{
	CDvmDataset *pDataset = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;//GBS_GetItemReportDataEx();

	if (pDataset == NULL)
	{
		return 0;
	}

	CDsvSequence *pDsvSequence = _CGbScriptGlobalDefine::GetDsvSequence();

	return pDsvSequence->DsValidate(pDataset, NULL, nValidateHead);
}

long GBS_RecordCmd(CTScriptSingleVM *pXvm, const char *pszCmdID, const char *pszCmdPara)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	pTestControl->GBS_RecordCmd(pszCmdID, pszCmdPara);
#endif

	return 0;
}

long GBS_AdjustWord(CTScriptSingleVM *pXvm, long nPopDlg)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	pTestControl->AdjustReport(NULL);
#endif
	
	return 0;
}


void GBS_CalSoeTime(CTScriptSingleVM *pXvm, const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_FtcnCmdUse.GetString() /*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return;
	}

	((CCommCmd*)pItem)->CalSoeTime(pszRptID, pszSoeID1, pszSoeID2);
}

void GBS_CalSoeTimeEx(CTScriptSingleVM *pXvm, const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_FtcnCmdUse.GetString() /*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return;
	}

	((CCommCmd*)pItem)->CalSoeTime(pszRptID, pszSoeID1, pszVal1, pszSoeID2, pszVal2);
}

void GBS_SetSoeTripDesc(CTScriptSingleVM *pXvm, const char *pszRptID, const char *pszSoeID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_FtcnCmdUse.GetString() /*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return;
	}

	((CCommCmd*)pItem)->SetSoeTripDesc(pszRptID, pszSoeID);
}

long  GBS_CalSoeError(CTScriptSingleVM *pXvm, double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return 0;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_FtcnCmdUse.GetString() /*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return 0;
	}

	return ((CCommCmd*)pItem)->CalSoeError(dRate, pszDsPathID, pszRptID, pszAbsErrID, pszRelErrID, dStandVal, dAbsErr, dRelErr);
}

long GBS_CalSoeError2(CTScriptSingleVM *pXvm, double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID
					  , double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return 0;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_FtcnCmdUse.GetString() /*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return 0;
	}

	return ((CCommCmd*)pItem)->CalSoeError2(dRate, pszDsPathID, pszRptID, pszAbsErrID, pszRelErrID, dStandVal, dErrRefStandVal, dAbsErr, dRelErr);
}


//Record
long GBS_RcdSetProgID(CTScriptSingleVM *pXvm, const char* pszRcdProgID)
{
#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdSetProgID(pszRcdProgID);
#else
	return 0;
#endif
}

long GBS_RcdExit(CTScriptSingleVM *pXvm)
{
#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdExit();
#else
	return 0;
#endif
}

long GBS_RcdConfig(CTScriptSingleVM *pXvm, const char* pszPara)
{
#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdConfig(pszPara);
#else
	return 0;
#endif
}

long GBS_RcdSelect(CTScriptSingleVM *pXvm, const char* pszPara)
{
#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);

	return pTestControl->GBS_RcdSelect(pszPara);
#else
	return 0;
#endif
}

long GBS_RcdValidate(CTScriptSingleVM *pXvm, const char* pszRsltID)
{
#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdValidate(pszRsltID);
#else
	return 0;
#endif
}

long GBS_RcdCmpClear(CTScriptSingleVM *pXvm)
{
#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdCmpClear();
#else
	return 0;
#endif
}

long GBS_RcdCmpInit(CTScriptSingleVM *pXvm, const char* pszRcdFilePathRoot, long nCreateTestTimesDir)
{
#ifndef GUIDEBOOK_DEV_MODE
	g_strRcdFilePathRoot = pszRcdFilePathRoot;
	g_bCreateTestTimesDir = nCreateTestTimesDir;
	return 0;
#else
	return 0;
#endif
}

long GBS_RcdCmp(CTScriptSingleVM *pXvm, const char* pszStdFile, const char* pszTestFile)
{
#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdCmp(pszStdFile, pszTestFile);
#else
	return 0;
#endif
}

long GBS_RcdCopyFile(CTScriptSingleVM *pXvm, const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir)
{
#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdCopyFile(pszSrcFile, pszDestFile, nCreateTestTimesDir);
#else
	return 0;
#endif
}

long GBS_RcdAnalyse(CTScriptSingleVM *pXvm, const char* pszRcdFile)
{
#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdAnalyse(pszRcdFile);
#else
	return 0;
#endif
}

long GBS_RcdSetPath(CTScriptSingleVM *pXvm, long nAppendItemPath, const char* pszRcdFilePathRoot, long nAppendTestTimeDir)
{
#ifndef GUIDEBOOK_DEV_MODE
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdSetPath(pItem, nAppendItemPath, pszRcdFilePathRoot, nAppendTestTimeDir);
#else
	return 0;
#endif
}

//重复测试相关
long GBS_GetRepeatTimes(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	CGbItemBase *pItem = NULL;
	long nRepeatTimes = 0;

	if (oListDest.GetCount() == 1)
	{
		pItem = oListDest.GetHead();
		
		if (pItem->GetClassID() == GBCLASSID_COMMCMD)
		{
			CCommCmd *pCommCmd = (CCommCmd*)pItem;
			CCmd *pCmd = pCommCmd->GetCmd();
			nRepeatTimes = pCmd->m_nRepeatTimes;
		}
		
	}

	oListDest.RemoveAll();
	return nRepeatTimes;
}

long GBS_GetRepeatSuccTimes(CTScriptSingleVM *pXvm, const char* pszItemPath)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	CGbItemBase *pItem = NULL;
	long nSuccTimes = 0;

	if (oListDest.GetCount() == 1)
	{
		pItem = oListDest.GetHead();

		CReports *pReports = pItem->GetReports();
		POS pos = pReports->GetHeadPosition();
		CReport *pReport = NULL;

		while (pos != NULL)
		{
			pReport = (CReport *)pReports->GetNext(pos);

			if (pReport->GetResultJudge() != 0)
			{
				nSuccTimes++;
			}
		}

	}

	oListDest.RemoveAll();
	return nSuccTimes;
}

void GBS_SetCmdZoneIndex(CTScriptSingleVM *pXvm, long nZoneIndex)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem == NULL)
	{
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_FtcnCmdUse2.GetString() /*_T("SetCmdZoneIndex函数只能用于通讯命令")*/);
		return;
	}

	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd *pCmd = pCommCmd->GetCmd();

	pCmd->m_nZoneIndex = nZoneIndex;
}

//修正动作值的起始值和终止值
void Gbs_ValidBeginEndValRange(CTScriptSingleVM *pXvm, const char *pBeginValID, const char *pEndValID, const char *pStepID
							   , double dMinRange, double dMinStep
							   , long nMinSteps, long nMaxSteps, long nUseNeg)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem(NULL);

	if (pItem == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_FtcnScriptCall.GetString() /*_T("函数ValidBeginEndValRange只能作为电气量项目的脚本调用")*/);
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_MACROTEST)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_FtcnScriptCall.GetString() /*_T("函数ValidBeginEndValRange只能作为电气量项目的脚本调用")*/);
		return;
	}

	//获取数据并验证范围
	CMacroTest *pMacroTest = (CMacroTest*)pItem;
	CString strBeginValID, strEndValID, strStepID;
	strBeginValID = pBeginValID;
	strEndValID = pEndValID;
	strStepID = pStepID;

	double dBeginVal, dEndVal, dStepVal;

	if (!pMacroTest->GetItemParaValue(strBeginValID, dBeginVal))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_FctnUnExist.GetString() /*_T("函数ValidBeginEndValRange:[%s]不存在")*/, strBeginValID.GetString());
		return;
	}

	if (!pMacroTest->GetItemParaValue(strEndValID, dEndVal))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_FctnUnExist.GetString() /*_T("函数ValidBeginEndValRange:[%s]不存在")*/, strEndValID.GetString());
		return;
	}

	if (!pMacroTest->GetItemParaValue(strStepID, dStepVal))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_FctnUnExist.GetString() /*_T("函数ValidBeginEndValRange:[%s]不存在")*/, strStepID.GetString());
		return;
	}

	double dRange = fabs(dBeginVal-dEndVal);
	long nSteps = dRange / dStepVal;

	//如果两个值的范围大于最小范围，则结束
	if ((dMinRange <= dRange) && (nMinSteps <= nSteps && nSteps <= nMaxSteps))
		return;

	if (nMaxSteps <= 0)
		nMaxSteps = 1000000;
	if (nMinSteps <= 0)
		nMinSteps = 10;
	if (nMinSteps > nMaxSteps)
		nMaxSteps = nMinSteps + 100;

	if (dStepVal < dMinStep)
		dStepVal = dMinStep;

	if (dMinRange > dRange)
	{
		double dGap = dMinRange - fabs(dEndVal - dBeginVal);
		dGap /= 2;

		if (dBeginVal > dEndVal)
		{
			dBeginVal += dGap;
			dEndVal -= dGap;

			if (dEndVal < 0 && (!nUseNeg))
			{
				dEndVal = 0;
				dBeginVal = dEndVal + dMinRange;
			}
		}
		else
		{
			dEndVal += dGap;
			dBeginVal -= dGap;

			if (dBeginVal < 0 && (!nUseNeg))
			{
				dBeginVal = 0;
				dEndVal = dBeginVal + dMinRange;
			}
		}
	}


	dRange = fabs(dBeginVal-dEndVal);
	nSteps = dRange / dStepVal;

	//如果步数在步数的范围之内，则结束
	if (nMinSteps > nSteps || nSteps > nMaxSteps)
	{
		if (nSteps < nMinSteps)
			nSteps = nMinSteps;
		if (nSteps > nMaxSteps)
			nSteps = nMaxSteps;
		
		long nTempSteps = nSteps / 2;

		if (dBeginVal > dEndVal)
		{
			dBeginVal = dBeginVal + nTempSteps * dStepVal;
			dEndVal = dBeginVal - nSteps * dStepVal;

			if (dEndVal < 0 && (!nUseNeg))
			{
				dEndVal = 0;
				dBeginVal = nSteps * dStepVal;
			}
		}
		else
		{
			dEndVal = dEndVal + nTempSteps * dStepVal;
			dBeginVal = dEndVal - nSteps * dStepVal;

			if (dBeginVal < 0 && (!nUseNeg))
			{
				dBeginVal = 0;
				dEndVal = nSteps * dStepVal;
			}
		}

	}


	CString strVal;

	strVal.Format(_T("%f"), dBeginVal);
	pMacroTest->SetItemParaValue(strBeginValID, strVal, TRUE);
	strVal.Format(_T("%f"), dEndVal);
	pMacroTest->SetItemParaValue(strEndValID, strVal, TRUE);
	strVal.Format(_T("%f"), dStepVal);
	pMacroTest->SetItemParaValue(strStepID, strVal, TRUE);

#ifndef GUIDEBOOK_DEV_MODE
	if (g_nLog_TestControl_Msg)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ValidBeginEndValRange:%s=%f  %s=%f  %s=%f")
            ,strBeginValID.GetString(), dBeginVal, strEndValID.GetString(), dEndVal, strStepID.GetString(), dStepVal);
	}
#endif
}



//时间出发函数
void Gbs_SetTmTriggerSecond(CTScriptSingleVM *pXvm, long nSecond, long nOptr)
{
#ifdef GUIDEBOOK_DEV_MODE
#else
    CTestControlBase* pTestControl = GBS_GetTestControl2(pXvm);
	pTestControl->Gbs_SetTmTriggerSecond(nSecond, nOptr);
#endif
}

void Gbs_SetTmTriggerCountMinute(CTScriptSingleVM *pXvm, long nMinute)
{
#ifdef GUIDEBOOK_DEV_MODE
#else
    CTestControlBase* pTestControl = GBS_GetTestControl2(pXvm);
	pTestControl->Gbs_SetTmTriggerCountMinute(nMinute);
#endif
}

void Gbs_EnterTmTrigger(CTScriptSingleVM *pXvm)
{
#ifdef GUIDEBOOK_DEV_MODE
#else
    CTestControlBase* pTestControl = GBS_GetTestControl2(pXvm);
	pTestControl->Gbs_EnterTmTrigger();
#endif
}

void Gbs_StartTimerTigger(CTScriptSingleVM *pXvm)
{
#ifdef GUIDEBOOK_DEV_MODE
#else
    CTestControlBase* pTestControl = GBS_GetTestControl2(pXvm);
	pTestControl->Gbs_StartTimerTigger();
#endif
}

void Gbs_StopTimerTrigger(CTScriptSingleVM *pXvm)
{
#ifdef GUIDEBOOK_DEV_MODE
#else
    CTestControlBase* pTestControl = GBS_GetTestControl2(pXvm);
	pTestControl->Gbs_StopTimerTrigger();
#endif
}

double Gbs_ValueRevised(CTScriptSingleVM *pXvm, double dValue, long nDots)
{
	return math_ValueRevised(dValue, nDots);
}


//////////////////////////////////////////////////////////////////////////
//日志部分
CDvmLogs* Gbs_log_query_get_logs(CTScriptSingleVM *pXvm)
{
	CCommCmd *pCommCmd = (CCommCmd*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem_CommCmd();

	if (pCommCmd == NULL)
	{
		return NULL;
	}

	CReport *pReport = pCommCmd->GetCurrReport();

	if ( pReport != NULL )
	{
		return pReport->m_pLogs;
	}
	else
	{
		return NULL;
	}
}

CDvmLog* Gbs_log_query_get_log(CTScriptSingleVM *pXvm, long nLogIndex)
{
	CCommCmd *pCommCmd = (CCommCmd*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem_CommCmd();

	if (pCommCmd == NULL)
	{
		return NULL;
	}

	CReport *pReport = pCommCmd->GetCurrReport();

	if ( pReport == NULL )
	{
		return NULL;
	}
	
	if (pReport->m_pLogs == NULL)
	{
		return NULL;
	}

	return (CDvmLog*)pReport->m_pLogs->GetAtIndex(nLogIndex);
}

long Gbs_log_query_clear(CTScriptSingleVM *pXvm)
{
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogs.RemoveAll();
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas.RemoveAll();

	return 0;
}

long Gbs_log_query_time(CTScriptSingleVM *pXvm, const char *pszBeginTine, const char *pszEndTime)
{
#ifndef _PSX_QT_LINUX_
    CDvmLogs *pLogs = Gbs_log_query_get_logs(pXvm);
	POS pos = pLogs->GetHeadPosition();
	CDvmLog *pLog = NULL;
	
	COleDateTime tmBegin, tmEnd;
	COleDateTime tmData;
	CString strTimeBegin(pszBeginTine), strTimeEnd(pszEndTime);

	tmBegin.Format(strTimeBegin);
	tmEnd.Format(strTimeEnd);

	while (pos != NULL)
	{
		pLog = (CDvmLog *)pLogs->GetNext(pos);
		tmData = (__time64_t)pLog->m_dCurrTime;

		if (tmBegin <= tmData && tmData <= tmEnd)
		{
			_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogs.AddTail(pLog);
		}
	}
#endif

	return 0;
}

long Gbs_log_query_entryid(CTScriptSingleVM *pXvm, const char *pszEntryID)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs(pXvm);
	return 0;
}

long Gbs_log_query_logctrl(CTScriptSingleVM *pXvm, const char *pszLogCtrl)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs(pXvm);
	POS pos = pLogs->GetHeadPosition();
	CDvmLog *pLog = NULL;
	CString strText(pszLogCtrl);

	if (strText.GetLength() == 0)
	{
		_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogs.Append(pLogs);
		return 0;
	}

	while (pos != NULL)
	{
		pLog = (CDvmLog *)pLogs->GetNext(pos);

		if (pLog->m_strLogCtrl == strText)
		{
			_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogs.AddTail(pLog);
		}
	}

	return 0;
}

long Gbs_log_query_dataset(CTScriptSingleVM *pXvm, const char *pszDataset)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs(pXvm);
	POS pos = pLogs->GetHeadPosition();
	CDvmLog *pLog = NULL;
	CString strDataset(pszDataset);

	while (pos != NULL)
	{
		pLog = (CDvmLog *)pLogs->GetNext(pos);

		if (pLog->m_strDataset == strDataset)
		{
			_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogs.AddTail(pLog);
		}
	}

	return 0;
}

long Gbs_log_query_data_clear(CTScriptSingleVM *pXvm)
{
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas.RemoveAll();
	return 0;
}

long Gbs_log_query_data(CTScriptSingleVM *pXvm, CDvmLog *pLog, const CString &strDataID)
{
	if (strDataID.GetLength() == 0)
	{
		_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas.Append(pLog);
		return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas.GetCount();
	}

	POS pos = pLog->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pLog->GetNext(pos);

		if (pData->m_strID == strDataID)
		{
			_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas.AddTail(pData);
		}
	}

	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas.GetCount();
}

long Gbs_log_query_data(CTScriptSingleVM *pXvm, const char *pszDataID)
{
	//CDvmLogs *pLogs = Gbs_log_query_get_logs();
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogs;
	POS pos = pList->GetHeadPosition();
	CDvmLog *pLog = NULL;
	CString strDataID(pszDataID);
	long nCount = 0;

	while (pos != NULL)
	{
		pLog = (CDvmLog *)pList->GetNext(pos);
		nCount += Gbs_log_query_data(pXvm, pLog, strDataID);
	}

	return nCount;
}

long Gbs_log_query_data_get_count(CTScriptSingleVM *pXvm)
{
	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas.GetCount();;
}

long Gbs_log_query_data_add_to_rpt(CTScriptSingleVM *pXvm)
{
	CReport* pReport = GBS_GetItemReport(pXvm);
	
	pReport->AddRptDvmDataset(_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas);

	return pReport->m_pRptDvmDataset->GetCount();
}

long Gbs_log_query(CTScriptSingleVM *pXvm, const char *pszScript)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs(pXvm);
	return 0;
}

long Gbs_log_get_count(CTScriptSingleVM *pXvm)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs(pXvm);

	if (pLogs == NULL)
	{
		return 0;
	}
	else
	{
		return pLogs->GetCount();
	}
}

const char* Gbs_log_get_attr(CTScriptSingleVM *pXvm, long nLogIndex, const char *pszAttr)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs(pXvm);
	g_pLuaReturnString[0] = 0;

	if (pLogs == NULL)
	{
		return g_pLuaReturnString;
	}
	
	CString strAttr, strValue;
	strAttr = pszAttr;
	CDvmLog *pLog = (CDvmLog*)pLogs->GetAtIndex(nLogIndex);

	if (pLog == NULL)
	{
		return g_pLuaReturnString;
	}

	if (pLog->GetValueByID(strAttr, strValue))
	{
		CString_to_char(strValue, g_pLuaReturnString);
	}

	return g_pLuaReturnString;
}

long Gbs_log_get_data_count(CTScriptSingleVM *pXvm, long nLogIndex)
{
	CDvmLog *pLog = Gbs_log_query_get_log(pXvm, nLogIndex);

	if (pLog == NULL)
	{
		return 0;
	}

	return pLog->GetCount();
}

const char* Gbs_log_get_data_attr(CTScriptSingleVM *pXvm, long nLogIndex, long nDataIndex, const char *pszAttr)
{
	CDvmLog *pLog = Gbs_log_query_get_log(pXvm, nLogIndex);
	g_pLuaReturnString[0] = 0;

	if (pLog == NULL)
	{
		return g_pLuaReturnString;
	}

	CDvmData *pData = (CDvmData *)pLog->GetAtIndex(nDataIndex);

	if (pData == NULL)
	{
		return g_pLuaReturnString;
	}

	CString strAttr, strValue;
	strAttr = pszAttr;

	if (pData->GetValueByID(strAttr, strValue))
	{
		CString_to_char(strValue, g_pLuaReturnString);
	}

	return g_pLuaReturnString;
}

const char* Gbs_log_get_data_attr2(CTScriptSingleVM *pXvm, long nLogIndex, const char *pszDataID, const char *pszAttr)
{
	CDvmLog *pLog = Gbs_log_query_get_log(pXvm, nLogIndex);
	g_pLuaReturnString[0] = 0;

	if (pLog == NULL)
	{
		return g_pLuaReturnString;
	}

	CString strDataID;
	strDataID = pszDataID;
	CDvmData *pData = (CDvmData *)pLog->FindByID(strDataID);

	if (pData == NULL)
	{
		return g_pLuaReturnString;
	}

	CString strAttr, strValue;
	strAttr = pszAttr;

	if (pData->GetValueByID(strAttr, strValue))
	{
		CString_to_char(strValue, g_pLuaReturnString);
	}

	return g_pLuaReturnString;
}


//////////////////////////////////////////////////////////////////////////
//字符串处理
long GBS_InitStrTok(CTScriptSingleVM *pXvm, const char *pszString, const char *pControl)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	return pGuideBook->GBS_InitStrTok((char*)pszString, (char*)pControl);

// #ifdef GUIDEBOOK_DEV_MODE
// 	return pGuideBook->GBS_InitStrTok((char*)pszString, (char*)pControl);
// #else
// 	CTestControlBase* pTestControl = GBS_GetTestControl2();
// 	return pTestControl->GBS_InitStrTok((char*)pszString, (char*)pControl);
// #endif
}

long GBS_StrTokCount(CTScriptSingleVM *pXvm)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	return pGuideBook->GBS_StrTokCount();

// #ifdef GUIDEBOOK_DEV_MODE
// 	return CTestControlBase::GBS_StrTokCount();
// #else
// 	CTestControlBase* pTestControl = GBS_GetTestControl2();
// 	return pTestControl->GBS_StrTokCount();
// #endif
}

const char* GBS_StrTokIndex(CTScriptSingleVM *pXvm, long nIndex)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	return pGuideBook->GBS_StrTokIndex(nIndex);
// 
// #ifdef GUIDEBOOK_DEV_MODE
// 	return CTestControlBase::GBS_StrTokIndex(nIndex);
// #else
// 	CTestControlBase* pTestControl = GBS_GetTestControl2();
// 	return pTestControl->GBS_StrTokIndex(nIndex);
// #endif
}

const char* GBS_StrTokNext(CTScriptSingleVM *pXvm)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	return pGuideBook->GBS_StrTokNext();
// 
// #ifdef GUIDEBOOK_DEV_MODE
// 	return CTestControlBase::GBS_StrTokNext();
// #else
// 	CTestControlBase* pTestControl = GBS_GetTestControl2();
// 	return pTestControl->GBS_StrTokNext();
// #endif
}

//装置的全局参数
void GBS_SetGlobal_Str(CTScriptSingleVM *pXvm, const char *pszID, const char *pszValue)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	
	if (pGuideBook != NULL)
	{
		CString strID, strValue;
		strID = pszID;
		strValue = pszValue;
		pGuideBook->GBS_SetGlobal_Str(strID, strValue);

#ifndef _PSX_QT_LINUX_
#ifndef GUIDEBOOK_DEV_MODE
		if (g_strGbGlobalData_DeviceIndex == strID)
		{
			CFactoryBatchTestMngr::PostFacBatchTestMsg(FacBatchTestMsg_Attr_IdxDv, (LPARAM)pGuideBook);
		}
#endif  //GUIDEBOOK_DEV_MODE
#endif//_PSX_QT_LINUX_
	}
}

void GBS_SetGlobal_Long(CTScriptSingleVM *pXvm, const char *pszID, long nValue)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pGuideBook != NULL)
	{
		CString strID, strValue;
		strID = pszID;
		strValue.Format(_T("%d"), nValue);
		pGuideBook->GBS_SetGlobal_Str(strID, strValue);

		//2019-10-30  定义修改定值的时候，是否判断最大最小值
		if (strID == g_strGbGlobalData_WSetsUseMinMax)
		{
			pGuideBook->m_bWSetsUseMinMax = nValue;
		}
	}
}

void GBS_SetGlobal_Float(CTScriptSingleVM *pXvm, const char *pszID, float fValue)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pGuideBook != NULL)
	{
		CString strID, strValue;
		strID = pszID;
		strValue.Format(_T("%f"), fValue);
		pGuideBook->GBS_SetGlobal_Str(strID, strValue);
	}
}


const char* GBS_GetGlobal_Str(CTScriptSingleVM *pXvm, const char *pszID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);

	g_pLuaReturnString[0] = 0;

	if (pGuideBook != NULL)
	{
		CString strID, strValue;
		strID = pszID;
		strValue = pGuideBook->GBS_GetGlobal_Str(strID);
		CString_to_char(strValue, g_pLuaReturnString);
	}

	return g_pLuaReturnString;
}

long GBS_GetGlobal_Long2(CTScriptSingleVM *pXvm, const CString &strID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);

	long nRet = 0;

	if (pGuideBook != NULL)
	{
		CString strValue;
		strValue = pGuideBook->GBS_GetGlobal_Str(strID);
		nRet = CString_To_long(strValue);
	}

	return nRet;
}

long GBS_GetGlobal_Long(CTScriptSingleVM *pXvm, const char *pszID)
{
	CString strID;
	strID = pszID;
	return GBS_GetGlobal_Long2(pXvm, strID);
}

float GBS_GetGlobal_Float(CTScriptSingleVM *pXvm, const char *pszID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);

	double fRet = 0;

	if (pGuideBook != NULL)
	{
		CString strID, strValue;
		strID = pszID;
		strValue = pGuideBook->GBS_GetGlobal_Str(strID);
		fRet = CString_To_double(strValue);
	}

	return fRet;
}

void GBS_Set_TestError(CTScriptSingleVM *pXvm, const char *pszTestError)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);

	CString strTestError;
	strTestError = pszTestError;
	pGuideBook->SetTestError(strTestError);
	pItem->SetRsltJdg(0);
}

long GBS_BinRslt(CTScriptSingleVM *pXvm, const char *pszParaID, const char *pszRsltID)
{

#ifdef GUIDEBOOK_DEV_MODE
	return 1;
#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);
	return pTestControl->GBS_BinRslt(pItem, pszParaID, pszRsltID);
#endif
}

long GBS_BinStateRslt(CTScriptSingleVM *pXvm, const char *pszParaID, const char *pszRsltID)
{

#ifdef GUIDEBOOK_DEV_MODE
	return 1;
#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);
	return pTestControl->GBS_BinStateRslt(pItem, pszParaID, pszRsltID);
#endif
}

long GBS_BinChngCntRslt(CTScriptSingleVM *pXvm, const char *pszBinChngData, const char *pszRsltID)
{

#ifdef GUIDEBOOK_DEV_MODE
	return 1;
#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);
	return pTestControl->GBS_BinChngCntRslt(pItem, pszBinChngData, pszRsltID);
#endif
}

// 
// long GBS_BinRsltEx(CTScriptSingleVM *pXvm, const char *pszParaDatas, const char *pszRsltDatas)
// {
// #ifdef GUIDEBOOK_DEV_MODE
// 	return 1;
// #else
// 	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
// 	CTestControlBase *pTestControl = GBS_GetTestControl2();
// 	return pTestControl->GBS_BinRsltEx(pItem, pszParaDatas, pszRsltDatas);
// #endif
// }


//2019-1-6:增加数据对象是否合格的功能   lijq
// BOOL g_bAddDataErrorValueToRpt = FALSE;
void GBS_Set_AddDataErrorValueToRpt(CTScriptSingleVM *pXvm, long nValue)
{
	if (nValue == 0)
	{
		g_bAddDataErrorValueToRpt = FALSE;
	}
	else
	{
		g_bAddDataErrorValueToRpt = TRUE;
	}
}

void GBS_AddDataErrorToRpt(CTScriptSingleVM *pXvm, const char* pszDataID, long nValue)
{
#ifdef GUIDEBOOK_DEV_MODE
	
#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
    CTestControlBase *pTestControl = GBS_GetTestControl2(pXvm);
	pTestControl->GBS_AddDataErrorToRpt(pItem, pszDataID, nValue);
#endif
}

//2019-6-5  测试记录文件相关
const char* GBS_GetTemplateFile(CTScriptSingleVM *pXvm, long nWithPath)
{
	g_pLuaReturnString[0] = 0;

#ifdef GUIDEBOOK_DEV_MODE

#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	CString strTemplateFile;

	if (nWithPath == 0)
	{
		strTemplateFile = ParseFileName(pGuideBook->m_strGbXmlFile);
	}
	else
	{
		strTemplateFile = pGuideBook->m_strGbXmlFile;
	}

	CString_to_char(strTemplateFile, g_pLuaReturnString);
#endif

	return g_pLuaReturnString;
}

const char* GBS_GetGbrptFile(CTScriptSingleVM *pXvm, long nWithPath)
{
	g_pLuaReturnString[0] = 0;

#ifdef GUIDEBOOK_DEV_MODE

#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	CString strGbrptFile;

	if (nWithPath == 0)
	{
		strGbrptFile = pTestControl->GetGbBinaryFileName();
	}
	else
	{
		strGbrptFile = pTestControl->GetGbBinaryFile();
	}

	CString_to_char(strGbrptFile, g_pLuaReturnString);
#endif

	return g_pLuaReturnString;
}

void GBS_SetGbrptFileName(CTScriptSingleVM *pXvm, const char *pszFileName)
{
#ifdef GUIDEBOOK_DEV_MODE

#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	CString strGbrptFile;
	strGbrptFile = pszFileName;

	if (strGbrptFile.GetLength() == 0)
	{
		return;
	}

	pTestControl->ChangeReportFileName(strGbrptFile);
#endif

}

//2019-7-19     根据装置的编号，调整动作时间
void GBS_OffsetTestDataByGbrptIndex(CTScriptSingleVM *pXvm, const char *pszDestDataID)
{
#ifdef GUIDEBOOK_DEV_MODE

#else
	CString strID;
	strID = pszDestDataID;
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
    CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	pTestControl->GBS_OffsetTestDataByGbrptIndex(pItem, pszDestDataID);
#endif

}

//2020-6-2  lijunqing 通用功能，不需要写到TestControl中
long GBS_VersionInfoCompare(CTScriptSingleVM *pXvm, CGuideBook *pGuideBook, const char *pszDatasetPath, const char *pszStandFile)
{
	CDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return 0;
	}

	CDataSet *pDataSet = NULL;
	CString strDataSetPath, strStandFile;
	strDataSetPath = pszDatasetPath;
	strStandFile = pszStandFile;
	pDataSet = pDevice->SelectDataSetEx(strDataSetPath);

	if (pDataSet == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("版本比对，数据集路径错误：%s"), strDataSetPath.GetString());
		return 0;
	}

	CString strFilePath;
	strFilePath = _P_GetLibraryPath();;

	if (strStandFile.IsEmpty())
	{
		strStandFile = _T("VersionStandardInfo.xml");
	}

	strFilePath = strFilePath + strStandFile;
	CDvmData oStandFile;
	oStandFile.OpenXmlFile(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CDvmDataset oRslt;

	long nRslt = pDataSet->CompareVersionInfo(&oStandFile, &oRslt);
	CReport *pReport = pItem->GetReport(-1);

	if (pReport != NULL)
	{
		CDvmDataset *pDs = pReport->m_pRptDvmDataset;
		pDs->AppendClone(&oRslt);
		oRslt.DeleteAll();
	}

	return nRslt;
}

//2020-05-22   磐能版本比对功能  shaolei；
long GBS_VersionInfoCompare (CTScriptSingleVM *pXvm, const char* pszPath, const char* pszFilePath)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	return GBS_VersionInfoCompare(pXvm, pGuideBook, pszPath, pszFilePath);
}

void GBS_SetComtradeDrawLineMode(CTScriptSingleVM *pXvm, const char *pszMode)
{
#ifdef GUIDEBOOK_DEV_MODE

#else
#ifndef _PSX_QT_LINUX_
    if (stricmp(pszMode, "line") == 0)
	{
		MrDraw::g_dwAnalogDrawMode = ANALOG_DRAW_MODE_LINE;
	}
	else if (stricmp(pszMode, "crossa") == 0)
	{
		MrDraw::g_dwAnalogDrawMode = ANALOG_DRAW_MODE_CROSSA;
	}
	else if (stricmp(pszMode, "crossx") == 0)
	{
		MrDraw::g_dwAnalogDrawMode = ANALOG_DRAW_MODE_CROSSX;
	}
	else
	{
		MrDraw::g_dwAnalogDrawMode = ANALOG_DRAW_MODE_LINE;
	}
#endif
#endif
}

//2021-2-21  lijunqing
#ifndef GUIDEBOOK_DEV_MODE
#ifndef _PSX_QT_LINUX_
#include "..\..\Module\Record\Analysis\XRcdAnalysisTool.h"
#endif
#endif

void GBS_RcdAnalysis(CTScriptSingleVM *pXvm, const char *pszRcdFile, const char *pszAnalysisFile)
{
#ifndef GUIDEBOOK_DEV_MODE
#ifndef _PSX_QT_LINUX_
	CString strRcdFile, strAnalysisFile, strRcdFileID;
	strRcdFileID = pszRcdFile;
	strAnalysisFile = pszAnalysisFile;
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT ( (pItem != NULL) && (pGuideBook != NULL) );

	if (strRcdFileID.Find('.') < 0)
	{//不是是文件
		if (! pItem->GetItemReportValue(strRcdFileID, strRcdFile))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("RcdAnalysis: RCD File[%s] error"));
			return;
		}
	}
	else
	{
		strRcdFile = strRcdFileID;
	}

	strRcdFile = ats_GetBinaryTempFilePath(pItem) + strRcdFile;
	strAnalysisFile = _P_GetConfigPath() + strAnalysisFile;
	CXRcdAnalysisTool oRcdAnalysisTool;
	oRcdAnalysisTool.OpenRcdAnalysisFile(strAnalysisFile);
	oRcdAnalysisTool.RcdAnalysis(strRcdFile);

	//分析结果记录
	CReport *pReport = pItem->GetReport(-1);
	pReport->UpdateReportValues(&oRcdAnalysisTool.m_oResults);

#endif
#endif 
}


//2021-3-28  lijunqing  根据数据集创建安全措施的数据对象
void GBS_CreateSafetyDatasByDvmDataset(CTScriptSingleVM *pXvm, const char *pszDvmDatasetPath, const char *pszAttrs
									   , const char *pszDataType, const char *pszDataFormat, const char *pszDefValue)
{
	CValues oAttrs;
	CString strValues;
	strValues = pszAttrs;
	oAttrs.SetValuesByString(strValues);

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT ( (pItem != NULL) && (pGuideBook != NULL) );

	if (pItem->GetClassID() != GBCLASSID_SAFETY)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("CreateSafetyDatasByDvmDataset: not in safety"));
		return;
	}

	CDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	CDataSet *pDataSet = NULL;
	CString strDataSetPath;
	strDataSetPath = pszDvmDatasetPath;
	pDataSet = pDevice->SelectDataSetEx(strDataSetPath);

	if (pDataSet == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("CreateSafetyDatasByDvmDataset: [%s] error"), strDataSetPath.GetString());
		return;
	}

	CSafety *pSafety = (CSafety*)pItem;
	pSafety->CreateSafetyDatasByDvmDataset(pDataSet, &oAttrs, pszDataType, pszDataFormat, pszDefValue);
}

//2021-5-23 lijunqing  
#ifndef _PSX_QT_LINUX_
#include "../SetsTools/StesFilePdfTool.h"
#include "../SetsTools/SetsImportEditDlg.h"
#endif

void GBS_ImportSets(CTScriptSingleVM *pXvm)
{
#ifndef _PSX_QT_LINUX_
/*
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CDevice *pDevice = (CDevice*)pItem->GetAncestor(GBCLASSID_DEVICE);

	if (pDevice == NULL)
	{
		return;
	}

	CGuideBook *pGuideBook = (CGuideBook*)pDevice->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT ( (pItem != NULL) && (pGuideBook != NULL) );
// 	CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetAncestor(GBCLASSID_TESTCONTROL);

	if (pItem->GetClassID() != GBCLASSID_SAFETY)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("ImportSets: not in safety"));
		return;
	}

	CString strFile;
	strFile = _P_GetInstallPath();
	strFile += _T("*.pdf");
	CString strFilter;
	strFilter = _T("PDF定值文件(*.pdf)|*.pdf||");

	if (!PopupOpenFileDialog(AfxGetMainWnd(), strFile, strFilter, _T("pdf")))
	{
		return;
	}

	CStesFilePdfTool oStesFilePdfTool;
	oStesFilePdfTool.SetCpus(pDevice->GetCpus());
	oStesFilePdfTool.ImportFile(strFile);

	CSetsImportEditDlg dlg;
	dlg.m_pStesFileTool = &oStesFilePdfTool;
	dlg.DoModal();
*/

#endif
}

void GBS_Sleep(CTScriptSingleVM *pXvm, long nMs)
{
#ifdef GUIDEBOOK_DEV_MODE
	return;
#endif
	CTickCount32 oTikc;
	oTikc.DoEvents(nMs);
}
//参数二：数据配置文件，文件中配置的数据是需要导出的
void GBS_SaveExportDatas(CTScriptSingleVM *pXvm, const char *pszDestFile, const char *pszDataConfig)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	CDvmDataset *pExportDataDef = (CDvmDataset *)pGuideBook->FindByID(g_strGbExportDatasDefID);

	if (pExportDataDef == NULL)
	{
		return;
	}

	CString strSavePath;
	strSavePath.AppendFormat(_T("%s\\%s"),CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_strExportDatasSavePath.GetString(), pszDestFile);
	CString strConfigPath;
	strConfigPath = _P_GetConfigPath();
	strConfigPath.AppendFormat(_T("%s"), pszDataConfig);

	CDataGroup oDataConfig;
	BOOL bOpen = oDataConfig.OpenXmlFile(strConfigPath, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (!bOpen)
	{
		//如果配置文件不存在，则直接保存所有数据
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++SaveExportDatas++++导出数据配置文件打开失败！导出所有数据+++"));
		pExportDataDef->SaveXmlFile(strSavePath, CDataMngrXmlRWKeys::g_pXmlKeys);
		return;
	}

	CDvmDataset oDataset;
	POS pos = oDataConfig.GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)oDataConfig.GetNext(pos);
		CDvmData *pDataExport = (CDvmData *)pExportDataDef->FindByID(pData->m_strID);

		if (pDataExport == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("SaveExportDatas Err！数据【%s】不存在"), pData->m_strID.GetString());
			continue;
		}

		oDataset.AddNewChild(pDataExport);
	}

	oDataset.SaveXmlFile(strSavePath, CDataMngrXmlRWKeys::g_pXmlKeys);
	oDataset.RemoveAll();
	return;
}

void GBS_SetExportData(CTScriptSingleVM *pXvm, const char *pszName, const char *pszID, const char *pszDataType, const char *pszValue)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	CDvmDataset *pExportDataDef = (CDvmDataset *)pGuideBook->FindByID(g_strGbExportDatasDefID);

	if (pExportDataDef == NULL)
	{
		pExportDataDef = new CDvmDataset();
		pExportDataDef->m_strName = _T("外部导出数据");
		pExportDataDef->m_strID = g_strGbExportDatasDefID;
		pGuideBook->AddNewChild(pExportDataDef);
	}

	pExportDataDef->AddNewData(pszName, pszID, pszDataType, pszValue);
}

long GBS_IsDsDataExist(CTScriptSingleVM *pXvm, const char* pszDataID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	//CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pCpus->SelectDataObj(CString(pszID));
	CDataObj *pData = _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->FindDataObjByID(CString(pszDataID), -1);
	
	if (pData == NULL)
	{
		return 0;
	}
	
	return 1;
}

#ifndef _PSX_IDE_QT_
//2022-4-17
//SmartTest中，m_pTCtrlMsgRcv不是测试页面视图，因此删除节点失败，因此增加此部分，直接从界面中删除
#include "../../UITestItem/GuideBookTreeCtrl.h"
#endif
void GBS_GenSvMatchItems(CTScriptSingleVM *pXvm, const char* pszDataNameHas)
{
#ifndef GUIDEBOOK_DEV_MODE
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL); 
	CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();

#ifndef _PSX_IDE_QT_
	CGuideBookTreeCtrl *pGuideBookTree = (CGuideBookTreeCtrl*)((CTestControl*)pTestControl)->GetGbTreeCtrl();
#endif

	CDevice *pDevice = pGuideBook->GetDevice();
	CCpus *pCpus = pDevice->m_pCpus;

	//先查找Ena数据集中，名称包含SV|sv字符的数据
	CExBaseList oListDataObjs;   //查找数据的临时链表；
	pCpus->GetDataObjsByNameHas(_T("Ena"), CString(pszDataNameHas), &oListDataObjs);

	//从模板中，查找包含指定字符串的测试项目，形成临时链表；
	CExBaseList oListItems;
	Gb_GetItem_IDHas(_T("SV_ENA_TEST_"), pDevice, &oListItems);

	//智能生成对应的项目
	Gb_GenSvMatchItems(&oListDataObjs, &oListItems);

// 	//结束后，并刷新界面显示
	POS pos = oListItems.GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = (CExBaseObject *)oListItems.GetNext(pos);
		nClassID = pObj->GetClassID();

		//目前只考虑电气量项目
		if (nClassID != GBCLASSID_MACROTEST)
		{
			continue;
		}

		CMacroTest *pMacroTest = (CMacroTest *)pObj;
		CGuideBook *pGuideBook = (CGuideBook *)pMacroTest->GetAncestor(GBCLASSID_GUIDEBOOK);
		CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();

		POS pos2 = pMacroTest->GetHeadPosition();
		long nIndex = 0;
		CExBaseObject *pObj2 = NULL;
		CCommCmd *pCommCmd = NULL;
		UINT nClassID2 = 0;

		while (pos2 != NULL)
		{
			pObj2 = pMacroTest->GetNext(pos2);
			nClassID2 = pObj2->GetClassID();

			if (nClassID2 != GBCLASSID_COMMCMD)
			{
				continue;
			}

			pCommCmd = (CCommCmd *)pObj2;

			if (nIndex <= 2)
			{
				//前三个，是需要删掉的
				//pTestControl->m_oTCtrlMsgRcv.DeleteItem(pMacroTest, pCommCmd);
			
#ifndef _PSX_IDE_QT_
				if (pCommCmd->m_dwItemData != 0)
				{
					if (pGuideBookTree != NULL)
					{
					pGuideBookTree->GB_DeleteItem(pMacroTest, pCommCmd);
				}
				}
#endif
			}
			else
			{
				//从第四个开始，动态生成的
				//pTestControl->m_oTCtrlMsgRcv.InsertItem(pMacroTest, pCommCmd);
		
#ifndef _PSX_IDE_QT_
				if (pCommCmd->m_dwItemData == 0)
				{
					if (pGuideBookTree != NULL)
					{
					pGuideBookTree->GB_InsertItem(pMacroTest, pCommCmd);
				}
				}
#endif
			}


			nIndex++;
		}

		/*pTestControl->m_oTCtrlMsgRcv.OnCurrItemStateChanged(pMacroTest);*/

		CCommCmd *pEnaOn = NULL;
		CCommCmd *pReadAin = NULL;
		CCommCmd *pEnaOff = NULL;
		//电气量项目，有三个通讯命令子项目：投压板、读遥测、退压板
		pMacroTest->GenSvMatchItems_GetSubCommCmd(&pEnaOn, &pReadAin, &pEnaOff);
		pMacroTest->Delete(pEnaOn);
		pMacroTest->Delete(pReadAin);
		pMacroTest->Delete(pEnaOff);
		pEnaOn = NULL;
	}
	
	//结束后，重新刷新Container
	pGuideBook->m_nIndex = 0;
	CItemContainer* pItemContainer = (CItemContainer*)pGuideBook->GetItemContainer();
	pGuideBook->InitGuideBook();
	pTestControl->QueryFrom_Ex(pItem->m_nIndex);
	pItemContainer->SetPosByItem(pItem);
	
	oListItems.RemoveAll();
	oListDataObjs.RemoveAll();
	pItem->SetEnable(FALSE);
	//pItem->SetSelect(FALSE);
#endif
}

void GBS_SaveDvmToLocal(CTScriptSingleVM *pXvm, const char* pszFileName)
{
	CString strFileName(pszFileName);

	if (strFileName.Find(_T(".")) < 0)
	{
		strFileName += _T(".xml");
	}

	CString strPath;
	strPath = _P_GetLibraryPath();
	strPath += strFileName;

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL); 

	CDevice *pDevice = pGuideBook->GetDevice();
	CCpus *pCpus = pDevice->m_pCpus;

	pCpus->SaveModelFile(strPath);
}

void GBS_ReadDvmFromLocal(CTScriptSingleVM *pXvm, const char* pszFileName)
{
	CString strFileName(pszFileName);

	if (strFileName.Find(_T(".")) < 0)
	{
		strFileName += _T(".xml");
	}

	CString strPath;
	strPath = _P_GetLibraryPath();
	strPath += strFileName;

	if (!IsFileExist(strPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("参数错误！模型文件【%s】在Library根目录中不存在！"), pszFileName);
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL); 

	CDevice *pDevice = pGuideBook->GetDevice();
	CCpus *pCpus = pDevice->m_pCpus;

	CCpus oCpusFromFile;
	oCpusFromFile.OpenModelFile(strPath);

	pCpus->UpdataModelValue(&oCpusFromFile, TRUE);
}

void GBS_IecfgAddCnnInfoToSft(CTScriptSingleVM *pSingleVm, const char* pszItemPath, const char* pszIecfgID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem(pszItemPath);

	if (pItem == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Item [%s] not exist"), pszItemPath);
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_SAFETY)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Item [%s] is not safety"), pszItemPath);
		return;
	}

#ifdef CGuideBook_with_iecfg_file
	CSafety *pSafety = (CSafety*)pItem;

	if (pSafety->FindByID(_T("IecCnn")) != NULL)
	{//已经添加，则返回
		return;
	}

	//2023-6-6 lijunqing  清空之前的提示信息
	//pSafety->m_oListMsgs.DeleteAll();
	pSafety->DeleteAllMsgs();

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL); 

	if (pGuideBook->m_pIecCfgDevice == NULL)
	{
		pGuideBook->InitByIecfFile();
	}

	CIecCfgDevice *pIecCfgDevice = pGuideBook->m_pIecCfgDevice;

	if (pIecCfgDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("IecfgAddCnnInfoToSft: 模板没有IEC配置文件"));
		return;
	}

	CIecCfgDatasMngr *pIecfgDatasMngr = NULL;
	POS pos = pIecCfgDevice->GetHeadPosition();

	while (pos != NULL)
	{
		//配置对象
		pIecfgDatasMngr = (CIecCfgDatasMngr *)pIecCfgDevice->GetNext(pos);

		if (pszIecfgID[0] != 0)
		{//如果定义了配置对象，则判断是否为指定的配置对象
			if (pIecfgDatasMngr->m_strID != pszIecfgID)
			{
				continue;
			}
		}

		//遍历各配置对象的配置数据集合
		POS posIecfgDatas = pIecfgDatasMngr->GetHeadPosition();
		CIecCfgDatasBase *pIecfgDatas = NULL;

		while (posIecfgDatas != NULL)
		{
			pIecfgDatas = (CIecCfgDatasBase *)pIecfgDatasMngr->GetNext(posIecfgDatas);

			if (! iecfg_IsDatas(pIecfgDatas->GetClassID()))
			{
				continue;
			}

			//遍历每个控制块
			POS posData = pIecfgDatas->GetHeadPosition();
			CIecCfgDataBase *pIecfgData = NULL;

			while (posData != NULL)
			{
				pIecfgData = (CIecCfgDataBase *)pIecfgDatas->GetNext(posData);

				if (! iecfg_IsData(pIecfgData->GetClassID()))
				{
					continue;
				}

				if (pIecfgData->m_nUseFlag != 1)
				{
					continue;
				}

				CString strMsg;
				strMsg = pIecfgData->m_strIedRefDesc + _T("----------------------------------");
				strMsg.AppendFormat( _T("光口%d"), pIecfgData->m_nFiberIndex + 1);
				pSafety->AddMsg(_T("IecCnn"), strMsg);
			}
		}
	}
#endif

}

void GBS_GenTransPlayItems(CTScriptSingleVM *pXvm, const char* pszFilePath)
{
#ifndef _PSX_QT_LINUX_
#ifndef GUIDEBOOK_DEV_MODE
	CString strFilePath(pszFilePath);

	if (strFilePath.Find(_T(":")) < 0)
	{
		//相对路径
		CString strSrc = _P_GetLibraryPath();
		strSrc += _T("ComtradeFile\\");
		strFilePath = strSrc + strFilePath;
	}

	//根据模板结构，pItem为“生成批量项目”的安全措施项目。
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);
	//需要生成批量项目的父项目节点，一定是CItems节点
	CItems *pParentItems = (CItems *)pItem->GetParent();
	ASSERT(pParentItems->GetClassID() == GBCLASSID_ITEMS);

	//固定ID前缀的分类节点，作为批量生成项目的模板。批量生成后，模板项目要删除。
	CItems *pTemplateItems = (CItems *)pParentItems->FindItemByIDHas(_T("COMTRADE_")); 
	ASSERT(pTemplateItems != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL); 
	CTestControlBase *pTestControl = (CTestControlBase*)pGuideBook->GetParent();
	//2023-8-15 改为全局链表管理
	//CExBaseList oNewItemsList;  //新生成的项目，统一临时管理。统一插入树形控件。

	CXFileMngr oXFileMngr;
	oXFileMngr.SetLibraryPath(strFilePath);

	POS pos = oXFileMngr.GetHeadPosition();
	CExBaseObject *p = NULL;
	CXFile *pXFile = NULL;
	CString strPostfix;
	CString strComtradeFile;

	while (pos != NULL)
	{
		p = oXFileMngr.GetNext(pos);

		if (p->GetClassID() != CLASSID_XFILE)
		{
			continue;
		}

		pXFile = (CXFile *)p;
		pXFile->GetFilePostfix(strPostfix, FALSE);
		strPostfix.MakeLower();

		if (strPostfix != _T("cfg"))
		{
			continue;
		}

		strComtradeFile = pXFile->m_strName;
		//克隆的项目，应当包含电气量和通讯命令
		CItems *pNewItems = (CItems *)pTemplateItems->CloneEx(TRUE, TRUE);
		pParentItems->AddNewChild(pNewItems, TRUE);
		pNewItems->m_strName = ChangeFilePostfix(strComtradeFile, _T(""));
		g_oListItemsInsertToTree.AddTail(pNewItems);

		CMacroTest *pMacroTest = (CMacroTest *)pNewItems->FindItemByIDHas(_T("TRANSPLAY_"), GBCLASSID_MACROTEST);
		ASSERT(pMacroTest != NULL);

		CMacroTestPara *pMacroTestPara = pMacroTest->GetMacroTestPara();
		CMacroTestParaDatas* pParas = pMacroTestPara->GetFaultParaDatas();
		CMacroTestParaData* pPara = (CMacroTestParaData*)pParas->AddPara(_T("RecordFileName"));  //波形文件名的参数
		strComtradeFile = oXFileMngr.m_strRootPath + strComtradeFile;  //带文件名的绝对路径
		pPara->m_strExpression = strComtradeFile;
	}

#ifndef _PSX_IDE_QT_
	CGuideBookTreeCtrl *pGuideBookTree = (CGuideBookTreeCtrl*)((CTestControl*)pTestControl)->GetGbTreeCtrl();
#endif

	//删除模板项目
	//pTestControl->m_oTCtrlMsgRcv.DeleteItem(pParentItems, pTemplateItems);
#ifndef _PSX_IDE_QT_
	if (pGuideBookTree != NULL)
	{
	pGuideBookTree->GB_DeleteItem(pParentItems, pTemplateItems);
	}	
#endif
	pParentItems->Delete(pTemplateItems);

	//pGuideBookTree->PostMessage(WM_INSERT_ITEMS, (WPARAM)pParentItems, 0);

  //为了防止界面卡死，在插入树中时，通过发消息处理
	//插入所有的新增项目
	pos = g_oListItemsInsertToTree.GetHeadPosition();

	while (pos != NULL)
	{
		CItems *pNewItems = (CItems *)g_oListItemsInsertToTree.GetNext(pos);

		//pTestControl->m_oTCtrlMsgRcv.InsertItemEx(pParentItems, pNewItems);
#ifndef _PSX_IDE_QT_
		if (pGuideBookTree != NULL)
		{
		pGuideBookTree->GB_InsertItemEx(pParentItems, pNewItems);
		}
#endif
	}

	g_oListItemsInsertToTree.RemoveAll();


	//结束后，重新刷新Container
	pGuideBook->m_nIndex = 0;
	CItemContainer* pItemContainer = (CItemContainer*)pGuideBook->GetItemContainer();
	pGuideBook->InitGuideBook();
	//pItem为执行脚本的安全措施项目，为了防止脚本二次执行，将该项目enable设置为FALSE；
	pTestControl->QueryFrom_Ex(pItem->m_nIndex);
	pItemContainer->SetPosByItem(pItem);
	pItem->SetEnable(FALSE);
#endif
#endif

// 	CString strFile;
// 	strFile = _P_GetTemplatePath();
// 	strFile += _T("000_TestFor_transplay.gbxml");
// 	pGuideBook->SaveXMLFile(strFile);
}
