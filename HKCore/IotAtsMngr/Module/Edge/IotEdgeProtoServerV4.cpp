#include "stdafx.h"
#include "IotEdgeProtoServerV4.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../Module/System/StringTokenizer.h"
#include "IotEdgeProtoServer_MqttClientV4.h"
#include "MqttEdgePkgBase.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEdgeProtoServerV4::CIotEdgeProtoServerV4()
{

}

CIotEdgeProtoServerV4::~CIotEdgeProtoServerV4()
{
	
}

BOOL CIotEdgeProtoServerV4::Init(const char *pszIP,long nPort)
{
	FreePxCmmInterface();

	CIotEdgeProtoServer_MqttClientV4 *pProtocolMqttClient = new CIotEdgeProtoServer_MqttClientV4();
	
	//2021-9-9 yzj
	//��ΪPxProtocolBase���̳���ExbaseList,Init��ע�͵��ĵ�һ��strID��������strIDΪ��
	//��ʱ����m_pDvmDevice
	pProtocolMqttClient->m_strDeviceSN = m_strDeviceID;//���ڶ�������
	BOOL bRet = pProtocolMqttClient->Connect(pszIP,nPort, "EdgeProtoServerV4");

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
