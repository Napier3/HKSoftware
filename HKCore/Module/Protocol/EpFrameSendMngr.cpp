#include "StdAfx.h"
#include "EpFrameSendMngr.h"

CEpFrameSendMngr::CEpFrameSendMngr(void)
{
}

CEpFrameSendMngr::~CEpFrameSendMngr(void)
{
	DeleteAll();
}

CEpFrameBase* CEpFrameSendMngr::AddNew(CExBaseObject *pPpProcedure, CEpCmmChannel *pChannel)
{
	CEpFrameBase *pPkgSend = new CEpFrameBase();
	pPkgSend->InitSend(pPpProcedure, pChannel);
	AddTail(pPkgSend);
	return pPkgSend;
}

void CEpFrameSendMngr::DeleteSendFrames()
{
	POS posTail = GetTailPosition();
	POS pos = GetHeadPosition();
	CEpFrameBase *pPkgSend = NULL;
	POS posPrev = NULL;

	while (pos != posTail)
	{
		posPrev = pos;
		pPkgSend = (CEpFrameBase*)GetNext(pos);

		//已经发送并且没有被锁住
		if (pPkgSend->HasSended() && !pPkgSend->IsLock())
		{
			RemoveAt(posPrev);
			delete pPkgSend;
		}
	}
}

BOOL CEpFrameSendMngr::HasAllSend()
{
	POS pos = GetHeadPosition();
	CEpFrameBase *pPkgSend = NULL;
	BOOL bTue = TRUE;

	while (pos != NULL)
	{
		pPkgSend = (CEpFrameBase*)GetNext(pos);

		//已经发送并且没有被锁住
		if ( ! pPkgSend->HasSended() )
		{
			bTue = FALSE;
			break;
		}
	}

	return bTue;
}

