#pragma once
#include "MqttEngineBase.h"
#include "../../../SttStudio/Module/SttCmd/SttIotCmd.h"
#include "../../../SttStudio/Module/SttCmd/SttSysState.h"


class CSttMqttEngineBase:public CMqttEngineBase
{
public:
	CSttMqttEngineBase();
	virtual ~CSttMqttEngineBase();

public:
	virtual void BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat);

	//当前命令的应答
	virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttCmdData *pRetData);
	virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,const CString &strDeviceID=_T(""));

	//2021-7-22  lijunqing  增加返回系统状态的各种函数调用
	//前两个为兼容后面对用户信息返回，上面两个函数，不直接增加是为了兼容已有代码不要出现问题
	//以下函数，shaolei重新整理修改：函数名，形参等；  20210727
	virtual long ReturnSysState_REPLY(CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID, char *pszRetCmdType);
	virtual long ReturnSysState_EVENT(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID, char *pszRetCmdType);

	//2021-8-6  lijunqing
	virtual long ReturnSysState_REPORT(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszRetCmdType);
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdBase *pSttCmd, long nCmdExecStatus, const CString &strDeviceID);
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, int nCmdType, char *pszCmdID, BOOL bIsSuccess);
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, CSttSysState *pSysState, BOOL bSpyAllCmd);

};