#pragma once

#include "SttTestEngineBase.h"
#include "../TestClient/SttMacroTestInterface.h"
#include "SttTestEngineClientData.h"

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

class CSttClientTestEngine : public CSttTestEngineBase, public CSttTestEngineClientData
{
public:
	CSttClientTestEngine();
	virtual ~CSttClientTestEngine();

	virtual CSttCmdOverTimeMsgRcv *GetCmdOverTimeMsgRcv(){	return this;	};
	
	virtual BOOL ConnectServer(const CString &strIPServer, long nPort);
//	virtual void CloseSocket(CSttSocketDataBase *pSocket);
	virtual void OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket = TRUE);

public:
	virtual long OnTestMsg(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen);

	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket,  CSttTestCmd &oTestCmd);
	virtual long Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);

	virtual long Process_SysState_System(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Test(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Debug(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Ats(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Adjust(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_IOT(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

	virtual long Process_SysState_BroadcastUserMngr(CSttSysState &oSysState);
	virtual long Process_SysState_State(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_SearchPointReport(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Exception(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Packet(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Report(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Event(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Update(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Log(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_RtData(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
    virtual long Process_SysState_Meas(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Ats_Stop(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

	virtual long Process_Cmd_Comtrade(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Comtrade_RequestData(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Comtrade_SendDataStartAck(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_SysState_System_LiveUpdate(CSttSysState &oSysState);

//2020-10-25  lijunqing
public:
	virtual long Process_SysState(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor, char *pszRetCmdType);

    //2022-2-12  lijunqing
    virtual void AddPkgDispatch(CSttPkgDispatchInterface *pPkgDispatch);
	virtual void RemovePkgDispatch(CSttPkgDispatchInterface *pPkgDispatch);
};
