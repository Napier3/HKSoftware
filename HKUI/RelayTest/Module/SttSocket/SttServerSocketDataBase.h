#pragma once

#include "../SttSocket/SttSocketDataBase.h"
//#include "../SttSocket/SttSocketDataBase_File.h"
#include "../SttSocket/SttCmdOverTimeMsgRcv.h"
#include "../../../Module/BaseClass/ExBaseList.h"

class CSttServerSocketDataBase : public CExBaseList, public CSttCmdOverTimeMsgRcv
{
public:
	CSttServerSocketDataBase();
	virtual ~CSttServerSocketDataBase();

public:
	virtual void OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);
	virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);
	void AttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv);

	CString m_strIPLocal;
	int m_nPortLocal;
	int m_nMaxClientCount;
public:
	//用于设置连接socket的Engine,用于区分NativeEngine和TestSeverEngine
	CSttTestEngineBase *m_pTestEngine;
	void SetTestEngine(CSttTestEngineBase *pTestEngine)	{	m_pTestEngine = pTestEngine;	}

public:
	virtual void OnSttSktAccept(CSttSocketDataBase_File *pSttSkt);
    virtual void OnSttScktClose(CSttXcmdChInterface *pSttSckt, BOOL bDeleteSocket = TRUE);   //shaolei 2023-12-29 增加是否删除形参
	virtual BOOL CreateServer(const char *pszIP, int nPort) = 0;
	virtual void CloseSttServer();    	//2020-4-6  lijq

	virtual BOOL SendBufferToChildren(CSttSocketDataBase *pExceptSocket,BYTE *pBuf,long nLen);	

	BOOL IsSocketExist(CSttSocketDataBase_File *p);	

private:
	CSttCmdOverTimeMsgRcv *m_pCmdOverTimeMsgRcv;
	CAutoCriticSection m_oCriticSection;
};

