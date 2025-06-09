#include "stdafx.h"
#include "SttAppWndAssistInterface.h"

//显示/隐藏一个子窗口
void CSttWndAssistInterface::ast_Show(const CString &strWndIdPath, bool bShow)
{

}

//窗口样式
void CSttWndAssistInterface::ast_SetStyle(const CString &strWndIDPath, const CString &strStyle)
{

}

CString CSttWndAssistInterface::ast_GetStyle(const CString &strWndIDPath)
{
	CString strStyle;

	return strStyle;
}

//查找窗口，保留用 找到返回窗口,      否则返回NULL
CSttWndAssistInterface* CSttWndAssistInterface::ast_FindWnd(const CString &strWndID)
{
	return NULL;
}

//获取窗口位置 找到窗口返回true，否则返回false
bool CSttWndAssistInterface::ast_GetWndPos(const CString &strWndIdPath, CRect &rcWndPos)
{
	return false;
}

