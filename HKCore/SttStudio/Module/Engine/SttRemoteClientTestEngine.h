#pragma once

#include "SttTestEngineBase.h"
#include "../TestClient/SttMacroTestInterface.h"
#include "SttTestEngineRemoteClientData.h"

//˵��1��
//CSttClientTestEngine����Ϊһ̨�����ǵĲ��Կ��ƶ�������Ƕ�̨�����ǣ���Ҫ�������CSttClientTestEngine����
//����CSttClientTestEngine�����Ϊȫ��Ψһ����
//��������

//˵��2��
//���Զˣ����ڲ��ԵĹ��̿��ƣ����Ϊ��״̬��ģʽ��
//0=û��ʼ���ԣ�
//1=�����˲��������û���أ�������ġ���ʼ����ֹͣ����ť�����ܰ���
//2=����أ���ʼ���Թ��̣�������ġ���ʼ����ң���ֹͣ����ťʹ�ܡ�
//3=���Խ�����������ġ���ʼ��ʹ�ܣ���ֹͣ����ť��ҡ�
//4=�����쳣��������ġ���ʼ��ʹ�ܣ���ֹͣ����ť��ҡ�
//0=�ر��豸��CloseDevice�������س�ʼ״̬

class CSttRemoteClientTestEngine : public CSttTestEngineBase, public CSttTestEngineRemoteClientData
{
public:
	CSttRemoteClientTestEngine();
	virtual ~CSttRemoteClientTestEngine();

	virtual CSttCmdOverTimeMsgRcv *GetCmdOverTimeMsgRcv(){	return this;	};

	virtual BOOL ConnectServer(const CString &strIPServer, long nPort);
	virtual void OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket = TRUE);
	
public:
	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket,  CSttTestCmd &oTestCmd);
	virtual long Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);

	virtual long Process_SysState_System(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Test(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Debug(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Remote(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

	//Ҫ���ǣ�ϵͳæ����Ȩ�޵�Ӧ����Ϣ

	virtual long Process_SysState_BroadcastUserMngr(CSttSysState &oSysState);

	//shaolei   20210527
	virtual long Process_SysState_Event(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Exception(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Report(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
public:

};
