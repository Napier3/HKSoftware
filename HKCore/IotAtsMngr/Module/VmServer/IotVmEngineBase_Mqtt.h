#pragma once
#include "../EngineServer/SttMqttEngineBase.h"
#include "../../../SttStudio/Module/SttCmd/SttTestCmd.h"

class CIotVmEngineBase_Mqtt : public CSttMqttEngineBase
{
public:
	CIotVmEngineBase_Mqtt();
	virtual ~CIotVmEngineBase_Mqtt();

public:
	virtual void BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat);
};