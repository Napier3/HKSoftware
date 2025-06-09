#pragma  once

#include "..\..\Module\mosquitto-1.4.8\src\Mosquitto_Process.h"


class CSttIotMqttSvrBase
{
public:
	CSttIotMqttSvrBase();
	virtual ~CSttIotMqttSvrBase();

	static long GenerateIndexTest();
	static long GenerateIndexItem();

private:
	CExBaseObject* NewMosquittoClient(const char* strName, const char* strID);

public:
	void InitSttIotMqttSvrBase();
	void ExitSttIotMqttSvrBase();

	static BOOL SendTopicData(const CString& strTopic, char *pBuf, long nLen);
	void SetMsgWnd(const HWND hWnd);
	void Process_UpdateLog(int nPriority, const char* strMsg);
	void Process_Disconnect(const char* strID);
	void Process_Connect(const char* strIP, const char* strID);
	void Process_Subscribe(const char* strTopic, const char* strID);
	void Process_Unsubscribe(const char* strTopic, const char* strID);

public:
	CExBaseList m_oClientList;
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;

	HWND m_hWnd;
};

extern CString g_strRTDeviceRptPath;

