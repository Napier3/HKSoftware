#pragma once

#include "XUserTcpClientBase.h"

class CXUserTcpClient : public CXUserTcpClientBase
{
public:
	CXUserTcpClient(void);
	virtual ~CXUserTcpClient(void);

public:
	BOOL ConnectServer(const CString &strIP, UINT nPort);
	void DisConnectServer();

protected:
	virtual BOOL ProcessXUserCmd(CDvmData *pData);

	BOOL ProcessXUserCmd_Login(CDvmData *pData);
	BOOL ProcessXUserCmd_Logout(CDvmData *pData);
	BOOL ProcessXUserCmd_GetInfor(CDvmData *pData);
	BOOL ProcessXUserCmd_HasFetureID(CDvmData *pData);


public:
	virtual void OnClose(int nErrorCode);
};
