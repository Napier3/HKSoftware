#include "stdafx.h"
#include "IotPxEngineServerApp.h"

#include "IotPxEngineServer.h"
#include "../../../IotProtoServer/Module/SttPpEngineFactory.h"
#include "../../../SttStudio/Module/Engine/PpEngineServerBase/SttPpEngineServer.h"

//��ͳЭ��
#include "../../../Protocol/Module/PxiEngine/PxiEngine.h"

//MMSЭ��
#ifdef IOT_PROTOCOL_SERVER_HAS_MMS
#include "../../../IotProtoServer/Module/SttMmsEngineFactory.h"
#include "../../../61850/Module/PoEngine/PoMmsEngine.h"
#endif

//MMSЭ��
#ifdef IOT_PROTOCOL_SERVER_HAS_CMS
#include "../../../IotProtoServer/Module/SttCmsEngineFactory.h"
#include "../../../61850/Module/PoCmsEngine/PoCmsEngine.h"
#endif

#ifdef IOT_PROTOCOL_SERVER_HAS_MMS
#include "../../../61850/Module/XLanguageResourcePp_Mms.h"
#endif
#include"../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../Protocol/Module/XLanguageResourcePp_PpEngine.h"

#ifdef IOT_PROTOCOL_SERVER_USE_MQTT
#include "../../../SttStudio/Module/Engine/PpEngineServerBase/PpSvrInterfaceMqttClient.h"
#endif

CIotPxEngineServerApp::CIotPxEngineServerApp()
{

}

CIotPxEngineServerApp::~CIotPxEngineServerApp()
{

}

void CIotPxEngineServerApp::InitIotPxEngineServerApp()
{
	CMacroXmlKeys::Create();

	//PpEngine
	CPxiEngine::Create();

#ifdef IOT_PROTOCOL_SERVER_HAS_MMS
    CPoMmsEngine::Create();
//#else
	//MmsEngine
	CMmsEngineAppBase::Create();
#endif

#ifdef IOT_PROTOCOL_SERVER_HAS_CMS
    CPoCmsEngine::Create();
#endif

 	//��������еĹ������
   CIotPxEngineServer::Create(); 

	//STTЭ����������������MQTTЭ�飬���������CMqttPpEngineServer
    CSttPpEngineServer *pSttPpEngineServer = CSttPpEngineServer::Create(); 
//	CIotPxEngineServer::m_pServerSocketRef = pSttPpEngineServer->GetServerSocketDataBase();

	//����Э������Ĺ���ע��
    CSttPpEngineFactory *pSttPpEngineFactory = new CSttPpEngineFactory();
    CIotPxEngineServer::RegisterFactory(pSttPpEngineFactory);

#ifdef IOT_PROTOCOL_SERVER_HAS_MMS
    CSttMmsEngineFactory *pSttMmsEngineFactory = new CSttMmsEngineFactory();
    CIotPxEngineServer::RegisterFactory(pSttMmsEngineFactory);
#endif

#ifdef IOT_PROTOCOL_SERVER_HAS_CMS
    CSttCmsEngineFactory *pSttCmsEngineFactory = new CSttCmsEngineFactory();
    CIotPxEngineServer::RegisterFactory(pSttCmsEngineFactory);
#endif

    CXLanguageXmlRWKeys::Create();
#ifdef IOT_PROTOCOL_SERVER_HAS_MMS
    CXLanguageMngr::Create(new CXLanguageResourcePp_Mms(), TRUE );
    CXLanguageMngr::xlang_AddXLanguageRerouce(new CXLanguageResourcePp_PpEngine, TRUE);
#endif

#ifdef IOT_PROTOCOL_SERVER_USE_MQTT
	CPpSvrInterfaceMqttClient::Create();
#endif
}

void CIotPxEngineServerApp::ExitIotPxEngineServerApp()
{
	CIotPxEngineServer::Release();
	CSttPpEngineServer::Release();

	//PpEngine
	CPxiEngine::Release();

#ifdef IOT_PROTOCOL_SERVER_HAS_MMS
    CPoMmsEngine::Release();
//#else
	//MmsEngine
	CMmsEngineAppBase::Release();
#endif

#ifdef IOT_PROTOCOL_SERVER_HAS_CMS
	CPoCmsEngine::Release();
#endif

	CMacroXmlKeys::Release();

    CXLanguageXmlRWKeys::Release();
    CXLanguageMngr::Release();

#ifdef IOT_PROTOCOL_SERVER_USE_MQTT
	CPpSvrInterfaceMqttClient::Release();
#endif
}

