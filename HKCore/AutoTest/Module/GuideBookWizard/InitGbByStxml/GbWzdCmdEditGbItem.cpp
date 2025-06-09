#include "stdafx.h"
#include "GbWzdCmdEditGbItem.h"
#include "..\..\XLanguageResourceAts.h"

CGbWzdCmdEditGbItem::CGbWzdCmdEditGbItem()
{
	m_strName = _T("");
	m_strID = _T("");
	m_pGbItem = NULL;
}


CGbWzdCmdEditGbItem::~CGbWzdCmdEditGbItem()
{
	
}


BOOL CGbWzdCmdEditGbItem::Execute(DWORD dwExecMode)
{
	CGbWzdCmd::Execute(dwExecMode);
	
	CTreeCtrl *pGbTree = GetGuideBookEditTreeCtrl();
	CGuideBook *pGuideBook = GetGuideBook();
	CExBaseObject *pSel = NULL;
	CExBaseList oListItem;
	pGuideBook->SelectDatas(m_strID, oListItem, _T("$"));
	long nCount = oListItem.GetCount();
	CString strMsg;

	if (nCount == 0)
	{
		strMsg.Format(/*_T("测试项目【%s】不存在")*/g_sLangTxt_TestItemNotExist, m_strName);
		ShowGbWzdMsg(strMsg);
		return FALSE;
	}
	else if (nCount > 1)
	{
		oListItem.RemoveAll();
		strMsg.Format(/*_T("测试项目【%s】不存在")*/g_sLangTxt_TestItemNotExist, m_strName);
		ShowGbWzdMsg(strMsg);
		return FALSE;
	}

	pSel = oListItem.GetHead();
	oListItem.RemoveAll();
	strMsg.Format(/*_T("设置项目【%s】\r\n设置通讯命令数据：数据集、参数数据")*/g_sLangTxt_SetItem, m_strName);
	ShowGbWzdMsg(strMsg);
	pGbTree->SendMessage(WM_USER + 1055, (WPARAM)pSel, (LPARAM)pSel);
	
// 	CFrameWnd* pFrameWnd = GetMaiFrame();
// 	ShowGbWzdMsg(_T("保存测试模板，结束向导"));
// 	pFrameWnd->PostMessage(WM_COMMAND, ID_FILE_SAVE, 0);//导入设备数据模型对话框

	return TRUE;
}

void CGbWzdCmdEditGbItem::GetCmdInfor(CString &strText)
{
	CGbWzdCmd::GetCmdInfor(strText);
}

BOOL CGbWzdCmdEditGbItem::IsCmdFinish()
{
	m_nCmdExecState = GBWZDCMD_STATE_FINISH;
	return TRUE;
}

