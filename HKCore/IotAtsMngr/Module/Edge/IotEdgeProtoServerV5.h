#pragma once

#include "IotEdgeProtoServerBase.h"

class CIotEdgeProtoServerV5:public CIotEdgeProtoServerBase
{
public:
	CIotEdgeProtoServerV5();
	virtual ~CIotEdgeProtoServerV5();

public:
	virtual BOOL Init(const char *pszIP,long nPort);
//	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);
};