#include "stdafx.h"
#include "SttMqttTopicParser.h"
#include "../../Module/API/StringApi.h"
#include "../../Module/xml/XmlRWBase.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

/////////////////////////////////////////////
CSttMqttTopicParser::CSttMqttTopicParser()
{
	m_pMqttPkgBuffer = NULL;
	m_nMqttPkgBufferLen = 0;
	m_pszTopic = NULL;

	for (long nIndex=0; nIndex<STT_MQTT_SUBTOPIC_MAX_COUNT; nIndex++)
	{
		m_pszSubTopic[nIndex] = NULL;
	}
}

CSttMqttTopicParser::CSttMqttTopicParser(char *pszMqttTopic)
{
	m_pMqttPkgBuffer = NULL;
	m_nMqttPkgBufferLen = 0;
	InitSttMqttTopic(pszMqttTopic);
}

void CSttMqttTopicParser::InitSttMqttTopic(char *pszMqttTopic)
{
	m_nTopicLen = strlen(pszMqttTopic);
	m_pszTopic = new char [m_nTopicLen + 2];
	memcpy(m_pszTopic, pszMqttTopic, m_nTopicLen);
	m_pszTopic[m_nTopicLen] = 0;
	m_pszTopic[m_nTopicLen+1] = 0;
	
	long nIndex = 0;
	char *p = m_pszTopic;
	m_nCount = 0;
	m_pszSubTopic[m_nCount] = p;

	while (*p != 0)
	{
		if (*p == '/')
		{
			*p = 0;
			p++;
			m_nCount++;
			m_pszSubTopic[m_nCount] = p;
		}
		else
		{
			p++;
		}
	}

	m_nCount++;

	for (nIndex=m_nCount; nIndex<STT_MQTT_SUBTOPIC_MAX_COUNT; nIndex++)
	{
		m_pszSubTopic[nIndex] = NULL;
	}
}

CSttMqttTopicParser::~CSttMqttTopicParser()
{
	delete m_pszTopic;
}

long CSttMqttTopicParser::GetXmlRWType()
{
	if (*m_pMqttPkgBuffer == '<')
	{
		return _PUGI_XML_TYPE_;
	}
	else if (*m_pMqttPkgBuffer == '{')
	{
		return _JSON_TYPE_;
	}
	else
	{
		return _PUGI_XML_TYPE_;
	}
}

//2023-9-6  lijunqing 查找命令的主题位置
long CSttMqttTopicParser::FindXCmdType(const char *pszCmdType)
{
	long k = 0;

	for (k=0; k<m_nCount; k++)
	{
		if (strcmp(pszCmdType, m_pszSubTopic[k]) == 0)
		{
			return k;
		}
	}

	return -1;
}

void CSttMqttTopicParser::InitByParser(CSttMqttTopicParser *pSrc)
{
	m_nTopicLen = pSrc->m_nTopicLen;
	m_pszTopic = new char[m_nTopicLen+2];
	memcpy(m_pszTopic, pSrc->m_pszTopic, m_nTopicLen);
	m_nCount = pSrc->m_nCount;
	m_pszTopic[m_nTopicLen] = 0;
	m_pszTopic[m_nTopicLen+1] = 0;

	long nIndex = 0;
	char *p = m_pszTopic;
	char *pEnd = m_pszTopic + m_nTopicLen;
	m_pszSubTopic[0] = p;
	nIndex = 1;

	while (p < pEnd)
	{
		if (*p == 0)
		{
			m_pszSubTopic[nIndex] = p+1;
			nIndex++;
		}

		p++;
	}

	for (nIndex=m_nCount; nIndex<STT_MQTT_SUBTOPIC_MAX_COUNT; nIndex++)
	{
		m_pszSubTopic[nIndex] = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//
CSttMqttTopicCmbn::CSttMqttTopicCmbn()
{
	m_pszBuffer = NULL;
	m_nBufferLength = 0;
	m_pszTopic = NULL;
	m_nTopicLen = 0;
}

CSttMqttTopicCmbn::~CSttMqttTopicCmbn()
{
	if (m_pszBuffer != NULL)
	{
		delete m_pszBuffer;
		m_pszBuffer = NULL;
	}

	if (m_pszTopic != NULL)
	{
		delete m_pszTopic;
		m_pszTopic = NULL;
	}
}

void CSttMqttTopicCmbn::FreeBuffer()
{
	if (m_pszBuffer != NULL)
	{
		delete m_pszBuffer;
		m_pszBuffer = NULL;
	}
}

void CSttMqttTopicCmbn::ResetSubTopics()
{
	m_oSubTopics.RemoveAll();
}

void CSttMqttTopicCmbn::AddSubTopic(const CString &strText)
{
	m_oSubTopics.Add(strText);
}

void CSttMqttTopicCmbn::AddSubTopic(const char *strText)
{
	m_oSubTopics.Add(CString(strText));
}

void CSttMqttTopicCmbn::AddSubTopic(long nValue)
{
	CString strText;
	strText.Format(_T("%d"), nValue);
	AddSubTopic(strText);
}

void CSttMqttTopicCmbn::SetSubTopic(long nIndex, const CString &strText)
{
	m_oSubTopics.SetAt(nIndex, strText);
}

void CSttMqttTopicCmbn::SetSubTopic(long nIndex, const char *strText)
{
	m_oSubTopics.SetAt(nIndex, CString(strText));
}

void CSttMqttTopicCmbn::SetSubTopic(long nIndex, long nValue)
{
	CString strText;
	strText.Format(_T("%d"), nValue);
	SetSubTopic(nIndex, strText);
}

CString CSttMqttTopicCmbn::GetTopic()
{
	CString strTopic;
	long nIndex = 0;
	long nCount = m_oSubTopics.GetSize();

	for (nIndex=0; nIndex<nCount-1; nIndex++)
	{
		strTopic += m_oSubTopics.GetAt(nIndex);
		strTopic += _T("/");
	}

	strTopic += m_oSubTopics.GetAt(nIndex);

	return strTopic;
}

char* CSttMqttTopicCmbn::CmbnTopic()
{
	InitTopic();

	long nIndex = 0;
	long nCount = m_oSubTopics.GetSize();
	char *p = m_pszTopic;
	long nLen = 0;

	for (nIndex=0; nIndex<nCount-1; nIndex++)
	{
		nLen = CString_to_char(m_oSubTopics.GetAt(nIndex), p);
		p += nLen;
		*p = '/';
		p++;
	}

	CString_to_char(m_oSubTopics.GetAt(nIndex), p);

	return m_pszTopic;
}

//直接针对m_pszMqttTopic
void CSttMqttTopicCmbn::InitTopic(CSttMqttTopicParser &oParser)
{
	InitTopic();
	m_nTopicLen = oParser.GetTopicLen();
	memcpy(m_pszTopic, oParser.GetTopic(), m_nTopicLen);

	char *pEnd = m_pszTopic + m_nTopicLen;
	char *p = m_pszTopic;

	//oParser的Topic，将'/'格式化为NULL
	while (p < pEnd)
	{
		if (*p == 0)
		{
			*p = '/';
		}

		p++;
	}
}

void CSttMqttTopicCmbn::InitTopicRet1(CSttMqttTopicParser &oParser, const char *pszSubTopic)
{
	InitTopic();
	long k = 0;

	for (k=0; k<oParser.m_nCount; k++)
	{
		AddSubTopic2(oParser.m_pszSubTopic[k]);
	}

	AddSubTopic2(pszSubTopic);
}

void CSttMqttTopicCmbn::InitTopicRet2(CSttMqttTopicParser &oParser, const char *pszSubTopic)
{
	InitTopic();
	long k = 0;

	AddSubTopic2(oParser.m_pszSubTopic[1]);
	AddSubTopic2(oParser.m_pszSubTopic[0]);

	for (k=2; k<oParser.m_nCount; k++)
	{
		AddSubTopic2(oParser.m_pszSubTopic[k]);
	}

	AddSubTopic2(pszSubTopic);
}

void CSttMqttTopicCmbn::AddSubTopic2(const CString &strText)
{
	char *pszText = NULL;
	CString_to_char(strText, &pszText);
	AddSubTopic2(pszText);
	delete pszText;
}

void CSttMqttTopicCmbn::AddSubTopic2(const char *strText)
{
	char *pEnd = m_pszTopic + m_nTopicLen;

	if (m_nTopicLen > 0)
	{
		*pEnd = '/';
		pEnd++;
		strcpy(pEnd, strText);
		m_nTopicLen = m_nTopicLen + strlen(strText) + 1;
	}
	else
	{
		strcpy(pEnd, strText);
		m_nTopicLen = m_nTopicLen + strlen(strText) ;
	}
}

void CSttMqttTopicCmbn::ReplaceSubTopicTail(long nValue)
{
	char *pEnd = m_pszTopic + m_nTopicLen;
	while (*pEnd != '/')
	{
		*pEnd = 0;
		pEnd--;
		m_nTopicLen--;
	}

	//从 / 后面开始
	pEnd++;
	m_nTopicLen++;
	sprintf(pEnd, "%d", nValue);
	m_nTopicLen += strlen(pEnd);
}

BOOL CSttMqttTopicCmbn::GetSubTopicPos(long nIndex, long &nPos1, long &nPos2)
{
	nPos1 = -1;
	nPos2 = -1;
	char *p = m_pszTopic;
	long nCurr = 0;

	if (nIndex == 0)
	{
		nPos1 =0;
	}
	else
	{
		while (*p != 0)
		{
			if (*p == '/')
			{
				nCurr++;

				if (nCurr == nIndex)
				{
					nPos1 = p - m_pszTopic + 1;
					break;
				}
			}

			p++;
		}
	}

	if (nPos1 == -1)
	{
		return FALSE;
	}

	p++;
	while (*p != 0)
	{
		if (*p == '/')
		{
			nPos2 = p - m_pszTopic;
			break;
		}

		p++;
	}

	if (nPos2 == -1)
	{
		nPos2 = m_nTopicLen;
	}

	return TRUE;
}

void CSttMqttTopicCmbn::ReplaceSubTopic(long nIndex, const char *pszText)
{	//不考虑替换第一个
	long nPos1 = 0, nPos2 = 0;
	char *p = m_pszTopic;
	long nCurr = 0;

	if (!GetSubTopicPos(nIndex, nPos1, nPos2))
	{
		return;
	}

	//  1/2/3
	long nLen = strlen(pszText);

	if (nPos1 + nLen > nPos2)
	{
		char *pEnd = m_pszTopic + nPos2;
		char *p1 = m_pszTopic + m_nTopicLen;
		m_nTopicLen += nLen + nPos1 - nPos2;
		char *p2 = m_pszTopic + m_nTopicLen;

		while (p1 >= pEnd)
		{
			*p2 = *p1;
			p1--;
			p2--;
		}
	}
	else if (nPos1 + nLen < nPos2)
	{
		memcpy(m_pszTopic+ nPos1+nLen, m_pszTopic + nPos2, m_nTopicLen - nPos2);
		m_nTopicLen +=  nLen + nPos1 - nPos2;
		m_pszTopic[m_nTopicLen] = 0;
	}

	memcpy(m_pszTopic + nPos1, pszText, nLen);
}

void CSttMqttTopicCmbn::ClearSubTopicTail()
{
	char *p = m_pszTopic + m_nTopicLen;

	while (*p != '/')
	{
		*p = 0;
		p--;
	}

	*p = 0;
}

void CSttMqttTopicCmbn::InitTopic()
{
	if (m_pszTopic == NULL)
	{
		m_pszTopic = new char[128];
	}

	m_nTopicLen = 0;
	memset(m_pszTopic, 0, 128);
}

BOOL CSttMqttTopicCmbn::GetSubTopic(long nIndex, char *strText)
{
	long nPos1 = 0, nPos2 = 0;
	char *p = m_pszTopic;
	long nCurr = 0;

	if (!GetSubTopicPos(nIndex, nPos1, nPos2))
	{
		return FALSE;
	}

	long nLen = nPos2 - nPos1;
	memcpy(strText, m_pszTopic + nPos1, nLen);
	strText[nLen] = 0;

	return TRUE;
}

void CSttMqttTopicCmbn::InitTopic(CSttMqttTopicCmbn *pSrc)
{
	ResetSubTopics();
	m_oSubTopics.Append(pSrc->m_oSubTopics);
}

