//ExternInstruct.cpp
#include "stdafx.h"
#include "UIScript_Functions.h"
#include "UIWndThread.h"
#include "UILuaScript_GlobalDefine.h"
#include "UILuaScript.h"
#include "..\Language\LanguageMngr.h"

extern char g_pLuaReturnString[MAX_PATH];


inline CUIWindowBase* UIS_GetUIWindow(const char *pszWindowID)
{
	return _CUILuaScriptGlobalDefine::UIS_GetUIWindow(pszWindowID);
}

inline CUIWndLayer* UIS_GetUILayer(const char *pszLayerID)
{
	return _CUILuaScriptGlobalDefine::UIS_GetUILayer(pszLayerID);
}

long UIS_ShowMessageBox(const char *pszModal, const char *pszFormat, const char *pszMsg)
{
	
	return 0;
}

void UIS_LogLayerNotExist(const char *pszLayerName)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Layer [%s] 不存在"), pszLayerName);
}

void UIS_SetLayerHeight(const char *pszLayerName, long nHeight)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL)
	{
		pLayer->SetWndHeight(nHeight);
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}
}

long UIS_GetLayerHeight(const char *pszLayerName, long &nHeight)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL) 
	{
		nHeight = pLayer->GetWndHeight();
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}

	return 0;
}

void UIS_SetLayerWidth(const char *pszLayerName, long nWidth)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);
	
	if (pLayer != NULL)
	{
		pLayer->SetWndWidth(nWidth);
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}
}

long UIS_GetLayerWidth(const char *pszLayerName)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);
	
	if (pLayer != NULL)
	{
		return pLayer->GetWndWidth();
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}

	return 0;
}

void UIS_SetLayerLeft(const char *pszLayerName, long nLeft)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL) 
	{
		pLayer->SetWndLeft(nLeft);
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}
}

long UIS_GetLayerLeft(const char *pszLayerName)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL)
	{
		return pLayer->GetWndLeft();
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}

	return 0;
}


void UIS_SetLayerTop(const char *pszLayerName, long nTop)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL) 
	{
		pLayer->SetWndTop(nTop);
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}
}

long UIS_GetLayerTop(const char *pszLayerName)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL)
	{
		return pLayer->GetWndTop();
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}

	return 0;
}

void UIS_SetLayerRight(const char *pszLayerName, long nRight)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL) 
	{
		pLayer->SetWndRight(nRight);
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}
}

long UIS_GetLayerRight(const char *pszLayerName)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL) 
	{
		return pLayer->GetWndRight();
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}

	return 0;
}

void UIS_SetLayerBottom(const char *pszLayerName, long nBottom)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL) 
	{
		pLayer->SetWndBottom(nBottom);
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}
}

long UIS_GetLayerBottom(const char *pszLayerName)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL) 
	{
		return pLayer->GetWndBottom();
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}

	return 0;
}

void UIS_SetLayerSize(const char *pszLayerName, long nWidth, long nHeight)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL) 
	{
		pLayer->SetWndSize(nWidth, nHeight);
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}
}

void UIS_SetLayerPosition(const char *pszLayerName, long nLeft, long nTop, long nRight, long nBottom)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL)
	{
		pLayer->SetWndPosition(nLeft, nTop, nRight, nBottom);
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}
}


void UIS_ShowLayer(const char *pszLayerName, long nShow)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);

	if (pLayer != NULL)
	{
		pLayer->Show(nShow);
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}
}

long UIS_IsLayerShow(const char *pszLayerName)
{
	CUIWndLayer *pLayer = UIS_GetUILayer(pszLayerName);
	
	if (pLayer != NULL)
	{
		return pLayer->IsShow();
	}
	else
	{
		UIS_LogLayerNotExist(pszLayerName);
	}
	
	return -1;
}

//////////////////////////////////////////////////////////////////////////
//page
void UIS_LogPageNotExist(const char *pszPageName)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Page [%s] 不存在"), pszPageName);
}

long UIS_GetPageWidth(const char *pszPageName)
{
	CUIWndPage *pPage = UIS_GetUIPage(pszPageName);

	if (pPage != NULL)
	{
		return pPage->GetPageWidth();
	}
	else
	{
		UIS_LogPageNotExist(pszPageName);
	}

	return 0;
}

void UIS_SetPageWidth(const char *pszPageName, long nWidth)
{
	CUIWndPage *pPage = UIS_GetUIPage(pszPageName);

	if (pPage != NULL)
	{
		pPage->SetPageWidth(nWidth);
	}
	else
	{
		UIS_LogPageNotExist(pszPageName);
	}
}

long UIS_GetPageHeight(const char *pszPageName)
{
	CUIWndPage *pPage = UIS_GetUIPage(pszPageName);

	if (pPage != NULL)
	{
		return pPage->GetPageHeight();
	}
	else
	{
		UIS_LogPageNotExist(pszPageName);
	}

	return 0;
}

void UIS_SetPageHeight(const char *pszPageName, long nHeight)
{
	CUIWndPage *pPage = UIS_GetUIPage(pszPageName);

	if (pPage != NULL)
	{
		pPage->SetPageHeight(nHeight);
	}
	else
	{
		UIS_LogPageNotExist(pszPageName);
	}
}

void UIS_SetPageSize(const char *pszPageName, long nWidth, long nHeight)
{
	CUIWndPage *pPage = UIS_GetUIPage(pszPageName);

	if (pPage != NULL)
	{
		pPage->SetPageSize(nWidth, nHeight);
	}
	else
	{
		UIS_LogPageNotExist(pszPageName);
	}
}

void UIS_SetPagePosition(const char *pszPageName, long nLeft, long nTop, long nRight, long nBottom)
{
	CUIWndPage *pPage = UIS_GetUIPage(pszPageName);

	if (pPage != NULL)
	{
		pPage->SetPagePosition(nLeft, nTop, nRight, nBottom);
	}
	else
	{
		UIS_LogPageNotExist(pszPageName);
	}
}

long UIS_ShowPage(const char *pszPageID, long nShow)
{
	CString strPage;
	strPage = pszPageID;
	return CUIWndThread::ShowPage(strPage, nShow);
}

long UIS_ClosePage(const char *pszPageID)
{
	CString strPage;
	strPage = pszPageID;
	return CUIWndThread::ClosePage(strPage);
}

//////////////////////////////////////////////////////////////////////////
//wnd
void UIS_LogWndNotExist(const char *pszWndName)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Window [%s] 不存在"), pszWndName);
}


void UIS_SetWndHeight(const char *pszWndName, long nHeight)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL)
	{
		pWnd->SetWndHeight(nHeight);
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}
}


long UIS_GetWndHeight(const char *pszWndName)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL) 
	{
		return pWnd->GetWndHeight();
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}

	return 0;
}

void UIS_SetWndWidth(const char *pszWndName, long nWidth)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL)
	{
		pWnd->SetWndWidth(nWidth);
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}
}

long UIS_GetWndWidth(const char *pszWndName)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL)
	{
		return pWnd->GetWndWidth();
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}

	return 0;
}

void UIS_SetWndLeft(const char *pszWndName, long nLeft)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL) 
	{
		pWnd->SetWndLeft(nLeft);
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}
}

long UIS_GetWndLeft(const char *pszWndName)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL)
	{
		return pWnd->GetWndLeft();
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}

	return 0;
}


void UIS_SetWndTop(const char *pszWndName, long nTop)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL) 
	{
		pWnd->SetWndTop(nTop);
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}
}

long UIS_GetWndTop(const char *pszWndName)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL)
	{
		return pWnd->GetWndTop();
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}

	return 0;
}

void UIS_SetWndRight(const char *pszWndName, long nRight)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL) 
	{
		pWnd->SetWndRight(nRight);
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}
}

long UIS_GetWndRight(const char *pszWndName)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL) 
	{
		return pWnd->GetWndRight();
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}

	return 0;
}

void UIS_SetWndBottom(const char *pszWndName, long nBottom)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL) 
	{
		pWnd->SetWndBottom(nBottom);
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}
}

long UIS_GetWndBottom(const char *pszWndName)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL) 
	{
		return pWnd->GetWndBottom();
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}

	return 0;
}

void UIS_SetWndSize(const char *pszWndName, long nWidth, long nHeight)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL) 
	{
		pWnd->SetWndSize(nWidth, nHeight);
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}
}

void UIS_SetWndPosition(const char *pszWndName, long nLeft, long nTop, long nRight, long nBottom)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL)
	{
		pWnd->SetWndPosition(nLeft, nTop, nRight, nBottom);
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}
}

long UIS_IsWndShow(const char *pszWndName)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWndName);

	if (pWnd != NULL)
	{
		return pWnd->IsShow();
	}
	else
	{
		UIS_LogWndNotExist(pszWndName);
	}

	return -1;
}



char* UIS_GetWndText(const char *pszWindowID)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);

	if (pWnd != NULL)
	{
		CString strTemp = pWnd->GetWndText();
		CString_to_char(strTemp, UILuaScript::g_pLuaReturnString);
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
		UILuaScript::g_pLuaReturnString[0] = 0;
	}
	
	return UILuaScript::g_pLuaReturnString;
}

void UIS_SetWndText(const char *pszWindowID, const char *pWndText)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);

	if (pWnd != NULL)
	{
		CString strText;
		strText = pWndText;
		pWnd->SetWndText(strText);
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
	}

}


long UIS_GetWndCurrSel(const char *pszWindowID)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);
	
	if (pWnd != NULL)
	{
		return pWnd->GetWndCurrSel();
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
	}

	return -1;
}

void UIS_SetWndCurrSel(const char *pszWindowID, long nCurrSel)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);
	
	if (pWnd != NULL)
	{
		pWnd->SetWndCurrSel(nCurrSel);
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
	}
}

long UIS_GetCheckState(const char *pszWindowID)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);
	
	if (pWnd != NULL)
	{
		return pWnd->GetCheckState();
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
	}

	return 0;
}

void UIS_SetCheckState(const char *pszWindowID, long nCheckState)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);
	
	if (pWnd != NULL)
	{
		pWnd->SetCheckState(nCheckState);
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
	}
}

void UIS_EnableWnd(const char *pszWindowID, long nEnableWnd)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);
	
	if (pWnd != NULL)
	{
		pWnd->Enable(nEnableWnd);
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
	}
}

long UIS_IsWndEnable(const char *pszWindowID)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);
	
	if (pWnd != NULL)
	{
		return pWnd->IsEnable();
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
	}

	return 0;
}

void UIS_ShowWnd(const char *pszWindowID, long nShow)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);
	
	if (pWnd != NULL)
	{
		pWnd->Show(nShow);
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
	}
}

long UIS_GetWndShow(const char *pszWindowID)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);
	
	if (pWnd != NULL)
	{
		return pWnd->IsShow();
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
	}

	return 0;
}


void UIS_ChangeLanguage(long nSelect)
{
// 	CString strRoot,strRegKey,strRegKeyVal;
// 	switch(nSelect)
// 	{
// 	case 0:
// 		strRegKeyVal = "Chinese";
// 		break;
// 	case 1:
// 		strRegKeyVal = "English";
// 		break;
// 	}
// 
// 	
// 	strRoot	= _P_GetSoftRegKey();
// 	strRegKey = CLanguageMngr::g_strCurrLanguageRegKey;
// 	const char *sRoot = strRoot.GetBuffer(strRoot.GetLength() + 1);
// 	const char *sRegKey = strRegKey.GetBuffer(strRegKey.GetLength() + 1);
// 	const char *sRegKeyVal = strRegKeyVal.GetBuffer(strRegKeyVal.GetLength() + 1);
// 	WriteDataToRegister(sRoot,sRegKey,sRegKeyVal);
// 
// 	strRoot.ReleaseBuffer();
// 	strRegKey.ReleaseBuffer();
// 	strRegKeyVal.ReleaseBuffer();
}


void UIS_ReDrawWnd(const char *pszPageID,const char *pszWindowID)
{
	CUIWndPage *pPage = UIS_GetUIPage(pszPageID);
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);
	
	if (pWnd != NULL)
	{
		pWnd->ReDrawWnd();
	}
	else
	{
		UIS_LogWndNotExist(pszWindowID);
	}
}

//获取多语言文字资源
char* UIS_GetLanguageStringByID(const char *pszStringID)
{
// 	CString strID;
// 	strID = pszStringID;
// 	CString str = GetLanguageStringByID(strID);
// 
// 	if (str.GetLength() > MAX_PATH)
// 	{
// 		str = str.Left(MAX_PATH - 2);
// 	}
// 
// 	CString_to_char(str, UILuaScript::g_pLuaReturnString);

	return UILuaScript::g_pLuaReturnString;
}


//显示系统信息
void UIS_TraceSysInfor(const char *pszMsg)
{
	CString strMsg;
	strMsg = pszMsg;
	CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
}


long UIS_ExecWndCmd(const char *pszWindowID, const char *pszCmd, const char *pszPara)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);

	if (pWnd == NULL)
	{
		return 0;
	}

	return pWnd->ExecWndCmd(pszCmd, pszPara);
}

long UIS_ExecCmd(const char *pszCmd, const char *pszPara)
{
	return 0;
}

long UIS_GetWndAttr(const char *pszWindowID, const char *pszAttr, CString &strValue)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);

	if (pWnd == NULL)
	{
		return -1;
	}

	CString strAttr;
	strAttr = pszAttr;
	return pWnd->GetWndAttr(strAttr, strValue);
}

long UIS_WndAttrEqL(const char *pszWindowID, const char *pszAttr, long nValue)
{
	CString strValue;
	
	if (UIS_GetWndAttr(pszWindowID, pszAttr, strValue) == -1)
	{
		return 0;
	}

	return (nValue == CString_To_long(strValue));
}

long UIS_WndAttrEqD(const char *pszWindowID, const char *pszAttr, double dValue)
{
	CString strValue;

	if (UIS_GetWndAttr(pszWindowID, pszAttr, strValue) == -1)
	{
		return 0;
	}

	return (dValue == CString_To_double(strValue));
}

long UIS_WndAttrEqS(const char *pszWindowID, const char *pszAttr, const char *pszValue)
{
	CString strValue;

	if (UIS_GetWndAttr(pszWindowID, pszAttr, strValue) == -1)
	{
		return 0;
	}

	CString strTemp;
	strTemp = pszValue;

	return (strTemp == strValue);
}


long UIS_SetWndAttr(const char *pszWindowID, const char *pszAttr, const CString &strValue)
{
	CUIWindowBase *pWnd = UIS_GetUIWindow(pszWindowID);

	if (pWnd == NULL)
	{
		return -1;
	}

	CString strAttr;
	strAttr = pszAttr;

	return pWnd->SetWndAttr(strAttr, strValue);
}

void UIS_SetWndAttrL(const char *pszWindowID, const char *pszAttr, long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);

	UIS_SetWndAttr(pszWindowID, pszAttr, strValue);
}

void UIS_SetWndAttrD(const char *pszWindowID, const char *pszAttr, double dValue)
{
	CString strValue;
	strValue.Format(_T("%f"), dValue);

	UIS_SetWndAttr(pszWindowID, pszAttr, strValue);
}

void UIS_SetWndAttrS(const char *pszWindowID, const char *pszAttr, const char *pszValue)
{
	CString strValue;
	strValue  = pszValue;

	UIS_SetWndAttr(pszWindowID, pszAttr, strValue);
}

long UIS_ShellExec(const char *pszExe, const char *pszCmdLine, const char *pszMode)
{
	CString strExe, strCmdLine, strMode;
	strExe = pszExe;
	strExe = _P_GetFullPath(strExe);
	strCmdLine = pszCmdLine;
	strMode = pszMode;

	ExecuteFile(strExe, strCmdLine, strMode);

	return 0;
}


