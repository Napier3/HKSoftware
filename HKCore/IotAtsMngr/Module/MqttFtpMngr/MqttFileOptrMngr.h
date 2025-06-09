#pragma once
#include "MqttFileOptr.h"

class CMqttFileOptrMngr:public CExBaseList,public CMqttCmdOverTimeMsgRcv
{
public:
	CMqttFileOptrMngr();
	virtual ~CMqttFileOptrMngr();

public:
	virtual void OnSendCmdFailFinish(const char *pszSrcID, const char *pszCmdType,UINT nErrCode);
	virtual void OnSendCmdFinish(const char *pszSrcID, const char *pszCmdType);
	virtual void OnSendCmdOverTime(const char *pszSrcID, const char *pszTopic);

public:
	void SubcribeFtpToic();
	void CheckMqttFtpMsgRecv(CStringTokenizer &oToken,char *pBuf,long nLen);
	long Process_UploadFileCmd(CStringTokenizer &oToken,char *pBuf,long nLen);
	long Process_DownloadFileCmd(CStringTokenizer &oToken,char *pBuf,long nLen);
};