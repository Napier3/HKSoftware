#pragma once
#include "../EngineServer/MqttClientToPxEngine.h"
#include "EdgeCmd/EdgeGlobalDef.h"
#include "EdgeCmd/EdgeCmd.h"
// #include "../../../SttStudio/Module/SttGlobalDef.h"
// #include "../../../SttStudio/Module/SttCmd/SttSysState.h"

//用于边设备通信的Mqtt客户端基类，接收和发送物联协议命令

class CEdgeMqttClientBase:public CMqttClientToPxEngine
{
public:
	CEdgeMqttClientBase();
	virtual ~CEdgeMqttClientBase();

	//通信接口
public:
	//订阅主题
	virtual BOOL SubcribeMqttTopic(int nQos);
	virtual long Send(CExBaseObject *pCmdBase);
	BOOL Send_Stt(CExBaseObject *pCmdBase);
	//主题与报文类型互转接口
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN,long &nCmdType, char *pszCmdID, char *pszRetType);

public:
	//特殊主题字段：主题第一字段,DeviceID
	CString m_strVersion;

};