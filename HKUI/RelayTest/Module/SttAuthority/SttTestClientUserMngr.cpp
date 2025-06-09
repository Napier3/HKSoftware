﻿#include "stdafx.h"
#include "SttTestClientUserMngr.h"
#include "QList"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttUserMngrMutex g_oUserMngrMutex;

CSttTestClientUserMngr::CSttTestClientUserMngr()
{

}

CSttTestClientUserMngr::~CSttTestClientUserMngr()
{

}

CSttTestClientUser *CSttTestClientUserMngr::FindUser(CSttXcmdChInterface *pSocket,long nID_Test)
{
	if (nID_Test != 0)
	{
		return FindByIDTest(nID_Test);
	}

	CExBaseList oUsers;
	CSttTestClientUser *pFind = NULL;

	if (FindByRefSocket(pSocket,oUsers))
	{
		pFind = (CSttTestClientUser *)oUsers.GetHead();
		oUsers.RemoveAll();
	}

	return pFind;
}

BOOL CSttTestClientUserMngr::FindByRefSocket(CSttXcmdChInterface *pSocket,CExBaseList &oUseList)
{
	BOOL bRet = FALSE;
	
	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);

	POS pos = GetHeadPosition();
	CSttTestClientUser *pFind = NULL;

	while(pos != NULL)
	{		
		pFind = (CSttTestClientUser *)GetNext(pos);

		if (pFind->m_pRefSttSckt == pSocket)
		{
			oUseList.AddTail(pFind);
			bRet = TRUE;
		}		
		}
	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	return bRet;
}

BOOL CSttTestClientUserMngr::FindByIdSoft(const CString &strIdSoft,CExBaseList &oUseList)
{
	BOOL bRet = FALSE;
	
	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);

	POS pos = GetHeadPosition();
	CSttTestClientUser *pFind = NULL;

	while(pos != NULL)
	{		
		pFind = (CSttTestClientUser *)GetNext(pos);

		if (pFind->id_soft() == strIdSoft)
		{
			oUseList.AddTail(pFind);
			bRet = TRUE;
		}		
		}
	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	return bRet;
}

CSttTestClientUser *CSttTestClientUserMngr::FindByIDTest(DWORD nID_Test)
{
	POS pos = GetHeadPosition();
	CSttTestClientUser *pFind = NULL;

	while(pos != NULL)
	{
		pFind = (CSttTestClientUser *)GetNext(pos);

		if (pFind->GetIDTest() == nID_Test)
		{
			return pFind;
		}
	}

	return NULL;
}

//2020-11-29   lijunqing
CSttTestClientUser *CSttTestClientUserMngr::FindByIDTest(DWORD nID_Test, const CString &strSoftID)
{
	POS pos = GetHeadPosition();
	CSttTestClientUser *pFind = NULL;

	while(pos != NULL)
	{
		pFind = (CSttTestClientUser *)GetNext(pos);

		if ((pFind->GetIDTest() == nID_Test) && (pFind->id_soft() == strSoftID) )
		{
			return pFind;
		}
	}

	return NULL;
}

CSttTestClientUser *CSttTestClientUserMngr::FindHasAuthority(const CString &strAuthorityID)
{
	POS pos = GetHeadPosition();
	CSttTestClientUser *pFind = NULL;

	while(pos != NULL)
	{
		pFind = (CSttTestClientUser *)GetNext(pos);

		if (pFind->HasAuthority(strAuthorityID))
		{
			return pFind;
		}
	}

	return NULL;
}

BOOL CSttTestClientUserMngr::DeleteUserByRefSocket(CSttXcmdChInterface *pSocket)
{
	POS pos = GetHeadPosition();
	POS prePos = NULL;
	CSttTestClientUser *pFind = NULL;
	BOOL bRet = FALSE;

	while(pos != NULL)
	{
		prePos = pos;
		pFind = (CSttTestClientUser *)GetNext(pos);

		if (pFind->m_pRefSttSckt == pSocket)
		{
			DeleteAt(prePos);
			bRet = TRUE;
		}
	}

	return bRet;
}

void CSttTestClientUserMngr::DeleteUserByIDTest(DWORD nID_Test)
{
	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);

	CSttTestClientUser *pFind = FindByIDTest(nID_Test);

	if (pFind != NULL)
	{
		Delete(pFind);
	}
	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttTestClientUserMngr::DeleteUserByIDTest(DWORD nID_Test, const CString &strSoftID)
{
	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);

	CSttTestClientUser *pFind = FindByIDTest(nID_Test,strSoftID);

	if (pFind != NULL)
	{
		Delete(pFind);
	}
	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttTestClientUserMngr::DeleteUserByIDTerminal(const CString &strIdTerminal)
{
	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);

	POS pos = GetHeadPosition();
	CSttTestClientUser *pUser = NULL;
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		pUser = (CSttTestClientUser *)GetNext(pos);

		if (strIdTerminal == pUser->ID_Terminal())
		{
			DeleteAt(posPrev);
		}
	}
	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

BOOL CSttTestClientUserMngr::UpdateUserList(CSttSysState &oSysState)
{//Login\Logout\Request命令点对点应答后，广播所有用户链表命令
	DeleteAll();

	CSttParas *pSttParas = oSysState.GetSttParas();

	POS pos = pSttParas->GetHeadPosition();
	CExBaseObject *p = NULL;

	while(pos != NULL)
	{
		p = pSttParas->GetNext(pos);

		if (p->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}
		if (p->m_strID != STT_CMD_TESTOR)
		{
			continue;
		}

		CSttTestClientUser *pUser = new CSttTestClientUser();
		p->Copy(pUser);
		AddNewChild(pUser);
	}

	return TRUE;
}

BOOL CSttTestClientUserMngr::UpdateCurrUser(CSttTestClientUser &oCurrUser)
{
	DWORD nIDTester = oCurrUser.GetIDTest();

	CSttTestClientUser *pFind = FindByIDTest(nIDTester);

	if (pFind == NULL)
	{
		return FALSE;
	}

	oCurrUser.DeleteAll();
	oCurrUser.AppendCloneEx(*pFind);
	return TRUE;
}

//用户链表来生成Login\Logout\Request命令应答
void CSttTestClientUserMngr::GenerateSysState(CSttSysState &oSysState)
{
	oSysState.Free();

	CSttTestClientUser *pUser = NULL;
	
	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);

	POS pos = GetHeadPosition();
	CSttParas* pSttParas = oSysState.GetSttParas();

	while(pos != NULL)
	{
		pUser = (CSttTestClientUser *)GetNext(pos);

		CDvmData *pData = pSttParas->AddNewData(STT_CMD_TESTOR, "1", FALSE);

//		CDvmData *pData = oSysState.AddNewParasData(STT_CMD_TESTOR, 1);20231120 zhoulei 配合公共模块修改作出调整
		pData->AppendCloneEx(*pUser);
	}
	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

void CSttTestClientUserMngr::OnAuthority(const CString &strAuthorityID,long nOwnAuthority)
{
	POS pos = GetHeadPosition();
	CSttTestClientUser *p = NULL;

	while(pos != NULL)
	{
		p = (CSttTestClientUser *)GetNext(pos);

		if (p->IsTerminalType_Native())
		{
			p->SetAuthority(strAuthorityID,nOwnAuthority);
		}
		else
		{
			p->SetAuthority(strAuthorityID,0);
		}
	}
}

void CSttTestClientUserMngr::ClearOtherAuthoritys(CExBaseList *pParas, CSttTestClientUser *pCurrUser)
{	
	CSttTestClientUser *p = NULL;
	POS pos = GetHeadPosition();

	while(pos != NULL)
	{
		p = (CSttTestClientUser *)GetNext(pos);

		if (p == pCurrUser)
		{
			continue;
		}

		//取消其他用户的权限，取消的权限为当前用户授权的权限
		p->ClearAuthoritys(pParas);
	}
}

void CSttTestClientUserMngr::RestartRecvHeartbeatTickCount(DWORD nID_Test)
{
	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);

	CSttTestClientUser *pFind = FindByIDTest(nID_Test);
	if (pFind == NULL || pFind->m_pRefSttSckt == NULL)
	{
		g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
		return;
	}

	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	pFind->m_pRefSttSckt->XRestartRecvHeartbeatTickCount();
}

//2020-11-29  lijunqing
//根据软件ID返回报文
void CSttTestClientUserMngr::SendToAllUser(const CString &strSoftID, BYTE *pBuf,long nLen)
{
	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);

    CSttTestClientUser *pUser = NULL;
    POS pos = GetHeadPosition();

    while(pos != NULL)
    {
        pUser = (CSttTestClientUser *)GetNext(pos);

        if (pUser->m_pRefSttSckt == NULL)
        {
            continue;
        }

        if (pUser->id_soft() == strSoftID)
        {
            pUser->m_pRefSttSckt->XSendBuffer(pBuf,nLen);
        }
    }

	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
}

//2020-11-29  lijunqing
void CSttTestClientUserMngr::SendSysState(CSttXcmdChInterface *pCurrSocket, CSttSysState *pSysState, BOOL bSpyAllCmd)
{
    BYTE *pSendBuf = NULL;
    long nSendBufLen = 0;

	if (pCurrSocket != NULL)
	{
		stt_InitRetSendBuf(&pSendBuf,nSendBufLen,pSysState, FALSE, pCurrSocket->m_nSttCmdDataFormat);
	}
	else
	{
		stt_InitRetSendBuf(&pSendBuf,nSendBufLen,pSysState, FALSE, _PUGI_XML_TYPE_);
	}

    if (pCurrSocket != NULL)
    {
        pCurrSocket->XSendBuffer(pSendBuf,nSendBufLen);
    }

    if (bSpyAllCmd)
    {
        //返回非Debug的全部报文
        if (! pCurrSocket->Match_IdSoft( STT_SOFT_ID_DEBUG) )
        {
            SendToAllUser(STT_SOFT_ID_DEBUG, pSendBuf, nSendBufLen);
        }
    }

    delete pSendBuf;
}

//2020-12-08  lijunqing
void CSttTestClientUserMngr::SendCmd(CSttXcmdChInterface *pCurrSocket, CSttCmdBase *pSttCmd, BOOL bSpyAllCmd)
{
    BYTE *pSendBuf = NULL;
    long nSendBufLen = 0;

	if (pCurrSocket != NULL)
	{
	   stt_InitSendBuf_Cmd(&pSendBuf,nSendBufLen,pSttCmd, FALSE, pCurrSocket->m_nSttCmdDataFormat);
	}
	else
	{
		stt_InitSendBuf_Cmd(&pSendBuf,nSendBufLen,pSttCmd, FALSE, _PUGI_XML_TYPE_);
	}

    if (pCurrSocket != NULL)
    {
        pCurrSocket->XSendBuffer(pSendBuf,nSendBufLen);
    }

    if (bSpyAllCmd)
    {
        //返回非Debug的全部报文
        if (! pCurrSocket->Match_IdSoft( STT_SOFT_ID_DEBUG) )
        {
            SendToAllUser(STT_SOFT_ID_DEBUG, pSendBuf, nSendBufLen);
        }
    }

    delete pSendBuf;
}

