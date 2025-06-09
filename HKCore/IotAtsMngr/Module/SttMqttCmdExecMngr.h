#pragma once

#include "SttMqttCmdExec.h"
#include "AtsMngrDB/Ats_HisTask.h"
#include "SttMqttClientTool.h"
#include "SensorPpCfg/SensorPpConfig.h"


class CSttMqttCmdExecMngr : public CExBaseList
{//子对象为CSttMqttCmdExec
public:
	CSttMqttCmdExecMngr();
	virtual ~CSttMqttCmdExecMngr();

public:
	CSttMqttCmdExec *FindDevice(__int64 nSensorID,CPpPrjDevice **ppPrjDevice);
};

