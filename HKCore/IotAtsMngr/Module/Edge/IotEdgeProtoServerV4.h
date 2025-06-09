#pragma once

#include "IotEdgeProtoServerBase.h"

class CIotEdgeProtoServerV4:public CIotEdgeProtoServerBase
{
public:
	CIotEdgeProtoServerV4();
	virtual ~CIotEdgeProtoServerV4();

public:
	virtual BOOL Init(const char *pszIP,long nPort);
//	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);
};