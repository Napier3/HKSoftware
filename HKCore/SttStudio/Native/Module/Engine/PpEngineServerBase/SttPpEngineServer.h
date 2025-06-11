#pragma once

#include "../SttTestEngineServerBase.h"
#include "../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineFactoryBase.h"
/*
STTЭ���ͨ�����������࣬�˻����ʼ��ʱ������CSttPpServerSocket
��������ʱ������CSttPpServerClientSocket��ʵ��IOT���Ի��Ĵ���

����ڲ����ǵ�Engine��
    ----SttPpEngineServerֻ����Ϊ����������CreateDevice��CloseDeviceָ���������͹رն���
	----CSttPpServerClientSocket�����ĵĻ�������
	----CIotPxEngineDeviceBaseʵ�־����Э��ʵ�֣���������Э�����
	----CSttPpServerClientSocket��CIotPxEngineDeviceBase��һ�ԣ��໥����
*/

class CSttPpEngineServer : public  CSttTestEngineServerBase//, public CIotPxEngineFactoryBase
{
private:
	CSttPpEngineServer();
	virtual ~CSttPpEngineServer();

	static CSttPpEngineServer *g_pSttPpEngineServer;
	static long g_nSttPpEngineServerRef;

public:
	static CSttPpEngineServer* Create();
	static CSttPpEngineServer* Create(char *pszIP, int nPort);
	static void Release();

public:
    virtual void InitSttServerEngine(const char *pszIP, int nPort,int nReplayPort = 0);
	virtual void ExitSttServerEngine();
	virtual void OnTimer();

	virtual void CheckHeartbeatOverTime(){};
};

