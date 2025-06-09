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
��һ��������ļ��Ƿ���ڣ������ڣ��򷵻�TRUE���������ڣ�ִ�еڶ���
�ڶ�������ѯװ�ñ�����Լ����������ļ�
***********************************/
	BOOL CheckDeviceInfo(const CString &strDeviceID,CString &strDvmFile,CString &strPpxmlFile);

public:
	CIotEngineMqttServer m_oIotEngineMqttServer;
};

extern CSensorEngineProtoSvrBase *g_pSensorEngineProtoSvrBase;

//��Լ�������ģ��ģ�ͺ͹�Լ�ļ�����·��
extern CString g_strDvmFilePath;
extern CString g_strPpxmlFilePath;