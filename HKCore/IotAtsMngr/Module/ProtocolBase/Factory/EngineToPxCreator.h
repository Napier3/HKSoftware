#pragma once

#include "../../EngineServer/IotEngineToPxBase.h"

//2021-8-19  lijunqing  ʹ�á�2:����ʾ��To���Ƿǳ����õ�һ�ֱ�ʾ��ʽ����������������
//��Ϊ��Щʱ�����ǻ�ʹ�����ֽ��б�ʶ   PFN_CREATE_ENGINE2PX

//2021-8-19  lijunqing  CIotEngineProtocolServer::CreateProtocol(CSttIotCmd &oIotCmd)����������ͨ�õĺ���
//��Ӧ���о���Ĺ�����ӡ������Ͳ��ǹ���ģʽ  x_Sensor_EngineProtoSvr_x
//CIotEngineProtocolServer
typedef CIotEngineToPxBase* (PFN_CREATE_ENGINE_TO_PX)(CMqttEngineBase_Stt *pIotEngineProtocolServer, CSttCmdBase *pCmd);

class CEngineToPxCreator : public CExBaseObject
{
public:
	CEngineToPxCreator(const CString &strPxProtoID, PFN_CREATE_ENGINE_TO_PX* pFunCreate);
	virtual ~CEngineToPxCreator(void);

	CIotEngineToPxBase* Create(CMqttEngineBase_Stt *pIotEngineProtocolServer, CSttCmdBase *pCmd);

private:
	PFN_CREATE_ENGINE_TO_PX* m_pFunCreate;

private:
	CEngineToPxCreator(void ) {	}
};
