#include "stdafx.h"
#include "IotEdgeProtoServerV5.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../Module/System/StringTokenizer.h"
#include "IotEdgeProtoServer_MqttClientV5.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEdgeProtoServerV5::CIotEdgeProtoServerV5()
{

}

CIotEdgeProtoServerV5::~CIotEdgeProtoServerV5()
{
	//yzj 2021-10-25 closedeviceʱӦ�ý������д�����mqtt client����
	if(m_pPxCmmOptrInterface != NULL)
	{
		m_pPxCmmOptrInterface->Disconnect();
	}
}

BOOL CIotEdgeProtoServerV5::Init(const char *pszIP,long nPort)
{
	FreePxCmmInterface();

	CIotEdgeProtoServer_MqttClientV5 *pProtocolMqttClient = new CIotEdgeProtoServer_MqttClientV5();
	pProtocolMqttClient->m_strDeviceSN = m_strDeviceID;//���ڶ�������
	BOOL bRet = pProtocolMqttClient->Connect(pszIP,nPort, "EdgeProtoServerV5");

	if (bRet)
	{
		pProtocolMqttClient->SetMqttEngineRef(this);
		AttachPxCmmInterface(pProtocolMqttClient);

		//���ӷ������ɹ��󣬴�������ִ���߳�
		StartEngineThread();
	}
	else
	{
		delete pProtocolMqttClient;
	}

	return bRet;
}