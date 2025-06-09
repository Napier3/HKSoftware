#pragma once

#include "EdgeMqttEngineBase.h"

class CIotEdgeServer_Mqtt:public CEdgeMqttEngineBase
{
public:
	CIotEdgeServer_Mqtt();
	virtual ~CIotEdgeServer_Mqtt();

	//yzj 2021-12-4 ��֤��linkup֮ǰ,������Ҫ�ȴ���֤��Ϣ,linkupʱȡ����ɾ��
	CDataGroup m_oEdgeAuthList;

public:
	BOOL Init(const char *pszIP,long nPort);
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN, char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);

	virtual long Process_Edge_Device(const CString &strFromSN, char *pBuf, long nLen,char *pszCmdID);
	virtual long Process_Edge_Device_Request(const CString &strFromSN, char *pBuf, long nLen);
	virtual long Process_Edge_Device_Data(const CString &strFromSN, char *pBuf, long nLen);
};