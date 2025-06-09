// EpNode104MbAgcResponse.h: interface for the CEpNode104MbAgcResponse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPNODE104MBAGCRESPONSE_H__)
#define _EPNODE104MBAGCRESPONSE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ProtocolBase\EpNode.h"

class CEpNode104MbAgcResponse : public CEpNode 
{
public:
	CEpNode104MbAgcResponse(long nType);
	virtual ~CEpNode104MbAgcResponse();

public:
	CEpNode *m_pMbNode;  //转发ModBus的节点
	
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

#endif // !defined(_EPNODE104MBAGCRESPONSE_H__)
