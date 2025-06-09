#include "stdafx.h"
#include "GbWzdCmd.h"
#include "..\XLanguageResourceAts.h"
#include "GuideBookWizard.h"

//////////////////////////////////////////////////////////////////////////
CGbWzdCmd::CGbWzdCmd()
{
	m_nCmdExecState = GBWZDCMD_STATE_NORMAL;
}


CGbWzdCmd::~CGbWzdCmd()
{
	
}



long CGbWzdCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CGbWzdCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}

long CGbWzdCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	return 0;
}

BSTR CGbWzdCmd::GetXmlElementKey()
{
	return CGbWzdToolXmlRWKeys::CGbWzdCmdKey();
}


BOOL CGbWzdCmd::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CGbWzdCmd::CopyOwn(CBaseObject* pDesObj)
{
	return TRUE;
}

CBaseObject* CGbWzdCmd::Clone()
{
	CGbWzdCmd *pNew = new CGbWzdCmd();
	Copy(pNew);
	return pNew;
}



BOOL CGbWzdCmd::Execute(DWORD dwExecMode)
{
	m_nCmdExecState = GBWZDCMD_STATE_EXEC;
	PostExecCmdMsg();
	return TRUE;
}

void CGbWzdCmd::GetStateInfor(CString &strText)
{
	switch (m_nCmdExecState)
	{
	case GBWZDCMD_STATE_NORMAL:
		strText = _T("");
		break;

	case GBWZDCMD_STATE_EXEC:
		strText = /*_T("Ö´ÐÐ")*/g_sLangTxt_Execute;
		break;

	case GBWZDCMD_STATE_FINISH:
		strText = _T("--");
		break;

	default:
		strText = _T("");
		break;
	}
}

void CGbWzdCmd::GetCmdInfor(CString &strText)
{
	strText = m_strName;
}

long CGbWzdCmd::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);

	GetStateInfor(strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, strTemp);

	GetCmdInfor(strTemp);
	pListCtrl->SetItemText(lItemIndex, 2, strTemp);
	
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);

	return 0;
}


CGuideBook* CGbWzdCmd::GetGuideBook()
{
	CGuideBookWizard *pWzd = (CGuideBookWizard*)GetAncestor(GBWZDCLASSID_GBWIZARD);
	ASSERT (pWzd != NULL);
	return pWzd->m_pGuideBook;
}

CTreeCtrl* CGbWzdCmd::GetGuideBookEditTreeCtrl()
{
	CGuideBookWizard *pWzd = (CGuideBookWizard*)GetAncestor(GBWZDCLASSID_GBWIZARD);
	ASSERT (pWzd != NULL);
	return pWzd->m_pGbTree;
}

CFrameWnd* CGbWzdCmd::GetMaiFrame()
{
	CGuideBookWizard *pWzd = (CGuideBookWizard*)GetAncestor(GBWZDCLASSID_GBWIZARD);
	ASSERT (pWzd != NULL);
	return pWzd->m_pMainFrame;
}

CWnd* CGbWzdCmd::GetGbWzdWnd()
{
	CGuideBookWizard *pWzd = (CGuideBookWizard*)GetAncestor(GBWZDCLASSID_GBWIZARD);
	ASSERT (pWzd != NULL);
	return pWzd->m_pWndGbWzd;
}

CDevice* CGbWzdCmd::GetDevice()
{
	CGuideBook *pGuideBook = GetGuideBook();
	return pGuideBook->GetDevice();
}

void CGbWzdCmd::ShowGbWzdMsg(const CString &strWzdMsg)
{
	CWnd *pWnd = GetGbWzdWnd();
	pWnd->SendMessage(WM_EXEC_GBWZD_MSG, (WPARAM)&strWzdMsg, (LPARAM)this);
}

void CGbWzdCmd::UpdateWzdState()
{
	CWnd *pWnd = GetGbWzdWnd();
	pWnd->SendMessage(WM_EXEC_GBWZD_STATE, (WPARAM)this, (LPARAM)this);
}

void CGbWzdCmd::PostExecCmdMsg()
{
	CWnd *pGbWzdWnd = GetGbWzdWnd();
	ASSERT(pGbWzdWnd != NULL);
	pGbWzdWnd->PostMessage(WM_EXEC_GBWZD_CMD, (WPARAM)this, (LPARAM)this);
}

//////////////////////////////////////////////////////////////////////////
CGbWzdCmdList::CGbWzdCmdList()
{
	m_nWzdCmdIndex = -1;
	m_listCmd.SetParent(this);
}


CGbWzdCmdList::~CGbWzdCmdList()
{

}

BOOL CGbWzdCmdList::Execute(DWORD dwExecMode)
{
	return ExecNextGbWzdCmd(dwExecMode);
}

BOOL CGbWzdCmdList::IsCmdFinish()	
{	
	CGbWzdCmd *pTail = (CGbWzdCmd*)m_listCmd.GetTail();
	CGbWzdCmd *pCurr = GetCurrGbWzdCmd();

	ASSERT (pTail != NULL);

	if (pTail == NULL)
	{
		m_nCmdExecState = GBWZDCMD_STATE_FINISH;
		return TRUE;
	}

	if (pTail == pCurr && pCurr->IsCmdFinish())
	{
		m_nCmdExecState = GBWZDCMD_STATE_FINISH;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CGbWzdCmdList::ResetCmdList()
{
	m_nWzdCmdIndex = 0;
	POS pos = m_listCmd.GetHeadPosition();
	CGbWzdCmd *pCmd = NULL;

	while (pos != NULL)
	{
		pCmd = (CGbWzdCmd *)m_listCmd.GetNext(pos);
		pCmd->ResetState();
	}

	return (m_listCmd.GetCount() > 0);
}

CGbWzdCmd* CGbWzdCmdList::GetCurrGbWzdCmd()
{
	CGbWzdCmd *pGbWzdCmd = NULL;
	ASSERT (m_nWzdCmdIndex < m_listCmd.GetCount());

	if (m_nWzdCmdIndex >= m_listCmd.GetCount())
	{
		pGbWzdCmd = NULL;
	}
	else
	{
		pGbWzdCmd = (CGbWzdCmd *)m_listCmd.GetAtIndex(m_nWzdCmdIndex);
	}

	return pGbWzdCmd;
}

CGbWzdCmd* CGbWzdCmdList::GetNextGbWzdCmd()
{
	m_nWzdCmdIndex++;
	return GetCurrGbWzdCmd();
}

BOOL CGbWzdCmdList::ExecCurrGbWzdCmd(DWORD dwExecMode)
{
	CGbWzdCmd *pGbWzdCmd = GetCurrGbWzdCmd();
	ASSERT (pGbWzdCmd != NULL);

	if (pGbWzdCmd == NULL)
	{
		return FALSE;
	}
	else
	{
		return pGbWzdCmd->Execute(dwExecMode);
	}
}

BOOL CGbWzdCmdList::ExecNextGbWzdCmd(DWORD dwExecMode)
{
	CGbWzdCmd *pGbWzdCmd = GetCurrGbWzdCmd();
	ASSERT (pGbWzdCmd != NULL);
	BOOL bTrue = FALSE;
	CWnd *pWndGbWzd = GetGbWzdWnd();

	if (pGbWzdCmd == NULL)
	{
		pWndGbWzd->PostMessage(WM_EXEC_GBWZD_FINISH, 0, 0);
		return FALSE;
	}

	if (!pGbWzdCmd->IsCmdFinish())
	{
		bTrue = pGbWzdCmd->Execute(dwExecMode);
		pGbWzdCmd->UpdateWzdState();
		return bTrue;
	}

	pGbWzdCmd->UpdateWzdState();
	pGbWzdCmd = GetNextGbWzdCmd();

	if (pGbWzdCmd == NULL)
	{
		return FALSE;
	}

	bTrue = pGbWzdCmd->Execute(dwExecMode);
	pGbWzdCmd->UpdateWzdState();
	
	return bTrue;
}

BOOL CGbWzdCmdList::IsCurrCmdFinish()
{
	CGbWzdCmd *pGbWzdCmd = GetCurrGbWzdCmd();
	ASSERT (pGbWzdCmd != NULL);

	if (pGbWzdCmd == NULL)
	{
		return TRUE;
	}

	return pGbWzdCmd->IsCmdFinish();
}

