// MmsDataNode.cpp : 实现文件
//

#include "stdafx.h"
#include "MmsDataNode.h"

CDataNode::CDataNode()
{

}

CDataNode::~CDataNode()
{

}

BOOL CDataNode::Empty()
{
	return (m_nCount == 0);
}

CDataNode* CDataNode::Child(const CString &strID)
{
	CDataNode *pFind = (CDataNode*)FindByID(strID);

	return pFind;
}

CDataNode* CDataNode::AppendChild(const CString &strID, UINT nType)
{
	CDataNode *pNew  =new CDataNode();
	AddNewChild(pNew);
	pNew->m_strID  =strID;
	pNew->m_type = nType;

	return pNew;
}