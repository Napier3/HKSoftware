#pragma once
#include "../EngineServer/MqttClientToPxEngine.h"
#include "EdgeCmd/EdgeGlobalDef.h"
#include "EdgeCmd/EdgeCmd.h"
// #include "../../../SttStudio/Module/SttGlobalDef.h"
// #include "../../../SttStudio/Module/SttCmd/SttSysState.h"

//���ڱ��豸ͨ�ŵ�Mqtt�ͻ��˻��࣬���պͷ�������Э������

class CEdgeMqttClientBase:public CMqttClientToPxEngine
{
public:
	CEdgeMqttClientBase();
	virtual ~CEdgeMqttClientBase();

	//ͨ�Žӿ�
public:
	//��������
	virtual BOOL SubcribeMqttTopic(int nQos);
	virtual long Send(CExBaseObject *pCmdBase);
	BOOL Send_Stt(CExBaseObject *pCmdBase);
	//�����뱨�����ͻ�ת�ӿ�
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN,long &nCmdType, char *pszCmdID, char *pszRetType);

public:
	//���������ֶΣ������һ�ֶ�,DeviceID
	CString m_strVersion;

};