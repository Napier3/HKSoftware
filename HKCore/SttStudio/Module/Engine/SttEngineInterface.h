#pragma once

#include "../CmmInterface/SttCmmInterface.h"
#include "../SttCmd/SttSysState.h"

/*  2021-7-18  lijunqing
����CSttProtocolInterface�ӿڵ�Ŀ�ģ�
��STTЭ��Ϊ����
	����ģ�飬�����û�����Ȩ�޹���ȹ��ܣ������Զ����Ի��ǲ����ǿ��ƣ�����
ͨ�õ���Ҫ�����Ĺ��ܡ�
	�����Զ����Թ�����˵��Ŀǰ��Ƶ�MQTTЭ�飬û���û������Ȩ�޿��ƣ���������
ģʽ��Ҫ���иĽ��������ƴ˽ӿ�
	����ģʽ��STT��MQTT����������
	STT������ͨ��ģ�����Ӳ����ǿ���Э�����ָ����Զ�����Э�����ָ�룬
���ܱ��ĺ�����������û�Ȩ�޲��֣���Ա��Ľ��д������������صĿ��ƶ���
ָ����д���
	MQTT������ͨ��ģ�����Ӳ����Ƕ���ָ����Զ�����Э�����ָ�룬���ܱ��º�
���ݱ��ĵ����ͣ�������صĿ��ƶ���ָ����д���
	����ģʽ���������ǿ���Э������Զ�����Э�����Ϳ�������ͨ�ã�STT��MQTT
���ܹ����ã�m_pPxCmmOptrInterfaceָ��ʵ�ַ��ͱ��ĵĽӿڡ�����STT�㲥ģʽ��������
CSttCmmOptrInterface����������������⴦��Ҳ������CSttProtocolInterface������������
�������⴦��
*/
class CSttProtocolInterface
{
public:
	CSttProtocolInterface()
	{
		m_pPxCmmOptrInterface = NULL;
	}

	virtual ~CSttProtocolInterface(){}

public:
	void AttachPxCmmInterface(CSttCmmOptrInterface *pPxCmmInterface)
	{
		m_pPxCmmOptrInterface = pPxCmmInterface;
	}
	
	void FreePxCmmInterface()
	{
		m_bConnected = FALSE;

		if (m_pPxCmmOptrInterface != NULL)
		{
			delete m_pPxCmmOptrInterface;
			m_pPxCmmOptrInterface = NULL;
		}
	}

	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN, char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType) = 0;
	virtual void OnClose(char *pszErr) = 0;
	virtual long Send(const CString &strToSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID) = 0;
	virtual long Send(CExBaseObject *pCmdBase) = 0;
	virtual BOOL Connect(const char *pszIP,long nPort) = 0;
	virtual void Disconnect() = 0;

	virtual void BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat) = 0;

	//2021-7-21  lijunqing  �������ǽ��������װ��Atsִ�ж����У�CSttAtsSvrMqttImpBaseֻ��Ϊ������ת���󣬼���
	//ͨ�Ŷ���STT��MQTT��  <<==>>  SttCmd     
	virtual long Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv){return 0;}
	//shaolei 2023-6-13
	virtual long Process_Cmd_Iot(CXObjectRefDriver &oIotCmdDrv){return 0;}
	virtual long Process_Cmd_Test(CXObjectRefDriver &oTestCmdDrv){return 0;}
	virtual long Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv){return 0;}

	//shaolei 20210927
	virtual long Process_Cmd_Ats_Event_UploadFinish(CSttCmdBase* pSttCmdBase){return 0;}

	//��ǰ�����Ӧ��
	virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus, CSttCmdData *pRetData){return 0;}
	virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus, const CString &strDeviceID=_T("")){return 0;}

	//2021-7-22  lijunqing  ���ӷ���ϵͳ״̬�ĸ��ֺ�������
	//ǰ����Ϊ���ݺ�����û���Ϣ���أ�����������������ֱ��������Ϊ�˼������д��벻Ҫ��������
	//���º�����shaolei���������޸ģ����������βεȣ�  20210727
	virtual long ReturnSysState_REPLY(CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID, char *pszRetCmdType){return 0;}
	virtual long ReturnSysState_EVENT(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID, char *pszRetCmdType)	{return 0;	}
	
	//2021-8-6  lijunqing
	virtual long ReturnSysState_REPORT(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszRetCmdType)	{return 0;	}
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdBase *pSttCmd, long nCmdExecStatus, const CString &strDeviceID){return 0;}
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, int nCmdType, char *pszCmdID, BOOL bIsSuccess){return 0;}
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, CSttSysState *pSysState, BOOL bSpyAllCmd){return 0;}

	CSttCmmOptrInterface* GetPxCmmOptrInterface()  {   return m_pPxCmmOptrInterface; }
protected:
	//2021-7-18  ���  ��m_pPxCmmInterface ��Ϊm_pPxCmmOptrInterface	//���ӿɶ���
	//m_pPxCmmOptrInterface��������ͨ�Ŷ��󣬴���ģʽ������һ��һ��ģʽ
	//���ڶ�ͻ��˿��ƶ��󣬲�ʵ�ã���Ҫ����Ϣ�����������ӽ��ܱ��ĵĶ��󣬻����Ƿ���
	//��Ϣ��ͨ�Ŷ���
	CSttCmmOptrInterface *m_pPxCmmOptrInterface;
	BOOL m_bConnected;	

};

class CSttEngineInterface : public CExBaseList, public CSttProtocolInterface
{
public:
	CSttEngineInterface();
	virtual ~CSttEngineInterface();

public:
	//void AttachPxCmmInterface(CSttCmmOptrInterface *pPxCmmInterface){m_pPxCmmInterface = pPxCmmInterface;}
	//void FreePxCmmInterface();
	//2021-8-22  lijunqing Add strFromSN
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,  char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);
	virtual void OnClose(char *pszErr);
	virtual long Send(const CString &strToSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	virtual long Send(CExBaseObject *pCmdBase);
	virtual BOOL Connect(const char *pszIP,long nPort);
	virtual void Disconnect();

	virtual void BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat);

protected:
	//CSttCmmOptrInterface *m_pPxCmmInterface;

	//BOOL m_bConnected;	

	//����xml������ʱ��Ƶ�������ڴ棬ȱʡΪ1M
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;
	void SetXmlBufferLen(long nLen);
};

//2021-7-17  lijunqing  �յ�������Ϣ
#define WM_ON_STT_ENGINE_CMD_RCV  (WM_USER+1717)   //��ӦCAtsCmd

//2021-8-21 lijunqing NewDevice
#define WM_ON_STT_ENGINE_NEW_DEVICE   (WM_USER+1718)
//2021-9-9 yzj
#define WM_ON_STT_ENGINE_DEL_DEVICE   (WM_USER+1719)
#define WM_ON_STT_ENGINE_CMD_RCV_JSON  (WM_USER+1720)
 
#define WM_ON_STT_ENGINE_CMD_RCV_IOTCMD    (WM_USER+1721)  //��ӦCIotCmd
#define WM_ON_STT_ENGINE_CMD_RCV_TESTCMD   (WM_USER+1722)  //��ӦCTestCmd
#define WM_ON_STT_ENGINE_CMD_RCV_SYSSTATE  (WM_USER+1723)  //��ӦCSysState
