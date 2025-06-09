//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrService.h  CAtsSvrService

#pragma once

#include "AtsSvrService.h"

#include "..\SttMqttClientTool.h"
#include "../../../Module/MySqlApp/MySqlBaseApp.h"
#include "../Iot_AtsMngrDB/Iot_Bench.h"

class CAtsSvrServiceApplication : public CExBaseList, public CMySqlBaseApp
{
private:
	CAtsSvrServiceApplication();
	virtual ~CAtsSvrServiceApplication();

	static long g_nAtsSvrServiceApplicationRef;
	static CAtsSvrServiceApplication *g_pAtsSvrServiceApplication;

public:
	static CAtsSvrServiceApplication* Create();
	static void Release();
	static CAtsSvrServiceApplication* GetApplication();

	static CAtsSvrService* GetAtsSvrService();
	static CAtsSvrService* GetAtsSvrService(const CString &strSN);
	static CAtsSvrService* GetAtsSvrService(long nIndex);
	static CXSttSmartTestXInterface* FindSmartTestXInterface(const CString &strDeviceSN);

public:
	CIot_Benchs* m_pIotBenchs;
	BOOL SyncBenchs();   //�����󣬴����ݿ�ͬ������̨��Ϣ
	BOOL InitMySqlDB();
	void InitAtsSvrService();
	void InitAtsSvrService(const CString &strFile);
	void SaveAtsSvrService();

	CXSttSmartTestXInterface* In_FindSmartTestXInterface(const CString &strDeviceSN);
};

