// ExternInstruct.h: interface for the CMessageImp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EXTERNINSTRUCT_H__)
#define _EXTERNINSTRUCT_H__

#include "UIWndPage.h"
#include "UIWndLayer.h"
#include "UIWndMain.h"

CUIWndPage* UIS_GetUIPage(const char*pszPageID);
long UIS_ShowMessageBox(const char *pszModal, const char *pszFormat, const char *pszMsg);

//设置\获取Layer位置、大小
void UIS_SetLayerHeight(const char *pszLayerName, long nHeight);
long UIS_GetLayerHeight(const char *pszLayerName);
void UIS_SetLayerWidth(const char *pszLayerName, long nWidth);
long UIS_GetLayerWidth(const char *pszLayerName);
void UIS_SetLayerLeft(const char *pszLayerName, long nLeft);
long UIS_GetLayerLeft(const char *pszLayerName);
void UIS_SetLayerTop(const char *pszLayerName, long nTop);
long UIS_GetLayerTop(const char *pszLayerName);
void UIS_SetLayerRight(const char *pszLayerName, long nRight);
long UIS_GetLayerRight(const char *pszLayerName);
void UIS_SetLayerBottom(const char *pszLayerName, long nBottom);
long UIS_GetLayerBottom(const char *pszLayerName);
void UIS_SetLayerSize(const char *pszLayerName, long nWidth, long nHeight);
void UIS_SetLayerPosition(const char *pszLayerName, long nLeft, long nTop, long nRight, long nBottom);
void UIS_ShowLayer(const char *pszLayerName, long nShow);
long UIS_IsLayerShow(const char *pszLayerName);

//page
long UIS_GetPageWidth(const char *pszPageName);
void UIS_SetPageWidth(const char *pszPageName, long nWidth);
long UIS_GetPageHeight(const char *pszPageName);
void UIS_SetPageHeight(const char *pszPageName, long nHeight);
void UIS_SetPagePosition(const char *pszPageName, long nLeft, long nTop, long nRight, long nBottom);
void UIS_SetPageSize(const char *pszPageName, long nWidth, long nHeight);
long UIS_ShowPage(const char *pszPageID, long nShow);
long UIS_ClosePage(const char *pszPageID);

//设置\获取wnd的位置、大小
void UIS_SetWndHeight(const char *pszWndName, long nHeight);
long UIS_GetWndHeight(const char *pszWndName);
void UIS_SetWndWidth(const char *pszWndName, long nWidth);
long UIS_GetWndWidth(const char *pszWndName);
void UIS_SetWndLeft(const char *pszWndName, long nLeft);
long UIS_GetWndLeft(const char *pszWndName);
void UIS_SetWndTop(const char *pszWndName, long nTop);
long UIS_GetWndTop(const char *pszWndName);
void UIS_SetWndRight(const char *pszWndName, long nRight);
long UIS_GetWndRight(const char *pszWndName);
void UIS_SetWndBottom(const char *pszWndName, long nBottom);
long UIS_GetWndBottom(const char *pszWndName);
void UIS_SetWndSize(const char *pszWndName, long nWidth, long nHeight);
void UIS_SetWndPosition(const char *pszWndName, long nLeft, long nTop, long nRight, long nBottom);

//设置\获取wnd的文本
char* UIS_GetWndText(const char *pszWindowID);
void UIS_SetWndText(const char *pszWindowID, const char *pWndText);

//设置\获取wnd的显示状态
void UIS_ShowWnd(const char *pszWindowID, long nShow);
long UIS_IsWndShow(const char *pszWindowID);

void UIS_EnableWnd(const char *pszWindowID, long nEnableWnd);
long UIS_IsWndEnable(const char *pszWindowID);

long UIS_GetWndCurrSel(const char *pszWindowID);
void UIS_SetWndCurrSel(const char *pszWindowID, long nCurrSel);

long UIS_GetCheckState(const char *pszWindowID);
void UIS_SetCheckState(const char *pszWindowID, long nCheckState);

//修改当前的时间
void UIS_ChangeLanguage(long nSelect);
CUIWindowBase* UIS_GetUIWindow(const char *pszWindowID);

//重新绘制某个Page的某个Wnd
void UIS_ReDrawWnd(const char *pszPageID,const char *pszWindowID);

//显示系统信息
void UIS_TraceSysInfor(const char *pszMsg);

//获取多语言文字资源
char* UIS_GetLanguageStringByID(const char *pszStringID);

inline CUIWndLayer* UIS_GetUILayer(const char *pszLayerID);

long UIS_ExecWndCmd(const char *pszWindowID, const char *pszCmd, const char *pszPara);
long UIS_ExecCmd(const char *pszCmd, const char *pszPara);
long UIS_WndAttrEqL(const char *pszWindowID, const char *pszAttr, long nValue);
long UIS_WndAttrEqD(const char *pszWindowID, const char *pszAttr, double dValue);
long UIS_WndAttrEqS(const char *pszWindowID, const char *pszAttr, const char *pszValue);
void UIS_SetWndAttrL(const char *pszWindowID, const char *pszAttr, long nValue);
void UIS_SetWndAttrD(const char *pszWindowID, const char *pszAttr, double dValue);
void UIS_SetWndAttrS(const char *pszWindowID, const char *pszAttr, const char *pszValue);
long UIS_ShellExec(const char *pszExe, const char *pszCmdLine, const char *pszMode);


#endif // !defined(_EXTERNINSTRUCT_H__)
