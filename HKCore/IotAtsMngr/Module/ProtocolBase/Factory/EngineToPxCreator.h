#pragma once

#include "../../EngineServer/IotEngineToPxBase.h"

//2021-8-19  lijunqing  使用“2:”表示“To”是非常不好的一种表示方式，很容易引起歧义
//因为有些时候我们会使用数字进行标识   PFN_CREATE_ENGINE2PX

//2021-8-19  lijunqing  CIotEngineProtocolServer::CreateProtocol(CSttIotCmd &oIotCmd)函数，属于通用的函数
//不应该有具体的工程烙印，否则就不是工厂模式  x_Sensor_EngineProtoSvr_x
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
