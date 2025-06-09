#ifndef _SttCmdToolMngr_h_
#define _SttCmdToolMngr_h_

#include "SttSocket/SttCmdOverTimeMngr.h"
#include "SttSocket/SttSocketDataBase.h"

////////////文件上传下载机制/////////////////
#define STT_CMD_RET_RESULT_NULL 			0
#define STT_CMD_RET_RESULT_PROCESSING	 	1
#define STT_CMD_RET_RESULT_FINISH			2
#define STT_CMD_RET_RESULT_FAILURE 			3
#define STT_CMD_RET_RESULT_TIMEOUT 			4


//文件上传下载工具类
class CSttCmdTool: public CExBaseList, public CSttCmdOverTimeMsgRcv
{
public:
	CSttCmdTool();
	virtual ~CSttCmdTool();

public:
	virtual void OnSendCmdFailFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);
	virtual void OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);
	virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);

public:
	void AttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv);
	virtual BOOL SendCmd(CSttSocketDataBase *pSocket,CSttCmdBase *pCmd,long nTimeout);

protected:
	void SetRetResult_NULL();
	void SetRetResult_Proccessing();
	void SetRetResult_Failure();
	void SetRetResult_Timeout();
	void SetRetResult_Finish();
	BOOL IsRetResult_NULL();
	BOOL IsRetResult_Proccessing();
	BOOL IsRetResult_Finish();
	BOOL IsRetResult_Failure();
	BOOL IsRetResult_Timeout();
	
public:
	long m_nRetResult;//

	CSttCmdOverTimeMsgRcv *m_pCmdOverTimeMsgRcv;
};


#endif