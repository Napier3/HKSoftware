// EpNode104MbRoot.cpp: implementation of the CEpNode104MbRoot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpNode104MbRoot.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpNode104MbRoot::CEpNode104MbRoot(long nType)
{
	
}

CEpNode104MbRoot::~CEpNode104MbRoot()
{

}


void CEpNode104MbRoot::CreateResponseNodes()
{
	m_pResponseNodes = new CEpNodes();
	AddNewChild(m_pResponseNodes);
	CEpNode *pNode = NULL;
	
	//ĿǰAGC�����ںη�ʽ
	pNode = m_pResponseNodes->AddNode(EPCLASSID_101_FRAME_68_ASDU01, EPNODE_TYPE_RESPONSE);
	
}

void CEpNode104MbRoot::CreateProcessNodes()
{

}

void CEpNode104MbRoot::CreateJumpsNodes()
{

}

void CEpNode104MbRoot::CreateTimers()
{

}

CEpNode104MbRoot* CEpNode104MbRoot::RunJumps(CEpFrameBase *pPkgDetail)
{
// 	//ִ�г�ʼ���ű�
// 	RunInitScript(pPkgDetail);
// 
// 	if (m_pJumps == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CEpNode104MbRoot *pNode = m_pJumps->RunJumps(pPkgDetail);
// 
// 	//ִ�н����ű�
// 	RunEndScript(pPkgDetail);

	return NULL;
}

void CEpNode104MbRoot::RunInitScript(CEpFrameBase *pFrame)
{

}

void CEpNode104MbRoot::RunEndScript(CEpFrameBase *pFrame)
{

}

void CEpNode104MbRoot::RunNodeScript(CEpFrameBase *pFrame)
{

}

