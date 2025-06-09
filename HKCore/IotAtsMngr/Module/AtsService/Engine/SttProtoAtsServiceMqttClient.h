#pragma once

#include "../../EngineServer/SttMqttClientBase.h"

/************************************************************************/
/*
自动测试控制服务对应的mqtt客户端
实现：
	接受自动测试控制指令：CreateTest、StartTest、FinishInputData等
	发送自动测试系统状态指令
*/
/*
对应的自动测试服务调用客户端为：CSttSartTestClientMqttClient，目前自动测试客户端为网站端，暂时不开发
*/
/************************************************************************/

class CSttProtoAtsServiceMqttClient:public CSttMqttClientBase
{
public:
	CSttProtoAtsServiceMqttClient(const CString &strMqttTopic);
	CSttProtoAtsServiceMqttClient();
	virtual ~CSttProtoAtsServiceMqttClient();

public:
	//连接成功后，订阅主题
	//virtual BOOL Connect(const char *pszIP,long nPort);
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);

	//主题与报文类型互转接口
	//shaolei 20210805
	virtual CString GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType);
	
public:
	//订阅的主题，CSttProtoAtsServiceMqttClient有两种模式，测试服务模式和测试台模式
	//测试服务模式：TestService只接受创建测试指令，创建测试控制流CAtsSvrTestFlow
	//测试台模式：CAtsTestBench、CAtsSvrTestFlow接受测试控制指令，执行自动测试
	CString m_strAtsMqttTopic;

	CString m_strSN;  //测试台SN或者测试服务端SN，对象创建的时候设置
	//void Init(const CString &strIP,long nPort,const CString &strClientID);
};

/************************************************************************/
/*
自动测试模板服务对应的mqtt客户端
实现：
	接受自动测试模板服务相关的指令：UploadTemplate、ImportTaskInfo、ImportSampleInfo、ExportReport等
*/
/*
对应的自动测试服务调用客户端为：CSttSartTestClientMqttClient，目前自动测试客户端为网站端，暂时不开发
*/
/************************************************************************/

class CSttProtoAtsService_Template_MqttClient:public CSttProtoAtsServiceMqttClient
{
public:
	CSttProtoAtsService_Template_MqttClient(const CString &strMqttTopic);
	CSttProtoAtsService_Template_MqttClient();
	virtual ~CSttProtoAtsService_Template_MqttClient();

public:
	//连接成功后，订阅主题
	//virtual BOOL Connect(const char *pszIP,long nPort);
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);
	virtual CString GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
};