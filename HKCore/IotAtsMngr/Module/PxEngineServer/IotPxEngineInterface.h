#pragma once

#include "../../../SttStudio/Module/SttCmd/SttIotCmd.h"
#include "../../../SttStudio/Module/SttCmd/SttSysState.h"
#include "../../../Module/BaseClass/XObjectRefBase.h"
#include "../../../Module/BaseClass/TxArray.h"

class CIotPxEngineInterface;
class CIotPxEngineServerInterface;

class CIotPxEngineDeviceBase;
class CXObjectRefBase;

#define _PxCommChannelInterface_CLASSID_SOCKET_  0
#define _PxCommChannelInterface_CLASSID_MQTT_    1

//通信通道接口，例如STT协议、MQTT协议
class CIotPxCommChannelInterface: public CXObjectRefBase
{
public:
	CIotPxCommChannelInterface();
	virtual ~CIotPxCommChannelInterface();
	
public:
	virtual long PxSendBuffer(BYTE *pBuf, long nLen) = 0;
	virtual long PxSendSysState(CSttSysState *pSysState) = 0;
	virtual UINT GetClassID() = 0;
	virtual void FreeCmd(CExBaseObject *pCmd);
	virtual void AddCmd(CExBaseObject *pCmd);
	virtual void Release();
	virtual void Release(BOOL bDeleteThis);//zhouhj 2024.9.27
	
public:
	//引擎服务对象，创建、关闭设备需要在引擎服务对象中进行
	CIotPxEngineServerInterface *m_pPxEngineServer;
	
	//引擎对象，各种通信命令的执行
	CIotPxEngineDeviceBase *m_PxEngineDevice;

	long m_nSttCmdDataFormat;  //2022-10-22  lijunqing 命令数据的格式，根据接收的报文自动识别
	TxArray<CSttCmdBase> m_oArrIotCmd;  //绑定当前接口的cmd列表

	inline void InitSttCmdDataFormat(char ch)
	{
		if (m_nSttCmdDataFormat != -1)
		{
			return;
		}

		if (ch == '<')
		{
			m_nSttCmdDataFormat = _PUGI_XML_TYPE_;
		}
		else if (ch == '{')
		{
			m_nSttCmdDataFormat = _JSON_TYPE_;
		}
		else
		{
			m_nSttCmdDataFormat = _PUGI_XML_TYPE_;
		}
	}

	inline long GetSttCmdDataFormat()
	{
		if (m_nSttCmdDataFormat == -1)
		{
			return _PUGI_XML_TYPE_;
		}
		else
		{
			return m_nSttCmdDataFormat;
		}
	}
};

//引擎接口
class CIotPxEngineInterface : public CExBaseList
{
public:
	CIotPxEngineInterface();
	virtual ~CIotPxEngineInterface();

public:
	virtual CIotPxEngineDeviceBase* CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd);
	virtual void CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd);

};

class CIotPxEngineServerInterface : public CIotPxEngineInterface
{
public:
	CIotPxEngineServerInterface();
	virtual ~CIotPxEngineServerInterface();

};

long iotpx_ReturnSysState(CIotPxCommChannelInterface *pCommCh, CSttCmdBase *pSttCmd, long nCmdExecStatus,
						  CDvmDataset *pDataset=NULL,const CString &strAddDataID = _T(""),const CString &strAddDataValue = _T(""));
long iotpx_ReturnSysState(CIotPxCommChannelInterface *pCommCh, CSttSysState &oSysState);
long iotpx_ReturnSysState(CSttSysState &oSysState, const CString &strFromSN, const CString &strDeviceSN);
//2022-12-15  lijunqing
void iotpx_LogSttCmd(CSttCmdBase *pSttCmd);


