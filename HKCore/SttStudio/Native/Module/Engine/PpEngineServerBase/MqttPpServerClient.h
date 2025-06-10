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

//MQTT�¼�����ӿڣ���CMqttMsgInterface�������
//class CMqttMsgProcessInterface
public:
	//�����յ���MQTT�������ƥ�䣬���ƥ��ɹ����򷵻�TRUE�����򷵻�FALSE
	virtual BOOL MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser);
	//MQTT��Ϣ����
	virtual void MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser);

	//MQTT���ⶩ�Ľӿں�����MQTT Client���ӳɹ��󣬱�����CMqttMsgProcessInterface
	//������ص�����
	virtual BOOL MqttSubscribeTopic();

	//MQTTȡ�����ⶩ�Ľӿں�����MQTT Client�Ͽ����Ӻ󣬱�����CMqttMsgProcessInterface
	//Tȡ��������ص�����
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
	CString m_strDeviceSN;   //�豸SN
	CString m_strFromSN;  //����ָ���SN
};

#endif // _CMqttPpServerClient_H
