#pragma once

#include "../CmmInterface/SttCmmInterface.h"
#include "../SttCmd/SttSysState.h"

/*  2021-7-18  lijunqing
增加CSttProtocolInterface接口的目的：
以STT协议为例：
	基础模块，比如用户管理、权限管理等功能，对于自动测试还是测试仪控制，都是
通用的需要派生的功能。
	对于自动测试功能来说，目前设计的MQTT协议，没有用户管理和权限控制，所以这种
模式需要进行改进。因此设计此接口
	此种模式：STT何MQTT，处理如下
	STT：基础通信模块增加测试仪控制协议对象指针和自动测试协议对象指针，
接受报文后，如果报文是用户权限部分，则对报文进行处理，否则调用相关的控制对象
指针进行处理
	MQTT：基础通信模块增加测试仪对象指针和自动测试协议对象指针，接受保温后
根据报文的类型，调用相关的控制对象指针进行处理。
	这种模式处理：测试仪控制协议对象、自动测试协议对象就可以做成通用，STT和MQTT
都能够调用，m_pPxCmmOptrInterface指针实现发送报文的接口。对于STT广播模式，可以在
CSttCmmOptrInterface的派生对象进行特殊处理。也可以在CSttProtocolInterface的派生对象中
进行特殊处理
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

	//2021-7-21  lijunqing  后续考虑将命令函数封装到Ats执行对象中，CSttAtsSvrMqttImpBase只作为命令中转对象，即：
	//通信对象（STT、MQTT）  <<==>>  SttCmd     
	virtual long Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv){return 0;}
	//shaolei 2023-6-13
	virtual long Process_Cmd_Iot(CXObjectRefDriver &oIotCmdDrv){return 0;}
	virtual long Process_Cmd_Test(CXObjectRefDriver &oTestCmdDrv){return 0;}
	virtual long Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv){return 0;}

	//shaolei 20210927
	virtual long Process_Cmd_Ats_Event_UploadFinish(CSttCmdBase* pSttCmdBase){return 0;}

	//当前命令的应答
	virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus, CSttCmdData *pRetData){return 0;}
	virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus, const CString &strDeviceID=_T("")){return 0;}

	//2021-7-22  lijunqing  增加返回系统状态的各种函数调用
	//前两个为兼容后面对用户信息返回，上面两个函数，不直接增加是为了兼容已有代码不要出现问题
	//以下函数，shaolei重新整理修改：函数名，形参等；  20210727
	virtual long ReturnSysState_REPLY(CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID, char *pszRetCmdType){return 0;}
	virtual long ReturnSysState_EVENT(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID, char *pszRetCmdType)	{return 0;	}
	
	//2021-8-6  lijunqing
	virtual long ReturnSysState_REPORT(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszRetCmdType)	{return 0;	}
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdBase *pSttCmd, long nCmdExecStatus, const CString &strDeviceID){return 0;}
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, int nCmdType, char *pszCmdID, BOOL bIsSuccess){return 0;}
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, CSttSysState *pSysState, BOOL bSpyAllCmd){return 0;}

	CSttCmmOptrInterface* GetPxCmmOptrInterface()  {   return m_pPxCmmOptrInterface; }
protected:
	//2021-7-18  李俊庆  由m_pPxCmmInterface 改为m_pPxCmmOptrInterface	//增加可读性
	//m_pPxCmmOptrInterface：关联的通信对象，此种模式适用于一对一的模式
	//对于多客户端控制对象，不实用，需要在消息处理函数中增加接受报文的对象，或者是返回
	//消息的通信对象
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

	//避免xml解析的时候，频繁分配内存，缺省为1M
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;
	void SetXmlBufferLen(long nLen);
};

//2021-7-17  lijunqing  收到命令消息
#define WM_ON_STT_ENGINE_CMD_RCV  (WM_USER+1717)   //对应CAtsCmd

//2021-8-21 lijunqing NewDevice
#define WM_ON_STT_ENGINE_NEW_DEVICE   (WM_USER+1718)
//2021-9-9 yzj
#define WM_ON_STT_ENGINE_DEL_DEVICE   (WM_USER+1719)
#define WM_ON_STT_ENGINE_CMD_RCV_JSON  (WM_USER+1720)
 
#define WM_ON_STT_ENGINE_CMD_RCV_IOTCMD    (WM_USER+1721)  //对应CIotCmd
#define WM_ON_STT_ENGINE_CMD_RCV_TESTCMD   (WM_USER+1722)  //对应CTestCmd
#define WM_ON_STT_ENGINE_CMD_RCV_SYSSTATE  (WM_USER+1723)  //对应CSysState
