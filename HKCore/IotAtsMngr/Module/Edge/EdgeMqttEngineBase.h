#pragma once
#include "../EngineServer/MqttEngineBase.h"
#include "EdgeCmd\EdgeCmd.h"

class CEdgeMqttEngineBase:public CMqttEngineBase
{
public:
	CEdgeMqttEngineBase();
	virtual ~CEdgeMqttEngineBase();

public:
	virtual void BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat);
};