#pragma once

#include "IotPxEngineDeviceMngr.h"
#include "IotPxEngineFactoryMngr.h"
#include "IotPxEngineServerWnd.h"



class CIotPxEngineServer : public CIotPxEngineServerInterface
{
private:
	CIotPxEngineServer();
	virtual ~CIotPxEngineServer();

	static long g_nPxEngineServerRef;
	static CIotPxEngineServer* g_pIotPxEngineServer;

	CIotPxEngineServerWnd *m_pIotPxEngineServerWnd;

public:
	static CIotPxEngineServer*  Create();
	static void Release();

	static void RegisterFactory(CIotPxEngineFactoryBase *pFactory);
	static void POST_WM_IOT_CMD_MSG(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);

public:
	CIotPxEngineFactoryMngr m_oIotPxEngineFactoryMngr;   //����ӿڹ���
	CIotPxEngineDeviceMngr m_oIotPxEngineDeviceMngr;  //����������ͨ���豸�������

//	static CExBaseList *m_pServerSocketRef;//Socket�����,���ں���ͨ�����������ж϶�ӦSocket�Ƿ񻹴���
//	TxArray<CIotPxCommChannelInterface> m_oIotPxCommChannelInterfaceRef;//�����ӵ�ȫ��ͨ���ӿ�
	
protected:
	CIotPxEngineDeviceMngr m_oDeviceMngrForDel;  //��Ҫɾ���Ķ���
	TxArray<CIotPxCommChannelInterface> m_oPxCommChannelInterfaceRef;//zhouhj 2024.9.27 ��Linux�³��ֵ��õ������豸�ӿ�ʱ,�ö�Ӧ�Ѿ���ɾ��,��ʱ�Ȳ�ɾ��ʵ�ʶ���
    void DeleteAllDevice();

public:
	void RemoveDeviceFromFolDel(CIotPxEngineDeviceBase *pDevice);
	virtual CIotPxEngineDeviceBase* CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd);
	virtual void CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd) ;
	virtual void CloseByPxCommChannel(CIotPxCommChannelInterface *pPxCommChn) ;

public:
	void OnIotCmd(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd);

	void AddIotPxCommChannelInterfaceRef(CIotPxCommChannelInterface *pPxCommChn);

	long Process_Cmd_IOT_CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);
	long Process_Cmd_IOT_CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd);

};

//ȫ�ֵ�Э�����������󣬵�ǰֻ����һ��Э���������
//��Э��������漯��MEAS��PpEngine��MmsEngine��CMSEngine��
extern CIotPxEngineServer* g_theIotPxEngineServer;