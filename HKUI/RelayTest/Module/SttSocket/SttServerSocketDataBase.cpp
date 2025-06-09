#include "stdafx.h"

#include "SttServerSocketDataBase.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttServerSocketDataBase::CSttServerSocketDataBase()
{
	m_nMaxClientCount = 5;
	m_pCmdOverTimeMsgRcv = NULL;
	m_pTestEngine = NULL;
}

CSttServerSocketDataBase::~CSttServerSocketDataBase()
{
}

void CSttServerSocketDataBase::OnSttSktAccept(CSttSocketDataBase_File *pSttSkt)
{
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s Connect"), pSttSkt->m_strIPRemote.GetString());

	CAutoSimpleLock oLock(m_oCriticSection);

	pSttSkt->AttachCmdOverTimeMsgRcv(this);
	AddNewChild(pSttSkt);
}

void CSttServerSocketDataBase::OnSttScktClose(CSttXcmdChInterface *pSttSckt, BOOL bDeleteSocket)
{
	if (pSttSckt == NULL)
	{
		return;
	}

    //CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s Disconnect[OnSttScktClose]"), pSttSckt->m_strIPRemote.GetString());

	if (bDeleteSocket)
	{
        //CAutoSimpleLock oLock(m_oCriticSection);
        Delete((CSttSocketDataBase*)pSttSckt);
	}
}

void CSttServerSocketDataBase::CloseSttServer()
{
	{
		CAutoSimpleLock oLock(m_oCriticSection);

		POS pos = GetHeadPosition();
		CSttSocketDataBase *p = NULL;

		while (pos != NULL)
		{
			p = (CSttSocketDataBase *)GetNext(pos);

			p->CloseSocket();
		}
	}
	
	CTickCount32 oTick(FALSE);
	while(GetCount() > 0)
	{
		oTick.DoEvents(5);
	}
}

void CSttServerSocketDataBase::AttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv)
{
	m_pCmdOverTimeMsgRcv = pCmdOverTimeMsgRcv;
}

void CSttServerSocketDataBase::OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	if (m_pCmdOverTimeMsgRcv != NULL)
	{	
		m_pCmdOverTimeMsgRcv->OnSendCmdFinish(pSocketRef,nCmdType,pszCmdID);		
	}
}

void CSttServerSocketDataBase::OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{
	CSttSocketDataBase_File *pSocket = (CSttSocketDataBase_File *)pSocketRef;
	if (m_pCmdOverTimeMsgRcv != NULL)
	{	
		m_pCmdOverTimeMsgRcv->OnSendCmdOverTime(pSocketRef,nCmdType,pszCmdID);		
	}

	if (IsSocketExist(pSocket))
	{
		pSocket->ProcessCmd_End();
	}
}

BOOL CSttServerSocketDataBase::IsSocketExist(CSttSocketDataBase_File *p)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	POS pos = GetHeadPosition();
	CSttSocketDataBase_File *pSocket = NULL;

	while(pos != NULL)
	{
		pSocket = (CSttSocketDataBase_File *)GetNext(pos);

		if (pSocket == p)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSttServerSocketDataBase::SendBufferToChildren(CSttSocketDataBase *pExceptSocket,BYTE *pBuf,long nLen)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	POS pos = GetHeadPosition();
	CSttSocketDataBase *p = NULL;

	while( pos != NULL )
	{
		p = (CSttSocketDataBase *)GetNext(pos);

		if(p != pExceptSocket)
		{
			p->SendBuffer(pBuf,nLen);
		}
	}

	return TRUE;
}
