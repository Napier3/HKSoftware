#include "StdAfx.h"
#include "GbScript_GuideBook.h"
#include "GbItemBase.h"
#include "Device.h"
#include "../GpsPcTime/GpsPcTime.h"
#include "MacroTest.h"
#include "../../Module/MemBuffer/EquationBuffer.h"
#include "GuideBook.h"

#ifndef GUIDEBOOK_DEV_MODE
#include "../TestControl.h"
#endif

#include "../XLanguageResourceAts.h"
//Lua
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luabind.hpp"

#include "../../../Module/DataMngr/DatasetValid/DsvChoice.h"
#include "../../../Module/API/MathApi.h"
#include "../TCtrlCntrConfig.h"
#include "../FactoryBatchTestMngr.h"

#include "../../../Module/Record/Draw/DrawGlobalDef.h"

#ifndef GUIDEBOOK_DEV_MODE
#include "../TctrlCntrBaseApp.h"
extern CTCtrlCntrBaseApp *g_theTCtrlCntrApp;
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern lua_State* g_pGuideBookLua;
extern char g_pLuaReturnString[MAX_PATH];

extern long g_nLog_TestControl_Msg;

#ifndef GUIDEBOOK_DEV_MODE
CTestControl* GBS_GetTestControl2()
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	return pTestControl;
#else
	return NULL;
#endif

}
#endif


CDataObj* GBS_GetDsDataObj(long nDeviceIndex, const char* pszID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();

	if (pTestControl->GetParent() == NULL)
	{
		return pTestControl->GBS_GetDsDataObj(pItem, nDeviceIndex, pszID);
	}
	else
	{
		CTestControl *pMany = (CTestControl*)pTestControl->GetParent();
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

CReport* GBS_GetItemReport()
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CReport *pReport = pItem->GetCurrReport();

	if (pReport == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,  CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport/*L"没有报告数据"*/);
		return NULL;
	}

	return pReport;
}

CDvmDataset* GBS_GetItemReportDataEx()
{
	CReport *pReport = GBS_GetItemReport();

	if (pReport == NULL)
	{
		return NULL;
	}

	if (pReport->m_pRptDvmDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,  CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport/*L"没有报告数据"*/);
		return NULL;
	}

	return pReport->m_pRptDvmDataset;
}

CValues* GBS_GetItemReportValues()
{
	CReport *pReport = GBS_GetItemReport();

	if (pReport == NULL)
	{
		return NULL;
	}

	if (pReport->m_pValues == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,  CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport/*L"没有报告数据"*/);
		return NULL;
	}

	return pReport->m_pValues;
}

CGbItemBase* GBS_SelectGbItem(const char* pszItemPath)
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
		strErrorInfo.Format( _T("Path(%s) select %d items"), strPath, nCount);
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
void GBS_GotoItem(const char* pszItemPath)
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
// 		CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
// 		CGbItemBase *pGotoItem = (CGbItemBase*)oListDest.GetHead();
// 		pTestControl->GotoItem(pGotoItem);
// #endif
// 	}
// 
// 	oListDest.RemoveAll();

	CGbItemBase *pGotoItem = GBS_SelectGbItem(pszItemPath);

	if (pGotoItem != NULL)
	{
#ifndef GUIDEBOOK_DEV_MODE
// 		CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
// 		ASSERT (pItem != NULL);
// 
// 		CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
// 		ASSERT (pGuideBook != NULL);
// 
// 		CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
		CTestControl *pTestControl = GBS_GetTestControl2();

		if (pTestControl != NULL)
		{
			pTestControl->GotoItem(pGotoItem);
		}
#endif
	}
}

void GBS_GotoItemEx(const char* pszItemPath, long nRslt, long nAndOr)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBase *pGotoItem = GBS_SelectGbItem(pszItemPath);

	if (pGotoItem != NULL)
	{
#ifndef GUIDEBOOK_DEV_MODE
		CTestControl *pTestControl = GBS_GetTestControl2();
		CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

		if (pTestControl != NULL)
		{
			pTestControl->GBS_GotoItemEx(pItem, pGotoItem, pszItemPath, nRslt, nAndOr);
		}
#endif
	}
}

void GBS_FireTestNextMsg()
{
}

void GBS_BreakLoop(long nLevel)
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


void GBS_MtExcuteCmd(const char *pszCmd, const char *pCmdPara)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	pTestControl->GBS_MtExcuteCmd(pszCmd, pCmdPara);
#endif
}

void GBS_MtRegistPpDataMsg(const char *pszDvmDataPath)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	pTestControl->GBS_MtRegistPpDataMsg(pszDvmDataPath);
#endif
}

void GBS_MtUnRegistPpDataMsg(const char *pszDvmDataPath)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	pTestControl->GBS_MtUnRegistPpDataMsg(pszDvmDataPath);
#endif
}


void GBS_MtRegistCmdMsg(const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	pTestControl->GBS_MtRegistCmdMsg(pszCmdID, nCmdState, nCmdWParam, nCmdLParam);
#endif
}

void GBS_MtUnRegistCmdMsg(const char *pszCmdID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	pTestControl->GBS_MtUnRegistCmdMsg(pszCmdID);
#endif
}


void GBS_MtRegistPpDataMsgRange(const char *pszDvmDataPath, double dMin, double dMax)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	pTestControl->GBS_MtRegistPpDataMsgRange(pszDvmDataPath, dMin, dMax);
#endif
}


void GBS_BreakItems(long nLevel)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();

	if (nLevel < 0)
	{
		nLevel = 0;
	}

	pTestControl->m_nBreakItemsLevel = nLevel;
#endif
}

void GBS_SetUploadRptFile(const char *pszFileName)
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
double GBS_GetDsDataValue(const char* pszID)
{
	return GBS_GetDsDataValueEx(-1, pszID);
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

double GBS_GetDsDataAttr(const char* pszID, const char *pszAttrID)
{
	CString strAttrID, strValue;
	strAttrID = pszAttrID;

	CDataObj *pDataObj = GBS_GetDsDataObj(-1, pszID);

	if (pDataObj != NULL)
	{
		pDataObj->GetValueByID(strAttrID, strValue);
#ifdef _UNICODE
		return _wtof(strValue);
#else
		return atof(strValue);
#endif
	}
	else
	{
		return 0;
	}
}

void GBS_SetDsDataValue(const char* pszID, double dVal)
{
	GBS_SetDsDataValueEx(-1, pszID, dVal);
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
const char* GBS_GetDsDataValueStr(const char* pszID)
{
	return GBS_GetDsDataValueStrEx(-1, pszID);
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
void GBS_SetDsDataValueStr(const char* pszID, const char* pszVal)
{
	GBS_SetDsDataValueStrEx(-1, pszID, pszVal);
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
double GBS_GetDsDataValueEx(long nDeviceIndex, const char* pszID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();

	if (pTestControl->GetParent() == NULL)
	{
		return pTestControl->GBS_GetDsDataValueEx(pItem, nDeviceIndex, pszID);
	}
	else
	{
		CTestControl *pMany = (CTestControl*)pTestControl->GetParent();
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

void GBS_SetDsDataValueEx(long nDeviceIndex, const char* pszID, double dVal)
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("dsData id(%s) not exist"), (CString)pszID);

// 		CString strErrorInfo;
// 		CString strID(pszID);
// 		strErrorInfo.Format( L"Set id(%s) not exist", strID);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
}
const char* GBS_GetDsDataValueStrEx(long nDeviceIndex, const char* pszID)
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("dsData id(%s) not exist"), (CString)pszID);
	}

	return g_pLuaReturnString;
}
void GBS_SetDsDataValueStrEx(long nDeviceIndex, const char* pszID, const char* pszVal)
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("dsData id(%s) not exist"), (CString)pszID);
	}
}


long GBS_CalAinError(double dAbsCal, double dRelCal, double dAbsErr, double dRelErr)
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


long GBS_CalAinError(double dAbsCal, double dRelCal, double dAbsErr, double dRelErr, CValue *pDataRst)
{
	long nRsltJdg = GBS_CalAinError(dAbsCal, dRelCal, dAbsErr, dRelErr);

	if (nRsltJdg == 1)
	{
		if (pDataRst != NULL)
		{
			pDataRst->m_strValue = /*g_strResultDescValueCorrect*/CXLanguageResourceAtsBase::g_sLangTxt_Qualified;
		}
	}
	else
	{
		if (pDataRst != NULL)
		{
			pDataRst->m_strValue = /*g_strResultDescValueIncorrect*/	CXLanguageResourceAtsBase::g_sLangTxt_Unqualified;
		}
	}

	return nRsltJdg;
}

void GBS_CalAinError(double dValue, double dRefValue, double &dAbsCal, double &dRelCal, BOOL bIsAngle)
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

CReport* GBS_GetReport(CGbItemBase *pItem, long nIndex)
{
#ifdef GUIDEBOOK_DEV_MODE
	return pItem->GetReport(nIndex);
#else

	CGbItemBase *pCurrItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CTestControl *pTestControl = (CTestControl*)pItem->GetAncestor(GBCLASSID_TESTCONTROL);

	if (pItem == pCurrItem)
	{
		return pTestControl->GetReport(pItem, nIndex);
	}
	else
	{
		if (!g_theTCtrlCntrApp->IsSaveRptToDB())
		{
			return pTestControl->GetReport(pItem, nIndex);
		}
		else
		{
			CGuideBook *pGuideBook = (CGuideBook*)pCurrItem->GetAncestor(GBCLASSID_GUIDEBOOK);
			CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
			return pTestControl->GBS_GetReport(pItem, nIndex);
		}
	}

#endif
}

void GBS_AddDataErrorToRpt_Rslt_Ex(CValues *pValues, const CString &strValueID, long nRslt)
{
	if (g_bAddDataErrorValueToRpt)
	{
		Gb_AddDataErrorToRpt_Rslt(pValues, strValueID, nRslt);
	}
}

long GBS_CalAinError(const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ParaError3/*_T("CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	
	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnTest/*L"CalAinErr函数只用用于测试量值测试项目"*/);
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

	CReport *pReport = GBS_GetReport(pItem, -1); //pItem->GetReport(-1);
	CValues *pValues = pReport->GetValues();
	CValue *pData = (CValue *)pValues->FindByID(strID);

	if (pData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnUnExist/*L"CalAinErr函数数据【%s】不存在"*/, strID);
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

	nRsltJdg = GBS_CalAinError(dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRelTemp);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d")
			, dValue,dRefVal, dValErrAbs, dValErrRelTemp, dAbsErr, dRelErr, nRsltJdg);
	}

	GBS_AddDataErrorToRpt_Rslt_Ex(pValues, strID, nRsltJdg);
	//2019-1-2   将数据调整到顶部，方便查阅
	pValues->BringToHead(pDataRst);
	pValues->BringToHead(pDataRel);
	pValues->BringToHead(pDataAbs);
	pValues->BringToHead(pData);

#endif

	return nRsltJdg;
}

long GBS_CalAinErrorEx(double dRate, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ParaError3/*_T("CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	
	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnTest/*L"CalAinErr函数只用用于测试量值测试项目"*/);
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

	CReport *pReport = GBS_GetReport(pItem, -1); //pItem->GetReport(-1);
	CValues *pValues = pReport->GetValues();
	CValue *pData = (CValue *)pValues->FindByID(strID);

	if (pData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnUnExist/*L"CalAinErr函数数据【%s】不存在"*/, strID);
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

	nRsltJdg = GBS_CalAinError(dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRelTemp);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d")
			, dValue,dRefVal, dValErrAbs, dValErrRelTemp, dAbsErr, dRelErr, nRsltJdg);
	}

	GBS_AddDataErrorToRpt_Rslt_Ex(pValues, strID, nRsltJdg);
#endif

	return nRsltJdg;
}

long GBS_CalAinErrorNom(double dRate, const char *pszAinID, double dRefVal, double dNom, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ParaError3/*_T("CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	
	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnTest/*L"CalAinErr函数只用用于测试量值测试项目"*/);
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

	CReport *pReport = GBS_GetReport(pItem, -1); //pItem->GetReport(-1);
	CValues *pValues = pReport->GetValues();
	CValue *pData = (CValue *)pValues->FindByID(strID);

	if (pData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnUnExist /*L"CalAinErr函数数据【%s】不存在"*/, strID);
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

	nRsltJdg = GBS_CalAinError(dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRelTemp);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f , NOM=%.5f, AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d")
			, dValue,dRefVal,dNom, dValErrAbs, dValErrRelTemp, dAbsErr, dRelErr, nRsltJdg);
	}

	GBS_AddDataErrorToRpt_Rslt_Ex(pValues, strID, nRsltJdg);
#endif

	return nRsltJdg;
}

long GBS_CalAinStdError(double dRate, const char *pszAinID,double dRefVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ParaError4/*_T("CalAinStdError函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_StdErrorFctnTest/*L"CalAinStdError函数只用用于测试量值测试项目"*/);
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

	CTestControl *pTestControl = GBS_GetTestControl2();
	CValues *pValues = NULL;
	double dValue = 0;
	CValue *pData = NULL;
	CReport *pReport = NULL;

	if (!pTestControl->CanRunCommCmdFinalResultScript(pCommCmd))
	{
		pReport = GBS_GetReport(pCommCmd, -1); //pCommCmd->GetReport(-1);
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_StdErrorFctnUnExistData/*L"CalAinStdError函数数据【%d】不存在不够"*/, nReports);
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_StdErrorFctnUnExistData/*L"CalAinStdError函数数据【%d】不存在不够"*/, nValueCount);
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
	pReport = GBS_GetReport(pItem, -1); //pItem->GetReport(-1);
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

	nRsltJdg = GBS_CalAinError(dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRel);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f  nRsltJdg=%d")
			, dValStdCal,dRefVal, dValErrAbs, dValErrRel, dAbsErr, dRelErr, nRsltJdg);
	}

	GBS_AddDataErrorToRpt_Rslt_Ex(pValues, strID, nRsltJdg);
#endif

	return nRsltJdg;
}



long GBS_FlterCalError(const CString &strValID, const char* pszAbsErrID, const char *pszRelErrID
					   , CExBaseList &oList, CValue **ppAbsData, CValue **ppRelData)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_FlterFctnTest/*L"FlterCalErrorMax函数只用用于测试量值测试项目"*/);
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

	CReport *pReport = GBS_GetReport(pItem, -1); //pItem->GetReport(-1);
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

long GBS_FlterCalError(double dValue, double dRefVal, double dAbsErr, double dRelErr, CValue *pAbsData, CValue *pRelData,BOOL bIsAngle)
{
	double dAbsCal = 0, dRelCal = 0;

	//计算误差
	GBS_CalAinError(dValue, dRefVal, dAbsCal, dRelCal, bIsAngle);
	
	//误差判断
	long nRslt = GBS_CalAinError(dAbsCal, dRelCal, dAbsErr, dRelErr);
	
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

long GBS_FlterCalErrorMax(const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,CXLanguageResourceAtsBase::g_sLangTxt_ParaError3 /*_T("CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_FlterFctnTest/*L"FlterCalErrorMax函数只用用于测试量值测试项目"*/);
		return 0;
	}

	CString strID;
	CExBaseList oList;
	CValue *pAbsData = NULL;
	CValue *pRelData = NULL;

	strID = pszValID;

	//获得所有的数据对象
	GBS_FlterCalError(strID, pszAbsErrID, pszRelErrID, oList, &pAbsData, &pRelData);

#ifdef GUIDEBOOK_DEV_MODE

	return 1;

#else

	if (oList.GetCount() == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnUnExist/*L"CalAinErr函数数据【%s】不存在"*/, strID);
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
	return GBS_FlterCalError(dValue, dRefVal, dAbsErr, dRelErr, pAbsData, pRelData, (strID.Find(_T("ang$f")) > 0));

#endif
}


long GBS_FlterCalErrorMin(const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ParaError3/*_T("CalAinErr函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_FlterFctnTest/*L"FlterCalErrorMax函数只用用于测试量值测试项目"*/);
		return 0;
	}

	CString strID;
	CExBaseList oList;
	CValue *pAbsData = NULL;
	CValue *pRelData = NULL;

	strID = pszValID;
	GBS_FlterCalError(strID, pszAbsErrID, pszRelErrID, oList, &pAbsData, &pRelData);

#ifdef GUIDEBOOK_DEV_MODE

	return 1;

#else

	if (oList.GetCount() == 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnUnExist/*L"CalAinErr函数数据【%s】不存在"*/, strID);
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
	return GBS_FlterCalError(dValue, dRefVal, dAbsErr, dRelErr, pAbsData, pRelData, (strID.Find(_T("ang$f")) > 0));

#endif
}

long GBS_CalAinError2(const char *pszAinID, const char *pszAinBaseID, double dStdVal, double dAbsErr, double dRelErr)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	
	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnTest/*L"CalAinErr函数只用用于测试量值测试项目"*/);
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

	CReport *pReport = GBS_GetReport(pItem, -1); //pItem->GetReport(-1);
	CValues *pValues = pReport->GetValues();
	CValue *pData = (CValue *)pValues->FindByID(strID);
	CValue *pRefData = (CValue *)pValues->FindByID(strIDBase);

	if (pData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnUnExist/*L"CalAinErr函数数据【%s】不存在"*/, strID);
		return 0;		
	}

	if (pRefData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ErrFctnUnExist/*L"CalAinErr函数数据【%s】不存在"*/, strIDBase);
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

	nRsltJdg = GBS_CalAinError(dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRelTemp);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  ,Rate=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d")
		, dValue,dValueRef, dStdVal, dValErrAbs, dValErrRelTemp, dAbsErr, dRelErr, nRsltJdg);

	GBS_AddDataErrorToRpt_Rslt_Ex(pValues, strID, nRsltJdg);
#endif

	return nRsltJdg;
}

long GBS_CalAinStdError2(const char *pszAinID, const char *pszAinBaseID, double dStdVal, double dAbsErr, double dRelErr)
{
	if (dAbsErr < 0 && dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ParaError4/*_T("CalAinStdError函数:绝对误差限[%f]和相对误差限[%f]都小于0，参数错误！")*/, dAbsErr, dRelErr);
		return 1;
	}

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_StdErrorFctnTest/*L"CalAinStdError函数只用用于测试量值测试项目"*/);
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

	CTestControl *pTestControl = GBS_GetTestControl2();
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
		pReport = GBS_GetReport(pCommCmd, -1); //pCommCmd->GetReport(-1);
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_StdErrorFctnUnExistData/*L"CalAinStdError函数数据【%s】不存在不够"*/);
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_StdErrorFctnUnExistData/*L"CalAinStdError函数数据【%s】不存在不够"*/);
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
	pReport = GBS_GetReport(pItem, -1); //pItem->GetReport(-1);
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

	nRsltJdg = GBS_CalAinError(dValErrAbs, dValErrRel, dAbsErr, dRelErr, pDataRst);

	if (pDataRel != NULL)
	{
		pDataRel->m_strValue.Format(_T("%f"), dValErrRel);
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Val=%.5f  ,Std=%.5f  AbsErrCal=%.5f  RealErrCal=%.5f  AbsErrSet=%.5f  RealErSet=%.5f nRsltJdg=%d" )
			, dValStdCal,dStdVal, dValErrAbs, dValErrRel, dAbsErr, dRelErr, nRsltJdg);
	}

	GBS_AddDataErrorToRpt_Rslt_Ex(pValues, strID, nRsltJdg);
#endif

	return nRsltJdg;
}

double GBS_CalVariation(double dValue, double dTheoreticalVal, double dBaseValue, double dRate)
{
	return ((dTheoreticalVal - dValue) / dBaseValue) * dRate;
}

long GBS_CalVariationErr(double dValue, double dTheoreticalVal, double dBaseValue, double dRate, double dRelErr)
{
	if (dRelErr < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ParaError5/*_T("CalVariationEror函数:误差限[%f]都小于0，参数错误！")*/, dRelErr);
		return 1;
	}

	double dVarVal = GBS_CalVariation(dValue, dTheoreticalVal, dBaseValue, dRate);
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

long GBS_CalVariationErrEx(const char *pszAinID, const char *pszTheoreticalID, const char *pszBaseValueID, const char *pszRsltID, const char *pszRelErr, double dRate)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_VariationFctnTest/*L"CalVariationErrorEx函数只用用于测量值测试项目"*/);
		return 1;
	}

	CMacroTest *pMacroTest = (CMacroTest*)pItem->GetParent();

	if (pMacroTest->GetClassID() != GBCLASSID_MACROTEST)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_VariationFctnItem/*L"CalVariationErrorEx函数所在的项目的父项目不是电气量项目"*/);
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,CXLanguageResourceAtsBase::g_sLangTxt_FctnVariousUnExist /*_T("CalVariationErrorEx函数:误差限变量[%s]不存在！")*/, strErrID);
			return 1;
		}

		dRelErr = CString_To_double(pError->m_strValue);
	}

	
	if (dRelErr <= 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_ParaError5/*_T("CalVariationErrorEx函数:误差限[%f]小于0，参数错误！")*/, dRelErr);
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

	CReport *pReport = GBS_GetReport(pItem, -1); //pItem->GetReport(-1);
	CValues *pValues = pReport->GetValues();
	CReport *pReport2 = GBS_GetReport(pMacroTest, -1); //pMacroTest->GetReport(-1);
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,  CXLanguageResourceAtsBase::g_sLangTxt_VariationFctnUnExist3/*L"CalVariationErrorEx函数数据【实测值】【%s】不存在"*/, strID);
		return 0;		
	}

	if (pTheoreticalData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_VariationFctnUnExist4/*L"CalVariationErrorEx函数数据【理论值】【%s】不存在"*/, strTheoreticalID);
		return 0;		
	}

	if (pDataBaseVal == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_VariationFctnUnExist5/*L"CalVariationErrorEx函数：测试参数基准值【%s】不存在"*/, strBaseValID);
		return 0;		
	}

	if (pDataRst == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_VariationFctnUnExist6/*L"CalVariationErrorEx函数数据【结果变量】【%s】不存在"*/, strRsltID);
	}

	double dValue = CString_To_double(pData->m_strValue);
	double dTheoreticalValue = CString_To_double(pTheoreticalData->m_strValue);
	double dBaseValue = CString_To_double(pDataBaseVal->m_strValue);

	double dCalVarVal = GBS_CalVariation(dValue, dTheoreticalValue, dBaseValue, dRate);
	
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
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_ResultJude/*_T("实测值=%.5f  ,理论值=%.5f  ,基准值=%.5f  变差=%.5f 误差限=%.5f  结果判断=%d")*/
		, dValue, dTheoreticalValue, dBaseValue, dCalVarVal, dRelErr, nRsltJdg);
	}

#endif

	return nRsltJdg;
}


// 获取定值数据
// pszID：数据的ID
double GBS_GetSetValue(const char* pszID)
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
	return GBS_GetDsDataValue(pszID);
}

void GBS_SetSetValue(const char* pszID, double dVal)
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
	GBS_SetDsDataValue(pszID, dVal);
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
double GBS_GetSysParaValue(const char* pszID)
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
		strErrorInfo.Format( _T("SysPara id(%s) not exist"), strID);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
		//lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
		//throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
#ifdef _UNICODE
		dValue = _wtof(pData->m_strValue);
#else
		dValue = atof(pData->m_strValue);
#endif
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("GetSysParaValue([%s] [%.f]")
//		, CString(pszID), dValue);

	return dValue;
}

void GBS_SetSysParaValue(const char* pszID, double dValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas != NULL);
	CDataObj  *pData = (CDataObj*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas->FindByID(CString(pszID));

	if (pData == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SysPara id(%s) not exist"), (CString)pszID);

		CString strErrorInfo;
		CString strID(pszID);
		strErrorInfo.Format( _T("SysPara id(%s) not exist"), strID);
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
double GBS_GetTestParaValue(const char* pszID)
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
		strErrorInfo.Format(_T("SysPara id(%s) not exist"), strID);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
#ifdef _UNICODE
		dValue = _wtof(pData->m_strValue);
#else
		dValue = atof(pData->m_strValue);
#endif
	}

	return dValue;
}

const char* GBS_GetTestParaStr(const char* pszID)
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
void GBS_SetTestParaValue(const char* pszID, double dValue)
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
		strErrorInfo.Format(_T("SysPara id(%s) not exist"), strID);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		pData->m_strValue.Format(_T("%f"), dValue);
	}
}

void GBS_SetTestParaStr(const char* pszID, const char *pszValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice != NULL);
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas != NULL);
	CDataObj  *pData = (CDataObj*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pDevice->m_pSysParas->FindByID(CString(pszID));

	if (pData == NULL)
	{
		CString strErrorInfo;
		CString strID(pszID);
		strErrorInfo.Format(_T("SysPara id(%s) not exist"), strID);
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
void GBS_SetItemShow(const char* pszItemPath, long nShow)
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
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Item(%s) SHOW=%d"), (CString)pItem->m_strID, nShow);
			}
		}
	}

	oListDest.RemoveAll();
}


// 获取满足条件的项目的Show属性
// pszItemPath为Item的路径
long GBS_GetItemShow(const char* pszItemPath)
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
		strErrorInfo.Format( _T("Path(%s) select %d items"), strPath, nCount);
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
		strErrorInfo.Format( _T("Path(%s) select %d items"), strPath, nCount);
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
void GBS_SetItemEnable(const char* pszItemPath, long nEnable)
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
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Item(%s) ENABLE=%d"), (CString)pItem->m_strID, nEnable);
			}
		}
	}

	oListDest.RemoveAll();
}

// 获取满足条件的项目的Enable属性
// pszItemPath为Item的路径
long GBS_GetItemEnable(const char* pszItemPath)
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
		strErrorInfo.Format(_T("Path(%s) select %d items"), strPath, nCount);
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
		strErrorInfo.Format(_T("Path(%s) select %d items"), strPath, nCount);
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

void GBS_SetItemSelect(const char* pszItemPath, long nSelect)
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

long GBS_GetItemSelect(const char* pszItemPath)
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
		strErrorInfo.Format(_T("Path(%s) select %d items"), strPath, nCount);
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
		strErrorInfo.Format(_T("Path(%s) select %d items"), strPath, nCount);
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
void GBS_SetItemName(const char* pszItemPath, const char* pszName)
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Item(%s) name=[%s]"), (CString)pItem->m_strID, (CString)pItem->m_strName);
	}

	oListDest.RemoveAll();
}

// 获取满足条件的项目的Name属性
// pszItemPath为Item的路径
const char* GBS_GetItemName(const char* pszItemPath)
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
		strErrorInfo.Format(_T("Path(%s) select %d items"), strPath, nCount);
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
void GBS_SetRsltJdg(CGbItemBase *pItem, long nResult)
{
	CReport *pReport = GBS_GetReport(pItem, -1);
	pItem->SetRsltJdg(pReport, nResult);
}

void GBS_SetItemResultJudge(const char* pszItemPath, long nResult)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = NULL;

	while (pos != NULL)
	{
		pItem = oListDest.GetNext(pos);

		GBS_SetRsltJdg(pItem, nResult);//pItem->SetRsltJdg(nResult);
		//发送项目显示改变消息 #########
		//显示函数调用信息
	}

	oListDest.RemoveAll();
}

long GBS_GetItemResultJudge(const char* pszItemPath)
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), strPath, nCount);
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Path(%s) select %d items"), strPath, nCount);
		//lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
		//throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
		nResult = pItem->GetRsltJdg();

		if (pItem->m_nState == TEST_STATE_INLEGIBLE)
		{
			nResult = 0;
		}
	}

	oListDest.RemoveAll();
	return nResult;
}




// 设置满足条件的项目的数据的值
// pszItemPath为Item的路径
void GBS_SetItemParaValue(const char* pszItemPath, const char* pszValID, double dValue)
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
			strErrorInfo.Format( CXLanguageResourceAtsBase::g_sLangTxt_SetItemIDUnExist/*L"SetItemParaValue ID不存在,Path(%s) ID(%s) items"*/, strPath, strID);
			CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 			lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 			throw luabind::error(g_pGuideBookLua);		//抛出异常信息
		}
	}

	oListDest.RemoveAll();
}

void GBS_SetItemParaValueStr(const char* pszItemPath, const char* pszValID, const char *pszValue)
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
			strErrorInfo.Format( CXLanguageResourceAtsBase::g_sLangTxt_SetItemIDUnExist/*L"SetItemParaValue ID不存在,Path(%s) ID(%s) items"*/, strPath, strID);
			CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 			lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 			throw luabind::error(g_pGuideBookLua);		//抛出异常信息
		}
	}

	oListDest.RemoveAll();
}

double GBS_GetItemParaValueEx(CGbItemBase *pItem, const char* pszValID)
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
		if (!g_theTCtrlCntrApp->IsSaveRptToDB())
		{
			return pItem->GetItemParaValue(pszValID);
		}
		else
		{
			CGuideBook *pGuideBook = (CGuideBook*)pCurrItem->GetAncestor(GBCLASSID_GUIDEBOOK);
			CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
			return pTestControl->GBS_GetItemParaValueEx(pItem, pszValID);
		}
	}
*/

#endif
}

double GBS_GetItemParaValue(const char* pszItemPath, const char* pszValID)
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
		strErrorInfo.Format(_T("Path(%s) select %d items"), strPath, nCount);
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
		strErrorInfo.Format(_T("Path(%s) select %d items"), strPath, nCount);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
// 		lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else
	{
		 //2019-4-16  多装置测试，报告数据保存到本地数据库，结果判断时要取得其他项目的报告，因此改进此功能
		pItem = (CGbItemBase*)oListDest.GetHead();
		dValue = GBS_GetItemParaValueEx(pItem, pszValID);//pItem->GetItemParaValue(pszValID); 
	}

	oListDest.RemoveAll();
	return dValue;
}

const char* GBS_GetItemParaString(const char* pszItemPath, const char* pszValID)
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
		dValue = GBS_GetItemParaValueEx(pItem, pszValID);//pItem->GetItemParaValue(pszValID); 
		sprintf(g_pLuaReturnString, "%f", dValue);
	}

	oListDest.RemoveAll();
	return g_pLuaReturnString;
}

void GBS_GetItemTestTime_Mode(const char* pszItemPath, CString &strTime, long nMode)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItems(pszItemPath, oListDest);
	CGbItemBase *pItem = NULL;
	long nCount = oListDest.GetCount();

	if (nCount == 1)
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
		CReport *pReport = GBS_GetReport(pItem, -1); //pItem->GetReport(-1);

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

const char* GBS_GetItemTestTime(const char* pszItemPath)
{
	CString strTime;
	
	GBS_GetItemTestTime_Mode(pszItemPath, strTime, 0);

	CString_to_char(strTime, g_pLuaReturnString);
	return g_pLuaReturnString;
}

const char* GBS_GetItemTestBeginTime(const char* pszItemPath)
{
	CString strTime;

	GBS_GetItemTestTime_Mode(pszItemPath, strTime, 1);

	CString_to_char(strTime, g_pLuaReturnString);
	return g_pLuaReturnString;
}

const char* GBS_GetItemTestEndTime(const char* pszItemPath)
{
	CString strTime;

	GBS_GetItemTestTime_Mode(pszItemPath, strTime, 2);

	CString_to_char(strTime, g_pLuaReturnString);
	return g_pLuaReturnString;
}

//通讯命令的参数脚本函数  2019-3-19
void GBS_ClearCommCmdParas(const char* pszItemPath)
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

void GBS_AddCommCmdParaValue_String(const char* pszItemPath, const char* pszValID, const CString &strValue)
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
		strErrorInfo.Format( CXLanguageResourceAtsBase::g_sLangTxt_SetItemIDUnExist/*L"SetItemParaValue ID不存在,Path(%s) ID(%s) items"*/, strPath, strValID);
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

void GBS_AddCommCmdParaValue(const char* pszItemPath, const char* pszValID, double dValue)
{
	CString strValue;
	strValue.Format(_T("%f"), dValue);
	GBS_AddCommCmdParaValue_String(pszItemPath, pszValID, strValue);
}

void GBS_AddCommCmdParaValue_Long(const char* pszItemPath, const char* pszValID, long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	GBS_AddCommCmdParaValue_String(pszItemPath, pszValID, strValue);
}

void GBS_AddCommCmdParaValue_String(const char* pszItemPath, const char* pszValID, const char *pszValue)
{
	CString strValue;
	strValue = pszValue;
	GBS_AddCommCmdParaValue_String(pszItemPath, pszValID, strValue);
}

void GBS_AddRptMapData(const char* pszValID)
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

BOOL GBS_SetItemReportValue(CGbItemBase *pItem, const CString &strValueID, const CString &strValue)
{
	CReport *pReport = GBS_GetReport(pItem, -1);
	return pReport->SetValue(strValueID, strValue);
}

//报告数据
void GBS_SetItemReportValue(const char* pszItemPath, const char* pszValID, double dValue)
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
		if (!GBS_SetItemReportValue(pItem, strValID, bstrVal))
		{
			//ID不存在
			oListDest.RemoveAll();

#ifdef GUIDEBOOK_DEV_MODE
			CString strErrorInfo;
			CString strPath(pszItemPath);
			CString strID(pszValID);
			strErrorInfo.Format( CXLanguageResourceAtsBase::g_sLangTxt_SetItemIDUnExist2/*L"SetReportValue ID不存在,Path(%s) ID(%s) items"*/, strPath, strID);
			CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
#endif
// 			lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 			throw luabind::error(g_pGuideBookLua);	
		}
	}

	oListDest.RemoveAll();
}

void GBS_SetItemReportValueString(const char* pszItemPath, const char* pszValID, const char* pszValString)
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
		if (!GBS_SetItemReportValue(pItem, strValID, bstrVal))
		{
			//ID不存在
			oListDest.RemoveAll();
#ifdef GUIDEBOOK_DEV_MODE
			CString strErrorInfo;
			CString strPath(pszItemPath);
			CString strID(pszValID);
			strErrorInfo.Format( CXLanguageResourceAtsBase::g_sLangTxt_SetItemIDUnExist2/*L"SetReportValue ID不存在,Path(%s) ID(%s) items"*/, strPath, strID);
			CLogPrint::LogString(XLOGLEVEL_TRACE, strErrorInfo);
#endif
// 			lua_pushstring(g_pGuideBookLua,(_bstr_t)strErrorInfo);
// 			throw luabind::error(g_pGuideBookLua);	
		}
	}

	oListDest.RemoveAll();
}

CGbItemBase* GBS_GetItem(const char* pszItemPath)
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_PathItem/*"路径检索的项目不唯一,Path(%s) select %d items"*/, CString(pszItemPath), nCount);
//		CLogPrint::LogString(XLOGLEVEL_TRACE, CString(pszErrorInfo));
// 		lua_pushstring(g_pGuideBookLua,pszErrorInfo);
// 		throw luabind::error(g_pGuideBookLua);		//抛出异常信息
	}
	else if (nCount == 0)
	{
		//char pszErrorInfo[MAX_PATH];
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_PathItem2 /*"路径指定的项目不存在,Path(%s) select %d items"*/, CString(pszItemPath), nCount);
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

double GBS_GetItemReportValue(CGbItemBase *pItem, const char* pszValID)
{
	CReport *pReport = GBS_GetReport(pItem, -1);

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

char* GBS_GetItemReportValue(CGbItemBase *pItem, const char* pszValID, char *pszValue, long nIndex)
{
	CReport *pReport = GBS_GetReport(pItem, nIndex);

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

double GBS_GetItemReportValue(const char* pszItemPath, const char* pszValID)
{
	CGbItemBase *pItem = GBS_GetItem(pszItemPath);
	double dValue = 0;

	if (pItem != NULL)
	{
		//dValue = pItem->GetItemReportValue(pszValID);
		dValue = GBS_GetItemReportValue(pItem, pszValID);
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

long GBS_GetItemReportValueLong(const char* pszItemPath, const char* pszValID)
{
	double dValue = GBS_GetItemReportValue(pszItemPath, pszValID);
	long nValue = (long)dValue;
	return nValue;
}


const char* GBS_GetItemReportValueString(const char* pszItemPath, const char* pszValID)
{
	CGbItemBase *pItem = GBS_GetItem(pszItemPath);

	if (pItem != NULL)
	{
		//pItem->GetItemReportValue(pszValID, g_pLuaReturnString);
		GBS_GetItemReportValue(pItem, pszValID, g_pLuaReturnString, -1);
	}
	else
	{
		g_pLuaReturnString[0] = 0;
	}

	return g_pLuaReturnString;
}

double GBS_GetItemReportValueEx(const char* pszItemPath, const char* pszValID, long nIndex)
{
	GBS_GetItemReportValueStringEx(pszItemPath, pszValID, nIndex);

	if (g_pLuaReturnString[0] == 0)
	{
		return 0;
	}
	else
	{
		return atof(g_pLuaReturnString);
	}
}

long GBS_GetItemReportValueLongEx(const char* pszItemPath, const char* pszValID, long nIndex)
{
	GBS_GetItemReportValueStringEx(pszItemPath, pszValID, nIndex);

	if (g_pLuaReturnString[0] == 0)
	{
		return 0;
	}
	else
	{
		return atol(g_pLuaReturnString);
	}
}

const char* GBS_GetItemReportValueStringEx(const char* pszItemPath, const char* pszValID, long nIndex)
{
	CGbItemBase *pItem = GBS_GetItem(pszItemPath);

	if (pItem != NULL)
	{
		//pItem->GetItemReportValue(pszValID, g_pLuaReturnString, nIndex);
		GBS_GetItemReportValue(pItem, pszValID, g_pLuaReturnString, nIndex);
	}
	else
	{
		g_pLuaReturnString[0] = 0;
	}

	return g_pLuaReturnString;
}

long GBS_GetItemReportCount(const char* pszItemPath)
{
	CGbItemBase *pItem = GBS_GetItem(pszItemPath);

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

void GBS_ClearReports(const char* pszItemPath)
{
	CGbItemBase *pItem = GBS_GetItem(pszItemPath);

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

void GBS_CalRptValMax(CExBaseList *pList, const CString &strValID, double &dMax)
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
			GBS_CalRptValMax(pItems, strValID, dMax);
		}
		else if ((nClassID & GBCLASSID_ITEMBASE) == GBCLASSID_ITEMBASE)
		{
			CGbItemBase *pItemBase = (CGbItemBase*)pItem;
			pItemBase->CalRptValMax(strValID, dMax);
		}
	}
}


double GBS_CalRptValMax(const char* pszItemPath, const char* pszValID, double dDefVal)
{
	CGbItemBase *pItem = GBS_GetItem(pszItemPath);

	if (pItem == NULL)
	{
		return dDefVal;
	}

	CString strValID;
	strValID = pszValID;
	double dMax = dDefVal;

	if (pItem->GetClassID() == GBCLASSID_ITEMS)
	{
		GBS_CalRptValMax(pItem, strValID, dMax);
	}
	else
	{
		pItem->CalRptValMax(strValID, dMax);
	}

	return dMax;
}


void GBS_CalRptValMin(CExBaseList *pList, const CString &strValID, double &dMin)
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
			GBS_CalRptValMin(pItems, strValID, dMin);
		}
		else if ((nClassID & GBCLASSID_ITEMBASE) == GBCLASSID_ITEMBASE)
		{
			CGbItemBase *pItemBase = (CGbItemBase*)pItem;
			pItemBase->CalRptValMin(strValID, dMin);
		}
	}
}

double GBS_CalRptValMin(const char* pszItemPath, const char* pszValID, double dDefVal)
{
	CGbItemBase *pItem = GBS_GetItem(pszItemPath);

	if (pItem == NULL)
	{
		return dDefVal;
	}

	CString strValID;
	strValID = pszValID;
	double dMin = dDefVal;

	if (pItem->GetClassID() == GBCLASSID_ITEMS)
	{
		GBS_CalRptValMin(pItem, strValID, dMin);
	}
	else
	{
		pItem->CalRptValMin(strValID, dMin);
	}

	return dMin;
}


void GBS_CalRptValAvg(CExBaseList *pList, const CString &strValID, double &dValue, long &nCount)
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
			GBS_CalRptValAvg(pItems, strValID, dValue, nCount);
		}
		else if ((nClassID & GBCLASSID_ITEMBASE) == GBCLASSID_ITEMBASE)
		{
			CGbItemBase *pItemBase = (CGbItemBase*)pItem;
			pItemBase->CalRptValSum(strValID, dValue, nCount);
		}
	}
}

double GBS_CalRptValAvg(const char* pszItemPath, const char* pszValID, double dDefVal)
{
	CGbItemBase *pItem = GBS_GetItem(pszItemPath);

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
		GBS_CalRptValAvg(pItem, strValID, dValue, nCount);
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
long GBS_LGetItemReportDataCount(const char* pszItemPath, const char *pszDataID, long nDataValue)
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
		strErrorInfo.Format( CXLanguageResourceAtsBase::g_sLangTxt_PathItem/*L"路径检索的项目不唯一,Path(%s) select %d items"*/, strPath, nCount);
	}
	else if (nCount == 0)
	{
		//显示消息：路径指定的项目不存在
		CString strErrorInfo;
		CString strPath(pszItemPath);
		strErrorInfo.Format( CXLanguageResourceAtsBase::g_sLangTxt_PathItem2/*L"路径指定的项目不存在,Path(%s) select %d items"*/, strPath, nCount);
	}
	else
	{
		pItem = (CGbItemBase*)oListDest.GetHead();
		nDataCount = pItem->LGetItemReportDataCount(CString(pszDataID), nDataValue);
	}

	oListDest.RemoveAll();
	return nDataCount;
}

double GBS_GetItemReportExValue(long nIndex, const char* pszValID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;
	double dValue = 0;

	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	dValue = pItem->GetItemReportExValue(nIndex, pszValID);
	
	return dValue;
}


BOOL GBS_GetItemReportExValue(const char* pszDataID, const char* pszValID, CString &strValue)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	return pItem->GetItemReportExValue(pszDataID, pszValID, strValue);
}


double GBS_GetItemReportExValue_D(const char* pszDataID, const char* pszValID)
{
	double dValue = 0;
	CString strValue;

	if (GBS_GetItemReportExValue(pszDataID, pszValID, strValue))
	{
#ifdef _UNICODE
		dValue = _wtof(strValue);
#else
		dValue = atof(strValue);
#endif
	}

	return dValue;
}

long   GBS_GetItemReportExValue_L(const char* pszDataID, const char* pszValID)
{
	long nValue = 0;
	CString strValue;

	if (GBS_GetItemReportExValue(pszDataID, pszValID, strValue))
	{
#ifdef _UNICODE
		nValue = _wtol(strValue);
#else
		nValue = atol(strValue);
#endif
	}

	return nValue;
}

char*  GBS_GetItemReportExValue_S(const char* pszDataID, const char* pszValID)
{
	CString strValue;
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer[0] = 0;

	if (GBS_GetItemReportExValue(pszDataID, pszValID, strValue))
	{
		CString_to_char(strValue, _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer);
	}

	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
}

char* GBS_GetFileInReportEx(const char *pszFilePostfix, long nFileIndex)
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

long GBS_GetFileNumInReportEx(const char *pszFilePostfix)
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

long GBS_GetItemReportExCount()
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;
	long nCount = 0;

	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	return pItem->GetItemReportExCount();
}


long GBS_GetItemReportExDataCountByID(const char* pszDataAttrID)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CReport *pReport = (CReport*)GBS_GetReport(pItem, -1); //pItem->GetReport(-1);

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

long GBS_GetItemReportDataIndexByIDIndex(const char* pszDataAttrID,long nIndex)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CReport *pReport = (CReport*)GBS_GetReport(pItem, -1); //pItem->GetReport(-1);

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


long GBS_CalTimeGapStr(const char* pszTime1, const char* pszTime2)
{
	CGpsPcTimeSpan ts;
	GBS_CalTimeGapStr_Span(pszTime1, pszTime2, ts);
	long nGap = ts.GetTotalMilliseconds();
	return nGap;
}

long GBS_CalTimeGapStr_us(const char* pszTime1, const char* pszTime2)
{
	CGpsPcTimeSpan ts;
	GBS_CalTimeGapStr_Span(pszTime1, pszTime2, ts);
	long nGap = ts.GetTotalMicroseconds();

	return nGap;
}

long GBS_CalItemReportTimeGap(long nItem1Index, long nItem2Index, const char* pszValID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_CalCall/*L"CalTmGap只能在通讯命令项目中被调用"*/);
		return -1;
	}

	CReport *pReport = pItem->GetCurrReport();

	if (pReport == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	if (pReport->m_pRptDvmDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	CDvmData* oRpt1 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem1Index);
	CDvmData* oRpt2 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem2Index);

	if (oRpt1 == NULL || oRpt2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	CDvmValue* oData1 = (CDvmValue*)oRpt1->FindByID(CString(pszValID));
	CDvmValue* oData2 = (CDvmValue*)oRpt2->FindByID(CString(pszValID));

	if (oData1 == NULL || oData2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
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

long GBS_CalItemReportTimeGapEx(long nItem1Index, long nItem2Index, const char* pszValID1, const char *pszValID2)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_CalCall/*L"CalTmGap只能在通讯命令项目中被调用"*/);
		return -1;
	}

	CReport *pReport = pItem->GetCurrReport();

	if (pReport == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	if (pReport->m_pRptDvmDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	CDvmData* oRpt1 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem1Index);
	CDvmData* oRpt2 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem2Index);

	if (oRpt1 == NULL || oRpt2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
		return -1;
	}

	CDvmValue* oData1 = (CDvmValue*)oRpt1->FindByID(CString(pszValID1));
	CDvmValue* oData2 = (CDvmValue*)oRpt2->FindByID(CString(pszValID2));

	if (oData1 == NULL || oData2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
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

long GBS_CalItemReportTimeGapEx2(long nItem1Index, long nItem2Index, long nValIndex1, long nValIndex2)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_CalCall/*L"CalTmGap只能在通讯命令项目中被调用"*/);
		return 0;
	}

	CReport *pReport = pItem->GetCurrReport();

	if (pReport == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
		return 0;
	}

	if (pReport->m_pRptDvmDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
		return 0;
	}

	CDvmData* oRpt1 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem1Index);
	CDvmData* oRpt2 = (CDvmData*)pReport->m_pRptDvmDataset->GetAtIndex(nItem2Index);

	if (oRpt1 == NULL || oRpt2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
		return 0;
	}

	CDvmValue* oData1 = (CDvmValue*)oRpt1->GetAtIndex(nValIndex1);
	CDvmValue* oData2 = (CDvmValue*)oRpt2->GetAtIndex(nValIndex2);

	if (oData1 == NULL || oData2 == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoDataReport2/*L"CalTmGap:没有报告数据"*/);
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
void GBS_FilterInit()
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CDvmDataset* pReportEx = GBS_GetItemReportDataEx();

	if (pReportEx != NULL)
	{
		pList->RemoveAll();
		pList->Append(pReportEx);
	}
}

long GBS_FilterReportExEqualValueL(const char* pszDataAttrID, long nAttrValue)
{
	char pszAttrValue[20];
	sprintf(pszAttrValue, "%d", nAttrValue);
	return GBS_FilterReportExEqualValueStr(pszDataAttrID, pszAttrValue);
}

long GBS_FilterReportExEqualValueStr(const char* pszDataAttrID, const char* pszValue)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CExBaseList oListDest;
	CDvmData *pData = NULL;
	//CTag *pAttr = NULL;
	CString strTagID(pszDataAttrID);
	CString strValue(pszValue);
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CDvmData*)pList->GetNext(pos);
		//pAttr = pData->FindByTagID(strTagID);

		//if (pAttr != NULL)
		if (pData->HasValueEx(strTagID, strValue))
		{
			oListDest.AddTail(pData);
// 			if (pAttr->m_strValue == strValue)
// 			{
// 				oListDest.AddTail(pData);
// 			}
		}
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CString strMsg;
		strMsg.Format(_T("Filter(%s # %s) %d=>%d"), strTagID, strValue, pList->GetCount(), oListDest.GetCount());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
	}

	pList->RemoveAll();
	pList->Append(oListDest);
	oListDest.RemoveAll();
	return pList->GetCount();
}

long GBS_FilterReportExHasValueStr(const char* pszDataAttrID, const char* pszValue)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CExBaseList oListDest;
	CDvmData *pData = NULL;
	//CTag *pAttr = NULL;
	CString strTagID(pszDataAttrID);
	CString strValue(pszValue);
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CDvmData*)pList->GetNext(pos);
		//pAttr = pData->FindByTagID(strTagID);

		//if (pAttr != NULL)
		if (pData->HasValueHasStr(strTagID, strValue))
		{
			oListDest.AddTail(pData);
// 			if (pAttr->m_strValue.Find(strValue) >= 0)
// 			{
// 				oListDest.AddTail(pData);
// 			}
		}
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CString strMsg;
		strMsg.Format(_T("Filter(%s # %s) %d=>%d"), strTagID, strValue, pList->GetCount(), oListDest.GetCount());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
	}

	pList->RemoveAll();
	pList->Append(oListDest);
	oListDest.RemoveAll();
	return pList->GetCount();
}

long GBS_FilterReportExHasNoValueStr(const char* pszDataAttrID, const char* pszValue)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CExBaseList oListDest;
	CDvmData *pData = NULL;
	//CTag *pAttr = NULL;
	CString strTagID(pszDataAttrID);
	CString strValue(pszValue);
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CDvmData*)pList->GetNext(pos);
		//pAttr = pData->FindByTagID(strTagID);

		//if (pAttr != NULL)
		if (pData->HasValueHasNoStr(strTagID, strValue))
		{
			oListDest.AddTail(pData);
// 			if (pAttr->m_strValue.Find(strValue) < 0)
// 			{
// 				oListDest.AddTail(pData);
// 			}
		}
	}

	if (g_nLog_TestControl_Msg == 1)
	{
		CString strMsg;
		strMsg.Format(_T("Filter(%s # %s) %d=>%d"), strTagID, strValue, pList->GetCount(), oListDest.GetCount());
		CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
	}

	pList->RemoveAll();
	pList->Append(oListDest);
	oListDest.RemoveAll();
	return pList->GetCount();
}

void GBS_FilterCombineReportEx(const char* pszDataAttrID, const char* pszRptDataID, const char* pszSeparator)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	CValues *pValues = GBS_GetItemReportValues();

	if (pValues == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NullDataReport/*_T("FilterCombineReportEx函数：报告数据为空")*/);
		return;
	}

	CDvmData *pData = NULL;
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
		pData = (CDvmData*)pList->GetNext(pos);
		//pAttr = pData->FindByTagID(strTagID);

		//if (pAttr != NULL)
		if (pData->GetValueByID(strTagID, strValue))
		{
			strValues.AppendFormat(_T("%s%s"), strValue, strSeparator);
		}
	}

	CString strDataID(pszRptDataID);
	CValue *pValue = (CValue*)pValues->FindByID(strDataID);

	if (g_nLog_TestControl_Msg == 1)
	{
		CString strMsg;
		strMsg.Format(_T("FilterComb( %d ) (%s)"), pList->GetCount(), strValues);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
	}

	if (pValue != NULL)
	{
		pValue->m_strValue = strValues;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_DataReportID/*_T("不存在ID为\"%s\"的报告数据")*/, strDataID);
	}
}

CEquationBuffer g_oEquationBuffer;

BOOL GBS_FilterRptExQueryData(CDvmData *pData)
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

long GBS_FilterRptExQuery(const char* pszQuery)
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;

	if (strlen(pszQuery) < 3)
	{
		GBS_FilterInit();
		return pList->GetCount();
	}

	g_oEquationBuffer.DeleteAll();
	long nEnd = strlen(pszQuery);
	const char *pEnd = pszQuery + nEnd;
	g_oEquationBuffer.InitBuffer(pszQuery, pEnd);

	CDvmData *pData = NULL;
	POS pos = pList->GetHeadPosition();
	long nIndex = 0, nIndexFind = 0;
	CExBaseList oList;

	while (pos != NULL)
	{
		pData = (CDvmData *)pList->GetNext(pos);

		if (GBS_FilterRptExQueryData(pData))
		{
			oList.AddTail(pData);
		}
	}

	pList->RemoveAll();
	pList->Append(oList);
	oList.RemoveAll();

	return pList->GetCount();
}

long GBS_FilterRptExGetCount()
{
	CExBaseList *pList = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;
	return pList->GetCount();
}

long GBS_FilterRptExGetLong(long nIndex, const char* pszDataAttrID)
{
	char *pValue = GBS_FilterRptExGetString(nIndex, pszDataAttrID);

	return atol(pValue);
}

char* GBS_FilterRptExGetString(long nIndex, const char* pszDataAttrID)
{
	if (g_nLog_TestControl_Msg == 1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("FilterRptExGetString(%d, %s)"), nIndex, (CString(pszDataAttrID)));
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

	if (!bFind)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,CXLanguageResourceAtsBase::g_sLangTxt_DataUnExist/*_T("ReportEx数据(Index=%d  AttrID=%s)不存在")*/, nIndex, CString(pszDataAttrID));
	}

	return g_pLuaReturnString;
}

double GBS_FilterRptExGetDouble(long nIndex, const char* pszDataAttrID)
{
	char *pValue = GBS_FilterRptExGetString(nIndex, pszDataAttrID);

	return atof(pValue);
}

long GBS_FilterRptExGetValCount(long nDataIndex)
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


long GBS_FilterRptExGetValLong(long nDataIndex, const char* pszValIndex)
{
	char *pValue = GBS_FilterRptExGetString(nDataIndex, pszValIndex);

	return atol(pValue);
}

CDvmValue* GBS_FilterRptExGetDvmValue(long nDataIndex, const char* pszValIndex)
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

char* GBS_FilterRptExGetValString(long nDataIndex, const char* pszValIndex)
{
	CDvmValue *pDvmValue = GBS_FilterRptExGetDvmValue(nDataIndex, pszValIndex);
	g_pLuaReturnString[0] = '0';
	g_pLuaReturnString[1] = 0;
	g_pLuaReturnString[2] = 0;
	CString strValue;

	if (!pDvmValue)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,CXLanguageResourceAtsBase::g_sLangTxt_DataUnExist/*_T("ReportEx数据(Index=%d  AttrID=%s)不存在")*/, nDataIndex, CString(pszValIndex));
	}
	else
	{
		CString_to_char(pDvmValue->m_strValue, g_pLuaReturnString);
	}

	return g_pLuaReturnString;
}

double GBS_FilterRptExGetValDouble(long nDataIndex, const char* pszValIndex)
{
	char *pValue = GBS_FilterRptExGetString(nDataIndex, pszValIndex);

	return atof(pValue);
}

long GBS_FilterRptExCalValError(long nDataIndex, const char* pszValIndex, double dRefVal, double dAbsErr, double dRelErr)
{
	CDvmValue *pDvmValue = GBS_FilterRptExGetDvmValue(nDataIndex, pszValIndex);

	if (pDvmValue == NULL)
	{
		return 0;
	}

#ifdef _UNICODE
	double dValue = _wtof(pDvmValue->m_strValue);
#else
	double dValue = atof(pDvmValue->m_strValue);
#endif
	double dValErrAbs = fabs(dValue - dRefVal);
	double dValErrRel = dValErrAbs;

	if (fabs(dRefVal) > 0.0001)
	{
		dValErrRel /= dRefVal;
	}

	return (dValErrAbs < dAbsErr || dValErrRel < dRelErr);
}

long GBS_FilterRptExCalValErrorEx(const char *pszDataID, const char *pszValID, double dRefVal, double dAbsErr, double dRelErr)
{
	CDvmDataset* pReportEx = GBS_GetItemReportDataEx();
	CDvmValue *pValue = NULL;
	CDvmValue *p = NULL;
	CString strDataID, strValueID;
	strDataID = pszDataID;
	strValueID = pszValID;

	CDvmData *pDataFind = (CDvmData*)pReportEx->FindByID(strDataID);

	if (pDataFind == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_DataUnExist2/*_T("数据【%s】不存在")*/, strDataID);
		return 0;
	}

	pValue = (CDvmValue *)pDataFind->FindByID(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_DataUnExist3/*_T("数据值【%s】不存在")*/, strValueID);
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

CDvmData* Gbs_FilterRptExQueryMaxErr(CExBaseList &listDatas, const CString &strAttrID, double dStand, long nWriteDs, double &dValue, CValues *pReportValues)
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

CDvmData* Gbs_FilterRptExQueryMaxErr(CExBaseList &listDatas, const CString &strAttrID1, const CString &strAttrID2, const CString &strOptr, double dStand, long nWriteDs, double &dValue, CValues *pReportValues)
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

CDvmData* Gbs_FilterRptExQueryMaxErr(CExBaseList &listDatas, double dStand, long nWriteDs, double &dValue, CValues *pReportValues)
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


void Gbs_FilterRptExQueryByDataID(const char *pszDataID, long nMaxCount, CExBaseList &listDatas)
{
#ifdef GUIDEBOOK_DEV_MODE
#else
	CReport *pReport = GBS_GetItemReport();
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

double Gbs_FilterRptExQueryUseErr(const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs)
{
	CExBaseList listDatas;
	Gbs_FilterRptExQueryByDataID(pszDataID, nMaxCount, listDatas);

	CReport *pReport = GBS_GetItemReport();
 	CValues *pValues = pReport->m_pValues;
 	CDvmData *pData = NULL;
	CString strAttrID, strDataID;
	strAttrID = pszAttrID;
	strDataID = pszDataID;
	double dDataValue  = -9999999;
	CDvmValue *pValueFind = NULL;

	if (strAttrID.GetLength() > 0)
	{
		pData = Gbs_FilterRptExQueryMaxErr(listDatas, strAttrID, dStand, nWriteDs, dDataValue, pValues);
	}
	else
	{
		pData = Gbs_FilterRptExQueryMaxErr(listDatas, dStand, nWriteDs, dDataValue, pValues);
	}

	if (pData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Report Query(DataID=[%s] AttrID=[%s] error"), strDataID, strAttrID);
	}

	listDatas.RemoveAll();

	return dDataValue;
}

double Gbs_FilterRptExQueryUseErrEx(const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs)
{
	CExBaseList listDatas;
	Gbs_FilterRptExQueryByDataID(pszDataID, nMaxCount, listDatas);

	CReport *pReport = GBS_GetItemReport();
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
		pData = Gbs_FilterRptExQueryMaxErr(listDatas, strAttrID1, strAttrID2, strOptr, dStand, nWriteDs, dDataValue, pValues);
	}
	else
	{
		pData = Gbs_FilterRptExQueryMaxErr(listDatas, dStand, nWriteDs, dDataValue, pValues);
	}

	if (pData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Report Query(DataID=[%s] AttrID1=[%s]  AttrID2=[%s] error"), strDataID, strAttrID1, strAttrID2);
	}

	listDatas.RemoveAll();

	return dDataValue;
}

//////////////////////////////////////////////////////////////////////////
//Avg
CDvmData* Gbs_FilterRptExQueryAvg(CExBaseList &listDatas, const CString &strAttrID, CDvmData &oDestData, double &dValue, CValues *pReportValues)
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

CDvmData* Gbs_FilterRptExQueryAvg(CExBaseList &listDatas, const CString &strAttrID1, const CString &strAttrID2, const CString &strOptr, CDvmData &oDestData, double &dValue, CValues *pReportValues)
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

CDvmData* Gbs_FilterRptExQueryAvg(CExBaseList &listDatas, CDvmData &oDestData, double &dValue, CValues *pReportValues)
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

double Gbs_FilterRptExQueryUseAvg(const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs)
{
	CExBaseList listDatas;
	Gbs_FilterRptExQueryByDataID(pszDataID, nMaxCount, listDatas);

	CReport *pReport = GBS_GetItemReport();
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
		pData = Gbs_FilterRptExQueryAvg(listDatas, strAttrID, oDestData, dDataValue, pValues);
	}
	else
	{
		pData = Gbs_FilterRptExQueryAvg(listDatas, oDestData, dDataValue, pValues);
	}

	if (pData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Report Query(DataID=[%s] AttrID=[%s] error"), strDataID, strAttrID);
	}

	listDatas.RemoveAll();

	return dDataValue;
}

double Gbs_FilterRptExQueryUseAvgEx(const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs)
{
	CExBaseList listDatas;
	Gbs_FilterRptExQueryByDataID(pszDataID, nMaxCount, listDatas);

	CReport *pReport = GBS_GetItemReport();
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
		pData = Gbs_FilterRptExQueryAvg(listDatas, strAttrID1, strAttrID2, strOptr, oDestData, dDataValue, pValues);
	}
	else
	{
		pData = Gbs_FilterRptExQueryAvg(listDatas, oDestData, dDataValue, pValues);
	}

	if (pData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Report Query(DataID=[%s] AttrID1=[%s]  AttrID2=[%s] error"), strDataID, strAttrID1, strAttrID2);
	}

	listDatas.RemoveAll();

	return dDataValue;
}

long Gbs_FilterRptExQueryClearNotUse()
{
	CDvmDataset* pReportEx = GBS_GetItemReportDataEx();
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
long GBS_SSelectItem(const char *pszItemPath)
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
long GBS_SGetItemReportCount()
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
long GBS_SSelectItemReport(long nReportIndex)
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
double GBS_SGetItemReportValue(const char* pszValID)
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
long GBS_SGetItemReportValueLong(const char* pszValID)
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
const char* GBS_SGetItemReportValueString(const char* pszValID)
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
long GBS_SGetItemReportValueCount()
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

void GBS_SGetItemReportValue(CValue* &pValue, long nDataIndex)
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

double GBS_SGetItemReportValue2(long nDataIndex)
{
	CValue *pValue = NULL;

	GBS_SGetItemReportValue(pValue, nDataIndex);

	if (pValue == NULL)
	{
		return 0;
	}

	_bstr_t bstrValue = pValue->m_strValue;
	double dValue = _wtof(bstrValue);

	return dValue;
}

long GBS_SGetItemReportValueLong2(long nDataIndex)
{
	CValue *pValue = NULL;

	GBS_SGetItemReportValue(pValue, nDataIndex);

	if (pValue == NULL)
	{
		return 0;
	}

	_bstr_t bstrValue = pValue->m_strValue;
	long nValue = _wtol(bstrValue);

	return nValue;
}

const char* GBS_SGetItemReportValueString2(long nDataIndex)
{
	CValue *pValue = NULL;

	GBS_SGetItemReportValue(pValue, nDataIndex);

	if (pValue == NULL)
	{
		return 0;
	}

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer[0] = 0;
	_bstr_t bstrValue = pValue->m_strValue;
	BSTR_to_char(bstrValue, _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer);

	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_pszSysToLuaBuffer;
}

//扩展报告处理函数******************************************************

//获得项目的指定的报告的数据个数
long GBS_SGetItemReportExDataCount()
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


void GBS_SGetItemReportExValue(CDvmValue* &oTag, long nDataIndex, const char* pszValID)
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
double GBS_SGetItemReportExDataValue(long nDataIndex, const char* pszValID)
{
	CDvmValue* oTag = NULL;
	GBS_SGetItemReportExValue(oTag, nDataIndex, pszValID);

	if (oTag == NULL)
	{
		return 0;
	}

#ifdef _UNICODE
	return _wtof(oTag->m_strValue);
#else
	return atof(oTag->m_strValue);
#endif
}

//获得项目的指定的报告的数据：整数
long GBS_SGetItemReportExDataValueLong(long nDataIndex, const char* pszValID)
{
	CDvmValue* oTag = NULL;
	GBS_SGetItemReportExValue(oTag, nDataIndex, pszValID);

	if (oTag == NULL)
	{
		return 0;
	}

#ifdef _UNICODE
	return _wtol(oTag->m_strValue);
#else
	return atol(oTag->m_strValue);
#endif
}

//获得项目的指定的报告的数据：整数
const char* GBS_SGetItemReportExDataValueString(long nDataIndex, const char* pszValID)
{
	CDvmValue* oTag = NULL;
	GBS_SGetItemReportExValue(oTag, nDataIndex, pszValID);

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
void GBS_RptExDsSelect(const char *pszPath, CExBaseList &oList)
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

long GBS_RptExDsGetCount(const char* pszPath)
{
	CExBaseList oList;
	GBS_RptExDsSelect(pszPath, oList);

	long nCount = oList.GetCount();
	oList.RemoveAll();

	return nCount;
}

//获得项目的指定的报告的数据：浮点数
double GBS_RptExDsGetValueD(const char* pszPath, long nIndex)
{
	const char *pszValue = GBS_RptExDsGetValueStr(pszPath, nIndex);
	return atof(pszValue);
}

//获得项目的指定的报告的数据：整数
long GBS_RptExDsGetValueL(const char* pszPath, long nIndex)
{
	const char *pszValue = GBS_RptExDsGetValueStr(pszPath, nIndex);
	return atol(pszValue);
}

//获得项目的指定的报告的数据：整数
const char* GBS_RptExDsGetValueStr(const char* pszPath, long nIndex)
{
	CExBaseList oList;
	GBS_RptExDsSelect(pszPath, oList);

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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,CXLanguageResourceAtsBase::g_sLangTxt_DataPathUn /*_T("数据路径【%s】检索出的数据【%d】不存在")*/,CString(pszPath), nIndex );
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
void GBS_RptExDsValidClear()
{
	CDsvSequence *pDvmSequence = _CGbScriptGlobalDefine::GetDsvSequence();
	pDvmSequence->DeleteAll();
}

void GBS_RptExDsValidAddElement(const char* pszText, long nOption, long nUnbound)
{
	CDsvSequence *pDvmSequence = _CGbScriptGlobalDefine::GetDsvSequence();
	pDvmSequence->AddElement(CString(pszText), nOption, nUnbound);
}

void GBS_RptExDsValidAddElementChoice(const char* pszText, long nOption, long nUnbound)
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

long GBS_RptExDsValid(long nValidateHead)
{
	CDvmDataset *pDataset = &_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListRptExFilter;//GBS_GetItemReportDataEx();

	if (pDataset == NULL)
	{
		return 0;
	}

	CDsvSequence *pDsvSequence = _CGbScriptGlobalDefine::GetDsvSequence();

	return pDsvSequence->DsValidate(pDataset, NULL, nValidateHead);
}

long GBS_RecordCmd(const char *pszCmdID, const char *pszCmdPara)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	pTestControl->GBS_RecordCmd(pszCmdID, pszCmdPara);
#endif

	return 0;
}

long GBS_AdjustWord(long nPopDlg)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	pTestControl->AdjustReport(NULL);
#endif
	
	return 0;
}


void GBS_CalSoeTime(const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FtcnCmdUse/*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return;
	}

	((CCommCmd*)pItem)->CalSoeTime(pszRptID, pszSoeID1, pszSoeID2);
}

void GBS_CalSoeTimeEx(const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FtcnCmdUse/*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return;
	}

	((CCommCmd*)pItem)->CalSoeTime(pszRptID, pszSoeID1, pszVal1, pszSoeID2, pszVal2);
}

void GBS_SetSoeTripDesc(const char *pszRptID, const char *pszSoeID)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FtcnCmdUse/*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return;
	}

	((CCommCmd*)pItem)->SetSoeTripDesc(pszRptID, pszSoeID);
}

long  GBS_CalSoeError(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return 0;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FtcnCmdUse/*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return 0;
	}

	return ((CCommCmd*)pItem)->CalSoeError(dRate, pszDsPathID, pszRptID, pszAbsErrID, pszRelErrID, dStandVal, dAbsErr, dRelErr);
}

long GBS_CalSoeError2(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID
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
		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FtcnCmdUse/*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return 0;
	}

	return ((CCommCmd*)pItem)->CalSoeError2(dRate, pszDsPathID, pszRptID, pszAbsErrID, pszRelErrID, dStandVal, dErrRefStandVal, dAbsErr, dRelErr);
}


//Record
long GBS_RcdSetProgID(const char* pszRcdProgID)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = GBS_GetTestControl2();

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdSetProgID(pszRcdProgID);
#else
	return 0;
#endif
}

long GBS_RcdExit()
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = GBS_GetTestControl2();

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdExit();
#else
	return 0;
#endif
}

long GBS_RcdConfig(const char* pszPara)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = GBS_GetTestControl2();

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdConfig(pszPara);
#else
	return 0;
#endif
}

long GBS_RcdSelect(const char* pszPara)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = GBS_GetTestControl2();

	return pTestControl->GBS_RcdSelect(pszPara);
#else
	return 0;
#endif
}

long GBS_RcdValidate(const char* pszRsltID)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = GBS_GetTestControl2();

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdValidate(pszRsltID);
#else
	return 0;
#endif
}

long GBS_RcdCmpClear()
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = GBS_GetTestControl2();

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdCmpClear();
#else
	return 0;
#endif
}

long GBS_RcdCmpInit(const char* pszRcdFilePathRoot, long nCreateTestTimesDir)
{
#ifndef GUIDEBOOK_DEV_MODE
	g_strRcdFilePathRoot = pszRcdFilePathRoot;
	g_bCreateTestTimesDir = nCreateTestTimesDir;
	return 0;
#else
	return 0;
#endif
}

long GBS_RcdCmp(const char* pszStdFile, const char* pszTestFile)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = GBS_GetTestControl2();

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdCmp(pszStdFile, pszTestFile);
#else
	return 0;
#endif
}

long GBS_RcdCopyFile(const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = GBS_GetTestControl2();

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdCopyFile(pszSrcFile, pszDestFile, nCreateTestTimesDir);
#else
	return 0;
#endif
}

long GBS_RcdAnalyse(const char* pszRcdFile)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = GBS_GetTestControl2();

	if (pTestControl == NULL)
	{
		return 0;
	}

	return pTestControl->GBS_RcdAnalyse(pszRcdFile);
#else
	return 0;
#endif
}

long GBS_RcdSetPath(long nAppendItemPath, const char* pszRcdFilePathRoot, long nAppendTestTimeDir)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestControl = GBS_GetTestControl2();
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
long GBS_GetRepeatTimes(const char* pszItemPath)
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

long GBS_GetRepeatSuccTimes(const char* pszItemPath)
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

void GBS_SetCmdZoneIndex(long nZoneIndex)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	if (pItem == NULL)
	{
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FtcnCmdUse2/*_T("SetCmdZoneIndex函数只能用于通讯命令")*/);
		return;
	}

	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd *pCmd = pCommCmd->GetCmd();

	pCmd->m_nZoneIndex = nZoneIndex;
}

//修正动作值的起始值和终止值
void Gbs_ValidBeginEndValRange(const char *pBeginValID, const char *pEndValID, const char *pStepID
							   , double dMinRange, double dMinStep
							   , long nMinSteps, long nMaxSteps, long nUseNeg)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);

	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem(NULL);

	if (pItem == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FtcnScriptCall/*_T("函数ValidBeginEndValRange只能作为电气量项目的脚本调用")*/);
		return;
	}

	if (pItem->GetClassID() != GBCLASSID_MACROTEST)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FtcnScriptCall/*_T("函数ValidBeginEndValRange只能作为电气量项目的脚本调用")*/);
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FctnUnExist/*_T("函数ValidBeginEndValRange:[%s]不存在")*/, strBeginValID);
		return;
	}

	if (!pMacroTest->GetItemParaValue(strEndValID, dEndVal))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FctnUnExist/*_T("函数ValidBeginEndValRange:[%s]不存在")*/, strEndValID);
		return;
	}

	if (!pMacroTest->GetItemParaValue(strStepID, dStepVal))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_FctnUnExist/*_T("函数ValidBeginEndValRange:[%s]不存在")*/, strStepID);
		return;
	}

	double dRange = abs(dBeginVal-dEndVal);
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
		double dGap = dMinRange - abs(dEndVal - dBeginVal);
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


	dRange = abs(dBeginVal-dEndVal);
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
			,strBeginValID, dBeginVal, strEndValID, dEndVal, strStepID, dStepVal);
	}
#endif
}



//时间出发函数
void Gbs_SetTmTriggerSecond(long nSecond, long nOptr)
{
#ifdef GUIDEBOOK_DEV_MODE
#else
	CTestControl* pTestControl = GBS_GetTestControl2();
	pTestControl->Gbs_SetTmTriggerSecond(nSecond, nOptr);
#endif
}

void Gbs_SetTmTriggerCountMinute(long nMinute)
{
#ifdef GUIDEBOOK_DEV_MODE
#else
	CTestControl* pTestControl = GBS_GetTestControl2();
	pTestControl->Gbs_SetTmTriggerCountMinute(nMinute);
#endif
}

void Gbs_EnterTmTrigger()
{
#ifdef GUIDEBOOK_DEV_MODE
#else
	CTestControl* pTestControl = GBS_GetTestControl2();
	pTestControl->Gbs_EnterTmTrigger();
#endif
}

void Gbs_StartTimerTigger()
{
#ifdef GUIDEBOOK_DEV_MODE
#else
	CTestControl* pTestControl = GBS_GetTestControl2();
	pTestControl->Gbs_StartTimerTigger();
#endif
}

void Gbs_StopTimerTrigger()
{
#ifdef GUIDEBOOK_DEV_MODE
#else
	CTestControl* pTestControl = GBS_GetTestControl2();
	pTestControl->Gbs_StopTimerTrigger();
#endif
}

double Gbs_ValueRevised(double dValue, long nDots)
{
	return math_ValueRevised(dValue, nDots);
}


//////////////////////////////////////////////////////////////////////////
//日志部分
CDvmLogs* Gbs_log_query_get_logs()
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

CDvmLog* Gbs_log_query_get_log(long nLogIndex)
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

long Gbs_log_query_clear()
{
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogs.RemoveAll();
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas.RemoveAll();

	return 0;
}

long Gbs_log_query_time(const char *pszBeginTine, const char *pszEndTime)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs();
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

	return 0;
}

long Gbs_log_query_entryid(const char *pszEntryID)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs();
	return 0;
}

long Gbs_log_query_logctrl(const char *pszLogCtrl)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs();
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

long Gbs_log_query_dataset(const char *pszDataset)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs();
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

long Gbs_log_query_data_clear()
{
	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas.RemoveAll();
	return 0;
}

long Gbs_log_query_data(CDvmLog *pLog, const CString &strDataID)
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

long Gbs_log_query_data(const char *pszDataID)
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
		nCount += Gbs_log_query_data(pLog, strDataID);
	}

	return nCount;
}

long Gbs_log_query_data_get_count()
{
	return _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas.GetCount();;
}

long Gbs_log_query_data_add_to_rpt()
{
	CReport* pReport = GBS_GetItemReport();
	
	pReport->m_pRptDvmDataset->AppendCloneEx(_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oListLogDatas);

	return pReport->m_pRptDvmDataset->GetCount();
}

long Gbs_log_query(const char *pszScript)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs();
	return 0;
}

long Gbs_log_get_count()
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs();

	if (pLogs == NULL)
	{
		return 0;
	}
	else
	{
		return pLogs->GetCount();
	}
}

const char* Gbs_log_get_attr(long nLogIndex, const char *pszAttr)
{
	CDvmLogs *pLogs = Gbs_log_query_get_logs();
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

long Gbs_log_get_data_count(long nLogIndex)
{
	CDvmLog *pLog = Gbs_log_query_get_log(nLogIndex);

	if (pLog == NULL)
	{
		return 0;
	}

	return pLog->GetCount();
}

const char* Gbs_log_get_data_attr(long nLogIndex, long nDataIndex, const char *pszAttr)
{
	CDvmLog *pLog = Gbs_log_query_get_log(nLogIndex);
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

const char* Gbs_log_get_data_attr2(long nLogIndex, const char *pszDataID, const char *pszAttr)
{
	CDvmLog *pLog = Gbs_log_query_get_log(nLogIndex);
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
long GBS_InitStrTok(const char *pszString, const char *pControl)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	return pGuideBook->GBS_InitStrTok((char*)pszString, (char*)pControl);

// #ifdef GUIDEBOOK_DEV_MODE
// 	return pGuideBook->GBS_InitStrTok((char*)pszString, (char*)pControl);
// #else
// 	CTestControl* pTestControl = GBS_GetTestControl2();
// 	return pTestControl->GBS_InitStrTok((char*)pszString, (char*)pControl);
// #endif
}

long GBS_StrTokCount()
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	return pGuideBook->GBS_StrTokCount();

// #ifdef GUIDEBOOK_DEV_MODE
// 	return CTestControl::GBS_StrTokCount();
// #else
// 	CTestControl* pTestControl = GBS_GetTestControl2();
// 	return pTestControl->GBS_StrTokCount();
// #endif
}

const char* GBS_StrTokIndex(long nIndex)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	return pGuideBook->GBS_StrTokIndex(nIndex);
// 
// #ifdef GUIDEBOOK_DEV_MODE
// 	return CTestControl::GBS_StrTokIndex(nIndex);
// #else
// 	CTestControl* pTestControl = GBS_GetTestControl2();
// 	return pTestControl->GBS_StrTokIndex(nIndex);
// #endif
}

const char* GBS_StrTokNext()
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	return pGuideBook->GBS_StrTokNext();
// 
// #ifdef GUIDEBOOK_DEV_MODE
// 	return CTestControl::GBS_StrTokNext();
// #else
// 	CTestControl* pTestControl = GBS_GetTestControl2();
// 	return pTestControl->GBS_StrTokNext();
// #endif
}

//装置的全局参数
void GBS_SetGlobal_Str(const char *pszID, const char *pszValue)
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

#ifndef GUIDEBOOK_DEV_MODE
		if (g_strGbGlobalData_DeviceIndex == strID)
		{
			CFactoryBatchTestMngr::PostFacBatchTestMsg(FacBatchTestMsg_Attr_IdxDv, (LPARAM)pGuideBook);
		}
#endif
	}
}

void GBS_SetGlobal_Long(const char *pszID, long nValue)
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

void GBS_SetGlobal_Float(const char *pszID, float fValue)
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


const char* GBS_GetGlobal_Str(const char *pszID)
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

long GBS_GetGlobal_Long2(const CString &strID)
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

long GBS_GetGlobal_Long(const char *pszID)
{
	CString strID;
	strID = pszID;
	return GBS_GetGlobal_Long2(strID);
}

float GBS_GetGlobal_Float(const char *pszID)
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

void GBS_Set_TestError(const char *pszTestError)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);

	CString strTestError;
	strTestError = pszTestError;
	pGuideBook->SetTestError(strTestError);
	pItem->SetRsltJdg(0);
}

long GBS_BinRslt(const char *pszParaID, const char *pszRsltID)
{

#ifdef GUIDEBOOK_DEV_MODE
	return 1;
#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CTestControl *pTestControl = GBS_GetTestControl2();
	return pTestControl->GBS_BinRslt(pItem, pszParaID, pszRsltID);
#endif
}

long GBS_BinStateRslt(const char *pszParaID, const char *pszRsltID)
{

#ifdef GUIDEBOOK_DEV_MODE
	return 1;
#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CTestControl *pTestControl = GBS_GetTestControl2();
	return pTestControl->GBS_BinStateRslt(pItem, pszParaID, pszRsltID);
#endif
}

long GBS_BinChngCntRslt(const char *pszBinChngData, const char *pszRsltID)
{

#ifdef GUIDEBOOK_DEV_MODE
	return 1;
#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CTestControl *pTestControl = GBS_GetTestControl2();
	return pTestControl->GBS_BinChngCntRslt(pItem, pszBinChngData, pszRsltID);
#endif
}

// 
// long GBS_BinRsltEx(const char *pszParaDatas, const char *pszRsltDatas)
// {
// #ifdef GUIDEBOOK_DEV_MODE
// 	return 1;
// #else
// 	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
// 	CTestControl *pTestControl = GBS_GetTestControl2();
// 	return pTestControl->GBS_BinRsltEx(pItem, pszParaDatas, pszRsltDatas);
// #endif
// }


//2019-1-6:增加数据对象是否合格的功能   lijq
// BOOL g_bAddDataErrorValueToRpt = FALSE;
void GBS_Set_AddDataErrorValueToRpt(long nValue)
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

void GBS_AddDataErrorToRpt(const char* pszDataID, long nValue)
{
#ifdef GUIDEBOOK_DEV_MODE
	
#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CTestControl *pTestControl = GBS_GetTestControl2();
	pTestControl->GBS_AddDataErrorToRpt(pItem, pszDataID, nValue);
#endif
}

//2019-6-5  测试记录文件相关
const char* GBS_GetTemplateFile(long nWithPath)
{
	g_pLuaReturnString[0] = 0;

#ifdef GUIDEBOOK_DEV_MODE

#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
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

const char* GBS_GetGbrptFile(long nWithPath)
{
	g_pLuaReturnString[0] = 0;

#ifdef GUIDEBOOK_DEV_MODE

#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
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

void GBS_SetGbrptFileName(const char *pszFileName)
{
#ifdef GUIDEBOOK_DEV_MODE

#else
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
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
void GBS_OffsetTestDataByGbrptIndex(const char *pszDestDataID)
{
#ifdef GUIDEBOOK_DEV_MODE

#else
	CString strID;
	strID = pszDestDataID;
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	pTestControl->GBS_OffsetTestDataByGbrptIndex(pItem, pszDestDataID);
#endif

}

//2020-05-22   磐能版本比对功能  shaolei；
long GBS_VersionInfoCompare (const char* pszPath, const char* pszFilePath)
{
// 	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
// 	ASSERT (pItem != NULL);
// 
// 	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
// 	ASSERT (pGuideBook != NULL);
// 	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
// 
// 	return pTestControl->GBS_VersionInfoCompare(pszPath, pszFilePath);
	return 0;
}

void GBS_SetComtradeDrawLineMode(const char *pszMode)
{
#ifdef GUIDEBOOK_DEV_MODE

#else
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
}

