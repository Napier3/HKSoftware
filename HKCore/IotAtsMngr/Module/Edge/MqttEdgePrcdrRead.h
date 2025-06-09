#pragma once

#include "MqttEdgePrcdrBase.h"
//#include "MqttEdgePkgBase.h"

/******************
������ȡ����״̬����
�������̣���ʼ��״̬Ϊ��PrcdrState_Step_NULL��
���Ͷ������������ʱ����״̬ΪPrcdrState_Step_1
�ȴ���ʱ���յ�Ӧ�������رն�ʱ����״̬ΪPrcdrState_Step_End
******************/ 

class CMqttEdgePrcdrRead : public CMqttEdgePrcdrBase
{
public:
	CMqttEdgePrcdrRead();
	virtual ~CMqttEdgePrcdrRead();

public:
	//ѭ��ִ�У��жϳ�ʱ���ͱ��ģ����̽�������TRUE
	virtual BOOL Run();

public:
	virtual BOOL RunStepNull();
	virtual BOOL RunStep1();

	//����Ӧ�����߼�
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);

public:
	//����jsonͨ������
	BOOL RunProcedure_Query(CString& strProcedureID);
	//����ҵ��
	BOOL OnRunProcedure_Service(CString& strProcedureID);
	//�����豸
	BOOL OnRunProcedure_Device(CString& strProcedureID);
	//��������
	BOOL OnRunProcedure_Container(CString& strProcedureID);
	//����Ӧ��
	BOOL OnRunProcedure_App(CString& strProcedureID);
};