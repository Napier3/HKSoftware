#pragma once

#include "SttClientTestEngine.h"

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

class CSttNativeClientTestEngine : public CSttClientTestEngine
{
public:
	CSttNativeClientTestEngine();
	virtual ~CSttNativeClientTestEngine();
	
public:
	virtual BOOL OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType, BOOL &bRet);

	virtual long Process_SysState_System(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_Cmd_Debug(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	long Process_Debug_GetSocketConnect(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);

	//ֻ�о��е�������Ȩ�޵Ĳ��Զ˶�ʱ��������
	virtual void OnSendHeartbeatTimer();

public:
	void SetExternEngineRef(CSttTestEngineBase *pExternEngineRef)	{	m_pExternEngineRef = pExternEngineRef;	}

protected:
	CSttTestEngineBase *m_pExternEngineRef;

};
