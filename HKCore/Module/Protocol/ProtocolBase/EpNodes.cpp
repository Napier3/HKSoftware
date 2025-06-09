// EpNodes.cpp: implementation of the CEpNodes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpNodes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpNodes::CEpNodes()
{

}

CEpNodes::~CEpNodes()
{

}

CEpNode* CEpNodes::AddNode(DWORD dwFrameID, DWORD dwNodeType)
{
	CEpNode *pNode = new CEpNode();
	pNode->m_dwFrameID = dwFrameID;
	pNode->m_nTypeID = dwNodeType;
	AddNewChild(pNode);
	return pNode;
}

CEpNode* CEpNodes::AddNode(DWORD dwFrameID, const CString &strChannelID, DWORD dwNodeType)
{
	CEpNode *pNode = new CEpNode();
	pNode->m_dwFrameID = dwFrameID;
	pNode->m_nTypeID = dwNodeType;
	AddNewChild(pNode);
	return pNode;
}

CEpNode* CEpNodes::AddNode(CEpNode *pNode)
{
	AddNewChild(pNode);
	return pNode;
}

