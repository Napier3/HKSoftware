#pragma once
#include "../../../../module/baseclass/exbaseobject.h"
#include "DeviceClassIDDefine.h"
#include "DeviceModelXmlKeys.h"
#include "CmmConfigBase.h"

class CCmmNetServerConfig :	public CCmmConfigBase
{
public:
	CCmmNetServerConfig(void);
	virtual ~CCmmNetServerConfig(void);

	CString m_strLocalIP;
	long    m_nLocalPort;

	CString m_strClientIP;

	BOOL m_bPostConnectFinishMsgAfterAccept;
public:
	virtual UINT GetClassID(){return DMCLASSID_CMMNETSERVERCONFIG;};

	//´®ÐÐ»¯
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	// ¸´ÖÆ
	virtual BOOL CopyOwn(CBaseObject* pDest);

	//2023-4-18 lijunqing
	virtual void SetPort(long nPort)
	{
		m_nLocalPort = nPort;
	}

};
