#ifndef _IotEngineGlobalDef_h_
#define _IotEngineGlobalDef_h_

#define PROCEDURE_ID_WriteMmsAttr		_T("WriteMmsAttr")
#define MODEL_DEVICE_ID_Attr			_T("dsDeviceAttr")
#define MODEL_Attr_PkgUpTmInterval		_T("PkgUpTmInterval")

//过程事件
#define RUNPROCEDURE_EVENT_ConnectDeviceFailed			_T("ConnectDeviceFailed")
#define RUNPROCEDURE_EVENT_ConnectDeviceSuccessful		_T("ConnectDeviceSuccessful")
#define RUNPROCEDURE_EVENT_CommError					_T("CommError")
#define RUNPROCEDURE_EVENT_CommFinish					_T("CommFinish")
#define RUNPROCEDURE_EVENT_CommCmdError					_T("CommCmdError")
#define RUNPROCEDURE_EVENT_Exception					_T("Exception")
#define RUNPROCEDURE_EVENT_CommOverTime					_T("CommOverTime")

enum _tagEngineSystemDefine
{//2020-5-21  lijunqing
	engineConnectDeviceFailed= 1, //0,
	engineConnectDeviceSuccessful=2, //1,
	engineCommError = 3, //2,
	engineCommFinish = 4, //3,
	engineCommCmdError=5, //4
	engineException=6 //5
};

//命令执行状态	ExecStatus	0=未处理  1=ACK 2=执行失败，3=执行成功
#define STT_CMD_ExecStatus_NULL		0
#define STT_CMD_ExecStatus_ACK		1
#define STT_CMD_ExecStatus_FAILURE	2
#define STT_CMD_ExecStatus_SUCCESS	3
#define STT_CMD_ExecStatus_TIMEOUT	4
#define STT_CMD_ExecStatus_SocketClose	5

inline BOOL Stt_Is_ExecStatus_NULL(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_NULL);
}

inline BOOL Stt_Is_ExecStatus_Ack(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_ACK);
}

inline BOOL Stt_Is_ExecStatus_Failure(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_FAILURE);
}

inline BOOL Stt_Is_ExecStatus_Success(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_SUCCESS);
}

inline BOOL Stt_Is_ExecStatus_Timeout(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_TIMEOUT);
}


#endif