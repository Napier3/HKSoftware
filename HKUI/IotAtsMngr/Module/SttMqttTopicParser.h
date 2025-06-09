#pragma once

#define STT_MQTT_SUBTOPIC_MAX_COUNT 16

class CSttMqttTopicParser
{
public:
	CSttMqttTopicParser();
	CSttMqttTopicParser(char *pszMqttTopic);
	virtual ~CSttMqttTopicParser();

	void InitSttMqttTopic(char *pszMqttTopic);

public:
	//主题拆分
	long m_nCount;
	char* m_pszSubTopic[STT_MQTT_SUBTOPIC_MAX_COUNT];
	CString m_strTopic;  //记录原始主题，兼容之前的业务

	//MQTT报文
	char *m_pMqttPkgBuffer;
	long m_nMqttPkgBufferLen;

private:
	char *m_pszTopic;
	long m_nTopicLen;

public:
	char *GetTopic()	{	return m_pszTopic;	}
	long GetTopicLen()	{	return m_nTopicLen;	}
	long GetXmlRWType();
	long FindXCmdType(const char *pszCmdType);  //2023-9-6  lijunqing 查找命令的主题位置
	void InitByParser(CSttMqttTopicParser *pSrc);
};

class CSttMqttTopicCmbn
{
public:
	CSttMqttTopicCmbn();
	virtual ~CSttMqttTopicCmbn();

	char *m_pszBuffer;
	long m_nBufferLength;

	void FreeBuffer();

public:
	//针对m_oSubTopics的操作函数
	void ResetSubTopics();
	void AddSubTopic(const CString &strText);
	void AddSubTopic(const char *strText);
	void AddSubTopic(long nValue);
	void SetSubTopic(long nIndex, const CString &strText);
	void SetSubTopic(long nIndex, const char *strText);
	void SetSubTopic(long nIndex, long nValue);
	CString GetTopic();
	char* CmbnTopic();
	char* GetTopic2()		{	return m_pszTopic;	}

	//直接针对m_pszMqttTopic
	void InitTopic(CSttMqttTopicParser &oParser);
	void InitTopicRet1(CSttMqttTopicParser &oParser, const char *pszSubTopic);
	void InitTopicRet2(CSttMqttTopicParser &oParser, const char *pszSubTopic);
	void AddSubTopic2(const CString &strText);
	void AddSubTopic2(const char *strText);
	void ReplaceSubTopicTail(long nValue);
	void ReplaceSubTopic(long nIndex, const char *pszText);
	void ClearSubTopicTail();
	void InitTopic();
	BOOL GetSubTopic(long nIndex, char *strText);

protected:
	BOOL GetSubTopicPos(long nIndex, long &nPos1, long &nPos2);

private:
	CStringArray m_oSubTopics;
	char *m_pszTopic;
	long m_nTopicLen;

//2023-8-16  lijunqing
public:
	void InitTopic(CSttMqttTopicCmbn *pSrc);
	long GetSubTopicCount()	{		return m_oSubTopics.GetSize();	}
};

