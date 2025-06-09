#include "StdAfx.h"
#include "PpPackageSendMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpPackageSendMngr::CPpPackageSendMngr(void)
{
}

CPpPackageSendMngr::~CPpPackageSendMngr(void)
{
	DeleteAll();
}

CPpPackageSend* CPpPackageSendMngr::AddNew(CExBaseObject *pPpProcedureRun, CCmmChannel *pChannel, long nBufferLen)
{
	CPpPackageSend *pPkgSend = new CPpPackageSend(pPpProcedureRun, pChannel, nBufferLen);
	pPkgSend->SetParent(this);
	AddTail(pPkgSend);
	return pPkgSend;
}

void CPpPackageSendMngr::DeleteSendPackages()
{
	POS posTail = GetTailPosition();
	POS pos = GetHeadPosition();
	CPpPackageSend *pPkgSend = NULL;
	POS posPrev = NULL;

	while (pos != posTail)
	{
		posPrev = pos;
		pPkgSend = (CPpPackageSend*)GetNext(pos);

		//已经发送并且没有被锁住
		if (pPkgSend->HasSended() && !pPkgSend->IsLock() && pPkgSend->IsTimeout() )
		{
			RemoveAt(posPrev);
			delete pPkgSend;
		}
	}
}

BOOL CPpPackageSendMngr::HasAllSend()
{
	POS pos = GetHeadPosition();
	CPpPackageSend *pPkgSend = NULL;
	BOOL bTue = TRUE;

	while (pos != NULL)
	{
		pPkgSend = (CPpPackageSend*)GetNext(pos);

		//已经发送并且没有被锁住
		if ( ! pPkgSend->HasSended() )
		{
			bTue = FALSE;
			break;
		}
	}

	return bTue;
}

