#pragma once

#include "MqttEdgePrcdrBase.h"
//#include "MqttEdgePkgBase.h"

/******************
参数读取过程状态机：
创建过程，初始化状态为：PrcdrState_Step_NULL，
发送读命令后，启动定时器，状态为PrcdrState_Step_1
等待超时或收到应答结果，关闭定时器，状态为PrcdrState_Step_End
******************/ 

class CMqttEdgePrcdrRead : public CMqttEdgePrcdrBase
{
public:
	CMqttEdgePrcdrRead();
	virtual ~CMqttEdgePrcdrRead();

public:
	//循环执行，判断超时或发送报文，过程结束返回TRUE
	virtual BOOL Run();

public:
	virtual BOOL RunStepNull();
	virtual BOOL RunStep1();

	//处理应答报文逻辑
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);

public:
	//以下json通用生成
	BOOL RunProcedure_Query(CString& strProcedureID);
	//以下业务
	BOOL OnRunProcedure_Service(CString& strProcedureID);
	//以下设备
	BOOL OnRunProcedure_Device(CString& strProcedureID);
	//以下容器
	BOOL OnRunProcedure_Container(CString& strProcedureID);
	//以下应用
	BOOL OnRunProcedure_App(CString& strProcedureID);
};