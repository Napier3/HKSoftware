#pragma once
#include "ExBaseList.h"
#include "PpPackageSend.h"

class CPpPackageSendMngr :	public CExBaseList
{
public:
	CPpPackageSendMngr(void);
	virtual ~CPpPackageSendMngr(void);

public:
	CPpPackageSend* AddNew(CExBaseObject *pPpProcedureRun, CCmmChannel *pChannel, long nBufferLen);

	void DeleteSendPackages();
	BOOL HasAllSend();
};
