#include "StdAfx.h"
#include "MsgSendRegister.h"
#include "../XLanguage/XLanguageResource.h"
CMsgSendRegister::CMsgSendRegister()
{
	m_nMsgType = MSGSENDTYPE_WINDOW;   //线程消息、窗口消息
	m_nHWndOrThreadID = 0;  //窗口的句本或者线程的ID
	m_nMessageID = 0;           //消息ID
	m_lParam = 0;
	m_wParam = 0;     
	m_nItemData = 0;           //关联的数据
}

CMsgSendRegister::~CMsgSendRegister()
{

}

BOOL CMsgSendRegister::IsEqual(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
{
	if ( (dwMask & MSREGMASK_MSGTYPE) == MSREGMASK_MSGTYPE)
	{
		if (pMsgRegister->nMsgType != m_nMsgType)
		{
			return FALSE;
		}
	}

	if ( (dwMask & MSREGMASK_HWNDORTHREADID) == MSREGMASK_HWNDORTHREADID)
	{
		if (pMsgRegister->nHWndOrThreadID != m_nHWndOrThreadID)
		{
			return FALSE;
		}
	}

	if ( (dwMask & MSREGMASK_MESSAGEID) == MSREGMASK_MESSAGEID)
	{
		if (pMsgRegister->nMessageID != m_nMessageID)
		{
			return FALSE;
		}
	}

	if ( (dwMask & MSREGMASK_LPARAM) == MSREGMASK_LPARAM)
	{
		if (pMsgRegister->lParam != m_lParam)
		{
			return FALSE;
		}
	}

	if ( (dwMask & MSREGMASK_WPARAM) == MSREGMASK_WPARAM)
	{
		if (pMsgRegister->wParam != m_wParam)
		{
			return FALSE;
		}
	}

	if ( (dwMask & MSREGMASK_ITEMDATA) == MSREGMASK_ITEMDATA)
	{
		if (pMsgRegister->nItemData != m_nItemData)
		{
			return FALSE;
		}
	}

	if ( (dwMask & MSREGMASK_MSGTYPE) == MSREGMASK_MSGTYPE)
	{
		if (pMsgRegister->nMsgType != m_nMsgType)
		{
			return FALSE;
		}
	}

	if ( (dwMask & MSREGMASK_ID) == MSREGMASK_ID)
	{
		if (pMsgRegister->strID != m_strID)
		{
			return FALSE;
		}
	}

	return TRUE;
}


void CMsgSendRegister::Init(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
{
	if ( (dwMask & MSREGMASK_MSGTYPE) == MSREGMASK_MSGTYPE)
	{
		m_nMsgType = pMsgRegister->nMsgType;
	}

	if ( (dwMask & MSREGMASK_HWNDORTHREADID) == MSREGMASK_HWNDORTHREADID)
	{
		m_nHWndOrThreadID = pMsgRegister->nHWndOrThreadID;
	}

	if ( (dwMask & MSREGMASK_MESSAGEID) == MSREGMASK_MESSAGEID)
	{
		m_nMessageID = pMsgRegister->nMessageID;
	}

	if ( (dwMask & MSREGMASK_LPARAM) == MSREGMASK_LPARAM)
	{
		m_lParam = pMsgRegister->lParam;
	}

	if ( (dwMask & MSREGMASK_WPARAM) == MSREGMASK_WPARAM)
	{
		m_wParam = pMsgRegister->wParam;
	}

	if ( (dwMask & MSREGMASK_ITEMDATA) == MSREGMASK_ITEMDATA)
	{
		m_nItemData = pMsgRegister->nItemData;
	}

	if ( (dwMask & MSREGMASK_MSGTYPE) == MSREGMASK_MSGTYPE)
	{
		m_nMsgType = pMsgRegister->nMsgType;
	}

	if ( (dwMask & MSREGMASK_ID) == MSREGMASK_ID)
	{
		m_strID = pMsgRegister->strID;
	}
}

void CMsgSendRegister::PostMessage(long wPara, long lPara)
{
#ifndef _PSX_QT_LINUX_
    if (wPara < 0)
	{
		wPara = m_wParam;
	}

	if (lPara < 0)
	{
		lPara = m_lParam;
	}

    if (MSGSENDTYPE_WINDOW == m_nMsgType)
	{
		HWND hWnd = (HWND)m_nHWndOrThreadID;

		if (::IsWindow(hWnd))
		{
			::PostMessage(hWnd, m_nMessageID, wPara, lPara);
			//TRACE(_T("PostMessage(hWnd=%08x, m_nMessageID=%08x)"), hWnd, m_nMessageID);
		}
	}
	else
	{
		::PostThreadMessage(m_nHWndOrThreadID, m_nMessageID, wPara, lPara);
		//TRACE(_T("PostMessage(m_nHWndOrThreadID=%08x, m_nMessageID=%08x)"), m_nHWndOrThreadID, m_nMessageID);
	}
#endif
}

CMessageMngr::CMessageMngr(void)
{
}

CMessageMngr::~CMessageMngr(void)
{
}

CMsgSendRegister* CMessageMngr::Register(ULONG nMsgType, ULONG nHWndOrThreadID, ULONG nMessageID, LPARAM lParam, WPARAM wParam, ULONG nItemData)
{
	CAutoSimpleLock oLock(m_oMsgMngrCriticSection);
	CMsgSendRegister *pRegister = new CMsgSendRegister();

	pRegister->m_nMsgType = nMsgType;
	pRegister->m_nHWndOrThreadID = nHWndOrThreadID;
	pRegister->m_nMessageID = nMessageID;
	pRegister->m_lParam = lParam;
	pRegister->m_wParam = wParam;
	pRegister->m_nItemData = nItemData;

	AddTail(pRegister);

	return pRegister;
}

CMsgSendRegister* CMessageMngr::Find(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
{
	CMsgSendRegister *pFind = NULL;
	CMsgSendRegister *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CMsgSendRegister*)GetNext(pos);

		if (p->IsEqual(pMsgRegister, dwMask))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CMessageMngr::UnRegister(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
{
	CAutoSimpleLock oLock(m_oMsgMngrCriticSection);

	while (TRUE)
	{
		CMsgSendRegister *p = NULL;
		p = Find(pMsgRegister, dwMask);

		if (p != NULL)
		{
			Delete(p);
		}
		else
		{
			break;
		}
	}
}

CMsgSendRegister* CMessageMngr::Register(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
{
	CAutoSimpleLock oLock(m_oMsgMngrCriticSection);
	CMsgSendRegister *pRegister = new CMsgSendRegister();

	pRegister->Init(pMsgRegister, dwMask);
	AddTail(pRegister);

	return pRegister;
}

void CMessageMngr::PostMessageByID(const CString &strProcedureID, long wPara, long lPara)
{
	CAutoSimpleLock oLock(m_oMsgMngrCriticSection);

	CMsgSendRegister *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CMsgSendRegister*)GetNext(pos);

		if (p->m_strID == strProcedureID)
		{
			p->PostMessage(wPara, lPara);
		}
	}
}


void CMessageMngr::PostMessageByItemData(ULONG nItemData, long wPara, long lPara)
{
	CAutoSimpleLock oLock(m_oMsgMngrCriticSection);

	CMsgSendRegister *p = NULL;
	POS pos = GetHeadPosition();
	long nCount = 0;

	while (pos != NULL)
	{
		p = (CMsgSendRegister*)GetNext(pos);

		if (p->m_nItemData == nItemData)
		{
			p->PostMessage(wPara, lPara);
			nCount++;
		}
	}

	if (nCount == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                 , g_sLangTxt_NoDataChangeMsg.GetString()/*_T("没有注册节点[%d]数据改变消息")*/, nItemData);
	}
}

