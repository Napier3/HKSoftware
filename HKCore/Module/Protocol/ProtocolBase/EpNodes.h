// EpNodes.h: interface for the CEpNodes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPNODES_H__)
#define _EPNODES_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpNode.h"


class CEpNodes : public CExBaseList  
{
public:
	CEpNodes();
	virtual ~CEpNodes();

public:
	//基本方法
	virtual void Init() {}
	virtual UINT GetClassID()		{ return EPCLASSID_NODES; }

	//编辑
	virtual long IsEqual(CExBaseObject* pObj)	{ return 0;}
	virtual long Copy(CExBaseObject* pDesObj)	{ return 0;}
	virtual CExBaseObject* Clone()				{ return NULL;}

public:
	virtual CEpNode* AddNode(DWORD dwFrameID, DWORD dwNodeType=EPNODE_TYPE_EMPTY);
	virtual CEpNode* AddNode(DWORD dwFrameID, const CString &strChannelID, DWORD dwNodeType=EPNODE_TYPE_EMPTY);
	virtual CEpNode* AddNode(CEpNode *pNode);
};

#endif // !defined(_EPNODES_H__)
