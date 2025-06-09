#ifndef _CMqttPpServerClient_H
#define _CMqttPpServerClient_H

#include "../../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineInterface.h"
#include "../../../../IotAtsMngr/Module/MqttCmmInterface.h"

class CMqttPpServerClient : public CMqttMsgProcessInterface, public CIotPxCommChannelInterface
{
public:
	CMqttPpServerClient();
    virtual ~CMqttPpServerClient();
	
	CSttIotCmd* MqttTopicParser_To_IotCmd(CSttMqttTopicParser &oSttMqttTopicParser);
	void IOT_CreateDevice(CSttMqttTopicParser &oSttMqttTopicParser);
	void IOT_CloseDevice(CSttMqttTopicParser &oSttMqttTopicParser);

//MQTT事件处理接口，共CMqttMsgInterface对象调用
//class CMqttMsgProcessInterface
public:
	//根据收到的MQTT主题进行匹配，如果匹配成功，则返回TRUE，否则返回FALSE
	virtual BOOL MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser);
	//MQTT消息处理
	virtual void MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser);

	//MQTT主题订阅接口函数：MQTT Client连接成功后，遍历各CMqttMsgProcessInterface
	//订阅相关的主题
	virtual BOOL MqttSubscribeTopic();

	//MQTT取消主题订阅接口函数：MQTT Client断开连接后，遍历各CMqttMsgProcessInterface
	//T取消订阅相关的主题
	virtual BOOL MqttUnSubscribeTopic();

//////////////////////////////////////////////////////////////////////////
//CIotPxCommChannelInterface
public:
	virtual long PxSendBuffer(BYTE *pBuf, long nLen) ;
	virtual long PxSendSysState(CSttSysState *pSysState);
	virtual UINT GetClassID()	{	return _PxCommChannelInterface_CLASSID_MQTT_;	}

public:
	virtual BOOL ProcessRecvPacket(BYTE *pBuf,long nLen);
	virtual long OnTestMsg(BYTE *pBuf, long nLen);

	virtual long Process_Cmd_System(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_IOT(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	virtual void OnSocketClose(int nErrorCode, BOOL bDeleteSocket = TRUE);
	CString GetDeviceSN()	{	return m_strDeviceSN;	}

protected:
	CString m_strDeviceSN;   //设备SN
	CString m_strFromSN;  //发送指令的SN
};

#endif // _CMqttPpServerClient_H
