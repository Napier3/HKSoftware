#pragma once

#include "../ProtocolBase/PxProtocolImpInterface.h"
#include "IotVmEngineBase_Mqtt.h"
#include "../ProtocolBase/PxProtocolBase.h"

#include"../../../SttStudio/Module/SmartTestInterface/MacroTestInterface.h"
#include"../../../SttStudio/Module/SmartTestInterface/SttMacroTestServerInterface.h"
#include "../Vm/VmXImpBase.h"


class CIotVmServer_Mqtt;
class CIotVmProtoToXImp;



class CIotVmProtoToXImp : public CIotVmEngineBase_Mqtt, public CPxProtocolBase
	, public CSttMacroTestEventServerInterface
{
public:
	CIotVmProtoToXImp(CIotVmServer_Mqtt *pVmServer);
	virtual ~CIotVmProtoToXImp();

private:
	CIotVmProtoToXImp();

public:
	//协议被调用执行接口
	virtual void InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);

	virtual BOOL Init(const char *pszIP,long nPort);
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);
	virtual void OnClose(char *pszErr);

	virtual void OnTestState_Reply(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas);

public:
	//重新订阅主题:主要解决IotEngine断链后，规约引擎服务不知道，同一个装置再试收到CreateDevice主题，
	//需要取消订阅之前的主题，重新订阅新的主题
	void ReSubcribeMqttTopic();

	//创建协议转换模块和协议服务模块
	BOOL CreateProtocol(CSttTestCmd &oTestCmd);

public:
	CIotVmServer_Mqtt *m_pIotVmServer_Mqtt;

//测试仪接口定义部分
public:
	//通讯接口 + 消息处理
	CVmXImpBase *m_pVmXImpBase;
	CString m_strCurrPortocolID;

	LRESULT OnElectricTestMsg(WPARAM wParam, LPARAM lParam);
	void OnTimer(UINT nIDEvent);

//CSttMacroTestEventServerInterface
public:
	virtual void OnTestState_Reply(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttCmdData *pParas, long nExecStaus, char *pszEventID, char *pszRetCmdType);
	virtual void OnTestState_Report(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas);
	virtual void OnTestState_Exception(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas);

	virtual void OnTestEvent_ExecCmd(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas);
	virtual void OnTestEvent_ConnectSuccess(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas);
	virtual void OnTestEvent_ConnectFailed(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas);
	virtual void OnTestEvent_TestStarted(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas);
	virtual void OnTestEvent_TestFinished(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas);
	virtual void OnTestEvent_TestStoped(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas);
	virtual void OnTestEvent_SearchPointReport(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas);

};
