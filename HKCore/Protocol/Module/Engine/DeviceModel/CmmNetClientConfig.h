#pragma once
#include "CmmNetServerConfig.h"

class CCmmNetClientConfig :	public CCmmNetServerConfig
{
public:
	CCmmNetClientConfig(void);
	virtual ~CCmmNetClientConfig(void);

	CString m_strRemoteIP;
	long    m_nRemotePort;

public:
	virtual UINT GetClassID(){return DMCLASSID_CMMNETCLIENTCONFIG;};
	//´®ÐÐ»¯
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	// ¸´ÖÆ
	virtual BOOL CopyOwn(CBaseObject* pDest);
	//virtual CBaseObject* Clone();

	//2023-4-18 lijunqing
	virtual void SetPort(long nPort)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%08X]:SetPort [%s][%d]"), (unsigned long)this, m_strRemoteIP.GetString()
			, m_nRemotePort);

		m_nRemotePort = nPort;
	}
};
