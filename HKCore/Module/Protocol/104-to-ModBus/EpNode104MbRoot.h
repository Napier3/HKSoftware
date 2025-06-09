// EpNode104MbRoot.h: interface for the CEpNode104MbRoot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPNODE104MBROOT_H__)
#define _EPNODE104MBROOT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ProtocolBase\EpNode.h"

class CEpNode104MbRoot : public CEpNode 
{
public:
	CEpNode104MbRoot(long nType);
	virtual ~CEpNode104MbRoot();

public:
	
public:

public:
	virtual CEpNode* RunJumps(CEpFrameBase *pFrame);
	virtual void RunInitScript(CEpFrameBase *pFrame);
	virtual void RunEndScript(CEpFrameBase *pFrame);
	virtual void RunNodeScript(CEpFrameBase *pFrame);
	
protected:
	virtual void CreateResponseNodes();
	virtual void CreateProcessNodes();
	virtual void CreateJumpsNodes();
	virtual void CreateTimers();

};

#endif // !defined(_EPNODE104MBROOT_H__)
