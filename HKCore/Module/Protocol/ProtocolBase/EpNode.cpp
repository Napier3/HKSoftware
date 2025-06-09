// EpNode.cpp: implementation of the CEpNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpNode.h"
#include "EpNodes.h"
#include "EpTimers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpNode::CEpNode(EPNODETYPE nType, const CString &strChannelID)
{
	m_pResponseNodes = NULL;
	m_pProcessNodes = NULL;
	m_pTimers = NULL;
	m_dwFrameID = 0;
	m_nTypeID = nType;
	m_pFrameSend = NULL;

	CreateResponseNodes();
	CreateProcessNodes();
	CreateJumpsNodes();
	CreateTimers();
}

CEpNode::~CEpNode()
{

}

void CEpNode::CreateResponseNodes()
{

}

void CEpNode::CreateProcessNodes()
{

}

void CEpNode::CreateJumpsNodes()
{

}

void CEpNode::CreateTimers()
{

}

//设置当前节点的发送帧
void CEpNode::SetFrameSend(CExBaseObject *pPkgSend)
{
	CEpFrameBase *pCurr = (CEpFrameBase*)m_pFrameSend;

	if (pCurr != NULL)
	{
		pCurr->Lock(FALSE);
	}

	m_pFrameSend = (CEpFrameBase*)pPkgSend;

	if (m_pFrameSend != NULL)
	{
		pCurr = (CEpFrameBase*)m_pFrameSend;
		pCurr->Lock();
	}
}


BOOL CEpNode::IsFrameResponse(CEpFrameBase *pPkgDetail)
{
	return (m_dwFrameID == pPkgDetail->GetClassID());
}


BOOL CEpNode::IsFrameResponses(CEpFrameBase *pPkgDetail)
{
	if (m_pResponseNodes == NULL)
	{
		return FALSE;
	}

	POS pos = m_pResponseNodes->GetHeadPosition();
	CEpNode *pNode = NULL;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pNode = (CEpNode*)m_pResponseNodes->GetNext(pos);

		if (pNode->IsFrameResponse(pPkgDetail))
		{
			bTrue = TRUE;
			break;
		}
	}

	return bTrue;
}

void CEpNode::BeginTimer()
{
	if (m_pTimers != NULL)
	{
		m_pTimers->BeginTimer();
	}
}
void CEpNode::ResetTimer()
{
	if (m_pTimers != NULL)
	{
		m_pTimers->ResetTimer();
	}
}

void CEpNode::KillTimer()
{
	if (m_pTimers != NULL)
	{
		m_pTimers->KillTimer();
	}
}

CEpNode* CEpNode::RunJumps(CEpFrameBase *pPkgDetail)
{
// 	//执行初始化脚本
// 	RunInitScript(pPkgDetail);
// 
// 	if (m_pJumps == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CEpNode *pNode = m_pJumps->RunJumps(pPkgDetail);
// 
// 	//执行结束脚本
// 	RunEndScript(pPkgDetail);

	return NULL;
}

void CEpNode::RunInitScript(CEpFrameBase *pFrame)
{

}

void CEpNode::RunEndScript(CEpFrameBase *pFrame)
{

}

void CEpNode::RunNodeScript(CEpFrameBase *pFrame)
{

}

void CEpNode::SetCmmChannelID(const CString &strChannelID)
{
	m_strChannelID = strChannelID;
	m_pEpCmmChannel = Ep_FindCmmChannel(this, m_strChannelID);
}

 void CEpNode::RunNode(CEpFrameBase *pFrame, CExBaseObject *pChannel)
 {
//	 CEpProduceFrame *pRoducePkg = (CEpProduceFrame*)pFrame;
	 CEpProcedure *pProcedure = (CEpProcedure*)GetAncestor(EPCLASSID_PROCEDURE);
	 ASSERT (pProcedure != NULL);

	 //执行节点的初始化脚本
	 RunInitScript(pFrame);

	 if (m_pEpCmmChannel == NULL)
	 {
		 m_pEpCmmChannel = Ep_FindCmmChannel(this, m_strChannelID);
	 }

	 if (m_pEpCmmChannel == NULL)
	 {
		 CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("Node:%s channel[%s] not exist"), m_strID, m_strChannelID);
		 return;
	 }

	 pFrame->m_nPkgNum = m_pEpCmmChannel->GetSendIndex();

	 EPBUFFERPOS oPkgBufPos;
	 pFrame->GetFrameBufferPos(&oPkgBufPos);
	 pFrame->Produce(&oPkgBufPos);
	 pFrame->SetChannel(m_pEpCmmChannel);

	 //为节点关联发送帧
	 SetFrameSend(pFrame);

	 //发送规约报文
	 pFrame->Send();

	 //执行节点的结束脚本
	 RunEndScript(pFrame);
 }


CEpNode*  CEpNode::RunTimers(DWORD dwTickCount)
{
	return m_pTimers->RunTimer(dwTickCount);
}

BOOL CEpNode::IsEndNode()
{
	return (g_pPpEndNode == this);
}

