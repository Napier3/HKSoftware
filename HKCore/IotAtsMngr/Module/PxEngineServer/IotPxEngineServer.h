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
	CIotPxEngineFactoryMngr m_oIotPxEngineFactoryMngr;   //引擎接口管理
	CIotPxEngineDeviceMngr m_oIotPxEngineDeviceMngr;  //创建的所有通信设备对象管理

//	static CExBaseList *m_pServerSocketRef;//Socket服务端,用于后续通过查找链表判断对应Socket是否还存在
//	TxArray<CIotPxCommChannelInterface> m_oIotPxCommChannelInterfaceRef;//存放添加的全部通道接口
	
protected:
	CIotPxEngineDeviceMngr m_oDeviceMngrForDel;  //需要删除的对象
	TxArray<CIotPxCommChannelInterface> m_oPxCommChannelInterfaceRef;//zhouhj 2024.9.27 在Linux下出现调用到创建设备接口时,该对应已经被删除,暂时先不删除实际对象
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

//全局的协议引擎服务对象，当前只考虑一个协议服务引擎
//此协议服务引擎集成MEAS、PpEngine、MmsEngine、CMSEngine等
extern CIotPxEngineServer* g_theIotPxEngineServer;