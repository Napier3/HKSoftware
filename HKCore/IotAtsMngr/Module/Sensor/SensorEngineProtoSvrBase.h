#pragma once

#include "../EngineServer/IotEngineMqttServer.h"
#include "IotSensorSvrEngine.h"
#include "..\..\..\Module\mysqlapp\mysqlbaseapp.h"


class CSensorEngineProtoSvrBase: public CMySqlBaseApp
{
public:
	CSensorEngineProtoSvrBase();
	virtual ~CSensorEngineProtoSvrBase();

	void InitSensorEngineProtoSvrBase();
	void ExitSensorEngineProtoSvrBase();

	//void InitMySql();

/*********************************
第一步：检查文件是否存在，若存在，则返回TRUE，若不存在，执行第二步
第二步：查询装置表，及规约引擎表，下载文件
***********************************/
	BOOL CheckDeviceInfo(const CString &strDeviceID,CString &strDvmFile,CString &strPpxmlFile);

public:
	CIotEngineMqttServer m_oIotEngineMqttServer;
};

extern CSensorEngineProtoSvrBase *g_pSensorEngineProtoSvrBase;

//规约引擎服务模块模型和规约文件管理路径
extern CString g_strDvmFilePath;
extern CString g_strPpxmlFilePath;