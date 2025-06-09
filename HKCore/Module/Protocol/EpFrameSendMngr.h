#pragma once
#include "..\baseclass\exbaselist.h"
#include "EpFrameBase.h"
#include "CmmChannel\EpCmmChannel.h"

class CEpFrameSendMngr :	public CExBaseList
{
public:
	CEpFrameSendMngr(void);
	~CEpFrameSendMngr(void);

public:
	CEpFrameBase* AddNew(CExBaseObject *pPpProcedure, CEpCmmChannel *pChannel);

	void DeleteSendFrames();
	BOOL HasAllSend();
};
