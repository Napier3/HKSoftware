//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttAtsSvrMqttImpBase.h  CSttAtsSvrMqttImpBase

#pragma once

#include "../../../../SttStudio/Module/SttCmd/SttAtsCmd.h"
#include "SttProtoAtsServiceMqttClient.h"
#include "../../EngineServer/SttMqttEngineBase.h"

class CAtsSvrMsgWnd;

/*
2021-7-21  lijunqing
Ϊ�˸Ͻ��ȣ���ʱ�ͽ����ܼ��ɵ�CSttAtsSvrMqttImpBase�У�CSttAtsSvrMqttImpBase��CSttMqttEngineBase����
��������ͨ�ã���������صĽӿڣ����Զ����Է���Ĺ��ܴ�CSttAtsSvrMqttImpBase�����ȥ������STT�ĵ���
���Կ��ǲ��ù���ģʽע��ʹ�����صĴ������
*/

class CSttAtsSvrMqttImpBase : public CSttMqttEngineBase
{
public:
	CSttAtsSvrMqttImpBase();
	virtual ~CSttAtsSvrMqttImpBase();


//˽�г�Ա����
private:

protected:
	CSttProtoAtsServiceMqttClient *m_pMqttClient;
	CAtsSvrMsgWnd *m_pServiceWnd;

//˽�г�Ա�������ʷ���
public:
	BOOL CreateAtsServiceMqttClient(const CString &strMqttTopic);

public:
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN, char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);

};

