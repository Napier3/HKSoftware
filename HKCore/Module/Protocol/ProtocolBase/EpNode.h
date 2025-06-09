// EpNode.h: interface for the CEpNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPNODE_H__)
#define _EPNODE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpFrameBase.h"

class CEpNodes;
class CEpTimers;

//////////////////////////////////////////////////////////////////////////
//
typedef enum eEpNodeType
{
	EPNODE_TYPE_EMPTY   =    0,
	EPNODE_TYPE_PRODUCE =   1,
	EPNODE_TYPE_RESPONSE =  2,
	EPNODE_TYPE_PROCESS   =  3
}EPNODETYPE;


class CEpNode : public CExBaseObject  
{
public:
	CEpNode(EPNODETYPE nType=EPNODE_TYPE_EMPTY, const CString &strChannelID=_T(""));
	virtual ~CEpNode();

public:
	CEpNodes* m_pResponseNodes;
	CEpNodes* m_pProcessNodes;
	CEpTimers* m_pTimers;
	DWORD m_dwFrameID;
	CEpFrameBase *m_pFrameSend;
	DWORD m_nTypeID;
	CString m_strChannelID; //节点使用的通讯通道
	CEpCmmChannel *m_pEpCmmChannel;

private:

public:
	//基本方法
	virtual void Init()	{}
	virtual UINT GetClassID()		{ return EPCLASSID_PROCEDURE; }
	CString GetChannelID()	{	return m_strChannelID;	}

	//编辑
	virtual long IsEqual(CExBaseObject* pObj) {	return 0;}
	virtual long Copy(CExBaseObject* pDesObj) {	return 0;}
	virtual CExBaseObject* Clone()			  {	return NULL;  }

	DWORD GetNodeFrameID()	{		return m_dwFrameID;		}
	void SetCmmChannelID(const CString &strChannelID);

public:
	void SetFrameSend(CExBaseObject *pPkgSend);
	CExBaseObject* GetFrameSend()		{	return m_pFrameSend;		};

	BOOL IsFrameResponse(CEpFrameBase *pFrame);
	BOOL IsFrameResponses(CEpFrameBase *pFrame);
	void BeginTimer();
	void ResetTimer();
	void KillTimer();
	BOOL IsEndNode();
	CEpNode* RunTimers(DWORD dwTickCount);

	virtual CEpNode* RunJumps(CEpFrameBase *pFrame);
	virtual void RunInitScript(CEpFrameBase *pFrame);
	virtual void RunEndScript(CEpFrameBase *pFrame);
	virtual void RunNodeScript(CEpFrameBase *pFrame);

	virtual void RunNode(CEpFrameBase *pFrame, CExBaseObject *pChannel=NULL);

protected:
	virtual void CreateResponseNodes();
	virtual void CreateProcessNodes();
	virtual void CreateJumpsNodes();
	virtual void CreateTimers();
};

extern CEpNode *g_pPpEndNode;
static const CString g_strProcedureEndNodeID = _T("END");


#endif // !defined(_EPNODE_H__)
