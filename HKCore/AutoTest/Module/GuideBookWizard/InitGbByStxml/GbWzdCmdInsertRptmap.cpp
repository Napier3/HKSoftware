#include "stdafx.h"
#include "GbWzdCmdInsertRptmap.h"


CGbWzdCmdInsertRptmap::CGbWzdCmdInsertRptmap()
{
	m_strName = _T("");
	m_strID = _T("");
	m_pGbItem = NULL;
}


CGbWzdCmdInsertRptmap::~CGbWzdCmdInsertRptmap()
{
	
}


BOOL CGbWzdCmdInsertRptmap::Execute()
{
	CGbWzdCmd::Execute();
	
	CTreeCtrl *pGbTree = GetGuideBookEditTreeCtrl();
	CGuideBook *pGuideBook = GetGuideBook();
	CExBaseObject *pSel = NULL;
	CExBaseList oListItem;
	pGuideBook->SelectDatas(m_strID, oListItem, _T("$"));
	long nCount = oListItem.GetCount();
	CString strMsg;

	if (nCount == 0)
	{
		strMsg.Format(_T("������Ŀ��%s��������"), m_strName);
		ShowGbWzdMsg(strMsg);
		return FALSE;
	}
	else if (nCount > 1)
	{
		oListItem.RemoveAll();
		strMsg.Format(_T("������Ŀ��%s��������"), m_strName);
		ShowGbWzdMsg(strMsg);
		return FALSE;
	}

	pSel = oListItem.GetHead();
	oListItem.RemoveAll();
	strMsg.Format(_T("������Ŀ��%s��\r\n����ͨѶ�������ݣ����ݼ�����������"), m_strName);
	ShowGbWzdMsg(strMsg);
	pGbTree->SendMessage(WM_USER + 1055, (WPARAM)pSel, (LPARAM)pSel);
	
// 	CFrameWnd* pFrameWnd = GetMaiFrame();
// 	ShowGbWzdMsg(_T("�������ģ�壬������"));
// 	pFrameWnd->PostMessage(WM_COMMAND, ID_FILE_SAVE, 0);//�����豸����ģ�ͶԻ���

	return TRUE;
}

void CGbWzdCmdInsertRptmap::GetCmdInfor(CString &strText)
{
	CGbWzdCmd::GetCmdInfor(strText);
}

BOOL CGbWzdCmdInsertRptmap::IsCmdFinish()
{
	m_nCmdExecState = GBWZDCMD_STATE_FINISH;
	return TRUE;
}

