#include "StdAfx.h"
#include "GuideBook\GbScript_Engine.h"

#ifndef GUIDEBOOK_DEV_MODE
#include "TestControl.h"
#endif

//Lua
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luabind.hpp"
#include "XLanguageResourceAts.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern lua_State* g_pGuideBookLua;
extern char g_pLuaReturnString[MAX_PATH];

#ifndef GUIDEBOOK_DEV_MODE
CTestControl* GBS_GetTestControl()
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();

	return pTestControl;
}
#endif


// 规约帧录波设置
void GBS_RecordPackage(const  char* pszPkgID)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl* pTestControl = GBS_GetTestControl();
	pTestControl->GBS_RecordPackage(pszPkgID);
#endif
}

void GBS_UnRecordPackage(const  char* pszPkgID)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl* pTestControl = GBS_GetTestControl();
	pTestControl->GBS_UnRecordPackage(pszPkgID);
#endif
}

void GBS_GetPackagePcTime(const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail)
{
// 	CTestControl* pTestControl = GBS_GetTestControl();
// 	pTestControl->GBS_GetPackagePcTime(pszPkgID, pszPcTimeID, nUseHeadOrTail);
}

// 读取标准源装置GPS时间与PC时间的之间对应关系
void GBS_GetGpsPcTimeMap(const char *pszGpsTime, const char *pszPcTime)
{
// 	CTestControl* pTestControl = GBS_GetTestControl();
// 	pTestControl->GBS_GetGpsPcTimeMap(pszGpsTime, pszPcTime);
}

//读取输出开始时刻的标准源装置GPS时间
void GBS_GetOutGpsTime(const char *pszGpsTimeID)
{
// 	CTestControl* pTestControl = GBS_GetTestControl();
// 	pTestControl->GBS_GetOutGpsTime(pszGpsTimeID);
}

long GBS_ReadMacroTestResult()
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl* pTestControl = GBS_GetTestControl();
	pTestControl->GBS_ReadMacroTestResult();
#endif

	return 0;
}


//重新下载电气量测试项目的参数
void GBS_DownloadMacroTestPara()
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
	CGbItemBaseList oListDest;
	long nCount = 0;

	POS pos = oListDest.GetHeadPosition();
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	UINT nClassID = pItem->GetClassID();

	if (nClassID != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_CannotUse/*L"DownMacroPara不能在项目\"%s\"中使用"*/, pItem->m_strName);
		return;
	}

	CGbItemBase *pMacroTest = (CGbItemBase*)pItem->GetParent();

	if (pMacroTest == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_CannotUse2/*L"DownMacroPara不能在项目\"%s\"中使用(项目的父对象错误)"*/, pItem->m_strName);
		return;
	}

	nClassID = pMacroTest->GetClassID();

	if (nClassID != GBCLASSID_MACROTEST)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_CannotUse3/*L"DownMacroPara不能在项目\"%s\"中使用(项目的父对象非电气量项目)"*/, pItem->m_strName);
		return;
	}

#ifndef GUIDEBOOK_DEV_MODE
	CTestControl* pTestControl = GBS_GetTestControl();
	pTestControl->GBS_DownloadMacroTestPara();
#endif

}

double GBS_PpGetDeviceAttr(const char *pszAttrID)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();


	if (pTestCtrl == NULL)
	{
		return 0;
	}


	CString strAttr;
	pTestCtrl->GBS_PpGetDeviceAttr(pszAttrID, strAttr);

	return CString_To_double(strAttr);
#else
	return 0;
#endif
}

long GBS_PpGetDeviceAttrL(const char *pszAttrID)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();

	if (pTestCtrl == NULL)
	{
		return 0;
	}

	CString strAttr;
	pTestCtrl->GBS_PpGetDeviceAttr(pszAttrID, strAttr);

	return CString_To_long(strAttr);
#else
	return 0;
#endif
}

const char* GBS_PpGetDeviceAttrStr(const char *pszAttrID)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();

	if (pTestCtrl == NULL)
	{
		return 0;
	}


	CString strAttr;
	pTestCtrl->GBS_PpGetDeviceAttr(pszAttrID, strAttr);

	CString_to_char(strAttr, g_pLuaReturnString);
	return g_pLuaReturnString;
	//CString_to_char(strAttr, g_pLuaReturnString);
	//return g_pLuaReturnString;
#else
	return 0;
#endif
}

void GBS_PpSetDeviceAttrL(const char *pszAttrID, long nValue)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();


	if (pTestCtrl == NULL)
	{
		return;
	}

	CString strAttr;
	strAttr.Format(_T("%d"), nValue);
	pTestCtrl->GBS_PpSetDeviceAttr(pszAttrID, strAttr);
#else
	return;
#endif
}

void GBS_PpSetDeviceAttrStr(const char *pszAttrID, const char *pszValue)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();

	if (pTestCtrl == NULL)
	{
		return;
	}

	CString strAttr;
	strAttr = pszValue;
	pTestCtrl->GBS_PpSetDeviceAttr(pszAttrID, strAttr);
#else
	return;
#endif
}


long GBS_PpRptGetDevieNodeDatas(const char *pszNodePath)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();
	return pTestCtrl->GBS_PpRptGetDevieNodeDatas(pszNodePath);
#else
	return 0;
#endif
}

long GBS_PpDeleteAllNodeData(const char *pszNodePath)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();
	return pTestCtrl->GBS_PpDeleteAllNodeData(pszNodePath);
#else
	return 0;
#endif
}

long GBS_PpRptGetDeviceAttrs(void)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();
	return pTestCtrl->GBS_PpRptGetDeviceAttrs();
#else
	return 0;
#endif
}

double GBS_PpGetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();
	CString strAttr;
	pTestCtrl->GBS_PpGetDevieNodeDataAttr(strDataPath, strAttrID, strAttr);

	return CString_To_double(strAttr);
	//CString_to_char(strAttr, g_pLuaReturnString);
	//return g_pLuaReturnString;
#else
	return 0;
#endif
}

long GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, double dValue)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();
	char strValue[MAX_PATH];
	sprintf(strValue, "%f", dValue);
	return pTestCtrl->GBS_PpSetDevieNodeDataAttr(strDataPath, strAttrID, strValue);
#else
	return 0;
#endif
}

// 
// long GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, const char *strValue)
// {
// 	CTestControl *pTestCtrl = GBS_GetTestControl();
// 	return pTestCtrl->GBS_PpSetDevieNodeDataAttr(strDataPath, strAttrID, strValue);
// }
// 

long GBS_PpCreateDevice(const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();
	return pTestCtrl->GBS_PpCreateDevice(pszPpFile, pszDeviceFile, pszDeviceID);
#else
	return 0;
#endif
}

long GBS_PpReleaseDevice(const char *pszDeviceID)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();
	return pTestCtrl->GBS_PpReleaseDevice(pszDeviceID);
#else
	return 0;
#endif
}


long GBS_PpReleaseAllDevice()
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl *pTestCtrl = GBS_GetTestControl();
	return pTestCtrl->GBS_PpReleaseAllDevice();
#else
	return 0;
#endif
}


long GBS_GetTestIndex()
{

#ifndef GUIDEBOOK_DEV_MODE
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();

	CTestControl *pTestCtrl = GBS_GetTestControl();
	return pTestCtrl->GBS_GetTestIndex(pItem);
#else
	return 0;
#endif
}



long GBS_IsProtocol(const char *pszProtocol)
{
#ifndef GUIDEBOOK_DEV_MODE
	CTestControl* pTestControl = GBS_GetTestControl();
	CString strProtocol;
	CString strMmsEngine = g_strPpEngineProgIDMms;
	CString strEngineProgID = pTestControl->m_pGuideBook->m_strPpEngineProgID;

	strProtocol = pszProtocol;
	strProtocol.MakeLower();
	strEngineProgID.MakeLower();
	strMmsEngine.MakeLower();

	if (strEngineProgID == strMmsEngine)
	{
		return (strEngineProgID.Find(strProtocol) >= 0);
	}

	CString strPpFile = pTestControl->m_pGuideBook->m_strPpTemplateFile;
	strPpFile.MakeLower();
	strPpFile = ParseFileName(strPpFile);

	long nRet = (strPpFile == strProtocol);
	return nRet;

#else
	return 1;
#endif
}
