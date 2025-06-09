// EpProcedure.cpp: implementation of the CEpProcedure class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpProcedure.h"
#include "..\EpEngineThread.h"
#include "EpProduceFrame.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpProcedure::CEpProcedure()
{

}

CEpProcedure::~CEpProcedure()
{

}


void CEpProcedure::RunNode()
{
	ASSERT (m_pCurrNode != NULL);

	if (m_pCurrNode == NULL)
	{
		m_bProcedureExit = TRUE;
		return;
	}

	if (m_pCurrNode->IsEndNode())
	{
		m_bProcedureExit = TRUE;
	}
	else
	{
		DWORD dwClassID = m_pCurrNode->GetNodeFrameID();
		CEpFrameBase *pFrame =  Ep_FindFrameByID(dwClassID, this);

		if (pFrame == NULL)
		{//空节点
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("节点\"%s\"关联的制造帧\"%08x\"不存在"), m_pCurrNode->m_strID, dwClassID);
		}
		else
		{//发送节点
			//是否为制造帧判断
// 			if (pFrame->GetClassID() != PPCLASSID_PPPODUCEPACKGE)
// 			{
// 				CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("节点\"%s\"关联的\"%s\"不是制造帧"), m_pCurrNode->m_strID, strFrameID);
// 			}
// 			else
// 			{
// 				RunWFrame(pFrame);
// 			}
			RunWFrame(pFrame);
		}

		//启动定时时钟
		m_pCurrNode->BeginTimer();
	}
}


void CEpProcedure::ProcessNode()
{

	CEpNode* pNodeToRun = NULL;

	pNodeToRun = ProcessNodeProcess();

	if (pNodeToRun == NULL)
	{
		pNodeToRun = ProcessNodeJumps();
	}

	if (pNodeToRun == NULL)
	{
		pNodeToRun = ProcessNodeTimers();
	}

	if (pNodeToRun != NULL)
	{
		m_pCurrNode->KillTimer();
		//m_pCurrNode = pNodeToRun;
		SetCurrNode(pNodeToRun);
		RunNode();
	}
}


CEpNode* CEpProcedure::ProcessNodeProcess()
{
	ASSERT (m_pListReceiveFrame != NULL);
	ASSERT (m_pEngineThread != NULL);

	POS posPkg = NULL;
	POS posPkgPrev = NULL;
	CEpNodes *pNodes = m_pCurrNode->m_pResponseNodes;
	POS posNode = pNodes->GetHeadPosition();
	CEpNode *pNode = NULL;
	CEpEngineThread *pEngineThread = (CEpEngineThread*)m_pEngineThread;
	CEpFrameBase *pPkgDetail = NULL;
	CEpNode *pNodeToRun = NULL;
	CExBaseList oList;

	//进入帧解析链表互斥区，遍历帧解析链表,为了提高速度，从链表中复制数据出来
	//CAutoSimpleLock oLock(&pEngineThread->m_oRcvPkgCriticSection);
	oList.RemoveAll();
	oList.Append(*m_pListReceiveFrame);
	//oLock.Free();

	//遍历响应节点
	while (posNode != NULL)
	{
		pNode = (CEpNode*)pNodes->GetNext(posNode);

		// 		//进入帧解析链表互斥区，遍历帧解析链表,为了提高速度，从链表中复制数据出来
		// 		CAutoSimpleLock oLock(&pEngineThread->m_oRcvPkgCriticSection);
		// 		oList.RemoveAll();
		// 		oList.Append(*m_pListReceiveFrame);
		// 		oLock.Free();

		posPkg = oList.GetHeadPosition();

		while (posPkg != NULL)
		{
			posPkgPrev = posPkg;
			pPkgDetail = (CEpFrameBase*)oList.GetNext(posPkg);

			if (pPkgDetail->m_bUsed)
			{
				continue;
			}

			if (pNode->IsFrameResponse(pPkgDetail))
			{//Frame为Node的响应
				pNode->ResetTimer();
				pPkgDetail->m_bUsed = TRUE;
				pNodeToRun = pNode->RunJumps(pPkgDetail);
			}
		}

		if (pNodeToRun != NULL)
		{
			break;
		}
	}//end of "遍历响应节点"

	oList.RemoveAll();

	return pNodeToRun;
}

CEpNode* CEpProcedure::ProcessNodeJumps()
{
	CEpNode *pNodeToRun = NULL;

	//暂时不考虑发送节点的跳转情况
	CEpFrameBase *pSend = (CEpFrameBase*)m_pCurrNode->GetFrameSend();

	if (pSend == NULL)
	{
		return NULL;
	}

	CEpFrameBase *pDetail = pSend;

	if (pDetail == NULL)
	{
		return NULL;
	}

	pNodeToRun = m_pCurrNode->RunJumps(pDetail);

	return pNodeToRun;
}

CEpNode* CEpProcedure::ProcessNodeTimers()
{
	CEpNode *pNodeToRun = NULL;

	if (m_pCurrNode->m_pTimers != NULL)
	{
		DWORD dwTickCount = ::GetTickCount();
		pNodeToRun = m_pCurrNode->RunTimers(dwTickCount);
	}

	return pNodeToRun;
}

void CEpProcedure::RunWFrame(CEpFrameBase *pFrame)
{
	CEpEngineThread *pEngineThread = (CEpEngineThread*)m_pEngineThread;
	CEpProduceFrame *pRoducePkg = (CEpProduceFrame*)pFrame;//->Clone();
	CEpProcedure *pProcedure = (CEpProcedure*)m_pCurrNode->GetAncestor(EPCLASSID_PROCEDURE);
	ASSERT (pProcedure != NULL);

	//执行节点的初始化脚本
	m_pCurrNode->RunInitScript(pRoducePkg);

	//调用制造帧制造规约报文
	CEpFrameBase *pPkgSend = pEngineThread->AddFrameSend(this);
	pPkgSend->m_pEngineThread = pEngineThread;
	CEpCmmChannel *pChannel = (CEpCmmChannel*)pPkgSend->m_pChannel;

	if (pRoducePkg != NULL)
	{
		pRoducePkg->m_nPkgNum = pChannel->GetSendIndex();
	}

	EPBUFFERPOS oPkgBufPos;
	pPkgSend->GetFrameBufferPos(&oPkgBufPos);
	pRoducePkg->Produce(&oPkgBufPos);

	//为节点关联发送帧
	m_pCurrNode->SetFrameSend(pPkgSend);

	//发送规约报文
	pPkgSend->Send();

	//执行节点的结束脚本
	m_pCurrNode->RunEndScript(pRoducePkg);
}

void CEpProcedure::CopyDataInterfaceToFrame()
{
	
}